/*!
* \file   TFEL/Material/MCBigoniFullBehaviourData.hxx
* \brief  this file implements the MCBigoniFullBehaviourData class.
*         File generated by tfel version 3.4.0
* \author Simon Raude
* \date   07 / 10 / 2022
 */

#ifndef LIB_TFELMATERIAL_MCBIGONIFULL_BEHAVIOUR_DATA_HXX
#define LIB_TFELMATERIAL_MCBIGONIFULL_BEHAVIOUR_DATA_HXX

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
#include"TFEL/Math/stensor.hxx"
#include"TFEL/Math/Stensor/StensorView.hxx"
#include"TFEL/Math/Stensor/StensorConceptIO.hxx"
#include"TFEL/Math/tmatrix.hxx"
#include"TFEL/Math/Matrix/tmatrixIO.hxx"
#include"TFEL/Math/st2tost2.hxx"
#include"TFEL/Math/ST2toST2/ST2toST2ConceptIO.hxx"
#include"TFEL/Math/ST2toST2/ST2toST2View.hxx"
#include"TFEL/Material/ModellingHypothesis.hxx"

#line 107 "MCBigoniFull.mfront"
#include"TFEL/Material/Lame.hxx"

#include"MFront/Aster/Aster.hxx"

namespace tfel{

namespace material{

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename,bool>
class MCBigoniFullBehaviourData;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename Type,bool use_qt>
class MCBigoniFullIntegrationData;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
 operator <<(std::ostream&,const MCBigoniFullBehaviourData<hypothesis,Type,false>&);

template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
class MCBigoniFullBehaviourData<hypothesis,Type,false>
{

static constexpr unsigned short N = ModellingHypothesisToSpaceDimension<hypothesis>::value;
TFEL_STATIC_ASSERT(N==1||N==2||N==3);
TFEL_STATIC_ASSERT(tfel::typetraits::IsFundamentalNumericType<Type>::cond);
TFEL_STATIC_ASSERT(tfel::typetraits::IsReal<Type>::cond);

friend std::ostream& operator<< <>(std::ostream&,const MCBigoniFullBehaviourData&);

/* integration data is declared friend to access   driving variables at the beginning of the time step */
friend class MCBigoniFullIntegrationData<hypothesis,Type,false>;

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

#line 26 "MCBigoniFull.mfront"
stress young;
#line 30 "MCBigoniFull.mfront"
real nu;
#line 34 "MCBigoniFull.mfront"
real phi;
#line 38 "MCBigoniFull.mfront"
real psi;
#line 42 "MCBigoniFull.mfront"
stress coh;
#line 46 "MCBigoniFull.mfront"
real at;
#line 50 "MCBigoniFull.mfront"
real gam;

StrainStensor eel;
#line 81 "MCBigoniFull.mfront"
real lam;
#line 88 "MCBigoniFull.mfront"
real niter;
#line 89 "MCBigoniFull.mfront"
real ip;
#line 90 "MCBigoniFull.mfront"
strain evp;
#line 91 "MCBigoniFull.mfront"
strain gap;
#line 92 "MCBigoniFull.mfront"
real inst;
#line 93 "MCBigoniFull.mfront"
real lode;
temperature T;

public:

/*!
* \brief Default constructor
*/
MCBigoniFullBehaviourData()
{}

/*!
* \brief copy constructor
*/
MCBigoniFullBehaviourData(const MCBigoniFullBehaviourData& src)
: eto(src.eto),
sig(src.sig),
young(src.young),
nu(src.nu),
phi(src.phi),
psi(src.psi),
coh(src.coh),
at(src.at),
gam(src.gam),
eel(src.eel),
lam(src.lam),
niter(src.niter),
ip(src.ip),
evp(src.evp),
gap(src.gap),
inst(src.inst),
lode(src.lode),
T(src.T)
{}

/*
 * \brief constructor for the Aster interface
 * \param[in] ASTERT_: temperature
 * \param[in] ASTERmat: material properties
 * \param[in] ASTERint_vars: state variables
 * \param[in] ASTERext_vars: external std::ate variables
 */
MCBigoniFullBehaviourData(const Type* const ASTERT_,const Type* const ASTERmat,
const Type* const ASTERint_vars
,const Type* const)
: young(ASTERmat[0]),
nu(ASTERmat[1]),
phi(ASTERmat[2]),
psi(ASTERmat[3]),
coh(ASTERmat[4]),
at(ASTERmat[5]),
gam(ASTERmat[6]),
eel(&ASTERint_vars[0]),
lam(ASTERint_vars[StensorSize]),
niter(ASTERint_vars[1+StensorSize]),
ip(ASTERint_vars[2+StensorSize]),
evp(ASTERint_vars[3+StensorSize]),
gap(ASTERint_vars[4+StensorSize]),
inst(ASTERint_vars[5+StensorSize]),
lode(ASTERint_vars[6+StensorSize]),
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
MCBigoniFullBehaviourData&
operator=(const MCBigoniFullBehaviourData& src){
this->eto = src.eto;
this->sig = src.sig;
this->young = src.young;
this->nu = src.nu;
this->phi = src.phi;
this->psi = src.psi;
this->coh = src.coh;
this->at = src.at;
this->gam = src.gam;
this->eel = src.eel;
this->lam = src.lam;
this->niter = src.niter;
this->ip = src.ip;
this->evp = src.evp;
this->gap = src.gap;
this->inst = src.inst;
this->lode = src.lode;
this->T = src.T;
return *this;
}

void
ASTERexportStateData(Type * const ASTERstress_,Type * const ASTERstatev) const
{
using namespace tfel::math;
this->sig.exportTab(ASTERstress_);
exportToBaseTypeArray(this->eel,&ASTERstatev[0]);
ASTERstatev[StensorSize] = this->lam;
ASTERstatev[1+StensorSize] = this->niter;
ASTERstatev[2+StensorSize] = this->ip;
ASTERstatev[3+StensorSize] = this->evp;
ASTERstatev[4+StensorSize] = this->gap;
ASTERstatev[5+StensorSize] = this->inst;
ASTERstatev[6+StensorSize] = this->lode;
} // end of ASTERexportStateData

}; // end of MCBigoniFullBehaviourDataclass

template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
operator <<(std::ostream& os,const MCBigoniFullBehaviourData<hypothesis,Type,false>& b)
{
os << "???????? : " << b.eto << '\n';
os << "?? : " << b.sig << '\n';
os << "young : " << b.young << '\n';
os << "nu : " << b.nu << '\n';
os << "phi : " << b.phi << '\n';
os << "psi : " << b.psi << '\n';
os << "coh : " << b.coh << '\n';
os << "at : " << b.at << '\n';
os << "gam : " << b.gam << '\n';
os << "??????? : " << b.eel << '\n';
os << "lam : " << b.lam << '\n';
os << "niter : " << b.niter << '\n';
os << "ip : " << b.ip << '\n';
os << "evp : " << b.evp << '\n';
os << "gap : " << b.gap << '\n';
os << "inst : " << b.inst << '\n';
os << "lode : " << b.lode << '\n';
os << "T : " << b.T << '\n';
return os;
}

} // end of namespace material

} // end of namespace tfel

#endif /* LIB_TFELMATERIAL_MCBIGONIFULL_BEHAVIOUR_DATA_HXX */
