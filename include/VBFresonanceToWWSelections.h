#pragma once

#include "UHH2/core/include/fwd.h"
#include "UHH2/core/include/Selection.h"

namespace uhh2examples {
    
/* Select events with at least two jets in which the leading two jets have deltaphi > 2.7 and the third jet pt is
 * below 20% of the average of the leading two jets, where the minimum deltaphi and
 * maximum third jet pt fraction can be changed in the constructor.
 * The jets are assumed to be sorted in pt.
 */
class DijetSelection: public uhh2::Selection {
public:
    DijetSelection(float dphi_min = 2.7f, float third_frac_max = 0.2f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float dphi_min, third_frac_max;
};

class VBFdeltaEtajetSelection: public uhh2::Selection {
public:
    VBFdeltaEtajetSelection(float deta_min = 3.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float deta_min;
};

class VBFdeltaEtaGenjetSelection: public uhh2::Selection {
public:
    VBFdeltaEtaGenjetSelection(float deta_min = 3.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float deta_min;
};

class VBFEtaSignjetSelection: public uhh2::Selection {
public:
    VBFEtaSignjetSelection();
    virtual bool passes(const uhh2::Event & event) override;
private:
   
};

class VBFEtaSignGenjetSelection: public uhh2::Selection {
public:
    VBFEtaSignGenjetSelection();
    virtual bool passes(const uhh2::Event & event) override;
private:
   
};

class VBFEtajetSelection: public uhh2::Selection {
public:
    VBFEtajetSelection(float deta_min = 3.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float deta_min;
};

class VBFEtaGenjetSelection: public uhh2::Selection {
public:
    VBFEtaGenjetSelection(float deta_min = 3.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float deta_min;
};


class JetsOverlappingSelection: public uhh2::Selection {
public:
    JetsOverlappingSelection(float deta_min = 1.2f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float deta_min;
};

class GenJetsOverlappingSelection: public uhh2::Selection {
public:
    GenJetsOverlappingSelection(float deta_min = 1.2f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float deta_min;
};

class VBFdeltaEtaTopjetSelection: public uhh2::Selection {
public:
    VBFdeltaEtaTopjetSelection(float deta_min = 1.3f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float deta_min;
};




}
