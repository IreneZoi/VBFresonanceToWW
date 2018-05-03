#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWGenTopJetHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/GenTopJet.h"
#include "UHH2/core/include/LorentzVector.h"

#include "TH1F.h"
#include "TMath.h"
#include <iostream>



using namespace uhh2;


VBFresonanceToWWGenTopJetHists::VBFresonanceToWWGenTopJetHists(Context & ctx, 
					     const std::string & dirname)  : Hists(ctx, dirname){
  //number
  book<TH1F>("Njets","N jets",10,0,10);
  
  //mass
  book<TH1F>("Mass_1","Mass_{1} [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_2","Mass_{2} [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_1_match","Mass_{1} [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_2_match","Mass_{2} [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_1_match_low","Mass_{1} [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_2_match_low","Mass_{2} [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_1_match_high","Mass_{1} [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_2_match_high","Mass_{2} [GeV/c^{2}]",100,0,300);

  book<TH1F>("Mass_1_lowM2","Mass_{1} [GeV/c^{2}]",100,0,300);

  book<TH1F>("Mass_1_noOv","Mass_{1} [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_2_noOv","Mass_{2} [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_1_quark","Mass_{1} [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_2_quark","Mass_{2} [GeV/c^{2}]",100,0,300);

  //PT    
  book<TH1F>("PT_1","P_{T,1} [GeV/c]",45,0,2025);
  book<TH1F>("PT_2","P_{T,2} [GeV/c]",45,0,2025);
  book<TH1F>("PT_1_match","P_{T,1} [GeV/c]",45,0,2025);
  book<TH1F>("PT_2_match","P_{T,2} [GeV/c]",45,0,2025);
  book<TH1F>("PT_1_match_low","P_{T,1} [GeV/c]",45,0,2025);
  book<TH1F>("PT_2_match_low","P_{T,2} [GeV/c]",45,0,2025);
  book<TH1F>("PT_1_match_high","P_{T,1} [GeV/c]",45,0,2025);
  book<TH1F>("PT_2_match_high","P_{T,2} [GeV/c]",45,0,2025);

  book<TH1F>("PT_1_lowM2","P_{T,1} [GeV/c]",45,0,2025);
  book<TH1F>("PT_2_lowM2","P_{T,2} [GeV/c]",45,0,2025);

  book<TH1F>("PT_1_noOv","P_{T,1} [GeV/c]",45,0,2025);
  book<TH1F>("PT_2_noOv","P_{T,2} [GeV/c]",45,0,2025);

  book<TH1F>("PT_1_quark","P_{T,1} [GeV/c]",45,0,2025);
  book<TH1F>("PT_2_quark","P_{T,2} [GeV/c]",45,0,2025);
  
  // Phi 
  book<TH1F>("Phi_1"," #phi_{1} ",100,-M_PI,M_PI);
  book<TH1F>("Phi_2"," #phi_{2} ",100,-M_PI,M_PI);
  
  //Eta 
  book<TH1F>("Eta_1","#eta_{1}",50,-2.5,2.5);
  book<TH1F>("Eta_2","#eta_{2}",50,-2.5,2.5);
  book<TH1F>("Eta_1_match","#eta_{1}",50,-2.5,2.5);
  book<TH1F>("Eta_2_match","#eta_{2}",50,-2.5,2.5);
  book<TH1F>("Eta_1_match_low","#eta_{1}",50,-2.5,2.5);
  book<TH1F>("Eta_2_match_low","#eta_{2}",50,-2.5,2.5);
  book<TH1F>("Eta_1_match_high","#eta_{1}",50,-2.5,2.5);
  book<TH1F>("Eta_2_match_high","#eta_{2}",50,-2.5,2.5);

  book<TH1F>("Eta_1_lowM2","#eta_{1}",50,-2.5,2.5);
  book<TH1F>("Eta_2_lowM2","#eta_{2}",50,-2.5,2.5);

  book<TH1F>("Eta_1_noOv","P_{T,1} [GeV/c]",45,0,2025);
  book<TH1F>("Eta_2_noOv","P_{T,2} [GeV/c]",45,0,2025);

  book<TH1F>("Eta_1_quark","P_{T,1} [GeV/c]",45,0,2025);
  book<TH1F>("Eta_2_quark","P_{T,2} [GeV/c]",45,0,2025);

  //substructure
  book<TH1F>("SoftDropMass_Gen1", "GenJetSoftDropMass [GeV/c^2]", 100,0,300);
  book<TH1F>("CHF_1","CHF_{1}",100,0,1);
  book<TH1F>("TAU1_1","#tau_{1_{1}}",50,0,1); 
  book<TH1F>("TAU2_1","#tau_{2_{1}}",50,0,1);
  book<TH1F>("Tau21_Gen1", "#tau_{2}/#tau_{1}", 50,0,1); 

  book<TH1F>("SoftDropMass_Gen2", "GenJetSoftDropMass [GeV/c^2]", 100,0,300);
  book<TH1F>("CHF_2","CHF_{2}",100,0,1);
  book<TH1F>("TAU1_2","#tau_{1_{2}}",50,0,1); 
  book<TH1F>("TAU2_2","#tau_{2_{2}}",50,0,1);
  book<TH1F>("Tau21_Gen2", "#tau_{2}/#tau_{1}", 50,0,1); 

  book<TH1F>("invMass","M_{jj} [GeV/c^{2}]",30,1000,7000);
  book<TH1F>("invMass_quark","M_{jj} [GeV/c^{2}]",30,1000,7000);
  book<TH1F>("invMass_noOv","M_{jj} [GeV/c^{2}]",30,1000,7000);
  book<TH1F>("invMass_lowM2","M_{jj} [GeV/c^{2}]",30,1000,7000);
  book<TH1F>("invMass_wtag","M_{jj} [GeV/c^{2}]",30,1000,7000);
  book<TH1F>("invMass_wtag_low","M_{jj} [GeV/c^{2}]",30,1000,7000);
  book<TH1F>("invMass_wtag_high","M_{jj} [GeV/c^{2}]",30,1000,7000);
  book<TH1F>("invMass_forfit","M_{jj} [GeV/c^{2}]",30,1050,4050);
  book<TH1F>("delta_eta","#Delta #eta_{jj}",80,-5,5);
  book<TH1F>("delta_phi","#Delta #phi_{jj}",200,-2*M_PI,2*M_PI);
  book<TH1F>("delta_R","#Delta R_{jj}",70,0,7);

  h_gentopjets = ctx.get_handle<std::vector <GenTopJet> >("gentopjets");
  h_particles = ctx.get_handle<std::vector <GenParticle> >("genparticles");
 }


void VBFresonanceToWWGenTopJetHists::fill(const uhh2::Event & event){
  assert(event.gentopjets);

 //Generator-Teilchen
  if(!event.is_valid(h_gentopjets)){
    return;
  }
  

    //Weightning
  double weight = event.weight;
  
  const std::vector<GenTopJet> &  jet = event.get(h_gentopjets);
       
  float NJet = jet.size();
  hist("Njets")->Fill(NJet, weight);
  
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
      
      



  std::vector<GenTopJet> GTjets = *event.gentopjets;
  if(GTjets.size()<2) return;
  const auto & gjet = GTjets[0];
  LorentzVector gsubjet_sum;
  for (const auto sg : gjet.subjets()) {
    gsubjet_sum += sg.v4();
  }
  const auto & gjet2 = GTjets[1];
  LorentzVector gsubjet_sum2;
  for (const auto sg2 : gjet2.subjets()) {
    gsubjet_sum2 += sg2.v4();
  }
      
  //auto GenJetSDMass1 = event.gentopjets->at(0).v4().M();                                                                                                                                                   
  auto GenJetSDMass1 = gsubjet_sum.M();
  auto GenJetSDMass2 = gsubjet_sum2.M();
   
  //      auto GenJetSDMass1 = event.gentopjets->at(0).v4().M();
  hist("SoftDropMass_Gen1")->Fill(GenJetSDMass1, weight);
  hist("SoftDropMass_Gen2")->Fill(GenJetSDMass2, weight);
  
  
       
  float chf1 = jet.at(0).chf();
  hist("CHF_1")->Fill(chf1, weight);
  float tau1_1 = jet.at(0).tau1();
  hist("TAU1_1")->Fill(tau1_1, weight);
  float tau2_1 = jet.at(0).tau2();
  hist("TAU2_1")->Fill(tau2_1, weight);
  float tau21_1 = tau2_1/tau1_1;
  hist("Tau21_Gen1")->Fill(tau21_1, weight);

  float chf2 = jet.at(1).chf();
  hist("CHF_2")->Fill(chf2, weight);
  float tau1_2 = jet.at(1).tau1();
  hist("TAU1_2")->Fill(tau1_2, weight);
  float tau2_2 = jet.at(1).tau2();
  hist("TAU2_2")->Fill(tau2_2, weight);
  float tau21_2 = tau2_2/tau1_2;
  hist("Tau21_Gen2")->Fill(tau21_2, weight);
  
  float mass = (jet.at(0).v4() + jet.at(1).v4()).M();
  hist("invMass")->Fill(mass, weight);
  hist("invMass_forfit")->Fill(mass, weight);



  if(Mass2 < 55)
    {
      hist("Mass_1_lowM2")->Fill(Mass1, weight);
      hist("PT_1_lowM2")->Fill(PT1, weight);
      hist("Eta_1_lowM2")->Fill(Eta1, weight);

      hist("PT_2_lowM2")->Fill(PT2, weight);
      hist("Eta_2_lowM2")->Fill(Eta2, weight);

      hist("invMass_lowM2")->Fill(mass, weight);
  
    }

  
  assert(event.genparticles);
  if(!event.is_valid(h_particles)){
    return;
  }
  
  const std::vector<GenParticle> &  genp = event.get(h_particles);
  
  
  GenParticle W;
  GenParticle W1;
  GenParticle W2;
  GenParticle q1vbf;
  GenParticle q2vbf;
  GenParticle qW1;
  GenParticle qW2;
  GenParticle qW3;
  GenParticle qW4;
  int j = 0;
  int k = 0;
  bool quark=false;
  //std::cout << " new" << std::endl;
  for(unsigned int i=0; i<genp.size(); i++)
    {
      const GenParticle & gp = genp[i];
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
	      //	      j=0;
	    }
	  j++;
	}


      if(
	 abs(gp.pdgId())>0 
	 && abs(gp.pdgId())<7 
	 && gp.mother1()>0 
	 && gp.mother2()>gp.mother1()
	 )
	{
	  if(k==0)
	    {
	      qW1 = gp;
	      //std::cout<< k <<std::endl;
	    }
	  if(k==1)
	    {
	    qW2 = gp;
	      //std::cout<< k <<std::endl;
	    }
	  if(k==2)
	    {
	    qW3 = gp;
	      //std::cout<< k <<std::endl;
	    }
	  if(k==3)
	    {
	      qW4 = gp;
	      //	      k=0;
	      quark = true;
	      //std::cout<< k <<std::endl;
	    }
	  k++;
	}


  }

  float pt_W1 = W1.v4().pt();
  float pt_W2 = W2.v4().pt();

  if((deltaR(W1,jet.at(0))<0.4 && deltaR(W2,jet.at(1))<0.4 )|| (  deltaR(W1,jet.at(1))<0.4 &&  deltaR(W2,jet.at(0))<0.4))
    {
      hist("Mass_1_match")->Fill(Mass1, weight);
      hist("PT_1_match")->Fill(PT1, weight);
      hist("Eta_1_match")->Fill(Eta1, weight);
      
      hist("Mass_2_match")->Fill(Mass2, weight);
      hist("PT_2_match")->Fill(PT2, weight);
      hist("Eta_2_match")->Fill(Eta2, weight);

      hist("invMass_wtag")->Fill(mass, weight);

      if((pt_W1 <700 && pt_W1 > 100)||(pt_W2 <700 && pt_W2 > 100))
	{
	  hist("Mass_1_match_low")->Fill(Mass1, weight);
	  hist("PT_1_match_low")->Fill(PT1, weight);
	  hist("Eta_1_match_low")->Fill(Eta1, weight);
	  
	  hist("Mass_2_match_low")->Fill(Mass2, weight);
	  hist("PT_2_match_low")->Fill(PT2, weight);
	  hist("Eta_2_match_low")->Fill(Eta2, weight);
	  
	  hist("invMass_wtag_low")->Fill(mass, weight);

	}
      if(pt_W1 > 800 || pt_W2 > 800)
	{
	  hist("Mass_1_match_high")->Fill(Mass1, weight);
	  hist("PT_1_match_high")->Fill(PT1, weight);
	  hist("Eta_1_match_high")->Fill(Eta1, weight);
	  
	  hist("Mass_2_match_high")->Fill(Mass2, weight);
	  hist("PT_2_match_high")->Fill(PT2, weight);
	  hist("Eta_2_match_high")->Fill(Eta2, weight);
	  
	  hist("invMass_wtag_high")->Fill(mass, weight);

	}


      if((deltaR(q1vbf,jet.at(0))>0.2 && deltaR(q2vbf,jet.at(1))>0.2 )|| (  deltaR(q1vbf,jet.at(1))>0.2 &&  deltaR(q2vbf,jet.at(0))>0.2))
	{
	  hist("Mass_1_noOv")->Fill(Mass1, weight);
	  hist("PT_1_noOv")->Fill(PT1, weight);
	  hist("Eta_1_noOv")->Fill(Eta1, weight);
	  
	  hist("Mass_2_noOv")->Fill(Mass2, weight);
	  hist("PT_2_noOv")->Fill(PT2, weight);
	  hist("Eta_2_noOv")->Fill(Eta2, weight);
	  
	  hist("invMass_noOv")->Fill(mass, weight);
	  
	}

      if(quark)
	{
	  hist("Mass_1_quark")->Fill(Mass1, weight);
	  hist("PT_1_quark")->Fill(PT1, weight);
	  hist("Eta_1_quark")->Fill(Eta1, weight);
	  
	  hist("Mass_2_quark")->Fill(Mass2, weight);
	  hist("PT_2_quark")->Fill(PT2, weight);
	  hist("Eta_2_quark")->Fill(Eta2, weight);
	  
	  hist("invMass_quark")->Fill(mass, weight);

	}



    }




      float deta = jet.at(0).eta() - jet.at(1).eta();
      hist("delta_eta")->Fill(deta, weight);
      float dphi = deltaPhi(jet.at(0),jet.at(1));
      //      float dphi = jet.at(0).phi() - jet.at(1).phi();
      hist("delta_phi")->Fill(dphi, weight);
      //      float dR = sqrt(deta*deta+dphi*dphi);
      float dR = deltaR(jet.at(0),jet.at(1));
      hist("delta_R")->Fill(dR, weight);

}
