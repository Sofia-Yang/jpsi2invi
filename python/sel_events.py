#!/usr/bin/env python
"""
Event Selection 
"""

__author__ = "SHI Xin <shixin@ihep.ac.cn>"
__copyright__ = "Copyright (c) SHI Xin"
__created__ = "[2016-06-28 Tue 09:09]" 

import sys
import os
import math 
import ROOT 
from progressbar import Bar, Percentage, ProgressBar
from time import time 
from tools import duration, check_outfile_path
from array import array


#TEST=True 
TEST=False

# Global constants 
JPSI_MASS = 3.096916; 

# Global histograms

h_evtflw = ROOT.TH1F('hevtflw', 'eventflow', 10, 0, 10) 
h_evtflw.GetXaxis().SetBinLabel(1, 'raw')
h_evtflw.GetXaxis().SetBinLabel(2, 'N_{#gamma}=0')
h_evtflw.GetXaxis().SetBinLabel(3, '|cos#theta|<0.8')
h_evtflw.GetXaxis().SetBinLabel(4, '|p|<0.45') 
h_evtflw.GetXaxis().SetBinLabel(5, 'PID') 
h_evtflw.GetXaxis().SetBinLabel(6, 'cos#theta_{#pi^{+}#pi^{-}}<0.95') 
h_evtflw.GetXaxis().SetBinLabel(7, 'cos#theta_{#pi#pi sys}<0.9') 
h_evtflw.GetXaxis().SetBinLabel(8, '3<M_{#pi#pi}^{rec}<3.2') 

h_mrecpipi = ROOT.TH1D('h_mrecpipi', 'mrecpipi', 100, 3.03, 3.17)
h_mrecpipi_fit = ROOT.TH1D('h_mrecpipi_fit', 'mrecpipi_fit', 1400, 3.03, 3.17)
h_mpipi = ROOT.TH1D('h_mpipi', 'mpipi', 100, 0.2, 0.7) 
h_pid_pip = ROOT.TH1D('h_pid_pip', 'pid_pip', 100, 0.0, 1.0)
h_pid_pim = ROOT.TH1D('h_pid_pim', 'pid_pim', 100, 0.0, 1.0)
h_pid_kp = ROOT.TH1D('h_pid_kp', 'pid_kp', 100, 0.0, 1.0)
h_pid_km = ROOT.TH1D('h_pid_km', 'pid_km', 100, 0.0, 1.0)
h_pid_pip_no = ROOT.TH1D('h_pid_pip_no', 'pid_pip_no', 100, 0.0, 1.0)
h_pid_pim_no = ROOT.TH1D('h_pid_pim_no', 'pid_pim_no', 100, 0.0, 1.0)
h_pid_kp_no = ROOT.TH1D('h_pid_kp_no', 'pid_kp_no', 100, 0.0, 1.0)
h_pid_km_no = ROOT.TH1D('h_pid_km_no', 'pid_km_no', 100, 0.0, 1.0)
h_pip_p = ROOT.TH1D('h_pip_p', 'pip_p', 100, 0.0, 0.5) 
h_pim_p = ROOT.TH1D('h_pim_p', 'pim_p', 100, 0.0, 0.5) 
h_pip_m = ROOT.TH1D('h_pip_m', 'pip_m', 100, 0.0, 0.5) 
h_pim_m = ROOT.TH1D('h_pim_m', 'pim_m', 100, 0.0, 0.5) 
h_pip_phi = ROOT.TH1D('h_pip_phi', 'pip_phi', 100, -3.3, 3.3)
h_pim_phi = ROOT.TH1D('h_pim_phi', 'pim_phi', 100, -3.3, 3.3)
h_pip_costhe = ROOT.TH1D('h_pip_costhe', 'pip_costhe', 100, -1.0, 1.0)
h_pim_costhe = ROOT.TH1D('h_pim_costhe', 'pim_costhe', 100, -1.0, 1.0)
h_mc_costhe_pip = ROOT.TH1D('h_mc_costhe_pip', 'mc_costhe_pip', 100, -1.0, 1.0)
h_mc_costhe_pim = ROOT.TH1D('h_mc_costhe_pim', 'mc_costhe_pim', 100, -1.0, 1.0)
h_cospipi = ROOT.TH1D('h_cospipi', 'cospipi', 200, -1.0, 1.0)
#h_cospipi = ROOT.TH1D('h_cospipi', 'cospipi', 100, 0.0, 1.0)
h_cos2pisys = ROOT.TH1D('h_cos2pisys', 'cos2pisys', 100, -1.0, 1.0)
h_ngam = ROOT.TH1D('h_ngam', 'ngam', 100, 0, 20)

prob_pip = array('d', [999.])
prob_kp = array('d', [999.])
prob_pim = array('d', [999.])
prob_km = array('d', [999.])

prob_pip_no = array('d', [999.])
prob_kp_no = array('d', [999.])
prob_pim_no = array('d', [999.])
prob_km_no = array('d', [999.])

n_run = array('i',[0])
n_event = array('i',[0])
n_indexmc = array('i',[0])
n_pdgid = array('i',100*[-99])
n_motheridx = array('i',100*[-99])

ROOT.gROOT.ProcessLine(


"struct MyTreeStruct{\
   Double_t vtx_mrecpipi;\
};"	);


def usage():
    sys.stdout.write('''
NAME
    sel_events.py 

SYNOPSIS

    ./sel_events.py infile outfile 

AUTHOR 
    SHI Xin <shixin@ihep.ac.cn> 

DATE
    July 2016 
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

    fout = ROOT.TFile(outfile, "RECREATE")
    t_out = ROOT.TTree('signal', 'signal')
    t_out.Branch('run', n_run, 'run/I')
    t_out.Branch('event', n_event, 'event/I')
    t_out.Branch('indexmc', n_indexmc, 'indexmc/I')
    t_out.Branch('pdgid', n_pdgid, 'pdgid[100]/I')
    t_out.Branch('motheridx', n_motheridx, 'motheridx[100]/I')
    t_out.Branch('prob_pip', prob_pip, 'prob_pip/D')
    t_out.Branch('prob_kp', prob_kp, 'prob_kp/D')
    t_out.Branch('prob_pim', prob_pim, 'prob_pim/D')
    t_out.Branch('prob_km', prob_km, 'prob_km/D')

    t_out_2 = ROOT.TTree('pid', 'pid')
    t_out_2.Branch('prob_pip_no', prob_pip_no, 'prob_pip_no/D')
    t_out_2.Branch('prob_kp_no', prob_kp_no, 'prob_kp_no/D')
    t_out_2.Branch('prob_pim_no', prob_pim_no, 'prob_pim_no/D')
    t_out_2.Branch('prob_km_no', prob_km_no, 'prob_km_no/D')

    mystruct = ROOT.MyTreeStruct()
    t_out.Branch('vtx_mrecpipi', mystruct, 'vtx_mrecpipi/D')

    pbar = ProgressBar(widgets=[Percentage(), Bar()], maxval=entries).start()
    time_start = time()

    # mystruct = ROOT.MyTreeStruct()

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

        # if t.run > 25600:
        #     continue
        # if (t.run > 26200 or t.run < 25600 ):
        #     continue
      #   if (t.run > 26600 or t.run < 26200 ):
      #       continue
      #   if (t.run > 26900 or t.run < 26600 ):
      #       continue
       #  if t.run < 26900:
       #      continue

        # if t.run < 10000:
        if t.run > 10000:
            continue
        
        fill_histograms(t, t_out, t_out_2)
        
        if select_jpsi_to_invisible(t): 
            h_mrecpipi.Fill(t.vtx_mrecpipi)
            h_mrecpipi_fit.Fill(t.vtx_mrecpipi)
            mystruct.vtx_mrecpipi = t.vtx_mrecpipi
            t_out.Fill()
 
    # fout = ROOT.TFile(outfile, "RECREATE")
    t_out.Write()
    t_out_2.Write()
    write_histograms() 
    fout.Close()
    pbar.finish()
    
    dur = duration(time()-time_start)
    sys.stdout.write(' \nDone in %s. \n' % dur) 


def fill_histograms(t, t_out, t_out_2):
    cut_ngam = (t.ngam == 0)
    cut_trkp_costhe = (abs(math.cos(t.trkp_theta)) < 0.8)
    cut_trkm_costhe = (abs(math.cos(t.trkm_theta)) < 0.8)
    cut_trkp_p = (abs(t.trkp_p) < 0.45) 
    cut_trkm_p = (abs(t.trkm_p) < 0.45)
    cut_cospipi =  (t.vtx_cospipi < 0.95)
    cut_cos2pisys = (abs(t.vtx_cos2pisys) < 0.9)
    cut_pi_PID = (t.prob_pip > t.prob_kp and t.prob_pip > 0.001 and
                  t.prob_pim > t.prob_km and t.prob_pim > 0.001)
    # cut_pi_PID = (t.prob_pip > t.prob_kp  and t.prob_pim > t.prob_km )
    cut_mjpsi_win = (t.vtx_mrecpipi > 3.0 and t.vtx_mrecpipi < 3.2)
    cut_mjpsi_sig = (abs(t.vtx_mrecpipi - JPSI_MASS)<0.015)

    if (cut_ngam and cut_trkp_costhe and cut_trkm_costhe and cut_trkp_p and cut_trkm_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_win):
        h_mpipi.Fill(t.vtx_mpipi)
        h_pip_m.Fill(t.vtx_pip_e)
        h_pim_m.Fill(t.vtx_pim_e)
        h_pip_phi.Fill(t.vtx_pip_phi)
        h_pim_phi.Fill(t.vtx_pim_phi)

        n_run[0] = t.run
		# print n_run[0]
        n_event[0] = t.event
        if (t.run<0):
            n_indexmc[0] = t.indexmc
            for ii in range(t.indexmc):
                if (t.m_pdgid[ii] != -22): 
                    n_pdgid[ii] = t.m_pdgid[ii]
                    n_motheridx[ii] = t.m_motheridx[ii]
        prob_pip[0] = t.prob_pip
        prob_pim[0] = t.prob_pim
        prob_kp[0] = t.prob_kp
        prob_km[0] = t.prob_km
        h_pid_pip.Fill(t.prob_pip)
        h_pid_kp.Fill(t.prob_kp)
        h_pid_pim.Fill(t.prob_pim)
        h_pid_km.Fill(t.prob_km)

    if (cut_ngam and cut_trkp_costhe and cut_trkm_costhe and cut_trkp_p and cut_trkm_p and
        cut_cospipi and cut_cos2pisys and                 cut_mjpsi_win):
        prob_pip_no[0] = t.prob_pip
        prob_pim_no[0] = t.prob_pim
        prob_kp_no[0] = t.prob_kp
        prob_km_no[0] = t.prob_km
        h_pid_pip_no.Fill(t.prob_pip)
        h_pid_pim_no.Fill(t.prob_pim)
        h_pid_kp_no.Fill(t.prob_kp)
        h_pid_km_no.Fill(t.prob_km)
        t_out_2.Fill()

    if (cut_ngam and cut_trkp_costhe and cut_trkm_costhe                and cut_trkm_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_win):
        h_pip_p.Fill(t.trkp_p)

    if (cut_ngam and cut_trkp_costhe and cut_trkm_costhe and cut_trkp_p                and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_win):
        h_pim_p.Fill(t.trkm_p)

    if (cut_ngam and                     cut_trkm_costhe and cut_trkp_p and cut_trkm_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_win):
        h_pip_costhe.Fill(math.cos(t.trkp_theta))

    if (cut_ngam and cut_trkp_costhe                     and cut_trkp_p and cut_trkm_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_win):
        h_pim_costhe.Fill(math.cos(t.trkm_theta))

        
    if (cut_ngam and cut_trkp_costhe and cut_trkm_costhe and cut_trkp_p and cut_trkm_p and
                        cut_cos2pisys and cut_pi_PID and cut_mjpsi_win):
        h_cospipi.Fill(t.vtx_cospipi)

    if (cut_ngam and cut_trkp_costhe and cut_trkm_costhe and cut_trkp_p and cut_trkm_p and
        cut_cospipi                   and cut_pi_PID and cut_mjpsi_win):
        h_cos2pisys.Fill(t.vtx_cos2pisys)

    if (             cut_trkp_costhe and cut_trkm_costhe and cut_trkp_p and cut_trkm_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_win):
        h_ngam.Fill(t.ngam)

    # h_mc_costhe_pim.Fill(t.mc_costhe_pim)
    # h_mc_costhe_pip.Fill(t.mc_costhe_pip)
    
def write_histograms():
    h_evtflw.Write()
    h_mrecpipi.Write()
    h_mrecpipi_fit.Write()
    h_mpipi.Write()
    h_pid_pip.Write()
    h_pid_kp.Write()
    h_pid_pim.Write()
    h_pid_km.Write()
    h_pid_pip_no.Write()
    h_pid_kp_no.Write()
    h_pid_pim_no.Write()
    h_pid_km_no.Write()
    h_pip_p.Write()
    h_pim_p.Write()
    h_pip_m.Write()
    h_pim_m.Write()
    h_pip_phi.Write()
    h_pim_phi.Write()
    h_pip_costhe.Write()
    h_pim_costhe.Write()
    h_mc_costhe_pip.Write()
    h_mc_costhe_pim.Write()
    h_cospipi.Write()
    h_cos2pisys.Write()
    h_ngam.Write()

    
def select_jpsi_to_invisible(t):
    h_evtflw.Fill(0) 

    if not (t.ngam == 0):
        return False
    h_evtflw.Fill(1) 
    
    if not ( abs(math.cos(t.trkp_theta)) < 0.8 and abs(math.cos(t.trkm_theta)) < 0.8):
        return False
    h_evtflw.Fill(2) 

    if not (abs(t.trkp_p) < 0.45 and abs(t.trkm_p) < 0.45):
        return False 
    h_evtflw.Fill(3) 

    if not (t.prob_pip > t.prob_kp and t.prob_pip > 0.001 and
            t.prob_pim > t.prob_km and t.prob_pim > 0.001):
        return False
    h_evtflw.Fill(4)

    if not (t.vtx_cospipi < 0.95):
        return False
    h_evtflw.Fill(5)

    if not (abs(t.vtx_cos2pisys) < 0.9):
        return False
    h_evtflw.Fill(6)

    if not (t.vtx_mrecpipi > 3.0 and t.vtx_mrecpipi < 3.2):
        return False
    h_evtflw.Fill(7)
    
    return True
    
    
if __name__ == '__main__':
    main()
