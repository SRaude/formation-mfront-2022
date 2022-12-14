/*!
* \file   TFEL/Material/MCBigoniMiniKHDBehaviourData.hxx
* \brief  this file implements the MCBigoniMiniKHDBehaviourData class.
*         File generated by tfel version 3.4.0
* \author Simon Raude
* \date   08 / 10 / 2022
 */

#ifndef LIB_TFELMATERIAL_MCBIGONIMINIKHD_BEHAVIOUR_DATA_HXX
#define LIB_TFELMATERIAL_MCBIGONIMINIKHD_BEHAVIOUR_DATA_HXX

#include<limits>
#include<string>
#include<sstream>
#include<iostream>
#include<stdexcept>
#include<algorithm>

#include"TFEL/Raise.hxx"
#include"TFEL/PhysicalConstants.hxx"
#include"TFEL/Config/TFELConfig.hxx"
#include"TFEL/Config/TFELTypes.hxx"
#include"TFEL/Metaprogramming/StaticAssert.hxx"
#include"TFEL/TypeTraits/IsFundamentalNumericType.hxx"
#include"TFEL/TypeTraits/IsReal.hxx"
#include"TFEL/Math/General/IEEE754.hxx"
#include"TFEL/Math/tvector.hxx"
#include"TFEL/Math/Vector/tvectorIO.hxx"
#include"TFEL/Math/stensor.hxx"
#include"TFEL/Math/Stensor/StensorView.hxx"
#include"TFEL/Math/Stensor/StensorConceptIO.hxx"
#include"TFEL/Math/tmatrix.hxx"
#include"TFEL/Math/Matrix/tmatrixIO.hxx"
#include"TFEL/Math/st2tost2.hxx"
#include"TFEL/Math/ST2toST2/ST2toST2ConceptIO.hxx"
#include"TFEL/Math/ST2toST2/ST2toST2View.hxx"
#include"TFEL/Material/ModellingHypothesis.hxx"

#line 128 "MCBigoniMiniKHD.mfront"
#include"TFEL/Material/Lame.hxx"

#include"MFront/Aster/Aster.hxx"

namespace tfel{

namespace material{

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename,bool>
class MCBigoniMiniKHDBehaviourData;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename Type,bool use_qt>
class MCBigoniMiniKHDIntegrationData;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
 operator <<(std::ostream&,const MCBigoniMiniKHDBehaviourData<hypothesis,Type,false>&);

template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
class MCBigoniMiniKHDBehaviourData<hypothesis,Type,false>
{

static constexpr unsigned short N = ModellingHypothesisToSpaceDimension<hypothesis>::value;
TFEL_STATIC_ASSERT(N==1||N==2||N==3);
TFEL_STATIC_ASSERT(tfel::typetraits::IsFundamentalNumericType<Type>::cond);
TFEL_STATIC_ASSERT(tfel::typetraits::IsReal<Type>::cond);

friend std::ostream& operator<< <>(std::ostream&,const MCBigoniMiniKHDBehaviourData&);

/* integration data is declared friend to access   driving variables at the beginning of the time step */
friend class MCBigoniMiniKHDIntegrationData<hypothesis,Type,false>;

static constexpr unsigned short TVectorSize = N;
typedef tfel::math::StensorDimeToSize<N> StensorDimeToSize;
static constexpr unsigned short StensorSize = StensorDimeToSize::value;
typedef tfel::math::TensorDimeToSize<N> TensorDimeToSize;
static constexpr unsigned short TensorSize = TensorDimeToSize::value;

using ushort =  unsigned short;
using Types = tfel::config::Types<N,Type,false>;
using real                = typename Types::real;
using time                = typename Types::time;
using length              = typename Types::length;
using frequency           = typename Types::frequency;
using stress              = typename Types::stress;
using strain              = typename Types::strain;
using strainrate          = typename Types::strainrate;
using stressrate          = typename Types::stressrate;
using temperature         = typename Types::temperature;
using thermalexpansion    = typename Types::thermalexpansion;
using thermalconductivity = typename Types::thermalconductivity;
using massdensity         = typename Types::massdensity;
using energydensity         = typename Types::energydensity;
using TVector             = typename Types::TVector;
using Stensor             = typename Types::Stensor;
using Stensor4            = typename Types::Stensor4;
using FrequencyStensor    = typename Types::FrequencyStensor;
using ForceTVector        = typename Types::ForceTVector;
using StressStensor       = typename Types::StressStensor;
using StressRateStensor   = typename Types::StressRateStensor;
using DisplacementTVector = typename Types::DisplacementTVector;
using StrainStensor       = typename Types::StrainStensor;
using StrainRateStensor   = typename Types::StrainRateStensor;
using StiffnessTensor     = typename Types::StiffnessTensor;
using Tensor              = typename Types::Tensor;
using FrequencyTensor     = typename Types::FrequencyTensor;
using StressTensor        = typename Types::StressTensor;
using ThermalExpansionCoefficientTensor = typename Types::ThermalExpansionCoefficientTensor;
using DeformationGradientTensor         = typename Types::DeformationGradientTensor;
using DeformationGradientRateTensor     = typename Types::DeformationGradientRateTensor;
using TemperatureGradient = typename Types::TemperatureGradient;
using HeatFlux = typename Types::HeatFlux;
using TangentOperator   = StiffnessTensor;
using PhysicalConstants = tfel::PhysicalConstants<real>;

protected:

StrainStensor eto;

StressStensor sig;

#line 27 "MCBigoniMiniKHD.mfront"
stress young;
#line 31 "MCBigoniMiniKHD.mfront"
real nu;
#line 35 "MCBigoniMiniKHD.mfront"
real phi;
#line 39 "MCBigoniMiniKHD.mfront"
real psi;
#line 43 "MCBigoniMiniKHD.mfront"
stress coh;
#line 47 "MCBigoniMiniKHD.mfront"
real at;
#line 51 "MCBigoniMiniKHD.mfront"
stress Yc;
#line 55 "MCBigoniMiniKHD.mfront"
real nD;
#line 59 "MCBigoniMiniKHD.mfront"
real qD;

StrainStensor eel;
#line 91 "MCBigoniMiniKHD.mfront"
StrainStensor epl;
#line 92 "MCBigoniMiniKHD.mfront"
real lam;
#line 93 "MCBigoniMiniKHD.mfront"
real alp;
#line 103 "MCBigoniMiniKHD.mfront"
real niter;
#line 104 "MCBigoniMiniKHD.mfront"
real ip;
#line 105 "MCBigoniMiniKHD.mfront"
strain evp;
#line 106 "MCBigoniMiniKHD.mfront"
strain gap;
#line 107 "MCBigoniMiniKHD.mfront"
real inst;
#line 108 "MCBigoniMiniKHD.mfront"
real domain;
#line 109 "MCBigoniMiniKHD.mfront"
stress XeqASV;
#line 110 "MCBigoniMiniKHD.mfront"
stress XmASV;
#line 111 "MCBigoniMiniKHD.mfront"
stress YASV;
temperature T;

public:

/*!
* \brief Default constructor
*/
MCBigoniMiniKHDBehaviourData()
{}

/*!
* \brief copy constructor
*/
MCBigoniMiniKHDBehaviourData(const MCBigoniMiniKHDBehaviourData& src)
: eto(src.eto),
sig(src.sig),
young(src.young),
nu(src.nu),
phi(src.phi),
psi(src.psi),
coh(src.coh),
at(src.at),
Yc(src.Yc),
nD(src.nD),
qD(src.qD),
eel(src.eel),
epl(src.epl),
lam(src.lam),
alp(src.alp),
niter(src.niter),
ip(src.ip),
evp(src.evp),
gap(src.gap),
inst(src.inst),
domain(src.domain),
XeqASV(src.XeqASV),
XmASV(src.XmASV),
YASV(src.YASV),
T(src.T)
{}

/*
 * \brief constructor for the Aster interface
 * \param[in] ASTERT_: temperature
 * \param[in] ASTERmat: material properties
 * \param[in] ASTERint_vars: state variables
 * \param[in] ASTERext_vars: external std::ate variables
 */
MCBigoniMiniKHDBehaviourData(const Type* const ASTERT_,const Type* const ASTERmat,
const Type* const ASTERint_vars
,const Type* const)
: young(ASTERmat[0]),
nu(ASTERmat[1]),
phi(ASTERmat[2]),
psi(ASTERmat[3]),
coh(ASTERmat[4]),
at(ASTERmat[5]),
Yc(ASTERmat[6]),
nD(ASTERmat[7]),
qD(ASTERmat[8]),
eel(&ASTERint_vars[0]),
epl(&ASTERint_vars[StensorSize]),
lam(ASTERint_vars[2*StensorSize]),
alp(ASTERint_vars[1+2*StensorSize]),
niter(ASTERint_vars[2+2*StensorSize]),
ip(ASTERint_vars[3+2*StensorSize]),
evp(ASTERint_vars[4+2*StensorSize]),
gap(ASTERint_vars[5+2*StensorSize]),
inst(ASTERint_vars[6+2*StensorSize]),
domain(ASTERint_vars[7+2*StensorSize]),
XeqASV(ASTERint_vars[8+2*StensorSize]),
XmASV(ASTERint_vars[9+2*StensorSize]),
YASV(ASTERint_vars[10+2*StensorSize]),
T(*ASTERT_)
{
}

void setASTERBehaviourDataGradients(const Type* const ASTERstran)
{
this->eto.importVoigt(ASTERstran);
}

void setASTERBehaviourDataThermodynamicForces(const Type* const ASTERstress_)
{
this->sig.importTab(ASTERstress_);
}


/*
* \brief Assignement operator
*/
MCBigoniMiniKHDBehaviourData&
operator=(const MCBigoniMiniKHDBehaviourData& src){
this->eto = src.eto;
this->sig = src.sig;
this->young = src.young;
this->nu = src.nu;
this->phi = src.phi;
this->psi = src.psi;
this->coh = src.coh;
this->at = src.at;
this->Yc = src.Yc;
this->nD = src.nD;
this->qD = src.qD;
this->eel = src.eel;
this->epl = src.epl;
this->lam = src.lam;
this->alp = src.alp;
this->niter = src.niter;
this->ip = src.ip;
this->evp = src.evp;
this->gap = src.gap;
this->inst = src.inst;
this->domain = src.domain;
this->XeqASV = src.XeqASV;
this->XmASV = src.XmASV;
this->YASV = src.YASV;
this->T = src.T;
return *this;
}

void
ASTERexportStateData(Type * const ASTERstress_,Type * const ASTERstatev) const
{
using namespace tfel::math;
this->sig.exportTab(ASTERstress_);
exportToBaseTypeArray(this->eel,&ASTERstatev[0]);
exportToBaseTypeArray(this->epl,&ASTERstatev[StensorSize]);
ASTERstatev[2*StensorSize] = this->lam;
ASTERstatev[1+2*StensorSize] = this->alp;
ASTERstatev[2+2*StensorSize] = this->niter;
ASTERstatev[3+2*StensorSize] = this->ip;
ASTERstatev[4+2*StensorSize] = this->evp;
ASTERstatev[5+2*StensorSize] = this->gap;
ASTERstatev[6+2*StensorSize] = this->inst;
ASTERstatev[7+2*StensorSize] = this->domain;
ASTERstatev[8+2*StensorSize] = this->XeqASV;
ASTERstatev[9+2*StensorSize] = this->XmASV;
ASTERstatev[10+2*StensorSize] = this->YASV;
} // end of ASTERexportStateData

}; // end of MCBigoniMiniKHDBehaviourDataclass

template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
operator <<(std::ostream& os,const MCBigoniMiniKHDBehaviourData<hypothesis,Type,false>& b)
{
os << "???????? : " << b.eto << '\n';
os << "?? : " << b.sig << '\n';
os << "young : " << b.young << '\n';
os << "nu : " << b.nu << '\n';
os << "phi : " << b.phi << '\n';
os << "psi : " << b.psi << '\n';
os << "coh : " << b.coh << '\n';
os << "at : " << b.at << '\n';
os << "Yc : " << b.Yc << '\n';
os << "nD : " << b.nD << '\n';
os << "qD : " << b.qD << '\n';
os << "??????? : " << b.eel << '\n';
os << "epl : " << b.epl << '\n';
os << "lam : " << b.lam << '\n';
os << "alp : " << b.alp << '\n';
os << "niter : " << b.niter << '\n';
os << "ip : " << b.ip << '\n';
os << "evp : " << b.evp << '\n';
os << "gap : " << b.gap << '\n';
os << "inst : " << b.inst << '\n';
os << "domain : " << b.domain << '\n';
os << "XeqASV : " << b.XeqASV << '\n';
os << "XmASV : " << b.XmASV << '\n';
os << "YASV : " << b.YASV << '\n';
os << "T : " << b.T << '\n';
return os;
}

} // end of namespace material

} // end of namespace tfel

#endif /* LIB_TFELMATERIAL_MCBIGONIMINIKHD_BEHAVIOUR_DATA_HXX */
