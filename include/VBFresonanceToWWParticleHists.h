#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/LorentzVector.h"
/**
 *
 *Histograms for GenParticle
 *
 **/

class VBFresonanceToWWParticleHists : public uhh2::Hists{
  public:
  VBFresonanceToWWParticleHists(uhh2::Context & ctx, const std::string & dirname);//, const std::string & collection = " ");
    virtual void fill(const uhh2::Event & event) override;

 protected:
    TH1F *pt, *eta, *phi, *mass, *chf, *tau1, *tau2;
    //uhh2::Event::Handle<GenTopJet> h_gentopjets;
    uhh2::Event::Handle<std::vector <GenParticle>  > h_particles;

    TH2F *Wpt1_Wpt2;
    TH2F *Weta1_Weta2;
    TH2F *Weta1_Weta2_low;
    TH2F *Weta1_Weta2_high;
    TH2F *Wcosteta1_Wcosteta2;
    TH2F *Wcosteta1_Wcosteta2_low;
    TH2F *Wcosteta1_Wcosteta2_high;

};
