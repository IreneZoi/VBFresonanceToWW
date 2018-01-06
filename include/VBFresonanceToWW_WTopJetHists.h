#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
//#include "ZPrimeTotTPrimeGenSelections.h"
#include "UHH2/core/include/LorentzVector.h"
/**
 *
 *Histograms for GenTopJet
 *
 **/

class VBFresonanceToWW_WTopJetHists : public uhh2::Hists{
  public:
  VBFresonanceToWW_WTopJetHists(uhh2::Context & ctx, const std::string & dirname);//, const std::string & collection = " ");
    virtual void fill(const uhh2::Event & event) override;

 protected:
    TH1F *pt, *eta, *phi, *mass, *chf, *tau1, *tau2;
    //uhh2::Event::Handle<GenTopJet> h_gentopjets;
    uhh2::Event::Handle<std::vector <Jet>  > h_jets;
    bool isMC;
    uhh2::Event::Handle<std::vector <GenParticle>  > h_particles;
};
