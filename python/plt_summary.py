#!/usr/bin/env python
"""
Plot summary histograms 
"""

__author__ = "SHI Xin <shixin@ihep.ac.cn>"
__copyright__ = "Copyright (c) SHI Xin"
__created__ = "[2016-07-25 Mon 09:22]" 

import os
import sys 
import ROOT 
from tools import check_outfile_path, set_root_style


def main():
    set_root_style(stat=0, grid=0) 
    ROOT.gStyle.SetPadLeftMargin(0.15)

    sample = sys.argv[1:]
    fs = get_files_from_sample(sample)
    c = ROOT.TCanvas('c', 'c', 800, 800)

    draw_mrecpipi(sample, c, fs)
    draw_mpipi(sample, c, fs)
    draw_pip_p(sample, c, fs) 
    draw_pim_p(sample, c, fs) 
    draw_pip_costhe(sample, c, fs) 
    draw_pim_costhe(sample, c, fs)
    draw_cospipi(sample, c, fs) 
    draw_cos2pisys(sample, c, fs)
    draw_ngam(sample, c, fs)
    

def get_files_from_sample(sample):
    fs = [] 
    if 'hist' in sample:
        # fs.append(ROOT.TFile('run/jpsi2invi/hist/jpsi2invi_data_psip_data12_event_merged_1.root'))
        fs.append(ROOT.TFile('run/jpsi2invi/hist/jpsi2invi_data_psip_data12_event_merged_phi.root'))

    if 'hist_incl' in sample:
        # fs.append(ROOT.TFile('run/jpsi2incl/hist/jpsi2incl_data_psip_data12_event_merged_1.root'))
        fs.append(ROOT.TFile('run/jpsi2incl/hist/jpsi2incl_data_psip_data12_event_merged_phi.root'))
    
    if 'mc12' in sample:
	    fs.append(ROOT.TFile('run/jpsi2invi/hist_mc12/jpsi2invi_psip_mc12_event_merged_1.root'))

    if 'mc12_incl' in sample:
	    fs.append(ROOT.TFile('run/jpsi2incl/hist_mc12/jpsi2incl_psip_mc12_event_merged_1.root'))

    if 'data3650' in sample:
		fs.append(ROOT.TFile('run/jpsi2invi/hist_data3650/jpsi2invi_data3650_event_merged_1.root'))

    if 'data09' in sample:
        fs.append(ROOT.TFile('run/hist/data09/jpsi2invi_data09_merged_1.root'))

    if 'mc_psip09' in sample:
        fs.append(ROOT.TFile('run/hist/mc_psip09/jpsi2invi_mc_psip_09mc_merged_1.root'))
        
    if 'mc_psip12' in sample:
        fs.append(ROOT.TFile('run/hist/mc_psip12/jpsi2invi_mc_psip_12mc_merged_1.root'))
        
    return fs 

def get_common_objects_to_draw(fs, hname, leg):
    hs = []

    leg.SetTextSize(0.03)
    leg.SetFillColor(0)
    leg.SetFillStyle(0)
    leg.SetLineColor(0)
    leg.SetShadowColor(0)
    
    for f in fs:
        h = f.Get(hname)
        if fs.index(f) == 0:
            #h.Sumw2()
            h.GetXaxis().SetLabelSize(0.03) 
            h.GetYaxis().SetLabelSize(0.03) 
            h.GetYaxis().SetTitleOffset(1.8) 
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            
        elif fs.index(f) == 1:
            h.SetLineColor(29)
            h.SetFillColor(29)

        elif fs.index(f) == 2:
            h.SetLineColor(ROOT.kOrange)
            h.SetFillColor(ROOT.kOrange)
            
        leg = leg_add_entry_hist(leg, f, h)    
        hs.append(h) 
            
    return  hs, leg 


def leg_add_entry_hist(leg, f, h):
    sample = f.GetName()
    sample = sample.split('/')[2] 

    if sample in ['data' or 'data09']:
        leg.AddEntry(h, "Data", "lp")

    elif sample in ['hist']:
        leg.AddEntry(h, "hist")

    elif sample in ['hist_incl']:
        leg.AddEntry(h, "hist_incl")

    elif sample in ['hist_mc12']:
        leg.AddEntry(h, "hist_mc12")

    elif sample in ['hist_mc12_incl']:
        leg.AddEntry(h, "hist_mc12_incl")

    elif sample in ['hist_data3650']:
        leg.AddEntry(h, "hist_data3650")

    elif sample in ['mc_psip12', 'mc_psip09']:
        leg.AddEntry(h, "#psi(2S) inclusive MC")
    else:
        raise NameError(sample)

    return leg


def draw_mrecpipi(sample, c, fs):
    hname = 'h_mrecpipi'
    figfile = 'doc/fig/jpsi2invi_mrecpipi_%s.pdf' %'_'.join(sample)
    check_outfile_path(figfile)
        
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 

    for h in hs:
        if hs.index(h) == 0:
            h.SetXTitle('M(recoil(#pi^{+}#pi^{-})) (GeV/c^{2})') 
            h.SetYTitle('Events/(0.0012 GeV/c^{2})')
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
        else:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)

    
def draw_mpipi(sample, c, fs):
    hname = 'h_mpipi'
    figfile = 'doc/fig/jpsi2invi_mpipi_%s.pdf' %'_'.join(sample) 
        
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 
    
    for h in hs:
        if hs.index(h) == 0:
            h.SetXTitle('M(#pi^{+}#pi^{-}) (GeV/c^{2})') 
            h.SetYTitle('Events/(0.0012 GeV/c^{2})')
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
        else:
            h.Draw('same')

    leg.Draw()
    c.SaveAs(figfile)


def draw_pip_p(sample, c, fs):
    hname = 'h_pip_p'
    figfile = 'doc/fig/jpsi2invi_pip_p_%s.pdf'  %'_'.join(sample) 
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 

    for h in hs:
        if hs.index(h) == 0:
            h.SetXTitle('P(#pi^{+}) (GeV/c)')
            h.SetYTitle('Events/(0.005 GeV/c)') 
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
        else:
            h.Draw('same') 

    leg.Draw()
    c.SaveAs(figfile)


def draw_pim_p(sample, c, fs):
    hname = 'h_pim_p'
    figfile = 'doc/fig/jpsi2invi_pim_p_%s.pdf'  %'_'.join(sample) 
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 
    
    for h in hs:
        if hs.index(h) == 0:
            h.SetXTitle('P(#pi^{-}) (GeV/c)')
            h.SetYTitle('Events/(0.005 GeV/c)') 
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
        else: 
            h.Draw('same') 

    leg.Draw()
    c.SaveAs(figfile)


def draw_pip_costhe(sample, c, fs):
    hname = 'h_pip_costhe'
    figfile = 'doc/fig/jpsi2invi_pip_costhe_%s.pdf'   %'_'.join(sample)  
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 
    
    i = 0
    for h in hs:
        i = i+1 
        if i == 1:
            h.SetXTitle('cos#theta_{#pi^{+}}')
            h.SetYTitle('Events/0.02')
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
        else:
            h.Draw('same') 

    leg.Draw()
    c.SaveAs(figfile)


def draw_pim_costhe(sample, c, fs):
    hname = 'h_pim_costhe'
    figfile = 'doc/fig/jpsi2invi_pim_costhe_%s.pdf' %'_'.join(sample)  
    
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 
    
    for h in hs:
        if hs.index(h) == 0:
            h.SetXTitle('Cos#theta_{#pi^{-}}')
            h.SetYTitle('Events/0.02')
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
        else: 
            h.Draw('same') 

    leg.Draw()
    c.SaveAs(figfile)


def draw_cospipi(sample, c, fs):
    hname = 'h_cospipi'
    figfile = 'doc/fig/jpsi2invi_cospipi_%s.pdf' %'_'.join(sample) 
    
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 
    
    for h in hs:
        if hs.index(h) == 0:
            h.SetXTitle('cos#theta_{#pi^{+}#pi^{-}}')
            h.SetYTitle('Events/0.01')
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
        else: 
            h.Draw('same') 

    leg.Draw()
    c.SaveAs(figfile)


def draw_cos2pisys(sample, c, fs):
    hname = 'h_cos2pisys'
    figfile = 'doc/fig/jpsi2invi_cos2pisys_%s.pdf' %'_'.join(sample)     
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 

    for h in hs:
        if hs.index(h) == 0:
            h.SetXTitle('Cos#theta_{#pi#pi sys.}')
            h.SetYTitle('Events/0.02')
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
        else:
            h.Draw('same') 

    leg.Draw()
    c.SaveAs(figfile)


def draw_ngam(sample, c, fs):
    hname = 'h_ngam'
    figfile = 'doc/fig/jpsi2invi_ngam_%s.pdf' %'_'.join(sample)  
    
    leg = ROOT.TLegend(0.2, 0.71, 0.32, 0.91)
    hs, leg = get_common_objects_to_draw(fs, hname, leg) 

    for h in hs:
        if hs.index(h) == 0:
            h.SetXTitle('N_{#gamma}')
            h.SetYTitle('Events')
            h.SetMarkerStyle(ROOT.kFullDotLarge)
            h.Draw()
        else: 
            h.Draw('same') 

    leg.Draw()
    c.SaveAs(figfile)

    
if __name__ == '__main__':
    main()
