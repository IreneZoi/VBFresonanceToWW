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
#include <UHH2/common/include/MCWeight.h>
#include "UHH2/common/include/PrintingModules.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/MuonHists.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/GenJetsHists.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWSelections.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWHists.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWGenTopJetHists.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWParticleHists.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWW_WTopJetHists.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWDiJetHists.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWGenDiJetHists.h"

#define PRINT false

using namespace std;
using namespace uhh2;

namespace uhh2examples {

  /** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
   * 
   * This is the central class which calls other AnalysisModules, Hists or Selection classes.
   * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
   */
  class VBFresonanceToWWCHSModule: public AnalysisModule {
  public:
    

    explicit VBFresonanceToWWCHSModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    std::string channel_;
    
    std::unique_ptr<CommonModules> common;

    std::unique_ptr<AnalysisModule> Gen_printer;  

    // std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner;
    // std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner_BCD;
    // std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner_EF;
    // std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner_G;
    // std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner_H;

    std::unique_ptr<JetCorrector> jet_corrector;

    std::unique_ptr<JetCorrector> jet_corrector_BCD;
    std::unique_ptr<JetCorrector> jet_corrector_EF;
    std::unique_ptr<JetCorrector> jet_corrector_G;
    std::unique_ptr<JetCorrector> jet_corrector_H;

    std::unique_ptr<TopJetCorrector> topjet_corrector;
    std::unique_ptr<TopJetCorrector> topjet_corrector_BCD;
    std::unique_ptr<TopJetCorrector> topjet_corrector_EF;
    std::unique_ptr<TopJetCorrector> topjet_corrector_G;
    std::unique_ptr<TopJetCorrector> topjet_corrector_H;

    std::unique_ptr<SubJetCorrector> subjet_corrector;
    std::unique_ptr<SubJetCorrector> subjet_corrector_BCD;
    std::unique_ptr<SubJetCorrector> subjet_corrector_EF;
    std::unique_ptr<SubJetCorrector> subjet_corrector_G;
    std::unique_ptr<SubJetCorrector> subjet_corrector_H;


    std::unique_ptr<JetResolutionSmearer> jetER_smearer;
    std::unique_ptr<GenericJetResolutionSmearer> topjetER_smearer;

    std::unique_ptr<JetCleaner> jetcleaner;
    std::unique_ptr<TopJetCleaner> topjetcleaner;


    // Data/MC scale factors
    std::unique_ptr<uhh2::AnalysisModule> pileup_SF;
    std::unique_ptr<uhh2::AnalysisModule> lumiweight;

    //********** SELECTIONS ***************  
    // declare the Selections to use. Use unique_ptr to ensure automatic call of delete in the destructor,
    // to avoid memory leaks.
    std::unique_ptr<Selection> muon_sel, electron_sel;//lepton veto
    //W jets
    std::unique_ptr<Selection> topjet2_sel;
    std::unique_ptr<Selection> invMtopjet_fitsel;
    std::unique_ptr<Selection> invMtopjet_sel;
    std::unique_ptr<Selection> invMtopjet_SDsel;
    std::unique_ptr<Selection> topjets_deta_sel;
    std::unique_ptr<Selection> VVmass_sel, WWmass_sel;
    std::unique_ptr<Selection> tau21topjet_sel, tau21topjet04_sel, tau21topjet05_sel, tau21topjet06_sel, tau21topjet07_sel;
    //VBF jets
    std::unique_ptr<Selection> jet2_sel;
    std::unique_ptr<Selection> vbfdeta_sel, vbfdeta4_sel, vbfdeta5_sel, vbfdeta6_sel;
    std::unique_ptr<Selection> vbfetasign_sel;
    std::unique_ptr<Selection> vbfeta_sel, vbfeta4_sel, vbfeta5_sel, vbfeta6_sel;
    std::unique_ptr<Selection> invM500_sel, invM1000_sel, invM1500_sel, invM2000_sel;
    std::unique_ptr<Selection> invM2500_sel, invM3000_sel, invM3500_sel, invM4000_sel;
    //    std::unique_ptr<Selection> invM400_sel, invM600_sel, invM800_sel, invM1200_sel;
    //genjet
    //    std::unique_ptr<Selection> eta_topgensel, cleaner_topgensel, gentopjets_deta_sel, invMgentopjet_sel, noOverlapping_genjetsel, vbfdeta_gensel , vbfetasign_gensel, vbfeta_gensel;
  
    //********** HISTOS ***************  
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
    std::unique_ptr<Hists> h_input;
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

    std::unique_ptr<Hists> h_Wtopjets_jec;

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

    std::unique_ptr<Hists> h_Wtopjets_compareSD;

    
    std::unique_ptr<Hists> h_Wtopjets_VVMass;
    std::unique_ptr<Hists> h_topjets_VVMass;
    std::unique_ptr<Hists> h_Dijets_VVMass;
    std::unique_ptr<Hists> h_jets_VVMass;
    std::unique_ptr<Hists> h_VVMass;

    /*    
    std::unique_ptr<Hists> h_Wtopjets_tau21;
    std::unique_ptr<Hists> h_topjets_tau21;

    std::unique_ptr<Hists> h_Wtopjets_tau21_04;
    std::unique_ptr<Hists> h_topjets_tau21_04;

    std::unique_ptr<Hists> h_Wtopjets_tau21_05;
    std::unique_ptr<Hists> h_topjets_tau21_05;

    std::unique_ptr<Hists> h_Wtopjets_tau21_06;
    std::unique_ptr<Hists> h_topjets_tau21_06;

    std::unique_ptr<Hists> h_Wtopjets_tau21_07;
    std::unique_ptr<Hists> h_topjets_tau21_07;
    */

    std::unique_ptr<Hists> h_Wtopjets_WWMass;
    std::unique_ptr<Hists> h_topjets_WWMass;
    
    std::unique_ptr<Hists> h_Wtopjets_tau21WW;
    std::unique_ptr<Hists> h_topjets_tau21WW;
    
    std::unique_ptr<Hists> h_jets_2jetsel;
    std::unique_ptr<Hists> h_Wtopjets_2jetsel;
    
    std::unique_ptr<Hists> h_jets_vbfdeltaeta;
    
    std::unique_ptr<Hists> h_jets_vbfetasign;
    std::unique_ptr<Hists> h_Wtopjets_vbfetasign;
    
    std::unique_ptr<Hists> h_jets_VBF;
    std::unique_ptr<Hists> h_Dijets_VBF;
    std::unique_ptr<Hists> h_Wtopjets_withVBF;
    std::unique_ptr<Hists> h_topjets_withVBF;

    std::unique_ptr<Hists> h_VBF_VVMass;
    std::unique_ptr<Hists> h_jets_VBF_VVMass;
    std::unique_ptr<Hists> h_Dijets_VBF_VVMass;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_VVMass;
    std::unique_ptr<Hists> h_topjets_withVBF_VVMass;

    std::unique_ptr<Hists> h_Dijets_VBF_invM500;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM500;
    
    std::unique_ptr<Hists> h_Dijets_VBF_invM1000;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM1000;
    
    std::unique_ptr<Hists> h_Dijets_VBF_invM1500;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM1500;
    
    std::unique_ptr<Hists> h_Dijets_VBF_invM2000;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM2000;

    std::unique_ptr<Hists> h_Dijets_VBF_invM2500;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM2500;
    
    std::unique_ptr<Hists> h_Dijets_VBF_invM3000;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM3000;
    
    std::unique_ptr<Hists> h_Dijets_VBF_invM3500;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM3500;
    
    std::unique_ptr<Hists> h_Dijets_VBF_invM4000;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM4000;


    /*
    std::unique_ptr<Hists> h_Dijets_VBF_invM400;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM400;
    std::unique_ptr<Hists> h_Dijets_VBF_invM600;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM600;
    std::unique_ptr<Hists> h_Dijets_VBF_invM800;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM800;
    std::unique_ptr<Hists> h_Dijets_VBF_invM1000;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM1000;
    std::unique_ptr<Hists> h_Dijets_VBF_invM1200;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM1200;
    */

    /*
    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_deta4;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_deta4;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_deta5;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_deta5;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_deta6;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_deta6;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_04;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_04;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_04_deta4;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_04_deta4;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_04_deta5;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_04_deta5;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_04_deta6;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_04_deta6;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_05;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_05;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_05_deta4;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_05_deta4;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_05_deta5;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_05_deta5;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_05_deta6;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_05_deta6;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_06;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_06;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_06_deta4;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_06_deta4;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_06_deta5;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_06_deta5;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_06_deta6;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_06_deta6;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_07;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_07;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_07_deta4;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_07_deta4;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_07_deta5;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_07_deta5;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21_07_deta6;
    std::unique_ptr<Hists> h_Dijets_VBF_tau21_07_deta6;
    */
    
    /*
    std::unique_ptr<Hists> h_Dijets_VBF_invM500;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM500;
    
    std::unique_ptr<Hists> h_Dijets_VBF_invM1000;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM1000;
    
    std::unique_ptr<Hists> h_Dijets_VBF_invM1500;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM1500;
    
    std::unique_ptr<Hists> h_Dijets_VBF_invM2000;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM2000;
    */

    std::unique_ptr<Hists> h_Wtopjets_withVBF_WWMass;
    std::unique_ptr<Hists> h_topjets_withVBF_WWMass;
    
    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21WW;
    std::unique_ptr<Hists> h_topjets_withVBF_tau21WW;
    
    std::unique_ptr<Hists> h_input_gentopjets;
    std::unique_ptr<Hists> h_input_gendijets;
    std::unique_ptr<Hists> h_input_genjets;
    std::unique_ptr<Hists> h_input_genparticle;
    // std::unique_ptr<Hists> h_eta_gentopjets;
    // std::unique_ptr<Hists> h_cleaner_gentopjets;
    // std::unique_ptr<Hists> h_Wgentopjets;
    // std::unique_ptr<Hists> h_Wgentopjets_invM;
    // std::unique_ptr<Hists> h_cleaner_genjets;
    // std::unique_ptr<Hists> h_vbfdeltaeta_genjets;
    // std::unique_ptr<Hists> h_vbfW_genjets;
    // std::unique_ptr<Hists> h_vbfeta_genjets;
    // std::unique_ptr<Hists> h_Wgentopjets_VBF;
    // std::unique_ptr<Hists> h_vbfetasign_genjets;    

    const int runnr_BCD = 276811;
    const int runnr_EF = 278802;
    const int runnr_G = 280385;

    bool isMC;

    MuonId     MuId;
    ElectronId EleId;

  };


  VBFresonanceToWWCHSModule::VBFresonanceToWWCHSModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.
    
    cout << "Hello World from VBFresonanceToWWCHSModule!" << endl;

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


    MuId  = AndId<Muon>(MuonIDTight(), PtEtaCut(30., 2.4));
    EleId = AndId<Electron>(ElectronID_HEEP_RunII_25ns, PtEtaCut(35., 2.5));
    //EleId = AndId<Electron>(ElectronID_Spring16_tight_noIso, PtEtaCut(20., 5.));


    common.reset(new CommonModules());
    // TODO: configure common here, e.g. by 
    // calling common->set_*_id or common->disable_*
    

    //    common->disable_mcpileupreweight(); //irene                                                                                                                                                      
    common->disable_jersmear(); //irene
    common->disable_jec(); //irene       
    //    common->disable_metfilters(); //irene                                                                                           
    if(PRINT) cout << "common" <<endl;
    //    common->set_jet_id(PtEtaCut(30.0, 2.4)); 


    // TopJet correctors
    std::vector<std::string> JEC_AK4, JEC_AK8,JEC_AK4_BCD,JEC_AK4_EF,JEC_AK4_G,JEC_AK4_H,JEC_AK8_BCD,JEC_AK8_EF,JEC_AK8_G,JEC_AK8_H;
    if(isMC)
      {
	JEC_AK4 = JERFiles::Summer16_23Sep2016_V4_L123_AK4PFchs_MC;
	//	JEC_AK4 = JERFiles::Summer16_23Sep2016_V4_L123_AK4PFPuppi_MC;
	JEC_AK8 = JERFiles::Summer16_23Sep2016_V4_L123_AK8PFPuppi_MC;
      }
    else
      {
	JEC_AK4_BCD =  JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK4PFchs_DATA;
	JEC_AK4_EF = JERFiles::Summer16_23Sep2016_V4_EF_L123_AK4PFchs_DATA;
	JEC_AK4_G =  JERFiles::Summer16_23Sep2016_V4_G_L123_AK4PFchs_DATA;
	JEC_AK4_H =  JERFiles::Summer16_23Sep2016_V4_H_L123_AK4PFchs_DATA;	
	// JEC_AK4_BCD =  JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK4PFPuppi_DATA;
	// JEC_AK4_EF = JERFiles::Summer16_23Sep2016_V4_EF_L123_AK4PFPuppi_DATA;
	// JEC_AK4_G =  JERFiles::Summer16_23Sep2016_V4_G_L123_AK4PFPuppi_DATA;
	// JEC_AK4_H =  JERFiles::Summer16_23Sep2016_V4_H_L123_AK4PFPuppi_DATA;
	
	JEC_AK8_BCD =  JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK8PFPuppi_DATA;
	JEC_AK8_EF =  JERFiles::Summer16_23Sep2016_V4_EF_L123_AK8PFPuppi_DATA;
	JEC_AK8_G =  JERFiles::Summer16_23Sep2016_V4_G_L123_AK8PFPuppi_DATA;
	JEC_AK8_H =  JERFiles::Summer16_23Sep2016_V4_H_L123_AK8PFPuppi_DATA;
      }

    if(isMC)
      { 
	// jetlepton_cleaner.reset(new JetLeptonCleaner(ctx,JEC_AK4));
	// jetlepton_cleaner->set_drmax(.4);      
	jet_corrector.reset(new JetCorrector(ctx, JEC_AK4));
	topjet_corrector.reset(new TopJetCorrector(ctx, JEC_AK8));
	subjet_corrector.reset(new SubJetCorrector(ctx,JEC_AK4));
	if(channel_=="signal")
	  {
	    jetER_smearer.reset(new JetResolutionSmearer(ctx));
	    //	   	    topjetER_smearer.reset(new GenericJetResolutionSmearer(ctx,"topjets","gentopjets"));
	    topjetER_smearer.reset(new GenericJetResolutionSmearer(ctx,"topjets","gentopjets",true,JERSmearing::SF_13TeV_2016,"Spring16_25nsV10_MC_PtResolution_AK8PFPuppi.txt"));
	   	    // topjetER_smearer.reset(new GenericJetResolutionSmearer(ctx,"topjets","gentopjets",true,JERSmearing::SF_13TeV_2016,"Spring16_25nsV10_MC_PtResolution_AK8PFchs.txt"));
	  }
      }
    else 
      {
	

	// jetlepton_cleaner_BCD.reset(new JetLeptonCleaner(ctx, JEC_AK4_BCD));
	// jetlepton_cleaner_EF.reset(new JetLeptonCleaner(ctx, JEC_AK4_EF));
	// jetlepton_cleaner_G.reset(new JetLeptonCleaner(ctx,JEC_AK4_G ));
	// jetlepton_cleaner_H.reset(new JetLeptonCleaner(ctx,JEC_AK4_H ));
	
	// jetlepton_cleaner_BCD->set_drmax(.4);
	// jetlepton_cleaner_EF->set_drmax(.4);
	// jetlepton_cleaner_G->set_drmax(.4);
	// jetlepton_cleaner_H->set_drmax(.4);
	
	jet_corrector_BCD.reset(new JetCorrector(ctx, JEC_AK4_BCD));
	jet_corrector_EF.reset(new JetCorrector(ctx, JEC_AK4_EF));
	jet_corrector_G.reset(new JetCorrector(ctx,JEC_AK4_G ));
	jet_corrector_H.reset(new JetCorrector(ctx,JEC_AK4_H ));

	topjet_corrector_BCD.reset(new TopJetCorrector(ctx, JEC_AK8_BCD));
	topjet_corrector_EF.reset(new TopJetCorrector(ctx, JEC_AK8_EF));
	topjet_corrector_G.reset(new TopJetCorrector(ctx,JEC_AK8_G ));
	topjet_corrector_H.reset(new TopJetCorrector(ctx,JEC_AK8_H ));
	
	subjet_corrector_BCD.reset(new SubJetCorrector(ctx, JEC_AK4_BCD));
	subjet_corrector_EF.reset(new SubJetCorrector(ctx, JEC_AK4_EF));
	subjet_corrector_G.reset(new SubJetCorrector(ctx,JEC_AK4_G ));
	subjet_corrector_H.reset(new SubJetCorrector(ctx,JEC_AK4_H ));

      }


    //    jetcleaner.reset(new JetCleaner(ctx, 20.0, 5)); 
    jetcleaner.reset(new JetCleaner(ctx, 30.0, 5)); 
    //    topjetcleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(200., 2.4))));
    topjetcleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(200., 2.5))));
    
    if(PRINT) cout << "cleaners" <<endl;
    



    common->init(ctx);

    // note that the JetCleaner is only kept for the sake of example;
    // instead of constructing a jetcleaner explicitly,
    // the cleaning can also be achieved with less code via CommonModules with:
    // common->set_jet_id(PtEtaCut(30.0, 2.4));
    // before the 'common->init(ctx)' line.
    
    // 2. set up selections ***

    //    njet_sel.reset(new NJetSelection(2)); // see common/include/NSelections.h
    muon_sel.reset(new MuonVeto(0.8,MuId)); // see VBFresonanceToWWSelections
    electron_sel.reset(new ElectronVeto(0.8,EleId)); // see VBFresonanceToWWSelections

    //    topjet1_sel.reset(new NTopJetSelection(1)); // at least 1 jets
    topjet2_sel.reset(new NTopJetSelection(2)); // at least 2 jets      
    invMtopjet_fitsel.reset(new invMassTopjetSelection()); // see VBFresonanceToWWSelections
    topjets_deta_sel.reset(new deltaEtaTopjetSelection()); // see VBFresonanceToWWSelections
    invMtopjet_sel.reset(new invMassTopjetSelection(1070.0f)); // see VBFresonanceToWWSelections
    invMtopjet_SDsel.reset(new invMassTopjetSelection(1080.0f)); // see VBFresonanceToWWSelections
    VVmass_sel.reset(new VVMassTopjetSelection());// see VBFresonanceToWWSelections
    WWmass_sel.reset(new VVMassTopjetSelection(65.0f,85.0f));// see VBFresonanceToWWSelections
    tau21topjet_sel.reset(new nSubjTopjetSelection()); // see VBFresonanceToWWSelections
    tau21topjet04_sel.reset(new nSubjTopjetSelection(0.4f)); // see VBFresonanceToWWSelections
    tau21topjet05_sel.reset(new nSubjTopjetSelection(0.5f)); // see VBFresonanceToWWSelections
    tau21topjet06_sel.reset(new nSubjTopjetSelection(0.6f)); // see VBFresonanceToWWSelections
    tau21topjet07_sel.reset(new nSubjTopjetSelection(0.7f)); // see VBFresonanceToWWSelections

    //    jet1_sel.reset(new NJetSelection(1)); // at least 1 jets      
    jet2_sel.reset(new NJetSelection(2)); // at least 2 jets      
    vbfdeta_sel.reset(new VBFdeltaEtajetSelection()); // see VBFresonanceToWWSelections
    vbfetasign_sel.reset(new VBFEtaSignjetSelection()); // see VBFresonanceToWWSelections
    vbfeta_sel.reset(new VBFEtajetSelection()); // see VBFresonanceToWWSelections
    vbfeta4_sel.reset(new VBFEtajetSelection(4.0f)); // see VBFresonanceToWWSelections
    vbfeta5_sel.reset(new VBFEtajetSelection(5.0f)); // see VBFresonanceToWWSelections
    vbfeta6_sel.reset(new VBFEtajetSelection(6.0f)); // see VBFresonanceToWWSelections
    invM500_sel.reset(new invMassVBFjetSelection()); // see VBFresonanceToWWSelections
    invM1000_sel.reset(new invMassVBFjetSelection(1000.0f)); // see VBFresonanceToWWSelections
    invM1500_sel.reset(new invMassVBFjetSelection(1500.0f)); // see VBFresonanceToWWSelections
    invM2000_sel.reset(new invMassVBFjetSelection(2000.0f)); // see VBFresonanceToWWSelections
    invM2500_sel.reset(new invMassVBFjetSelection(2500.0f)); // see VBFresonanceToWWSelections
    invM3000_sel.reset(new invMassVBFjetSelection(3000.0f)); // see VBFresonanceToWWSelections
    invM3500_sel.reset(new invMassVBFjetSelection(3500.0f)); // see VBFresonanceToWWSelections
    invM4000_sel.reset(new invMassVBFjetSelection(4000.0f)); // see VBFresonanceToWWSelections
    // invM400_sel.reset(new invMassVBFjetSelection(400.0f)); // see VBFresonanceToWWSelections
    // invM600_sel.reset(new invMassVBFjetSelection(600.0f)); // see VBFresonanceToWWSelections
    // invM800_sel.reset(new invMassVBFjetSelection(800.0f)); // see VBFresonanceToWWSelections
    // invM1200_sel.reset(new invMassVBFjetSelection(1200.0f)); // see VBFresonanceToWWSelections

    // noOverlapping_genjetsel.reset(new deltaRGenTopjetSelection()); // see VBFresonanceToWWSelections
    // eta_topgensel.reset(new EtaGenTopjetSelection()); // see VBFresonanceToWWSelections
    // cleaner_topgensel.reset(new PtGenTopjetSelection()); // see VBFresonanceToWWSelections
    // vbfdeta_gensel.reset(new VBFdeltaEtaGenjetSelection()); // see VBFresonanceToWWSelections
    // vbfetasign_gensel.reset(new VBFEtaSignGenjetSelection()); // see VBFresonanceToWWSelections
    // vbfeta_gensel.reset(new VBFEtaGenjetSelection()); // see VBFresonanceToWWSelections
    // gentopjets_deta_sel.reset(new deltaEtaGenTopjetSelection()); // see VBFresonanceToWWSelections
    // invMgentopjet_sel.reset(new invMassGenTopjetSelection()); // see VBFresonanceToWWSelections

    if(PRINT) cout << "reset sel" <<endl;


    // 3. Set up Hists classes:
    h_input.reset(new VBFresonanceToWWHists(ctx, "input"));
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

    h_Wtopjets_jec.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_jec"));

    h_cleaner.reset(new VBFresonanceToWWHists(ctx, "cleaner"));
    h_Wtopjets_cleaner.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_cleaner"));
    h_topjets_cleaner.reset(new TopJetHists(ctx, "topjets_cleaner"));
    h_jets_cleaner.reset(new JetHists(ctx, "jets_cleaner"));

    h_topjets_2topjetsel.reset(new TopJetHists(ctx, "topjets_2AK8"));
    h_Wtopjets_2topjetsel.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_2AK8"));

    h_Wtopjets_noOverlapping.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_noOverlapping"));
    h_topjets_noOverlapping.reset(new TopJetHists(ctx, "topjets_noOverlapping"));
    h_jets_noOverlapping.reset(new JetHists(ctx, "jets_noOverlapping"));

    h_Wtopjets_noOverlapping_eta.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_noOverlapping_eta"));
    h_jets_noOverlapping_eta.reset(new JetHists(ctx, "jets_noOverlapping_eta"));

    h_Wtopjets_invM.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_invM"));
    h_topjets_invM.reset(new TopJetHists(ctx, "topjets_invM"));

    h_Wtopjets_deta.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_deta"));
    h_topjets_deta.reset(new TopJetHists(ctx, "topjets_deta"));

    h_Wtopjets_compare.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_compare"));
    h_topjets_compare.reset(new TopJetHists(ctx, "topjets_compare"));
    h_Dijets_compare.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_compare"));
    h_jets_compare.reset(new JetHists(ctx, "jets_compare"));
    h_compare.reset(new VBFresonanceToWWHists(ctx, "compare"));

    h_Wtopjets_compareSD.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_compareSD"));


    h_Wtopjets_VVMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VVMass"));
    h_topjets_VVMass.reset(new TopJetHists(ctx, "topjets_VVMass"));
    h_Dijets_VVMass.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VVMass"));
    h_jets_VVMass.reset(new JetHists(ctx, "jets_VVMass"));
    h_VVMass.reset(new VBFresonanceToWWHists(ctx, "VVMass"));
    /*
    h_Wtopjets_tau21.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_tau21"));
    h_topjets_tau21.reset(new TopJetHists(ctx, "topjets_tau21"));

    h_Wtopjets_tau21_04.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_tau21_04"));
    h_topjets_tau21_04.reset(new TopJetHists(ctx, "topjets_tau21_04"));

    h_Wtopjets_tau21_05.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_tau21_05"));
    h_topjets_tau21_05.reset(new TopJetHists(ctx, "topjets_tau21_05"));

    h_Wtopjets_tau21_06.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_tau21_06"));
    h_topjets_tau21_06.reset(new TopJetHists(ctx, "topjets_tau21_06"));

    h_Wtopjets_tau21_07.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_tau21_07"));
    h_topjets_tau21_07.reset(new TopJetHists(ctx, "topjets_tau21_07"));
    */
    h_Wtopjets_WWMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_WWMass"));
    h_topjets_WWMass.reset(new TopJetHists(ctx, "topjets_WWMass"));

    h_Wtopjets_tau21WW.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_tau21WW"));
    h_topjets_tau21WW.reset(new TopJetHists(ctx, "topjets_tau21WW"));

    h_jets_2jetsel.reset(new JetHists(ctx, "jets_2AK4"));
    h_Wtopjets_2jetsel.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_2AK4"));

    h_jets_vbfdeltaeta.reset(new JetHists(ctx, "jets_vbfdeltaeta"));

    h_jets_vbfetasign.reset(new JetHists(ctx, "jets_vbfetasign"));
    h_Wtopjets_vbfetasign.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_vbfetasign"));

    // h_Dijets_VBF.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF"));
    // h_jets_VBF.reset(new JetHists(ctx, "jets_VBF"));
    // h_Wtopjets_withVBF.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF"));
    // h_topjets_withVBF.reset(new TopJetHists(ctx, "topjets_withVBF"));

    h_VBF_VVMass.reset(new VBFresonanceToWWHists(ctx, "VBF_VVMass"));
    h_Dijets_VBF_VVMass.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_VVMass"));
    h_jets_VBF_VVMass.reset(new JetHists(ctx, "jets_VBF_VVMass"));
    h_Wtopjets_withVBF_VVMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_VVMass"));
    h_topjets_withVBF_VVMass.reset(new TopJetHists(ctx, "topjets_withVBF_VVMass"));

    h_Dijets_VBF_invM500.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_invM500"));
    h_Wtopjets_withVBF_invM500.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VBF_invM500"));

    h_Dijets_VBF_invM1000.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_invM1000"));
    h_Wtopjets_withVBF_invM1000.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VBF_invM1000"));

    h_Dijets_VBF_invM1500.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_invM1500"));
    h_Wtopjets_withVBF_invM1500.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VBF_invM1500"));

    h_Dijets_VBF_invM2000.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_invM2000"));
    h_Wtopjets_withVBF_invM2000.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VBF_invM2000"));

    h_Dijets_VBF_invM2500.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_invM2500"));
    h_Wtopjets_withVBF_invM2500.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VBF_invM2500"));

    h_Dijets_VBF_invM3000.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_invM3000"));
    h_Wtopjets_withVBF_invM3000.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VBF_invM3000"));

    h_Dijets_VBF_invM3500.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_invM3500"));
    h_Wtopjets_withVBF_invM3500.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VBF_invM3500"));

    h_Dijets_VBF_invM4000.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_invM4000"));
    h_Wtopjets_withVBF_invM4000.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VBF_invM4000"));




    /*
    h_Wtopjets_withVBF_tau21.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21"));
    h_Dijets_VBF_tau21.reset(new TopJetHists(ctx, "topjets_withVBF_tau21"));

    h_Wtopjets_withVBF_tau21_deta4.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_deta4"));
    h_Dijets_VBF_tau21_deta4.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_deta4"));

    h_Wtopjets_withVBF_tau21_deta5.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_deta5"));
    h_Dijets_VBF_tau21_deta5.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_deta5"));

    h_Wtopjets_withVBF_tau21_deta6.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_deta6"));
    h_Dijets_VBF_tau21_deta6.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_deta6"));

    h_Wtopjets_withVBF_tau21_04.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_04"));
    h_Dijets_VBF_tau21_04.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_04"));

    h_Wtopjets_withVBF_tau21_04_deta4.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_04_deta4"));
    h_Dijets_VBF_tau21_04_deta4.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_04_deta4"));

    h_Wtopjets_withVBF_tau21_04_deta5.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_04_deta5"));
    h_Dijets_VBF_tau21_04_deta5.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_04_deta5"));

    h_Wtopjets_withVBF_tau21_04_deta6.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_04_deta6"));
    h_Dijets_VBF_tau21_04_deta6.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_04_deta6"));

    h_Wtopjets_withVBF_tau21_05.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_05"));
    h_Dijets_VBF_tau21_05.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_05"));

    h_Wtopjets_withVBF_tau21_05_deta4.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_05_deta4"));
    h_Dijets_VBF_tau21_05_deta4.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_05_deta4"));

    h_Wtopjets_withVBF_tau21_05_deta5.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_05_deta5"));
    h_Dijets_VBF_tau21_05_deta5.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_05_deta5"));

    h_Wtopjets_withVBF_tau21_05_deta6.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_05_deta6"));
    h_Dijets_VBF_tau21_05_deta6.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_05_deta6"));

    h_Wtopjets_withVBF_tau21_06.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_06"));
    h_Dijets_VBF_tau21_06.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_06"));

    h_Wtopjets_withVBF_tau21_06_deta4.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_06_deta4"));
    h_Dijets_VBF_tau21_06_deta4.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_06_deta4"));

    h_Wtopjets_withVBF_tau21_06_deta5.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_06_deta5"));
    h_Dijets_VBF_tau21_06_deta5.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_06_deta5"));

    h_Wtopjets_withVBF_tau21_06_deta6.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_06_deta6"));
    h_Dijets_VBF_tau21_06_deta6.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_06_deta6"));

    h_Wtopjets_withVBF_tau21_07.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_07"));
    h_Dijets_VBF_tau21_07.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_07"));

    h_Wtopjets_withVBF_tau21_07_deta4.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_07_deta4"));
    h_Dijets_VBF_tau21_07_deta4.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_07_deta4"));

    h_Wtopjets_withVBF_tau21_07_deta5.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_07_deta5"));
    h_Dijets_VBF_tau21_07_deta5.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_07_deta5"));

    h_Wtopjets_withVBF_tau21_07_deta6.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21_07_deta6"));
    h_Dijets_VBF_tau21_07_deta6.reset(new TopJetHists(ctx, "topjets_withVBF_tau21_07_deta6"));
    */

    h_Wtopjets_withVBF_WWMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_WWmass"));
    h_topjets_withVBF_WWMass.reset(new TopJetHists(ctx, "topjets_withVBF_WWmass"));

    h_Wtopjets_withVBF_tau21WW.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_tau21WW"));
    h_topjets_withVBF_tau21WW.reset(new TopJetHists(ctx, "topjets_withVBF_tau21WW"));

    //genjet

    h_input_genparticle.reset(new VBFresonanceToWWParticleHists(ctx, "GenParticle"));
    h_input_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "input_GenTopJet"));
    h_input_gendijets.reset(new VBFresonanceToWWGenDiJetHists(ctx, "input_GenDiJet"));
    h_input_genjets.reset(new GenJetsHists(ctx, "input_GenJet"));
    // h_eta_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "eta_GenTopJet"));
    // h_cleaner_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "cleaner_GenTopJet"));
    // h_cleaner_genjets.reset(new GenJetsHists(ctx, "cleaner_GenJet"));
    // h_Wgentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "deta_GenTopJet"));
    // h_Wgentopjets_invM.reset(new VBFresonanceToWWGenTopJetHists(ctx, "invM_GenTopJet"));
    // h_Wgentopjets_VBF.reset(new VBFresonanceToWWGenTopJetHists(ctx, "VBF_GenTopJet"));
    // h_vbfdeltaeta_genjets.reset(new GenJetsHists(ctx, "vbfdeltaeta_GenJet"));
    // h_vbfetasign_genjets.reset(new GenJetsHists(ctx, "vbfetasign_GenJet"));
    // h_vbfeta_genjets.reset(new GenJetsHists(ctx, "vbfeta_GenJet"));
    // h_vbfW_genjets.reset(new GenJetsHists(ctx, "vbfW_GenJet"));



    if(PRINT) cout << "hist setup" <<endl;


  }


  bool VBFresonanceToWWCHSModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.
    
    if(PRINT)    cout << "VBFresonanceToWWCHSModule: Starting to process event (runid, eventid) = (" << event.run << ", " <<", " << event.event << "); weight = " << event.weight << endl;
    

    /////////////////////////////////////////////////////////// Common Modules   ///////////////////////////////////////////////////////////////////////////////


    //common Modules
    /* pileup SF
    if(!event.isRealData)
      { 
		pileup_SF->process(event);
		lumiweight->process(event);
      }
    */
    // keep Jets *before cleaning* to store them in the ntuple if event is accepted   
    std::unique_ptr< std::vector<Jet> >    uncleaned_jets   (new std::vector<Jet>   (*event.jets));   
    std::unique_ptr< std::vector<TopJet> > uncleaned_topjets(new std::vector<TopJet>(*event.topjets));

    // 1. run all modules other modules.

    h_input->fill(event);
    h_topjets_input->fill(event);
    h_jets_input->fill(event);
    h_Wtopjets_input->fill(event);
    h_ele_input->fill(event);
    h_muon_input->fill(event);


    bool pass_cm = common->process(event);
    if(!pass_cm) return false; 
    //    if(PRINT)     Gen_printer->process(event);

    h_commonmod->fill(event);
    h_topjets_commonmod->fill(event);
    h_jets_commonmod->fill(event);
    h_Wtopjets_commonmod->fill(event);
    h_ele_commonmod->fill(event);
    h_muon_commonmod->fill(event);

    
    // 2. test selections and fill histograms
    if(isMC)
      {
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

    // JET CLEANING
    if(isMC)
      {
	// jetlepton_cleaner->process(event);
	// jet_corrector->process(event);
	topjet_corrector->process(event);
	subjet_corrector->process(event);
	jet_corrector->correct_met(event);
	if(channel_=="signal")
	  {
	    //	    cout << "Smearing" << endl;
	    jetER_smearer->process(event);
	    topjetER_smearer->process(event);
	  }
      }else{
      if(event.run <= runnr_BCD)  {       
	//	jetlepton_cleaner_BCD->process(event);    
	jet_corrector_BCD->process(event);
	topjet_corrector_BCD->process(event);
	subjet_corrector_BCD->process(event);
	jet_corrector_BCD->correct_met(event);
     }
      else if(event.run < runnr_EF){       
	//	jetlepton_cleaner_EF->process(event);   
	jet_corrector_EF->process(event);
	topjet_corrector_EF->process(event);
	subjet_corrector_EF->process(event);
	jet_corrector_EF->correct_met(event);
      } 
      else if(event.run <= runnr_G) {       
	//	jetlepton_cleaner_G->process(event);   
	jet_corrector_G->process(event);
	topjet_corrector_G->process(event);
	subjet_corrector_G->process(event);
	jet_corrector_G->correct_met(event);
      } 
      else if(event.run > runnr_G) {       
	//	jetlepton_cleaner_H->process(event); 
	jet_corrector_H->process(event);
	topjet_corrector_H->process(event);
	subjet_corrector_H->process(event);
	jet_corrector_H->correct_met(event);
      } 
    }

    sort_by_pt<Jet>(*event.jets);
    sort_by_pt<TopJet>(*event.topjets);

    h_Wtopjets_jec->fill(event);

    jetcleaner->process(event);
    topjetcleaner->process(event);

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
    h_Wtopjets_noOverlapping->fill(event);
    h_jets_noOverlapping->fill(event);

    // sort_by_eta<Jet>(*event.jets);
    // h_Wtopjets_noOverlapping_eta->fill(event);
    // h_jets_noOverlapping_eta->fill(event);


    //genjet
    // if(isMC)
    //   {
	
    // 	bool noOverlapping_genjetselection = noOverlapping_genjetsel->passes(event);
    // 	bool eta_gentopjetselection = eta_topgensel->passes(event);
    // 	if(eta_gentopjetselection)
    // 	  //      if(eta_gentopjetselection && noOverlapping_genjetselection)
    // 	  {
    // 	    h_eta_gentopjets->fill(event);
    // 	  }
    // 	bool cleaner_gentopjetselection = cleaner_topgensel->passes(event);
    // 	//      if(eta_gentopjetselection && cleaner_gentopjetselection && noOverlapping_genjetselection)
    // 	if(eta_gentopjetselection  && cleaner_gentopjetselection ) 
    // 	  {
    // 	    h_cleaner_gentopjets->fill(event);
    // 	  }
    // 	bool gentopjets_deta_selection = gentopjets_deta_sel->passes(event);
    // 	if(gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection)
    // 	  //      if(gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection && noOverlapping_genjetselection)
    // 	  {
    // 	    h_Wgentopjets->fill(event);
    // 	  }
    // 	bool invMgentopjet_selection = invMgentopjet_sel->passes(event);
    // 	//      if(invMgentopjet_selection && gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection && noOverlapping_genjetselection)
    // 	if(invMgentopjet_selection && gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection)
    // 	  {
    // 	    h_Wgentopjets_invM->fill(event);
    // 	    h_cleaner_genjets->fill(event);
	    
    // 	  }
    // 	bool vbfdeta_genselection = vbfdeta_gensel->passes(event);
    // 	if(vbfdeta_genselection){
    // 	  h_vbfdeltaeta_genjets->fill(event);
    // 	}
    // 	bool vbfetasign_genselection = vbfetasign_gensel->passes(event);
    // 	if(vbfetasign_genselection)// && invMgentopjet_selection && gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection && noOverlapping_genjetselection)
    // 	  {
    // 	    h_vbfetasign_genjets->fill(event);
    // 	  }
    // 	bool vbfeta_genselection = vbfeta_gensel->passes(event);
    // 	if(vbfeta_genselection && invMgentopjet_selection && gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection)
    // 	  //      if(vbfeta_genselection && invMgentopjet_selection && gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection && noOverlapping_genjetselection)
    // 	  {
    // 	    h_vbfW_genjets->fill(event);
    // 	    //      h_GenDijets->fill(event);
    // 	  }
	
    // 	if(vbfeta_genselection)
    // 	  {
    // 	    h_vbfeta_genjets->fill(event);
    // 	    h_Wgentopjets_VBF->fill(event);	
	    
    // 	  }
	
	
    //   }


    bool invMtopjet_fitselection = invMtopjet_fitsel->passes(event);
    if(!invMtopjet_fitselection )
      return false;

      h_Wtopjets_invM->fill(event);
      h_topjets_invM->fill(event);

    bool topjets_deta_selection = topjets_deta_sel->passes(event);
    if(!topjets_deta_selection)
      return false;
    h_Wtopjets_deta->fill(event);
    h_topjets_deta->fill(event);

    bool invMtopjet_selection = invMtopjet_sel->passes(event);
    bool invMtopjet_SDselection = invMtopjet_SDsel->passes(event);
    bool tau21topjet_selection = tau21topjet_sel->passes(event);
    bool tau21topjet04_selection = tau21topjet04_sel->passes(event);
    bool tau21topjet05_selection = tau21topjet05_sel->passes(event);
    bool tau21topjet06_selection = tau21topjet06_sel->passes(event);
    bool tau21topjet07_selection = tau21topjet07_sel->passes(event);

    if(invMtopjet_selection )
      {
	h_Wtopjets_compare->fill(event);
	h_topjets_compare->fill(event);
	h_Dijets_compare->fill(event);
	h_jets_compare->fill(event);
	h_compare->fill(event);
	if(invMtopjet_SDselection && tau21topjet_selection)
	  h_Wtopjets_compareSD->fill(event);

      }
    bool VVMtopjet_selection = VVmass_sel->passes(event);
    bool WWMtopjet_selection = WWmass_sel->passes(event);

    if(WWMtopjet_selection )
      {
	h_Wtopjets_WWMass->fill(event);
	h_topjets_WWMass->fill(event);
      }
    if(tau21topjet_selection && WWMtopjet_selection)
      {
	h_Wtopjets_tau21WW->fill(event);
	h_topjets_tau21WW->fill(event);
      }
    
    if(!VVMtopjet_selection) return false;
    
    h_Wtopjets_VVMass->fill(event);
    h_topjets_VVMass->fill(event);
    h_Dijets_VVMass->fill(event);
    h_jets_VVMass->fill(event);
    h_VVMass->fill(event);

    /*
    if(tau21topjet_selection)
      {
	h_Wtopjets_tau21->fill(event);
	h_topjets_tau21->fill(event);
      }
    if(tau21topjet04_selection)
      {
	h_Wtopjets_tau21_04->fill(event);
	h_topjets_tau21_04->fill(event);
      }
    if(tau21topjet05_selection)
      {
	h_Wtopjets_tau21_05->fill(event);
	h_topjets_tau21_05->fill(event);
      }
    if(tau21topjet06_selection)
      {
	h_Wtopjets_tau21_06->fill(event);
	h_topjets_tau21_06->fill(event);
      }
    */
     
    // Selections for AK4
    bool jets2_selection = jet2_sel->passes(event);
    if(!jets2_selection) return false;
    
    h_jets_2jetsel->fill(event);
    h_Wtopjets_2jetsel->fill(event);

    // bool vbfdeta_selection = vbfdeta_sel->passes(event);
    // if(vbfdeta_selection){
    //   if(PRINT)      cout << "vbfdeta_selection jets" <<endl;
    //   h_jets_vbfdeltaeta->fill(event);
    //   if(PRINT) cout << "vbfdeta_selection jets" <<endl;
    // }
    
    bool vbfetasign_selection = vbfetasign_sel->passes(event);
    if(!vbfetasign_selection) return false;
    
    h_jets_vbfetasign->fill(event);
    h_Wtopjets_vbfetasign->fill(event);
    if(PRINT) cout << "vbfeta_sign jets" <<endl;
    

    bool vbfeta_selection = vbfeta_sel->passes(event);
    bool vbfeta4_selection = vbfeta4_sel->passes(event);
    bool vbfeta5_selection = vbfeta5_sel->passes(event);
    bool vbfeta6_selection = vbfeta6_sel->passes(event);
    bool invM500jet_selection = invM500_sel->passes(event);
    bool invM1000jet_selection = invM1000_sel->passes(event);
    bool invM1500jet_selection = invM1500_sel->passes(event);
    bool invM2000jet_selection = invM2000_sel->passes(event);
    bool invM2500jet_selection = invM2500_sel->passes(event);
    bool invM3000jet_selection = invM3000_sel->passes(event);
    bool invM3500jet_selection = invM3500_sel->passes(event);
    bool invM4000jet_selection = invM4000_sel->passes(event);

    // if(!vbfeta_selection) return false;
    if(vbfeta_selection)
      {    
	// h_jets_VBF->fill(event);
	// h_Dijets_VBF->fill(event);
	// h_Wtopjets_withVBF->fill(event);
	// h_topjets_withVBF->fill(event);
	
	// if(PRINT) cout << "vbfeta_selection topjets" <<endl;
	
	// if(VVMtopjet_selection)
	//   {
	h_VBF_VVMass->fill(event);
	h_jets_VBF_VVMass->fill(event);
	h_Dijets_VBF_VVMass->fill(event);
	h_Wtopjets_withVBF_VVMass->fill(event);
	h_topjets_withVBF_VVMass->fill(event);

	/*
	if(invM1000jet_selection )
	  {
	    h_Dijets_VBF_invM1000->fill(event);
	    h_Wtopjets_withVBF_invM1000->fill(event);

	    if(WWMtopjet_selection)
	      {
		h_Wtopjets_withVBF_WWMass->fill(event);
		h_topjets_withVBF_WWMass->fill(event);
		if(PRINT) cout << "SD mass fill" <<endl;	
	      }
	    if(tau21topjet_selection && WWMtopjet_selection)
	      {
		h_Wtopjets_withVBF_tau21WW->fill(event);
		h_topjets_withVBF_tau21WW->fill(event);
		if(PRINT) cout << "tau fill" <<endl;
	      }   
    
	    if(PRINT) cout << "jets tau and SD" <<endl;
	    	    
	  }//invM1000
	*/
      }	//VBF VV (VBF delta eta sel)  

    if(!vbfeta_selection) return false;



    if(!invM500jet_selection) return false;
    h_Dijets_VBF_invM500->fill(event);
    h_Wtopjets_withVBF_invM500->fill(event);
    if(!invM1000jet_selection) return false;
    h_Dijets_VBF_invM1000->fill(event);
    h_Wtopjets_withVBF_invM1000->fill(event);
    if(!invM1500jet_selection) return false;
    h_Dijets_VBF_invM1500->fill(event);
    h_Wtopjets_withVBF_invM1500->fill(event);
    if(!invM2000jet_selection) return false;
    h_Dijets_VBF_invM2000->fill(event);
    h_Wtopjets_withVBF_invM2000->fill(event);
    if(!invM2500jet_selection) return false;
    h_Dijets_VBF_invM2500->fill(event);
    h_Wtopjets_withVBF_invM2500->fill(event);
    if(!invM3000jet_selection) return false;
    h_Dijets_VBF_invM3000->fill(event);
    h_Wtopjets_withVBF_invM3000->fill(event);
    if(!invM3500jet_selection) return false;
    h_Dijets_VBF_invM3500->fill(event);
    h_Wtopjets_withVBF_invM3500->fill(event);
    if(!invM4000jet_selection) return false;
    h_Dijets_VBF_invM4000->fill(event);
    h_Wtopjets_withVBF_invM4000->fill(event);


/*
    //deta 3, different tau21
    if(vbfeta_selection && tau21topjet_selection)
      {    
	h_Dijets_VBF_tau21->fill(event);
	h_Wtopjets_withVBF_tau21->fill(event);
      }
    if(vbfeta_selection && tau21topjet04_selection)
      {    
	h_Dijets_VBF_tau21_04->fill(event);
	h_Wtopjets_withVBF_tau21_04->fill(event);
      }
    if(vbfeta_selection && tau21topjet05_selection)
      {    
	h_Dijets_VBF_tau21_05->fill(event);
	h_Wtopjets_withVBF_tau21_05->fill(event);
      }
    if(vbfeta_selection && tau21topjet06_selection)
      {    
	h_Dijets_VBF_tau21_06->fill(event);
	h_Wtopjets_withVBF_tau21_06->fill(event);
      }
    if(vbfeta_selection && tau21topjet07_selection)
      {    
	h_Dijets_VBF_tau21_07->fill(event);
	h_Wtopjets_withVBF_tau21_07->fill(event);
      }

    //deta 4, different tau21
    if(vbfeta4_selection && tau21topjet_selection)
      {    
	h_Dijets_VBF_tau21_deta4->fill(event);
	h_Wtopjets_withVBF_tau21_deta4->fill(event);
      }
    if(vbfeta4_selection && tau21topjet04_selection)
      {    
	h_Dijets_VBF_tau21_04_deta4->fill(event);
	h_Wtopjets_withVBF_tau21_04_deta4->fill(event);
      }
    if(vbfeta4_selection && tau21topjet05_selection)
      {    
	h_Dijets_VBF_tau21_05_deta4->fill(event);
	h_Wtopjets_withVBF_tau21_05_deta4->fill(event);
      }
    if(vbfeta4_selection && tau21topjet06_selection)
      {    
	h_Dijets_VBF_tau21_06_deta4->fill(event);
	h_Wtopjets_withVBF_tau21_06_deta4->fill(event);
      }
    if(vbfeta4_selection && tau21topjet07_selection)
      {    
	h_Dijets_VBF_tau21_07_deta4->fill(event);
	h_Wtopjets_withVBF_tau21_07_deta4->fill(event);
      }

    //deta 5, different tau21
    if(vbfeta5_selection && tau21topjet_selection)
      {    
	h_Dijets_VBF_tau21_deta5->fill(event);
	h_Wtopjets_withVBF_tau21_deta5->fill(event);
      }
    if(vbfeta5_selection && tau21topjet04_selection)
      {    
	h_Dijets_VBF_tau21_04_deta5->fill(event);
	h_Wtopjets_withVBF_tau21_04_deta5->fill(event);
      }
    if(vbfeta5_selection && tau21topjet05_selection)
      {    
	h_Dijets_VBF_tau21_05_deta5->fill(event);
	h_Wtopjets_withVBF_tau21_05_deta5->fill(event);
      }
    if(vbfeta5_selection && tau21topjet06_selection)
      {    
	h_Dijets_VBF_tau21_06_deta5->fill(event);
	h_Wtopjets_withVBF_tau21_06_deta5->fill(event);
      }
    if(vbfeta5_selection && tau21topjet07_selection)
      {    
	h_Dijets_VBF_tau21_07_deta5->fill(event);
	h_Wtopjets_withVBF_tau21_07_deta5->fill(event);
      }

    //deta 6, different tau21
    if(vbfeta6_selection && tau21topjet_selection)
      {    
	h_Dijets_VBF_tau21_deta6->fill(event);
	h_Wtopjets_withVBF_tau21_deta6->fill(event);
      }
    if(vbfeta6_selection && tau21topjet04_selection)
      {    
	h_Dijets_VBF_tau21_04_deta6->fill(event);
	h_Wtopjets_withVBF_tau21_04_deta6->fill(event);
      }
    if(vbfeta6_selection && tau21topjet05_selection)
      {    
	h_Dijets_VBF_tau21_05_deta6->fill(event);
	h_Wtopjets_withVBF_tau21_05_deta6->fill(event);
      }
    if(vbfeta6_selection && tau21topjet06_selection)
      {    
	h_Dijets_VBF_tau21_06_deta6->fill(event);
	h_Wtopjets_withVBF_tau21_06_deta6->fill(event);
      }
    if(vbfeta6_selection && tau21topjet07_selection)
      {    
	h_Dijets_VBF_tau21_07_deta6->fill(event);
	h_Wtopjets_withVBF_tau21_07_deta6->fill(event);
      }

*/




	  // bool invM500jet_selection = invM500_sel->passes(event);
	  // if(invM500jet_selection )
	  //   {
	  //     h_Dijets_VBF_invM500->fill(event);
	  //     h_Wtopjets_withVBF_invM500->fill(event);
	  //   }
	  // bool invM1000jet_selection = invM1000_sel->passes(event);
	  // if(invM1000jet_selection )
	  //   {
	  //     h_Dijets_VBF_invM1000->fill(event);
	  //     h_Wtopjets_withVBF_invM1000->fill(event);
	  //   }
	  // bool invM1500jet_selection = invM1500_sel->passes(event);
	  // if(invM1500jet_selection )
	  //   {
	  //     h_Dijets_VBF_invM1500->fill(event);
	  //     h_Wtopjets_withVBF_invM1500->fill(event);
	  //   }
	  // bool invM2000jet_selection = invM2000_sel->passes(event);
	  // if(invM2000jet_selection )
	  //   {
	  //     h_Dijets_VBF_invM2000->fill(event);
	  //     h_Wtopjets_withVBF_invM2000->fill(event);
	  //   }
	  
	//   if(PRINT) cout << " jets invM" <<endl;
	  
	// }




      



    // store Jets *before cleaning* in the ntuple                                                                                                                                                     
    event.jets->clear();
    event.jets->reserve(uncleaned_jets->size());
    for(const auto & j : *uncleaned_jets) event.jets->push_back(j);
    sort_by_pt<Jet>(*event.jets);
    if(PRINT) cout << "jets clear reserve push" <<endl;
    
    event.topjets->clear();
    event.topjets->reserve(uncleaned_topjets->size());
    for(const auto & j : *uncleaned_topjets) event.topjets->push_back(j);
    sort_by_pt<TopJet>(*event.topjets);
      if(PRINT) cout << "topjets clear reserve push" <<endl;

    // 3. decide whether or not to keep the current event in the output:
    return true;

  }


  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the VBFresonanceToWWCHSModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(VBFresonanceToWWCHSModule)

}
