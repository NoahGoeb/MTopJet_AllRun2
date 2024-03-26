import ROOT

ROOT.gROOT.SetBatch(True)

# Open the ROOT file

filepath = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/PostSelection/"

savepath = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/plots/TT_Mtt-700to1000/decayProductComparison/"
file1 = ROOT.TFile(filepath + "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt-700to1000_TuneCP5_13TeV-powher-pythia8_2018.root")
file2 = ROOT.TFile(filepath + "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt-700to1000_TuneCP5_13TeV-powher-pythia8_2018_2Jet.root")

histpath = ["genNoLep/", "decay_same_jet_gen/", "genNoLep_pT700/"]

ROOT.gInterpreter.Declare("""
double mean;
double nEvents;
""")

colors = [ROOT.kRed, ROOT.kBlue, ROOT.kGreen, ROOT.kYellow, ROOT.kMagenta, ROOT.kCyan, ROOT.kViolet]

histogramNames = ["All", "Bot", "TwoLightQ", "BotOneLightQ", "OneQ", "NoQ", "GluonAll", "GluonBot", "GluonTwoLightQ", "GluonBotOneLightQ", "GluonOneQ", "GluonNoQ"]

#-------------------------------------

for x in range(len(histogramNames)):
    
    canvas = ROOT.TCanvas("canvas", "Histogram")

    histogram = file1.Get(histpath[0] + "M_jet1_Mass" + histogramNames[x])

    histogram.SetStats(False)
    histogram.SetFillColor(ROOT.kGray)
    histogram.SetLineColor(ROOT.kBlack)
    histogram.SetLineWidth(2)

    histogram1 = file2.Get(histpath[1] + "M_jet1_Mass" + histogramNames[x])

    histogram1.SetStats(False)
    histogram1.SetLineColor(colors[0])
    histogram1.SetLineWidth(2)

    histogram.Draw("hist")
    histogram1.Draw("hist same")

    legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

    legend.AddEntry(histogram, "3Jet " + histogramNames[x], "l")

    ROOT.mean = histogram.GetMean(1)
    ROOT.nEvents = histogram.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.AddEntry(histogram1, "2Jet " + histogramNames[x], "l")

    ROOT.mean = histogram1.GetMean(1)
    ROOT.nEvents = histogram1.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.Draw()

    canvas.Modified()
    canvas.Update()

    canvas.SaveAs(savepath + histogramNames[x] + ".png")

#-----------------------------------------------------------------------------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file1.Get(histpath[0] + "jetMass")

histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram1 = file2.Get(histpath[1] + "M_jet_Mass")

histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "3Jet GenJetMass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "2Jet GenJetMass", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "GenJetMass.png")

#-----------------------------------------------------------------------------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file1.Get(histpath[0] + "M_DecayInBoth")

histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram1 = file1.Get(histpath[0] + "dt_topJet_M_EachQuarkMatched")

histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "DecayInBoth", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "dt_EachQuarkMatched", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "GenJetDecayInBoth.png")

#-----------------------------------------------------------------------------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file1.Get(histpath[0] + "M_oneJetAllDRJet12")

histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("colz")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "allInOneJetDRJet12", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "GenJetAllInOneDRJet12.png")

#-----------------------------------------------------------------------------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file1.Get(histpath[0] + "M_twoJetAllDRJet12")

histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("colz")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "allInTwoJetDRJet12", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "GenJetAllInTwoDRJet12.png")

#-----------------------------------------------------------------------------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")
#canvas.SetLogy(1)

histogram5 = file1.Get(histpath[0] + "twoAllSubTau21MaxMass")

histogram5.SetStats(False)
histogram5.SetLineColor(colors[0])
histogram5.SetLineWidth(2)

histogram7 = file1.Get(histpath[0] + "twoAllSubMaxPTMass")

histogram7.SetStats(False)
histogram7.SetLineColor(colors[1])
histogram7.SetLineWidth(2)

histogram5.Draw("hist")
histogram7.Draw("hist same")

histogram5.Scale(1/histogram5.Integral())
histogram7.Scale(1/histogram7.Integral())

hist_max = max(histogram5.GetMaximum(), histogram7.GetMaximum())
histogram.GetYaxis().SetRangeUser(0,hist_max*1.1)

legend = ROOT.TLegend(0.5, 0.5, 0.5, 0.5)

legend.AddEntry(histogram5, "twoAllSubTau21MaxMass", "l")

ROOT.nEvents = histogram5.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram7, "twoAllSubMaxPTMass", "l")

ROOT.nEvents = histogram7.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "SubjetCombinedAllMassComparison.png")

#-----------------------------------------------------------------------------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")
#canvas.SetLogy(1)

histogram = file1.Get(histpath[0] + "twoAllSubAllMass")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
histogram.SetXTitle("m(GeV)")
histogram.SetYTitle("events")
histogram.SetTitle("")

histogram1 = file1.Get(histpath[0] + "twoAllSubMatchedMass")

histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram2 = file1.Get(histpath[0] + "twoAllSubPartialMatchedMass")

histogram2.SetStats(False)
histogram2.SetLineColor(colors[1])
histogram2.SetLineWidth(2)

histogram3 = file1.Get(histpath[0] + "twoAll4SubMatchedMass")

histogram3.SetStats(False)
histogram3.SetLineColor(colors[2])
histogram3.SetLineWidth(2)

histogram4 = file1.Get(histpath[0] + "twoAll4SubPartialMatchedMass")

histogram4.SetStats(False)
histogram4.SetLineColor(colors[3])
histogram4.SetLineWidth(2)

histogram6 = file1.Get(histpath[0] + "twoAllSubMatchedMultipleSubjetsJet")

histogram6.SetStats(False)
histogram6.SetLineColor(colors[4])
histogram6.SetLineWidth(2)

histogram7 = file1.Get(histpath[0] + "twoAllSubNoneMatchedMass")

histogram7.SetStats(False)
histogram7.SetLineColor(colors[5])
histogram7.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")
histogram2.Draw("hist same")
histogram3.Draw("hist same")
histogram4.Draw("hist same")
histogram6.Draw("hist same")
histogram7.Draw("hist same")

histogram.Scale(1/histogram.Integral())
histogram1.Scale(1/histogram1.Integral())
histogram2.Scale(1/histogram2.Integral())
histogram3.Scale(1/histogram3.Integral())
histogram4.Scale(1/histogram4.Integral())
histogram6.Scale(1/histogram6.Integral())
histogram7.Scale(1/histogram7.Integral())

hist_max = max(histogram.GetMaximum(), histogram1.GetMaximum(), histogram2.GetMaximum(), histogram3.GetMaximum(), histogram4.GetMaximum(), histogram6.GetMaximum(), histogram7.GetMaximum())
histogram.GetYaxis().SetRangeUser(0,hist_max*1.1)

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "3 combi(" + str(int(histogram.GetEntries())) + ")", "l")

legend.AddEntry(histogram1, "3 fully merged(" + str(int(histogram1.GetEntries())) + ")", "l")

legend.AddEntry(histogram2, "3 semi merged(" + str(int(histogram2.GetEntries())) + ")", "l")

legend.AddEntry(histogram3, "4 fully merged(" + str(int(histogram3.GetEntries())) + ")", "l")

legend.AddEntry(histogram4, "4 semi merged(" + str(int(histogram4.GetEntries())) + ")", "l")

legend.AddEntry(histogram6, "3 uniquely merged(" + str(int(histogram6.GetEntries())) + ")", "l")

legend.AddEntry(histogram7, "3 not merged(" + str(int(histogram7.GetEntries())) + ")", "l")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "SubjetCombinedMassComparison.png")

#-----------------------------------------------------------------------------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram5 = file1.Get(histpath[0] + "jetMass")

histogram5.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram5.SetLineWidth(2)
histogram5.SetXTitle("m(GeV)")
histogram5.SetYTitle("events")
histogram5.SetTitle("")

histogram7 = file1.Get(histpath[0] + "jetMassCombinedOnly")

histogram7.SetStats(False)
histogram7.SetLineColor(colors[0])
histogram7.SetLineWidth(2)

histogram8 = file1.Get(histpath[0] + "jetMassNotCombinedOnly")

histogram8.SetStats(False)
histogram8.SetLineColor(colors[1])
histogram8.SetLineWidth(2)

hist_max = max(histogram5.GetMaximum(), histogram7.GetMaximum(), histogram8.GetMaximum())
histogram5.GetYaxis().SetRangeUser(0,hist_max*1.1)

histogram5.Draw("hist")
histogram7.Draw("hist same")
histogram8.Draw("hist same")

legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)

legend.AddEntry(histogram5, "combi + lead(" + str(int(histogram5.GetEntries())) + ")", "l")

legend.AddEntry(histogram7, "only combi(" + str(int(histogram7.GetEntries())) + ")", "l")

legend.AddEntry(histogram8, "only lead(" + str(int(histogram8.GetEntries())) + ")", "l")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "jetMassCombinedOnly.png")

#-----------------------------------------------------------------------------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram5 = file1.Get(histpath[2] + "jetMass")

histogram5.SetStats(False)
histogram5.SetFillColor(ROOT.kGray)
histogram5.SetLineColor(ROOT.kBlack)
histogram5.SetLineWidth(2)
histogram5.SetXTitle("m(GeV)")
histogram5.SetYTitle("events")
histogram5.SetTitle("")

histogram7 = file1.Get(histpath[2] + "jetMassCombinedOnly")

histogram7.SetStats(False)
histogram7.SetLineColor(colors[0])
histogram7.SetLineWidth(2)

histogram8 = file1.Get(histpath[2] + "jetMassNotCombinedOnly")

histogram8.SetStats(False)
histogram8.SetLineColor(colors[1])
histogram8.SetLineWidth(2)

hist_max = max(histogram5.GetMaximum(), histogram7.GetMaximum(), histogram8.GetMaximum())
histogram.GetYaxis().SetRangeUser(0,hist_max*1.1)

histogram5.Draw("hist")
histogram7.Draw("hist same")
histogram8.Draw("hist same")

legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)

legend.AddEntry(None, " pT > 700:", "")

legend.AddEntry(histogram5, "combi + lead(" + str(int(histogram5.GetEntries())) + ")", "l")

legend.AddEntry(histogram7, "only combi(" + str(int(histogram7.GetEntries())) + ")", "l")

legend.AddEntry(histogram8, "only lead(" + str(int(histogram8.GetEntries())) + ")", "l")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "jetMassCombinedOnly_pT700.png")

#-----------------------------------------------------------------------------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram5 = file1.Get(histpath[0] + "jetMassNotCombinedOnly")

histogram5.SetStats(False)
histogram5.SetLineColor(ROOT.kBlack)
histogram5.SetLineWidth(2)
histogram5.SetXTitle("m(GeV)")
histogram5.SetYTitle("events")
histogram5.SetTitle("")

histogram7 = file2.Get(histpath[1] + "M_jet_Mass")

histogram7.SetStats(False)
histogram7.SetLineColor(colors[0])
histogram7.SetLineWidth(2)

histogram5.Scale(1/histogram5.Integral())
histogram7.Scale(1/histogram7.Integral())

hist_max = max(histogram5.GetMaximum(), histogram7.GetMaximum())
histogram5.GetYaxis().SetRangeUser(0, hist_max*1.1)

histogram5.Draw("hist")
histogram7.Draw("hist same")

legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)

legend.AddEntry(histogram5, "lead 3jet(" + str(int(histogram5.GetEntries())) + ")", "l")

legend.AddEntry(histogram7, "2jet(" + str(int(histogram7.GetEntries())) + ")", "l")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "jetMassLead2Jet3JetComparison.png")

# Close the ROOT file
file1.Close()
file2.Close()