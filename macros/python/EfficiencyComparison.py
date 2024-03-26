import ROOT

ROOT.gROOT.SetBatch(True)

# Open the ROOT file

filepath = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/PreSelection/"

savepath = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/PreSelection/"
savepath1 = "/nfs/dust/cms/user/goebnoah/MTopJet_Run2/PostSelection/"
#file1 = ROOT.TFile(filepath + "uhh2.AnalysisModuleRunner.MC.TTbar_Test1_2018_OldNtuple.root")
file2 = ROOT.TFile(filepath + "uhh2.AnalysisModuleRunner.MC.TTbar_Test1_2018.root")
file3 = ROOT.TFile("/nfs/dust/cms/user/goebnoah/MTopJet_Run2/Selection/uhh2.AnalysisModuleRunner.MC.TTbar_Test1_2018.root")
file4 = ROOT.TFile("/nfs/dust/cms/user/goebnoah/MTopJet_Run2/Gen/muon/rootfiles/uhh2.AnalysisModuleRunner.MC.TTbar_Test1_2018.root")

ROOT.gInterpreter.Declare("""
double mean;
double nEvents;
""")

colors = [ROOT.kRed, ROOT.kBlue, ROOT.kGreen, ROOT.kYellow, ROOT.kMagenta, ROOT.kCyan]

canvas = ROOT.TCanvas("canvas", "Histogram")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file2.Get("nocuts/M_jet_MassAllJets")

histogram.SetTitle("M_jet")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jet_MassAllJets", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "MassAllJets.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file2.Get("nocuts/M_jet_Mass")

histogram.SetTitle("M_jet")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jet_Mass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "MassJet1.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file2.Get("nocuts/M_jet_MassAllJets")

histogram.SetTitle("M_jet")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram1 = file2.Get("semilep/M_jet_MassAllJets")

histogram1.SetTitle("M_jet")
histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

histogram2 = file2.Get("lepton/M_jet_MassAllJets")

histogram2.SetTitle("M_jet")
histogram2.SetStats(False)
histogram2.SetLineColor(colors[1])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "nocuts", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "semilep", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "lepton", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "MassAllJetsGenComparison.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file2.Get("nocuts/M_jet_MassAllJets")

histogram.SetTitle("M_jet")
histogram.SetStats(False)
histogram.SetFillColor(ROOT.kGray)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram1 = file2.Get("passPreSel/M_jet_MassAllJets")

histogram1.SetTitle("M_jet")
histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

histogram2 = file3.Get("passSel/M_jet_MassAllJets")

histogram2.SetTitle("M_jet")
histogram2.SetStats(False)
histogram2.SetLineColor(colors[1])
histogram2.SetLineWidth(2)

histogram2.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "nocuts", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "passPreSel", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram2, "passSel", "l")

ROOT.mean = histogram2.GetMean(1)
ROOT.nEvents = histogram2.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath + "MassAllJetsSelComparison.png")

#-------------------------------------deltaR----------------------##########################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/deltaR_Jet1Jet2")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaR_Jet1Jet2", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "deltaR_Jet1Jet2.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/deltaR_Jet2Jet3")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaR_Jet2Jet3", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "deltaR_Jet2Jet3.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/deltaR_Jet3Jet1")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaR_Jet3Jet1", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "deltaR_Jet3Jet1.png")

#-------------------------------------subjets-------------####################

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/deltaRJet1_Subjet1Subjet2")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaRJet1_Subjet1Subjet2", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "deltaRJet1_Subjet1Subjet2.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/deltaRJet1_Subjet2Subjet3")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaRJet1_Subjet2Subjet3", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "deltaRJet1_Subjet2Subjet3.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/deltaRJet1_Subjet3Subjet1")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaRJet1_Subjet3Subjet1", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "deltaRJet1_Subjet3Subjet1.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/deltaRJet2_Subjet1Subjet2")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaRJet2_Subjet1Subjet2", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "deltaRJet2_Subjet1Subjet2.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/deltaRJet2_Subjet2Subjet3")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaRJet2_Subjet2Subjet3", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "deltaRJet2_Subjet2Subjet3.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/deltaRJet2_Subjet3Subjet1")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaRJet2_Subjet3Subjet1", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "deltaRJet2_Subjet3Subjet1.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/deltaRJet3_Subjet1Subjet2")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaRJet3_Subjet1Subjet2", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "deltaRJet3_Subjet1Subjet2.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/deltaRJet3_Subjet2Subjet3")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaRJet3_Subjet2Subjet3", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "deltaRJet3_Subjet2Subjet3.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/deltaRJet3_Subjet3Subjet1")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaRJet3_Subjet3Subjet1", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "deltaRJet3_Subjet3Subjet1.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/M_jet_MassAllJets")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram1 = file4.Get("nolepjets_gen/M_jet_TopMatchedInAnyJet")

histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jet_MassAllJets", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "M_jet_TopMatchedInAnyJet", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "M_jet_TopMatchedInAnyJet.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/M_jet_MassAllJets")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram1 = file4.Get("nolepjets_gen/M_jet_MassAllJets")

histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "alljets_gen", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "nolepjets_gen", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "M_jet_MassAllJets.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/M_jet_TopMatchedInAnyJet")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram1 = file4.Get("nolepjets_gen/M_jet_TopMatchedInAnyJetPtCut2")

histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jet_TopMatchedInAnyJet", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "M_jet_TopMatchedInAnyJetPtCut2", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "M_jet_TopMatchedInAnyJetPtCut.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/M_jet_TopMatchedInAnyJetPtCut")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram1 = file4.Get("nolepjets_gen/M_jet_TopMatchedInAnyJetPtCut2")

histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "top pt cut", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "jet pt cut", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "M_jet_TopMatchedInAnyJetPtCutComparison.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/jet_tau2_tau1")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram1 = file4.Get("nolepjets_gen/jet_tau3_tau2")

histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jet_tau2_tau1", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "jet_tau3_tau2", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "jet_tauRatio.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("alljets_gen/deltaR_0")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram1 = file4.Get("nolepjets_gen/deltaR_0")

histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "alljets_gen", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "nolepjets_gen", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "deltaR_0.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/M_jet_MassAllJets")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram1 = file4.Get("nolepjets_gen/M_jet_GluonMatchedInAnyJet")

histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jet_MassAllJets", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "M_jet_GluonMatchedInAnyJet", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "M_jet_GluonMatchedInAnyJet.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/M_jet_TopMatchedInAnyJetPtCut2")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram1 = file4.Get("nolepjets_gen/M_jet_GluonMatchedInAnyJetPtCut")

histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jet_TopMatchedInAnyJetPtCut2", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "M_jet_GluonMatchedInAnyJetPtCut", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "M_jet_GluonMatchedInAnyJetPtCut.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allnolepjets_comparison/sizeDif")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "sizeDif", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "M_jet_AllNoLepSizeComparison.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allNoNearestLepjets_comparison/sizeDif")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "sizeDif", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "M_jet_AllNoNearestLepSizeComparison.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/deltaR_topPtCutNearest")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaR_topPtCutNearest", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "M_jet_deltaR_topPtCutNearest.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/deltaR_jetPtCutNearest")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "deltaR_jetPtCutNearest", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "M_jet_deltaR_jetPtCutNearest.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/DeltaR_CombinedMass_NonLepJets")

histogram.SetStats(False)

histogram.Draw("colz")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "DeltaR_CombinedMass_NonLepJets", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

ROOT.gPad.SetLogz(1)

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "DeltaR_CombinedMass_NonLepJets.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/DeltaR_CombinedMass_NonLepJets_PTCutJet")

histogram.SetStats(False)

histogram.Draw("colz")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "DeltaR_CombinedMass_NonLepJets_PTCutJet", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

ROOT.gPad.SetLogz(1)

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "DeltaR_CombinedMass_NonLepJets_PTCutJet.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/DeltaR_CombinedMass_NonLepJets_PTCutTop")

histogram.SetStats(False)

histogram.Draw("colz")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "DeltaR_CombinedMass_NonLepJets_PTCutTop", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

ROOT.gPad.SetLogz(1)

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "DeltaR_CombinedMass_NonLepJets_PTCutTop.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/DeltaR_Mass1_NonLepJet")

histogram.SetStats(False)

histogram.Draw("colz")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "DeltaR_Mass1_NonLepJet", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

ROOT.gPad.SetLogz(1)

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "DeltaR_Mass1_NonLepJet.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/DeltaR_Mass1_NonLepJet_PTCutJet")

histogram.SetStats(False)

histogram.Draw("colz")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "DeltaR_Mass1_NonLepJet_PTCutJet", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

ROOT.gPad.SetLogz(1)

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "DeltaR_Mass1_NonLepJet_PTCutJet.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/DeltaR_Mass1_NonLepJet_PTCutTop")

histogram.SetStats(False)

histogram.Draw("colz")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "DeltaR_Mass1_NonLepJet_PTCutTop", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

ROOT.gPad.SetLogz(1)

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "DeltaR_Mass1_NonLepJet_PTCutTop.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/DeltaR_Mass2_NonLepJet")

histogram.SetStats(False)

histogram.Draw("colz")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "DeltaR_Mass2_NonLepJet", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

ROOT.gPad.SetLogz(1)

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "DeltaR_Mass2_NonLepJet.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/DeltaR_Mass2_NonLepJet_PTCutJet")

histogram.SetStats(False)

histogram.Draw("colz")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "DeltaR_Mass2_NonLepJet_PTCutJet", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

ROOT.gPad.SetLogz(1)

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "DeltaR_Mass2_NonLepJet_PTCutJet.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/DeltaR_Mass2_NonLepJet_PTCutTop")

histogram.SetStats(False)

histogram.Draw("colz")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "DeltaR_Mass2_NonLepJet_PTCutTop", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

ROOT.gPad.SetLogz(1)

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "DeltaR_Mass2_NonLepJet_PTCutTop.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("nolepjets_gen/M_jet_TopMatchedInAnyJetPtCut2")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

histogram1 = file4.Get("nolepjets_gen/M_jet_GluonMatchedInAnyJetPtCutOtherJet")

histogram1.SetStats(False)
histogram1.SetLineColor(colors[0])
histogram1.SetLineWidth(2)

histogram1.Draw("hist same")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jet_TopMatchedInAnyJetPtCut", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.AddEntry(histogram1, "M_jet_GluonMatchedInAnyJetPtCutOtherJet", "l")

ROOT.mean = histogram1.GetMean(1)
ROOT.nEvents = histogram1.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")

legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "M_jet_GluonMatchedInAnyJetPtCutOtherJet.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allnolepjets_sizeDiff0/jets1_PT")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jets1_PT", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noLepSizeDiff0_jets1_PT.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allnolepjets_sizeDiff0/jets2_PT")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jets2_PT", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noLepSizeDiff0_jets2_PT.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allnolepjets_sizeDiff0/M_jets1_Mass")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jets1_Mass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noLepSizeDiff0_M_jets1_Mass.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allnolepjets_sizeDiff0/M_jets2_Mass")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jets2_Mass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noLepSizeDiff0_M_jets2_Mass.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allnolepjets_sizeDiff2/jets1_PT")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jets1_PT", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noLepSizeDiff2_jets1_PT.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allnolepjets_sizeDiff2/jets2_PT")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jets2_PT", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noLepSizeDiff2_jets2_PT.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allnolepjets_sizeDiff2/M_jets1_Mass")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jets1_Mass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noLepSizeDiff2_M_jets1_Mass.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allnolepjets_sizeDiff2/M_jets2_Mass")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jets2_Mass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noLepSizeDiff2_M_jets2_Mass.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allnolepjets_sizeDiff3/jets1_PT")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jets1_PT", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noLepSizeDiff3_jets1_PT.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allnolepjets_sizeDiff3/jets2_PT")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jets2_PT", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noLepSizeDiff3_jets2_PT.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allnolepjets_sizeDiff3/M_jets1_Mass")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jets1_Mass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noLepSizeDiff3_M_jets1_Mass.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allnolepjets_sizeDiff3/M_jets2_Mass")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jets2_Mass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noLepSizeDiff3_M_jets2_Mass.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allNoNearestLepjets_sizeDiff0/jets1_PT")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jets1_PT", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noNearestLepSizeDiff0_jets1_PT.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allNoNearestLepjets_sizeDiff0/jets2_PT")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jets2_PT", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noNearestLepSizeDiff0_jets2_PT.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allNoNearestLepjets_sizeDiff0/M_jets1_Mass")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jets1_Mass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noNearestLepSizeDiff0_M_jets1_Mass.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allNoNearestLepjets_sizeDiff0/M_jets2_Mass")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jets2_Mass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noNearestLepSizeDiff0_M_jets2_Mass.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allNoNearestLepjets_sizeDiff2/jets1_PT")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jets1_PT", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noNearestLepSizeDiff2_jets1_PT.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allNoNearestLepjets_sizeDiff2/jets2_PT")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jets2_PT", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noNearestLepSizeDiff2_jets2_PT.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allNoNearestLepjets_sizeDiff2/M_jets1_Mass")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jets1_Mass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noNearestLepSizeDiff2_M_jets1_Mass.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allNoNearestLepjets_sizeDiff2/M_jets2_Mass")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jets2_Mass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noNearestLepSizeDiff2_M_jets2_Mass.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allNoNearestLepjets_sizeDiff3/jets1_PT")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jets1_PT", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noNearestLepSizeDiff3_jets1_PT.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allNoNearestLepjets_sizeDiff3/jets2_PT")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jets2_PT", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noNearestLepSizeDiff3_jets2_PT.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allNoNearestLepjets_sizeDiff3/M_jets1_Mass")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jets1_Mass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noNearestLepSizeDiff3_M_jets1_Mass.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file4.Get("allNoNearestLepjets_sizeDiff3/M_jets2_Mass")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "M_jets2_Mass", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "noNearestLepSizeDiff3_M_jets2_Mass.png")

#-------------------------------------

canvas = ROOT.TCanvas("canvas", "Histogram")

histogram = file3.Get("passSel/jet_tau1")

histogram.SetStats(False)
histogram.SetLineColor(ROOT.kBlack)
histogram.SetLineWidth(2)

histogram.Draw("hist")

legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)

legend.AddEntry(histogram, "jet_tau1", "l")

ROOT.mean = histogram.GetMean(1)
ROOT.nEvents = histogram.GetEntries()
legend.AddEntry(0, "mean: " + str(round(ROOT.mean, 1)), "1")
legend.AddEntry(0, "nEvents: " + str(int(round(ROOT.nEvents))), "1")
legend.Draw()

canvas.Modified()
canvas.Update()

canvas.SaveAs(savepath1 + "sel_jet_tau1.png")

# Close the ROOT file
#file1.Close()
file2.Close()
file3.Close()
file4.Close()