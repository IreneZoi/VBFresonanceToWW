#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWW_WTopJetPDFHists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/TopJet.h"


#include "TH1F.h"
#include <iostream>
#include <sstream>

using namespace uhh2;
using namespace std;

VBFresonanceToWW_WTopJetPDFHists::VBFresonanceToWW_WTopJetPDFHists(Context & ctx,
					     const std::string & dirname)  : Hists(ctx, dirname){



  for(int i=0; i<100; i++)
    {
      stringstream ss_name;
      ss_name << "invMass_PDF_"  << i+1 ;
      
      stringstream ss_title;
      ss_title << "M_{jj}-AK8 [GeV/c^{2}] for PDF No. "  << i+1 << " out of 100" ;
      

      string s_name = ss_name.str();
      string s_title = ss_title.str();
      
      const char* char_name = s_name.c_str();
      const char* char_title = s_title.c_str();
      
      histo_names[i] = s_name;
      
      book<TH1F>(char_name, char_title, 30,1000,7000);
  }





  //  h_topjets = ctx.get_handle<std::vector <TopJet> >("topjets");
  h_jets = ctx.get_handle<std::vector <Jet> >("jets");
  h_particles = ctx.get_handle<std::vector <GenParticle> >("genparticles");
  isMC = (ctx.get("dataset_type") == "MC");


 }


void VBFresonanceToWW_WTopJetPDFHists::fill(const uhh2::Event & event){
  assert(event.topjets);
  if(isMC)
    assert(event.genparticles);



  
  std::vector<TopJet>* jet = event.topjets;
  

  if(jet->size() < 2) return;

  float mass = (jet->at(0).v4() + jet->at(1).v4()).M();

  const auto & sys_weights = event.genInfo->systweights();
  float orig_weight = sys_weights[0];
  //  float orig_weight = event.genInfo->pdf_scalePDF();
  cout << " event.genInfo->pdf_scalePDF() " << event.genInfo->pdf_scalePDF() << endl;
  cout << " event.genInfo->systweights(0) " << sys_weights[0] << endl;
  int MY_FIRST_INDEX = 9;

  for(int i=0;i<100;i++)
    {
      const char* name = histo_names[i].c_str();
      hist(name)->Fill(mass, event.weight * sys_weights[i+MY_FIRST_INDEX]/orig_weight);
      cout << "weight " << i << " " << sys_weights[i+MY_FIRST_INDEX]/orig_weight << endl; 
    }
}
