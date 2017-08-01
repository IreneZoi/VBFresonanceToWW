#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/JetCorrections.h"
#include <UHH2/common/include/MCWeight.h>
#include "UHH2/common/include/PrintingModules.h"
#include "UHH2/common/include/ElectronHists.h"
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
  class VBFresonanceToWWModule: public AnalysisModule {
  public:
    
    explicit VBFresonanceToWWModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    
    std::unique_ptr<CommonModules> common;

    std::unique_ptr<AnalysisModule> Gen_printer;  

    std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner;
    std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner_BCD;
    std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner_EF;
    std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner_G;
    std::unique_ptr<JetLeptonCleaner> jetlepton_cleaner_H;

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
    std::unique_ptr<Selection> njet_sel, dijet_sel, vbfdeta_sel, vbfdeta_gensel, jet1_sel, jet2_sel, topjet1_sel, topjet2_sel, vbfetasign_sel, vbfetasign_gensel, vbfeta_sel, vbfeta_gensel, topjets_deta_sel, SDmass_sel, invMtopjet_sel;
  
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
    std::unique_ptr<Hists> h_start_jets;
    std::unique_ptr<Hists> h_nocuts, h_njet, /*h_dijet,*/ h_input_topjets, h_input_jets, h_input_gentopjets, h_input_genjets, h_input_genparticle;
    std::unique_ptr<Hists> h_cleaner, h_cleaner_topjets, h_cleaner_jets, h_cleaner_gentopjets, h_cleaner_genjets;
    std::unique_ptr<Hists> h_noOverlapping_topjets, h_noOverlapping_jets;

    std::unique_ptr<Hists> h_2topjetsel_topjets;
    std::unique_ptr<Hists> h_2jetsel_jets;
    std::unique_ptr<Hists> h_jetsel, h_jetsel_topjets, h_jetsel_jets, h_jetsel_gentopjets, h_jetsel_genjets;
    std::unique_ptr<Hists> h_vbfdeltaeta_jets, h_vbfdeltaeta_genjets;
    std::unique_ptr<Hists> h_vbfetasign_jets, h_vbfetasign_genjets;
    std::unique_ptr<Hists> h_vbfeta_jets, h_vbfeta_genjets;
    std::unique_ptr<Hists> h_Wtopjets;
    std::unique_ptr<Hists> h_Dijets;
    //  std::unique_ptr<Hists> h_GenDijets;


    std::unique_ptr<Hists> h_Wtopjets_invM;
    std::unique_ptr<Hists> h_topjets_invM;

    // std::unique_ptr<Hists> h_Wtopjets_deta;
    // std::unique_ptr<Hists> h_topjets_deta;

    std::unique_ptr<Hists> h_Wtopjets_SDMass;
    std::unique_ptr<Hists> h_topjets_SDMass;

    std::unique_ptr<Hists> h_Wtopjets_invMdeta;
    std::unique_ptr<Hists> h_topjets_invMdeta;
    std::unique_ptr<Hists> h_Dijets_invMdeta;
    std::unique_ptr<Hists> h_jets_invMdeta;
    std::unique_ptr<Hists> h_invMdeta;

    std::unique_ptr<Hists> h_Dijets_VBF;
    std::unique_ptr<Hists> h_jets_VBF;
    std::unique_ptr<Hists> h_Wtopjets_withVBF;
    std::unique_ptr<Hists> h_topjets_withVBF;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_SDMass;
    std::unique_ptr<Hists> h_topjets_withVBF_SDMass;

    std::unique_ptr<Hists> h_final;


    const int runnr_BCD = 276811;
    const int runnr_EF = 278802;
    const int runnr_G = 280385;

    bool isMC;
  };


  VBFresonanceToWWModule::VBFresonanceToWWModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.
    
    cout << "Hello World from VBFresonanceToWWModule!" << endl;

    Gen_printer.reset(new GenParticlesPrinter(ctx));
    
    // If needed, access the configuration of the module here, e.g.:
    string testvalue = ctx.get("TestKey", "<not set>");
    cout << "TestKey in the configuration was: " << testvalue << endl;


    //choose channel from .xml file
    isMC = (ctx.get("dataset_type") == "MC");
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
    common.reset(new CommonModules());
    // TODO: configure common here, e.g. by 
    // calling common->set_*_id or common->disable_*
    //    common->disable_mcpileupreweight(); //irene                                                                                                                                                      
    common->disable_jersmear(); //irene
    common->disable_jec(); //irene       
    common->disable_metfilters(); //irene                                                                                           
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
	jetlepton_cleaner.reset(new JetLeptonCleaner(ctx,JEC_AK4));
	jetlepton_cleaner->set_drmax(.4);      
	jet_corrector.reset(new JetCorrector(ctx, JEC_AK4));
	topjet_corrector.reset(new TopJetCorrector(ctx, JEC_AK8));
	subjet_corrector.reset(new SubJetCorrector(ctx,JEC_AK4));
      	jetER_smearer.reset(new JetResolutionSmearer(ctx));
	topjetER_smearer.reset(new GenericJetResolutionSmearer(ctx,"topjets","gentopjets"));
      }
    else 
      {
	

	jetlepton_cleaner_BCD.reset(new JetLeptonCleaner(ctx, JEC_AK4_BCD));
	jetlepton_cleaner_EF.reset(new JetLeptonCleaner(ctx, JEC_AK4_EF));
	jetlepton_cleaner_G.reset(new JetLeptonCleaner(ctx,JEC_AK4_G ));
	jetlepton_cleaner_H.reset(new JetLeptonCleaner(ctx,JEC_AK4_H ));
	
	jetlepton_cleaner_BCD->set_drmax(.4);
	jetlepton_cleaner_EF->set_drmax(.4);
	jetlepton_cleaner_G->set_drmax(.4);
	jetlepton_cleaner_H->set_drmax(.4);
	
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
    dijet_sel.reset(new DijetSelection()); // see VBFresonanceToWWSelections
    jet2_sel.reset(new NJetSelection(2)); // at least 2 jets      
    jet1_sel.reset(new NJetSelection(1)); // at least 1 jets      
    topjet1_sel.reset(new NTopJetSelection(1)); // at least 1 jets
    topjet2_sel.reset(new NTopJetSelection(2)); // at least 2 jets      
    vbfdeta_sel.reset(new VBFdeltaEtajetSelection()); // see VBFresonanceToWWSelections
    vbfdeta_gensel.reset(new VBFdeltaEtaGenjetSelection()); // see VBFresonanceToWWSelections
    vbfetasign_sel.reset(new VBFEtaSignjetSelection()); // see VBFresonanceToWWSelections
    vbfetasign_gensel.reset(new VBFEtaSignGenjetSelection()); // see VBFresonanceToWWSelections
    vbfeta_sel.reset(new VBFEtajetSelection()); // see VBFresonanceToWWSelections
    vbfeta_gensel.reset(new VBFEtaGenjetSelection()); // see VBFresonanceToWWSelections
    topjets_deta_sel.reset(new deltaEtaTopjetSelection()); // see VBFresonanceToWWSelections
    SDmass_sel.reset(new SDMassTopjetSelection()); // see VBFresonanceToWWSelections
    invMtopjet_sel.reset(new invMassTopjetSelection()); // see VBFresonanceToWWSelections

    if(PRINT) cout << "reset sel" <<endl;


    // 3. Set up Hists classes:
    h_start_jets.reset(new JetHists(ctx, "start_Jet"));
    h_nocuts.reset(new VBFresonanceToWWHists(ctx, "NoCuts"));
    h_njet.reset(new VBFresonanceToWWHists(ctx, "Njet"));
    //    h_dijet.reset(new VBFresonanceToWWHists(ctx, "Dijet"));
    h_input_genparticle.reset(new VBFresonanceToWWParticleHists(ctx, "GenParticle"));
    h_input_topjets.reset(new TopJetHists(ctx, "input_TopJet"));
    h_input_jets.reset(new JetHists(ctx, "input_Jet"));
    h_input_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "input_GenTopJet"));
    h_input_genjets.reset(new GenJetsHists(ctx, "input_GenJet"));

    h_cleaner.reset(new VBFresonanceToWWHists(ctx, "cleaner"));
    h_cleaner_topjets.reset(new TopJetHists(ctx, "cleaner_TopJet"));
    h_cleaner_jets.reset(new JetHists(ctx, "cleaner_Jet"));
    h_cleaner_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "cleaner_GenTopJet"));
    h_cleaner_genjets.reset(new GenJetsHists(ctx, "cleaner_GenJet"));


    h_noOverlapping_topjets.reset(new TopJetHists(ctx, "noOverlapping_TopJet"));
    h_noOverlapping_jets.reset(new JetHists(ctx, "noOverlapping_Jet"));

    h_2topjetsel_topjets.reset(new TopJetHists(ctx, "2AK8_TopJet"));
    h_2jetsel_jets.reset(new JetHists(ctx, "2AK4_Jet"));


    h_jetsel.reset(new VBFresonanceToWWHists(ctx, "jetsel"));
    h_jetsel_topjets.reset(new TopJetHists(ctx, "jetsel_TopJet"));
    h_jetsel_jets.reset(new JetHists(ctx, "jetsel_Jet"));
    h_jetsel_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "jetsel_GenTopJet"));
    h_jetsel_genjets.reset(new GenJetsHists(ctx, "jetsel_GenJet"));


    h_Wtopjets_SDMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_SDMass"));
    h_topjets_SDMass.reset(new TopJetHists(ctx, "TopJet_SDMass"));


    h_Wtopjets_invM.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_invM"));
    h_topjets_invM.reset(new TopJetHists(ctx, "TopJet_invM"));

    // h_Wtopjets_deta.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_deta"));
    // h_topjets_deta.reset(new TopJetHists(ctx, "TopJet_deta"));

    h_Wtopjets_invMdeta.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_invMdeta"));
    h_topjets_invMdeta.reset(new TopJetHists(ctx, "TopJet_invMdeta"));
    h_Dijets_invMdeta.reset(new VBFresonanceToWWDiJetHists(ctx, "DiJet_invMdeta"));
    h_jets_invMdeta.reset(new JetHists(ctx, "jet_invMdeta"));
    h_invMdeta.reset(new VBFresonanceToWWHists(ctx, "invMdeta"));



    h_vbfdeltaeta_jets.reset(new JetHists(ctx, "vbfdeltaeta_Jet"));
    h_vbfdeltaeta_genjets.reset(new GenJetsHists(ctx, "vbfdeltaeta_GenJet"));

    h_vbfetasign_jets.reset(new JetHists(ctx, "vbfetasign_Jet"));
    h_vbfetasign_genjets.reset(new GenJetsHists(ctx, "vbfetasign_GenJet"));

    h_vbfeta_jets.reset(new JetHists(ctx, "vbfeta_Jet"));
    h_vbfeta_genjets.reset(new GenJetsHists(ctx, "vbfeta_GenJet"));

    h_Wtopjets.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet"));
    h_Dijets.reset(new VBFresonanceToWWDiJetHists(ctx, "DiJet"));
    //    h_GenDijets.reset(new VBFresonanceToWWGenDiJetHists(ctx, "DiJet"));


    h_Dijets_VBF.reset(new VBFresonanceToWWDiJetHists(ctx, "DiJet_VBF"));
    h_jets_VBF.reset(new JetHists(ctx, "VBF_jets"));
    h_Wtopjets_withVBF.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_withVBF"));
    h_topjets_withVBF.reset(new TopJetHists(ctx, "TopJet_withVBF"));
    h_Wtopjets_withVBF_SDMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet_withVBF_SDmass"));
    h_topjets_withVBF_SDMass.reset(new TopJetHists(ctx, "TopJet_withVBF_SDmass"));
    h_final.reset(new VBFresonanceToWWHists(ctx, "final"));


    if(PRINT) cout << "hist setup" <<endl;


  }


  bool VBFresonanceToWWModule::process(Event & event) {
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
    
    if(PRINT)    cout << "VBFresonanceToWWModule: Starting to process event (runid, eventid) = (" << event.run << ", " <<", " << event.event << "); weight = " << event.weight << endl;
    

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


    common->process(event);
    //    if(PRINT)    Gen_printer->process(event);
    
    // 2. test selections and fill histograms
    h_nocuts->fill(event);
    h_input_topjets->fill(event);
    h_input_jets->fill(event);

    if(isMC)
      {

	h_input_gentopjets->fill(event);
	h_input_genjets->fill(event);
	h_input_genparticle->fill(event);
      }

    // JET CLEANING
    if(isMC)
      {
	jetlepton_cleaner->process(event);
	jet_corrector->process(event);
	topjet_corrector->process(event);
	subjet_corrector->process(event);
	jet_corrector->correct_met(event);
		jetER_smearer->process(event);
		topjetER_smearer->process(event);
      }else{
      if(event.run <= runnr_BCD)  {       
	jetlepton_cleaner_BCD->process(event);    
	jet_corrector_BCD->process(event);
	topjet_corrector_BCD->process(event);
	subjet_corrector_BCD->process(event);
	jet_corrector_BCD->correct_met(event);
     }
      else if(event.run < runnr_EF){       
	jetlepton_cleaner_EF->process(event);   
	jet_corrector_EF->process(event);
	topjet_corrector_EF->process(event);
	subjet_corrector_EF->process(event);
	jet_corrector_EF->correct_met(event);
      } 
      else if(event.run <= runnr_G) {       
	jetlepton_cleaner_G->process(event);   
	jet_corrector_G->process(event);
	topjet_corrector_G->process(event);
	subjet_corrector_G->process(event);
	jet_corrector_G->correct_met(event);
      } 
      else if(event.run > runnr_G) {       
	jetlepton_cleaner_H->process(event); 
	jet_corrector_H->process(event);
	topjet_corrector_H->process(event);
	subjet_corrector_H->process(event);
	jet_corrector_H->correct_met(event);
      } 
    }



    jetcleaner->process(event);
    topjetcleaner->process(event);

    h_cleaner->fill(event);
    h_cleaner_topjets->fill(event);
    h_cleaner_jets->fill(event);

    if(isMC)
      {

	h_cleaner_gentopjets->fill(event);
	h_cleaner_genjets->fill(event);
      }

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

    bool invMtopjet_selection = invMtopjet_sel->passes(event);
    if(!invMtopjet_selection )
      return false;

      h_Wtopjets_invM->fill(event);
      h_topjets_invM->fill(event);

    bool topjets_deta_selection = topjets_deta_sel->passes(event);
    if(!topjets_deta_selection)
      return false;

	h_Wtopjets_invMdeta->fill(event);
	h_topjets_invMdeta->fill(event);
	h_Dijets_invMdeta->fill(event);
	h_jets_invMdeta->fill(event);
	h_invMdeta->fill(event);
    
    if(PRINT) cout << "SD mass sel starting" <<endl;
       bool SDMtopjet_selection = SDmass_sel->passes(event);
     if(PRINT) cout << "SD mass" <<endl;
    if(SDMtopjet_selection)
      {
	h_Wtopjets_SDMass->fill(event);
	h_topjets_SDMass->fill(event);
	if(PRINT) cout << "SD mass fill" <<endl;	
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
    if(isMC)
      {
	bool vbfdeta_genselection = vbfdeta_gensel->passes(event);
	if(vbfdeta_genselection){
	  h_vbfdeltaeta_genjets->fill(event);
	}
      }

    bool vbfetasign_selection = vbfetasign_sel->passes(event);
    if(vbfetasign_selection){
      h_vbfetasign_jets->fill(event);
      if(PRINT) cout << "vbfeta_sign jets" <<endl;
    }

    if(isMC){
      bool vbfetasign_genselection = vbfetasign_gensel->passes(event);
      if(vbfetasign_genselection){
	h_vbfetasign_genjets->fill(event);
      }
    }
    bool vbfeta_selection = vbfeta_sel->passes(event);
    if(vbfeta_selection){
      h_jets_VBF->fill(event);
      h_Dijets_VBF->fill(event);

      if(PRINT) cout << "vbfeta_selection jets" <<endl;

    }

    if(isMC){
      bool vbfeta_genselection = vbfeta_gensel->passes(event);
      if(vbfeta_genselection){
	h_vbfeta_genjets->fill(event);
	//      h_GenDijets->fill(event);
      }
    }

    if(!vbfeta_selection) return false;
    h_Wtopjets_withVBF->fill(event);
    h_topjets_withVBF->fill(event);
    if(SDMtopjet_selection)
      {
	h_Wtopjets_withVBF_SDMass->fill(event);
	h_topjets_withVBF_SDMass->fill(event);
	if(PRINT) cout << "SD mass fill" <<endl;	
      }



    h_final->fill(event);




    // store Jets *before cleaning* in the ntuple                                                                                                                                                     
    event.jets->clear();
    event.jets->reserve(uncleaned_jets->size());
    for(const auto & j : *uncleaned_jets) event.jets->push_back(j);
    sort_by_pt<Jet>(*event.jets);

    event.topjets->clear();
    event.topjets->reserve(uncleaned_topjets->size());
    for(const auto & j : *uncleaned_topjets) event.topjets->push_back(j);
    sort_by_pt<TopJet>(*event.topjets);

    // 3. decide whether or not to keep the current event in the output:
    return true;

  }

  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the VBFresonanceToWWModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(VBFresonanceToWWModule)

}
