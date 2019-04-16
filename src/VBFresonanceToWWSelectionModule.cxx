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
#define L1pref false

using namespace std;
using namespace uhh2;

namespace uhh2examples {

  /** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
   *
   * This is the central class which calls other AnalysisModules, Hists or Selection classes.
   * This AnalysisModule, in turn, is called (via AnalysisModuleRunner) by SFrame.
   */
  class VBFresonanceToWWSelectionModule: public AnalysisModule {
  public:


    explicit VBFresonanceToWWSelectionModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    std::string channel_;

    std::unique_ptr<uhh2::AnalysisModule> MCWeightModule;
    std::unique_ptr<uhh2::AnalysisModule> MCPileupReweightModule;

    std::unique_ptr<AnalysisModule> Gen_printer;

    //102X    std::unique_ptr<L1PrefiringSF> jet_L1PrefiringSF;

    std::unique_ptr<JetCleaner> jetcleaner;

    //102X    std::unique_ptr<JetCleaner> ak4pfidfilter;

    //********** SELECTIONS ***************
    // declare the Selections to use. Use unique_ptr to ensure automatic call of delete in the destructor,
    // to avoid memory leaks.

    //W jets
    std::unique_ptr<Selection> topjet2_sel;
    std::unique_ptr<Selection> invMtopjet_fitsel;
    std::unique_ptr<Selection> invMtopjet_SDsel;
    std::unique_ptr<Selection> topjets_deta_sel;
    std::unique_ptr<Selection> VVmass_sel, WWmass_sel;
    std::unique_ptr<Selection> tau21topjetHP_sel;
    //VBF jets
    std::unique_ptr<Selection> jet2_sel;
    std::unique_ptr<Selection> vbfdeta_sel;
    std::unique_ptr<Selection> vbfetasign_sel;
    std::unique_ptr<Selection> vbfeta45_sel;
    std::unique_ptr<Selection> invM800_sel;

    //********** HISTOS ***************
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
    std::unique_ptr<Hists> h_Wtopjets_compare;
    std::unique_ptr<Hists> h_topjets_compare;
    std::unique_ptr<Hists> h_Dijets_compare;
    std::unique_ptr<Hists> h_jets_compare;
    std::unique_ptr<Hists> h_compare;
    std::unique_ptr<Hists> h_event_compare;

    std::unique_ptr<Hists> h_Wtopjets_compareSD;
    std::unique_ptr<Hists> h_Wtopjets_compareTAU;

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

    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM800;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM800_de4;
    std::unique_ptr<Hists> h_Dijets_VBF_invM800_de4;

    std::unique_ptr<Hists> h_input_gentopjets;
    std::unique_ptr<Hists> h_input_gendijets;
    std::unique_ptr<Hists> h_input_genjets;
    std::unique_ptr<Hists> h_input_genparticle;

    bool isMC;

    //102X    JetId AK4PFID;
    TopJetId AK8PFID;
  };


  VBFresonanceToWWSelectionModule::VBFresonanceToWWSelectionModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.

    cout << "Hello World from VBFresonanceToWWSelectionModule!" << endl;

    Gen_printer.reset(new GenParticlesPrinter(ctx));

    // If needed, access the configuration of the module here, e.g.:
    string testvalue = ctx.get("TestKey", "<not set>");
    cout << "TestKey in the configuration was: " << testvalue << endl;


    //choose channel from .xml file
    isMC = (ctx.get("dataset_type") == "MC");
    if(PRINT) cout << "isMC? " << isMC << endl;

    channel_ = ctx.get("channel");

    if(PRINT) cout << "channel " << ctx.get("channel") << endl;

    // If running in SFrame, the keys "dataset_version", "dataset_type", "dataset_lumi",
    // and "target_lumi" are set to the according values in the xml file. For CMSSW, these are
    // not set automatically, but can be set in the python config file.
    for(auto & kv : ctx.get_all()){
      cout << " " << kv.first << " = " << kv.second << endl;
    }

    if(isMC){
      MCWeightModule.reset(new MCLumiWeight(ctx));
      MCPileupReweightModule.reset(new MCPileupReweight(ctx));
      //h_weight_pu =ctx.get_handle<float>("weight_pu");
    }



    if(PRINT) cout << " LUMI and PU done " << endl;


    if(PRINT && L1pref) cout << "before reset L1" << endl;
    //    jet_L1PrefiringSF.reset(new L1PrefiringSF(ctx, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/Jet_L1IsoEG30eff_bxm1_looseJet_2016H.root","jets"));
    //    jet_L1PrefiringSF.reset(new L1PrefiringSF(ctx, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/Map_Jet_L1IsoEG30eff_bxm1_looseJet_SingleMuon_Run2016B-F.root","jets"));
    //    jet_L1PrefiringSF.reset(new L1PrefiringSF(ctx, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/Map_Jet_L1IsoEG30eff_bxm1_looseJet_SingleMuon_Run2016B-H.root","jets"));
    //    jet_L1PrefiringSF.reset(new L1PrefiringSF(ctx, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/Map_Jet_L1IsoEG30eff_bxm1_looseJet_JetHT_Run2016B-H.root","jets"));
    //102X    jet_L1PrefiringSF.reset(new L1PrefiringSF(ctx, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/L1prefiring_jet_2017BtoF.root","jets"));
    if(PRINT && L1pref) cout << "after reset L1" << endl;


    jetcleaner.reset(new JetCleaner(ctx, 30.0, 5));
    //102X    AK4PFID=JetPFID(JetPFID::WP_LOOSE_PUPPI);
    //102Xak4pfidfilter.reset(new JetCleaner(ctx,AK4PFID));


    if(PRINT) cout << "cleaners" <<endl;





    // 2. set up selections ***

    topjet2_sel.reset(new NTopJetSelection(2)); // at least 2 jets
    invMtopjet_fitsel.reset(new invMassTopjetSelection()); // see VBFresonanceToWWSelections
    topjets_deta_sel.reset(new deltaEtaTopjetSelection()); // see VBFresonanceToWWSelections
    invMtopjet_SDsel.reset(new invMassTopjetSelection(1080.0f)); // see VBFresonanceToWWSelections
    VVmass_sel.reset(new VVMassTopjetSelection());// see VBFresonanceToWWSelections
    tau21topjetHP_sel.reset(new nSubjTopjetSelection(0.f,0.35f)); // see VBFresonanceToWWSelections
    jet2_sel.reset(new NJetSelection(2)); // at least 2 jets
    vbfdeta_sel.reset(new VBFdeltaEtajetSelection(3.0f)); // see VBFresonanceToWWSelections
    vbfetasign_sel.reset(new VBFEtaSignjetSelection()); // see VBFresonanceToWWSelections
    vbfeta45_sel.reset(new VBFEtajetSelection(4.5f)); // see VBFresonanceToWWSelections
    invM800_sel.reset(new invMassVBFjetSelection(800.0f)); // see VBFresonanceToWWSelections
    if(PRINT) cout << "reset sel" <<endl;


    // 3. Set up Hists classes:
    //102X    h_Wtopjets_compare.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_compare"));
    h_Wtopjets_compare.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_compare"));
    h_topjets_compare.reset(new TopJetHists(ctx, "topjets_compare"));
    h_Dijets_compare.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_compare"));
    h_jets_compare.reset(new JetHists(ctx, "jets_compare"));
    h_compare.reset(new VBFresonanceToWWHists(ctx, "compare"));
    h_event_compare.reset(new EventHists(ctx, "event_compare"));

    //102X    h_Wtopjets_compareSD.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_compareSD"));
    //102Xh_Wtopjets_compareTAU.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_compareTAU"));
    h_Wtopjets_compareSD.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_compareSD"));
    h_Wtopjets_compareTAU.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_compareTAU"));


    //102X    h_Wtopjets_VVMass.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VVMass"));
    h_Wtopjets_VVMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VVMass"));
    h_topjets_VVMass.reset(new TopJetHists(ctx, "topjets_VVMass"));
    h_Dijets_VVMass.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VVMass"));
    h_jets_VVMass.reset(new JetHists(ctx, "jets_VVMass"));
    h_VVMass.reset(new VBFresonanceToWWHists(ctx, "VVMass"));

    //102X    h_Wtopjets_VVMass_tau21HP.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VVMass_tau21HP"));
    h_Wtopjets_VVMass_tau21HP.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VVMass_tau21HP"));
    h_topjets_VVMass_tau21HP.reset(new TopJetHists(ctx, "topjets_VVMass_tau21HP"));
    h_Dijets_VVMass_tau21HP.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VVMass_tau21HP"));
    h_jets_VVMass_tau21HP.reset(new JetHists(ctx, "jets_VVMass_tau21HP"));

    //102X    h_Wtopjets_AK4cleaner.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_AK4cleaner"));
    h_Wtopjets_AK4cleaner.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_AK4cleaner"));
    h_jets_AK4cleaner.reset(new JetHists(ctx, "jets_AK4cleaner"));

    h_jets_2jetsel.reset(new JetHists(ctx, "jets_2AK4"));
    //102X    h_Wtopjets_2jetsel.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_2AK4"));
    h_Wtopjets_2jetsel.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_2AK4"));

    h_jets_vbfetasign.reset(new JetHists(ctx, "jets_vbfetasign"));
    //102X    h_Wtopjets_vbfetasign.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_vbfetasign"));
    h_Wtopjets_vbfetasign.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_vbfetasign"));

    h_VBF_VVMass.reset(new VBFresonanceToWWHists(ctx, "VBF_VVMass"));
    h_Dijets_VBF_VVMass.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_VVMass"));
    h_jets_VBF_VVMass.reset(new JetHists(ctx, "jets_VBF_VVMass"));
    //102X    h_Wtopjets_withVBF_VVMass.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_withVBF_VVMass"));
    h_Wtopjets_withVBF_VVMass.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_VVMass"));
    h_topjets_withVBF_VVMass.reset(new TopJetHists(ctx, "topjets_withVBF_VVMass"));

    h_Dijets_VBF_VVMass_tau21HP.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_VVMass_tau21HP"));
    h_jets_VBF_VVMass_tau21HP.reset(new JetHists(ctx, "jets_VBF_VVMass_tau21HP"));
    //102X    h_Wtopjets_withVBF_VVMass_tau21HP.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_withVBF_VVMass_tau21HP"));
    h_Wtopjets_withVBF_VVMass_tau21HP.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_withVBF_VVMass_tau21HP"));
    h_topjets_withVBF_VVMass_tau21HP.reset(new TopJetHists(ctx, "topjets_withVBF_VVMass_tau21HP"));

    //102X    h_Wtopjets_withVBF_invM800.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VBF_invM800"));
    //102X    h_Wtopjets_withVBF_invM800_de4.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VBF_invM800_de45"));
    h_Wtopjets_withVBF_invM800.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VBF_invM800"));
    h_Wtopjets_withVBF_invM800_de4.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VBF_invM800_de45"));
    h_Dijets_VBF_invM800_de4.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_invM800_45"));



    //genjet

    h_input_genparticle.reset(new VBFresonanceToWWParticleHists(ctx, "GenParticle"));
    h_input_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "input_GenTopJet"));
    h_input_gendijets.reset(new VBFresonanceToWWGenDiJetHists(ctx, "input_GenDiJet"));
    h_input_genjets.reset(new GenJetsHists(ctx, "input_GenJet"));

    if(PRINT) cout << "hist setup" <<endl;


  }


  bool VBFresonanceToWWSelectionModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.
    if(PRINT)    cout << "VBFresonanceToWWSelectionModule: Starting to process event (runid, eventid) = (" << event.run << ", " <<", " << event.event << "); weight = " << event.weight << endl;

    if(isMC){
      MCWeightModule->process(event);
      MCPileupReweightModule->process(event);
      //event.weight *= event.get(h_weight_pu);
    }


    h_Wtopjets_compare->fill(event);
    if(PRINT) std::cout<<"compare "<<std::endl;
    h_topjets_compare->fill(event);
    h_Dijets_compare->fill(event);
    h_jets_compare->fill(event);
    h_compare->fill(event);
    h_event_compare->fill(event);



    bool invMtopjet_SDselection = invMtopjet_SDsel->passes(event);
    if(PRINT) std::cout<<"sd "<<std::endl;
    bool tau21topjetHP_selection = tau21topjetHP_sel->passes(event);
    if(PRINT) std::cout<<"tau21 "<<std::endl;
      if(PRINT) std::cout<<"compare and sd "<<std::endl;

    bool VVMtopjet_selection = VVmass_sel->passes(event);

    if(VVMtopjet_selection)
      h_Wtopjets_compareSD->fill(event);
    if(tau21topjetHP_selection)
      h_Wtopjets_compareTAU->fill(event);

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
    //102X    ak4pfidfilter->process(event);
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


    //    bool vbfeta_selection = vbfeta_sel->passes(event);
    bool vbfeta45_selection = vbfeta45_sel->passes(event);

    if(!vbfeta45_selection) return false;

    h_VBF_VVMass->fill(event);
    h_jets_VBF_VVMass->fill(event);
    h_Dijets_VBF_VVMass->fill(event);
    h_Wtopjets_withVBF_VVMass->fill(event);
    h_topjets_withVBF_VVMass->fill(event);
    if(PRINT) std::cout<<"VBF "<<std::endl;


    bool invM800jet_selection = invM800_sel->passes(event);



    if(!invM800jet_selection) return false;
    h_Wtopjets_withVBF_invM800->fill(event);

    if(!vbfeta45_selection) return false;
    h_Wtopjets_withVBF_invM800_de4->fill(event);
    h_Dijets_VBF_invM800_de4->fill(event);
    //102X    if(L1pref)	jet_L1PrefiringSF->process(event);



    // 3. decide whether or not to keep the current event in the output:
    return true;

  }


  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the VBFresonanceToWWSelectionModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(VBFresonanceToWWSelectionModule)

}
