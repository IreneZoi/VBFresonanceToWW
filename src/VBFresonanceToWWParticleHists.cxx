#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWParticleHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/GenParticle.h"
#include "UHH2/common/include/CommonModules.h"

#include "TH1F.h"
#include "TH2F.h"
#include "TMath.h"
#include <iostream>

using namespace uhh2;


VBFresonanceToWWParticleHists::VBFresonanceToWWParticleHists(Context & ctx, 
					     const std::string & dirname)  : Hists(ctx, dirname){
  
  //mass
  book<TH1F>("Mass_X","Mass [GeV/c^{2}]",100,1990,2010);
  book<TH1F>("Mass_X_low","Mass [GeV/c^{2}]",100,1990,2010);
  book<TH1F>("Mass_X_high","Mass [GeV/c^{2}]",100,1990,2010);

  book<TH1F>("Mass_q1vbf","Mass [GeV/c^{2}]",100,0,1);
  book<TH1F>("Mass_q1vbf_low","Mass [GeV/c^{2}]",100,0,1);
  book<TH1F>("Mass_q1vbf_high","Mass [GeV/c^{2}]",100,0,1);
  book<TH1F>("Mass_q2vbf","Mass [GeV/c^{2}]",100,0,1);
  book<TH1F>("Mass_q2vbf_low","Mass [GeV/c^{2}]",100,0,1);
  book<TH1F>("Mass_q2vbf_high","Mass [GeV/c^{2}]",100,0,1);

  book<TH1F>("Mass_W","Mass [GeV/c^{2}]",80,60,100);
  book<TH1F>("Mass_W_low","Mass [GeV/c^{2}]",80,60,100);
  book<TH1F>("Mass_W_high","Mass [GeV/c^{2}]",80,60,100);
  book<TH1F>("InvMass_2W","Mass_{jj} [GeV/c^{2}]",100,1900,2100);
  book<TH1F>("InvMass_2W_low","Mass_{jj} [GeV/c^{2}]",100,1900,2100);
  book<TH1F>("InvMass_2W_high","Mass_{jj} [GeV/c^{2}]",100,1900,2100);

  book<TH1F>("Mass_q_W","Mass [GeV/c^{2}]",100,0,1);
  book<TH1F>("Mass_q_W_low","Mass [GeV/c^{2}]",100,0,1);
  book<TH1F>("Mass_q_W_high","Mass [GeV/c^{2}]",100,0,1);

  //PT    
  book<TH1F>("PT_X","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_X_low","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_X_high","P_{T} [GeV/c]",100,0,1500);

  book<TH1F>("PT_q1vbf","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_q1vbf_low","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_q1vbf_high","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_q2vbf","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_q2vbf_low","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_q2vbf_high","P_{T} [GeV/c]",100,0,1500);

  book<TH1F>("PT_W","P_{T} [GeV/c]",100,0,2500);
  Wpt1_Wpt2 = book<TH2F>("Wpt1_vs_Wpt2", "W pt1 vs W pt2",100,0,2500, 100,0,2500); //irene 
  book<TH1F>("PT_W_low","P_{T} [GeV/c]",100,0,2500);
  book<TH1F>("PT_W_high","P_{T} [GeV/c]",100,0,2500);

  book<TH1F>("PT_q_W","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_q_W_low","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_q_W_high","P_{T} [GeV/c]",100,0,1500);
  
  // Phi 
  book<TH1F>("Phi_X","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_X_low","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_X_high","#phi ",100,-M_PI,M_PI);

  book<TH1F>("Phi_q1vbf","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_q1vbf_low","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_q1vbf_high","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_q2vbf","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_q2vbf_low","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_q2vbf_high","#phi ",100,-M_PI,M_PI);

  book<TH1F>("Phi_W","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_W_low","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_W_high","#phi ",100,-M_PI,M_PI);

  book<TH1F>("Phi_q_W","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_q_W_low","#phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_q_W_high","#phi ",100,-M_PI,M_PI);
  
  //Eta 
  book<TH1F>("Eta_X","#eta ",100,-10,10);
  book<TH1F>("Eta_X_low","#eta ",100,-10,10);
  book<TH1F>("Eta_X_high","#eta ",100,-10,10);

  book<TH1F>("Eta_q1vbf","#eta ",100,-10,10);
  book<TH1F>("Eta_q1vbf_low","#eta ",100,-10,10);
  book<TH1F>("Eta_q1vbf_high","#eta ",100,-10,10);
  book<TH1F>("Eta_q2vbf","#eta ",100,-10,10);
  book<TH1F>("Eta_q2vbf_low","#eta ",100,-10,10);
  book<TH1F>("Eta_q2vbf_high","#eta ",100,-10,10);

  book<TH1F>("Eta_W","#eta ",100,-10,10);
  book<TH1F>("Eta_W_low","#eta ",100,-10,10);
  book<TH1F>("Eta_W_high","#eta ",100,-10,10);
  Weta1_Weta2 = book<TH2F>("Weta1_vs_Weta2", "W eta1 vs W eta2",100,-10,10, 100,-10,10); //irene 
  Weta1_Weta2_low = book<TH2F>("Weta1_vs_Weta2_low", "W eta1 vs W eta2",100,-10,10, 100,-10,10); //irene 
  Weta1_Weta2_high = book<TH2F>("Weta1_vs_Weta2_high", "W eta1 vs W eta2",100,-10,10, 100,-10,10); //irene 


  book<TH1F>("Teta_W","#teta ",100,0,3.5);
  book<TH1F>("Teta_W1","#teta ",100,0,3.5);
  book<TH1F>("Teta_W2","#teta ",100,0,3.5);
  book<TH1F>("Teta_W_low","#teta ",100,0,3.5);
  book<TH1F>("Teta_W_low1","#teta ",100,0,3.5);
  book<TH1F>("Teta_W_low2","#teta ",100,0,3.5);
  book<TH1F>("Teta_W1_low","#teta ",100,0,3.5);
  book<TH1F>("Teta_W1_low1","#teta ",100,0,3.5);
  book<TH1F>("Teta_W1_low2","#teta ",100,0,3.5);
  book<TH1F>("Teta_W2_low","#teta ",100,0,3.5);
  book<TH1F>("Teta_W2_low1","#teta ",100,0,3.5);
  book<TH1F>("Teta_W2_low2","#teta ",100,0,3.5);
  book<TH1F>("Teta_W_high","#teta ",100,0,3.5);
  book<TH1F>("Teta_W_high1","#teta ",100,0,3.5);
  book<TH1F>("Teta_W_high2","#teta ",100,0,3.5);
  book<TH1F>("Teta_W1_high","#teta ",100,0,3.5);
  book<TH1F>("Teta_W1_high1","#teta ",100,0,3.5);
  book<TH1F>("Teta_W1_high2","#teta ",100,0,3.5);
  book<TH1F>("Teta_W2_high","#teta ",100,0,3.5);
  book<TH1F>("Teta_W2_high1","#teta ",100,0,3.5);
  book<TH1F>("Teta_W2_high2","#teta ",100,0,3.5);


  book<TH1F>("Costeta_W","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W1","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W2","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W_low","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W_low1","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W_low2","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W1_low","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W1_low1","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W1_low2","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W2_low","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W2_low1","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W2_low2","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W_high","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W_high1","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W_high2","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W1_high","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W1_high1","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W1_high2","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W2_high","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W2_high1","cos(#teta) ",100,-1.,1.);
  book<TH1F>("Costeta_W2_high2","cos(#teta) ",100,-1.,1.);


  Wcosteta1_Wcosteta2 = book<TH2F>("Wcosteta1_vs_Wcosteta2", "W costeta1 vs W costeta2",100,-1.,1., 100,-1.,1.); //irene 
  Wcosteta1_Wcosteta2_low = book<TH2F>("Wcosteta1_vs_Wcosteta2_low", "W costeta1 vs W costeta2",100,-1.,1., 100,-1.,1.); //irene 
  Wcosteta1_Wcosteta2_high = book<TH2F>("Wcosteta1_vs_Wcosteta2_high", "W costeta1 vs W costeta2",100,-1.,1., 100,-1.,1.); //irene 


  book<TH1F>("Eta_q_W","#eta ",100,-10,10);
  book<TH1F>("Eta_q_W_low","#eta ",100,-10,10);
  book<TH1F>("Eta_q_W_high","#eta ",100,-10,10);


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

      GenParticle X;
      GenParticle q1vbf;
      GenParticle q2vbf;
      GenParticle W;
      GenParticle W1;
      GenParticle W2;
      GenParticle qW;
      int j=0;
       
  for(unsigned int i=0; i<genp.size(); i++)
    {
      const GenParticle & gp = genp[i];

      if((abs(gp.pdgId())==39 || abs(gp.pdgId())==35)
	 && gp.mother1()<2 
	 && gp.mother2()<2
	 )
	{
	  X = gp;
	  //	  float mass_X = gp.v4().mass();
	  // hist("Mass_X")->Fill(mass_X, weight);
	  // hist("Mass_X")->Fill(mass_X, weight);
	  // hist("Mass_X")->Fill(mass_X, weight);
	  // float pt_X = gp.v4().pt();
	  // hist("PT_X")->Fill(pt_X, weight);
	  // hist("PT_X")->Fill(pt_X, weight);
	  // hist("PT_X")->Fill(pt_X, weight);
	  // float phi_X = gp.v4().phi();
	  // hist("Phi_X")->Fill(phi_X, weight);
	  // float eta_X = gp.v4().eta();
	  // hist("Eta_X")->Fill(eta_X, weight);
	  
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
	  if(j==0)
	    q1vbf=gp;
	  if(j==1)
	    {
	      q2vbf=gp;
	      j=0;
	    }
	  // float mass_qvbf = gp.v4().mass();
	  // hist("Mass_qvbf")->Fill(mass_qvbf, weight);
	  // float pt_qvbf = gp.v4().pt();
	  // hist("PT_qvbf")->Fill(pt_qvbf, weight);
	  // float phi_qvbf = gp.v4().phi();
	  // hist("Phi_qvbf")->Fill(phi_qvbf, weight);
	  // float eta_qvbf = gp.v4().eta();
	  // hist("Eta_qvbf")->Fill(eta_qvbf, weight);
	  j++;
	}


      if(
	 abs(gp.pdgId())==24
         && gp.mother1()==2
         && gp.mother2()>0
	 )
        {
	  W=gp;
	  if(W.daughter1()==7)
	    W1=gp;
	  if(W.daughter1()==9)
	    W2=gp;
          // float mass_W = gp.v4().mass();
          // hist("Mass_W")->Fill(mass_W, weight);
          // float pt_W = gp.v4().pt();
          // hist("PT_W")->Fill(pt_W, weight);
          // float phi_W = gp.v4().phi();
          // hist("Phi_W")->Fill(phi_W, weight);
          // float eta_W = gp.v4().eta();
          // hist("Eta_W")->Fill(eta_W, weight);

        }

      
      if(
	 abs(gp.pdgId())>0 
	 && abs(gp.pdgId())<7 
	 && gp.mother1()>0 
	 && gp.mother2()>gp.mother1()
	 )
	{
	  qW=gp;
	  // float mass_q_W = gp.v4().mass();
	  // hist("Mass_q_W")->Fill(mass_q_W, weight);
	  // float pt_q_W = gp.v4().pt();
	  // hist("PT_q_W")->Fill(pt_q_W, weight);
	  // float phi_q_W = gp.v4().phi();
	  // hist("Phi_q_W")->Fill(phi_q_W, weight);
	  // float eta_q_W = gp.v4().eta();
	  // hist("Eta_q_W")->Fill(eta_q_W, weight);

	}

    }
      float mass_X = X.v4().mass();
      hist("Mass_X")->Fill(mass_X, weight);
      float pt_X = X.v4().pt();
      hist("PT_X")->Fill(pt_X, weight);
      float phi_X = X.v4().phi();
      hist("Phi_X")->Fill(phi_X, weight);
      float eta_X = X.v4().eta();
      hist("Eta_X")->Fill(eta_X, weight);

      // std::cout << " X " << std::endl;
      // std::cout << "mass: " << mass_X << " pt: " << pt_X << " eta:" << eta_X << " phi: " << phi_X << std::endl; 

      float mass_q1vbf = q1vbf.v4().mass();
      hist("Mass_q1vbf")->Fill(mass_q1vbf, weight);
      float pt_q1vbf = q1vbf.v4().pt();
      hist("PT_q1vbf")->Fill(pt_q1vbf, weight);
      float phi_q1vbf = q1vbf.v4().phi();
      hist("Phi_q1vbf")->Fill(phi_q1vbf, weight);
      float eta_q1vbf = q1vbf.v4().eta();
      hist("Eta_q1vbf")->Fill(eta_q1vbf, weight);
      float mass_q2vbf = q2vbf.v4().mass();
      hist("Mass_q2vbf")->Fill(mass_q2vbf, weight);
      float pt_q2vbf = q2vbf.v4().pt();
      hist("PT_q2vbf")->Fill(pt_q2vbf, weight);
      float phi_q2vbf = q2vbf.v4().phi();
      hist("Phi_q2vbf")->Fill(phi_q2vbf, weight);
      float eta_q2vbf = q2vbf.v4().eta();
      hist("Eta_q2vbf")->Fill(eta_q2vbf, weight);

      // std::cout << " q1vbf " << std::endl;
      // std::cout << "mass: " << mass_q1vbf << " pt: " << pt_q1vbf << " eta:" << eta_q1vbf << " phi: " << phi_q1vbf << std::endl; 

      // std::cout << " q2vbf " << std::endl;
      // std::cout << "mass: " << mass_q2vbf << " pt: " << pt_q2vbf << " eta:" << eta_q2vbf << " phi: " << phi_q2vbf << std::endl; 

     
      float mass_W = W.v4().mass();
      float mass_W1 = W1.v4().mass();
      float mass_W2 = W2.v4().mass();
      hist("Mass_W")->Fill(mass_W, weight);
      float invmass = (W1.v4() + W2.v4()).M();
      hist("InvMass_2W")->Fill(invmass, weight);
      float pt_W = W.v4().pt();
      float pt_W1 = W1.v4().pt();
      float pt_W2 = W2.v4().pt();
      Wpt1_Wpt2->Fill(pt_W1,pt_W2,weight);
      hist("PT_W")->Fill(pt_W, weight);
      float phi_W = W.v4().phi();
      float phi_W1 = W1.v4().phi();
      float phi_W2 = W2.v4().phi();
      hist("Phi_W")->Fill(phi_W, weight);
      float eta_W = W.v4().eta();
      float eta_W1 = W1.v4().eta();
      float eta_W2 = W2.v4().eta();
      hist("Eta_W")->Fill(eta_W, weight);
      Weta1_Weta2->Fill(eta_W1,eta_W2,weight);

      float teta_W = 2*TMath::ATan(TMath::Power(TMath::E(),-eta_W));
      float costeta_W = TMath::Cos(teta_W);
      float teta_W1 = 2*TMath::ATan(TMath::Power(TMath::E(),-eta_W1));
      float costeta_W1 = TMath::Cos(teta_W1);
      float teta_W2 = 2*TMath::ATan(TMath::Power(TMath::E(),-eta_W2));
      float costeta_W2 = TMath::Cos(teta_W2);

      hist("Teta_W")->Fill(teta_W, weight);
      hist("Teta_W1")->Fill(teta_W1, weight);
      hist("Teta_W2")->Fill(teta_W2, weight);

      hist("Costeta_W")->Fill(costeta_W, weight);
      hist("Costeta_W1")->Fill(costeta_W1, weight);
      hist("Costeta_W2")->Fill(costeta_W2, weight);
      Wcosteta1_Wcosteta2->Fill(costeta_W1,costeta_W2,weight);

      // std::cout << " W1 " << std::endl;
      // std::cout << "mass: " << mass_W1 << " pt: " << pt_W1 << " eta:" << eta_W1 << " phi: " << phi_W1 << std::endl; 

      // std::cout << " W2 " << std::endl;
      // std::cout << "mass: " << mass_W2 << " pt: " << pt_W2 << " eta:" << eta_W2 << " phi: " << phi_W2 << std::endl; 


      
      float mass_q_W = qW.v4().mass();
      hist("Mass_q_W")->Fill(mass_q_W, weight);
      float pt_q_W = qW.v4().pt();
      hist("PT_q_W")->Fill(pt_q_W, weight);
      float phi_q_W = qW.v4().phi();
      hist("Phi_q_W")->Fill(phi_q_W, weight);
      float eta_q_W = qW.v4().eta();
      hist("Eta_q_W")->Fill(eta_q_W, weight);

      if((pt_W1 <700 && pt_W1 > 100)||(pt_W2 <700 && pt_W2 > 100))
	{
	  hist("Mass_X_low")->Fill(mass_X, weight);
	  hist("PT_X_low")->Fill(pt_X, weight);
	  hist("Phi_X_low")->Fill(phi_X, weight);
	  hist("Eta_X_low")->Fill(eta_X, weight);
	  
	  hist("Mass_q1vbf_low")->Fill(mass_q1vbf, weight);
	  hist("PT_q1vbf_low")->Fill(pt_q1vbf, weight);
	  hist("Phi_q1vbf_low")->Fill(phi_q1vbf, weight);
	  hist("Eta_q1vbf_low")->Fill(eta_q1vbf, weight);
	  hist("Mass_q2vbf_low")->Fill(mass_q2vbf, weight);
	  hist("PT_q2vbf_low")->Fill(pt_q2vbf, weight);
	  hist("Phi_q2vbf_low")->Fill(phi_q2vbf, weight);
	  hist("Eta_q2vbf_low")->Fill(eta_q2vbf, weight);
     
	  hist("Mass_W_low")->Fill(mass_W, weight);
	  hist("InvMass_2W_low")->Fill(invmass, weight);
	  hist("PT_W_low")->Fill(pt_W, weight);
	  hist("Phi_W_low")->Fill(phi_W, weight);
	  hist("Eta_W_low")->Fill(eta_W, weight);
	  Weta1_Weta2_low->Fill(eta_W1,eta_W2,weight);

	  hist("Teta_W_low")->Fill(teta_W, weight);
	  hist("Teta_W1_low")->Fill(teta_W1, weight);
	  hist("Teta_W2_low")->Fill(teta_W2, weight);

	  hist("Costeta_W_low")->Fill(costeta_W, weight);
	  hist("Costeta_W1_low")->Fill(costeta_W1, weight);
	  hist("Costeta_W2_low")->Fill(costeta_W2, weight);
	  Wcosteta1_Wcosteta2_low->Fill(costeta_W1,costeta_W2,weight);
      
	  hist("Mass_q_W_low")->Fill(mass_q_W, weight);
	  hist("PT_q_W_low")->Fill(pt_q_W, weight);
	  hist("Phi_q_W_low")->Fill(phi_q_W, weight);
	  hist("Eta_q_W_low")->Fill(eta_q_W, weight);
	}

      if(pt_W1 > 800 || pt_W2 > 800)
	{
	  hist("Mass_X_high")->Fill(mass_X, weight);
	  hist("PT_X_high")->Fill(pt_X, weight);
	  hist("Phi_X_high")->Fill(phi_X, weight);
	  hist("Eta_X_high")->Fill(eta_X, weight);
	  
	  hist("Mass_q1vbf_high")->Fill(mass_q1vbf, weight);
	  hist("PT_q1vbf_high")->Fill(pt_q1vbf, weight);
	  hist("Phi_q1vbf_high")->Fill(phi_q1vbf, weight);
	  hist("Eta_q1vbf_high")->Fill(eta_q1vbf, weight);
	  hist("Mass_q2vbf_high")->Fill(mass_q2vbf, weight);
	  hist("PT_q2vbf_high")->Fill(pt_q2vbf, weight);
	  hist("Phi_q2vbf_high")->Fill(phi_q2vbf, weight);
	  hist("Eta_q2vbf_high")->Fill(eta_q2vbf, weight);
     
	  hist("Mass_W_high")->Fill(mass_W, weight);
	  hist("InvMass_2W_high")->Fill(invmass, weight);
	  hist("PT_W_high")->Fill(pt_W, weight);
	  hist("Phi_W_high")->Fill(phi_W, weight);
	  hist("Eta_W_high")->Fill(eta_W, weight);
	  Weta1_Weta2_high->Fill(eta_W1,eta_W2,weight);

	  hist("Teta_W_high")->Fill(teta_W, weight);
	  hist("Teta_W1_high")->Fill(teta_W1, weight);
	  hist("Teta_W2_high")->Fill(teta_W2, weight);

	  hist("Costeta_W_high")->Fill(costeta_W, weight);
	  hist("Costeta_W1_high")->Fill(costeta_W1, weight);
	  hist("Costeta_W2_high")->Fill(costeta_W2, weight);
	  Wcosteta1_Wcosteta2_high->Fill(costeta_W1,costeta_W2,weight);
      
	  hist("Mass_q_W_high")->Fill(mass_q_W, weight);
	  hist("PT_q_W_high")->Fill(pt_q_W, weight);
	  hist("Phi_q_W_high")->Fill(phi_q_W, weight);
	  hist("Eta_q_W_high")->Fill(eta_q_W, weight);
	}


      if(pt_W1 <700 && pt_W1 > 100)
	{
	  hist("Teta_W_low1")->Fill(teta_W, weight);
	  hist("Teta_W1_low1")->Fill(teta_W1, weight);
	  hist("Teta_W2_low1")->Fill(teta_W2, weight);

	  hist("Costeta_W_low1")->Fill(costeta_W, weight);
	  hist("Costeta_W1_low1")->Fill(costeta_W1, weight);
	  hist("Costeta_W2_low1")->Fill(costeta_W2, weight);
	}
      if(pt_W2 <700 && pt_W2 > 100)
	{
	  hist("Teta_W_low2")->Fill(teta_W, weight);
	  hist("Teta_W1_low2")->Fill(teta_W1, weight);
	  hist("Teta_W2_low2")->Fill(teta_W2, weight);

	  hist("Costeta_W_low2")->Fill(costeta_W, weight);
	  hist("Costeta_W1_low2")->Fill(costeta_W1, weight);
	  hist("Costeta_W2_low2")->Fill(costeta_W2, weight);
	}
      if(pt_W1 > 800)
	{
	  hist("Teta_W_high1")->Fill(teta_W, weight);
	  hist("Teta_W1_high1")->Fill(teta_W1, weight);
	  hist("Teta_W2_high1")->Fill(teta_W2, weight);

	  hist("Costeta_W_high1")->Fill(costeta_W, weight);
	  hist("Costeta_W1_high1")->Fill(costeta_W1, weight);
	  hist("Costeta_W2_high1")->Fill(costeta_W2, weight);
	}
      if(pt_W2 > 800)
	{
	  hist("Teta_W_high2")->Fill(teta_W, weight);
	  hist("Teta_W1_high2")->Fill(teta_W1, weight);
	  hist("Teta_W2_high2")->Fill(teta_W2, weight);

	  hist("Costeta_W_high2")->Fill(costeta_W, weight);
	  hist("Costeta_W1_high2")->Fill(costeta_W1, weight);
	  hist("Costeta_W2_high2")->Fill(costeta_W2, weight);
	}
}
