#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"

//#include "TProfile.h"

namespace uhh2examples {

/**  \brief Example class for booking and filling histograms
 * 
 * NOTE: This class uses the 'hist' method to retrieve histograms.
 * This requires a string lookup and is therefore slow if you have
 * many histograms. Therefore, it is recommended to use histogram
 * pointers as member data instead, like in 'common/include/ElectronHists.h'.
 */
class VBFresonanceToWWHists: public uhh2::Hists {
public:
    // use the same constructor arguments as Hists for forwarding:
    VBFresonanceToWWHists(uhh2::Context & ctx, const std::string & dirname);


    virtual void fill(const uhh2::Event & ev) override;
    virtual ~VBFresonanceToWWHists();
protected:
    TH2F* Njets_Npv;
    TH2F* Njets_Npv_barrel;
    TH2F* Njets_Npv_edge;
    TH2F* Njets_Npv_forward;
    //    TProfile* Njets_vs_Npv;


};

}
