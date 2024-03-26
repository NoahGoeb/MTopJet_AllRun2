#pragma once
#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/PFParticle.h"
#include "UHH2/common/include/TTbarGen.h"

#include <UHH2/MTopJet/include/CombineXCone.h>

#include <iostream>
#include <math.h>
#include <vector>

#include "TH1F.h"
#include "TH2F.h"
using namespace std;

class GenHists_GenNoLep: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
  GenHists_GenNoLep(uhh2::Context & ctx, const std::string & dirname, const std::string & jetname, float dR);

  virtual void fill(const uhh2::Event & ev) override;
  bool subjetMatching(std::vector<GenJet> subjets, std::vector<GenParticle> quarks, unsigned int* remaining_quarks, bool unique,std::vector<int>* subjetIndices);
  //static GenParticle* gluonInEvent(const uhh2::Event & event);
  void fillTauHistsSubjets(std::vector<TH1F*> hists, GenTopJet jet, double genweight);
  void fillAllTauHistsSubjets(std::vector<GenJet> combinedSubjets, double genweight);
  void fillDRSubjetHists(std::vector<GenJet> tmpSubjets, GenTopJet tmpJet, double genweight);

protected:

    float dR_;

    CombineXCone* combine;

    TH1F *STGenTopJetPT, *STGenGluonJetPT;
    TH1F *STGenTopJetM, *STGenGluonJetM;
    TH1F *STGenTopJetMSmallPT;

    TH1F *STGenDeltaRTopGluon;

    TH1F *STGluonSubjetPtSum;

    TH1F *GenTopJetTau1, *GenTopJetTau2, *GenTopJetTau3, *GenTopJetTau4;
    TH1F *GenGluonJetTau1, *GenGluonJetTau2, *GenGluonJetTau3, *GenGluonJetTau4;

    TH1F *GenTopJetTau2Tau1, *GenTopJetTau3Tau2, *GenTopJetTau3Tau1, *GenTopJetTau4Tau3, *GenTopJetTau4Tau2, *GenTopJetTau4Tau1;
    TH1F *GenGluonJetTau2Tau1, *GenGluonJetTau3Tau2, *GenGluonJetTau3Tau1, *GenGluonJetTau4Tau3, *GenGluonJetTau4Tau2, *GenGluonJetTau4Tau1;

    TH1F *GenTopSubjetM1M, *GenTopSubjetM2M, *GenTopSubjetM3M;
    TH1F *GenGluonSubjetM1M, *GenGluonSubjetM2M, *GenGluonSubjetM3M;

    TH1F *GenTopSubjetPT1PT, *GenTopSubjetPT2PT, *GenTopSubjetPT3PT;
    TH1F *GenGluonSubjetPT1PT, *GenGluonSubjetPT2PT, *GenGluonSubjetPT3PT;
    
    TH1F *GenTopJetNumber, *GenGluonJetNumber;

    TH1F *DTGenTopJetPT;
    TH1F *DTGenTopJetM;
    TH1F *DTGenTopJetPtCombined, *DTGenTopJetMCombined;

    TH1F *DTGenTopJetTau1, *DTGenTopJetTau2, *DTGenTopJetTau3, *DTGenTopJetTau4;
    TH1F *DTGenTopJetTau2Tau1, *DTGenTopJetTau3Tau2, *DTGenTopJetTau3Tau1, *DTGenTopJetTau4Tau3, *DTGenTopJetTau4Tau2, *DTGenTopJetTau4Tau1;
    TH1F *DTGenTopSubjetM1M, *DTGenTopSubjetM2M, *DTGenTopSubjetM3M;
    TH1F *DTGenTopSubjetPT1PT, *DTGenTopSubjetPT2PT, *DTGenTopSubjetPT3PT;

    TH1F *DTNGGenTopJetTau1, *DTNGGenTopJetTau2, *DTNGGenTopJetTau3, *DTNGGenTopJetTau4;
    TH1F *DTNGGenTopJetTau2Tau1, *DTNGGenTopJetTau3Tau2, *DTNGGenTopJetTau3Tau1, *DTNGGenTopJetTau4Tau3, *DTNGGenTopJetTau4Tau2, *DTNGGenTopJetTau4Tau1;
    TH1F *DTNGGenTopSubjetM1M, *DTNGGenTopSubjetM2M, *DTNGGenTopSubjetM3M;
    TH1F *DTNGGenTopSubjetPT1PT, *DTNGGenTopSubjetPT2PT, *DTNGGenTopSubjetPT3PT;

    TH1F *GenTopJetCombinedTau1, *GenTopJetCombinedTau2, *GenTopJetCombinedTau3, *GenTopJetCombinedTau4;
    TH1F *GenTopJetCombinedTau2Tau1, *GenTopJetCombinedTau3Tau2, *GenTopJetCombinedTau3Tau1, *GenTopJetCombinedTau4Tau3, *GenTopJetCombinedTau4Tau2, *GenTopJetCombinedTau4Tau1;

    TH1F *GenTopJet1Tau1, *GenTopJet1Tau2, *GenTopJet1Tau3, *GenTopJet1Tau4;
    TH1F *GenTopJet1Tau2Tau1, *GenTopJet1Tau3Tau2, *GenTopJet1Tau3Tau1, *GenTopJet1Tau4Tau3, *GenTopJet1Tau4Tau2, *GenTopJet1Tau4Tau1;

    TH1F *GenTopJet2Tau1, *GenTopJet2Tau2, *GenTopJet2Tau3, *GenTopJet2Tau4;
    TH1F *GenTopJet2Tau2Tau1, *GenTopJet2Tau3Tau2, *GenTopJet2Tau3Tau1, *GenTopJet2Tau4Tau3, *GenTopJet2Tau4Tau2, *GenTopJet2Tau4Tau1;

    TH1F *GenTopJet12Tau1, *GenTopJet12Tau2, *GenTopJet12Tau3, *GenTopJet12Tau4;
    TH1F *GenTopJet12Tau2Tau1, *GenTopJet12Tau3Tau2, *GenTopJet12Tau3Tau1, *GenTopJet12Tau4Tau3, *GenTopJet12Tau4Tau2, *GenTopJet12Tau4Tau1;

    TH1F *GenTopJetCombinedOnlyTau1, *GenTopJetCombinedOnlyTau2, *GenTopJetCombinedOnlyTau3, *GenTopJetCombinedOnlyTau4;
    TH1F *GenTopJetCombinedOnlyTau2Tau1, *GenTopJetCombinedOnlyTau3Tau2, *GenTopJetCombinedOnlyTau3Tau1, *GenTopJetCombinedOnlyTau4Tau3, *GenTopJetCombinedOnlyTau4Tau2, *GenTopJetCombinedOnlyTau4Tau1;

    TH1F *GenJetMass, *GenJetMassCombinedOnly, *GenJetMassNotCombinedOnly;

    TH1F *GenJetMassNotCombinedOnlySubjetsMatched;

    TH1F *DTGenDeltaRTopTop;

    TH1F *DTGenTopJetM_EachQuarkMatched;
    TH1F *DTGenTopJetM_EachQuarkMatched_GluonMatched, *DTGenTopJetM_EachQuarkMatched_NoGluonMatched;

    TH1F *STGenTopJetM_EachQuarkMatched;
    TH1F *STGenTopJetM_EachQuarkMatched_GluonMatched, *STGenTopJetM_EachQuarkMatched_NoGluonMatched;

    TH1F *DTGenTopJetMRatio, *DTGenTopJetpTRatio;

    TH1F *GenTopJetM_dR12, *GenTopJetM_dR08, *GenTopJetM_dR04;
    TH1F *GenTopJetLeadingM_dR12, *GenTopJetLeadingM_dR08, *GenTopJetLeadingM_dR04;
    TH1F *GenTopJetSubLeadingM_dR12, *GenTopJetSubLeadingM_dR08, *GenTopJetSubLeadingM_dR04;

    TH1F *GenTopJetM_dRvaried600, *GenTopJetM_dRvaried450, *GenTopJetM_dRvaried350;
    TH1F *GenTopJetLeadingM_dRvaried600, *GenTopJetLeadingM_dRvaried450, *GenTopJetLeadingM_dRvaried350;
    TH1F *GenTopJetSubLeadingM_dRvaried600, *GenTopJetSubLeadingM_dRvaried450, *GenTopJetSubLeadingM_dRvaried350;

    TH1F *GenDeltaRJets;

    TH1F *GenJetM_dR12, *GenJetM_dR08, *GenJetM_dR04;
    TH1F *GenJetM_dRvaried600, *GenJetM_dRvaried450, *GenJetM_dRvaried350;

    TH1F *GenJetM_dR12_AllQuarksMatched, *GenJetM_dR08_AllQuarksMatched, *GenJetM_dR04_AllQuarksMatched;
    TH1F *GenJetM_dRvaried600_AllQuarksMatched, *GenJetM_dRvaried450_AllQuarksMatched, *GenJetM_dRvaried350_AllQuarksMatched;

    TH1F *GenJetM_dR12_AllQuarksMatched_Gluon, *GenJetM_dR12_AllQuarksMatched_NoGluon;

    TH1F *GenGluonSubjetSize, *GenTopSubjetSize;
    TH1F *GenGluonPt0, *GenTopPt0;

    TH1F *GenGluonNumber;
    TH1F *GenDeltaRGluonTop;
    TH1F *GenDeltaRTopAntitop;
    TH2F *GenDeltaRTopGluonDeltaRTopAntitop;

    TH1F *GenJet1MassAll;
    TH1F *GenJet1MassBot;
    TH1F *GenJet1MassTwoLightQ;
    TH1F *GenJet1MassBotOneLightQ;
    TH1F *GenJet1MassOneQ;
    TH1F *GenJet1MassNoQ;

    TH1F *GenJet1MassGluonAll;
    TH1F *GenJet1MassGluonBot;
    TH1F *GenJet1MassGluonTwoLightQ;
    TH1F *GenJet1MassGluonBotOneLightQ;
    TH1F *GenJet1MassGluonOneQ;
    TH1F *GenJet1MassGluonNoQ;

    TH1F *GenOneJetMassAll, *GenOneJetMassBot, *GenOneJetMassLightQ, *GenOneJetMassBotOneLightQ, *GenOneJetMassTwoLightQ, *GenOneJetMassNoQ;
    TH1F *GenTwoJetMassAll, *GenTwoJetMassTwoQuarks;

    TH1F *GenOneJetAllTau1, *GenOneJetAllTau2, *GenOneJetAllTau3, *GenOneJetAllTau4;
    TH1F *GenOneJetAllTau2Tau1, *GenOneJetAllTau3Tau2, *GenOneJetAllTau3Tau1, *GenOneJetAllTau4Tau3, *GenOneJetAllTau4Tau2, *GenOneJetAllTau4Tau1;


    TH1F *GenTwoJetAllSub1234Tau1, *GenTwoJetAllSub1234Tau2, *GenTwoJetAllSub1234Tau3;
    TH1F *GenTwoJetAllSub1234Tau2Tau1, *GenTwoJetAllSub1234Tau3Tau2, *GenTwoJetAllSub1234Tau3Tau1;

    TH1F *GenTwoJetAllSub1235Tau1, *GenTwoJetAllSub1235Tau2, *GenTwoJetAllSub1235Tau3, *GenTwoJetAllSub1235Tau4;
    TH1F *GenTwoJetAllSub1235Tau2Tau1, *GenTwoJetAllSub1235Tau3Tau2, *GenTwoJetAllSub1235Tau3Tau1, *GenTwoJetAllSub1235Tau4Tau3, *GenTwoJetAllSub1235Tau4Tau2, *GenTwoJetAllSub1235Tau4Tau1;

    TH1F *GenTwoJetAllSub1236Tau1, *GenTwoJetAllSub1236Tau2, *GenTwoJetAllSub1236Tau3, *GenTwoJetAllSub1236Tau4;
    TH1F *GenTwoJetAllSub1236Tau2Tau1, *GenTwoJetAllSub1236Tau3Tau2, *GenTwoJetAllSub1236Tau3Tau1, *GenTwoJetAllSub1236Tau4Tau3, *GenTwoJetAllSub1236Tau4Tau2, *GenTwoJetAllSub1236Tau4Tau1;

    TH1F *GenTwoJetAllSub1245Tau1, *GenTwoJetAllSub1245Tau2, *GenTwoJetAllSub1245Tau3, *GenTwoJetAllSub1245Tau4;
    TH1F *GenTwoJetAllSub1245Tau2Tau1, *GenTwoJetAllSub1245Tau3Tau2, *GenTwoJetAllSub1245Tau3Tau1, *GenTwoJetAllSub1245Tau4Tau3, *GenTwoJetAllSub1245Tau4Tau2, *GenTwoJetAllSub1245Tau4Tau1;

    TH1F *GenTwoJetAllSub1246Tau1, *GenTwoJetAllSub1246Tau2, *GenTwoJetAllSub1246Tau3, *GenTwoJetAllSub1246Tau4;
    TH1F *GenTwoJetAllSub1246Tau2Tau1, *GenTwoJetAllSub1246Tau3Tau2, *GenTwoJetAllSub1246Tau3Tau1, *GenTwoJetAllSub1246Tau4Tau3, *GenTwoJetAllSub1246Tau4Tau2, *GenTwoJetAllSub1246Tau4Tau1;

    TH1F *GenTwoJetAllSub1256Tau1, *GenTwoJetAllSub1256Tau2, *GenTwoJetAllSub1256Tau3, *GenTwoJetAllSub1256Tau4;
    TH1F *GenTwoJetAllSub1256Tau2Tau1, *GenTwoJetAllSub1256Tau3Tau2, *GenTwoJetAllSub1256Tau3Tau1, *GenTwoJetAllSub1256Tau4Tau3, *GenTwoJetAllSub1256Tau4Tau2, *GenTwoJetAllSub1256Tau4Tau1;

    TH1F *GenTwoJetAllSub1345Tau1, *GenTwoJetAllSub1345Tau2, *GenTwoJetAllSub1345Tau3, *GenTwoJetAllSub1345Tau4;
    TH1F *GenTwoJetAllSub1345Tau2Tau1, *GenTwoJetAllSub1345Tau3Tau2, *GenTwoJetAllSub1345Tau3Tau1, *GenTwoJetAllSub1345Tau4Tau3, *GenTwoJetAllSub1345Tau4Tau2, *GenTwoJetAllSub1345Tau4Tau1;

    TH1F *GenTwoJetAllSub1346Tau1, *GenTwoJetAllSub1346Tau2, *GenTwoJetAllSub1346Tau3, *GenTwoJetAllSub1346Tau4;
    TH1F *GenTwoJetAllSub1346Tau2Tau1, *GenTwoJetAllSub1346Tau3Tau2, *GenTwoJetAllSub1346Tau3Tau1, *GenTwoJetAllSub1346Tau4Tau3, *GenTwoJetAllSub1346Tau4Tau2, *GenTwoJetAllSub1346Tau4Tau1;

    TH1F *GenTwoJetAllSub1356Tau1, *GenTwoJetAllSub1356Tau2, *GenTwoJetAllSub1356Tau3, *GenTwoJetAllSub1356Tau4;
    TH1F *GenTwoJetAllSub1356Tau2Tau1, *GenTwoJetAllSub1356Tau3Tau2, *GenTwoJetAllSub1356Tau3Tau1, *GenTwoJetAllSub1356Tau4Tau3, *GenTwoJetAllSub1356Tau4Tau2, *GenTwoJetAllSub1356Tau4Tau1;

    TH1F *GenTwoJetAllSub1456Tau1, *GenTwoJetAllSub1456Tau2, *GenTwoJetAllSub1456Tau3, *GenTwoJetAllSub1456Tau4;
    TH1F *GenTwoJetAllSub1456Tau2Tau1, *GenTwoJetAllSub1456Tau3Tau2, *GenTwoJetAllSub1456Tau3Tau1, *GenTwoJetAllSub1456Tau4Tau3, *GenTwoJetAllSub1456Tau4Tau2, *GenTwoJetAllSub1456Tau4Tau1;
    
    TH1F *GenTwoJetAllSub2345Tau1, *GenTwoJetAllSub2345Tau2, *GenTwoJetAllSub2345Tau3, *GenTwoJetAllSub2345Tau4;
    TH1F *GenTwoJetAllSub2345Tau2Tau1, *GenTwoJetAllSub2345Tau3Tau2, *GenTwoJetAllSub2345Tau3Tau1, *GenTwoJetAllSub2345Tau4Tau3, *GenTwoJetAllSub2345Tau4Tau2, *GenTwoJetAllSub2345Tau4Tau1;
    
    TH1F *GenTwoJetAllSub2346Tau1, *GenTwoJetAllSub2346Tau2, *GenTwoJetAllSub2346Tau3, *GenTwoJetAllSub2346Tau4;
    TH1F *GenTwoJetAllSub2346Tau2Tau1, *GenTwoJetAllSub2346Tau3Tau2, *GenTwoJetAllSub2346Tau3Tau1, *GenTwoJetAllSub2346Tau4Tau3, *GenTwoJetAllSub2346Tau4Tau2, *GenTwoJetAllSub2346Tau4Tau1;
    
    TH1F *GenTwoJetAllSub2356Tau1, *GenTwoJetAllSub2356Tau2, *GenTwoJetAllSub2356Tau3, *GenTwoJetAllSub2356Tau4;
    TH1F *GenTwoJetAllSub2356Tau2Tau1, *GenTwoJetAllSub2356Tau3Tau2, *GenTwoJetAllSub2356Tau3Tau1, *GenTwoJetAllSub2356Tau4Tau3, *GenTwoJetAllSub2356Tau4Tau2, *GenTwoJetAllSub2356Tau4Tau1;
    
    TH1F *GenTwoJetAllSub2456Tau1, *GenTwoJetAllSub2456Tau2, *GenTwoJetAllSub2456Tau3, *GenTwoJetAllSub2456Tau4;
    TH1F *GenTwoJetAllSub2456Tau2Tau1, *GenTwoJetAllSub2456Tau3Tau2, *GenTwoJetAllSub2456Tau3Tau1, *GenTwoJetAllSub2456Tau4Tau3, *GenTwoJetAllSub2456Tau4Tau2, *GenTwoJetAllSub2456Tau4Tau1;
    
    TH1F *GenTwoJetAllSub3456Tau1, *GenTwoJetAllSub3456Tau2, *GenTwoJetAllSub3456Tau3, *GenTwoJetAllSub3456Tau4;
    TH1F *GenTwoJetAllSub3456Tau2Tau1, *GenTwoJetAllSub3456Tau3Tau2, *GenTwoJetAllSub3456Tau3Tau1, *GenTwoJetAllSub3456Tau4Tau3, *GenTwoJetAllSub3456Tau4Tau2, *GenTwoJetAllSub3456Tau4Tau1;
    
    TH1F *GenTwoJetAllSubAllTau1, *GenTwoJetAllSubAllTau2, *GenTwoJetAllSubAllTau3, *GenTwoJetAllSubAllTau4;
    TH1F *GenTwoJetAllSubAllTau2Tau1, *GenTwoJetAllSubAllTau3Tau2, *GenTwoJetAllSubAllTau3Tau1, *GenTwoJetAllSubAllTau4Tau3, *GenTwoJetAllSubAllTau4Tau2, *GenTwoJetAllSubAllTau4Tau1;
    
    TH1F *GenTwoJetAllSubMatchedTau1, *GenTwoJetAllSubMatchedTau2, *GenTwoJetAllSubMatchedTau3, *GenTwoJetAllSubMatchedTau4;
    TH1F *GenTwoJetAllSubMatchedTau2Tau1, *GenTwoJetAllSubMatchedTau3Tau2, *GenTwoJetAllSubMatchedTau3Tau1, *GenTwoJetAllSubMatchedTau4Tau3, *GenTwoJetAllSubMatchedTau4Tau2, *GenTwoJetAllSubMatchedTau4Tau1;

    TH1F *GenTwoJetAllSubOneMatchedTau1, *GenTwoJetAllSubOneMatchedTau2, *GenTwoJetAllSubOneMatchedTau3, *GenTwoJetAllSubOneMatchedTau4;
    TH1F *GenTwoJetAllSubOneMatchedTau2Tau1, *GenTwoJetAllSubOneMatchedTau3Tau2, *GenTwoJetAllSubOneMatchedTau3Tau1, *GenTwoJetAllSubOneMatchedTau4Tau3, *GenTwoJetAllSubOneMatchedTau4Tau2, *GenTwoJetAllSubOneMatchedTau4Tau1;

    TH1F *GenTwoJetAllSubTwoMatchedTau1, *GenTwoJetAllSubTwoMatchedTau2, *GenTwoJetAllSubTwoMatchedTau3, *GenTwoJetAllSubTwoMatchedTau4;
    TH1F *GenTwoJetAllSubTwoMatchedTau2Tau1, *GenTwoJetAllSubTwoMatchedTau3Tau2, *GenTwoJetAllSubTwoMatchedTau3Tau1, *GenTwoJetAllSubTwoMatchedTau4Tau3, *GenTwoJetAllSubTwoMatchedTau4Tau2, *GenTwoJetAllSubTwoMatchedTau4Tau1;

    TH1F *GenTwoJetAllSubPartialMatchedTau1, *GenTwoJetAllSubPartialMatchedTau2, *GenTwoJetAllSubPartialMatchedTau3, *GenTwoJetAllSubPartialMatchedTau4;
    TH1F *GenTwoJetAllSubPartialMatchedTau2Tau1, *GenTwoJetAllSubPartialMatchedTau3Tau2, *GenTwoJetAllSubPartialMatchedTau3Tau1, *GenTwoJetAllSubPartialMatchedTau4Tau3, *GenTwoJetAllSubPartialMatchedTau4Tau2, *GenTwoJetAllSubPartialMatchedTau4Tau1;

    TH1F *GenTwoJetAllSubOnlyThreeMatchedTau1, *GenTwoJetAllSubOnlyThreeMatchedTau2, *GenTwoJetAllSubOnlyThreeMatchedTau3, *GenTwoJetAllSubOnlyThreeMatchedTau4;
    TH1F *GenTwoJetAllSubOnlyThreeMatchedTau2Tau1, *GenTwoJetAllSubOnlyThreeMatchedTau3Tau2, *GenTwoJetAllSubOnlyThreeMatchedTau3Tau1, *GenTwoJetAllSubOnlyThreeMatchedTau4Tau3, *GenTwoJetAllSubOnlyThreeMatchedTau4Tau2, *GenTwoJetAllSubOnlyThreeMatchedTau4Tau1;

    TH1F *GenTwoJetAllSubUnmatchedTau1, *GenTwoJetAllSubUnmatchedTau2, *GenTwoJetAllSubUnmatchedTau3, *GenTwoJetAllSubUnmatchedTau4;
    TH1F *GenTwoJetAllSubUnmatchedTau2Tau1, *GenTwoJetAllSubUnmatchedTau3Tau2, *GenTwoJetAllSubUnmatchedTau3Tau1, *GenTwoJetAllSubUnmatchedTau4Tau3, *GenTwoJetAllSubUnmatchedTau4Tau2, *GenTwoJetAllSubUnmatchedTau4Tau1;


    TH1F *GenTwoJetAllSubAllMass, *GenTwoJetAllSubMatchedMass, *GenTwoJetAllSubPartialMatchedMass, *GenTwoJetAllSubNoneMatchedMass, *GenTwoJetAll4SubMatchedMass, *GenTwoJetAll4SubPartialMatchedMass, *GenTwoJetAllSubTau21MaxMass, *GenTwoJetAllSubMaxPTMass;


    TH1F *GenTwoJetAllTau1, *GenTwoJetAllTau2, *GenTwoJetAllTau3, *GenTwoJetAllTau4;
    TH1F *GenTwoJetAllTau2Tau1, *GenTwoJetAllTau3Tau2, *GenTwoJetAllTau3Tau1, *GenTwoJetAllTau4Tau3, *GenTwoJetAllTau4Tau2, *GenTwoJetAllTau4Tau1;


    TH1F *GenTwoJetAllSubMatchedSize;
    TH1F *GenTwoJetAllSubOneMatchedSize;
    TH1F *GenTwoJetAllSubTwoMatchedSize;
    TH1F* GenTwoJetAllSubUnmatchedSize;
    TH1F *GenTwoJetAll4SubMatchedSize;
    TH1F *GenTwoJetAll4SubPartialMatchedSize;

    TH1F *GenDecayProductInBothJets;

    TH2F *GenOneJetMassAllDRJet12;
    TH2F *GenTwoJetMassAllDRJet12;

    TH1F *GenJetMassSingleJet, *GenJetMassNearCombined, *GenJetMassNear3SubCombined, *GenJetMassNear4SubCombined;

    TH1F *GenTwoJetAllSubPartialMatchedTau2Zero;
    TH1F *GenTwoJetAllSubMatchedMultipleSubjets;

    TH1F *GenTwoJetAllSubAllSubjet1pT, *GenTwoJetAllSubAllSubjet2pT, *GenTwoJetAllSubAllSubjet3pT;
    TH1F *GenTwoJetAllSubMatchedSubjet1pT, *GenTwoJetAllSubMatchedSubjet2pT, *GenTwoJetAllSubMatchedSubjet3pT;
    TH1F *GenTwoJetAllSubPartialMatchedSubjet1pT, *GenTwoJetAllSubPartialMatchedSubjet2pT, *GenTwoJetAllSubPartialMatchedSubjet3pT;

    TH1F *GenTwoJetAllSubAllDR12, *GenTwoJetAllSubAllDR23, *GenTwoJetAllSubAllDR31;
    TH1F *GenTwoJetAllSubMatchedDR12, *GenTwoJetAllSubMatchedDR23, *GenTwoJetAllSubMatchedDR31;
    TH1F *GenTwoJetAllSubPartialMatchedDR12, *GenTwoJetAllSubPartialMatchedDR23, *GenTwoJetAllSubPartialMatchedDR31;

    TH1F *GenTwoJetAllSubAllDR1Axis, *GenTwoJetAllSubAllDR2Axis, *GenTwoJetAllSubAllDR3Axis;
    TH1F *GenTwoJetAllSubMatchedDR1Axis, *GenTwoJetAllSubMatchedDR2Axis, *GenTwoJetAllSubMatchedDR3Axis;
    TH1F *GenTwoJetAllSubPartialMatchedDR1Axis, *GenTwoJetAllSubPartialMatchedDR2Axis, *GenTwoJetAllSubPartialMatchedDR3Axis;

    TH2F *GenTwoJetAllSubAllDRAxisMinMax, *GenTwoJetAllSubMatchedDRAxisMinMax, *GenTwoJetAllSubPartialMatchedDRAxisMinMax, *GenTwoJetAllSubUnmatchedDRAxisMinMax;

    TH1F *GenTwoJetAllSubjet1pT, *GenTwoJetAllSubjet2pT, *GenTwoJetAllSubjet3pT, *GenTwoJetAllSubjet4pT, *GenTwoJetAllSubjet5pT, *GenTwoJetAllSubjet6pT;
    TH1F *GenTwoJetBotSubjetpT, *GenTwoJetLightQ1SubjetpT, *GenTwoJetLightQ2SubjetpT, *GenTwoJetLightQCombinedSubjetpT, *GenTwoJetMultipleQSubjetpT;


    TH1F *GenJetMassTau21CutLower, *GenJetMassTau21CutLowerTop, *GenJetMassTau21CutLowerGluon;
    TH1F *GenJetMassTau21CutHigher, *GenJetMassTau21CutHigherTop, *GenJetMassTau21CutHigherGluon;

    TH1F *GenJetMassTau31CutLower, *GenJetMassTau31CutLowerTop, *GenJetMassTau31CutLowerGluon;
    TH1F *GenJetMassTau31CutHigher, *GenJetMassTau31CutHigherTop, *GenJetMassTau31CutHigherGluon;

    TH1F *GenJetMassTau32CutLower, *GenJetMassTau32CutLowerTop, *GenJetMassTau32CutLowerGluon;
    TH1F *GenJetMassTau32CutHigher, *GenJetMassTau32CutHigherTop, *GenJetMassTau32CutHigherGluon;

    TH1F *GenJetMassTau41CutLower, *GenJetMassTau41CutLowerTop, *GenJetMassTau41CutLowerGluon;
    TH1F *GenJetMassTau41CutHigher, *GenJetMassTau41CutHigherTop, *GenJetMassTau41CutHigherGluon;

    TH1F *GenJetMassTau42CutLower, *GenJetMassTau42CutLowerTop, *GenJetMassTau42CutLowerGluon;
    TH1F *GenJetMassTau42CutHigher, *GenJetMassTau42CutHigherTop, *GenJetMassTau42CutHigherGluon;


    TH1F *GenJetMassCombinedTau21CutLower, *GenJetMassCombinedTau21CutLowerTop, *GenJetMassCombinedTau21CutLowerGluon;
    TH1F *GenJetMassCombinedTau21CutHigher, *GenJetMassCombinedTau21CutHigherTop, *GenJetMassCombinedTau21CutHigherGluon;

    TH1F *GenJetMassCombinedTau31CutLower, *GenJetMassCombinedTau31CutLowerTop, *GenJetMassCombinedTau31CutLowerGluon;
    TH1F *GenJetMassCombinedTau31CutHigher, *GenJetMassCombinedTau31CutHigherTop, *GenJetMassCombinedTau31CutHigherGluon;

    TH1F *GenJetMassCombinedTau32CutLower, *GenJetMassCombinedTau32CutLowerTop, *GenJetMassCombinedTau32CutLowerGluon;
    TH1F *GenJetMassCombinedTau32CutHigher, *GenJetMassCombinedTau32CutHigherTop, *GenJetMassCombinedTau32CutHigherGluon;

    TH1F *GenJetMassCombinedTau41CutLower, *GenJetMassCombinedTau41CutLowerTop, *GenJetMassCombinedTau41CutLowerGluon;
    TH1F *GenJetMassCombinedTau41CutHigher, *GenJetMassCombinedTau41CutHigherTop, *GenJetMassCombinedTau41CutHigherGluon;

    TH1F *GenJetMassCombinedTau42CutLower, *GenJetMassCombinedTau42CutLowerTop, *GenJetMassCombinedTau42CutLowerGluon;
    TH1F *GenJetMassCombinedTau42CutHigher, *GenJetMassCombinedTau42CutHigherTop, *GenJetMassCombinedTau42CutHigherGluon;


    TH1F *GenJetMassNoCombinedTau21CutLower, *GenJetMassNoCombinedTau21CutLowerTop, *GenJetMassNoCombinedTau21CutLowerGluon;
    TH1F *GenJetMassNoCombinedTau21CutHigher, *GenJetMassNoCombinedTau21CutHigherTop, *GenJetMassNoCombinedTau21CutHigherGluon;

    TH1F *GenJetMassNoCombinedTau31CutLower, *GenJetMassNoCombinedTau31CutLowerTop, *GenJetMassNoCombinedTau31CutLowerGluon;
    TH1F *GenJetMassNoCombinedTau31CutHigher, *GenJetMassNoCombinedTau31CutHigherTop, *GenJetMassNoCombinedTau31CutHigherGluon;

    TH1F *GenJetMassNoCombinedTau32CutLower, *GenJetMassNoCombinedTau32CutLowerTop, *GenJetMassNoCombinedTau32CutLowerGluon;
    TH1F *GenJetMassNoCombinedTau32CutHigher, *GenJetMassNoCombinedTau32CutHigherTop, *GenJetMassNoCombinedTau32CutHigherGluon;

    TH1F *GenJetMassNoCombinedTau41CutLower, *GenJetMassNoCombinedTau41CutLowerTop, *GenJetMassNoCombinedTau41CutLowerGluon;
    TH1F *GenJetMassNoCombinedTau41CutHigher, *GenJetMassNoCombinedTau41CutHigherTop, *GenJetMassNoCombinedTau41CutHigherGluon;

    TH1F *GenJetMassNoCombinedTau42CutLower, *GenJetMassNoCombinedTau42CutLowerTop, *GenJetMassNoCombinedTau42CutLowerGluon;
    TH1F *GenJetMassNoCombinedTau42CutHigher, *GenJetMassNoCombinedTau42CutHigherTop, *GenJetMassNoCombinedTau42CutHigherGluon;

    TH1F *GenJetNumber;

    uhh2::Event::Handle<TTbarGen>h_ttbargen;
    uhh2::Event::Handle<std::vector<GenTopJet>>h_jets;

    bool debug;
};
