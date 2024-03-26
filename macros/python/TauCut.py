import ROOT

ROOT.gROOT.SetBatch(True)

# Open the ROOT file

filepath = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/PostSelection/"

savepath = ["/nfs/dust/cms/user/goebnoah/MTopJet_Run2/plots/TT_Mtt-700to1000/tauCut/", "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/plots/TT_Mtt-700to1000/tauCutPT700/"]
file1 = ROOT.TFile(filepath + "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt-700to1000_TuneCP5_13TeV-powher-pythia8_2018.root")

histpath = ["genNoLep/", "genNoLep_pT700/"]
histpathIndex = 1

ROOT.gInterpreter.Declare("""
double mean;
double nEvents;
""")

colors = [ROOT.kRed, ROOT.kBlue, ROOT.kGreen, ROOT.kYellow, ROOT.kMagenta, ROOT.kCyan]

histogramNames = ["Tau21", "Tau31", "Tau32", "Tau41", "Tau42", "CombinedTau21", "CombinedTau31", "CombinedTau32", "CombinedTau41", "CombinedTau42", "NoCombinedTau21", "NoCombinedTau31", "NoCombinedTau32", "NoCombinedTau41", "NoCombinedTau42"]

#-------------------------------------

for x in range(len(histogramNames)):
    
    canvas = ROOT.TCanvas("canvas", "Histogram")

    histogram = file1.Get(histpath[histpathIndex] + "M_jet_Mass" + histogramNames[x] + "CutLower")

    histogram.SetStats(False)
    histogram.SetFillColor(ROOT.kGray)
    histogram.SetLineColor(ROOT.kBlack)
    histogram.SetLineWidth(2)
    histogram.SetXTitle("m(GeV)")
    histogram.SetYTitle("events")
    if histpathIndex == 0:
        histogram.SetTitle("pT > 400")
    else:
        histogram.SetTitle("pT > 700")

    fit_func = ROOT.TF1("fit_func", "gaus", 140, 200)
    fit_func.SetLineColor(colors[5])
    histogram.Fit(fit_func)


    histogram1 = file1.Get(histpath[histpathIndex] + "M_jet_Mass" + histogramNames[x] + "CutLowerTop")

    histogram1.SetStats(False)
    histogram1.SetLineColor(colors[0])
    histogram1.SetLineWidth(2)

    histogram2 = file1.Get(histpath[histpathIndex] + "M_jet_Mass" + histogramNames[x] + "CutLowerGluon")

    histogram2.SetStats(False)
    histogram2.SetLineColor(colors[1])
    histogram2.SetLineWidth(2)

    histogram.Draw("hist")
    histogram1.Draw("hist same")
    histogram2.Draw("hist same")
    #fit_func.Draw("same")

    legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

    legend.AddEntry(histogram, "tau42 < 0.54(" + str(int(histogram.GetEntries())) + ")", "l")

    legend.AddEntry(histogram1, "top matched(" + str(int(histogram1.GetEntries())) + ")", "l")

    legend.AddEntry(histogram2, "gluon matched(" + str(int(histogram2.GetEntries())) + ")", "l")

    #legend.AddEntry(fit_func, "mean: " + "{:3.2f}".format(fit_func.GetParameter(1)) + ", sigma: " + "{:2.2f}".format(fit_func.GetParameter(2)), "")

    legend.AddEntry(None, "top/gluon in peak: " + "{:.2f}".format(histogram1.GetBinContent(18)/histogram2.GetBinContent(18)), "")
    
    print("bin content: " + str(histogram1.GetBinContent(18)))

    legend.Draw()

    canvas.Modified()
    canvas.Update()

    canvas.SaveAs(savepath[histpathIndex] + histogramNames[x] + "CutLower.png")

#-----------------------------------------------------------------------------------------------------------

for x in range(len(histogramNames)):
    
    canvas = ROOT.TCanvas("canvas", "Histogram")

    histogram = file1.Get(histpath[histpathIndex] + "M_jet_Mass" + histogramNames[x] + "CutHigher")

    histogram.SetStats(False)
    histogram.SetFillColor(ROOT.kGray)
    histogram.SetLineColor(ROOT.kBlack)
    histogram.SetLineWidth(2)
    histogram.SetXTitle("m(GeV)")
    histogram.SetYTitle("events")
    histogram.SetTitle(histogramNames[x])

    histogram1 = file1.Get(histpath[histpathIndex] + "M_jet_Mass" + histogramNames[x] + "CutHigherTop")

    histogram1.SetStats(False)
    histogram1.SetLineColor(colors[0])
    histogram1.SetLineWidth(2)

    histogram2 = file1.Get(histpath[histpathIndex] + "M_jet_Mass" + histogramNames[x] + "CutHigherGluon")

    histogram2.SetStats(False)
    histogram2.SetLineColor(colors[1])
    histogram2.SetLineWidth(2)

    histogram.Draw("hist")
    histogram1.Draw("hist same")
    histogram2.Draw("hist same")

    legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

    legend.AddEntry(histogram, "above cut(" + str(int(histogram.GetEntries())) + ")", "l")

    legend.AddEntry(histogram1, "top matched(" + str(int(histogram1.GetEntries())) + ")", "l")

    legend.AddEntry(histogram2, "gluon matched(" + str(int(histogram2.GetEntries())) + ")", "l")

    legend.Draw()

    canvas.Modified()
    canvas.Update()

    canvas.SaveAs(savepath[histpathIndex] + histogramNames[x] + "CutHigher.png")

#-----------------------------------------------------------------------------------------------------------



# Close the ROOT file
file1.Close()