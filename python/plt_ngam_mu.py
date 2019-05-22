#!/usr/bin/env python
"""
Generate costhe without eff
"""

__author__ = "Suyu XIAO <xiaosuyu@ihep.ac.cn>"
__copyright__ = "Copyright (c) Suyu XIAO"
__created__ = "[2019-02-21 Thu 14:38]"

import sys
import ROOT
from ROOT import gStyle, TCanvas, TString, TChain, TStyle
from ROOT import TH1D, TFile, TLegend

c1 = TCanvas('c1', '', 800, 600)
c1.SetFillColor(0)
c1.SetFrameFillColor(0)
gStyle.SetPadColor(0)
gStyle.SetCanvasColor(0)
gStyle.SetOptStat(0)
c1.SetLeftMargin(0.15)
c1.SetRightMargin(0.15)
c1.SetTopMargin(0.1)
c1.SetBottomMargin(0.15)
# c1.SetTicks(1,1)

logdir = sys.argv[1:]
print logdir
 
histo = 'h_ngam_mu'

if logdir in [['09']]:
    f_data = TFile('run/jpsi2lplm/hist_data09/jpsi2lplm_data_psip_data09_event_merged_ngam_mu.root')            # 752895
    f_inMC = TFile('run/jpsi2lplm/hist_mc09/jpsi2lplm_psip_mc09_event_merged_ngam_mu.root')                     # 739060
    f_mu = TFile('run/gen_mc/jpsi2mumu_09/job_text/hist/jpsi2lplm_gen_mc_mumu_09_event_merged_ngam_mu.root')    # 1015332

elif logdir in [['12']]:
    f_data = TFile('run/jpsi2lplm/hist/jpsi2lplm_data_psip_data12_event_merged_ngam_mu.root')                   # 2339327
    f_inMC = TFile('run/jpsi2lplm/hist_mc12/jpsi2lplm_psip_mc12_event_merged_ngam_mu.root')                     # 2718392
    f_mu = TFile('run/gen_mc/jpsi2mumu/job_text/hist/jpsi2lplm_gen_mc_mumu_event_merged_ngam_mu.root')          # 977972

h_data = f_data.Get(histo)
h_inMC = f_inMC.Get(histo)
h_mu = f_mu.Get(histo)

if logdir in [['09']]:
    h_mu.Scale(752895.0/1015332.0)
    h_inMC.Scale(752895.0/739060.0)
    h_data.GetYaxis().SetRangeUser(0, 700000)
elif logdir in [['12']]:
    h_mu.Scale(2339327.0/977972.0)
    h_inMC.Scale(2339327.0/2718392.0)
    h_data.GetYaxis().SetRangeUser(0, 2200000)

h_data.SetTitle("")
h_data.SetLineColor(ROOT.kBlack)
# h_data.SetLineStyle(12)
h_inMC.SetLineColor(ROOT.kRed)
h_mu.SetLineColor(ROOT.kBlue)
h_inMC.SetLineWidth(2)
h_data.SetLineWidth(2)
h_mu.SetLineWidth(2)
h_data.Draw()
h_inMC.Draw("same")
h_mu.Draw("same")

h_data.GetYaxis().SetTitle()
h_data.GetYaxis().SetTitleOffset(1.5)
h_data.GetXaxis().CenterTitle()
h_data.GetYaxis().CenterTitle()

legend = TLegend(0.48, 0.68, 0.83, 0.88)

if logdir in [['09']]:
    legend.AddEntry(h_data, "J/#psi#rightarrow#mu^{+}#mu^{-} data")
    legend.AddEntry(h_inMC, "J/#psi incl MC")
    legend.AddEntry(h_mu, "J/#psi#rightarrow#mu^{+}#mu^{-} MC")
elif logdir in [['12']]:
    legend.AddEntry(h_data, "J/#psi#rightarrow#mu^{+}#mu^{-} data")
    legend.AddEntry(h_inMC, "J/#psi incl MC")
    legend.AddEntry(h_mu, "J/#psi#rightarrow#mu^{+}#mu^{-} MC")

legend.SetBorderSize(0)
legend.SetFillColor(0)
legend.Draw()
h_data.GetXaxis().SetTitle('N_{#gamma}')
h_data.GetYaxis().SetTitle('Events')
h_data.GetXaxis().SetTitleOffset(1.2)
h_data.GetYaxis().SetTitleOffset(0.9)
h_data.GetXaxis().SetTitleSize(0.06)
h_data.GetYaxis().SetTitleSize(0.07)
h_data.GetXaxis().SetLabelSize(0.05)
h_data.GetYaxis().SetLabelSize(0.05)
h_data.GetXaxis().CenterTitle()
h_data.GetYaxis().CenterTitle()
h_data.GetYaxis().SetNdivisions(505)
h_data.GetYaxis().SetNdivisions(505)

figfile = 'python/plots/ngam_mu_%s.pdf' %'_'.join(logdir)

c1.SaveAs(figfile)
