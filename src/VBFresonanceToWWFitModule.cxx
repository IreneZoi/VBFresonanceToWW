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
//#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWGenDiJetHists.h"

#define PRINT false

using namespace std;
using namespace uhh2;

namespace uhh2examples {

  /** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
   * 
   * This is the central class which calls other AnalysisModules, Hists or Selection classes.
   * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
   */
  class VBFresonanceToWWFitModule: public AnalysisModule {
  public:
    

    explicit VBFresonanceToWWFitModule(Context & ctx);
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

  
    // declare the Selections to use. Use unique_ptr to ensure automatic call of delete in the destructor,
    // to avoid memory leaks.
    std::unique_ptr<Selection> njet_sel, nmuon_sel,nelectron_sel, dijet_sel, vbfdeta_sel, vbfdeta_gensel, jet1_sel, jet2_sel, topjet1_sel, topjet2_sel, vbfetasign_sel, vbfetasign_gensel, vbfeta_sel, vbfeta_gensel, topjets_deta_sel, SDmass_sel, VVmass_sel, invMtopjet_sel, invMtopjet_fitsel, tau21topjet_sel, invM500_sel, invM1000_sel, invM1500_sel, invM2000_sel;
    std::unique_ptr<Selection> eta_topgensel, cleaner_topgensel, gentopjets_deta_sel, invMgentopjet_sel, noOverlapping_genjetsel;//, jet1_sel, jet2_sel, topjet1_sel, topjet2_sel, vbfetasign_sel, vbfetasign_gensel, vbfeta_sel, vbfeta_gensel, SDmass_sel, invMtopjet_fitsel, tau21topjet_sel, invM500_sel, invM1000_sel, invM1500_sel, invM2000_sel;
  
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
    std::unique_ptr<Hists> h_start_jets, h_ele_input, h_muon_input,  h_ele_removed, h_muon_removed;
    std::unique_ptr<Hists> h_nocuts, h_njet, /*h_dijet,*/ h_input_topjets, h_input_Wtopjets, h_input_jets, h_input_gentopjets, h_input_genjets, h_input_genparticle;
    std::unique_ptr<Hists> h_cleaner, h_cleaner_topjets, h_cleaner_jets, h_eta_gentopjets, h_cleaner_gentopjets, h_cleaner_genjets;
    std::unique_ptr<Hists> h_noOverlapping_topjets, h_noOverlapping_jets;

    std::unique_ptr<Hists> h_2topjetsel_topjets;
    std::unique_ptr<Hists> h_2jetsel_jets;
    std::unique_ptr<Hists> h_jetsel, h_jetsel_topjets, h_jetsel_jets, h_jetsel_gentopjets, h_jetsel_genjets;
    std::unique_ptr<Hists> h_vbfdeltaeta_jets, h_vbfdeltaeta_genjets;
    std::unique_ptr<Hists> h_vbfetasign_jets, h_vbfetasign_genjets;
    std::unique_ptr<Hists> h_vbfeta_jets, h_vbfeta_genjets, h_vbfW_genjets;

    std::unique_ptr<Hists> h_Wgentopjets;
    std::unique_ptr<Hists> h_Wgentopjets_invM;
    std::unique_ptr<Hists> h_Wgentopjets_VBF;

    std::unique_ptr<Hists> h_Wtopjets;
    std::unique_ptr<Hists> h_Dijets;
    //  std::unique_ptr<Hists> h_GenDijets;


    std::unique_ptr<Hists> h_Wtopjets_invM;
    std::unique_ptr<Hists> h_topjets_invM;

     std::unique_ptr<Hists> h_Wtopjets_deta;
     std::unique_ptr<Hists> h_topjets_deta;

    std::unique_ptr<Hists> h_Wtopjets_VVMass;
    std::unique_ptr<Hists> h_topjets_VVMass;

    std::unique_ptr<Hists> h_Wtopjets_SDMass;
    std::unique_ptr<Hists> h_topjets_SDMass;

    std::unique_ptr<Hists> h_Wtopjets_tau21;
    std::unique_ptr<Hists> h_topjets_tau21;

    std::unique_ptr<Hists> h_Wtopjets_invMdeta;
    std::unique_ptr<Hists> h_topjets_invMdeta;
    std::unique_ptr<Hists> h_Dijets_invMdeta;
    std::unique_ptr<Hists> h_jets_invMdeta;
    std::unique_ptr<Hists> h_invMdeta;

    std::unique_ptr<Hists> h_Dijets_VBF;
    std::unique_ptr<Hists> h_jets_VBF;
    std::unique_ptr<Hists> h_Wtopjets_withVBF;
    std::unique_ptr<Hists> h_topjets_withVBF;

    std::unique_ptr<Hists> h_Dijets_VBF_invM500;
    std::unique_ptr<Hists> h_Dijets_VBF_invM1000;
    std::unique_ptr<Hists> h_Dijets_VBF_invM1500;
    std::unique_ptr<Hists> h_Dijets_VBF_invM2000;

    std::unique_ptr<Hists> h_Wtopjets_VBF_invM500;
    std::unique_ptr<Hists> h_Wtopjets_VBF_invM1000;
    std::unique_ptr<Hists> h_Wtopjets_VBF_invM1500;
    std::unique_ptr<Hists> h_Wtopjets_VBF_invM2000;


    std::unique_ptr<Hists> h_Wtopjets_withVBF_SDMass;
    std::unique_ptr<Hists> h_topjets_withVBF_SDMass;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_tau21;
    std::unique_ptr<Hists> h_topjets_withVBF_tau21;

    std::unique_ptr<Hists> h_final;


    const int runnr_BCD = 276811;
    const int runnr_EF = 278802;
    const int runnr_G = 280385;

    bool isMC;

    MuonId     MuId;
    ElectronId EleId;

  };


  VBFresonanceToWWFitModule::VBFresonanceToWWFitModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.
    
    cout << "Hello World from VBFresonanceToWWFitModule!" << endl;

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
    //    EleId = AndId<Electron>(ElectronID_Spring16_tight_noIso, PtEtaCut(20., 5.));


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


    jetcleaner.reset(new JetCleaner(ctx, 30.0, 5)); 
    topjetcleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(200., 2.4))));
    
    if(PRINT) cout << "cleaners" <<endl;
    



    common->init(ctx);

    // note that the JetCleaner is only kept for the sake of example;
    // instead of constructing a jetcleaner explicitly,
    // the cleaning can also be achieved with less code via CommonModules with:
    // common->set_jet_id(PtEtaCut(30.0, 2.4));
    // before the 'common->init(ctx)' line.
    
    // 2. set up selections
    njet_sel.reset(new NJetSelection(2)); // see common/include/NSelections.h
    nmuon_sel.reset(new NMuonSelection(0,0,MuId)); // see common/include/NSelections.h
    nelectron_sel.reset(new NElectronSelection(0,0,EleId)); // see common/include/NSelections.h
    dijet_sel.reset(new DijetSelection()); // see VBFresonanceToWWSelections
    jet2_sel.reset(new NJetSelection(2)); // at least 2 jets      
    jet1_sel.reset(new NJetSelection(1)); // at least 1 jets      
    topjet1_sel.reset(new NTopJetSelection(1)); // at least 1 jets
    topjet2_sel.reset(new NTopJetSelection(2)); // at least 2 jets      
    vbfdeta_sel.reset(new VBFdeltaEtajetSelection()); // see VBFresonanceToWWSelections
    noOverlapping_genjetsel.reset(new deltaRGenTopjetSelection()); // see VBFresonanceToWWSelections
    eta_topgensel.reset(new EtaGenTopjetSelection()); // see VBFresonanceToWWSelections
    cleaner_topgensel.reset(new PtGenTopjetSelection()); // see VBFresonanceToWWSelections
    vbfdeta_gensel.reset(new VBFdeltaEtaGenjetSelection()); // see VBFresonanceToWWSelections
    vbfetasign_sel.reset(new VBFEtaSignjetSelection()); // see VBFresonanceToWWSelections
    vbfetasign_gensel.reset(new VBFEtaSignGenjetSelection()); // see VBFresonanceToWWSelections
    vbfeta_sel.reset(new VBFEtajetSelection()); // see VBFresonanceToWWSelections
    vbfeta_gensel.reset(new VBFEtaGenjetSelection()); // see VBFresonanceToWWSelections
    topjets_deta_sel.reset(new deltaEtaTopjetSelection()); // see VBFresonanceToWWSelections
    gentopjets_deta_sel.reset(new deltaEtaGenTopjetSelection()); // see VBFresonanceToWWSelections
    SDmass_sel.reset(new SDMassTopjetSelection()); // see VBFresonanceToWWSelections
    VVmass_sel.reset(new VVMassTopjetSelection()); // see VBFresonanceToWWSelections
    invMtopjet_fitsel.reset(new invMassTopjetFitSelection()); // see VBFresonanceToWWSelections
    invMtopjet_sel.reset(new invMassTopjetSelection()); // see VBFresonanceToWWSelections
    invMgentopjet_sel.reset(new invMassGenTopjetSelection()); // see VBFresonanceToWWSelections
    tau21topjet_sel.reset(new nSubjTopjetFitSelection()); // see VBFresonanceToWWSelections
    invM500_sel.reset(new invM500VBFjetFitSelection()); // see VBFresonanceToWWSelections
    invM1000_sel.reset(new invM1000VBFjetFitSelection()); // see VBFresonanceToWWSelections
    invM1500_sel.reset(new invM1500VBFjetFitSelection()); // see VBFresonanceToWWSelections
    invM2000_sel.reset(new invM2000VBFjetFitSelection()); // see VBFresonanceToWWSelections

    if(PRINT) cout << "reset sel" <<endl;


    // 3. Set up Hists classes:
    h_start_jets.reset(new JetHists(ctx, "start_Jet"));
    h_ele_input.reset(new ElectronHists(ctx, "ele_input"));
    h_muon_input.reset(new MuonHists(ctx, "muon_input"));
    h_ele_removed.reset(new ElectronHists(ctx, "ele_removed"));
    h_muon_removed.reset(new MuonHists(ctx, "muon_removed"));
    h_nocuts.reset(new VBFresonanceToWWHists(ctx, "NoCuts"));
    h_njet.reset(new VBFresonanceToWWHists(ctx, "Njet"));
    //    h_dijet.reset(new VBFresonanceToWWHists(ctx, "Dijet"));
    h_input_genparticle.reset(new VBFresonanceToWWParticleHists(ctx, "GenParticle"));
    h_input_topjets.reset(new TopJetHists(ctx, "input_TopJet"));
    h_input_Wtopjets.reset(new VBFresonanceToWW_WTopJetHists(ctx, "input_WTopJet"));
    h_input_jets.reset(new JetHists(ctx, "input_Jet"));
    h_input_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "input_GenTopJet"));
    h_input_genjets.reset(new GenJetsHists(ctx, "input_GenJet"));

    h_cleaner.reset(new VBFresonanceToWWHists(ctx, "cleaner"));
    h_cleaner_topjets.reset(new TopJetHists(ctx, "cleaner_TopJet"));
    h_cleaner_jets.reset(new JetHists(ctx, "cleaner_Jet"));
    h_eta_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "eta_GenTopJet"));
    h_cleaner_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "cleaner_GenTopJet"));
    h_cleaner_genjets.reset(new GenJetsHists(ctx, "cleaner_GenJet"));


    h_noOverlapping_topjets.reset(new TopJetHists(ctx, "noOverlapping_TopJet"));
    h_noOverlapping_jets.reset(new JetHists(ctx, "noOverlapping_Jet"));

    h_2topjetsel_topjets.reset(new TopJetHists(ctx, "2AK8_TopJet"));
    h_2jetsel_jets.reset(new JetHists(ctx, "2AK4_Jet"));

    h_Wgentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "deta_GenTopJet"));
    h_Wgentopjets_invM.reset(new VBFresonanceToWWGenTopJetHists(ctx, "invM_GenTopJet"));
    h_Wgentopjets_VBF.reset(new VBFresonanceToWWGenTopJetHists(ctx, "VBF_GenTopJet"));

    h_jetsel.reset(new VBFresonanceToWWHists(ctx, "jetsel"));
    h_jetsel_topjets.reset(new TopJetHists(ctx, "jetsel_TopJet"));
    h_jetsel_jets.reset(new JetHists(ctx, "jetsel_Jet"));
    h_jetsel_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "jetsel_GenTopJet"));
    h_jetsel_genjets.reset(new GenJetsHists(ctx, "jetsel_GenJet"));


    h_Wtopjets_invM.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_invM"));
    h_topjets_invM.reset(new TopJetHists(ctx, "TopJet_invM"));

    h_Wtopjets_deta.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_deta"));
    h_topjets_deta.reset(new TopJetHists(ctx, "TopJet_deta"));

    h_Wtopjets_invMdeta.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_invMdeta"));
    h_topjets_invMdeta.reset(new TopJetHists(ctx, "TopJet_invMdeta"));
    h_Dijets_invMdeta.reset(new VBFresonanceToWWDiJetHists(ctx, "DiJet_invMdeta"));
    h_jets_invMdeta.reset(new JetHists(ctx, "jet_invMdeta"));
    h_invMdeta.reset(new VBFresonanceToWWHists(ctx, "invMdeta"));

    h_Wtopjets_VVMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_VVMass"));
    h_topjets_VVMass.reset(new TopJetHists(ctx, "TopJet_VVMass"));

    h_Wtopjets_SDMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_SDMass"));
    h_topjets_SDMass.reset(new TopJetHists(ctx, "TopJet_SDMass"));

    h_Wtopjets_tau21.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_tau21"));
    h_topjets_tau21.reset(new TopJetHists(ctx, "TopJet_tau21"));



    h_vbfdeltaeta_jets.reset(new JetHists(ctx, "vbfdeltaeta_Jet"));
    h_vbfdeltaeta_genjets.reset(new GenJetsHists(ctx, "vbfdeltaeta_GenJet"));

    h_vbfetasign_jets.reset(new JetHists(ctx, "vbfetasign_Jet"));
    h_vbfetasign_genjets.reset(new GenJetsHists(ctx, "vbfetasign_GenJet"));

    h_vbfeta_jets.reset(new JetHists(ctx, "vbfeta_Jet"));
    h_vbfeta_genjets.reset(new GenJetsHists(ctx, "vbfeta_GenJet"));
    h_vbfW_genjets.reset(new GenJetsHists(ctx, "vbfW_GenJet"));

    h_Wtopjets.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet"));
    h_Dijets.reset(new VBFresonanceToWWDiJetHists(ctx, "DiJet"));
    //    h_GenDijets.reset(new VBFresonanceToWWGenDiJetHists(ctx, "DiJet"));


    h_Dijets_VBF.reset(new VBFresonanceToWWDiJetHists(ctx, "DiJet_VBF"));
    h_jets_VBF.reset(new JetHists(ctx, "VBF_jets"));
    h_Wtopjets_withVBF.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_withVBF"));
    h_topjets_withVBF.reset(new TopJetHists(ctx, "TopJet_withVBF"));

    h_Dijets_VBF_invM500.reset(new VBFresonanceToWWDiJetHists(ctx, "DiJet_VBF_invM500"));
    h_Dijets_VBF_invM1000.reset(new VBFresonanceToWWDiJetHists(ctx, "DiJet_VBF_invM1000"));
    h_Dijets_VBF_invM1500.reset(new VBFresonanceToWWDiJetHists(ctx, "DiJet_VBF_invM1500"));
    h_Dijets_VBF_invM2000.reset(new VBFresonanceToWWDiJetHists(ctx, "DiJet_VBF_invM2000"));

    h_Wtopjets_VBF_invM500.reset(new VBFresonanceToWWGenTopJetHists(ctx, "Wtopjets_VBF_invM500"));
    h_Wtopjets_VBF_invM1000.reset(new VBFresonanceToWWGenTopJetHists(ctx, "Wtopjets_VBF_invM1000"));
    h_Wtopjets_VBF_invM1500.reset(new VBFresonanceToWWGenTopJetHists(ctx, "Wtopjets_VBF_invM1500"));
    h_Wtopjets_VBF_invM2000.reset(new VBFresonanceToWWGenTopJetHists(ctx, "Wtopjets_VBF_invM2000"));



    h_Wtopjets_withVBF_SDMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_withVBF_SDmass"));
    h_topjets_withVBF_SDMass.reset(new TopJetHists(ctx, "TopJet_withVBF_SDmass"));

    h_Wtopjets_withVBF_tau21.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_withVBF_tau21"));
    h_topjets_withVBF_tau21.reset(new TopJetHists(ctx, "TopJet_withVBF_tau21"));
    h_final.reset(new VBFresonanceToWWHists(ctx, "final"));


    if(PRINT) cout << "hist setup" <<endl;


  }


  bool VBFresonanceToWWFitModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.
    h_start_jets->fill(event);
    
    if(PRINT)    cout << "VBFresonanceToWWFitModule: Starting to process event (runid, eventid) = (" << event.run << ", " <<", " << event.event << "); weight = " << event.weight << endl;
    

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


    bool pass_cm = common->process(event);
    if(!pass_cm) return false; 
    //    if(PRINT)        Gen_printer->process(event);
    
    // 2. test selections and fill histograms
    h_nocuts->fill(event);
    h_input_topjets->fill(event);
    h_input_jets->fill(event);
    h_input_Wtopjets->fill(event);
    h_ele_input->fill(event);
    h_muon_input->fill(event);

    if(isMC)
      {

	h_input_gentopjets->fill(event);
	h_input_genjets->fill(event);
	h_input_genparticle->fill(event);
      }
    //old lepton veto
    // bool muon_sel = nmuon_sel->passes(event);
    // if(!muon_sel) return false;
    // bool electron_sel = nelectron_sel->passes(event);
    // if(!electron_sel) return false;
    // h_ele_removed->fill(event);
    // h_muon_removed->fill(event);

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

    jetcleaner->process(event);
    topjetcleaner->process(event);

    h_cleaner->fill(event);
    h_cleaner_topjets->fill(event);
    h_cleaner_jets->fill(event);

    
    //Cleaning AK4 by overlap of AK8
    std::vector<Jet>* AK4Jets(new std::vector<Jet> (*event.jets));
    AK4Jets->clear();
    AK4Jets->reserve(event.jets->size());

    if(PRINT) std::cout<<"SelectionModule L:858 Size AK4 before cleaning "<<event.jets->size() <<std::endl;
    for(const Jet ak4:*event.jets){
      bool bdeltaR=true;
      for(const TopJet ak8:*event.topjets){
	double deltar = deltaR(ak4,ak8);
	if(PRINT) std::cout<<"SelectionModule L:858 DeltaR(ak4, ak8)<1.2 "<<deltar <<std::endl;
	if(deltar < 1.2) bdeltaR=false;
	if(PRINT) std::cout<<"SelectionModule L:858 bdeltaR  "<<bdeltaR <<std::endl;
      }
      if(bdeltaR)AK4Jets ->push_back(ak4);
    }
    sort_by_pt<Jet>(*AK4Jets);
    ////put cleaned AK4 jets in event.jet
    event.jets->clear();
    event.jets->reserve(AK4Jets->size());
    for(const auto & j : *AK4Jets) event.jets->push_back(j); 
    sort_by_pt<Jet>(*event.jets);
    if(PRINT) std::cout<<"SelectionModule L:858 Size topjets Collection "<<event.jets->size() <<std::endl;

    /////////////////AK4 cleaning end ////////////////


    h_noOverlapping_jets->fill(event);
    h_noOverlapping_topjets->fill(event);


    //genjet
    if(isMC){
      bool noOverlapping_genjetselection = noOverlapping_genjetsel->passes(event);
      bool eta_gentopjetselection = eta_topgensel->passes(event);
      if(eta_gentopjetselection)
	//      if(eta_gentopjetselection && noOverlapping_genjetselection)
	{
	  h_eta_gentopjets->fill(event);
	}
      bool cleaner_gentopjetselection = cleaner_topgensel->passes(event);
      //      if(eta_gentopjetselection && cleaner_gentopjetselection && noOverlapping_genjetselection)
      if(eta_gentopjetselection  && cleaner_gentopjetselection ) 
	{
	  h_cleaner_gentopjets->fill(event);
	}
      bool gentopjets_deta_selection = gentopjets_deta_sel->passes(event);
      if(gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection)
	//      if(gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection && noOverlapping_genjetselection)
	{
	  h_Wgentopjets->fill(event);
	}
      bool invMgentopjet_selection = invMgentopjet_sel->passes(event);
      //      if(invMgentopjet_selection && gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection && noOverlapping_genjetselection)
      if(invMgentopjet_selection && gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection)
	{
	  h_Wgentopjets_invM->fill(event);
	  h_cleaner_genjets->fill(event);
	 
	}
      bool vbfdeta_genselection = vbfdeta_gensel->passes(event);
      if(vbfdeta_genselection){
	h_vbfdeltaeta_genjets->fill(event);
      }
      bool vbfetasign_genselection = vbfetasign_gensel->passes(event);
      if(vbfetasign_genselection)// && invMgentopjet_selection && gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection && noOverlapping_genjetselection)
	{
	  h_vbfetasign_genjets->fill(event);
	}
      bool vbfeta_genselection = vbfeta_gensel->passes(event);
      if(vbfeta_genselection && invMgentopjet_selection && gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection)
	//      if(vbfeta_genselection && invMgentopjet_selection && gentopjets_deta_selection && eta_gentopjetselection && cleaner_gentopjetselection && noOverlapping_genjetselection)
	{
	  h_vbfW_genjets->fill(event);
	  //      h_GenDijets->fill(event);
	}

      if(vbfeta_genselection)
	{
	  h_vbfeta_genjets->fill(event);
	  h_Wgentopjets_VBF->fill(event);	

	}


    }




    bool njet_selection = njet_sel->passes(event);
    if(njet_selection){
      h_njet->fill(event);
    }

    //    bool jets_selection = (jet2_sel->passes(event) && topjet2_sel->passes(event));
    //if(!jets_selection) return false;

    bool topjets2_selection = topjet2_sel->passes(event);
    if(!topjets2_selection) return false;

    h_2topjetsel_topjets->fill(event);


    /*
    h_jetsel->fill(event);
    h_jetsel_topjets->fill(event);
    h_jetsel_jets->fill(event);
    h_jetsel_gentopjets->fill(event);
    h_jetsel_genjets->fill(event);
    */
    h_Wtopjets->fill(event);

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
    if(invMtopjet_selection )
      {
	h_Wtopjets_invMdeta->fill(event);
	h_topjets_invMdeta->fill(event);
	h_Dijets_invMdeta->fill(event);
	h_jets_invMdeta->fill(event);
	h_invMdeta->fill(event);
       bool VVMtopjet_selection = VVmass_sel->passes(event);
       if(VVMtopjet_selection )
	 {
	   h_Wtopjets_VVMass->fill(event);
	   h_topjets_VVMass->fill(event);
	 }
      }



	//for fit
    if(PRINT) cout << "SD mass sel starting" <<endl;
       bool SDMtopjet_selection = SDmass_sel->passes(event);
     if(PRINT) cout << "SD mass" <<endl;
    if(SDMtopjet_selection )
      {
	h_Wtopjets_SDMass->fill(event);
	h_topjets_SDMass->fill(event);
	if(PRINT) cout << "SD mass fill" <<endl;	
      }
       bool tau21topjet_selection = tau21topjet_sel->passes(event);
     if(PRINT) cout << "tau21" <<endl;
    if(tau21topjet_selection && SDMtopjet_selection)
      {
	h_Wtopjets_tau21->fill(event);
	h_topjets_tau21->fill(event);
	if(PRINT) cout << "tau fill" <<endl;	
      }

    
	// Selections for AK4

    bool jets2_selection = jet2_sel->passes(event);
    if(!jets2_selection) return false;

    h_2jetsel_jets->fill(event);



    //    bool dijet_selection = dijet_sel->passes(event);
    //if(dijet_selection){
    //  h_dijet->fill(event);
    //}
    bool vbfdeta_selection = vbfdeta_sel->passes(event);
    if(vbfdeta_selection){
      if(PRINT)      cout << "vbfdeta_selection jets" <<endl;
      h_vbfdeltaeta_jets->fill(event);
      if(PRINT) cout << "vbfdeta_selection jets" <<endl;
    }
    
    bool vbfetasign_selection = vbfetasign_sel->passes(event);
    if(vbfetasign_selection){
      h_vbfetasign_jets->fill(event);
      if(PRINT) cout << "vbfeta_sign jets" <<endl;
    }

      bool vbfeta_selection = vbfeta_sel->passes(event);
      if(vbfeta_selection){
	h_jets_VBF->fill(event);
	h_Dijets_VBF->fill(event);
	if(PRINT) cout << "vbfeta_selection genjets" <<endl;
	
      }


    if(!vbfeta_selection) return false;
    h_Wtopjets_withVBF->fill(event);
    h_topjets_withVBF->fill(event);
    
      if(PRINT) cout << "vbfeta_selection topjets" <<endl;

      bool invM500jet_selection = invM500_sel->passes(event);
      if(invM500jet_selection )
	{
	  h_Dijets_VBF_invM500->fill(event);
	  h_Wtopjets_VBF_invM500->fill(event);
	}
      bool invM1000jet_selection = invM1000_sel->passes(event);
      if(invM1000jet_selection )
	{
	  h_Dijets_VBF_invM1000->fill(event);
	  h_Wtopjets_VBF_invM1000->fill(event);
	}
      bool invM1500jet_selection = invM1500_sel->passes(event);
      if(invM1500jet_selection )
	{
	  h_Dijets_VBF_invM1500->fill(event);
	  h_Wtopjets_VBF_invM1500->fill(event);
	}
      bool invM2000jet_selection = invM2000_sel->passes(event);
      if(invM2000jet_selection )
	{
	  h_Dijets_VBF_invM2000->fill(event);
	  h_Wtopjets_VBF_invM2000->fill(event);
	}

      if(PRINT) cout << " jets invM" <<endl;





    if(SDMtopjet_selection)
      {
	h_Wtopjets_withVBF_SDMass->fill(event);
	h_topjets_withVBF_SDMass->fill(event);
	if(PRINT) cout << "SD mass fill" <<endl;	
      }
    if(tau21topjet_selection && SDMtopjet_selection)
      {
        h_Wtopjets_withVBF_tau21->fill(event);
        h_topjets_withVBF_tau21->fill(event);
        if(PRINT) cout << "tau fill" <<endl;
      }
    

      if(PRINT) cout << "jets tau and SD" <<endl;

      
      h_final->fill(event);
      
      if(PRINT) cout << "final" <<endl;



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
  // make sure the VBFresonanceToWWFitModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(VBFresonanceToWWFitModule)

}
