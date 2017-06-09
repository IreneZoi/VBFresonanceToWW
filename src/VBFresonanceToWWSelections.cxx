#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWSelections.h"
#include "UHH2/core/include/Event.h"

#include <stdexcept>

using namespace uhh2examples;
using namespace uhh2;


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
	if((deltaR( event.genjets->at(i), event.gentopjets->at(0)) < deta_min)||(deltaR( event.genjets->at(i), event.gentopjets->at(0)) < deta_min)) return false;
	    else return true;
      }
     return true;
}

VBFdeltaEtaTopjetSelection::VBFdeltaEtaTopjetSelection(float deta_min_): deta_min(deta_min_){}

bool VBFdeltaEtaTopjetSelection::passes(const Event & event){
  assert(event.topjets); // if this fails, it probably means jets are not read in                                                                                                                             
  if(event.topjets->size() < 2) return false;

	  auto deltaeta = event.topjets->at(0).eta()-event.topjets->at(1).eta();
	  if( fabs(deltaeta) > deta_min) return false;
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
