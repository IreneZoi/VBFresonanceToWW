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
    /*
    const auto & jet0 = event.jets->at(0);
    const auto & jet1 = event.jets->at(1);
    auto deltaeta = event.jets->at(0).eta()-event.jets->at(1).eta();
    if( fabs(deltaeta) < deta_min) return false;
    else return true;
    */
    
    for(unsigned int i = 0; i <event.jets->size(); i++)
      {
	for(unsigned int j = i+1; j <event.jets->size(); j++)
	  {
	    auto deltaeta = event.jets->at(i).eta()-event.jets->at(j).eta();
	    if( fabs(deltaeta) < deta_min) return false;
            else return true;
	    std::cout << deltaeta << std::endl;
	  }
      }
    return true;
    
}

VBFdeltaEtaGenjetSelection::VBFdeltaEtaGenjetSelection(float deta_min_): deta_min(deta_min_){}
    
bool VBFdeltaEtaGenjetSelection::passes(const Event & event){
    assert(event.genjets); // if this fails, it probably means jets are not read in
    if(event.genjets->size() < 2) return false;
    /*
    const auto & jet0 = event.genjets->at(0);
    const auto & jet1 = event.genjets->at(1);
    auto deltaeta = event.genjets->at(0).eta()-event.genjets->at(1).eta();
    if(  fabs(deltaeta) < deta_min) return false;
    else return true;
    */    

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
    /*
    const auto & jet0 = event.jets->at(0);
    const auto & jet1 = event.jets->at(1);
    auto etaproduct = event.jets->at(0).eta()*event.jets->at(1).eta();   
    if (etaproduct > 0) return false;
    else return true;
    */
    
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
