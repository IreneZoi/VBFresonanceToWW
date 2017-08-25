#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWSelections.h"
#include "UHH2/core/include/Event.h"

#include <stdexcept>

using namespace uhh2examples;
using namespace uhh2;
using namespace std;

bool PRINT = false;


DijetSelection::DijetSelection(float dphi_min_, float third_frac_max_): dphi_min(dphi_min_), third_frac_max(third_frac_max_){}
    
bool DijetSelection::passes(const Event & event){
    assert(event.jets); // if this fails, it probably means jets are not read in
    if(event.jets->size() < 2) return false;
    const auto & jet0 = event.jets->at(0);
    const auto & jet1 = event.jets->at(1);
    auto dphi = deltaPhi(jet0, jet1);
    if(dphi < dphi_min) return false;
    if(event.jets->size() == 2) return true;
    const auto & jet2 = event.jets->at(2);
    auto third_jet_frac = jet2.pt() / (0.5 * (jet0.pt() + jet1.pt()));
    return third_jet_frac < third_frac_max;

}

VBFdeltaEtajetSelection::VBFdeltaEtajetSelection(float deta_min_): deta_min(deta_min_){}
    
bool VBFdeltaEtajetSelection::passes(const Event & event){
    assert(event.jets); // if this fails, it probably means jets are not read in
    if(event.jets->size() < 2) return false;
    
    for(unsigned int i = 0; i <event.jets->size(); i++)
      {
	for(unsigned int j = i+1; j <event.jets->size(); j++)
	  {
	    auto deltaeta = event.jets->at(i).eta()-event.jets->at(j).eta();
	    if( fabs(deltaeta) < deta_min) return false;
            else return true;
	  }
      }
    return true;
    
}

VBFdeltaEtaGenjetSelection::VBFdeltaEtaGenjetSelection(float deta_min_): deta_min(deta_min_){}
    
bool VBFdeltaEtaGenjetSelection::passes(const Event & event){
    assert(event.genjets); // if this fails, it probably means jets are not read in
    if(event.genjets->size() < 2) return false;

    for(unsigned int i = 0; i <event.genjets->size(); i++)
      {
	for(unsigned int j = i+1; j <event.genjets->size(); j++)
	  {
	    auto deltaeta = event.genjets->at(i).eta()-event.genjets->at(j).eta();
	    if(  fabs(deltaeta) < deta_min) return false;
	    else return true;
	  }
      }
    return true;
  }    


VBFEtaSignjetSelection::VBFEtaSignjetSelection(){}
    
bool VBFEtaSignjetSelection::passes(const Event & event){
    assert(event.jets); // if this fails, it probably means jets are not read in
    if(event.jets->size() < 2) return false;
    for(unsigned int i = 0; i <event.jets->size(); i++)
      {
	for(unsigned int j = i+1; j <event.jets->size(); j++)
	  {

	    auto etaproduct = event.jets->at(i).eta()*event.jets->at(j).eta();
	    if (etaproduct > 0) return false;
	    else return true;
	  }
      }
    return true;
    
}

VBFEtaSignGenjetSelection::VBFEtaSignGenjetSelection(){}
    
bool VBFEtaSignGenjetSelection::passes(const Event & event){
    assert(event.genjets); // if this fails, it probably means jets are not read in
    if(event.genjets->size() < 2) return false;


    for(unsigned int i = 0; i <event.genjets->size(); i++)
      {
	for(unsigned int j = i+1; j <event.genjets->size(); j++)
	  {

	    auto etaproduct = event.genjets->at(i).eta()*event.genjets->at(j).eta();
	    if ( etaproduct > 0) return false;
	    else return true;
	  }
      }
    
    return true;
  }


VBFEtajetSelection::VBFEtajetSelection(float deta_min_): deta_min(deta_min_){}
    
bool VBFEtajetSelection::passes(const Event & event){
    assert(event.jets); // if this fails, it probably means jets are not read in
    if(event.jets->size() < 2) return false;
     for(unsigned int i = 0; i <event.jets->size(); i++)
      {
	for(unsigned int j = i+1; j <event.jets->size(); j++)
	  {

	    auto etaproduct = event.jets->at(i).eta()*event.jets->at(j).eta();
	    auto deltaeta = event.jets->at(i).eta()-event.jets->at(j).eta();
	    if (  (fabs(deltaeta) < deta_min) || (etaproduct > 0)) return false;
	    else return true;
	  }
      }
     return true;
}

VBFEtaGenjetSelection::VBFEtaGenjetSelection(float deta_min_): deta_min(deta_min_){}
    
bool VBFEtaGenjetSelection::passes(const Event & event){
    assert(event.genjets); // if this fails, it probably means jets are not read in
    if(event.genjets->size() < 2) return false;
     for(unsigned int i = 0; i <event.genjets->size(); i++)
      {
	for(unsigned int j = i+1; j <event.genjets->size(); j++)
	  {
	    auto etaproduct = event.genjets->at(i).eta()*event.genjets->at(j).eta();
	    auto deltaeta = event.genjets->at(i).eta()-event.genjets->at(j).eta();
	    if(  (fabs(deltaeta) < deta_min) || (etaproduct > 0)) return false;
	    else return true;
	  }
      }
     return true;
  }


JetsOverlappingSelection::JetsOverlappingSelection(float deta_min_): deta_min(deta_min_){}
    
bool JetsOverlappingSelection::passes(const Event & event){
    assert(event.jets); // if this fails, it probably means jets are not read in
    assert(event.topjets); // if this fails, it probably means jets are not read in

    if(event.jets->size() < 2) return false;
    if(event.topjets->size() < 2) return false;

    for(unsigned int i = 0; i <event.jets->size(); i++)
      {
	if((deltaR( event.jets->at(i), event.topjets->at(0)) < deta_min) ||(deltaR( event.jets->at(i), event.topjets->at(1)) < deta_min))  return false;
	    else return true;
      }
     return true;
}

GenJetsOverlappingSelection::GenJetsOverlappingSelection(float deta_min_): deta_min(deta_min_){}
    
bool GenJetsOverlappingSelection::passes(const Event & event){
    assert(event.genjets); // if this fails, it probably means jets are not read in
    assert(event.gentopjets); // if this fails, it probably means jets are not read in

    if(event.genjets->size() < 2) return false;
    if(event.gentopjets->size() < 2) return false;

    for(unsigned int i = 0; i <event.genjets->size(); i++)
      {
	if((deltaR( event.genjets->at(i), event.gentopjets->at(0)) < deta_min)||(deltaR( event.genjets->at(i), event.gentopjets->at(1)) < deta_min)) return false;
	    else return true;
      }
     return true;
  }

EtaGenTopjetSelection::EtaGenTopjetSelection(float eta_max_): eta_max(eta_max_){}

bool EtaGenTopjetSelection::passes(const Event & event){
  assert(event.gentopjets); // if this fails, it probably means jets are not read in                                                                                                                             
  if(event.gentopjets->size() < 2) return false;
    for(unsigned int i = 0; i <event.gentopjets->size(); i++)
      {
	if( fabs(event.gentopjets->at(i).eta()) > eta_max) return false;
	  else return true;
      }
    return true;
}

PtGenTopjetSelection::PtGenTopjetSelection(float pt_min_): pt_min(pt_min_){}

bool PtGenTopjetSelection::passes(const Event & event){
  assert(event.gentopjets); // if this fails, it probably means jets are not read in                                                                                                                             
  if(event.gentopjets->size() < 2) return false;
    for(unsigned int i = 0; i <event.gentopjets->size(); i++)
      {
	if( fabs(event.gentopjets->at(i).pt()) < pt_min) return false;
	  else return true;
      }
    return true;
}

deltaEtaGenTopjetSelection::deltaEtaGenTopjetSelection(float deta_max_): deta_max(deta_max_){}

bool deltaEtaGenTopjetSelection::passes(const Event & event){
  assert(event.gentopjets); // if this fails, it probably means jets are not read in                                                                                                                             
  if(event.gentopjets->size() < 2) return false;

	  auto deltaeta = event.gentopjets->at(0).eta()-event.gentopjets->at(1).eta();
	  if( fabs(deltaeta) > deta_max) return false;
	  else return true;
}

deltaRGenTopjetSelection::deltaRGenTopjetSelection(float deltaR_min_): deltaR_min(deltaR_min_){}

bool deltaRGenTopjetSelection::passes(const Event & event){
  assert(event.gentopjets); // if this fails, it probably means jets are not read in                                                                                                                       
  assert(event.genjets); // if this fails, it probably means jets are not read in  

  double deltaphi;
  double deltaeta;
  double deltar;
  for(int i=0; i< event.gentopjets->size(); i++)
    {
      for(int j=0; j< event.genjets->size(); j++)
	{
	  deltaphi = fabs(event.gentopjets->at(i).phi() - event.genjets->at(j).phi());
	  if(deltaphi > M_PI) deltaphi = 2* M_PI - deltaphi;
	  deltaeta = event.gentopjets->at(i).eta() - event.genjets->at(j).eta();
	  deltar = sqrt(deltaeta * deltaeta + deltaphi * deltaphi);
	  if( fabs(deltar) < deltaR_min) return false;
	  else return true;
	}
    }
}


invMassGenTopjetSelection::invMassGenTopjetSelection(float invM_min_): invM_min(invM_min_){}

bool invMassGenTopjetSelection::passes(const Event & event){
  assert(event.gentopjets); // if this fails, it probably means jets are not read in                                                                                                                          
  if(event.gentopjets->size() < 2) return false;

  auto invariantMass = (event.gentopjets->at(0).v4() + event.gentopjets->at(1).v4()).M();
	  if( invariantMass < invM_min) return false;
	  else return true;
}




deltaEtaTopjetSelection::deltaEtaTopjetSelection(float deta_max_): deta_max(deta_max_){}

bool deltaEtaTopjetSelection::passes(const Event & event){
  assert(event.topjets); // if this fails, it probably means jets are not read in                                                                                                                             
  if(event.topjets->size() < 2) return false;

	  auto deltaeta = event.topjets->at(0).eta()-event.topjets->at(1).eta();
	  if( fabs(deltaeta) > deta_max) return false;
	  else return true;
}

SDMassTopjetSelection::SDMassTopjetSelection(float M_sd_min_, float M_sd_max_): M_sd_min(M_sd_min_), M_sd_max(M_sd_max_){}

bool SDMassTopjetSelection::passes(const Event & event){
  if(PRINT) cout << " in SD mass sel " <<endl;
  assert(event.topjets); // if this fails, it probably means jets are not read in                                                                                                                           
  if(PRINT) cout << " asserted topjets" <<endl;
  if(event.topjets->size() < 2) return false;
  std::vector<TopJet> Tjets = *event.topjets;
  if(PRINT) cout << "TopJet" <<endl;
  const auto & jet1 = Tjets[0];
  const auto & jet2 = Tjets[1];
  if(PRINT) cout << "jets" <<endl;
  LorentzVector subjet_sum1;
  LorentzVector subjet_sum2;
  if(PRINT) cout << "lorentz subj" <<endl;
  for (const auto s1 : jet1.subjets())
    {
      subjet_sum1 += s1.v4();
    }

  auto JetSDMass1 = subjet_sum1.M();
  if(PRINT) cout << "sd mass 1 " <<endl;

  for (const auto s2 : jet2.subjets())
    {
      subjet_sum2 += s2.v4();
    }
  auto JetSDMass2 = subjet_sum2.M();
  if(PRINT) cout << "sd mass 2" <<endl;

	  if( JetSDMass1 < M_sd_min || JetSDMass2 < M_sd_min || JetSDMass1 > M_sd_max || JetSDMass2 > M_sd_max) return false;
	  if(PRINT) cout << "sd mass selection" <<endl;
	  
	  return true;
	  if(PRINT) cout << "end SD mass selection" <<endl;

}
VVMassTopjetSelection::VVMassTopjetSelection(float M_sd_min_, float M_sd_max_): M_sd_min(M_sd_min_), M_sd_max(M_sd_max_){}

bool VVMassTopjetSelection::passes(const Event & event){
  if(PRINT) cout << " in SD mass sel " <<endl;
  assert(event.topjets); // if this fails, it probably means jets are not read in                                                                                                                           
  if(PRINT) cout << " asserted topjets" <<endl;
  if(event.topjets->size() < 2) return false;
  std::vector<TopJet> Tjets = *event.topjets;
  if(PRINT) cout << "TopJet" <<endl;
  const auto & jet1 = Tjets[0];
  const auto & jet2 = Tjets[1];
  if(PRINT) cout << "jets" <<endl;
  LorentzVector subjet_sum1;
  LorentzVector subjet_sum2;
  if(PRINT) cout << "lorentz subj" <<endl;
  for (const auto s1 : jet1.subjets())
    {
      subjet_sum1 += s1.v4();
    }

  auto JetSDMass1 = subjet_sum1.M();
  if(PRINT) cout << "sd mass 1 " <<endl;

  for (const auto s2 : jet2.subjets())
    {
      subjet_sum2 += s2.v4();
    }
  auto JetSDMass2 = subjet_sum2.M();
  if(PRINT) cout << "sd mass 2" <<endl;

	  if( JetSDMass1 < M_sd_min || JetSDMass2 < M_sd_min || JetSDMass1 > M_sd_max || JetSDMass2 > M_sd_max) return false;
	  if(PRINT) cout << "sd mass selection" <<endl;
	  
	  return true;
	  if(PRINT) cout << "end SD mass selection" <<endl;

}

invMassTopjetSelection::invMassTopjetSelection(float invM_min_): invM_min(invM_min_){}

bool invMassTopjetSelection::passes(const Event & event){
  assert(event.topjets); // if this fails, it probably means jets are not read in                                                                                                                          
  if(event.topjets->size() < 2) return false;

  auto invariantMass = (event.topjets->at(0).v4() + event.topjets->at(1).v4()).M();
	  if( invariantMass < invM_min) return false;
	  else return true;
}

invMassTopjetFitSelection::invMassTopjetFitSelection(float invM_min_): invM_min(invM_min_){}

bool invMassTopjetFitSelection::passes(const Event & event){
  assert(event.topjets); // if this fails, it probably means jets are not read in                                                                                                                          
  if(event.topjets->size() < 2) return false;

  auto invariantMass = (event.topjets->at(0).v4() + event.topjets->at(1).v4()).M();
	  if( invariantMass < invM_min) return false;
	  else return true;
}

nSubjTopjetFitSelection::nSubjTopjetFitSelection(float tau21_max_): tau21_max(tau21_max_){}

bool nSubjTopjetFitSelection::passes(const Event & event){
  assert(event.topjets); // if this fails, it probably means jets are not read in   

  if(event.topjets->size() < 2) return false;


  float tau1_1 = event.topjets->at(0).tau1();                                                                                                                                                            
  float tau2_1 = event.topjets->at(0).tau2();                                                                                                                                                            
  float tau21_1 = tau2_1/tau1_1;             

  float tau1_2 = event.topjets->at(1).tau1();
  float tau2_2 = event.topjets->at(1).tau2();
  float tau21_2 = tau2_2/tau1_2;




  if( tau21_1 > tau21_max || tau21_2 > tau21_max ) return false;
	  else return true;
}

invM500VBFjetFitSelection::invM500VBFjetFitSelection(float invM_min_): invM_min(invM_min_){}

bool invM500VBFjetFitSelection::passes(const Event & event){
  assert(event.jets); // if this fails, it probably means jets are not read in                                                                                                                          
  if(event.jets->size() < 2) return false;

  auto invariantMass = (event.jets->at(0).v4() + event.jets->at(1).v4()).M();
	  if( invariantMass < invM_min) return false;
	  else return true;
}

invM1000VBFjetFitSelection::invM1000VBFjetFitSelection(float invM_min_): invM_min(invM_min_){}

bool invM1000VBFjetFitSelection::passes(const Event & event){
  assert(event.jets); // if this fails, it probably means jets are not read in                                                                                                                          
  if(event.jets->size() < 2) return false;

  auto invariantMass = (event.jets->at(0).v4() + event.jets->at(1).v4()).M();
	  if( invariantMass < invM_min) return false;
	  else return true;
}

invM1500VBFjetFitSelection::invM1500VBFjetFitSelection(float invM_min_): invM_min(invM_min_){}

bool invM1500VBFjetFitSelection::passes(const Event & event){
  assert(event.jets); // if this fails, it probably means jets are not read in                                                                                                                          
  if(event.jets->size() < 2) return false;

  auto invariantMass = (event.jets->at(0).v4() + event.jets->at(1).v4()).M();
	  if( invariantMass < invM_min) return false;
	  else return true;
}

invM2000VBFjetFitSelection::invM2000VBFjetFitSelection(float invM_min_): invM_min(invM_min_){}

bool invM2000VBFjetFitSelection::passes(const Event & event){
  assert(event.jets); // if this fails, it probably means jets are not read in                                                                                                                          
  if(event.jets->size() < 2) return false;

  auto invariantMass = (event.jets->at(0).v4() + event.jets->at(1).v4()).M();
	  if( invariantMass < invM_min) return false;
	  else return true;
}

















/*
VBFinvMassDijetSelection::VBFinvMassDijetSelection(float mass_min_): mass_min(mass_min_){}
    
bool VBFEtajetSelection::passes(const Event & event){
    assert(event.jets); // if this fails, it probably means jets are not read in
    if(event.jets->size() < 2) return false;
     for(unsigned int i = 0; i <event.jets->size(); i++)
      {
	for(unsigned int j = i+1; j <event.jets->size(); j++)
	  {

	    auto etaproduct = event.jets->at(i).eta()*event.jets->at(j).eta();
	    auto deltaeta = event.jets->at(i).eta()-event.jets->at(j).eta();
	    if (  (fabs(deltaeta) < deta_min) || (etaproduct > 0)) return false;
	    else return true;
	  }
      }
     return true;
}
*/
