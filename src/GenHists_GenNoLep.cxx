#include <UHH2/MTopJet/include/GenHists_GenNoLep.h>

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

#include "fastjet/PseudoJet.hh"
#include "fastjet/contrib/Nsubjettiness.hh"
#include "fastjet/contrib/SoftDrop.hh"
#include "fastjet/JetDefinition.hh"
#include "fastjet/ClusterSequence.hh"

#include "TH1F.h"

using namespace uhh2;

const double jetradius = 1.2;
const double subjetRadius = 0.2;

const int max_m = 500;
const int min_m = 0;
const int n_massbins = 50;

bool printOut3 = false;

GenHists_GenNoLep::GenHists_GenNoLep(uhh2::Context & ctx, const std::string & dirname, const std::string & jetname, float dR): Hists(ctx, dirname){
  // book all histograms here
  
  STGenTopJetPT = book<TH1F>("st_topJet_PT", "p_{T}^{st_top}", 50, 0, 1000);
  STGenGluonJetPT = book<TH1F>("st_gluonJet_PT", "p_{T}^{st_gluon}", 50, 0, 1000);
  STGenTopJetMSmallPT = book<TH1F>("st_topJet_M_smallPt", "M_{jet}^{st_top_smallPt}", 50, 0, 1000);

  STGenTopJetM = book<TH1F>("st_topJet_M", "M_{jet}^{st_top}", n_massbins, 0, max_m);
  STGenGluonJetM = book<TH1F>("st_gluonJet_M", "M_{jet}^{st_gluon}", n_massbins, 0, max_m);

  GenTopJetTau1 = book<TH1F>("topJet_tau1", "tau1^{top}", 50, 0, 1);
  GenTopJetTau2 = book<TH1F>("topJet_tau2", "tau2^{top}", 50, 0, 1);
  GenTopJetTau3 = book<TH1F>("topJet_tau3", "tau3^{top}", 50, 0, 1);
  GenTopJetTau4 = book<TH1F>("topJet_tau4", "tau4^{top}", 50, 0, 1);

  GenGluonJetTau1 = book<TH1F>("gluonJet_tau1", "tau1^{gluon}", 50, 0, 1);
  GenGluonJetTau2 = book<TH1F>("gluonJet_tau2", "tau2^{gluon}", 50, 0, 1);
  GenGluonJetTau3 = book<TH1F>("gluonJet_tau3", "tau3^{gluon}", 50, 0, 1);
  GenGluonJetTau4 = book<TH1F>("gluonJet_tau4", "tau4^{gluon}", 50, 0, 1);

  GenTopJetTau2Tau1 = book<TH1F>("topJet_tau2tau1", "(tau2/tau1)^{top}", 50, 0, 1);
  GenTopJetTau3Tau2 = book<TH1F>("topJet_tau3tau2", "(tau3/tau2)^{top}", 50, 0, 1);
  GenTopJetTau3Tau1 = book<TH1F>("topJet_tau3tau1", "(tau3/tau1)^{top}", 50, 0, 1);
  GenTopJetTau4Tau3 = book<TH1F>("topJet_tau4tau3", "(tau4/tau3)^{top}", 50, 0, 1);
  GenTopJetTau4Tau2 = book<TH1F>("topJet_tau4tau2", "(tau4/tau2)^{top}", 50, 0, 1);
  GenTopJetTau4Tau1 = book<TH1F>("topJet_tau4tau1", "(tau4/tau1)^{top}", 50, 0, 1);

  GenGluonJetTau2Tau1 = book<TH1F>("gluonJet_tau2tau1", "(tau2/tau1)^{gluon}", 50, 0, 1);
  GenGluonJetTau3Tau2 = book<TH1F>("gluonJet_tau3tau2", "(tau3/tau2)^{gluon}", 50, 0, 1);
  GenGluonJetTau3Tau1 = book<TH1F>("gluonJet_tau3tau1", "(tau3/tau1)^{gluon}", 50, 0, 1);
  GenGluonJetTau4Tau3 = book<TH1F>("gluonJet_tau4tau3", "(tau4/tau3)^{gluon}", 50, 0, 1);
  GenGluonJetTau4Tau2 = book<TH1F>("gluonJet_tau4tau2", "(tau4/tau2)^{gluon}", 50, 0, 1);
  GenGluonJetTau4Tau1 = book<TH1F>("gluonJet_tau4tau1", "(tau4/tau1)^{gluon}", 50, 0, 1);

  STGenDeltaRTopGluon = book<TH1F>("st_deltaRTopGluon", "st_DeltaR(topJet,gluonJet)", 80, 0, 4.0);

  STGluonSubjetPtSum = book<TH1F>("st_subjetPtSum", "(p_{T}^{subjets}/p_{T}^{jet})^{st_gluon}", 80, 0, 2.0);

  GenTopSubjetM1M = book<TH1F>("topSubjetM1M", "(M_{subjet1}/M_{jet})_{top}", 50, 0, 1);
  GenTopSubjetM2M = book<TH1F>("topSubjetM2M", "(M_{subjet2}/M_{jet})_{top}", 50, 0, 1);
  GenTopSubjetM3M = book<TH1F>("topSubjetM3M", "(M_{subjet3}/M_{jet})_{top}", 50, 0, 1);

  GenGluonSubjetM1M = book<TH1F>("gluonSubjetM1M", "(M_{subjet1}/M_{jet})_{gluon}", 50, 0, 1);
  GenGluonSubjetM2M = book<TH1F>("gluonSubjetM2M", "(M_{subjet2}/M_{jet})_{gluon}", 50, 0, 1);
  GenGluonSubjetM3M = book<TH1F>("gluonSubjetM3M", "(M_{subjet3}/M_{jet})_{gluon}", 50, 0, 1);

  GenTopSubjetPT1PT = book<TH1F>("topSubjetPT1PT", "(p_{T}^{subjet1}/p_{T}^{jet})^{top}", 50, 0, 1);
  GenTopSubjetPT2PT = book<TH1F>("topSubjetPT2PT", "(p_{T}^{subjet2}/p_{T}^{jet})^{top}", 50, 0, 1);
  GenTopSubjetPT3PT = book<TH1F>("topSubjetPT3PT", "(p_{T}^{subjet3}/p_{T}^{jet})^{top}", 50, 0, 1);

  GenGluonSubjetPT1PT = book<TH1F>("gluonSubjetPT1PT", "(p_{T}^{subjet1}/p_{T}^{jet})^{gluon}", 50, 0, 1);
  GenGluonSubjetPT2PT = book<TH1F>("gluonSubjetPT2PT", "(p_{T}^{subjet2}/p_{T}^{jet})^{gluon}", 50, 0, 1);
  GenGluonSubjetPT3PT = book<TH1F>("gluonSubjetPT3PT", "(p_{T}^{subjet3}/p_{T}^{jet})^{gluon}", 50, 0, 1);
  
  GenTopJetNumber = book<TH1F>("topJetNumber", "topJets.size()", 50, 0, 4);
  GenGluonJetNumber = book<TH1F>("gluonJetNumber", "gluonJets.size()", 50, 0, 4);

  DTGenTopJetPT = book<TH1F>("dt_topJet_PT", "p_{T}^{dt_top}", 50, 0, 1000);
  DTGenTopJetM = book<TH1F>("dt_topJet_M", "M_{jet}^{dt_top}", n_massbins, 0, max_m);

  DTGenTopJetPtCombined = book<TH1F>("dt_topJet_PT_combined", "p_{T}^{dt_top_combined}", 50, 0, 1000);
  DTGenTopJetMCombined = book<TH1F>("dt_topJet_M_combined", "M_{jet_combined}^{dt_top}", n_massbins, 0, max_m);

  DTGenDeltaRTopTop = book<TH1F>("dt_deltaRTopTop", "dt_DeltaR(topJet1,topJet2)", 80, 0, 4.0);


  DTGenTopJetTau1 = book<TH1F>("dt_topJet_tau1", "tau1^{dt_top}", 50, 0, 1);
  DTGenTopJetTau2 = book<TH1F>("dt_topJet_tau2", "tau2^{dt_top}", 50, 0, 1);
  DTGenTopJetTau3 = book<TH1F>("dt_topJet_tau3", "tau3^{dt_top}", 50, 0, 1);
  DTGenTopJetTau4 = book<TH1F>("dt_topJet_tau4", "tau4^{dt_top}", 50, 0, 1);

  DTGenTopJetTau2Tau1 = book<TH1F>("dt_topJet_tau2tau1", "(tau2/tau1)^{dt_top}", 50, 0, 1);
  DTGenTopJetTau3Tau2 = book<TH1F>("dt_topJet_tau3tau2", "(tau3/tau2)^{dt_top}", 50, 0, 1);
  DTGenTopJetTau3Tau1 = book<TH1F>("dt_topJet_tau3tau1", "(tau3/tau1)^{dt_top}", 50, 0, 1);
  DTGenTopJetTau4Tau3 = book<TH1F>("dt_topJet_tau4tau3", "(tau4/tau3)^{dt_top}", 50, 0, 1);
  DTGenTopJetTau4Tau2 = book<TH1F>("dt_topJet_tau4tau2", "(tau4/tau2)^{dt_top}", 50, 0, 1);
  DTGenTopJetTau4Tau1 = book<TH1F>("dt_topJet_tau4tau1", "(tau4/tau1)^{dt_top}", 50, 0, 1);

  DTGenTopSubjetM1M = book<TH1F>("dt_topSubjetM1M", "(M_{subjet1}/M_{jet})_{dt_top}", 50, 0, 1);
  DTGenTopSubjetM2M = book<TH1F>("dt_topSubjetM2M", "(M_{subjet2}/M_{jet})_{dt_top}", 50, 0, 1);
  DTGenTopSubjetM3M = book<TH1F>("dt_topSubjetM3M", "(M_{subjet3}/M_{jet})_{dt_top}", 50, 0, 1);

  DTGenTopSubjetPT1PT = book<TH1F>("dt_topSubjetPT1PT", "(p_{T}^{subjet1}/p_{T}^{jet})^{dt_top}", 50, 0, 1);
  DTGenTopSubjetPT2PT = book<TH1F>("dt_topSubjetPT2PT", "(p_{T}^{subjet2}/p_{T}^{jet})^{dt_top}", 50, 0, 1);
  DTGenTopSubjetPT3PT = book<TH1F>("dt_topSubjetPT3PT", "(p_{T}^{subjet3}/p_{T}^{jet})^{dt_top}", 50, 0, 1);


  DTNGGenTopJetTau1 = book<TH1F>("dtng_topJet_tau1", "tau1^{dtng_top}", 50, 0, 1);
  DTNGGenTopJetTau2 = book<TH1F>("dtng_topJet_tau2", "tau2^{dtng_top}", 50, 0, 1);
  DTNGGenTopJetTau3 = book<TH1F>("dtng_topJet_tau3", "tau3^{dtng_top}", 50, 0, 1);
  DTNGGenTopJetTau4 = book<TH1F>("dtng_topJet_tau4", "tau4^{dtng_top}", 50, 0, 1);

  DTNGGenTopJetTau2Tau1 = book<TH1F>("dtng_topJet_tau2tau1", "(tau2/tau1)^{dtng_top}", 50, 0, 1);
  DTNGGenTopJetTau3Tau2 = book<TH1F>("dtng_topJet_tau3tau2", "(tau3/tau2)^{dtng_top}", 50, 0, 1);
  DTNGGenTopJetTau3Tau1 = book<TH1F>("dtng_topJet_tau3tau1", "(tau3/tau1)^{dtng_top}", 50, 0, 1);
  DTNGGenTopJetTau4Tau3 = book<TH1F>("dtng_topJet_tau4tau3", "(tau4/tau3)^{dtng_top}", 50, 0, 1);
  DTNGGenTopJetTau4Tau2 = book<TH1F>("dtng_topJet_tau4tau2", "(tau4/tau2)^{dtng_top}", 50, 0, 1);
  DTNGGenTopJetTau4Tau1 = book<TH1F>("dtng_topJet_tau4tau1", "(tau4/tau1)^{dtng_top}", 50, 0, 1);
  
  DTNGGenTopSubjetM1M = book<TH1F>("dtng_topSubjetM1M", "(M_{subjet1}/M_{jet})_{dtng_top}", 50, 0, 1);
  DTNGGenTopSubjetM2M = book<TH1F>("dtng_topSubjetM2M", "(M_{subjet2}/M_{jet})_{dtng_top}", 50, 0, 1);
  DTNGGenTopSubjetM3M = book<TH1F>("dtng_topSubjetM3M", "(M_{subjet3}/M_{jet})_{dtng_top}", 50, 0, 1);

  DTNGGenTopSubjetPT1PT = book<TH1F>("dtng_topSubjetPT1PT", "(p_{T}^{subjet1}/p_{T}^{jet})^{dtng_top}", 50, 0, 1);
  DTNGGenTopSubjetPT2PT = book<TH1F>("dtng_topSubjetPT2PT", "(p_{T}^{subjet2}/p_{T}^{jet})^{dtng_top}", 50, 0, 1);
  DTNGGenTopSubjetPT3PT = book<TH1F>("dtng_topSubjetPT3PT", "(p_{T}^{subjet3}/p_{T}^{jet})^{dtng_top}", 50, 0, 1);


  GenTopJetCombinedTau1 = book<TH1F>("combinedTopJet_tau1", "tau1^{topCombined}", 50, 0, 1);
  GenTopJetCombinedTau2 = book<TH1F>("combinedTopJet_tau2", "tau2^{topCombined}", 50, 0, 1);
  GenTopJetCombinedTau3 = book<TH1F>("combinedTopJet_tau3", "tau3^{topCombined}", 50, 0, 1);
  GenTopJetCombinedTau4 = book<TH1F>("combinedTopJet_tau4", "tau4^{topCombined}", 50, 0, 1);

  GenTopJetCombinedTau2Tau1 = book<TH1F>("combinedTopJet_tau2tau1", "(tau2/tau1)^{topCombined}", 50, 0, 1);
  GenTopJetCombinedTau3Tau2 = book<TH1F>("combinedTopJet_tau3tau2", "(tau3/tau2)^{topCombined}", 50, 0, 1);
  GenTopJetCombinedTau3Tau1 = book<TH1F>("combinedTopJet_tau3tau1", "(tau3/tau1)^{topCombined}", 50, 0, 1);
  GenTopJetCombinedTau4Tau3 = book<TH1F>("combinedTopJet_tau4tau3", "(tau4/tau3)^{topCombined}", 50, 0, 1);
  GenTopJetCombinedTau4Tau2 = book<TH1F>("combinedTopJet_tau4tau2", "(tau4/tau2)^{topCombined}", 50, 0, 1);
  GenTopJetCombinedTau4Tau1 = book<TH1F>("combinedTopJet_tau4tau1", "(tau4/tau1)^{topCombined}", 50, 0, 1);


  GenTopJetCombinedOnlyTau1 = book<TH1F>("combinedOnlyTopJet_tau1", "tau1^{topCombinedOnly}", 50, 0, 1);
  GenTopJetCombinedOnlyTau2 = book<TH1F>("combinedOnlyTopJet_tau2", "tau2^{topCombinedOnly}", 50, 0, 1);
  GenTopJetCombinedOnlyTau3 = book<TH1F>("combinedOnlyTopJet_tau3", "tau3^{topCombinedOnly}", 50, 0, 1);
  GenTopJetCombinedOnlyTau4 = book<TH1F>("combinedOnlyTopJet_tau4", "tau4^{topCombinedOnly}", 50, 0, 1);

  GenTopJetCombinedOnlyTau2Tau1 = book<TH1F>("combinedOnlyTopJet_tau2tau1", "(tau2/tau1)^{topCombinedOnly}", 50, 0, 1);
  GenTopJetCombinedOnlyTau3Tau2 = book<TH1F>("combinedOnlyTopJet_tau3tau2", "(tau3/tau2)^{topCombinedOnly}", 50, 0, 1);
  GenTopJetCombinedOnlyTau3Tau1 = book<TH1F>("combinedOnlyTopJet_tau3tau1", "(tau3/tau1)^{topCombinedOnly}", 50, 0, 1);
  GenTopJetCombinedOnlyTau4Tau3 = book<TH1F>("combinedOnlyTopJet_tau4tau3", "(tau4/tau3)^{topCombinedOnly}", 50, 0, 1);
  GenTopJetCombinedOnlyTau4Tau2 = book<TH1F>("combinedOnlyTopJet_tau4tau2", "(tau4/tau2)^{topCombinedOnly}", 50, 0, 1);
  GenTopJetCombinedOnlyTau4Tau1 = book<TH1F>("combinedOnlyTopJet_tau4tau1", "(tau4/tau1)^{topCombinedOnly}", 50, 0, 1);


  GenTopJet1Tau1 = book<TH1F>("top1Jet_tau1", "tau1^{top1}", 50, 0, 1);
  GenTopJet1Tau2 = book<TH1F>("top1Jet_tau2", "tau2^{top1}", 50, 0, 1);
  GenTopJet1Tau3 = book<TH1F>("top1Jet_tau3", "tau3^{top1}", 50, 0, 1);
  GenTopJet1Tau4 = book<TH1F>("top1Jet_tau4", "tau4^{top1}", 50, 0, 1);

  GenTopJet1Tau2Tau1 = book<TH1F>("top1Jet_tau2tau1", "(tau2/tau1)^{top1}", 50, 0, 1);
  GenTopJet1Tau3Tau2 = book<TH1F>("top1Jet_tau3tau2", "(tau3/tau2)^{top1}", 50, 0, 1);
  GenTopJet1Tau3Tau1 = book<TH1F>("top1Jet_tau3tau1", "(tau3/tau1)^{top1}", 50, 0, 1);
  GenTopJet1Tau4Tau3 = book<TH1F>("top1Jet_tau4tau3", "(tau4/tau3)^{top1}", 50, 0, 1);
  GenTopJet1Tau4Tau2 = book<TH1F>("top1Jet_tau4tau2", "(tau4/tau2)^{top1}", 50, 0, 1);
  GenTopJet1Tau4Tau1 = book<TH1F>("top1Jet_tau4tau1", "(tau4/tau1)^{top1}", 50, 0, 1);


  GenTopJet2Tau1 = book<TH1F>("top2Jet_tau1", "tau1^{top2}", 50, 0, 1);
  GenTopJet2Tau2 = book<TH1F>("top2Jet_tau2", "tau2^{top2}", 50, 0, 1);
  GenTopJet2Tau3 = book<TH1F>("top2Jet_tau3", "tau3^{top2}", 50, 0, 1);
  GenTopJet2Tau4 = book<TH1F>("top2Jet_tau4", "tau4^{top2}", 50, 0, 1);

  GenTopJet2Tau2Tau1 = book<TH1F>("top2Jet_tau2tau1", "(tau2/tau1)^{top2}", 50, 0, 1);
  GenTopJet2Tau3Tau2 = book<TH1F>("top2Jet_tau3tau2", "(tau3/tau2)^{top2}", 50, 0, 1);
  GenTopJet2Tau3Tau1 = book<TH1F>("top2Jet_tau3tau1", "(tau3/tau1)^{top2}", 50, 0, 1);
  GenTopJet2Tau4Tau3 = book<TH1F>("top2Jet_tau4tau3", "(tau4/tau3)^{top2}", 50, 0, 1);
  GenTopJet2Tau4Tau2 = book<TH1F>("top2Jet_tau4tau2", "(tau4/tau2)^{top2}", 50, 0, 1);
  GenTopJet2Tau4Tau1 = book<TH1F>("top2Jet_tau4tau1", "(tau4/tau1)^{top2}", 50, 0, 1);


  GenTopJet12Tau1 = book<TH1F>("top12Jet_tau1", "tau1^{top12}", 50, 0, 1);
  GenTopJet12Tau2 = book<TH1F>("top12Jet_tau2", "tau2^{top12}", 50, 0, 1);
  GenTopJet12Tau3 = book<TH1F>("top12Jet_tau3", "tau3^{top12}", 50, 0, 1);
  GenTopJet12Tau4 = book<TH1F>("top12Jet_tau4", "tau4^{top12}", 50, 0, 1);

  GenTopJet12Tau2Tau1 = book<TH1F>("top12Jet_tau2tau1", "(tau2/tau1)^{top12}", 50, 0, 1);
  GenTopJet12Tau3Tau2 = book<TH1F>("top12Jet_tau3tau2", "(tau3/tau2)^{top12}", 50, 0, 1);
  GenTopJet12Tau3Tau1 = book<TH1F>("top12Jet_tau3tau1", "(tau3/tau1)^{top12}", 50, 0, 1);
  GenTopJet12Tau4Tau3 = book<TH1F>("top12Jet_tau4tau3", "(tau4/tau3)^{top12}", 50, 0, 1);
  GenTopJet12Tau4Tau2 = book<TH1F>("top12Jet_tau4tau2", "(tau4/tau2)^{top12}", 50, 0, 1);
  GenTopJet12Tau4Tau1 = book<TH1F>("top12Jet_tau4tau1", "(tau4/tau1)^{top12}", 50, 0, 1);


  GenJetMass = book<TH1F>("jetMass", "M^{jet}", n_massbins, 0, max_m);
  GenJetMassCombinedOnly = book<TH1F>("jetMassCombinedOnly", "M^{jetCombinedOnly}", n_massbins, 0, max_m);
  GenJetMassNotCombinedOnly = book<TH1F>("jetMassNotCombinedOnly", "M^{jetNotCombinedOnly}", n_massbins, 0, max_m);

  GenJetMassNotCombinedOnlySubjetsMatched = book<TH1F>("jetMassCombinedOnlySubjetsMatched", "M^{jetCombinedOnlySubjetsMatched}", n_massbins, 0, max_m);

  DTGenTopJetM_EachQuarkMatched = book<TH1F>("dt_topJet_M_EachQuarkMatched", "M_{jet}^{dt_top_eachQuarkMatched}", n_massbins, 0, max_m);
  DTGenTopJetM_EachQuarkMatched_GluonMatched = book<TH1F>("dt_topJet_M_EachQuarkMatched_GluonMatched", "M_{jet}^{dt_top_eachQuarkMatched_GluonMatched}", n_massbins, 0, max_m);
  DTGenTopJetM_EachQuarkMatched_NoGluonMatched = book<TH1F>("dt_topJet_M_EachQuarkMatched_NoGluonMatched", "M_{jet}^{dt_top_eachQuarkMatched_NoGluonMatched}", n_massbins, 0, max_m);

  STGenTopJetM_EachQuarkMatched = book<TH1F>("st_topJet_M_EachQuarkMatched", "M_{jet}^{st_top_eachQuarkMatched}", n_massbins, 0, max_m);
  STGenTopJetM_EachQuarkMatched_GluonMatched = book<TH1F>("st_topJet_M_EachQuarkMatched_GluonMatched", "M_{jet}^{st_top_eachQuarkMatched_GluonMatched}", n_massbins, 0, max_m);
  STGenTopJetM_EachQuarkMatched_NoGluonMatched = book<TH1F>("st_topJet_M_EachQuarkMatched_NoGluonMatched", "M_{jet}^{st_top_eachQuarkMatched_NoGluonMatched}", n_massbins, 0, max_m);

  DTGenTopJetMRatio = book<TH1F>("dt_topJetM1M2", "(M_{jet2}/M_{jet1})_{dt_top}", 20, 0, 2);
  DTGenTopJetpTRatio = book<TH1F>("dt_topJetPT1PT2", "(p_{T}^{jet2}/p_{T}^{jet1})_{dt_top}", 20, 0, 2);

  GenTopJetM_dR12 = book<TH1F>("topJet_M_dR12", "M_{jet}^{top_dR12}", n_massbins, 0, max_m);
  GenTopJetM_dR08 = book<TH1F>("topJet_M_dR08", "M_{jet}^{top_dR08}", n_massbins, 0, max_m);
  GenTopJetM_dR04 = book<TH1F>("topJet_M_dR04", "M_{jet}^{top_dR04}", n_massbins, 0, max_m);

  GenTopJetLeadingM_dR12 = book<TH1F>("topJetLeading_M_dR12", "M_{jet}^{topLeading_dR12}", n_massbins, 0, max_m);
  GenTopJetLeadingM_dR08 = book<TH1F>("topJetLeading_M_dR08", "M_{jet}^{topLeading_dR08}", n_massbins, 0, max_m);
  GenTopJetLeadingM_dR04 = book<TH1F>("topJetLeading_M_dR04", "M_{jet}^{topLeading_dR04}", n_massbins, 0, max_m);

  GenTopJetSubLeadingM_dR12 = book<TH1F>("topJetSubLeading_M_dR12", "M_{jet}^{topSubLeading_dR12}", n_massbins, 0, max_m);
  GenTopJetSubLeadingM_dR08 = book<TH1F>("topJetSubLeading_M_dR08", "M_{jet}^{topSubLeading_dR08}", n_massbins, 0, max_m);
  GenTopJetSubLeadingM_dR04 = book<TH1F>("topJetSubLeading_M_dR04", "M_{jet}^{topSubLeading_dR04}", n_massbins, 0, max_m);

  GenTopJetM_dRvaried600 = book<TH1F>("topJet_M_dRvaried600", "M_{jet}^{top_dRvaried600}", n_massbins, 0, max_m);
  GenTopJetM_dRvaried450 = book<TH1F>("topJet_M_dRvaried450", "M_{jet}^{top_dRvaried450}", n_massbins, 0, max_m);
  GenTopJetM_dRvaried350 = book<TH1F>("topJet_M_dRvaried350", "M_{jet}^{top_dRvaried350}", n_massbins, 0, max_m);

  GenTopJetLeadingM_dRvaried600 = book<TH1F>("topJetLeading_M_dRvaried600", "M_{jet}^{topLeading_dRvaried600}", n_massbins, 0, max_m);
  GenTopJetLeadingM_dRvaried450 = book<TH1F>("topJetLeading_M_dRvaried450", "M_{jet}^{topLeading_dRvaried450}", n_massbins, 0, max_m);
  GenTopJetLeadingM_dRvaried350 = book<TH1F>("topJetLeading_M_dRvaried350", "M_{jet}^{topLeading_dRvaried350}", n_massbins, 0, max_m);

  GenTopJetSubLeadingM_dRvaried600 = book<TH1F>("topJetSubLeading_M_dRvaried600", "M_{jet}^{topSubLeading_dRvaried600}", n_massbins, 0, max_m);
  GenTopJetSubLeadingM_dRvaried450 = book<TH1F>("topJetSubLeading_M_dRvaried450", "M_{jet}^{topSubLeading_dRvaried450}", n_massbins, 0, max_m);
  GenTopJetSubLeadingM_dRvaried350 = book<TH1F>("topJetSubLeading_M_dRvaried350", "M_{jet}^{topSubLeading_dRvaried350}", n_massbins, 0, max_m);

  GenDeltaRJets = book<TH1F>("deltaRJets", "DeltaR(jet1,jet2)", 80, 0, 4.0);

  GenJetM_dR12 = book<TH1F>("jet_M_dR12", "M_{jet}^{dR12}", n_massbins, 0, max_m);
  GenJetM_dR08 = book<TH1F>("jet_M_dR08", "M_{jet}^{dR08}", n_massbins, 0, max_m);
  GenJetM_dR04 = book<TH1F>("jet_M_dR04", "M_{jet}^{dR04}", n_massbins, 0, max_m);

  GenJetM_dRvaried600 = book<TH1F>("jet_M_dRvaried600", "M_{jet}^{dRvaried600}", n_massbins, 0, max_m);
  GenJetM_dRvaried450 = book<TH1F>("jet_M_dRvaried450", "M_{jet}^{dRvaried450}", n_massbins, 0, max_m);
  GenJetM_dRvaried350 = book<TH1F>("jet_M_dRvaried350", "M_{jet}^{dRvaried350}", n_massbins, 0, max_m);

  GenJetM_dR12_AllQuarksMatched = book<TH1F>("jet_M_dR12_AllQuarksMatched", "M_{jet}^{dR12_AllQuarksMatched}", n_massbins, 0, max_m);
  GenJetM_dR08_AllQuarksMatched = book<TH1F>("jet_M_dR08_AllQuarksMatched", "M_{jet}^{dR08_AllQuarksMatched}", n_massbins, 0, max_m);
  GenJetM_dR04_AllQuarksMatched = book<TH1F>("jet_M_dR04_AllQuarksMatched", "M_{jet}^{dR04_AllQuarksMatched}", n_massbins, 0, max_m);

  GenJetM_dRvaried600_AllQuarksMatched = book<TH1F>("jet_M_dRvaried600_AllQuarksMatched", "M_{jet}^{dRvaried600_AllQuarksMatched}", n_massbins, 0, max_m);
  GenJetM_dRvaried450_AllQuarksMatched = book<TH1F>("jet_M_dRvaried450_AllQuarksMatched", "M_{jet}^{dRvaried450_AllQuarksMatched}", n_massbins, 0, max_m);
  GenJetM_dRvaried350_AllQuarksMatched = book<TH1F>("jet_M_dRvaried350_AllQuarksMatched", "M_{jet}^{dRvaried350_AllQuarksMatched}", n_massbins, 0, max_m);

  GenJetM_dR12_AllQuarksMatched_Gluon = book<TH1F>("jet_M_dR12_AllQuarksMatched_Gluon", "M_{jet}^{dR12_AllQuarksMatched_Gluon}", n_massbins, 0, max_m);
  GenJetM_dR12_AllQuarksMatched_NoGluon = book<TH1F>("jet_M_dR12_AllQuarksMatched_NoGluon", "M_{jet}^{dR12_AllQuarksMatched_NoGluon}", n_massbins, 0, max_m);

  GenGluonSubjetSize = book<TH1F>("gluonSubjetNumber", "gluonSubjets.size()", 50, 0, 4);
  GenTopSubjetSize = book<TH1F>("topSubjetNumber", "topSubjets.size()", 50, 0, 4);

  GenGluonPt0 = book<TH1F>("gluonPt0", "gluon with Pt = 0", 50, 0, 4);
  GenTopPt0 = book<TH1F>("topPt0", "top with Pt = 0", 50, 0, 4);

  GenGluonNumber = book<TH1F>("gluonNumber", "gluonNumber", 10, 0, 10);
  GenDeltaRGluonTop = book<TH1F>("deltaRGluonTop", "DeltaR(gluon,top)", 80, 0, 4.0);
  GenDeltaRTopAntitop = book<TH1F>("deltaRTopAntitop", "DeltaR(top,antitop)", 80, 0, 4.0);
  GenDeltaRTopGluonDeltaRTopAntitop = book<TH2F>("deltaRTopGluonDeltaRTopAntitop", "deltaR(top,gluon) vs deltaR(top,antitop)", 80, 0, 4.0, 80, 0, 4.0);


  GenJet1MassAll = book<TH1F>("M_jet1_MassAll", "M_{jetAll}", n_massbins, min_m, max_m);
  GenJet1MassBot = book<TH1F>("M_jet1_MassBot", "M_{jetBot}", n_massbins, min_m, max_m);
  GenJet1MassTwoLightQ = book<TH1F>("M_jet1_MassTwoLightQ", "M_{jetTwoLightQ}", n_massbins, min_m, max_m);
  GenJet1MassBotOneLightQ = book<TH1F>("M_jet1_MassBotOneLightQ", "M_{jetBotOneLightQ}", n_massbins, min_m, max_m);
  GenJet1MassOneQ = book<TH1F>("M_jet1_MassOneQ", "M_{jetOneQ}", n_massbins, min_m, max_m);
  GenJet1MassNoQ = book<TH1F>("M_jet1_MassNoQ", "M_{jetNoQ}", n_massbins, min_m, max_m);

  GenJet1MassGluonAll = book<TH1F>("M_jet1_MassGluonAll", "M_{jetGluonAll}", n_massbins, min_m, max_m);
  GenJet1MassGluonBot = book<TH1F>("M_jet1_MassGluonBot", "M_{jetGluonBot}", n_massbins, min_m, max_m);
  GenJet1MassGluonTwoLightQ = book<TH1F>("M_jet1_MassGluonTwoLightQ", "M_{jetGluonTwoLightQ}", n_massbins, min_m, max_m);
  GenJet1MassGluonBotOneLightQ = book<TH1F>("M_jet1_MassGluonBotOneLightQ", "M_{jetGluonBotOneLightQ}", n_massbins, min_m, max_m);
  GenJet1MassGluonOneQ = book<TH1F>("M_jet1_MassGluonOneQ", "M_{jetGluonOneQ}", n_massbins, min_m, max_m);
  GenJet1MassGluonNoQ = book<TH1F>("M_jet1_MassGluonNoQ", "M_{jetGluonNoQ}", n_massbins, min_m, max_m);


  GenOneJetMassAll = book<TH1F>("M_oneJet_MassAll", "M_{oneJetAll}", n_massbins, min_m, max_m);
  GenOneJetMassBot = book<TH1F>("M_oneJet_MassBot", "M_{oneJetBot}", n_massbins, min_m, max_m);
  GenOneJetMassTwoLightQ = book<TH1F>("M_oneJet_MassTwoLightQ", "M_{oneJetTwoLightQ}", n_massbins, min_m, max_m);
  GenOneJetMassBotOneLightQ = book<TH1F>("M_oneJet_MassBotOneLightQ", "M_{oneJetBotOneLightQ}", n_massbins, min_m, max_m);
  GenOneJetMassLightQ = book<TH1F>("M_oneJet_MassLightQ", "M_{oneJetLightQ}", n_massbins, min_m, max_m);
  GenOneJetMassNoQ = book<TH1F>("oneJet", "M_{oneJetNoQ}", n_massbins, min_m, max_m);

  GenTwoJetMassAll = book<TH1F>("M_twoJet_MassAll", "M_{twoJetAll}", n_massbins, min_m, max_m);
  GenTwoJetMassTwoQuarks = book<TH1F>("M_twoJet_MassTwoQuarks", "M_{twoJetTwoQuarks}", n_massbins, min_m, max_m);

  GenDecayProductInBothJets = book<TH1F>("M_DecayInBoth", "M_{decayInBoth}", n_massbins, min_m, max_m);


  GenOneJetAllTau1 = book<TH1F>("oneAllJet_tau1", "tau1^{oneAll}", 50, 0, 1);
  GenOneJetAllTau2 = book<TH1F>("oneAllJet_tau2", "tau2^{oneAll}", 50, 0, 1);
  GenOneJetAllTau3 = book<TH1F>("oneAllJet_tau3", "tau3^{oneAll}", 50, 0, 1);
  GenOneJetAllTau4 = book<TH1F>("oneAllJet_tau4", "tau4^{oneAll}", 50, 0, 1);

  GenOneJetAllTau2Tau1 = book<TH1F>("oneAllJet_tau2tau1", "(tau2/tau1)^{oneAll}", 50, 0, 1);
  GenOneJetAllTau3Tau2 = book<TH1F>("oneAllJet_tau3tau2", "(tau3/tau2)^{oneAll}", 50, 0, 1);
  GenOneJetAllTau3Tau1 = book<TH1F>("oneAllJet_tau3tau1", "(tau3/tau1)^{oneAll}", 50, 0, 1);
  GenOneJetAllTau4Tau3 = book<TH1F>("oneAllJet_tau4tau3", "(tau4/tau3)^{oneAll}", 50, 0, 1);
  GenOneJetAllTau4Tau2 = book<TH1F>("oneAllJet_tau4tau2", "(tau4/tau2)^{oneAll}", 50, 0, 1);
  GenOneJetAllTau4Tau1 = book<TH1F>("oneAllJet_tau4tau1", "(tau4/tau1)^{oneAll}", 50, 0, 1);


  GenTwoJetAllSub1234Tau1 = book<TH1F>("twoAllSub1234Jet_tau1", "tau1^{twoAllSub1234}", 50, 0, 1);
  GenTwoJetAllSub1234Tau2 = book<TH1F>("twoAllSub1234Jet_tau2", "tau2^{twoAllSub1234}", 50, 0, 1);
  GenTwoJetAllSub1234Tau3 = book<TH1F>("twoAllSub1234Jet_tau3", "tau3^{twoAllSub1234}", 50, 0, 1);

  GenTwoJetAllSub1234Tau2Tau1 = book<TH1F>("twoAllSub1234Jet_tau2tau1", "(tau2/tau1)^{twoAllSub1234}", 50, 0, 1);
  GenTwoJetAllSub1234Tau3Tau2 = book<TH1F>("twoAllSub1234Jet_tau3tau2", "(tau3/tau2)^{twoAllSub1234}", 50, 0, 1);
  GenTwoJetAllSub1234Tau3Tau1 = book<TH1F>("twoAllSub1234Jet_tau3tau1", "(tau3/tau1)^{twoAllSub1234}", 50, 0, 1);

  GenTwoJetAllSub1235Tau1 = book<TH1F>("twoAllSub1235Jet_tau1", "tau1^{twoAllSub1235}", 50, 0, 1);
  GenTwoJetAllSub1235Tau2 = book<TH1F>("twoAllSub1235Jet_tau2", "tau2^{twoAllSub1235}", 50, 0, 1);
  GenTwoJetAllSub1235Tau3 = book<TH1F>("twoAllSub1235Jet_tau3", "tau3^{twoAllSub1235}", 50, 0, 1);

  GenTwoJetAllSub1235Tau2Tau1 = book<TH1F>("twoAllSub1235Jet_tau2tau1", "(tau2/tau1)^{twoAllSub1235}", 50, 0, 1);
  GenTwoJetAllSub1235Tau3Tau2 = book<TH1F>("twoAllSub1235Jet_tau3tau2", "(tau3/tau2)^{twoAllSub1235}", 50, 0, 1);
  GenTwoJetAllSub1235Tau3Tau1 = book<TH1F>("twoAllSub1235Jet_tau3tau1", "(tau3/tau1)^{twoAllSub1235}", 50, 0, 1);

  GenTwoJetAllSub1236Tau1 = book<TH1F>("twoAllSub1236Jet_tau1", "tau1^{twoAllSub1236}", 50, 0, 1);
  GenTwoJetAllSub1236Tau2 = book<TH1F>("twoAllSub1236Jet_tau2", "tau2^{twoAllSub1236}", 50, 0, 1);
  GenTwoJetAllSub1236Tau3 = book<TH1F>("twoAllSub1236Jet_tau3", "tau3^{twoAllSub1236}", 50, 0, 1);

  GenTwoJetAllSub1236Tau2Tau1 = book<TH1F>("twoAllSub1236Jet_tau2tau1", "(tau2/tau1)^{twoAllSub1236}", 50, 0, 1);
  GenTwoJetAllSub1236Tau3Tau2 = book<TH1F>("twoAllSub1236Jet_tau3tau2", "(tau3/tau2)^{twoAllSub1236}", 50, 0, 1);
  GenTwoJetAllSub1236Tau3Tau1 = book<TH1F>("twoAllSub1236Jet_tau3tau1", "(tau3/tau1)^{twoAllSub1236}", 50, 0, 1);

  GenTwoJetAllSub1245Tau1 = book<TH1F>("twoAllSub1245Jet_tau1", "tau1^{twoAllSub1245}", 50, 0, 1);
  GenTwoJetAllSub1245Tau2 = book<TH1F>("twoAllSub1245Jet_tau2", "tau2^{twoAllSub1245}", 50, 0, 1);
  GenTwoJetAllSub1245Tau3 = book<TH1F>("twoAllSub1245Jet_tau3", "tau3^{twoAllSub1245}", 50, 0, 1);

  GenTwoJetAllSub1245Tau2Tau1 = book<TH1F>("twoAllSub1245Jet_tau2tau1", "(tau2/tau1)^{twoAllSub1245}", 50, 0, 1);
  GenTwoJetAllSub1245Tau3Tau2 = book<TH1F>("twoAllSub1245Jet_tau3tau2", "(tau3/tau2)^{twoAllSub1245}", 50, 0, 1);
  GenTwoJetAllSub1245Tau3Tau1 = book<TH1F>("twoAllSub1245Jet_tau3tau1", "(tau3/tau1)^{twoAllSub1245}", 50, 0, 1);

  GenTwoJetAllSub1246Tau1 = book<TH1F>("twoAllSub1246Jet_tau1", "tau1^{twoAllSub1246}", 50, 0, 1);
  GenTwoJetAllSub1246Tau2 = book<TH1F>("twoAllSub1246Jet_tau2", "tau2^{twoAllSub1246}", 50, 0, 1);
  GenTwoJetAllSub1246Tau3 = book<TH1F>("twoAllSub1246Jet_tau3", "tau3^{twoAllSub1246}", 50, 0, 1);

  GenTwoJetAllSub1246Tau2Tau1 = book<TH1F>("twoAllSub1246Jet_tau2tau1", "(tau2/tau1)^{twoAllSub1246}", 50, 0, 1);
  GenTwoJetAllSub1246Tau3Tau2 = book<TH1F>("twoAllSub1246Jet_tau3tau2", "(tau3/tau2)^{twoAllSub1246}", 50, 0, 1);
  GenTwoJetAllSub1246Tau3Tau1 = book<TH1F>("twoAllSub1246Jet_tau3tau1", "(tau3/tau1)^{twoAllSub1246}", 50, 0, 1);

  GenTwoJetAllSub1256Tau1 = book<TH1F>("twoAllSub1256Jet_tau1", "tau1^{twoAllSub1256}", 50, 0, 1);
  GenTwoJetAllSub1256Tau2 = book<TH1F>("twoAllSub1256Jet_tau2", "tau2^{twoAllSub1256}", 50, 0, 1);
  GenTwoJetAllSub1256Tau3 = book<TH1F>("twoAllSub1256Jet_tau3", "tau3^{twoAllSub1256}", 50, 0, 1);

  GenTwoJetAllSub1256Tau2Tau1 = book<TH1F>("twoAllSub1256Jet_tau2tau1", "(tau2/tau1)^{twoAllSub1256}", 50, 0, 1);
  GenTwoJetAllSub1256Tau3Tau2 = book<TH1F>("twoAllSub1256Jet_tau3tau2", "(tau3/tau2)^{twoAllSub1256}", 50, 0, 1);
  GenTwoJetAllSub1256Tau3Tau1 = book<TH1F>("twoAllSub1256Jet_tau3tau1", "(tau3/tau1)^{twoAllSub1256}", 50, 0, 1);

  GenTwoJetAllSub1345Tau1 = book<TH1F>("twoAllSub1345Jet_tau1", "tau1^{twoAllSub1345}", 50, 0, 1);
  GenTwoJetAllSub1345Tau2 = book<TH1F>("twoAllSub1345Jet_tau2", "tau2^{twoAllSub1345}", 50, 0, 1);
  GenTwoJetAllSub1345Tau3 = book<TH1F>("twoAllSub1345Jet_tau3", "tau3^{twoAllSub1345}", 50, 0, 1);

  GenTwoJetAllSub1345Tau2Tau1 = book<TH1F>("twoAllSub1345Jet_tau2tau1", "(tau2/tau1)^{twoAllSub1345}", 50, 0, 1);
  GenTwoJetAllSub1345Tau3Tau2 = book<TH1F>("twoAllSub1345Jet_tau3tau2", "(tau3/tau2)^{twoAllSub1345}", 50, 0, 1);
  GenTwoJetAllSub1345Tau3Tau1 = book<TH1F>("twoAllSub1345Jet_tau3tau1", "(tau3/tau1)^{twoAllSub1345}", 50, 0, 1);

  GenTwoJetAllSub1346Tau1 = book<TH1F>("twoAllSub1346Jet_tau1", "tau1^{twoAllSub1346}", 50, 0, 1);
  GenTwoJetAllSub1346Tau2 = book<TH1F>("twoAllSub1346Jet_tau2", "tau2^{twoAllSub1346}", 50, 0, 1);
  GenTwoJetAllSub1346Tau3 = book<TH1F>("twoAllSub1346Jet_tau3", "tau3^{twoAllSub1346}", 50, 0, 1);

  GenTwoJetAllSub1346Tau2Tau1 = book<TH1F>("twoAllSub1346Jet_tau2tau1", "(tau2/tau1)^{twoAllSub1346}", 50, 0, 1);
  GenTwoJetAllSub1346Tau3Tau2 = book<TH1F>("twoAllSub1346Jet_tau3tau2", "(tau3/tau2)^{twoAllSub1346}", 50, 0, 1);
  GenTwoJetAllSub1346Tau3Tau1 = book<TH1F>("twoAllSub1346Jet_tau3tau1", "(tau3/tau1)^{twoAllSub1346}", 50, 0, 1);

  GenTwoJetAllSub1356Tau1 = book<TH1F>("twoAllSub1356Jet_tau1", "tau1^{twoAllSub1356}", 50, 0, 1);
  GenTwoJetAllSub1356Tau2 = book<TH1F>("twoAllSub1356Jet_tau2", "tau2^{twoAllSub1356}", 50, 0, 1);
  GenTwoJetAllSub1356Tau3 = book<TH1F>("twoAllSub1356Jet_tau3", "tau3^{twoAllSub1356}", 50, 0, 1);

  GenTwoJetAllSub1356Tau2Tau1 = book<TH1F>("twoAllSub1356Jet_tau2tau1", "(tau2/tau1)^{twoAllSub1356}", 50, 0, 1);
  GenTwoJetAllSub1356Tau3Tau2 = book<TH1F>("twoAllSub1356Jet_tau3tau2", "(tau3/tau2)^{twoAllSub1356}", 50, 0, 1);
  GenTwoJetAllSub1356Tau3Tau1 = book<TH1F>("twoAllSub1356Jet_tau3tau1", "(tau3/tau1)^{twoAllSub1356}", 50, 0, 1);

  GenTwoJetAllSub1456Tau1 = book<TH1F>("twoAllSub1456Jet_tau1", "tau1^{twoAllSub1456}", 50, 0, 1);
  GenTwoJetAllSub1456Tau2 = book<TH1F>("twoAllSub1456Jet_tau2", "tau2^{twoAllSub1456}", 50, 0, 1);
  GenTwoJetAllSub1456Tau3 = book<TH1F>("twoAllSub1456Jet_tau3", "tau3^{twoAllSub1456}", 50, 0, 1);

  GenTwoJetAllSub1456Tau2Tau1 = book<TH1F>("twoAllSub1456Jet_tau2tau1", "(tau2/tau1)^{twoAllSub1456}", 50, 0, 1);
  GenTwoJetAllSub1456Tau3Tau2 = book<TH1F>("twoAllSub1456Jet_tau3tau2", "(tau3/tau2)^{twoAllSub1456}", 50, 0, 1);
  GenTwoJetAllSub1456Tau3Tau1 = book<TH1F>("twoAllSub1456Jet_tau3tau1", "(tau3/tau1)^{twoAllSub1456}", 50, 0, 1);

  GenTwoJetAllSub2345Tau1 = book<TH1F>("twoAllSub2345Jet_tau1", "tau1^{twoAllSub2345}", 50, 0, 1);
  GenTwoJetAllSub2345Tau2 = book<TH1F>("twoAllSub2345Jet_tau2", "tau2^{twoAllSub2345}", 50, 0, 1);
  GenTwoJetAllSub2345Tau3 = book<TH1F>("twoAllSub2345Jet_tau3", "tau3^{twoAllSub2345}", 50, 0, 1);

  GenTwoJetAllSub2345Tau2Tau1 = book<TH1F>("twoAllSub2345Jet_tau2tau1", "(tau2/tau1)^{twoAllSub2345}", 50, 0, 1);
  GenTwoJetAllSub2345Tau3Tau2 = book<TH1F>("twoAllSub2345Jet_tau3tau2", "(tau3/tau2)^{twoAllSub2345}", 50, 0, 1);
  GenTwoJetAllSub2345Tau3Tau1 = book<TH1F>("twoAllSub2345Jet_tau3tau1", "(tau3/tau1)^{twoAllSub2345}", 50, 0, 1);

  GenTwoJetAllSub2346Tau1 = book<TH1F>("twoAllSub2346Jet_tau1", "tau1^{twoAllSub2346}", 50, 0, 1);
  GenTwoJetAllSub2346Tau2 = book<TH1F>("twoAllSub2346Jet_tau2", "tau2^{twoAllSub2346}", 50, 0, 1);
  GenTwoJetAllSub2346Tau3 = book<TH1F>("twoAllSub2346Jet_tau3", "tau3^{twoAllSub2346}", 50, 0, 1);

  GenTwoJetAllSub2346Tau2Tau1 = book<TH1F>("twoAllSub2346Jet_tau2tau1", "(tau2/tau1)^{twoAllSub2346}", 50, 0, 1);
  GenTwoJetAllSub2346Tau3Tau2 = book<TH1F>("twoAllSub2346Jet_tau3tau2", "(tau3/tau2)^{twoAllSub2346}", 50, 0, 1);
  GenTwoJetAllSub2346Tau3Tau1 = book<TH1F>("twoAllSub2346Jet_tau3tau1", "(tau3/tau1)^{twoAllSub2346}", 50, 0, 1);

  GenTwoJetAllSub2356Tau1 = book<TH1F>("twoAllSub2356Jet_tau1", "tau1^{twoAllSub2356}", 50, 0, 1);
  GenTwoJetAllSub2356Tau2 = book<TH1F>("twoAllSub2356Jet_tau2", "tau2^{twoAllSub2356}", 50, 0, 1);
  GenTwoJetAllSub2356Tau3 = book<TH1F>("twoAllSub2356Jet_tau3", "tau3^{twoAllSub2356}", 50, 0, 1);

  GenTwoJetAllSub2356Tau2Tau1 = book<TH1F>("twoAllSub2356Jet_tau2tau1", "(tau2/tau1)^{twoAllSub2356}", 50, 0, 1);
  GenTwoJetAllSub2356Tau3Tau2 = book<TH1F>("twoAllSub2356Jet_tau3tau2", "(tau3/tau2)^{twoAllSub2356}", 50, 0, 1);
  GenTwoJetAllSub2356Tau3Tau1 = book<TH1F>("twoAllSub2356Jet_tau3tau1", "(tau3/tau1)^{twoAllSub2356}", 50, 0, 1);

  GenTwoJetAllSub2456Tau1 = book<TH1F>("twoAllSub2456Jet_tau1", "tau1^{twoAllSub2456}", 50, 0, 1);
  GenTwoJetAllSub2456Tau2 = book<TH1F>("twoAllSub2456Jet_tau2", "tau2^{twoAllSub2456}", 50, 0, 1);
  GenTwoJetAllSub2456Tau3 = book<TH1F>("twoAllSub2456Jet_tau3", "tau3^{twoAllSub2456}", 50, 0, 1);

  GenTwoJetAllSub2456Tau2Tau1 = book<TH1F>("twoAllSub2456Jet_tau2tau1", "(tau2/tau1)^{twoAllSub2456}", 50, 0, 1);
  GenTwoJetAllSub2456Tau3Tau2 = book<TH1F>("twoAllSub2456Jet_tau3tau2", "(tau3/tau2)^{twoAllSub2456}", 50, 0, 1);
  GenTwoJetAllSub2456Tau3Tau1 = book<TH1F>("twoAllSub2456Jet_tau3tau1", "(tau3/tau1)^{twoAllSub2456}", 50, 0, 1);

  GenTwoJetAllSub3456Tau1 = book<TH1F>("twoAllSub3456Jet_tau1", "tau1^{twoAllSub3456}", 50, 0, 1);
  GenTwoJetAllSub3456Tau2 = book<TH1F>("twoAllSub3456Jet_tau2", "tau2^{twoAllSub3456}", 50, 0, 1);
  GenTwoJetAllSub3456Tau3 = book<TH1F>("twoAllSub3456Jet_tau3", "tau3^{twoAllSub3456}", 50, 0, 1);

  GenTwoJetAllSub3456Tau2Tau1 = book<TH1F>("twoAllSub3456Jet_tau2tau1", "(tau2/tau1)^{twoAllSub3456}", 50, 0, 1);
  GenTwoJetAllSub3456Tau3Tau2 = book<TH1F>("twoAllSub3456Jet_tau3tau2", "(tau3/tau2)^{twoAllSub3456}", 50, 0, 1);
  GenTwoJetAllSub3456Tau3Tau1 = book<TH1F>("twoAllSub3456Jet_tau3tau1", "(tau3/tau1)^{twoAllSub3456}", 50, 0, 1);


  GenTwoJetAllSubAllTau1 = book<TH1F>("twoAllSubAllJet_tau1", "tau1^{twoAllSubAll}", 50, 0, 1);
  GenTwoJetAllSubAllTau2 = book<TH1F>("twoAllSubAllJet_tau2", "tau2^{twoAllSubAll}", 50, 0, 1);
  GenTwoJetAllSubAllTau3 = book<TH1F>("twoAllSubAllJet_tau3", "tau3^{twoAllSubAll}", 50, 0, 1);

  GenTwoJetAllSubAllTau2Tau1 = book<TH1F>("twoAllSubAllJet_tau2tau1", "(tau2/tau1)^{twoAllSubAll}", 50, 0, 1);
  GenTwoJetAllSubAllTau3Tau2 = book<TH1F>("twoAllSubAllJet_tau3tau2", "(tau3/tau2)^{twoAllSubAll}", 50, 0, 1);
  GenTwoJetAllSubAllTau3Tau1 = book<TH1F>("twoAllSubAllJet_tau3tau1", "(tau3/tau1)^{twoAllSubAll}", 50, 0, 1);

  GenTwoJetAllSubMatchedTau1 = book<TH1F>("twoAllSubMatchedJet_tau1", "tau1^{twoAllSubMatched}", 50, 0, 1);
  GenTwoJetAllSubMatchedTau2 = book<TH1F>("twoAllSubMatchedJet_tau2", "tau2^{twoAllSubMatched}", 50, 0, 1);
  GenTwoJetAllSubMatchedTau3 = book<TH1F>("twoAllSubMatchedJet_tau3", "tau3^{twoAllSubMatched}", 50, 0, 1);

  GenTwoJetAllSubMatchedTau2Tau1 = book<TH1F>("twoAllSubMatchedJet_tau2tau1", "(tau2/tau1)^{twoAllSubMatched}", 50, 0, 1);
  GenTwoJetAllSubMatchedTau3Tau2 = book<TH1F>("twoAllSubMatchedJet_tau3tau2", "(tau3/tau2)^{twoAllSubMatched}", 50, 0, 1);
  GenTwoJetAllSubMatchedTau3Tau1 = book<TH1F>("twoAllSubMatchedJet_tau3tau1", "(tau3/tau1)^{twoAllSubMatched}", 50, 0, 1);

  GenTwoJetAllSubOneMatchedTau1 = book<TH1F>("twoAllSubOneMatchedJet_tau1", "tau1^{twoAllSubOneMatched}", 50, 0, 1);
  GenTwoJetAllSubOneMatchedTau2 = book<TH1F>("twoAllSubOneMatchedJet_tau2", "tau2^{twoAllSubOneMatched}", 50, 0, 1);
  GenTwoJetAllSubOneMatchedTau3 = book<TH1F>("twoAllSubOneMatchedJet_tau3", "tau3^{twoAllSubOneMatched}", 50, 0, 1);

  GenTwoJetAllSubOneMatchedTau2Tau1 = book<TH1F>("twoAllSubOneMatchedJet_tau2tau1", "(tau2/tau1)^{twoAllSubOneMatched}", 50, 0, 1);
  GenTwoJetAllSubOneMatchedTau3Tau2 = book<TH1F>("twoAllSubOneMatchedJet_tau3tau2", "(tau3/tau2)^{twoAllSubOneMatched}", 50, 0, 1);
  GenTwoJetAllSubOneMatchedTau3Tau1 = book<TH1F>("twoAllSubOneMatchedJet_tau3tau1", "(tau3/tau1)^{twoAllSubOneMatched}", 50, 0, 1);

  GenTwoJetAllSubTwoMatchedTau1 = book<TH1F>("twoAllSubTwoMatchedJet_tau1", "tau1^{twoAllSubTwoMatched}", 50, 0, 1);
  GenTwoJetAllSubTwoMatchedTau2 = book<TH1F>("twoAllSubTwoMatchedJet_tau2", "tau2^{twoAllSubTwoMatched}", 50, 0, 1);
  GenTwoJetAllSubTwoMatchedTau3 = book<TH1F>("twoAllSubTwoMatchedJet_tau3", "tau3^{twoAllSubTwoMatched}", 50, 0, 1);

  GenTwoJetAllSubTwoMatchedTau2Tau1 = book<TH1F>("twoAllSubTwoMatchedJet_tau2tau1", "(tau2/tau1)^{twoAllSubTwoMatched}", 50, 0, 1);
  GenTwoJetAllSubTwoMatchedTau3Tau2 = book<TH1F>("twoAllSubTwoMatchedJet_tau3tau2", "(tau3/tau2)^{twoAllSubTwoMatched}", 50, 0, 1);
  GenTwoJetAllSubTwoMatchedTau3Tau1 = book<TH1F>("twoAllSubTwoMatchedJet_tau3tau1", "(tau3/tau1)^{twoAllSubTwoMatched}", 50, 0, 1);

  GenTwoJetAllSubPartialMatchedTau1 = book<TH1F>("twoAllSubPartialMatchedJet_tau1", "tau1^{twoAllSubPartialMatched}", 50, 0, 1);
  GenTwoJetAllSubPartialMatchedTau2 = book<TH1F>("twoAllSubPartialMatchedJet_tau2", "tau2^{twoAllSubPartialMatched}", 50, 0, 1);
  GenTwoJetAllSubPartialMatchedTau3 = book<TH1F>("twoAllSubPartialMatchedJet_tau3", "tau3^{twoAllSubPartialMatched}", 50, 0, 1);

  GenTwoJetAllSubPartialMatchedTau2Tau1 = book<TH1F>("twoAllSubPartialMatchedJet_tau2tau1", "(tau2/tau1)^{twoAllSubPartialMatched}", 50, 0, 1);
  GenTwoJetAllSubPartialMatchedTau3Tau2 = book<TH1F>("twoAllSubPartialMatchedJet_tau3tau2", "(tau3/tau2)^{twoAllSubPartialMatched}", 50, 0, 1);
  GenTwoJetAllSubPartialMatchedTau3Tau1 = book<TH1F>("twoAllSubPartialMatchedJet_tau3tau1", "(tau3/tau1)^{twoAllSubPartialMatched}", 50, 0, 1);

  GenTwoJetAllSubOnlyThreeMatchedTau1 = book<TH1F>("twoAllSubOnlyThreeMatchedJet_tau1", "tau1^{twoAllSubOnlyThreeMatched}", 50, 0, 1);
  GenTwoJetAllSubOnlyThreeMatchedTau2 = book<TH1F>("twoAllSubOnlyThreeMatchedJet_tau2", "tau2^{twoAllSubOnlyThreeMatched}", 50, 0, 1);
  GenTwoJetAllSubOnlyThreeMatchedTau3 = book<TH1F>("twoAllSubOnlyThreeMatchedJet_tau3", "tau3^{twoAllSubOnlyThreeMatched}", 50, 0, 1);

  GenTwoJetAllSubOnlyThreeMatchedTau2Tau1 = book<TH1F>("twoAllSubOnlyThreeMatchedJet_tau2tau1", "(tau2/tau1)^{twoAllSubOnlyThreeMatched}", 50, 0, 1);
  GenTwoJetAllSubOnlyThreeMatchedTau3Tau2 = book<TH1F>("twoAllSubOnlyThreeMatchedJet_tau3tau2", "(tau3/tau2)^{twoAllSubOnlyThreeMatched}", 50, 0, 1);
  GenTwoJetAllSubOnlyThreeMatchedTau3Tau1 = book<TH1F>("twoAllSubOnlyThreeMatchedJet_tau3tau1", "(tau3/tau1)^{twoAllSubOnlyThreeMatched}", 50, 0, 1);

  GenTwoJetAllSubUnmatchedTau1 = book<TH1F>("twoAllSubUnmatchedJet_tau1", "tau1^{twoAllSubUnmatched}", 50, 0, 1);
  GenTwoJetAllSubUnmatchedTau2 = book<TH1F>("twoAllSubUnmatchedJet_tau2", "tau2^{twoAllSubUnmatched}", 50, 0, 1);
  GenTwoJetAllSubUnmatchedTau3 = book<TH1F>("twoAllSubUnmatchedJet_tau3", "tau3^{twoAllSubUnmatched}", 50, 0, 1);

  GenTwoJetAllSubUnmatchedTau2Tau1 = book<TH1F>("twoAllSubUnmatchedJet_tau2tau1", "(tau2/tau1)^{twoAllSubUnmatched}", 50, 0, 1);
  GenTwoJetAllSubUnmatchedTau3Tau2 = book<TH1F>("twoAllSubUnmatchedJet_tau3tau2", "(tau3/tau2)^{twoAllSubUnmatched}", 50, 0, 1);
  GenTwoJetAllSubUnmatchedTau3Tau1 = book<TH1F>("twoAllSubUnmatchedJet_tau3tau1", "(tau3/tau1)^{twoAllSubUnmatched}", 50, 0, 1);


  GenTwoJetAllSubAllMass = book<TH1F>("twoAllSubAllMass", "M_{twoAllSubAllMass}", n_massbins, min_m, max_m);
  GenTwoJetAllSubMatchedMass = book<TH1F>("twoAllSubMatchedMass", "M_{twoAllSubMatchedMass}", n_massbins, min_m, max_m);
  GenTwoJetAllSubPartialMatchedMass = book<TH1F>("twoAllSubPartialMatchedMass", "M_{twoAllSubPartialMatchedMass}", n_massbins, min_m, max_m);
  GenTwoJetAllSubNoneMatchedMass = book<TH1F>("twoAllSubNoneMatchedMass", "M_{twoAllSubNoneMatchedMass}", n_massbins, min_m, max_m);
  GenTwoJetAll4SubMatchedMass = book<TH1F>("twoAll4SubMatchedMass", "M_{twoAll4SubMatchedMass}", n_massbins, min_m, max_m);
  GenTwoJetAll4SubPartialMatchedMass = book<TH1F>("twoAll4SubPartialMatchedMass", "M_{twoAll4SubPartialMatchedMass}", n_massbins, min_m, max_m);
  GenTwoJetAllSubTau21MaxMass = book<TH1F>("twoAllSubTau21MaxMass", "M_{twoAllSubTau21MaxMass}", n_massbins, min_m, max_m);
  GenTwoJetAllSubMaxPTMass = book<TH1F>("twoAllSubMaxPTMass", "M_{twoAllSubMaxPTMass}", n_massbins, min_m, max_m);


  GenTwoJetAllTau1 = book<TH1F>("twoAllJet_tau1", "tau1^{twoAll}", 50, 0, 1);
  GenTwoJetAllTau2 = book<TH1F>("twoAllJet_tau2", "tau2^{twoAll}", 50, 0, 1);
  GenTwoJetAllTau3 = book<TH1F>("twoAllJet_tau3", "tau3^{twoAll}", 50, 0, 1);
  GenTwoJetAllTau4 = book<TH1F>("twoAllJet_tau4", "tau4^{twoAll}", 50, 0, 1);

  GenTwoJetAllTau2Tau1 = book<TH1F>("twoAllJet_tau2tau1", "(tau2/tau1)^{twoAll}", 50, 0, 1);
  GenTwoJetAllTau3Tau2 = book<TH1F>("twoAllJet_tau3tau2", "(tau3/tau2)^{twoAll}", 50, 0, 1);
  GenTwoJetAllTau3Tau1 = book<TH1F>("twoAllJet_tau3tau1", "(tau3/tau1)^{twoAll}", 50, 0, 1);
  GenTwoJetAllTau4Tau3 = book<TH1F>("twoAllJet_tau4tau3", "(tau4/tau3)^{twoAll}", 50, 0, 1);
  GenTwoJetAllTau4Tau2 = book<TH1F>("twoAllJet_tau4tau2", "(tau4/tau2)^{twoAll}", 50, 0, 1);
  GenTwoJetAllTau4Tau1 = book<TH1F>("twoAllJet_tau4tau1", "(tau4/tau1)^{twoAll}", 50, 0, 1);

  
  GenTwoJetAllSubMatchedSize = book<TH1F>("twoAllSubMatchedJet_size", "size_{twoAllSubMatched}", 50, 0, 7);
  GenTwoJetAllSubOneMatchedSize = book<TH1F>("twoAllSubOneMatchedJet_size", "size_{twoAllSubOneMatched}", 50, 0, 7);
  GenTwoJetAllSubTwoMatchedSize = book<TH1F>("twoAllSubTwoMatchedJet_size", "size_{twoAllSubTwoMatched}", 50, 0, 7);
  GenTwoJetAllSubUnmatchedSize = book<TH1F>("twoAllSubUnmatchedJet_size", "size_{twoAllSubUnmatched}", 50, 0, 7);
  GenTwoJetAll4SubMatchedSize = book<TH1F>("twoAll4SubMatchedJet_size", "size_{twoAll4SubMatched}", 50, 0, 7);
  GenTwoJetAll4SubPartialMatchedSize = book<TH1F>("twoAll4SubPartialMatchedJet_size", "size_{twoAll4SubPartialMatched}", 50, 0, 7);

  GenOneJetMassAllDRJet12 = book<TH2F>("M_oneJetAllDRJet12", "M_{oneJetAllDRJet12}", n_massbins, min_m, max_m, 80, 0, 4.0);
  GenTwoJetMassAllDRJet12 = book<TH2F>("M_twoJetAllDRJet12", "M_{twoJetAllDRJet12}", n_massbins, min_m, max_m, 80, 0, 4.0);

  GenJetMassSingleJet = book<TH1F>("singleJetMass", "M_{singleJet}", n_massbins, min_m, max_m);
  GenJetMassNearCombined = book<TH1F>("nearCombinedMass", "M_{nearCombined}", n_massbins, min_m, max_m);
  GenJetMassNear3SubCombined = book<TH1F>("near3SubCombinedMass", "M_{near3SubCombined}", n_massbins, min_m, max_m);
  GenJetMassNear4SubCombined = book<TH1F>("near4SubCombinedMass", "M_{near4SubCombined}", n_massbins, min_m, max_m);

  GenTwoJetAllSubPartialMatchedTau2Zero = book<TH1F>("twoAllSubPartialMatchedZeroJet_tau2", "tau2^{twoAllSubPartialMatchedZero}", 50, 0, 1);
  GenTwoJetAllSubMatchedMultipleSubjets = book<TH1F>("twoAllSubMatchedMultipleSubjetsJet", "M_{twoAllSubMatchedMultipleSubjets}", n_massbins, 0, max_m);


  GenTwoJetAllSubAllSubjet1pT = book<TH1F>("twoJetAllSubAllSubjet1pT", "(p_T)^{twoJetAllSubAllSubjet1}", 50, 0, 400);
  GenTwoJetAllSubAllSubjet2pT = book<TH1F>("twoJetAllSubAllSubjet2pT", "(p_T)^{twoJetAllSubAllSubjet2}", 50, 0, 400);
  GenTwoJetAllSubAllSubjet3pT = book<TH1F>("twoJetAllSubAllSubjet3pT", "(p_T)^{twoJetAllSubAllSubjet3}", 50, 0, 400);

  GenTwoJetAllSubMatchedSubjet1pT = book<TH1F>("twoJetAllSubMatchedSubjet1pT", "(p_T)^{twoJetAllSubMatchedSubjet1}", 50, 0, 400);
  GenTwoJetAllSubMatchedSubjet2pT = book<TH1F>("twoJetAllSubMatchedSubjet2pT", "(p_T)^{twoJetAllSubMatchedSubjet2}", 50, 0, 400);
  GenTwoJetAllSubMatchedSubjet3pT = book<TH1F>("twoJetAllSubMatchedSubjet3pT", "(p_T)^{twoJetAllSubMatchedSubjet3}", 50, 0, 400);

  GenTwoJetAllSubPartialMatchedSubjet1pT = book<TH1F>("twoJetAllSubPartialMatchedSubjet1pT", "(p_T)^{twoJetAllSubPartialMatchedSubjet1}", 50, 0, 400);
  GenTwoJetAllSubPartialMatchedSubjet2pT = book<TH1F>("twoJetAllSubPartialMatchedSubjet2pT", "(p_T)^{twoJetAllSubPartialMatchedSubjet2}", 50, 0, 400);
  GenTwoJetAllSubPartialMatchedSubjet3pT = book<TH1F>("twoJetAllSubPartialMatchedSubjet3pT", "(p_T)^{twoJetAllSubPartialMatchedSubjet3}", 50, 0, 400);

  GenTwoJetAllSubAllDR12 = book<TH1F>("twoJetAllSubAllDR12", "(DR12)^{twoJetAllSubAll}", 50, 0, 4);
  GenTwoJetAllSubAllDR23 = book<TH1F>("twoJetAllSubAllDR23", "(DR23)^{twoJetAllSubAll}", 50, 0, 4);
  GenTwoJetAllSubAllDR31 = book<TH1F>("twoJetAllSubAllDR31", "(DR31)^{twoJetAllSubAll}", 50, 0, 4);

  GenTwoJetAllSubMatchedDR12 = book<TH1F>("twoJetAllSubMatchedDR12", "(DR12)^{twoJetAllSubMatched}", 50, 0, 4);
  GenTwoJetAllSubMatchedDR23 = book<TH1F>("twoJetAllSubMatchedDR23", "(DR23)^{twoJetAllSubMatched}", 50, 0, 4);
  GenTwoJetAllSubMatchedDR31 = book<TH1F>("twoJetAllSubMatchedDR31", "(DR31)^{twoJetAllSubMatched}", 50, 0, 4);

  GenTwoJetAllSubPartialMatchedDR12 = book<TH1F>("twoJetAllSubPartialMatchedDR12", "(DR12)^{twoJetAllSubPartialMatched}", 50, 0, 4);
  GenTwoJetAllSubPartialMatchedDR23 = book<TH1F>("twoJetAllSubPartialMatchedDR23", "(DR23)^{twoJetAllSubPartialMatched}", 50, 0, 4);
  GenTwoJetAllSubPartialMatchedDR31 = book<TH1F>("twoJetAllSubPartialMatchedDR31", "(DR31)^{twoJetAllSubPartialMatched}", 50, 0, 4);

  GenTwoJetAllSubAllDR1Axis = book<TH1F>("twoJetAllSubAllDR1Axis", "(DR1Axis)^{twoJetAllSubAll}", 50, 0, 4);
  GenTwoJetAllSubAllDR2Axis = book<TH1F>("twoJetAllSubAllDR2Axis", "(DR2Axis)^{twoJetAllSubAll}", 50, 0, 4);
  GenTwoJetAllSubAllDR3Axis = book<TH1F>("twoJetAllSubAllDR3Axis", "(DR3Axis)^{twoJetAllSubAll}", 50, 0, 4);

  GenTwoJetAllSubMatchedDR1Axis = book<TH1F>("twoJetAllSubMatchedDR1Axis", "(DR1Axis)^{twoJetAllSubMatched}", 50, 0, 4);
  GenTwoJetAllSubMatchedDR2Axis = book<TH1F>("twoJetAllSubMatchedDR2Axis", "(DR2Axis)^{twoJetAllSubMatched}", 50, 0, 4);
  GenTwoJetAllSubMatchedDR3Axis = book<TH1F>("twoJetAllSubMatchedDR3Axis", "(DR3Axis)^{twoJetAllSubMatched}", 50, 0, 4);

  GenTwoJetAllSubPartialMatchedDR1Axis = book<TH1F>("twoJetAllSubPartialMatchedDR1Axis", "(DR1Axis)^{twoJetAllSubPartialMatched}", 50, 0, 4);
  GenTwoJetAllSubPartialMatchedDR2Axis = book<TH1F>("twoJetAllSubPartialMatchedDR2Axis", "(DR2Axis)^{twoJetAllSubPartialMatched}", 50, 0, 4);
  GenTwoJetAllSubPartialMatchedDR3Axis = book<TH1F>("twoJetAllSubPartialMatchedDR3Axis", "(DR3Axis)^{twoJetAllSubPartialMatched}", 50, 0, 4);

  GenTwoJetAllSubAllDRAxisMinMax = book<TH2F>("twoJetAllSubAllDRAxisMinMax", "SubAllDRAxisMinMax", 80, 0, 4.0, 80, 0, 4.0);
  GenTwoJetAllSubMatchedDRAxisMinMax = book<TH2F>("twoJetAllSubMatchedDRAxisMinMax", "SubMatchedDRAxisMinMax", 80, 0, 4.0, 80, 0, 4.0);
  GenTwoJetAllSubPartialMatchedDRAxisMinMax = book<TH2F>("twoJetAllSubPartialMatchedDRAxisMinMax", "SubPartialMatchedDRAxisMinMax", 80, 0, 4.0, 80, 0, 4.0);
  GenTwoJetAllSubUnmatchedDRAxisMinMax = book<TH2F>("twoJetAllSubUnmatchedDRAxisMinMax", "SubUnmatchedDRAxisMinMax", 80, 0, 4.0, 80, 0, 4.0);

  GenTwoJetAllSubjet1pT = book<TH1F>("twoJetAllSubjet1pT", "(p_T)^{twoJetAllSubjet1}", 50, 0, 400);
  GenTwoJetAllSubjet2pT = book<TH1F>("twoJetAllSubjet2pT", "(p_T)^{twoJetAllSubjet2}", 50, 0, 400);
  GenTwoJetAllSubjet3pT = book<TH1F>("twoJetAllSubjet3pT", "(p_T)^{twoJetAllSubjet3}", 50, 0, 400);
  GenTwoJetAllSubjet4pT = book<TH1F>("twoJetAllSubjet4pT", "(p_T)^{twoJetAllSubjet4}", 50, 0, 400);
  GenTwoJetAllSubjet5pT = book<TH1F>("twoJetAllSubjet5pT", "(p_T)^{twoJetAllSubjet5}", 50, 0, 400);
  GenTwoJetAllSubjet6pT = book<TH1F>("twoJetAllSubjet6pT", "(p_T)^{twoJetAllSubjet6}", 50, 0, 400);

  GenTwoJetBotSubjetpT = book<TH1F>("twoJetBotSubjetpT", "(p_T)^{twoJetBotSubjet}", 50, 0, 400);
  GenTwoJetLightQ1SubjetpT = book<TH1F>("twoJetLightQ1SubjetpT", "(p_T)^{twoJetLightQ1Subjet}", 50, 0, 400);
  GenTwoJetLightQ2SubjetpT = book<TH1F>("twoJetLightQ2SubjetpT", "(p_T)^{twoJetLightQ2Subjet}", 50, 0, 400);
  GenTwoJetLightQCombinedSubjetpT = book<TH1F>("twoJetLightQCombinedSubjetpT", "(p_T)^{twoJetLightQCombinedSubjet}", 50, 0, 400);
  GenTwoJetMultipleQSubjetpT = book<TH1F>("twoJetMultipleQSubjetpT", "(p_T)^{twoJetMultipleQSubjet}", 50, 0, 400);


  GenJetMassTau21CutLower = book<TH1F>("M_jet_MassTau21CutLower", "M_{jetTau21CutLower}", n_massbins, 0, max_m);
  GenJetMassTau21CutLowerTop = book<TH1F>("M_jet_MassTau21CutLowerTop", "M_{jetTau21CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassTau21CutLowerGluon = book<TH1F>("M_jet_MassTau21CutLowerGluon", "M_{jetTau21CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassTau21CutHigher = book<TH1F>("M_jet_MassTau21CutHigher", "M_{jetTau21CutHigher}", n_massbins, 0, max_m);
  GenJetMassTau21CutHigherTop = book<TH1F>("M_jet_MassTau21CutHigherTop", "M_{jetTau21CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassTau21CutHigherGluon = book<TH1F>("M_jet_MassTau21CutHigherGluon", "M_{jetTau21CutHigherGluon}", n_massbins, 0, max_m);

  GenJetMassTau31CutLower = book<TH1F>("M_jet_MassTau31CutLower", "M_{jetTau31CutLower}", n_massbins, 0, max_m);
  GenJetMassTau31CutLowerTop = book<TH1F>("M_jet_MassTau31CutLowerTop", "M_{jetTau31CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassTau31CutLowerGluon = book<TH1F>("M_jet_MassTau31CutLowerGluon", "M_{jetTau31CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassTau31CutHigher = book<TH1F>("M_jet_MassTau31CutHigher", "M_{jetTau31CutHigher}", n_massbins, 0, max_m);
  GenJetMassTau31CutHigherTop = book<TH1F>("M_jet_MassTau31CutHigherTop", "M_{jetTau31CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassTau31CutHigherGluon = book<TH1F>("M_jet_MassTau31CutHigherGluon", "M_{jetTau31CutHigherGluon}", n_massbins, 0, max_m);

  GenJetMassTau32CutLower = book<TH1F>("M_jet_MassTau32CutLower", "M_{jetTau32CutLower}", n_massbins, 0, max_m);
  GenJetMassTau32CutLowerTop = book<TH1F>("M_jet_MassTau32CutLowerTop", "M_{jetTau32CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassTau32CutLowerGluon = book<TH1F>("M_jet_MassTau32CutLowerGluon", "M_{jetTau32CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassTau32CutHigher = book<TH1F>("M_jet_MassTau32CutHigher", "M_{jetTau32CutHigher}", n_massbins, 0, max_m);
  GenJetMassTau32CutHigherTop = book<TH1F>("M_jet_MassTau32CutHigherTop", "M_{jetTau32CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassTau32CutHigherGluon = book<TH1F>("M_jet_MassTau32CutHigherGluon", "M_{jetTau32CutHigherGluon}", n_massbins, 0, max_m);

  GenJetMassTau41CutLower = book<TH1F>("M_jet_MassTau41CutLower", "M_{jetTau41CutLower}", n_massbins, 0, max_m);
  GenJetMassTau41CutLowerTop = book<TH1F>("M_jet_MassTau41CutLowerTop", "M_{jetTau41CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassTau41CutLowerGluon = book<TH1F>("M_jet_MassTau41CutLowerGluon", "M_{jetTau41CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassTau41CutHigher = book<TH1F>("M_jet_MassTau41CutHigher", "M_{jetTau41CutHigher}", n_massbins, 0, max_m);
  GenJetMassTau41CutHigherTop = book<TH1F>("M_jet_MassTau41CutHigherTop", "M_{jetTau41CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassTau41CutHigherGluon = book<TH1F>("M_jet_MassTau41CutHigherGluon", "M_{jetTau41CutHigherGluon}", n_massbins, 0, max_m);

  GenJetMassTau42CutLower = book<TH1F>("M_jet_MassTau42CutLower", "M_{jetTau42CutLower}", n_massbins, 0, max_m);
  GenJetMassTau42CutLowerTop = book<TH1F>("M_jet_MassTau42CutLowerTop", "M_{jetTau42CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassTau42CutLowerGluon = book<TH1F>("M_jet_MassTau42CutLowerGluon", "M_{jetTau42CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassTau42CutHigher = book<TH1F>("M_jet_MassTau42CutHigher", "M_{jetTau42CutHigher}", n_massbins, 0, max_m);
  GenJetMassTau42CutHigherTop = book<TH1F>("M_jet_MassTau42CutHigherTop", "M_{jetTau42CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassTau42CutHigherGluon = book<TH1F>("M_jet_MassTau42CutHigherGluon", "M_{jetTau42CutHigherGluon}", n_massbins, 0, max_m);


  GenJetMassCombinedTau21CutLower = book<TH1F>("M_jet_MassCombinedTau21CutLower", "M_{jetCombinedTau21CutLower}", n_massbins, 0, max_m);
  GenJetMassCombinedTau21CutLowerTop = book<TH1F>("M_jet_MassCombinedTau21CutLowerTop", "M_{jetCombinedTau21CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassCombinedTau21CutLowerGluon = book<TH1F>("M_jet_MassCombinedTau21CutLowerGluon", "M_{jetCombinedTau21CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassCombinedTau21CutHigher = book<TH1F>("M_jet_MassCombinedTau21CutHigher", "M_{jetCombinedTau21CutHigher}", n_massbins, 0, max_m);
  GenJetMassCombinedTau21CutHigherTop = book<TH1F>("M_jet_MassCombinedTau21CutHigherTop", "M_{jetCombinedTau21CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassCombinedTau21CutHigherGluon = book<TH1F>("M_jet_MassCombinedTau21CutHigherGluon", "M_{jetCombinedTau21CutHigherGluon}", n_massbins, 0, max_m);

  GenJetMassCombinedTau31CutLower = book<TH1F>("M_jet_MassCombinedTau31CutLower", "M_{jetCombinedTau31CutLower}", n_massbins, 0, max_m);
  GenJetMassCombinedTau31CutLowerTop = book<TH1F>("M_jet_MassCombinedTau31CutLowerTop", "M_{jetCombinedTau31CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassCombinedTau31CutLowerGluon = book<TH1F>("M_jet_MassCombinedTau31CutLowerGluon", "M_{jetCombinedTau31CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassCombinedTau31CutHigher = book<TH1F>("M_jet_MassCombinedTau31CutHigher", "M_{jetCombinedTau31CutHigher}", n_massbins, 0, max_m);
  GenJetMassCombinedTau31CutHigherTop = book<TH1F>("M_jet_MassCombinedTau31CutHigherTop", "M_{jetCombinedTau31CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassCombinedTau31CutHigherGluon = book<TH1F>("M_jet_MassCombinedTau31CutHigherGluon", "M_{jetCombinedTau31CutHigherGluon}", n_massbins, 0, max_m);

  GenJetMassCombinedTau32CutLower = book<TH1F>("M_jet_MassCombinedTau32CutLower", "M_{jetCombinedTau32CutLower}", n_massbins, 0, max_m);
  GenJetMassCombinedTau32CutLowerTop = book<TH1F>("M_jet_MassCombinedTau32CutLowerTop", "M_{jetCombinedTau32CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassCombinedTau32CutLowerGluon = book<TH1F>("M_jet_MassCombinedTau32CutLowerGluon", "M_{jetCombinedTau32CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassCombinedTau32CutHigher = book<TH1F>("M_jet_MassCombinedTau32CutHigher", "M_{jetCombinedTau32CutHigher}", n_massbins, 0, max_m);
  GenJetMassCombinedTau32CutHigherTop = book<TH1F>("M_jet_MassCombinedTau32CutHigherTop", "M_{jetCombinedTau32CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassCombinedTau32CutHigherGluon = book<TH1F>("M_jet_MassCombinedTau32CutHigherGluon", "M_{jetCombinedTau32CutHigherGluon}", n_massbins, 0, max_m);

  GenJetMassCombinedTau41CutLower = book<TH1F>("M_jet_MassCombinedTau41CutLower", "M_{jetCombinedTau41CutLower}", n_massbins, 0, max_m);
  GenJetMassCombinedTau41CutLowerTop = book<TH1F>("M_jet_MassCombinedTau41CutLowerTop", "M_{jetCombinedTau41CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassCombinedTau41CutLowerGluon = book<TH1F>("M_jet_MassCombinedTau41CutLowerGluon", "M_{jetCombinedTau41CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassCombinedTau41CutHigher = book<TH1F>("M_jet_MassCombinedTau41CutHigher", "M_{jetCombinedTau41CutHigher}", n_massbins, 0, max_m);
  GenJetMassCombinedTau41CutHigherTop = book<TH1F>("M_jet_MassCombinedTau41CutHigherTop", "M_{jetCombinedTau41CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassCombinedTau41CutHigherGluon = book<TH1F>("M_jet_MassCombinedTau41CutHigherGluon", "M_{jetCombinedTau41CutHigherGluon}", n_massbins, 0, max_m);

  GenJetMassCombinedTau42CutLower = book<TH1F>("M_jet_MassCombinedTau42CutLower", "M_{jetCombinedTau42CutLower}", n_massbins, 0, max_m);
  GenJetMassCombinedTau42CutLowerTop = book<TH1F>("M_jet_MassCombinedTau42CutLowerTop", "M_{jetCombinedTau42CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassCombinedTau42CutLowerGluon = book<TH1F>("M_jet_MassCombinedTau42CutLowerGluon", "M_{jetCombinedTau42CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassCombinedTau42CutHigher = book<TH1F>("M_jet_MassCombinedTau42CutHigher", "M_{jetCombinedTau42CutHigher}", n_massbins, 0, max_m);
  GenJetMassCombinedTau42CutHigherTop = book<TH1F>("M_jet_MassCombinedTau42CutHigherTop", "M_{jetCombinedTau42CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassCombinedTau42CutHigherGluon = book<TH1F>("M_jet_MassCombinedTau42CutHigherGluon", "M_{jetCombinedTau42CutHigherGluon}", n_massbins, 0, max_m);


  GenJetMassNoCombinedTau21CutLower = book<TH1F>("M_jet_MassNoCombinedTau21CutLower", "M_{jetNoCombinedTau21CutLower}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau21CutLowerTop = book<TH1F>("M_jet_MassNoCombinedTau21CutLowerTop", "M_{jetNoCombinedTau21CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau21CutLowerGluon = book<TH1F>("M_jet_MassNoCombinedTau21CutLowerGluon", "M_{jetNoCombinedTau21CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau21CutHigher = book<TH1F>("M_jet_MassNoCombinedTau21CutHigher", "M_{jetNoCombinedTau21CutHigher}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau21CutHigherTop = book<TH1F>("M_jet_MassNoCombinedTau21CutHigherTop", "M_{jetNoCombinedTau21CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau21CutHigherGluon = book<TH1F>("M_jet_MassNoCombinedTau21CutHigherGluon", "M_{jetNoCombinedTau21CutHigherGluon}", n_massbins, 0, max_m);

  GenJetMassNoCombinedTau31CutLower = book<TH1F>("M_jet_MassNoCombinedTau31CutLower", "M_{jetNoCombinedTau31CutLower}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau31CutLowerTop = book<TH1F>("M_jet_MassNoCombinedTau31CutLowerTop", "M_{jetNoCombinedTau31CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau31CutLowerGluon = book<TH1F>("M_jet_MassNoCombinedTau31CutLowerGluon", "M_{jetNoCombinedTau31CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau31CutHigher = book<TH1F>("M_jet_MassNoCombinedTau31CutHigher", "M_{jetNoCombinedTau31CutHigher}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau31CutHigherTop = book<TH1F>("M_jet_MassNoCombinedTau31CutHigherTop", "M_{jetNoCombinedTau31CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau31CutHigherGluon = book<TH1F>("M_jet_MassNoCombinedTau31CutHigherGluon", "M_{jetNoCombinedTau31CutHigherGluon}", n_massbins, 0, max_m);

  GenJetMassNoCombinedTau32CutLower = book<TH1F>("M_jet_MassNoCombinedTau32CutLower", "M_{jetNoCombinedTau32CutLower}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau32CutLowerTop = book<TH1F>("M_jet_MassNoCombinedTau32CutLowerTop", "M_{jetNoCombinedTau32CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau32CutLowerGluon = book<TH1F>("M_jet_MassNoCombinedTau32CutLowerGluon", "M_{jetNoCombinedTau32CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau32CutHigher = book<TH1F>("M_jet_MassNoCombinedTau32CutHigher", "M_{jetNoCombinedTau32CutHigher}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau32CutHigherTop = book<TH1F>("M_jet_MassNoCombinedTau32CutHigherTop", "M_{jetNoCombinedTau32CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau32CutHigherGluon = book<TH1F>("M_jet_MassNoCombinedTau32CutHigherGluon", "M_{jetNoCombinedTau32CutHigherGluon}", n_massbins, 0, max_m);

  GenJetMassNoCombinedTau41CutLower = book<TH1F>("M_jet_MassNoCombinedTau41CutLower", "M_{jetNoCombinedTau41CutLower}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau41CutLowerTop = book<TH1F>("M_jet_MassNoCombinedTau41CutLowerTop", "M_{jetNoCombinedTau41CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau41CutLowerGluon = book<TH1F>("M_jet_MassNoCombinedTau41CutLowerGluon", "M_{jetNoCombinedTau41CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau41CutHigher = book<TH1F>("M_jet_MassNoCombinedTau41CutHigher", "M_{jetNoCombinedTau41CutHigher}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau41CutHigherTop = book<TH1F>("M_jet_MassNoCombinedTau41CutHigherTop", "M_{jetNoCombinedTau41CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau41CutHigherGluon = book<TH1F>("M_jet_MassNoCombinedTau41CutHigherGluon", "M_{jetNoCombinedTau41CutHigherGluon}", n_massbins, 0, max_m);

  GenJetMassNoCombinedTau42CutLower = book<TH1F>("M_jet_MassNoCombinedTau42CutLower", "M_{jetNoCombinedTau42CutLower}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau42CutLowerTop = book<TH1F>("M_jet_MassNoCombinedTau42CutLowerTop", "M_{jetNoCombinedTau42CutLowerTop}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau42CutLowerGluon = book<TH1F>("M_jet_MassNoCombinedTau42CutLowerGluon", "M_{jetNoCombinedTau42CutLowerGluon}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau42CutHigher = book<TH1F>("M_jet_MassNoCombinedTau42CutHigher", "M_{jetNoCombinedTau42CutHigher}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau42CutHigherTop = book<TH1F>("M_jet_MassNoCombinedTau42CutHigherTop", "M_{jetNoCombinedTau42CutHigherTop}", n_massbins, 0, max_m);
  GenJetMassNoCombinedTau42CutHigherGluon = book<TH1F>("M_jet_MassNoCombinedTau42CutHigherGluon", "M_{jetNoCombinedTau42CutHigherGluon}", n_massbins, 0, max_m);

  GenJetNumber = book<TH1F>("N_Jets", "N_{Jets}", 5, 0, 4);

  // handle for TTbarGen class
  h_ttbargen=ctx.get_handle<TTbarGen>("ttbargen");
  // handle for clustered jets
  h_jets=ctx.get_handle<std::vector<GenTopJet>>(jetname);

  dR_ = dR;
  combine = new CombineXCone();

  debug = string2bool(ctx.get("Debug","false"));
}
/*
void createSubjetQuarkDeltaRMatrix(std::vector<GenJet> subjets, std::vector<GenParticle> quarks, std::vector<std::vector<double>>* matrix) {
  unsigned int nSubjets = subjets.size();
  unsigned int nQuarks = quarks.size();

  for(unsigned int i=0; i<nSubjets; i++) {
    for(unsigned int j=0; j<nQuarks; j++) {
      matrix->at(0).at(j) = deltaR(subjets.at(i), quarks.at(j));
    }
  }
}

int nearestSubjet(GenParticle q, std::vector<GenJet> subjets) {
  double minR = 100;
  int minIndex = -1;

  for(unsigned int i=0; i<subjets.size(); i++) {
    double tmpR = deltaR(q, subjets.at(i));
    if(printOut3) cout << tmpR << ", ";
    if(tmpR < minR) {
      minR = tmpR;
      minIndex = i;
    }
  }
  if(printOut3) cout << endl;

  return minIndex;
}
*/
bool GenHists_GenNoLep::subjetMatching(std::vector<GenJet> subjets, std::vector<GenParticle> quarks, unsigned int* remaining_quarks, bool unique, std::vector<int>* subjetIndices) {
  
  bool matched = true;
  for(unsigned int i=0; i<subjets.size(); i++) {

    double minR = 100;
    int j_remove = -1;

    if(printOut3) cout << "subjet " << i << ": ";

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

    //if(v) cout << "minR = " << minR << ", j_remove = " << j_remove << endl;

  }

  if(remaining_quarks != nullptr) {
    *remaining_quarks = quarks.size();

    if(printOut3) cout << ", remaining quarks = " << *remaining_quarks << endl;
  }
  return matched;
}

//"gluons" might not be exclusively gluons
vector<GenParticle> gluonsInEvent(const Event & event) {
  std::vector<GenParticle> *genparticles = event.genparticles;
  int nparts = genparticles->size();
  
  vector<GenParticle> gluons;
  //look for outgoing gluons in jet
  for(int i=0; i<nparts; ++i) {
    GenParticle* p = &(genparticles->at(i));

    auto mother1 = p->mother(genparticles,1);
    auto mother2 = p->mother(genparticles,2);

    if(mother1 != nullptr && mother2 != nullptr) {
      if(abs(p->pdgId()) != 6 && mother1->status() == 21 && mother2->status() == 21) {
        if(p->pt() > 20) gluons.push_back(*p);
      }
    }
  }

  return gluons;
}

bool compareSubjetPt(TLorentzVector subjet1, TLorentzVector subjet2) {
  return subjet1.Pt()>subjet2.Pt();
}

bool compareSubjetPtGenJet(GenJet subjet1, GenJet subjet2) {
  return subjet1.pt()>subjet2.pt();
}

bool compareSubjetM(TLorentzVector subjet1, TLorentzVector subjet2) {
  return subjet1.M()>subjet2.M();
}

bool compareJetPt(TLorentzVector jet1, TLorentzVector jet2) {
  return jet1.Pt()<jet2.Pt();
}
/*
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

void calculateNSubjettines(GenTopJet* topJet, std::vector<GenJet> subjets) {
  std::vector<fastjet::PseudoJet> pfpart_psj;
  int user_index = 0;

  // convert PFParticles to PseudoJets
  // Hier würdest du dann nicht über die particles sondern über die 6 subjets loopen
  for(const auto & cand: subjets) {
    fastjet::PseudoJet tmp_psj = fastjet::PseudoJet(cand.v4().px(), cand.v4().py(), cand.v4().pz(), cand.v4().energy());
    tmp_psj.set_user_index(user_index);
    pfpart_psj.push_back(tmp_psj);
    user_index++;
  }

  // So baut man aus den pseudojets dann einen jet, der die pseudojets als constituents hinzufügt
  fastjet::PseudoJet jet = join(pfpart_psj);
  std::vector<float> taus;
  for(int n=1; n<5; n++) {
    fastjet::contrib::Nsubjettiness nSub(n, fastjet::contrib::OnePass_KT_Axes(), fastjet::contrib::NormalizedMeasure(1.0, 0.8)); // beta = 1.0, R0 = 0.8
    taus.push_back(nSub(jet));
  }

  topJet->set_tau1(taus.at(0));
  topJet->set_tau2(taus.at(1));
  topJet->set_tau3(taus.at(2));
  topJet->set_tau4(taus.at(3));
}

void fillTauHists(std::vector<TH1F*> hists, GenTopJet jet, double genweight) {

  hists.at(0)->Fill(jet.tau1(), genweight);
  hists.at(1)->Fill(jet.tau2(), genweight);
  hists.at(2)->Fill(jet.tau3(), genweight);
  hists.at(3)->Fill(jet.tau4(), genweight);

  if(jet.tau1() != 0) hists.at(4)->Fill(jet.tau2()/jet.tau1(), genweight);
  if(jet.tau2() != 0) hists.at(5)->Fill(jet.tau3()/jet.tau2(), genweight);
  if(jet.tau1() != 0) hists.at(6)->Fill(jet.tau3()/jet.tau1(), genweight);
  if(jet.tau3() != 0) hists.at(7)->Fill(jet.tau4()/jet.tau3(), genweight);
  if(jet.tau2() != 0) hists.at(8)->Fill(jet.tau4()/jet.tau2(), genweight);
  if(jet.tau1() != 0) hists.at(9)->Fill(jet.tau4()/jet.tau1(), genweight);

}

void GenHists_GenNoLep::fillTauHistsSubjets(std::vector<TH1F*> hists, GenTopJet jet, double genweight) {
  
  if(debug) cout << "\t\t--- filling SubjetHists" << endl;
  hists.at(0)->Fill(jet.tau1(), genweight);
  hists.at(1)->Fill(jet.tau2(), genweight);
  hists.at(2)->Fill(jet.tau3(), genweight);

  if(jet.tau1() != 0) hists.at(3)->Fill(jet.tau2()/jet.tau1(), genweight);
  if(jet.tau2() != 0) hists.at(4)->Fill(jet.tau3()/jet.tau2(), genweight);
  if(jet.tau1() != 0) hists.at(5)->Fill(jet.tau3()/jet.tau1(), genweight);

}

void GenHists_GenNoLep::fillAllTauHistsSubjets(std::vector<GenJet> combinedSubjets, double genweight) {

  std::vector<GenJet> tmp1234Subjets = {combinedSubjets.at(0), combinedSubjets.at(1), combinedSubjets.at(2), combinedSubjets.at(3)};
  GenTopJet tmpJet1234;
  calculateNSubjettines(&tmpJet1234, tmp1234Subjets);
  std::vector<TH1F*> GenTwoJetAllSub1234Taus = {GenTwoJetAllSub1234Tau1, GenTwoJetAllSub1234Tau2, GenTwoJetAllSub1234Tau3, GenTwoJetAllSub1234Tau2Tau1, GenTwoJetAllSub1234Tau3Tau2, GenTwoJetAllSub1234Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub1234Taus, tmpJet1234, genweight);

  std::vector<GenJet> tmp1235Subjets = {combinedSubjets.at(0), combinedSubjets.at(1), combinedSubjets.at(2), combinedSubjets.at(4)};
  GenTopJet tmpJet1235;
  calculateNSubjettines(&tmpJet1235, tmp1235Subjets);
  std::vector<TH1F*> GenTwoJetAllSub1235Taus = {GenTwoJetAllSub1235Tau1, GenTwoJetAllSub1235Tau2, GenTwoJetAllSub1235Tau3, GenTwoJetAllSub1235Tau2Tau1, GenTwoJetAllSub1235Tau3Tau2, GenTwoJetAllSub1235Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub1235Taus, tmpJet1235, genweight);

  std::vector<GenJet> tmp1236Subjets = {combinedSubjets.at(0), combinedSubjets.at(1), combinedSubjets.at(2), combinedSubjets.at(5)};
  GenTopJet tmpJet1236;
  calculateNSubjettines(&tmpJet1236, tmp1236Subjets);
  std::vector<TH1F*> GenTwoJetAllSub1236Taus = {GenTwoJetAllSub1236Tau1, GenTwoJetAllSub1236Tau2, GenTwoJetAllSub1236Tau3, GenTwoJetAllSub1236Tau2Tau1, GenTwoJetAllSub1236Tau3Tau2, GenTwoJetAllSub1236Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub1236Taus, tmpJet1236, genweight);

  std::vector<GenJet> tmp1245Subjets = {combinedSubjets.at(0), combinedSubjets.at(1), combinedSubjets.at(3), combinedSubjets.at(4)};
  GenTopJet tmpJet1245;
  calculateNSubjettines(&tmpJet1245, tmp1245Subjets);
  std::vector<TH1F*> GenTwoJetAllSub1245Taus = {GenTwoJetAllSub1245Tau1, GenTwoJetAllSub1245Tau2, GenTwoJetAllSub1245Tau3, GenTwoJetAllSub1245Tau2Tau1, GenTwoJetAllSub1245Tau3Tau2, GenTwoJetAllSub1245Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub1245Taus, tmpJet1245, genweight);

  std::vector<GenJet> tmp1246Subjets = {combinedSubjets.at(0), combinedSubjets.at(1), combinedSubjets.at(3), combinedSubjets.at(5)};
  GenTopJet tmpJet1246;
  calculateNSubjettines(&tmpJet1246, tmp1246Subjets);
  std::vector<TH1F*> GenTwoJetAllSub1246Taus = {GenTwoJetAllSub1246Tau1, GenTwoJetAllSub1246Tau2, GenTwoJetAllSub1246Tau3, GenTwoJetAllSub1246Tau2Tau1, GenTwoJetAllSub1246Tau3Tau2, GenTwoJetAllSub1246Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub1246Taus, tmpJet1246, genweight);

  std::vector<GenJet> tmp1256Subjets = {combinedSubjets.at(0), combinedSubjets.at(1), combinedSubjets.at(4), combinedSubjets.at(5)};
  GenTopJet tmpJet1256;
  calculateNSubjettines(&tmpJet1256, tmp1256Subjets);
  std::vector<TH1F*> GenTwoJetAllSub1256Taus = {GenTwoJetAllSub1256Tau1, GenTwoJetAllSub1256Tau2, GenTwoJetAllSub1256Tau3, GenTwoJetAllSub1256Tau2Tau1, GenTwoJetAllSub1256Tau3Tau2, GenTwoJetAllSub1256Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub1256Taus, tmpJet1256, genweight);

  std::vector<GenJet> tmp1345Subjets = {combinedSubjets.at(0), combinedSubjets.at(2), combinedSubjets.at(3), combinedSubjets.at(4)};
  GenTopJet tmpJet1345;
  calculateNSubjettines(&tmpJet1345, tmp1345Subjets);
  std::vector<TH1F*> GenTwoJetAllSub1345Taus = {GenTwoJetAllSub1345Tau1, GenTwoJetAllSub1345Tau2, GenTwoJetAllSub1345Tau3, GenTwoJetAllSub1345Tau2Tau1, GenTwoJetAllSub1345Tau3Tau2, GenTwoJetAllSub1345Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub1345Taus, tmpJet1345, genweight);

  std::vector<GenJet> tmp1346Subjets = {combinedSubjets.at(0), combinedSubjets.at(2), combinedSubjets.at(3), combinedSubjets.at(5)};
  GenTopJet tmpJet1346;
  calculateNSubjettines(&tmpJet1346, tmp1346Subjets);
  std::vector<TH1F*> GenTwoJetAllSub1346Taus = {GenTwoJetAllSub1346Tau1, GenTwoJetAllSub1346Tau2, GenTwoJetAllSub1346Tau3, GenTwoJetAllSub1346Tau2Tau1, GenTwoJetAllSub1346Tau3Tau2, GenTwoJetAllSub1346Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub1346Taus, tmpJet1346, genweight);

  std::vector<GenJet> tmp1356Subjets = {combinedSubjets.at(0), combinedSubjets.at(2), combinedSubjets.at(4), combinedSubjets.at(5)};
  GenTopJet tmpJet1356;
  calculateNSubjettines(&tmpJet1356, tmp1356Subjets);
  std::vector<TH1F*> GenTwoJetAllSub1356Taus = {GenTwoJetAllSub1356Tau1, GenTwoJetAllSub1356Tau2, GenTwoJetAllSub1356Tau3, GenTwoJetAllSub1356Tau2Tau1, GenTwoJetAllSub1356Tau3Tau2, GenTwoJetAllSub1356Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub1356Taus, tmpJet1356, genweight);

  std::vector<GenJet> tmp1456Subjets = {combinedSubjets.at(0), combinedSubjets.at(3), combinedSubjets.at(4), combinedSubjets.at(5)};
  GenTopJet tmpJet1456;
  calculateNSubjettines(&tmpJet1456, tmp1456Subjets);
  std::vector<TH1F*> GenTwoJetAllSub1456Taus = {GenTwoJetAllSub1456Tau1, GenTwoJetAllSub1456Tau2, GenTwoJetAllSub1456Tau3, GenTwoJetAllSub1456Tau2Tau1, GenTwoJetAllSub1456Tau3Tau2, GenTwoJetAllSub1456Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub1456Taus, tmpJet1456, genweight);

  std::vector<GenJet> tmp2345Subjets = {combinedSubjets.at(1), combinedSubjets.at(2), combinedSubjets.at(3), combinedSubjets.at(4)};
  GenTopJet tmpJet2345;
  calculateNSubjettines(&tmpJet2345, tmp2345Subjets);
  std::vector<TH1F*> GenTwoJetAllSub2345Taus = {GenTwoJetAllSub2345Tau1, GenTwoJetAllSub2345Tau2, GenTwoJetAllSub2345Tau3, GenTwoJetAllSub2345Tau2Tau1, GenTwoJetAllSub2345Tau3Tau2, GenTwoJetAllSub2345Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub2345Taus, tmpJet2345, genweight);

  std::vector<GenJet> tmp2346Subjets = {combinedSubjets.at(1), combinedSubjets.at(2), combinedSubjets.at(3), combinedSubjets.at(5)};
  GenTopJet tmpJet2346;
  calculateNSubjettines(&tmpJet2346, tmp2346Subjets);
  std::vector<TH1F*> GenTwoJetAllSub2346Taus = {GenTwoJetAllSub2346Tau1, GenTwoJetAllSub2346Tau2, GenTwoJetAllSub2346Tau3, GenTwoJetAllSub2346Tau2Tau1, GenTwoJetAllSub2346Tau3Tau2, GenTwoJetAllSub2346Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub2346Taus, tmpJet2346, genweight);

  std::vector<GenJet> tmp2356Subjets = {combinedSubjets.at(1), combinedSubjets.at(2), combinedSubjets.at(4), combinedSubjets.at(5)};
  GenTopJet tmpJet2356;
  calculateNSubjettines(&tmpJet2356, tmp2356Subjets);
  std::vector<TH1F*> GenTwoJetAllSub2356Taus = {GenTwoJetAllSub2356Tau1, GenTwoJetAllSub2356Tau2, GenTwoJetAllSub2356Tau3, GenTwoJetAllSub2356Tau2Tau1, GenTwoJetAllSub2356Tau3Tau2, GenTwoJetAllSub2356Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub2356Taus, tmpJet2356, genweight);

  std::vector<GenJet> tmp2456Subjets = {combinedSubjets.at(1), combinedSubjets.at(3), combinedSubjets.at(4), combinedSubjets.at(5)};
  GenTopJet tmpJet2456;
  calculateNSubjettines(&tmpJet2456, tmp2456Subjets);
  std::vector<TH1F*> GenTwoJetAllSub2456Taus = {GenTwoJetAllSub2456Tau1, GenTwoJetAllSub2456Tau2, GenTwoJetAllSub2456Tau3, GenTwoJetAllSub2456Tau2Tau1, GenTwoJetAllSub2456Tau3Tau2, GenTwoJetAllSub2456Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub2456Taus, tmpJet2456, genweight);

  std::vector<GenJet> tmp3456Subjets = {combinedSubjets.at(2), combinedSubjets.at(3), combinedSubjets.at(4), combinedSubjets.at(5)};
  GenTopJet tmpJet3456;
  calculateNSubjettines(&tmpJet3456, tmp3456Subjets);
  std::vector<TH1F*> GenTwoJetAllSub3456Taus = {GenTwoJetAllSub3456Tau1, GenTwoJetAllSub3456Tau2, GenTwoJetAllSub3456Tau3, GenTwoJetAllSub3456Tau2Tau1, GenTwoJetAllSub3456Tau3Tau2, GenTwoJetAllSub3456Tau3Tau1};
  fillTauHistsSubjets(GenTwoJetAllSub3456Taus, tmpJet3456, genweight);

  GenTopJet tmpJet123, tmpJet124, tmpJet125, tmpJet126, tmpJet134, tmpJet135, tmpJet136, tmpJet145, tmpJet146, tmpJet156, tmpJet234, tmpJet235, tmpJet236, tmpJet245, tmpJet246, tmpJet256, tmpJet345, tmpJet346, tmpJet356, tmpJet456;
  std::vector<GenJet> tmp123Subjets = {combinedSubjets.at(0), combinedSubjets.at(1), combinedSubjets.at(2)};
  std::vector<GenJet> tmp124Subjets = {combinedSubjets.at(0), combinedSubjets.at(1), combinedSubjets.at(3)};
  std::vector<GenJet> tmp125Subjets = {combinedSubjets.at(0), combinedSubjets.at(1), combinedSubjets.at(4)};
  std::vector<GenJet> tmp126Subjets = {combinedSubjets.at(0), combinedSubjets.at(1), combinedSubjets.at(5)};
  std::vector<GenJet> tmp134Subjets = {combinedSubjets.at(0), combinedSubjets.at(2), combinedSubjets.at(3)};
  std::vector<GenJet> tmp135Subjets = {combinedSubjets.at(0), combinedSubjets.at(2), combinedSubjets.at(4)};
  std::vector<GenJet> tmp136Subjets = {combinedSubjets.at(0), combinedSubjets.at(2), combinedSubjets.at(5)};
  std::vector<GenJet> tmp145Subjets = {combinedSubjets.at(0), combinedSubjets.at(3), combinedSubjets.at(4)};
  std::vector<GenJet> tmp146Subjets = {combinedSubjets.at(0), combinedSubjets.at(3), combinedSubjets.at(5)};
  std::vector<GenJet> tmp156Subjets = {combinedSubjets.at(0), combinedSubjets.at(4), combinedSubjets.at(5)};
  std::vector<GenJet> tmp234Subjets = {combinedSubjets.at(1), combinedSubjets.at(2), combinedSubjets.at(3)};
  std::vector<GenJet> tmp235Subjets = {combinedSubjets.at(1), combinedSubjets.at(2), combinedSubjets.at(4)};
  std::vector<GenJet> tmp236Subjets = {combinedSubjets.at(1), combinedSubjets.at(2), combinedSubjets.at(5)};
  std::vector<GenJet> tmp245Subjets = {combinedSubjets.at(1), combinedSubjets.at(3), combinedSubjets.at(4)};
  std::vector<GenJet> tmp246Subjets = {combinedSubjets.at(1), combinedSubjets.at(3), combinedSubjets.at(5)};
  std::vector<GenJet> tmp256Subjets = {combinedSubjets.at(1), combinedSubjets.at(4), combinedSubjets.at(5)};
  std::vector<GenJet> tmp345Subjets = {combinedSubjets.at(2), combinedSubjets.at(3), combinedSubjets.at(4)};
  std::vector<GenJet> tmp346Subjets = {combinedSubjets.at(2), combinedSubjets.at(3), combinedSubjets.at(5)};
  std::vector<GenJet> tmp356Subjets = {combinedSubjets.at(2), combinedSubjets.at(4), combinedSubjets.at(5)};
  std::vector<GenJet> tmp456Subjets = {combinedSubjets.at(3), combinedSubjets.at(4), combinedSubjets.at(5)};

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp123Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp123Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp123Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp124Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp124Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp124Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp125Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp125Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp125Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp126Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp126Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp126Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp134Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp134Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp134Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp135Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp135Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp135Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp136Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp136Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp136Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp145Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp145Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp145Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp146Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp146Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp146Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp156Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp156Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp156Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp234Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp234Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp234Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp235Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp235Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp235Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp236Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp236Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp236Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp245Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp245Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp245Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp246Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp246Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp246Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp256Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp256Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp256Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp345Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp345Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp345Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp346Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp346Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp346Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp356Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp356Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp356Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllSubjet1pT->Fill(tmp456Subjets.at(0).pt(), genweight);
  GenTwoJetAllSubAllSubjet2pT->Fill(tmp456Subjets.at(1).pt(), genweight);
  GenTwoJetAllSubAllSubjet3pT->Fill(tmp456Subjets.at(2).pt(), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp123Subjets.at(0), tmp123Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp123Subjets.at(1), tmp123Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp123Subjets.at(2), tmp123Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp124Subjets.at(0), tmp124Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp124Subjets.at(1), tmp124Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp124Subjets.at(2), tmp124Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp125Subjets.at(0), tmp125Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp125Subjets.at(1), tmp125Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp125Subjets.at(2), tmp125Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp126Subjets.at(0), tmp126Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp126Subjets.at(1), tmp126Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp126Subjets.at(2), tmp126Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp134Subjets.at(0), tmp134Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp134Subjets.at(1), tmp134Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp134Subjets.at(2), tmp134Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp135Subjets.at(0), tmp135Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp135Subjets.at(1), tmp135Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp135Subjets.at(2), tmp135Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp136Subjets.at(0), tmp136Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp136Subjets.at(1), tmp136Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp136Subjets.at(2), tmp136Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp145Subjets.at(0), tmp145Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp145Subjets.at(1), tmp145Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp145Subjets.at(2), tmp145Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp146Subjets.at(0), tmp146Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp146Subjets.at(1), tmp146Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp146Subjets.at(2), tmp146Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp156Subjets.at(0), tmp156Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp156Subjets.at(1), tmp156Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp156Subjets.at(2), tmp156Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp234Subjets.at(0), tmp234Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp234Subjets.at(1), tmp234Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp234Subjets.at(2), tmp234Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp235Subjets.at(0), tmp235Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp235Subjets.at(1), tmp235Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp235Subjets.at(2), tmp235Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp236Subjets.at(0), tmp236Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp236Subjets.at(1), tmp236Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp236Subjets.at(2), tmp236Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp245Subjets.at(0), tmp245Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp245Subjets.at(1), tmp245Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp245Subjets.at(2), tmp245Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp246Subjets.at(0), tmp246Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp246Subjets.at(1), tmp246Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp246Subjets.at(2), tmp246Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp256Subjets.at(0), tmp256Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp256Subjets.at(1), tmp256Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp256Subjets.at(2), tmp256Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp345Subjets.at(0), tmp345Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp345Subjets.at(1), tmp345Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp345Subjets.at(2), tmp345Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp346Subjets.at(0), tmp346Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp346Subjets.at(1), tmp346Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp346Subjets.at(2), tmp346Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp356Subjets.at(0), tmp356Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp356Subjets.at(1), tmp356Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp356Subjets.at(2), tmp356Subjets.at(1)), genweight);

  GenTwoJetAllSubAllDR12->Fill(deltaR(tmp456Subjets.at(0), tmp456Subjets.at(1)), genweight);
  GenTwoJetAllSubAllDR23->Fill(deltaR(tmp456Subjets.at(1), tmp456Subjets.at(2)), genweight);
  GenTwoJetAllSubAllDR31->Fill(deltaR(tmp456Subjets.at(2), tmp456Subjets.at(1)), genweight);


  tmpJet123 = combine->CreateTopJetFromSubjets_gen(tmp123Subjets, 0, 2.5);
  tmpJet124 = combine->CreateTopJetFromSubjets_gen(tmp124Subjets, 0, 2.5);
  tmpJet125 = combine->CreateTopJetFromSubjets_gen(tmp125Subjets, 0, 2.5);
  tmpJet126 = combine->CreateTopJetFromSubjets_gen(tmp126Subjets, 0, 2.5);
  tmpJet134 = combine->CreateTopJetFromSubjets_gen(tmp134Subjets, 0, 2.5);
  tmpJet135 = combine->CreateTopJetFromSubjets_gen(tmp135Subjets, 0, 2.5);
  tmpJet136 = combine->CreateTopJetFromSubjets_gen(tmp136Subjets, 0, 2.5);
  tmpJet145 = combine->CreateTopJetFromSubjets_gen(tmp145Subjets, 0, 2.5);
  tmpJet146 = combine->CreateTopJetFromSubjets_gen(tmp146Subjets, 0, 2.5);
  tmpJet156 = combine->CreateTopJetFromSubjets_gen(tmp156Subjets, 0, 2.5);
  tmpJet234 = combine->CreateTopJetFromSubjets_gen(tmp234Subjets, 0, 2.5);
  tmpJet235 = combine->CreateTopJetFromSubjets_gen(tmp235Subjets, 0, 2.5);
  tmpJet236 = combine->CreateTopJetFromSubjets_gen(tmp236Subjets, 0, 2.5);
  tmpJet245 = combine->CreateTopJetFromSubjets_gen(tmp245Subjets, 0, 2.5);
  tmpJet246 = combine->CreateTopJetFromSubjets_gen(tmp246Subjets, 0, 2.5);
  tmpJet256 = combine->CreateTopJetFromSubjets_gen(tmp256Subjets, 0, 2.5);
  tmpJet345 = combine->CreateTopJetFromSubjets_gen(tmp345Subjets, 0, 2.5);
  tmpJet346 = combine->CreateTopJetFromSubjets_gen(tmp346Subjets, 0, 2.5);
  tmpJet356 = combine->CreateTopJetFromSubjets_gen(tmp356Subjets, 0, 2.5);
  tmpJet456 = combine->CreateTopJetFromSubjets_gen(tmp456Subjets, 0, 2.5);


  fillDRSubjetHists(tmp123Subjets, tmpJet123, genweight);
  fillDRSubjetHists(tmp124Subjets, tmpJet124, genweight);
  fillDRSubjetHists(tmp125Subjets, tmpJet125, genweight);
  fillDRSubjetHists(tmp126Subjets, tmpJet126, genweight);
  fillDRSubjetHists(tmp134Subjets, tmpJet134, genweight);
  fillDRSubjetHists(tmp135Subjets, tmpJet135, genweight);
  fillDRSubjetHists(tmp136Subjets, tmpJet136, genweight);
  fillDRSubjetHists(tmp145Subjets, tmpJet145, genweight);
  fillDRSubjetHists(tmp146Subjets, tmpJet146, genweight);
  fillDRSubjetHists(tmp156Subjets, tmpJet156, genweight);
  fillDRSubjetHists(tmp234Subjets, tmpJet234, genweight);
  fillDRSubjetHists(tmp235Subjets, tmpJet235, genweight);
  fillDRSubjetHists(tmp236Subjets, tmpJet236, genweight);
  fillDRSubjetHists(tmp245Subjets, tmpJet245, genweight);
  fillDRSubjetHists(tmp246Subjets, tmpJet246, genweight);
  fillDRSubjetHists(tmp256Subjets, tmpJet256, genweight);
  fillDRSubjetHists(tmp345Subjets, tmpJet345, genweight);
  fillDRSubjetHists(tmp346Subjets, tmpJet346, genweight);
  fillDRSubjetHists(tmp356Subjets, tmpJet356, genweight);
  fillDRSubjetHists(tmp456Subjets, tmpJet456, genweight);


  TLorentzVector tmpJet123_v4, tmpJet124_v4, tmpJet125_v4, tmpJet126_v4, tmpJet134_v4, tmpJet135_v4, tmpJet136_v4, tmpJet145_v4, tmpJet146_v4, tmpJet156_v4, tmpJet234_v4, tmpJet235_v4, tmpJet236_v4, tmpJet245_v4, tmpJet246_v4, tmpJet256_v4, tmpJet345_v4, tmpJet346_v4, tmpJet356_v4, tmpJet456_v4;
  tmpJet123_v4.SetPxPyPzE(tmpJet123.v4().Px(), tmpJet123.v4().Py(), tmpJet123.v4().Pz(), tmpJet123.v4().E());
  tmpJet124_v4.SetPxPyPzE(tmpJet124.v4().Px(), tmpJet124.v4().Py(), tmpJet124.v4().Pz(), tmpJet124.v4().E());
  tmpJet125_v4.SetPxPyPzE(tmpJet125.v4().Px(), tmpJet125.v4().Py(), tmpJet125.v4().Pz(), tmpJet125.v4().E());
  tmpJet126_v4.SetPxPyPzE(tmpJet126.v4().Px(), tmpJet126.v4().Py(), tmpJet126.v4().Pz(), tmpJet126.v4().E());
  tmpJet134_v4.SetPxPyPzE(tmpJet134.v4().Px(), tmpJet134.v4().Py(), tmpJet134.v4().Pz(), tmpJet134.v4().E());
  tmpJet135_v4.SetPxPyPzE(tmpJet135.v4().Px(), tmpJet135.v4().Py(), tmpJet135.v4().Pz(), tmpJet135.v4().E());
  tmpJet136_v4.SetPxPyPzE(tmpJet136.v4().Px(), tmpJet136.v4().Py(), tmpJet136.v4().Pz(), tmpJet136.v4().E());
  tmpJet145_v4.SetPxPyPzE(tmpJet145.v4().Px(), tmpJet145.v4().Py(), tmpJet145.v4().Pz(), tmpJet145.v4().E());
  tmpJet146_v4.SetPxPyPzE(tmpJet146.v4().Px(), tmpJet146.v4().Py(), tmpJet146.v4().Pz(), tmpJet146.v4().E());
  tmpJet156_v4.SetPxPyPzE(tmpJet156.v4().Px(), tmpJet156.v4().Py(), tmpJet156.v4().Pz(), tmpJet156.v4().E());
  tmpJet234_v4.SetPxPyPzE(tmpJet234.v4().Px(), tmpJet234.v4().Py(), tmpJet234.v4().Pz(), tmpJet234.v4().E());
  tmpJet235_v4.SetPxPyPzE(tmpJet235.v4().Px(), tmpJet235.v4().Py(), tmpJet235.v4().Pz(), tmpJet235.v4().E());
  tmpJet236_v4.SetPxPyPzE(tmpJet236.v4().Px(), tmpJet236.v4().Py(), tmpJet236.v4().Pz(), tmpJet236.v4().E());
  tmpJet245_v4.SetPxPyPzE(tmpJet245.v4().Px(), tmpJet245.v4().Py(), tmpJet245.v4().Pz(), tmpJet245.v4().E());
  tmpJet246_v4.SetPxPyPzE(tmpJet246.v4().Px(), tmpJet246.v4().Py(), tmpJet246.v4().Pz(), tmpJet246.v4().E());
  tmpJet256_v4.SetPxPyPzE(tmpJet256.v4().Px(), tmpJet256.v4().Py(), tmpJet256.v4().Pz(), tmpJet256.v4().E());
  tmpJet345_v4.SetPxPyPzE(tmpJet345.v4().Px(), tmpJet345.v4().Py(), tmpJet345.v4().Pz(), tmpJet345.v4().E());
  tmpJet346_v4.SetPxPyPzE(tmpJet346.v4().Px(), tmpJet346.v4().Py(), tmpJet346.v4().Pz(), tmpJet346.v4().E());
  tmpJet356_v4.SetPxPyPzE(tmpJet356.v4().Px(), tmpJet356.v4().Py(), tmpJet356.v4().Pz(), tmpJet356.v4().E());
  tmpJet456_v4.SetPxPyPzE(tmpJet456.v4().Px(), tmpJet456.v4().Py(), tmpJet456.v4().Pz(), tmpJet456.v4().E());

  
  calculateNSubjettines(&tmpJet123, tmp123Subjets);
  calculateNSubjettines(&tmpJet124, tmp124Subjets);
  calculateNSubjettines(&tmpJet125, tmp125Subjets);
  calculateNSubjettines(&tmpJet126, tmp126Subjets);
  calculateNSubjettines(&tmpJet134, tmp134Subjets);
  calculateNSubjettines(&tmpJet135, tmp135Subjets);
  calculateNSubjettines(&tmpJet136, tmp136Subjets);
  calculateNSubjettines(&tmpJet145, tmp145Subjets);
  calculateNSubjettines(&tmpJet146, tmp146Subjets);
  calculateNSubjettines(&tmpJet156, tmp156Subjets);
  calculateNSubjettines(&tmpJet234, tmp234Subjets);
  calculateNSubjettines(&tmpJet235, tmp235Subjets);
  calculateNSubjettines(&tmpJet236, tmp236Subjets);
  calculateNSubjettines(&tmpJet245, tmp245Subjets);
  calculateNSubjettines(&tmpJet246, tmp246Subjets);
  calculateNSubjettines(&tmpJet256, tmp256Subjets);
  calculateNSubjettines(&tmpJet345, tmp345Subjets);
  calculateNSubjettines(&tmpJet346, tmp346Subjets);
  calculateNSubjettines(&tmpJet356, tmp356Subjets);
  calculateNSubjettines(&tmpJet456, tmp456Subjets);

  std::vector<GenTopJet> tmpJets = {tmpJet123, tmpJet124, tmpJet125, tmpJet126, tmpJet134, tmpJet135, tmpJet136, tmpJet145, tmpJet146, tmpJet156, tmpJet234, tmpJet235, tmpJet236, tmpJet245, tmpJet246, tmpJet256, tmpJet345, tmpJet346, tmpJet356, tmpJet456};
  std::vector<TLorentzVector> tmpJets_v4 = {tmpJet123_v4, tmpJet124_v4, tmpJet125_v4, tmpJet126_v4, tmpJet134_v4, tmpJet135_v4, tmpJet136_v4, tmpJet145_v4, tmpJet146_v4, tmpJet156_v4, tmpJet234_v4, tmpJet235_v4, tmpJet236_v4, tmpJet245_v4, tmpJet246_v4, tmpJet256_v4, tmpJet345_v4, tmpJet346_v4, tmpJet356_v4, tmpJet456_v4};
  
  float tau21 = 0.0;
  uint maxI = -1;

  float pT = 0.0;
  uint pTI = -1;

  for(uint i=0; i<tmpJets.size(); i++) {

    if(tmpJets.at(i).tau1() != 0 && tmpJets.at(i).tau2()/tmpJets.at(i).tau1() > tau21) {
      tau21 = tmpJets.at(i).tau2()/tmpJets.at(i).tau1();
      maxI = i;
    }

    if(tmpJets_v4.at(i).Pt() > pT) {
      pT = tmpJets_v4.at(i).Pt();
      pTI = i;
    }

  }

  if(tau21 > 0.24) {
    GenTwoJetAllSubTau21MaxMass->Fill(tmpJets_v4.at(maxI).M(), genweight);
    GenTwoJetAllSubMaxPTMass->Fill(tmpJets_v4.at(pTI).M(), genweight);
  }
  
  std::vector<TH1F*> GenTwoJetAllSubAllTaus = {GenTwoJetAllSubAllTau1, GenTwoJetAllSubAllTau2, GenTwoJetAllSubAllTau3, GenTwoJetAllSubAllTau2Tau1, GenTwoJetAllSubAllTau3Tau2, GenTwoJetAllSubAllTau3Tau1};
  
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet123, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet124, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet125, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet126, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet134, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet135, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet136, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet145, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet146, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet156, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet234, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet235, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet236, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet245, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet246, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet256, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet345, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet346, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet356, genweight);
  fillTauHistsSubjets(GenTwoJetAllSubAllTaus, tmpJet456, genweight);

  GenTwoJetAllSubAllMass->Fill(tmpJet123_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet124_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet125_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet126_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet134_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet135_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet136_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet145_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet146_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet156_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet234_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet235_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet236_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet245_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet246_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet256_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet345_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet346_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet356_v4.M(), genweight);
  GenTwoJetAllSubAllMass->Fill(tmpJet456_v4.M(), genweight);


}

void GenHists_GenNoLep::fillDRSubjetHists(std::vector<GenJet> tmpSubjets, GenTopJet tmpJet, double genweight) {

  GenTwoJetAllSubAllDR1Axis->Fill(deltaR(tmpSubjets.at(0), tmpJet), genweight);
  GenTwoJetAllSubAllDR2Axis->Fill(deltaR(tmpSubjets.at(1), tmpJet), genweight);
  GenTwoJetAllSubAllDR3Axis->Fill(deltaR(tmpSubjets.at(2), tmpJet), genweight);

  float minDR = 4;
  float maxDR = 0;

  for(uint i=0; i<tmpSubjets.size(); i++) {
    if(deltaR(tmpSubjets.at(i), tmpJet) < minDR) {
      minDR = deltaR(tmpSubjets.at(i), tmpJet);
    }
    if(deltaR(tmpSubjets.at(i), tmpJet) > maxDR) {
      maxDR = deltaR(tmpSubjets.at(i), tmpJet); 
    }
  }

  GenTwoJetAllSubAllDRAxisMinMax->Fill(minDR, maxDR, genweight);

}

void matchedSubjets(std::vector<GenJet>* matchedSubjets, std::vector<GenJet>* unmatchedSubjets, std::vector<bool>* matched, std::vector<GenJet> subjets, std::vector<GenParticle> quarks, uint nMatchedSubjets) {

  std::vector<bool> quarksMatched = {false, false, false};
  std::vector<uint> matchedIndices;

  for(uint i=0; i<quarks.size(); i++) {

    float dR = 100;
    uint minJ = -1;
    for(uint j=0; j<subjets.size(); j++) {

      bool subjetNotMatchedJet = true;
      for(uint k=0; k<matchedIndices.size(); k++) {
        if(j == matchedIndices.at(k)) subjetNotMatchedJet = false;
      }

      if(subjetNotMatchedJet && deltaR(subjets.at(j), quarks.at(i)) < dR) {
        dR = deltaR(subjets.at(j), quarks.at(i));
        minJ = j;
      }
    }

    if(dR < subjetRadius) {
      matchedSubjets->push_back(subjets.at(minJ));
      quarksMatched.at(i) = true;
      matchedIndices.push_back(minJ);
    }
  }

  bool allMatched = quarksMatched.at(0) && quarksMatched.at(1) && quarksMatched.at(2);
  bool botMatched = quarksMatched.at(0) && !quarksMatched.at(1) && !quarksMatched.at(2);
  bool lightQMatched =  (!quarksMatched.at(0) && quarksMatched.at(1) && !quarksMatched.at(2)) || (!quarksMatched.at(0) && !quarksMatched.at(1) && quarksMatched.at(2));
  bool botLightQMatched = (quarksMatched.at(0) && !quarksMatched.at(1) && quarksMatched.at(2)) || (quarksMatched.at(0) && quarksMatched.at(1) && !quarksMatched.at(2));
  bool twoLightQMatched = !quarksMatched.at(0) && quarksMatched.at(1) && quarksMatched.at(2);

  if(allMatched) matched->at(0) = true;
  if(botMatched) matched->at(1) = true;
  if(lightQMatched) matched->at(2) = true;
  if(botLightQMatched) matched->at(3) = true;
  if(twoLightQMatched) matched->at(4) = true;

  for(uint i=0; i<subjets.size(); i++) {
    for(uint j=0; j<quarks.size(); j++) {

      bool subjetNotMatchedJet = true;
      for(uint k=0; k<matchedIndices.size(); k++) {
        if(i == matchedIndices.at(k)) subjetNotMatchedJet = false;
      }
      
      if(subjetNotMatchedJet && matchedSubjets->size() < nMatchedSubjets && deltaR(subjets.at(i), quarks.at(j)) < subjetRadius) {
        matchedSubjets->push_back(subjets.at(i));
        matchedIndices.push_back(i);
      }
    }
  }

  for(uint i=0; i<subjets.size(); i++) {

    bool subjetNotMatchedJet = true;
    for(uint k=0; k<matchedIndices.size(); k++) {
      if(i == matchedIndices.at(k)) subjetNotMatchedJet = false;
    }
    
    if(subjetNotMatchedJet && matchedSubjets->size() < nMatchedSubjets) {
      matchedSubjets->push_back(subjets.at(i));
      matchedIndices.push_back(i);
    }
  }

  for(uint i=0; i<subjets.size(); i++) {

    bool subjetNotMatchedJet = true;
    for(uint k=0; k<matchedIndices.size(); k++) {
      if(i == matchedIndices.at(k)) subjetNotMatchedJet = false;
    }

    if(subjetNotMatchedJet) {
      unmatchedSubjets->push_back(subjets.at(i));
    }
  }

  /*cout << "matched Indices:" << endl;

  for(uint i=0; i<matchedIndices.size(); i++) {
    cout << matchedIndices.at(i) << ", " << endl;
  }*/

}

void GenHists_GenNoLep::fill(const Event & event) {

  if(debug) cout << "--- fill GenNoLepHists ---" << endl;
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
  std::vector<GenTopJet> topJets, gluonJets;
  TLorentzVector jeti_v4, combinedJet_v4;
  TLorentzVector topJet_v4_combined;
  std::vector<TLorentzVector> subjets_v4 = {};
  std::vector<TLorentzVector> sortedSubjets_v4 = {};
  std::vector<TLorentzVector> jets_v4, topJets_v4, gluonJets_v4;
  std::vector<std::vector<TLorentzVector>> topSubjets_v4 = {};
  std::vector<std::vector<TLorentzVector>> gluonSubjets_v4 = {};

  TLorentzVector jet1_v4, jet2_v4, lepton1_v4, jet2_lep_v4, topjet1_v4, topjet2_v4;
  GenTopJet jet1,jet2,jet3,jet4,jet5,jet6, tmpJet;
  std::vector<GenJet> subjets, sortedSubjets;
  if(debug) cout << "\t\t--- get jet1" << endl;

  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------


  //---------------------------------------------------------------------------------------
  //--------------------------------- Matching --------------------------------------------
  //---------------------------------------------------------------------------------------
  if(debug) cout << "\t--- Matching" << endl;

  //bool isTTBar = true;

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
      //isTTBar = false;
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

  vector<GenParticle> quarks = {bot, q1, q2};
  vector<GenParticle> gluons = gluonsInEvent(event);

  double genweight = event.weight;
  //genweight = 1;

  if(debug) cout << "\t\t--- set jets_v4" << endl;

  TLorentzVector tmp;
  std::vector<TLorentzVector> tmpSubjets;

  for(uint i=0; i<jets.size(); i++) {
    jeti_v4.SetPxPyPzE(jets.at(i).v4().Px(), jets.at(i).v4().Py(), jets.at(i).v4().Pz(), jets.at(i).v4().E());
    jets_v4.push_back(jeti_v4);
  }

  if(jets.size()>1 && compareJetPt(jets_v4.at(0), jets_v4.at(1))) {
    tmpJet = jets.at(0);
    jets.at(0) = jets.at(1);
    jets.at(1) = tmpJet;
    tmp = jets_v4.at(0);
    jets_v4.at(0) = jets_v4.at(1);
    jets_v4.at(1) = tmp;
  }

  for(uint i=0; i<jets.size(); i++) {
    jeti_v4.SetPxPyPzE(jets.at(i).v4().Px(), jets.at(i).v4().Py(), jets.at(i).v4().Pz(), jets.at(i).v4().E());

    for(uint j=0; j<jets.at(i).subjets().size(); j++) {
      tmp.SetPxPyPzE(jets.at(i).subjets().at(j).v4().Px(), jets.at(i).subjets().at(j).v4().Py(), jets.at(i).subjets().at(j).v4().Pz(), jets.at(i).subjets().at(j).v4().E());
      tmpSubjets.push_back(tmp);
    }

    std::sort(tmpSubjets.begin(), tmpSubjets.end(), compareSubjetPt);

    if(deltaR(top, jets.at(i)) < 1.2) {
      topJets.push_back(jets.at(i));
      topJets_v4.push_back(jeti_v4);
      topSubjets_v4.push_back(tmpSubjets);
    } else {
      gluonJets.push_back(jets.at(i));
      gluonJets_v4.push_back(jeti_v4);
      gluonSubjets_v4.push_back(tmpSubjets);
    }
  }

  //---------------------------------------------------------------------------------------
  //--------------------------------- Fill Hists here -------------------------------------
  //---------------------------------------------------------------------------------------

  if(debug) cout << "\t--- Fill Hists" << endl;

  GenJetNumber->Fill(jets.size(), genweight);
  GenTopJetNumber->Fill(topJets.size(), genweight);
  GenGluonJetNumber->Fill(gluonJets.size(), genweight);

  if(jets.size()>1 && deltaR(jets.at(0), jets.at(1)) < dR_) {

    combinedJet_v4 = jets_v4.at(0) + jets_v4.at(1);

    GenJetMass->Fill(combinedJet_v4.M(), genweight);
    GenJetMassCombinedOnly->Fill(combinedJet_v4.M(), genweight);

  } else if (jets.size()>0) {

    GenJetMass->Fill(jets_v4.at(0).M(), genweight);
    GenJetMassNotCombinedOnly->Fill(jets_v4.at(0).M(), genweight);

    bool leadSubjetMatching = subjetMatching(jets.at(0).subjets(), quarks, nullptr, false, nullptr);

    if(leadSubjetMatching) GenJetMassNotCombinedOnlySubjetsMatched->Fill(jets_v4.at(0).M(), genweight);

  }

  if(topJets.size() == 1 && gluonJets.size() == 1) {

    STGenTopJetPT->Fill(topJets_v4.at(0).Pt(), genweight);
    STGenGluonJetPT->Fill(gluonJets_v4.at(0).Pt(), genweight);

    STGenTopJetM->Fill(topJets_v4.at(0).M(), genweight);
    STGenGluonJetM->Fill(gluonJets_v4.at(0).M(), genweight);

    if(topJets_v4.at(0).Pt() < 400) {
      STGenTopJetMSmallPT->Fill(topJets_v4.at(0).M(), genweight);
    }

    /*
    GenTopJetTau1->Fill(topJets.at(0).tau1(), genweight);
    GenTopJetTau2->Fill(topJets.at(0).tau2(), genweight);
    GenTopJetTau3->Fill(topJets.at(0).tau3(), genweight);
    GenTopJetTau4->Fill(topJets.at(0).tau4(), genweight);

    if(debug) cout << "\t\t--- top tau ratios" << endl;
    if(topJets.at(0).tau1() != 0) GenTopJetTau2Tau1->Fill(topJets.at(0).tau2()/topJets.at(0).tau1(), genweight);
    if(topJets.at(0).tau2() != 0) GenTopJetTau3Tau2->Fill(topJets.at(0).tau3()/topJets.at(0).tau2(), genweight);
    if(topJets.at(0).tau1() != 0) GenTopJetTau3Tau1->Fill(topJets.at(0).tau3()/topJets.at(0).tau1(), genweight);
    if(topJets.at(0).tau3() != 0) GenTopJetTau4Tau3->Fill(topJets.at(0).tau4()/topJets.at(0).tau3(), genweight);
    if(topJets.at(0).tau2() != 0) GenTopJetTau4Tau2->Fill(topJets.at(0).tau4()/topJets.at(0).tau2(), genweight);
    if(topJets.at(0).tau1() != 0) GenTopJetTau4Tau1->Fill(topJets.at(0).tau4()/topJets.at(0).tau1(), genweight);*/

    std::vector<TH1F*> GenTopJetTaus = {GenTopJetTau1, GenTopJetTau2, GenTopJetTau3, GenTopJetTau4, GenTopJetTau2Tau1, GenTopJetTau3Tau2, GenTopJetTau3Tau1, GenTopJetTau4Tau3, GenTopJetTau4Tau2, GenTopJetTau4Tau1};
    fillTauHists(GenTopJetTaus, topJets.at(0), genweight);


    GenTopJetCombinedTau1->Fill(topJets.at(0).tau1(), genweight);
    GenTopJetCombinedTau2->Fill(topJets.at(0).tau2(), genweight);
    GenTopJetCombinedTau3->Fill(topJets.at(0).tau3(), genweight);
    GenTopJetCombinedTau4->Fill(topJets.at(0).tau4(), genweight);

    if(debug) cout << "\t\t--- top combined tau ratios" << endl;
    if(topJets.at(0).tau1() != 0) GenTopJetCombinedTau2Tau1->Fill(topJets.at(0).tau2()/topJets.at(0).tau1(), genweight);
    if(topJets.at(0).tau2() != 0) GenTopJetCombinedTau3Tau2->Fill(topJets.at(0).tau3()/topJets.at(0).tau2(), genweight);
    if(topJets.at(0).tau1() != 0) GenTopJetCombinedTau3Tau1->Fill(topJets.at(0).tau3()/topJets.at(0).tau1(), genweight);
    if(topJets.at(0).tau3() != 0) GenTopJetCombinedTau4Tau3->Fill(topJets.at(0).tau4()/topJets.at(0).tau3(), genweight);
    if(topJets.at(0).tau2() != 0) GenTopJetCombinedTau4Tau2->Fill(topJets.at(0).tau4()/topJets.at(0).tau2(), genweight);
    if(topJets.at(0).tau1() != 0) GenTopJetCombinedTau4Tau1->Fill(topJets.at(0).tau4()/topJets.at(0).tau1(), genweight);


    GenGluonJetTau1->Fill(gluonJets.at(0).tau1(), genweight);
    GenGluonJetTau2->Fill(gluonJets.at(0).tau2(), genweight);
    GenGluonJetTau3->Fill(gluonJets.at(0).tau3(), genweight);
    GenGluonJetTau4->Fill(gluonJets.at(0).tau4(), genweight);

    if(debug) cout << "\t\t--- gluon tau ratios" << endl;

    if(gluonJets.at(0).tau1() != 0) GenGluonJetTau2Tau1->Fill(gluonJets.at(0).tau2()/gluonJets.at(0).tau1(), genweight);
    if(gluonJets.at(0).tau2() != 0) GenGluonJetTau3Tau2->Fill(gluonJets.at(0).tau3()/gluonJets.at(0).tau2(), genweight);
    if(gluonJets.at(0).tau1() != 0) GenGluonJetTau3Tau1->Fill(gluonJets.at(0).tau3()/gluonJets.at(0).tau1(), genweight);
    if(gluonJets.at(0).tau3() != 0) GenGluonJetTau4Tau3->Fill(gluonJets.at(0).tau4()/gluonJets.at(0).tau3(), genweight);
    if(gluonJets.at(0).tau2() != 0) GenGluonJetTau4Tau2->Fill(gluonJets.at(0).tau4()/gluonJets.at(0).tau2(), genweight);
    if(gluonJets.at(0).tau1() != 0) GenGluonJetTau4Tau1->Fill(gluonJets.at(0).tau4()/gluonJets.at(0).tau1(), genweight);

    STGenDeltaRTopGluon->Fill(deltaR(topJets.at(0), gluonJets.at(0)), genweight);

    if(debug) cout << "\t\t--- top subjet ratios" << endl;

    GenTopSubjetSize->Fill(topSubjets_v4.at(0).size(), genweight);
    if(topJets_v4.at(0).Pt() == 0) GenTopPt0->Fill(1, genweight);

    if(topSubjets_v4.at(0).size() == 3 && topJets_v4.at(0).Pt() != 0) {
      GenTopSubjetPT1PT->Fill(topSubjets_v4.at(0).at(0).Pt()/topJets_v4.at(0).Pt(), genweight);
      GenTopSubjetPT2PT->Fill(topSubjets_v4.at(0).at(1).Pt()/topJets_v4.at(0).Pt(), genweight);
      GenTopSubjetPT3PT->Fill(topSubjets_v4.at(0).at(2).Pt()/topJets_v4.at(0).Pt(), genweight);
    }

    if(printOut3) cout << "sorted subjet pts: " << topSubjets_v4.at(0).at(0).Pt() << ", " << topSubjets_v4.at(0).at(1).Pt() << ", " << topSubjets_v4.at(0).at(2).Pt() << endl;
    if(printOut3) cout << "sorted subjet pt sum: " << topSubjets_v4.at(0).at(0).Pt() + topSubjets_v4.at(0).at(1).Pt() + topSubjets_v4.at(0).at(2).Pt() << ", fatjet pt: " << topJets_v4.at(0).Pt() << endl;

    std::sort(topSubjets_v4.at(0).begin(), topSubjets_v4.at(0).end(), compareSubjetM);

    if(topSubjets_v4.at(0).size() == 3 && topJets_v4.at(0).M() != 0) {
      GenTopSubjetM1M->Fill(topSubjets_v4.at(0).at(0).M()/topJets_v4.at(0).M(), genweight);
      GenTopSubjetM2M->Fill(topSubjets_v4.at(0).at(1).M()/topJets_v4.at(0).M(), genweight);
      GenTopSubjetM3M->Fill(topSubjets_v4.at(0).at(2).M()/topJets_v4.at(0).M(), genweight);
    }

    if(debug) cout << "\t\t--- gluon subjet ratios" << endl;

    GenGluonSubjetSize->Fill(gluonSubjets_v4.at(0).size(), genweight);
    if(gluonJets_v4.at(0).Pt() == 0) GenGluonPt0->Fill(1, genweight);

    if(gluonSubjets_v4.at(0).size() == 3 && gluonJets_v4.at(0).Pt() != 0) {
      GenGluonSubjetPT1PT->Fill(gluonSubjets_v4.at(0).at(0).Pt()/gluonJets_v4.at(0).Pt(), genweight);
      GenGluonSubjetPT2PT->Fill(gluonSubjets_v4.at(0).at(1).Pt()/gluonJets_v4.at(0).Pt(), genweight);
      GenGluonSubjetPT3PT->Fill(gluonSubjets_v4.at(0).at(2).Pt()/gluonJets_v4.at(0).Pt(), genweight);

      STGluonSubjetPtSum->Fill((gluonSubjets_v4.at(0).at(0).Pt() + gluonSubjets_v4.at(0).at(1).Pt() + gluonSubjets_v4.at(0).at(2).Pt())/gluonJets_v4.at(0).Pt(), genweight);
    }

    std::sort(gluonSubjets_v4.at(0).begin(), gluonSubjets_v4.at(0).end(), compareSubjetM);

    if(gluonSubjets_v4.at(0).size() == 3 && gluonJets_v4.at(0).M() != 0) {
      GenGluonSubjetM1M->Fill(gluonSubjets_v4.at(0).at(0).M()/gluonJets_v4.at(0).M(), genweight);
      GenGluonSubjetM2M->Fill(gluonSubjets_v4.at(0).at(1).M()/gluonJets_v4.at(0).M(), genweight);
      GenGluonSubjetM3M->Fill(gluonSubjets_v4.at(0).at(2).M()/gluonJets_v4.at(0).M(), genweight);
    }

    bool botPassed = deltaR(bot, topJets.at(0)) < jetradius;
    bool q1Passed = deltaR(q1, topJets.at(0)) < jetradius;
    bool q2Passed = deltaR(q2, topJets.at(0)) < jetradius;

    if(botPassed && q1Passed && q2Passed) {
      STGenTopJetM_EachQuarkMatched->Fill(topJets_v4.at(0).M(), genweight);
      float dRTmp = 10;
      if(gluons.size() > 0) {
        dRTmp = deltaR(gluons.at(0), topJets.at(0));
      }
      if(dRTmp < 1.2) {
        STGenTopJetM_EachQuarkMatched_GluonMatched->Fill(topJets_v4.at(0).M(), genweight);
      } else {
        STGenTopJetM_EachQuarkMatched_NoGluonMatched->Fill(topJets_v4.at(0).M(), genweight);
      }
    }

  } else if(topJets.size() == 2) {

    topJet_v4_combined = topJets_v4.at(0) + topJets_v4.at(1);

    DTGenTopJetPT->Fill(topJets_v4.at(0).Pt(), genweight);
    DTGenTopJetPT->Fill(topJets_v4.at(1).Pt(), genweight);

    DTGenTopJetM->Fill(topJets_v4.at(0).M(), genweight);
    DTGenTopJetM->Fill(topJets_v4.at(1).M(), genweight);

    DTGenTopJetPtCombined->Fill(topJet_v4_combined.Pt(), genweight);
    DTGenTopJetMCombined->Fill(topJet_v4_combined.M(), genweight);

    /*
    GenTopJetTau1->Fill(topJets.at(0).tau1(), genweight);
    GenTopJetTau2->Fill(topJets.at(0).tau2(), genweight);
    GenTopJetTau3->Fill(topJets.at(0).tau3(), genweight);
    GenTopJetTau4->Fill(topJets.at(0).tau4(), genweight);
    */

    DTGenTopJetTau1->Fill(topJets.at(0).tau1(), genweight);
    DTGenTopJetTau2->Fill(topJets.at(0).tau2(), genweight);
    DTGenTopJetTau3->Fill(topJets.at(0).tau3(), genweight);
    DTGenTopJetTau4->Fill(topJets.at(0).tau4(), genweight);

    if(gluons.size() > 0) {
      if(deltaR(gluons.at(0), topJets.at(0)) > 1.2) {
        DTNGGenTopJetTau1->Fill(topJets.at(0).tau1(), genweight);
        DTNGGenTopJetTau2->Fill(topJets.at(0).tau2(), genweight);
        DTNGGenTopJetTau3->Fill(topJets.at(0).tau3(), genweight);
        DTNGGenTopJetTau4->Fill(topJets.at(0).tau4(), genweight);
      }
    }

    if(debug) cout << "\t\t--- top tau ratios" << endl;

    /*
    if(topJets.at(0).tau1() != 0) GenTopJetTau2Tau1->Fill(topJets.at(0).tau2()/topJets.at(0).tau1(), genweight);
    if(topJets.at(0).tau2() != 0) GenTopJetTau3Tau2->Fill(topJets.at(0).tau3()/topJets.at(0).tau2(), genweight);
    if(topJets.at(0).tau1() != 0) GenTopJetTau3Tau1->Fill(topJets.at(0).tau3()/topJets.at(0).tau1(), genweight);
    if(topJets.at(0).tau3() != 0) GenTopJetTau4Tau3->Fill(topJets.at(0).tau4()/topJets.at(0).tau3(), genweight);
    if(topJets.at(0).tau2() != 0) GenTopJetTau4Tau2->Fill(topJets.at(0).tau4()/topJets.at(0).tau2(), genweight);
    if(topJets.at(0).tau1() != 0) GenTopJetTau4Tau1->Fill(topJets.at(0).tau4()/topJets.at(0).tau1(), genweight);
    */

    if(topJets.at(0).tau1() != 0) DTGenTopJetTau2Tau1->Fill(topJets.at(0).tau2()/topJets.at(0).tau1(), genweight);
    if(topJets.at(0).tau2() != 0) DTGenTopJetTau3Tau2->Fill(topJets.at(0).tau3()/topJets.at(0).tau2(), genweight);
    if(topJets.at(0).tau1() != 0) DTGenTopJetTau3Tau1->Fill(topJets.at(0).tau3()/topJets.at(0).tau1(), genweight);
    if(topJets.at(0).tau3() != 0) DTGenTopJetTau4Tau3->Fill(topJets.at(0).tau4()/topJets.at(0).tau3(), genweight);
    if(topJets.at(0).tau2() != 0) DTGenTopJetTau4Tau2->Fill(topJets.at(0).tau4()/topJets.at(0).tau2(), genweight);
    if(topJets.at(0).tau1() != 0) DTGenTopJetTau4Tau1->Fill(topJets.at(0).tau4()/topJets.at(0).tau1(), genweight);

    if(gluons.size() > 0) {
      if(deltaR(gluons.at(0), topJets.at(0)) > 1.2) {
        if(topJets.at(0).tau1() != 0) DTNGGenTopJetTau2Tau1->Fill(topJets.at(0).tau2()/topJets.at(0).tau1(), genweight);
        if(topJets.at(0).tau2() != 0) DTNGGenTopJetTau3Tau2->Fill(topJets.at(0).tau3()/topJets.at(0).tau2(), genweight);
        if(topJets.at(0).tau1() != 0) DTNGGenTopJetTau3Tau1->Fill(topJets.at(0).tau3()/topJets.at(0).tau1(), genweight);
        if(topJets.at(0).tau3() != 0) DTNGGenTopJetTau4Tau3->Fill(topJets.at(0).tau4()/topJets.at(0).tau3(), genweight);
        if(topJets.at(0).tau2() != 0) DTNGGenTopJetTau4Tau2->Fill(topJets.at(0).tau4()/topJets.at(0).tau2(), genweight);
        if(topJets.at(0).tau1() != 0) DTNGGenTopJetTau4Tau1->Fill(topJets.at(0).tau4()/topJets.at(0).tau1(), genweight);
      }
    }

    /*
    GenTopJetTau1->Fill(topJets.at(1).tau1(), genweight);
    GenTopJetTau2->Fill(topJets.at(1).tau2(), genweight);
    GenTopJetTau3->Fill(topJets.at(1).tau3(), genweight);
    GenTopJetTau4->Fill(topJets.at(1).tau4(), genweight);
    */

    DTGenTopJetTau1->Fill(topJets.at(1).tau1(), genweight);
    DTGenTopJetTau2->Fill(topJets.at(1).tau2(), genweight);
    DTGenTopJetTau3->Fill(topJets.at(1).tau3(), genweight);
    DTGenTopJetTau4->Fill(topJets.at(1).tau4(), genweight);

    if(gluons.size() > 0) {
      if(deltaR(gluons.at(0), topJets.at(1)) > 1.2) {
        DTNGGenTopJetTau1->Fill(topJets.at(1).tau1(), genweight);
        DTNGGenTopJetTau2->Fill(topJets.at(1).tau2(), genweight);
        DTNGGenTopJetTau3->Fill(topJets.at(1).tau3(), genweight);
        DTNGGenTopJetTau4->Fill(topJets.at(1).tau4(), genweight);
      }
    }

    /*
    if(topJets.at(1).tau1() != 0) GenTopJetTau2Tau1->Fill(topJets.at(1).tau2()/topJets.at(1).tau1(), genweight);
    if(topJets.at(1).tau2() != 0) GenTopJetTau3Tau2->Fill(topJets.at(1).tau3()/topJets.at(1).tau2(), genweight);
    if(topJets.at(1).tau1() != 0) GenTopJetTau3Tau1->Fill(topJets.at(1).tau3()/topJets.at(1).tau1(), genweight);
    if(topJets.at(1).tau3() != 0) GenTopJetTau4Tau3->Fill(topJets.at(1).tau4()/topJets.at(1).tau3(), genweight);
    if(topJets.at(1).tau2() != 0) GenTopJetTau4Tau2->Fill(topJets.at(1).tau4()/topJets.at(1).tau2(), genweight);
    if(topJets.at(1).tau1() != 0) GenTopJetTau4Tau1->Fill(topJets.at(1).tau4()/topJets.at(1).tau1(), genweight);
    */

    if(topJets.at(1).tau1() != 0) DTGenTopJetTau2Tau1->Fill(topJets.at(1).tau2()/topJets.at(1).tau1(), genweight);
    if(topJets.at(1).tau2() != 0) DTGenTopJetTau3Tau2->Fill(topJets.at(1).tau3()/topJets.at(1).tau2(), genweight);
    if(topJets.at(1).tau1() != 0) DTGenTopJetTau3Tau1->Fill(topJets.at(1).tau3()/topJets.at(1).tau1(), genweight);
    if(topJets.at(1).tau3() != 0) DTGenTopJetTau4Tau3->Fill(topJets.at(1).tau4()/topJets.at(1).tau3(), genweight);
    if(topJets.at(1).tau2() != 0) DTGenTopJetTau4Tau2->Fill(topJets.at(1).tau4()/topJets.at(1).tau2(), genweight);
    if(topJets.at(1).tau1() != 0) DTGenTopJetTau4Tau1->Fill(topJets.at(1).tau4()/topJets.at(1).tau1(), genweight);

    if(gluons.size() > 0) {
      if(deltaR(gluons.at(0), topJets.at(1)) > 1.2) {
        if(topJets.at(1).tau1() != 0) DTNGGenTopJetTau2Tau1->Fill(topJets.at(1).tau2()/topJets.at(1).tau1(), genweight);
        if(topJets.at(1).tau2() != 0) DTNGGenTopJetTau3Tau2->Fill(topJets.at(1).tau3()/topJets.at(1).tau2(), genweight);
        if(topJets.at(1).tau1() != 0) DTNGGenTopJetTau3Tau1->Fill(topJets.at(1).tau3()/topJets.at(1).tau1(), genweight);
        if(topJets.at(1).tau3() != 0) DTNGGenTopJetTau4Tau3->Fill(topJets.at(1).tau4()/topJets.at(1).tau3(), genweight);
        if(topJets.at(1).tau2() != 0) DTNGGenTopJetTau4Tau2->Fill(topJets.at(1).tau4()/topJets.at(1).tau2(), genweight);
        if(topJets.at(1).tau1() != 0) DTNGGenTopJetTau4Tau1->Fill(topJets.at(1).tau4()/topJets.at(1).tau1(), genweight);
      }
    }

    DTGenDeltaRTopTop->Fill(deltaR(topJets.at(0), topJets.at(1)), genweight);

    if(debug) cout << "\t\t--- top subjet M ratios" << endl;

    GenTopSubjetSize->Fill(topSubjets_v4.at(0).size(), genweight);
    if(topJets_v4.at(0).Pt() == 0) GenTopPt0->Fill(1, genweight);

    GenTopSubjetSize->Fill(topSubjets_v4.at(1).size(), genweight);
    if(topJets_v4.at(1).Pt() == 0) GenTopPt0->Fill(1, genweight);

    /*
    if(topSubjets_v4.at(0).size() == 3 && topJets_v4.at(0).Pt() != 0) {
      GenTopSubjetPT1PT->Fill(topSubjets_v4.at(0).at(0).Pt()/topJets_v4.at(0).Pt(), genweight);
      GenTopSubjetPT2PT->Fill(topSubjets_v4.at(0).at(1).Pt()/topJets_v4.at(0).Pt(), genweight);
      GenTopSubjetPT3PT->Fill(topSubjets_v4.at(0).at(2).Pt()/topJets_v4.at(0).Pt(), genweight);
    }

    if(topSubjets_v4.at(1).size() == 3 && topJets_v4.at(1).Pt() != 0) {
      GenTopSubjetPT1PT->Fill(topSubjets_v4.at(1).at(0).Pt()/topJets_v4.at(1).Pt(), genweight);
      GenTopSubjetPT2PT->Fill(topSubjets_v4.at(1).at(1).Pt()/topJets_v4.at(1).Pt(), genweight);
      GenTopSubjetPT3PT->Fill(topSubjets_v4.at(1).at(2).Pt()/topJets_v4.at(1).Pt(), genweight);
    }
    */

    if(topSubjets_v4.at(0).size() == 3 && topJets_v4.at(0).Pt() != 0) {
      DTGenTopSubjetPT1PT->Fill(topSubjets_v4.at(0).at(0).Pt()/topJets_v4.at(0).Pt(), genweight);
      DTGenTopSubjetPT2PT->Fill(topSubjets_v4.at(0).at(1).Pt()/topJets_v4.at(0).Pt(), genweight);
      DTGenTopSubjetPT3PT->Fill(topSubjets_v4.at(0).at(2).Pt()/topJets_v4.at(0).Pt(), genweight);
    }

    if(topSubjets_v4.at(1).size() == 3 && topJets_v4.at(1).Pt() != 0) {
      DTGenTopSubjetPT1PT->Fill(topSubjets_v4.at(1).at(0).Pt()/topJets_v4.at(1).Pt(), genweight);
      DTGenTopSubjetPT2PT->Fill(topSubjets_v4.at(1).at(1).Pt()/topJets_v4.at(1).Pt(), genweight);
      DTGenTopSubjetPT3PT->Fill(topSubjets_v4.at(1).at(2).Pt()/topJets_v4.at(1).Pt(), genweight);
    }

    if(gluons.size() > 0) {
      if(deltaR(gluons.at(0), topJets.at(0)) > 1.2) {
        if(topSubjets_v4.at(0).size() == 3 && topJets_v4.at(0).Pt() != 0) {
          DTNGGenTopSubjetPT1PT->Fill(topSubjets_v4.at(0).at(0).Pt()/topJets_v4.at(0).Pt(), genweight);
          DTNGGenTopSubjetPT2PT->Fill(topSubjets_v4.at(0).at(1).Pt()/topJets_v4.at(0).Pt(), genweight);
          DTNGGenTopSubjetPT3PT->Fill(topSubjets_v4.at(0).at(2).Pt()/topJets_v4.at(0).Pt(), genweight);
        }
      }
    }

    if(gluons.size() > 0) {
      if(deltaR(gluons.at(0), topJets.at(1)) > 1.2) {
        if(topSubjets_v4.at(1).size() == 3 && topJets_v4.at(1).Pt() != 0) {
          DTNGGenTopSubjetPT1PT->Fill(topSubjets_v4.at(1).at(0).Pt()/topJets_v4.at(1).Pt(), genweight);
          DTNGGenTopSubjetPT2PT->Fill(topSubjets_v4.at(1).at(1).Pt()/topJets_v4.at(1).Pt(), genweight);
          DTNGGenTopSubjetPT3PT->Fill(topSubjets_v4.at(1).at(2).Pt()/topJets_v4.at(1).Pt(), genweight);
        }
      }
    }

    std::sort(topSubjets_v4.at(0).begin(), topSubjets_v4.at(0).end(), compareSubjetM);
    std::sort(topSubjets_v4.at(1).begin(), topSubjets_v4.at(1).end(), compareSubjetM);

    /*
    if(topSubjets_v4.at(0).size() == 3 && topJets_v4.at(0).M() != 0) {
      GenTopSubjetM1M->Fill(topSubjets_v4.at(0).at(0).M()/topJets_v4.at(0).M(), genweight);
      GenTopSubjetM2M->Fill(topSubjets_v4.at(0).at(1).M()/topJets_v4.at(0).M(), genweight);
      GenTopSubjetM3M->Fill(topSubjets_v4.at(0).at(2).M()/topJets_v4.at(0).M(), genweight);
    }

    if(topSubjets_v4.at(1).size() == 3 && topJets_v4.at(1).M() != 0) {
      GenTopSubjetM1M->Fill(topSubjets_v4.at(1).at(0).M()/topJets_v4.at(1).M(), genweight);
      GenTopSubjetM2M->Fill(topSubjets_v4.at(1).at(1).M()/topJets_v4.at(1).M(), genweight);
      GenTopSubjetM3M->Fill(topSubjets_v4.at(1).at(2).M()/topJets_v4.at(1).M(), genweight);
    }
    */

    if(topSubjets_v4.at(0).size() == 3 && topJets_v4.at(0).M() != 0) {
      DTGenTopSubjetM1M->Fill(topSubjets_v4.at(0).at(0).M()/topJets_v4.at(0).M(), genweight);
      DTGenTopSubjetM2M->Fill(topSubjets_v4.at(0).at(1).M()/topJets_v4.at(0).M(), genweight);
      DTGenTopSubjetM3M->Fill(topSubjets_v4.at(0).at(2).M()/topJets_v4.at(0).M(), genweight);
    }

    if(topSubjets_v4.at(1).size() == 3 && topJets_v4.at(1).M() != 0) {
      DTGenTopSubjetM1M->Fill(topSubjets_v4.at(1).at(0).M()/topJets_v4.at(1).M(), genweight);
      DTGenTopSubjetM2M->Fill(topSubjets_v4.at(1).at(1).M()/topJets_v4.at(1).M(), genweight);
      DTGenTopSubjetM3M->Fill(topSubjets_v4.at(1).at(2).M()/topJets_v4.at(1).M(), genweight);
    }

    if(gluons.size() > 0) {
      if(deltaR(gluons.at(0), topJets.at(0)) > 1.2) {
        if(topSubjets_v4.at(0).size() == 3 && topJets_v4.at(0).M() != 0) {
          DTNGGenTopSubjetM1M->Fill(topSubjets_v4.at(0).at(0).M()/topJets_v4.at(0).M(), genweight);
          DTNGGenTopSubjetM2M->Fill(topSubjets_v4.at(0).at(1).M()/topJets_v4.at(0).M(), genweight);
          DTNGGenTopSubjetM3M->Fill(topSubjets_v4.at(0).at(2).M()/topJets_v4.at(0).M(), genweight);
        }
      }
    }

    if(gluons.size() > 0) {
      if(deltaR(gluons.at(0), topJets.at(1)) > 1.2) {
        if(topSubjets_v4.at(1).size() == 3 && topJets_v4.at(1).M() != 0) {
          DTNGGenTopSubjetM1M->Fill(topSubjets_v4.at(1).at(0).M()/topJets_v4.at(1).M(), genweight);
          DTNGGenTopSubjetM2M->Fill(topSubjets_v4.at(1).at(1).M()/topJets_v4.at(1).M(), genweight);
          DTNGGenTopSubjetM3M->Fill(topSubjets_v4.at(1).at(2).M()/topJets_v4.at(1).M(), genweight);
        }
      }
    }

    if(deltaR(topJets.at(0), topJets.at(1)) < 1.2) {

      GenTopJet combinedTopJet;
      std::vector<GenJet> combinedSubjets = topJets.at(0).subjets();
      combinedSubjets.insert(combinedSubjets.end(), topJets.at(1).subjets().begin(), topJets.at(1).subjets().end());
      calculateNSubjettines(&combinedTopJet, combinedSubjets);

      GenTopJetCombinedTau1->Fill(combinedTopJet.tau1(), genweight);
      GenTopJetCombinedTau2->Fill(combinedTopJet.tau2(), genweight);
      GenTopJetCombinedTau3->Fill(combinedTopJet.tau3(), genweight);
      GenTopJetCombinedTau4->Fill(combinedTopJet.tau4(), genweight);

      if(debug) {
        cout << "\t\t combined tau1: " << combinedTopJet.tau1() << endl;
        cout << "\t\t combined tau2: " << combinedTopJet.tau2() << endl;
        cout << "\t\t combined tau3: " << combinedTopJet.tau3() << endl;
        cout << "\t\t combined tau4: " << combinedTopJet.tau4() << endl;
      }

      if(debug) cout << "\t\t--- top combined tau ratios" << endl;
      if(combinedTopJet.tau1() != 0) GenTopJetCombinedTau2Tau1->Fill(combinedTopJet.tau2()/combinedTopJet.tau1(), genweight);
      if(combinedTopJet.tau2() != 0) GenTopJetCombinedTau3Tau2->Fill(combinedTopJet.tau3()/combinedTopJet.tau2(), genweight);
      if(combinedTopJet.tau1() != 0) GenTopJetCombinedTau3Tau1->Fill(combinedTopJet.tau3()/combinedTopJet.tau1(), genweight);
      if(combinedTopJet.tau3() != 0) GenTopJetCombinedTau4Tau3->Fill(combinedTopJet.tau4()/combinedTopJet.tau3(), genweight);
      if(combinedTopJet.tau2() != 0) GenTopJetCombinedTau4Tau2->Fill(combinedTopJet.tau4()/combinedTopJet.tau2(), genweight);
      if(combinedTopJet.tau1() != 0) GenTopJetCombinedTau4Tau1->Fill(combinedTopJet.tau4()/combinedTopJet.tau1(), genweight);


      std::vector<TH1F*> GenTopJetCombinedOnlyTaus = {GenTopJetCombinedOnlyTau1, GenTopJetCombinedOnlyTau2, GenTopJetCombinedOnlyTau3, GenTopJetCombinedOnlyTau4, GenTopJetCombinedOnlyTau2Tau1, GenTopJetCombinedOnlyTau3Tau2, GenTopJetCombinedOnlyTau3Tau1, GenTopJetCombinedOnlyTau4Tau3, GenTopJetCombinedOnlyTau4Tau2, GenTopJetCombinedOnlyTau4Tau1};
      fillTauHists(GenTopJetCombinedOnlyTaus, combinedTopJet, genweight);

      std::vector<TH1F*> GenTopJet1Taus = {GenTopJet1Tau1, GenTopJet1Tau2, GenTopJet1Tau3, GenTopJet1Tau4, GenTopJet1Tau2Tau1, GenTopJet1Tau3Tau2, GenTopJet1Tau3Tau1, GenTopJet1Tau4Tau3, GenTopJet1Tau4Tau2, GenTopJet1Tau4Tau1};
      fillTauHists(GenTopJet1Taus, topJets.at(0), genweight);

      std::vector<TH1F*> GenTopJet2Taus = {GenTopJet2Tau1, GenTopJet2Tau2, GenTopJet2Tau3, GenTopJet2Tau4, GenTopJet2Tau2Tau1, GenTopJet2Tau3Tau2, GenTopJet2Tau3Tau1, GenTopJet2Tau4Tau3, GenTopJet2Tau4Tau2, GenTopJet2Tau4Tau1};
      fillTauHists(GenTopJet2Taus, topJets.at(1), genweight);

      std::vector<TH1F*> GenTopJet12Taus = {GenTopJet12Tau1, GenTopJet12Tau2, GenTopJet12Tau3, GenTopJet12Tau4, GenTopJet12Tau2Tau1, GenTopJet12Tau3Tau2, GenTopJet12Tau3Tau1, GenTopJet12Tau4Tau3, GenTopJet12Tau4Tau2, GenTopJet12Tau4Tau1};
      fillTauHists(GenTopJet12Taus, topJets.at(0), genweight);
      fillTauHists(GenTopJet12Taus, topJets.at(1), genweight);

    } else {

      GenTopJetCombinedTau1->Fill(topJets.at(0).tau1(), genweight);
      GenTopJetCombinedTau2->Fill(topJets.at(0).tau2(), genweight);
      GenTopJetCombinedTau3->Fill(topJets.at(0).tau3(), genweight);
      GenTopJetCombinedTau4->Fill(topJets.at(0).tau4(), genweight);

      if(debug) cout << "\t\t--- top combined tau ratios" << endl;
      if(topJets.at(0).tau1() != 0) GenTopJetCombinedTau2Tau1->Fill(topJets.at(0).tau2()/topJets.at(0).tau1(), genweight);
      if(topJets.at(0).tau2() != 0) GenTopJetCombinedTau3Tau2->Fill(topJets.at(0).tau3()/topJets.at(0).tau2(), genweight);
      if(topJets.at(0).tau1() != 0) GenTopJetCombinedTau3Tau1->Fill(topJets.at(0).tau3()/topJets.at(0).tau1(), genweight);
      if(topJets.at(0).tau3() != 0) GenTopJetCombinedTau4Tau3->Fill(topJets.at(0).tau4()/topJets.at(0).tau3(), genweight);
      if(topJets.at(0).tau2() != 0) GenTopJetCombinedTau4Tau2->Fill(topJets.at(0).tau4()/topJets.at(0).tau2(), genweight);
      if(topJets.at(0).tau1() != 0) GenTopJetCombinedTau4Tau1->Fill(topJets.at(0).tau4()/topJets.at(0).tau1(), genweight);

      GenTopJetCombinedTau1->Fill(topJets.at(1).tau1(), genweight);
      GenTopJetCombinedTau2->Fill(topJets.at(1).tau2(), genweight);
      GenTopJetCombinedTau3->Fill(topJets.at(1).tau3(), genweight);
      GenTopJetCombinedTau4->Fill(topJets.at(1).tau4(), genweight);

      if(topJets.at(1).tau1() != 0) GenTopJetCombinedTau2Tau1->Fill(topJets.at(1).tau2()/topJets.at(1).tau1(), genweight);
      if(topJets.at(1).tau2() != 0) GenTopJetCombinedTau3Tau2->Fill(topJets.at(1).tau3()/topJets.at(1).tau2(), genweight);
      if(topJets.at(1).tau1() != 0) GenTopJetCombinedTau3Tau1->Fill(topJets.at(1).tau3()/topJets.at(1).tau1(), genweight);
      if(topJets.at(1).tau3() != 0) GenTopJetCombinedTau4Tau3->Fill(topJets.at(1).tau4()/topJets.at(1).tau3(), genweight);
      if(topJets.at(1).tau2() != 0) GenTopJetCombinedTau4Tau2->Fill(topJets.at(1).tau4()/topJets.at(1).tau2(), genweight);
      if(topJets.at(1).tau1() != 0) GenTopJetCombinedTau4Tau1->Fill(topJets.at(1).tau4()/topJets.at(1).tau1(), genweight);

      /*
      GenTopJetCombinedOnlyTau1->Fill(topJets.at(0).tau1(), genweight);
      GenTopJetCombinedOnlyTau2->Fill(topJets.at(0).tau2(), genweight);
      GenTopJetCombinedOnlyTau3->Fill(topJets.at(0).tau3(), genweight);
      GenTopJetCombinedOnlyTau4->Fill(topJets.at(0).tau4(), genweight);

      if(debug) cout << "\t\t--- top combined tau ratios" << endl;
      if(topJets.at(0).tau1() != 0) GenTopJetCombinedOnlyTau2Tau1->Fill(topJets.at(0).tau2()/topJets.at(0).tau1(), genweight);
      if(topJets.at(0).tau2() != 0) GenTopJetCombinedOnlyTau3Tau2->Fill(topJets.at(0).tau3()/topJets.at(0).tau2(), genweight);
      if(topJets.at(0).tau1() != 0) GenTopJetCombinedOnlyTau3Tau1->Fill(topJets.at(0).tau3()/topJets.at(0).tau1(), genweight);
      if(topJets.at(0).tau3() != 0) GenTopJetCombinedOnlyTau4Tau3->Fill(topJets.at(0).tau4()/topJets.at(0).tau3(), genweight);
      if(topJets.at(0).tau2() != 0) GenTopJetCombinedOnlyTau4Tau2->Fill(topJets.at(0).tau4()/topJets.at(0).tau2(), genweight);
      if(topJets.at(0).tau1() != 0) GenTopJetCombinedOnlyTau4Tau1->Fill(topJets.at(0).tau4()/topJets.at(0).tau1(), genweight);

      
      GenTopJetCombinedOnlyTau1->Fill(topJets.at(1).tau1(), genweight);
      GenTopJetCombinedOnlyTau2->Fill(topJets.at(1).tau2(), genweight);
      GenTopJetCombinedOnlyTau3->Fill(topJets.at(1).tau3(), genweight);
      GenTopJetCombinedOnlyTau4->Fill(topJets.at(1).tau4(), genweight);

      if(topJets.at(1).tau1() != 0) GenTopJetCombinedOnlyTau2Tau1->Fill(topJets.at(1).tau2()/topJets.at(1).tau1(), genweight);
      if(topJets.at(1).tau2() != 0) GenTopJetCombinedOnlyTau3Tau2->Fill(topJets.at(1).tau3()/topJets.at(1).tau2(), genweight);
      if(topJets.at(1).tau1() != 0) GenTopJetCombinedOnlyTau3Tau1->Fill(topJets.at(1).tau3()/topJets.at(1).tau1(), genweight);
      if(topJets.at(1).tau3() != 0) GenTopJetCombinedOnlyTau4Tau3->Fill(topJets.at(1).tau4()/topJets.at(1).tau3(), genweight);
      if(topJets.at(1).tau2() != 0) GenTopJetCombinedOnlyTau4Tau2->Fill(topJets.at(1).tau4()/topJets.at(1).tau2(), genweight);
      if(topJets.at(1).tau1() != 0) GenTopJetCombinedOnlyTau4Tau1->Fill(topJets.at(1).tau4()/topJets.at(1).tau1(), genweight);
      */

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

    if(botPassed && q1Passed && q2Passed) {
      DTGenTopJetM_EachQuarkMatched->Fill(topJet_v4_combined.M(), genweight);
      float dR1 = 10;
      float dR2 = 10;
      if(gluons.size() > 0) {
        dR1 = deltaR(gluons.at(0), topJets.at(0));
        dR2 = deltaR(gluons.at(0), topJets.at(1));
      }
      if(dR1 < 1.2 || dR2 < 1.2) {
        DTGenTopJetM_EachQuarkMatched_GluonMatched->Fill(topJet_v4_combined.M(), genweight);
      } else {
        DTGenTopJetM_EachQuarkMatched_NoGluonMatched->Fill(topJet_v4_combined.M(), genweight);
      }
    }

    if(topJets_v4.at(0).M() != 0) DTGenTopJetMRatio->Fill(topJets_v4.at(1).M()/topJets_v4.at(0).M(), genweight);
    if(topJets_v4.at(0).Pt() != 0) DTGenTopJetpTRatio->Fill(topJets_v4.at(1).Pt()/topJets_v4.at(0).Pt(), genweight);

  }

  if(jets.size() > 1) {
    float dRJet1Jet2 = deltaR(jets.at(0), jets.at(1));

    LorentzVector combinedJet;

    bool botPassed = false;
    bool q1Passed = false;
    bool q2Passed = false;

    GenDeltaRJets->Fill(dRJet1Jet2);

    if(debug) cout << "\t\t--- dR 1.2" << endl;
    if(dRJet1Jet2 < 1.2) {
      GenTopJetLeadingM_dR12->Fill(jets_v4.at(0).M(), genweight);
      GenTopJetSubLeadingM_dR12->Fill(jets_v4.at(1).M(), genweight);
      if(topJets.size() == 1) {
        GenTopJetM_dR12->Fill(topJets_v4.at(0).M(), genweight);
      } else if(topJets.size() == 2) {
        combinedJet_v4 = topJets_v4.at(0) + topJets_v4.at(1);
        GenTopJetM_dR12->Fill(combinedJet_v4.M(), genweight);
      }
      if(debug) cout << "\t\t--- combine jets_v4" << endl;
      combinedJet_v4 = jets_v4.at(0) + jets_v4.at(1);
      if(debug) cout << "\t\t--- set Lorentzvector" << endl;
      combinedJet.SetPxPyPzE(combinedJet_v4.Px(), combinedJet_v4.Py(), combinedJet_v4.Pz(), combinedJet_v4.E());
      if(debug) cout << "\t\t--- Fill combinedJet_v4" << endl;
      if(deltaR(top, jets.at(0)) < 1.2 && deltaR(top, jets.at(1)) < 1.2) { 
        GenJetM_dR12->Fill(combinedJet_v4.M(), genweight);
        botPassed = deltaR(bot, jets.at(0)) < 1.2 || deltaR(bot, jets.at(1)) < 1.2;
        q1Passed = deltaR(q1, jets.at(0)) < 1.2 || deltaR(q1, jets.at(1)) < 1.2;
        q2Passed = deltaR(q2, jets.at(0)) < 1.2 || deltaR(q2, jets.at(1)) < 1.2;
        if(botPassed && q1Passed && q2Passed) { 
          GenJetM_dR12_AllQuarksMatched->Fill(combinedJet_v4.M(), genweight);
          if(gluons.size() > 0) {
            double dRGluonTop1 = deltaR(gluons.at(0), jets.at(0));
            double dRGluonTop2 = deltaR(gluons.at(0), jets.at(1));
            if(dRGluonTop1 > 1.2 && dRGluonTop2 > 1.2) {
              GenJetM_dR12_AllQuarksMatched_NoGluon->Fill(combinedJet_v4.M(), genweight);
            } else if(dRGluonTop1 > 1.2 && dRGluonTop2 <= 1.2) {
              GenJetM_dR12_AllQuarksMatched_NoGluon->Fill(jets_v4.at(0).M(), genweight);
              GenJetM_dR12_AllQuarksMatched_Gluon->Fill(jets_v4.at(1).M(), genweight);
            }else if(dRGluonTop1 <= 1.2 && dRGluonTop2 > 1.2) {
              GenJetM_dR12_AllQuarksMatched_Gluon->Fill(jets_v4.at(0).M(), genweight);
              GenJetM_dR12_AllQuarksMatched_NoGluon->Fill(jets_v4.at(1).M(), genweight);
            } else {
              GenJetM_dR12_AllQuarksMatched_Gluon->Fill(jets_v4.at(0).M(), genweight);
              GenJetM_dR12_AllQuarksMatched_Gluon->Fill(jets_v4.at(1).M(), genweight);
            }
          }
        }
      }
    } else {
      if(debug) cout << "\t\t--- Fill topJets_v4" << endl;
      if(topJets.size() > 0) {
        GenJetM_dR12->Fill(topJets_v4.at(0).M(), genweight);
        botPassed = deltaR(bot, topJets.at(0)) < 1.2;
        q1Passed = deltaR(q1, topJets.at(0)) < 1.2;
        q2Passed = deltaR(q2, topJets.at(0)) < 1.2;
        if(botPassed && q1Passed && q2Passed) {
          GenJetM_dR12_AllQuarksMatched->Fill(topJets_v4.at(0).M(), genweight);
          if(gluons.size() > 0) {
            if(deltaR(gluons.at(0), topJets.at(0)) > 1.2) {
              GenJetM_dR12_AllQuarksMatched_NoGluon->Fill(topJets_v4.at(0).M(), genweight);
            } else {
              GenJetM_dR12_AllQuarksMatched_Gluon->Fill(topJets_v4.at(0).M(), genweight);
            }
          }
        }
      }
    }

    if(debug) cout << "\t\t--- dR 0.8" << endl;
    if(dRJet1Jet2 < 0.8) {
      GenTopJetLeadingM_dR08->Fill(jets_v4.at(0).M(), genweight);
      GenTopJetSubLeadingM_dR08->Fill(jets_v4.at(1).M(), genweight);
      if(topJets.size() == 1) {
        GenTopJetM_dR08->Fill(topJets_v4.at(0).M(), genweight);
      } else if(topJets.size() == 2) {
        combinedJet_v4 = topJets_v4.at(0) + topJets_v4.at(1);
        GenTopJetM_dR08->Fill(combinedJet_v4.M(), genweight);
      }
      combinedJet_v4 = jets_v4.at(0) + jets_v4.at(1);
      combinedJet.SetPxPyPzE(combinedJet_v4.Px(), combinedJet_v4.Py(), combinedJet_v4.Pz(), combinedJet_v4.E());
      if(deltaR(top, combinedJet) < 1.2) { 
        GenJetM_dR08->Fill(combinedJet_v4.M(), genweight);
        botPassed = deltaR(bot, jets.at(0)) < 1.2 || deltaR(bot, jets.at(1)) < 1.2;
        q1Passed = deltaR(q1, jets.at(0)) < 1.2 || deltaR(q1, jets.at(1)) < 1.2;
        q2Passed = deltaR(q2, jets.at(0)) < 1.2 || deltaR(q2, jets.at(1)) < 1.2;
        if(botPassed && q1Passed && q2Passed) GenJetM_dR08_AllQuarksMatched->Fill(combinedJet_v4.M(), genweight);
      }
    } else {
      if(topJets.size() > 0) {
        GenJetM_dR08->Fill(topJets_v4.at(0).M(), genweight);
        botPassed = deltaR(bot, topJets.at(0)) < 1.2;
        q1Passed = deltaR(q1, topJets.at(0)) < 1.2;
        q2Passed = deltaR(q2, topJets.at(0)) < 1.2;
        if(botPassed && q1Passed && q2Passed) GenJetM_dR08_AllQuarksMatched->Fill(topJets_v4.at(0).M(), genweight);
      }
    }

    if(debug) cout << "\t\t--- dR 0.4" << endl;
    if(dRJet1Jet2 < 0.4) {
      GenTopJetLeadingM_dR04->Fill(jets_v4.at(0).M(), genweight);
      GenTopJetSubLeadingM_dR04->Fill(jets_v4.at(1).M(), genweight);
      if(topJets.size() == 1) {
        GenTopJetM_dR04->Fill(topJets_v4.at(0).M(), genweight);
      } else if(topJets.size() == 2) {
        combinedJet_v4 = topJets_v4.at(0) + topJets_v4.at(1);
        GenTopJetM_dR04->Fill(combinedJet_v4.M(), genweight);
      }
      combinedJet_v4 = jets_v4.at(0) + jets_v4.at(1);
      combinedJet.SetPxPyPzE(combinedJet_v4.Px(), combinedJet_v4.Py(), combinedJet_v4.Pz(), combinedJet_v4.E());
      if(deltaR(top, combinedJet) < 1.2) {
        GenJetM_dR04->Fill(combinedJet_v4.M(), genweight);
        botPassed = deltaR(bot, jets.at(0)) < 1.2 || deltaR(bot, jets.at(1)) < 1.2;
        q1Passed = deltaR(q1, jets.at(0)) < 1.2 || deltaR(q1, jets.at(1)) < 1.2;
        q2Passed = deltaR(q2, jets.at(0)) < 1.2 || deltaR(q2, jets.at(1)) < 1.2;
        if(botPassed && q1Passed && q2Passed) GenJetM_dR04_AllQuarksMatched->Fill(combinedJet_v4.M(), genweight);
      }
    } else {
      if(topJets.size() > 0) {
        GenJetM_dR04->Fill(topJets_v4.at(0).M(), genweight);
        botPassed = deltaR(bot, topJets.at(0)) < 1.2;
        q1Passed = deltaR(q1, topJets.at(0)) < 1.2;
        q2Passed = deltaR(q2, topJets.at(0)) < 1.2;
        if(botPassed && q1Passed && q2Passed) GenJetM_dR04_AllQuarksMatched->Fill(topJets_v4.at(0).M(), genweight);
      }
    }

    if(debug) cout << "\t\t--- dRvaried 600" << endl;
    combinedJet_v4 = jets_v4.at(0) + jets_v4.at(1);

    if(combinedJet_v4.Pt() != 0 && dRJet1Jet2 < 600/combinedJet_v4.Pt()) {
      GenTopJetLeadingM_dRvaried600->Fill(jets_v4.at(0).M(), genweight);
      GenTopJetSubLeadingM_dRvaried600->Fill(jets_v4.at(1).M(), genweight);
      if(topJets.size() == 1) {
        GenTopJetM_dRvaried600->Fill(topJets_v4.at(0).M(), genweight);
      } else if(topJets.size() == 2) {
        combinedJet_v4 = topJets_v4.at(0) + topJets_v4.at(1);
        GenTopJetM_dRvaried600->Fill(combinedJet_v4.M(), genweight);
      }
      combinedJet_v4 = jets_v4.at(0) + jets_v4.at(1);
      combinedJet.SetPxPyPzE(combinedJet_v4.Px(), combinedJet_v4.Py(), combinedJet_v4.Pz(), combinedJet_v4.E());
      if(deltaR(top, combinedJet) < 1.2) {
        GenJetM_dRvaried600->Fill(combinedJet_v4.M(), genweight);
        botPassed = deltaR(bot, jets.at(0)) < 1.2 || deltaR(bot, jets.at(1)) < 1.2;
        q1Passed = deltaR(q1, jets.at(0)) < 1.2 || deltaR(q1, jets.at(1)) < 1.2;
        q2Passed = deltaR(q2, jets.at(0)) < 1.2 || deltaR(q2, jets.at(1)) < 1.2;
        if(botPassed && q1Passed && q2Passed) GenJetM_dRvaried600_AllQuarksMatched->Fill(combinedJet_v4.M(), genweight);
      }
    } else {
      if(topJets.size() > 0) {
        GenJetM_dRvaried600->Fill(topJets_v4.at(0).M(), genweight);
        botPassed = deltaR(bot, topJets.at(0)) < 1.2;
        q1Passed = deltaR(q1, topJets.at(0)) < 1.2;
        q2Passed = deltaR(q2, topJets.at(0)) < 1.2;
        if(botPassed && q1Passed && q2Passed) GenJetM_dRvaried600_AllQuarksMatched->Fill(topJets_v4.at(0).M(), genweight);
      }
    }

    if(debug) cout << "\t\t--- dRvaried 450" << endl;
    if(combinedJet_v4.Pt() != 0 && dRJet1Jet2 < 450/combinedJet_v4.Pt()) {
      GenTopJetLeadingM_dRvaried450->Fill(jets_v4.at(0).M(), genweight);
      GenTopJetSubLeadingM_dRvaried450->Fill(jets_v4.at(1).M(), genweight);
      if(topJets.size() == 1) {
        GenTopJetM_dRvaried450->Fill(topJets_v4.at(0).M(), genweight);
      } else if(topJets.size() == 2) {
        combinedJet_v4 = topJets_v4.at(0) + topJets_v4.at(1);
        GenTopJetM_dRvaried450->Fill(combinedJet_v4.M(), genweight);
      }
      combinedJet_v4 = jets_v4.at(0) + jets_v4.at(1);
      combinedJet.SetPxPyPzE(combinedJet_v4.Px(), combinedJet_v4.Py(), combinedJet_v4.Pz(), combinedJet_v4.E());
      if(deltaR(top, combinedJet) < 1.2) {
        GenJetM_dRvaried450->Fill(combinedJet_v4.M(), genweight);
        botPassed = deltaR(bot, jets.at(0)) < 1.2 || deltaR(bot, jets.at(1)) < 1.2;
        q1Passed = deltaR(q1, jets.at(0)) < 1.2 || deltaR(q1, jets.at(1)) < 1.2;
        q2Passed = deltaR(q2, jets.at(0)) < 1.2 || deltaR(q2, jets.at(1)) < 1.2;
        if(botPassed && q1Passed && q2Passed) GenJetM_dRvaried450_AllQuarksMatched->Fill(combinedJet_v4.M(), genweight);
      }
    } else {
      if(topJets.size() > 0) {
        GenJetM_dRvaried450->Fill(topJets_v4.at(0).M(), genweight);
        botPassed = deltaR(bot, topJets.at(0)) < 1.2;
        q1Passed = deltaR(q1, topJets.at(0)) < 1.2;
        q2Passed = deltaR(q2, topJets.at(0)) < 1.2;
        if(botPassed && q1Passed && q2Passed) GenJetM_dRvaried450_AllQuarksMatched->Fill(topJets_v4.at(0).M(), genweight);
      }
    }

    if(debug) cout << "\t\t--- dRvaried 350" << endl;
    if(combinedJet_v4.Pt() != 0 && dRJet1Jet2 < 350/combinedJet_v4.Pt()) {
      GenTopJetLeadingM_dRvaried350->Fill(jets_v4.at(0).M(), genweight);
      GenTopJetSubLeadingM_dRvaried350->Fill(jets_v4.at(1).M(), genweight);
      if(topJets.size() == 1) {
        GenTopJetM_dRvaried350->Fill(topJets_v4.at(0).M(), genweight);
      } else if(topJets.size() == 2) {
        combinedJet_v4 = topJets_v4.at(0) + topJets_v4.at(1);
        GenTopJetM_dRvaried350->Fill(combinedJet_v4.M(), genweight);
      }
      combinedJet_v4 = jets_v4.at(0) + jets_v4.at(1);
      combinedJet.SetPxPyPzE(combinedJet_v4.Px(), combinedJet_v4.Py(), combinedJet_v4.Pz(), combinedJet_v4.E());
      if(deltaR(top, combinedJet) < 1.2) {
        GenJetM_dRvaried350->Fill(combinedJet_v4.M(), genweight);
        botPassed = deltaR(bot, jets.at(0)) < 1.2 || deltaR(bot, jets.at(1)) < 1.2;
        q1Passed = deltaR(q1, jets.at(0)) < 1.2 || deltaR(q1, jets.at(1)) < 1.2;
        q2Passed = deltaR(q2, jets.at(0)) < 1.2 || deltaR(q2, jets.at(1)) < 1.2;
        if(botPassed && q1Passed && q2Passed) GenJetM_dRvaried350_AllQuarksMatched->Fill(combinedJet_v4.M(), genweight);
      }
    } else {
      if(topJets.size() > 0) {
        GenJetM_dRvaried350->Fill(topJets_v4.at(0).M(), genweight);
        botPassed = deltaR(bot, topJets.at(0)) < 1.2;
        q1Passed = deltaR(q1, topJets.at(0)) < 1.2;
        q2Passed = deltaR(q2, topJets.at(0)) < 1.2;
        if(botPassed && q1Passed && q2Passed) GenJetM_dRvaried350_AllQuarksMatched->Fill(topJets_v4.at(0).M(), genweight);
      }
    }

    if(debug) cout << "--- pre gluon plots" << endl;

    GenGluonNumber->Fill(gluons.size(), genweight);

    if(gluons.size() > 0) {
      GenDeltaRGluonTop->Fill(deltaR(gluons.at(0), top), genweight);
    }

    if(debug) cout << "--- pre new gluon plots" << endl;

    GenDeltaRTopAntitop->Fill(deltaR(top, antitop), genweight);
    if(gluons.size() > 0) GenDeltaRTopGluonDeltaRTopAntitop->Fill(deltaR(top, gluons.at(0)), deltaR(top, antitop), genweight);

    botPassed = false;
    q1Passed = false;
    q2Passed = false;
    bool allPassed = false;
    bool gluonInJet = false;

    jet1_v4.SetPxPyPzE(jets.at(0).v4().Px(), jets.at(0).v4().Py(), jets.at(0).v4().Pz(), jets.at(0).v4().E());
    jet2_v4.SetPxPyPzE(jets.at(1).v4().Px(), jets.at(1).v4().Py(), jets.at(1).v4().Pz(), jets.at(1).v4().E());
    if(deltaR(jets.at(0), jets.at(1)) < 1.2) {
      jet1_v4 += jet2_v4;
      botPassed = deltaR(bot, jets.at(0)) <= jetradius || deltaR(bot, jets.at(1)) <= jetradius;
      q1Passed = deltaR(q1, jets.at(0)) <= jetradius || deltaR(q1, jets.at(1)) <= jetradius;
      q2Passed = deltaR(q2, jets.at(0)) <= jetradius || deltaR(q2, jets.at(1)) <= jetradius;
      if(gluons.size()>0) gluonInJet = deltaR(gluons.at(0), jets.at(0)) <= jetradius || deltaR(gluons.at(0), jets.at(1)) <= jetradius;
    } else {
      botPassed = deltaR(bot, jets.at(0)) <= jetradius;
      q1Passed = deltaR(q1, jets.at(0)) <= jetradius;
      q2Passed = deltaR(q2, jets.at(0)) <= jetradius;
      if(gluons.size()>0) gluonInJet = deltaR(gluons.at(0), jets.at(0)) <= jetradius;
    }

    allPassed = botPassed && q1Passed && q2Passed;

    if(botPassed && !q1Passed && !q2Passed) {
      GenJet1MassBot->Fill(jet1_v4.M(), genweight);
      if(gluonInJet) GenJet1MassGluonBot->Fill(jet1_v4.M(), genweight);
    }

    if(botPassed && ((q1Passed && !q2Passed) || (!q1Passed && q2Passed))) {
      GenJet1MassBotOneLightQ->Fill(jet1_v4.M(), genweight);
      if(gluonInJet) GenJet1MassGluonBotOneLightQ->Fill(jet1_v4.M(), genweight);
    }

    if((botPassed && !(q1Passed || q2Passed)) || (!botPassed && ((q1Passed && !q2Passed) || (!q1Passed && q2Passed)))) {
      GenJet1MassOneQ->Fill(jet1_v4.M(), genweight);
      if(gluonInJet) GenJet1MassGluonOneQ->Fill(jet1_v4.M(), genweight);
    }

    if(!botPassed && q1Passed && q2Passed) {
      GenJet1MassTwoLightQ->Fill(jet1_v4.M(), genweight);
      if(gluonInJet) GenJet1MassGluonTwoLightQ->Fill(jet1_v4.M(), genweight);
    }

    if(!botPassed && !q1Passed && !q2Passed) {
      GenJet1MassNoQ->Fill(jet1_v4.M(), genweight);
      if(gluonInJet) GenJet1MassGluonNoQ->Fill(jet1_v4.M(), genweight);
    }

    if(allPassed) {
      //GenJet1MassAll->Fill(jet1_v4.M(), genweight);
      if(gluonInJet) GenJet1MassGluonAll->Fill(jet1_v4.M(), genweight);
    }

  }

  bool botPassed1;
  bool botPassed2;
  bool q1Passed1;
  bool q1Passed2;
  bool q2Passed1;
  bool q2Passed2;

  GenTopJet combinedTopJet, combinedTopJetMatched, combinedTopJetUnmatched, combined4TopJetMatched, tmpTopJet1, tmpTopJet2, tmpTopJet3;

  if(jets.size()>1) {

    combinedJet_v4 = jets_v4.at(0) + jets_v4.at(1);


    if(deltaR(jets.at(0), jets.at(1)) < jetradius) {

      GenJetMassNearCombined->Fill(combinedJet_v4.M(), genweight);

    } else {

      GenJetMassNearCombined->Fill(jets_v4.at(0).M(), genweight);
      
    }

    botPassed1 = deltaR(bot, jets.at(0)) < jetradius;
    botPassed2 = deltaR(bot, jets.at(1)) < jetradius;
    q1Passed1 = deltaR(q1, jets.at(0)) < jetradius;
    q1Passed2 = deltaR(q1, jets.at(1)) < jetradius;
    q2Passed1 = deltaR(q2, jets.at(0)) < jetradius;
    q2Passed2 = deltaR(q2, jets.at(1)) < jetradius;

    std::vector<GenJet> combinedSubjets = jets.at(0).subjets();
    combinedSubjets.insert(combinedSubjets.end(), jets.at(1).subjets().begin(), jets.at(1).subjets().end());
    std::sort(combinedSubjets.begin(), combinedSubjets.end(), compareSubjetPtGenJet);

    std::vector<GenJet> combinedSubjetsMatched, combinedSubjetsUnmatched, combined4SubjetsMatched, combined4SubjetsUnmatched;
    std::vector<bool> matchedQuarksInSubjets = {false, false, false, false, false};
    std::vector<bool> matchedQuarksIn4Subjets = {false, false, false, false, false};
    matchedSubjets(&combinedSubjetsMatched, &combinedSubjetsUnmatched, &matchedQuarksInSubjets, combinedSubjets, quarks, 3);
    matchedSubjets(&combined4SubjetsMatched, &combined4SubjetsUnmatched, &matchedQuarksIn4Subjets, combinedSubjets, quarks, 4);

    combinedTopJetMatched = combine->CreateTopJetFromSubjets_gen(combinedSubjetsMatched, 0, 2.5);
    combined4TopJetMatched = combine->CreateTopJetFromSubjets_gen(combined4SubjetsMatched, 0, 2.5);
    combinedTopJetUnmatched = combine->CreateTopJetFromSubjets_gen(combinedSubjetsUnmatched, 0, 2.5);
    TLorentzVector combinedTopJetMatched_v4, combinedTopJetUnmatched_v4, combined4TopJetMatched_v4;
    combinedTopJetMatched_v4.SetPxPyPzE(combinedTopJetMatched.v4().Px(), combinedTopJetMatched.v4().Py(), combinedTopJetMatched.v4().Pz(), combinedTopJetMatched.v4().E());
    combinedTopJetUnmatched_v4.SetPxPyPzE(combinedTopJetUnmatched.v4().Px(), combinedTopJetUnmatched.v4().Py(), combinedTopJetUnmatched.v4().Pz(), combinedTopJetUnmatched.v4().E());
    combined4TopJetMatched_v4.SetPxPyPzE(combined4TopJetMatched.v4().Px(), combined4TopJetMatched.v4().Py(), combined4TopJetMatched.v4().Pz(), combined4TopJetMatched.v4().E());

    calculateNSubjettines(&combinedTopJetMatched, combinedSubjetsMatched);
    calculateNSubjettines(&combinedTopJetUnmatched, combinedSubjetsUnmatched);
    calculateNSubjettines(&combinedTopJet, combinedSubjets);

    std::vector<bool> multipleSubjetsToQuarkMatched = {false, false, false};
    std::vector<int> numberOfMatchedSubjets = {0,0,0};
    for(uint i=0; i<quarks.size(); i++) {
      for(uint j=0; j<combinedSubjets.size(); j++) {
        if(deltaR(quarks.at(i), combinedSubjets.at(j)) < subjetRadius) {
          numberOfMatchedSubjets.at(i)++;
        }
      }
      if(numberOfMatchedSubjets.at(i) > 1) multipleSubjetsToQuarkMatched.at(i) = true;
    }

    
    /*combinedSubjets.resize(5);
    calculateNSubjettines(&tmpTopJet1, combinedSubjets);
    combinedSubjets.resize(4);
    calculateNSubjettines(&tmpTopJet2, combinedSubjets);
    combinedSubjets.resize(3);
    calculateNSubjettines(&tmpTopJet3, combinedSubjets);*/

    if((botPassed1 && botPassed2) || (q1Passed1 && q1Passed2) || (q2Passed1 && q2Passed2)) GenDecayProductInBothJets->Fill(combinedJet_v4.M(), genweight);

    if(botPassed1 && q1Passed1 && q2Passed1 && !botPassed2 && !q1Passed2 && !q2Passed2) {
      GenOneJetMassAll->Fill(jets_v4.at(0).M(), genweight);
      GenOneJetMassAllDRJet12->Fill(jets_v4.at(0).M(), deltaR(jets.at(0), jets.at(1)), genweight);
      GenJet1MassAll->Fill(jets_v4.at(0).M(), genweight);

      GenJetMassSingleJet->Fill(jets_v4.at(0).M(), genweight);

      std::vector<TH1F*> GenOneJetAllTaus = {GenOneJetAllTau1, GenOneJetAllTau2, GenOneJetAllTau3, GenOneJetAllTau4, GenOneJetAllTau2Tau1, GenOneJetAllTau3Tau2, GenOneJetAllTau3Tau1, GenOneJetAllTau4Tau3, GenOneJetAllTau4Tau2, GenOneJetAllTau4Tau1};
      fillTauHists(GenOneJetAllTaus, jets.at(0), genweight);
    }

    if(!botPassed1 && !q1Passed1 && !q2Passed1 && botPassed2 && q1Passed2 && q2Passed2) {
      GenOneJetMassAll->Fill(jets_v4.at(1).M(), genweight);
      GenOneJetMassAllDRJet12->Fill(jets_v4.at(1).M(), deltaR(jets.at(0), jets.at(1)), genweight);
      GenJet1MassAll->Fill(jets_v4.at(1).M(), genweight);

      GenJetMassSingleJet->Fill(jets_v4.at(1).M(), genweight);

      std::vector<TH1F*> GenOneJetAllTaus = {GenOneJetAllTau1, GenOneJetAllTau2, GenOneJetAllTau3, GenOneJetAllTau4, GenOneJetAllTau2Tau1, GenOneJetAllTau3Tau2, GenOneJetAllTau3Tau1, GenOneJetAllTau4Tau3, GenOneJetAllTau4Tau2, GenOneJetAllTau4Tau1};
      fillTauHists(GenOneJetAllTaus, jets.at(1), genweight);
    }

    if((botPassed1 && q1Passed1 && q2Passed2) || (botPassed1 && q1Passed2 && q2Passed1)) {

      GenJetMassSingleJet->Fill(jets_v4.at(0).M(), genweight);

    }

    if((botPassed2 && q1Passed1 && q2Passed2) || (botPassed2 && q1Passed2 && q2Passed1)) {

      GenJetMassSingleJet->Fill(jets_v4.at(1).M(), genweight);

    }
    
    if((botPassed1 && q1Passed1 && q2Passed2) || (botPassed1 && q1Passed2 && q2Passed1) || (botPassed2 && q1Passed1 && q2Passed2) || (botPassed2 && q1Passed2 && q2Passed1)) {
      GenTwoJetMassAll->Fill(combinedJet_v4.M(), genweight);
      GenTwoJetMassAllDRJet12->Fill(combinedJet_v4.M(), deltaR(jets.at(0), jets.at(1)), 1);
      GenJet1MassAll->Fill(combinedJet_v4.M(), genweight);

      std::vector<TH1F*> GenTwoJetAllTaus = {GenTwoJetAllTau1, GenTwoJetAllTau2, GenTwoJetAllTau3, GenTwoJetAllTau4, GenTwoJetAllTau2Tau1, GenTwoJetAllTau3Tau2, GenTwoJetAllTau3Tau1, GenTwoJetAllTau4Tau3, GenTwoJetAllTau4Tau2, GenTwoJetAllTau4Tau1};
      fillTauHists(GenTwoJetAllTaus, combinedTopJet, genweight);

      if(debug) cout << "--- pre tau subjet plots" << endl;

      if(combinedSubjets.size() == 6) {

        fillAllTauHistsSubjets(combinedSubjets, genweight);

        GenTwoJetAllSubjet1pT->Fill(combinedSubjets.at(0).pt(), genweight);
        GenTwoJetAllSubjet2pT->Fill(combinedSubjets.at(1).pt(), genweight);
        GenTwoJetAllSubjet3pT->Fill(combinedSubjets.at(2).pt(), genweight);
        GenTwoJetAllSubjet4pT->Fill(combinedSubjets.at(3).pt(), genweight);
        GenTwoJetAllSubjet5pT->Fill(combinedSubjets.at(4).pt(), genweight);
        GenTwoJetAllSubjet6pT->Fill(combinedSubjets.at(5).pt(), genweight);

      }

      GenTwoJetAllSubNoneMatchedMass->Fill(combinedTopJetUnmatched_v4.M(), genweight);
      GenTwoJetAllSubUnmatchedSize->Fill(combinedSubjetsUnmatched.size(), genweight);

      GenTwoJetAllSubUnmatchedTau1->Fill(combinedTopJetUnmatched.tau1(), genweight);
      GenTwoJetAllSubUnmatchedTau2->Fill(combinedTopJetUnmatched.tau2(), genweight);
      GenTwoJetAllSubUnmatchedTau3->Fill(combinedTopJetUnmatched.tau3(), genweight);

      if(combinedTopJetUnmatched.tau1() != 0) GenTwoJetAllSubUnmatchedTau2Tau1->Fill(combinedTopJetUnmatched.tau2()/combinedTopJetUnmatched.tau1(), genweight);
      if(combinedTopJetUnmatched.tau2() != 0) GenTwoJetAllSubUnmatchedTau3Tau2->Fill(combinedTopJetUnmatched.tau3()/combinedTopJetUnmatched.tau2(), genweight);
      if(combinedTopJetUnmatched.tau1() != 0) GenTwoJetAllSubUnmatchedTau3Tau1->Fill(combinedTopJetUnmatched.tau3()/combinedTopJetUnmatched.tau1(), genweight);

      float minDR = 4;
      float maxDR = 0;

      for(uint i=0; i<combinedSubjetsUnmatched.size(); i++) {
        if(deltaR(combinedSubjetsUnmatched.at(i), combinedTopJetUnmatched) < minDR) {
          minDR = deltaR(combinedSubjetsUnmatched.at(i), combinedTopJetUnmatched);
        } 
        if(deltaR(combinedSubjetsUnmatched.at(i), combinedTopJetUnmatched) > maxDR) {
           maxDR = deltaR(combinedSubjetsUnmatched.at(i), combinedTopJetUnmatched); 
        }
      }

      GenTwoJetAllSubUnmatchedDRAxisMinMax->Fill(minDR, maxDR, genweight);
      
      if(matchedQuarksInSubjets.at(0)) {

        if(debug) cout << "--- pre tau matched subjet plots" << endl;

        GenTwoJetAllSubMatchedMass->Fill(combinedTopJetMatched_v4.M(), genweight);

        GenTwoJetAllSubMatchedSubjet1pT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);
        GenTwoJetAllSubMatchedSubjet2pT->Fill(combinedSubjetsMatched.at(1).pt(), genweight);
        GenTwoJetAllSubMatchedSubjet3pT->Fill(combinedSubjetsMatched.at(2).pt(), genweight);

        GenTwoJetAllSubMatchedDR12->Fill(deltaR(combinedSubjetsMatched.at(0), combinedSubjetsMatched.at(1)), genweight);
        GenTwoJetAllSubMatchedDR23->Fill(deltaR(combinedSubjetsMatched.at(1), combinedSubjetsMatched.at(2)), genweight);
        GenTwoJetAllSubMatchedDR31->Fill(deltaR(combinedSubjetsMatched.at(2), combinedSubjetsMatched.at(0)), genweight);

        GenTwoJetAllSubMatchedDR1Axis->Fill(deltaR(combinedSubjetsMatched.at(0), combinedTopJetMatched), genweight);
        GenTwoJetAllSubMatchedDR2Axis->Fill(deltaR(combinedSubjetsMatched.at(1), combinedTopJetMatched), genweight);
        GenTwoJetAllSubMatchedDR3Axis->Fill(deltaR(combinedSubjetsMatched.at(2), combinedTopJetMatched), genweight);

        minDR = 4;
        maxDR = 0;

        for(uint i=0; i<combinedSubjetsMatched.size(); i++) {
          if(deltaR(combinedSubjetsMatched.at(i), combinedTopJetMatched) < minDR) {
             minDR = deltaR(combinedSubjetsMatched.at(i), combinedTopJetMatched);
          } 
          if(deltaR(combinedSubjetsMatched.at(i), combinedTopJetMatched) > maxDR) {
             maxDR = deltaR(combinedSubjetsMatched.at(i), combinedTopJetMatched); 
          }
        }

        GenTwoJetAllSubMatchedDRAxisMinMax->Fill(minDR, maxDR, genweight);


        GenTwoJetAllSubMatchedSize->Fill(combinedSubjetsMatched.size(), genweight);

        GenTwoJetAllSubMatchedTau1->Fill(combinedTopJetMatched.tau1(), genweight);
        GenTwoJetAllSubMatchedTau2->Fill(combinedTopJetMatched.tau2(), genweight);
        GenTwoJetAllSubMatchedTau3->Fill(combinedTopJetMatched.tau3(), genweight);

        if(combinedTopJetMatched.tau1() != 0) GenTwoJetAllSubMatchedTau2Tau1->Fill(combinedTopJetMatched.tau2()/combinedTopJetMatched.tau1(), genweight);
        if(combinedTopJetMatched.tau2() != 0) GenTwoJetAllSubMatchedTau3Tau2->Fill(combinedTopJetMatched.tau3()/combinedTopJetMatched.tau2(), genweight);
        if(combinedTopJetMatched.tau1() != 0) GenTwoJetAllSubMatchedTau3Tau1->Fill(combinedTopJetMatched.tau3()/combinedTopJetMatched.tau1(), genweight);

        
        if(!(multipleSubjetsToQuarkMatched.at(0) || multipleSubjetsToQuarkMatched.at(1) || multipleSubjetsToQuarkMatched.at(2))) {

          GenTwoJetAllSubMatchedMultipleSubjets->Fill(combinedTopJetMatched_v4.M(), genweight);

          GenTwoJetAllSubOnlyThreeMatchedTau1->Fill(combinedTopJetMatched.tau1(), genweight);
          GenTwoJetAllSubOnlyThreeMatchedTau2->Fill(combinedTopJetMatched.tau2(), genweight);
          GenTwoJetAllSubOnlyThreeMatchedTau3->Fill(combinedTopJetMatched.tau3(), genweight);

          if(combinedTopJetMatched.tau1() != 0) GenTwoJetAllSubOnlyThreeMatchedTau2Tau1->Fill(combinedTopJetMatched.tau2()/combinedTopJetMatched.tau1(), genweight);
          if(combinedTopJetMatched.tau2() != 0) GenTwoJetAllSubOnlyThreeMatchedTau3Tau2->Fill(combinedTopJetMatched.tau3()/combinedTopJetMatched.tau2(), genweight);
          if(combinedTopJetMatched.tau1() != 0) GenTwoJetAllSubOnlyThreeMatchedTau3Tau1->Fill(combinedTopJetMatched.tau3()/combinedTopJetMatched.tau1(), genweight);

        }

      } else if(matchedQuarksInSubjets.at(1) || matchedQuarksInSubjets.at(2)) {

        GenTwoJetAllSubPartialMatchedMass->Fill(combinedTopJetMatched_v4.M(), genweight);

        GenTwoJetAllSubPartialMatchedSubjet1pT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);
        GenTwoJetAllSubPartialMatchedSubjet2pT->Fill(combinedSubjetsMatched.at(1).pt(), genweight);
        GenTwoJetAllSubPartialMatchedSubjet3pT->Fill(combinedSubjetsMatched.at(2).pt(), genweight);

        GenTwoJetAllSubPartialMatchedDR12->Fill(deltaR(combinedSubjetsMatched.at(0), combinedSubjetsMatched.at(1)), genweight);
        GenTwoJetAllSubPartialMatchedDR23->Fill(deltaR(combinedSubjetsMatched.at(1), combinedSubjetsMatched.at(2)), genweight);
        GenTwoJetAllSubPartialMatchedDR31->Fill(deltaR(combinedSubjetsMatched.at(2), combinedSubjetsMatched.at(0)), genweight);

        GenTwoJetAllSubPartialMatchedDR1Axis->Fill(deltaR(combinedSubjetsMatched.at(0), combinedTopJetMatched), genweight);
        GenTwoJetAllSubPartialMatchedDR2Axis->Fill(deltaR(combinedSubjetsMatched.at(1), combinedTopJetMatched), genweight);
        GenTwoJetAllSubPartialMatchedDR3Axis->Fill(deltaR(combinedSubjetsMatched.at(2), combinedTopJetMatched), genweight);

        GenTwoJetAllSubOneMatchedSize->Fill(combinedSubjetsMatched.size(), genweight);

        GenTwoJetAllSubOneMatchedTau1->Fill(combinedTopJetMatched.tau1(), genweight);
        GenTwoJetAllSubOneMatchedTau2->Fill(combinedTopJetMatched.tau2(), genweight);
        GenTwoJetAllSubOneMatchedTau3->Fill(combinedTopJetMatched.tau3(), genweight);

        if(combinedTopJetMatched.tau1() != 0) GenTwoJetAllSubOneMatchedTau2Tau1->Fill(combinedTopJetMatched.tau2()/combinedTopJetMatched.tau1(), genweight);
        if(combinedTopJetMatched.tau2() != 0) GenTwoJetAllSubOneMatchedTau3Tau2->Fill(combinedTopJetMatched.tau3()/combinedTopJetMatched.tau2(), genweight);
        if(combinedTopJetMatched.tau1() != 0) GenTwoJetAllSubOneMatchedTau3Tau1->Fill(combinedTopJetMatched.tau3()/combinedTopJetMatched.tau1(), genweight);


        GenTwoJetAllSubPartialMatchedTau1->Fill(combinedTopJetMatched.tau1(), genweight);
        GenTwoJetAllSubPartialMatchedTau2->Fill(combinedTopJetMatched.tau2(), genweight);
        GenTwoJetAllSubPartialMatchedTau3->Fill(combinedTopJetMatched.tau3(), genweight);

        if(combinedTopJetMatched.tau2() == 0) GenTwoJetAllSubPartialMatchedTau2Zero->Fill(combinedTopJetMatched.tau2(), genweight);

        if(combinedTopJetMatched.tau1() != 0) GenTwoJetAllSubPartialMatchedTau2Tau1->Fill(combinedTopJetMatched.tau2()/combinedTopJetMatched.tau1(), genweight);
        if(combinedTopJetMatched.tau2() != 0) GenTwoJetAllSubPartialMatchedTau3Tau2->Fill(combinedTopJetMatched.tau3()/combinedTopJetMatched.tau2(), genweight);
        if(combinedTopJetMatched.tau1() != 0) GenTwoJetAllSubPartialMatchedTau3Tau1->Fill(combinedTopJetMatched.tau3()/combinedTopJetMatched.tau1(), genweight);

      } else if(matchedQuarksInSubjets.at(3) || matchedQuarksInSubjets.at(4)) {

        GenTwoJetAllSubPartialMatchedMass->Fill(combinedTopJetMatched_v4.M(), genweight);

        GenTwoJetAllSubPartialMatchedSubjet1pT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);
        GenTwoJetAllSubPartialMatchedSubjet2pT->Fill(combinedSubjetsMatched.at(1).pt(), genweight);
        GenTwoJetAllSubPartialMatchedSubjet3pT->Fill(combinedSubjetsMatched.at(2).pt(), genweight);

        GenTwoJetAllSubPartialMatchedDR12->Fill(deltaR(combinedSubjetsMatched.at(0), combinedSubjetsMatched.at(1)), genweight);
        GenTwoJetAllSubPartialMatchedDR23->Fill(deltaR(combinedSubjetsMatched.at(1), combinedSubjetsMatched.at(2)), genweight);
        GenTwoJetAllSubPartialMatchedDR31->Fill(deltaR(combinedSubjetsMatched.at(2), combinedSubjetsMatched.at(0)), genweight);
        
        GenTwoJetAllSubPartialMatchedDR1Axis->Fill(deltaR(combinedSubjetsMatched.at(0), combinedTopJetMatched), genweight);
        GenTwoJetAllSubPartialMatchedDR2Axis->Fill(deltaR(combinedSubjetsMatched.at(1), combinedTopJetMatched), genweight);
        GenTwoJetAllSubPartialMatchedDR3Axis->Fill(deltaR(combinedSubjetsMatched.at(2), combinedTopJetMatched), genweight);

        GenTwoJetAllSubTwoMatchedSize->Fill(combinedSubjetsMatched.size(), genweight);

        GenTwoJetAllSubTwoMatchedTau1->Fill(combinedTopJetMatched.tau1(), genweight);
        GenTwoJetAllSubTwoMatchedTau2->Fill(combinedTopJetMatched.tau2(), genweight);
        GenTwoJetAllSubTwoMatchedTau3->Fill(combinedTopJetMatched.tau3(), genweight);

        if(combinedTopJetMatched.tau1() != 0) GenTwoJetAllSubTwoMatchedTau2Tau1->Fill(combinedTopJetMatched.tau2()/combinedTopJetMatched.tau1(), genweight);
        if(combinedTopJetMatched.tau2() != 0) GenTwoJetAllSubTwoMatchedTau3Tau2->Fill(combinedTopJetMatched.tau3()/combinedTopJetMatched.tau2(), genweight);
        if(combinedTopJetMatched.tau1() != 0) GenTwoJetAllSubTwoMatchedTau3Tau1->Fill(combinedTopJetMatched.tau3()/combinedTopJetMatched.tau1(), genweight);


        GenTwoJetAllSubPartialMatchedTau1->Fill(combinedTopJetMatched.tau1(), genweight);
        GenTwoJetAllSubPartialMatchedTau2->Fill(combinedTopJetMatched.tau2(), genweight);
        GenTwoJetAllSubPartialMatchedTau3->Fill(combinedTopJetMatched.tau3(), genweight);

        if(combinedTopJetMatched.tau2() == 0) GenTwoJetAllSubPartialMatchedTau2Zero->Fill(combinedTopJetMatched.tau2(), genweight);

        if(combinedTopJetMatched.tau1() != 0) GenTwoJetAllSubPartialMatchedTau2Tau1->Fill(combinedTopJetMatched.tau2()/combinedTopJetMatched.tau1(), genweight);
        if(combinedTopJetMatched.tau2() != 0) GenTwoJetAllSubPartialMatchedTau3Tau2->Fill(combinedTopJetMatched.tau3()/combinedTopJetMatched.tau2(), genweight);
        if(combinedTopJetMatched.tau1() != 0) GenTwoJetAllSubPartialMatchedTau3Tau1->Fill(combinedTopJetMatched.tau3()/combinedTopJetMatched.tau1(), genweight);

      }

      if(matchedQuarksInSubjets.at(1) || matchedQuarksInSubjets.at(2) || matchedQuarksInSubjets.at(3) || matchedQuarksInSubjets.at(4)) {

        minDR = 4;
        maxDR = 0;

        for(uint i=0; i<combinedSubjetsMatched.size(); i++) {
          if(deltaR(combinedSubjetsMatched.at(i), combinedTopJetMatched) < minDR) {
             minDR = deltaR(combinedSubjetsMatched.at(i), combinedTopJetMatched);
          } 
          if(deltaR(combinedSubjetsMatched.at(i), combinedTopJetMatched) > maxDR) {
             maxDR = deltaR(combinedSubjetsMatched.at(i), combinedTopJetMatched); 
          }
        }

        GenTwoJetAllSubPartialMatchedDRAxisMinMax->Fill(minDR, maxDR, genweight);

      }

      if(matchedQuarksInSubjets.at(0)) {

        if(multipleSubjetsToQuarkMatched.at(0)) GenTwoJetMultipleQSubjetpT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);
        else GenTwoJetBotSubjetpT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);
        if(multipleSubjetsToQuarkMatched.at(1)) GenTwoJetMultipleQSubjetpT->Fill(combinedSubjetsMatched.at(1).pt(), genweight);
        else GenTwoJetLightQ1SubjetpT->Fill(combinedSubjetsMatched.at(1).pt(), genweight);
        if(multipleSubjetsToQuarkMatched.at(2)) GenTwoJetMultipleQSubjetpT->Fill(combinedSubjetsMatched.at(2).pt(), genweight);
        else GenTwoJetLightQ2SubjetpT->Fill(combinedSubjetsMatched.at(2).pt(), genweight);

      } else if(matchedQuarksInSubjets.at(1)) {

        if(multipleSubjetsToQuarkMatched.at(0)) GenTwoJetMultipleQSubjetpT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);
        else GenTwoJetBotSubjetpT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);

      } else if(matchedQuarksInSubjets.at(2)) {

        if(multipleSubjetsToQuarkMatched.at(1)) GenTwoJetMultipleQSubjetpT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);
        else GenTwoJetLightQ1SubjetpT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);
        if(multipleSubjetsToQuarkMatched.at(2)) GenTwoJetMultipleQSubjetpT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);
        else GenTwoJetLightQ2SubjetpT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);

      } else if(matchedQuarksInSubjets.at(3)) {

        if(multipleSubjetsToQuarkMatched.at(0)) GenTwoJetMultipleQSubjetpT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);
        else GenTwoJetBotSubjetpT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);
        if(multipleSubjetsToQuarkMatched.at(1)) GenTwoJetMultipleQSubjetpT->Fill(combinedSubjetsMatched.at(1).pt(), genweight);
        else GenTwoJetLightQ1SubjetpT->Fill(combinedSubjetsMatched.at(1).pt(), genweight);
        if(multipleSubjetsToQuarkMatched.at(2)) GenTwoJetMultipleQSubjetpT->Fill(combinedSubjetsMatched.at(1).pt(), genweight);
        else GenTwoJetLightQ2SubjetpT->Fill(combinedSubjetsMatched.at(1).pt(), genweight);

      } else if(matchedQuarksInSubjets.at(4)) {

        if(multipleSubjetsToQuarkMatched.at(1)) GenTwoJetMultipleQSubjetpT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);
        else GenTwoJetLightQ1SubjetpT->Fill(combinedSubjetsMatched.at(0).pt(), genweight);
        if(multipleSubjetsToQuarkMatched.at(2)) GenTwoJetMultipleQSubjetpT->Fill(combinedSubjetsMatched.at(1).pt(), genweight);
        else GenTwoJetLightQ2SubjetpT->Fill(combinedSubjetsMatched.at(1).pt(), genweight);

        TLorentzVector q1_v4, q2_v4, qCombined_v4;

        q1_v4.SetPxPyPzE(combinedSubjetsMatched.at(0).v4().Px(), combinedSubjetsMatched.at(0).v4().Py(), combinedSubjetsMatched.at(0).v4().Pz(), combinedSubjetsMatched.at(0).v4().E());
        q2_v4.SetPxPyPzE(combinedSubjetsMatched.at(1).v4().Px(), combinedSubjetsMatched.at(1).v4().Py(), combinedSubjetsMatched.at(1).v4().Pz(), combinedSubjetsMatched.at(1).v4().E());

        qCombined_v4 = q1_v4 + q2_v4;

        GenTwoJetLightQCombinedSubjetpT->Fill(qCombined_v4.Pt(), genweight);

      }

      if(matchedQuarksIn4Subjets.at(0)) {

        GenTwoJetAll4SubMatchedMass->Fill(combined4TopJetMatched_v4.M(), genweight);

        GenTwoJetAll4SubMatchedSize->Fill(combined4SubjetsMatched.size(), genweight);

      } else if(matchedQuarksIn4Subjets.at(1) || matchedQuarksIn4Subjets.at(2) || matchedQuarksIn4Subjets.at(3) || matchedQuarksIn4Subjets.at(4)) {

        GenTwoJetAll4SubPartialMatchedMass->Fill(combined4TopJetMatched_v4.M(), genweight);

        GenTwoJetAll4SubPartialMatchedSize->Fill(combined4SubjetsMatched.size(), genweight);

      }
    }

  } else if(jets.size()>0) {
    botPassed1 = deltaR(bot, jets.at(0)) < jetradius;
    q1Passed1 = deltaR(q1, jets.at(0)) < jetradius;
    q2Passed1 = deltaR(q2, jets.at(0)) < jetradius;
  }


  if(debug) cout << "\t\t ---pre cut" << endl;

  if(jets.size() > 1 && deltaR(jets.at(0), jets.at(1)) < 1.2) {

    if(combinedTopJet.tau1() != 0) {
      if(combinedTopJet.tau2()/combinedTopJet.tau1() < 0.62) {
        GenJetMassCombinedTau21CutLower->Fill(combinedJet_v4.M(), genweight);
        if(debug) cout << "\t\t ---filled a cut hist" << endl;
        if(deltaR(combinedTopJet, top) < jetradius) GenJetMassCombinedTau21CutLowerTop->Fill(combinedJet_v4.M(), genweight);
        if(gluons.size() > 0 && deltaR(combinedTopJet, gluons.at(0)) < jetradius) GenJetMassCombinedTau21CutLowerGluon->Fill(combinedJet_v4.M(), genweight);
      } else {
        GenJetMassCombinedTau21CutHigher->Fill(combinedJet_v4.M(), genweight);
        if(deltaR(combinedTopJet, top) < jetradius) GenJetMassCombinedTau21CutHigherTop->Fill(combinedJet_v4.M(), genweight);
        if(gluons.size() > 0 && deltaR(combinedTopJet, gluons.at(0)) < jetradius) GenJetMassCombinedTau21CutHigherGluon->Fill(combinedJet_v4.M(), genweight);
      }

      if(combinedTopJet.tau3()/combinedTopJet.tau1() < 0.38) {
        GenJetMassCombinedTau31CutLower->Fill(combinedJet_v4.M(), genweight);
        if(deltaR(combinedTopJet, top) < jetradius) GenJetMassCombinedTau31CutLowerTop->Fill(combinedJet_v4.M(), genweight);
        if(gluons.size() > 0 && deltaR(combinedTopJet, gluons.at(0)) < jetradius) GenJetMassCombinedTau31CutLowerGluon->Fill(combinedJet_v4.M(), genweight);
      } else {
        GenJetMassCombinedTau31CutHigher->Fill(combinedJet_v4.M(), genweight);
        if(deltaR(combinedTopJet, top) < jetradius) GenJetMassCombinedTau31CutHigherTop->Fill(combinedJet_v4.M(), genweight);
        if(gluons.size() > 0 && deltaR(combinedTopJet, gluons.at(0)) < jetradius) GenJetMassCombinedTau31CutHigherGluon->Fill(combinedJet_v4.M(), genweight);
      }

      if(combinedTopJet.tau4()/combinedTopJet.tau1() < 0.3) {
        GenJetMassCombinedTau41CutLower->Fill(combinedJet_v4.M(), genweight);
        if(deltaR(combinedTopJet, top) < jetradius) GenJetMassCombinedTau41CutLowerTop->Fill(combinedJet_v4.M(), genweight);
        if(gluons.size() > 0 && deltaR(combinedTopJet, gluons.at(0)) < jetradius) GenJetMassCombinedTau41CutLowerGluon->Fill(combinedJet_v4.M(), genweight);
      } else {
        GenJetMassCombinedTau41CutHigher->Fill(combinedJet_v4.M(), genweight);
        if(deltaR(combinedTopJet, top) < jetradius) GenJetMassCombinedTau41CutHigherTop->Fill(combinedJet_v4.M(), genweight);
        if(gluons.size() > 0 && deltaR(combinedTopJet, gluons.at(0)) < jetradius) GenJetMassCombinedTau41CutHigherGluon->Fill(combinedJet_v4.M(), genweight);
      }
    }

    if(combinedTopJet.tau2() != 0) {
      if(combinedTopJet.tau3()/combinedTopJet.tau2() < 0.7) {
        GenJetMassCombinedTau32CutLower->Fill(combinedJet_v4.M(), genweight);
        if(deltaR(combinedTopJet, top) < jetradius) GenJetMassCombinedTau32CutLowerTop->Fill(combinedJet_v4.M(), genweight);
        if(gluons.size() > 0 && deltaR(combinedTopJet, gluons.at(0)) < jetradius) GenJetMassCombinedTau32CutLowerGluon->Fill(combinedJet_v4.M(), genweight);
      } else {
        GenJetMassCombinedTau32CutHigher->Fill(combinedJet_v4.M(), genweight);
        if(deltaR(combinedTopJet, top) < jetradius) GenJetMassCombinedTau32CutHigherTop->Fill(combinedJet_v4.M(), genweight);
        if(gluons.size() > 0 && deltaR(combinedTopJet, gluons.at(0)) < jetradius) GenJetMassCombinedTau32CutHigherGluon->Fill(combinedJet_v4.M(), genweight);
      }

      if(combinedTopJet.tau4()/combinedTopJet.tau2() < 0.54) {
        GenJetMassCombinedTau42CutLower->Fill(combinedJet_v4.M(), genweight);
        if(deltaR(combinedTopJet, top) < jetradius) GenJetMassCombinedTau42CutLowerTop->Fill(combinedJet_v4.M(), genweight);
        if(gluons.size() > 0 && deltaR(combinedTopJet, gluons.at(0)) < jetradius) GenJetMassCombinedTau42CutLowerGluon->Fill(combinedJet_v4.M(), genweight);
      } else {
        GenJetMassCombinedTau42CutHigher->Fill(combinedJet_v4.M(), genweight);
        if(deltaR(combinedTopJet, top) < jetradius) GenJetMassCombinedTau42CutHigherTop->Fill(combinedJet_v4.M(), genweight);
        if(gluons.size() > 0 && deltaR(combinedTopJet, gluons.at(0)) < jetradius) GenJetMassCombinedTau42CutHigherGluon->Fill(combinedJet_v4.M(), genweight);
      }
    }

  } else {

    if(debug) cout << "\t\t ---cut jet" << endl;
    if(jets.at(0).tau1() != 0) {
      if(jets.at(0).tau2()/jets.at(0).tau1() < 0.62) {
        GenJetMassCombinedTau21CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(debug) cout << "\t\t ---filled a cut hist" << endl;
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassCombinedTau21CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassCombinedTau21CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassCombinedTau21CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassCombinedTau21CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassCombinedTau21CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }

      if(jets.at(0).tau3()/jets.at(0).tau1() < 0.38) {
        GenJetMassCombinedTau31CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassCombinedTau31CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassCombinedTau31CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassCombinedTau31CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassCombinedTau31CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassCombinedTau31CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }

      if(jets.at(0).tau4()/jets.at(0).tau1() < 0.3) {
        GenJetMassCombinedTau41CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassCombinedTau41CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassCombinedTau41CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassCombinedTau41CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassCombinedTau41CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassCombinedTau41CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }
    }

    if(jets.at(0).tau2() != 0) {
      if(jets.at(0).tau3()/jets.at(0).tau2() < 0.7) {
        GenJetMassCombinedTau32CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassCombinedTau32CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassCombinedTau32CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassCombinedTau32CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassCombinedTau32CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassCombinedTau32CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }

      if(jets.at(0).tau4()/jets.at(0).tau2() < 0.54) {
        GenJetMassCombinedTau42CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassCombinedTau42CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassCombinedTau42CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassCombinedTau42CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassCombinedTau42CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassCombinedTau42CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }
    }

    if(debug) cout << "\t\t ---cut jet"<< endl;
    if(jets.at(0).tau1() != 0) {
      if(jets.at(0).tau2()/jets.at(0).tau1() < 0.62) {
        GenJetMassNoCombinedTau21CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(debug) cout << "\t\t ---filled a cut hist" << endl;
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassNoCombinedTau21CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassNoCombinedTau21CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassNoCombinedTau21CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassNoCombinedTau21CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassNoCombinedTau21CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }

      if(jets.at(0).tau3()/jets.at(0).tau1() < 0.38) {
        GenJetMassNoCombinedTau31CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassNoCombinedTau31CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassNoCombinedTau31CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassNoCombinedTau31CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassNoCombinedTau31CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassNoCombinedTau31CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }

      if(jets.at(0).tau4()/jets.at(0).tau1() < 0.3) {
        GenJetMassNoCombinedTau41CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassNoCombinedTau41CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassNoCombinedTau41CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassNoCombinedTau41CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassNoCombinedTau41CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassNoCombinedTau41CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }
    }

    if(jets.at(0).tau2() != 0) {
      if(jets.at(0).tau3()/jets.at(0).tau2() < 0.7) {
        GenJetMassNoCombinedTau32CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassNoCombinedTau32CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassNoCombinedTau32CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassNoCombinedTau32CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassNoCombinedTau32CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassNoCombinedTau32CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }

      if(jets.at(0).tau4()/jets.at(0).tau2() < 0.54) {
        GenJetMassNoCombinedTau42CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassNoCombinedTau42CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassNoCombinedTau42CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassNoCombinedTau42CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassNoCombinedTau42CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassNoCombinedTau42CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }
    }
  

    if(debug) cout << "\t\t ---cut jet" << endl;
    if(jets.at(0).tau1() != 0) {
      if(jets.at(0).tau2()/jets.at(0).tau1() < 0.62) {
        GenJetMassTau21CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(debug) cout << "\t\t ---filled a cut hist" << endl;
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassTau21CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassTau21CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassTau21CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassTau21CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassTau21CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }

      if(jets.at(0).tau3()/jets.at(0).tau1() < 0.38) {
        GenJetMassTau31CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassTau31CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassTau31CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassTau31CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassTau31CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassTau31CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }

      if(jets.at(0).tau4()/jets.at(0).tau1() < 0.3) {
        GenJetMassTau41CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassTau41CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassTau41CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassTau41CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassTau41CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassTau41CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }
    }

    if(jets.at(0).tau2() != 0) {
      if(jets.at(0).tau3()/jets.at(0).tau2() < 0.7) {
        GenJetMassTau32CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassTau32CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassTau32CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassTau32CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassTau32CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassTau32CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }

      if(jets.at(0).tau4()/jets.at(0).tau2() < 0.54) {
        GenJetMassTau42CutLower->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassTau42CutLowerTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassTau42CutLowerGluon->Fill(jets_v4.at(0).M(), genweight);
      } else {
        GenJetMassTau42CutHigher->Fill(jets_v4.at(0).M(), genweight);
        if(deltaR(jets.at(0), top) < jetradius) GenJetMassTau42CutHigherTop->Fill(jets_v4.at(0).M(), genweight);
        if(gluons.size() > 0 && deltaR(jets.at(0), gluons.at(0)) < jetradius) GenJetMassTau42CutHigherGluon->Fill(jets_v4.at(0).M(), genweight);
      }
    }
  }
  
  //---------------------------------------------------------------------------------------
  //--------------------------------- Clear all used objects ------------------------------
  //---------------------------------------------------------------------------------------
  if(debug) cout << "\t--- Clear all used objects" << endl;
  lepton1_v4.Delete();
  jet2_lep_v4.Delete();
  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------

}
