#include <UHH2/MTopJet/include/GenHists_TwoJetCollections.h>

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

GenHists_TwoJetCollections::GenHists_TwoJetCollections(uhh2::Context & ctx, const std::string & dirname, const std::string & jetname1, const std::string & jetname2): Hists(ctx, dirname){
  // book all histograms here
  
  GenJetsNumberDiff = book<TH1F>("sizeDif", "size1 - size2", 100, 0, 6.0);

  GenJets1PT = book<TH1F>("jets1_PT", "p_{T}", 50, 0, 1000);
  GenJets2PT = book<TH1F>("jets2_PT", "p_{T}", 50, 0, 1000);

  GenJets1Mass = book<TH1F>("M_jets1_Mass", "M_{jet}", 50, 0, 500);
  GenJets2Mass = book<TH1F>("M_jets2_Mass", "M_{jet}", 50, 0, 500);

  // handle for TTbarGen class
  h_ttbargen=ctx.get_handle<TTbarGen>("ttbargen");
  // handle for clustered jets
  h_jets1=ctx.get_handle<std::vector<GenTopJet>>(jetname1);
  h_jets2=ctx.get_handle<std::vector<GenTopJet>>(jetname2);

  debug = string2bool(ctx.get("Debug","false"));
}

void GenHists_TwoJetCollections::fill(const Event & event){

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
  std::vector<GenTopJet> jets1 = event.get(h_jets1);
  std::vector<GenTopJet> jets2 = event.get(h_jets2);
  TLorentzVector jet1_v4, jeti_v4, botSubjet_v4, q1Subjet_v4, q2Subjet_v4;
  std::vector<TLorentzVector> subjets_v4 = {};
  std::vector<TLorentzVector> sortedSubjets_v4 = {};
  std::vector<TLorentzVector> jets1_v4,jets2_v4;

  TLorentzVector lepton1_v4, jet2_lep_v4, topjet1_v4, topjet2_v4;
  GenTopJet jet1,jet2,jet3,jet4,jet5,jet6;
  std::vector<GenJet> subjets, sortedSubjets;
  if(debug) cout << "\t\t--- get jet1" << endl;
  if(jets1.size()>0) {
    jet1 = jets1.at(0);
    subjets = jet1.subjets();
    sortedSubjets = jet1.subjets();
  }
  if(debug) cout << "\t\t--- get jet2" << endl;
  if(jets1.size()>1) jet2 = jets1.at(1);
  if(jets1.size()>2) jet3 = jets1.at(2);
  if(jets1.size()>3) jet4 = jets1.at(3);
  // if(jets1.size()>4) jet5 = jets1.at(4);
  // if(jets1.size()>5) jet6 = jets1.at(5);

  if(debug) cout << "\t\t--- set jets_v4" << endl;

  for(uint i=0; i<jets1.size(); i++) {
    jeti_v4.SetPxPyPzE(jets1.at(i).v4().Px(), jets1.at(i).v4().Py(), jets1.at(i).v4().Pz(), jets1.at(i).v4().E());
    jets1_v4.push_back(jeti_v4);
  }

  for(uint i=0; i<jets2.size(); i++) {
    jeti_v4.SetPxPyPzE(jets2.at(i).v4().Px(), jets2.at(i).v4().Py(), jets2.at(i).v4().Pz(), jets2.at(i).v4().E());
    jets2_v4.push_back(jeti_v4);
  }


  //cout << "sorted subjet pts: " << sortedSubjets.at(0).pt() << ", " << sortedSubjets.at(1).pt() << ", " << sortedSubjets.at(2).pt() << endl;

  //---------------------------------------------------------------------------------------
  //---------------------------------------------------------------------------------------

  uint sizeDiff = jets1.size() - jets2.size();

  GenJetsNumberDiff->Fill(sizeDiff, 1);

  for(uint i=0; i<jets1.size(); i++) {
    GenJets1PT->Fill(jets1_v4.at(i).Pt(), 1);
    GenJets1Mass->Fill(jets1_v4.at(i).M(), 1);
  }

  for(uint i=0; i<jets2.size(); i++) {
    GenJets2PT->Fill(jets2_v4.at(i).Pt(), 1);
    GenJets2Mass->Fill(jets2_v4.at(i).M(), 1);
  }

  //---------------------------------------------------------------------------------------
  //--------------------------------- Matching --------------------------------------------
  //---------------------------------------------------------------------------------------
  if(debug) cout << "\t--- Matching" << endl;

  //bool isTTBar = true;

  // get stable particles from ttbar decay and sort them into leptonic and hadronic

  GenParticle bot, q1, q2, bot_lep, lep1, lep2, lepton, top, antitop; //leptons already defined above
  if(jets1.size() > 0){
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
