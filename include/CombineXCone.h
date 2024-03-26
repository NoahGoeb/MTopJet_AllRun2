#pragma once
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/TTbarGen.h"

#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/Jet.h"
#include "UHH2/core/include/TopJet.h"
#include "UHH2/core/include/GenJet.h"
#include "UHH2/core/include/GenParticle.h"
#include "UHH2/core/include/PFParticle.h"
#include "UHH2/core/include/AnalysisModule.h"

#include <vector>
#include <iostream>
#include <math.h>

using namespace std;
using namespace uhh2;


class CombineXCone{

 public:

  bool FindLepton(uhh2::Event &);
  bool FindLepton_gen(uhh2::Event &);
  Particle GetLepton(uhh2::Event &);
  GenParticle GetLepton_gen(uhh2::Event &);
  TopJet CreateTopJetFromSubjets(vector<Jet> subjets, double ptmin, double etamax);
  GenTopJet CreateTopJetFromSubjets_gen(vector<GenJet> subjets, double ptmin, double etamax);
  TopJet FindHadjet(uhh2::Event &, const vector<TopJet> &);

private:

  uhh2::Event::Handle<std::vector<TopJet>>h_xcone33hadjets;
  uhh2::Event::Handle<std::vector<TopJet>>h_xcone33lepjets;
  uhh2::Event::Handle<std::vector<TopJet>>h_fatjets;

};


class CombineXCone33: public uhh2::AnalysisModule{
public:

  explicit CombineXCone33(uhh2::Context &,  const std::string &, const std::string & , const std::string &);
  virtual bool process(uhh2::Event & ) override;
  vector<int> GetWSubjetsIndices(uhh2::Event & );
  TopJet GetHadronicWJet(uhh2::Event &, const vector<int>&);

private:

  uhh2::Event::Handle<std::vector<TopJet>>h_xcone33hadjets;
  uhh2::Event::Handle<std::vector<TopJet>>h_xcone33lepjets;
  uhh2::Event::Handle<std::vector<TopJet>>h_fatjets;

};

class CombineXCone33_gen: public uhh2::AnalysisModule{
public:

  explicit CombineXCone33_gen(uhh2::Context &, bool);
  virtual bool process(uhh2::Event & ) override;

private:

  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENxcone33hadjets;
  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENxcone33lepjets;
  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENfatjets;
  uhh2::Event::Handle<TTbarGen> h_ttbargen;
  bool isTTbar_;
  // TTbarGen ttbargen;

};

class CombineXCone3all_gen: public uhh2::AnalysisModule{
public:

  explicit CombineXCone3all_gen(uhh2::Context &, uint, const std::string &, const std::string &);
  virtual bool process(uhh2::Event & ) override;

private:

  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENxcone3alljets;
  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENfatjets;
  uhh2::Event::Handle<TTbarGen> h_ttbargen;
  uint nJets_;
  // TTbarGen ttbargen;

};

class CombineXCone3nolep_gen: public uhh2::AnalysisModule{
public:

  explicit CombineXCone3nolep_gen(uhh2::Context &, bool, bool, float, const std::string &, const std::string &);
  virtual bool process(uhh2::Event & ) override;

private:

  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENxcone3nolepjets;
  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENfatjets;
  uhh2::Event::Handle<TTbarGen> h_ttbargen;
  bool isTTbar_;
  bool doPtdR_;
  float dR_;
  // TTbarGen ttbargen;

};

class CombineXCone3top_gluon_gen: public uhh2::AnalysisModule{
public:

  explicit CombineXCone3top_gluon_gen(uhh2::Context &, bool, bool, float, const std::string &, const std::string &, const std::string &, const std::string &);
  virtual bool process(uhh2::Event & ) override;

private:

  uhh2::Event::Handle<std::vector<GenTopJet>> h_GENxcone3topjets, h_GENxcone3gluonjets, h_GENxcone3lepjets;
  uhh2::Event::Handle<std::vector<GenTopJet>> h_GENfatjets;
  uhh2::Event::Handle<TTbarGen> h_ttbargen;
  bool isTTbar_;
  bool doPtdR_;
  float dR_;
  // TTbarGen ttbargen;

};

class CombineXCone3noNearestLep_gen: public uhh2::AnalysisModule{
public:

  explicit CombineXCone3noNearestLep_gen(uhh2::Context &, bool, const std::string &, const std::string &);
  virtual bool process(uhh2::Event & ) override;

private:

  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENxcone3noNearestLepjets;
  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENfatjets;
  uhh2::Event::Handle<TTbarGen> h_ttbargen;
  bool isTTbar_;
  // TTbarGen ttbargen;

};

class CombineXConeAllHad: public uhh2::AnalysisModule{
public:

  explicit CombineXConeAllHad(uhh2::Context &,  const std::string &, const std::string & , const std::string &);
  virtual bool process(uhh2::Event & ) override;

private:

  uhh2::Event::Handle<std::vector<TopJet>>h_xcone33hadjets;
  uhh2::Event::Handle<std::vector<TopJet>>h_xcone33lepjets;
  uhh2::Event::Handle<std::vector<TopJet>>h_fatjets;

};

class CombineXConeAllHad_gen: public uhh2::AnalysisModule{
public:

  explicit CombineXConeAllHad_gen(uhh2::Context &);
  virtual bool process(uhh2::Event & ) override;

private:

  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENxcone33hadjets;
  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENxcone33lepjets;
  uhh2::Event::Handle<std::vector<GenTopJet>>h_GENfatjets;

};

class CopyJets: public uhh2::AnalysisModule{
public:

  explicit CopyJets(uhh2::Context &, const std::string &, const std::string &);
  virtual bool process(uhh2::Event & ) override;

private:

  uhh2::Event::Handle<std::vector<TopJet>>h_new;
  uhh2::Event::Handle<std::vector<TopJet>>h_old;

};
