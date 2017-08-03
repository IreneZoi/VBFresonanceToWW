#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Jet.h"
//#include "ZPrimeTotTPrimeGenSelections.h"
#include "UHH2/core/include/LorentzVector.h"
#include <vector>
/**
 *
 *Histograms for GenTopJet
 *
 **/

class VBFresonanceToWWGenDiJetHists : public uhh2::Hists{
  public:
  VBFresonanceToWWGenDiJetHists(uhh2::Context & ctx, const std::string & dirname);//, const std::string & collection = " ");
    virtual void fill(const uhh2::Event & event) override;


 protected:
    TH1F *pt, *eta, *phi, *mass, *chf, *tau1, *tau2;

    /*    
    void BubbleSort(std::vector<Particle> &vec)
    {
      int i, j, flag = 1;    // set flag to 1 to start first pass
      float temp;             // holding variable
      int numLength = vec.size( ); 
      const  std::vector<Particle>  &   num;
     
      for(i = 1; (i <= numLength) && flag; i++)
	{
          flag = 0;
          for (j=0; j < (numLength -1); j++)
	    {
	      if (.at(j+1).v4().eta() > num.at(j).v4().eta())      // ascending order simply changes to <
		{ 
		  temp = num.at(j).v4().eta();             // swap elements
		  *num.at(j).v4().eta() = num.at(j+1).v4().eta();
		  *num.at(j+1).v4().eta() = temp;
		  flag = 1;               // indicates that a swap occurred.
		}
	    }
	}
      return;   //arrays are passed to functions by address; nothing is returned
    }
    */

    
    uhh2::Event::Handle<std::vector <Particle>  > h_genjets;
};
