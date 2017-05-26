#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWDiJetHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/LorentzVector.h"
#include "UHH2/core/include/Jet.h"
#include "UHH2/common/include/Utils.h"

#include "TH1F.h"
#include <iostream>

using namespace uhh2;


VBFresonanceToWWDiJetHists::VBFresonanceToWWDiJetHists(Context & ctx, 
					     const std::string & dirname)  : Hists(ctx, dirname){
  //number
  book<TH1F>("Njets","N jets",10,0,10);
  //number
  book<TH1F>("N_jj","N_jj ",10,0,10);

  
  //mass
  book<TH1F>("Mass_1","Mass_{1} [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_2","Mass_{2} [GeV/c^{2}]",100,0,300);
  //mass eta
  book<TH1F>("eta_Mass_1","Mass_{1} [GeV/c^{2}]",100,0,300);
  book<TH1F>("eta_Mass_2","Mass_{2} [GeV/c^{2}]",100,0,300);

  //PT    
  book<TH1F>("PT_1","P_{T,1} [GeV/c]",100,0,1500);
  book<TH1F>("PT_2","P_{T,2} [GeV/c]",100,0,1500);
  //PT eta   
  book<TH1F>("eta_PT_1","P_{T,1} [GeV/c]",100,0,1500);
  book<TH1F>("eta_PT_2","P_{T,2} [GeV/c]",100,0,1500);

  //energy
  book<TH1F>("Energy_1","E_{1} [GeV]",100,0,2000);
  book<TH1F>("Energy_2","E_{2} [GeV]",100,0,2000);

  //energy eta
  book<TH1F>("eta_Energy_1","E_{jj} [GeV]",100,0,2000);
  book<TH1F>("eta_Energy_2","E_{jj} [GeV]",100,0,2000);
  
  // Phi 
  book<TH1F>("Phi_1"," #phi_{1} ",100,-M_PI,M_PI);
  book<TH1F>("Phi_2"," #phi_{2} ",100,-M_PI,M_PI);
  // Phi eta
  book<TH1F>("eta_Phi_1"," #phi_{1} ",100,-M_PI,M_PI);
  book<TH1F>("eta_Phi_2"," #phi_{2} ",100,-M_PI,M_PI);
  
  //Eta 
  book<TH1F>("Eta_1","#eta_{1}",50,-2.5,2.5);
  book<TH1F>("Eta_2","#eta_{2}",50,-2.5,2.5);
  //Eta eta
  book<TH1F>("eta_Eta_1","#eta_{1}",50,-2.5,2.5);
  book<TH1F>("eta_Eta_2","#eta_{2}",50,-2.5,2.5);

  //jj

  //inv mass
  book<TH1F>("InvariantMass_jj","Mass_{jj} [GeV/c^{2}]",100,0,3000);
  //mass eta
  book<TH1F>("eta_InvariantMass_jj","Mass_{jj} [GeV/c^{2}]",100,0,3000);

  //pt
  book<TH1F>("Pt_jj","p_{T_{jj}} [GeV/c]",100,0,500);
  //pt eta
  book<TH1F>("eta_Pt_jj","p_{T_{jj}} [GeV/c]",100,0,500);

  //delta phi
  book<TH1F>("Phi_jj","#Delta #phi_{jj}",100,0,M_PI);
  //pt eta
  book<TH1F>("eta_Phi_jj","#Delta #phi_{jj}",100,0,M_PI);

  //delta eta
  book<TH1F>("Eta_jj","#Delta #eta_{jj}",100,-5,5);
  //pt eta
  book<TH1F>("eta_Eta_jj","#Delta #eta_{jj}",100,-5,5);

  //delta R
  book<TH1F>("R_jj","#Delta R_{jj}",70,3,10);
  //pt eta
  book<TH1F>("eta_R_jj","#Delta R_{jj}",70,3,10);

 }


void VBFresonanceToWWDiJetHists::fill(const uhh2::Event & event){
  assert(event.jets);

  

    //Weightning
  double weight = event.weight;

  std::vector<Jet>* jet = event.jets;
  //  Jet Dijet();
  //  Dijet().set_v4(jet->at(0).v4()+jet->at(1).v4());

      float NJet = jet->size();
      hist("Njets")->Fill(NJet, weight);

      unsigned int count =0;
      for(unsigned int i = 0; i <jet->size(); i++)
	{
	  for(unsigned int j = i+1; j <jet->size(); j++)
	    {

	      auto etaproduct = jet->at(i).eta()*jet->at(j).eta();
	      auto deltaeta = jet->at(i).eta()-jet->at(j).eta();
	      if (  (fabs(deltaeta) > 3.0) && (etaproduct < 0)) count++;
	      
	    }
	}
      hist("N_jj")->Fill(count);



      std::unique_ptr< std::vector<Jet> >    eta_jets   (new std::vector<Jet>   (*event.jets));      
      sort_by_eta<Jet>(*eta_jets);



      float eta_Mass1;// = eta_jets->at(0).v4().mass();
      float eta_Mass2;// = eta_jets->at(eta_jets->size()-1).v4().mass();
      float eta_PT1;// = eta_jets->at(0).v4().pt();
      float eta_PT2;// = eta_jets->at(eta_jets->size()-1).v4().pt();
      float eta_Energy1;// = eta_jets->at(0).v4().energy();
      float eta_Energy2;// = eta_jets->at(1).v4().energy();
      float eta_Eta1;// = eta_jets->at(0).v4().eta();
      float eta_Eta2;// = eta_jets->at(eta_jets->size()-1).v4().eta();
      float eta_Phi1;// = eta_jets->at(0).v4().phi();
      float eta_Phi2;// = eta_jets->at(eta_jets->size()-1).v4().phi();

      if ( eta_jets->at(0).v4().pt() > eta_jets->at(1).v4().pt())
	{
	  eta_Mass1 = eta_jets->at(0).v4().mass();
	  eta_Mass2 = eta_jets->at(eta_jets->size()-1).v4().mass();
	  eta_PT1 = eta_jets->at(0).v4().pt();
	  eta_PT2 = eta_jets->at(eta_jets->size()-1).v4().pt();
	  eta_Energy1 = eta_jets->at(0).v4().energy();
	  eta_Energy2 = eta_jets->at(eta_jets->size()-1).v4().energy();
	  eta_Eta1 = eta_jets->at(0).v4().eta();
	  eta_Eta2 = eta_jets->at(eta_jets->size()-1).v4().eta();
	  eta_Phi1 = eta_jets->at(0).v4().phi();
	  eta_Phi2 = eta_jets->at(eta_jets->size()-1).v4().phi();
	}
      else 
	{
	  eta_Mass2 = eta_jets->at(0).v4().mass();
	  eta_Mass1 = eta_jets->at(eta_jets->size()-1).v4().mass();
	  eta_PT2 = eta_jets->at(0).v4().pt();
	  eta_PT1 = eta_jets->at(eta_jets->size()-1).v4().pt();
	  eta_Energy2 = eta_jets->at(0).v4().energy();
	  eta_Energy1 = eta_jets->at(eta_jets->size()-1).v4().energy();
	  eta_Eta2 = eta_jets->at(0).v4().eta();
	  eta_Eta1 = eta_jets->at(eta_jets->size()-1).v4().eta();
	  eta_Phi2 = eta_jets->at(0).v4().phi();
	  eta_Phi1 = eta_jets->at(eta_jets->size()-1).v4().phi();
	}

      hist("eta_Mass_1")->Fill(eta_Mass1, weight);
      hist("eta_Mass_2")->Fill(eta_Mass2, weight);

      hist("eta_PT_1")->Fill(eta_PT1, weight);
      hist("eta_PT_2")->Fill(eta_PT2, weight);

      hist("eta_Energy_1")->Fill(eta_Energy1, weight);
      hist("eta_Energy_2")->Fill(eta_Energy2, weight);

      float eta_invMass = (eta_jets->at(0).v4()+eta_jets->at(eta_jets->size()-1).v4()).M();
      hist("eta_InvariantMass_jj")->Fill(eta_invMass,weight);
      float eta_pt = (eta_jets->at(0).v4()+eta_jets->at(eta_jets->size()-1).v4()).pt();
      hist("eta_Pt_jj")->Fill(eta_pt,weight);


      hist("eta_Eta_1")->Fill(eta_Eta1, weight);
      hist("eta_Eta_2")->Fill(eta_Eta2, weight);
      hist("eta_Phi_1")->Fill(eta_Phi1, weight);
      hist("eta_Phi_2")->Fill(eta_Phi2, weight);


      auto eta_deltaphi = deltaPhi(eta_jets->at(0).v4(),eta_jets->at(eta_jets->size()-1).v4());
      hist("eta_Phi_jj")->Fill(eta_deltaphi,weight);
      auto eta_deltaeta = eta_jets->at(0).eta()-eta_jets->at(eta_jets->size()-1).eta();
      hist("eta_Eta_jj")->Fill(eta_deltaeta,weight);
      auto eta_deltar = deltaR(eta_jets->at(0).v4(),eta_jets->at(eta_jets->size()-1).v4());
      hist("eta_R_jj")->Fill(eta_deltar,weight);



      //	std::cout<< "sort by eta  " << eta_jets->at(0).eta() << " " <<eta_jets->at(1).eta() <<std::endl;

  if(jet->size() < 2) return;
      float Mass1 = jet->at(0).v4().mass();
      hist("Mass_1")->Fill(Mass1, weight);
      float PT1 = jet->at(0).v4().pt();
      hist("PT_1")->Fill(PT1, weight);
      float Phi1 = jet->at(0).v4().phi();
      hist("Phi_1")->Fill(Phi1, weight);
      float Eta1 = jet->at(0).v4().eta();
      hist("Eta_1")->Fill(Eta1, weight);

      float Mass2 = jet->at(1).v4().mass();
      hist("Mass_2")->Fill(Mass2, weight);
      float PT2 = jet->at(1).v4().pt();
      hist("PT_2")->Fill(PT2, weight);
      float Phi2 = jet->at(1).v4().phi();
      hist("Phi_2")->Fill(Phi2, weight);
      float Eta2 = jet->at(1).v4().eta();
      hist("Eta_2")->Fill(Eta2, weight);

      float Energy1 = jet->at(0).v4().energy();
      hist("Energy_1")->Fill(Energy1, weight);
      float Energy2 = jet->at(1).v4().energy();
      hist("Energy_2")->Fill(Energy2, weight);

      float energy = Energy1 + Energy2;
      //      float invMass = sqrt(energy*energy -(PT1+PT2)*(PT1+PT2));
      float invMass = (jet->at(0).v4()+jet->at(1).v4()).M();
      hist("InvariantMass_jj")->Fill(invMass,weight);
      float Pt = (jet->at(0).v4()+jet->at(1).v4()).pt();
      hist("Pt_jj")->Fill(Pt,weight);
      auto deltaphi = deltaPhi(jet->at(0).v4(),jet->at(1).v4());
      hist("Phi_jj")->Fill(deltaphi,weight);
      auto deltaeta = jet->at(0).eta()-jet->at(1).eta();
      hist("Eta_jj")->Fill(deltaeta,weight);
      auto deltar = deltaR(jet->at(0).v4(),jet->at(1).v4());
      hist("R_jj")->Fill(deltar,weight);

}
