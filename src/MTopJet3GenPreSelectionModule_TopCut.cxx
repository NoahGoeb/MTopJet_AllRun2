#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/LumiSelection.h>
#include <UHH2/common/include/TriggerSelection.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/AdditionalSelections.h>
#include "UHH2/common/include/YearRunSwitchers.h"

// Hists
#include <UHH2/MTopJet/include/CombineXCone.h>
#include <UHH2/MTopJet/include/GenHists_GenOnly.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/EventHists.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/TTbarGenHists.h>
#include <UHH2/MTopJet/include/MTopJetHists.h>
//
#include <UHH2/MTopJet/include/ModuleBASE.h>
#include <UHH2/MTopJet/include/RecoSelections.h>
#include <UHH2/MTopJet/include/GenSelections.h>
#include <UHH2/MTopJet/include/MTopJetUtils.h>

#include <UHH2/MTopJet/include/ControlHists.h>

#include "TH1F.h"

using namespace std;

class MTopJet3GenPreSelectionModule_TopCut : public ModuleBASE {

public:
  explicit MTopJet3GenPreSelectionModule_TopCut(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

protected:
  // enum lepton { muon, elec };
  // lepton channel_;

  // selections
  std::unique_ptr<uhh2::Selection> lumi_sel;

  std::unique_ptr<uhh2::Selection> genmttbar_sel;
  std::unique_ptr<uhh2::Selection> genflavor_sel;
  std::unique_ptr<uhh2::Selection> muon_sel;
  std::unique_ptr<uhh2::Selection> elec_sel;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> SemiLepDecay;
  std::unique_ptr<uhh2::Selection> GenMuonPT;
  std::unique_ptr<uhh2::Selection> GenElecPT;

  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;

  //hists rec
  std::unique_ptr<Hists> h_lep1, h_met, h_lepsel, h_fatpt;
  //hists gen
  std::unique_ptr<Hists> h_genpt;
  std::unique_ptr<Hists> h_nocuts, h_isMC, h_semilep, h_lepton, h_passPreSel;

  // handles for output
  Event::Handle<bool>h_recsel;
  Event::Handle<bool>h_gensel;
  Event::Handle<std::vector<GenTopJet>>h_GENfatjets;
  Event::Handle<std::vector<TopJet>>h_fatjets;
  Event::Handle<TTbarGen> h_ttbargen;

  // bools
  bool isMC;
  bool isPhotonStream;
  bool isElectronStream;
  bool debug;

  // store Hist collection as member variables
  std::unique_ptr<Hists> h_ttbar;

  //Year year;
};

/*
███    ███  ██████  ██████  ██    ██ ██      ███████
████  ████ ██    ██ ██   ██ ██    ██ ██      ██
██ ████ ██ ██    ██ ██   ██ ██    ██ ██      █████
██  ██  ██ ██    ██ ██   ██ ██    ██ ██      ██
██      ██  ██████  ██████   ██████  ███████ ███████
*/

MTopJet3GenPreSelectionModule_TopCut::MTopJet3GenPreSelectionModule_TopCut(uhh2::Context& ctx){

  debug = string2bool(ctx.get("Debug","false")); // look for Debug, expect false if not found

  if(debug) cout << "Start Module - Ctx" << endl;
  
  //// CONFIGURATION
  bool isherwig;
  if(ctx.get("dataset_version") == "TTbar_powheg-herwig") isherwig = true;
  else isherwig = false;

  isMC = (ctx.get("dataset_type") == "MC"); 

  if(debug) cout << "CONFIGURATION" << endl;

  //HIST-classes
  h_ttbar.reset(new TTbarGenHists(ctx, "TTbar"));

  //year = extract_year(ctx); // Ask for the year of Event

  // const std::string& channel = ctx.get("channel", ""); //define Channel
  // if     (channel == "muon") channel_ = muon;
  // else if(channel == "elec") channel_ = elec;
  // else {
  //
  //   std::string log("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- ");
  //   log += "invalid argument for 'channel' key in xml file (must be 'muon' or 'elec'): \""+channel+"\"";
  //
  //   throw std::runtime_error(log);
  // }

  h_recsel = ctx.declare_event_output<bool>("passed_recsel");
  h_gensel = ctx.declare_event_output<bool>("passed_gensel");
  h_GENfatjets = ctx.get_handle<std::vector<GenTopJet>>("genXCone3TopJets");
  h_fatjets = ctx.get_handle<std::vector<TopJet>>("xconeCHS");
  h_ttbargen = ctx.get_handle<TTbarGen>("ttbargen");
  ////

  if(debug) cout << "Output and Handles" << endl;

  //// COMMON MODULES

  if(!isMC) lumi_sel.reset(new LumiSelection(ctx));

  if(debug) cout << "LumiSelection" << endl;

  /* GEN M-ttbar selection [TTbar MC "0.<M^{gen}_{ttbar}(GeV)<700.] */
  const std::string ttbar_gen_label("ttbargen");

  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));

  if(debug) cout << "TTbarGenProducer" << endl;

  TString samplename = ctx.get("dataset_version");
  if( samplename.Contains("Mtt0000to0700") ){
    genmttbar_sel.reset(new MttbarGenSelection(0., 700.));
  }
  else{
    genmttbar_sel.reset(new uhh2::AndSelection(ctx));
  }

  //else throw runtime_error("In PreSelectionModule: This Event is not from 2016v3, 2017v2 or 2018!");

  /******************************************************************/

  //// EVENT SELECTION REC
  met_sel.reset(new METCut(40, uhh2::infinity));
  muon_sel.reset(new NMuonSelection(1, -1, MuonId(PtEtaCut(50, 2.4 ))));
  elec_sel.reset(new NElectronSelection(1, -1, ElectronId(PtEtaCut(50, 2.4))));
  ////

  if(debug) cout << "EVENT SELECTION REC" << endl;

  //// EVENTS SELECTION GEN
  if(isMC && !isherwig) SemiLepDecay.reset(new TTbarSemilep(ctx));
  else if(isherwig) SemiLepDecay.reset(new TTbarSemilep_herwig(ctx));
  if(isMC){
    GenMuonPT.reset(new GenMuonSel(ctx, 55.));
    GenElecPT.reset(new GenElecSel(ctx, 55.));
  }
  ////

  if(debug) cout << "EVENTS SELECTION GEN" << endl;

  h_lep1.reset(new CountingEventHists(ctx, "h_lep1"));
  h_met.reset(new CountingEventHists(ctx, "h_met"));
  h_fatpt.reset(new CountingEventHists(ctx, "h_fatpt"));
  h_lepsel.reset(new CountingEventHists(ctx, "h_lepsel"));

  h_genpt.reset(new CountingEventHists(ctx, "h_genpts"));

  h_nocuts.reset(new GenHists_GenOnly(ctx, "nocuts", "genXCone3TopJets"));
  h_isMC.reset(new GenHists_GenOnly(ctx, "isMC", "genXCone3TopJets"));
  h_semilep.reset(new GenHists_GenOnly(ctx, "semilep", "genXCone3TopJets"));
  h_lepton.reset(new GenHists_GenOnly(ctx, "lepton", "genXCone3TopJets"));
  h_passPreSel.reset(new GenHists_GenOnly(ctx, "passPreSel", "genXCone3TopJets"));

}

/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/

bool MTopJet3GenPreSelectionModule_TopCut::process(uhh2::Event& event){

  if(debug) cout << "Start Module - Process" << endl;

  bool passed_recsel;
  bool passed_gensel;

  if(!event.isRealData){
    /* GEN M-ttbar selection */
    ttgenprod->process(event);
    if(!genmttbar_sel->passes(event)) return false;
  }

  /* CMS-certified luminosity sections */
  if(event.isRealData){
    if(!lumi_sel->passes(event)) return false;
  }

  if(debug) cout << "CMS-certified luminosity sections" << endl;

  const bool pass_lep1 = ((event.muons->size() >= 1) || (event.electrons->size() >= 1));
  const bool pass_met = met_sel->passes(event);
  const bool pass_lepsel = (muon_sel->passes(event) || elec_sel->passes(event));

  // cut on fatjet pt
  bool passed_fatpt=false;
  std::vector<TopJet> jets = event.get(h_fatjets);
  double ptcut = 200;
  for(auto jet: jets){
    if(jet.pt() > ptcut) passed_fatpt = true;
  }
  ///

  if(debug) cout << "cut on fatjet pt" << endl;

  bool pass_semilep;
  if(isMC)pass_semilep = SemiLepDecay->passes(event);
  else pass_semilep=false;

  bool pass_genlepton = false;
  bool pass_genmuon = false;
  bool pass_genelec = false;
  if(isMC){
    pass_genmuon = GenMuonPT->passes(event);
    pass_genelec = GenElecPT->passes(event);
  }
  if(pass_genmuon || pass_genelec) pass_genlepton = true;

  if(debug) cout << "lepton pt" << endl;

  // cut on GEN Jet PT
  bool passed_genpt = true;
  /*if(isMC && pass_semilep && pass_genlepton) {
    
  }*/
  ///

  TTbarGen ttbargen = event.get(h_ttbargen);
  GenParticle top;
  if(ttbargen.IsTopHadronicDecay()) {
    top = ttbargen.Top();
  } else if(ttbargen.IsAntiTopHadronicDecay()) {
    top = ttbargen.Antitop();
  }
  bool passed_genTopCut = top.pt() > 400;

  if(pass_lep1 && passed_fatpt && pass_met && pass_lepsel) passed_recsel = true;
  else passed_recsel = false;

  if(pass_semilep && passed_genpt && pass_genlepton && passed_genTopCut) passed_gensel = true;
  else passed_gensel = false;

  if(pass_lep1) h_lep1->fill(event);
  if(pass_lep1 && pass_met) h_met->fill(event);
  if(pass_lep1 && pass_met && passed_fatpt) h_fatpt->fill(event);
  if(pass_lep1 && pass_met && passed_fatpt && pass_lepsel) h_lepsel->fill(event);

  if(pass_semilep && pass_genlepton && passed_genpt) h_genpt->fill(event);

  //FILL HISTS
  h_ttbar->fill(event);

  h_nocuts->fill(event);
  if(isMC) {
    h_isMC->fill(event);
    if(pass_semilep) {
      h_semilep->fill(event);
      if(pass_genlepton) {
        h_lepton->fill(event);
      }
    }
  }

  if(!passed_recsel && !passed_gensel) return false;

  h_passPreSel->fill(event);

  event.set(h_recsel, passed_recsel);
  event.set(h_gensel, passed_gensel);

  return true;

}

UHH2_REGISTER_ANALYSIS_MODULE(MTopJet3GenPreSelectionModule_TopCut)
