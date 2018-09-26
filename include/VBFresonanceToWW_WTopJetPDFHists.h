#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "TFile.h"
#include "TF1.h"
//#include "ZPrimeTotTPrimeGenSelections.h"
#include "UHH2/core/include/LorentzVector.h"
/**
 *
 *Histograms for GenTopJet
 *
 **/

class VBFresonanceToWW_WTopJetPDFHists : public uhh2::Hists{
  public:
  VBFresonanceToWW_WTopJetPDFHists(uhh2::Context & ctx, const std::string & dirname);//, const std::string & collection = " ");
    virtual void fill(const uhh2::Event & event) override;
    std::string histo_names[100];
 protected:
    TH1F *pt, *eta, *phi, *mass, *chf, *tau1, *tau2;
    //uhh2::Event::Handle<GenTopJet> h_gentopjets;
    uhh2::Event::Handle<std::vector <Jet>  > h_jets;
    bool isMC;
    uhh2::Event::Handle<std::vector <GenParticle>  > h_particles;
    TString puppi_sd_reweight;

    TFile * file;
    TF1 * puppisd_corrGEN     ;// = (TF1*)file.Get("puppiJECcorr_gen");
    TF1 * puppisd_corrRECO_cen ;//= (TF1*)file.Get("puppiJECcorr_reco_0eta1v3");
    TF1 * puppisd_corrRECO_for ;//= (TF1*)file.Get("puppiJECcorr_reco_1v3eta2v5");

};
