from optparse import OptionParser
import ROOT as rt
from array import *
import os
import random
import sys
import math

def setStyle():
    rt.gStyle.SetOptStat(0)
    rt.gStyle.SetOptFit(0000)
    rt.gStyle.SetOptTitle(0)
    rt.gStyle.SetPaintTextFormat("1.2g")
    #rt.gStyle.SetPalette()
    rt.gStyle.SetNumberContours(999)
    rt.gROOT.SetBatch()
    rt.RooMsgService.instance().setGlobalKillBelow(rt.RooFit.FATAL)
    
    rt.gStyle.SetStatY(1.9)
    rt.gStyle.SetStatX(1.9)
    rt.gStyle.SetStatW(0.1)
    rt.gStyle.SetStatH(0.1)


if __name__ == '__main__':
    parser = OptionParser()
    parser.add_option('-d','--dir',dest="outDir",default="./",type="string",
                  help="Output directory to store results")
    parser.add_option('-l','--lumi',dest="lumi", default=300.,type="float",
                  help="integrated luminosity in pb^-1")
    parser.add_option('--numerator',dest="numerator",default="HLT_RsqMR240_Rsq0p09_MR200",type="string", 
                  help="numerator trigger")
    parser.add_option('--denominator',dest="denominator",default="HLT_Ele27_eta2p1_WPLoose_Gsf",type="string",
                  help="denominator trigger")
    parser.add_option('-i',dest="inputFile",default="AnalysisOutput.root",type="string",
                  help="denominator trigger")


    
    (options,args) = parser.parse_args()
     


    #x = array('d', [1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325, 354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607, 1687, 1770, 1856, 1945, 2037, 2132, 2231, 2332, 2438, 2546, 2659, 2775, 2895, 3019, 3147, 3279, 3416, 3558, 3704, 3854, 4010, 4171, 4337, 4509, 4686, 4869, 5058, 5253, 5455, 5663, 5877, 6099, 6328, 6564, 6808, 7060, 7320, 7589, 7866, 8152, 8447, 8752, 9067, 9391, 9726, 10072, 10430, 10798, 11179, 11571, 11977, 12395, 12827, 13272, 13732, 14000])

    # HT/mjj binning
    if 'HT_' in options.numerator or 'MjjWide_' in options.numerator or 'Mjj_' in options.numerator:
        x = array('d', [1, 3, 6, 10, 16, 23, 31, 40, 50, 61, 74, 88, 103, 119, 137, 156, 176, 197, 220, 244, 270, 296, 325, 354, 386, 419, 453, 489, 526, 565, 606, 649, 693, 740, 788, 838, 890, 944, 1000, 1058, 1118, 1181, 1246, 1313, 1383, 1455, 1530, 1607, 1687, 1770, 1856, 1945, 2037])
    else:
        x = array('d', [ix*5./50. for ix in range(0,51)])
    

    tfile = rt.TFile.Open(options.inputFile,'read')

    num = tfile.Get(options.numerator)
    denom = tfile.Get(options.denominator)

    # rebin
     
    num.Rebin(len(x)-1,'num_rebin',x)
    num = rt.gDirectory.Get('num_rebin')
    num.SetDirectory(0)
    
    denom.Rebin(len(x)-1,'denom_rebin',x)
    denom = rt.gDirectory.Get('denom_rebin')
    denom.SetDirectory(0)
    
    setStyle()
    c = rt.TCanvas("c_"+options.numerator.split('/')[-1],"c_"+options.numerator.split('/')[-1],500,400)
    c.SetRightMargin(0.15)

    pEff = rt.TEfficiency(num, denom)
    pEff.SetName('eff_'+options.numerator.split('/')[-1])
    if 'recoHT' in options.numerator:
        xaxisTitle = "Reco. H_{T}"
    elif 'recoMjjWide' in options.numerator:
        xaxisTitle = "Reco. wide jet m_{jj}"
    elif 'recoMjj' in options.numerator:
        xaxisTitle = "Reco. m_{jj}"
    elif 'recoDeltaEtajjWide' in options.numerator:
        xaxisTitle = "Reco. wide jet #Delta#eta_{jj}"
    elif 'recoDeltaEtajj' in options.numerator:
        xaxisTitle = "Reco. #Delta#eta_{jj}"
    elif 'pfHT' in options.numerator:
        xaxisTitle = "PF scout. H_{T}"
    elif 'pfMjjWide' in options.numerator:
        xaxisTitle = "PF scout. wide jet m_{jj}"
    elif 'pfMjj' in options.numerator:
        xaxisTitle = "PF scout. m_{jj}"
    elif 'pfDeltaEtajjWide' in options.numerator:
        xaxisTitle = "PF scout. wide jet #Delta#eta_{jj}"
    elif 'pfDeltaEtajj' in options.numerator:
        xaxisTitle = "PF scout. #Delta#eta_{jj}"
    elif 'caloHT' in options.numerator:
        xaxisTitle = "Calo. scout. H_{T}"
    elif 'caloMjjWide' in options.numerator:
        xaxisTitle = "Calo. scout. wide jet m_{jj}"
    elif 'caloMjj' in options.numerator:
        xaxisTitle = "Calo. scout. m_{jj}"
    elif 'caloDeltaEtajjWide' in options.numerator:
        xaxisTitle = "Calo. scout. wide jet #Delta#eta_{jj}"
    elif 'caloDeltaEtajj' in options.numerator:
        xaxisTitle = "Calo. scout. #Delta#eta_{jj}"
    
    pEff.SetTitle("efficiency;%s;efficiency"%xaxisTitle)
    
    sigmoid = rt.TF1("sigmoid_"+options.numerator.split('/')[-1],"[0]/(1.0+exp(-(x-[1])/[2]))",x[0],x[-1])
    sigmoid.SetParameter(0,1)
    sigmoid.SetParLimits(0,0,1)
    sigmoid.SetParameter(1,200)
    sigmoid.SetParameter(2,30)
    
    pEff.SetMarkerSize(0.8)
    pEff.SetMarkerStyle(20)
    pEff.Draw("apez")
    #pEff.Fit(sigmoid,"I")
    #sigmoid.SetNpx(1000)
    #sigmoidHist = sigmoid.GetHistogram()
    #pEff.Draw("apez")
    #sigmoidHist.Draw('same')
    
    rt.gPad.Update()        
    #pEff.GetPaintedHistogram().GetXaxis().SetRangeUser(x[0],x[-1])
    pEff.GetPaintedGraph().SetMarkerStyle(8)
    pEff.GetPaintedGraph().SetMarkerSize(20)        
    pEff.GetPaintedGraph().SetMinimum(0)
    pEff.GetPaintedGraph().SetMaximum(1.3)
    pEff.GetPaintedGraph().GetXaxis().SetTitle('Wide m_{jj}')
    
    rt.gPad.Update()      
    l = rt.TLatex()
    l.SetTextAlign(11)
    l.SetTextSize(0.045)
    l.SetTextFont(42)
    l.SetNDC()
    l.DrawLatex(0.12,0.92,"CMS preliminary")
    l.DrawLatex(0.6,0.92,"13 TeV (%.1f fb^{-1})"%(options.lumi/1000.))
    l.SetTextFont(52)
    #l.DrawLatex(0.7,0.75,"R^{2} > %.2f"%yCut)
    l.SetTextSize(0.02)
    l.SetTextFont(42)        
    if 'HT250' in options.numerator:
        l.DrawLatex(0.12,0.88,"signal:       %s"%('DST_HT250_CaloScouting'))
    else:
        l.DrawLatex(0.12,0.88,"signal:       %s"%('DST_HT410_PFScouting'))
    l.DrawLatex(0.12,0.85,"reference:  %s"%('HLT_Mu50'))
    c.Print(options.outDir+"/"+"scoutingHltEff_" + options.numerator.split('/')[-1] + ".pdf")
    c.Print(options.outDir+"/"+"scoutingHltEff_" + options.numerator.split('/')[-1] + ".C")


    rootFile = rt.TFile.Open('scoutingHltEff.root','update')
    tdirectory = rootFile.GetDirectory('scoutingHltEff')
    if tdirectory==None:
        rootFile.mkdir('scoutingHltEff')
        tdirectory = rootFile.GetDirectory('scoutingHltEff')
    
    tdirectory.cd()
    pEff.Write()
    #sigmoid.Write()
    #sigmoidHist.Write()
    c.Write()
