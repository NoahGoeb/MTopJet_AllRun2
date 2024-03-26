import ROOT

ROOT.gROOT.SetBatch(True)

# Open the ROOT file

filepath = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/PostSelection/"

savepath = ["/nfs/dust/cms/user/goebnoah/MTopJet_Run2/plots/TT_Mtt-700to1000/topGluonJetComparisonPT700/", "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/plots/TT_Mtt-700to1000/combinedJetComparisonPT700/", "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/plots/TT_Mtt-700to1000/decayProductComparisonPT700/"] 
file1 = ROOT.TFile(filepath + "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt-700to1000_TuneCP5_13TeV-powher-pythia8_2018.root")
file2 = ROOT.TFile(filepath + "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt-700to1000_TuneCP5_13TeV-powher-pythia8_2018_TopCut.root")

histpath = "genNoLep_pT700/"

ROOT.gInterpreter.Declare("""
double mean;
double nEvents;
""")

colors = [ROOT.kRed, ROOT.kBlue, ROOT.kGreen, ROOT.kYellow, ROOT.kMagenta, ROOT.kCyan]

histogramNames = ["Jet_tau1", "Jet_tau2", "Jet_tau3", "Jet_tau4", "Jet_tau2tau1", "Jet_tau3tau2", "Jet_tau3tau1", "Jet_tau4tau3", "Jet_tau4tau2", "Jet_tau4tau1", "SubjetM1M", "SubjetM2M", "SubjetM3M", "SubjetPT1PT", "SubjetPT2PT", "SubjetPT3PT"]

#-------------------------------------

for x in range(len(histogramNames)):
    
    canvas = ROOT.TCanvas("canvas", "Histogram")

    histogram = file1.Get(histpath + "top" + histogramNames[x])

    histogram.SetStats(False)
    histogram.SetFillColor(ROOT.kGray)
    histogram.SetLineColor(ROOT.kBlack)
    histogram.SetLineWidth(2)

    histogram1 = file1.Get(histpath + "dt_top" + histogramNames[x])

    histogram1.SetStats(False)
    histogram1.SetLineColor(colors[0])
    histogram1.SetLineWidth(2)

    histogram2 = file1.Get(histpath + "dtng_top" + histogramNames[x])

    histogram2.SetStats(False)
    histogram2.SetLineColor(colors[1])
    histogram2.SetLineWidth(2)

    histogram3 = file1.Get(histpath + "gluon" + histogramNames[x])

    histogram3.SetStats(False)
    histogram3.SetLineColor(colors[2])
    histogram3.SetLineWidth(2)

    histogram.Scale(1/histogram.Integral())
    histogram1.Scale(1/histogram1.Integral())
    histogram2.Scale(1/histogram2.Integral())
    histogram3.Scale(1/histogram3.Integral())

    histogram.Draw("hist")
    histogram1.Draw("hist same")
    histogram2.Draw("hist same")
    histogram3.Draw("hist same")

    """if x<10:
        histogram4 = file1.Get(histpath + "combinedTop" + histogramNames[x])

        histogram4.SetStats(False)
        histogram4.SetLineColor(colors[4])
        histogram4.SetLineWidth(2)

        histogram4.Scale(1/histogram4.Integral())

        histogram4.Draw("hist same")

        histogram5 = file1.Get(histpath + "combinedOnlyTop" + histogramNames[x])

        histogram5.SetStats(False)
        histogram5.SetLineColor(colors[5])
        histogram5.SetLineWidth(2)
        
        histogram5.Scale(1/histogram5.Integral())

        histogram5.Draw("hist same")
"""
    legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

    legend.AddEntry(histogram, "top" + histogramNames[x], "l")

    ROOT.mean = histogram.GetMean(1)
    ROOT.nEvents = histogram.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.AddEntry(histogram1, "dt_top" + histogramNames[x], "l")

    ROOT.mean = histogram1.GetMean(1)
    ROOT.nEvents = histogram1.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.AddEntry(histogram2, "dtng_top" + histogramNames[x], "l")

    ROOT.mean = histogram2.GetMean(1)
    ROOT.nEvents = histogram2.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.AddEntry(histogram3, "gluon" + histogramNames[x], "l")

    ROOT.mean = histogram3.GetMean(1)
    ROOT.nEvents = histogram3.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    """if x<10:
        legend.AddEntry(histogram4, "combinedTop" + histogramNames[x], "l")

        ROOT.mean = histogram4.GetMean(1)
        ROOT.nEvents = histogram4.GetEntries()
        legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
        legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

        legend.AddEntry(histogram5, "combinedOnlyTop" + histogramNames[x], "l")

        ROOT.mean = histogram5.GetMean(1)
        ROOT.nEvents = histogram5.GetEntries()
        legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
        legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
"""
    legend.Draw()

    canvas.Modified()
    canvas.Update()

    canvas.SaveAs(savepath[0] + histogramNames[x] + ".png")

#-----------------------------------------------------------------------------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file1.Get(histpath + "deltaRTopGluonDeltaRTopAntitop")

histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("colz")
"""
legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaRTopGluonDeltaRTopAntitop", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()
"""
canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[0] + "deltaRTopGluonDeltaRTopAntitop.png")

#-----------------------------------------------------------------------------------------------------------

for x in range(len(histogramNames)-6):
    
    canvas = ROOT.TCanvas("canvas", "Histogram")

    histogram = file1.Get(histpath + "combinedOnlyTop" + histogramNames[x])

    histogram.SetStats(False)
    histogram.SetFillColor(ROOT.kGray)
    histogram.SetLineColor(ROOT.kBlack)
    histogram.SetLineWidth(2)

    histogram1 = file1.Get(histpath + "top1" + histogramNames[x])

    histogram1.SetStats(False)
    histogram1.SetLineColor(colors[0])
    histogram1.SetLineWidth(2)

    histogram2 = file1.Get(histpath + "top2" + histogramNames[x])

    histogram2.SetStats(False)
    histogram2.SetLineColor(colors[1])
    histogram2.SetLineWidth(2)

    histogram3 = file1.Get(histpath + "top12" + histogramNames[x])

    histogram3.SetStats(False)
    histogram3.SetLineColor(colors[2])
    histogram3.SetLineWidth(2)

    histogram.Scale(1/histogram.Integral())
    histogram1.Scale(1/histogram1.Integral())
    histogram2.Scale(1/histogram2.Integral())
    histogram3.Scale(1/histogram3.Integral())

    histogram.Draw("hist")
    histogram1.Draw("hist same")
    histogram2.Draw("hist same")
    histogram3.Draw("hist same")

    legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

    legend.AddEntry(histogram, "combinedOnlyTop" + histogramNames[x], "l")

    ROOT.mean = histogram.GetMean(1)
    ROOT.nEvents = histogram.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.AddEntry(histogram1, "top1" + histogramNames[x], "l")

    ROOT.mean = histogram1.GetMean(1)
    ROOT.nEvents = histogram1.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.AddEntry(histogram2, "top2" + histogramNames[x], "l")

    ROOT.mean = histogram2.GetMean(1)
    ROOT.nEvents = histogram2.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.AddEntry(histogram3, "top12" + histogramNames[x], "l")

    ROOT.mean = histogram3.GetMean(1)
    ROOT.nEvents = histogram3.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.Draw()

    canvas.Modified()
    canvas.Update()

    canvas.SaveAs(savepath[1] + histogramNames[x] + ".png")

#-----------------------------------------------------------------------------------------------------------

for x in range(len(histogramNames)-6):
    
    canvas = ROOT.TCanvas("canvas", "Histogram")

    histogram = file1.Get(histpath + "oneAll" + histogramNames[x])

    histogram.SetStats(False)
    histogram.SetFillColor(ROOT.kGray)
    histogram.SetLineColor(ROOT.kBlack)
    histogram.SetLineWidth(2)

    histogram1 = file1.Get(histpath + "twoAll" + histogramNames[x])

    histogram1.SetStats(False)
    histogram1.SetLineColor(colors[0])
    histogram1.SetLineWidth(2)

    histogram.Scale(1/histogram.Integral())
    histogram1.Scale(1/histogram1.Integral())

    histogram.Draw("hist")
    histogram1.Draw("hist same")

    legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

    legend.AddEntry(histogram, "oneAll" + histogramNames[x], "l")

    ROOT.mean = histogram.GetMean(1)
    ROOT.nEvents = histogram.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.AddEntry(histogram1, "twoALl" + histogramNames[x], "l")

    ROOT.mean = histogram1.GetMean(1)
    ROOT.nEvents = histogram1.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.Draw()

    canvas.Modified()
    canvas.Update()

    canvas.SaveAs(savepath[2] + histogramNames[x] + ".png")

#-----------------------------------------------------------------------------------------------------------

# Close the ROOT file
file1.Close()
file2.Close()