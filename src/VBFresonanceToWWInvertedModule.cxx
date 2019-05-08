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
  class VBFresonanceToWWInvertedModule: public AnalysisModule {
  public:


    explicit VBFresonanceToWWInvertedModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    std::string channel_;
    std::unique_ptr<uhh2::AnalysisModule> MCWeightModule;
    std::unique_ptr<uhh2::AnalysisModule> MCPileupReweightModule;

    std::unique_ptr<AnalysisModule> Gen_printer;


    std::unique_ptr<JetCleaner> jetcleaner;
    //102X    std::unique_ptr<JetCleaner> ak4pfidfilter;

    // Data/MC scale factors
    std::unique_ptr<uhh2::AnalysisModule> pileup_SF;
    std::unique_ptr<uhh2::AnalysisModule> lumiweight;

    //********** SELECTIONS ***************
    // declare the Selections to use. Use unique_ptr to ensure automatic call of delete in the destructor,
    // to avoid memory leaks.

    //W jets
    std::unique_ptr<Selection> topjet2_sel;
    std::unique_ptr<Selection> invMtopjet_fitsel;
    std::unique_ptr<Selection> invMtopjet_sel;
    std::unique_ptr<Selection> invMtopjet_SDsel;
    std::unique_ptr<Selection> topjets_deta_sel;
    std::unique_ptr<Selection> VVmass_sel;
    std::unique_ptr<Selection> tau21topjet_sel;
    //VBF jets
    std::unique_ptr<Selection> jet2_sel;
    std::unique_ptr<Selection> vbfdeta_sel;
    std::unique_ptr<Selection> vbfetasign_sel;
    std::unique_ptr<Selection> vbfeta_sel;
    std::unique_ptr<Selection> invM800_sel;
    //inverted VBF jets
    std::unique_ptr<Selection> jet2_invsel;
    std::unique_ptr<Selection> vbfetasign_invsel;
    std::unique_ptr<Selection> vbfeta_invsel;
    std::unique_ptr<Selection> invM800_invsel;


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
    std::unique_ptr<Hists> h_withVBF_VVMass;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_VVMass_inverted;
    std::unique_ptr<Hists> h_withVBF_VVMass_inverted;
    std::unique_ptr<Hists> h_Dijets_VBF_VVMass_inverted;

    std::unique_ptr<Hists> h_VBF_VVMass;
    std::unique_ptr<Hists> h_jets_VBF_VVMass;
    std::unique_ptr<Hists> h_Dijets_VBF_VVMass;
    std::unique_ptr<Hists> h_topjets_withVBF_VVMass;


    // std::unique_ptr<Hists> h_Dijets_VBF_invM800;
    // std::unique_ptr<Hists> h_Wtopjets_withVBF_invM800;


    std::unique_ptr<Hists> h_input_gentopjets;
    std::unique_ptr<Hists> h_input_gendijets;
    std::unique_ptr<Hists> h_input_genjets;
    std::unique_ptr<Hists> h_input_genparticle;

    bool isMC;
    //102X    JetId AK4PFID;
  };


  VBFresonanceToWWInvertedModule::VBFresonanceToWWInvertedModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.

    cout << "Hello World from VBFresonanceToWWInvertedModule!" << endl;

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


    if(isMC){
      MCWeightModule.reset(new MCLumiWeight(ctx));
      MCPileupReweightModule.reset(new MCPileupReweight(ctx));
    //  MCPileupReweightModule.reset(new MCPileupReweight(ctx,"up"));
    //  MCPileupReweightModule.reset(new MCPileupReweight(ctx,"down"));

    }




    // 1. setup other modules. CommonModules and the JetCleaner:

    jetcleaner.reset(new JetCleaner(ctx, 30.0, 5));

    //102X    AK4PFID=JetPFID(JetPFID::WP_LOOSE_PUPPI);
    //102Xak4pfidfilter.reset(new JetCleaner(ctx,AK4PFID));

    if(PRINT) cout << "cleaners" <<endl;





    // note that the JetCleaner is only kept for the sake of example;
    // instead of constructing a jetcleaner explicitly,
    // the cleaning can also be achieved with less code via CommonModules with:
    // common->set_jet_id(PtEtaCut(30.0, 2.4));
    // before the 'common->init(ctx)' line.

    // 2. set up selections ***

    topjet2_sel.reset(new NTopJetSelection(2)); // at least 2 jets
    invMtopjet_fitsel.reset(new invMassTopjetSelection()); // see VBFresonanceToWWSelections
    topjets_deta_sel.reset(new deltaEtaTopjetSelection()); // see VBFresonanceToWWSelections
    invMtopjet_sel.reset(new invMassTopjetSelection(1070.0f)); // see VBFresonanceToWWSelections
    invMtopjet_SDsel.reset(new invMassTopjetSelection(1080.0f)); // see VBFresonanceToWWSelections
    VVmass_sel.reset(new VVMassTopjetSelection());// see VBFresonanceToWWSelections
    tau21topjet_sel.reset(new nSubjTopjetSelection(0.f,0.35f)); // see VBFresonanceToWWSelections

    jet2_sel.reset(new NJetSelection(2)); // at least 2 jets
    vbfdeta_sel.reset(new VBFdeltaEtajetSelection()); // see VBFresonanceToWWSelections
    vbfetasign_sel.reset(new VBFEtaSignjetSelection()); // see VBFresonanceToWWSelections
    vbfeta_sel.reset(new VBFEtajetSelection(4.5f)); // see VBFresonanceToWWSelections
    invM800_sel.reset(new invMassVBFjetSelection(800.0f)); // see VBFresonanceToWWSelections
    if(PRINT) cout << "reset sel" <<endl;

    //VBF inverted
    jet2_invsel.reset(new DijetInvSelection(2.f)); // at least 2 jets
    vbfetasign_invsel.reset(new VBFEtaSignjetInvSelection()); // see VBFresonanceToWWSelections
    vbfeta_invsel.reset(new VBFEtajetInvSelection(4.5f)); // see VBFresonanceToWWSelections
    invM800_invsel.reset(new invMassVBFjetInvSelection(800.0f)); // see VBFresonanceToWWSelections


    // 3. Set up Hists classes:
    //102X    h_Wtopjets_compare.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_compare"));
    h_Wtopjets_compare.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_compare"));
    h_topjets_compare.reset(new TopJetHists(ctx, "topjets_compare"));
    h_Dijets_compare.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_compare"));
    h_jets_compare.reset(new JetHists(ctx, "jets_compare"));
    h_compare.reset(new VBFresonanceToWWHists(ctx, "compare"));

    //102X    h_Wtopjets_VVMass.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VVMass"));
    h_Wtopjets_VVMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VVMass"));
    h_topjets_VVMass.reset(new TopJetHists(ctx, "topjets_VVMass"));
    h_Dijets_VVMass.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VVMass"));
    h_jets_VVMass.reset(new JetHists(ctx, "jets_VVMass"));
    h_VVMass.reset(new VBFresonanceToWWHists(ctx, "VVMass"));

    //102X    h_Wtopjets_withVBF_VVMass.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_withVBF_VVMass"));
    h_Wtopjets_withVBF_VVMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_VVMass"));
    h_withVBF_VVMass.reset(new VBFresonanceToWWHists(ctx, "withVBF_VVMass"));

    //102X    h_Wtopjets_withVBF_VVMass_inverted.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_withVBF_VVMass_inverted"));
    h_Wtopjets_withVBF_VVMass_inverted.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_VVMass_inverted"));
    h_withVBF_VVMass_inverted.reset(new VBFresonanceToWWHists(ctx, "withVBF_VVMass_inverted"));

    h_Dijets_VBF_VVMass.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_VVMass"));
    h_Dijets_VBF_VVMass_inverted.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_VVMass_inverted"));
    // h_Wtopjets_withVBF_invM800.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VBF_invM800"));


    //genjet
    h_input_genparticle.reset(new VBFresonanceToWWParticleHists(ctx, "GenParticle"));
    h_input_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "input_GenTopJet"));
    h_input_gendijets.reset(new VBFresonanceToWWGenDiJetHists(ctx, "input_GenDiJet"));
    h_input_genjets.reset(new GenJetsHists(ctx, "input_GenJet"));

    if(PRINT) cout << "hist setup" <<endl;


  }


  bool VBFresonanceToWWInvertedModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.

    if(PRINT)    cout << "VBFresonanceToWWInvertedModule: Starting to process event (runid, eventid) = (" << event.run << ", " <<", " << event.event << "); weight = " << event.weight << endl;

    if(isMC){
      MCWeightModule->process(event);
      MCPileupReweightModule->process(event);
    }


    h_Wtopjets_compare->fill(event);
    h_topjets_compare->fill(event);
    h_Dijets_compare->fill(event);
    h_jets_compare->fill(event);
    h_compare->fill(event);
    if(PRINT)    cout << "VBFresonanceToWWInvertedModule: compare hists" << endl;


    bool VVMtopjet_selection = VVmass_sel->passes(event);
    bool tau21topjet_selection = tau21topjet_sel->passes(event);
    if(!VVMtopjet_selection) return false;
    if(!tau21topjet_selection) return false;
    if(PRINT)    cout << "VBFresonanceToWWInver VV sel" << endl;

    h_Wtopjets_VVMass->fill(event);
    h_topjets_VVMass->fill(event);
    h_Dijets_VVMass->fill(event);
    h_jets_VVMass->fill(event);
    h_VVMass->fill(event);



    jetcleaner->process(event);
    if(PRINT)    cout << "VBFresonanceToWWInver AK4cleaning" << endl;

    //Inverted Selections for AK4
    bool jets2_invselection = jet2_invsel->passes(event);
    if(PRINT)    cout << "VBFresonanceToWWInver 2 ak4 inv" << endl;

    bool vbfetasign_invselection = vbfetasign_invsel->passes(event);
    if(PRINT)    cout << "VBFresonanceToWWInver 2 ak4 sign inv" << endl;

    bool vbfeta_invselection = vbfeta_invsel->passes(event);
    if(PRINT)    cout << "VBFresonanceToWWInver 2 ak4 eta inv" << endl;

    bool invM800_invselection = invM800_invsel->passes(event);
    if(PRINT)    cout << "VBFresonanceToWWInver 2 ak4 mass inv" << endl;

//    if(ptjets1_invselection || jets2_invselection || vbfetasign_invselection || vbfeta_invselection || invM800_invselection)
    if(jets2_invselection || vbfetasign_invselection || vbfeta_invselection || invM800_invselection)
      {
	       h_Wtopjets_withVBF_VVMass_inverted->fill(event);
	       if(PRINT)    cout << "VBFresonanceToWWInver ak8 plots inv" << endl;
         h_Dijets_VBF_VVMass_inverted->fill(event);
	       h_withVBF_VVMass_inverted->fill(event);
      }

    if(PRINT)    cout << "VBFresonanceToWWInver VBF inv sel" << endl;

    // Selections for AK4
    bool jets2_selection = jet2_sel->passes(event);
    bool vbfetasign_selection = vbfetasign_sel->passes(event);
    bool vbfeta_selection = vbfeta_sel->passes(event);
    bool invM800jet_selection = invM800_sel->passes(event);

    //if(!ptjets1_selection) return false;
    if(!jets2_selection) return false;
    if(!vbfetasign_selection) return false;
    if(!vbfeta_selection) return false;
    if(!invM800jet_selection) return false;
    h_Wtopjets_withVBF_VVMass->fill(event);
    h_withVBF_VVMass->fill(event);
    h_Dijets_VBF_VVMass->fill(event);

    if(PRINT)    cout << "VBFresonanceToWWInver VBF sel" << endl;



    // 3. decide whether or not to keep the current event in the output:
    return true;

  }


  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the VBFresonanceToWWInvertedModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(VBFresonanceToWWInvertedModule)

}
