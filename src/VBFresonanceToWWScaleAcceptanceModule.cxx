#include <iostream>
#include <memory>
#include <string>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CommonModules.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/MuonIds.h"
#include "UHH2/common/include/ElectronIds.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/JetCorrections.h"
#include <UHH2/common/include/MCWeight.h>
#include "UHH2/common/include/PDFWeights.h"
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
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWW_WTopJetPDFHists.h"
#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWW_WTopJetInvMHists.h"

#define PRINT false
#define PDFs 2
using namespace std;
using namespace uhh2;

namespace uhh2examples {

  /** \brief Basic analysis example of an AnalysisModule (formerly 'cycle') in UHH2
  *
  Module to calculate Scale acceptance uncertainty
  */
  class VBFresonanceToWWScaleAcceptanceModule: public AnalysisModule {
  public:


    explicit VBFresonanceToWWScaleAcceptanceModule(Context & ctx);
    virtual bool process(Event & event) override;

  private:
    std::string channel_;

    Event::Handle<vector<Jet>> h_IdCriteriaJets;
    std::unique_ptr<CommonModules> common;

    std::unique_ptr<AnalysisModule> Gen_printer;

    std::unique_ptr<JetCorrector> jet_corrector;

    std::unique_ptr<JetCorrector> jet_corrector_BCD;
    std::unique_ptr<JetCorrector> jet_corrector_EF;
    //std::unique_ptr<JetCorrector> jet_corrector_G;
    //std::unique_ptr<JetCorrector> jet_corrector_H;
    std::unique_ptr<JetCorrector> jet_corrector_GH;

    std::unique_ptr<TopJetCorrector> topjet_corrector;
    std::unique_ptr<TopJetCorrector> topjet_corrector_BCD;
    std::unique_ptr<TopJetCorrector> topjet_corrector_EF;
    //std::unique_ptr<TopJetCorrector> topjet_corrector_G;
    //std::unique_ptr<TopJetCorrector> topjet_corrector_H;
    std::unique_ptr<TopJetCorrector> topjet_corrector_GH;

    //102X    std::unique_ptr<SoftDropMassCalculator> topjet_sdmasscorrector;
    //102X    std::unique_ptr<JetMassScale> topjet_jms;


    std::unique_ptr<JetResolutionSmearer> jetER_smearer;
    std::unique_ptr<GenericJetResolutionSmearer> topjetER_smearer;

    std::unique_ptr<JetCleaner> jetcleaner;
    std::unique_ptr<TopJetCleaner> topjetcleaner;

    std::unique_ptr<JetCleaner> ak4pfidfilter;
    std::unique_ptr<TopJetCleaner> ak8pfidfilter;

    //Scale stuff
    std::unique_ptr<uhh2::AnalysisModule> MCScaleModule;

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
    std::unique_ptr<Selection> vbfeta_sel, vbfeta35_sel, vbfeta4_sel, vbfeta45_sel, vbfeta5_sel, vbfeta55_sel, vbfeta6_sel;
    std::unique_ptr<Selection> invM800_sel;



    //inverted VBF jets
    std::unique_ptr<Selection> ptjet1_invsel;
    std::unique_ptr<Selection> jet2_invsel;
    std::unique_ptr<Selection> vbfetasign_invsel;
    std::unique_ptr<Selection> vbfeta_invsel;
    std::unique_ptr<Selection> invM1000_invsel;

    //********** HISTOS ***************
    // store the Hists collection as member variables. Again, use unique_ptr to avoid memory leaks.
    // std::unique_ptr<Hists> h_Wtopjets_input;
    // std::unique_ptr<Hists> h_Wtopjets_input_pdf;
    // std::unique_ptr<Hists> h_Wtopjets_withVBF_invM800_de45;
    // std::unique_ptr<Hists> h_Wtopjets_withVBF_invM800_de45_pdf;
    std::unique_ptr<Hists> h_Wtopjets_input[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_common[PDFs];
    // std::unique_ptr<Hists> h_WtopjetsHist_common[PDFs];
    // std::unique_ptr<Hists> h_muon_common[PDFs];
    // std::unique_ptr<Hists> h_electron_common[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_muon[PDFs];
    // std::unique_ptr<Hists> h_WtopjetsHist_muon[PDFs];
    // std::unique_ptr<Hists> h_muon_muon[PDFs];
    // std::unique_ptr<Hists> h_electron_muon[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_electron[PDFs];
    // std::unique_ptr<Hists> h_electron_electron[PDFs];
    // std::unique_ptr<Hists> h_muon_electron[PDFs];
    // std::unique_ptr<Hists> h_WtopjetsHist_electron[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_correctors[PDFs];
    // std::unique_ptr<Hists> h_WtopjetsHist_correctors[PDFs];
    // std::unique_ptr<Hists> h_muon_correctors[PDFs];
    // std::unique_ptr<Hists> h_electron_correctors[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_SDMcorrectors[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_tcleaner[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_ak8filt[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_2tjets[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_corrections[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_invM[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_deta[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_VVM[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_tau21[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_2jet[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_sign[PDFs];
    // std::unique_ptr<Hists> h_Wtopjets_800[PDFs];
    std::unique_ptr<Hists> h_Wtopjets_passVBF_invM800_de45[PDFs];
    std::unique_ptr<Hists> h_Wtopjets_failVBF_invM800_de45[PDFs];

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


  VBFresonanceToWWScaleAcceptanceModule::VBFresonanceToWWScaleAcceptanceModule(Context & ctx){
    // In the constructor, the typical tasks are to initialize the
    // member variables, in particular the AnalysisModules such as
    // CommonModules or some cleaner module, Selections and Hists.
    // But you can do more and e.g. access the configuration, as shown below.

    cout << "Hello World from VBFresonanceToWWScaleAcceptanceModule!" << endl;

    Gen_printer.reset(new GenParticlesPrinter(ctx));

    // If needed, access the configuration of the module here, e.g.:
    string testvalue = ctx.get("TestKey", "<not set>");
    cout << "TestKey in the configuration was: " << testvalue << endl;


    //choose channel from .xml file
    isMC = (ctx.get("dataset_type") == "MC");
    channel_ = ctx.get("channel");
    if(isMC)
    {
      //pileup_SF.reset(new MCPileupReweight(ctx));
      //lumiweight.reset(new MCLumiWeight(ctx));
      //Scale stuff
      MCScaleModule.reset(new MCScaleVariation(ctx));
    }

    // If running in SFrame, the keys "dataset_version", "dataset_type", "dataset_lumi",
    // and "target_lumi" are set to the according values in the xml file. For CMSSW, these are
    // not set automatically, but can be set in the python config file.
    for(auto & kv : ctx.get_all()){
      cout << " " << kv.first << " = " << kv.second << endl;
    }

    // 1. setup other modules. CommonModules and the JetCleaner:
    h_IdCriteriaJets = ctx.get_handle<vector<Jet>>("patJetsAK8PFPUPPI");

    MuId  = AndId<Muon>(MuonID(Muon::Tight), PtEtaCut(30., 2.4));//102X
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
//    std::vector<std::string> JEC_AK4, JEC_AK8,JEC_AK4_BCD,JEC_AK4_EF,JEC_AK4_G,JEC_AK4_H,JEC_AK8_BCD,JEC_AK8_EF,JEC_AK8_G,JEC_AK8_H;
    std::vector<std::string> JEC_AK4, JEC_AK8,JEC_AK4_BCD,JEC_AK4_EF,JEC_AK4_G,JEC_AK4_H,JEC_AK4_GH,JEC_AK8_BCD,JEC_AK8_EF,JEC_AK8_G,JEC_AK8_H,JEC_AK8_GH;
/*
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
*/

if(isMC)
{
  JEC_AK4     = JERFiles::Summer16_07Aug2017_V11_L123_AK4PFPuppi_MC;
  JEC_AK8     = JERFiles::Summer16_07Aug2017_V11_L123_AK8PFPuppi_MC;
}
else
{
  JEC_AK4_BCD = JERFiles::Summer16_07Aug2017_V11_BCD_L123_AK4PFPuppi_DATA;
  JEC_AK4_EF  = JERFiles::Summer16_07Aug2017_V11_EF_L123_AK4PFPuppi_DATA;
  JEC_AK4_GH   = JERFiles::Summer16_07Aug2017_V11_GH_L123_AK4PFPuppi_DATA;

  JEC_AK8_BCD = JERFiles::Summer16_07Aug2017_V11_BCD_L123_AK8PFPuppi_DATA;
  JEC_AK8_EF  = JERFiles::Summer16_07Aug2017_V11_EF_L123_AK8PFPuppi_DATA;
  JEC_AK8_GH   = JERFiles::Summer16_07Aug2017_V11_GH_L123_AK8PFPuppi_DATA;
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
    topjetER_smearer.reset(new GenericJetResolutionSmearer(ctx,"topjets","gentopjets",true,JERSmearing::SF_13TeV_2016_25nsV1,"Summer16_25nsV1_MC_PtResolution_AK8PFPuppi.txt"));
//        topjetER_smearer.reset(new GenericJetResolutionSmearer(ctx,"topjets","gentopjets",true,JERSmearing::SF_13TeV_2016,"Spring16_25nsV10_MC_PtResolution_AK8PFPuppi.txt"));
        // topjetER_smearer.reset(new GenericJetResolutionSmearer(ctx,"topjets","gentopjets",true,JERSmearing::SF_13TeV_2016,"Spring16_25nsV10_MC_PtResolution_AK8PFchs.txt"));
      }
    }
    else
    {



      jet_corrector_BCD.reset(new JetCorrector(ctx, JEC_AK4_BCD));
      jet_corrector_EF.reset(new JetCorrector(ctx, JEC_AK4_EF));
  //    jet_corrector_G.reset(new JetCorrector(ctx,JEC_AK4_G ));
//      jet_corrector_H.reset(new JetCorrector(ctx,JEC_AK4_H ));
jet_corrector_GH.reset(new JetCorrector(ctx,JEC_AK4_GH ));

      topjet_corrector_BCD.reset(new TopJetCorrector(ctx, JEC_AK8_BCD));
//      topjet_corrector_EF.reset(new TopJetCorrector(ctx, JEC_AK8_EF));
//      topjet_corrector_H.reset(new TopJetCorrector(ctx,JEC_AK8_H ));
topjet_corrector_GH.reset(new TopJetCorrector(ctx,JEC_AK8_GH ));

    }


    //102X    topjet_sdmasscorrector.reset(new SoftDropMassCalculator(ctx, true, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/puppiCorr.root","topjets"));
    //102X topjet_jms.reset(new JetMassScale(ctx,true, "/nfs/dust/cms/user/zoiirene/CMSSW_8_0_24_patch1/src/UHH2/common/data/jetmassResolution.root","topjets"));

    //    jetcleaner.reset(new JetCleaner(ctx, 20.0, 5));
    jetcleaner.reset(new JetCleaner(ctx, 30.0, 5));
    //    topjetcleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(200., 2.4))));
    topjetcleaner.reset(new TopJetCleaner(ctx,TopJetId(PtEtaCut(200., 2.5))));

    AK4PFID=JetPFID(JetPFID::WP_LOOSE_PUPPI);
    AK8PFID=JetPFID(JetPFID::WP_LOOSE_PUPPI);


    ak8pfidfilter.reset(new TopJetCleaner(ctx,AK8PFID));
    ak4pfidfilter.reset(new JetCleaner(ctx,AK4PFID));
    //PDFweightgetter.reset(new PDFWeights("NNPDF30_lo_as_0130_nf_4"));

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
    vbfdeta_sel.reset(new VBFdeltaEtajetSelection(3.0f)); // see VBFresonanceToWWSelections
    vbfetasign_sel.reset(new VBFEtaSignjetSelection()); // see VBFresonanceToWWSelections
    vbfeta_sel.reset(new VBFEtajetSelection()); // see VBFresonanceToWWSelections
    vbfeta35_sel.reset(new VBFEtajetSelection(3.5f)); // see VBFresonanceToWWSelections
    vbfeta4_sel.reset(new VBFEtajetSelection(4.0f)); // see VBFresonanceToWWSelections
    vbfeta45_sel.reset(new VBFEtajetSelection(4.5f)); // see VBFresonanceToWWSelections
    vbfeta5_sel.reset(new VBFEtajetSelection(5.0f)); // see VBFresonanceToWWSelections
    vbfeta55_sel.reset(new VBFEtajetSelection(5.5f)); // see VBFresonanceToWWSelections
    vbfeta6_sel.reset(new VBFEtajetSelection(6.0f)); // see VBFresonanceToWWSelections
    invM800_sel.reset(new invMassVBFjetSelection(800.0f)); // see VBFresonanceToWWSelections


    //VBF inverted
    ptjet1_invsel.reset(new AK4PtInvSelection(100.f)); // see VBFresonanceToWWSelections
    jet2_invsel.reset(new DijetInvSelection(2.f)); // at least 2 jets
    vbfetasign_invsel.reset(new VBFEtaSignjetInvSelection()); // see VBFresonanceToWWSelections
    vbfeta_invsel.reset(new VBFEtajetInvSelection(4.5f)); // see VBFresonanceToWWSelections
    invM1000_invsel.reset(new invMassVBFjetInvSelection(800.0f)); // see VBFresonanceToWWSelections


    if(PRINT) cout << "reset sel" <<endl;


    // 3. Set up Hists classes:
    /*
    h_Wtopjets_input.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_input_nominal"));
    h_Wtopjets_input_pdf.reset(new VBFresonanceToWW_WTopJetPDFHists(ctx, "Wtopjets_input_pdf"));
    h_Wtopjets_withVBF_invM800_de45.reset(new VBFresonanceToWW_WTopJetHists(ctx, "Wtopjets_VBF_invM800_de45_nominal"));
    h_Wtopjets_withVBF_invM800_de45_pdf.reset(new VBFresonanceToWW_WTopJetPDFHists(ctx, "Wtopjets_VBF_invM800_de45_pdf"));
    */


    for(int i = 0; i < PDFs; i++)
    {
      if(i==0)
      {
        h_Wtopjets_input[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_input_nominal"));
        // h_Wtopjets_common[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_common_nominal"));
        // h_WtopjetsHist_common[i].reset(new VBFresonanceToWW_WTopJetHists(ctx, "WtopjetsHist_common_nominal"));
        // h_muon_common[i].reset(new MuonHists(ctx, "Muon_common_nominal"));
        // h_electron_common[i].reset(new ElectronHists(ctx, "Electron_common_nominal"));
        // h_Wtopjets_muon[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_muon_nominal"));
        // h_WtopjetsHist_muon[i].reset(new VBFresonanceToWW_WTopJetHists(ctx, "WtopjetsHist_muon_nominal"));
        // h_muon_muon[i].reset(new MuonHists(ctx, "Muon_muon_nominal"));
        // h_electron_muon[i].reset(new ElectronHists(ctx, "Electron_muon_nominal"));
        // h_Wtopjets_electron[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_electron_nominal"));
        // h_WtopjetsHist_electron[i].reset(new VBFresonanceToWW_WTopJetHists(ctx, "WtopjetsHist_electron_nominal"));
        // h_muon_electron[i].reset(new MuonHists(ctx, "Muon_electron_nominal"));
        // h_electron_electron[i].reset(new ElectronHists(ctx, "Electron_electron_nominal"));
        // h_Wtopjets_correctors[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_correctors_nominal"));
        // h_WtopjetsHist_correctors[i].reset(new VBFresonanceToWW_WTopJetHists(ctx, "WtopjetsHist_correctorsnominal"));
        // h_muon_correctors[i].reset(new MuonHists(ctx, "Muon_correctors_nominal"));
        // h_electron_correctors[i].reset(new ElectronHists(ctx, "Electron_correctors_nominal"));
        // h_Wtopjets_SDMcorrectors[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_SDMcorrectors_nominal"));
        // h_Wtopjets_tcleaner[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_tcleaner_nominal"));
        // h_Wtopjets_ak8filt[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_ak8filt_nominal"));
        // h_Wtopjets_2tjets[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_2tjets_nominal"));
        // h_Wtopjets_corrections[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_corrections_nominal"));
        // h_Wtopjets_invM[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_invM_nominal"));
        // h_Wtopjets_deta[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_deta_nominal"));
        // h_Wtopjets_VVM[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_VVM_nominal"));
        // h_Wtopjets_tau21[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_tau21_nominal"));
        // h_Wtopjets_2jet[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_2jet_nominal"));
        // h_Wtopjets_sign[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_sign_nominal"));
        // h_Wtopjets_800[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_800_nominal"));
        h_Wtopjets_passVBF_invM800_de45[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_passVBF_invM800_de45_nominal"));
        h_Wtopjets_failVBF_invM800_de45[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_failVBF_invM800_de45_nominal"));
      }
      else
      {
        //   std::string pdf = std::to_string(i);
        h_Wtopjets_input[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_input_scalevariation"));
        // h_Wtopjets_common[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_common_scalevariation"));
        // h_electron_common[i].reset(new ElectronHists(ctx, "Electron_common_scalevariation"));
        // h_WtopjetsHist_common[i].reset(new VBFresonanceToWW_WTopJetHists(ctx, "WtopjetsHist_common_scalevariation"));
        // h_muon_common[i].reset(new MuonHists(ctx, "Muon_common_scalevariation"));
        // h_Wtopjets_muon[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_muon_scalevariation"));
        // h_WtopjetsHist_muon[i].reset(new VBFresonanceToWW_WTopJetHists(ctx, "WtopjetsHist_muon_scalevariation"));
        // h_muon_muon[i].reset(new MuonHists(ctx, "Muon_muon_scalevariation"));
        // h_electron_muon[i].reset(new ElectronHists(ctx, "Electron_muon_scalevariation"));
        // h_Wtopjets_electron[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_electron_scalevariation"));
        // h_WtopjetsHist_electron[i].reset(new VBFresonanceToWW_WTopJetHists(ctx, "WtopjetsHist_electron_scalevariation"));
        // h_muon_electron[i].reset(new MuonHists(ctx, "Muon_electron_scalevariation"));
        // h_electron_electron[i].reset(new ElectronHists(ctx, "Electron_electron_scalevariation"));
        // h_Wtopjets_correctors[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_correctors_scalevariation"));
        // h_WtopjetsHist_correctors[i].reset(new VBFresonanceToWW_WTopJetHists(ctx, "WtopjetsHist_correctorsscalevariation"));
        // h_muon_correctors[i].reset(new MuonHists(ctx, "Muon_correctors_scalevariation"));
        // h_electron_correctors[i].reset(new ElectronHists(ctx, "Electron_correctors_scalevariation"));
        // h_Wtopjets_SDMcorrectors[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_SDMcorrectors_scalevariation"));
        // h_Wtopjets_tcleaner[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_tcleaner_scalevariation"));
        // h_Wtopjets_ak8filt[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_ak8filt_scalevariation"));
        // h_Wtopjets_2tjets[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_2tjets_scalevariation"));
        // h_Wtopjets_corrections[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_corrections_scalevariation"));
        // h_Wtopjets_invM[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_invM_scalevariation"));
        // h_Wtopjets_deta[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_deta_scalevariation"));
        // h_Wtopjets_VVM[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_VVM_scalevariation"));
        // h_Wtopjets_tau21[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_tau21_scalevariation"));
        // h_Wtopjets_2jet[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_2jet_scalevariation"));
        // h_Wtopjets_sign[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_sign_scalevariation"));
        // h_Wtopjets_800[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_800_scalevariation"));
        h_Wtopjets_passVBF_invM800_de45[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_passVBF_invM800_de45_scalevariation"));
        h_Wtopjets_failVBF_invM800_de45[i].reset(new VBFresonanceToWW_WTopJetInvMHists(ctx, "Wtopjets_failVBF_invM800_de45_scalevariation"));
      }
    }


    //genjet

    h_input_genparticle.reset(new VBFresonanceToWWParticleHists(ctx, "GenParticle"));
    h_input_gentopjets.reset(new VBFresonanceToWWGenTopJetHists(ctx, "input_GenTopJet"));
    h_input_gendijets.reset(new VBFresonanceToWWGenDiJetHists(ctx, "input_GenDiJet"));
    h_input_genjets.reset(new GenJetsHists(ctx, "input_GenJet"));



    if(PRINT) cout << "hist setup" <<endl;


  }


  bool VBFresonanceToWWScaleAcceptanceModule::process(Event & event) {
    // This is the main procedure, called for each event. Typically,
    // do some pre-processing by calling the modules' process method
    // of the modules constructed in the constructor (1).
    // Then, test whether the event passes some selection and -- if yes --
    // use it to fill the histograms (2).
    // Finally, decide whether or not to keep the event in the output (3);
    // this is controlled by the return value of this method: If it
    // returns true, the event is kept; if it returns false, the event
    // is thrown away.

    if(PRINT)    cout << "VBFresonanceToWWScaleAcceptanceModule: Starting to process event (runid, eventid) = (" << event.run << ", " <<", " << event.event << "); weight = " << event.weight << endl;


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


  // if(PRINT) cout << " event.weight before common " << event.weight << endl;
  // // 1. run all modules other modules.
  // bool pass_cm = common->process(event);
  // if(!pass_cm) return false;
  // if(PRINT) cout << " event.weight after common " << event.weight << endl;

  auto original_weight = event.weight;
  std::unique_ptr< std::vector<Jet> >    uncleaned_jets   (new std::vector<Jet>   (*event.jets));
  std::unique_ptr< std::vector<TopJet> > uncleaned_topjets(new std::vector<TopJet>(*event.topjets));
  std::unique_ptr< std::vector<Electron> > uncleaned_electrons(new std::vector<Electron>(*event.electrons));
  std::unique_ptr< std::vector<Muon> > uncleaned_muons(new std::vector<Muon>(*event.muons));




  for(int i = 0; i < PDFs; i++)
  {
    //  float orig_weight = event.genInfo->pdf_scalePDF();

    event.jets->clear();
    event.jets->reserve(uncleaned_jets->size());
    for(const auto & j : *uncleaned_jets) event.jets->push_back(j);

    event.topjets->clear();
    event.topjets->reserve(uncleaned_topjets->size());
    for(const auto & tj : *uncleaned_topjets) event.topjets->push_back(tj);

    event.electrons->clear();
    event.electrons->reserve(uncleaned_electrons->size());
    for(const auto & e : *uncleaned_electrons) event.electrons->push_back(e);

    event.muons->clear();
    event.muons->reserve(uncleaned_muons->size());
    for(const auto & m : *uncleaned_muons) event.muons->push_back(m);

    event.weight = original_weight;

    if(i > 0  && isMC) MCScaleModule->process(event);
    if(PRINT) cout << " pdf " << i << " event.weight after common " << event.weight << endl;


    h_Wtopjets_input[i]->fill(event);

    bool pass_cm = common->process(event);
    //    if(!pass_cm) return false;

    bool muon_selection = muon_sel->passes(event);
    bool electron_selection = electron_sel->passes(event);

    if(pass_cm)
    {
      // h_Wtopjets_common[i]->fill(event);
      // h_WtopjetsHist_common[i]->fill(event);
      // h_muon_common[i]->fill(event);
      // h_electron_common[i]->fill(event);

      if(muon_selection)
      {
        // h_Wtopjets_muon[i]->fill(event);
        // h_WtopjetsHist_muon[i]->fill(event);
        // h_muon_muon[i]->fill(event);
        // h_electron_muon[i]->fill(event);

        if(electron_selection)
        {
          // h_Wtopjets_electron[i]->fill(event);
          // h_WtopjetsHist_electron[i]->fill(event);
          // h_muon_electron[i]->fill(event);
          // h_electron_electron[i]->fill(event);


          sort_by_pt<Jet>(*event.jets);
          sort_by_pt<TopJet>(*event.topjets);


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
            else if(event.run >= runnr_EF) {
              //	jetlepton_cleaner_G->process(event);
              jet_corrector_GH->process(event);
              topjet_corrector_GH->process(event);
              //	subjet_corrector_G->process(event);
              jet_corrector_GH->correct_met(event);
            }
            // else if(event.run <= runnr_G) {
            //   //	jetlepton_cleaner_G->process(event);
            //   jet_corrector_G->process(event);
            //   topjet_corrector_G->process(event);
            //   //	subjet_corrector_G->process(event);
            //   jet_corrector_G->correct_met(event);
            // }
            // else if(event.run > runnr_G) {
            //   //	jetlepton_cleaner_H->process(event);
            //   jet_corrector_H->process(event);
            //   topjet_corrector_H->process(event);
            //   //	subjet_corrector_H->process(event);
            //   jet_corrector_H->correct_met(event);
            // }
          }

          sort_by_pt<Jet>(*event.jets);
          sort_by_pt<TopJet>(*event.topjets);
          if(PRINT)    cout << "VBFresonanceToWWScaleAcceptanceModule: jec applied " << endl;
          // h_Wtopjets_correctors[i]->fill(event);
          // h_WtopjetsHist_correctors[i]->fill(event);
          // h_muon_correctors[i]->fill(event);
          // h_electron_correctors[i]->fill(event);

	  //102X          topjet_sdmasscorrector->process(event);
          //		    h_Wtopjets_SDMcorrectors[i]->fill(event);
	  //102X	  topjet_jms->process(event);
          //    jetcleaner->process(event);
          topjetcleaner->process(event);
          //h_Wtopjets_tcleaner[i]->fill(event);

          ak8pfidfilter->process(event);
          //h_Wtopjets_ak8filt[i]->fill(event);

          bool topjets2_selection = topjet2_sel->passes(event);
          //h_Wtopjets_2tjets[i]->fill(event);

          if(topjets2_selection)
          {

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

            bool invMtopjet_fitselection = invMtopjet_fitsel->passes(event);
            bool topjets_deta_selection = topjets_deta_sel->passes(event);
            bool VVMtopjet_selection = VVmass_sel->passes(event);
            bool tau21topjetHP_selection = tau21topjetHP_sel->passes(event);

            //h_Wtopjets_corrections[i]->fill(event);

            if(invMtopjet_fitselection)
            {
              //  h_Wtopjets_invM[i]->fill(event);
              if(topjets_deta_selection)
              {
                //	h_Wtopjets_deta[i]->fill(event);
                if(VVMtopjet_selection)
                {
                  //  h_Wtopjets_VVM[i]->fill(event);
                  if(tau21topjetHP_selection)
                  {
                    //	h_Wtopjets_tau21[i]->fill(event);


                    jetcleaner->process(event);
                    ak4pfidfilter->process(event);

                    // Selections for AK4
                    bool jets2_selection = jet2_sel->passes(event);
                    bool vbfetasign_selection = vbfetasign_sel->passes(event);
                    bool vbfeta_selection = vbfeta_sel->passes(event);
                    bool vbfeta45_selection = vbfeta45_sel->passes(event);
                    bool invM800jet_selection = invM800_sel->passes(event);

                    if(jets2_selection)
                    {
                      //h_Wtopjets_2jet[i]->fill(event);
                      if(vbfetasign_selection)
                      {
                        //	h_Wtopjets_sign[i]->fill(event);
                        if(invM800jet_selection)
                        {
                          //  h_Wtopjets_800[i]->fill(event);
                          if( vbfeta45_selection)
                          h_Wtopjets_passVBF_invM800_de45[i]->fill(event);
                        }
                      }
                    }

                    //Inverted Selections for AK4
                    bool jets2_invselection = jet2_invsel->passes(event);
                    if(PRINT)    cout << "VBFresonanceToWWInver 2 ak4 inv" << endl;
                    bool vbfetasign_invselection = vbfetasign_invsel->passes(event);
                    if(PRINT)    cout << "VBFresonanceToWWInver 2 ak4 sign inv" << endl;
                    bool vbfeta_invselection = vbfeta_invsel->passes(event);
                    if(PRINT)    cout << "VBFresonanceToWWInver 2 ak4 eta inv" << endl;
                    bool invM1000_invselection = invM1000_invsel->passes(event);
                    if(PRINT)    cout << "VBFresonanceToWWInver 2 ak4 mass inv" << endl;
                  //    if(ptjets1_invselection || jets2_invselection || vbfetasign_invselection || vbfeta_invselection || invM1000_invselection)
                    if(jets2_invselection || vbfetasign_invselection || vbfeta_invselection || invM1000_invselection)
                      {
                         h_Wtopjets_failVBF_invM800_de45[i]->fill(event);
                      }



                  }//VV
                }
              }
            }
          }//if 2 topjets
        }
      }
    }//if on common and leptons
  }//pdfs
  // 3. decide whether or not to keep the current event in the output:
  return true;

}


// as we want to run the ExampleCycleNew directly with AnalysisModuleRunner,
// make sure the VBFresonanceToWWScaleAcceptanceModule is found by class name. This is ensured by this macro:
UHH2_REGISTER_ANALYSIS_MODULE(VBFresonanceToWWScaleAcceptanceModule)

}

//  LocalWords:  scalevariation
