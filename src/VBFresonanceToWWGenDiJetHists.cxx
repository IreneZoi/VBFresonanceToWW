#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWGenDiJetHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/LorentzVector.h"
#include "UHH2/core/include/Jet.h"
#include "UHH2/core/include/Particle.h"
#include "UHH2/core/include/GenParticle.h"
#include "UHH2/common/include/Utils.h"

#include "TH1F.h"
#include <iostream>
#include <algorithm>

using namespace uhh2;
using namespace std;

VBFresonanceToWWGenDiJetHists::VBFresonanceToWWGenDiJetHists(Context & ctx, 
					     const std::string & dirname)  : Hists(ctx, dirname){
  //number
  book<TH1F>("N_jj","N_jj ",10,0,10);
  
  //mass
  book<TH1F>("Mass_1","Mass_{1} [GeV/c^{2}]",100,0,200);
  book<TH1F>("Mass_2","Mass_{2} [GeV/c^{2}]",100,0,200);

  //PT    
  book<TH1F>("PT_1","P_{T,1} [GeV/c]",100,0,5000);
  book<TH1F>("PT_2","P_{T,2} [GeV/c]",100,0,5000);

  // Phi 
  book<TH1F>("Phi_1"," #phi_{1} ",100,-M_PI,M_PI);
  book<TH1F>("Phi_2"," #phi_{2} ",100,-M_PI,M_PI);

  //Eta 
  book<TH1F>("Eta_1","#eta_{1}",60,-3,3);
  book<TH1F>("Eta_2","#eta_{2}",60,-3,3);

  //energy
  book<TH1F>("Energy_1","E_{1} [GeV]",100,0,7000);
  book<TH1F>("Energy_2","E_{2} [GeV]",100,0,7000);

  //jj

  //inv mass
  book<TH1F>("InvariantMass_jj","Mass_{jj} [GeV/c^{2}]",100,0,5000);

  //pt
  book<TH1F>("Pt_jj","p_{T_{jj}} [GeV/c]",100,0,1000);

  //delta phi
  book<TH1F>("Phi_jj","#Delta #phi_{jj}",100,0,M_PI);

  //delta eta
  book<TH1F>("Eta_jj","#Delta #eta_{jj}",100,-7,7);

  //delta R
  book<TH1F>("R_jj","#Delta R_{jj}",10,0,10);


  //VBF
  //number
  book<TH1F>("VBF_N_jj","N_jj ",10,0,10);
  
  //mass
  book<TH1F>("VBF_Mass_1","Mass_{1} [GeV/c^{2}]",100,0,1.6);
  book<TH1F>("VBF_Mass_2","Mass_{2} [GeV/c^{2}]",100,0,1.6);

  //PT    
  book<TH1F>("VBF_PT_1","P_{T,1} [GeV/c]",100,0,1500);
  book<TH1F>("VBF_PT_2","P_{T,2} [GeV/c]",100,0,1500);

  // Phi 
  book<TH1F>("VBF_Phi_1"," #phi_{1} ",100,-M_PI,M_PI);
  book<TH1F>("VBF_Phi_2"," #phi_{2} ",100,-M_PI,M_PI);

  //Eta 
  book<TH1F>("VBF_Eta_1","#eta_{1}",60,-6,6);
  book<TH1F>("VBF_Eta_2","#eta_{2}",60,-6,6);

  //energy
  book<TH1F>("VBF_Energy_1","E_{1} [GeV]",100,0,5000);
  book<TH1F>("VBF_Energy_2","E_{2} [GeV]",100,0,5000);

  //jj

  //inv mass
  book<TH1F>("VBF_InvariantMass_jj","Mass_{jj} [GeV/c^{2}]",100,0,7000);

  //pt
  book<TH1F>("VBF_Pt_jj","p_{T_{jj}} [GeV/c]",100,0,1000);

  //delta phi
  book<TH1F>("VBF_Phi_jj","#Delta #phi_{jj}",100,0,M_PI);

  //delta eta
  book<TH1F>("VBF_Eta_jj","#Delta #eta_{jj}",100,-15,15);

  //delta R
  book<TH1F>("VBF_R_jj","#Delta R_{jj}",70,0,15);

  h_genjets = ctx.get_handle<std::vector <GenParticle> >("genparticles");




 }


void VBFresonanceToWWGenDiJetHists::fill(const uhh2::Event & event){


  //Generator-Teilchen 
  assert(event.genjets);
  if(!event.is_valid(h_genjets)){

    return;

  }


  //Weightning                                                                                                                               
  double weight = event.weight;

  
  
  /*
    N_gp = 11
    ------------------------------------------------------------------------
    | id  | ind | d1    | d2    | mo1   | mo2   | stat | pt     | eta      | 
    ------------------------------------------------------------------------
    | 1   | 0   | 2     | 3     | 65535 | 65535 | 21   |    0   | 25222    | 
    | 2   | 1   | 2     | 3     | 65535 | 65535 | 21   |    0   | -25100   | 
    | 35  | 2   | 5     | 6     | 0     | 1     | 22   | 416.24 | 0.13285  | 
    | 2   | 3   | 65535 | 65535 | 0     | 1     | 23   | 96.752 | 3.3632   | 
    | 1   | 4   | 65535 | 65535 | 0     | 1     | 23   | 320.47 | -2.1299  | 
    | 24  | 5   | 7     | 8     | 2     | 65535 | 22   | 1092.7 | 0.46736  | 
    | -24 | 6   | 9     | 10    | 2     | 65535 | 22   | 675.58 | -0.65135 | 
    | 2   | 7   | 65535 | 65535 | 5     | 65535 | 23   | 236.95 | 0.57766  | 
    | -1  | 8   | 65535 | 65535 | 5     | 65535 | 23   | 856.63 | 0.4354   | 
    | 1   | 9   | 65535 | 65535 | 6     | 65535 | 23   | 334.13 | -0.53267 | 
    | -2  | 10  | 65535 | 65535 | 6     | 65535 | 23   | 341.81 | -0.75953 | 
    ------------------------------------------------------------------------
  */
  const std::vector<GenParticle> &  jet = event.get(h_genjets);
  const GenParticle & VBF1 = jet[3];
  const GenParticle & VBF2 = jet[4];
  const GenParticle & V1 = jet[5];
  const GenParticle & V2 = jet[6];
 

  float Mass1=0;
  float PT1=0;
  float Phi1=0;
  float Eta1=0;
  float Mass2=0;
  float PT2=0;
  float Phi2=0;
  float Eta2=0;
  float Energy1=0;
  float Energy2=0;

  if(VBF1.pt()>=VBF2.pt())
    {
      Mass1 = VBF1.v4().mass();
      PT1 = VBF1.pt();
      Phi1 = VBF1.v4().phi();
      Eta1 = VBF1.v4().eta();
      Mass2 = VBF2.v4().mass();
      PT2 = VBF2.pt();
      Phi2 = VBF2.v4().phi();
      Eta2 = VBF2.v4().eta();
      Energy1 = VBF1.v4().energy();
      Energy2 = VBF2.v4().energy();

    }
  else if(VBF2.pt()>VBF1.pt())
    {
      Mass1 = VBF2.v4().mass();
      PT1 = VBF2.pt();
      Phi1 = VBF2.v4().phi();
      Eta1 = VBF2.v4().eta();
      Mass2 = VBF1.v4().mass();
      PT2 = VBF1.pt();
      Phi2 = VBF1.v4().phi();
      Eta2 = VBF1.v4().eta();
      Energy1 = VBF2.v4().energy();
      Energy2 = VBF1.v4().energy();

    }

      hist("VBF_Mass_1")->Fill(Mass1, weight);
      hist("VBF_PT_1")->Fill(PT1, weight);
      hist("VBF_Phi_1")->Fill(Phi1, weight);
      hist("VBF_Eta_1")->Fill(Eta1, weight);
      hist("VBF_Mass_2")->Fill(Mass2, weight);
      hist("VBF_PT_2")->Fill(PT2, weight);
      hist("VBF_Phi_2")->Fill(Phi2, weight);
      hist("VBF_Eta_2")->Fill(Eta2, weight);
      hist("VBF_Energy_1")->Fill(Energy1, weight);
      hist("VBF_Energy_2")->Fill(Energy2, weight);
      float invMass = (VBF1.v4()+VBF2.v4()).M();
      hist("VBF_InvariantMass_jj")->Fill(invMass,weight);
      float Pt = (VBF1.v4()+VBF2.v4()).pt();
      hist("VBF_Pt_jj")->Fill(Pt,weight);
      auto deltaphi = deltaPhi(VBF1.v4(),VBF2.v4());
      hist("VBF_Phi_jj")->Fill(deltaphi,weight);
      auto deltaeta = VBF1.eta()-VBF2.eta();
      hist("VBF_Eta_jj")->Fill(deltaeta,weight);
      auto deltar = deltaR(VBF1.v4(),VBF2.v4());
      hist("VBF_R_jj")->Fill(deltar,weight);


      auto etaproduct = VBF1.eta()*VBF2.eta();
      if (  (fabs(deltaeta) > 3.0) && (etaproduct < 0))   hist("VBF_N_jj")->Fill(1);
  
  

  //  if(jet.size() < 2) return;
  if(V1.pt()>=V2.pt())
    {
      Mass1 = V1.v4().mass();
      PT1 = V1.pt();
      Phi1 = V1.v4().phi();
      Eta1 = V1.v4().eta();
      Mass2 = V2.v4().mass();
      PT2 = V2.pt();
      Phi2 = V2.v4().phi();
      Eta2 = V2.v4().eta();
      Energy1 = V1.v4().energy();
      Energy2 = V2.v4().energy();

    }
  else if(V2.pt()>V1.pt())
    {
      Mass1 = V2.v4().mass();
      PT1 = V2.pt();
      Phi1 = V2.v4().phi();
      Eta1 = V2.v4().eta();
      Mass2 = V1.v4().mass();
      PT2 = V1.pt();
      Phi2 = V1.v4().phi();
      Eta2 = V1.v4().eta();
      Energy1 = V2.v4().energy();
      Energy2 = V1.v4().energy();

    }



  hist("Mass_1")->Fill(Mass1, weight);
  hist("PT_1")->Fill(PT1, weight);
  hist("Phi_1")->Fill(Phi1, weight);
  hist("Eta_1")->Fill(Eta1, weight);
  hist("Mass_2")->Fill(Mass2, weight);
  hist("PT_2")->Fill(PT2, weight);
  hist("Phi_2")->Fill(Phi2, weight);
  hist("Eta_2")->Fill(Eta2, weight);
  hist("Energy_1")->Fill(Energy1, weight);
  hist("Energy_2")->Fill(Energy2, weight);

  hist("N_jj")->Fill(1);
  invMass = (V1.v4()+V2.v4()).M();
  hist("InvariantMass_jj")->Fill(invMass,weight);
  Pt = (V1.v4()+V2.v4()).pt();
  hist("Pt_jj")->Fill(Pt,weight);
  deltaphi = deltaPhi(V1.v4(),V2.v4());
  hist("Phi_jj")->Fill(deltaphi,weight);
  deltaeta = V1.eta()-V2.eta();
  hist("Eta_jj")->Fill(deltaeta,weight);
  deltar = deltaR(V1.v4(),V2.v4());
  hist("R_jj")->Fill(deltar,weight);

}




