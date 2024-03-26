import ROOT

ROOT.gROOT.SetBatch(True)

# Open the ROOT file

filepath = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/PostSelection/"

savepath = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/plots/TT_Mtt-700to1000/subjetComparison/"
file1 = ROOT.TFile(filepath + "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt-700to1000_TuneCP5_13TeV-powher-pythia8_2018.root")

histpath = "genNoLep/"

ROOT.gInterpreter.Declare("""
double mean;
double nEvents;
""")

colors = [ROOT.kRed, ROOT.kBlue, ROOT.kGreen, ROOT.kYellow, ROOT.kMagenta, ROOT.kCyan, ROOT.kViolet]

histogramNames = ["Subjet1pT", "Subjet2pT", "Subjet3pT", "DR12", "DR23", "DR31", "DR1Axis", "DR2Axis", "DR3Axis"]

#-------------------------------------

for x in range(len(histogramNames)):
    
    canvas = ROOT.TCanvas("canvas", "Histogram")

    histogram = file1.Get(histpath + "twoJetAllSubAll" + histogramNames[x])

    histogram.SetStats(False)
    histogram.SetLineColor(ROOT.kBlack)
    histogram.SetLineWidth(2)

    histogram1 = file1.Get(histpath + "twoJetAllSubMatched" + histogramNames[x])

    histogram1.SetStats(False)
    histogram1.SetLineColor(colors[0])
    histogram1.SetLineWidth(2)

    histogram2 = file1.Get(histpath + "twoJetAllSubPartialMatched" + histogramNames[x])

    histogram2.SetStats(False)
    histogram2.SetLineColor(colors[1])
    histogram2.SetLineWidth(2)

    histogram.Scale(1/histogram.Integral())
    histogram1.Scale(1/histogram1.Integral())
    histogram2.Scale(1/histogram2.Integral())

    hist_max = max(histogram.GetMaximum(), histogram1.GetMaximum(), histogram2.GetMaximum())
    histogram.GetYaxis().SetRangeUser(0,hist_max*1.1)

    histogram.Draw("hist")
    histogram1.Draw("hist same")
    histogram2.Draw("hist same")

    legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

    legend.AddEntry(histogram, "twoJetAllSubAll", "l")

    ROOT.mean = histogram.GetMean(1)
    ROOT.nEvents = histogram.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.AddEntry(histogram1, "twoJetAllSubMatched", "l")

    ROOT.mean = histogram1.GetMean(1)
    ROOT.nEvents = histogram1.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.AddEntry(histogram2, "twoJetAllSubPartialMatched", "l")

    ROOT.mean = histogram2.GetMean(1)
    ROOT.nEvents = histogram2.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.Draw()

    canvas.Modified()
    canvas.Update()

    canvas.SaveAs(savepath + histogramNames[x] + ".png")

#-------------------------------------

histogramNames = ["AllSubjet1pT", "AllSubjet2pT", "AllSubjet3pT", "AllSubjet4pT", "AllSubjet5pT", "AllSubjet6pT", "BotSubjetpT", "LightQ1SubjetpT", "LightQ2SubjetpT", "LightQCombinedSubjetpT", "MultipleQSubjetpT"]

for x in range(len(histogramNames)):
    
    canvas = ROOT.TCanvas("canvas", "Histogram")

    histogram = file1.Get(histpath + "twoJet" + histogramNames[x])

    histogram.SetStats(False)
    histogram.SetLineColor(ROOT.kBlack)
    histogram.SetLineWidth(2)
    histogram.SetXTitle("pT(GeV)")
    histogram.SetYTitle("events")
    histogram.SetTitle("")

    histogram.Draw("hist")

    legend = ROOT.TLegend(0.6, 0.8, 0.9, 0.9)

    legend.AddEntry(histogram, histogramNames[x] + "(" + str(int(histogram.GetEntries())) + ")", "l")

    legend.Draw()


    canvas.Modified()
    canvas.Update()

    canvas.SaveAs(savepath + histogramNames[x] + ".png")

#-----------------------------------------------------------------------------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file1.Get(histpath + "twoJetAllSubAllDRAxisMinMax")

histogram.SetStats(False)
histogram.SetLineWidth(2)
histogram.SetXTitle("minDRAxis")
histogram.SetYTitle("maxDRAxis")
histogram.SetTitle("")
histogram.Draw("colz")

legend = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)

legend.AddEntry(histogram, "3 combinations(" + str(int(histogram.GetEntries())) + ")", "l")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "twoJetAllSubAllDRAxisMinMax.png")

#-----------------------------------------------------------------------------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file1.Get(histpath + "twoJetAllSubMatchedDRAxisMinMax")

histogram.SetStats(False)
histogram.SetLineWidth(2)
histogram.SetXTitle("minDRAxis")
histogram.SetYTitle("maxDRAxis")
histogram.SetTitle("")

histogram.Draw("colz")

legend = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)

legend.AddEntry(histogram, "fully merged(" + str(int(histogram.GetEntries())) + ")", "l")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "twoJetAllSubMatchedDRAxisMinMax.png")

#-----------------------------------------------------------------------------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file1.Get(histpath + "twoJetAllSubPartialMatchedDRAxisMinMax")

histogram.SetStats(False)
histogram.SetLineWidth(2)
histogram.SetXTitle("minDRAxis")
histogram.SetYTitle("maxDRAxis")
histogram.SetTitle("")

histogram.Draw("colz")

legend = ROOT.TLegend(0.7, 0.1, 0.9, 0.2)

legend.AddEntry(histogram, "semi merged(" + str(int(histogram.GetEntries())) + ")", "l")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "twoJetAllSubPartialMatchedDRAxisMinMax.png")


# Close the ROOT file
file1.Close()