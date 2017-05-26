#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Jet.h"
//#include "ZPrimeTotTPrimeGenSelections.h"
#include "UHH2/core/include/LorentzVector.h"
#include <vector>
/**
 *
 *Histograms for GenTopJet
 *
 **/

class VBFresonanceToWWDiJetHists : public uhh2::Hists{
  public:
  VBFresonanceToWWDiJetHists(uhh2::Context & ctx, const std::string & dirname);//, const std::string & collection = " ");
    virtual void fill(const uhh2::Event & event) override;

 protected:
    TH1F *pt, *eta, *phi, *mass, *chf, *tau1, *tau2;
    Jet Dijet() const;

};
