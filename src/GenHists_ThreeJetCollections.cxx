#include <UHH2/MTopJet/include/GenHists_ThreeJetCollections.h>

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
const int n_massbins = 50;

bool printOut2 = false;

GenHists_ThreeJetCollections::GenHists_ThreeJetCollections(uhh2::Context & ctx, const std::string & dirname, const std::string & topJetName, const std::string & gluonJetName, const std::string & lepJetName): Hists(ctx, dirname){
  // book all histograms here
  /*GenJetMass = book<TH1F>("M_jet_Mass", "M_{jet}", n_massbins, 0, max_m);

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

  GenJet1MassAll = book<TH1F>("M_jet1_MassAll", "M_{jet}", n_massbins, 0, max_m);
  GenJet1MassNotAll = book<TH1F>("M_jet1_MassNotAll", "M_{jet}", n_massbins, 0, max_m);

  GenJet1MassBot = book<TH1F>("M_jet1_MassBot", "M_{jet}", n_massbins, 0, max_m);

  GenJet1MassTwoLightQ = book<TH1F>("M_jet1_MassTwoLightQ", "M_{jet}", n_massbins, 0, max_m);

  GenJet1MassBotOneLightQ = book<TH1F>("M_jet1_MassBotOneLightQ", "M_{jet}", n_massbins, 0, max_m);

  GenJet1MassOneQ = book<TH1F>("M_jet1_MassOneQ", "M_{jet}", n_massbins, 0, max_m);

  GenJet1MassNoQ = book<TH1F>("M_jet1_MassNoQ", "M_{jet}", n_massbins, 0, max_m);

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

  GenJet1MassRest = book<TH1F>("M_jet1_MassRest", "M_{jet}", n_massbins, 0, max_m);
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

  STGenTopJetPT = book<TH1F>("st_topJet_PT", "p_{T}^{st_top}", 50, 0, 1000);
  STGenGluonJetPT = book<TH1F>("st_gluonJet_PT", "p_{T}^{st_gluon}", 50, 0, 1000);
  STGenLepJetPT = book<TH1F>("st_lepJet_PT", "p_{T}^{st_lep}", 50, 0, 1000);
  STGenTopJetMSmallPT = book<TH1F>("st_topJet_M_smallPt", "M_{jet}^{st_top_smallPt}", 50, 0, 1000);
  STGenTopJetMSmallPTCombined = book<TH1F>("st_topJet_M_smallPt_Combined", "M_{jet_combined}^{st_top_smallPt}", 50, 0, 1000);

  STGenTopJetM = book<TH1F>("st_topJet_M", "M_{jet}^{st_top}", n_massbins, 0, max_m);
  STGenGluonJetM = book<TH1F>("st_gluonJet_M", "M_{jet}^{st_gluon}", n_massbins, 0, max_m);
  STGenLepJetM = book<TH1F>("st_lepJet_M", "M_{jet}^{st_lep}", n_massbins, 0, max_m);

  STGenTopJetTau1 = book<TH1F>("st_topJet_tau1", "tau1^{st_top}", 50, 0, 1);
  STGenTopJetTau2 = book<TH1F>("st_topJet_tau2", "tau2^{st_top}", 50, 0, 1);
  STGenTopJetTau3 = book<TH1F>("st_topJet_tau3", "tau3^{st_top}", 50, 0, 1);
  STGenTopJetTau4 = book<TH1F>("st_topJet_tau4", "tau4^{st_top}", 50, 0, 1);

  STGenGluonJetTau1 = book<TH1F>("st_gluonJet_tau1", "tau1^{st_gluon}", 50, 0, 1);
  STGenGluonJetTau2 = book<TH1F>("st_gluonJet_tau2", "tau2^{st_gluon}", 50, 0, 1);
  STGenGluonJetTau3 = book<TH1F>("st_gluonJet_tau3", "tau3^{st_gluon}", 50, 0, 1);
  STGenGluonJetTau4 = book<TH1F>("st_gluonJet_tau4", "tau4^{st_gluon}", 50, 0, 1);

  STGenLepJetTau1 = book<TH1F>("st_lepJet_tau1", "tau1^{st_lep}", 50, 0, 1);
  STGenLepJetTau2 = book<TH1F>("st_lepJet_tau2", "tau2^{st_lep}", 50, 0, 1);
  STGenLepJetTau3 = book<TH1F>("st_lepJet_tau3", "tau3^{st_lep}", 50, 0, 1);
  STGenLepJetTau4 = book<TH1F>("st_lepJet_tau4", "tau4^{st_lep}", 50, 0, 1);

  STGenTopJetTau3Tau2 = book<TH1F>("st_topJet_tau3tau2", "(tau3/tau2)^{st_top}", 50, 0, 1);
  STGenTopJetTau4Tau3 = book<TH1F>("st_topJet_tau4tau3", "(tau4/tau3)^{st_top}", 50, 0, 1);
  STGenTopJetTau4Tau2 = book<TH1F>("st_topJet_tau4tau2", "(tau4/tau2)^{st_top}", 50, 0, 1);

  STGenGluonJetTau3Tau2 = book<TH1F>("st_gluonJet_tau3tau2", "(tau3/tau2)^{st_gluon}", 50, 0, 1);
  STGenGluonJetTau4Tau3 = book<TH1F>("st_gluonJet_tau4tau3", "(tau4/tau3)^{st_gluon}", 50, 0, 1);
  STGenGluonJetTau4Tau2 = book<TH1F>("st_gluonJet_tau4tau2", "(tau4/tau2)^{st_gluon}", 50, 0, 1);

  STGenLepJetTau3Tau2 = book<TH1F>("st_lepJet_tau3tau2", "(tau3/tau2)^{st_lep}", 50, 0, 1);
  STGenLepJetTau4Tau3 = book<TH1F>("st_lepJet_tau4tau3", "(tau4/tau3)^{st_lep}", 50, 0, 1);
  STGenLepJetTau4Tau2 = book<TH1F>("st_lepJet_tau4tau2", "(tau4/tau2)^{st_lep}", 50, 0, 1);

  STGenDeltaRTopGluon = book<TH1F>("st_deltaRTopGluon", "st_DeltaR(topJet,gluonJet)", 80, 0, 4.0);
  STGenDeltaRTopLep = book<TH1F>("st_deltaRTopLep", "st_DeltaR(topJet,lepJet)", 80, 0, 4.0);
  STGenDeltaRGluonLep = book<TH1F>("st_deltaRGluonLep", "st_DeltaR(gluonJet,lepJet)", 80, 0, 4.0);

  STGenTopSubjetM1M2 = book<TH1F>("st_topSubjetM1M2", "(M_{subjet1}/M_{subjet2})_{st_top}", 50, 0, 1);
  STGenTopSubjetM2M3 = book<TH1F>("st_topSubjetM2M3", "(M_{subjet2}/M_{subjet3})_{st_top}", 50, 0, 1);
  STGenTopSubjetM1M3 = book<TH1F>("st_topSubjetM1M3", "(M_{subjet1}/M_{subjet3})_{st_top}", 50, 0, 1);

  STGenGluonSubjetM1M2 = book<TH1F>("st_gluonSubjetM1M2", "(M_{subjet1}/M_{subjet2})_{st_gluon}", 50, 0, 1);
  STGenGluonSubjetM2M3 = book<TH1F>("st_gluonSubjetM2M3", "(M_{subjet2}/M_{subjet3})_{st_gluon}", 50, 0, 1);
  STGenGluonSubjetM1M3 = book<TH1F>("st_gluonSubjetM1M3", "(M_{subjet1}/M_{subjet3})_{st_gluon}", 50, 0, 1);

  STGenGluonSubjetM1 = book<TH1F>("st_gluonSubjet_M1", "M_{subjet1}^{st_gluon}", 50, 0, 400);
  STGenGluonSubjetM2 = book<TH1F>("st_gluonSubjet_M2", "M_{subjet2}^{st_gluon}", 50, 0, 400);
  STGenGluonSubjetM3 = book<TH1F>("st_gluonSubjet_M3", "M_{subjet3}^{st_gluon}", 50, 0, 400);

  STGenGluonSubjetPt1 = book<TH1F>("st_gluonSubjet_Pt1", "p_{T}^{st_gluonSubjet1}", 50, 0, 400);
  STGenGluonSubjetPt2 = book<TH1F>("st_gluonSubjet_Pt2", "p_{T}^{st_gluonSubjet2}", 50, 0, 400);
  STGenGluonSubjetPt3 = book<TH1F>("st_gluonSubjet_Pt3", "p_{T}^{st_gluonSubjet3}", 50, 0, 400);

  STGenTopJetM_EachSubjetMatched = book<TH1F>("st_topJet_M_EachSubjetMatched", "M_{jet}^{st_top_eachSubjetMatched}", n_massbins, 0, max_m);

  GenTopJetNumber = book<TH1F>("topJetNumber", "topJets.size()", 50, 0, 4);
  GenGluonJetNumber = book<TH1F>("gluonJetNumber", "gluonJets.size()", 50, 0, 4);
  GenLepJetNumber = book<TH1F>("lepJetNumber", "lepJets.size()", 50, 0, 4);

  GenDeltaRLepJetTop = book<TH1F>("deltaRLepJetTop", "DeltaR(lepJet,top)", 80, 0, 4.0);

  DTGenTopJetPT = book<TH1F>("dt_topJet_PT", "p_{T}^{dt_top}", 50, 0, 1000);
  DTGenLepJetPT = book<TH1F>("dt_lepJet_PT", "p_{T}^{dt_lep}", 50, 0, 1000);

  DTGenTopJetM = book<TH1F>("dt_topJet_M", "M_{jet}^{dt_top}", n_massbins, 0, max_m);
  DTGenLepJetM = book<TH1F>("dt_lepJet_M", "M_{jet}^{dt_lep}", n_massbins, 0, max_m);

  DTGenTopJetPtCombined = book<TH1F>("dt_topJet_PT_combined", "p_{T}^{dt_top_combined}", 50, 0, 1000);
  DTGenTopJetMCombined = book<TH1F>("dt_topJet_M_combined", "M_{jet_combined}^{dt_top}", n_massbins, 0, max_m);

  DTGenTopJetTau1 = book<TH1F>("dt_topJet_tau1", "tau1^{dt_top}", 50, 0, 1);
  DTGenTopJetTau2 = book<TH1F>("dt_topJet_tau2", "tau2^{dt_top}", 50, 0, 1);
  DTGenTopJetTau3 = book<TH1F>("dt_topJet_tau3", "tau3^{dt_top}", 50, 0, 1);
  DTGenTopJetTau4 = book<TH1F>("dt_topJet_tau4", "tau4^{dt_top}", 50, 0, 1);

  DTGenLepJetTau1 = book<TH1F>("dt_lepJet_tau1", "tau1^{dt_lep}", 50, 0, 1);
  DTGenLepJetTau2 = book<TH1F>("dt_lepJet_tau2", "tau2^{dt_lep}", 50, 0, 1);
  DTGenLepJetTau3 = book<TH1F>("dt_lepJet_tau3", "tau3^{dt_lep}", 50, 0, 1);
  DTGenLepJetTau4 = book<TH1F>("dt_lepJet_tau4", "tau4^{dt_lep}", 50, 0, 1);

  DTGenTopJetTau3Tau2 = book<TH1F>("dt_topJet_tau3tau2", "(tau3/tau2)^{dt_top}", 50, 0, 1);
  DTGenTopJetTau4Tau3 = book<TH1F>("dt_topJet_tau4tau3", "(tau4/tau3)^{dt_top}", 50, 0, 1);
  DTGenTopJetTau4Tau2 = book<TH1F>("dt_topJet_tau4tau2", "(tau4/tau2)^{dt_top}", 50, 0, 1);

  DTGenLepJetTau3Tau2 = book<TH1F>("dt_lepJet_tau3tau2", "(tau3/tau2)^{dt_lep}", 50, 0, 1);
  DTGenLepJetTau4Tau3 = book<TH1F>("dt_lepJet_tau4tau3", "(tau4/tau3)^{dt_lep}", 50, 0, 1);
  DTGenLepJetTau4Tau2 = book<TH1F>("dt_lepJet_tau4tau2", "(tau4/tau2)^{dt_lep}", 50, 0, 1);

  DTGenDeltaRTopTop = book<TH1F>("dt_deltaRTopTop", "dt_DeltaR(topJet1,topJet2)", 80, 0, 4.0);
  DTGenDeltaRTopLep = book<TH1F>("dt_deltaRTopLep", "dt_DeltaR(topJet,lepJet)", 80, 0, 4.0);

  DTGenTopSubjetM1M2 = book<TH1F>("dt_topSubjetM1M2", "(M_{subjet1}/M_{subjet2})_{dt_top}", 50, 0, 1);
  DTGenTopSubjetM2M3 = book<TH1F>("dt_topSubjetM2M3", "(M_{subjet2}/M_{subjet3})_{dt_top}", 50, 0, 1);
  DTGenTopSubjetM1M3 = book<TH1F>("dt_topSubjetM1M3", "(M_{subjet1}/M_{subjet3})_{dt_top}", 50, 0, 1);

  DTGenTopJetM_EachQuarkMatched = book<TH1F>("dt_topJet_M_EachQuarkMatched", "M_{jet}^{dt_top_eachQuarkMatched}", n_massbins, 0, max_m);

  // handle for TTbarGen class
  h_ttbargen=ctx.get_handle<TTbarGen>("ttbargen");
  // handle for clustered jets
  h_topJets=ctx.get_handle<std::vector<GenTopJet>>(topJetName);
  h_gluonJets=ctx.get_handle<std::vector<GenTopJet>>(gluonJetName);
  h_lepJets=ctx.get_handle<std::vector<GenTopJet>>(lepJetName);

  debug = string2bool(ctx.get("Debug","false"));
}
/*
void createSubjetQuarkDeltaRMatrix(std::vector<GenJet> subjets, std::vector<GenParticle> quarks, std::vector<std::vector<double>>* matrix) {
  unsigned int nSubjets = subjets.size();
  unsigned int nQuarks = quarks.size();

  for(unsigned int i=0; i<nSubjets; i++) {
    for(unsigned int j=0; j<nQuarks; j++) {
      matrix->at(i).at(j) = deltaR(subjets.at(i), quarks.at(j));
    }
  }
}
*/
float deltaRNearestSubjet(GenParticle q, std::vector<GenJet> subjets) {
  float minR = 100;

  for(unsigned int i=0; i<subjets.size(); i++) {
    float tmpR = deltaR(q, subjets.at(i));
    if(printOut2) cout << tmpR << ", ";
    if(tmpR < minR) {
      minR = tmpR;
    }
  }
  if(printOut2) cout << endl;

  return minR;
}

bool subjetMatching(std::vector<GenJet> subjets, std::vector<GenParticle> quarks, unsigned int* remaining_quarks, bool unique, std::vector<int>* subjetIndices) {
  
  bool matched = true;
  for(unsigned int i=0; i<subjets.size(); i++) {

    double minR = 100;
    int j_remove = -1;

    if(printOut2) cout << "subjet " << i << ": ";

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

    if(printOut2) cout << "minR = " << minR << ", j_remove = " << j_remove << endl;

  }

  if(remaining_quarks != nullptr) {
    *remaining_quarks = quarks.size();

    if(printOut2) cout << ", remaining quarks = " << *remaining_quarks << endl;
  }
  return matched;
}
/*
//"gluons" might not be exclusively gluons
const GenParticle* gluonInEvent(const Event & event) {
  std::vector<GenParticle> *genparticles = event.genparticles;
  int nparts = genparticles->size();
  
  const GenParticle* gluon = nullptr;
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
*/

void GenHists_ThreeJetCollections::fill(const Event & event){

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
  std::vector<GenTopJet> topJets = event.get(h_topJets);
  std::vector<GenTopJet> gluonJets = event.get(h_gluonJets);
  std::vector<GenTopJet> lepJets = event.get(h_lepJets);
  std::vector<TLorentzVector> topJet_v4, gluonJet_v4, lepJet_v4;
  TLorentzVector topJet_v4_combined;
  TLorentzVector jet1_v4, jeti_v4, botSubjet_v4, q1Subjet_v4, q2Subjet_v4;
  std::vector<std::vector<TLorentzVector>> topSubjets_v4 = {};
  std::vector<std::vector<TLorentzVector>> gluonSubjets_v4 = {};
  std::vector<TLorentzVector> sortedSubjets_v4 = {};
  std::vector<TLorentzVector> jets_v4;

  TLorentzVector lepton1_v4, jet2_lep_v4, topjet1_v4, topjet2_v4;
  std::vector<GenJet> subjets, sortedSubjets;

  GenParticle bot, q1, q2, bot_lep, lep1, lep2, lepton, top, antitop;

  TLorentzVector tmp;
  std::vector<TLorentzVector> tmpSubjets;

  for(uint i=0; i<topJets.size(); i++) {
    tmp.SetPxPyPzE(topJets.at(i).v4().Px(), topJets.at(i).v4().Py(), topJets.at(i).v4().Pz(), topJets.at(i).v4().E());
    topJet_v4.push_back(tmp);
    for(uint j=0; j<topJets.at(i).subjets().size(); j++) {
      tmp.SetPxPyPzE(topJets.at(i).subjets().at(j).v4().Px(), topJets.at(i).subjets().at(j).v4().Py(), topJets.at(i).subjets().at(j).v4().Pz(), topJets.at(i).subjets().at(j).v4().E());
      tmpSubjets.push_back(tmp);
    }
    topSubjets_v4.push_back(tmpSubjets);
  }

  tmpSubjets = {};
  for(uint i=0; i<gluonJets.size(); i++) {
    tmp.SetPxPyPzE(gluonJets.at(i).v4().Px(), gluonJets.at(i).v4().Py(), gluonJets.at(i).v4().Pz(), gluonJets.at(i).v4().E());
    gluonJet_v4.push_back(tmp);
    for(uint j=0; j<gluonJets.at(i).subjets().size(); j++) {
      tmp.SetPxPyPzE(gluonJets.at(i).subjets().at(j).v4().Px(), gluonJets.at(i).subjets().at(j).v4().Py(), gluonJets.at(i).subjets().at(j).v4().Pz(), gluonJets.at(i).subjets().at(j).v4().E());
      tmpSubjets.push_back(tmp);
    }
    gluonSubjets_v4.push_back(tmpSubjets);
  }

  for(uint i=0; i<lepJets.size(); i++) {
    tmp.SetPxPyPzE(lepJets.at(i).v4().Px(), lepJets.at(i).v4().Py(), lepJets.at(i).v4().Pz(), lepJets.at(i).v4().E());
    lepJet_v4.push_back(tmp);
  }

  bool isTTBar = true;

  // get stable particles from ttbar decay and sort them into leptonic and hadronic
    
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

  std::vector<GenParticle> quarks = {bot, q1, q2};

  double genweight = event.weight;

  GenTopJetNumber->Fill(topJets.size(), genweight);
  GenGluonJetNumber->Fill(gluonJets.size(), genweight);
  GenLepJetNumber->Fill(lepJets.size(), genweight);

  if(lepJets.size() > 0) {
    GenDeltaRLepJetTop->Fill(deltaR(lepJets.at(0), top), genweight);
  }

  //---------------------------------------------------------------------------------------
  //------------------------ all three jets exist -----------------------------------------
  //---------------------------------------------------------------------------------------

  if(debug) cout << "\t--- single top jet" << endl;

  if(topJets.size() == 1 && gluonJets.size() == 1 && lepJets.size() == 1) {

    if(debug) cout << "\t\t--- set jets_v4" << endl;

    //---------------------------------------------------------------------------------------
    //--------------------------------- fill first Hists ------------------------------------
    //---------------------------------------------------------------------------------------

    topJet_v4_combined = topJet_v4.at(0) + gluonJet_v4.at(0);

    STGenTopJetPT->Fill(topJet_v4.at(0).Pt(), genweight);
    STGenGluonJetPT->Fill(gluonJet_v4.at(0).Pt(), genweight);
    STGenLepJetPT->Fill(lepJet_v4.at(0).Pt(), genweight);

    STGenTopJetM->Fill(topJet_v4.at(0).M(), genweight);
    STGenGluonJetM->Fill(gluonJet_v4.at(0).M(), genweight);
    STGenLepJetM->Fill(lepJet_v4.at(0).M(), genweight);

    if(topJet_v4.at(0).Pt() < 400) {
      STGenTopJetMSmallPT->Fill(topJet_v4.at(0).M(), genweight);
      STGenTopJetMSmallPTCombined->Fill(topJet_v4_combined.M(), genweight);
    }

    STGenTopJetTau1->Fill(topJets.at(0).tau1(), genweight);
    STGenTopJetTau2->Fill(topJets.at(0).tau2(), genweight);
    STGenTopJetTau3->Fill(topJets.at(0).tau3(), genweight);
    STGenTopJetTau4->Fill(topJets.at(0).tau4(), genweight);

    if(debug) cout << "\t\t--- top tau ratios" << endl;
    
    if(topJets.at(0).tau2() != 0) STGenTopJetTau3Tau2->Fill(topJets.at(0).tau3()/topJets.at(0).tau2(), genweight);
    if(topJets.at(0).tau3() != 0) STGenTopJetTau4Tau3->Fill(topJets.at(0).tau4()/topJets.at(0).tau3(), genweight);
    if(topJets.at(0).tau2() != 0) STGenTopJetTau4Tau2->Fill(topJets.at(0).tau4()/topJets.at(0).tau2(), genweight);

    STGenGluonJetTau1->Fill(gluonJets.at(0).tau1(), genweight);
    STGenGluonJetTau2->Fill(gluonJets.at(0).tau2(), genweight);
    STGenGluonJetTau3->Fill(gluonJets.at(0).tau3(), genweight);
    STGenGluonJetTau4->Fill(gluonJets.at(0).tau4(), genweight);

    if(debug) cout << "\t\t--- gluon tau ratios" << endl;

    if(gluonJets.at(0).tau2() != 0) STGenGluonJetTau3Tau2->Fill(gluonJets.at(0).tau3()/gluonJets.at(0).tau2(), genweight);
    if(gluonJets.at(0).tau3() != 0) STGenGluonJetTau4Tau3->Fill(gluonJets.at(0).tau4()/gluonJets.at(0).tau3(), genweight);
    if(gluonJets.at(0).tau2() != 0) STGenGluonJetTau4Tau2->Fill(gluonJets.at(0).tau4()/gluonJets.at(0).tau2(), genweight);

    STGenLepJetTau1->Fill(lepJets.at(0).tau1(), genweight);
    STGenLepJetTau2->Fill(lepJets.at(0).tau2(), genweight);
    STGenLepJetTau3->Fill(lepJets.at(0).tau3(), genweight);
    STGenLepJetTau4->Fill(lepJets.at(0).tau4(), genweight);

    if(debug) cout << "\t\t--- lep tau ratios" << endl;

    if(lepJets.at(0).tau2() != 0) STGenLepJetTau3Tau2->Fill(lepJets.at(0).tau3()/lepJets.at(0).tau2(), genweight);
    if(lepJets.at(0).tau3() != 0) STGenLepJetTau4Tau3->Fill(lepJets.at(0).tau4()/lepJets.at(0).tau3(), genweight);
    if(lepJets.at(0).tau2() != 0) STGenLepJetTau4Tau2->Fill(lepJets.at(0).tau4()/lepJets.at(0).tau2(), genweight);

    STGenDeltaRTopGluon->Fill(deltaR(topJets.at(0), gluonJets.at(0)), genweight);
    STGenDeltaRTopLep->Fill(deltaR(topJets.at(0), lepJets.at(0)), genweight);
    STGenDeltaRGluonLep->Fill(deltaR(gluonJets.at(0), lepJets.at(0)), genweight);

    if(debug) cout << "\t\t--- top subjet M ratios" << endl;

    if(topSubjets_v4.at(0).size() == 3) {
      if(topSubjets_v4.at(0).at(1).M() != 0) STGenTopSubjetM1M2->Fill(topSubjets_v4.at(0).at(0).M()/topSubjets_v4.at(0).at(1).M(), genweight);
      if(topSubjets_v4.at(0).at(2).M() != 0) STGenTopSubjetM2M3->Fill(topSubjets_v4.at(0).at(1).M()/topSubjets_v4.at(0).at(2).M(), genweight);
      if(topSubjets_v4.at(0).at(2).M() != 0) STGenTopSubjetM1M3->Fill(topSubjets_v4.at(0).at(0).M()/topSubjets_v4.at(0).at(2).M(), genweight);
    }

    if(debug) cout << "\t\t--- gluon subjet M ratios" << endl;

    if(gluonSubjets_v4.at(0).size() == 3) {
      if(gluonSubjets_v4.at(0).at(1).M() != 0) STGenGluonSubjetM1M2->Fill(gluonSubjets_v4.at(0).at(0).M()/gluonSubjets_v4.at(0).at(1).M(), genweight);
      if(gluonSubjets_v4.at(0).at(2).M() != 0) STGenGluonSubjetM2M3->Fill(gluonSubjets_v4.at(0).at(1).M()/gluonSubjets_v4.at(0).at(2).M(), genweight);
      if(gluonSubjets_v4.at(0).at(2).M() != 0) STGenGluonSubjetM1M3->Fill(gluonSubjets_v4.at(0).at(0).M()/gluonSubjets_v4.at(0).at(2).M(), genweight);

      if(debug) cout << "\t\t--- gluon subjet M and Pt" << endl;

      STGenGluonSubjetM1->Fill(gluonSubjets_v4.at(0).at(0).M(), genweight);
      STGenGluonSubjetM2->Fill(gluonSubjets_v4.at(0).at(1).M(), genweight);
      STGenGluonSubjetM3->Fill(gluonSubjets_v4.at(0).at(2).M(), genweight);

      STGenGluonSubjetPt1->Fill(gluonSubjets_v4.at(0).at(0).Pt(), genweight);
      STGenGluonSubjetPt2->Fill(gluonSubjets_v4.at(0).at(1).Pt(), genweight);
      STGenGluonSubjetPt3->Fill(gluonSubjets_v4.at(0).at(2).Pt(), genweight);

      /*if(gluonJet_v4.at(0).Pt() == 0) {
        TLorentzVector gluonJet_v4_recombined = gluonSubjets_v4.at(0).at(1) + gluonSubjets_v4.at(0).at(2) + gluonSubjets_v4.at(0).at(2);
        cout << "!!! Pt_gluon == 0:" << endl;
        cout << "subjet1.M()     " << gluonSubjets_v4.at(0).at(0).M() << endl;
        cout << "subjet2.M()     " << gluonSubjets_v4.at(0).at(1).M() << endl;
        cout << "subjet3.M()     " << gluonSubjets_v4.at(0).at(2).M() << endl;
        cout << "recombined.M()  " << gluonJet_v4_recombined.M() << endl;
        cout << "subjet1.Pt()    " << gluonSubjets_v4.at(0).at(0).Pt() << endl;
        cout << "subjet2.Pt()    " << gluonSubjets_v4.at(0).at(1).Pt() << endl;
        cout << "subjet3.Pt()    " << gluonSubjets_v4.at(0).at(2).Pt() << endl;
        cout << "recombined.Pt() " << gluonJet_v4_recombined.Pt() << endl;
      }*/
    }

    

    //---------------------------------------------------------------------------------------
    //--------------------------------- Matching --------------------------------------------
    //---------------------------------------------------------------------------------------
    if(debug) cout << "\t--- Matching" << endl;

    bool each_subjet_matching = subjetMatching(topJets.at(0).subjets(), quarks, nullptr, true, nullptr);

    if(each_subjet_matching) STGenTopJetM_EachSubjetMatched->Fill(topJet_v4.at(0).M(), genweight);

  } else if(topJets.size() == 2 && lepJets.size() == 1) {
    
    if(debug) cout << "\t--- double top jet" << endl;

    topJet_v4_combined = topJet_v4.at(0) + topJet_v4.at(1);

    DTGenTopJetPT->Fill(topJet_v4.at(0).Pt(), genweight);
    DTGenTopJetPT->Fill(topJet_v4.at(1).Pt(), genweight);
    DTGenLepJetPT->Fill(lepJet_v4.at(0).Pt(), genweight);

    DTGenTopJetM->Fill(topJet_v4.at(0).M(), genweight);
    DTGenTopJetM->Fill(topJet_v4.at(1).M(), genweight);
    DTGenLepJetM->Fill(lepJet_v4.at(0).M(), genweight);

    DTGenTopJetPtCombined->Fill(topJet_v4_combined.Pt(), genweight);
    DTGenTopJetMCombined->Fill(topJet_v4_combined.M(), genweight);

    DTGenTopJetTau1->Fill(topJets.at(0).tau1(), genweight);
    DTGenTopJetTau2->Fill(topJets.at(0).tau2(), genweight);
    DTGenTopJetTau3->Fill(topJets.at(0).tau3(), genweight);
    DTGenTopJetTau4->Fill(topJets.at(0).tau4(), genweight);

    if(debug) cout << "\t\t--- top tau ratios" << endl;

    if(topJets.at(0).tau2() != 0) DTGenTopJetTau3Tau2->Fill(topJets.at(0).tau3()/topJets.at(0).tau2(), genweight);
    if(topJets.at(0).tau3() != 0) DTGenTopJetTau4Tau3->Fill(topJets.at(0).tau4()/topJets.at(0).tau3(), genweight);
    if(topJets.at(0).tau2() != 0) DTGenTopJetTau4Tau2->Fill(topJets.at(0).tau4()/topJets.at(0).tau2(), genweight);

    DTGenTopJetTau1->Fill(topJets.at(1).tau1(), genweight);
    DTGenTopJetTau2->Fill(topJets.at(1).tau2(), genweight);
    DTGenTopJetTau3->Fill(topJets.at(1).tau3(), genweight);
    DTGenTopJetTau4->Fill(topJets.at(1).tau4(), genweight);

    if(topJets.at(1).tau2() != 0) DTGenTopJetTau3Tau2->Fill(topJets.at(1).tau3()/topJets.at(1).tau2(), genweight);
    if(topJets.at(1).tau3() != 0) DTGenTopJetTau4Tau3->Fill(topJets.at(1).tau4()/topJets.at(1).tau3(), genweight);
    if(topJets.at(1).tau2() != 0) DTGenTopJetTau4Tau2->Fill(topJets.at(1).tau4()/topJets.at(1).tau2(), genweight);

    DTGenLepJetTau1->Fill(lepJets.at(0).tau1(), genweight);
    DTGenLepJetTau2->Fill(lepJets.at(0).tau2(), genweight);
    DTGenLepJetTau3->Fill(lepJets.at(0).tau3(), genweight);
    DTGenLepJetTau4->Fill(lepJets.at(0).tau4(), genweight);

    if(debug) cout << "\t\t--- lep tau ratios" << endl;

    if(lepJets.at(0).tau2() != 0) STGenLepJetTau3Tau2->Fill(lepJets.at(0).tau3()/lepJets.at(0).tau2(), genweight);
    if(lepJets.at(0).tau3() != 0) STGenLepJetTau4Tau3->Fill(lepJets.at(0).tau4()/lepJets.at(0).tau3(), genweight);
    if(lepJets.at(0).tau2() != 0) STGenLepJetTau4Tau2->Fill(lepJets.at(0).tau4()/lepJets.at(0).tau2(), genweight);

    DTGenDeltaRTopTop->Fill(deltaR(topJets.at(0), topJets.at(1)), genweight);
    DTGenDeltaRTopLep->Fill(deltaR(topJets.at(0), lepJets.at(0)), genweight);
    DTGenDeltaRTopLep->Fill(deltaR(topJets.at(1), lepJets.at(0)), genweight);

    if(debug) cout << "\t\t--- top subjet M ratios" << endl;
    if(topSubjets_v4.at(0).size() == 3) {
      if(topSubjets_v4.at(0).at(1).M() != 0) DTGenTopSubjetM1M2->Fill(topSubjets_v4.at(0).at(0).M()/topSubjets_v4.at(0).at(1).M(), genweight);
      if(topSubjets_v4.at(0).at(2).M() != 0) DTGenTopSubjetM2M3->Fill(topSubjets_v4.at(0).at(1).M()/topSubjets_v4.at(0).at(2).M(), genweight);
      if(topSubjets_v4.at(0).at(2).M() != 0) DTGenTopSubjetM1M3->Fill(topSubjets_v4.at(0).at(0).M()/topSubjets_v4.at(0).at(2).M(), genweight);
    }

    if(topSubjets_v4.at(1).size() == 3) {
      if(topSubjets_v4.at(1).at(1).M() != 0) DTGenTopSubjetM1M2->Fill(topSubjets_v4.at(1).at(0).M()/topSubjets_v4.at(1).at(1).M(), genweight);
      if(topSubjets_v4.at(1).at(2).M() != 0) DTGenTopSubjetM2M3->Fill(topSubjets_v4.at(1).at(1).M()/topSubjets_v4.at(1).at(2).M(), genweight);
      if(topSubjets_v4.at(1).at(2).M() != 0) DTGenTopSubjetM1M3->Fill(topSubjets_v4.at(1).at(0).M()/topSubjets_v4.at(1).at(2).M(), genweight);
    }

    bool botPassed1 = deltaR(bot, topJets.at(0)) < jetradius;
    bool botPassed2 = deltaR(bot, topJets.at(1)) < jetradius;
    bool q1Passed1 = deltaR(q1, topJets.at(0)) < jetradius;
    bool q1Passed2 = deltaR(q1, topJets.at(1)) < jetradius;
    bool q2Passed1 = deltaR(q2, topJets.at(0)) < jetradius;
    bool q2Passed2 = deltaR(q2, topJets.at(1)) < jetradius;

    bool botPassed = botPassed1 || botPassed2;
    bool q1Passed = q1Passed1 || q1Passed2;
    bool q2Passed = q2Passed1 || q2Passed2;

    if(botPassed && q1Passed && q2Passed) DTGenTopJetM_EachQuarkMatched->Fill(topJet_v4_combined.M(), genweight);

  }

  //---------------------------------------------------------------------------------------
  //--------------------------------- Clear all used objects ------------------------------
  //---------------------------------------------------------------------------------------
  if(debug) cout << "\t--- Clear all used objects" << endl;
  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------

}
