#pragma once
#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/PFParticle.h"
#include "UHH2/common/include/TTbarGen.h"
#include "UHH2/MTopJet/include/JetCluster.h"


/**  \brief Example class for booking and filling histograms
 * 
 * NOTE: This class uses the 'hist' method to retrieve histograms.
 * This requires a string lookup and is therefore slow if you have
 * many histograms. Therefore, it is recommended to use histogram
 * pointers as member data instead, like in 'common/include/ElectronHists.h'.
 */
class GenHists: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
  GenHists(uhh2::Context & ctx, const std::string & dirname, const std::string & jetname);
    
    virtual void fill(const uhh2::Event & ev) override;

protected:

    TH1F *GenJetNumber;
    TH1F *GenJet1Mass, *Mass1Mass2;
    TH1F *GenJet1PT, *GenJet2PT, *GenJet1Jet2PT, *GenJet3PT, *LeptonPT, *GenJetPT;
    TH1F *GenJet2Eta;
    TH1F *TopHadPT, *TopLepPT;
    TH1F *deltaR_bot_jet1, *deltaR_botlep_jet1,*deltaR_q1_jet1, *deltaR_q2_jet1, *deltaR_lep1_jet1, *deltaR_lep2_jet1, *deltaR_tophad_jet1, *deltaR_toplep_jet1;
    TH1F *deltaR_bot_jet2, *deltaR_botlep_jet2,*deltaR_q1_jet2, *deltaR_q2_jet2, *deltaR_lep1_jet2, *deltaR_lep2_jet2, *deltaR_tophad_jet2, *deltaR_toplep_jet2;
    TH1F *dR_GenParts_q1_q2, *dR_GenParts_bot_q1,*dR_GenParts_bot_q2, *dR_GenParts_highest, *dR_GenParts_lowest; 
    TH2F *dR_GenParts_q1_q2_toppt, *dR_GenParts_bot_q1_toppt,*dR_GenParts_bot_q2_toppt, *dR_GenParts_highest_toppt, *dR_GenParts_lowest_toppt; 
    /* TH1F *deltaR_bot_jet3, *deltaR_botlep_jet3,*deltaR_q1_jet3, *deltaR_q2_jet3, *deltaR_lep1_jet3, *deltaR_lep2_jet3, *deltaR_tophad_jet3, *deltaR_toplep_jet3; */
    /* TH1F *deltaR_bot_jet4, *deltaR_botlep_jet4,*deltaR_q1_jet4, *deltaR_q2_jet4, *deltaR_lep1_jet4, *deltaR_lep2_jet4, *deltaR_tophad_jet4, *deltaR_toplep_jet4; */
    /* TH1F *deltaR_bot_jet5, *deltaR_botlep_jet5,*deltaR_q1_jet5, *deltaR_q2_jet5, *deltaR_lep1_jet5, *deltaR_lep2_jet5, *deltaR_tophad_jet5, *deltaR_toplep_jet5; */
    /* TH1F *deltaR_bot_jet6, *deltaR_botlep_jet6,*deltaR_q1_jet6, *deltaR_q2_jet6, *deltaR_lep1_jet6, *deltaR_lep2_jet6, *deltaR_tophad_jet6, *deltaR_toplep_jet6; */
    
    uhh2::Event::Handle<TTbarGen>h_ttbargen;
    uhh2::Event::Handle<std::vector<Jet>>h_jets;
};

