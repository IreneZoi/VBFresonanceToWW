#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWW_WTopJetHistsCorrectedSDMass.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/TopJet.h"


#include "TH1F.h"
#include "TFile.h"
#include "TF1.h"
#include <iostream>

using namespace uhh2;


VBFresonanceToWW_WTopJetHistsCorrectedSDMass::VBFresonanceToWW_WTopJetHistsCorrectedSDMass(Context & ctx,
					     const std::string & dirname)  : Hists(ctx, dirname){
  //number
  book<TH1F>("Njets","N jets",10,0,10);

  //mass
  book<TH1F>("Mass_1","Mass_{1} [GeV/c^{2}]",100,0,300);
  book<TH1F>("Mass_2","Mass_{2} [GeV/c^{2}]",100,0,300);

  //PT
  book<TH1F>("PT_1","P_{T,1} [GeV/c]",45,0,2025);
  book<TH1F>("PT_2","P_{T,2} [GeV/c]",45,0,2025);
  book<TH1F>("PT_both","P_{T} [GeV/c]",45,0,2025);

  book<TH1F>("PT_1_bigRange","P_{T,1} [GeV/c]",140,0,7000);
  book<TH1F>("PT_2_bigRange","P_{T,2} [GeV/c]",140,0,7000);
  book<TH1F>("PT_both_bigRange","P_{T} [GeV/c]",140,0,7000);

  // Phi
  book<TH1F>("Phi_1","#phi_{1} ",100,-M_PI,M_PI);
  book<TH1F>("Phi_2","#phi_{2} ",100,-M_PI,M_PI);
	book<TH1F>("Phi_both","#phi ",100,-M_PI,M_PI);

  //Eta
  book<TH1F>("Eta_1","#eta_{1}",50,-2.5,2.5);
  book<TH1F>("Eta_2","#eta_{2}",50,-2.5,2.5);
  book<TH1F>("Eta_both","#eta",50,-2.5,2.5);

  //substructure
  book<TH1F>("SoftDropMass_1", "M_{1}^{SD} [GeV/c^{2}]", 100,0,300);
  book<TH1F>("CHF_1","CHF_{1}",100,0,1);
  book<TH1F>("TAU1_1","#tau_{1_{1}}",20,0,1);
  book<TH1F>("TAU2_1","#tau_{2_{1}}",20,0,1);
  book<TH1F>("Tau21_1", "#tau_{2_{1}}/#tau_{1_{1}}", 20,0,1);

  book<TH1F>("SoftDropMass_2", "M_{2}^{SD} [GeV/c^{2}]", 100,0,300);
  book<TH1F>("CHF_2","CHF_{2}",100,0,1);
  book<TH1F>("TAU1_2","#tau_{1_{2}}",20,0,1);
  book<TH1F>("TAU2_2","#tau_{2_{2}}",20,0,1);
  book<TH1F>("Tau21_2", "#tau_{2_{2}}/#tau_{1_{2}}", 20,0,1);

	book<TH1F>("TAU1_both","#tau_{1}",20,0,1);
	book<TH1F>("TAU2_both","#tau_{2}",20,0,1);
	book<TH1F>("Tau21_both", "#tau_{2}/#tau_{1}", 20,0,1);
	book<TH1F>("SoftDropMass_both", "M^{SD} [GeV/c^{2}]", 100,0,300);
  book<TH1F>("CHF_both","Charged Hadron Energy Fraction",100,0,1);


	book<TH1F>("CM_both","Charged Multiplicity",120,0,120);
	book<TH1F>("NM_both","Neutral Multiplicity",90,0,90);
	book<TH1F>("PM_both","Photon Multiplicity",100,0,100);
	book<TH1F>("CEF_both","Charged EM Energy Fraction",100,0,1);
	book<TH1F>("MEF_both","Muon Energy Fraction",100,0,1);
	book<TH1F>("NHF_both","Neutral Hadron Energy Fraction",100,0,1);
	book<TH1F>("NEF_both","Neutral EM Energy Fraction",100,0,1);

  book<TH1F>("invMass","M_{jj}-AK8 [GeV/c^{2}]",30,1000,7000);
  book<TH1F>("invMass_check2AK4","M_{jj}-AK8 [GeV/c^{2}]",30,1000,7000);
  book<TH1F>("invMass_check1AK4","M_{jj}-AK8 [GeV/c^{2}]",30,1000,7000);
  book<TH1F>("invMass_checkLeptons","M_{jj}-AK8 [GeV/c^{2}]",30,1000,7000);
  book<TH1F>("pdgID","pdgID",33,-16,16);
  book<TH1F>("pdgID_checkLeptons","pdgID",33,-16,16);
  book<TH1F>("invMass_forfit","M_{jj}-AK8 [GeV/c^{2}]",30,1050,4050);
  book<TH1F>("invMass_rootfile","M_{jj}-AK8 [GeV/c^{2}]",13000,0,13000);

  book<TH1F>("delta_eta","#Delta #eta_{jj}",80,-5,5);
	book<TH1F>("abs_delta_eta_both","|#Delta #eta_{jj}|",40,0.,1.5);
  book<TH1F>("delta_phi","#Delta #phi_{jj}",200,-2*M_PI,2*M_PI);
  book<TH1F>("delta_R","#Delta R_{jj}",70,0,7);


  //  h_topjets = ctx.get_handle<std::vector <TopJet> >("topjets");
  h_jets = ctx.get_handle<std::vector <Jet> >("jets");
  h_particles = ctx.get_handle<std::vector <GenParticle> >("genparticles");
  isMC = (ctx.get("dataset_type") == "MC");


 }


void VBFresonanceToWW_WTopJetHistsCorrectedSDMass::fill(const uhh2::Event & event){
  assert(event.topjets);
  if(isMC)
    assert(event.genparticles);



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
      hist("PT_1_bigRange")->Fill(PT1, weight);
      float Phi1 = jet->at(0).v4().phi();
      hist("Phi_1")->Fill(Phi1, weight);
      float Eta1 = jet->at(0).v4().eta();
      hist("Eta_1")->Fill(Eta1, weight);

      float Mass2 = jet->at(1).v4().mass();
      hist("Mass_2")->Fill(Mass2, weight);
      float PT2 = jet->at(1).v4().pt();
      hist("PT_2")->Fill(PT2, weight);
      hist("PT_2_bigRange")->Fill(PT2, weight);
      hist("PT_both")->Fill(PT1, weight);
      hist("PT_both")->Fill(PT2, weight);
      hist("PT_both_bigRange")->Fill(PT1, weight);
      hist("PT_both_bigRange")->Fill(PT2, weight);
      float Phi2 = jet->at(1).v4().phi();
      hist("Phi_2")->Fill(Phi2, weight);
			hist("Phi_both")->Fill(Phi1, weight);
			hist("Phi_both")->Fill(Phi2, weight);

			float Eta2 = jet->at(1).v4().eta();
      hist("Eta_2")->Fill(Eta2, weight);
      hist("Eta_both")->Fill(Eta1, weight);
      hist("Eta_both")->Fill(Eta2, weight);


      // std::vector<TopJet> Tjets = *event.topjets;
      // if(Tjets.size()<1) return;
      // const auto & jet1 = Tjets[0];
      // const auto & jet2 = Tjets[1];
      // LorentzVector subjet_sum1;
      // LorentzVector subjet_sum2;
      // for (const auto s1 : jet1.subjets()) {
      // 	subjet_sum1 += s1.v4();
      // }
      // auto JetSDMass1 = subjet_sum1.M();
      // for (const auto s2 : jet2.subjets()) {
      // 	subjet_sum2 += s2.v4();
      // }
      // auto JetSDMass2 = subjet_sum2.M();
      auto JetSDMass1 = jet->at(0).softdropmass();
      auto JetSDMass2 = jet->at(1).softdropmass();

			hist("SoftDropMass_1")->Fill(JetSDMass1, weight);
      hist("SoftDropMass_2")->Fill(JetSDMass2, weight);
			hist("SoftDropMass_both")->Fill(JetSDMass1, weight);
      hist("SoftDropMass_both")->Fill(JetSDMass2, weight);




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

			hist("TAU1_both")->Fill(tau1_1, weight);
      hist("TAU2_both")->Fill(tau2_1, weight);
      hist("Tau21_both")->Fill(tau21_1, weight);
			hist("TAU1_both")->Fill(tau1_2, weight);
      hist("TAU2_both")->Fill(tau2_2, weight);
      hist("Tau21_both")->Fill(tau21_2, weight);
			hist("CHF_both")->Fill(chf_1, weight);
			hist("CHF_both")->Fill(chf_2, weight);


			float cm_1 = jet->at(0).chargedMultiplicity();
			float cm_2 = jet->at(1).chargedMultiplicity();
			hist("CM_both")->Fill(cm_1, weight);
			hist("CM_both")->Fill(cm_2, weight);

			float nm_1 = jet->at(0).neutralMultiplicity();
			float nm_2 = jet->at(1).neutralMultiplicity();
			hist("NM_both")->Fill(nm_1, weight);
			hist("NM_both")->Fill(nm_2, weight);

			float pm_1 = jet->at(0).photonMultiplicity();
			float pm_2 = jet->at(1).photonMultiplicity();
			hist("PM_both")->Fill(pm_1, weight);
			hist("PM_both")->Fill(pm_2, weight);

			float cef_1 = jet->at(0).chargedEmEnergyFraction();
			float cef_2 = jet->at(1).chargedEmEnergyFraction();
			hist("CEF_both")->Fill(cef_1, weight);
			hist("CEF_both")->Fill(cef_2, weight);

			float mef_1 = jet->at(0).muonEnergyFraction();
			float mef_2 = jet->at(1).muonEnergyFraction();
			hist("MEF_both")->Fill(mef_1, weight);
			hist("MEF_both")->Fill(mef_2, weight);

			float nhf_1 = jet->at(0).neutralHadronEnergyFraction();
			float nhf_2 = jet->at(1).neutralHadronEnergyFraction();
			hist("NHF_both")->Fill(nhf_1, weight);
			hist("NHF_both")->Fill(nhf_2, weight);

			float nef_1 = jet->at(0).neutralEmEnergyFraction();
			float nef_2 = jet->at(1).neutralEmEnergyFraction();
			hist("NEF_both")->Fill(nef_1, weight);
			hist("NEF_both")->Fill(nef_2, weight);


      float mass = (jet->at(0).v4() + jet->at(1).v4()).M();
      hist("invMass")->Fill(mass, weight);

      //      if(mass< 1600)


      if(isMC)
      	{
	  const std::vector<GenParticle> &  genp = event.get(h_particles);
	  const std::vector<Jet> &  ak4 = event.get(h_jets);

	  //	  for(unsigned int i=0; i<event.genp->size(); i++)
	  const GenParticle & gq1 = genp[3];
	  const GenParticle & gq2 = genp[4];
	  if(ak4.size()>2)
	    {
	      const Jet & j1 = ak4[0];
	      const Jet & j2 = ak4[1];

	      if((deltaR(j1,gq1)<0.2 && deltaR(j2,gq2)<0.2)||(deltaR(j2,gq1)<0.2 && deltaR(j1,gq2)<0.2))
		  hist("invMass_check2AK4")->Fill(mass, weight);
	      if(deltaR(j1,gq1)<0.2 || deltaR(j2,gq2)<0.2 || deltaR(j2,gq1)<0.2 || deltaR(j1,gq2)<0.2)
		  hist("invMass_check1AK4")->Fill(mass, weight);

	    }
	  GenParticle qW1;
	  GenParticle qW2;
	  GenParticle qW3;
	  GenParticle qW4;
	  int k = 0;
	  bool quark=false;
	  //std::cout << " new" << std::endl;
  for(unsigned int i=0; i<genp.size(); i++)
    {

      const GenParticle & gp = genp[i];
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

  if(quark) 	hist("invMass_checkLeptons")->Fill(mass, weight);


     	}
      hist("invMass_forfit")->Fill(mass, weight);
      hist("invMass_rootfile")->Fill(mass, weight);
      float deta = jet->at(0).eta() - jet->at(1).eta();
      hist("delta_eta")->Fill(deta, weight);
			hist("abs_delta_eta_both")->Fill(fabs(deta), weight);
      float dphi = jet->at(0).phi() - jet->at(1).phi();
      hist("delta_phi")->Fill(dphi, weight);
      float dR = sqrt(deta*deta+dphi*dphi);
      hist("delta_R")->Fill(dR, weight);



      // std::unique_ptr< std::vector<TopJet> >    pruned_topjets   (new std::vector<TopJet>   (*event.topjets));
      // std::sort(pruned_topjets.begin(), pruned_topjets.end(), [](const P & p1, const P & p2){return p1.prunedmass() > p2.prunedmass();});









}
