#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWW_WTopJetInvMHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/TopJet.h"


#include "TH1F.h"
#include <iostream>
#include <sstream>

using namespace uhh2;
using namespace std;

VBFresonanceToWW_WTopJetInvMHists::VBFresonanceToWW_WTopJetInvMHists(Context & ctx,
					     const std::string & dirname)  : Hists(ctx, dirname){



  book<TH1F>("invMass", "M_{jj}-AK8 [GeV/c^{2}]", 30,1000,7000);
  book<TH1F>("events", "is in", 1,0.,2.);
  book<TH1F>("weights", "event.weight", 100.,0.,2.);





  //  h_topjets = ctx.get_handle<std::vector <TopJet> >("topjets");
  h_jets = ctx.get_handle<std::vector <Jet> >("jets");
  h_particles = ctx.get_handle<std::vector <GenParticle> >("genparticles");
  isMC = (ctx.get("dataset_type") == "MC");


 }


void VBFresonanceToWW_WTopJetInvMHists::fill(const uhh2::Event & event){
  assert(event.topjets);
  if(isMC)
    assert(event.genparticles);



  
  std::vector<TopJet>* jet = event.topjets;
  //  std::cout << "going to use event.weight " << event.weight << std::endl;  
  hist("events")->Fill(1., event.weight);
  hist("weights")->Fill(event.weight,1.);

  if(jet->size() < 2) return;

  float mass = (jet->at(0).v4() + jet->at(1).v4()).M();

  hist("invMass")->Fill(mass, event.weight);
  
}
