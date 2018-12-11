#pragma once

#include "UHH2/core/include/fwd.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/common/include/ObjectIdUtils.h"

namespace uhh2examples {

/* Select events with at least two jets in which the leading two jets have deltaphi > 2.7 and the third jet pt is
 * below 20% of the average of the leading two jets, where the minimum deltaphi and
 * maximum third jet pt fraction can be changed in the constructor.
 * The jets are assumed to be sorted in pt.
 */
class MuonVeto: public uhh2::Selection {
public:
    MuonVeto(float deltR_min = 0.8f, const boost::optional<MuonId> & muid = boost::none);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float deltaR_min;
    boost::optional<MuonId> muid;
};

class ElectronVeto: public uhh2::Selection {
public:
    ElectronVeto(float deltR_min = 0.8f, const boost::optional<ElectronId> & eleid = boost::none);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float deltaR_min;
    boost::optional<ElectronId> eleid;
};


class DijetInvSelection: public uhh2::Selection {
public:
    DijetInvSelection(float size_max = 2.f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float size_max;
};

class AK4PtSelection: public uhh2::Selection {
public:
    AK4PtSelection(float pt_min = 50.f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float pt_min;
};

class AK4PtInvSelection: public uhh2::Selection {
public:
    AK4PtInvSelection(float pt_min = 50.f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float pt_min;
};


class VBFdeltaEtajetSelection: public uhh2::Selection {
public:
    VBFdeltaEtajetSelection(float deta_min = 3.0f);
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

class VBFEtaSignjetInvSelection: public uhh2::Selection {
public:
    VBFEtaSignjetInvSelection();
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

class VBFEtajetInvSelection: public uhh2::Selection {
public:
    VBFEtajetInvSelection(float deta_max = 3.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float deta_max;
};


class deltaEtaTopjetSelection: public uhh2::Selection {
public:
    deltaEtaTopjetSelection(float deta_max = 1.3f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float deta_max;
};


class VVMassSecLeadingTopjetSelection: public uhh2::Selection {
public:
    VVMassSecLeadingTopjetSelection(float M_sd_min = 65.0f, float M_sd_max = 105.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float M_sd_min, M_sd_max;
};

class VVMassLeadingTopjetSelection: public uhh2::Selection {
public:
    VVMassLeadingTopjetSelection(float M_sd_min = 65.0f, float M_sd_max = 105.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float M_sd_min, M_sd_max;
};


class VVMassTopjetSelection: public uhh2::Selection {
public:
    VVMassTopjetSelection(float M_sd_min = 65.0f, float M_sd_max = 105.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float M_sd_min, M_sd_max;
};

class HighMassLeadingTopjetSelection: public uhh2::Selection {
public:
    HighMassLeadingTopjetSelection(float M_sd_min = 135.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float M_sd_min;
};

class HighMassSecLeadingTopjetSelection: public uhh2::Selection {
public:
    HighMassSecLeadingTopjetSelection(float M_sd_min = 135.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float M_sd_min;
};


class HighMassTopjetSelection: public uhh2::Selection {
public:
    HighMassTopjetSelection(float M_sd_min = 135.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float M_sd_min;
};

class invMassTopjetSelection: public uhh2::Selection {
public:
    invMassTopjetSelection(float invM_min = 1050.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float invM_min;
};


class nSubjTopjetSelection: public uhh2::Selection {
public:
    nSubjTopjetSelection(float tau21_min = 0.f, float tau21_max = 0.35f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float tau21_min, tau21_max;
};

class invMassVBFjetSelection: public uhh2::Selection {
public:
    invMassVBFjetSelection(float invM_min = 500.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float invM_min;
};




class invMassVBFjetInvSelection: public uhh2::Selection {
public:
    invMassVBFjetInvSelection(float invM_max = 500.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float invM_max;
};

}


/*
class VBFdeltaEtaGenjetSelection: public uhh2::Selection {
public:
    VBFdeltaEtaGenjetSelection(float deta_min = 3.0f);
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

class EtaGenTopjetSelection: public uhh2::Selection {
public:
    EtaGenTopjetSelection(float eta_max = 2.5f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float eta_max;
};

class PtGenTopjetSelection: public uhh2::Selection {
public:
    PtGenTopjetSelection(float pt_min = 200.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float pt_min;
};

class deltaEtaGenTopjetSelection: public uhh2::Selection {
public:
    deltaEtaGenTopjetSelection(float deta_max = 1.3f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float deta_max;
};

class deltaRGenTopjetSelection: public uhh2::Selection {
public:
    deltaRGenTopjetSelection(float deltaR_min = 1.2f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float deltaR_min;
};

class invMassGenTopjetSelection: public uhh2::Selection {
public:
    invMassGenTopjetSelection(float invM_min = 1070.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
        float invM_min;
};

class VBFEtaSignGenjetSelection: public uhh2::Selection {
public:
    VBFEtaSignGenjetSelection();
    virtual bool passes(const uhh2::Event & event) override;
private:

};

class WWMassTopjetSelection: public uhh2::Selection {
public:
    WWMassTopjetSelection(float M_sd_min = 65.0f, float M_sd_max = 85.0f);
    virtual bool passes(const uhh2::Event & event) override;
private:
    float M_sd_min, M_sd_max;
};


 */
