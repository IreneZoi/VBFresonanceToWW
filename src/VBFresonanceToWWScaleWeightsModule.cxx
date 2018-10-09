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
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWW_WTopJetPDFHists.h"
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
  class VBFresonanceToWWScaleWeightsModule: public AnalysisModule {
  public:
    

    explicit VBFresonanceToWWScaleWeightsModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    std::string channel_;

    std::unique_ptr<uhh2::AnalysisModule> MCWeightModule;
    uhh2::Event::Handle<float> h_weight_pu;
    std::unique_ptr<uhh2::AnalysisModule> MCScaleModule;

    //********** HISTOS ***************  
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.

       
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM800_de45;
    std::unique_ptr<Hists> h_Wtopjets_withVBF_invM800_de45_scaled;

    const int runnr_BCD = 276811;
    const int runnr_EF = 278802;
    const int runnr_G = 280385;

    bool isMC;

    JetId AK4PFID;
  };


  VBFresonanceToWWScaleWeightsModule::VBFresonanceToWWScaleWeightsModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.
    
    cout << "Hello World from VBFresonanceToWWScaleWeightsModule!" << endl;

    
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
      h_weight_pu =ctx.get_handle<float>("weight_pu");
      MCScaleModule.reset(new MCScaleVariation(ctx));

    }



    // 3. Set up Hists classes:
 
    h_Wtopjets_withVBF_invM800_de45.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VBF_invM800_de45"));
    h_Wtopjets_withVBF_invM800_de45_scaled.reset(new VBFresonanceToWW_WTopJetHistsCorrectedSDMass(ctx, "Wtopjets_VBF_invM800_de45_scaled"));
    if(PRINT) cout << "hist setup" <<endl;


  }


  bool VBFresonanceToWWScaleWeightsModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.
    
    if(PRINT)    cout << "VBFresonanceToWWScaleWeightsModule: Starting to process event (runid, eventid) = (" << event.run << ", " <<", " << event.event << "); weight = " << event.weight << " pileupe weight = "<< event.get(h_weight_pu) << endl;

    if(isMC)
      MCWeightModule->process(event);

    double eventweight = event.weight;
    double eventweight_nominal = 1;//eventweight*event.get(h_weight_pu);
    
    if(isMC)
      {
	eventweight_nominal = eventweight*event.get(h_weight_pu);
      }
    
    // for(int i = 0; i<event.genInfo->weights().size();i++)
    //   cout << " event.genInfo->weights() " << i << " " << event.genInfo->weights().at(i) << endl;

    if(isMC) event.weight = eventweight_nominal;
    h_Wtopjets_withVBF_invM800_de45->fill(event);
    if(PRINT) cout << " before scaling, event weight is " << event.weight << endl;
    if(isMC) MCScaleModule->process(event);
    if(PRINT) cout << " after scaling, event weight is " << event.weight << endl;
    h_Wtopjets_withVBF_invM800_de45_scaled->fill(event);

    // 3. decide whether or not to keep the current event in the output:
    return true;

  }


  // as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
  // make sure the VBFresonanceToWWScaleWeightsModule is found by class name. This is ensured by this macro:
  UHH2_REGISTER_ANALYSIS_MODULE(VBFresonanceToWWScaleWeightsModule)

}
