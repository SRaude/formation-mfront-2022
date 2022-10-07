/*!
* \file   src/asterMCBigoniMini.cxx
* \brief  This file implements the aster interface for the MCBigoniMini behaviour law
* \author Simon Raude
* \date   07 / 10 / 2022
*/

#include<iostream>
#include<stdexcept>
#include"TFEL/Material/OutOfBoundsPolicy.hxx"
#include"TFEL/Material/MCBigoniMini.hxx"
#include"MFront/Aster/AsterStressFreeExpansionHandler.hxx"

#include"MFront/Aster/AsterInterface.hxx"

#include"MFront/Aster/asterMCBigoniMini.hxx"

static tfel::material::OutOfBoundsPolicy&
astermcbigonimini_getOutOfBoundsPolicy(){
using namespace tfel::material;
static OutOfBoundsPolicy policy = None;
return policy;
}

extern "C"{

MFRONT_SHAREDOBJ const char* 
astermcbigonimini_build_id = "";

MFRONT_SHAREDOBJ const char* 
astermcbigonimini_mfront_ept = "astermcbigonimini";

MFRONT_SHAREDOBJ const char* 
astermcbigonimini_tfel_version = "3.4.0";

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
astermcbigonimini_mfront_interface = "Aster";

MFRONT_SHAREDOBJ const char *
astermcbigonimini_src = "MCBigoniMini.mfront";

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_nModellingHypotheses = 4u;

MFRONT_SHAREDOBJ const char * 
astermcbigonimini_ModellingHypotheses[4u] = {"Axisymmetrical",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_nMainVariables = 1;
MFRONT_SHAREDOBJ unsigned short astermcbigonimini_nGradients = 1;

MFRONT_SHAREDOBJ int astermcbigonimini_GradientsTypes[1] = {1};
MFRONT_SHAREDOBJ const char * astermcbigonimini_Gradients[1] = {"Strain"};
MFRONT_SHAREDOBJ unsigned short astermcbigonimini_nThermodynamicForces = 1;

MFRONT_SHAREDOBJ int astermcbigonimini_ThermodynamicForcesTypes[1] = {1};
MFRONT_SHAREDOBJ const char * astermcbigonimini_ThermodynamicForces[1] = {"Stress"};
MFRONT_SHAREDOBJ unsigned short astermcbigonimini_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * astermcbigonimini_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short astermcbigonimini_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_BehaviourKinematic = 0u;

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_savesTangentOperator = 0;
MFRONT_SHAREDOBJ unsigned short astermcbigonimini_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_nMaterialProperties = 6u;

MFRONT_SHAREDOBJ const char *astermcbigonimini_MaterialProperties[6u] = {"YoungModulus",
"PoissonRatio",
"FrictionAngle",
"DilationAngle",
"Cohesion",
"TensionCutOff"};

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_nInternalStateVariables = 7;
MFRONT_SHAREDOBJ const char * astermcbigonimini_InternalStateVariables[7] = {"ElasticStrain",
"PlastMultiplier","LocalNewtonIter","PlasticIndex","PVolumStrain","EquiPlastStrain",
"Time"};
MFRONT_SHAREDOBJ int astermcbigonimini_InternalStateVariablesTypes [] = {1,0,0,0,0,0,0};

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * astermcbigonimini_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_nParameters = 6;
MFRONT_SHAREDOBJ const char * astermcbigonimini_Parameters[6] = {"theta",
"epsilon","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon","iterMax"};
MFRONT_SHAREDOBJ int astermcbigonimini_ParametersTypes [] = {0,0,0,0,0,2};

MFRONT_SHAREDOBJ double astermcbigonimini_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double astermcbigonimini_epsilon_ParameterDefaultValue = 1e-14;

MFRONT_SHAREDOBJ double astermcbigonimini_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double astermcbigonimini_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double astermcbigonimini_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-15;

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short astermcbigonimini_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short astermcbigonimini_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short astermcbigonimini_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ int
astermcbigonimini_setParameter(const char *const key,const double value){
using tfel::material::MCBigoniMiniParametersInitializer;
auto& i = MCBigoniMiniParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
astermcbigonimini_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::MCBigoniMiniParametersInitializer;
auto& i = MCBigoniMiniParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ void
astermcbigonimini_setOutOfBoundsPolicy(const int p){
if(p==0){
astermcbigonimini_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
astermcbigonimini_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
astermcbigonimini_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "astermcbigonimini_setOutOfBoundsPolicy: invalid argument\n";
}
}

char *astermcbigonimini_getIntegrationErrorMessage(){
#if (defined __GNUC__) && (!defined __clang__) && (!defined __INTEL_COMPILER) && (!defined __PGI)
#if __GNUC__ * 10000+__GNUC_MINOR__ * 100 <  40800
static __thread char msg[128];
#else
static thread_local char msg[128];
#endif
#else /* (defined __GNUC__) ...*/
static thread_local char msg[128];
#endif /* (defined __GNUC__) ...*/
return msg;
} // end of astermcbigonimini_getIntegrationErrorMessage

MFRONT_SHAREDOBJ void
MCBigoniMini(aster::AsterReal *const STRESS,aster::AsterReal *const STATEV,aster::AsterReal *const DDSOE,const aster::AsterReal *const STRAN,const aster::AsterReal *const DSTRAN,const aster::AsterReal *const DTIME,const aster::AsterReal *const TEMP,const aster::AsterReal *const DTEMP,const aster::AsterReal *const PREDEF,const aster::AsterReal *const DPRED,const aster::AsterInt  *const NTENS,const aster::AsterInt  *const NSTATV,const aster::AsterReal *const PROPS,const aster::AsterInt  *const NPROPS,const aster::AsterReal *const DROT,aster::AsterReal *const PNEWDT,const aster::AsterInt *const NUMMOD)
{
char * msg = astermcbigonimini_getIntegrationErrorMessage();
if(aster::AsterInterface<tfel::material::MCBigoniMini>::exe(msg,NTENS,DTIME,DROT,DDSOE,STRAN,DSTRAN,TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,STATEV,NSTATV,STRESS,NUMMOD,astermcbigonimini_getOutOfBoundsPolicy(),aster::AsterStandardSmallStrainStressFreeExpansionHandler)!=0){
*PNEWDT = -1.;
return;
}
}

MFRONT_SHAREDOBJ void
astermcbigonimini(aster::AsterReal *const STRESS,aster::AsterReal *const STATEV,aster::AsterReal *const DDSOE,const aster::AsterReal *const STRAN,const aster::AsterReal *const DSTRAN,const aster::AsterReal *const DTIME,const aster::AsterReal *const TEMP,const aster::AsterReal *const DTEMP,const aster::AsterReal *const PREDEF,const aster::AsterReal *const DPRED,const aster::AsterInt  *const NTENS,const aster::AsterInt  *const NSTATV,const aster::AsterReal *const PROPS,const aster::AsterInt  *const NPROPS,const aster::AsterReal *const DROT,aster::AsterReal *const PNEWDT,const aster::AsterInt *const NUMMOD)
{
MCBigoniMini(STRESS,STATEV,DDSOE,STRAN,DSTRAN,DTIME,TEMP,DTEMP,
PREDEF,DPRED,NTENS,NSTATV,PROPS,NPROPS,DROT,PNEWDT,NUMMOD);
}

} // end of extern "C"
