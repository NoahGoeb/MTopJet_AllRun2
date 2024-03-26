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
#include <UHH2/common/include/MCWeight.h>

#include <UHH2/MTopJet/include/CombineXCone.h>
#include <UHH2/MTopJet/include/GenHists_xcone.h>
#include <UHH2/MTopJet/include/GenHists_GenOnly.h>
#include <UHH2/MTopJet/include/GenHists_TwoJetCollections.h>
#include <UHH2/MTopJet/include/GenHists_ThreeJetCollections.h>
#include <UHH2/MTopJet/include/GenHists_GenNoLep.h>
#include <UHH2/MTopJet/include/ControlHists.h>
#include <UHH2/MTopJet/include/ModuleBASE.h>
#include <UHH2/MTopJet/include/StoreBJet.h>

#include <UHH2/MTopJet/include/AnalysisOutput.h>
#include <UHH2/MTopJet/include/GenSelections.h>
#include <UHH2/MTopJet/include/MTopJetUtils.h>

#include "UHH2/JetMETObjects/interface/FactorizedJetCorrector.h"


#include <vector>

// ##############################################################################
// ### Definition of class
// ### public: Seen by all functions including class
// ### private: Variables, functions, etc. only seen by class. 
// ###          Outer functions cannot access them! 

class MTopJetGenPostSelectionModule : public ModuleBASE {

public:
  explicit MTopJetGenPostSelectionModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  void declare_output(uhh2::Context& ctx);
  void init_handels(uhh2::Context& ctx);
  void init_hists(uhh2::Context& ctx);
  void init_MC_hists(uhh2::Context& ctx);

protected:
  enum lepton { muon, elec };
  lepton channel_;

  // Selection Modules defined in scope of the analysis code
  unique_ptr<uhh2::Selection> pt_gensel;
  unique_ptr<uhh2::Selection> pt2_gensel;
  unique_ptr<uhh2::Selection> pt350_gensel;
  unique_ptr<uhh2::Selection> test_gensel;

  unique_ptr<uhh2::Selection> subjet_quality_gen;
  unique_ptr<uhh2::Selection> subjet_quality_eta_gen;
  unique_ptr<uhh2::Selection> mass_gensel;
  unique_ptr<uhh2::Selection> matched_sub_gen;
  unique_ptr<uhh2::Selection> matched_fat_gen;
  unique_ptr<uhh2::Selection> lepton_sel_gen;
  unique_ptr<uhh2::Selection> lepton_Nsel_gen;

  unique_ptr<uhh2::Selection> ptrange400500_gensel;
  unique_ptr<uhh2::Selection> ptrange500600_gensel;
  unique_ptr<uhh2::Selection> ptrange600700_gensel;
  unique_ptr<uhh2::Selection> ptrange700800_gensel;
  unique_ptr<uhh2::Selection> ptrange800900_gensel;
  unique_ptr<uhh2::Selection> ptrange9001000_gensel;

  unique_ptr<uhh2::Selection> ptrange5002000_gensel;
  unique_ptr<uhh2::Selection> ptrange6002000_gensel;
  unique_ptr<uhh2::Selection> ptrange7002000_gensel;
  unique_ptr<uhh2::Selection> ptrange8002000_gensel;
  unique_ptr<uhh2::Selection> ptrange9002000_gensel;

  unique_ptr<uhh2::Selection> pt_gensel_3jets;
  unique_ptr<uhh2::Selection> pt2_gensel_3jets;
  unique_ptr<uhh2::Selection> subjet_quality_gen_3jets;
  unique_ptr<uhh2::Selection> mass_gensel_3jets;
  unique_ptr<uhh2::Selection> lepton_sel_gen_3jets;

  unique_ptr<uhh2::Selection> pt08_gensel_3jets;
  unique_ptr<uhh2::Selection> pt10_gensel_3jets;
  unique_ptr<uhh2::Selection> pt12_gensel_3jets;
  unique_ptr<uhh2::Selection> pt14_gensel_3jets;
  unique_ptr<uhh2::Selection> pt16_gensel_3jets;

  unique_ptr<uhh2::Selection> pt12_gensel_3jets_OnlySmalldR;

  unique_ptr<uhh2::Selection> ptrange4002000_variedDR_gensel_3jets;
  unique_ptr<uhh2::Selection> ptrange700900_variedDR_gensel_3jets;

  unique_ptr<uhh2::Selection> ptrange4002000_variedDR_gensel_3jets_450;
  unique_ptr<uhh2::Selection> ptrange4002000_variedDR_gensel_3jets_600;
  unique_ptr<uhh2::Selection> ptrange4002000_variedDR_gensel_3jets_12;
  unique_ptr<uhh2::Selection> ptrange4002000_variedDR_gensel_3jets_08;
  unique_ptr<uhh2::Selection> ptrange4002000_variedDR_gensel_3jets_04;

  unique_ptr<uhh2::Selection> ptrange5002000_variedDR_gensel_3jets_12;
  unique_ptr<uhh2::Selection> ptrange6002000_variedDR_gensel_3jets_12;
  unique_ptr<uhh2::Selection> ptrange7002000_variedDR_gensel_3jets_12;
  unique_ptr<uhh2::Selection> ptrange8002000_variedDR_gensel_3jets_12;
  unique_ptr<uhh2::Selection> ptrange9002000_variedDR_gensel_3jets_12;

  unique_ptr<uhh2::Selection> ptrange700900_gensel_3jets;
  
  unique_ptr<uhh2::Selection> closeTopGluon;

  // Access XCone jets
  Event::Handle<std::vector<GenTopJet>> h_genjets33_had, h_genfatjets, h_genall3fatjets, h_gen3nolepjets, h_gen3noNearestLepjets;

  // Access events variables stored in input rootfile
  Event::Handle<bool> h_passed_gensel;
  Event::Handle<TTbarGen> h_ttbargen;

  std::unique_ptr<AnalysisModule> scale_variation;
  uhh2::Event::Handle<double> h_weight;

  // Handles to store variables in output
  Event::Handle<bool> h_measure_gen;

  Event::Handle<double> h_mass_gen33;
  Event::Handle<double> h_pt_gen33;
  Event::Handle<vector<double>> h_bquark_pt;

  // Define Histgrams
  unique_ptr<Hists> h_XCone_GEN_noCut, h_XCone_GEN_ptCut, h_XCone_GEN_pt2Cut, h_XCone_GEN_pt350Cut, h_XCone_GEN_test;
  unique_ptr<Hists> h_subjet_quality_gen;
  unique_ptr<Hists> h_subjet_quality_eta_gen;

  unique_ptr<Hists> h_XCone_GEN_Sel_measurement, h_XCone_GEN_Sel_noMass, h_XCone_GEN_Sel_pt350, h_XCone_GEN_Sel_ptsub;
  unique_ptr<Hists> h_eff_masscut_gen, h_eff_subjet_gen, h_eff_lep_pt_gen;

  unique_ptr<Hists> h_decay_same_jet_gen;
  unique_ptr<Hists> h_decay_same_jet_gen_count;

  unique_ptr<Hists> h_decay_same_jet_pt400500_gen;
  unique_ptr<Hists> h_decay_same_jet_pt500600_gen;
  unique_ptr<Hists> h_decay_same_jet_pt600700_gen;
  unique_ptr<Hists> h_decay_same_jet_pt700800_gen;
  unique_ptr<Hists> h_decay_same_jet_pt800900_gen;
  unique_ptr<Hists> h_decay_same_jet_pt9001000_gen;

  unique_ptr<Hists> h_decay_same_jet_pt5002000_gen, h_decay_same_jet_pt6002000_gen, h_decay_same_jet_pt7002000_gen, h_decay_same_jet_pt8002000_gen, h_decay_same_jet_pt9002000_gen;

  unique_ptr<Hists> h_alljets_gen, h_nolepjets_gen, h_noNearestLep_gen, h_allnolepjets_comparison, h_allNoNearestLepjets_comparison;
  unique_ptr<Hists> h_allnolepjets_sizeDiff0, h_allnolepjets_sizeDiff2, h_allnolepjets_sizeDiff3;
  unique_ptr<Hists> h_allNoNearestLepjets_sizeDiff0, h_allNoNearestLepjets_sizeDiff2, h_allNoNearestLepjets_sizeDiff3;

  unique_ptr<Hists> h_top_gluon_lep_gen_nocuts, h_top_gluon_lep_gen_measurement, h_top_gluon_lep_gen_pt700900;
  unique_ptr<Hists> h_top_gluon_lep_gen_newPtCut08, h_top_gluon_lep_gen_newPtCut10, h_top_gluon_lep_gen_newPtCut12, h_top_gluon_lep_gen_newPtCut14, h_top_gluon_lep_gen_newPtCut16;
  unique_ptr<Hists> h_top_gluon_lep_gen_newPtCut12_OnlySmalldR, h_top_gluon_lep_gen_newPtCutRange4002000_variedDR, h_top_gluon_lep_gen_newPtCutRange700900_variedDR;
  unique_ptr<Hists> h_top_gluon_lep_gen_variedDR_350, h_top_gluon_lep_gen_variedDR_450, h_top_gluon_lep_gen_variedDR_600, h_top_gluon_lep_gen_variedDR_12, h_top_gluon_lep_gen_variedDR_08, h_top_gluon_lep_gen_variedDR_04;
  
  unique_ptr<Hists> h_genNoLep, h_genNoLep_LeadingJetPtCut, h_genNoLep_closeGluonTop;
  unique_ptr<Hists> h_genNoLep_pT500, h_genNoLep_pT600, h_genNoLep_pT700, h_genNoLep_pT800, h_genNoLep_pT900;

  unique_ptr<Hists> h_highestPtSorted;

  // Object construction
  std::unique_ptr<uhh2::AnalysisModule> jetprod_gen, jetprod_gen1, jetprod_gen2, jetprod_gen3, jetprod_gen4, jetprod_gen5, jetprod_gen6, jetprod_gen7, jetprod_gen8, jetprod_gen9,jetprod_gen10, jetprod_gen11, jetprod_gen12, jetprod_gen13, jetprod_gen14;
  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;

  // global variables for class
  
  
  bool year_18;
  bool debug;

};

// ##############################################################################
// ### Constructor; for each xml
// ### Initilize all objects

// Get handles; Variables stored for each event in rootfile e.g. muon pt
void MTopJetGenPostSelectionModule::init_handels(uhh2::Context& ctx){
  // boolean if previous selection on gen level to select ttbar events passed 
  // See MTopJetSelection or MTopJetPreSelection
  h_passed_gensel = ctx.get_handle<bool>("passed_gensel_2");
  h_ttbargen = ctx.get_handle<TTbarGen>("ttbargen");
  h_weight = ctx.get_handle<double>("weight");
}

// Store handles in output rootfile
void MTopJetGenPostSelectionModule::declare_output(uhh2::Context& ctx){
  h_measure_gen = ctx.declare_event_output<bool>("passed_measurement_gen");
  //h_mass_gen33 = ctx.declare_event_output<double>("Mass_Gen33");
  //h_pt_gen33 = ctx.declare_event_output<double>("Pt_Gen33");
  //h_bquark_pt = ctx.declare_event_output<vector<double>>("bquark_pt");

}


// Histograms only stored for MC e.g. gen info is not accesible in data.
void MTopJetGenPostSelectionModule::init_MC_hists(uhh2::Context& ctx){
  // GenHists_xcone definiton also in MTopJet/src folder
  // Give name e.g. XCone_GEN_noCut as it should be stored in output file
  // Hist classes will be stored as `directories` and contains the defined histograms
  h_XCone_GEN_noCut.reset(new GenHists_xcone(ctx, "XCone_GEN_noCut"));
  h_XCone_GEN_ptCut.reset(new GenHists_xcone(ctx, "XCone_GEN_ptCut"));
  h_XCone_GEN_pt2Cut.reset(new GenHists_xcone(ctx, "XCone_GEN_pt2Cut"));
  h_XCone_GEN_pt350Cut.reset(new GenHists_xcone(ctx, "XCone_GEN_pt350Cut"));
  h_XCone_GEN_test.reset(new GenHists_xcone(ctx, "XCone_GEN_test"));
  h_subjet_quality_gen.reset(new CountingEventHists(ctx,"subjet_quality_gen"));
  h_subjet_quality_eta_gen.reset(new CountingEventHists(ctx,"subjet_quality_eta_gen"));
  
  h_eff_masscut_gen.reset(new CountingEventHists(ctx, "efficiency_masscut_gen"));
  h_eff_subjet_gen.reset(new CountingEventHists(ctx, "efficiency_subjet_gen"));
  h_eff_lep_pt_gen.reset(new CountingEventHists(ctx, "efficiency_lep_pt_gen"));

  h_XCone_GEN_Sel_measurement.reset(new GenHists_xcone(ctx, "XCone_GEN_Sel_measurement"));
  h_XCone_GEN_Sel_noMass.reset(new GenHists_xcone(ctx, "XCone_GEN_Sel_noMass"));
  h_XCone_GEN_Sel_pt350.reset(new GenHists_xcone(ctx, "XCone_GEN_Sel_pt350"));
  h_XCone_GEN_Sel_ptsub.reset(new GenHists_xcone(ctx, "XCone_GEN_Sel_ptsub"));

  if(debug) cout << "-decay_same_jet-" << endl;
  h_decay_same_jet_gen.reset(new GenHists_GenOnly(ctx, "decay_same_jet_gen", "GEN_XCone33_had_Combined"));

  h_decay_same_jet_gen_count.reset(new CountingEventHists(ctx, "decay_same_jet_gen_count"));

  h_decay_same_jet_pt400500_gen.reset(new GenHists_GenOnly(ctx, "decay_same_jet_pt400500_gen", "GEN_XCone33_had_Combined"));
  h_decay_same_jet_pt500600_gen.reset(new GenHists_GenOnly(ctx, "decay_same_jet_pt500600_gen", "GEN_XCone33_had_Combined"));
  h_decay_same_jet_pt600700_gen.reset(new GenHists_GenOnly(ctx, "decay_same_jet_pt600700_gen", "GEN_XCone33_had_Combined"));
  h_decay_same_jet_pt700800_gen.reset(new GenHists_GenOnly(ctx, "decay_same_jet_pt700800_gen", "GEN_XCone33_had_Combined"));
  h_decay_same_jet_pt800900_gen.reset(new GenHists_GenOnly(ctx, "decay_same_jet_pt800900_gen", "GEN_XCone33_had_Combined"));
  h_decay_same_jet_pt9001000_gen.reset(new GenHists_GenOnly(ctx, "decay_same_jet_pt9001000_gen", "GEN_XCone33_had_Combined"));

  h_decay_same_jet_pt5002000_gen.reset(new GenHists_GenOnly(ctx, "decay_same_jet_pt5002000_gen", "GEN_XCone33_had_Combined"));
  h_decay_same_jet_pt6002000_gen.reset(new GenHists_GenOnly(ctx, "decay_same_jet_pt6002000_gen", "GEN_XCone33_had_Combined"));
  h_decay_same_jet_pt7002000_gen.reset(new GenHists_GenOnly(ctx, "decay_same_jet_pt7002000_gen", "GEN_XCone33_had_Combined"));
  h_decay_same_jet_pt8002000_gen.reset(new GenHists_GenOnly(ctx, "decay_same_jet_pt8002000_gen", "GEN_XCone33_had_Combined"));
  h_decay_same_jet_pt9002000_gen.reset(new GenHists_GenOnly(ctx, "decay_same_jet_pt9002000_gen", "GEN_XCone33_had_Combined"));

  h_alljets_gen.reset(new GenHists_GenOnly(ctx, "alljets_gen", "GEN_XCone3_all_Combined"));
  h_nolepjets_gen.reset(new GenHists_GenOnly(ctx, "nolepjets_gen", "GEN_XCone3_nolep_Combined_dR12"));
  if(debug) cout << "-after nolepjet_gen reached-" << endl;
  h_noNearestLep_gen.reset(new GenHists_GenOnly(ctx, "noNearestLepjets_gen", "GEN_XCone3_noNearestLep_Combined"));

  h_allnolepjets_comparison.reset(new GenHists_TwoJetCollections(ctx, "allnolepjets_comparison", "GEN_XCone3_all_Combined", "GEN_XCone3_nolep_Combined_dR12"));
  h_allNoNearestLepjets_comparison.reset(new GenHists_TwoJetCollections(ctx, "allNoNearestLepjets_comparison", "GEN_XCone3_all_Combined", "GEN_XCone3_noNearestLep_Combined"));

  h_allnolepjets_sizeDiff0.reset(new GenHists_TwoJetCollections(ctx, "allnolepjets_sizeDiff0", "GEN_XCone3_all_Combined", "GEN_XCone3_nolep_Combined_dR12"));
  h_allnolepjets_sizeDiff2.reset(new GenHists_TwoJetCollections(ctx, "allnolepjets_sizeDiff2", "GEN_XCone3_all_Combined", "GEN_XCone3_nolep_Combined_dR12"));
  h_allnolepjets_sizeDiff3.reset(new GenHists_TwoJetCollections(ctx, "allnolepjets_sizeDiff3", "GEN_XCone3_all_Combined", "GEN_XCone3_nolep_Combined_dR12"));

  h_allNoNearestLepjets_sizeDiff0.reset(new GenHists_TwoJetCollections(ctx, "allNoNearestLepjets_sizeDiff0", "GEN_XCone3_all_Combined", "GEN_XCone3_noNearestLep_Combined"));
  h_allNoNearestLepjets_sizeDiff2.reset(new GenHists_TwoJetCollections(ctx, "allNoNearestLepjets_sizeDiff2", "GEN_XCone3_all_Combined", "GEN_XCone3_noNearestLep_Combined"));
  h_allNoNearestLepjets_sizeDiff3.reset(new GenHists_TwoJetCollections(ctx, "allNoNearestLepjets_sizeDiff3", "GEN_XCone3_all_Combined", "GEN_XCone3_noNearestLep_Combined"));

  h_top_gluon_lep_gen_nocuts.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepNoCuts", "GEN_XCone3_top_Combined_dR12", "GEN_XCone3_gluon_Combined_dR12", "GEN_XCone3_lep_Combined_dR12"));
  h_top_gluon_lep_gen_measurement.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepMeasurement", "GEN_XCone3_top_Combined_dR12", "GEN_XCone3_gluon_Combined_dR12", "GEN_XCone3_lep_Combined_dR12"));

  h_top_gluon_lep_gen_newPtCut08.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepNewPtCut08", "GEN_XCone3_top_Combined_dR12", "GEN_XCone3_gluon_Combined_dR12", "GEN_XCone3_lep_Combined_dR12"));
  h_top_gluon_lep_gen_newPtCut10.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepNewPtCut10", "GEN_XCone3_top_Combined_dR12", "GEN_XCone3_gluon_Combined_dR12", "GEN_XCone3_lep_Combined_dR12"));
  h_top_gluon_lep_gen_newPtCut12.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepNewPtCut12", "GEN_XCone3_top_Combined_dR12", "GEN_XCone3_gluon_Combined_dR12", "GEN_XCone3_lep_Combined_dR12"));
  h_top_gluon_lep_gen_newPtCut14.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepNewPtCut14", "GEN_XCone3_top_Combined_dR12", "GEN_XCone3_gluon_Combined_dR12", "GEN_XCone3_lep_Combined_dR12"));
  h_top_gluon_lep_gen_newPtCut16.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepNewPtCut16", "GEN_XCone3_top_Combined_dR12", "GEN_XCone3_gluon_Combined_dR12", "GEN_XCone3_lep_Combined_dR12"));

  h_top_gluon_lep_gen_newPtCut12_OnlySmalldR.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepNewPtCut12_OnlySmalldR", "GEN_XCone3_top_Combined_dR12", "GEN_XCone3_gluon_Combined_dR12", "GEN_XCone3_lep_Combined_dR12"));

  h_top_gluon_lep_gen_newPtCutRange4002000_variedDR.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepNewPtCutRange4002000_variedDR", "GEN_XCone3_top_Combined_dR12", "GEN_XCone3_gluon_Combined_dR12", "GEN_XCone3_lep_Combined_dR12"));
  h_top_gluon_lep_gen_newPtCutRange700900_variedDR.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepNewPtCutRange700900_variedDR", "GEN_XCone3_top_Combined_dR12", "GEN_XCone3_gluon_Combined_dR12", "GEN_XCone3_lep_Combined_dR12"));

  h_top_gluon_lep_gen_pt700900.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepPt700900", "GEN_XCone3_top_Combined_dR12", "GEN_XCone3_gluon_Combined_dR12", "GEN_XCone3_lep_Combined_dR12"));

  h_top_gluon_lep_gen_variedDR_350.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepVariedDR350", "GEN_XCone3_top_Combined_dR350varied", "GEN_XCone3_gluon_Combined_dR350varied", "GEN_XCone3_lep_Combined_dR350varied"));
  h_top_gluon_lep_gen_variedDR_450.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepVariedDR450", "GEN_XCone3_top_Combined_dR450varied", "GEN_XCone3_gluon_Combined_dR450varied", "GEN_XCone3_lep_Combined_dR450varied"));
  h_top_gluon_lep_gen_variedDR_600.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepVariedDR600", "GEN_XCone3_top_Combined_dR600varied", "GEN_XCone3_gluon_Combined_dR600varied", "GEN_XCone3_lep_Combined_dR600varied"));
  h_top_gluon_lep_gen_variedDR_12.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepDR12", "GEN_XCone3_top_Combined_dR12", "GEN_XCone3_gluon_Combined_dR12", "GEN_XCone3_lep_Combined_dR12"));
  h_top_gluon_lep_gen_variedDR_08.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepDR08", "GEN_XCone3_top_Combined_dR08", "GEN_XCone3_gluon_Combined_dR08", "GEN_XCone3_lep_Combined_dR08"));
  h_top_gluon_lep_gen_variedDR_04.reset(new GenHists_ThreeJetCollections(ctx, "topGluonLepDR04", "GEN_XCone3_top_Combined_dR04", "GEN_XCone3_gluon_Combined_dR04", "GEN_XCone3_lep_Combined_dR04"));

  h_genNoLep.reset(new GenHists_GenNoLep(ctx, "genNoLep", "GEN_XCone3_nolep_Combined_dR12", 1.2));
  h_genNoLep_LeadingJetPtCut.reset(new GenHists_GenNoLep(ctx, "genNoLep_LeadingJetPtCut", "GEN_XCone3_nolep_Combined_dR12", 1.2));
  h_genNoLep_pT500.reset(new GenHists_GenNoLep(ctx, "genNoLep_pT500", "GEN_XCone3_nolep_Combined_dR12", 1.2));
  h_genNoLep_pT600.reset(new GenHists_GenNoLep(ctx, "genNoLep_pT600", "GEN_XCone3_nolep_Combined_dR12", 1.2));
  h_genNoLep_pT700.reset(new GenHists_GenNoLep(ctx, "genNoLep_pT700", "GEN_XCone3_nolep_Combined_dR12", 1.2));
  h_genNoLep_pT800.reset(new GenHists_GenNoLep(ctx, "genNoLep_pT800", "GEN_XCone3_nolep_Combined_dR12", 1.2));
  h_genNoLep_pT900.reset(new GenHists_GenNoLep(ctx, "genNoLep_pT900", "GEN_XCone3_nolep_Combined_dR12", 1.2));
  h_genNoLep_closeGluonTop.reset(new GenHists_GenNoLep(ctx, "genNoLep_closeGluonTop", "GEN_XCone3_nolep_Combined_dR12", 1.2));

  h_highestPtSorted.reset(new CountingEventHists(ctx, "highestPtSorted"));

  if(debug) cout << "-end of init reached-" << endl;
}

// Histograms for MC and data, so only rec level
void MTopJetGenPostSelectionModule::init_hists(uhh2::Context& ctx){

}

// Main constructor. add previous functions in here.
// Not necessary, but when constructor gets to large (too many lines),
// the compile complains and crashes.
MTopJetGenPostSelectionModule::MTopJetGenPostSelectionModule(uhh2::Context& ctx){

  // /////////////
  // Set variables

  // Only set true if you want to test the code and/or the code crashes. 
  // Only true if run locally and not via HTCondor.
  // Set in xml file, so one does not has to compile everytime
  debug = string2bool(ctx.get("Debug","false")); // look for Debug, expect false if not found

  if(debug) cout << "--- Start Module - CTX ---" << endl;

  // Example, not important now, but when you analyse multiple years.
  year_18 = false;

  // //////////////////
  // channel

  const std::string& channel = ctx.get("channel", ""); //define Channel
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;

  // //////////////////
  // construct gen jets 
  if(debug) cout << "\t--- Construct XCone jets" << endl;

  // gat ttbar gen info; Important for clustering, ignore for now
  const std::string ttbar_gen_label("ttbargen");
  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));
  h_ttbargen=ctx.get_handle<TTbarGen>("ttbargen");

  scale_variation.reset(new MCScaleVariation(ctx));

  jetprod_gen.reset(new CombineXCone33_gen(ctx, true)); // keep true for now, since you look only at ttbar
  jetprod_gen1.reset(new CombineXCone3all_gen(ctx, 3, "GEN_XCone3_all_Combined", "genXCone3TopJets"));
  jetprod_gen2.reset(new CombineXCone3nolep_gen(ctx, true, false, 1.2, "GEN_XCone3_nolep_Combined_dR12", "genXCone3TopJets"));
  jetprod_gen3.reset(new CombineXCone3noNearestLep_gen(ctx, true, "GEN_XCone3_noNearestLep_Combined", "genXCone3TopJets"));
  jetprod_gen4.reset(new CombineXCone3top_gluon_gen(ctx, true, false, 1.2, "GEN_XCone3_top_Combined_dR12", "GEN_XCone3_gluon_Combined_dR12", "GEN_XCone3_lep_Combined_dR12", "genXCone3TopJets"));
  jetprod_gen5.reset(new CombineXCone3top_gluon_gen(ctx, true, false, 0.8, "GEN_XCone3_top_Combined_dR08", "GEN_XCone3_gluon_Combined_dR08", "GEN_XCone3_lep_Combined_dR08", "genXCone3TopJets"));
  jetprod_gen6.reset(new CombineXCone3top_gluon_gen(ctx, true, false, 0.4, "GEN_XCone3_top_Combined_dR04", "GEN_XCone3_gluon_Combined_dR04", "GEN_XCone3_lep_Combined_dR04", "genXCone3TopJets"));
  jetprod_gen7.reset(new CombineXCone3top_gluon_gen(ctx, true, true, 350, "GEN_XCone3_top_Combined_dR350varied", "GEN_XCone3_gluon_Combined_dR350varied", "GEN_XCone3_lep_Combined_dR350varied", "genXCone3TopJets"));
  jetprod_gen8.reset(new CombineXCone3top_gluon_gen(ctx, true, true, 450, "GEN_XCone3_top_Combined_dR450varied", "GEN_XCone3_gluon_Combined_dR450varied", "GEN_XCone3_lep_Combined_dR450varied", "genXCone3TopJets"));
  jetprod_gen9.reset(new CombineXCone3top_gluon_gen(ctx, true, true, 600, "GEN_XCone3_top_Combined_dR600varied", "GEN_XCone3_gluon_Combined_dR600varied", "GEN_XCone3_lep_Combined_dR600varied", "genXCone3TopJets"));
  jetprod_gen10.reset(new CombineXCone3nolep_gen(ctx, true, false, 0.8, "GEN_XCone3_nolep_Combined_dR08", "genXCone3TopJets"));
  jetprod_gen11.reset(new CombineXCone3nolep_gen(ctx, true, false, 0.4, "GEN_XCone3_nolep_Combined_dR04", "genXCone3TopJets"));
  jetprod_gen12.reset(new CombineXCone3nolep_gen(ctx, true, true, 350, "GEN_XCone3_nolep_Combined_dR350varied", "genXCone3TopJets"));
  jetprod_gen13.reset(new CombineXCone3nolep_gen(ctx, true, true, 450, "GEN_XCone3_nolep_Combined_dR450varied", "genXCone3TopJets"));
  jetprod_gen14.reset(new CombineXCone3nolep_gen(ctx, true, true, 600, "GEN_XCone3_nolep_Combined_dR600varied", "genXCone3TopJets"));

  // //////////////
  // Access genjets
  if(debug) cout << "\t--- Access genejts" << endl;

  // fatjets: XCone jets with R=1.2 (both hadronic and leptonic)
  // `combined jets`: Combined subjets (R=0.4) within fatjet; Used for measurement
  // 33 means both fatjets have 3 subjets. 
  h_genfatjets = ctx.get_handle<std::vector<GenTopJet>>("genXCone3TopJets");

  // GEN_XCone33_had_Combined produces in CombineXCone33_gen, so define afterwards
  // Only hadronic nowSubjet
  h_genjets33_had = ctx.get_handle<std::vector<GenTopJet>>("GEN_XCone33_had_Combined");
  h_genall3fatjets = ctx.get_handle<std::vector<GenTopJet>>("GEN_XCone3_all_Combined");
  h_gen3nolepjets = ctx.get_handle<std::vector<GenTopJet>>("GEN_XCone3_nolep_Combined_dR12");
  h_gen3noNearestLepjets = ctx.get_handle<std::vector<GenTopJet>>("GEN_XCone3_noNearestLep_Combined");

  // /////////////////
  // Define Selections
  if(debug) cout << "\t--- Define selections" << endl;

  // Defined in GenSelections.cxx
  if(channel_ == muon) {
    lepton_sel_gen.reset(new GenMuonSel(ctx, 60.0));
    lepton_Nsel_gen.reset(new GenMuonCount(ctx));
    lepton_sel_gen_3jets.reset(new GenMuonSel(ctx, 60.0));
  } else {
    lepton_sel_gen.reset(new GenElecSel(ctx, 60.0));
    lepton_Nsel_gen.reset(new GenElecCount(ctx));
    lepton_sel_gen_3jets.reset(new GenElecSel(ctx, 60.0));
  }

  if(debug) cout << "\t--- old selections" << endl;

  pt_gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone33_had_Combined", 400));
  pt2_gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone33_lep_Combined", 10));
  pt350_gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone33_had_Combined", 350));
  test_gensel.reset(new LeadingJetPT_gen(ctx, "GEN_XCone33_had_Combined", 300));
  subjet_quality_gen.reset(new SubjetQuality_gen(ctx, "GEN_XCone33_had_Combined", 30, 2.5));
  subjet_quality_eta_gen.reset(new SubjetQuality_gen(ctx, "GEN_XCone33_had_Combined", 0, 2.5));
  mass_gensel.reset(new MassCut_gen(ctx, "GEN_XCone33_had_Combined", "GEN_XCone33_lep_Combined"));
  matched_sub_gen.reset(new Matching_XCone33GEN(ctx, "GEN_XCone33_had_Combined", true));
  matched_fat_gen.reset(new Matching_XCone33GEN(ctx, "GEN_XCone33_had_Combined", false));

  ptrange400500_gensel.reset(new LeadingJetPTRange_gen(ctx, "GEN_XCone33_had_Combined", 400, 500));
  ptrange500600_gensel.reset(new LeadingJetPTRange_gen(ctx, "GEN_XCone33_had_Combined", 500, 600));
  ptrange600700_gensel.reset(new LeadingJetPTRange_gen(ctx, "GEN_XCone33_had_Combined", 600, 700));
  ptrange700800_gensel.reset(new LeadingJetPTRange_gen(ctx, "GEN_XCone33_had_Combined", 700, 800));
  ptrange800900_gensel.reset(new LeadingJetPTRange_gen(ctx, "GEN_XCone33_had_Combined", 800, 900));
  ptrange9001000_gensel.reset(new LeadingJetPTRange_gen(ctx, "GEN_XCone33_had_Combined", 900, 1000));

  ptrange5002000_gensel.reset(new LeadingJetPTRange_gen(ctx, "GEN_XCone33_had_Combined", 500, 2000));
  ptrange6002000_gensel.reset(new LeadingJetPTRange_gen(ctx, "GEN_XCone33_had_Combined", 600, 2000));
  ptrange7002000_gensel.reset(new LeadingJetPTRange_gen(ctx, "GEN_XCone33_had_Combined", 700, 2000));
  ptrange8002000_gensel.reset(new LeadingJetPTRange_gen(ctx, "GEN_XCone33_had_Combined", 800, 2000));
  ptrange9002000_gensel.reset(new LeadingJetPTRange_gen(ctx, "GEN_XCone33_had_Combined", 900, 2000));

  if(debug) cout << "\t--- top pt cut selections" << endl;
  pt_gensel_3jets.reset(new LeadingJetPT_gen(ctx, "GEN_XCone3_top_Combined_dR12", 400));
  if(debug) cout << "\t--- lep pt cut selections" << endl;
  pt2_gensel_3jets.reset(new LeadingJetPT_gen(ctx, "GEN_XCone3_lep_Combined_dR12", 10));
  if(debug) cout << "\t--- subjet quality selections" << endl;
  subjet_quality_gen_3jets.reset(new SubjetQuality_gen(ctx, "GEN_XCone3_top_Combined_dR12", 30, 2.5));
  mass_gensel_3jets.reset(new MassCut3Jets_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", "GEN_XCone3_lep_Combined_dR12", 1.2));
  if(debug) cout << "\t--- jets pt cut selections" << endl;
  pt08_gensel_3jets.reset(new JetsPT_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", 400, 0.8));
  pt10_gensel_3jets.reset(new JetsPT_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", 400, 1.0));
  pt12_gensel_3jets.reset(new JetsPT_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", 400, 1.2));
  pt14_gensel_3jets.reset(new JetsPT_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", 400, 1.4));
  pt16_gensel_3jets.reset(new JetsPT_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", 400, 1.6));

  pt12_gensel_3jets_OnlySmalldR.reset(new JetsPTOnlySmalldR_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", 400, 1.2));
  
  ptrange4002000_variedDR_gensel_3jets.reset(new JetsPTRangeVariedDR_gen(ctx, "GEN_XCone3_nolep_Combined_dR350varied", true, 350, 400, 2000));
  ptrange700900_variedDR_gensel_3jets.reset(new JetsPTRangeVariedDR_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", true, 350, 700, 900));

  ptrange4002000_variedDR_gensel_3jets_450.reset(new JetsPTRangeVariedDR_gen(ctx, "GEN_XCone3_nolep_Combined_dR450varied", true, 450, 400, 2000));
  ptrange4002000_variedDR_gensel_3jets_600.reset(new JetsPTRangeVariedDR_gen(ctx, "GEN_XCone3_nolep_Combined_dR600varied", true, 600, 400, 2000));
  ptrange4002000_variedDR_gensel_3jets_12.reset(new JetsPTRangeVariedDR_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", false, 1.2, 400, 2000));
  ptrange4002000_variedDR_gensel_3jets_08.reset(new JetsPTRangeVariedDR_gen(ctx, "GEN_XCone3_nolep_Combined_dR08", false, 0.8, 400, 2000));
  ptrange4002000_variedDR_gensel_3jets_04.reset(new JetsPTRangeVariedDR_gen(ctx, "GEN_XCone3_nolep_Combined_dR04", false, 0.4, 400, 2000));

  ptrange5002000_variedDR_gensel_3jets_12.reset(new JetsPTRangeVariedDR_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", false, 1.2, 500, 2000));
  ptrange6002000_variedDR_gensel_3jets_12.reset(new JetsPTRangeVariedDR_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", false, 1.2, 600, 2000));
  ptrange7002000_variedDR_gensel_3jets_12.reset(new JetsPTRangeVariedDR_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", false, 1.2, 700, 2000));
  ptrange8002000_variedDR_gensel_3jets_12.reset(new JetsPTRangeVariedDR_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", false, 1.2, 800, 2000));
  ptrange9002000_variedDR_gensel_3jets_12.reset(new JetsPTRangeVariedDR_gen(ctx, "GEN_XCone3_nolep_Combined_dR12", false, 1.2, 900, 2000));

  ptrange700900_gensel_3jets.reset(new LeadingJetPTRange_gen(ctx, "GEN_XCone3_top_Combined_dR12", 700, 900));

  closeTopGluon.reset(new CloseTopGluonGen(ctx, 1.2));

  // /////////////////////////
  // Initiate input and output
  if(debug) cout << "\t--- Initiate input and output" << endl;
  init_handels(ctx);
  init_MC_hists(ctx);

  // /////////////
  // Handle output
  if(debug) cout << "\t--- Declare output" << endl;

  ctx.undeclare_all_event_output(); // Delete everything to save space
  declare_output(ctx); // Declare new output

}

// ##############################################################################
// ### Process; Event loop
// ### Selection, Corrections, fill of hists for each event               

bool MTopJetGenPostSelectionModule::process(uhh2::Event& event){

  if(debug) cout << "--- New Event ---" << endl;

  vector<GenTopJet> gen_jets3 = event.get(h_genfatjets);
  if(debug) cout << "jets size = " << gen_jets3.size() << endl;
  
  vector<TLorentzVector> gen_jets3_v4;
  TLorentzVector tmp;

  for(uint i=0; i<gen_jets3.size(); i++) {
    tmp.SetPxPyPzE(gen_jets3.at(i).v4().Px(), gen_jets3.at(i).v4().Py(), gen_jets3.at(i).v4().Pz(), gen_jets3.at(i).v4().E());
    gen_jets3_v4.push_back(tmp);
  }

  if(gen_jets3.size() < 2) {
    h_highestPtSorted->fill(event);
  } else if(gen_jets3.size() == 2) {
    if(gen_jets3_v4.at(0).Pt() > gen_jets3_v4.at(1).Pt()) h_highestPtSorted->fill(event);
  } else if(gen_jets3.size() == 3) {
    if(gen_jets3_v4.at(0).Pt() > gen_jets3_v4.at(1).Pt() && gen_jets3_v4.at(1).Pt() > gen_jets3_v4.at(2).Pt()) h_highestPtSorted->fill(event);
  }

  if(debug) {
    cout << "nSubjettines----" << endl;
    for(uint i=0; i< gen_jets3.size(); i++) {
      cout << i << " tau1: " << gen_jets3.at(i).tau1() << endl;
      cout << i << " tau2: " << gen_jets3.at(i).tau2() << endl;
      cout << i << " tau3: " << gen_jets3.at(i).tau3() << endl;
      cout << i << " tau4: " << gen_jets3.at(i).tau4() << endl;
    }
  }

  // /////////////////
  // Construct objects
  if(debug) cout << "\t--- Construct Obects" << endl;

  ttgenprod->process(event);
  jetprod_gen->process(event);
  jetprod_gen1->process(event);
  jetprod_gen2->process(event);
  jetprod_gen3->process(event);
  jetprod_gen4->process(event);
  jetprod_gen5->process(event);
  jetprod_gen6->process(event);
  jetprod_gen7->process(event);
  jetprod_gen8->process(event);
  jetprod_gen9->process(event);
  jetprod_gen10->process(event);
  jetprod_gen11->process(event);
  jetprod_gen12->process(event);
  jetprod_gen13->process(event);
  jetprod_gen14->process(event);

  // ////////////////////
  if(debug) cout << "\t\t--- before passed gensel" << endl;
  bool passed_gensel33 = event.get(h_passed_gensel);
  if(debug) cout << "\t\t--- after passed gensel" << endl;

  // /////////////////////////
  // Get Objects from rootfile
  if(debug) cout << "\t--- Get handles" << endl;

  vector<GenTopJet> gen_alljets3 = event.get(h_genall3fatjets);
  if(debug) cout << "alljets size = " << gen_alljets3.size() << endl;

  if(debug) {
    cout << "nSubjettines----" << endl;
    for(uint i=0; i< gen_jets3.size(); i++) {
      cout << i << " tau1: " << gen_jets3.at(i).tau1() << endl;
      cout << i << " tau2: " << gen_jets3.at(i).tau2() << endl;
      cout << i << " tau3: " << gen_jets3.at(i).tau3() << endl;
      cout << i << " tau4: " << gen_jets3.at(i).tau4() << endl;
    }
  }

  vector<GenTopJet> gen_nolepjets3 = event.get(h_gen3nolepjets);
  if(debug) cout << "nolepjets size = " << gen_nolepjets3.size() << endl;

  vector<GenTopJet> gen_noNearestLepjets3 = event.get(h_gen3noNearestLepjets);
  if(debug) cout << "noNearestLepjets size = " << gen_noNearestLepjets3.size() << endl;

  uint noLepSizeDiff = gen_alljets3.size()-gen_nolepjets3.size();
  uint noNearestLepSizeDiff = gen_alljets3.size()-gen_noNearestLepjets3.size();

  switch(noLepSizeDiff) {
    case 0:
      h_allnolepjets_sizeDiff0->fill(event);
      break;
    case 2:
      h_allnolepjets_sizeDiff2->fill(event);
      break;
    case 3:
      h_allnolepjets_sizeDiff3->fill(event);
      break;
    default:
      break;
  }

  switch(noNearestLepSizeDiff) {
    case 0:
      h_allNoNearestLepjets_sizeDiff0->fill(event);
      break;
    case 2:
      h_allNoNearestLepjets_sizeDiff2->fill(event);
      break;
    case 3:
      h_allNoNearestLepjets_sizeDiff3->fill(event);
      break;
    default:
      break;
  }

  //cout << gen_alljets3.size()-gen_nolepjets3.size() << endl;

  //auto ttbargen = event.get(h_ttbargen);
  /*
  double mass_gen33 = 0;
  double pt_gen33 = 0;
  vector<GenTopJet> gen_hadjets33 = event.get(h_genjets33_had);
  if(gen_hadjets33.size() > 0) {
    mass_gen33 = gen_hadjets33.at(0).v4().M();
    pt_gen33 = gen_hadjets33.at(0).v4().Pt();
  }
  event.set(h_mass_gen33, mass_gen33);
  event.set(h_pt_gen33, pt_gen33);

  vector<double> bquark_pt = {0,0};
  if(passed_gensel33) {
    const auto & tmp_ttbargen = event.get(h_ttbargen);
    GenParticle bot1 = tmp_ttbargen.bTop();
    GenParticle bot2 = tmp_ttbargen.bAntitop();
    bquark_pt[0] = bot1.pt();
    bquark_pt[1] = bot2.pt();
  }
  event.set(h_bquark_pt, bquark_pt);
  */
  // /////////////////////////////////////////////////////////////////////////////////
  // print genparticles
/*
  std::vector<GenParticle> *genparticles = event.genparticles; // these you should get through a handle
  int nparts = genparticles->size();

  cout << "----event start----" << endl;

  for(int i=0; i<nparts; ++i) {
    GenParticle* p = &(genparticles->at(i));
    //if(p->pdgId() == 21) {
    p->Print(genparticles);  // note that it needs the list of genparticles to display mother/daughter info
    //}
  }

  cout << "----event   end----" << endl;
*/
  // ///////////////////////////////
  // Run selection for single events
  if(debug) cout << "\t--- Run Selection" << endl;

  // fill all events
  h_XCone_GEN_noCut->fill(event);

  bool pass_pt400cut_gen;
  bool pass_pt2_gen;
  bool pass_pt350cut_gen;
  bool pass_test_selection;
  bool pass_subjet_quality_gen;
  bool pass_subjet_quality_eta_gen;

  bool pass_measurement_gen = false;
  bool pass_ignore_mass_gen = false;
  bool pass_ignore_subjet_gen = false;
  bool pass_ignore_lep_pt_gen = false;
  bool pass_pt350migration_gen = false;
  bool pass_massmigration_gen = false;
  bool pass_subptmigration_gen = false;
  //bool pass_leptonptmigration_gen = false;

  bool pass_ptrange400500_gen = false;
  bool pass_ptrange500600_gen = false;
  bool pass_ptrange600700_gen = false;
  bool pass_ptrange700800_gen = false;
  bool pass_ptrange800900_gen = false;
  bool pass_ptrange9001000_gen = false;

  bool pass_ptrange5002000_gen = false;
  bool pass_ptrange6002000_gen = false;
  bool pass_ptrange7002000_gen = false;
  bool pass_ptrange8002000_gen = false;
  bool pass_ptrange9002000_gen = false;

  bool pass_measurement_gen_3jets = false;
  bool pass_ptrange700900_gen_3jets = false;

  bool pass_newPtCut_gen_3jets = false;

  bool pass_newPtCut08_gen_3jets = false;
  bool pass_newPtCut10_gen_3jets = false;
  bool pass_newPtCut12_gen_3jets = false;
  bool pass_newPtCut14_gen_3jets = false;
  bool pass_newPtCut16_gen_3jets = false;

  bool pass_newPtCut12_gen_3jets_OnlySmalldR = false;

  bool pass_newPtCutRange4002000_variedDR_gen_3jets = false;
  bool pass_newPtCutRange700900_variedDR_gen_3jets = false;
  bool pass_newPtCutRange4002000_variedDR_gen_3jets_450 = false;
  bool pass_newPtCutRange4002000_variedDR_gen_3jets_600 = false;
  bool pass_newPtCutRange4002000_variedDR_gen_3jets_12 = false;
  bool pass_newPtCutRange4002000_variedDR_gen_3jets_08 = false;
  bool pass_newPtCutRange4002000_variedDR_gen_3jets_04 = false;

  bool pass_newPtCutRange5002000_variedDr_gen_3jets_12 = false;
  bool pass_newPtCutRange6002000_variedDr_gen_3jets_12 = false;
  bool pass_newPtCutRange7002000_variedDr_gen_3jets_12 = false;
  bool pass_newPtCutRange8002000_variedDr_gen_3jets_12 = false;
  bool pass_newPtCutRange9002000_variedDr_gen_3jets_12 = false;

  bool pass_newPtCutRange4002000_gen_3jets_12 = false;

  bool pass_closeTopGluon = false;

  pass_measurement_gen = passed_gensel33 && pt_gensel->passes(event) && pt2_gensel->passes(event) && mass_gensel->passes(event) && subjet_quality_gen->passes(event) && lepton_sel_gen->passes(event);
  pass_ignore_mass_gen = passed_gensel33 && pt_gensel->passes(event) && pt2_gensel->passes(event) && subjet_quality_gen->passes(event) && lepton_sel_gen->passes(event);
  pass_ignore_subjet_gen = passed_gensel33 && pt_gensel->passes(event) && pt2_gensel->passes(event) && mass_gensel->passes(event) && subjet_quality_eta_gen->passes(event) && lepton_sel_gen->passes(event);
  pass_ignore_lep_pt_gen = passed_gensel33 && pt_gensel->passes(event) && mass_gensel->passes(event) && subjet_quality_gen->passes(event) && lepton_sel_gen->passes(event);
  pass_pt350migration_gen = passed_gensel33 && !pt_gensel->passes(event) && pt2_gensel->passes(event) && pt350_gensel->passes(event) && mass_gensel->passes(event) && subjet_quality_gen->passes(event) && lepton_sel_gen->passes(event);
  pass_massmigration_gen = passed_gensel33 && pt_gensel->passes(event) && pt2_gensel->passes(event) && !mass_gensel->passes(event) && subjet_quality_gen->passes(event) && lepton_sel_gen->passes(event);
  pass_subptmigration_gen = passed_gensel33 && pt_gensel->passes(event) && pt2_gensel->passes(event) && mass_gensel->passes(event) && !subjet_quality_gen->passes(event) && lepton_sel_gen->passes(event);
  //pass_leptonptmigration_gen = passed_gensel33 && pt_gensel->passes(event) && pt2_gensel->passes(event) && mass_gensel->passes(event) && subjet_quality_gen->passes(event) && !lepton_sel_gen->passes(event);
  
  pass_ptrange400500_gen = pass_measurement_gen && ptrange400500_gensel->passes(event);
  pass_ptrange500600_gen = pass_measurement_gen && ptrange500600_gensel->passes(event);
  pass_ptrange600700_gen = pass_measurement_gen && ptrange600700_gensel->passes(event);
  pass_ptrange700800_gen = pass_measurement_gen && ptrange700800_gensel->passes(event);
  pass_ptrange800900_gen = pass_measurement_gen && ptrange800900_gensel->passes(event);
  pass_ptrange9001000_gen = pass_measurement_gen && ptrange9001000_gensel->passes(event);

  pass_ptrange5002000_gen = pass_measurement_gen && ptrange5002000_gensel->passes(event);
  pass_ptrange6002000_gen = pass_measurement_gen && ptrange6002000_gensel->passes(event);
  pass_ptrange7002000_gen = pass_measurement_gen && ptrange7002000_gensel->passes(event);
  pass_ptrange8002000_gen = pass_measurement_gen && ptrange8002000_gensel->passes(event);
  pass_ptrange9002000_gen = pass_measurement_gen && ptrange9002000_gensel->passes(event);

  pass_measurement_gen_3jets = passed_gensel33 && pt_gensel_3jets->passes(event) && pt2_gensel_3jets->passes(event) && subjet_quality_gen_3jets->passes(event) && lepton_sel_gen_3jets->passes(event);

  pass_ptrange700900_gen_3jets = pass_measurement_gen_3jets && ptrange700900_gensel_3jets->passes(event);

  pass_newPtCut_gen_3jets = passed_gensel33 && pt2_gensel_3jets->passes(event) && mass_gensel_3jets->passes(event) && subjet_quality_gen_3jets->passes(event) && lepton_sel_gen_3jets->passes(event);

  pass_newPtCut08_gen_3jets = pass_newPtCut_gen_3jets && pt08_gensel_3jets->passes(event);
  pass_newPtCut10_gen_3jets = pass_newPtCut_gen_3jets && pt10_gensel_3jets->passes(event);
  pass_newPtCut12_gen_3jets = pass_newPtCut_gen_3jets && pt12_gensel_3jets->passes(event);
  pass_newPtCut14_gen_3jets = pass_newPtCut_gen_3jets && pt14_gensel_3jets->passes(event);
  pass_newPtCut16_gen_3jets = pass_newPtCut_gen_3jets && pt16_gensel_3jets->passes(event);

  pass_newPtCut12_gen_3jets_OnlySmalldR = pass_newPtCut_gen_3jets && pt12_gensel_3jets_OnlySmalldR->passes(event);

  pass_newPtCutRange4002000_variedDR_gen_3jets = pass_newPtCut_gen_3jets && ptrange4002000_variedDR_gensel_3jets->passes(event);
  pass_newPtCutRange700900_variedDR_gen_3jets = pass_newPtCut_gen_3jets && ptrange700900_variedDR_gensel_3jets->passes(event);
  pass_newPtCutRange4002000_variedDR_gen_3jets_450 = pass_newPtCut_gen_3jets && ptrange4002000_variedDR_gensel_3jets_450->passes(event);
  pass_newPtCutRange4002000_variedDR_gen_3jets_600 = pass_newPtCut_gen_3jets && ptrange4002000_variedDR_gensel_3jets_600->passes(event);
  pass_newPtCutRange4002000_variedDR_gen_3jets_12 = pass_newPtCut_gen_3jets && ptrange4002000_variedDR_gensel_3jets_12->passes(event);
  pass_newPtCutRange4002000_variedDR_gen_3jets_08 = pass_newPtCut_gen_3jets && ptrange4002000_variedDR_gensel_3jets_08->passes(event);
  pass_newPtCutRange4002000_variedDR_gen_3jets_04 = pass_newPtCut_gen_3jets && ptrange4002000_variedDR_gensel_3jets_04->passes(event);

  pass_newPtCutRange5002000_variedDr_gen_3jets_12 = pass_newPtCut_gen_3jets && ptrange5002000_variedDR_gensel_3jets_12->passes(event);
  pass_newPtCutRange6002000_variedDr_gen_3jets_12 = pass_newPtCut_gen_3jets && ptrange6002000_variedDR_gensel_3jets_12->passes(event);
  pass_newPtCutRange7002000_variedDr_gen_3jets_12 = pass_newPtCut_gen_3jets && ptrange7002000_variedDR_gensel_3jets_12->passes(event);
  pass_newPtCutRange8002000_variedDr_gen_3jets_12 = pass_newPtCut_gen_3jets && ptrange8002000_variedDR_gensel_3jets_12->passes(event);
  pass_newPtCutRange9002000_variedDr_gen_3jets_12 = pass_newPtCut_gen_3jets && ptrange9002000_variedDR_gensel_3jets_12->passes(event);

  pass_newPtCutRange4002000_gen_3jets_12 = pass_newPtCut_gen_3jets && pt_gensel_3jets->passes(event);

  // Check of events passes selection
  // Use function with pointer: pointer->func()
  // Pointer points to memory location of object;
  //    --- Faster and more efficient, because no object has to be copied
  //    --- Be careful, since function changes object you give as an arguments
  //        --- p1->func(p2, o1); p2 can also be changed. o1 will be copied and be a new object (p=pointer, o=object) 
  pass_pt400cut_gen = passed_gensel33 && pt_gensel->passes(event); // Pass both: logical and && (in c++)
  pass_pt2_gen = passed_gensel33 && pt2_gensel->passes(event);
  pass_pt350cut_gen = passed_gensel33 && pt350_gensel->passes(event);
  pass_test_selection = passed_gensel33 && test_gensel->passes(event);

  pass_subjet_quality_gen = pass_pt400cut_gen && subjet_quality_gen->passes(event);
  pass_subjet_quality_eta_gen = pass_pt400cut_gen && subjet_quality_eta_gen->passes(event);

  pass_closeTopGluon = closeTopGluon->passes(event);

  //double weight = event.weight;
  event.weight = event.get(h_weight);

  scale_variation->process(event);

  // fill events after selection
  if(pass_pt400cut_gen)           h_XCone_GEN_ptCut->fill(event);
  if(pass_pt2_gen)                h_XCone_GEN_pt2Cut->fill(event);
  if(pass_pt350cut_gen)           h_XCone_GEN_pt350Cut->fill(event);
  if(pass_test_selection)         h_XCone_GEN_test->fill(event);
  if(pass_subjet_quality_gen)     h_subjet_quality_gen->fill(event);
  if(pass_subjet_quality_eta_gen) h_subjet_quality_eta_gen->fill(event);

  if(pass_measurement_gen)    h_XCone_GEN_Sel_measurement->fill(event);
  if(pass_pt350migration_gen) h_XCone_GEN_Sel_pt350->fill(event);
  if(pass_massmigration_gen)  h_XCone_GEN_Sel_noMass->fill(event);
  if(pass_subptmigration_gen) h_XCone_GEN_Sel_ptsub->fill(event);
  if(pass_ignore_subjet_gen)  h_eff_subjet_gen->fill(event);
  if(pass_ignore_mass_gen)    h_eff_masscut_gen->fill(event);
  if(pass_ignore_lep_pt_gen)  h_eff_lep_pt_gen->fill(event);


  //cout << "h_weight: " << std::to_string(event.weight) << ", event.weight" << std::to_string(weight) << endl;

  if(pass_measurement_gen) {
    h_decay_same_jet_gen->fill(event);
    h_decay_same_jet_gen_count->fill(event);

    if(pass_ptrange400500_gen)  h_decay_same_jet_pt400500_gen->fill(event);
    if(pass_ptrange500600_gen)  h_decay_same_jet_pt500600_gen->fill(event);
    if(pass_ptrange600700_gen)  h_decay_same_jet_pt600700_gen->fill(event);
    if(pass_ptrange700800_gen)  h_decay_same_jet_pt700800_gen->fill(event);
    if(pass_ptrange800900_gen)  h_decay_same_jet_pt800900_gen->fill(event);
    if(pass_ptrange9001000_gen) h_decay_same_jet_pt9001000_gen->fill(event);

    if(pass_ptrange5002000_gen) h_decay_same_jet_pt5002000_gen->fill(event);
    if(pass_ptrange6002000_gen) h_decay_same_jet_pt6002000_gen->fill(event);
    if(pass_ptrange7002000_gen) h_decay_same_jet_pt7002000_gen->fill(event);
    if(pass_ptrange8002000_gen) h_decay_same_jet_pt8002000_gen->fill(event);
    if(pass_ptrange9002000_gen) h_decay_same_jet_pt9002000_gen->fill(event);

  }

  h_alljets_gen->fill(event);
  h_nolepjets_gen->fill(event);
  h_noNearestLep_gen->fill(event);
  h_allnolepjets_comparison->fill(event);
  h_allNoNearestLepjets_comparison->fill(event);

  h_top_gluon_lep_gen_nocuts->fill(event);

  if(pass_measurement_gen_3jets) {
    h_top_gluon_lep_gen_measurement->fill(event);
  }

  if(pass_ptrange700900_gen_3jets) h_top_gluon_lep_gen_pt700900->fill(event);

  if(pass_newPtCut08_gen_3jets) h_top_gluon_lep_gen_newPtCut08->fill(event);
  if(pass_newPtCut10_gen_3jets) h_top_gluon_lep_gen_newPtCut10->fill(event);
  if(pass_newPtCut12_gen_3jets) h_top_gluon_lep_gen_newPtCut12->fill(event);
  if(pass_newPtCut14_gen_3jets) h_top_gluon_lep_gen_newPtCut14->fill(event);
  if(pass_newPtCut16_gen_3jets) h_top_gluon_lep_gen_newPtCut16->fill(event);

  if(pass_newPtCut12_gen_3jets_OnlySmalldR) h_top_gluon_lep_gen_newPtCut12_OnlySmalldR->fill(event);

  if(pass_newPtCutRange4002000_variedDR_gen_3jets) h_top_gluon_lep_gen_newPtCutRange4002000_variedDR->fill(event);
  if(pass_newPtCutRange700900_variedDR_gen_3jets) h_top_gluon_lep_gen_newPtCutRange700900_variedDR->fill(event);

  if(pass_newPtCutRange4002000_variedDR_gen_3jets) h_top_gluon_lep_gen_variedDR_350->fill(event);
  if(pass_newPtCutRange4002000_variedDR_gen_3jets_450) h_top_gluon_lep_gen_variedDR_450->fill(event);
  if(pass_newPtCutRange4002000_variedDR_gen_3jets_600) h_top_gluon_lep_gen_variedDR_600->fill(event);
  if(pass_newPtCutRange4002000_variedDR_gen_3jets_12) h_top_gluon_lep_gen_variedDR_12->fill(event);
  if(pass_newPtCutRange4002000_variedDR_gen_3jets_08) h_top_gluon_lep_gen_variedDR_08->fill(event);
  if(pass_newPtCutRange4002000_variedDR_gen_3jets_04) h_top_gluon_lep_gen_variedDR_04->fill(event);

  if(pass_newPtCutRange4002000_variedDR_gen_3jets_12) h_genNoLep->fill(event);
  if(pass_newPtCutRange4002000_gen_3jets_12) h_genNoLep_LeadingJetPtCut->fill(event);

  if(pass_newPtCutRange5002000_variedDr_gen_3jets_12) h_genNoLep_pT500->fill(event);
  if(pass_newPtCutRange6002000_variedDr_gen_3jets_12) h_genNoLep_pT600->fill(event);
  if(pass_newPtCutRange7002000_variedDr_gen_3jets_12) h_genNoLep_pT700->fill(event);
  if(pass_newPtCutRange8002000_variedDr_gen_3jets_12) h_genNoLep_pT800->fill(event);
  if(pass_newPtCutRange9002000_variedDr_gen_3jets_12) h_genNoLep_pT900->fill(event);

  if(pass_newPtCutRange4002000_variedDR_gen_3jets_12 && pass_closeTopGluon) h_genNoLep_closeGluonTop->fill(event);

  // Fill handles for output
  if(debug) cout << "\t--- Set output" << endl;
  event.set(h_measure_gen, pass_pt400cut_gen); // either 0 or 1, but filled for all events

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(MTopJetGenPostSelectionModule)
