#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWParticleHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/GenParticle.h"
#include "UHH2/common/include/CommonModules.h"

#include "TH1F.h"
#include <iostream>

using namespace uhh2;


VBFresonanceToWWParticleHists::VBFresonanceToWWParticleHists(Context & ctx, 
					     const std::string & dirname)  : Hists(ctx, dirname){
  
  //mass

  // book<TH1F>("Mass_qi_1","Mass [GeV/c^{2}]",100,0,3000);
  // book<TH1F>("Mass_qi_2","Mass [GeV/c^{2}]",100,0,3000);
  book<TH1F>("Mass_X","Mass [GeV/c^{2}]",100,1990,2010);
  book<TH1F>("Mass_qvbf","Mass [GeV/c^{2}]",100,0,1);
  book<TH1F>("Mass_W","Mass [GeV/c^{2}]",80,60,100);
  book<TH1F>("Mass_q_W","Mass [GeV/c^{2}]",100,0,1);
  book<TH1F>("InvMass_W","Mass [GeV/c^{2}]",100,0,1);
  book<TH1F>("InvMass_qvbf","Mass [GeV/c^{2}]",100,0,1);

  //PT    

  // book<TH1F>("PT_qi_1","P_{T} [GeV/c]",100,0,1500);
  // book<TH1F>("PT_qi_2","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_X","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_qvbf","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_W","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_q_W","P_{T} [GeV/c]",100,0,1500);


  
  // Phi 

  // book<TH1F>("Phi_qi_1","#phi ",100,-M_PI,M_PI);
  // book<TH1F>("Phi_qi_2","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_X","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_qvbf","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_W","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_q_W","#phi ",100,-M_PI,M_PI);

  
  //Eta 

  // book<TH1F>("Eta_qi_1","#eta ",100,-10,10);
  // book<TH1F>("Eta_qi_2","#eta ",100,-10,10);
  book<TH1F>("Eta_X","#eta ",100,-10,10);
  book<TH1F>("Eta_qvbf","#eta ",100,-10,10);
  book<TH1F>("Eta_W","#eta ",100,-10,10);
  book<TH1F>("Eta_q_W","#eta ",100,-10,10);


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
  
  const std::vector<GenParticle> &  genp = event.get(h_particles);
  //  sort_by_pt<std::vector<GenParticle>>();

       
  for(unsigned int i=0; i<genp.size(); i++)
    {
      const GenParticle & gp = genp[i];


      if(abs(gp.pdgId())==39 || abs(gp.pdgId())==35)
	{

	  float mass_X = gp.v4().mass();
	  hist("Mass_X")->Fill(mass_X, weight);
	  float pt_X = gp.v4().pt();
	  hist("PT_X")->Fill(pt_X, weight);
	  float phi_X = gp.v4().phi();
	  hist("Phi_X")->Fill(phi_X, weight);
	  float eta_X = gp.v4().eta();
	  hist("Eta_X")->Fill(eta_X, weight);
	  
	}

      if(
	 abs(gp.pdgId())>0 
	 && abs(gp.pdgId())<7 
	 && gp.daughter1()==gp.daughter2()
	 && gp.daughter1()>0 
	 && gp.mother1()<2 
	 && gp.mother2()<2
	 )
	{
	  float mass_qvbf = gp.v4().mass();
	  hist("Mass_qvbf")->Fill(mass_qvbf, weight);
	  float pt_qvbf = gp.v4().pt();
	  hist("PT_qvbf")->Fill(pt_qvbf, weight);
	  float phi_qvbf = gp.v4().phi();
	  hist("Phi_qvbf")->Fill(phi_qvbf, weight);
	  float eta_qvbf = gp.v4().eta();
	  hist("Eta_qvbf")->Fill(eta_qvbf, weight);

	}


      if(
	 abs(gp.pdgId())==24
         && gp.mother1()==2
         && gp.mother2()>0
	 )
        {
          float mass_W = gp.v4().mass();
          hist("Mass_W")->Fill(mass_W, weight);
          float pt_W = gp.v4().pt();
          hist("PT_W")->Fill(pt_W, weight);
          float phi_W = gp.v4().phi();
          hist("Phi_W")->Fill(phi_W, weight);
          float eta_W = gp.v4().eta();
          hist("Eta_W")->Fill(eta_W, weight);

        }

      
      if(
	 abs(gp.pdgId())>0 
	 && abs(gp.pdgId())<7 
	 && gp.mother1()>0 
	 && gp.mother2()>gp.mother1()
	 )
	{
	  float mass_q_W = gp.v4().mass();
	  hist("Mass_q_W")->Fill(mass_q_W, weight);
	  float pt_q_W = gp.v4().pt();
	  hist("PT_q_W")->Fill(pt_q_W, weight);
	  float phi_q_W = gp.v4().phi();
	  hist("Phi_q_W")->Fill(phi_q_W, weight);
	  float eta_q_W = gp.v4().eta();
	  hist("Eta_q_W")->Fill(eta_q_W, weight);

	}

      









    }





}
