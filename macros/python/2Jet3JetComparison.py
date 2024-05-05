import ROOT

ROOT.gROOT.SetBatch(True)

# Open the ROOT file

filepath = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/PostSelection/"

savepath = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/plots/TT_Mtt-700to1000/2Jet3JetComparison/"
file1 = ROOT.TFile(filepath + "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt-700to1000_TuneCP5_13TeV-powher-pythia8_2018.root")
file2 = ROOT.TFile(filepath + "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt-700to1000_TuneCP5_13TeV-powher-pythia8_2018_2Jet.root")

histpath2Jet = ["decay_same_jet_gen/", "decay_same_jet_pt5002000_gen/", "decay_same_jet_pt6002000_gen/", "decay_same_jet_pt7002000_gen/", "decay_same_jet_pt8002000_gen/", "decay_same_jet_pt9002000_gen/"]
histpath3Jet = ["genNoLep/", "genNoLep_pT500/", "genNoLep_pT600/", "genNoLep_pT700/", "genNoLep_pT800/", "genNoLep_pT900/"]
names = ["pt400", "pt500", "pt600", "pt700", "pt800", "pt900"]

colors = [ROOT.kRed, ROOT.kBlue, ROOT.kGreen, ROOT.kYellow, ROOT.kMagenta, ROOT.kCyan, ROOT.kViolet]

canvas = ROOT.TCanvas("canvas", "Histogram")

for i in range(len(histpath2Jet)):

    histogram5 = file2.Get(histpath2Jet[i] + "M_jet_Mass")

    histogram5.SetStats(False)
    histogram5.SetLineColor(ROOT.kBlack)
    histogram5.SetLineWidth(2)
    histogram5.SetXTitle("m(GeV)")
    histogram5.SetYTitle("events")
    histogram5.SetTitle(names[i])

    histogram7 = file1.Get(histpath3Jet[i] + "jetMassNotCombinedOnly")

    histogram7.SetStats(False)
    histogram7.SetLineColor(colors[0])
    histogram7.SetLineWidth(2)

    #histogram5.Scale(1/histogram5.Integral())
    #histogram7.Scale(1/histogram7.Integral())

    hist_max = max(histogram5.GetMaximum(), histogram7.GetMaximum())
    histogram5.GetYaxis().SetRangeUser(0, hist_max*1.1)

    histogram5.Draw("hist")
    histogram7.Draw("hist same")

    legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)

    legend.AddEntry(histogram5, "2jet(" + str(int(histogram5.GetEntries())) + ")", "l")

    legend.AddEntry(histogram7, "lead 3jet(" + str(int(histogram7.GetEntries())) + ")", "l")

    legend.Draw()

    canvas.Modified()
    canvas.Update()

    canvas.SaveAs(savepath + "jetMassLead2Jet3JetComparison" + names[i] + ".pdf")



    histogram5 = file2.Get(histpath2Jet[i] + "M_EachInOneSubjetMass")

    histogram5.SetStats(False)
    histogram5.SetLineColor(ROOT.kBlack)
    histogram5.SetLineWidth(2)
    histogram5.SetXTitle("m(GeV)")
    histogram5.SetYTitle("events")
    histogram5.SetTitle(names[i])

    histogram7 = file1.Get(histpath3Jet[i] + "jetMassCombinedOnlySubjetsMatched")

    histogram7.SetStats(False)
    histogram7.SetLineColor(colors[0])
    histogram7.SetLineWidth(2)

    #histogram5.Scale(1/histogram5.Integral())
    #histogram7.Scale(1/histogram7.Integral())

    hist_max = max(histogram5.GetMaximum(), histogram7.GetMaximum())
    histogram5.GetYaxis().SetRangeUser(0, hist_max*1.1)

    histogram5.Draw("hist")
    histogram7.Draw("hist same")

    legend = ROOT.TLegend(0.7, 0.7, 0.9, 0.9)

    legend.AddEntry(histogram5, "2jet(" + str(int(histogram5.GetEntries())) + ")", "l")

    legend.AddEntry(histogram7, "lead 3jet(" + str(int(histogram7.GetEntries())) + ")", "l")

    legend.Draw()

    canvas.Modified()
    canvas.Update()

    canvas.SaveAs(savepath + "jetMassLead2Jet3JetComparisonSubjetsMatched" + names[i] + ".pdf")

# Close the ROOT file
file1.Close()
file2.Close()