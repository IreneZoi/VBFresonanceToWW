#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWW_WTopJetHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/TopJet.h"


#include "TH1F.h"
#include <iostream>

using namespace uhh2;


VBFresonanceToWW_WTopJetHists::VBFresonanceToWW_WTopJetHists(Context & ctx, 
					     const std::string & dirname)  : Hists(ctx, dirname){
  //number
  book<TH1F>("Njets","N jets",10,0,10);
  
  //mass
  book<TH1F>("Mass_1","Mass_{1} [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_2","Mass_{2} [GeV/c^{2}]",100,0,300);

  //PT    
  book<TH1F>("PT_1","P_{T,1} [GeV/c]",45,0,2025);
  book<TH1F>("PT_2","P_{T,2} [GeV/c]",45,0,2025);
  
  // Phi 
  book<TH1F>("Phi_1","#phi_{1} ",100,-M_PI,M_PI);
  book<TH1F>("Phi_2","#phi_{2} ",100,-M_PI,M_PI);
  
  //Eta 
  book<TH1F>("Eta_1","#eta_{1}",50,-2.5,2.5);
  book<TH1F>("Eta_2","#eta_{2}",50,-2.5,2.5);

  //substructure
  book<TH1F>("SoftDropMass_1", "SoftDropMass_{1} [GeV/c^2]", 100,0,300);
  book<TH1F>("CHF_1","CHF_{1}",100,0,1);
  book<TH1F>("TAU1_1","#tau_{1_{1}}",50,0,1); 
  book<TH1F>("TAU2_1","#tau_{2_{1}}",50,0,1);
  book<TH1F>("Tau21_1", "#tau_{2_{1}}/#tau_{1_{1}}", 50,0,1); 

  book<TH1F>("SoftDropMass_2", "SoftDropMass_{2} [GeV/c^2]", 100,0,300);
  book<TH1F>("CHF_2","CHF_{2}",100,0,1);
  book<TH1F>("TAU1_2","#tau_{1_{2}}",50,0,1); 
  book<TH1F>("TAU2_2","#tau_{2_{2}}",50,0,1);
  book<TH1F>("Tau21_2", "#tau_{2_{2}}/#tau_{1_{2}}", 50,0,1); 

  book<TH1F>("invMass","M_{jj} [GeV/c^{2}]",30,1000,7000);
  book<TH1F>("invMass_checkLeptons","M_{jj} [GeV/c^{2}]",3,1000,1600);
  book<TH1F>("pdgID","pdgID",33,-16,16);
  book<TH1F>("pdgID_checkLeptons","pdgID",33,-16,16);
  book<TH1F>("invMass_forfit","M_{jj} [GeV/c^{2}]",30,1050,4050);

  book<TH1F>("delta_eta","#Delta #eta_{jj}",80,-5,5);
  book<TH1F>("delta_phi","#Delta #phi_{jj}",200,-2*M_PI,2*M_PI);
  book<TH1F>("delta_R","#Delta R_{jj}",70,0,7);


  //  h_topjets = ctx.get_handle<std::vector <TopJet> >("topjets");
  //  h_particles = ctx.get_handle<std::vector <GenParticle> >("genparticles");
  isMC = (ctx.get("dataset_type") == "MC");
 }


void VBFresonanceToWW_WTopJetHists::fill(const uhh2::Event & event){
  assert(event.topjets);
  // if(isMC)
  //   assert(event.genparticles);

  

    //Weightning
  double weight = event.weight;
  
  std::vector<TopJet>* jet = event.topjets;
     
      float NJet = jet->size();
      hist("Njets")->Fill(NJet, weight);

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


      std::vector<TopJet> Tjets = *event.topjets;
      if(Tjets.size()<1) return;
      const auto & jet1 = Tjets[0];
      const auto & jet2 = Tjets[1];
      LorentzVector subjet_sum1;
      LorentzVector subjet_sum2;
      for (const auto s1 : jet1.subjets()) {
	subjet_sum1 += s1.v4();
      }
      auto JetSDMass1 = subjet_sum1.M();
      for (const auto s2 : jet2.subjets()) {
	subjet_sum2 += s2.v4();
      }
      auto JetSDMass2 = subjet_sum2.M();

      hist("SoftDropMass_1")->Fill(JetSDMass1, weight);
      hist("SoftDropMass_2")->Fill(JetSDMass2, weight);
       
      float chf_1 = jet->at(0).chargedHadronEnergyFraction();
      hist("CHF_1")->Fill(chf_1, weight);
      float tau1_1 = jet->at(0).tau1();
      hist("TAU1_1")->Fill(tau1_1, weight);
      float tau2_1 = jet->at(0).tau2();
      hist("TAU2_1")->Fill(tau2_1, weight);
      float tau21_1 = tau2_1/tau1_1;
      hist("Tau21_1")->Fill(tau21_1, weight);

      float chf_2 = jet->at(1).chargedHadronEnergyFraction();
      hist("CHF_2")->Fill(chf_2, weight);
      float tau1_2 = jet->at(1).tau1();
      hist("TAU1_2")->Fill(tau1_2, weight);
      float tau2_2 = jet->at(1).tau2();
      hist("TAU2_2")->Fill(tau2_2, weight);
      float tau21_2 = tau2_2/tau1_2;
      hist("Tau21_2")->Fill(tau21_2, weight);

      float mass = (jet->at(0).v4() + jet->at(1).v4()).M();
      hist("invMass")->Fill(mass, weight);
      if(mass< 1600)
	hist("invMass_checkLeptons")->Fill(mass, weight);


      // const std::vector<GenParticle> &  genp = event.get(h_particles);
      // if(isMC)
      // 	{ 
      // 	    {
      // 	      for(int i =0;i<4;i++)
      // 		{
      // 		  const GenParticle & gpd = genp[i+7];
      // 		  hist("pdgID")->Fill(gpd.pdgId(), weight);
		  
      // 		  if(mass< 1600)
      // 		    hist("pdgID_checkLeptons")->Fill(gpd.pdgId(), weight);
      // 		}
      // 	    }
      // 	}
      hist("invMass_forfit")->Fill(mass, weight);
      float deta = jet->at(0).eta() - jet->at(1).eta();
      hist("delta_eta")->Fill(deta, weight);
      float dphi = jet->at(0).phi() - jet->at(1).phi();
      hist("delta_phi")->Fill(dphi, weight);
      float dR = sqrt(deta*deta+dphi*dphi);
      hist("delta_R")->Fill(dR, weight);



      // std::unique_ptr< std::vector<TopJet> >    pruned_topjets   (new std::vector<TopJet>   (*event.topjets));                                
      // std::sort(pruned_topjets.begin(), pruned_topjets.end(), [](const P & p1, const P & p2){return p1.prunedmass() > p2.prunedmass();});









}
