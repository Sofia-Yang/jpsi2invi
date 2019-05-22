#!/usr/bin/env python

import os
import sys
import ROOT
import math

logdir = sys.argv[1:]
print logdir

# for data 2009
if logdir in [['09']]:
	x0 = -46.044903/10000.0
	sigma = 29.967286/10000.0

# for data 2012
elif logdir in [['12']]:
	# x0 = -219.72/10000.0
	x0 = -255.35/10000.0
	# sigma = 34.44/10000.0
	sigma = 33.34/10000.0

else:
    print 'input error'


# for combine
# x0 = -168.17/10000.0
# sigma = 28.26/10000.0

mu_t=[0]*130000
Prob=[0]*130000

# h_gaus = ROOT.TH1F('hgaus', 'hgaus', 23000, -0.006, 0.017)
h_gaus = ROOT.TH1F('hgaus', 'hgaus', 25000, -0.023, 0.002)
sum = 0.0
# for i in range(0, 23000):
for i in range(0, 25000):
	# mu_t[i] = (-6.0+i*0.001)/1000.0
	mu_t[i] = (-23.0+i*0.001)/1000.0
	c1 = 1/math.sqrt(2*3.141592653858*sigma*sigma)
	Prob[i] = c1*math.exp(-(x0-mu_t[i])*(x0-mu_t[i])/2/sigma/sigma)
	# Prob[i] = c1*math.exp(-(x0-mu_t[i])*(x0-mu_t[i])/2/sigma/sigma)*pow(10.0, 5.0)
	h_gaus.SetBinContent(i+1, Prob[i])
	
	if (mu_t[i]>0.0) :
		sum = sum + Prob[i]

ROOT.gStyle.SetCanvasColor(0)
c = ROOT.TCanvas("c","",800,600)
# c.SetLogy()
c.cd()
#h_gaus.GetYaxis().SetRangeUser(0.0001, 100000000)
h_gaus.Draw()

c.SetTicks(1,1)

ratio = 0.90
tmp_sum = 0.0
hmax = 0.0

# for j in range(0, 23000):
for j in range(0, 25000):
	if Prob[j] > hmax:
		hmax = Prob[j]
			
	if mu_t[j]>=0.0 :
		tmp_sum += Prob[j]

	if tmp_sum >= sum*ratio:
		j_CL=j
		CL_mu = mu_t[j]
		break



print '90% CL limit ='
print CL_mu

t1 = ROOT.TLine(CL_mu, 0, CL_mu, hmax*1.05)
t1.Draw()

#ROOT.gPad.SetLeftMargin(0.12)
ROOT.gPad.SetLeftMargin(0.2)
ROOT.gPad.SetBottomMargin(0.17)
ROOT.gPad.GetFrame().SetBorderMode(0)

# h_gaus_shaded = ROOT.TH1F('hgaus_shaded', 'hgaus_shaded', 23000, -0.006, 0.017)
h_gaus_shaded = ROOT.TH1F('hgaus_shaded', 'hgaus_shaded', 25000, -0.023, 0.002)
# for i in range(0, 23000):
for i in range(0, 25000):
	if mu_t[i]>=0.0 and CL_mu>mu_t[i]:
		h_gaus_shaded.SetBinContent(i+1, Prob[i])
	else:
		h_gaus_shaded.SetBinContent(i+1, 0.0)
h_gaus_shaded.Draw('same')
h_gaus_shaded.SetFillColor(4)
h_gaus.Draw('same')
h_gaus.SetLineColor(1)
h_gaus.SetLineWidth(2)
h_gaus_shaded.SetLineColor(1)

ROOT.gROOT.SetStyle("Plain")
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetOptTitle(0)

h_gaus.SetName("")
h_gaus.SetTitle("")
h_gaus.GetXaxis().SetTitleFont(22)
h_gaus.GetYaxis().SetTitleFont(22)
h_gaus.GetXaxis().SetTitleOffset(1.2)
h_gaus.GetYaxis().SetTitleOffset(0.9)
h_gaus.GetXaxis().SetTitleSize(0.06)
h_gaus.GetYaxis().SetTitleSize(0.06)
h_gaus.GetXaxis().SetLabelSize(0.05)
h_gaus.GetYaxis().SetLabelSize(0.05)
h_gaus.GetXaxis().SetTitle("Br(J/#psi#rightarrow invisible)/Br(J/#psi#rightarrow#mu^{+}#mu^{-    })")
h_gaus.GetYaxis().SetTitle("Likelihood(in arbitrary unit)")
# h_gaus.GetYaxis().SetLabel("*10^{5}")
h_gaus.GetXaxis().CenterTitle()
h_gaus.GetYaxis().CenterTitle()
h_gaus.GetYaxis().SetNdivisions(505)
h_gaus.GetYaxis().SetNdivisions(505)

c.Print("c.eps")
