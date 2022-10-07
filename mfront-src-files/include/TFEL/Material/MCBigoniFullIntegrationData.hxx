/*!
* \file   TFEL/Material/MCBigoniFullIntegrationData.hxx
* \brief  this file implements the MCBigoniFullIntegrationData class.
*         File generated by tfel version 3.4.0
* \author Simon Raude
* \date   15 / 09 / 2022
 */

#ifndef LIB_TFELMATERIAL_MCBIGONIFULL_INTEGRATION_DATA_HXX
#define LIB_TFELMATERIAL_MCBIGONIFULL_INTEGRATION_DATA_HXX

#include<string>
#include<iostream>
#include<limits>
#include<stdexcept>
#include<algorithm>

#include"TFEL/Raise.hxx"
#include"TFEL/PhysicalConstants.hxx"
#include"TFEL/Config/TFELConfig.hxx"
#include"TFEL/Config/TFELTypes.hxx"
#include"TFEL/Metaprogramming/StaticAssert.hxx"
#include"TFEL/TypeTraits/IsFundamentalNumericType.hxx"
#include"TFEL/TypeTraits/IsScalar.hxx"
#include"TFEL/TypeTraits/IsReal.hxx"
#include"TFEL/TypeTraits/Promote.hxx"
#include"TFEL/Math/General/IEEE754.hxx"
#include"TFEL/Math/stensor.hxx"
#include"TFEL/Math/st2tost2.hxx"
#line 104 "MCBigoniFull.mfront"
#include"TFEL/Material/Lame.hxx"

#include"MFront/Aster/Aster.hxx"

namespace tfel{

namespace material{

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename Type,bool use_qt>
class MCBigoniFullIntegrationData;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
 operator <<(std::ostream&,const MCBigoniFullIntegrationData<hypothesis,Type,false>&);

template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
class MCBigoniFullIntegrationData<hypothesis,Type,false>
{

static constexpr unsigned short N = ModellingHypothesisToSpaceDimension<hypothesis>::value;
TFEL_STATIC_ASSERT(N==1||N==2||N==3);
TFEL_STATIC_ASSERT(tfel::typetraits::IsFundamentalNumericType<Type>::cond);
TFEL_STATIC_ASSERT(tfel::typetraits::IsReal<Type>::cond);

friend std::ostream& operator<< <>(std::ostream&,const MCBigoniFullIntegrationData&);

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

/*!
 * \brief eto increment
 */
StrainStensor deto;

/*!
 * \brief time increment
 */
time dt;

temperature dT;
public:

/*!
* \brief Default constructor
*/
MCBigoniFullIntegrationData()
{}

/*!
* \brief Copy constructor
*/
MCBigoniFullIntegrationData(const MCBigoniFullIntegrationData& src)
: deto(src.deto),
dt(src.dt),
dT(src.dT)
{}

/*
 * \brief constructor for the Aster interface
 * \param[in] ASTERdt_: time increment
 * \param[in] ASTERdT_: temperature increment
 * \param[in] ASTERdext_vars: external state variables increments
 */
MCBigoniFullIntegrationData(const Type* const ASTERdt_,
const Type* const ASTERdT_,const Type* const)
: dt(*ASTERdt_),dT(*ASTERdT_)
{
}

void setASTERIntegrationDataGradients(const Type* const ASTERdstran)
{
this->deto.importVoigt(ASTERdstran);
}


/*
* \brief scale the integration data by a scalar.
*/
template<typename Scal>
typename std::enable_if<
tfel::typetraits::IsFundamentalNumericType<Scal>::cond&&
tfel::typetraits::IsScalar<Scal>::cond&&
tfel::typetraits::IsReal<Scal>::cond&&
std::is_same<Type,typename tfel::typetraits::Promote<Type,Scal>::type>::value,
MCBigoniFullIntegrationData&
>::type
scale(const MCBigoniFullBehaviourData<hypothesis,Type,false>&, const Scal time_scaling_factor){
this->dt   *= time_scaling_factor;
this->deto *= time_scaling_factor;
this->dT *= time_scaling_factor;
return *this;
}

/*!
* \brief update the driving variable in case of substepping.
*/
MCBigoniFullIntegrationData&
updateDrivingVariables(const MCBigoniFullBehaviourData<hypothesis,Type,false>&){
return *this;
}

}; // end of MCBigoniFullIntegrationDataclass

template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
operator <<(std::ostream& os,const MCBigoniFullIntegrationData<hypothesis,Type,false>& b)
{
os << "Δεᵗᵒ : " << b.deto << '\n';
os << "σ : " << b.sig << '\n';
os << "Δt : " << b.dt << '\n';
os << "ΔT : " << b.dT << '\n';
return os;
}

} // end of namespace material

} // end of namespace tfel

#endif /* LIB_TFELMATERIAL_MCBIGONIFULL_INTEGRATION_DATA_HXX */