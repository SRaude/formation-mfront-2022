/*!
* \file   TFEL/Material/MCBigoniMini.hxx
* \brief  this file implements the MCBigoniMini Behaviour.
*         File generated by tfel version 3.4.0
* \author Simon Raude
* \date   07 / 10 / 2022
 */

#ifndef LIB_TFELMATERIAL_MCBIGONIMINI_HXX
#define LIB_TFELMATERIAL_MCBIGONIMINI_HXX

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
#include"TFEL/Material/MCBigoniMiniBehaviourData.hxx"
#include"TFEL/Material/MCBigoniMiniIntegrationData.hxx"

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
#include"MFront/Aster/Aster.hxx"

namespace tfel{

namespace material{

struct MCBigoniMiniParametersInitializer
{
static MCBigoniMiniParametersInitializer&
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

MCBigoniMiniParametersInitializer();

MCBigoniMiniParametersInitializer(const MCBigoniMiniParametersInitializer&);

MCBigoniMiniParametersInitializer&
operator=(const MCBigoniMiniParametersInitializer&);
/*!
 * \brief read the parameters from the given file
 * \param[out] pi : parameters initializer
 * \param[in]  fn : file name
 */
static void readParameters(MCBigoniMiniParametersInitializer&,const char* const);
};

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis,typename Type,bool use_qt>
class MCBigoniMini;

//! \brief forward declaration
template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
 operator <<(std::ostream&,const MCBigoniMini<hypothesis,Type,false>&);

/*!
* \class MCBigoniMini
* \brief This class implements the MCBigoniMini behaviour.
* \param hypothesis, modelling hypothesis.
* \param Type, numerical type.
* \author Simon Raude
* \date   07 / 10 / 2022
*/
template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
class MCBigoniMini<hypothesis,Type,false> final
: public MechanicalBehaviour<MechanicalBehaviourBase::STANDARDSTRAINBASEDBEHAVIOUR,hypothesis,Type,false>,
public MCBigoniMiniBehaviourData<hypothesis,Type,false>,
public MCBigoniMiniIntegrationData<hypothesis,Type,false>
{

static constexpr unsigned short N = ModellingHypothesisToSpaceDimension<hypothesis>::value;

TFEL_STATIC_ASSERT(N==1||N==2||N==3);
TFEL_STATIC_ASSERT(tfel::typetraits::IsFundamentalNumericType<Type>::cond);
TFEL_STATIC_ASSERT(tfel::typetraits::IsReal<Type>::cond);

friend std::ostream& operator<< <>(std::ostream&,const MCBigoniMini&);

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

typedef MCBigoniMiniBehaviourData<hypothesis,Type,false> BehaviourData;
typedef MCBigoniMiniIntegrationData<hypothesis,Type,false> IntegrationData;
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
#line 74 "MCBigoniMini.mfront"
real& dlam;

#line 53 "MCBigoniMini.mfront"
bool b;
#line 54 "MCBigoniMini.mfront"
real local_zero_tolerance;
#line 55 "MCBigoniMini.mfront"
stress slocal_zero_tolerance;
#line 56 "MCBigoniMini.mfront"
real pi;
#line 57 "MCBigoniMini.mfront"
real phir;
#line 58 "MCBigoniMini.mfront"
real psir;
#line 59 "MCBigoniMini.mfront"
real thetaFm;
#line 60 "MCBigoniMini.mfront"
real thetaGm;
#line 61 "MCBigoniMini.mfront"
real KFm;
#line 62 "MCBigoniMini.mfront"
real KGm;
#line 63 "MCBigoniMini.mfront"
stress aG;
#line 64 "MCBigoniMini.mfront"
Stensor4 Ce;
#line 65 "MCBigoniMini.mfront"
stress lambda;
#line 66 "MCBigoniMini.mfront"
stress mu;
#line 67 "MCBigoniMini.mfront"
stress ks;
#line 68 "MCBigoniMini.mfront"
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
#line 148 "MCBigoniMini.mfront"
this->sig=this->lambda*trace((this->eel+(this->theta)*(this->deel)))*StrainStensor::Id()+2.*this->mu*(this->eel+(this->theta)*(this->deel));
} // end of MCBigoniMini::computeThermodynamicForces

void computeFinalThermodynamicForces(){
using namespace std;
using namespace tfel::math;
using std::vector;
#line 148 "MCBigoniMini.mfront"
this->sig=this->lambda*trace(this->eel)*StrainStensor::Id()+2.*this->mu*this->eel;
} // end of MCBigoniMini::computeFinalThermodynamicForces

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
#line 219 "MCBigoniMini.mfront"
this->inst+=this->dt;
#line 220 "MCBigoniMini.mfront"
this->niter=iter;
#line 221 "MCBigoniMini.mfront"
if (this->dlam>0) {
#line 222 "MCBigoniMini.mfront"
this->ip=1;
#line 223 "MCBigoniMini.mfront"
this->evp+=this->dlam*sin(this->psir);
#line 224 "MCBigoniMini.mfront"
this->gap+=this->dlam*sqrt(2.*deviator(this->nGtmp)|deviator(this->nGtmp)/3.);
#line 225 "MCBigoniMini.mfront"
} else {
#line 226 "MCBigoniMini.mfront"
this->ip=0;
#line 227 "MCBigoniMini.mfront"
}
}

//! \brief Default constructor (disabled)
MCBigoniMini() =delete ;
//! \brief Copy constructor (disabled)
MCBigoniMini(const MCBigoniMini&) = delete;
//! \brief Assignement operator (disabled)
MCBigoniMini& operator = (const MCBigoniMini&) = delete;

public:

/*!
* \brief Constructor
*/
MCBigoniMini(const MCBigoniMiniBehaviourData<hypothesis,Type,false>& src1,
const MCBigoniMiniIntegrationData<hypothesis,Type,false>& src2)
: MCBigoniMiniBehaviourData<hypothesis,Type,false>(src1),
MCBigoniMiniIntegrationData<hypothesis,Type,false>(src2),
deel(this->zeros),
dlam(this->zeros(StensorSize)),
dsig_ddeto(Dt),
zeros(real(0)),
fzeros(real(0))
{
using namespace std;
using namespace tfel::math;
using std::vector;
this->theta = MCBigoniMiniParametersInitializer::get().theta;
this->epsilon = MCBigoniMiniParametersInitializer::get().epsilon;
this->minimal_time_step_scaling_factor = MCBigoniMiniParametersInitializer::get().minimal_time_step_scaling_factor;
this->maximal_time_step_scaling_factor = MCBigoniMiniParametersInitializer::get().maximal_time_step_scaling_factor;
this->numerical_jacobian_epsilon = MCBigoniMiniParametersInitializer::get().numerical_jacobian_epsilon;
this->iterMax = MCBigoniMiniParametersInitializer::get().iterMax;
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
MCBigoniMini(const Type* const ASTERdt_,
const Type* const ASTERT_,
const Type* const ASTERdT_,
const Type* const ASTERmat,
const Type* const ASTERint_vars,
const Type* const ASTERext_vars,
const Type* const ASTERdext_vars)
: MCBigoniMiniBehaviourData<hypothesis,Type,false>(ASTERT_,ASTERmat,
ASTERint_vars,ASTERext_vars),
MCBigoniMiniIntegrationData<hypothesis,Type,false>(ASTERdt_,ASTERdT_,ASTERdext_vars),
deel(this->zeros),
dlam(this->zeros(StensorSize)),
dsig_ddeto(Dt),
zeros(real(0)),
fzeros(real(0))
{
using namespace std;
using namespace tfel::math;
using std::vector;
this->theta = MCBigoniMiniParametersInitializer::get().theta;
this->epsilon = MCBigoniMiniParametersInitializer::get().epsilon;
this->minimal_time_step_scaling_factor = MCBigoniMiniParametersInitializer::get().minimal_time_step_scaling_factor;
this->maximal_time_step_scaling_factor = MCBigoniMiniParametersInitializer::get().maximal_time_step_scaling_factor;
this->numerical_jacobian_epsilon = MCBigoniMiniParametersInitializer::get().numerical_jacobian_epsilon;
this->iterMax = MCBigoniMiniParametersInitializer::get().iterMax;
}

/*!
 * \ brief initialize the behaviour with user code
 */
void initialize(){
using namespace std;
using namespace tfel::math;
using std::vector;
#line 98 "MCBigoniMini.mfront"
this->local_zero_tolerance=real(1e-12);
#line 99 "MCBigoniMini.mfront"
this->slocal_zero_tolerance=this->young*this->local_zero_tolerance;
#line 101 "MCBigoniMini.mfront"
this->pi=4.*atan(1.);
#line 102 "MCBigoniMini.mfront"
this->phir=this->phi*this->pi/180.;
#line 103 "MCBigoniMini.mfront"
this->psir=this->psi*this->pi/180.;
#line 105 "MCBigoniMini.mfront"
this->thetaFm=atan(-sin(this->phir)/sqrt(3.));
#line 106 "MCBigoniMini.mfront"
this->thetaGm=atan(-sin(this->psir)/sqrt(3.));
#line 107 "MCBigoniMini.mfront"
this->KFm=(cos(this->thetaFm)-sin(this->phir)*sin(this->thetaFm)/sqrt(3.));
#line 108 "MCBigoniMini.mfront"
this->KGm=(cos(this->thetaGm)-sin(this->psir)*sin(this->thetaGm)/sqrt(3.));
#line 110 "MCBigoniMini.mfront"
this->aG=this->at*tan(this->phir)/tan(this->psir);
#line 112 "MCBigoniMini.mfront"
this->lambda=computeLambda(this->young,this->nu);
#line 113 "MCBigoniMini.mfront"
this->mu=computeMu(this->young,this->nu);
#line 114 "MCBigoniMini.mfront"
this->ks=this->lambda+2.*this->mu/3.;
#line 115 "MCBigoniMini.mfront"
this->Ce=3.*this->ks*Stensor4::J()+2.*this->mu*Stensor4::K();
#line 117 "MCBigoniMini.mfront"
if (this->inst==real(0) && this->lam==real(0)) {
#line 118 "MCBigoniMini.mfront"
const Stensor4 Se=invert(this->Ce);
#line 119 "MCBigoniMini.mfront"
this->eel=(Se*this->sig);
#line 120 "MCBigoniMini.mfront"
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
tfel::raise("MCBigoniMini::computePredictionOperator: "
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
#line 130 "MCBigoniMini.mfront"
StressStensor sigel(this->lambda*trace(this->eel+this->deto)*Stensor::Id()+2.*this->mu*(this->eel+this->deto));
#line 133 "MCBigoniMini.mfront"
const StressStensor sdel=deviator(sigel);
#line 134 "MCBigoniMini.mfront"
const real J2el=.5*(sdel|sdel);
#line 135 "MCBigoniMini.mfront"
const stress I1el=trace(sigel);
#line 138 "MCBigoniMini.mfront"
const stress RFel=sqrt(J2el*this->KFm*this->KFm+this->at*this->at*sin(this->phir)*sin(this->phir));
#line 139 "MCBigoniMini.mfront"
this->b=RFel+I1el*sin(this->phir)/3.-this->coh*cos(this->phir)>real(0);
auto error = real{};
bool converged=false;
this->iter=0;
while((converged==false)&&
(this->iter<MCBigoniMini::iterMax)){
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
} // end of MCBigoniMini::integrate

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
#line 158 "MCBigoniMini.mfront"
if ((this->b)){
#line 161 "MCBigoniMini.mfront"
const StressStensor sd=deviator((this->sig));
#line 162 "MCBigoniMini.mfront"
const real J2=.5*(sd|sd);
#line 163 "MCBigoniMini.mfront"
const stress I1=trace((this->sig));
#line 166 "MCBigoniMini.mfront"
const stress RF=sqrt(J2*(this->KFm)*(this->KFm)+(this->at)*(this->at)*sin((this->phir))*sin((this->phir)));
#line 167 "MCBigoniMini.mfront"
const stress RG=sqrt(J2*(this->KGm)*(this->KGm)+(this->aG)*(this->aG)*sin((this->psir))*sin((this->psir)));
#line 168 "MCBigoniMini.mfront"
const stress F=RF+I1*sin((this->phir))/3.-(this->coh)*cos((this->phir));
#line 171 "MCBigoniMini.mfront"
const real dG_dI1=sin((this->psir))/3.;
#line 172 "MCBigoniMini.mfront"
const real dG_dJ2=.5*(this->KGm)*(this->KGm)/max(RG,(this->slocal_zero_tolerance));
#line 173 "MCBigoniMini.mfront"
const Stensor nG=dG_dI1*Stensor::Id()+dG_dJ2*sd;
#line 174 "MCBigoniMini.mfront"
(this->nGtmp)=nG;
#line 177 "MCBigoniMini.mfront"
feel=(this->deel)-(this->deto)+(this->dlam)*nG;
#line 178 "MCBigoniMini.mfront"
flam=F/(this->young);
#line 186 "MCBigoniMini.mfront"
const real dG_ddJ2=-.5*(this->KGm)*(this->KGm)*dG_dJ2/max(RG,(this->local_zero_tolerance))/max(RG,(this->slocal_zero_tolerance));
#line 187 "MCBigoniMini.mfront"
const Stensor4 dnG_dsig=dG_ddJ2*(sd^sd)+dG_dJ2*Stensor4::K();
#line 189 "MCBigoniMini.mfront"
const real dF_dI1=sin((this->phir))/3.;
#line 190 "MCBigoniMini.mfront"
const real dF_dJ2=.5*(this->KFm)*(this->KFm)/max(RF,(this->slocal_zero_tolerance));
#line 191 "MCBigoniMini.mfront"
const Stensor dF_dsig=dF_dI1*Stensor::Id()+dF_dJ2*sd;
#line 194 "MCBigoniMini.mfront"
dfeel_ddeel=Stensor4::Id()+(this->dlam)*(dnG_dsig*(this->Ce));
#line 195 "MCBigoniMini.mfront"
dfeel_ddlam=nG;
#line 198 "MCBigoniMini.mfront"
dflam_ddeel=(dF_dsig|(this->Ce))/(this->young);
#line 199 "MCBigoniMini.mfront"
dflam_ddlam=real(0);
#line 203 "MCBigoniMini.mfront"
}
#line 206 "MCBigoniMini.mfront"
else {
#line 208 "MCBigoniMini.mfront"
feel=(this->deel)-(this->deto);
#line 209 "MCBigoniMini.mfront"
flam=(this->dlam);
#line 211 "MCBigoniMini.mfront"
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
GetPartialJacobianInvert(MCBigoniMini& b,
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
MCBigoniMini& behaviour;
const tfel::math::TinyPermutation<1+StensorSize>& permutation;
}; // end of struct GetPartialJacobianInvert
GetPartialJacobianInvert getPartialJacobianInvert(*this, jacobian_permutation);
#line 236 "MCBigoniMini.mfront"
if((smt==ELASTIC)||(smt==SECANTOPERATOR)) {
#line 237 "MCBigoniMini.mfront"
computeElasticStiffness<N,Type>::exe((this->Dt),(this->lambda),(this->mu));
#line 238 "MCBigoniMini.mfront"
}
#line 239 "MCBigoniMini.mfront"
else if (smt==CONSISTENTTANGENTOPERATOR) {
#line 240 "MCBigoniMini.mfront"
Stensor4 Je;
#line 241 "MCBigoniMini.mfront"
getPartialJacobianInvert(Je);
#line 242 "MCBigoniMini.mfront"
(this->Dt)=(this->Ce)*Je;
#line 243 "MCBigoniMini.mfront"
}
#line 244 "MCBigoniMini.mfront"
else {
#line 245 "MCBigoniMini.mfront"
return false;
#line 246 "MCBigoniMini.mfront"
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
~MCBigoniMini()
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
}; // end of MCBigoniMini class

template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
std::ostream&
operator <<(std::ostream& os,const MCBigoniMini<hypothesis,Type,false>& b)
{
os << "???????? : " << b.eto << '\n';
os << "?????????? : " << b.deto << '\n';
os << "?? : " << b.sig << '\n';
os << "??t : " << b.dt << '\n';
os << "young : " << b.young << '\n';
os << "nu : " << b.nu << '\n';
os << "phi : " << b.phi << '\n';
os << "psi : " << b.psi << '\n';
os << "coh : " << b.coh << '\n';
os << "at : " << b.at << '\n';
os << "??????? : " << b.eel << '\n';
os << "????????? : " << b.deel << '\n';
os << "lam : " << b.lam << '\n';
os << "??lam : " << b.dlam << '\n';
os << "niter : " << b.niter << '\n';
os << "ip : " << b.ip << '\n';
os << "evp : " << b.evp << '\n';
os << "gap : " << b.gap << '\n';
os << "inst : " << b.inst << '\n';
os << "T : " << b.T << '\n';
os << "??T : " << b.dT << '\n';
os << "Ce : " << b.Ce << '\n';
os << "nGtmp : " << b.nGtmp << '\n';
os << "?? : " << b.theta << '\n';
os << "?? : " << b.epsilon << '\n';
os << "minimal_time_step_scaling_factor : " << b.minimal_time_step_scaling_factor << '\n';
os << "maximal_time_step_scaling_factor : " << b.maximal_time_step_scaling_factor << '\n';
os << "numerical_jacobian_epsilon : " << b.numerical_jacobian_epsilon << '\n';
os << "iterMax : " << b.iterMax << '\n';
return os;
}

/*!
* Partial specialisation for MCBigoniMini.
*/
template<ModellingHypothesis::Hypothesis hypothesis,typename Type>
class MechanicalBehaviourTraits<MCBigoniMini<hypothesis,Type,false> >
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
static constexpr unsigned short material_properties_nb = 6;
static constexpr unsigned short internal_variables_nb  = 6+StensorSize;
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
return "MCBigoniMini";
}

};

/*!
* Partial specialisation for MCBigoniMini.
*/
template<typename Type>
class MechanicalBehaviourTraits<MCBigoniMini<ModellingHypothesis::AXISYMMETRICALGENERALISEDPLANESTRESS,Type,false> >
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
return "MCBigoniMini";
}

};

/*!
* Partial specialisation for MCBigoniMini.
*/
template<typename Type>
class MechanicalBehaviourTraits<MCBigoniMini<ModellingHypothesis::PLANESTRESS,Type,false> >
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
return "MCBigoniMini";
}

};

} // end of namespace material

} // end of namespace tfel

#endif /* LIB_TFELMATERIAL_MCBIGONIMINI_HXX */
