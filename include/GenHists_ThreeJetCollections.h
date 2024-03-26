#pragma once
#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/PFParticle.h"
#include "UHH2/common/include/TTbarGen.h"

#include <iostream>
#include <math.h>
#include <vector>

#include "TH1F.h"
#include "TH2F.h"
using namespace std;

class GenHists_ThreeJetCollections: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
  GenHists_ThreeJetCollections(uhh2::Context & ctx, const std::string & dirname, const std::string & topJetName, const std::string & gluonJetName, const std::string & lepJetName);

    virtual void fill(const uhh2::Event & ev) override;

protected:
    TH1F *GenJetMass;

    TH1F *GenJetMassAllJets;

    TH1F *GenDeltaRJet1Jet2, *GenDeltaRJet2Jet3, *GenDeltaRJet3Jet1;
    TH1F *GenJet1DeltaRSubjet1Subjet2, *GenJet1DeltaRSubjet2Subjet3, *GenJet1DeltaRSubjet3Subjet1;
    TH1F *GenJet2DeltaRSubjet1Subjet2, *GenJet2DeltaRSubjet2Subjet3, *GenJet2DeltaRSubjet3Subjet1;
    TH1F *GenJet3DeltaRSubjet1Subjet2, *GenJet3DeltaRSubjet2Subjet3, *GenJet3DeltaRSubjet3Subjet1;

    TH1F *GenDeltaRJetsPtDiff;

    TH1F *GenMatchedTopInAnyJet, *GenMatchedTopInAnyJetPtCut, *GenMatchedTopInAnyJetPtCut2;
    TH1F *GenMatchedGluonInAnyJet, *GenMatchedGluonInAnyJetPtCut, *GenMatchedGluonInAnyJetPtCutOtherJet;

    TH1F *GenDeltaRTopPtCutNearest, *GenDeltaRJetPtCutNearest;

    TH1F *GenJetNumber;
    TH1F *GenTTBarJetMass;
    TH1F *GenJet1MassAll, *GenJet1MassNotAll;
    TH1F *GenJet1MassBot;
    TH1F *GenJet1MassTwoLightQ;
    TH1F *GenJet1MassBotOneLightQ;
    TH1F *GenJet1MassOneQ;
    TH1F *GenJet1MassNoQ;
    TH1F *GenJet1MassRest;

    TH1F *GenJet1MassAllNoGluons;
    TH1F *GenJet1MassNotAllNoGluons;

    TH1F *GenJetMassGluon;
    TH1F *GenJetMassNoGluon;

    TH1F *GenJetMassGluonInJet;
    TH1F *GenJetMassGluonNotInJet;
    TH1F *GenJetMassGluonNearTop;
    TH1F *GenJetMassGluonNotNearTop;
    TH1F *GenJetMassGluonInSubjet;
    TH1F *GenJetMassGluonNotInSubjet;
    TH1F *GenJetMassGluonInJetAndSubjet;
    TH1F *GenJetMassGluonInJetAndNotSubjet;

    TH1F *GenJetMassGluonNearTopAndAllSubjetsMatched;
    TH1F *GenJetMassGluonNotNearTopAndAllSubjetsMatched;

    TH1F *GenJetTau3Tau2;
    TH1F *GenJetTau2Tau1;
    TH1F *GenJetTau1;

    TH1F *GenJetPT, *GenSubjetNumber;
    TH1F *GenSubjet1Mass, *GenSubjet2Mass, *GenSubjet3Mass;
    TH1F *GenEachInOneSubjetMass, *GenEachInOneSubjetMassAllInJet;
    TH1F *GenTwoInOneSubjetMass, *GenTwoInOneSubjetMassAllInJet;
    TH1F *GenOneInOneSubjetMass, *GenOneInOneSubjetMassAllInJet;
    TH1F *GenNoneInOneSubjetMass, *GenNoneInOneSubjetMassAllInJet;
    TH1F *GenAnySubjetMass, *GenAnyButNotEachSubjetMass;

    TH1F *PTRatio_bot_subjet, *PTRatio_q1_subjet, *PTRatio_q2_subjet;
    TH1F *SameNearestSubjet;

    TH1F *GenJetMassUnmatched;

    TH1F *GenJetMassEachInOneSubjetAndGluonInSubjet, *GenJetMassEachInOneSubjetAndGluonNotInSubjet, *GenJetMassEachInOneSubjetAndGluonInJet, *GenJetMassEachInOneSubjetAndGluonNotInJet;
    TH1F *GenJetMassUnmatchedAndGluonInSubjet, *GenJetMassUnmatchedAndGluonNotInSubjet, *GenJetMassUnmatchedAndGluonInJet, *GenJetMassUnmatchedAndGluonNotInJet;

    TH1F *deltaR_TTBar;

    TH1F *GenSubjetPTRatioQ1BotMatched, *GenSubjetPTRatioQ2BotMatched, *GenSubjetPTRatioQ12Matched, *GenSubjetPTRatioBotQ1Matched, *GenSubjetPTRatioBotQ2Matched, *GenSubjetPTRatioQ21Matched;
    TH1F *GenSubjetMRatioQ1BotMatched, *GenSubjetMRatioQ2BotMatched, *GenSubjetMRatioQ12Matched, *GenSubjetMRatioBotQ1Matched, *GenSubjetMRatioBotQ2Matched, *GenSubjetMRatioQ21Matched;
    
    TH1F *GenSubjetPTRatioQ1JetMatched, *GenSubjetPTRatioQ2JetMatched, *GenSubjetPTRatioBotJetMatched, *GenSubjetPTRatioQuarksJetMatched;
    TH1F *GenSubjetMRatioQ1JetMatched, *GenSubjetMRatioQ2JetMatched, *GenSubjetMRatioBotJetMatched, *GenSubjetMRatioQuarksJetMatched;
    
    TH1F *GenPTRatioSubjet1JetMatched, *GenPTRatioSubjet2JetMatched, *GenPTRatioSubjet3JetMatched;
    TH1F *GenMRatioSubjet1JetMatched, *GenMRatioSubjet2JetMatched, *GenMRatioSubjet3JetMatched;

    TH1F *GenPTRatioSubjet1JetUnmatched, *GenPTRatioSubjet2JetUnmatched, *GenPTRatioSubjet3JetUnmatched, *GenPTRatioQuarksJetUnmatched;
    TH1F *GenMRatioSubjet1JetUnmatched, *GenMRatioSubjet2JetUnmatched, *GenMRatioSubjet3JetUnmatched, *GenMRatioQuarksJetUnmatched;

    TH1F *GenJetMassMatchedTop, *GenJetMassMatchedGluon;

    TH1F *GenPTRatioSubjet1JetMatchedTop, *GenPTRatioSubjet2JetMatchedTop, *GenPTRatioSubjet3JetMatchedTop, *GenPTRatioQuarksJetMatchedTop;
    TH1F *GenPTRatioSubjet1Subjet2MatchedTop, *GenPTRatioSubjet1Subjet3MatchedTop, *GenPTRatioSubjet2Subjet3MatchedTop;
    TH1F *GenMRatioSubjet1JetMatchedTop, *GenMRatioSubjet2JetMatchedTop, *GenMRatioSubjet3JetMatchedTop, *GenMRatioQuarksJetMatchedTop;
    TH1F *GenMRatioSubjet1Subjet2MatchedTop, *GenMRatioSubjet1Subjet3MatchedTop, *GenMRatioSubjet2Subjet3MatchedTop;

    TH1F *GenPTRatioSubjet1JetMatchedGluon, *GenPTRatioSubjet2JetMatchedGluon, *GenPTRatioSubjet3JetMatchedGluon, *GenPTRatioQuarksJetMatchedGluon;
    TH1F *GenPTRatioSubjet1Subjet2MatchedGluon, *GenPTRatioSubjet1Subjet3MatchedGluon, *GenPTRatioSubjet2Subjet3MatchedGluon;
    TH1F *GenMRatioSubjet1JetMatchedGluon, *GenMRatioSubjet2JetMatchedGluon, *GenMRatioSubjet3JetMatchedGluon, *GenMRatioQuarksJetMatchedGluon;
    TH1F *GenMRatioSubjet1Subjet2MatchedGluon, *GenMRatioSubjet1Subjet3MatchedGluon, *GenMRatioSubjet2Subjet3MatchedGluon;

    TH2F *Gen_DeltaR_CombinedMass_NonLepJets, *Gen_DeltaR_CombinedMass_NonLepJets_PTCutJet, *Gen_DeltaR_CombinedMass_NonLepJets_PTCutTop;
    TH2F *Gen_DeltaR_Mass1_NonLepJet, *Gen_DeltaR_Mass1_NonLepJet_PTCutJet, *Gen_DeltaR_Mass1_NonLepJet_PTCutTop;
    TH2F *Gen_DeltaR_Mass2_NonLepJet, *Gen_DeltaR_Mass2_NonLepJet_PTCutJet, *Gen_DeltaR_Mass2_NonLepJet_PTCutTop;

    /*
    TH1F *GenJet2Mass, *GenJet2LepMass, *Mass1Mass2;
    TH1F *GenJet1PT, *GenJet2PT, *GenJet3PT, *GenJet4PT, *GenJet5PT, *GenJet1Jet2PT, *LeptonPT;
    TH1F *GenJet2Eta;
    TH1F *TopHadPT, *TopLepPT, *BotHadPT, *BotLepPT;
    TH1F *deltaR_bot_jet1, *deltaR_botlep_jet1,*deltaR_q1_jet1, *deltaR_q2_jet1, *deltaR_lep1_jet1, *deltaR_lep2_jet1, *deltaR_tophad_jet1, *deltaR_toplep_jet1;
    TH1F *deltaR_bot_jet2, *deltaR_botlep_jet2,*deltaR_q1_jet2, *deltaR_q2_jet2, *deltaR_lep1_jet2, *deltaR_lep2_jet2, *deltaR_tophad_jet2, *deltaR_toplep_jet2;
    TH1F *deltaPhi_lep1_jet1, *deltaPhi_lep1_jet2;
    TH1F *dR_GenParts_q1_q2, *dR_GenParts_bot_q1,*dR_GenParts_bot_q2, *dR_GenParts_highest, *dR_GenParts_lowest;
    TH2F *dR_GenParts_q1_q2_toppt, *dR_GenParts_bot_q1_toppt,*dR_GenParts_bot_q2_toppt, *dR_GenParts_highest_toppt, *dR_GenParts_lowest_toppt;
    TH1F *deltaR_bot_jet3, *deltaR_botlep_jet3,*deltaR_q1_jet3, *deltaR_q2_jet3, *deltaR_lep1_jet3, *deltaR_lep2_jet3, *deltaR_tophad_jet3, *deltaR_toplep_jet3;
    TH1F *deltaR_bot_jet4, *deltaR_botlep_jet4,*deltaR_q1_jet4, *deltaR_q2_jet4, *deltaR_lep1_jet4, *deltaR_lep2_jet4, *deltaR_tophad_jet4, *deltaR_toplep_jet4;
    TH1F *deltaR_bot_jet5, *deltaR_botlep_jet5,*deltaR_q1_jet5, *deltaR_q2_jet5, *deltaR_lep1_jet5, *deltaR_lep2_jet5, *deltaR_tophad_jet5, *deltaR_toplep_jet5;
    TH1F *deltaR_bot_jet6, *deltaR_botlep_jet6,*deltaR_q1_jet6, *deltaR_q2_jet6, *deltaR_lep1_jet6, *deltaR_lep2_jet6, *deltaR_tophad_jet6, *deltaR_toplep_jet6;
    TH2F *Eta_Phi_jet1, *Eta_Phi_bot, *Eta_Phi_q1, *Eta_Phi_q2;
    */

    TH1F *STGenTopJetPT, *STGenGluonJetPT, *STGenLepJetPT;
    TH1F *STGenTopJetM, *STGenGluonJetM, *STGenLepJetM;
    TH1F *STGenTopJetMSmallPT, *STGenTopJetMSmallPTCombined;

    TH1F *STGenTopJetTau1, *STGenTopJetTau2, *STGenTopJetTau3, *STGenTopJetTau4;
    TH1F *STGenGluonJetTau1, *STGenGluonJetTau2, *STGenGluonJetTau3, *STGenGluonJetTau4;
    TH1F *STGenLepJetTau1, *STGenLepJetTau2, *STGenLepJetTau3, *STGenLepJetTau4;

    TH1F *STGenTopJetTau3Tau2, *STGenTopJetTau4Tau3, *STGenTopJetTau4Tau2;
    TH1F *STGenGluonJetTau3Tau2, *STGenGluonJetTau4Tau3, *STGenGluonJetTau4Tau2;
    TH1F *STGenLepJetTau3Tau2, *STGenLepJetTau4Tau3, *STGenLepJetTau4Tau2;

    TH1F *STGenDeltaRTopGluon, *STGenDeltaRTopLep, *STGenDeltaRGluonLep;

    TH1F *STGenTopSubjetM1M2, *STGenTopSubjetM2M3, *STGenTopSubjetM1M3;
    TH1F *STGenGluonSubjetM1M2, *STGenGluonSubjetM2M3, *STGenGluonSubjetM1M3;

    TH1F *STGenGluonSubjetM1, *STGenGluonSubjetM2, *STGenGluonSubjetM3;
    TH1F *STGenGluonSubjetPt1, *STGenGluonSubjetPt2, *STGenGluonSubjetPt3;

    TH1F *STGenTopJetM_EachSubjetMatched;

    TH1F *GenTopJetNumber, *GenGluonJetNumber, *GenLepJetNumber;
    TH1F *GenDeltaRLepJetTop;

    TH1F *DTGenTopJetPT, *DTGenLepJetPT;
    TH1F *DTGenTopJetM, *DTGenLepJetM;
    TH1F *DTGenTopJetPtCombined, *DTGenTopJetMCombined;

    TH1F *DTGenTopJetTau1, *DTGenTopJetTau2, *DTGenTopJetTau3, *DTGenTopJetTau4;
    TH1F *DTGenLepJetTau1, *DTGenLepJetTau2, *DTGenLepJetTau3, *DTGenLepJetTau4;

    TH1F *DTGenTopJetTau3Tau2, *DTGenTopJetTau4Tau3, *DTGenTopJetTau4Tau2;
    TH1F *DTGenLepJetTau3Tau2, *DTGenLepJetTau4Tau3, *DTGenLepJetTau4Tau2;

    TH1F *DTGenDeltaRTopTop, *DTGenDeltaRTopLep;

    TH1F *DTGenTopSubjetM1M2, *DTGenTopSubjetM2M3, *DTGenTopSubjetM1M3;

    TH1F *DTGenTopJetM_EachQuarkMatched;

    uhh2::Event::Handle<TTbarGen> h_ttbargen;
    uhh2::Event::Handle<std::vector<GenTopJet>> h_topJets, h_gluonJets, h_lepJets;

    bool debug;
};
