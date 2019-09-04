#!/usr/bin/env python
"""
Event Selection 
"""

__author__ = "R. Kiuchi <kiuchi@ihep.ac.cn>"
__copyright__ = "Copyright (c) Ryuta Kiuchi"
__created__ = "[2018-01-29 Tue 18:35]" 

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

h_evtflw = ROOT.TH1F('hevtflw', 'eventflow', 10, 0, 10) 
h_evtflw.GetXaxis().SetBinLabel(1, 'raw')
h_evtflw.GetXaxis().SetBinLabel(2, 'N_{#gamma}=0')
h_evtflw.GetXaxis().SetBinLabel(3, '|cos#theta|<0.8')
h_evtflw.GetXaxis().SetBinLabel(4, '|p|<0.45') 
h_evtflw.GetXaxis().SetBinLabel(5, 'PID') 
h_evtflw.GetXaxis().SetBinLabel(6, 'cos#theta_{#pi^{+}#pi^{-}}<0.95') 
h_evtflw.GetXaxis().SetBinLabel(7, 'cos#theta_{#pi#pi sys}<0.9') 
h_evtflw.GetXaxis().SetBinLabel(8, '3<M_{#pi#pi}^{rec}<3.2') 


h_mrecpipi_zc = ROOT.TH1D('h_mrecpipi_zc', 'mrecpipi_zc', 100, 3.04, 3.16)
h_mrecpipi = ROOT.TH1D('h_mrecpipi', 'mrecpipi', 140, 3.03, 3.17)
h_mpipi = ROOT.TH1D('h_mpipi', 'mpipi', 100, 0.2, 0.7) 
h_pip_p = ROOT.TH1D('h_pip_p', 'pip_p', 100, 0.0, 0.5) 
h_pim_p = ROOT.TH1D('h_pim_p', 'pim_p', 100, 0.0, 0.5) 
h_pip_costhe = ROOT.TH1D('h_pip_costhe', 'pip_costhe', 100, -1.0, 1.0)
h_pim_costhe = ROOT.TH1D('h_pim_costhe', 'pim_costhe', 100, -1.0, 1.0)
h_cospipi = ROOT.TH1D('h_cospipi', 'cospipi', 200, -1.0, 1.0)
h_cos2pisys = ROOT.TH1D('h_cos2pisys', 'cos2pisys', 100, -1.0, 1.0)
h_ngam = ROOT.TH1D('h_ngam', 'ngam', 20, 0, 20)
h_gcostheta = ROOT.TH1D('h_gcostheta', 'gcostheta', 2000, -1.0, 1.0)

h_mgg = ROOT.TH1D('h_mgg', 'mgg', 100, 0.4, 0.7)
#h_mpipigg = ROOT.TH1D('h_mpipigg', 'mpipigg', 100, 0.4, 2.7)
h_ch_count = ROOT.TH1D('h_ch_count', 'ch_count', 22, 0, 22)

def usage():
    sys.stdout.write('''
NAME
    sel_events.py 

SYNOPSIS

    ./sel_events.py infile outfile 

AUTHOR 
    R. Kiuchi <kiuchi@ihep.ac.cn>

DATE
    January 2018 
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


    count0 = 0
    count1 = 0
    count2 = 0
    count3 = 0
    count4 = 0
    count5 = 0
    count6 = 0
    count7 = 0
    count8 = 0
    count9 = 0
    count10 = 0
    count11 = 0
    count12 = 0
    count13 = 0
    count14 = 0
    count15 = 0
    count_EMC_Track = 0
    count_all = 0

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

        #fill_histograms(t)
        
        if select_jpsi_to_gammaEta(t):

            cut_chisq = (t.kmfit_chisq < 60 )
            cut_mjpsi_sig = (abs(t.vtx_mrecpipi - JPSI_MASS)<0.015)
    
            flag = 0
            cut_mgg = 0
            cut_mpipieta = 0
            if ( t.kmfit_g1g2dang < t.kmfit_g1g3dang and t.kmfit_g1g2dang < t.kmfit_g2g3dang ):
                flag = 1
                cut_mgg = (t.kmfit_m_g1g2 > 0.51 and t.kmfit_m_g1g2 < 0.57)
                print t.kmfit_m_g1g2
                cut_mpipieta = (t.kmfit_m_pipig1g2 > 1.0)

            if ( t.kmfit_g1g3dang < t.kmfit_g1g2dang and t.kmfit_g1g3dang < t.kmfit_g2g3dang ):
                flag = 2
                cut_mgg = (t.kmfit_m_g1g3 > 0.51 and t.kmfit_m_g1g3 < 0.57)
                cut_mpipieta = (t.kmfit_m_pipig1g3 > 1.0)

            if ( t.kmfit_g2g3dang < t.kmfit_g1g2dang and t.kmfit_g2g3dang < t.kmfit_g1g3dang ):
                flag = 3
                cut_mgg = (t.kmfit_m_g2g3 > 0.51 and t.kmfit_m_g2g3 < 0.57)
                cut_mpipieta = (t.kmfit_m_pipig2g3 > 1.0)
 
            if ( cut_chisq and cut_mpipieta ):
                if ( cut_mjpsi_sig ):
                    if ( flag == 1 ):
                        h_mgg.Fill(t.kmfit_m_g1g2)
                    if ( flag == 2 ):
                        h_mgg.Fill(t.kmfit_m_g1g3)
                    if ( flag == 3 ):
                        h_mgg.Fill(t.kmfit_m_g2g3)
            
                if ( cut_mgg ):
                    h_mrecpipi_zc.Fill(t.vtx_mrecpipi)
                    h_mpipi.Fill(t.vtx_mpipi)
                    h_pip_p.Fill(t.trkp_p)
                    h_pim_p.Fill(t.trkm_p)
                    h_pip_costhe.Fill(math.cos(t.trkp_theta))
                    h_pim_costhe.Fill(math.cos(t.trkm_theta))
                    h_cospipi.Fill(t.vtx_cospipi)
                    h_cos2pisys.Fill(t.vtx_cos2pisys)
                    ngam = t.ngam       
                    for gentry in range(ngam):
                        h_gcostheta.Fill(t.raw_costheta[gentry])
                    
                if ( cut_mjpsi_sig and cut_mgg and (t.run>0) ):  # Only for data sample
                    ch0 = t.m_trig_channel[0]
                    ch1 = t.m_trig_channel[1]
                    ch2 = t.m_trig_channel[2]
                    ch3 = t.m_trig_channel[3]
                    ch4 = t.m_trig_channel[4]
                    ch5 = t.m_trig_channel[5]
                    ch6 = t.m_trig_channel[6]
                    ch7 = t.m_trig_channel[7]
                    ch8 = t.m_trig_channel[8]
                    ch9 = t.m_trig_channel[9]
                    ch10 = t.m_trig_channel[10]
                    ch11 = t.m_trig_channel[11]
                    ch12 = t.m_trig_channel[12]
                    ch13 = t.m_trig_channel[13]
                    ch14 = t.m_trig_channel[14]
                    ch15 = t.m_trig_channel[15]
                    
                    count0 = count0 + ch0
                    count1 = count1 + ch1
                    count2 = count2 + ch2
                    count3 = count3 + ch3
                    count4 = count4 + ch4
                    count5 = count5 + ch5
                    count6 = count6 + ch6
                    count7 = count7 + ch7
                    count8 = count8 + ch8
                    count9 = count9 + ch9
                    count10 = count10 + ch10
                    count11 = count11 + ch11
                    count12 = count12 + ch12
                    count13 = count13 + ch13
                    count14 = count14 + ch14
                    count15 = count15 + ch15

                    count_all = count_all + 1
                    if( ch11 == 1 and ( ch0==1 or ch1==1 or ch2==1 or ch3==1 or ch4==1 or ch5==1 ) ):
                        count_EMC_Track = count_EMC_Track + 1
                    
                

    h_ch_count.Fill(0, count0);
    h_ch_count.Fill(1, count1);
    h_ch_count.Fill(2, count2);
    h_ch_count.Fill(3, count3);
    h_ch_count.Fill(4, count4);
    h_ch_count.Fill(5, count5);
    h_ch_count.Fill(6, count6);
    h_ch_count.Fill(7, count7);
    h_ch_count.Fill(8, count8);
    h_ch_count.Fill(9, count9);
    h_ch_count.Fill(10, count10);
    h_ch_count.Fill(11, count11);
    h_ch_count.Fill(12, count12);
    h_ch_count.Fill(13, count13);
    h_ch_count.Fill(14, count14);
    h_ch_count.Fill(15, count15);
    h_ch_count.Fill(19, count_EMC_Track);
    h_ch_count.Fill(21, count_all);
    
    
    fout = ROOT.TFile(outfile, "RECREATE")
    write_histograms() 
    fout.Close()
    pbar.finish()

#    print "count0 = " , count0
#    print "count1 = " , count1
#    print "count2 = " , count2
#    print "count3 = " , count3
#    print "count4 = " , count4
#    print "count5 = " , count5
#    print "count6 = " , count6
#    print "count7 = " , count7
#    print "count8 = " , count8
#    print "count9 = " , count9
#    print "count10 = " , count10
#    print "count11 = " , count11
#    print "count12 = " , count12
#    print "count13 = " , count13
#    print "count14 = " , count14
#    print "count15 = " , count15
#    print "count_EMC_Track = " , count_EMC_Track
    
    
    dur = duration(time()-time_start)
    sys.stdout.write(' \nDone in %s. \n' % dur) 


def fill_histograms(t):

    cut_ngam = (t.ngam < 11)
    cut_trkp_costhe = (abs(math.cos(t.trkp_theta)) < 0.8)
    cut_trkm_costhe = (abs(math.cos(t.trkm_theta)) < 0.8)
    cut_trkp_p = (abs(t.trkp_p) < 0.45) 
    cut_trkm_p = (abs(t.trkm_p) < 0.45)
    cut_cospipi =  (t.vtx_cospipi < 0.95)
    cut_cos2pisys = (abs(t.vtx_cos2pisys) < 0.9)
    cut_pi_PID = (t.prob_pip > t.prob_kp and t.prob_pip > 0.001 and
                  t.prob_pim > t.prob_km and t.prob_pim > 0.001)
    cut_mjpsi_win = (t.vtx_mrecpipi > 3.0 and t.vtx_mrecpipi < 3.2)
    cut_mjpsi_sig = (abs(t.vtx_mrecpipi - JPSI_MASS)<0.015)    
 
            
    if (cut_ngam and cut_trkp_costhe and cut_trkm_costhe and cut_trkp_p and cut_trkm_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_sig):
        h_mpipi.Fill(t.vtx_mpipi)

    if (cut_ngam and cut_trkp_costhe and cut_trkm_costhe                and cut_trkm_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_sig):
        h_pip_p.Fill(t.trkp_p)

    if (cut_ngam and cut_trkp_costhe and cut_trkm_costhe and cut_trkp_p                and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_sig):
        h_pim_p.Fill(t.trkm_p)

    if (cut_ngam and                     cut_trkm_costhe and cut_trkp_p and cut_trkm_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_sig):
        h_pip_costhe.Fill(math.cos(t.trkp_theta))

    if (cut_ngam and cut_trkp_costhe                     and cut_trkp_p and cut_trkm_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_sig):
        h_pim_costhe.Fill(math.cos(t.trkm_theta))

        
    if (cut_ngam and cut_trkp_costhe and cut_trkm_costhe and cut_trkp_p and cut_trkm_p and
                        cut_cos2pisys and cut_pi_PID and cut_mjpsi_sig):
        h_cospipi.Fill(t.vtx_cospipi)

    if (cut_ngam and cut_trkp_costhe and cut_trkm_costhe and cut_trkp_p and cut_trkm_p and
        cut_cospipi                   and cut_pi_PID and cut_mjpsi_sig):
        h_cos2pisys.Fill(t.vtx_cos2pisys)

    if (             cut_trkp_costhe and cut_trkm_costhe and cut_trkp_p and cut_trkm_p and
        cut_cospipi and cut_cos2pisys and cut_pi_PID and cut_mjpsi_sig):
        h_ngam.Fill(t.ngam)
        
        ngam = t.ngam
        #print ngam
        for gentry in range(ngam):
            h_gcostheta.Fill(t.raw_costheta[gentry])
    
def write_histograms():
    h_evtflw.Write()
    h_mrecpipi.Write()
    h_mrecpipi_zc.Write()    
    h_mpipi.Write()
    h_pip_p.Write()
    h_pim_p.Write()
    h_pip_costhe.Write()
    h_pim_costhe.Write()
    h_cospipi.Write()
    h_cos2pisys.Write()
    h_ngam.Write()
    h_gcostheta.Write()

    h_mgg.Write()
    h_ch_count.Write()

def select_jpsi_to_gammaEta(t):
    h_evtflw.Fill(0) 
    
    # Cut on the number of good photon to make the same condition as Z.C.
    if not (t.ngam < 10):
        return False
    h_evtflw.Fill(1) 
    
    # Selection Criteria for soft pions -- the same as invisible etc.
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
