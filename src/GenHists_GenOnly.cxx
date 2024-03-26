#include <UHH2/MTopJet/include/GenHists_GenOnly.h>

#include <iostream>
#include <fstream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/AdditionalSelections.h>
#include <UHH2/common/include/CommonModules.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/Utils.h>

#include <UHH2/MTopJet/include/CombineXCone.h>
#include <UHH2/MTopJet/include/GenHists_xcone.h>
#include <UHH2/MTopJet/include/ControlHists.h>
#include <UHH2/MTopJet/include/ModuleBASE.h>
#include <UHH2/MTopJet/include/StoreBJet.h>

#include <UHH2/MTopJet/include/AnalysisOutput.h>
#include <UHH2/MTopJet/include/GenSelections.h>
#include <UHH2/MTopJet/include/MTopJetUtils.h> 

using namespace uhh2;

const double jetradius = 1.2;
const double subjetRadius = 0.2;

const int max_m = 500;
const int min_m = 0;
const int n_massbins = 50;

bool printOut = false;

GenHists_GenOnly::GenHists_GenOnly(uhh2::Context & ctx, const std::string & dirname, const std::string & jetname): Hists(ctx, dirname){
  // book all histograms here
  GenJetMass = book<TH1F>("M_jet_Mass", "M_{jet}", n_massbins, 0, max_m);

  GenJetMassAllJets = book<TH1F>("M_jet_MassAllJets", "M_{jet}", n_massbins, 0, max_m);

  GenDeltaRJet1Jet2 = book<TH1F>("deltaR_Jet1Jet2", "Delta R(jet1,jet2)", 80, 0, 6.0);
  GenDeltaRJet2Jet3 = book<TH1F>("deltaR_Jet2Jet3", "Delta R(jet2,jet3)", 80, 0, 6.0);
  GenDeltaRJet3Jet1 = book<TH1F>("deltaR_Jet3Jet1", "Delta R(jet3,jet1)", 80, 0, 6.0);

  GenDeltaRJetsPtDiff = book<TH1F>("deltaR_0", "Delta p_T", 80, 0, 6.0);

  GenJet1DeltaRSubjet1Subjet2 = book<TH1F>("deltaRJet1_Subjet1Subjet2", "Delta R(subjet1,subjet2)", 80, 0, 3.0);
  GenJet1DeltaRSubjet2Subjet3 = book<TH1F>("deltaRJet1_Subjet2Subjet3", "Delta R(subjet2,subjet3)", 80, 0, 3.0);
  GenJet1DeltaRSubjet3Subjet1 = book<TH1F>("deltaRJet1_Subjet3Subjet1", "Delta R(subjet3,subjet1)", 80, 0, 3.0);

  GenJet2DeltaRSubjet1Subjet2 = book<TH1F>("deltaRJet2_Subjet1Subjet2", "Delta R(subjet1,subjet2)", 80, 0, 3.0);
  GenJet2DeltaRSubjet2Subjet3 = book<TH1F>("deltaRJet2_Subjet2Subjet3", "Delta R(subjet2,subjet3)", 80, 0, 3.0);
  GenJet2DeltaRSubjet3Subjet1 = book<TH1F>("deltaRJet2_Subjet3Subjet1", "Delta R(subjet3,subjet1)", 80, 0, 3.0);

  GenJet3DeltaRSubjet1Subjet2 = book<TH1F>("deltaRJet3_Subjet1Subjet2", "Delta R(subjet1,subjet2)", 80, 0, 3.0);
  GenJet3DeltaRSubjet2Subjet3 = book<TH1F>("deltaRJet3_Subjet2Subjet3", "Delta R(subjet2,subjet3)", 80, 0, 3.0);
  GenJet3DeltaRSubjet3Subjet1 = book<TH1F>("deltaRJet3_Subjet3Subjet1", "Delta R(subjet3,subjet1)", 80, 0, 3.0);

  GenMatchedTopInAnyJet = book<TH1F>("M_jet_TopMatchedInAnyJet", "M_{jet}", n_massbins, 0, max_m);

  GenMatchedTopInAnyJetPtCut = book<TH1F>("M_jet_TopMatchedInAnyJetPtCut", "M_{jet}", n_massbins, 0, max_m);
  GenMatchedTopInAnyJetPtCut2 = book<TH1F>("M_jet_TopMatchedInAnyJetPtCut2", "M_{jet}", n_massbins, 0, max_m);

  GenMatchedGluonInAnyJet = book<TH1F>("M_jet_GluonMatchedInAnyJet", "M_{jet}", n_massbins, 0, max_m);
  GenMatchedGluonInAnyJetPtCut  = book<TH1F>("M_jet_GluonMatchedInAnyJetPtCut", "M_{jet}", n_massbins, 0, max_m);
  GenMatchedGluonInAnyJetPtCutOtherJet = book<TH1F>("M_jet_GluonMatchedInAnyJetPtCutOtherJet", "M_{jet}", n_massbins, 0, max_m);

  GenDeltaRTopPtCutNearest = book<TH1F>("deltaR_topPtCutNearest", "Delta R(topjet,nearest)", 80, 0, 6.0);
  GenDeltaRJetPtCutNearest = book<TH1F>("deltaR_jetPtCutNearest", "Delta R(topjet,nearest)", 80, 0, 6.0);

  GenJetNumber = book<TH1F>("number_jets", "number", 21, 0, 20);

  GenTTBarJetMass = book<TH1F>("M_ttbar_jet_Mass", "M_{jet}", n_massbins, 0, max_m);

  GenJet1MassAll = book<TH1F>("M_jet1_MassAll", "M_{jet}", n_massbins, min_m, max_m);
  GenJet1MassNotAll = book<TH1F>("M_jet1_MassNotAll", "M_{jet}", n_massbins, 0, max_m);
  GenJet1MassRest = book<TH1F>("M_jet1_MassRest", "M_{jet}", n_massbins, 0, max_m);

  GenJet1MassBot = book<TH1F>("M_jet1_MassBot", "M_{jet}", n_massbins, min_m, max_m);
  GenJet1MassTwoLightQ = book<TH1F>("M_jet1_MassTwoLightQ", "M_{jet}", n_massbins, min_m, max_m);
  GenJet1MassBotOneLightQ = book<TH1F>("M_jet1_MassBotOneLightQ", "M_{jet}", n_massbins, min_m, max_m);
  GenJet1MassOneQ = book<TH1F>("M_jet1_MassOneQ", "M_{jet}", n_massbins, min_m, max_m);
  GenJet1MassNoQ = book<TH1F>("M_jet1_MassNoQ", "M_{jet}", n_massbins, min_m, max_m);

  GenJet1MassGluonAll = book<TH1F>("M_jet1_MassGluonAll", "M_{jet}", n_massbins, min_m, max_m);
  GenJet1MassGluonBot = book<TH1F>("M_jet1_MassGluonBot", "M_{jet}", n_massbins, min_m, max_m);
  GenJet1MassGluonTwoLightQ = book<TH1F>("M_jet1_MassGluonTwoLightQ", "M_{jet}", n_massbins, min_m, max_m);
  GenJet1MassGluonBotOneLightQ = book<TH1F>("M_jet1_MassGluonBotOneLightQ", "M_{jet}", n_massbins, min_m, max_m);
  GenJet1MassGluonOneQ = book<TH1F>("M_jet1_MassGluonOneQ", "M_{jet}", n_massbins, min_m, max_m);
  GenJet1MassGluonNoQ = book<TH1F>("M_jet1_MassGluonNoQ", "M_{jet}", n_massbins, min_m, max_m);

  GenJetPT = book<TH1F>("jet_PT", "p_{T}", 50, 0, 1000);
  GenSubjetNumber = book<TH1F>("number_subjets", "number", 21, 0, 20);

  GenJetTau3Tau2 = book<TH1F>("jet_tau3_tau2", "ratio", 50, 0, 10);
  GenJetTau2Tau1 = book<TH1F>("jet_tau2_tau1", "ratio", 50, 0, 10);
  GenJetTau1 = book<TH1F>("jet_tau1", "tau1", 50, 0, 1);

  GenSubjet1Mass = book<TH1F>("M_Subjet1Mass", "M_{subjet}", n_massbins, 0, 400);
  GenSubjet2Mass = book<TH1F>("M_Subjet2Mass", "M_{subjet}", n_massbins, 0, 400);
  GenSubjet3Mass = book<TH1F>("M_Subjet3Mass", "M_{subjet}", n_massbins, 0, 400);

  GenEachInOneSubjetMass = book<TH1F>("M_EachInOneSubjetMass", "M_{jet}", n_massbins, 0, max_m);
  GenEachInOneSubjetMassAllInJet = book<TH1F>("M_EachInOneSubjetMassAllInJet", "M_{jet}", n_massbins, 0, max_m);

  GenTwoInOneSubjetMass = book<TH1F>("M_TwoInOneSubjetMass", "M_{jet}", n_massbins, 0, max_m);
  GenTwoInOneSubjetMassAllInJet = book<TH1F>("M_TwoInOneSubjetMassAllInJet", "M_{jet}", n_massbins, 0, max_m);
  GenOneInOneSubjetMass = book<TH1F>("M_OneInOneSubjetMass", "M_{jet}", n_massbins, 0, max_m);
  GenOneInOneSubjetMassAllInJet = book<TH1F>("M_OneInOneSubjetMassAllInJet", "M_{jet}", n_massbins, 0, max_m);
  GenNoneInOneSubjetMass = book<TH1F>("M_NoneInOneSubjetMass", "M_{jet}", n_massbins, 0, max_m);
  GenNoneInOneSubjetMassAllInJet = book<TH1F>("M_NoneInOneSubjetMassAllInJet", "M_{jet}", n_massbins, 0, max_m);
  GenAnySubjetMass = book<TH1F>("M_AnySubjetMass", "M_{jet}", n_massbins, 0, max_m);
  GenAnyButNotEachSubjetMass = book<TH1F>("M_AnyButNotEachSubjetMass", "M_{jet}", n_massbins, 0, max_m);

  GenJet1MassAllNoGluons = book<TH1F>("M_jet1_MassAllNoGluons", "M_{jet}", n_massbins, 0, max_m);
  GenJet1MassNotAllNoGluons = book<TH1F>("M_jet1_MassNotAllNoGluons", "M_{jet}", n_massbins, 0, max_m);

  GenJetMassGluon = book<TH1F>("M_jet_MassGluon", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassNoGluon = book<TH1F>("M_jet_MassNoGluon", "M_{jet}", n_massbins, 0, max_m);

  GenJetMassGluonInJet = book<TH1F>("M_jet_MassGluonInJet", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassGluonNotInJet = book<TH1F>("M_jet_MassGluonNotInJet", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassGluonNearTop = book<TH1F>("M_jet_MassGluonNearTop", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassGluonNotNearTop = book<TH1F>("M_jet_MassGluonNotNearTop", "M_{jet}", n_massbins, 0, max_m);

  GenJetMassGluonNearTopAndAllSubjetsMatched = book<TH1F>("M_jet_MassGluonNearTopAndAllSubjetsMatched", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassGluonNotNearTopAndAllSubjetsMatched = book<TH1F>("M_jet_MassGluonNotNearTopAndAllSubjetsMatched", "M_{jet}", n_massbins, 0, max_m);

  PTRatio_bot_subjet = book<TH1F>("pt_bot_subjet", "ratio", 50, 0, 10);
  PTRatio_q1_subjet = book<TH1F>("pt_q1_subjet", "ratio", 50, 0, 10);
  PTRatio_q2_subjet = book<TH1F>("pt_q2_subjet", "ratio", 50, 0, 10);

  SameNearestSubjet = book<TH1F>("Same_nearest_subjet", "number", n_massbins, 0, max_m);

  GenJetMassGluonInSubjet = book<TH1F>("M_jet_MassGluonInSubjet", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassGluonNotInSubjet = book<TH1F>("M_jet_MassGluonNotInSubjet", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassGluonInJetAndSubjet = book<TH1F>("M_jet_MassGluonInJetAndSubjet", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassGluonInJetAndNotSubjet = book<TH1F>("M_jet_MassGluonInJetAndNotSubjet", "M_{jet}", n_massbins, 0, max_m);

  GenJetMassEachInOneSubjetAndGluonInSubjet = book<TH1F>("M_jet_MassEachInOneSubjetAndGluonInSubjet", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassEachInOneSubjetAndGluonNotInSubjet = book<TH1F>("M_jet_MassEachInOneSubjetAndGluonNotInSubjet", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassEachInOneSubjetAndGluonInJet = book<TH1F>("M_jet_MassEachInOneSubjetAndGluonInJet", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassEachInOneSubjetAndGluonNotInJet = book<TH1F>("M_jet_MassEachInOneSubjetAndGluonNotInJet", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassUnmatchedAndGluonInSubjet = book<TH1F>("M_jet_MassUnmatchedAndGluonInSubjet", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassUnmatchedAndGluonNotInSubjet = book<TH1F>("M_jet_MassUnmatchedAndGluonNotInSubjet", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassUnmatchedAndGluonInJet = book<TH1F>("M_jet_MassUnmatchedAndGluonInJet", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassUnmatchedAndGluonNotInJet = book<TH1F>("M_jet_MassUnmatchedAndGluonNotInJet", "M_{jet}", n_massbins, 0, max_m);

  GenJetMassUnmatched = book<TH1F>("M_jet_MassUnmatched", "M_{jet}", n_massbins, 0, max_m);

  deltaR_TTBar = book<TH1F>("deltaR_TTBar", "Delta R(t,tbar)", 80, 0, 4.0);

  GenSubjetPTRatioQ1BotMatched = book<TH1F>("matchedSubjetPT_q1_bot", "pt_{q1}/pt_{bot}", 50, 0, 5);
  GenSubjetPTRatioQ2BotMatched = book<TH1F>("matchedSubjetPT_q2_bot", "pt_{q2}/pt_{bot}", 50, 0, 5);
  GenSubjetPTRatioBotQ1Matched = book<TH1F>("matchedSubjetPT_bot_q1", "pt_{bot}/pt_{q1}", 50, 0, 5);
  GenSubjetPTRatioBotQ2Matched = book<TH1F>("matchedSubjetPT_bot_q2", "pt_{bot}/pt_{q2}", 50, 0, 5);
  GenSubjetPTRatioQ12Matched = book<TH1F>("matchedSubjetPT_q1_q2", "pt_{q1}/pt_{q2}", 50, 0, 5);
  GenSubjetPTRatioQ21Matched = book<TH1F>("matchedSubjetPT_q2_q1", "pt_{q2}/pt_{q1}", 50, 0, 5);

  GenSubjetMRatioQ1BotMatched = book<TH1F>("matchedSubjetM_q1_bot", "M_{q1}/M_{bot}", 50, 0, 5);
  GenSubjetMRatioQ2BotMatched = book<TH1F>("matchedSubjetM_q2_bot", "M_{q2}/M_{bot}", 50, 0, 5);
  GenSubjetMRatioBotQ1Matched = book<TH1F>("matchedSubjetM_bot_q1", "M_{bot}/M_{q1}", 50, 0, 5);
  GenSubjetMRatioBotQ2Matched = book<TH1F>("matchedSubjetM_bot_q2", "M_{bot}/M_{q2}", 50, 0, 5);
  GenSubjetMRatioQ12Matched = book<TH1F>("matchedSubjetM_q1_q2", "M_{q1}/M_{q2}", 50, 0, 5);
  GenSubjetMRatioQ21Matched = book<TH1F>("matchedSubjetM_q2_q1", "M_{q2}/M_{q1}", 50, 0, 5);

  GenSubjetPTRatioQ1JetMatched = book<TH1F>("matchedSubjetPT_q1_jet", "pt_{q1}/pt_{jet}", 50, 0, 1);
  GenSubjetPTRatioQ2JetMatched = book<TH1F>("matchedSubjetPT_q2_jet", "pt_{q2}/pt_{jet}", 50, 0, 1);
  GenSubjetPTRatioBotJetMatched = book<TH1F>("matchedSubjetPT_bot_jet", "pt_{bot}/pt_{jet}", 50, 0, 1);
  GenSubjetPTRatioQuarksJetMatched = book<TH1F>("matchedSubjetPT_quarks_jet", "(pt_{q1}+pt_{q2}+pt_{bot})/pt_{jet}", 50, 0, 2);

  GenSubjetMRatioQ1JetMatched = book<TH1F>("matchedSubjetM_q1_jet", "M_{q1}/M_{jet}", 50, 0, 1);
  GenSubjetMRatioQ2JetMatched = book<TH1F>("matchedSubjetM_q2_jet", "M_{q2}/M_{jet}", 50, 0, 1);
  GenSubjetMRatioBotJetMatched = book<TH1F>("matchedSubjetM_bot_jet", "M_{bot}/M_{jet}", 50, 0, 1);
  GenSubjetMRatioQuarksJetMatched = book<TH1F>("matchedSubjetM_quarks_jet", "(M_{q1}+M_{q2}+M_{bot})/M_{jet}", 50, 0, 1);

  GenPTRatioSubjet1JetMatched = book<TH1F>("matchedPT_subjet1_jet", "pt_{subjet1}/pt_{jet}", 50, 0, 1);
  GenPTRatioSubjet2JetMatched = book<TH1F>("matchedPT_subjet2_jet", "pt_{subjet2}/pt_{jet}", 50, 0, 1);
  GenPTRatioSubjet3JetMatched = book<TH1F>("matchedPT_subjet3_jet", "pt_{subjet3}/pt_{jet}", 50, 0, 1);

  GenMRatioSubjet1JetMatched = book<TH1F>("matchedM_subjet1_jet", "M_{subjet1}/M_{jet}", 50, 0, 1);
  GenMRatioSubjet2JetMatched = book<TH1F>("matchedM_subjet2_jet", "M_{subjet2}/M_{jet}", 50, 0, 1);
  GenMRatioSubjet3JetMatched = book<TH1F>("matchedM_subjet3_jet", "M_{subjet3}/M_{jet}", 50, 0, 1);

  GenPTRatioSubjet1JetUnmatched = book<TH1F>("unmatchedPT_subjet1_jet", "pt_{subjet1}/pt_{jet}", 50, 0, 1);
  GenPTRatioSubjet2JetUnmatched = book<TH1F>("unmatchedPT_subjet2_jet", "pt_{subjet2}/pt_{jet}", 50, 0, 1);
  GenPTRatioSubjet3JetUnmatched = book<TH1F>("unmatchedPT_subjet3_jet", "pt_{subjet3}/pt_{jet}", 50, 0, 1);
  GenPTRatioQuarksJetUnmatched = book<TH1F>("unmatchedPT_quarks_jet", "pt_{quarks}/pt_{jet}", 50, 0, 2);

  GenMRatioSubjet1JetUnmatched = book<TH1F>("unmatchedM_subjet1_jet", "M_{subjet1}/M_{jet}", 50, 0, 1);
  GenMRatioSubjet2JetUnmatched = book<TH1F>("unmatchedM_subjet2_jet", "M_{subjet2}/M_{jet}", 50, 0, 1);
  GenMRatioSubjet3JetUnmatched = book<TH1F>("unmatchedM_subjet3_jet", "M_{subjet3}/M_{jet}", 50, 0, 1);
  GenMRatioQuarksJetUnmatched = book<TH1F>("unmatchedM_quarks_jet", "M_{quarks}/M_{jet}", 50, 0, 1);

  GenJetMassMatchedTop = book<TH1F>("M_jet_MassTopMatched", "M_{jet}", n_massbins, 0, max_m);
  GenJetMassMatchedGluon = book<TH1F>("M_jet_MassGluonMatched", "M_{jet}", n_massbins, 0, max_m);

  GenPTRatioSubjet1JetMatchedTop = book<TH1F>("topMatchedPT_subjet1_jet", "pt_{subjet1}/pt_{jet}", 50, 0, 1);
  GenPTRatioSubjet2JetMatchedTop = book<TH1F>("topMatchedPT_subjet2_jet", "pt_{subjet2}/pt_{jet}", 50, 0, 1);
  GenPTRatioSubjet3JetMatchedTop = book<TH1F>("topMatchedPT_subjet3_jet", "pt_{subjet3}/pt_{jet}", 50, 0, 1);
  GenPTRatioQuarksJetMatchedTop = book<TH1F>("topMatchedPT_quarks_jet", "pt_{quarks}/pt_{jet}", 50, 0, 2);
  GenPTRatioSubjet1Subjet2MatchedTop = book<TH1F>("topMatchedPT_subjet1_subjet2", "pt_{subjet1}/pt_{subjet2}", 50, 0, 5);
  GenPTRatioSubjet2Subjet3MatchedTop = book<TH1F>("topMatchedPT_subjet2_subjet3", "pt_{subjet2}/pt_{subjet3}", 50, 0, 5);
  GenPTRatioSubjet1Subjet3MatchedTop = book<TH1F>("topMatchedPT_subjet1_subjet3", "pt_{subjet1}/pt_{subjet3}", 50, 0, 5);
  GenMRatioSubjet1JetMatchedTop = book<TH1F>("topMatchedM_subjet1_jet", "M_{subjet1}/M_{jet}", 50, 0, 1);
  GenMRatioSubjet2JetMatchedTop = book<TH1F>("topMatchedM_subjet2_jet", "M_{subjet2}/M_{jet}", 50, 0, 1);
  GenMRatioSubjet3JetMatchedTop = book<TH1F>("topMatchedM_subjet3_jet", "M_{subjet3}/M_{jet}", 50, 0, 1);
  GenMRatioQuarksJetMatchedTop = book<TH1F>("topMatchedM_quarks_jet", "M_{quarks}/M_{jet}", 50, 0, 1);
  GenMRatioSubjet1Subjet2MatchedTop = book<TH1F>("topMatchedM_subjet1_subjet2", "M_{subjet1}/M_{subjet2}", 50, 0, 5);
  GenMRatioSubjet2Subjet3MatchedTop = book<TH1F>("topMatchedM_subjet2_subjet3", "M_{subjet2}/M_{subjet3}", 50, 0, 5);
  GenMRatioSubjet1Subjet3MatchedTop = book<TH1F>("topMatchedM_subjet1_subjet3", "M_{subjet1}/M_{subjet3}", 50, 0, 5);

  GenPTRatioSubjet1JetMatchedGluon = book<TH1F>("gluonMatchedPT_subjet1_jet", "pt_{subjet1}/pt_{jet}", 50, 0, 1);
  GenPTRatioSubjet2JetMatchedGluon = book<TH1F>("gluonMatchedPT_subjet2_jet", "pt_{subjet2}/pt_{jet}", 50, 0, 1);
  GenPTRatioSubjet3JetMatchedGluon = book<TH1F>("gluonMatchedPT_subjet3_jet", "pt_{subjet3}/pt_{jet}", 50, 0, 1);
  GenPTRatioQuarksJetMatchedGluon = book<TH1F>("gluonMatchedPT_quarks_jet", "pt_{quarks}/pt_{jet}", 50, 0, 2);
  GenPTRatioSubjet1Subjet2MatchedGluon = book<TH1F>("gluonMatchedPT_subjet1_subjet2", "pt_{subjet1}/pt_{subjet2}", 50, 0, 5);
  GenPTRatioSubjet2Subjet3MatchedGluon = book<TH1F>("gluonMatchedPT_subjet2_subjet3", "pt_{subjet2}/pt_{subjet3}", 50, 0, 5);
  GenPTRatioSubjet1Subjet3MatchedGluon = book<TH1F>("gluonMatchedPT_subjet1_subjet3", "pt_{subjet1}/pt_{subjet3}", 50, 0, 5);
  GenMRatioSubjet1JetMatchedGluon = book<TH1F>("gluonMatchedM_subjet1_jet", "M_{subjet1}/M_{jet}", 50, 0, 1);
  GenMRatioSubjet2JetMatchedGluon = book<TH1F>("gluonMatchedM_subjet2_jet", "M_{subjet2}/M_{jet}", 50, 0, 1);
  GenMRatioSubjet3JetMatchedGluon = book<TH1F>("gluonMatchedM_subjet3_jet", "M_{subjet3}/M_{jet}", 50, 0, 1);
  GenMRatioQuarksJetMatchedGluon = book<TH1F>("gluonMatchedM_quarks_jet", "M_{quarks}/M_{jet}", 50, 0, 1);
  GenMRatioSubjet1Subjet2MatchedGluon = book<TH1F>("gluonMatchedM_subjet1_subjet2", "M_{subjet1}/M_{subjet2}", 50, 0, 5);
  GenMRatioSubjet2Subjet3MatchedGluon = book<TH1F>("gluonMatchedM_subjet2_subjet3", "M_{subjet2}/M_{subjet3}", 50, 0, 5);
  GenMRatioSubjet1Subjet3MatchedGluon = book<TH1F>("gluonMatchedM_subjet1_subjet3", "M_{subjet1}/M_{subjet3}", 50, 0, 5);

  Gen_DeltaR_CombinedMass_NonLepJets = book<TH2F>("DeltaR_CombinedMass_NonLepJets", "delta_R vs M*", 80, 0, 6, n_massbins, 0, max_m);
  Gen_DeltaR_CombinedMass_NonLepJets_PTCutJet = book<TH2F>("DeltaR_CombinedMass_NonLepJets_PTCutJet", "delta_R vs M*", 80, 0, 6, n_massbins, 0, max_m);
  Gen_DeltaR_CombinedMass_NonLepJets_PTCutTop = book<TH2F>("DeltaR_CombinedMass_NonLepJets_PTCutTop", "delta_R vs M*", 80, 0, 6, n_massbins, 0, max_m);

  Gen_DeltaR_Mass1_NonLepJet = book<TH2F>("DeltaR_Mass1_NonLepJet", "delta_R vs M", 80, 0, 6, n_massbins, 0, max_m);
  Gen_DeltaR_Mass1_NonLepJet_PTCutJet = book<TH2F>("DeltaR_Mass1_NonLepJet_PTCutJet", "delta_R vs M", 80, 0, 6, n_massbins, 0, max_m);
  Gen_DeltaR_Mass1_NonLepJet_PTCutTop = book<TH2F>("DeltaR_Mass1_NonLepJet_PTCutTop", "delta_R vs M", 80, 0, 6, n_massbins, 0, max_m);

  Gen_DeltaR_Mass2_NonLepJet = book<TH2F>("DeltaR_Mass2_NonLepJet", "delta_R vs M", 80, 0, 6, n_massbins, 0, max_m);
  Gen_DeltaR_Mass2_NonLepJet_PTCutJet = book<TH2F>("DeltaR_Mass2_NonLepJet_PTCutJet", "delta_R vs M", 80, 0, 6, n_massbins, 0, max_m);
  Gen_DeltaR_Mass2_NonLepJet_PTCutTop = book<TH2F>("DeltaR_Mass2_NonLepJet_PTCutTop", "delta_R vs M", 80, 0, 6, n_massbins, 0, max_m);

  /*
  GenJet2Mass = book<TH1F>("M_jet2", "M_{jet}", 50, 0, 500);
  GenJet2LepMass = book<TH1F>("GenJet2LepMass", "M_{jet2 + lepton}", 50, 0, 500);
  Mass1Mass2 = book<TH1F>("M_jet1-M_jet2+lep", "M_{jet1} - M_{jet2 + lepton}", 40, -200, 200);

  GenJet1PT = book<TH1F>("pt_jet1", "p_{T}", 50, 0, 1000);
  GenJet2PT = book<TH1F>("pt_jet2", "p_{T}", 50, 0, 1000);
  GenJet1Jet2PT = book<TH1F>("pt_jet1-pt_jet2", "p_{T,jet1} - p_{T,jet2}", 80, -400, 400);
  GenJet3PT = book<TH1F>("pt_jet3", "p_{T}", 50, 0, 1000);
  GenJet4PT = book<TH1F>("pt_jet4", "p_{T}", 50, 0, 1000);
  GenJet5PT = book<TH1F>("pt_jet5", "p_{T}", 50, 0, 1000);
  LeptonPT = book<TH1F>("pt_lepton", "p_{T}", 50, 0, 1000);

  TopHadPT = book<TH1F>("pt_tophad", "p_{T}", 20, 0, 1000);
  TopLepPT = book<TH1F>("pt_toplep", "p_{T}", 20, 0, 1000);
  BotHadPT = book<TH1F>("pt_bothad", "p_{T}", 40, 0, 800);
  BotLepPT = book<TH1F>("pt_botlep", "p_{T}", 40, 0, 800);

  GenJet2Eta = book<TH1F>("eta_jet2", "#eta", 24, -3, 3);

  deltaR_lep1_jet1 = book<TH1F>("deltaR_lep1_jet1", "#Delta R(lep1,1st Jet)", 80, 0, 4.0);
  deltaR_lep2_jet1 = book<TH1F>("deltaR_lep2_jet1", "#Delta R(lep2,1st Jet)", 80, 0, 4.0);
  deltaR_botlep_jet1 = book<TH1F>("deltaR_botlep_jet1", "#Delta R(bot_lep,1st Jet)", 80, 0, 4.0);
  deltaR_bot_jet1 = book<TH1F>("deltaR_bot_jet1", "#Delta R(bot,1st Jet)", 80, 0, 4.0);
  deltaR_q1_jet1 = book<TH1F>("deltaR_q1_jet1", "#Delta R(q1,1st Jet)", 80, 0, 4.0);
  deltaR_q2_jet1 = book<TH1F>("deltaR_q2_jet1", "#Delta R(q2,1st Jet)", 80, 0, 4.0);
  deltaR_tophad_jet1 = book<TH1F>("deltaR_tophad_jet1", "#Delta R(had Top, 1st Jet)", 80, 0, 4.0);
  deltaR_toplep_jet1 = book<TH1F>("deltaR_toplep_jet1", "#Delta R(lep Top, 1st Jet)", 80, 0, 4.0);

  deltaR_lep1_jet2 = book<TH1F>("deltaR_lep1_jet2", "#Delta R(lep1,2nd Jet)", 80, 0, 4.0);
  deltaR_lep2_jet2 = book<TH1F>("deltaR_lep2_jet2", "#Delta R(lep2,2nd Jet)", 80, 0, 4.0);
  deltaR_botlep_jet2 = book<TH1F>("deltaR_botlep_jet2", "#Delta R(bot_lep,2nd Jet)", 80, 0, 4.0);
  deltaR_bot_jet2 = book<TH1F>("deltaR_bot_jet2", "#Delta R(bot,2nd Jet)", 80, 0, 4.0);
  deltaR_q1_jet2 = book<TH1F>("deltaR_q1_jet2", "#Delta R(q1,2nd Jet)", 80, 0, 4.0);
  deltaR_q2_jet2 = book<TH1F>("deltaR_q2_jet2", "#Delta R(q2,2nd Jet)", 80, 0, 4.0);
  deltaR_tophad_jet2 = book<TH1F>("deltaR_tophad_jet2", "#Delta R(had Top, 2nd Jet)", 80, 0, 4.0);
  deltaR_toplep_jet2 = book<TH1F>("deltaR_toplep_jet2", "#Delta R(lep Top, 2nd Jet)", 80, 0, 4.0);

  deltaPhi_lep1_jet1 = book<TH1F>("deltaPhi_lep1_jet1", "#Delta #Phi(lep1,1st Jet)", 80, 0, 4.0);
  deltaPhi_lep1_jet2 = book<TH1F>("deltaPhi_lep1_jet2", "#Delta #Phi(lep1,2nd Jet)", 80, 0, 4.0);

  dR_GenParts_highest = book<TH1F>("dR_GenParts_largest_for_partons", "highest #Delta R between top had products", 80, 0, 4.0);
  dR_GenParts_lowest = book<TH1F>("dR_GenParts_lowest_for_partons", "lowest #Delta R between top had products", 80, 0, 4.0);
  dR_GenParts_highest_toppt = book<TH2F>("dR_GenParts_largest_for_partons_toppt", "x=p_T_tophad y=#Delta R(high)", 20, 0 , 1000, 40, 0, 4.0);
  dR_GenParts_lowest_toppt = book<TH2F>("dR_GenParts_lowest_for_partons_toppt", "x=p_T_tophad y=#Delta R(low)", 20, 0 , 1000, 40, 0, 4.0);

  dR_GenParts_q1_q2 = book<TH1F>("dR_GenParts_q1_q2", "#Delta R(q1, q2)", 80, 0, 4.0);
  dR_GenParts_bot_q1 = book<TH1F>("dR_GenParts_bot_q1", "#Delta R(bot, q1)", 80, 0, 4.0);
  dR_GenParts_bot_q2 = book<TH1F>("dR_GenParts_bot_q2", "#Delta R(bot, q2)", 80, 0, 4.0);
  dR_GenParts_q1_q2_toppt = book<TH2F>("dR_GenParts_q1_q2_toppt", "x=p_T_tophad y=#Delta R(q1, q2)", 20, 0 , 1000, 40, 0, 4.0);
  dR_GenParts_bot_q1_toppt = book<TH2F>("dR_GenParts_bot_q1_toppt", "x=p_T_tophad y=#Delta R(bot, q1)", 20, 0 , 1000,  40, 0, 4.0);
  dR_GenParts_bot_q2_toppt = book<TH2F>("dR_GenParts_bot_q2_toppt", "x=p_T_tophad y=#Delta R(bot, q2)", 20, 0 , 1000,  40, 0, 4.0);

  Eta_Phi_jet1 = book<TH2F>("Eta_Phi_jet1", "x=#eta y=#Phi", 30, -3 , 3,  40, -4, 4);
  Eta_Phi_bot = book<TH2F>("Eta_Phi_bot", "x=#eta y=#Phi", 30, -3 , 3,  40, -4, 4);
  Eta_Phi_q1 = book<TH2F>("Eta_Phi_q1", "x=#eta y=#Phi", 30, -3 , 3,  40, -4, 4);
  Eta_Phi_q2 = book<TH2F>("Eta_Phi_q2", "x=#eta y=#Phi", 30, -3 , 3,  40, -4, 4);

  // deltaR_lep1_jet3 = book<TH1F>("deltaR_lep1_jet3", "#Delta R(lep1,3rd Jet)", 80, 0, 4.0);
  // deltaR_lep2_jet3 = book<TH1F>("deltaR_lep2_jet3", "#Delta R(lep2,3rd Jet)", 80, 0, 4.0);
  // deltaR_botlep_jet3 = book<TH1F>("deltaR_botlep_jet3", "#Delta R(bot_lep,3rd Jet)", 80, 0, 4.0);
  // deltaR_bot_jet3 = book<TH1F>("deltaR_bot_jet3", "#Delta R(bot,3rd Jet)", 80, 0, 4.0);
  // deltaR_q1_jet3 = book<TH1F>("deltaR_q1_jet3", "#Delta R(q1,3rd Jet)", 80, 0, 4.0);
  // deltaR_q2_jet3 = book<TH1F>("deltaR_q2_jet3", "#Delta R(q2,3rd Jet)", 80, 0, 4.0);
  // deltaR_tophad_jet3 = book<TH1F>("deltaR_tophad_jet3", "#Delta R(had Top, 3rd Jet)", 80, 0, 4.0);
  // deltaR_toplep_jet3 = book<TH1F>("deltaR_toplep_jet3", "#Delta R(lep Top, 3rd Jet)", 80, 0, 4.0);

  // deltaR_lep1_jet4 = book<TH1F>("deltaR_lep1_jet4", "#Delta R(lep1,4th Jet)", 80, 0, 4.0);
  // deltaR_lep2_jet4 = book<TH1F>("deltaR_lep2_jet4", "#Delta R(lep2,4th Jet)", 80, 0, 4.0);
  // deltaR_botlep_jet4 = book<TH1F>("deltaR_botlep_jet4", "#Delta R(bot_lep,4th Jet)", 80, 0, 4.0);
  // deltaR_bot_jet4 = book<TH1F>("deltaR_bot_jet4", "#Delta R(bot,4th Jet)", 80, 0, 4.0);
  // deltaR_q1_jet4 = book<TH1F>("deltaR_q1_jet4", "#Delta R(q1,4th Jet)", 80, 0, 4.0);
  // deltaR_q2_jet4 = book<TH1F>("deltaR_q2_jet4", "#Delta R(q2,4th Jet)", 80, 0, 4.0);
  // deltaR_tophad_jet4 = book<TH1F>("deltaR_tophad_jet4", "#Delta R(had Top, 4th Jet)", 80, 0, 4.0);
  // deltaR_toplep_jet4 = book<TH1F>("deltaR_toplep_jet4", "#Delta R(lep Top, 4th Jet)", 80, 0, 4.0);

  // deltaR_lep1_jet5 = book<TH1F>("deltaR_lep1_jet5", "#Delta R(lep1,5th Jet)", 80, 0, 4.0);
  // deltaR_lep2_jet5 = book<TH1F>("deltaR_lep2_jet5", "#Delta R(lep2,5th Jet)", 80, 0, 4.0);
  // deltaR_botlep_jet5 = book<TH1F>("deltaR_botlep_jet5", "#Delta R(bot_lep,5th Jet)", 80, 0, 4.0);
  // deltaR_bot_jet5 = book<TH1F>("deltaR_bot_jet5", "#Delta R(bot,5th Jet)", 80, 0, 4.0);
  // deltaR_q1_jet5 = book<TH1F>("deltaR_q1_jet5", "#Delta R(q1,5th Jet)", 80, 0, 4.0);
  // deltaR_q2_jet5 = book<TH1F>("deltaR_q2_jet5", "#Delta R(q2,5th Jet)", 80, 0, 4.0);
  // deltaR_tophad_jet5 = book<TH1F>("deltaR_tophad_jet5", "#Delta R(had Top, 5th Jet)", 80, 0, 4.0);
  // deltaR_toplep_jet5 = book<TH1F>("deltaR_toplep_jet5", "#Delta R(lep Top, 5th Jet)", 80, 0, 4.0);

  // deltaR_lep1_jet6 = book<TH1F>("deltaR_lep1_jet6", "#Delta R(lep1,6th Jet)", 80, 0, 4.0);
  // deltaR_lep2_jet6 = book<TH1F>("deltaR_lep2_jet6", "#Delta R(lep2,6th Jet)", 80, 0, 4.0);
  // deltaR_botlep_jet6 = book<TH1F>("deltaR_botlep_jet6", "#Delta R(bot_lep,6th Jet)", 80, 0, 4.0);
  // deltaR_bot_jet6 = book<TH1F>("deltaR_bot_jet6", "#Delta R(bot,6th Jet)", 80, 0, 4.0);
  // deltaR_q1_jet6 = book<TH1F>("deltaR_q1_jet6", "#Delta R(q1,6th Jet)", 80, 0, 4.0);
  // deltaR_q2_jet6 = book<TH1F>("deltaR_q2_jet6", "#Delta R(q2,6th Jet)", 80, 0, 4.0);
  // deltaR_tophad_jet6 = book<TH1F>("deltaR_tophad_jet6", "#Delta R(had Top, 6th Jet)", 80, 0, 4.0);
  // deltaR_toplep_jet6 = book<TH1F>("deltaR_toplep_jet6", "#Delta R(lep Top, 6th Jet)", 80, 0, 4.0);
  */

  // handle for TTbarGen class
  h_ttbargen=ctx.get_handle<TTbarGen>("ttbargen");
  // handle for clustered jets
  h_jets=ctx.get_handle<std::vector<GenTopJet>>(jetname);

  debug = string2bool(ctx.get("Debug","false"));
}

void createSubjetQuarkDeltaRMatrix(std::vector<GenJet> subjets, std::vector<GenParticle> quarks, std::vector<std::vector<double>>* matrix) {
  unsigned int nSubjets = subjets.size();
  unsigned int nQuarks = quarks.size();

  for(unsigned int i=0; i<nSubjets; i++) {
    for(unsigned int j=0; j<nQuarks; j++) {
      matrix->at(i).at(j) = deltaR(subjets.at(i), quarks.at(j));
    }
  }
}

int nearestSubjet(GenParticle q, std::vector<GenJet> subjets) {
  double minR = 100;
  int minIndex = -1;

  for(unsigned int i=0; i<subjets.size(); i++) {
    double tmpR = deltaR(q, subjets.at(i));
    if(printOut) cout << tmpR << ", ";
    if(tmpR < minR) {
      minR = tmpR;
      minIndex = i;
    }
  }
  if(printOut) cout << endl;

  return minIndex;
}

bool GenHists_GenOnly::subjetMatching(std::vector<GenJet> subjets, std::vector<GenParticle> quarks, unsigned int* remaining_quarks, bool unique, std::vector<int>* subjetIndices) {
  
  bool matched = true;
  for(unsigned int i=0; i<subjets.size(); i++) {

    double minR = 100;
    int j_remove = -1;

    if(printOut) cout << "subjet " << i << ": ";

    for(unsigned int j=0; j<quarks.size(); j++) {

      double tmpR = deltaR(quarks.at(j), subjets.at(i));
      if(tmpR < minR) {
        minR = tmpR;
        j_remove = j;
      }
    }

    if(minR > subjetRadius) {
      matched = false;
    } else {
      if(unique) {//wether or not each subjet can only be matched to one quark
        quarks.erase(quarks.begin()+j_remove);
      }
      if(subjetIndices != nullptr) subjetIndices->at(i) = j_remove;
    }

    if(printOut) cout << "minR = " << minR << ", j_remove = " << j_remove << endl;

  }

  if(remaining_quarks != nullptr) {
    *remaining_quarks = quarks.size();

    if(printOut) cout << ", remaining quarks = " << *remaining_quarks << endl;
  }
  return matched;
}

//"gluons" might not be exclusively gluons
static GenParticle* gluonInEvent(const Event & event) {
  std::vector<GenParticle> *genparticles = event.genparticles;
  int nparts = genparticles->size();
  
  GenParticle* gluon = nullptr;
  //look for outgoing gluons in jet
  for(int i=0; i<nparts; ++i) {
    GenParticle* p = &(genparticles->at(i));

    auto mother1 = p->mother(genparticles,1);
    auto mother2 = p->mother(genparticles,2);

    if(mother1 != nullptr && mother2 != nullptr) {
      if(abs(p->pdgId()) != 6 && mother1->status() == 21 && mother2->status() == 21) {
        if(p->pt() > 5) gluon = p;
      }
    }
  }

  return gluon;
}

bool compareSubjets(GenJet subjet1, GenJet subjet2) {
  return subjet1.pt()>subjet2.pt();
}

uint nearestJet(GenTopJet jet, vector<GenTopJet> jets) {
  double minDR = 999.0;
  uint minI = 7;
  double tmpDR;
  
  for(uint i=0; i<jets.size(); i++) {
    tmpDR = deltaR(jet, jets.at(i));
    if(tmpDR != 0 && tmpDR < minDR) {
      tmpDR = minDR;
      minI = i;
    }
  }

  return minI;
}

void GenHists_GenOnly::fill(const Event & event){

  if(debug) cout << "--- fill GenHists ---" << endl;
  //---------------------------------------------------------------------------------------
  //--------------------------------- get first 13 gen parts -------------------------------
  //---------------------------------------------------------------------------------------
  // GenParticle* genp;
  // int id;
  // for(unsigned int i=0; i<13; ++i){
  //    genp = &(genparts->at(i));
  //    id = genp->pdgId();
  //    cout<<"ID of genparticle nr. " << i <<" : "<< id << endl;
  // }
  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------

  //---------------------------------------------------------------------------------------
  //--------------------------------- define needed objects-----------------------------------
  //---------------------------------------------------------------------------------------
  if(debug) cout << "\t--- define needed objects" << endl;
  const auto & ttbargen = event.get(h_ttbargen);
  // define all objects needed
  if(debug) cout << "\t\t--- get jets" << endl;
  std::vector<GenTopJet> jets = event.get(h_jets);
  TLorentzVector jet1_v4, jeti_v4, botSubjet_v4, q1Subjet_v4, q2Subjet_v4;
  std::vector<TLorentzVector> subjets_v4 = {};
  std::vector<TLorentzVector> sortedSubjets_v4 = {};
  std::vector<TLorentzVector> jets_v4;

  TLorentzVector lepton1_v4, jet2_lep_v4, topjet1_v4, topjet2_v4;
  GenTopJet jet1,jet2,jet3,jet4,jet5,jet6;
  std::vector<GenJet> subjets, sortedSubjets;
  if(debug) cout << "\t\t--- get jet1" << endl;
  if(jets.size()>0) {
    jet1 = jets.at(0);
    subjets = jet1.subjets();
    sortedSubjets = jet1.subjets();
  }
  if(debug) cout << "\t\t--- get jet2" << endl;
  if(jets.size()>1) jet2 = jets.at(1);
  if(jets.size()>2) jet3 = jets.at(2);
  if(jets.size()>3) jet4 = jets.at(3);
  // if(jets.size()>4) jet5 = jets.at(4);
  // if(jets.size()>5) jet6 = jets.at(5);

  if(debug) cout << "\t\t--- set jets_v4" << endl;

  for(uint i=0; i<jets.size(); i++) {
    jeti_v4.SetPxPyPzE(jets.at(i).v4().Px(), jets.at(i).v4().Py(), jets.at(i).v4().Pz(), jets.at(i).v4().E());
    jets_v4.push_back(jeti_v4);
  }

  std::sort(sortedSubjets.begin(), sortedSubjets.end(), compareSubjets);

  //cout << "sorted subjet pts: " << sortedSubjets.at(0).pt() << ", " << sortedSubjets.at(1).pt() << ", " << sortedSubjets.at(2).pt() << endl;

  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------


  //---------------------------------------------------------------------------------------
  //--------------------------------- Matching --------------------------------------------
  //---------------------------------------------------------------------------------------
  if(debug) cout << "\t--- Matching" << endl;

  bool isTTBar = true;

  // get stable particles from ttbar decay and sort them into leptonic and hadronic

  GenParticle bot, q1, q2, bot_lep, lep1, lep2, lepton, top, antitop; //leptons already defined above
  if(jets.size() > 0){
    if(ttbargen.IsTopHadronicDecay()){
      bot = ttbargen.bTop();
      q1 = ttbargen.Wdecay1();
      q2 = ttbargen.Wdecay2();
      bot_lep = ttbargen.bAntitop();
      lep1 = ttbargen.WMinusdecay1();
      lep2 = ttbargen.WMinusdecay2();
      top = ttbargen.Top();
      antitop = ttbargen.Antitop();
    }
    else if(ttbargen.IsAntiTopHadronicDecay()){
      bot = ttbargen.bAntitop();
      q1 = ttbargen.WMinusdecay1();
      q2 = ttbargen.WMinusdecay2();
      bot_lep = ttbargen.bTop();
      lep1 = ttbargen.Wdecay1();
      lep2 = ttbargen.Wdecay2();
      top = ttbargen.Antitop();
      antitop = ttbargen.Top();
    } 
    else {
      isTTBar = false;
      //cout << "-- no hadronic decay found" << endl;
    }
    //check which lep is neutrino and which is elec/muon
    if(abs(lep1.pdgId()) == 11 || abs(lep1.pdgId()) == 13){
      lepton = lep1;
    }
    else if(abs(lep2.pdgId()) == 11 || abs(lep2.pdgId()) == 13){
      lepton = lep2;
    }
  }

  const GenParticle* gluonPtr = gluonInEvent(event);
  GenParticle gluon;
  bool gluonPresent = gluonPtr != nullptr;
  if(gluonPresent) gluon = *gluonPtr;


  double genweight = event.weight;

  if(jets.size()>0) jet1_v4.SetPxPyPzE(jets.at(0).v4().Px(), jets.at(0).v4().Py(), jets.at(0).v4().Pz(), jets.at(0).v4().E());

  uint gluonI = 7;

  for(uint i=0; i<jets.size(); i++) {
    if(deltaR(jets.at(i), top) < jetradius) {
      GenMatchedTopInAnyJet->Fill(jets_v4.at(i).M(), genweight);
      if(top.pt() > 400) {
        GenMatchedTopInAnyJetPtCut->Fill(jets_v4.at(i).M(), genweight);
        uint nearestToTopPtCut = nearestJet(jets.at(i), jets);
        if(nearestToTopPtCut != 7) {
          GenDeltaRTopPtCutNearest->Fill(deltaR(jets.at(i), jets.at(nearestToTopPtCut)), genweight);
        }
      }
      if(jets.at(i).pt() > 400) {
        GenMatchedTopInAnyJetPtCut2->Fill(jets_v4.at(i).M(), genweight);
        uint nearestToTopJetPtCut = nearestJet(jets.at(i), jets);
        if(nearestToTopJetPtCut != 7) {
          GenDeltaRJetPtCutNearest->Fill(deltaR(jets.at(i), jets.at(nearestToTopJetPtCut)), genweight);
        }
      }
    }

    if(gluonPresent) {
      if(deltaR(jets.at(i), gluon) < jetradius) {
        GenMatchedGluonInAnyJet->Fill(jets_v4.at(i).M(), genweight);
        if(jets.at(i).pt() > 400) GenMatchedGluonInAnyJetPtCut->Fill(jets_v4.at(i).M(), genweight);
        gluonI = i;
      }
    }
  }

  for(uint i=0; i<jets.size(); i++) {
    if(i != gluonI) {
      if(jets.at(i).pt() > 400) GenMatchedGluonInAnyJetPtCutOtherJet->Fill(jets_v4.at(i).M(), genweight);
    }
  }

  GenJetMass->Fill(jet1_v4.M(), genweight);

  for(uint i=0; i<jets_v4.size(); i++) {
    GenJetMassAllJets->Fill(jets_v4.at(i).M(), genweight);
  }

  if(jets.size() > 1) {
    TLorentzVector combinedJets = jets_v4.at(0) + jets_v4.at(1);
    Gen_DeltaR_CombinedMass_NonLepJets->Fill(deltaR(jets.at(0), jets.at(1)), combinedJets.M(), genweight);
    if(jets.at(0).pt() > 400 || jets.at(1).pt() > 400)  Gen_DeltaR_CombinedMass_NonLepJets_PTCutJet->Fill(deltaR(jets.at(0), jets.at(1)), combinedJets.M(), genweight);
    if(top.pt() > 400)                                  Gen_DeltaR_CombinedMass_NonLepJets_PTCutTop->Fill(deltaR(jets.at(0), jets.at(1)), combinedJets.M(), genweight);

    Gen_DeltaR_Mass1_NonLepJet->Fill(deltaR(jets.at(0), jets.at(1)), jets_v4.at(0).M(), genweight);
    if(jets.at(0).pt() > 400) Gen_DeltaR_Mass1_NonLepJet_PTCutJet->Fill(deltaR(jets.at(0), jets.at(1)), jets_v4.at(0).M(), genweight);
    if(top.pt() > 400)        Gen_DeltaR_Mass1_NonLepJet_PTCutTop->Fill(deltaR(jets.at(0), jets.at(1)), jets_v4.at(0).M(), genweight);

    Gen_DeltaR_Mass2_NonLepJet->Fill(deltaR(jets.at(0), jets.at(1)), jets_v4.at(0).M(), genweight);
    if(jets.at(0).pt() > 400) Gen_DeltaR_Mass2_NonLepJet_PTCutJet->Fill(deltaR(jets.at(0), jets.at(1)), jets_v4.at(0).M(), genweight);
    if(top.pt() > 400)        Gen_DeltaR_Mass2_NonLepJet_PTCutTop->Fill(deltaR(jets.at(0), jets.at(1)), jets_v4.at(0).M(), genweight);
  }

  deltaR_TTBar->Fill(deltaR(top, antitop), genweight);
  
  double dR12, dR23, dR31;

  if(jets.size() == 3) {
    dR12 = deltaR(jets.at(0), jets.at(1));
    dR23 = deltaR(jets.at(1), jets.at(2));
    dR31 = deltaR(jets.at(2), jets.at(0));
    GenDeltaRJet1Jet2->Fill(dR12, genweight);
    GenDeltaRJet2Jet3->Fill(dR23, genweight);
    GenDeltaRJet3Jet1->Fill(dR31, genweight);

    if(dR12 == 0) GenDeltaRJetsPtDiff->Fill(jets.at(0).pt()/* - jets.at(1).pt()*/, genweight);
    if(dR23 == 0) GenDeltaRJetsPtDiff->Fill(jets.at(1).pt()/* - jets.at(2).pt()*/, genweight);
    if(dR31 == 0) GenDeltaRJetsPtDiff->Fill(jets.at(2).pt()/* - jets.at(0).pt()*/, genweight);

    if(jets.at(0).subjets().size() == 3) {
      GenJet1DeltaRSubjet1Subjet2->Fill(deltaR(jets.at(0).subjets().at(0), jets.at(0).subjets().at(1)), genweight);
      GenJet1DeltaRSubjet2Subjet3->Fill(deltaR(jets.at(0).subjets().at(1), jets.at(0).subjets().at(2)), genweight);
      GenJet1DeltaRSubjet3Subjet1->Fill(deltaR(jets.at(0).subjets().at(2), jets.at(0).subjets().at(0)), genweight);
    }

    if(jets.at(1).subjets().size() == 3) {
      GenJet2DeltaRSubjet1Subjet2->Fill(deltaR(jets.at(1).subjets().at(0), jets.at(1).subjets().at(1)), genweight);
      GenJet2DeltaRSubjet2Subjet3->Fill(deltaR(jets.at(1).subjets().at(1), jets.at(1).subjets().at(2)), genweight);
      GenJet2DeltaRSubjet3Subjet1->Fill(deltaR(jets.at(1).subjets().at(2), jets.at(1).subjets().at(0)), genweight);
    }

    if(jets.at(2).subjets().size() == 3) {
      GenJet3DeltaRSubjet1Subjet2->Fill(deltaR(jets.at(2).subjets().at(0), jets.at(2).subjets().at(1)), genweight);
      GenJet3DeltaRSubjet2Subjet3->Fill(deltaR(jets.at(2).subjets().at(1), jets.at(2).subjets().at(2)), genweight);
      GenJet3DeltaRSubjet3Subjet1->Fill(deltaR(jets.at(2).subjets().at(2), jets.at(2).subjets().at(0)), genweight);
    }
  }

  if(isTTBar) {

  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------



  //---------------------------------------------------------------------------------------
  //-------- set Lorentz Vectors of 2 jets and lepton -------------------------------------
  //---------------------------------------------------------------------------------------
  if(debug) cout << "\t--- Lorentz Vectors" << endl;
  // if(jets.size() > 1){
      if(subjets.size() == 3) {
        for(unsigned int i=0; i<subjets.size(); i++) {
          TLorentzVector tmp_v4;
          tmp_v4.SetPxPyPzE(subjets.at(i).v4().Px(), subjets.at(i).v4().Py(), subjets.at(i).v4().Pz(), subjets.at(i).v4().E());
          subjets_v4.push_back(tmp_v4);
          tmp_v4.SetPxPyPzE(sortedSubjets.at(i).v4().Px(), sortedSubjets.at(i).v4().Py(), sortedSubjets.at(i).v4().Pz(), sortedSubjets.at(i).v4().E());
          sortedSubjets_v4.push_back(tmp_v4);
        }
      }
      
      //jet2_v4.SetPxPyPzE(jets.at(1).v4().Px(), jets.at(1).v4().Py(), jets.at(1).v4().Pz(), jets.at(1).v4().E()); //v4 of first jet

      /*

      lepton1_v4.SetPxPyPzE(lepton.v4().Px(), lepton.v4().Py(), lepton.v4().Pz(), lepton.v4().E()); //v4 of lepton
      jet2_lep_v4 = jet2_v4 + lepton1_v4;

      */

  // }
  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------




  //---------------------------------------------------------------------------------------
  //--------------------------------- Fill Hists here -------------------------------------
  //---------------------------------------------------------------------------------------

  if(debug) cout << "\t--- Fill Hists" << endl;

  GenTTBarJetMass->Fill(jet1_v4.M(), genweight);
  GenJetNumber->Fill(jets.size(), genweight);
  GenJetPT->Fill(jet1.pt(), genweight);
  GenSubjetNumber->Fill(subjets.size(), genweight);

  GenJetTau3Tau2->Fill(jet1.tau3()/jet1.tau2(), genweight);
  GenJetTau2Tau1->Fill(jet1.tau2()/jet1.tau1(), genweight);
  GenJetTau1->Fill(jet1.tau1(), 1);

  if(debug) cout << "\t--- Fill subjetmass Hists" << endl;

  if(subjets_v4.size() == 3) {
    GenSubjet1Mass->Fill(subjets_v4.at(0).M(), genweight);
    GenSubjet2Mass->Fill(subjets_v4.at(1).M(), genweight);
    GenSubjet3Mass->Fill(subjets_v4.at(2).M(), genweight);
  }

  if(debug) cout << "\t--- General Hists done" << endl;
  
  /*

  LeptonPT->Fill(lepton1_v4.Pt(),weight);

  float pt;
  for(unsigned int i = 0; i<jets.size(); ++i){
    pt = jets.at(i).pt();
    GenJetPT->Fill(pt, weight);
  }

  */

  bool gluonInJet;
  if(gluonPresent) gluonInJet = deltaR(gluon, jet1) <= jetradius;
  else gluonInJet = false;

  bool gluonNearTop = deltaR(top, gluon) <= jetradius;
  bool gluonInSubjet; 
  if(gluonPresent && subjets.size() == 3) gluonInSubjet = deltaR(gluon, subjets[nearestSubjet(gluon, subjets)]) <= subjetRadius;
  else gluonInSubjet = false;

  bool topMatched = deltaR(top, jet1) <= jetradius;
  bool gluonMatched = !topMatched && gluonInJet;

  if(debug) cout << "\t--- gluon matching done" << endl;

  std::vector<GenParticle> quarks = {bot, q1, q2};
  std::vector<GenParticle> quarksReversed = {q2, q1, bot};

  std::vector<int> subjetIndices = {-1, -1, -1};
  unsigned int remaining_quarks1 = 0;
  unsigned int remaining_quarks2 = 0;
  bool subjet_matching1 = subjetMatching(subjets, quarks, &remaining_quarks1, true, &subjetIndices);
  bool subjet_matching2 = false;//subjetMatching(subjets, quarksReversed, &remaining_quarks2, true, &subjetIndices);

  unsigned int  remaining_quarks = remaining_quarks1;

  /*if(remaining_quarks1 <= remaining_quarks2) remaining_quarks = remaining_quarks1;
  else remaining_quarks = remaining_quarks2;*/

  bool each_subjet_matching = subjet_matching1 || subjet_matching2;

  GenJet botSubjet, q1Subjet, q2Subjet;
  if(each_subjet_matching && subjets.size() == 3) {
    botSubjet = subjets.at(subjetIndices.at(2));
    botSubjet_v4 = subjets_v4.at(subjetIndices.at(2));
    q1Subjet = subjets.at(subjetIndices.at(1));
    q1Subjet_v4 = subjets_v4.at(subjetIndices.at(1));
    q2Subjet = subjets.at(subjetIndices.at(0));
    q2Subjet_v4 = subjets_v4.at(subjetIndices.at(0));
  }

  quarks = {bot, q1, q2};
  bool any_subjet_matching = subjetMatching(subjets, quarks, nullptr, false, nullptr);

  std::vector<std::vector<double>> deltaRMatrix = {{0.0, 0.0, 0.0},
                                                   {0.0, 0.0, 0.0},
                                                   {0.0, 0.0, 0.0}};

  createSubjetQuarkDeltaRMatrix(subjets, quarks, &deltaRMatrix);

  if(debug) cout << "\t--- subjet matching prep done" << endl;

  //cout << "deltaR_subjet1_bot: " << deltaRMatrix.at(0).at(0) << endl;

  bool botPassed = deltaR(bot, jet1) <= jetradius;
  bool q1Passed = deltaR(q1, jet1) <= jetradius;
  bool q2Passed = deltaR(q2, jet1) <= jetradius;

  bool allPassed = botPassed && q1Passed && q2Passed;

  if(botPassed && !q1Passed && !q2Passed) {
    GenJet1MassBot->Fill(jet1_v4.M(), genweight);
    if(gluonInJet) GenJet1MassGluonBot->Fill(jet1_v4.M(), genweight);
  }

  if(botPassed && ((q1Passed && !q2Passed) || (!q1Passed && q2Passed))) {
    GenJet1MassBotOneLightQ->Fill(jet1_v4.M(), genweight);
    if(gluonInJet) GenJet1MassGluonBotOneLightQ->Fill(jet1_v4.M(), genweight);
    GenJet1MassRest->Fill(jet1_v4.M(), genweight);
  }

  if((botPassed && !(q1Passed || q2Passed)) || (!botPassed && ((q1Passed && !q2Passed) || (!q1Passed && q2Passed)))) {
    GenJet1MassOneQ->Fill(jet1_v4.M(), genweight);
    if(gluonInJet) GenJet1MassGluonOneQ->Fill(jet1_v4.M(), genweight);
    GenJet1MassRest->Fill(jet1_v4.M(), genweight);
  }

  if(!botPassed && q1Passed && q2Passed) {
    GenJet1MassTwoLightQ->Fill(jet1_v4.M(), genweight);
    if(gluonInJet) GenJet1MassGluonTwoLightQ->Fill(jet1_v4.M(), genweight);
    GenJet1MassRest->Fill(jet1_v4.M(), genweight);
  }

  if(!botPassed && !q1Passed && !q2Passed) {
    GenJet1MassNoQ->Fill(jet1_v4.M(), genweight);
    if(gluonInJet) GenJet1MassGluonNoQ->Fill(jet1_v4.M(), genweight);
    GenJet1MassRest->Fill(jet1_v4.M(), genweight);
  }

  if(allPassed) {
    GenJet1MassAll->Fill(jet1_v4.M(), genweight);
    if(gluonInJet) GenJet1MassGluonAll->Fill(jet1_v4.M(), genweight);
  } else {
    GenJet1MassNotAll->Fill(jet1_v4.M(), genweight);
  }

  if(allPassed && !gluonInJet) {
    GenJet1MassAllNoGluons->Fill(jet1_v4.M(), genweight);
  } else {
    GenJet1MassNotAllNoGluons->Fill(jet1_v4.M(), genweight);
  }

  if(debug) cout << "\t--- quark Hists done" << endl;

  if(gluonPresent) {
    GenJetMassGluon->Fill(jet1_v4.M(), genweight);

    if(gluonInJet) {
      GenJetMassGluonInJet->Fill(jet1_v4.M(), genweight);

      if(gluonInSubjet) {
        GenJetMassGluonInJetAndSubjet->Fill(jet1_v4.M(), genweight);
      } else {
      GenJetMassGluonInJetAndNotSubjet->Fill(jet1_v4.M(), genweight);
      }
    } else {
      GenJetMassGluonNotInJet->Fill(jet1_v4.M(), genweight);
    }

    if(gluonNearTop) {
      GenJetMassGluonNearTop->Fill(jet1_v4.M(), genweight);
    } else {
      GenJetMassGluonNotNearTop->Fill(jet1_v4.M(), genweight);
    }

    if(gluonInSubjet) {
      GenJetMassGluonInSubjet->Fill(jet1_v4.M(), genweight);
    } else {
      GenJetMassGluonNotInSubjet->Fill(jet1_v4.M(), genweight);
    }
  } else {
    GenJetMassNoGluon->Fill(jet1_v4.M(), genweight);
  }

  if(debug) cout << "\t--- gluonPresent Hists done" << endl;

  if(topMatched) {
    GenJetMassMatchedTop->Fill(jet1_v4.M(), genweight);

    if(sortedSubjets.size() == 3) {
      if(!(sortedSubjets.at(0).pt() == 0 || sortedSubjets.at(1).pt() == 0 || sortedSubjets.at(2).pt() == 0 || jet1.pt() == 0)) {
        GenPTRatioSubjet1JetMatchedTop->Fill(sortedSubjets.at(0).pt()/jet1.pt(), genweight);
        GenPTRatioSubjet2JetMatchedTop->Fill(sortedSubjets.at(1).pt()/jet1.pt(), genweight);
        GenPTRatioSubjet3JetMatchedTop->Fill(sortedSubjets.at(2).pt()/jet1.pt(), genweight);
        GenPTRatioQuarksJetMatchedTop->Fill((sortedSubjets.at(0).pt()+sortedSubjets.at(1).pt()+sortedSubjets.at(2).pt())/jet1.pt(), genweight);
        GenPTRatioSubjet1Subjet2MatchedTop->Fill(sortedSubjets.at(0).pt()/sortedSubjets.at(1).pt(), genweight);
        GenPTRatioSubjet2Subjet3MatchedTop->Fill(sortedSubjets.at(1).pt()/sortedSubjets.at(2).pt(), genweight);
        GenPTRatioSubjet1Subjet3MatchedTop->Fill(sortedSubjets.at(0).pt()/sortedSubjets.at(2).pt(), genweight);
      }
    }
    
    if(sortedSubjets_v4.size() == 3) {
      if(!(sortedSubjets_v4.at(0).M() == 0 || sortedSubjets_v4.at(1).M() == 0 || sortedSubjets_v4.at(2).M() == 0 || jet1_v4.M() == 0)) {
        GenMRatioSubjet1JetMatchedTop->Fill(sortedSubjets_v4.at(0).M()/jet1_v4.M(), genweight);
        GenMRatioSubjet2JetMatchedTop->Fill(sortedSubjets_v4.at(1).M()/jet1_v4.M(), genweight);
        GenMRatioSubjet3JetMatchedTop->Fill(sortedSubjets_v4.at(2).M()/jet1_v4.M(), genweight);
        GenMRatioQuarksJetMatchedTop->Fill((sortedSubjets_v4.at(0).M()+sortedSubjets_v4.at(1).M()+sortedSubjets_v4.at(2).M())/jet1_v4.M(), genweight);
        GenMRatioSubjet1Subjet2MatchedTop->Fill(sortedSubjets_v4.at(0).M()/sortedSubjets_v4.at(1).M(), genweight);
        GenMRatioSubjet2Subjet3MatchedTop->Fill(sortedSubjets_v4.at(1).M()/sortedSubjets_v4.at(2).M(), genweight);
        GenMRatioSubjet1Subjet3MatchedTop->Fill(sortedSubjets_v4.at(0).M()/sortedSubjets_v4.at(2).M(), genweight);
      }
    }
  }

  if(debug) cout << "\t--- top Hists done" << endl;

  if(gluonMatched) {
    GenJetMassMatchedGluon->Fill(jet1_v4.M(), genweight);

    if(sortedSubjets.size() == 3) {
      if(!(sortedSubjets.at(0).pt() == 0 || sortedSubjets.at(1).pt() == 0 || sortedSubjets.at(2).pt() == 0 || jet1.pt() == 0)) {
        GenPTRatioSubjet1JetMatchedGluon->Fill(sortedSubjets.at(0).pt()/jet1.pt(), genweight);
        GenPTRatioSubjet2JetMatchedGluon->Fill(sortedSubjets.at(1).pt()/jet1.pt(), genweight);
        GenPTRatioSubjet3JetMatchedGluon->Fill(sortedSubjets.at(2).pt()/jet1.pt(), genweight);
        GenPTRatioQuarksJetMatchedGluon->Fill((sortedSubjets.at(0).pt()+sortedSubjets.at(1).pt()+sortedSubjets.at(2).pt())/jet1.pt(), genweight);
        GenPTRatioSubjet1Subjet2MatchedGluon->Fill(sortedSubjets.at(0).pt()/sortedSubjets.at(1).pt(), genweight);
        GenPTRatioSubjet2Subjet3MatchedGluon->Fill(sortedSubjets.at(1).pt()/sortedSubjets.at(2).pt(), genweight);
        GenPTRatioSubjet1Subjet3MatchedGluon->Fill(sortedSubjets.at(0).pt()/sortedSubjets.at(2).pt(), genweight);
      }
    }

    if(sortedSubjets_v4.size() == 3) {
      if(!(sortedSubjets_v4.at(0).M() == 0 || sortedSubjets_v4.at(1).M() == 0 || sortedSubjets_v4.at(2).M() == 0 || jet1_v4.M() == 0)) {
        GenMRatioSubjet1JetMatchedGluon->Fill(sortedSubjets_v4.at(0).M()/jet1_v4.M(), genweight);
        GenMRatioSubjet2JetMatchedGluon->Fill(sortedSubjets_v4.at(1).M()/jet1_v4.M(), genweight);
        GenMRatioSubjet3JetMatchedGluon->Fill(sortedSubjets_v4.at(2).M()/jet1_v4.M(), genweight);
        GenMRatioQuarksJetMatchedGluon->Fill((sortedSubjets_v4.at(0).M()+sortedSubjets_v4.at(1).M()+sortedSubjets_v4.at(2).M())/jet1_v4.M(), genweight);
        GenMRatioSubjet1Subjet2MatchedGluon->Fill(sortedSubjets_v4.at(0).M()/sortedSubjets_v4.at(1).M(), genweight);
        GenMRatioSubjet2Subjet3MatchedGluon->Fill(sortedSubjets_v4.at(1).M()/sortedSubjets_v4.at(2).M(), genweight);
        GenMRatioSubjet1Subjet3MatchedGluon->Fill(sortedSubjets_v4.at(0).M()/sortedSubjets_v4.at(2).M(), genweight);
      }
    }
  }

  if(debug) cout << "\t--- gluonMatched Hists done" << endl;

  if(each_subjet_matching) {
    GenEachInOneSubjetMass->Fill(jet1_v4.M(), genweight);
    if(subjets.size() == 3) {
      if(!(botSubjet.pt() == 0 || q1Subjet.pt() == 0 || q2Subjet.pt() == 0 || jet1.pt() == 0)) {
        GenSubjetPTRatioQ1BotMatched->Fill(q1Subjet.pt()/botSubjet.pt(), genweight);
        GenSubjetPTRatioQ2BotMatched->Fill(q2Subjet.pt()/botSubjet.pt(), genweight);
        GenSubjetPTRatioQ12Matched->Fill(q1Subjet.pt()/q2Subjet.pt(), genweight);
        GenSubjetPTRatioBotQ1Matched->Fill(botSubjet.pt()/q1Subjet.pt(), genweight);
        GenSubjetPTRatioBotQ2Matched->Fill(botSubjet.pt()/q2Subjet.pt(), genweight);
        GenSubjetPTRatioQ21Matched->Fill(q2Subjet.pt()/q1Subjet.pt(), genweight);

        GenSubjetPTRatioQ1JetMatched->Fill(q1Subjet.pt()/jet1.pt(), genweight);
        GenSubjetPTRatioQ2JetMatched->Fill(q2Subjet.pt()/jet1.pt(), genweight);
        GenSubjetPTRatioBotJetMatched->Fill(botSubjet.pt()/jet1.pt(), genweight);
        GenSubjetPTRatioQuarksJetMatched->Fill((q1Subjet.pt()+q2Subjet.pt()+botSubjet.pt())/jet1.pt(), genweight);

        GenPTRatioSubjet1JetMatched->Fill(sortedSubjets.at(0).pt()/jet1.pt(), genweight);
        GenPTRatioSubjet2JetMatched->Fill(sortedSubjets.at(1).pt()/jet1.pt(), genweight);
        GenPTRatioSubjet3JetMatched->Fill(sortedSubjets.at(2).pt()/jet1.pt(), genweight);

      }
    }

    if(subjets_v4.size() == 3) {
      if(!(botSubjet_v4.M() == 0 || q1Subjet_v4.M() == 0 || q2Subjet_v4.M() == 0 || jet1_v4.M() == 0)) {
        GenSubjetMRatioQ1BotMatched->Fill(q1Subjet_v4.M()/botSubjet_v4.M(), genweight);
        GenSubjetMRatioQ2BotMatched->Fill(q2Subjet_v4.M()/botSubjet_v4.M(), genweight);
        GenSubjetMRatioQ12Matched->Fill(q1Subjet_v4.M()/q2Subjet_v4.M(), genweight);
        GenSubjetMRatioBotQ1Matched->Fill(botSubjet_v4.M()/q1Subjet_v4.M(), genweight);
        GenSubjetMRatioBotQ2Matched->Fill(botSubjet_v4.M()/q2Subjet_v4.M(), genweight);
        GenSubjetMRatioQ21Matched->Fill(q2Subjet_v4.M()/q1Subjet_v4.M(), genweight);

        GenSubjetMRatioQ1JetMatched->Fill(q1Subjet_v4.M()/jet1_v4.M(), genweight);
        GenSubjetMRatioQ2JetMatched->Fill(q2Subjet_v4.M()/jet1_v4.M(), genweight);
        GenSubjetMRatioBotJetMatched->Fill(botSubjet_v4.M()/jet1_v4.M(), genweight);
        GenSubjetMRatioQuarksJetMatched->Fill((q1Subjet_v4.M()+q2Subjet_v4.M()+botSubjet_v4.M())/jet1_v4.M(), genweight);

        GenMRatioSubjet1JetMatched->Fill(sortedSubjets_v4.at(0).M()/jet1_v4.M(), genweight);
        GenMRatioSubjet2JetMatched->Fill(sortedSubjets_v4.at(1).M()/jet1_v4.M(), genweight);
        GenMRatioSubjet3JetMatched->Fill(sortedSubjets_v4.at(2).M()/jet1_v4.M(), genweight);
      }
    }

    if(allPassed) {
      GenEachInOneSubjetMassAllInJet->Fill(jet1_v4.M(), genweight);
    }

    if(gluonInSubjet) {
      GenJetMassEachInOneSubjetAndGluonInSubjet->Fill(jet1_v4.M(), genweight);
    } else {
      GenJetMassEachInOneSubjetAndGluonNotInSubjet->Fill(jet1_v4.M(), genweight);
    }

    if(gluonInJet) {
      GenJetMassEachInOneSubjetAndGluonInJet->Fill(jet1_v4.M(), genweight);
    } else {
      GenJetMassEachInOneSubjetAndGluonNotInJet->Fill(jet1_v4.M(), genweight);
    }

  } else {

    GenJetMassUnmatched->Fill(jet1_v4.M(), genweight);

    if(sortedSubjets.size() == 3) {
      if(!(sortedSubjets.at(0).pt() == 0 || sortedSubjets.at(1).pt() == 0 || sortedSubjets.at(2).pt() == 0 || jet1.pt() == 0)) {
        GenPTRatioSubjet1JetUnmatched->Fill(sortedSubjets.at(0).pt()/jet1.pt(), genweight);
        GenPTRatioSubjet2JetUnmatched->Fill(sortedSubjets.at(1).pt()/jet1.pt(), genweight);
        GenPTRatioSubjet3JetUnmatched->Fill(sortedSubjets.at(2).pt()/jet1.pt(), genweight);
        GenPTRatioQuarksJetUnmatched->Fill((sortedSubjets.at(0).pt()+sortedSubjets.at(1).pt()+sortedSubjets.at(2).pt())/jet1.pt(), genweight);
      }
    }

    if(sortedSubjets_v4.size() == 3) {
      if(!(jet1_v4.M() == 0)) {
        GenMRatioSubjet1JetUnmatched->Fill(sortedSubjets_v4.at(0).M()/jet1_v4.M(), genweight);
        GenMRatioSubjet2JetUnmatched->Fill(sortedSubjets_v4.at(1).M()/jet1_v4.M(), genweight);
        GenMRatioSubjet3JetUnmatched->Fill(sortedSubjets_v4.at(2).M()/jet1_v4.M(), genweight);
        GenMRatioQuarksJetUnmatched->Fill((sortedSubjets_v4.at(0).M()+sortedSubjets_v4.at(1).M()+sortedSubjets_v4.at(2).M())/jet1_v4.M(), genweight);
      }
    }

    if(gluonInSubjet) {
      GenJetMassUnmatchedAndGluonInSubjet->Fill(jet1_v4.M(), genweight);
    } else {
      GenJetMassUnmatchedAndGluonNotInSubjet->Fill(jet1_v4.M(), genweight);
    }

    if(gluonInJet) {
      GenJetMassUnmatchedAndGluonInJet->Fill(jet1_v4.M(), genweight);
    } else {
      GenJetMassUnmatchedAndGluonNotInJet->Fill(jet1_v4.M(), genweight);
    }
    
    switch(remaining_quarks) {
      case 3:
        if(allPassed) GenNoneInOneSubjetMassAllInJet->Fill(jet1_v4.M(), genweight);
        GenNoneInOneSubjetMass->Fill(jet1_v4.M(), genweight);
        break;
      
      case 2:
        if(allPassed) GenOneInOneSubjetMassAllInJet->Fill(jet1_v4.M(), genweight);
        GenOneInOneSubjetMass->Fill(jet1_v4.M(), genweight);
        break;

      case 1:
        if(allPassed) GenTwoInOneSubjetMassAllInJet->Fill(jet1_v4.M(), genweight);
        GenTwoInOneSubjetMass->Fill(jet1_v4.M(), genweight);
        break;

      case 0:
        cout << "-- should not occur, but !each_subjet_matching && remaining_quarks == 0" << endl;
        break;

      default:
        cout << "-- should also not occur" << endl;
    }
  }

  if(any_subjet_matching) {
    GenAnySubjetMass->Fill(jet1_v4.M(), genweight);
    if(!each_subjet_matching) GenAnyButNotEachSubjetMass->Fill(jet1_v4.M(), genweight);
  }

  if(each_subjet_matching) {
    if(!gluonNearTop) GenJetMassGluonNotNearTopAndAllSubjetsMatched->Fill(jet1_v4.M(), genweight);
    else GenJetMassGluonNearTopAndAllSubjetsMatched->Fill(jet1_v4.M(), genweight);
  }
  
  
  GenJet botNearest, q1Nearest, q2Nearest;

  if(printOut) cout << remaining_quarks << " remaining quarks" << endl;
  if(printOut) cout << "dR_bot_subjets: ";
  int botNearestIndex = nearestSubjet(bot, subjets);
  if(botNearestIndex >= 0) botNearest = subjets.at(botNearestIndex);

  if(printOut) cout << "dR_q1_subjets: ";
  int q1NearestIndex = nearestSubjet(q1, subjets);
  if(q1NearestIndex >= 0) q1Nearest = subjets.at(q1NearestIndex);

  if(printOut) cout << "dR_q2_subjets: ";
  int q2NearestIndex = nearestSubjet(q2, subjets);
  if(q2NearestIndex >= 0) q2Nearest = subjets.at(q2NearestIndex);

  PTRatio_bot_subjet->Fill(bot.pt()/botNearest.pt(), genweight);
  PTRatio_q1_subjet->Fill(q1.pt()/q1Nearest.pt(), genweight);
  PTRatio_q2_subjet->Fill(q2.pt()/q2Nearest.pt(), genweight);

  bool anySameNearestSubjet = (botNearestIndex == q1NearestIndex) || (botNearestIndex == q2NearestIndex) || (q1NearestIndex == q2NearestIndex);
  if(anySameNearestSubjet) SameNearestSubjet->Fill(jet1_v4.M(), genweight);

  if(debug) cout << "\t\t---GenJetMass filled---" << endl;
    
    /*
  if((jets.size()) > 1){
    GenJet2Mass->Fill(jet2_v4.M(),weight);
    GenJet2LepMass->Fill(jet2_lep_v4.M(),weight);
    GenJet1PT->Fill(jet1_v4.Pt(),weight);
    GenJet2PT->Fill(jet2_v4.Pt(),weight);
    GenJet2Eta->Fill(jet2_v4.Eta(),weight);
    Mass1Mass2->Fill(jet1_v4.M() - jet2_lep_v4.M(), weight);
    GenJet1Jet2PT->Fill(jet1_v4.Pt() - jet2_v4.Pt(),weight);

  }

  */

  /*

  if((jets.size()) > 2){
    GenJet3PT->Fill(jets.at(2).pt(),weight);
  }
  if((jets.size()) > 3){
    GenJet4PT->Fill(jets.at(3).pt(),weight);
  }
  if((jets.size()) > 4){
    GenJet5PT->Fill(jets.at(4).pt(),weight);
  }

  */

  /*

  // pT of had. top
  GenParticle tophad = ttbargen.TopHad();
  double tophadpt = tophad.pt();
  TopHadPT->Fill(tophadpt, weight);

  // pT of lep. top
  GenParticle toplep = ttbargen.TopLep();
  double topleppt = toplep.pt();
  TopLepPT->Fill(topleppt, weight);

  // pT of bottoms
  BotHadPT->Fill(bot.pt(), weight);
  BotLepPT->Fill(bot_lep.pt(), weight);

  // delta R Hists
  if(jets.size() > 0){
    deltaR_lep1_jet1->Fill(deltaR(jet1, lep1), weight);
    deltaR_lep2_jet1->Fill(deltaR(jet1, lep2), weight);
    deltaR_botlep_jet1->Fill(deltaR(jet1, bot_lep), weight);
    deltaR_q1_jet1->Fill(deltaR(jet1, q1), weight);
    deltaR_q2_jet1->Fill(deltaR(jet1, q2), weight);
    deltaR_bot_jet1->Fill(deltaR(jet1, bot), weight);
    deltaR_tophad_jet1->Fill(deltaR(jet1, tophad), weight);
    deltaR_toplep_jet1->Fill(deltaR(jet1, toplep), weight);
    deltaPhi_lep1_jet1->Fill(abs(jet1.phi()-lep1.phi()), weight);
  }

  if(jets.size() > 1){
    deltaR_lep1_jet2->Fill(deltaR(jet2, lep1), weight);
    deltaR_lep2_jet2->Fill(deltaR(jet2, lep2), weight);
    deltaR_botlep_jet2->Fill(deltaR(jet2, bot_lep), weight);
    deltaR_q1_jet2->Fill(deltaR(jet2, q1), weight);
    deltaR_q2_jet2->Fill(deltaR(jet2, q2), weight);
    deltaR_bot_jet2->Fill(deltaR(jet2, bot), weight);
    deltaR_tophad_jet2->Fill(deltaR(jet2, tophad), weight);
    deltaR_toplep_jet2->Fill(deltaR(jet2, toplep), weight);
    deltaPhi_lep1_jet2->Fill(abs(jet2.phi()-lep1.phi()), weight);

  }

  dR_GenParts_q1_q2->Fill(deltaR(q1,q2), weight);
  dR_GenParts_bot_q1->Fill(deltaR(bot,q1), weight);
  dR_GenParts_bot_q2->Fill(deltaR(bot,q2), weight);

  dR_GenParts_q1_q2_toppt->Fill(tophadpt, deltaR(q1,q2), weight);
  dR_GenParts_bot_q1_toppt->Fill(tophadpt, deltaR(bot,q1), weight);
  dR_GenParts_bot_q2_toppt->Fill(tophadpt, deltaR(bot,q2), weight);

  double dR_high, dR_low;
  dR_low = deltaR(q1,q2);
  if(deltaR(bot,q1) < dR_low) dR_low = deltaR(bot,q1);
  if(deltaR(bot,q2) < dR_low) dR_low = deltaR(bot,q2);
  dR_high = deltaR(q1,q2);
  if(deltaR(bot,q1) > dR_high) dR_high = deltaR(bot,q1);
  if(deltaR(bot,q2) > dR_high) dR_high = deltaR(bot,q2);

  dR_GenParts_highest->Fill(dR_high, weight);
  dR_GenParts_lowest->Fill(dR_low, weight);
  dR_GenParts_highest_toppt->Fill(tophadpt, dR_high, weight);
  dR_GenParts_lowest_toppt->Fill(tophadpt, dR_low, weight);


  if(jets.size() > 0){
    Eta_Phi_jet1->Fill(jet1_v4.Eta(), jet1_v4.Phi(), weight);
    Eta_Phi_bot->Fill(bot.eta(), bot.phi(), weight);
    Eta_Phi_q1->Fill(q1.eta(), q1.phi(), weight);
    Eta_Phi_q2->Fill(q2.eta(), q2.phi(), weight);
  }
  // if(jets.size() > 2){
  //   deltaR_lep1_jet3->Fill(deltaR(jet3, lep1), weight);
  //   deltaR_lep2_jet3->Fill(deltaR(jet3, lep2), weight);
  //   deltaR_botlep_jet3->Fill(deltaR(jet3, bot_lep), weight);
  //   deltaR_q1_jet3->Fill(deltaR(jet3, q1), weight);
  //   deltaR_q2_jet3->Fill(deltaR(jet3, q2), weight);
  //   deltaR_bot_jet3->Fill(deltaR(jet3, bot), weight);
  //   deltaR_tophad_jet3->Fill(deltaR(jet3, tophad), weight);
  //   deltaR_toplep_jet3->Fill(deltaR(jet3, toplep), weight);
  // }

  // if(jets.size() > 3){
  //   deltaR_lep1_jet4->Fill(deltaR(jet4, lep1), weight);
  //   deltaR_lep2_jet4->Fill(deltaR(jet4, lep2), weight);
  //   deltaR_botlep_jet4->Fill(deltaR(jet4, bot_lep), weight);
  //   deltaR_q1_jet4->Fill(deltaR(jet4, q1), weight);
  //   deltaR_q2_jet4->Fill(deltaR(jet4, q2), weight);
  //   deltaR_bot_jet4->Fill(deltaR(jet4, bot), weight);
  //   deltaR_tophad_jet4->Fill(deltaR(jet4, tophad), weight);
  //   deltaR_toplep_jet4->Fill(deltaR(jet4, toplep), weight);
  // }

  // if(jets.size() > 4){
  //   deltaR_lep1_jet5->Fill(deltaR(jet5, lep1), weight);
  //   deltaR_lep2_jet5->Fill(deltaR(jet5, lep2), weight);
  //   deltaR_botlep_jet5->Fill(deltaR(jet5, bot_lep), weight);
  //   deltaR_q1_jet5->Fill(deltaR(jet5, q1), weight);
  //   deltaR_q2_jet5->Fill(deltaR(jet5, q2), weight);
  //   deltaR_bot_jet5->Fill(deltaR(jet5, bot), weight);
  //   deltaR_tophad_jet5->Fill(deltaR(jet5, tophad), weight);
  //   deltaR_toplep_jet5->Fill(deltaR(jet5, toplep), weight);
  // }

  // if(jets.size() > 5){
  //   deltaR_lep1_jet6->Fill(deltaR(jet6, lep1), weight);
  //   deltaR_lep2_jet6->Fill(deltaR(jet6, lep2), weight);
  //   deltaR_botlep_jet6->Fill(deltaR(jet6, bot_lep), weight);
  //   deltaR_q1_jet6->Fill(deltaR(jet6, q1), weight);
  //   deltaR_q2_jet6->Fill(deltaR(jet6, q2), weight);
  //   deltaR_bot_jet6->Fill(deltaR(jet6, bot), weight);
  //   deltaR_tophad_jet6->Fill(deltaR(jet6, tophad), weight);
  //   deltaR_toplep_jet6->Fill(deltaR(jet6, toplep), weight);
  // }
  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------

  */
  }
  //---------------------------------------------------------------------------------------
  //--------------------------------- Clear all used objects ------------------------------
  //---------------------------------------------------------------------------------------
  if(debug) cout << "\t--- Clear all used objects" << endl;
  jet1_v4.Delete();
  lepton1_v4.Delete();
  jet2_lep_v4.Delete();
  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------

}
