/*!
* \file   TFEL/Material/MCBigoniFull.hxx
* \brief  this file implements the MCBigoniFull Behaviour.
*         File generated by tfel version 3.4.0
* \author Simon Raude
* \date   07 / 10 / 2022
 */

#ifndef LIB_TFELMATERIAL_MCBIGONIFULL_HXX
#define LIB_TFELMATERIAL_MCBIGONIFULL_HXX

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
#include"TFEL/TypeTraits/IsReal.hxx"
#include"TFEL/Math/General/IEEE754.hxx"
#include"TFEL/Material/MaterialException.hxx"
#include"TFEL/Material/MechanicalBehaviour.hxx"
#include"TFEL/Material/MechanicalBehaviourTraits.hxx"
#include"TFEL/Material/OutOfBoundsPolicy.hxx"
#include"TFEL/Material/BoundsCheck.hxx"
#include"TFEL/Material/IsotropicPlasticity.hxx"
#include"TFEL/Material/Lame.hxx"
#include"TFEL/Material/Hosford1972YieldCriterion.hxx"
#include"TFEL/Material/MCBigoniFullBehaviourData.hxx"
#include"TFEL/Material/MCBigoniFullIntegrationData.hxx"

#include"TFEL/Math/st2tost2.hxx"
#include"TFEL/Math/tmatrix.hxx"
#include"TFEL/Math/tvector.hxx"
#include"TFEL/Math/Matrix/tmatrixIO.hxx"
#include"TFEL/Math/Vector/tvectorIO.hxx"
#include"TFEL/Math/ST2toST2/ST2toST2ConceptIO.hxx"
#include"TFEL/Math/Vector/TinyVectorFromTinyVectorView.hxx"
#include"TFEL/Math/Vector/TinyVectorFromTinyVectorViewIO.hxx"
#include"TFEL/Math/Stensor/StensorFromTinyVectorView.hxx"
#include "TFEL/Math/Stensor/StensorFromTinyMatrixRowView.hxx"
#include "TFEL/Math/Stensor/StensorFromTinyMatrixRowView2.hxx"
#include"TFEL/Math/ST2toST2/ST2toST2FromTinyMatrixView.hxx"

#include"TFEL/Math/ST2toST2/ST2toST2FromTinyMatrixView2.hxx"

#include"TFEL/Math/Stensor/StensorFromTinyMatrixColumnView.hxx"
#include"TFEL/Math/Stensor/StensorFromTinyMatrixRowView.hxx"
#include"TFEL/Math/Stensor/StensorFromTinyMatrixColumnView2.hxx"
#include"TFEL/Math/Stensor/StensorFromTinyMatrixRowView2.hxx"
#include"TFEL/Math/Vector/TinyVectorOfStensorFromTinyVectorView.hxx"
#include"TFEL/Math/Vector/TinyVectorOfStensorFromTinyVectorViewIO.hxx"
#line 107 "MCBigoniFull.mfront"
#include"TFEL/Material/Lame.hxx"

#include"MFront/Aster/Aster.hxx"

namespace tfel{

namespace material{

struct MCBigoniFullParametersInitializer
{
static MCBigoniFullParametersInitializer&
get();

double theta;
double epsilon;
double minimal_time_step_scaling_factor;
double maximal_time_step_scaling_factor;
double numerical_jacobian_epsilon;
unsigned short iterMax;

void set(const char* const,const double);

void set(const char* const,const unsigned short);

/*!
 * \brief convert a string to double
 * \param[in] p : parameter
 * \param[in] v : value
 */
static double getDouble(const std::string&,const std::string&);
/*!
 * \brief convert a string to unsigned short
 * \param[in] p : parameter
 * \param[in] v : value
 */
static unsigned short getUnsignedShort(const std::string&,const std::string&);
private :

MCBigoniFullParametersInitializer();

MCBigoniFullParametersInitializer(const MCBigoniFullParametersInitializer&);

MCBigoniFullParametersInitializer&
operator=(const MCBigoniFullParametersInitializer&);
/*!
 * \brief read the parameters from the given file
 * \param[out] pi : parameters initializer
 * \param[in]  fn : file name
 */
static void readParameters(MCBigoniFullParametersInitializer&,const char* const);
};

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis,typename Type,bool use_qt>
class MCBigoniFull;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
 operator <<(std::ostream&,const MCBigoniFull<hypothesis,Type,false>&);

/*!
* \class MCBigoniFull
* \brief This class implements the MCBigoniFull behaviour.
* \param hypothesis, modelling hypothesis.
* \param Type, numerical type.
* \author Simon Raude
* \date   07 / 10 / 2022
*/
template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
class MCBigoniFull<hypothesis,Type,false> final
: public MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>,
public MCBigoniFullBehaviourData<hypothesis,Type,false>,
public MCBigoniFullIntegrationData<hypothesis,Type,false>
{

static constexpr unsigned short N = ModellingHypothesisToSpaceDimension<hypothesis>::value;

TFEL_STATIC_ASSERT(N==1||N==2||N==3);
TFEL_STATIC_ASSERT(tfel::typetraits::IsFundamentalNumericType<Type>::cond);
TFEL_STATIC_ASSERT(tfel::typetraits::IsReal<Type>::cond);

friend std::ostream& operator<< <>(std::ostream&,const MCBigoniFull&);

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

public :

typedef MCBigoniFullBehaviourData<hypothesis,Type,false> BehaviourData;
typedef MCBigoniFullIntegrationData<hypothesis,Type,false> IntegrationData;
typedef typename MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::SMFlag SMFlag;
typedef typename MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::SMType SMType;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::ELASTIC;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::SECANTOPERATOR;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::TANGENTOPERATOR;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::CONSISTENTTANGENTOPERATOR;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::NOSTIFFNESSREQUESTED;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::STANDARDTANGENTOPERATOR;
using IntegrationResult = typename MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::IntegrationResult;

using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::SUCCESS;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::FAILURE;
using MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::UNRELIABLE_RESULTS;

using StressFreeExpansionType = StrainStensor;

private :



typename tfel::math::StensorFromTinyVectorView<N,1+StensorSize,0,real>::type deel;
#line 81 "MCBigoniFull.mfront"
real& dlam;

#line 57 "MCBigoniFull.mfront"
bool b;
#line 58 "MCBigoniFull.mfront"
real local_zero_tolerance;
#line 59 "MCBigoniFull.mfront"
real pi;
#line 60 "MCBigoniFull.mfront"
real phir;
#line 61 "MCBigoniFull.mfront"
real psir;
#line 62 "MCBigoniFull.mfront"
real thetaFm;
#line 63 "MCBigoniFull.mfront"
real thetaGm;
#line 64 "MCBigoniFull.mfront"
real rF;
#line 65 "MCBigoniFull.mfront"
real rG;
#line 66 "MCBigoniFull.mfront"
real betaF;
#line 67 "MCBigoniFull.mfront"
real betaG;
#line 68 "MCBigoniFull.mfront"
real KFm;
#line 69 "MCBigoniFull.mfront"
real KGm;
#line 70 "MCBigoniFull.mfront"
stress aG;
#line 71 "MCBigoniFull.mfront"
Stensor4 Ce;
#line 72 "MCBigoniFull.mfront"
stress lambda;
#line 73 "MCBigoniFull.mfront"
stress mu;
#line 74 "MCBigoniFull.mfront"
stress ks;
#line 75 "MCBigoniFull.mfront"
Stensor nGtmp;

real theta;
real epsilon;
real minimal_time_step_scaling_factor;
real maximal_time_step_scaling_factor;
real numerical_jacobian_epsilon;
ushort iterMax;

//! Tangent operator;
TangentOperator Dt;
//! alias to the tangent operator;
TangentOperator& dsig_ddeto;
// updating material properties, in mandatory
void updateMaterialPropertiesDependantOnStateVariables(){
using namespace std;
using namespace tfel::math;
using std::vector;
}

// Jacobian
tfel::math::tmatrix<1+StensorSize,1+StensorSize,real> jacobian;
// zeros
tfel::math::tvector<1+StensorSize,real> zeros;

// previous zeros
tfel::math::tvector<1+StensorSize,real> zeros_1;

// function
tfel::math::tvector<1+StensorSize,real> fzeros;

// number of iterations
unsigned int iter = 0u;

void computeNumericalJacobian(tfel::math::tmatrix<1+StensorSize,1+StensorSize,real>& njacobian)
{
using namespace std;
using namespace tfel::math;
tvector<1+StensorSize,real> tzeros(this->zeros);
tvector<1+StensorSize,real> tfzeros(this->fzeros);
tmatrix<1+StensorSize,1+StensorSize,real> tjacobian(this->jacobian);
for(unsigned short idx = 0; idx!= 1+StensorSize;++idx){
this->zeros(idx) -= this->numerical_jacobian_epsilon;
this->computeThermodynamicForces();
this->computeFdF(true);
this->zeros = tzeros;
tvector<1+StensorSize,real> tfzeros2(this->fzeros);
this->zeros(idx) += this->numerical_jacobian_epsilon;
this->computeThermodynamicForces();
this->computeFdF(true);
this->fzeros = (this->fzeros-tfzeros2)/(2*(this->numerical_jacobian_epsilon));
for(unsigned short idx2 = 0; idx2!= 1+StensorSize;++idx2){
njacobian(idx2,idx) = this->fzeros(idx2);
}
this->zeros    = tzeros;
this->fzeros   = tfzeros;
}
if(&njacobian!=&(this->jacobian)){
this->jacobian = tjacobian;
}
}

void
computePartialJacobianInvert(const tfel::math::TinyPermutation<1+StensorSize>& jacobian_permutation, tfel::math::derivative_type<StrainStensor, StrainStensor>& partial_jacobian_eel)
{
using namespace tfel::math;
for(unsigned short idx=0;idx!=StensorSize;++idx){
tvector<1+StensorSize,real> vect_e(real(0));
vect_e(idx) = real(1);
TinyMatrixSolve<1+StensorSize,real>::back_substitute(this->jacobian,jacobian_permutation,vect_e);
for(unsigned short idx2=0;idx2!=StensorSize;++idx2){
partial_jacobian_eel(idx2,idx)=vect_e(idx2);
}
}
}

void
computePartialJacobianInvert(const tfel::math::TinyPermutation<1+StensorSize>& jacobian_permutation, tfel::math::derivative_type<StrainStensor, StrainStensor>& partial_jacobian_eel,
tfel::math::derivative_type<real, StrainStensor>& partial_jacobian_lam)
{
using namespace tfel::math;
for(unsigned short idx=0;idx!=StensorSize;++idx){
tvector<1+StensorSize,real> vect_e(real(0));
vect_e(idx) = real(1);
TinyMatrixSolve<1+StensorSize,real>::back_substitute(this->jacobian,jacobian_permutation,vect_e);
for(unsigned short idx2=0;idx2!=StensorSize;++idx2){
partial_jacobian_eel(idx2,idx)=vect_e(idx2);
}
partial_jacobian_lam(idx)=vect_e(StensorSize);
}
}

void additionalConvergenceChecks(bool&,real&,const SMType) const{
} // end of additionalConvergenceChecks

void computeThermodynamicForces(){
using namespace std;
using namespace tfel::math;
using std::vector;
#line 170 "MCBigoniFull.mfront"
this->sig=this->lambda*trace((this->eel+(this->theta)*(this->deel)))*StrainStensor::Id()+2.*this->mu*(this->eel+(this->theta)*(this->deel));
} // end of MCBigoniFull::computeThermodynamicForces

void computeFinalThermodynamicForces(){
using namespace std;
using namespace tfel::math;
using std::vector;
#line 170 "MCBigoniFull.mfront"
this->sig=this->lambda*trace(this->eel)*StrainStensor::Id()+2.*this->mu*this->eel;
} // end of MCBigoniFull::computeFinalThermodynamicForces

/*!
* \brief Update internal variables at end of integration
*/
void updateIntegrationVariables(){
}

/*!
* \brief Update internal variables at end of integration
*/
void updateStateVariables(){
this->eel += this->deel;
this->lam += this->dlam;
}

/*!
* \brief Update auxiliary state variables at end of integration
*/
void updateAuxiliaryStateVariables(){
using namespace std;
using namespace tfel::math;
#line 288 "MCBigoniFull.mfront"
const StressStensor sd=deviator(this->sig);
#line 289 "MCBigoniFull.mfront"
const stress J2=.5*(sd|sd);
#line 290 "MCBigoniFull.mfront"
const stress J3=det(sd);
#line 291 "MCBigoniFull.mfront"
const real C3T=min(max(.5*J3*pow(3./max(J2,this->local_zero_tolerance),1.5),-1.),1.);
#line 292 "MCBigoniFull.mfront"
this->lode=acos(C3T)/3.*180./this->pi;
#line 293 "MCBigoniFull.mfront"
this->inst+=this->dt;
#line 294 "MCBigoniFull.mfront"
this->niter=iter;
#line 295 "MCBigoniFull.mfront"
if (this->dlam>0) {
#line 296 "MCBigoniFull.mfront"
this->ip=1;
#line 297 "MCBigoniFull.mfront"
this->evp+=this->dlam*sin(this->psir);
#line 298 "MCBigoniFull.mfront"
this->gap+=this->dlam*sqrt(2.*deviator(this->nGtmp)|deviator(this->nGtmp)/3.);
#line 299 "MCBigoniFull.mfront"
} else {
#line 300 "MCBigoniFull.mfront"
this->ip=0;
#line 301 "MCBigoniFull.mfront"
}
}

//! \brief Default constructor (disabled)
MCBigoniFull() =delete ;
//! \brief Copy constructor (disabled)
MCBigoniFull(const MCBigoniFull&) = delete;
//! \brief Assignement operator (disabled)
MCBigoniFull& operator = (const MCBigoniFull&) = delete;

public:

/*!
* \brief Constructor
*/
MCBigoniFull(const MCBigoniFullBehaviourData<hypothesis,Type,false>& src1,
const MCBigoniFullIntegrationData<hypothesis,Type,false>& src2)
: MCBigoniFullBehaviourData<hypothesis,Type,false>(src1),
MCBigoniFullIntegrationData<hypothesis,Type,false>(src2),
deel(this->zeros),
dlam(this->zeros(StensorSize)),
dsig_ddeto(Dt),
zeros(real(0)),
fzeros(real(0))
{
using namespace std;
using namespace tfel::math;
using std::vector;
this->theta = MCBigoniFullParametersInitializer::get().theta;
this->epsilon = MCBigoniFullParametersInitializer::get().epsilon;
this->minimal_time_step_scaling_factor = MCBigoniFullParametersInitializer::get().minimal_time_step_scaling_factor;
this->maximal_time_step_scaling_factor = MCBigoniFullParametersInitializer::get().maximal_time_step_scaling_factor;
this->numerical_jacobian_epsilon = MCBigoniFullParametersInitializer::get().numerical_jacobian_epsilon;
this->iterMax = MCBigoniFullParametersInitializer::get().iterMax;
}

/*
 * \brief constructor for the Aster interface
 * \param[in] ASTERdt_: time increment
 * \param[in] ASTERT_: temperature
 * \param[in] ASTERdT_: temperature increment
 * \param[in] ASTERmat: material properties
 * \param[in] ASTERint_vars: state variables
 * \param[in] ASTERext_vars: external state variables
 * \param[in] ASTERdext_vars: external state variables increments
 */
MCBigoniFull(const Type* const ASTERdt_,
const Type* const ASTERT_,
const Type* const ASTERdT_,
const Type* const ASTERmat,
const Type* const ASTERint_vars,
const Type* const ASTERext_vars,
const Type* const ASTERdext_vars)
: MCBigoniFullBehaviourData<hypothesis,Type,false>(ASTERT_,ASTERmat,
ASTERint_vars,ASTERext_vars),
MCBigoniFullIntegrationData<hypothesis,Type,false>(ASTERdt_,ASTERdT_,ASTERdext_vars),
deel(this->zeros),
dlam(this->zeros(StensorSize)),
dsig_ddeto(Dt),
zeros(real(0)),
fzeros(real(0))
{
using namespace std;
using namespace tfel::math;
using std::vector;
this->theta = MCBigoniFullParametersInitializer::get().theta;
this->epsilon = MCBigoniFullParametersInitializer::get().epsilon;
this->minimal_time_step_scaling_factor = MCBigoniFullParametersInitializer::get().minimal_time_step_scaling_factor;
this->maximal_time_step_scaling_factor = MCBigoniFullParametersInitializer::get().maximal_time_step_scaling_factor;
this->numerical_jacobian_epsilon = MCBigoniFullParametersInitializer::get().numerical_jacobian_epsilon;
this->iterMax = MCBigoniFullParametersInitializer::get().iterMax;
}

/*!
 * \ brief initialize the behaviour with user code
 */
void initialize(){
using namespace std;
using namespace tfel::math;
using std::vector;
#line 111 "MCBigoniFull.mfront"
using namespace tfel::material::lame;
#line 112 "MCBigoniFull.mfront"
this->local_zero_tolerance=real(1e-12);
#line 113 "MCBigoniFull.mfront"
this->pi=4.*atan(1.);
#line 115 "MCBigoniFull.mfront"
this->phir=this->phi*this->pi/180.;
#line 116 "MCBigoniFull.mfront"
this->psir=this->psi*this->pi/180.;
#line 118 "MCBigoniFull.mfront"
this->thetaFm=atan(-sin(this->phir)/sqrt(3.));
#line 119 "MCBigoniFull.mfront"
this->thetaGm=atan(-sin(this->psir)/sqrt(3.));
#line 120 "MCBigoniFull.mfront"
this->rF=(3.-sin(this->phir))/(3.+sin(this->phir));
#line 121 "MCBigoniFull.mfront"
this->rG=(3.-sin(this->psir))/(3.+sin(this->psir));
#line 122 "MCBigoniFull.mfront"
this->betaF=6./this->pi*atan((2.*this->rF-1.)/sqrt(3.));
#line 123 "MCBigoniFull.mfront"
this->betaG=6./this->pi*atan((2.*this->rG-1.)/sqrt(3.));
#line 124 "MCBigoniFull.mfront"
this->KFm=(cos(this->thetaFm)-sin(this->phir)*sin(this->thetaFm)/sqrt(3.))/cos(this->betaF*this->pi/6.-acos(this->gam*cos(3.*(this->thetaFm+this->pi/6.)))/3.);
#line 125 "MCBigoniFull.mfront"
this->KGm=(cos(this->thetaGm)-sin(this->psir)*sin(this->thetaGm)/sqrt(3.))/cos(this->betaG*this->pi/6.-acos(this->gam*cos(3.*(this->thetaGm+this->pi/6.)))/3.);
#line 127 "MCBigoniFull.mfront"
this->aG=this->at*tan(this->phir)/tan(this->psir);
#line 129 "MCBigoniFull.mfront"
this->lambda=computeLambda(this->young,this->nu);
#line 130 "MCBigoniFull.mfront"
this->mu=computeMu(this->young,this->nu);
#line 131 "MCBigoniFull.mfront"
this->ks=this->lambda+2.*this->mu/3.;
#line 132 "MCBigoniFull.mfront"
this->Ce=3.*this->ks*Stensor4::J()+2.*this->mu*Stensor4::K();
#line 134 "MCBigoniFull.mfront"
if (this->inst==real(0) && this->lam==real(0)) {
#line 135 "MCBigoniFull.mfront"
const Stensor4 Se=invert(this->Ce);
#line 136 "MCBigoniFull.mfront"
this->eel=(Se*this->sig);
#line 137 "MCBigoniFull.mfront"
}
}

/*!
* \brief set the policy for "out of bounds" conditions
*/
void
setOutOfBoundsPolicy(const OutOfBoundsPolicy policy_value){
this->policy = policy_value;
} // end of setOutOfBoundsPolicy

/*!
* \return the modelling hypothesis
*/
constexpr ModellingHypothesis::Hypothesis
getModellingHypothesis() const{
return hypothesis;
} // end of getModellingHypothesis

/*!
* \brief check bounds
*/
void checkBounds() const{
} // end of checkBounds

IntegrationResult computePredictionOperator(const SMFlag,const SMType) override{
tfel::raise("MCBigoniFull::computePredictionOperator: "
"unsupported prediction operator flag");
}

real getMinimalTimeStepScalingFactor() const override{
  return this->minimal_time_step_scaling_factor;
}

std::pair<bool,real>
computeAPrioriTimeStepScalingFactor(const real current_time_step_scaling_factor) const override{
const auto time_scaling_factor = this->computeAPrioriTimeStepScalingFactorII();
return {time_scaling_factor.first,
        std::min(std::min(std::max(time_scaling_factor.second,
                                   this->minimal_time_step_scaling_factor),
                          this->maximal_time_step_scaling_factor),
                  current_time_step_scaling_factor)};
}

/*!
 * \brief Integrate behaviour law over the time step
 */
IntegrationResult integrate(const SMFlag smflag,const SMType smt) override{
using namespace std;
using namespace tfel::math;
tfel::raise_if(smflag!=MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::STANDARDTANGENTOPERATOR,
"invalid tangent operator flag");
#line 147 "MCBigoniFull.mfront"
StressStensor sigel(this->lambda*trace(this->eel+this->deto)*Stensor::Id()+2.*this->mu*(this->eel+this->deto));
#line 150 "MCBigoniFull.mfront"
const StressStensor sdel=deviator(sigel);
#line 151 "MCBigoniFull.mfront"
const stress J2el=.5*(sdel|sdel);
#line 152 "MCBigoniFull.mfront"
const stress I1el=trace(sigel);
#line 153 "MCBigoniFull.mfront"
const stress J3el=det(sdel);
#line 154 "MCBigoniFull.mfront"
const real C3Tel=min(max(.5*J3el*pow(3./max(J2el,this->local_zero_tolerance),1.5),-1.),1.);
#line 157 "MCBigoniFull.mfront"
const real KFel=this->KFm*cos(this->betaF*this->pi/6.-acos(this->gam*C3Tel)/3.);
#line 160 "MCBigoniFull.mfront"
const stress RFel=sqrt(J2el*KFel*KFel+this->at*this->at*sin(this->phir)*sin(this->phir));
#line 161 "MCBigoniFull.mfront"
this->b=RFel+I1el*sin(this->phir)/3.-this->coh*cos(this->phir)>real(0);
auto error = real{};
bool converged=false;
this->iter=0;
while((converged==false)&&
(this->iter<MCBigoniFull::iterMax)){
++(this->iter);
this->computeThermodynamicForces();
const auto computeFdF_ok = this->computeFdF(false);
if(computeFdF_ok){
error=norm(this->fzeros)/(real(1+StensorSize));
}
if((!computeFdF_ok)||(!ieee754::isfinite(error))){
if(this->iter==1){
return MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::FAILURE;
} else {
const real integrate_one_half = real(1)/real(2);
this->zeros -= (this->zeros-this->zeros_1)*integrate_one_half;
this->updateMaterialPropertiesDependantOnStateVariables();
}
} else {
this->zeros_1  = this->zeros;
converged = error<this->epsilon;
this->additionalConvergenceChecks(converged, error, smt);
if((!converged)||(smt!=NOSTIFFNESSREQUESTED)){
}
if(!converged){
try{
TinyMatrixSolve<1+StensorSize,real>::exe(this->jacobian,this->fzeros);
}
catch(LUException&){
return MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::FAILURE;
}
this->zeros -= this->fzeros;
this->updateMaterialPropertiesDependantOnStateVariables();
}
}
}
if(this->iter==this->iterMax){
return MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::FAILURE;
}
this->updateIntegrationVariables();
this->updateStateVariables();
this->computeFinalThermodynamicForces();
this->updateAuxiliaryStateVariables();
if(smt!=NOSTIFFNESSREQUESTED){
if(!this->computeConsistentTangentOperator(smt)){
return MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::FAILURE;
}
}
return MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>::SUCCESS;
} // end of MCBigoniFull::integrate

/*!
* \brief compute fzeros and jacobian
*/
bool computeFdF(const bool perturbatedSystemEvaluation){
using namespace std;
using namespace tfel::math;
using std::vector;
// silent compiler warning
static_cast<void>(perturbatedSystemEvaluation); 
constexpr const auto eel_offset = 0;
static_cast<void>(eel_offset);
typename tfel::math::StensorFromTinyVectorView<N,1+StensorSize,0,real>::type feel(this->fzeros);
constexpr const auto lam_offset = StensorSize;
static_cast<void>(lam_offset);
real& flam(this->fzeros(StensorSize));
// derivative of variable feel by variable eel
typename tfel::math::ST2toST2FromTinyMatrixView<N,1+StensorSize,1+StensorSize,
0,0,real>::type dfeel_ddeel(this->jacobian);
// derivative of variable feel by variable lam
typename tfel::math::StensorFromTinyMatrixColumnView<N,1+StensorSize,1+StensorSize,
0,StensorSize,real>::type dfeel_ddlam(this->jacobian);
// derivative of variable flam by variable eel
typename tfel::math::StensorFromTinyMatrixRowView<N,1+StensorSize,1+StensorSize,
StensorSize,0,real>::type dflam_ddeel(this->jacobian);
// derivative of variable flam by variable lam
real& dflam_ddlam = this->jacobian(StensorSize,StensorSize);
// setting jacobian to identity
std::fill(this->jacobian.begin(),this->jacobian.end(),real(0));
for(unsigned short idx = 0; idx!=1+StensorSize;++idx){
this->jacobian(idx,idx)= real(1);
}
// setting f values to zeros
this->fzeros = this->zeros;
#line 180 "MCBigoniFull.mfront"
if ((this->b)){
#line 183 "MCBigoniFull.mfront"
const StressStensor sd=deviator((this->sig));
#line 184 "MCBigoniFull.mfront"
const stress J2=.5*(sd|sd);
#line 185 "MCBigoniFull.mfront"
const stress I1=trace((this->sig));
#line 186 "MCBigoniFull.mfront"
const stress J3=det(sd);
#line 187 "MCBigoniFull.mfront"
const real C3T=min(max(.5*J3*pow(3./max(J2,(this->local_zero_tolerance)),1.5),-1.),1.);
#line 190 "MCBigoniFull.mfront"
const real KF=(this->KFm)*cos((this->betaF)*(this->pi)/6.-acos((this->gam)*C3T)/3.);
#line 191 "MCBigoniFull.mfront"
const real KG=(this->KGm)*cos((this->betaG)*(this->pi)/6.-acos((this->gam)*C3T)/3.);
#line 194 "MCBigoniFull.mfront"
const stress RF=sqrt(J2*KF*KF+(this->at)*(this->at)*sin((this->phir))*sin((this->phir)));
#line 195 "MCBigoniFull.mfront"
const stress F=RF+I1*sin((this->phir))/3.-(this->coh)*cos((this->phir));
#line 198 "MCBigoniFull.mfront"
const stress RG=sqrt(J2*KG*KG+(this->aG)*(this->aG)*sin((this->psir))*sin((this->psir)));
#line 200 "MCBigoniFull.mfront"
const real dC3T_dJ2=-2.25*sqrt(3.)*J3*pow(max(J2,(this->local_zero_tolerance)),-2.5);
#line 201 "MCBigoniFull.mfront"
const real dC3T_dJ3=1.5*sqrt(3.)*pow(max(J2,(this->local_zero_tolerance)),-1.5);
#line 203 "MCBigoniFull.mfront"
const real dKG_dC3T=-(this->KGm)*(this->gam)*sin((this->betaG)*(this->pi)/6.-acos((this->gam)*C3T)/3.)/3./max(sqrt(1.-(this->gam)*(this->gam)*C3T*C3T),(this->local_zero_tolerance));
#line 204 "MCBigoniFull.mfront"
const real dKG_dJ2=dKG_dC3T*dC3T_dJ2;
#line 205 "MCBigoniFull.mfront"
const real dKG_dJ3=dKG_dC3T*dC3T_dJ3;
#line 207 "MCBigoniFull.mfront"
const real dG_dI1=sin((this->psir))/3.;
#line 208 "MCBigoniFull.mfront"
const real dG_dJ2=.5*KG*(KG+2.*J2*dKG_dJ2)/max(RG,(this->local_zero_tolerance));
#line 209 "MCBigoniFull.mfront"
const stress dG_dJ3=J2*KG*dKG_dJ3/max(RG,(this->local_zero_tolerance));
#line 211 "MCBigoniFull.mfront"
const Stensor dI1_dsig=Stensor::Id();
#line 212 "MCBigoniFull.mfront"
const Stensor dJ2_dsig=sd;
#line 213 "MCBigoniFull.mfront"
const Stensor dJ3_dsig=computeJ3Derivative((this->sig));
#line 215 "MCBigoniFull.mfront"
const Stensor nG=(dG_dI1*dI1_dsig)+(dG_dJ2*dJ2_dsig)+(dG_dJ3*dJ3_dsig);
#line 216 "MCBigoniFull.mfront"
(this->nGtmp)=nG;
#line 219 "MCBigoniFull.mfront"
feel=(this->deel)-(this->deto)+(this->dlam)*nG;
#line 220 "MCBigoniFull.mfront"
flam=F/(this->young);
#line 228 "MCBigoniFull.mfront"
const real dC3T_ddJ2=5.625*sqrt(3.)*J3*pow(max(J2,(this->local_zero_tolerance)),-3.5);
#line 229 "MCBigoniFull.mfront"
const real dC3T_ddJ3=real(0);
#line 230 "MCBigoniFull.mfront"
const real dC3T_dJ3dJ2=-2.25*sqrt(3.)*pow(max(J2,(this->local_zero_tolerance)),-2.5);
#line 231 "MCBigoniFull.mfront"
const real dC3T_dJ2dJ3=dC3T_dJ3dJ2;
#line 233 "MCBigoniFull.mfront"
const real dKG_ddC3T_1=-(this->gam)*(this->gam)*(this->gam)*C3T*sin((this->betaG)*(this->pi)/6.-acos((this->gam)*C3T)/3.)/3./pow(max(1.-(this->gam)*(this->gam)*C3T*C3T,(this->local_zero_tolerance)),1.5);
#line 234 "MCBigoniFull.mfront"
const real dKG_ddC3T_2=-(this->gam)*(this->gam)*cos((this->betaG)*(this->pi)/6.-acos((this->gam)*C3T)/3.)/9./max(1.-(this->gam)*(this->gam)*C3T*C3T,(this->local_zero_tolerance));
#line 235 "MCBigoniFull.mfront"
const real dKG_ddC3T=(this->KGm)*(dKG_ddC3T_1+dKG_ddC3T_2);
#line 236 "MCBigoniFull.mfront"
const real dKG_dJ2dC3T=dKG_ddC3T*dC3T_dJ2;
#line 237 "MCBigoniFull.mfront"
const real dKG_ddJ2=dKG_dJ2dC3T*dC3T_dJ2+dKG_dC3T*dC3T_ddJ2;
#line 238 "MCBigoniFull.mfront"
const real dKG_ddJ3=dKG_ddC3T*dC3T_dJ3*dC3T_dJ3+dKG_dC3T*dC3T_ddJ3;
#line 239 "MCBigoniFull.mfront"
const real dKG_dJ3dJ2=dKG_ddC3T*dC3T_dJ3*dC3T_dJ2+dKG_dC3T*dC3T_dJ3dJ2;
#line 240 "MCBigoniFull.mfront"
const real dKG_dJ2dJ3=dKG_ddC3T*dC3T_dJ2*dC3T_dJ3+dKG_dC3T*dC3T_dJ2dJ3;
#line 242 "MCBigoniFull.mfront"
const real dG_ddJ2=((2.*KG+J2*dKG_dJ2)*dKG_dJ2+KG*J2*dKG_ddJ2-dG_dJ2*dG_dJ2)/max(RG,(this->local_zero_tolerance));
#line 243 "MCBigoniFull.mfront"
const real dG_ddJ3=(J2*(dKG_dJ3*dKG_dJ3+KG*dKG_ddJ3)-dG_dJ3*dG_dJ3)/max(RG,(this->local_zero_tolerance));
#line 244 "MCBigoniFull.mfront"
const real dG_dJ3dJ2=(KG*dKG_dJ3+J2*dKG_dJ2*dKG_dJ3+J2*KG*dKG_dJ3dJ2-dG_dJ2*dG_dJ3)/max(RG,(this->local_zero_tolerance));
#line 245 "MCBigoniFull.mfront"
const real dG_dJ2dJ3=(dKG_dJ3*(KG+J2*dKG_dJ2)+J2*KG*dKG_dJ2dJ3-dG_dJ2*dG_dJ3)/max(RG,(this->local_zero_tolerance));
#line 247 "MCBigoniFull.mfront"
const Stensor4 dJ2_ddsig=Stensor4::K();
#line 248 "MCBigoniFull.mfront"
const Stensor4 dJ3_ddsig=computeJ3SecondDerivative((this->sig));
#line 250 "MCBigoniFull.mfront"
const Stensor4 dnG_dsig=((dG_ddJ2*dJ2_dsig+dG_dJ3dJ2*dJ3_dsig)^dJ2_dsig)+(dG_dJ2*dJ2_ddsig)+((dG_dJ2dJ3*dJ2_dsig+dG_ddJ3*dJ3_dsig)^dJ3_dsig)+(dG_dJ3*dJ3_ddsig);
#line 252 "MCBigoniFull.mfront"
const real dKF_dC3T=-(this->KFm)*(this->gam)*sin((this->betaF)*(this->pi)/6.-acos((this->gam)*C3T)/3.)/3./max(sqrt(1.-(this->gam)*(this->gam)*C3T*C3T),(this->local_zero_tolerance));
#line 253 "MCBigoniFull.mfront"
const real dKF_dJ2=dKF_dC3T*dC3T_dJ2;
#line 254 "MCBigoniFull.mfront"
const real dKF_dJ3=dKF_dC3T*dC3T_dJ3;
#line 256 "MCBigoniFull.mfront"
const real dF_dI1=sin((this->phir))/3.;
#line 257 "MCBigoniFull.mfront"
const real dF_dJ2=.5*KF*(KF+2.*J2*dKF_dJ2)/max(RF,(this->local_zero_tolerance));
#line 258 "MCBigoniFull.mfront"
const stress dF_dJ3=J2*KF*dKF_dJ3/max(RF,(this->local_zero_tolerance));
#line 260 "MCBigoniFull.mfront"
const Stensor dF_dsig=(dF_dI1*dI1_dsig)+(dF_dJ2*dJ2_dsig)+(dF_dJ3*dJ3_dsig);
#line 263 "MCBigoniFull.mfront"
dfeel_ddeel=Stensor4::Id()+(this->dlam)*(dnG_dsig*(this->Ce));
#line 264 "MCBigoniFull.mfront"
dfeel_ddlam=nG;
#line 267 "MCBigoniFull.mfront"
dflam_ddeel=(dF_dsig|(this->Ce))/(this->young);
#line 268 "MCBigoniFull.mfront"
dflam_ddlam=real(0);
#line 272 "MCBigoniFull.mfront"
}
#line 275 "MCBigoniFull.mfront"
else {
#line 277 "MCBigoniFull.mfront"
feel=(this->deel)-(this->deto);
#line 278 "MCBigoniFull.mfront"
flam=(this->dlam);
#line 280 "MCBigoniFull.mfront"
}
static_cast<void>(dfeel_ddeel); /* suppress potential warnings */
static_cast<void>(dfeel_ddlam); /* suppress potential warnings */
static_cast<void>(dflam_ddeel); /* suppress potential warnings */
static_cast<void>(dflam_ddlam); /* suppress potential warnings */
return true;
}

std::pair<bool,real>
computeAPosterioriTimeStepScalingFactor(const real current_time_step_scaling_factor) const override{
const auto time_scaling_factor = this->computeAPosterioriTimeStepScalingFactorII();
return {time_scaling_factor.first,
        std::min(std::min(std::max(time_scaling_factor.second,
                                   this->minimal_time_step_scaling_factor),
                          this->maximal_time_step_scaling_factor),
                 current_time_step_scaling_factor)};
}

/*!
* \brief Update the internal energy at end of the time step
* \param[in] Psi_s: internal energy at end of the time step
*/
void computeInternalEnergy(real& Psi_s) const
{
Psi_s=0;
}

/*!
* \brief Update the dissipated energy at end of the time step
* \param[in] Psi_d: dissipated energy at end of the time step
*/
void computeDissipatedEnergy(real& Psi_d) const
{
Psi_d=0;
}

bool computeConsistentTangentOperator(const SMType smt){
using namespace std;
using namespace tfel::math;
using std::vector;
TinyPermutation<1+StensorSize> jacobian_permutation;
TinyMatrixSolve<1+StensorSize,real>::decomp(this->jacobian,jacobian_permutation);
struct TFEL_VISIBILITY_LOCAL GetPartialJacobianInvert{
GetPartialJacobianInvert(MCBigoniFull& b,
const tfel::math::TinyPermutation<1+StensorSize>& p)
: behaviour(b),
permutation(p)
{}
void operator()(tfel::math::derivative_type<StrainStensor, StrainStensor>& partial_jacobian_eel){
this->behaviour.computePartialJacobianInvert(this->permutation, partial_jacobian_eel);
}
void operator()(tfel::math::derivative_type<StrainStensor, StrainStensor>& partial_jacobian_eel,
tfel::math::derivative_type<real, StrainStensor>& partial_jacobian_lam){
this->behaviour.computePartialJacobianInvert(this->permutation, partial_jacobian_eel,
partial_jacobian_lam);
}
private:
MCBigoniFull& behaviour;
const tfel::math::TinyPermutation<1+StensorSize>& permutation;
}; // end of struct GetPartialJacobianInvert
GetPartialJacobianInvert getPartialJacobianInvert(*this, jacobian_permutation);
#line 310 "MCBigoniFull.mfront"
if((smt==ELASTIC)||(smt==SECANTOPERATOR)) {
#line 311 "MCBigoniFull.mfront"
computeElasticStiffness<N,Type>::exe((this->Dt),(this->lambda),(this->mu));
#line 312 "MCBigoniFull.mfront"
}
#line 313 "MCBigoniFull.mfront"
else if (smt==CONSISTENTTANGENTOPERATOR) {
#line 314 "MCBigoniFull.mfront"
Stensor4 Je;
#line 315 "MCBigoniFull.mfront"
getPartialJacobianInvert(Je);
#line 316 "MCBigoniFull.mfront"
(this->Dt)=(this->Ce)*Je;
#line 317 "MCBigoniFull.mfront"
}
#line 318 "MCBigoniFull.mfront"
else {
#line 319 "MCBigoniFull.mfront"
return false;
#line 320 "MCBigoniFull.mfront"
}
return true;
}

const TangentOperator& getTangentOperator() const{
return this->Dt;
}

void updateExternalStateVariables(){
this->eto  += this->deto;
this->T += this->dT;
}

//!
~MCBigoniFull()
 override = default;

private:

std::pair<bool,real> computeAPrioriTimeStepScalingFactorII() const{
return {true,this->maximal_time_step_scaling_factor};
}

std::pair<bool,real> computeAPosterioriTimeStepScalingFactorII() const{
return {true,this->maximal_time_step_scaling_factor};
}

//! policy for treating out of bounds conditions
OutOfBoundsPolicy policy = None;
}; // end of MCBigoniFull class

template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
operator <<(std::ostream& os,const MCBigoniFull<hypothesis,Type,false>& b)
{
os << "εᵗᵒ : " << b.eto << '\n';
os << "Δεᵗᵒ : " << b.deto << '\n';
os << "σ : " << b.sig << '\n';
os << "Δt : " << b.dt << '\n';
os << "young : " << b.young << '\n';
os << "nu : " << b.nu << '\n';
os << "phi : " << b.phi << '\n';
os << "psi : " << b.psi << '\n';
os << "coh : " << b.coh << '\n';
os << "at : " << b.at << '\n';
os << "gam : " << b.gam << '\n';
os << "εᵉˡ : " << b.eel << '\n';
os << "Δεᵉˡ : " << b.deel << '\n';
os << "lam : " << b.lam << '\n';
os << "Δlam : " << b.dlam << '\n';
os << "niter : " << b.niter << '\n';
os << "ip : " << b.ip << '\n';
os << "evp : " << b.evp << '\n';
os << "gap : " << b.gap << '\n';
os << "inst : " << b.inst << '\n';
os << "lode : " << b.lode << '\n';
os << "T : " << b.T << '\n';
os << "ΔT : " << b.dT << '\n';
os << "Ce : " << b.Ce << '\n';
os << "nGtmp : " << b.nGtmp << '\n';
os << "θ : " << b.theta << '\n';
os << "ε : " << b.epsilon << '\n';
os << "minimal_time_step_scaling_factor : " << b.minimal_time_step_scaling_factor << '\n';
os << "maximal_time_step_scaling_factor : " << b.maximal_time_step_scaling_factor << '\n';
os << "numerical_jacobian_epsilon : " << b.numerical_jacobian_epsilon << '\n';
os << "iterMax : " << b.iterMax << '\n';
return os;
}

/*!
* Partial specialisation for MCBigoniFull.
*/
template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
class MechanicalBehaviourTraits<MCBigoniFull<hypothesis,Type,false> >
{
static constexpr unsigned short N = ModellingHypothesisToSpaceDimension<hypothesis>::value;
static constexpr unsigned short TVectorSize = N;
typedef tfel::math::StensorDimeToSize<N> StensorDimeToSize;
static constexpr unsigned short StensorSize = StensorDimeToSize::value;
typedef tfel::math::TensorDimeToSize<N> TensorDimeToSize;
static constexpr unsigned short TensorSize = TensorDimeToSize::value;
public:
static constexpr bool is_defined = true;
static constexpr bool use_quantities = false;
static constexpr bool hasStressFreeExpansion = false;
static constexpr bool handlesThermalExpansion = false;
static constexpr unsigned short dimension = N;
typedef Type NumType;
static constexpr unsigned short material_properties_nb = 7;
static constexpr unsigned short internal_variables_nb  = 7+StensorSize;
static constexpr unsigned short external_variables_nb  = 1;
static constexpr unsigned short external_variables_nb2 = 0;
static constexpr bool hasConsistentTangentOperator = true;
static constexpr bool isConsistentTangentOperatorSymmetric = false;
static constexpr bool hasPredictionOperator = false;
static constexpr bool hasAPrioriTimeStepScalingFactor = false;
static constexpr bool hasComputeInternalEnergy = false;
static constexpr bool hasComputeDissipatedEnergy = false;
/*!
* \return the name of the class.
*/
static const char* getName(){
return "MCBigoniFull";
}

};

/*!
* Partial specialisation for MCBigoniFull.
*/
template<typename Type>
class MechanicalBehaviourTraits<MCBigoniFull<ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRESS,Type,false> >
{
public:
static constexpr bool is_defined = false;
static constexpr bool use_quantities = false;
static constexpr bool hasStressFreeExpansion = false;
static constexpr bool handlesThermalExpansion = false;
static constexpr unsigned short dimension = 0u;
typedef Type NumType;
static constexpr unsigned short material_properties_nb = 0;
static constexpr unsigned short internal_variables_nb  = 0;
static constexpr unsigned short external_variables_nb  = 0;
static constexpr unsigned short external_variables_nb2 = 0;
static constexpr bool hasConsistentTangentOperator = false;
static constexpr bool isConsistentTangentOperatorSymmetric = false;
static constexpr bool hasPredictionOperator = false;
static constexpr bool hasAPrioriTimeStepScalingFactor = false;
static constexpr bool hasComputeInternalEnergy = false;
static constexpr bool hasComputeDissipatedEnergy = false;
/*!
* \return the name of the class.
*/
static const char* getName(){
return "MCBigoniFull";
}

};

/*!
* Partial specialisation for MCBigoniFull.
*/
template<typename Type>
class MechanicalBehaviourTraits<MCBigoniFull<ModellingHypothesis::PLANESTRESS,Type,false> >
{
public:
static constexpr bool is_defined = false;
static constexpr bool use_quantities = false;
static constexpr bool hasStressFreeExpansion = false;
static constexpr bool handlesThermalExpansion = false;
static constexpr unsigned short dimension = 0u;
typedef Type NumType;
static constexpr unsigned short material_properties_nb = 0;
static constexpr unsigned short internal_variables_nb  = 0;
static constexpr unsigned short external_variables_nb  = 0;
static constexpr unsigned short external_variables_nb2 = 0;
static constexpr bool hasConsistentTangentOperator = false;
static constexpr bool isConsistentTangentOperatorSymmetric = false;
static constexpr bool hasPredictionOperator = false;
static constexpr bool hasAPrioriTimeStepScalingFactor = false;
static constexpr bool hasComputeInternalEnergy = false;
static constexpr bool hasComputeDissipatedEnergy = false;
/*!
* \return the name of the class.
*/
static const char* getName(){
return "MCBigoniFull";
}

};

} // end of namespace material

} // end of namespace tfel

#endif /* LIB_TFELMATERIAL_MCBIGONIFULL_HXX */
