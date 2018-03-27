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
  class VBFresonanceToWWInvertedHSBModule: public AnalysisModule {
  public:
    

    explicit VBFresonanceToWWInvertedHSBModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    std::string channel_;
    
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
    std::unique_ptr<Selection> VVmass_sel, LOWmass_sel, HIGHmass_sel;
    std::unique_ptr<Selection> tau21topjet_sel;
    //VBF jets
    std::unique_ptr<Selection> jet2_sel;
    std::unique_ptr<Selection> vbfdeta_sel, vbfdeta4_sel, vbfdeta5_sel, vbfdeta6_sel;
    std::unique_ptr<Selection> vbfetasign_sel;
    std::unique_ptr<Selection> vbfeta_sel, vbfeta4_sel, vbfeta5_sel, vbfeta6_sel;
    std::unique_ptr<Selection> invM1000_sel;
    //inverted VBF jets
    std::unique_ptr<Selection> jet2_invsel;
    std::unique_ptr<Selection> vbfetasign_invsel;
    std::unique_ptr<Selection> vbfeta_invsel;
    std::unique_ptr<Selection> invM1000_invsel;

    //    std::unique_ptr<Selection> invM400_sel, invM600_sel, invM800_sel, invM1200_sel;
    //genjet
    //    std::unique_ptr<Selection> eta_topgensel, cleaner_topgensel, gentopjets_deta_sel, invMgentopjet_sel, noOverlapping_genjetsel, vbfdeta_gensel , vbfetasign_gensel, vbfeta_gensel;
  
    //********** HISTOS ***************  
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.

    std::unique_ptr<Hists> h_Wtopjets_compare;
    std::unique_ptr<Hists> h_topjets_compare;
    std::unique_ptr<Hists> h_Dijets_compare;
    std::unique_ptr<Hists> h_jets_compare;
    std::unique_ptr<Hists> h_compare;

    std::unique_ptr<Hists> h_Wtopjets_VVMass;
    std::unique_ptr<Hists> h_topjets_VVMass;
    std::unique_ptr<Hists> h_Dijets_VVMass;
    std::unique_ptr<Hists> h_jets_VVMass;
    std::unique_ptr<Hists> h_VVMass;

    std::unique_ptr<Hists> h_Wtopjets_withVBF_VVMass;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_VVMass_inverted;

    std::unique_ptr<Hists> h_VBF_VVMass;
    std::unique_ptr<Hists> h_jets_VBF_VVMass;
    std::unique_ptr<Hists> h_Dijets_VBF_VVMass;
    std::unique_ptr<Hists> h_topjets_withVBF_VVMass;

    
    std::unique_ptr<Hists> h_Dijets_VBF_invM1000;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM1000;
    

    std::unique_ptr<Hists> h_input_gentopjets;
    std::unique_ptr<Hists> h_input_gendijets;
    std::unique_ptr<Hists> h_input_genjets;
    std::unique_ptr<Hists> h_input_genparticle;

    const int runnr_BCD = 276811;
    const int runnr_EF = 278802;
    const int runnr_G = 280385;

    bool isMC;

    MuonId     MuId;
    ElectronId EleId;

  };


  VBFresonanceToWWInvertedHSBModule::VBFresonanceToWWInvertedHSBModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.
    
    cout << "Hello World from VBFresonanceToWWInvertedHSBModule!" << endl;

    Gen_printer.reset(new GenParticlesPrinter(ctx));
    
    // If needed, access the configuration of the module here, e.g.:
    string testvalue = ctx.get("TestKey", "<not set>");
    cout << "TestKey in the configuration was: " << testvalue << endl;


    //choose channel from .xml file
    isMC = (ctx.get("dataset_type") == "MC");
    channel_ = ctx.get("channel");
    // If running in SFrame, the keys "dataset_version", "dataset_type", "dataset_lumi",
    // and "target_lumi" are set to the according values in the xml file. For CMSSW, these are
    // not set automatically, but can be set in the python config file.
    for(auto & kv : ctx.get_all()){
      cout << " " << kv.first << " = " << kv.second << endl;
    }
    
    // 1. setup other modules. CommonModules and the JetCleaner:

    MuId  = AndId<Muon>(MuonIDTight(), PtEtaCut(30., 2.4));
    EleId = AndId<Electron>(ElectronID_HEEP_RunII_25ns, PtEtaCut(35., 2.5));


    common.reset(new CommonModules());
    // TODO: configure common here, e.g. by 
    // calling common->set_*_id or common->disable_*
    

    common->disable_jersmear(); //irene
    common->disable_jec(); //irene       

    if(PRINT) cout << "common" <<endl;


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
	jet_corrector.reset(new JetCorrector(ctx, JEC_AK4));
	topjet_corrector.reset(new TopJetCorrector(ctx, JEC_AK8));
	subjet_corrector.reset(new SubJetCorrector(ctx,JEC_AK4));
	if(channel_=="signal")
	  {
	    jetER_smearer.reset(new JetResolutionSmearer(ctx));
	    topjetER_smearer.reset(new GenericJetResolutionSmearer(ctx,"topjets","gentopjets",true,JERSmearing::SF_13TeV_2016,"Spring16_25nsV10_MC_PtResolution_AK8PFPuppi.txt"));
	  }
      }
    else 
      {
	
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
    topjetcleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(200., 2.5))));
    
    if(PRINT) cout << "cleaners" <<endl;
    



    common->init(ctx);

    // note that the JetCleaner is only kept for the sake of example;
    // instead of constructing a jetcleaner explicitly,
    // the cleaning can also be achieved with less code via CommonModules with:
    // common->set_jet_id(PtEtaCut(30.0, 2.4));
    // before the 'common->init(ctx)' line.
    
    // 2. set up selections ***

    muon_sel.reset(new MuonVeto(0.8,MuId)); // see VBFresonanceToWWSelections
    electron_sel.reset(new ElectronVeto(0.8,EleId)); // see VBFresonanceToWWSelections

    topjet2_sel.reset(new NTopJetSelection(2)); // at least 2 jets      
    invMtopjet_fitsel.reset(new invMassTopjetSelection()); // see VBFresonanceToWWSelections
    topjets_deta_sel.reset(new deltaEtaTopjetSelection()); // see VBFresonanceToWWSelections
    invMtopjet_sel.reset(new invMassTopjetSelection(1070.0f)); // see VBFresonanceToWWSelections
    invMtopjet_SDsel.reset(new invMassTopjetSelection(1080.0f)); // see VBFresonanceToWWSelections
    VVmass_sel.reset(new VVMassTopjetSelection());// see VBFresonanceToWWSelections
    LOWmass_sel.reset(new VVMassTopjetSelection(45.0f,65.0f));// see VBFresonanceToWWSelections
    HIGHmass_sel.reset(new HighMassTopjetSelection(135.0f));// see VBFresonanceToWWSelections
    tau21topjet_sel.reset(new nSubjTopjetSelection(0.f,0.35f)); // see VBFresonanceToWWSelections

    jet2_sel.reset(new NJetSelection(2)); // at least 2 jets      
    vbfdeta_sel.reset(new VBFdeltaEtajetSelection()); // see VBFresonanceToWWSelections
    vbfetasign_sel.reset(new VBFEtaSignjetSelection()); // see VBFresonanceToWWSelections
    vbfeta_sel.reset(new VBFEtajetSelection()); // see VBFresonanceToWWSelections
    vbfeta4_sel.reset(new VBFEtajetSelection(4.0f)); // see VBFresonanceToWWSelections
    vbfeta5_sel.reset(new VBFEtajetSelection(5.0f)); // see VBFresonanceToWWSelections
    vbfeta6_sel.reset(new VBFEtajetSelection(6.0f)); // see VBFresonanceToWWSelections
    invM1000_sel.reset(new invMassVBFjetSelection(1000.0f)); // see VBFresonanceToWWSelections
    if(PRINT) cout << "reset sel" <<endl;

    //VBF inverted
    jet2_invsel.reset(new DijetInvSelection(2.f)); // at least 2 jets      
    vbfetasign_invsel.reset(new VBFEtaSignjetInvSelection()); // see VBFresonanceToWWSelections
    vbfeta_invsel.reset(new VBFEtajetInvSelection()); // see VBFresonanceToWWSelections
    invM1000_invsel.reset(new invMassVBFjetInvSelection(1000.0f)); // see VBFresonanceToWWSelections


    // 3. Set up Hists classes:

    h_Wtopjets_compare.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_compare"));
    h_topjets_compare.reset(new TopJetHists(ctx, "topjets_compare"));
    h_Dijets_compare.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_compare"));
    h_jets_compare.reset(new JetHists(ctx, "jets_compare"));
    h_compare.reset(new VBFresonanceToWWHists(ctx, "compare"));

    h_Wtopjets_VVMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VVMass"));
    h_topjets_VVMass.reset(new TopJetHists(ctx, "topjets_VVMass"));
    h_Dijets_VVMass.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VVMass"));
    h_jets_VVMass.reset(new JetHists(ctx, "jets_VVMass"));
    h_VVMass.reset(new VBFresonanceToWWHists(ctx, "VVMass"));

    // h_Wtopjets_withVBF_VVMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_VVMass"));
    // h_Wtopjets_withVBF_VVMass_inverted.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_VVMass_inverted"));

    h_Dijets_VBF_invM1000.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_invM1000"));
    h_Wtopjets_withVBF_invM1000.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VBF_invM1000"));


    //genjet
    h_input_genparticle.reset(new VBFresonanceToWWParticleHists(ctx, "GenParticle"));
    h_input_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "input_GenTopJet"));
    h_input_gendijets.reset(new VBFresonanceToWWGenDiJetHists(ctx, "input_GenDiJet"));
    h_input_genjets.reset(new GenJetsHists(ctx, "input_GenJet"));

    if(PRINT) cout << "hist setup" <<endl;


  }


  bool VBFresonanceToWWInvertedHSBModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.
    
    if(PRINT)    cout << "VBFresonanceToWWInvertedHSBModule: Starting to process event (runid, eventid) = (" << event.run << ", " <<", " << event.event << "); weight = " << event.weight << endl;
    

    /////////////////////////////////////////////////////////// Common Modules   ///////////////////////////////////////////////////////////////////////////////


    //common Modules
    // keep Jets *before cleaning* to store them in the ntuple if event is accepted   
    std::unique_ptr< std::vector<Jet> >    uncleaned_jets   (new std::vector<Jet>   (*event.jets));   
    std::unique_ptr< std::vector<TopJet> > uncleaned_topjets(new std::vector<TopJet>(*event.topjets));

    // 1. run all modules other modules.
    bool pass_cm = common->process(event);
    if(!pass_cm) return false; 
    //    if(PRINT)    Gen_printer->process(event);

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

   sort_by_pt<Jet>(*event.jets);
   sort_by_pt<TopJet>(*event.topjets);


    // JET CLEANING
    if(isMC)
      {
	topjet_corrector->process(event);
	subjet_corrector->process(event);
	jet_corrector->correct_met(event);
	if(channel_=="signal")
	  {
	    jetER_smearer->process(event);
	    topjetER_smearer->process(event);
	  }
      }else{
      if(event.run <= runnr_BCD)  {       
	jet_corrector_BCD->process(event);
	topjet_corrector_BCD->process(event);
	subjet_corrector_BCD->process(event);
	jet_corrector_BCD->correct_met(event);
     }
      else if(event.run < runnr_EF){       
	jet_corrector_EF->process(event);
	topjet_corrector_EF->process(event);
	subjet_corrector_EF->process(event);
	jet_corrector_EF->correct_met(event);
      } 
      else if(event.run <= runnr_G) {       
	jet_corrector_G->process(event);
	topjet_corrector_G->process(event);
	subjet_corrector_G->process(event);
	jet_corrector_G->correct_met(event);
      } 
      else if(event.run > runnr_G) {       
	jet_corrector_H->process(event);
	topjet_corrector_H->process(event);
	subjet_corrector_H->process(event);
	jet_corrector_H->correct_met(event);
      } 
    }

    sort_by_pt<Jet>(*event.jets);
    sort_by_pt<TopJet>(*event.topjets);


    topjetcleaner->process(event);
    jetcleaner->process(event);



    bool topjets2_selection = topjet2_sel->passes(event);
    if(!topjets2_selection) return false;

    
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


    //    sort_by_eta<Jet>(*event.jets);

    bool invMtopjet_fitselection = invMtopjet_fitsel->passes(event);
    if(!invMtopjet_fitselection )
      return false;


    bool topjets_deta_selection = topjets_deta_sel->passes(event);
    if(!topjets_deta_selection)
      return false;

    bool invMtopjet_selection = invMtopjet_sel->passes(event);
    bool invMtopjet_SDselection = invMtopjet_SDsel->passes(event);

    if(invMtopjet_selection )
      {
	h_Wtopjets_compare->fill(event);
	h_topjets_compare->fill(event);
	h_Dijets_compare->fill(event);
	h_jets_compare->fill(event);
	h_compare->fill(event);

      }
    bool HIGHMtopjet_selection = HIGHmass_sel->passes(event);
    bool tau21topjet_selection = tau21topjet_sel->passes(event);
    if(!HIGHMtopjet_selection) return false;
    if(!tau21topjet_selection) return false;
    
    h_Wtopjets_VVMass->fill(event);
    h_topjets_VVMass->fill(event);
    h_Dijets_VVMass->fill(event);
    h_jets_VVMass->fill(event);
    h_VVMass->fill(event);




    //Inverted Selections for AK4
    bool jets2_invselection = jet2_invsel->passes(event);
    bool vbfetasign_invselection = vbfetasign_invsel->passes(event);
    bool vbfeta_invselection = vbfeta_invsel->passes(event);
    bool invM1000_invselection = invM1000_invsel->passes(event);

    if(jets2_invselection || vbfetasign_invselection || vbfeta_invselection || invM1000_invselection)
      h_Wtopjets_withVBF_VVMass_inverted->fill(event);


    // Selections for AK4
    bool jets2_selection = jet2_sel->passes(event);
    bool vbfetasign_selection = vbfetasign_sel->passes(event);
    bool vbfeta_selection = vbfeta_sel->passes(event);
    bool invM1000jet_selection = invM1000_sel->passes(event);

    if(!jets2_selection) return false;
    if(!vbfetasign_selection) return false;
   if(!vbfeta_selection) return false;
    if(!invM1000jet_selection) return false;
    h_Wtopjets_withVBF_invM1000->fill(event);





    // if(jets2_selection && vbfetasign_selection && vbfeta_selection) 
    //   {
    // 	h_Wtopjets_withVBF_VVMass->fill(event);
    // 	bool invM1000jet_invselection = invM1000_invsel->passes(event);
	
	
    // 	if(invM1000jet_invselection)  
    // 	  h_Wtopjets_withVBF_invM1000->fill(event);
	
    //   }

     





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
  // make sure the VBFresonanceToWWInvertedHSBModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(VBFresonanceToWWInvertedHSBModule)

}
