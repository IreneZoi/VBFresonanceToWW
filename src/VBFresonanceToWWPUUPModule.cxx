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
  class VBFresonanceToWWPUUPModule: public AnalysisModule {
  public:
    

    explicit VBFresonanceToWWPUUPModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    std::string channel_;

    std::unique_ptr<uhh2::AnalysisModule> MCWeightModule;
    std::unique_ptr<uhh2::AnalysisModule> MCPileupReweightModule;
    std::unique_ptr<uhh2::AnalysisModule> MCPileupReweightModuleUP;
    uhh2::Event::Handle<float> h_weight_pu;

    std::unique_ptr<AnalysisModule> Gen_printer;  

    //102X    std::unique_ptr<L1PrefiringSF> jet_L1PrefiringSF;

    std::unique_ptr<JetCleaner> jetcleaner;

    std::unique_ptr<JetCleaner> ak4pfidfilter;

    //********** SELECTIONS ***************  
    // declare the Selections to use. Use unique_ptr to ensure automatic call of delete in the destructor,
    // to avoid memory leaks.
    std::unique_ptr<Selection> muon_sel, electron_sel;//lepton veto
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
    std::unique_ptr<Selection> vbfeta_sel, vbfeta35_sel, vbfeta4_sel, vbfeta45_sel, vbfeta5_sel, vbfeta55_sel, vbfeta6_sel;
    std::unique_ptr<Selection> invM800_sel;
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

    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM1000;
    std::unique_ptr<Hists> h_Dijets_VBF_invM1000;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM1000_de4;

    
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

    JetId AK4PFID;
    TopJetId AK8PFID;
  };


  VBFresonanceToWWPUUPModule::VBFresonanceToWWPUUPModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.
    
    cout << "Hello World from VBFresonanceToWWPUUPModule!" << endl;

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
      if(PRINT) cout << " LUMI done " << endl;

      MCPileupReweightModule.reset(new MCPileupReweight(ctx,"up"));
      //      MCPileupReweightModuleUP.reset(new MCPileupReweight(ctx,"up"));
      //      h_weight_pu =ctx.get_handle<float>("weight_pu");
      if(PRINT) cout << " PU done " << endl;

    }



    if(PRINT) cout << " LUMI and PU done " << endl;


    if(PRINT && L1pref) cout << "before reset L1" << endl;
    //    jet_L1PrefiringSF.reset(new L1PrefiringSF(ctx, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/Jet_L1IsoEG30eff_bxm1_looseJet_2016H.root","jets"));
    //    jet_L1PrefiringSF.reset(new L1PrefiringSF(ctx, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/Map_Jet_L1IsoEG30eff_bxm1_looseJet_SingleMuon_Run2016B-F.root","jets"));
    //    jet_L1PrefiringSF.reset(new L1PrefiringSF(ctx, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/Map_Jet_L1IsoEG30eff_bxm1_looseJet_SingleMuon_Run2016B-H.root","jets"));
    //102X    jet_L1PrefiringSF.reset(new L1PrefiringSF(ctx, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/Map_Jet_L1IsoEG30eff_bxm1_looseJet_JetHT_Run2016B-H.root","jets"));
    if(PRINT && L1pref) cout << "after reset L1" << endl;


    jetcleaner.reset(new JetCleaner(ctx, 30.0, 5)); 
    AK4PFID=JetPFID(JetPFID::WP_LOOSE_PUPPI);
    ak4pfidfilter.reset(new JetCleaner(ctx,AK4PFID));


    if(PRINT) cout << "cleaners" <<endl;
    



    
    // 2. set up selections ***

    muon_sel.reset(new MuonVeto(0.8,MuId)); // see VBFresonanceToWWSelections
    electron_sel.reset(new ElectronVeto(0.8,EleId)); // see VBFresonanceToWWSelections

    topjet2_sel.reset(new NTopJetSelection(2)); // at least 2 jets      
    invMtopjet_fitsel.reset(new invMassTopjetSelection()); // see VBFresonanceToWWSelections
    topjets_deta_sel.reset(new deltaEtaTopjetSelection()); // see VBFresonanceToWWSelections
    invMtopjet_SDsel.reset(new invMassTopjetSelection(1080.0f)); // see VBFresonanceToWWSelections
    VVmass_sel.reset(new VVMassTopjetSelection());// see VBFresonanceToWWSelections
    tau21topjetHP_sel.reset(new nSubjTopjetSelection(0.f,0.35f)); // see VBFresonanceToWWSelections
    jet2_sel.reset(new NJetSelection(2)); // at least 2 jets      
    vbfdeta_sel.reset(new VBFdeltaEtajetSelection(3.0f)); // see VBFresonanceToWWSelections
    vbfetasign_sel.reset(new VBFEtaSignjetSelection()); // see VBFresonanceToWWSelections
    vbfeta_sel.reset(new VBFEtajetSelection()); // see VBFresonanceToWWSelections
    vbfeta4_sel.reset(new VBFEtajetSelection(4.0f)); // see VBFresonanceToWWSelections
    invM800_sel.reset(new invMassVBFjetSelection(800.0f)); // see VBFresonanceToWWSelections
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



    h_Wtopjets_withVBF_invM800.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VBF_invM800"));
    h_Wtopjets_withVBF_invM800_de4.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VBF_invM800_de4"));
    h_Dijets_VBF_invM800_de4.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_invM800_45"));
    h_Wtopjets_withVBF_invM1000.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VBF_invM1000"));
    h_Dijets_VBF_invM1000.reset(new VBFresonanceToWWDiJetHists(ctx, "Dijets_VBF_invM1000"));
    h_Wtopjets_withVBF_invM1000_de4.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VBF_invM1000_de4"));


    //genjet

    h_input_genparticle.reset(new VBFresonanceToWWParticleHists(ctx, "GenParticle"));
    h_input_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "input_GenTopJet"));
    h_input_gendijets.reset(new VBFresonanceToWWGenDiJetHists(ctx, "input_GenDiJet"));
    h_input_genjets.reset(new GenJetsHists(ctx, "input_GenJet"));

    if(PRINT) cout << "hist setup" <<endl;


  }


  bool VBFresonanceToWWPUUPModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.
    
    if(PRINT)    cout << "VBFresonanceToWWPUUPModule: Starting to process event (runid, eventid) = (" << event.run << ", " <<", " << event.event << "); weight = " << event.weight << endl;
    

    if(isMC){
      MCWeightModule->process(event);
      if(PRINT)    cout << " Lumi processed " << endl;
      // MCPileupReweightModuleUP->process(event);
      // if(PRINT)    cout << " PU UP processed " << endl;

      MCPileupReweightModule->process(event);
      //event.weight *= event.get(h_weight_pu);
      if(PRINT)    cout << " PU processed " << endl;
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
    if(invMtopjet_SDselection && tau21topjetHP_selection)
      h_Wtopjets_compareSD->fill(event);
    if(PRINT) std::cout<<"compare and sd "<<std::endl;

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
    bool vbfeta4_selection = vbfeta4_sel->passes(event);

    if(!vbfeta_selection) return false;

    h_VBF_VVMass->fill(event);
    h_jets_VBF_VVMass->fill(event);
    h_Dijets_VBF_VVMass->fill(event);
    h_Wtopjets_withVBF_VVMass->fill(event);
    h_topjets_withVBF_VVMass->fill(event);
    if(PRINT) std::cout<<"VBF "<<std::endl;


    bool invM800jet_selection = invM800_sel->passes(event);
    bool invM1000jet_selection = invM1000_sel->passes(event);



    if(!invM800jet_selection) return false;
    h_Wtopjets_withVBF_invM800->fill(event);
    if(vbfeta4_selection)
      {
	h_Wtopjets_withVBF_invM800_de4->fill(event);
	h_Dijets_VBF_invM800_de4->fill(event);
	//102X	if(L1pref)	jet_L1PrefiringSF->process(event);
      }

    if(!invM1000jet_selection) return false;
    h_Dijets_VBF_invM1000->fill(event);
    h_Wtopjets_withVBF_invM1000->fill(event);
    if(vbfeta4_selection)
      h_Wtopjets_withVBF_invM1000_de4->fill(event);

    if(PRINT) std::cout<<"VBF 1000"<<std::endl;


    // 3. decide whether or not to keep the current event in the output:
    return true;

  }


  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the VBFresonanceToWWPUUPModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(VBFresonanceToWWPUUPModule)

}
