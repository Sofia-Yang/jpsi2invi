#!/usr/bin/env python
"""
Following sel_events.py 

Event Selection 
"""

__author__ = "R. Kiuchi <kiuchi@ihep.ac.cn>"
__copyright__ = "Copyright (c) Ryuta Kiuchi"
__created__ = "[2017-05-17 Wed 00:23]" 

import sys
import os
import math 
import ROOT 
from progressbar import Bar, Percentage, ProgressBar
from time import time 
from tools import duration, check_outfile_path

#TEST=True 
TEST=False

# Global constants 
JPSI_MASS = 3.096916; 

# Global histograms

h_evtflw = ROOT.TH1F('hevtflw', 'eventflow', 13, 0, 13) 
h_evtflw.GetXaxis().SetBinLabel(1, 'raw')
h_evtflw.GetXaxis().SetBinLabel(2, '|cos#theta|<0.8')
h_evtflw.GetXaxis().SetBinLabel(3, '|p|<0.45') 
h_evtflw.GetXaxis().SetBinLabel(4, 'PID') 
h_evtflw.GetXaxis().SetBinLabel(5, 'cos#theta_{#pi^{+}#pi^{-}}<0.95') 
h_evtflw.GetXaxis().SetBinLabel(6, 'cos#theta_{#pi#pi sys}<0.9') 
h_evtflw.GetXaxis().SetBinLabel(7, '3<M_{#pi#pi}^{rec}<3.2') 
h_evtflw.GetXaxis().SetBinLabel(8, '|cos#theta|<0.8')
h_evtflw.GetXaxis().SetBinLabel(9, '0.45<|p_{lp}|<2.0')
h_evtflw.GetXaxis().SetBinLabel(10, '0.45<|p_{lm}|<2.0')


h_mrecpipi_el = ROOT.TH1D('h_mrecpipi_el', 'mrecpipi_el', 100, 3.04, 3.16)
#h_mrecpipi_el_fit = ROOT.TH1D('h_mrecpipi_el_fit', 'mrecpipi_el_fit', 7000, 3.03, 3.17)
h_mrecpipi_el_fit = ROOT.TH1D('h_mrecpipi_el_fit', 'mrecpipi_el_fit', 400, 3.00, 3.20)
h_mpipi_el = ROOT.TH1D('h_mpipi_el', 'mpipi_el', 100, 0.2, 0.7) 
h_pip_p_el = ROOT.TH1D('h_pip_p_el', 'pip_p_el', 100, 0.0, 0.5) 
h_pim_p_el = ROOT.TH1D('h_pim_p_el', 'pim_p_el', 100, 0.0, 0.5) 
h_pip_costhe_el = ROOT.TH1D('h_pip_costhe_el', 'pip_costhe_el', 100, -1.0, 1.0)
h_pim_costhe_el = ROOT.TH1D('h_pim_costhe_el', 'pim_costhe_el', 100, -1.0, 1.0)
h_cospipi_el = ROOT.TH1D('h_cospipi_el', 'cospipi_el', 200, -1.0, 1.0)
h_cos2pisys_el = ROOT.TH1D('h_cos2pisys_el', 'cos2pisys_el', 100, -1.0, 1.0)

h_mrecpipi_mu = ROOT.TH1D('h_mrecpipi_mu', 'mrecpipi_mu', 100, 3.04, 3.16)
h_mpipi_mu = ROOT.TH1D('h_mpipi_mu', 'mpipi_mu', 100, 0.2, 0.7) 
h_pip_p_mu = ROOT.TH1D('h_pip_p_mu', 'pip_p_mu', 100, 0.0, 0.5) 
h_pim_p_mu = ROOT.TH1D('h_pim_p_mu', 'pim_p_mu', 100, 0.0, 0.5) 
h_pip_costhe_mu = ROOT.TH1D('h_pip_costhe_mu', 'pip_costhe_mu', 100, -1.0, 1.0)
h_pim_costhe_mu = ROOT.TH1D('h_pim_costhe_mu', 'pim_costhe_mu', 100, -1.0, 1.0)
h_cospipi_mu = ROOT.TH1D('h_cospipi_mu', 'cospipi_mu', 200, -1.0, 1.0)
h_cos2pisys_mu = ROOT.TH1D('h_cos2pisys_mu', 'cos2pisys_mu', 100, -1.0, 1.0)
h_ngam_mu = ROOT.TH1D('h_ngam_mu', 'ngam_mu', 10, 0, 10)

h_melel = ROOT.TH1D('h_melel', 'melel', 100, 2.5, 3.5) 
h_elp_p = ROOT.TH1D('h_elp_p', 'elp_p', 100, 1.0, 2.0) 
h_elm_p = ROOT.TH1D('h_elm_p', 'elm_p', 100, 1.0, 2.0) 
h_elp_costhe = ROOT.TH1D('h_elp_costhe', 'elp_costhe', 100, -1.0, 1.0)
h_elm_costhe = ROOT.TH1D('h_elm_costhe', 'elm_costhe', 100, -1.0, 1.0)
h_coselel = ROOT.TH1D('h_coselel', 'coselel', 200, -1.0, 1.0)

h_mmumu = ROOT.TH1D('h_mmumu', 'mmumu', 100, 2.5, 3.5) 
h_mup_p = ROOT.TH1D('h_mup_p', 'mup_p', 100, 1.0, 2.0) 
h_mum_p = ROOT.TH1D('h_mum_p', 'mum_p', 100, 1.0, 2.0) 
h_mup_costhe = ROOT.TH1D('h_mup_costhe', 'mup_costhe', 100, -1.0, 1.0)
h_mum_costhe = ROOT.TH1D('h_mum_costhe', 'mum_costhe', 100, -1.0, 1.0)
h_cosmumu = ROOT.TH1D('h_cosmumu', 'cosmumu', 200, -1.0, 1.0)

h_EOP = ROOT.TH2D('h_EOP', 'EOP', 100, 0.0, 1.5, 100, 0.0, 1.5)


def usage():
    sys.stdout.write('''
NAME
    sel_events_lplm.py 

SYNOPSIS

    ./sel_events_lplm.py infile outfile 

AUTHOR 
    R. Kiuchi <kiuchi@ihep.ac.cn>
DATE
    May 2017 
\n''')

    
def main():

    if TEST:
        sys.stdout.write('Run in TEST mode! \n')
    
    args = sys.argv[1:]
    if len(args) < 2:
        return usage()
    
    infile = args[0]
    outfile = args[1]
    check_outfile_path(outfile)

    fin = ROOT.TFile(infile)
    t = fin.Get('tree')
    entries = t.GetEntriesFast()

    pbar = ProgressBar(widgets=[Percentage(), Bar()], maxval=entries).start()
    time_start = time()

    for jentry in xrange(entries):
        pbar.update(jentry+1)
        # get the next tree in the chain and verify
        ientry = t.LoadTree(jentry)
        if ientry < 0:
            break
        # copy next entry into memory and verify

        if TEST and ientry > 10000:
            break
        
        nb = t.GetEntry(jentry)
        if nb<=0:
            continue

        fill_histograms(t)
        
        if select_jpsi_to_ll(t): 
            
            cut_mu_eop_p = (abs(t.trklp_eraw/t.trklp_p) < 0.26)
            cut_mu_eop_m = (abs(t.trklm_eraw/t.trklm_p) < 0.26)

            cut_el_eop_p = (abs(t.trklp_eraw/t.trklp_p) > 0.80)
            cut_el_eop_m = (abs(t.trklm_eraw/t.trklm_p) > 0.80)
            cut_el_eop_pm = (math.sqrt( math.pow((t.trklp_eraw/t.trklp_p)-1 , 2)
                                        +math.pow((t.trklm_eraw/t.trklm_p)-1 , 2) ) < 0.4)
            
            eop1 = abs(t.trklp_eraw/t.trklp_p)
            eop2 = abs(t.trklm_eraw/t.trklm_p)
            h_EOP.Fill(eop1, eop2)

            cut_invMass_el = (t.vtx_melel > 2.7 and t.vtx_melel < 3.2)
            cut_invMass_mu = (t.vtx_mmumu > 3.0 and t.vtx_mmumu < 3.2)
            cut_invMass_mu_ngam = (t.vtx_mmumu > 3.08 and t.vtx_mmumu < 3.2)

            if (t.jpsi2elel_flag == 1 and (cut_el_eop_p or cut_el_eop_m or cut_el_eop_pm) and cut_invMass_el):
                h_mrecpipi_el.Fill(t.vtx_mrecpipi)
                h_mrecpipi_el_fit.Fill(t.vtx_mrecpipi)
                h_melel.Fill(t.vtx_melel)
                h_elp_p.Fill(t.vtx_elp_p)
                h_elm_p.Fill(t.vtx_elm_p)
                h_elp_costhe.Fill(t.vtx_elp_costheta)
                h_elm_costhe.Fill(t.vtx_elm_costheta)
                h_coselel.Fill(t.vtx_coselel)

            if (t.jpsi2mumu_flag == 1 and (cut_mu_eop_p and cut_mu_eop_m) and cut_invMass_mu):
                h_mrecpipi_mu.Fill(t.vtx_mrecpipi)
                h_mmumu.Fill(t.vtx_mmumu)
                h_mup_p.Fill(t.vtx_mup_p)
                h_mum_p.Fill(t.vtx_mum_p)
                h_mup_costhe.Fill(t.vtx_mup_costheta)
                h_mum_costhe.Fill(t.vtx_mum_costheta)
                h_cosmumu.Fill(t.vtx_cosmumu)

            if (t.jpsi2mumu_flag == 1 and (cut_mu_eop_p and cut_mu_eop_m) and cut_invMass_mu):
                h_ngam_mu.Fill(t.ngam)

    fout = ROOT.TFile(outfile, "RECREATE")
    write_histograms() 
    fout.Close()
    pbar.finish()
    
    dur = duration(time()-time_start)
    sys.stdout.write(' \nDone in %s. \n' % dur) 


def fill_histograms(t):
    #cut_ngam = (t.ngam == 0)
    # Pion Side
    cut_trkpip_costhe = (abs(math.cos(t.trkpip_theta)) < 0.8)
    cut_trkpim_costhe = (abs(math.cos(t.trkpim_theta)) < 0.8)
    cut_trkpip_p = (abs(t.trkpip_p) < 0.45) 
    cut_trkpim_p = (abs(t.trkpim_p) < 0.45)
    cut_cospipi =  (t.vtx_cospipi < 0.95)
    cut_cos2pisys = (abs(t.vtx_cos2pisys) < 0.9)
    cut_pi_PID = (t.prob_pip > t.prob_kp and t.prob_pip > 0.001 and
                  t.prob_pim > t.prob_km and t.prob_pim > 0.001)
    cut_mjpsi_win = (t.vtx_mrecpipi > 3.0 and t.vtx_mrecpipi < 3.2)
    cut_mjpsi_sig = (abs(t.vtx_mrecpipi - JPSI_MASS)<0.015)

    # Lepton Side
    cut_trklp_costhe = (abs(math.cos(t.trklp_theta)) < 0.8)
    cut_trklm_costhe = (abs(math.cos(t.trklm_theta)) < 0.8)

    cut_mu_eop_p = (abs(t.trklp_eraw/t.trklp_p) < 0.26)
    cut_mu_eop_m = (abs(t.trklm_eraw/t.trklm_p) < 0.26)

    cut_el_eop_p = (abs(t.trklp_eraw/t.trklp_p) > 0.80)
    cut_el_eop_m = (abs(t.trklm_eraw/t.trklm_p) > 0.80)
    cut_el_eop_pm = (math.sqrt( math.pow((t.trklp_eraw/t.trklp_p)-1 , 2)
                                +math.pow((t.trklm_eraw/t.trklm_p)-1 , 2) ) < 0.4)

    if (cut_trkpip_costhe and cut_trkpim_costhe and cut_trkpip_p and cut_trkpim_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_sig 
        and cut_trklp_costhe and cut_trklm_costhe):
        if (t.jpsi2elel_flag == 1 and (cut_el_eop_p or cut_el_eop_m or cut_el_eop_pm)):
            h_mpipi_el.Fill(t.vtx_mpipi)
        if (t.jpsi2mumu_flag == 1 and (cut_mu_eop_p and cut_mu_eop_m)):
            h_mpipi_mu.Fill(t.vtx_mpipi)

    if (cut_trkpip_costhe and cut_trkpim_costhe                and cut_trkpim_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_sig
        and cut_trklp_costhe and cut_trklm_costhe):
        if (t.jpsi2elel_flag == 1 and (cut_el_eop_p or cut_el_eop_m or cut_el_eop_pm)):
            h_pip_p_el.Fill(t.trkpip_p)
        if (t.jpsi2mumu_flag == 1 and (cut_mu_eop_p and cut_mu_eop_m)):
            h_pip_p_mu.Fill(t.trkpip_p)

    if (cut_trkpip_costhe and cut_trkpim_costhe and cut_trkpip_p                and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_sig
        and cut_trklp_costhe and cut_trklm_costhe):
        if (t.jpsi2elel_flag == 1 and (cut_el_eop_p or cut_el_eop_m or cut_el_eop_pm)):
            h_pim_p_el.Fill(t.trkpim_p)
        if (t.jpsi2mumu_flag == 1 and (cut_mu_eop_p and cut_mu_eop_m)):
            h_pim_p_mu.Fill(t.trkpim_p)

    if (                      cut_trkpim_costhe and cut_trkpip_p and cut_trkpim_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_sig
        and cut_trklp_costhe and cut_trklm_costhe):
        if (t.jpsi2elel_flag == 1 and (cut_el_eop_p or cut_el_eop_m or cut_el_eop_pm)):
            h_pip_costhe_el.Fill(math.cos(t.trkpip_theta))
        if (t.jpsi2mumu_flag == 1 and (cut_mu_eop_p and cut_mu_eop_m)):
            h_pip_costhe_mu.Fill(math.cos(t.trkpip_theta))

    if (cut_trkpip_costhe                       and cut_trkpip_p and cut_trkpim_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_sig
        and cut_trklp_costhe and cut_trklm_costhe):
        if (t.jpsi2elel_flag == 1 and (cut_el_eop_p or cut_el_eop_m or cut_el_eop_pm)):
            h_pim_costhe_el.Fill(math.cos(t.trkpim_theta))
        if (t.jpsi2mumu_flag == 1 and (cut_mu_eop_p and cut_mu_eop_m)):
            h_pim_costhe_mu.Fill(math.cos(t.trkpim_theta))
        
    if (cut_trkpip_costhe and cut_trkpim_costhe and cut_trkpip_p and cut_trkpim_p and
                        cut_cos2pisys and cut_pi_PID and cut_mjpsi_sig
        and cut_trklp_costhe and cut_trklm_costhe):
        if (t.jpsi2elel_flag == 1 and (cut_el_eop_p or cut_el_eop_m or cut_el_eop_pm)):
            h_cospipi_el.Fill(t.vtx_cospipi)
        if (t.jpsi2mumu_flag == 1 and (cut_mu_eop_p and cut_mu_eop_m)):
            h_cospipi_mu.Fill(t.vtx_cospipi)

    if (cut_trkpip_costhe and cut_trkpim_costhe and cut_trkpip_p and cut_trkpim_p and
        cut_cospipi                   and cut_pi_PID and cut_mjpsi_sig
        and cut_trklp_costhe and cut_trklm_costhe):
        if (t.jpsi2elel_flag == 1 and (cut_el_eop_p or cut_el_eop_m or cut_el_eop_pm)):
            h_cos2pisys_el.Fill(t.vtx_cos2pisys)
        if (t.jpsi2mumu_flag == 1 and (cut_mu_eop_p and cut_mu_eop_m)):
            h_cos2pisys_mu.Fill(t.vtx_cos2pisys)
    
def write_histograms():
    h_evtflw.Write()

    h_mrecpipi_el.Write()
    h_mrecpipi_el_fit.Write()
    h_mpipi_el.Write()
    h_pip_p_el.Write()
    h_pim_p_el.Write()
    h_pip_costhe_el.Write()
    h_pim_costhe_el.Write()
    h_cospipi_el.Write()
    h_cos2pisys_el.Write()

    h_mrecpipi_mu.Write()
    h_mpipi_mu.Write()
    h_pip_p_mu.Write()
    h_pim_p_mu.Write()
    h_pip_costhe_mu.Write()
    h_pim_costhe_mu.Write()
    h_cospipi_mu.Write()
    h_cos2pisys_mu.Write()
    h_ngam_mu.Write()

    h_melel.Write()
    h_elp_p.Write() 
    h_elm_p.Write() 
    h_elp_costhe.Write() 
    h_elm_costhe.Write() 
    h_coselel.Write() 

    h_mmumu.Write()
    h_mup_p.Write() 
    h_mum_p.Write() 
    h_mup_costhe.Write() 
    h_mum_costhe.Write() 
    h_cosmumu.Write() 
    
    h_EOP.Write()

def select_jpsi_to_ll(t):
    h_evtflw.Fill(0) 

    # Cut for Pion side
    if not ( abs(math.cos(t.trkpip_theta)) < 0.8 and abs(math.cos(t.trkpim_theta)) < 0.8):
        return False
    h_evtflw.Fill(1) 

    if not (abs(t.trkpip_p) < 0.45 and abs(t.trkpim_p) < 0.45):
        return False 
    h_evtflw.Fill(2) 

    if not (t.prob_pip > t.prob_kp and t.prob_pip > 0.001 and
            t.prob_pim > t.prob_km and t.prob_pim > 0.001):
        return False
    h_evtflw.Fill(3)

    if not (t.vtx_cospipi < 0.95):
        return False
    h_evtflw.Fill(4)

    if not (abs(t.vtx_cos2pisys) < 0.9):
        return False
    h_evtflw.Fill(5)

    if not (t.vtx_mrecpipi > 3.0 and t.vtx_mrecpipi < 3.2):
        return False
    h_evtflw.Fill(6)
    
    # Cut for Lepton side
    if not ( abs(math.cos(t.trklp_theta)) < 0.8 and abs(math.cos(t.trklm_theta)) < 0.8):
        return False
    h_evtflw.Fill(7)

    if not (abs(t.trklp_p) > 0.45 and abs(t.trklp_p) < 2.0):
        return False
    h_evtflw.Fill(8)

    if not (abs(t.trklm_p) > 0.45 and abs(t.trklm_p) < 2.0):
        return False
    h_evtflw.Fill(9)

    return True
    
    
if __name__ == '__main__':
    main()
