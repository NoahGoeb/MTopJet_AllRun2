import ROOT

ROOT.gROOT.SetBatch(True)

# Open the ROOT file

filepath = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/PostSelection/"

savepath = ["/nfs/dust/cms/user/goebnoah/MTopJet_Run2/plots/TT_Mtt-700to1000/subjetCombinedComparison/", "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/plots/TT_Mtt-700to1000/combinedJetComparison/", "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/plots/TT_Mtt-700to1000/decayProductComparison/"] 
file1 = ROOT.TFile(filepath + "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt-700to1000_TuneCP5_13TeV-powher-pythia8_2018.root")

histpath = "genNoLep/"
#histpath = "genNoLep_pT700/"

ROOT.gInterpreter.Declare("""
double mean;
double nEvents;
""")

colors = [ROOT.kRed, ROOT.kBlue, ROOT.kGreen, ROOT.kYellow, ROOT.kMagenta, ROOT.kCyan]

histogramNames = ["tau1", "tau2", "tau3", "tau2tau1", "tau3tau2", "tau3tau1"]

#-------------------------------------

for x in range(len(histogramNames)):
    
    canvas = ROOT.TCanvas("canvas", "Histogram")

    histogram = file1.Get(histpath + "twoAllSubAllJet_" + histogramNames[x])

    histogram.SetStats(False)
    histogram.SetLineColor(ROOT.kBlack)
    histogram.SetLineWidth(2)
    histogram.SetTitle("")
    histogram.SetXTitle(histogramNames[x])
    histogram.SetYTitle("events")

    histogram1 = file1.Get(histpath + "twoAllSubMatchedJet_" + histogramNames[x])

    histogram1.SetStats(False)
    histogram1.SetLineColor(colors[0])
    histogram1.SetLineWidth(2)

    histogram2 = file1.Get(histpath + "twoAllSubPartialMatchedJet_" + histogramNames[x])

    histogram2.SetStats(False)
    histogram2.SetLineColor(colors[1])
    histogram2.SetLineWidth(2)

    histogram3 = file1.Get(histpath + "twoAllSubOnlyThreeMatchedJet_" + histogramNames[x])

    histogram3.SetStats(False)
    histogram3.SetLineColor(colors[2])
    histogram3.SetLineWidth(2)

    histogram4 = file1.Get(histpath + "twoAllSubUnmatchedJet_" + histogramNames[x])

    histogram4.SetStats(False)
    histogram4.SetLineColor(colors[4])
    histogram4.SetLineWidth(2)

    histogram.Scale(1/histogram.Integral())
    histogram1.Scale(1/histogram1.Integral())
    histogram2.Scale(1/histogram2.Integral())
    histogram3.Scale(1/histogram3.Integral())
    histogram4.Scale(1/histogram4.Integral())

    hist_max = max(histogram.GetMaximum(), histogram1.GetMaximum(), histogram2.GetMaximum(), histogram3.GetMaximum(), histogram4.GetMaximum())
    histogram.GetYaxis().SetRangeUser(0,hist_max*1.1)

    histogram.Draw("hist")
    histogram1.Draw("hist same")
    histogram2.Draw("hist same")
    histogram3.Draw("hist same")
    histogram4.Draw("hist same")

    legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

    legend.AddEntry(histogram, "combi (" + str(int(histogram.GetEntries())) + ")", "l")

    legend.AddEntry(histogram1, "fully merged (" + str(int(histogram1.GetEntries())) + ")", "l")

    legend.AddEntry(histogram2, "semi merged (" + str(int(histogram2.GetEntries())) + ")", "l")

    legend.AddEntry(histogram3, "fully merged uniquely (" + str(int(histogram3.GetEntries())) + ")", "l")

    legend.AddEntry(histogram4, "unmerged (" + str(int(histogram4.GetEntries())) + ")", "l")

    legend.Draw()

    canvas.Modified()
    canvas.Update()

    canvas.SaveAs(savepath[0] + histogramNames[x] + ".pdf")

#-----------------------------------------------------------------------------------------------------------

for x in range(len(histogramNames)):
    
    canvas = ROOT.TCanvas("canvas", "Histogram")

    histogram = file1.Get(histpath + "twoAllSubOneMatchedJet_" + histogramNames[x])

    histogram.SetStats(False)
    histogram.SetLineColor(ROOT.kBlack)
    histogram.SetLineWidth(2)

    histogram1 = file1.Get(histpath + "twoAllSubTwoMatchedJet_" + histogramNames[x])

    histogram1.SetStats(False)
    histogram1.SetLineColor(colors[0])
    histogram1.SetLineWidth(2)

    #histogram.Scale(1/histogram.Integral())
    #histogram1.Scale(1/histogram1.Integral())

    if histogram.GetMaximum() > histogram1.GetMaximum():
        hist_max = histogram.GetMaximum()
    else:
        hist_max = histogram1.GetMaximum()
    
    histogram.GetYaxis().SetRangeUser(0,hist_max)

    histogram.Draw("hist")
    histogram1.Draw("hist same")

    legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

    legend.AddEntry(histogram, "twoAllSubOneMatched" + histogramNames[x], "l")

    ROOT.mean = histogram.GetMean(1)
    ROOT.nEvents = histogram.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.AddEntry(histogram1, "twoAllSubTwoMatched" + histogramNames[x], "l")

    ROOT.mean = histogram1.GetMean(1)
    ROOT.nEvents = histogram1.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.Draw()

    canvas.Modified()
    canvas.Update()

    canvas.SaveAs(savepath[0] + histogramNames[x] + "Partial.pdf")

#-----------------------------------------------------------------------------------------------------------

# Close the ROOT file
file1.Close()