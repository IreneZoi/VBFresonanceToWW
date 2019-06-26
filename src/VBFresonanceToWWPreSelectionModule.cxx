#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/MuonIds.h"
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/Utils.h"
#include <UHH2/common/include/MCWeight.h>
#include "UHH2/common/include/PrintingModules.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/MuonHists.h"
#include "UHH2/common/include/EventHists.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/GenJetsHists.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWSelections.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWHists.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWGenTopJetHists.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWParticleHists.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWW_WTopJetHists.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWW_WTopJetHistsCorrectedSDMass.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWDiJetHists.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWGenDiJetHists.h"

#define PRINT false
#define PUvariations false

using namespace std;
using namespace uhh2;

namespace uhh2examples {

  /** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
  *
  * This is the central class which calls other AnalysisModules, Hists or Selection classes.
  * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
  */
  class VBFresonanceToWWPreSelectionModule: public AnalysisModule {
  public:


    explicit VBFresonanceToWWPreSelectionModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    std::string channel_;

    Event::Handle<vector<Jet>> h_IdCriteriaJets;
    std::unique_ptr<CommonModules> common;

    std::unique_ptr<AnalysisModule> Gen_printer;

    std::unique_ptr<JetCorrector> jet_corrector;

    std::unique_ptr<JetCorrector> jet_corrector_2016_B;
    std::unique_ptr<JetCorrector> jet_corrector_2016_C;
    std::unique_ptr<JetCorrector> jet_corrector_2016_D;
    std::unique_ptr<JetCorrector> jet_corrector_2016_E;
    std::unique_ptr<JetCorrector> jet_corrector_2016_F;
    std::unique_ptr<JetCorrector> jet_corrector_2016_G;
    std::unique_ptr<JetCorrector> jet_corrector_2016_H;

    std::unique_ptr<JetCorrector> jet_corrector_2017_B;
    std::unique_ptr<JetCorrector> jet_corrector_2017_C;
    std::unique_ptr<JetCorrector> jet_corrector_2017_D;
    std::unique_ptr<JetCorrector> jet_corrector_2017_E;
    std::unique_ptr<JetCorrector> jet_corrector_2017_F;

    std::unique_ptr<JetCorrector> jet_corrector_2018_A;
    std::unique_ptr<JetCorrector> jet_corrector_2018_B;
    std::unique_ptr<JetCorrector> jet_corrector_2018_C;
    std::unique_ptr<JetCorrector> jet_corrector_2018_D;

    std::unique_ptr<TopJetCorrector> topjet_corrector;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2016_B;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2016_C;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2016_D;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2016_E;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2016_F;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2016_G;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2016_H;

    std::unique_ptr<TopJetCorrector> topjet_corrector_2017_B;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2017_C;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2017_D;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2017_E;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2017_F;

    std::unique_ptr<TopJetCorrector> topjet_corrector_2018_A;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2018_B;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2018_C;
    std::unique_ptr<TopJetCorrector> topjet_corrector_2018_D;
   
    std::unique_ptr<SoftDropMassCalculator> topjet_sdmasscorrector;
    //102X    std::unique_ptr<JetMassScale> topjet_jms;
    std::string jec_tag, jec_ver, jec_jet_coll_AK8puppi, jec_jet_coll_AK4puppi;
    JERSmearing::SFtype1 JER_sf;
    TString ResolutionFileName;   

    std::unique_ptr<JetResolutionSmearer> jetER_smearer;
    std::unique_ptr<GenericJetResolutionSmearer> topjetER_smearer;

    std::unique_ptr<JetCleaner> jetcleaner;
    std::unique_ptr<TopJetCleaner> topjetcleaner;

    std::unique_ptr<JetCleaner> ak4pfidfilter;
    std::unique_ptr<TopJetCleaner> ak8pfidfilter;

    // Data/MC scale factors
    std::unique_ptr<uhh2::AnalysisModule> pileup_SF;
    std::unique_ptr<uhh2::AnalysisModule> lumiweight;
    std::unique_ptr<uhh2::AnalysisModule> MCWeightModule;
    std::unique_ptr<uhh2::AnalysisModule> MCPileupReweightModule;

    //********** SELECTIONS ***************
    // declare the Selections to use. Use unique_ptr to ensure automatic call of delete in the destructor,
    // to avoid memory leaks.
    std::unique_ptr<Selection> muon_sel, electron_sel;//lepton veto
    //W jets
    std::unique_ptr<Selection> topjet2_sel;
    std::unique_ptr<Selection> invMtopjet_fitsel;
    // std::unique_ptr<Selection> invMtopjet_sel;
    std::unique_ptr<Selection> invMtopjet_SDsel;
    std::unique_ptr<Selection> topjets_deta_sel;
    std::unique_ptr<Selection> VVmass_sel, WWmass_sel;
    std::unique_ptr<Selection> tau21topjetHP_sel;
    //    std::unique_ptr<Selection> tau21topjet045_sel;
    //VBF jets
    std::unique_ptr<Selection> jet2_sel;

    //********** HISTOS ***************
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
    std::unique_ptr<Hists> h_input;
    std::unique_ptr<Hists> h_event_input;
    std::unique_ptr<Hists> h_topjets_input;
    std::unique_ptr<Hists> h_jets_input;
    std::unique_ptr<Hists> h_Wtopjets_input;
    std::unique_ptr<Hists> h_ele_input;
    std::unique_ptr<Hists> h_muon_input;

    std::unique_ptr<Hists> h_commonmod;
    std::unique_ptr<Hists> h_topjets_commonmod;
    std::unique_ptr<Hists> h_jets_commonmod;
    std::unique_ptr<Hists> h_Wtopjets_commonmod;
    std::unique_ptr<Hists> h_ele_commonmod;
    std::unique_ptr<Hists> h_muon_commonmod;

    std::unique_ptr<Hists> h_ele_leptonVeto;
    std::unique_ptr<Hists> h_muon_leptonVeto;
    std::unique_ptr<Hists> h_Wtopjets_leptonVeto;
    std::unique_ptr<Hists> h_leptonVeto;

    std::unique_ptr<Hists> h_Wtopjets_afterSD;
    //102X     std::unique_ptr<Hists> h_Wtopjets_afterSDcorrections;

    std::unique_ptr<Hists> h_Wtopjets_jec;
    std::unique_ptr<Hists> h_jec;

    std::unique_ptr<Hists> h_cleaner;
    std::unique_ptr<Hists> h_Wtopjets_cleaner;
    std::unique_ptr<Hists> h_topjets_cleaner;
    std::unique_ptr<Hists> h_jets_cleaner;

    std::unique_ptr<Hists> h_Wtopjets_noOverlapping;
    std::unique_ptr<Hists> h_topjets_noOverlapping;
    std::unique_ptr<Hists> h_jets_noOverlapping;

    std::unique_ptr<Hists> h_Wtopjets_noOverlapping_eta;
    std::unique_ptr<Hists> h_jets_noOverlapping_eta;

    std::unique_ptr<Hists> h_topjets_2topjetsel;
    std::unique_ptr<Hists> h_Wtopjets_2topjetsel;

    std::unique_ptr<Hists> h_Wtopjets_invM;
    std::unique_ptr<Hists> h_topjets_invM;

    std::unique_ptr<Hists> h_Wtopjets_deta;
    std::unique_ptr<Hists> h_topjets_deta;

    std::unique_ptr<Hists> h_Wtopjets_compare;
    std::unique_ptr<Hists> h_topjets_compare;
    std::unique_ptr<Hists> h_Dijets_compare;
    std::unique_ptr<Hists> h_jets_compare;
    std::unique_ptr<Hists> h_compare;
    std::unique_ptr<Hists> h_event_compare;

    std::unique_ptr<Hists> h_Wtopjets_compareSD;


    std::unique_ptr<Hists> h_Wtopjets_VVMass;
    std::unique_ptr<Hists> h_topjets_VVMass;
    std::unique_ptr<Hists> h_Dijets_VVMass;
    std::unique_ptr<Hists> h_jets_VVMass;
    std::unique_ptr<Hists> h_VVMass;

    std::unique_ptr<Hists> h_Wtopjets_VVMass_tau21HP;
    std::unique_ptr<Hists> h_topjets_VVMass_tau21HP;
    std::unique_ptr<Hists> h_Dijets_VVMass_tau21HP;
    std::unique_ptr<Hists> h_jets_VVMass_tau21HP;

    std::unique_ptr<Hists> h_Wtopjets_AK4cleaner;
    std::unique_ptr<Hists> h_jets_AK4cleaner;


    std::unique_ptr<Hists> h_Wtopjets_VVMass_tau21_045;


    std::unique_ptr<Hists> h_Wtopjets_WWMass;
    std::unique_ptr<Hists> h_topjets_WWMass;

    std::unique_ptr<Hists> h_Wtopjets_tau21WW;
    std::unique_ptr<Hists> h_topjets_tau21WW;

    std::unique_ptr<Hists> h_jets_2jetsel;
    std::unique_ptr<Hists> h_Wtopjets_2jetsel;

    std::unique_ptr<Hists> h_jets_vbfetasign;
    std::unique_ptr<Hists> h_Wtopjets_vbfetasign;

    std::unique_ptr<Hists> h_VBF_VVMass;
    std::unique_ptr<Hists> h_jets_VBF_VVMass;
    std::unique_ptr<Hists> h_Dijets_VBF_VVMass;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_VVMass;
    std::unique_ptr<Hists> h_topjets_withVBF_VVMass;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_VVMass_tau21HP;
    std::unique_ptr<Hists> h_topjets_withVBF_VVMass_tau21HP;
    std::unique_ptr<Hists> h_jets_VBF_VVMass_tau21HP;
    std::unique_ptr<Hists> h_Dijets_VBF_VVMass_tau21HP;


    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM800_de45;


    std::unique_ptr<Hists> h_input_gentopjets;
    std::unique_ptr<Hists> h_input_gendijets;
    std::unique_ptr<Hists> h_input_genjets;
    std::unique_ptr<Hists> h_input_genparticle;

    Year year; 

    const int runnr_2016_Ab = 271036;
    const int runnr_2016_Ae = 271658;
    const int runnr_2016_Bb = 272007;
    const int runnr_2016_Be = 275376;
    const int runnr_2016_Cb = 275657;
    const int runnr_2016_Ce = 276283;
    const int runnr_2016_Db = 276315;
    const int runnr_2016_De = 276811;
    const int runnr_2016_Eb = 276831;
    const int runnr_2016_Ee = 277420;
    const int runnr_2016_Fb = 277772;
    const int runnr_2016_Fe = 278808;
    const int runnr_2016_Gb = 278820;
    const int runnr_2016_Ge = 280385;
    const int runnr_2016_Hb = 280919;
    const int runnr_2016_He = 284044;

    const int runnr_2017_Ab = 294927;
    const int runnr_2017_Ae = 297019;
    const int runnr_2017_Bb = 297046;
    const int runnr_2017_Be = 299329;
    const int runnr_2017_Cb = 299368;
    const int runnr_2017_Ce = 302029;
    const int runnr_2017_Db = 302030;
    const int runnr_2017_De = 303434;
    const int runnr_2017_Eb = 303824;
    const int runnr_2017_Ee = 304797;
    const int runnr_2017_Fb = 305040;
    const int runnr_2017_Fe = 306462;

    const int runnr_2018_Ab = 315252;
    const int runnr_2018_Ae = 316995;
    const int runnr_2018_Bb = 317080;
    const int runnr_2018_Be = 319310;
    const int runnr_2018_Cb = 319337;
    const int runnr_2018_Ce = 320065;
    const int runnr_2018_Db = 320673;
    const int runnr_2018_De = 325175;


    bool isMC;

    MuonId     MuId;
    ElectronId EleId;

    JetId AK4PFID;
    TopJetId AK8PFID;
  };


  VBFresonanceToWWPreSelectionModule::VBFresonanceToWWPreSelectionModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.

    cout << "Hello World from VBFresonanceToWWPreSelectionModule!" << endl;

    Gen_printer.reset(new GenParticlesPrinter(ctx));

    // If needed, access the configuration of the module here, e.g.:
    string testvalue = ctx.get("TestKey", "<not set>");
    cout << "TestKey in the configuration was: " << testvalue << endl;


    //choose channel from .xml file
    isMC = (ctx.get("dataset_type") == "MC");
    channel_ = ctx.get("channel");
    /*
    if(isMC)
    {
    pileup_SF.reset(new MCPileupReweight(ctx));
    lumiweight.reset(new MCLumiWeight(ctx));
  }
  */
  // If running in SFrame, the keys "dataset_version", "dataset_type", "dataset_lumi",
  // and "target_lumi" are set to the according values in the xml file. For CMSSW, these are
  // not set automatically, but can be set in the python config file.
  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }

  // 1. setup other modules. CommonModules and the JetCleaner:
  h_IdCriteriaJets = ctx.get_handle<vector<Jet>>("patJetsAK8PFPUPPI");

  //80X  MuId  = AndId<Muon>(MuonIDTight(), PtEtaCut(30., 2.4));
  MuId  = AndId<Muon>(MuonID(Muon::CutBasedIdTight), PtEtaCut(30., 2.4), MuonID(Muon::TkIsoLoose)); //changed for 102X
  EleId = AndId<Electron>(ElectronID_HEEP_RunII_25ns, PtEtaCut(35., 2.5));
  //EleId = AndId<Electron>(ElectronID_Spring16_tight_noIso, PtEtaCut(20., 5.));

  if(isMC)
    {
      MCWeightModule.reset(new MCLumiWeight(ctx));
      MCPileupReweightModule.reset(new MCPileupReweight(ctx));
      if(PUvariations)
	{
	  MCPileupReweightModule.reset(new MCPileupReweight(ctx,"up"));
	  MCPileupReweightModule.reset(new MCPileupReweight(ctx,"down"));
	}
    }

  common.reset(new CommonModules());
  // TODO: configure common here, e.g. by
  // calling common->set_*_id or common->disable_*


  //common->disable_mcpileupreweight(); //irene
  common->switch_jetlepcleaner(false);
  common->disable_jetpfidfilter();
  common->disable_jersmear(); //irene
  common->disable_jec(); //irene
  //    common->disable_metfilters(); //irene
  if(PRINT) cout << "common" <<endl;
  //    common->set_jet_id(PtEtaCut(30.0, 2.4));
  year = extract_year(ctx);
  
  //JEC  correctors
  jec_jet_coll_AK8puppi   = "AK8PFPuppi";
  jec_jet_coll_AK4puppi = "AK4PFPuppi";

  if(year == Year::is2016v2 || year == Year::is2016v3){
    jec_tag = "Summer16_07Aug2017";
    jec_ver = "11";
    JER_sf  = JERSmearing::SF_13TeV_Summer16_25nsV1;
    ResolutionFileName = "2016/Summer16_25nsV1_MC_PtResolution_AK4PFPuppi.txt";
    }
  else if(year == Year::is2017v1 || year == Year::is2017v2){
    jec_tag = "Fall17_17Nov2017";
    jec_ver = "32";
    JER_sf  = JERSmearing::SF_13TeV_Fall17_V3;
    ResolutionFileName = "2017/Fall17_V3_MC_PtResolution_AK4PFPuppi.txt";
  }
  else if(year == Year::is2018 ){
    jec_tag = "Autumn18";
    jec_ver = "8";
    //    JER_sf  = JERSmearing::SF_13TeV_Autumn18_V4;
    JER_sf  = JERSmearing::SF_13TeV_Autumn18_RunABCD_V4;
    ResolutionFileName = "2018/Autumn18_V4_MC_PtResolution_AK4PFPuppi.txt";
  }

  if(isMC){
    std::cout << "USING "<< year_str_map.at(year) << " MC JEC: "<< jec_tag << " V" << jec_ver << std::endl;
    std::cout << "for the following jet collections: " << jec_jet_coll_AK8puppi << " " << jec_jet_coll_AK4puppi << std::endl;     
    std::cout << "Smearing: " << jec_jet_coll_AK8puppi << " with year default " << std::endl;
    std::cout << "Smearing: " << jec_jet_coll_AK4puppi << " with "<< ResolutionFileName << std::endl;     
    jet_corrector.reset(new JetCorrector(ctx, JERFiles::JECFilesMC(jec_tag, jec_ver, jec_jet_coll_AK4puppi)));
    topjet_corrector.reset(new TopJetCorrector(ctx,JERFiles::JECFilesMC(jec_tag, jec_ver, jec_jet_coll_AK8puppi)));
    if(channel_=="signal")
      {
	jetER_smearer.reset(new JetResolutionSmearer(ctx));
	topjetER_smearer.reset(new GenericJetResolutionSmearer(ctx,"topjets","gentopjets",JER_sf,ResolutionFileName));
      }
    

  }
  else{
    std::cout << "USING " << year_str_map.at(year) << " DATA JEC: "<< jec_tag << " V" << jec_ver << std::endl;
    if(year == Year::is2016v2 || year == Year::is2016v3){
      jet_corrector_2016_B.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "B")));
      jet_corrector_2016_C.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "C")));
      jet_corrector_2016_D.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "D")));
      jet_corrector_2016_E.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "E")));
      jet_corrector_2016_F.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "F")));
      jet_corrector_2016_G.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "G")));
      jet_corrector_2016_H.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "H")));

      topjet_corrector_2016_B.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "B")));
      topjet_corrector_2016_C.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "C")));
      topjet_corrector_2016_D.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "D")));
      topjet_corrector_2016_E.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "E")));
      topjet_corrector_2016_F.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "F")));
      topjet_corrector_2016_G.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "G")));
      topjet_corrector_2016_H.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "H")));
 
    }
    else if(year == Year::is2017v1 || year == Year::is2017v2){
      jet_corrector_2017_B.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "B")));
      jet_corrector_2017_C.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "C")));
      jet_corrector_2017_D.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "D")));
      jet_corrector_2017_E.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "E")));
      jet_corrector_2017_F.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "F")));

      topjet_corrector_2017_B.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "B")));
      topjet_corrector_2017_C.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "C")));
      topjet_corrector_2017_D.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "D")));
      topjet_corrector_2017_E.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "E")));
      topjet_corrector_2017_F.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "F")));
 
    }
    else if(year == Year::is2018 ){
      jet_corrector_2018_A.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "A")));
      jet_corrector_2018_B.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "B")));
      jet_corrector_2018_C.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "C")));
      jet_corrector_2018_D.reset(new JetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK8puppi, "D")));

      topjet_corrector_2018_A.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "A")));
      topjet_corrector_2018_B.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "B")));
      topjet_corrector_2018_C.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "C")));
      topjet_corrector_2018_D.reset(new TopJetCorrector(ctx, JERFiles::JECFilesDATA(jec_tag, jec_ver, jec_jet_coll_AK4puppi, "D")));
    }
  }
  std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
  /*end of year dependent initialization*/




  /*

  std::vector<std::string> JEC_AK4, JEC_AK8,JEC_AK4_A,JEC_AK4_B,JEC_AK4_C,JEC_AK4_D,JEC_AK4_E,JEC_AK4_F,JEC_AK4_G,JEC_AK4_H,JEC_AK8_A,JEC_AK8_B,JEC_AK8_C,JEC_AK8_D,JEC_AK8_E,JEC_AK8_F,JEC_AK8_G,JEC_AK8_H;

  if(isMC)
    {
      if(PRINT) cout << "MC JEC" <<endl;

      if(year == Year::is2016v2 || year == Year::is2016v3)
	{
	  if(PRINT) cout << "2016" <<endl;

	  JEC_AK4     = JERFiles::Summer16_07Aug2017_V11_L123_AK4PFPuppi_MC;
	  JEC_AK8     = JERFiles::Summer16_07Aug2017_V11_L123_AK8PFPuppi_MC;
	}
      else if(year == Year::is2017v1 || year == Year::is2017v2)
	{
	  if(PRINT) cout << "2017" <<endl;
	  JEC_AK4     = JERFiles::Fall17_17Nov2017_V32_L123_AK4PFPuppi_MC;
	  JEC_AK8     = JERFiles::Fall17_17Nov2017_V32_L123_AK8PFPuppi_MC;
	}
      else if(year == Year::is2018 )
	{
	  if(PRINT) cout << "2018" <<endl;
	  JEC_AK4     = JERFiles::Autumn18_V8_L123_AK4PFPuppi_MC;
	  JEC_AK8     = JERFiles::Autumn18_V8_L123_AK8PFPuppi_MC;
	}
    }
  else
    {
      if(PRINT) cout << "data JEC" <<endl;
      if(year == Year::is2016v2 || year == Year::is2016v3)
        {
	  if(PRINT) cout << "2016" <<endl;
	  JEC_AK4_B = JERFiles::Summer16_07Aug2017_V11_B_L123_AK4PFPuppi_DATA;
	  JEC_AK4_C = JERFiles::Summer16_07Aug2017_V11_C_L123_AK4PFPuppi_DATA;
	  JEC_AK4_D = JERFiles::Summer16_07Aug2017_V11_D_L123_AK4PFPuppi_DATA;
	  JEC_AK4_E = JERFiles::Summer16_07Aug2017_V11_E_L123_AK4PFPuppi_DATA;
	  JEC_AK4_F = JERFiles::Summer16_07Aug2017_V11_F_L123_AK4PFPuppi_DATA;
	  JEC_AK4_G = JERFiles::Summer16_07Aug2017_V11_G_L123_AK4PFPuppi_DATA;
	  JEC_AK4_H = JERFiles::Summer16_07Aug2017_V11_H_L123_AK4PFPuppi_DATA;
	  
	  JEC_AK8_B = JERFiles::Summer16_07Aug2017_V11_B_L123_AK8PFPuppi_DATA;
	  JEC_AK8_C = JERFiles::Summer16_07Aug2017_V11_C_L123_AK8PFPuppi_DATA;
	  JEC_AK8_D = JERFiles::Summer16_07Aug2017_V11_D_L123_AK8PFPuppi_DATA;
	  JEC_AK8_E = JERFiles::Summer16_07Aug2017_V11_E_L123_AK8PFPuppi_DATA;
	  JEC_AK8_F = JERFiles::Summer16_07Aug2017_V11_F_L123_AK8PFPuppi_DATA;
	  JEC_AK8_G = JERFiles::Summer16_07Aug2017_V11_G_L123_AK8PFPuppi_DATA;
	  JEC_AK8_H = JERFiles::Summer16_07Aug2017_V11_H_L123_AK8PFPuppi_DATA;
	}
      else if(year == Year::is2017v1 || year == Year::is2017v2)
	{
	  if(PRINT) cout << "2017" <<endl;
	  JEC_AK4_B = JERFiles::Fall17_17Nov2017_V32_B_L123_AK4PFPuppi_DATA;
	  JEC_AK4_C = JERFiles::Fall17_17Nov2017_V32_C_L123_AK4PFPuppi_DATA;
	  JEC_AK4_D = JERFiles::Fall17_17Nov2017_V32_D_L123_AK4PFPuppi_DATA;
	  JEC_AK4_E = JERFiles::Fall17_17Nov2017_V32_E_L123_AK4PFPuppi_DATA;
	  JEC_AK4_F = JERFiles::Fall17_17Nov2017_V32_F_L123_AK4PFPuppi_DATA;
	  
	  JEC_AK8_B = JERFiles::Fall17_17Nov2017_V32_B_L123_AK8PFPuppi_DATA;
	  JEC_AK8_C = JERFiles::Fall17_17Nov2017_V32_C_L123_AK8PFPuppi_DATA;
	  JEC_AK8_D = JERFiles::Fall17_17Nov2017_V32_D_L123_AK8PFPuppi_DATA;
	  JEC_AK8_E = JERFiles::Fall17_17Nov2017_V32_E_L123_AK8PFPuppi_DATA;
	  JEC_AK8_F = JERFiles::Fall17_17Nov2017_V32_F_L123_AK8PFPuppi_DATA;
	}  
      else if(year == Year::is2018 )
        {
	  if(PRINT) cout << "2018" <<endl;
	  JEC_AK4_A = JERFiles::Autumn18_V8_A_L123_AK4PFPuppi_DATA;
	  JEC_AK4_B = JERFiles::Autumn18_V8_B_L123_AK4PFPuppi_DATA;
	  JEC_AK4_C = JERFiles::Autumn18_V8_C_L123_AK4PFPuppi_DATA;
	  JEC_AK4_D = JERFiles::Autumn18_V8_D_L123_AK4PFPuppi_DATA;
	  
	  JEC_AK8_A = JERFiles::Autumn18_V8_A_L123_AK8PFPuppi_DATA;
	  JEC_AK8_B = JERFiles::Autumn18_V8_B_L123_AK8PFPuppi_DATA;
	  JEC_AK8_C = JERFiles::Autumn18_V8_C_L123_AK8PFPuppi_DATA;
	  JEC_AK8_D = JERFiles::Autumn18_V8_D_L123_AK8PFPuppi_DATA;
	}
    }

	  if(PRINT) cout << "jet correctors:" <<endl;


  if(isMC)
    {
      jet_corrector.reset(new JetCorrector(ctx, JEC_AK4));
      topjet_corrector.reset(new TopJetCorrector(ctx, JEC_AK8));

      	if(channel_=="signal")
	{
	  jetER_smearer.reset(new JetResolutionSmearer(ctx));
	  topjetER_smearer.reset(new GenericJetResolutionSmearer(ctx,"topjets","gentopjets",true,JERSmearing::SF_13TeV_Summer16_25nsV1,"201Summer16_25nsV1_MC_PtResolution_AK8PFPuppi.txt"));
	}
    }
  else
    {
      if(year == Year::is2016v2 || year == Year::is2016v3)
        {

	  jet_corrector_2016_B.reset(new JetCorrector(ctx, JEC_AK4_B));
	  jet_corrector_2016_C.reset(new JetCorrector(ctx, JEC_AK4_C));
	  jet_corrector_2016_D.reset(new JetCorrector(ctx, JEC_AK4_D));
	  jet_corrector_2016_E.reset(new JetCorrector(ctx, JEC_AK4_E));
	  jet_corrector_2016_F.reset(new JetCorrector(ctx, JEC_AK4_F));
	  jet_corrector_2016_G.reset(new JetCorrector(ctx,JEC_AK4_G ));
	  jet_corrector_2016_H.reset(new JetCorrector(ctx,JEC_AK4_H ));
	  
	  topjet_corrector_2016_B.reset(new TopJetCorrector(ctx, JEC_AK8_B));
	  topjet_corrector_2016_C.reset(new TopJetCorrector(ctx, JEC_AK8_C));
	  topjet_corrector_2016_D.reset(new TopJetCorrector(ctx, JEC_AK8_D));
	  topjet_corrector_2016_E.reset(new TopJetCorrector(ctx, JEC_AK8_F));
	  topjet_corrector_2016_F.reset(new TopJetCorrector(ctx, JEC_AK8_F));
	  topjet_corrector_2016_G.reset(new TopJetCorrector(ctx,JEC_AK8_G ));
	  topjet_corrector_2016_H.reset(new TopJetCorrector(ctx,JEC_AK8_H ));
	}
      else if(year == Year::is2017v1 || year == Year::is2017v2)
        {
          jet_corrector_2017_B.reset(new JetCorrector(ctx, JEC_AK4_B));
          jet_corrector_2017_C.reset(new JetCorrector(ctx, JEC_AK4_C));
          jet_corrector_2017_D.reset(new JetCorrector(ctx, JEC_AK4_D));
          jet_corrector_2017_E.reset(new JetCorrector(ctx, JEC_AK4_E));
          jet_corrector_2017_F.reset(new JetCorrector(ctx, JEC_AK4_F));

          topjet_corrector_2017_B.reset(new TopJetCorrector(ctx, JEC_AK8_B));
          topjet_corrector_2017_C.reset(new TopJetCorrector(ctx, JEC_AK8_C));
          topjet_corrector_2017_D.reset(new TopJetCorrector(ctx, JEC_AK8_D));
          topjet_corrector_2017_E.reset(new TopJetCorrector(ctx, JEC_AK8_F));
          topjet_corrector_2017_F.reset(new TopJetCorrector(ctx, JEC_AK8_F));

	}
      else if(year == Year::is2018 )
        {
          jet_corrector_2018_A.reset(new JetCorrector(ctx, JEC_AK4_A));
          jet_corrector_2018_B.reset(new JetCorrector(ctx, JEC_AK4_B));
          jet_corrector_2018_C.reset(new JetCorrector(ctx, JEC_AK4_C));
          jet_corrector_2018_D.reset(new JetCorrector(ctx, JEC_AK4_D));

          topjet_corrector_2018_A.reset(new TopJetCorrector(ctx, JEC_AK8_A));
          topjet_corrector_2018_B.reset(new TopJetCorrector(ctx, JEC_AK8_B));
          topjet_corrector_2018_C.reset(new TopJetCorrector(ctx, JEC_AK8_C));
          topjet_corrector_2018_D.reset(new TopJetCorrector(ctx, JEC_AK8_D));

	}
    }
  */
  topjet_sdmasscorrector.reset(new SoftDropMassCalculator(ctx, true, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/puppiCorr.root","topjets"));
  //102X topjet_jms.reset(new JetMassScale(ctx,true, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/jetmassResolution.root","topjets"));

  jetcleaner.reset(new JetCleaner(ctx, 30.0, 5));
  topjetcleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(200., 2.5))));

  AK4PFID=JetPFID(JetPFID::WP_LOOSE_PUPPI);
  AK8PFID=JetPFID(JetPFID::WP_LOOSE_PUPPI);


  //102X  ak8pfidfilter.reset(new TopJetCleaner(ctx,AK8PFID));
  //102X  ak4pfidfilter.reset(new JetCleaner(ctx,AK4PFID));
  
  
  if(PRINT) cout << "cleaners" <<endl;




  common->init(ctx);

  // note that the JetCleaner is only kept for the sake of example;
  // instead of constructing a jetcleaner explicitly,
  // the cleaning can also be achieved with less code via CommonModules with:
  // common->set_jet_id(PtEtaCut(30.0, 2.4));
  // before the 'common->init(ctx)' line.
  
  // 2. set up selections ***

  muon_sel.reset(new MuonVeto(MuId,0.8)); // see VBFresonanceToWWSelections
  electron_sel.reset(new ElectronVeto(EleId,0.8)); // see VBFresonanceToWWSelections
  topjet2_sel.reset(new NTopJetSelection(2)); // at least 2 jets
  invMtopjet_fitsel.reset(new invMassTopjetSelection()); // see VBFresonanceToWWSelections
  topjets_deta_sel.reset(new deltaEtaTopjetSelection()); // see VBFresonanceToWWSelections
  invMtopjet_SDsel.reset(new invMassTopjetSelection(1080.0f)); // see VBFresonanceToWWSelections
  VVmass_sel.reset(new VVMassTopjetSelection());// see VBFresonanceToWWSelections
  tau21topjetHP_sel.reset(new nSubjTopjetSelection(0.f,0.35f)); // see VBFresonanceToWWSelections
  jet2_sel.reset(new NJetSelection(2)); // at least 2 jets
  
  if(PRINT) cout << "reset sel" <<endl;
  
  
  // 3. Set up Hists classes:
  h_input.reset(new VBFresonanceToWWHists(ctx, "input"));
  h_event_input.reset(new EventHists(ctx, "event_input"));
  h_ele_input.reset(new ElectronHists(ctx, "ele_input"));
  h_muon_input.reset(new MuonHists(ctx, "muon_input"));
  h_topjets_input.reset(new TopJetHists(ctx, "topjets_input"));
  h_Wtopjets_input.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_input"));
  h_jets_input.reset(new JetHists(ctx, "jets_input"));
  
  h_commonmod.reset(new VBFresonanceToWWHists(ctx, "commonmod"));
  h_ele_commonmod.reset(new ElectronHists(ctx, "ele_commonmod"));
  h_muon_commonmod.reset(new MuonHists(ctx, "muon_commonmod"));
  h_topjets_commonmod.reset(new TopJetHists(ctx, "topjets_commonmod"));
  h_Wtopjets_commonmod.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_commonmod"));
  h_jets_commonmod.reset(new JetHists(ctx, "jets_commonmod"));
  

  h_ele_leptonVeto.reset(new ElectronHists(ctx, "ele_leptonVeto"));
  h_muon_leptonVeto.reset(new MuonHists(ctx, "muon_leptonVeto"));
  h_Wtopjets_leptonVeto.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_leptonVeto"));
  h_leptonVeto.reset(new VBFresonanceToWWHists(ctx, "leptonVeto"));
  
  h_Wtopjets_jec.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_jec"));
  h_jec.reset(new VBFresonanceToWWHists(ctx, "jec"));
  
  h_Wtopjets_afterSD.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_afterSD"));
  
  h_cleaner.reset(new VBFresonanceToWWHists(ctx, "cleaner"));
  h_Wtopjets_cleaner.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_cleaner"));
  //h_Wtopjets_cleaner.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_cleaner"));
  h_topjets_cleaner.reset(new TopJetHists(ctx, "topjets_cleaner"));
  h_jets_cleaner.reset(new JetHists(ctx, "jets_cleaner"));
  
  h_topjets_2topjetsel.reset(new TopJetHists(ctx, "topjets_2AK8"));
  h_Wtopjets_2topjetsel.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_2AK8"));
  //h_Wtopjets_2topjetsel.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_2AK8"));
  
  h_Wtopjets_noOverlapping.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_noOverlapping"));
  //h_Wtopjets_noOverlapping.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_noOverlapping"));
  h_topjets_noOverlapping.reset(new TopJetHists(ctx, "topjets_noOverlapping"));
  h_jets_noOverlapping.reset(new JetHists(ctx, "jets_noOverlapping"));
  
  h_Wtopjets_noOverlapping_eta.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_noOverlapping_eta"));
  //h_Wtopjets_noOverlapping_eta.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_noOverlapping_eta"));
  h_jets_noOverlapping_eta.reset(new JetHists(ctx, "jets_noOverlapping_eta"));
  
  h_Wtopjets_invM.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_invM"));
  //h_Wtopjets_invM.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_invM"));
  h_topjets_invM.reset(new TopJetHists(ctx, "topjets_invM"));
  
  h_Wtopjets_deta.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_deta"));
  //h_Wtopjets_deta.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_deta"));
  h_topjets_deta.reset(new TopJetHists(ctx, "topjets_deta"));
  
  h_Wtopjets_compare.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_compare"));
  //h_Wtopjets_compare.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_compare"));
  h_topjets_compare.reset(new TopJetHists(ctx, "topjets_compare"));
  h_Dijets_compare.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_compare"));
  h_jets_compare.reset(new JetHists(ctx, "jets_compare"));
  h_compare.reset(new VBFresonanceToWWHists(ctx, "compare"));
  h_event_compare.reset(new EventHists(ctx, "event_compare"));
 
  /*
  h_Wtopjets_compareSD.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_compareSD"));
  
  
  h_Wtopjets_VVMass.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VVMass"));
  h_topjets_VVMass.reset(new TopJetHists(ctx, "topjets_VVMass"));
  h_Dijets_VVMass.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VVMass"));
  h_jets_VVMass.reset(new JetHists(ctx, "jets_VVMass"));
  h_VVMass.reset(new VBFresonanceToWWHists(ctx, "VVMass"));
  
  h_Wtopjets_VVMass_tau21HP.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VVMass_tau21HP"));
  h_topjets_VVMass_tau21HP.reset(new TopJetHists(ctx, "topjets_VVMass_tau21HP"));
  h_Dijets_VVMass_tau21HP.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VVMass_tau21HP"));
  h_jets_VVMass_tau21HP.reset(new JetHists(ctx, "jets_VVMass_tau21HP"));
  
  h_Wtopjets_AK4cleaner.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_AK4cleaner"));
  h_jets_AK4cleaner.reset(new JetHists(ctx, "jets_AK4cleaner"));
  
  h_jets_2jetsel.reset(new JetHists(ctx, "jets_2AK4"));
  h_Wtopjets_2jetsel.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_2AK4"));
  */
  //genjet
  
  h_input_genparticle.reset(new VBFresonanceToWWParticleHists(ctx, "GenParticle"));
  h_input_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "input_GenTopJet"));
  h_input_gendijets.reset(new VBFresonanceToWWGenDiJetHists(ctx, "input_GenDiJet"));
  h_input_genjets.reset(new GenJetsHists(ctx, "input_GenJet"));
 
 

  if(PRINT) cout << "hist setup" <<endl;
  
  
  }
  

bool VBFresonanceToWWPreSelectionModule::process(Event & event) {
  // This is the main procedure, called for each event. Typically,
  // do some pre-processing by calling the modules' process method
  // of the modules constructed in the constructor (1).
  // Then, test whether the event passes some selection and -- if yes --
  // use it to fill the histograms (2).
  // Finally, decide whether or not to keep the event in the output (3);
  // this is controlled by the return value of this method: If it
  // returns true, the event is kept; if it returns false, the event
  // is thrown away.

  if(PRINT)    cout << "VBFresonanceToWWPreSelectionModule: Starting to process event (runid, eventid) = (" << event.run << ", " <<", " << event.event << "); weight = " << event.weight << endl;


  /////////////////////////////////////////////////////////// Common Modules   ///////////////////////////////////////////////////////////////////////////////


  //common Modules
  /* pileup SF
     if(!event.isRealData)
     {
     pileup_SF->process(event);
     lumiweight->process(event);
     }
  */
  

  /* not sure if this is needed in 102X
  vector<Jet> IdCriteriaJets = event.get(h_IdCriteriaJets);
  if(PRINT)    cout << " jet id criteria" << endl;

  std::vector<int> skipindex;
  for(unsigned int i=0;i<event.topjets->size();i++){
    if(PRINT)    cout << " event topjet " << i << endl;
    
    int N_Daughters = event.topjets->at(i).numberOfDaughters();
    float nEMFrac = event.topjets->at(i).neutralEmEnergyFraction();
    float nHFrac = event.topjets->at(i).neutralHadronEnergyFraction();
    float chEMFrac = event.topjets->at(i).chargedEmEnergyFraction();
    float chHFrac = event.topjets->at(i).chargedHadronEnergyFraction();
    float chMulti = event.topjets->at(i).chargedMultiplicity();
    
    double deltaR_min=99999.;
    int nearest_index=0;
    for(unsigned int j=0;j<IdCriteriaJets.size();j++){
      if(std::find(skipindex.begin(),skipindex.end(),j) != skipindex.end()) continue;
      double deltaR_candiate=deltaR(IdCriteriaJets.at(j),event.topjets->at(i));
      if(deltaR_candiate<deltaR_min){
	deltaR_min = deltaR_candiate;
	nearest_index=j;
      }
      skipindex.push_back(nearest_index);
      N_Daughters = IdCriteriaJets.at(nearest_index).numberOfDaughters();
      nEMFrac = IdCriteriaJets.at(nearest_index).neutralEmEnergyFraction();
      nHFrac = IdCriteriaJets.at(nearest_index).neutralHadronEnergyFraction();
      chEMFrac = IdCriteriaJets.at(nearest_index).chargedEmEnergyFraction();
      chHFrac =IdCriteriaJets.at(nearest_index).chargedHadronEnergyFraction();
      chMulti = IdCriteriaJets.at(nearest_index).chargedMultiplicity();
    }
    event.topjets->at(i).set_numberOfDaughters(N_Daughters);
    event.topjets->at(i).set_neutralEmEnergyFraction(nEMFrac);
    event.topjets->at(i).set_neutralHadronEnergyFraction(nHFrac);
    event.topjets->at(i).set_chargedEmEnergyFraction(chEMFrac);
    event.topjets->at(i).set_chargedHadronEnergyFraction(chHFrac);
    event.topjets->at(i).set_chargedMultiplicity(chMulti);
  }
  */

  // 1. run all modules other modules.
  if(PRINT)    cout << " starting input hists "  << endl;
  
  h_input->fill(event);
  if(PRINT)    cout << " h input hists "  << endl;
  h_event_input->fill(event);
  h_topjets_input->fill(event);
  h_jets_input->fill(event);
  h_Wtopjets_input->fill(event);
  h_ele_input->fill(event);
  h_muon_input->fill(event);

  //if(isMC){
  //MCWeightModule->process(event);
  //MCPileupReweightModule->process(event);
  //event.weight *= event.get(h_weight_pu);
  //}
  
  bool pass_cm = common->process(event);
 if(!pass_cm) return false;
 //    if(PRINT) 
   Gen_printer->process(event);
 
 h_commonmod->fill(event);
 h_topjets_commonmod->fill(event);
 h_jets_commonmod->fill(event);
 h_Wtopjets_commonmod->fill(event);
 h_ele_commonmod->fill(event);
 h_muon_commonmod->fill(event);
 if(PRINT)    cout << " common modules done "  << endl;
 
 
 
 // 2. test selections and fill histograms
 if(isMC)
   {
     sort_by_pt<GenTopJet>(*event.gentopjets);
     
     h_input_gentopjets->fill(event);
     h_input_gendijets->fill(event);
     h_input_genjets->fill(event);
     h_input_genparticle->fill(event);
   }
 
 bool muon_selection = muon_sel->passes(event);
 if(!muon_selection) return false;
 bool electron_selection = electron_sel->passes(event);
 if(!electron_selection) return false;
 
 h_ele_leptonVeto->fill(event);
 h_muon_leptonVeto->fill(event);

 sort_by_pt<Jet>(*event.jets);
 sort_by_pt<TopJet>(*event.topjets);
 
 h_Wtopjets_leptonVeto->fill(event);
 h_leptonVeto->fill(event);
 if(PRINT)    cout << " leptons done "  << endl;

 // JET CLEANING & JET CORRECTIONS
 if(isMC)
   {
     jet_corrector->process(event);
     topjet_corrector->process(event);
     jet_corrector->correct_met(event);
     if(PRINT)    cout << " jec mc done "  << endl;
     
     /*102X
       if(channel_=="signal")
       {
       //	    cout << "Smearing" << endl;
       jetER_smearer->process(event);
       if(PRINT)    cout << " jer jet mc done "  << endl;
       topjetER_smearer->process(event);
       if(PRINT)    cout << " jer topjet mc done "  << endl;
       }
     */
   }else{
  
   if(PRINT) cout << "data JEC" <<endl;
  
   
  
   //2016
   if(event.run >= runnr_2016_Bb && event.run <= runnr_2016_Be)
     {
       if(PRINT) cout << "2016 B" <<endl;   
       jet_corrector_2016_B->process(event);
       topjet_corrector_2016_B->process(event);
       jet_corrector_2016_B->correct_met(event);
     }
   else if(event.run >= runnr_2016_Cb && event.run <= runnr_2016_Ce)
     {
       jet_corrector_2016_C->process(event);
       topjet_corrector_2016_C->process(event);
       jet_corrector_2016_C->correct_met(event);
     }
   else if(event.run >= runnr_2016_Db && event.run <= runnr_2016_De)
     {
       jet_corrector_2016_D->process(event);
       topjet_corrector_2016_D->process(event);
       jet_corrector_2016_D->correct_met(event);
     }
   else if(event.run >= runnr_2016_Eb && event.run <= runnr_2016_Ee)
     {
       jet_corrector_2016_E->process(event);
       topjet_corrector_2016_E->process(event);
       jet_corrector_2016_E->correct_met(event);
     }
   else if(event.run >= runnr_2016_Fb && event.run <= runnr_2016_Fe)
     {
       jet_corrector_2016_F->process(event);
       topjet_corrector_2016_F->process(event);
       jet_corrector_2016_F->correct_met(event);
     }
   else if(event.run >= runnr_2016_Gb && event.run <= runnr_2016_Ge)
     {
       jet_corrector_2016_G->process(event);
       topjet_corrector_2016_G->process(event);
       jet_corrector_2016_G->correct_met(event);
     }
   else if(event.run >= runnr_2016_Hb && event.run <= runnr_2016_He)
     {
       jet_corrector_2016_H->process(event);
       topjet_corrector_2016_H->process(event);
       jet_corrector_2016_H->correct_met(event);
     }

   //2017
   if(event.run >= runnr_2017_Bb && event.run <= runnr_2017_Be)
     {
       jet_corrector_2017_B->process(event);
       topjet_corrector_2017_B->process(event);
       jet_corrector_2017_B->correct_met(event);
     }
   else if(event.run >= runnr_2017_Cb && event.run <= runnr_2017_Ce)
     {
       jet_corrector_2017_C->process(event);
       topjet_corrector_2017_C->process(event);
       jet_corrector_2017_C->correct_met(event);
     }
   else if(event.run >= runnr_2017_Db && event.run <= runnr_2017_De)
     {
       jet_corrector_2017_D->process(event);
	   topjet_corrector_2017_D->process(event);
	   jet_corrector_2017_D->correct_met(event);
     }
   else if(event.run >= runnr_2017_Eb && event.run <= runnr_2017_Ee)
     {
       jet_corrector_2017_E->process(event);
       topjet_corrector_2017_E->process(event);
       jet_corrector_2017_E->correct_met(event);
     }
   else if(event.run >= runnr_2017_Fb && event.run <= runnr_2017_Fe)
     {
       jet_corrector_2017_F->process(event);
       topjet_corrector_2017_F->process(event);
       jet_corrector_2017_F->correct_met(event);
     }
     
   //2018
   if(event.run >= runnr_2018_Ab && event.run <= runnr_2018_Ae)
     {
       if(PRINT) cout << "2018 A" <<endl;
       jet_corrector_2018_A->process(event);
       topjet_corrector_2018_A->process(event);
       jet_corrector_2018_A->correct_met(event);
     }
   else if(event.run >= runnr_2018_Bb && event.run <= runnr_2018_Be)
     {
       jet_corrector_2018_B->process(event);
       topjet_corrector_2018_B->process(event);
       jet_corrector_2018_B->correct_met(event);
     }
   else if(event.run >= runnr_2018_Cb && event.run <= runnr_2018_Ce)
     {
       jet_corrector_2018_C->process(event);
       topjet_corrector_2018_C->process(event);
       jet_corrector_2018_C->correct_met(event);
     }
   else if(event.run >= runnr_2018_Db && event.run <= runnr_2018_De)
     {
       if(PRINT) cout << "2018 D" <<endl;
       jet_corrector_2018_D->process(event);
       topjet_corrector_2018_D->process(event);
       jet_corrector_2018_D->correct_met(event);
     }
 
   
 }//else on MC = data

sort_by_pt<Jet>(*event.jets);
sort_by_pt<TopJet>(*event.topjets);
h_Wtopjets_jec->fill(event);
h_jec->fill(event);
if(PRINT)    cout << "VBFresonanceToWWPreSelectionModule: jec applied " << endl;

//102X topjet_sdmasscorrector->process(event);
//102X h_Wtopjets_afterSD->fill(event);
//102X if(PRINT)    cout << "VBFresonanceToWWPreSelectionModule: SD corrected " << endl;
//102X topjet_jms->process(event);
//102X if(PRINT)    cout << "VBFresonanceToWWPreSelectionModule: jms " << endl;
//102X h_Wtopjets_afterSDcorrections->fill(event);
//102X if(PRINT)    cout << "VBFresonanceToWWPreSelectionModule: jms " << endl;
//    jetcleaner->process(event);
topjetcleaner->process(event);
//102X ak8pfidfilter->process(event);

h_cleaner->fill(event);
h_Wtopjets_cleaner->fill(event);
h_topjets_cleaner->fill(event);
h_jets_cleaner->fill(event);


bool topjets2_selection = topjet2_sel->passes(event);
if(!topjets2_selection) return false;

h_topjets_2topjetsel->fill(event);
h_Wtopjets_2topjetsel->fill(event);


//Cleaning(removing) AK4 if overlapping with AK8
std::vector<Jet>* AK4Jets(new std::vector<Jet> (*event.jets));
vector<TopJet> Tjets = *event.topjets;
const TopJet & tj_0 = Tjets[0];
const TopJet & tj_1 = Tjets[1];

AK4Jets->clear();
AK4Jets->reserve(event.jets->size());

if(PRINT) std::cout<<"SelectionModule L:858 Size AK4 before cleaning "<<event.jets->size() <<std::endl;
for(const Jet ak4:*event.jets)
{
  bool bdeltaR=true;
  //      for(const TopJet ak8:*event.topjets){
  //	double deltar = deltaR(ak4,ak8);

  double deltar_0 = deltaR(ak4,tj_0);
  double deltar_1 = deltaR(ak4,tj_1);
  if((deltar_0 < 1.2) || (deltar_1 < 1.2)) bdeltaR=false;
  if(PRINT) std::cout<<"SelectionModule L:858 bdeltaR  "<<bdeltaR <<std::endl;
  //    }
  if(bdeltaR) AK4Jets->push_back(ak4);
}

sort_by_pt<Jet>(*AK4Jets);
////put cleaned AK4 jets in event.jet
event.jets->clear();
event.jets->reserve(AK4Jets->size());
for(const auto & j : *AK4Jets) event.jets->push_back(j);
sort_by_pt<Jet>(*event.jets);
sort_by_pt<TopJet>(*event.topjets);
if(PRINT) std::cout<<"SelectionModule L:858 Size topjets Collection "<<event.jets->size() <<std::endl;

/////////////////AK4 cleaning end ////////////////


 h_topjets_noOverlapping->fill(event);
 if(PRINT) std::cout<<"PreSelectionModule h_topjets_noOverlapping " <<std::endl;
 h_Wtopjets_noOverlapping->fill(event);
 if(PRINT) std::cout<<"PreSelectionModule h_Wtopjets_noOverlapping " <<std::endl;

 h_jets_noOverlapping->fill(event);
 if(PRINT) std::cout<<"PreSelectionModule h_jets_noOverlapping " <<std::endl;

//    sort_by_eta<Jet>(*event.jets);
//h_Wtopjets_noOverlapping_eta->fill(event);
//h_jets_noOverlapping_eta->fill(event);




bool invMtopjet_fitselection = invMtopjet_fitsel->passes(event);
if(!invMtopjet_fitselection )
return false;
 if(PRINT) std::cout<<"PreSelectionModule invm sel " <<std::endl;


h_Wtopjets_invM->fill(event);
 if(PRINT) std::cout<<"PreSelectionModule h_Wtopjets_invM " <<std::endl;

h_topjets_invM->fill(event);
if(PRINT) std::cout<<"inv M "<<std::endl;

bool topjets_deta_selection = topjets_deta_sel->passes(event);
if(!topjets_deta_selection)
return false;
if(PRINT) std::cout<<"deta "<<std::endl;

// bool tau21topjet_045_selection = tau21topjet045_sel->passes(event);


h_Wtopjets_compare->fill(event);
if(PRINT) std::cout<<"compare "<<std::endl;
h_topjets_compare->fill(event);
h_Dijets_compare->fill(event);
h_jets_compare->fill(event);
h_compare->fill(event);
h_event_compare->fill(event);



// 3. decide whether or not to keep the current event in the output:
return true;

}


// as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
// make sure the VBFresonanceToWWPreSelectionModule is found by class name. This is ensured by this macro:
UHH2_REGISTER_ANALYSIS_MODULE(VBFresonanceToWWPreSelectionModule)

}


