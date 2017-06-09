#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWParticleHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/GenParticle.h"
#include "UHH2/common/include/CommonModules.h"

#include "TH1F.h"
#include <iostream>

using namespace uhh2;


VBFresonanceToWWParticleHists::VBFresonanceToWWParticleHists(Context & ctx, 
					     const std::string & dirname)  : Hists(ctx, dirname){
  //number
  book<TH1F>("Nparticle","N particle",12,0,12);
  
  //mass
  book<TH1F>("Mass","Mass [GeV/c^{2}]",100,0,3000);

  book<TH1F>("Mass_1","Mass [GeV/c^{2}]",100,0,3000);
  book<TH1F>("Mass_2","Mass [GeV/c^{2}]",100,0,3000);
  book<TH1F>("Mass_3","Mass [GeV/c^{2}]",100,0,3000);
  book<TH1F>("Mass_4","Mass [GeV/c^{2}]",100,0,3000);

  //PT    
  book<TH1F>("PT","P_{T} [GeV/c]",100,0,1500);

  book<TH1F>("PT_1","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_2","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_3","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_4","P_{T} [GeV/c]",100,0,1500);
  
  // Phi 
  book<TH1F>("Phi"," Phi ",100,-M_PI,M_PI);

  book<TH1F>("Phi_1"," Phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_2"," Phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_3"," Phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_4"," Phi ",100,-M_PI,M_PI);
  
  //Eta 
  book<TH1F>("Eta","Eta",100,-4000,4000);

  book<TH1F>("Eta_1","Eta",100,0,4000);
  book<TH1F>("Eta_2","Eta",100,-4000,0);
  book<TH1F>("Eta_3","Eta",100,-4,4);
  book<TH1F>("Eta_4","Eta",100,-4,4);


  h_particles = ctx.get_handle<std::vector <GenParticle> >("genparticles");

 }


void VBFresonanceToWWParticleHists::fill(const uhh2::Event & event){
  assert(event.genparticles);

 //Generator-Teilchen
   if(!event.is_valid(h_particles)){
    return;
  }
  

    //Weightning
  double weight = event.weight;
  
  const std::vector<GenParticle> &  jet = event.get(h_particles);
  //  sort_by_pt<std::vector<GenParticle>>();
       
      float NJet = jet.size();
      hist("Nparticle")->Fill(NJet, weight);

      for(int j =0; j < NJet;j ++)
	{
	  hist("Mass")->Fill(jet.at(j).v4().mass(), weight);
	  hist("PT")->Fill(jet.at(j).v4().pt(), weight);
	  hist("Phi")->Fill(jet.at(j).v4().phi(), weight);
	  hist("Eta")->Fill(jet.at(j).v4().eta(), weight);
	}

  if(jet.size() < 2) return;
      float Mass1 = jet.at(0).v4().mass();
      hist("Mass_1")->Fill(Mass1, weight);
      float PT1 = jet.at(0).v4().pt();
      hist("PT_1")->Fill(PT1, weight);
      float Phi1 = jet.at(0).v4().phi();
      hist("Phi_1")->Fill(Phi1, weight);
      float Eta1 = jet.at(0).v4().eta();
      hist("Eta_1")->Fill(Eta1, weight);

      float Mass2 = jet.at(1).v4().mass();
      hist("Mass_2")->Fill(Mass2, weight);
      float PT2 = jet.at(1).v4().pt();
      hist("PT_2")->Fill(PT2, weight);
      float Phi2 = jet.at(1).v4().phi();
      hist("Phi_2")->Fill(Phi2, weight);
      float Eta2 = jet.at(1).v4().eta();
      hist("Eta_2")->Fill(Eta2, weight);

      if(jet.size() > 2)
	{

	  float Mass3 = jet.at(2).v4().mass();
	  hist("Mass_3")->Fill(Mass3, weight);
	  float PT3 = jet.at(2).v4().pt();
	  hist("PT_3")->Fill(PT3, weight);
	  float Phi3 = jet.at(2).v4().phi();
	  hist("Phi_3")->Fill(Phi3, weight);
	  float Eta3 = jet.at(2).v4().eta();
	  hist("Eta_3")->Fill(Eta3, weight);

	  if(jet.size() > 3)
	    {
	      
	      float Mass4 = jet.at(3).v4().mass();
	      hist("Mass_4")->Fill(Mass4, weight);
	      float PT4 = jet.at(3).v4().pt();
	      hist("PT_4")->Fill(PT4, weight);
	      float Phi4 = jet.at(3).v4().phi();
	      hist("Phi_4")->Fill(Phi4, weight);
	      float Eta4 = jet.at(3).v4().eta();
	      hist("Eta_4")->Fill(Eta4, weight);

	    }
	  
	}




}
