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

using namespace std;
using namespace uhh2;

namespace uhh2examples {

  /** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
   * 
   * This is the central class which calls other AnalysisModules, Hists or Selection classes.
   * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
   */
  class VBFresonanceToWWAllModule: public AnalysisModule {
  public:
    

    explicit VBFresonanceToWWAllModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    std::string channel_;
    
    Event::Handle<vector<Jet>> h_IdCriteriaJets;
    std::unique_ptr<CommonModules> common;

    std::unique_ptr<AnalysisModule> Gen_printer;  

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

    std::unique_ptr<SoftDropMassCalculator> topjet_sdmasscorrector;

    // std::unique_ptr<SubJetCorrector> subjet_corrector;
    // std::unique_ptr<SubJetCorrector> subjet_corrector_BCD;
    // std::unique_ptr<SubJetCorrector> subjet_corrector_EF;
    // std::unique_ptr<SubJetCorrector> subjet_corrector_G;
    // std::unique_ptr<SubJetCorrector> subjet_corrector_H;


    std::unique_ptr<JetResolutionSmearer> jetER_smearer;
    std::unique_ptr<GenericJetResolutionSmearer> topjetER_smearer;

    std::unique_ptr<JetCleaner> jetcleaner;
    std::unique_ptr<TopJetCleaner> topjetcleaner;

    std::unique_ptr<JetCleaner> ak4pfidfilter;
    std::unique_ptr<TopJetCleaner> ak8pfidfilter;

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
    // std::unique_ptr<Selection> invMtopjet_sel;
    std::unique_ptr<Selection> invMtopjet_SDsel;
    std::unique_ptr<Selection> topjets_deta_sel;
    std::unique_ptr<Selection> VVmass_sel, WWmass_sel;
    std::unique_ptr<Selection> tau21topjetHP_sel;
    //    std::unique_ptr<Selection> tau21topjet045_sel;
    //VBF jets
    std::unique_ptr<Selection> jet2_sel;
    std::unique_ptr<Selection> vbfdeta_sel;
    std::unique_ptr<Selection> vbfetasign_sel;
    std::unique_ptr<Selection> vbfeta_sel;
    std::unique_ptr<Selection> invM800_sel;
    std::unique_ptr<Selection> invM900_sel;
    std::unique_ptr<Selection> invM1000_sel;
  
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

    std::unique_ptr<Hists> h_topjets_afterSD;

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
    
    std::unique_ptr<Hists> h_jets_vbfdeltaeta;
    
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

    std::unique_ptr<Hists> h_Dijets_VBF_invM1000;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM800;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM900;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM1000;

    
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

    JetId AK4PFID;
    TopJetId AK8PFID;
  };


  VBFresonanceToWWAllModule::VBFresonanceToWWAllModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.
    
    cout << "Hello World from VBFresonanceToWWAllModule!" << endl;

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

    MuId  = AndId<Muon>(MuonIDTight(), PtEtaCut(30., 2.4));
    EleId = AndId<Electron>(ElectronID_HEEP_RunII_25ns, PtEtaCut(35., 2.5));
    //EleId = AndId<Electron>(ElectronID_Spring16_tight_noIso, PtEtaCut(20., 5.));


    common.reset(new CommonModules());
    // TODO: configure common here, e.g. by 
    // calling common->set_*_id or common->disable_*
    

    //    common->disable_mcpileupreweight(); //irene                                                                                                                                                      
    common->switch_jetlepcleaner(false);     
    common->disable_jetpfidfilter();
    common->disable_jersmear(); //irene
    common->disable_jec(); //irene  
    //    common->disable_metfilters(); //irene                                                                                           
    if(PRINT) cout << "common" <<endl;
    //    common->set_jet_id(PtEtaCut(30.0, 2.4)); 


    // TopJet correctors
    std::vector<std::string> JEC_AK4, JEC_AK8,JEC_AK4_BCD,JEC_AK4_EF,JEC_AK4_G,JEC_AK4_H,JEC_AK8_BCD,JEC_AK8_EF,JEC_AK8_G,JEC_AK8_H;
    if(isMC)
      {
	JEC_AK4 = JERFiles::Summer16_23Sep2016_V4_L123_AK4PFPuppi_MC;
	JEC_AK8 = JERFiles::Summer16_23Sep2016_V4_L123_AK8PFPuppi_MC;
      }
    else
      {
	JEC_AK4_BCD =  JERFiles::Summer16_23Sep2016_V4_BCD_L123_AK4PFPuppi_DATA;
	JEC_AK4_EF = JERFiles::Summer16_23Sep2016_V4_EF_L123_AK4PFPuppi_DATA;
	JEC_AK4_G =  JERFiles::Summer16_23Sep2016_V4_G_L123_AK4PFPuppi_DATA;
	JEC_AK4_H =  JERFiles::Summer16_23Sep2016_V4_H_L123_AK4PFPuppi_DATA;
	
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
	//	subjet_corrector.reset(new SubJetCorrector(ctx,JEC_AK4));
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
	
	// subjet_corrector_BCD.reset(new SubJetCorrector(ctx, JEC_AK4_BCD));
	// subjet_corrector_EF.reset(new SubJetCorrector(ctx, JEC_AK4_EF));
	// subjet_corrector_G.reset(new SubJetCorrector(ctx,JEC_AK4_G ));
	// subjet_corrector_H.reset(new SubJetCorrector(ctx,JEC_AK4_H ));

      }


    topjet_sdmasscorrector.reset(new SoftDropMassCalculator(ctx, true, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/puppiCorr.root","topjets"));


    //    jetcleaner.reset(new JetCleaner(ctx, 20.0, 5)); 
    jetcleaner.reset(new JetCleaner(ctx, 30.0, 5)); 
    //    topjetcleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(200., 2.4))));
    topjetcleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(200., 2.5))));
    
    AK4PFID=JetPFID(JetPFID::WP_LOOSE_PUPPI);
    AK8PFID=JetPFID(JetPFID::WP_LOOSE_PUPPI);


    ak8pfidfilter.reset(new TopJetCleaner(ctx,AK8PFID));
    ak4pfidfilter.reset(new JetCleaner(ctx,AK4PFID));


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
    //    invMtopjet_sel.reset(new invMassTopjetSelection(1070.0f)); // see VBFresonanceToWWSelections
    invMtopjet_SDsel.reset(new invMassTopjetSelection(1080.0f)); // see VBFresonanceToWWSelections
    VVmass_sel.reset(new VVMassTopjetSelection());// see VBFresonanceToWWSelections
    // WWmass_sel.reset(new VVMassTopjetSelection(65.0f,85.0f));// see VBFresonanceToWWSelections
    tau21topjetHP_sel.reset(new nSubjTopjetSelection(0.f,0.35f)); // see VBFresonanceToWWSelections
    jet2_sel.reset(new NJetSelection(2)); // at least 2 jets      
    vbfdeta_sel.reset(new VBFdeltaEtajetSelection()); // see VBFresonanceToWWSelections
    vbfetasign_sel.reset(new VBFEtaSignjetSelection()); // see VBFresonanceToWWSelections
    vbfeta_sel.reset(new VBFEtajetSelection()); // see VBFresonanceToWWSelections
    invM800_sel.reset(new invMassVBFjetSelection(800.0f)); // see VBFresonanceToWWSelections
    invM900_sel.reset(new invMassVBFjetSelection(900.0f)); // see VBFresonanceToWWSelections
    invM1000_sel.reset(new invMassVBFjetSelection(1000.0f)); // see VBFresonanceToWWSelections
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

    h_Wtopjets_jec.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_jec"));

    h_topjets_afterSD.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_afterSD"));

    h_cleaner.reset(new VBFresonanceToWWHists(ctx, "cleaner"));
    h_Wtopjets_cleaner.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_cleaner"));
    h_topjets_cleaner.reset(new TopJetHists(ctx, "topjets_cleaner"));
    h_jets_cleaner.reset(new JetHists(ctx, "jets_cleaner"));

    h_topjets_2topjetsel.reset(new TopJetHists(ctx, "topjets_2AK8"));
    h_Wtopjets_2topjetsel.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_2AK8"));

    h_Wtopjets_noOverlapping.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_noOverlapping"));
    h_topjets_noOverlapping.reset(new TopJetHists(ctx, "topjets_noOverlapping"));
    h_jets_noOverlapping.reset(new JetHists(ctx, "jets_noOverlapping"));

    h_Wtopjets_noOverlapping_eta.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_noOverlapping_eta"));
    h_jets_noOverlapping_eta.reset(new JetHists(ctx, "jets_noOverlapping_eta"));

    h_Wtopjets_invM.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_invM"));
    h_topjets_invM.reset(new TopJetHists(ctx, "topjets_invM"));

    h_Wtopjets_deta.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_deta"));
    h_topjets_deta.reset(new TopJetHists(ctx, "topjets_deta"));

    h_Wtopjets_compare.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_compare"));
    h_topjets_compare.reset(new TopJetHists(ctx, "topjets_compare"));
    h_Dijets_compare.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_compare"));
    h_jets_compare.reset(new JetHists(ctx, "jets_compare"));
    h_compare.reset(new VBFresonanceToWWHists(ctx, "compare"));
    h_event_compare.reset(new EventHists(ctx, "event_compare"));

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

    h_jets_vbfdeltaeta.reset(new JetHists(ctx, "jets_vbfdeltaeta"));

    h_jets_vbfetasign.reset(new JetHists(ctx, "jets_vbfetasign"));
    h_Wtopjets_vbfetasign.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_vbfetasign"));


    h_VBF_VVMass.reset(new VBFresonanceToWWHists(ctx, "VBF_VVMass"));
    h_Dijets_VBF_VVMass.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_VVMass"));
    h_jets_VBF_VVMass.reset(new JetHists(ctx, "jets_VBF_VVMass"));
    h_Wtopjets_withVBF_VVMass.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_withVBF_VVMass"));
    h_topjets_withVBF_VVMass.reset(new TopJetHists(ctx, "topjets_withVBF_VVMass"));

    h_Dijets_VBF_VVMass_tau21HP.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_VVMass_tau21HP"));
    h_jets_VBF_VVMass_tau21HP.reset(new JetHists(ctx, "jets_VBF_VVMass_tau21HP"));
    h_Wtopjets_withVBF_VVMass_tau21HP.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_withVBF_VVMass_tau21HP"));
    h_topjets_withVBF_VVMass_tau21HP.reset(new TopJetHists(ctx, "topjets_withVBF_VVMass_tau21HP"));



    h_Dijets_VBF_invM1000.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_invM1000"));
    h_Wtopjets_withVBF_invM800.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VBF_invM800"));
    h_Wtopjets_withVBF_invM900.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VBF_invM900"));
    h_Wtopjets_withVBF_invM1000.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VBF_invM1000"));


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


  bool VBFresonanceToWWAllModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.
    
    if(PRINT)    cout << "VBFresonanceToWWAllModule: Starting to process event (runid, eventid) = (" << event.run << ", " <<", " << event.event << "); weight = " << event.weight << endl;
    

    /////////////////////////////////////////////////////////// Common Modules   ///////////////////////////////////////////////////////////////////////////////


    //common Modules
    /* pileup SF
    if(!event.isRealData)
      { 
		pileup_SF->process(event);
		lumiweight->process(event);
      }
    */

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

    // 1. run all modules other modules.

    h_input->fill(event);
    h_event_input->fill(event);
    h_topjets_input->fill(event);
    h_jets_input->fill(event);
    h_Wtopjets_input->fill(event);
    h_ele_input->fill(event);
    h_muon_input->fill(event);


    bool pass_cm = common->process(event);
    if(!pass_cm) return false; 
    //    if(PRINT)    Gen_printer->process(event);

    h_commonmod->fill(event);
    h_topjets_commonmod->fill(event);
    h_jets_commonmod->fill(event);
    h_Wtopjets_commonmod->fill(event);
    h_ele_commonmod->fill(event);
    h_muon_commonmod->fill(event);

    
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

    // JET CLEANING
    if(isMC)
      {
	// jetlepton_cleaner->process(event);
	jet_corrector->process(event);
	topjet_corrector->process(event);
	//	subjet_corrector->process(event);
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

	//	subjet_corrector_BCD->process(event);
	jet_corrector_BCD->correct_met(event);
     }
      else if(event.run < runnr_EF){       
	//	jetlepton_cleaner_EF->process(event);   
	jet_corrector_EF->process(event);
	topjet_corrector_EF->process(event);
	//	subjet_corrector_EF->process(event);
	jet_corrector_EF->correct_met(event);
      } 
      else if(event.run <= runnr_G) {       
	//	jetlepton_cleaner_G->process(event);   
	jet_corrector_G->process(event);
	topjet_corrector_G->process(event);
	//	subjet_corrector_G->process(event);
	jet_corrector_G->correct_met(event);
      } 
      else if(event.run > runnr_G) {       
	//	jetlepton_cleaner_H->process(event); 
	jet_corrector_H->process(event);
	topjet_corrector_H->process(event);
	//	subjet_corrector_H->process(event);
	jet_corrector_H->correct_met(event);
      } 
    }

    sort_by_pt<Jet>(*event.jets);
    sort_by_pt<TopJet>(*event.topjets);
    h_Wtopjets_jec->fill(event);
    if(PRINT)    cout << "VBFresonanceToWWAllModule: jec applied " << endl;

    topjet_sdmasscorrector->process(event);
    h_topjets_afterSD->fill(event);

    //    jetcleaner->process(event);
    topjetcleaner->process(event);   
    ak8pfidfilter->process(event);

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
    //    sort_by_eta<Jet>(*event.jets);
    //h_Wtopjets_noOverlapping_eta->fill(event);
    //h_jets_noOverlapping_eta->fill(event);




    bool invMtopjet_fitselection = invMtopjet_fitsel->passes(event);
    if(!invMtopjet_fitselection )
      return false;

      h_Wtopjets_invM->fill(event);
      h_topjets_invM->fill(event);
    if(PRINT) std::cout<<"inv M "<<std::endl;

    bool topjets_deta_selection = topjets_deta_sel->passes(event);
    if(!topjets_deta_selection)
      return false;
    // h_Wtopjets_deta->fill(event);
    // h_topjets_deta->fill(event);
    if(PRINT) std::cout<<"deta "<<std::endl;

    // bool invMtopjet_selection = invMtopjet_sel->passes(event);
    // if(PRINT) std::cout<<"invM 2 "<<std::endl;

    bool invMtopjet_SDselection = invMtopjet_SDsel->passes(event);
    if(PRINT) std::cout<<"sd "<<std::endl;
    bool tau21topjetHP_selection = tau21topjetHP_sel->passes(event);
    if(PRINT) std::cout<<"tau21 "<<std::endl;
    // bool tau21topjet_045_selection = tau21topjet045_sel->passes(event);

    // if(invMtopjet_selection )
    //   {
    h_Wtopjets_compare->fill(event);
    if(PRINT) std::cout<<"compare "<<std::endl;
    h_topjets_compare->fill(event);
    h_Dijets_compare->fill(event);
    h_jets_compare->fill(event);
    h_compare->fill(event);
    h_event_compare->fill(event);
    if(invMtopjet_SDselection && tau21topjetHP_selection)
      h_Wtopjets_compareSD->fill(event);
    if(PRINT) std::cout<<"compare and sd "<<std::endl;

      // }
    bool VVMtopjet_selection = VVmass_sel->passes(event);
    
    if(!VVMtopjet_selection) return false;
    
    h_Wtopjets_VVMass->fill(event);
    h_topjets_VVMass->fill(event);
    h_Dijets_VVMass->fill(event);
    h_jets_VVMass->fill(event);
    h_VVMass->fill(event);
    if(PRINT) std::cout<<"VV "<<std::endl;

    if(!tau21topjetHP_selection) return false;
    h_Wtopjets_VVMass_tau21HP->fill(event);
    h_topjets_VVMass_tau21HP->fill(event);
    h_Dijets_VVMass_tau21HP->fill(event);
    h_jets_VVMass_tau21HP->fill(event);
	    if(PRINT) std::cout<<"tau21 "<<std::endl;


    jetcleaner->process(event);
    ak4pfidfilter->process(event);
    h_Wtopjets_AK4cleaner->fill(event);
    h_jets_AK4cleaner->fill(event);
     
    // Selections for AK4
    bool jets2_selection = jet2_sel->passes(event);
    if(!jets2_selection) return false;
    
    h_jets_2jetsel->fill(event);
    h_Wtopjets_2jetsel->fill(event);

    
    bool vbfetasign_selection = vbfetasign_sel->passes(event);
    if(!vbfetasign_selection) return false;
    
    h_jets_vbfetasign->fill(event);
    h_Wtopjets_vbfetasign->fill(event);
    if(PRINT) cout << "vbfeta_sign jets" <<endl;
    

    bool vbfeta_selection = vbfeta_sel->passes(event);
    bool invM800jet_selection = invM800_sel->passes(event);
    bool invM900jet_selection = invM900_sel->passes(event);
    bool invM1000jet_selection = invM1000_sel->passes(event);

    if(!vbfeta_selection) return false;

    h_VBF_VVMass->fill(event);
    h_jets_VBF_VVMass->fill(event);
    h_Dijets_VBF_VVMass->fill(event);
    h_Wtopjets_withVBF_VVMass->fill(event);
    h_topjets_withVBF_VVMass->fill(event);
    if(PRINT) std::cout<<"VBF "<<std::endl;

    if(!invM800jet_selection) return false;
    h_Wtopjets_withVBF_invM800->fill(event);
    if(!invM900jet_selection) return false;
    h_Wtopjets_withVBF_invM900->fill(event);


    if(!invM1000jet_selection) return false;
    h_Dijets_VBF_invM1000->fill(event);
    h_Wtopjets_withVBF_invM1000->fill(event);
    if(PRINT) std::cout<<"VBF 1000"<<std::endl;


    // store Jets *before cleaning* in the ntuple                                                                                                                                                     
    // event.jets->clear();
    // event.jets->reserve(uncleaned_jets->size());
    // for(const auto & j : *uncleaned_jets) event.jets->push_back(j);
    // sort_by_pt<Jet>(*event.jets);
    // if(PRINT) cout << "jets clear reserve push" <<endl;
    
    // event.topjets->clear();
    // event.topjets->reserve(uncleaned_topjets->size());
    // for(const auto & j : *uncleaned_topjets) event.topjets->push_back(j);
    // sort_by_pt<TopJet>(*event.topjets);
    //   if(PRINT) cout << "topjets clear reserve push" <<endl;

    // 3. decide whether or not to keep the current event in the output:
    return true;

  }


  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the VBFresonanceToWWAllModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(VBFresonanceToWWAllModule)

}
