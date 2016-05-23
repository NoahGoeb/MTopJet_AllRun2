#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/CleaningModules.h>
#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/LumiSelection.h>
#include <UHH2/common/include/TriggerSelection.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/MuonIds.h>
#include <UHH2/common/include/ElectronIds.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/AdditionalSelections.h>

#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/EventHists.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/TTbarGenHists.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>

class MTopJetSelectionModule : public ModuleBASE {

 public:
  explicit MTopJetSelectionModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

 protected:
  enum lepton { muon, elec };
  lepton channel_;

  // cleaners
  std::unique_ptr<MuonCleaner>     muoSR_cleaner;
  std::unique_ptr<ElectronCleaner> eleSR_cleaner;

  std::unique_ptr<JetCleaner>                      jet_IDcleaner;
  std::unique_ptr<JetCorrector>                    jet_corrector;
  std::unique_ptr<GenericJetResolutionSmearer>     jetER_smearer;
  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> jetlepton_cleaner;
  std::unique_ptr<JetCleaner>                      jet_cleaner1;
  std::unique_ptr<JetCleaner>                      jet_cleaner2;

  std::unique_ptr<JetCleaner>                  topjet_IDcleaner;
  std::unique_ptr<TopJetCorrector>             topjet_corrector;
  std::unique_ptr<SubJetCorrector>             topjet_subjet_corrector;
  std::unique_ptr<GenericJetResolutionSmearer> topjetER_smearer;
  std::unique_ptr<TopJetLeptonDeltaRCleaner>   topjetlepton_cleaner;
  std::unique_ptr<TopJetCleaner>               topjet_cleaner;

  // selections
  std::unique_ptr<uhh2::Selection> lumi_sel;
  std::unique_ptr<uhh2::AndSelection> metfilters_sel;

  std::unique_ptr<uhh2::Selection> genmttbar_sel;
  std::unique_ptr<uhh2::Selection> genflavor_sel;

  std::unique_ptr<uhh2::Selection> jet2_sel;
  std::unique_ptr<uhh2::Selection> jet1_sel;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<uhh2::Selection> twodcut_sel;

  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;


  // store Hist collection as member variables
  std::unique_ptr<Hists> h_jetsel_event, h_jetsel_elec, h_jetsel_muon, h_jetsel_jets, h_metsel_event, h_metsel_elec, h_metsel_muon, h_metsel_jets, h_htsel_event, h_htsel_elec, h_htsel_muon, h_htsel_jets, h_twodsel_event, h_twodsel_elec, h_twodsel_muon, h_twodsel_jets;

  // Event::Handle<float> tt_TMVA_response;// response of TMVA method, dummy value at this step

};

MTopJetSelectionModule::MTopJetSelectionModule(uhh2::Context& ctx){

  //// CONFIGURATION
  const bool isMC = (ctx.get("dataset_type") == "MC");

  const std::string& channel = ctx.get("channel", ""); //define Channel
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;
  else {

    std::string log("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- ");
    log += "invalid argument for 'channel' key in xml file (must be 'muon' or 'elec'): \""+channel+"\"";

    throw std::runtime_error(log);
  }

  ElectronId eleID;
  float jet1_pt(-1.), jet2_pt(-1.), MET(-1.), HT_lep(-1.);

  //    eleID  = ElectronID_Spring15_25ns_tight_noIso;
  eleID = ElectronID_MVAnotrig_Spring15_25ns_loose; //TEST 

  jet1_pt =  50.;
  jet2_pt =  50.;

  MET     =  20.;
  HT_lep  =  50.;
 
  ////

  //// COMMON MODULES

  if(!isMC) lumi_sel.reset(new LumiSelection(ctx));


  ////

  //// OBJ CLEANING
 
  //// EVENT SELECTION
  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));

  met_sel  .reset(new METCut  (MET   , uhh2::infinity));
  htlep_sel.reset(new HTlepCut(HT_lep, uhh2::infinity));

  twodcut_sel.reset(new TwoDCut1(.4, 40.));
  ////

  //// set up Hists classes:
  h_jetsel_event.reset(new EventHists(ctx, "01_JetSel_Event"));
  h_jetsel_elec.reset(new ElectronHists(ctx, "01_JetSel_Elec"));
  h_jetsel_muon.reset(new MuonHists(ctx, "01_JetSel_Muon"));
  h_jetsel_jets.reset(new JetHists(ctx, "01_JetSel_Jets"));

  h_metsel_event.reset(new EventHists(ctx, "02_METSel_Event"));
  h_metsel_elec.reset(new ElectronHists(ctx, "02_METSel_Elec"));
  h_metsel_muon.reset(new MuonHists(ctx, "02_METSel_Muon"));
  h_metsel_jets.reset(new JetHists(ctx, "02_METSel_Jets"));

  h_htsel_event.reset(new EventHists(ctx, "03_HTSel_Event"));
  h_htsel_elec.reset(new ElectronHists(ctx, "03_HTSel_Elec"));
  h_htsel_muon.reset(new MuonHists(ctx, "03_HTSel_Muon"));
  h_htsel_jets.reset(new JetHists(ctx, "03_HTSel_Jets"));

  h_twodsel_event.reset(new EventHists(ctx, "04_TwoDSel_Event"));
  h_twodsel_elec.reset(new ElectronHists(ctx, "04_TwoDSel_Elec"));
  h_twodsel_muon.reset(new MuonHists(ctx, "04_TwoDSel_Muon"));
  h_twodsel_jets.reset(new JetHists(ctx, "04_TwoDSel_Jets"));

  ////

}

bool MTopJetSelectionModule::process(uhh2::Event& event){

  //// COMMON MODULES


  ////

  //// LEPTON selection

  ////

  //// JET selection


  /* lepton-2Dcut variables */
  const bool pass_twodcut = twodcut_sel->passes(event); {

    for(auto& muo : *event.muons){

      float    dRmin, pTrel;
      std::tie(dRmin, pTrel) = drmin_pTrel(muo, *event.jets);

      muo.set_tag(Muon::twodcut_dRmin, dRmin);
      muo.set_tag(Muon::twodcut_pTrel, pTrel);
    }

    for(auto& ele : *event.electrons){

      float    dRmin, pTrel;
      std::tie(dRmin, pTrel) = drmin_pTrel(ele, *event.jets);

      ele.set_tag(Electron::twodcut_dRmin, dRmin);
      ele.set_tag(Electron::twodcut_pTrel, pTrel);
    }
  }


  /* 2nd AK4 jet selection */
  const bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;

  /* 1st AK4 jet selection */
  const bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;

  h_jetsel_event->fill(event);
  h_jetsel_elec->fill(event);
  h_jetsel_muon->fill(event);
  h_jetsel_jets->fill(event);
  ////

  //// MET selection
  const bool pass_met = met_sel->passes(event);
  if(!pass_met) return false;
  h_metsel_event->fill(event);
  h_metsel_elec->fill(event);
  h_metsel_muon->fill(event);
  h_metsel_jets->fill(event);
  ////

  //// HT_lep selection
  const bool pass_htlep = htlep_sel->passes(event);
  if(!pass_htlep) return false;
  h_htsel_event->fill(event);
  h_htsel_elec->fill(event);
  h_htsel_muon->fill(event);
  h_htsel_jets->fill(event);
  

  
  //// LEPTON-2Dcut selection
  if(!pass_twodcut) return false;
  h_twodsel_event->fill(event);
  h_twodsel_elec->fill(event);
  h_twodsel_muon->fill(event);
  h_twodsel_jets->fill(event);
  ////

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(MTopJetSelectionModule)
