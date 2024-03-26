import ROOT

ROOT.gROOT.SetBatch(True)

year = 2018

channel = "muon"

allEvents = False

# 0 = 'whole range', 1 = 400-500, 2 = 500-600, 3 = 600-700, 4 = 700-800, 5 = 800-900, 6 = 900-1000
ptrange = 0

index = 6

# Open the ROOT file
histpaths = [   "decay_same_jet_gen/",
                "decay_same_jet_pt400500_gen/",
                "decay_same_jet_pt500600_gen/",
                "decay_same_jet_pt600700_gen/",
                "decay_same_jet_pt700800_gen/",
                "decay_same_jet_pt800900_gen/",
                "decay_same_jet_pt9001000_gen/"]

file_path_muon = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/Gen/muon/rootfiles/"
file_path_elec = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/Gen/elec/rootfiles/"
save_path_muon = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/Gen/muon/" + histpaths[ptrange]
save_path_elec = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/Gen/elec/" + histpaths[ptrange]

if allEvents:
    file_path_muon += "allEvents/"
    file_path_elec += "allEvents/"

file_path_2018 = ["uhh2.AnalysisModuleRunner.MC.TTbar_2L2Nu_Mtt0000to0700_2018.root",
            "uhh2.AnalysisModuleRunner.MC.TTbar_SemiLeptonic_Mtt0000to0700_2018.root",
            "uhh2.AnalysisModuleRunner.MC.TTbar_Hadronic_Mtt0000to0700_2018.root",
            "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt0700to1000_2018.root",
            "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt1000toInft_2018.root",
            "ttbar_2018.root",
            "uhh2.AnalysisModuleRunner.MC.Test_2018.root"
]

file_path_2017 = ["uhh2.AnalysisModuleRunner.MC.TTbar_2L2Nu_Mtt0000to0700_2017v2.root",
            "uhh2.AnalysisModuleRunner.MC.TTbar_SemiLeptonic_Mtt0000to0700_2017v2.root",
            "uhh2.AnalysisModuleRunner.MC.TTbar_Hadronic_Mtt0000to0700_2017v2.root",
            "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt0700to1000_ext_2017v2.root",
            "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt1000toInft_ext_2017.root",
            "ttbar_2017.root"
]

file_path_2016 = ["uhh2.AnalysisModuleRunner.MC.TTbar_Mtt0000to0700_2016v3.root",
            "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt0700to1000_2016v3.root",
            "uhh2.AnalysisModuleRunner.MC.TTbar_Mtt1000toInft_2016v3.root",
            "ttbar_2016.root"
]


savepath_muon_2018 = [save_path_muon + "2018/2L2Nu_Mtt0000to0700/",
            save_path_muon + "2018/SemiLeptonic_Mtt0000to0700/",
            save_path_muon + "2018/Hadronic_Mtt0000to0700/",
            save_path_muon + "2018/Mtt0700to1000/",
            save_path_muon + "2018/Mtt1000toInft/",
            save_path_muon + "2018/ttbar/",
            save_path_muon + "2018/"
]

savepath_elec_2018 = [save_path_elec + "2018/2L2Nu_Mtt0000to0700/",
            save_path_elec + "2018/SemiLeptonic_Mtt0000to0700/",
            save_path_elec + "2018/Hadronic_Mtt0000to0700/",
            save_path_elec + "2018/Mtt0700to1000/",
            save_path_elec + "2018/Mtt1000toInft/",
            save_path_elec + "2018/ttbar/"
]

savepath_muon_2017 = [save_path_muon + "2017/2L2Nu_Mtt0000to0700/",
            save_path_muon + "2017/SemiLeptonic_Mtt0000to0700/",
            save_path_muon + "2017/Hadronic_Mtt0000to0700/",
            save_path_muon + "2017/Mtt0700to1000/",
            save_path_muon + "2017/Mtt1000toInft/",
            save_path_muon + "2017/ttbar/"
]

savepath_elec_2017 = [save_path_elec + "2017/2L2Nu_Mtt0000to0700/",
            save_path_elec + "2017/SemiLeptonic_Mtt0000to0700/",
            save_path_elec + "2017/Hadronic_Mtt0000to0700/",
            save_path_elec + "2017/Mtt0700to1000/",
            save_path_elec + "2017/Mtt1000toInft/",
            save_path_elec + "2017/ttbar/"
]

savepath_muon_2016 = [save_path_muon + "2016/Mtt0000to0700/",
            save_path_muon + "2016/Mtt0700to1000/",
            save_path_muon + "2016/Mtt1000toInft/",
            save_path_muon + "2016/ttbar/"
]

savepath_elec_2016 = [save_path_elec + "2016/Mtt0000to0700/",
            save_path_elec + "2016/Mtt0700to1000/",
            save_path_elec + "2016/Mtt1000toInft/",
            save_path_elec + "2016/ttbar/"
]


if year==2018 and channel=="muon":
    savepath = savepath_muon_2018
    file = ROOT.TFile(file_path_muon + file_path_2018[index])

if year==2018 and channel=="elec":
    savepath = savepath_elec_2018
    file = ROOT.TFile(file_path_elec + file_path_2018[index])

if year==2017 and channel=="muon":
    savepath = savepath_muon_2017
    file = ROOT.TFile(file_path_muon + file_path_2017[index])

if year==2017 and channel=="elec":
    savepath = savepath_elec_2017
    file = ROOT.TFile(file_path_elec + file_path_2017[index])

if year==2016 and channel=="muon":
    savepath = savepath_muon_2016
    file = ROOT.TFile(file_path_muon + file_path_2016[index])

if year==2016 and channel=="elec":
    savepath = savepath_elec_2016
    file = ROOT.TFile(file_path_elec + file_path_2016[index])

if allEvents:
    for i in range(len(savepath)):
        savepath[i] += "allEvents/"


paths = ["M_jet1_MassAll", "M_jet1_MassNotAll", "M_jet1_MassTwoLightQ", "M_jet1_MassBotOneLightQ", "M_jet1_MassOneQ", "M_jet1_MassNoQ", "M_jet1_MassRest"]

titles = ["M_{JetAll}", "M_{JetNotAll}", "M_{JetTwoLightQ}", "M_{JetBotOneLightQ}", "M_{JetOneQ}", "M_{JetNone}", "M_{JetRest}"]

colors = [ROOT.kRed, ROOT.kBlue, ROOT.kGreen, ROOT.kYellow, ROOT.kMagenta, ROOT.kCyan]

"""

canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("M_{jet}")

histogram_path = histpaths[ptrange] + "M_Subjet1Mass"
histogram = file.Get(histogram_path)

histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path1 = histpaths[ptrange] + "M_Subjet2Mass"
histogram1 = file.Get(histogram_path1)

histogram1.SetLineColor(ROOT.kBlue)
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

histogram_path2 = histpaths[ptrange] + "M_Subjet3Mass"
histogram2 = file.Get(histogram_path2)

histogram2.SetLineColor(ROOT.kRed)
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

"""

ROOT.gInterpreter.Declare("""
double mean;
double nEvents;
""")



canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet_Mass"
histogram = file.Get(histogram_path)

histogram.SetTitle("M_ttbar_jet_Mass")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path3 = histpaths[ptrange] + "M_ttbar_jet_Mass"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[0])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched+unmatched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram3, "ttbar matched", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_ttbar_jet_Mass.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet_Mass"
histogram = file.Get(histogram_path)

histogram.SetTitle("M_jet_Mass_Gluons")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet1_MassAll"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

histogram_path3 = histpaths[ptrange] + "M_jet1_MassAllNoGluons"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[1])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched+unmatched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "jetAll matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

legend.AddEntry(histogram3, "jetAllNoGluons matched", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_jet_MassAllNoGluons.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet_Mass"
histogram = file.Get(histogram_path)

histogram.SetTitle("M_jet_Mass_Gluons")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassNoGluon"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

histogram_path3 = histpaths[ptrange] + "M_jet_MassGluon"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[1])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched+unmatched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "no gluon matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

legend.AddEntry(histogram3, "gluon matched", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_jet_MassGluon.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet_Mass"
histogram = file.Get(histogram_path)

histogram.SetTitle("M_jet_Mass_Gluons")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassGluonNotNearTop"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

histogram_path3 = histpaths[ptrange] + "M_jet_MassGluonNearTop"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[1])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched+unmatched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "gluon not near top matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

legend.AddEntry(histogram3, "gluon near top matched", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_jet_MassGluonNearTop.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet_MassGluonInJet"
histogram = file.Get(histogram_path)

histogram.SetTitle("Gluon_NearTop_InJet_Comparison")
histogram.SetStats(False)
histogram.SetLineColor(colors[0])
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassGluonNearTop"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[1])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "in jet matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "near top matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "Gluon_NearTop_InJet_Comparison.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet_MassUnmatched"
histogram = file.Get(histogram_path)

histogram.SetTitle("Gluon_NearTop_InJet_Comparison")
histogram.SetStats(False)
histogram.SetLineColor(colors[0])
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassGluonNearTop"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[1])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "not each in subjet matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "near top matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "Gluon_NearTop_Unmatched_Comparison.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "Same_nearest_subjet"
histogram = file.Get(histogram_path)

histogram.SetTitle("Number")
histogram.SetStats(False)
histogram.SetLineColor(colors[0])
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_TwoInOneSubjetMassAllInJet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[1])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "same nearest subjet", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "two subjets matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "SameNearestSubjet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_EachInOneSubjetMass"
histogram = file.Get(histogram_path)

histogram.SetTitle("Comparison")
histogram.SetStats(False)
histogram.SetLineColor(colors[0])
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_EachInOneSubjetMassAllInJet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[1])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "subjets matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "subjets and in jet matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "SubjetJetComparison.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet_Mass"
histogram = file.Get(histogram_path)

histogram.SetTitle("M_jet_Mass_GluonInJet")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassGluonNotInJet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

histogram_path3 = histpaths[ptrange] + "M_jet_MassGluonInJet"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[1])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched+unmatched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "no gluon in jet", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

legend.AddEntry(histogram3, "gluon in jet", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_jet_MassGluonInJet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet_Mass"
histogram = file.Get(histogram_path)

histogram.SetTitle("GluonInSubjet")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassGluonNotInSubjet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

histogram_path3 = histpaths[ptrange] + "M_jet_MassGluonInSubjet"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[1])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched+unmatched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "gluon not in subjet matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

legend.AddEntry(histogram3, "gluon in subjet matched", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "GluonInSubjet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet_MassGluonInJet"
histogram = file.Get(histogram_path)

histogram.SetTitle("GluonInJetAndSubjet")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassGluonInJetAndNotSubjet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

histogram_path3 = histpaths[ptrange] + "M_jet_MassGluonInJetAndSubjet"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[1])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "gluon in jet matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "gluon not in subjet matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram3, "gluon in subjet matched", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "GluonInJetAndSubjet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet_MassGluonNotNearTop"
histogram = file.Get(histogram_path)

histogram.SetTitle("m_{jet}")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassGluonNotNearTopAndAllSubjetsMatched"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "gluon not near top matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "gluon not near top and all subjets matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_GluonNotNearTopAndAllSubjetsMatched.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_EachInOneSubjetMass"
histogram = file.Get(histogram_path)

histogram.SetTitle("m_{jet}")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassGluonNotNearTopAndAllSubjetsMatched"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

histogram_path3 = histpaths[ptrange] + "M_jet_MassGluonNearTopAndAllSubjetsMatched"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[1])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "all subjets matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "gluon not near top and all subjets matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram3, "gluon near top and all subjets matched", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_GluonSubjetComparison.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_EachInOneSubjetMass"
histogram = file.Get(histogram_path)

histogram.SetTitle("m_{jet}")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassEachInOneSubjetAndGluonInSubjet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

histogram_path3 = histpaths[ptrange] + "M_jet_MassEachInOneSubjetAndGluonNotInSubjet"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[1])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "each quark in subjet matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "each quark and gluon in subjet matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram3, "each quark and no gluon in subjet matched", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_EachSubjetMatchedGluonInSubjet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_EachInOneSubjetMass"
histogram = file.Get(histogram_path)

histogram.SetTitle("m_{jet}")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassEachInOneSubjetAndGluonInJet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

histogram_path3 = histpaths[ptrange] + "M_jet_MassEachInOneSubjetAndGluonNotInJet"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[1])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "each quark in subjet matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "each quark and gluon in jet matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram3, "each quark and no gluon in jet matched", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_EachSubjetMatchedGluonInJet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet_MassUnmatched"
histogram = file.Get(histogram_path)

histogram.SetTitle("m_{jet}")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassUnmatchedAndGluonInSubjet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

histogram_path3 = histpaths[ptrange] + "M_jet_MassUnmatchedAndGluonNotInSubjet"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[1])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "not each quark in subjet matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "unmatched and gluon in subjet matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram3, "unmatched and no gluon in subjet matched", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_UnmatchedGluonInSubjet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet_MassUnmatched"
histogram = file.Get(histogram_path)

histogram.SetTitle("m_{jet}")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassUnmatchedAndGluonInJet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

histogram_path3 = histpaths[ptrange] + "M_jet_MassUnmatchedAndGluonNotInJet"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[1])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "not each quark in subjet matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "unmatched and gluon in jet matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram3, "unmatched and no gluon in jet matched", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_UnmatchedGluonInJet.png")

###########################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet_MassTopMatched"
histogram = file.Get(histogram_path)

histogram.SetTitle("m_{jet}")
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "M_jet_MassGluonMatched"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "gluon matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_MassTopGluon.png")

########################################################################################################################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path0 = histpaths[ptrange] + "M_jet_Mass"
histogram0 = file.Get(histogram_path0)

histogram0.SetTitle("M_EachInOneSubjetMass")
histogram0.SetStats(False)
histogram0.SetFillColor(ROOT.kGray)
histogram0.SetLineColor(ROOT.kBlack)
histogram0.SetLineWidth(2)

histogram0.Draw("hist")

histogram_path = histpaths[ptrange] + "M_jet1_MassAll"
histogram = file.Get(histogram_path)

histogram.SetStats(False)
histogram.SetLineColor(colors[0])
histogram.SetLineWidth(2)

histogram.Draw("hist same")

histogram_path3 = histpaths[ptrange] + "M_EachInOneSubjetMassAllInJet"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[1])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")

histogram_path1 = histpaths[ptrange] + "M_TwoInOneSubjetMassAllInJet"
histogram1 = file.Get(histogram_path1)

histogram1.SetStats(False)
histogram1.SetLineColor(colors[2])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

histogram_path2 = histpaths[ptrange] + "M_OneInOneSubjetMassAllInJet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[3])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

histogram_path4 = histpaths[ptrange] + "M_NoneInOneSubjetMassAllInJet"
histogram4 = file.Get(histogram_path4)

histogram4.SetStats(False)
histogram4.SetLineColor(colors[4])
histogram4.SetLineWidth(2)

histogram4.Draw("hist same")



legend = ROOT.TLegend(0.6, 0.3, 0.9, 0.9)

legend.AddEntry(histogram0, "matched + unmatched", "l")

ROOT.mean = histogram0.GetMean(1)
ROOT.nEvents = histogram0.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram, "jetAll matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram3, "3subjets matched", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "2subjets matched", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "1subjet matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram4, "0subjets matched", "l")

ROOT.mean = histogram4.GetMean(1)
ROOT.nEvents = histogram4.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_NumberMatchedSubjetsMass.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path0 = histpaths[ptrange] + "M_jet_Mass"
histogram0 = file.Get(histogram_path0)

histogram0.SetTitle("M_EachInOneSubjetMass")
histogram0.SetStats(False)
histogram0.SetFillColor(ROOT.kGray)
histogram0.SetLineColor(ROOT.kBlack)
histogram0.SetLineWidth(2)

histogram0.Draw("hist")

histogram_path = histpaths[ptrange] + "M_jet1_MassAll"
histogram = file.Get(histogram_path)

histogram.SetStats(False)
histogram.SetLineColor(colors[0])
histogram.SetLineWidth(2)

histogram.Draw("hist same")

histogram_path3 = histpaths[ptrange] + "M_EachInOneSubjetMass"
histogram3 = file.Get(histogram_path3)

histogram3.SetStats(False)
histogram3.SetLineColor(colors[1])
histogram3.SetLineWidth(2)

histogram3.Draw("hist same")

histogram_path1 = histpaths[ptrange] + "M_TwoInOneSubjetMass"
histogram1 = file.Get(histogram_path1)

histogram1.SetStats(False)
histogram1.SetLineColor(colors[2])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

histogram_path2 = histpaths[ptrange] + "M_OneInOneSubjetMass"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[3])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

histogram_path4 = histpaths[ptrange] + "M_NoneInOneSubjetMass"
histogram4 = file.Get(histogram_path4)

histogram4.SetStats(False)
histogram4.SetLineColor(colors[4])
histogram4.SetLineWidth(2)

histogram4.Draw("hist same")



legend = ROOT.TLegend(0.6, 0.3, 0.9, 0.9)

legend.AddEntry(histogram0, "matched + unmatched", "l")

ROOT.mean = histogram0.GetMean(1)
ROOT.nEvents = histogram0.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram, "jetAll matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram3, "3subjets matched", "l")

ROOT.mean = histogram3.GetMean(1)
ROOT.nEvents = histogram3.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "2subjets matched", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "1subjet matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram4, "0subjets matched", "l")

ROOT.mean = histogram4.GetMean(1)
ROOT.nEvents = histogram4.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_NumberMatchedSubjetsMassNotInJet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path0 = histpaths[ptrange] + "M_jet_Mass"
histogram0 = file.Get(histogram_path0)

histogram0.SetTitle("M_EachInOneSubjetMass")
histogram0.SetStats(False)
histogram0.SetFillColor(ROOT.kGray)
histogram0.SetLineColor(ROOT.kBlack)
histogram0.SetLineWidth(2)

histogram0.Draw("hist")

histogram_path = histpaths[ptrange] + "M_AnySubjetMass"
histogram = file.Get(histogram_path)

histogram.SetStats(False)
histogram.SetLineColor(colors[0])
histogram.SetLineWidth(2)

histogram.Draw("hist same")

histogram_path1 = histpaths[ptrange] + "M_EachInOneSubjetMass"
histogram1 = file.Get(histogram_path1)

histogram1.SetStats(False)
histogram1.SetLineColor(colors[1])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.3, 0.9, 0.9)

legend.AddEntry(histogram0, "matched + unmatched", "l")

ROOT.mean = histogram0.GetMean(1)
ROOT.nEvents = histogram0.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram, "in any subjet matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "each in one subjet matched", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_InAnyEachInOneSubjetComparison.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path0 = histpaths[ptrange] + "M_jet_Mass"
histogram0 = file.Get(histogram_path0)

histogram0.SetTitle("M_EachInOneSubjetMass")
histogram0.SetStats(False)
histogram0.SetFillColor(ROOT.kGray)
histogram0.SetLineColor(ROOT.kBlack)
histogram0.SetLineWidth(2)

histogram0.Draw("hist")

histogram_path = histpaths[ptrange] + "M_AnySubjetMass"
histogram = file.Get(histogram_path)

histogram.SetStats(False)
histogram.SetLineColor(colors[0])
histogram.SetLineWidth(2)

histogram.Draw("hist same")

histogram_path1 = histpaths[ptrange] + "M_AnyButNotEachSubjetMass"
histogram1 = file.Get(histogram_path1)

histogram1.SetStats(False)
histogram1.SetLineColor(colors[1])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.3, 0.9, 0.9)

legend.AddEntry(histogram0, "matched + unmatched", "l")

ROOT.mean = histogram0.GetMean(1)
ROOT.nEvents = histogram0.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram, "in any subjet matched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "in any but not each in one subjet matched", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_InAnyButNotInEachSubjet.png")

#####################################

customRange = [0,6] 
#customRange = range(len(paths))
for i in customRange:
    canvas = ROOT.TCanvas("canvas", "Histogram")

    histogram_path = histpaths[ptrange] + "M_ttbar_jet_Mass"
    histogram = file.Get(histogram_path)
    
    histogram.SetTitle(titles[i])
    histogram.SetStats(False)
    histogram.SetFillColor(ROOT.kGray)
    histogram.SetLineColor(ROOT.kBlack)
    histogram.SetLineWidth(2)

    histogram.Draw("hist")

    histogram_path1 = histpaths[ptrange]
    histogram_path1 += paths[i]
    histogram1 = file.Get(histogram_path1)

    histogram1.SetStats(False)
    histogram1.SetLineColor(colors[0])
    histogram1.SetLineWidth(2)

    histogram1.Draw("hist same")
    
    legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)
    legend.AddEntry(histogram, "matched+unmatched", "l")

    ROOT.mean = histogram.GetMean(1)
    ROOT.nEvents = histogram.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.AddEntry(histogram1, "matched", "l")

    ROOT.mean = histogram1.GetMean(1)
    ROOT.nEvents = histogram1.GetEntries()
    legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
    legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

    legend.Draw()


    canvas.Modified()
    canvas.Update()

    canvas.SaveAs(savepath[index] + paths[i] + ".png")

###########################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "M_jet1_MassNotAll"
histogram = file.Get(histogram_path)

histogram.SetTitle("M_jet1_Mass_Comparison")
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlue)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path1 = histpaths[ptrange] + "M_jet1_MassRest"
histogram1 = file.Get(histogram_path1)

histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "MassNotAll", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "MassRest", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "M_jet1_Mass_Comparison.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "jet_PT"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("jet_{PT}")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "jet_PT.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "pt_bot_subjet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("ptRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "pt_bot_subjet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "pt_q1_subjet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("ptRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "pt_q1_subjet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "pt_q2_subjet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("ptRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "pt_q2_subjet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetPT_q1_bot"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("ptRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetPT_q1_bot.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetPT_q2_bot"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("ptRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetPT_q2_bot.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetPT_q1_q2"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("ptRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetPT_q1_q2.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetPT_bot_q1"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("ptRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetPT_bot_q1.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetPT_bot_q2"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("ptRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetPT_bot_q2.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetPT_q2_q1"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("ptRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetPT_q2_q1.png")

############################-------------M-------------###############

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetM_q1_bot"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetM_q1_bot.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetM_q2_bot"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetM_q2_bot.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetM_q1_q2"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetM_q1_q2.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetM_bot_q1"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetM_bot_q1.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetM_bot_q2"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetM_bot_q2.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetM_q2_q1"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetM_q2_q1.png")

############################-------Jet--------############################
############################-----matched------############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetPT_q1_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("PTRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetPT_q1_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetPT_q2_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("PTRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetPT_q2_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetPT_bot_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("PTRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetPT_bot_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetPT_quarks_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("PTRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetPT_quarks_jet.png")

############################------------M-----------------########################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetM_q1_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetM_q1_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetM_q2_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetM_q2_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetM_bot_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetM_bot_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedSubjetM_quarks_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedSubjetM_quarks_jet.png")

##############################################---------------------numbered subjets--------------------########################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedPT_subjet1_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("PTRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedPT_subjet1_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedPT_subjet2_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("PTRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedPT_subjet2_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedPT_subjet3_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("PTRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedPT_subjet3_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedM_subjet1_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("NRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedM_subjet1_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedM_subjet2_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedM_subjet2_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "matchedM_subjet3_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "matchedM_subjet3_jet.png")

############################---unmatched---############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "unmatchedPT_subjet1_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("PTRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "unmatchedPT_subjet1_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "unmatchedPT_subjet2_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("PTRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "unmatchedPT_subjet2_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "unmatchedPT_subjet3_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("PTRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "unmatchedPT_subjet3_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "unmatchedM_subjet1_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("NRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "unmatchedM_subjet1_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "unmatchedM_subjet2_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "unmatchedM_subjet2_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "unmatchedM_subjet3_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "unmatchedM_subjet3_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "unmatchedPT_quarks_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("PTRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "unmatchedPT_quarks_jet.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
histogram_path = histpaths[ptrange] + "unmatchedM_quarks_jet"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("MRatio")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "unmatchedM_quarks_jet.png")

#################################---Comparison---###################################
#####################################---M---########################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "matchedM_subjet1_jet"
histogram = file.Get(histogram_path)

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "unmatchedM_subjet1_jet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched ratio", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "unmatched ratio", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "ComparisonM_subjet1_jet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "matchedM_subjet2_jet"
histogram = file.Get(histogram_path)

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "unmatchedM_subjet2_jet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched ratio", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "unmatched ratio", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "ComparisonM_subjet2_jet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "matchedM_subjet3_jet"
histogram = file.Get(histogram_path)

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "unmatchedM_subjet3_jet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched ratio", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "unmatched ratio", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "ComparisonM_subjet3_jet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "matchedSubjetM_quarks_jet"
histogram = file.Get(histogram_path)

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "unmatchedM_quarks_jet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched ratio", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "unmatched ratio", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "ComparisonM_quarks_jet.png")

#####################################---PT---########################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "matchedPT_subjet1_jet"
histogram = file.Get(histogram_path)

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "unmatchedPT_subjet1_jet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched ratio", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "unmatched ratio", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "ComparisonPT_subjet1_jet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "matchedPT_subjet2_jet"
histogram = file.Get(histogram_path)

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "unmatchedPT_subjet2_jet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched ratio", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "unmatched ratio", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "ComparisonPT_subjet2_jet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "matchedPT_subjet3_jet"
histogram = file.Get(histogram_path)

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram_path2 = histpaths[ptrange] + "unmatchedPT_subjet3_jet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched ratio", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "unmatched ratio", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "ComparisonPT_subjet3_jet.png")

#####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "matchedSubjetPT_quarks_jet"
histogram = file.Get(histogram_path)

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)


histogram_path2 = histpaths[ptrange] + "unmatchedPT_quarks_jet"
histogram2 = file.Get(histogram_path2)

histogram2.SetStats(False)
histogram2.SetLineColor(colors[0])
histogram2.SetLineWidth(2)

histogram.GetYaxis().SetRangeUser(0,histogram2.GetMaximum()*1.2)
histogram.Draw("hist")
histogram2.Draw("hist same")


legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched ratio", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "unmatched ratio", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")


legend.Draw()


canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath[index] + "ComparisonPT_quarks_jet.png")

##########################################################################################
################################---top-gluon---###########################################
################################---pt----#################################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet1_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet1_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedPT_subjet1_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet1_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet1_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedPT_subjet1_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet2_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet2_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedPT_subjet2_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet3_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet3_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedPT_subjet3_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_quarks_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_quarks_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedPT_quarks_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet1_subjet2"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet1_subjet2"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedPT_subjet1_subjet2.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet2_subjet3"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet2_subjet3"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedPT_subjet2_subjet3.png")

####################################


canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet1_subjet3"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet1_subjet3"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedPT_subjet1_subjet3.png")

##########################################################################################
################################---M-----#################################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet1_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet1_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedM_subjet1_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet1_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet1_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedM_subjet1_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet2_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet2_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedM_subjet2_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet3_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet3_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedM_subjet3_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_quarks_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_quarks_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedM_quarks_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet1_subjet2"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet1_subjet2"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedM_subjet1_subjet2.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet2_subjet3"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet2_subjet3"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedM_subjet2_subjet3.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet1_subjet3"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet1_subjet3"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "topGluonMatchedM_subjet1_subjet3.png")

####################################--normalized--#################################################
################################---pt----#################################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet1_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet1_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedPT_subjet1_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet1_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet1_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedPT_subjet1_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet2_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet2_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedPT_subjet2_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet3_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet3_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedPT_subjet3_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_quarks_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_quarks_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedPT_quarks_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet1_subjet2"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet1_subjet2"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedPT_subjet1_subjet2.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet2_subjet3"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet2_subjet3"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedPT_subjet2_subjet3.png")

####################################


canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedPT_subjet1_subjet3"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedPT_subjet1_subjet3"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedPT_subjet1_subjet3.png")

##########################################################################################
################################---M-----#################################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet1_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet1_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedM_subjet1_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet1_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet1_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedM_subjet1_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet2_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet2_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedM_subjet2_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet3_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet3_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedM_subjet3_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_quarks_jet"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_quarks_jet"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedM_quarks_jet.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet1_subjet2"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet1_subjet2"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedM_subjet1_subjet2.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet2_subjet3"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet2_subjet3"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedM_subjet2_subjet3.png")

####################################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram_path = histpaths[ptrange] + "topMatchedM_subjet1_subjet3"
histogram = file.Get(histogram_path)
histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram_path1 = histpaths[ptrange] + "gluonMatchedM_subjet1_subjet3"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(ROOT.kRed)
histogram1.SetLineWidth(2)

if histogram.Integral() != 0:
    histogram.Scale(1/histogram.Integral())
if histogram1.Integral() != 0:
    histogram1.Scale(1/histogram1.Integral())

histogram.Draw("hist")
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top matched", "l")
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "gluon matched", "l")
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "normalizedTopGluonMatchedM_subjet1_subjet3.png")

####################################
"""
histogram_path = histpaths[ptrange] + "jet_tau3_tau2"
histogram = file.Get(histogram_path)
histogram.SetTitle("tau_{3}/tau_{2}")
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "jet_tau3_tau2.png")

############################

histogram_path = histpaths[ptrange] + "jet_tau2_tau1"
histogram = file.Get(histogram_path)
histogram.SetTitle("tau_{2}/tau_{1}")
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "jet_tau2_tau1.png")
"""
############################

histogram_path = "decay_same_jet_gen_count/n_events_noweight"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("count")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "Gen_Count.png")

############################

histogram_path = "decay_same_jet_gen/number_subjets"
histogram = file.Get(histogram_path)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("number")
histogram.Draw("hist")
canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "SubjetNumber.png")

###################################################------Reference------######################

file1 = ROOT.TFile("/nfs/dust/cms/user/goebnoah/MTopJet_Run2/Gen/muon/rootfiles/allEvents/matching_2018_muon.root")

canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("m_{jet}")

histogram_path = "all"
histogram = file1.Get(histogram_path)
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
histogram.Draw("hist")

histogram_path1 = "unmatched"
histogram1 = file1.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)
histogram1.Draw("hist same")

histogram_path2 = "matched"
histogram2 = file1.Get(histogram_path2)
histogram2.SetStats(False)
histogram2.SetLineColor(colors[1])
histogram2.SetLineWidth(2)
histogram2.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "matched + unmatched", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "unmatched", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

legend.AddEntry(histogram2, "matched", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "Reference_Histogram.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("m_{jet}")

histogram_path = "all"
histogram = file1.Get(histogram_path)
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
histogram.Draw("hist")

histogram_path1 = histpaths[ptrange] + "M_jet_Mass"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetFillStyle(0)
histogram1.SetLineWidth(2)
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "reference", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "matched + unmatched", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "Reference_Comparison_All.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("m_{jet}")

histogram_path = "matched"
histogram = file1.Get(histogram_path)
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
histogram.Draw("hist")

histogram_path1 = histpaths[ptrange] + "M_EachInOneSubjetMass"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetFillStyle(0)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "reference", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "each in subjet", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "Reference_Comparison_Matched.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("m_{jet}")

histogram_path = "unmatched"
histogram = file1.Get(histogram_path)
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
histogram.Draw("hist")

histogram_path1 = histpaths[ptrange] + "M_jet_MassUnmatched"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetFillStyle(0)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "reference", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "rest", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "Reference_Comparison_Unmatched.png")

############################

canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("m_{jet}")

histogram_path = "all"
histogram = file1.Get(histogram_path)
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
histogram.Draw("hist")

histogram_path1 = histpaths[ptrange] + "M_jet_Mass"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetFillStyle(0)                          ######################## for whatever reason
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "test1", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "test2", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "test.pdf")

############################

file2 = ROOT.TFile("/nfs/dust/cms/user/goebnoah/MTopJet_Run2/Gen/muon/rootfiles/allEvents/CheckForNoah.root")

canvas = ROOT.TCanvas("canvas", "Histogram")
canvas.SetTitle("m_{jet}")

histogram_path = "total"
histogram = file2.Get(histogram_path)
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)
histogram.Draw("hist")

histogram_path1 = histpaths[ptrange] + "M_jet_Mass"
histogram1 = file.Get(histogram_path1)
histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetFillStyle(0)
histogram1.SetLineWidth(2)
histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "reference", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "matched + unmatched", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()
canvas.SaveAs(savepath[index] + "Reference_Comparison_Total.png")

# Close the ROOT file
file.Close()
file1.Close()
file2.Close()