#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWGenTopJetHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/GenTopJet.h"


#include "TH1F.h"
#include <iostream>

using namespace uhh2;


VBFresonanceToWWGenTopJetHists::VBFresonanceToWWGenTopJetHists(Context & ctx, 
					     const std::string & dirname)  : Hists(ctx, dirname){
  //number
  book<TH1F>("Njets","N jets",10,0,10);
  
  //mass
  book<TH1F>("Mass_1","Mass [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_2","Mass [GeV/c^{2}]",100,0,300);

  //PT    
  book<TH1F>("PT_1","P_{T} [GeV/c]",100,0,1500);
  book<TH1F>("PT_2","P_{T} [GeV/c]",100,0,1500);
  
  // Phi 
  book<TH1F>("Phi_1"," Phi ",100,-M_PI,M_PI);
  book<TH1F>("Phi_2"," Phi ",100,-M_PI,M_PI);
  
  //Eta 
  book<TH1F>("Eta_1","Eta",100,-4,4);
  book<TH1F>("Eta_2","Eta",100,-4,4);

  //substructure
  book<TH1F>("SoftDropMass_Gen1", "GenJetSoftDropMass [GeV/c^2]", 100,0,300);
  book<TH1F>("CHF_1","CHF",100,0,1);
  book<TH1F>("TAU1_1","#tau_{1}",50,0,1); 
  book<TH1F>("TAU2_1","#tau_{2}",50,0,1);
  book<TH1F>("Tau21_Gen1", "#tau_{2}/#tau_{1}", 50,0,1); 

  book<TH1F>("SoftDropMass_Gen2", "GenJetSoftDropMass [GeV/c^2]", 100,0,300);
  book<TH1F>("CHF_2","CHF",100,0,1);
  book<TH1F>("TAU1_2","#tau_{1}",50,0,1); 
  book<TH1F>("TAU2_2","#tau_{2}",50,0,1);
  book<TH1F>("Tau21_Gen2", "#tau_{2}/#tau_{1}", 50,0,1); 

  book<TH1F>("invMass","M_{jj} [GeV/c^{2}]",100,0,2500);
  book<TH1F>("delta_eta","#Delta #eta_{jj}",80,-5,5);
  book<TH1F>("delta_phi","#Delta #phi_{jj}",200,-2*M_PI,2*M_PI);
  book<TH1F>("delta_R","#Delta R_{jj}",70,0,7);


  h_gentopjets = ctx.get_handle<std::vector <GenTopJet> >("gentopjets");

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
      float deta = jet.at(0).eta() - jet.at(1).eta();
      hist("delta_eta")->Fill(deta, weight);
      float dphi = jet.at(0).phi() - jet.at(1).phi();
      hist("delta_phi")->Fill(dphi, weight);
      float dR = sqrt(deta*deta+dphi*dphi);
      hist("delta_R")->Fill(dR, weight);

}
