#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/CleaningModules.h>
#include <UHH2/common/include/CommonModules.h>
#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/TriggerSelection.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/MuonIds.h>
#include <UHH2/common/include/ElectronIds.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/AdditionalSelections.h>
#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/TopPtReweight.h>

#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/LuminosityHists.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/MTopJet/include/MTopJetHists.h>
#include <UHH2/MTopJet/include/CombineXCone.h>
#include <UHH2/MTopJet/include/AnalysisOutput.h>

#include <UHH2/MTopJet/include/ModuleBASE.h>
#include <UHH2/MTopJet/include/RecoSelections.h>
#include <UHH2/MTopJet/include/MTopJetUtils.h>


/*
*******************************************************************
**************** TO DO ********************************************
*******************************************************************
- b tagging SF
*******************************************************************
*******************************************************************
*/

class MTopJetSelectionModule : public ModuleBASE {

 public:
  explicit MTopJetSelectionModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

 protected:
  enum lepton { muon, elec };
  lepton channel_;

  // cleaners
  std::unique_ptr<CommonModules> common;
  std::unique_ptr<MuonCleaner>     muoSR_cleaner;
  std::unique_ptr<ElectronCleaner> eleSR_cleaner;


  std::unique_ptr<JetCleaner>                      jet_cleaner1;
  std::unique_ptr<JetCleaner>                      jet_cleaner2;


  // selections
  std::unique_ptr<uhh2::AnalysisModule> jetprod_reco;
  std::unique_ptr<uhh2::AnalysisModule> jetprod_gen23;
  std::unique_ptr<uhh2::AnalysisModule> jetprod_gen33;

  std::unique_ptr<uhh2::Selection> trigger_sel_A;
  std::unique_ptr<uhh2::Selection> trigger_sel_B;
  std::unique_ptr<uhh2::Selection> muon_sel;
  std::unique_ptr<uhh2::Selection> elec_sel;
  std::unique_ptr<uhh2::Selection> triangc_sel;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> pv_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<uhh2::Selection> twodcut_sel;
  std::unique_ptr<uhh2::Selection> jet_sel;

  // just for testing
  std::unique_ptr<TopPtReweight> ttbar_reweight;

  // scale factors
  std::unique_ptr<BTagMCEfficiencyHists> BTagEffHists;
  std::unique_ptr<uhh2::AnalysisModule> muo_tight_noniso_SF, muo_trigger_SF;
  std::unique_ptr<uhh2::AnalysisModule> BTagScaleFactors;

  // write output
  std::unique_ptr<uhh2::AnalysisModule> output; 

  // store Hist collection as member variables
  std::unique_ptr<Hists> h_PreSel_event,  h_PreSel_elec, h_PreSel_muon, h_PreSel_jets, h_PreSel_lumi;
  std::unique_ptr<Hists> h_Trigger_event,  h_Trigger_elec, h_Trigger_muon, h_Trigger_jets, h_Trigger_lumi;
  std::unique_ptr<Hists> h_Cleaner_event,  h_Cleaner_elec, h_Cleaner_muon, h_Cleaner_jets, h_Cleaner_lumi;
  std::unique_ptr<Hists> h_Lepton_event,  h_Lepton_elec, h_Lepton_muon, h_Lepton_jets, h_Lepton_lumi;
  std::unique_ptr<Hists> h_TwoD_event,  h_TwoD_elec, h_TwoD_muon, h_TwoD_jets, h_TwoD_lumi;
  std::unique_ptr<Hists> h_Jet_event,  h_Jet_elec, h_Jet_muon, h_Jet_jets, h_Jet_lumi;
  std::unique_ptr<Hists> h_bTag_event,  h_bTag_elec, h_bTag_muon, h_bTag_jets, h_bTag_lumi;
  std::unique_ptr<Hists> h_Side_event,  h_Side_elec, h_Side_muon, h_Side_jets, h_Side_lumi;
  std::unique_ptr<Hists> h_HTlep_event,  h_HTlep_elec, h_HTlep_muon, h_HTlep_jets, h_HTlep_lumi;
  std::unique_ptr<Hists> h_MET_event,  h_MET_elec, h_MET_muon, h_MET_jets, h_MET_lumi;
  std::unique_ptr<Hists> h_ttbar_reweight_event, h_ttbar_reweight_elec, h_ttbar_reweight_muon, h_ttbar_reweight_jets, h_ttbar_reweight_lumi;


  bool isMC; //define here to use it in "process" part
  string BTag_variation ="central";
};

MTopJetSelectionModule::MTopJetSelectionModule(uhh2::Context& ctx){

  //// CONFIGURATION
  isMC = (ctx.get("dataset_type") == "MC");

  const std::string& channel = ctx.get("channel", ""); //define Channel
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;
  else {

    std::string log("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- ");
    log += "invalid argument for 'channel' key in xml file (must be 'muon' or 'elec'): \""+channel+"\"";

    throw std::runtime_error(log);
  }

  // combine XCone
  jetprod_reco.reset(new CombineXCone33(ctx)); 
  if(isMC){
    jetprod_gen23.reset(new CombineXCone23_gen(ctx));
    jetprod_gen33.reset(new CombineXCone33_gen(ctx));
  }	
  ////

  // write output
  output.reset(new WriteOutput(ctx));
  ////

  // just for testing
  ttbar_reweight.reset(new TopPtReweight(ctx,0.159,-0.00141,"","weight_ttbar",true,0.9910819));


  //// EVENT SELECTION


  // define IDs
  MuonId muid = AndId<Muon>(MuonIDTight(), PtEtaCut(55., 2.4));
  ElectronId eleid = AndId<Electron>(ElectronID_Spring16_medium_noIso, PtEtaCut(55., 2.4));
  JetId jetid_cleaner = AndId<Jet>(JetPFID(JetPFID::WP_LOOSE), PtEtaCut(30.0, 2.4));
  JetId jetid_selection = AndId<Jet>(JetPFID(JetPFID::WP_LOOSE), PtEtaCut(50.0, 2.4));
  ////

  // define Trigger
  if(channel_ == muon){
    trigger_sel_A = uhh2::make_unique<TriggerSelection>("HLT_Mu50_v*");
    trigger_sel_B = uhh2::make_unique<TriggerSelection>("HLT_TkMu50_v*");
  }
  ////

  /*Only select event with exacly 1 muon or electron */
  if(channel_ == elec){
    muon_sel.reset(new NMuonSelection(0, 0, muid));
    elec_sel.reset(new NElectronSelection(1, 1, eleid));
  }
  else if (channel_ == muon){
    muon_sel.reset(new NMuonSelection(1, 1, muid));
    elec_sel.reset(new NElectronSelection(0, 0, eleid));
  }

  jet_sel.reset(new NJetSelection(2, -1, jetid_selection));
  met_sel  .reset(new METCut  (50 , uhh2::infinity));
  htlep_sel.reset(new HTlepCut(100, uhh2::infinity));
  twodcut_sel.reset(new TwoDCut1(0.4, 40));
  pv_sel.reset(new NPVSelection(1, -1, PrimaryVertexId(StandardPrimaryVertexId())));

  // if     (channel_ == elec) triangc_sel.reset(new TriangularCuts(M_PI/2., (M_PI/2.)/75.));
  // else if(channel_ == muon) triangc_sel.reset(new uhh2::AndSelection(ctx));
  ////


  // scale factors
  BTagEffHists.reset(new BTagMCEfficiencyHists(ctx,"EffiHists/BTag",CSVBTag::WP_TIGHT));
  BTag_variation = ctx.get("BTag_variation","central");
  muo_tight_noniso_SF.reset(new MCMuonScaleFactor(ctx,"/nfs/dust/cms/user/schwarzd/CMSSW_8_0_24_patch1/src/UHH2/common/data/MuonID_EfficienciesAndSF_average_RunBtoH.root","MC_NUM_TightID_DEN_genTracks_PAR_pt_eta",1, "tightID"));
  muo_trigger_SF.reset(new MCMuonScaleFactor(ctx,"/nfs/dust/cms/user/schwarzd/CMSSW_8_0_24_patch1/src/UHH2/common/data/MuonTrigger_EfficienciesAndSF_average_RunBtoH.root","IsoMu50_OR_IsoTkMu50_PtEtaBins",1, "muonTrigger"));
  BTagScaleFactors.reset(new MCBTagScaleFactor(ctx,CSVBTag::WP_TIGHT,"jets",BTag_variation));

  //// Obj Cleaning

  common.reset(new CommonModules());
  common->set_HTjetid(jetid_cleaner);
  common->switch_jetlepcleaner(true);
  common->switch_metcorrection();
  common->init(ctx);
  

  muoSR_cleaner.reset(new     MuonCleaner(muid));
  eleSR_cleaner.reset(new ElectronCleaner(eleid));

  jet_cleaner1.reset(new JetCleaner(ctx, 15., 3.0));
  jet_cleaner2.reset(new JetCleaner(ctx, 30., 2.4));

  //

  //// set up Hists classes:

  h_PreSel_event.reset(new MTopJetHists(ctx, "00_PreSel_Event"));
  h_PreSel_elec.reset(new ElectronHists(ctx, "00_PreSel_Elec"));
  h_PreSel_muon.reset(new MuonHists(ctx, "00_PreSel_Muon"));
  h_PreSel_jets.reset(new JetHists(ctx, "00_PreSel_Jets"));
  h_PreSel_lumi.reset(new LuminosityHists(ctx, "00_PreSel_lumi"));

  h_Cleaner_event.reset(new MTopJetHists(ctx, "01_Cleaner_Event"));
  h_Cleaner_elec.reset(new ElectronHists(ctx, "01_Cleaner_Elec"));
  h_Cleaner_muon.reset(new MuonHists(ctx, "01_Cleaner_Muon"));
  h_Cleaner_jets.reset(new JetHists(ctx, "01_Cleaner_Jets"));
  h_Cleaner_lumi.reset(new LuminosityHists(ctx, "01_Cleaner_lumi"));

  h_Trigger_event.reset(new MTopJetHists(ctx, "02_Trigger_Event"));
  h_Trigger_elec.reset(new ElectronHists(ctx, "02_Trigger_Elec"));
  h_Trigger_muon.reset(new MuonHists(ctx, "02_Trigger_Muon"));
  h_Trigger_jets.reset(new JetHists(ctx, "02_Trigger_Jets"));
  h_Trigger_lumi.reset(new LuminosityHists(ctx, "02_Trigger_lumi"));

  h_Lepton_event.reset(new MTopJetHists(ctx, "03_Lepton_Event"));
  h_Lepton_elec.reset(new ElectronHists(ctx, "03_Lepton_Elec"));
  h_Lepton_muon.reset(new MuonHists(ctx, "03_Lepton_Muon"));
  h_Lepton_jets.reset(new JetHists(ctx, "03_Lepton_Jets"));
  h_Lepton_lumi.reset(new LuminosityHists(ctx, "03_Lepton_lumi"));

  h_Jet_event.reset(new MTopJetHists(ctx, "04_Jet_Event"));
  h_Jet_elec.reset(new ElectronHists(ctx, "04_Jet_Elec"));
  h_Jet_muon.reset(new MuonHists(ctx, "04_Jet_Muon"));
  h_Jet_jets.reset(new JetHists(ctx, "04_Jet_Jets"));
  h_Jet_lumi.reset(new LuminosityHists(ctx, "04_Jet_lumi"));

  h_TwoD_event.reset(new MTopJetHists(ctx, "05_TwoD_Event"));
  h_TwoD_elec.reset(new ElectronHists(ctx, "05_TwoD_Elec"));
  h_TwoD_muon.reset(new MuonHists(ctx, "05_TwoD_Muon"));
  h_TwoD_jets.reset(new JetHists(ctx, "05_TwoD_Jets"));
  h_TwoD_lumi.reset(new LuminosityHists(ctx, "05_TwoD_lumi"));

  h_MET_event.reset(new MTopJetHists(ctx, "06_MET_Event"));
  h_MET_elec.reset(new ElectronHists(ctx, "06_MET_Elec"));
  h_MET_muon.reset(new MuonHists(ctx, "06_MET_Muon"));
  h_MET_jets.reset(new JetHists(ctx, "06_MET_Jets"));
  h_MET_lumi.reset(new LuminosityHists(ctx, "06_MET_lumi"));

  h_HTlep_event.reset(new MTopJetHists(ctx, "07_HTlep_Event"));
  h_HTlep_elec.reset(new ElectronHists(ctx, "07_HTlep_Elec"));
  h_HTlep_muon.reset(new MuonHists(ctx, "07_HTlep_Muon"));
  h_HTlep_jets.reset(new JetHists(ctx, "07_HTlep_Jets"));
  h_HTlep_lumi.reset(new LuminosityHists(ctx, "07_HTlep_lumi"));

  h_bTag_event.reset(new MTopJetHists(ctx, "08_bTag_Event"));
  h_bTag_elec.reset(new ElectronHists(ctx, "08_bTag_Elec"));
  h_bTag_muon.reset(new MuonHists(ctx, "08_bTag_Muon"));
  h_bTag_jets.reset(new JetHists(ctx, "08_bTag_jets"));
  h_bTag_lumi.reset(new LuminosityHists(ctx, "08_bTag_lumi"));

  h_Side_event.reset(new MTopJetHists(ctx, "Side_Event"));
  h_Side_elec.reset(new ElectronHists(ctx, "Side_Elec"));
  h_Side_muon.reset(new MuonHists(ctx, "Side_Muon"));
  h_Side_jets.reset(new JetHists(ctx, "Side_Jets")); 
  h_Side_lumi.reset(new LuminosityHists(ctx, "Side_lumi")); 

  h_ttbar_reweight_event.reset(new MTopJetHists(ctx, "ttbar_reweight_Event"));
  h_ttbar_reweight_elec.reset(new ElectronHists(ctx, "ttbar_reweight_Elec"));
  h_ttbar_reweight_muon.reset(new MuonHists(ctx, "ttbar_reweight_Muon"));
  h_ttbar_reweight_jets.reset(new JetHists(ctx, "ttbar_reweight_Jets"));
  h_ttbar_reweight_lumi.reset(new LuminosityHists(ctx, "ttbar_reweight_lumi"));

  //

}

bool MTopJetSelectionModule::process(uhh2::Event& event){
  // cout << "*******************************" << endl;
  // cout << "processing event nr. " << event.event<< endl;

  h_PreSel_event->fill(event);
  h_PreSel_elec->fill(event);
  h_PreSel_muon->fill(event);
  h_PreSel_jets->fill(event);
  h_PreSel_lumi->fill(event);
  ////

  /* *********** Lepton Cleaner and Selection *********** */
  muoSR_cleaner->process(event);
  sort_by_pt<Muon>(*event.muons);

  eleSR_cleaner->process(event);
  sort_by_pt<Electron>(*event.electrons);

  const bool pass_lep1 = ((event.muons->size() > 0) || (event.electrons->size() > 0));
  if(!pass_lep1) return false;
  ////


  /* *********** Cleaner ********** */
  if(!common->process(event)) return false;

  jet_cleaner1->process(event);
  sort_by_pt<Jet>(*event.jets);


  /* *********** at least 1 good primary vertex *********** */
  if(!pv_sel->passes(event)) return false;

  /* *********** scale factor muon *********** */
  muo_tight_noniso_SF->process(event);

  h_Cleaner_event->fill(event);
  h_Cleaner_elec->fill(event);
  h_Cleaner_muon->fill(event);
  h_Cleaner_jets->fill(event);
  h_Cleaner_lumi->fill(event);

  /* *********** Trigger *********** */
  // for DATA until run 274954 -> use only Trigger A
  // for MC and DATA from 274954 -> use "A || B"

  if(channel_ == muon){
    if( !isMC && event.run < 274954) {
      if(!trigger_sel_A->passes(event)) return false;
    }else{
      if( !(trigger_sel_A->passes(event) || trigger_sel_B->passes(event)) ) return false;
    }
    // Trigger scale factor
    muo_trigger_SF->process(event);
  }

  h_Trigger_event->fill(event);
  h_Trigger_elec->fill(event);
  h_Trigger_muon->fill(event);
  h_Trigger_jets->fill(event);
  h_Trigger_lumi->fill(event);

  /* *********** lEPTON Selection *********** */
  const bool pass_lepsel = (muon_sel->passes(event) && elec_sel->passes(event));
  if(!pass_lepsel) return false;
  h_Lepton_event->fill(event);
  h_Lepton_elec->fill(event);
  h_Lepton_muon->fill(event);
  h_Lepton_jets->fill(event);
  h_Lepton_lumi->fill(event);
  ////

  /* *********** Jet Selection *********** */
  const bool pass_jetsel = (jet_sel->passes(event));
  if(!pass_jetsel) return false;

  // h_Jet_event->fill(event);
  h_Jet_elec->fill(event);
  h_Jet_muon->fill(event);
  h_Jet_jets->fill(event);
  h_Jet_lumi->fill(event);

  /* *********** BTag Effi Hist *********** */
  if(!event.isRealData) BTagEffHists->fill(event);

  /* *********** lepton-2Dcut variables ***********  */
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

  // 2D Cut (first soft cleaner [jet_cleaner1], then 2D Cut, then normal cleaner [jet_cleaner2]
  if(!pass_twodcut) return false;
  jet_cleaner2->process(event);
  sort_by_pt<Jet>(*event.jets);

  h_TwoD_event->fill(event);
  h_TwoD_elec->fill(event);
  h_TwoD_muon->fill(event);
  h_TwoD_jets->fill(event);
  h_TwoD_lumi->fill(event);
  ////



  /* *********** MET selection *********** */
  const bool pass_met = met_sel->passes(event);
  if(!pass_met) return false;

  h_MET_event->fill(event);
  h_MET_elec->fill(event);
  h_MET_muon->fill(event);
  h_MET_jets->fill(event);
  h_MET_lumi->fill(event);

  /* Triangular Cut in Electron channel */
  // const bool pass_trianc = triangc_sel->passes(event);
  // if(!pass_trianc) return false;

  /* *********** HT lep *********** */
  const bool pass_htlep = htlep_sel->passes(event);
  if(!pass_htlep) return false;

  h_HTlep_event->fill(event);
  h_HTlep_elec->fill(event);
  h_HTlep_muon->fill(event);
  h_HTlep_jets->fill(event);
  h_HTlep_lumi->fill(event);

  /* *********** b-tag counter *********** */
  int jetbtagN(0);
  for(const auto& j : *event.jets) if(CSVBTag(CSVBTag::WP_TIGHT)(j, event)) ++jetbtagN;
  if(jetbtagN == 0){
    h_Side_event->fill(event);
    h_Side_elec->fill(event);
    h_Side_muon->fill(event);
    h_Side_jets->fill(event);
    h_Side_lumi->fill(event);
  }

  if(jetbtagN < 1) return false;
  BTagScaleFactors->process(event);

  h_bTag_event->fill(event);
  h_bTag_elec->fill(event);
  h_bTag_muon->fill(event);
  h_bTag_jets->fill(event);
  h_bTag_lumi->fill(event);

  /* *********** now produce final XCone Jets and write output (especially weight) *********** */
  jetprod_reco->process(event);
  if(!event.isRealData){
    jetprod_gen23->process(event);
    jetprod_gen33->process(event);
  } 
  output->process(event);

  /* *********** just a check ****************************************** */
  ttbar_reweight->process(event);
  h_ttbar_reweight_event->fill(event);
  h_ttbar_reweight_elec->fill(event);
  h_ttbar_reweight_muon->fill(event);
  h_ttbar_reweight_jets->fill(event);
  h_ttbar_reweight_lumi->fill(event);

return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(MTopJetSelectionModule)
