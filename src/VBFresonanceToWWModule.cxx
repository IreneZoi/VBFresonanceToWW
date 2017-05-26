#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/common/include/JetHists.h"
#include "UHH2/common/include/GenJetsHists.h"
#include "UHH2/common/include/NSelections.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWSelections.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWHists.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWGenTopJetHists.h"
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
  
  std::unique_ptr<JetCleaner> jetcleaner;
  std::unique_ptr<TopJetCleaner> topjetcleaner;
  
  // declare the Selections to use. Use unique_ptr to ensure automatic call of delete in the destructor,
  // to avoid memory leaks.
  std::unique_ptr<Selection> njet_sel, dijet_sel, vbfdeta_sel, vbfdeta_gensel, jet1_sel, jet2_sel, topjet1_sel, topjet2_sel, vbfetasign_sel, vbfetasign_gensel, vbfeta_sel, vbfeta_gensel;
  
  // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
  std::unique_ptr<Hists> h_nocuts, h_njet, h_dijet, h_input_topjets, h_input_jets, h_input_gentopjets, h_input_genjets;
  std::unique_ptr<Hists> h_cleaner, h_cleaner_topjets, h_cleaner_jets, h_cleaner_gentopjets, h_cleaner_genjets;
  std::unique_ptr<Hists> h_jetsel, h_jetsel_topjets, h_jetsel_jets, h_jetsel_gentopjets, h_jetsel_genjets;
  std::unique_ptr<Hists> h_vbfdeltaeta_jets, h_vbfdeltaeta_genjets;
  std::unique_ptr<Hists> h_vbfetasign_jets, h_vbfetasign_genjets;
  std::unique_ptr<Hists> h_vbfeta_jets, h_vbfeta_genjets;
  std::unique_ptr<Hists> h_Wtopjets;
  std::unique_ptr<Hists> h_Dijets;
  //  std::unique_ptr<Hists> h_GenDijets;


};


VBFresonanceToWWModule::VBFresonanceToWWModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.
    
    cout << "Hello World from VBFresonanceToWWModule!" << endl;
    
    // If needed, access the configuration of the module here, e.g.:
    string testvalue = ctx.get("TestKey", "<not set>");
    cout << "TestKey in the configuration was: " << testvalue << endl;
    
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
    common->disable_mcpileupreweight(); //irene                                                                                                                                                             
    common->disable_metfilters(); //irene                                                                                                                                                                   
    if(PRINT) cout << "common" <<endl;
    //    common->set_jet_id(PtEtaCut(30.0, 2.4)); 
    common->init(ctx);
    jetcleaner.reset(new JetCleaner(ctx, 30.0, 2.4)); 
    topjetcleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(200., 2.5))));

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

    // 3. Set up Hists classes:
    h_nocuts.reset(new VBFresonanceToWWHists(ctx, "NoCuts"));
    h_njet.reset(new VBFresonanceToWWHists(ctx, "Njet"));
    h_dijet.reset(new VBFresonanceToWWHists(ctx, "Dijet"));
    h_input_topjets.reset(new TopJetHists(ctx, "input_TopJet"));
    h_input_jets.reset(new JetHists(ctx, "input_Jet"));
    h_input_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "input_GenTopJet"));
    h_input_genjets.reset(new GenJetsHists(ctx, "input_GenJet"));

    h_cleaner.reset(new VBFresonanceToWWHists(ctx, "cleaner"));
    h_cleaner_topjets.reset(new TopJetHists(ctx, "cleaner_TopJet"));
    h_cleaner_jets.reset(new JetHists(ctx, "cleaner_Jet"));
    h_cleaner_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "cleaner_GenTopJet"));
    h_cleaner_genjets.reset(new GenJetsHists(ctx, "cleaner_GenJet"));

    h_jetsel.reset(new VBFresonanceToWWHists(ctx, "jetsel"));
    h_jetsel_topjets.reset(new TopJetHists(ctx, "jetsel_TopJet"));
    h_jetsel_jets.reset(new JetHists(ctx, "jetsel_Jet"));
    h_jetsel_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "jetsel_GenTopJet"));
    h_jetsel_genjets.reset(new GenJetsHists(ctx, "jetsel_GenJet"));

    h_vbfdeltaeta_jets.reset(new JetHists(ctx, "vbfdeltaeta_Jet"));
    h_vbfdeltaeta_genjets.reset(new GenJetsHists(ctx, "vbfdeltaeta_GenJet"));

    h_vbfetasign_jets.reset(new JetHists(ctx, "vbfetasign_Jet"));
    h_vbfetasign_genjets.reset(new GenJetsHists(ctx, "vbfetasign_GenJet"));

    h_vbfeta_jets.reset(new JetHists(ctx, "vbfeta_Jet"));
    h_vbfeta_genjets.reset(new GenJetsHists(ctx, "vbfeta_GenJet"));

    h_Wtopjets.reset(new VBFresonanceToWW_WTopJetHists(ctx, "WTopJet"));
    h_Dijets.reset(new VBFresonanceToWWDiJetHists(ctx, "DiJet"));
    //    h_GenDijets.reset(new VBFresonanceToWWGenDiJetHists(ctx, "DiJet"));

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
    
    cout << "VBFresonanceToWWModule: Starting to process event (runid, eventid) = (" << event.run << ", " << event.event << "); weight = " << event.weight << endl;
    


    // keep Jets *before cleaning* to store them in the ntuple if event is accepted   
    std::unique_ptr< std::vector<Jet> >    uncleaned_jets   (new std::vector<Jet>   (*event.jets));   
    std::unique_ptr< std::vector<TopJet> > uncleaned_topjets(new std::vector<TopJet>(*event.topjets));


    // 1. run all modules other modules.
    common->process(event);
    
    // 2. test selections and fill histograms
    h_nocuts->fill(event);
    h_input_topjets->fill(event);
    h_input_jets->fill(event);
    h_input_gentopjets->fill(event);
    h_input_genjets->fill(event);
    
    jetcleaner->process(event);
    topjetcleaner->process(event);

    h_cleaner->fill(event);
    h_cleaner_topjets->fill(event);
    h_cleaner_jets->fill(event);
    h_cleaner_gentopjets->fill(event);
    h_cleaner_genjets->fill(event);


    bool njet_selection = njet_sel->passes(event);
    if(njet_selection){
        h_njet->fill(event);
    }

       bool jets_selection = (jet2_sel->passes(event) && topjet2_sel->passes(event));
       if(!jets_selection) return false;

    h_jetsel->fill(event);
    h_jetsel_topjets->fill(event);
    h_jetsel_jets->fill(event);
    h_jetsel_gentopjets->fill(event);
    h_jetsel_genjets->fill(event);

    h_Wtopjets->fill(event);


    bool dijet_selection = dijet_sel->passes(event);
    if(dijet_selection){
        h_dijet->fill(event);
    }
    bool vbfdeta_selection = vbfdeta_sel->passes(event);
    if(vbfdeta_selection){
      cout << "vbfdeta_selection jets" <<endl;
      h_vbfdeltaeta_jets->fill(event);
      if(PRINT) cout << "vbfdeta_selection jets" <<endl;
    }
    bool vbfdeta_genselection = vbfdeta_gensel->passes(event);
    if(vbfdeta_genselection){
      h_vbfdeltaeta_genjets->fill(event);
    }

    bool vbfetasign_selection = vbfetasign_sel->passes(event);
    if(vbfetasign_selection){
      h_vbfetasign_jets->fill(event);
      if(PRINT) cout << "vbfdeta_selection jets" <<endl;
    }
    bool vbfetasign_genselection = vbfetasign_gensel->passes(event);
    if(vbfetasign_genselection){
      h_vbfetasign_genjets->fill(event);
    }

    bool vbfeta_selection = vbfeta_sel->passes(event);
    if(vbfeta_selection){
      h_vbfeta_jets->fill(event);
      if(PRINT) cout << "vbfdeta_selection jets" <<endl;
      h_Dijets->fill(event);

    }
    bool vbfeta_genselection = vbfeta_gensel->passes(event);
    if(vbfeta_genselection){
      h_vbfeta_genjets->fill(event);
      //      h_GenDijets->fill(event);
    }

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
