#include "UHH2/VBFresonanceToWW/include/VBFresonanceToWWHists.h"
#include "UHH2/core/include/Event.h"

#include "TH1F.h"
#include <iostream>

using namespace std;
using namespace uhh2;
using namespace uhh2examples;

VBFresonanceToWWHists::VBFresonanceToWWHists(Context & ctx, const string & dirname): Hists(ctx, dirname){
  // book all histograms here
  
  // HT
  book<TH1F>("Ht_GenTopJet", "H_{T} [GeV/c]", 300, 0, 3000);  
  book<TH1F>("Ht_GenJet", "H_{T} [GeV/c]", 300, 0, 3000);  

  // jets
  book<TH1F>("N_jets", "N_{jets}", 20, 0, 20);  
  book<TH1F>("eta_jet1", "#eta^{jet 1}", 40, -2.5, 2.5);
  book<TH1F>("eta_jet2", "#eta^{jet 2}", 40, -2.5, 2.5);
  book<TH1F>("eta_jet3", "#eta^{jet 3}", 40, -2.5, 2.5);
  book<TH1F>("eta_jet4", "#eta^{jet 4}", 40, -2.5, 2.5);

  // leptons
  book<TH1F>("N_mu", "N^{#mu}", 10, 0, 10);
  book<TH1F>("pt_mu", "p_{T}^{#mu} [GeV/c]", 40, 0, 200);
  book<TH1F>("eta_mu", "#eta^{#mu}", 40, -2.1, 2.1);
  book<TH1F>("reliso_mu", "#mu rel. Iso", 40, 0, 0.5);

  // primary vertices
  book<TH1F>("N_pv", "N^{PV}", 25, 0, 50);


}


void VBFresonanceToWWHists::fill(const Event & event){
  // fill the histograms. Please note the comments in the header file:
  // 'hist' is used here a lot for simplicity, but it will be rather
  // slow when you have many histograms; therefore, better
  // use histogram pointers as members as in 'UHH2/common/include/ElectronHists.h'
  
  // Don't forget to always use the weight when filling.
  double weight = event.weight;

  //  Context * ctx;
  //bool isMC;

  //choose channel from .xml file                                                                                                                                                                          
  //isMC = (ctx->get("dataset_type") == "MC");

  //if(isMC)
  //{      
      // vector<GenTopJet> Tjets = *event.gentopjets;
      // if(Tjets.size()<1) return;
      // auto Ht_GenTopJet=0;
      
      // for(int i=0; i<Tjets.size();i++)
      // 	Ht_GenTopJet+=Tjets.at(i).pt();
      
      // hist("Ht_GenTopJet")->Fill(Ht_GenTopJet,weight);
      
      // vector<Particle> Gjets = *event.genjets;
      // if(Gjets.size()<1) return;
      // auto Ht_GenJet=0;
      
      // for(int i=0; i<Gjets.size();i++)
      // 	Ht_GenJet+=Gjets.at(i).pt();
      
      // hist("Ht_GenJet")->Fill(Ht_GenJet,weight);
      //}

  std::vector<Jet>* jets = event.jets;
  int Njets = jets->size();
  hist("N_jets")->Fill(Njets, weight);
  
  if(Njets>=1){
    hist("eta_jet1")->Fill(jets->at(0).eta(), weight);
  }
  if(Njets>=2){
    hist("eta_jet2")->Fill(jets->at(1).eta(), weight);
  }
  if(Njets>=3){
    hist("eta_jet3")->Fill(jets->at(2).eta(), weight);
  }
  if(Njets>=4){
    hist("eta_jet4")->Fill(jets->at(3).eta(), weight);
  }

  int Nmuons = event.muons->size();
  hist("N_mu")->Fill(Nmuons, weight);
  for (const Muon & thismu : *event.muons){
      hist("pt_mu")->Fill(thismu.pt(), weight);
      hist("eta_mu")->Fill(thismu.eta(), weight);
      hist("reliso_mu")->Fill(thismu.relIso(), weight);
  }
  
  int Npvs = event.pvs->size();
  hist("N_pv")->Fill(Npvs, weight);
}

VBFresonanceToWWHists::~VBFresonanceToWWHists(){}
