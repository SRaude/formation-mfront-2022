/*!
* \file   src/asterMCBigoniMiniIH.cxx
* \brief  This file implements the aster interface for the MCBigoniMiniIH behaviour law
* \author Simon Raude
* \date   07 / 10 / 2022
*/

#include<iostream>
#include<stdexcept>
#include"TFEL/Material/OutOfBoundsPolicy.hxx"
#include"TFEL/Material/MCBigoniMiniIH.hxx"
#include"MFront/Aster/AsterStressFreeExpansionHandler.hxx"

#include"MFront/Aster/AsterInterface.hxx"

#include"MFront/Aster/asterMCBigoniMiniIH.hxx"

static tfel::material::OutOfBoundsPolicy&
astermcbigoniminiih_getOutOfBoundsPolicy(){
using namespace tfel::material;
static OutOfBoundsPolicy policy = None;
return policy;
}

extern "C"{

MFRONT_SHAREDOBJ const char* 
astermcbigoniminiih_build_id = "";

MFRONT_SHAREDOBJ const char* 
astermcbigoniminiih_mfront_ept = "astermcbigoniminiih";

MFRONT_SHAREDOBJ const char* 
astermcbigoniminiih_tfel_version = "3.4.0";

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
astermcbigoniminiih_mfront_interface = "Aster";

MFRONT_SHAREDOBJ const char *
astermcbigoniminiih_src = "MCBigoniMiniIH.mfront";

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_nModellingHypotheses = 4u;

MFRONT_SHAREDOBJ const char * 
astermcbigoniminiih_ModellingHypotheses[4u] = {"Axisymmetrical",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_nMainVariables = 1;
MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_nGradients = 1;

MFRONT_SHAREDOBJ int astermcbigoniminiih_GradientsTypes[1] = {1};
MFRONT_SHAREDOBJ const char * astermcbigoniminiih_Gradients[1] = {"Strain"};
MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_nThermodynamicForces = 1;

MFRONT_SHAREDOBJ int astermcbigoniminiih_ThermodynamicForcesTypes[1] = {1};
MFRONT_SHAREDOBJ const char * astermcbigoniminiih_ThermodynamicForces[1] = {"Stress"};
MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * astermcbigoniminiih_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_BehaviourKinematic = 0u;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_savesTangentOperator = 0;
MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_nMaterialProperties = 7u;

MFRONT_SHAREDOBJ const char *astermcbigoniminiih_MaterialProperties[7u] = {"YoungModulus",
"PoissonRatio",
"FrictionAngle",
"DilationAngle",
"Cohesion",
"TensionCutOff",
"HardeningCoef"};

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_nInternalStateVariables = 7;
MFRONT_SHAREDOBJ const char * astermcbigoniminiih_InternalStateVariables[7] = {"ElasticStrain",
"PlastMultiplier","EquiPlastStrain","LocalNewtonIter","PlasticIndex","PVolumStrain",
"Time"};
MFRONT_SHAREDOBJ int astermcbigoniminiih_InternalStateVariablesTypes [] = {1,0,0,0,0,0,0};

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * astermcbigoniminiih_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_nParameters = 6;
MFRONT_SHAREDOBJ const char * astermcbigoniminiih_Parameters[6] = {"theta",
"epsilon","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon","iterMax"};
MFRONT_SHAREDOBJ int astermcbigoniminiih_ParametersTypes [] = {0,0,0,0,0,2};

MFRONT_SHAREDOBJ double astermcbigoniminiih_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double astermcbigoniminiih_epsilon_ParameterDefaultValue = 1e-14;

MFRONT_SHAREDOBJ double astermcbigoniminiih_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double astermcbigoniminiih_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double astermcbigoniminiih_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-15;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminiih_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ int
astermcbigoniminiih_setParameter(const char *const key,const double value){
using tfel::material::MCBigoniMiniIHParametersInitializer;
auto& i = MCBigoniMiniIHParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
astermcbigoniminiih_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::MCBigoniMiniIHParametersInitializer;
auto& i = MCBigoniMiniIHParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ void
astermcbigoniminiih_setOutOfBoundsPolicy(const int p){
if(p==0){
astermcbigoniminiih_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
astermcbigoniminiih_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
astermcbigoniminiih_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "astermcbigoniminiih_setOutOfBoundsPolicy: invalid argument\n";
}
}

char *astermcbigoniminiih_getIntegrationErrorMessage(){
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
} // end of astermcbigoniminiih_getIntegrationErrorMessage

MFRONT_SHAREDOBJ void
MCBigoniMiniIH(aster::AsterReal *const STRESS,aster::AsterReal *const STATEV,aster::AsterReal *const DDSOE,const aster::AsterReal *const STRAN,const aster::AsterReal *const DSTRAN,const aster::AsterReal *const DTIME,const aster::AsterReal *const TEMP,const aster::AsterReal *const DTEMP,const aster::AsterReal *const PREDEF,const aster::AsterReal *const DPRED,const aster::AsterInt  *const NTENS,const aster::AsterInt  *const NSTATV,const aster::AsterReal *const PROPS,const aster::AsterInt  *const NPROPS,const aster::AsterReal *const DROT,aster::AsterReal *const PNEWDT,const aster::AsterInt *const NUMMOD)
{
char * msg = astermcbigoniminiih_getIntegrationErrorMessage();
if(aster::AsterInterface<tfel::material::MCBigoniMiniIH>::exe(msg,NTENS,DTIME,DROT,DDSOE,STRAN,DSTRAN,TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,STATEV,NSTATV,STRESS,NUMMOD,astermcbigoniminiih_getOutOfBoundsPolicy(),aster::AsterStandardSmallStrainStressFreeExpansionHandler)!=0){
*PNEWDT = -1.;
return;
}
}

MFRONT_SHAREDOBJ void
astermcbigoniminiih(aster::AsterReal *const STRESS,aster::AsterReal *const STATEV,aster::AsterReal *const DDSOE,const aster::AsterReal *const STRAN,const aster::AsterReal *const DSTRAN,const aster::AsterReal *const DTIME,const aster::AsterReal *const TEMP,const aster::AsterReal *const DTEMP,const aster::AsterReal *const PREDEF,const aster::AsterReal *const DPRED,const aster::AsterInt  *const NTENS,const aster::AsterInt  *const NSTATV,const aster::AsterReal *const PROPS,const aster::AsterInt  *const NPROPS,const aster::AsterReal *const DROT,aster::AsterReal *const PNEWDT,const aster::AsterInt *const NUMMOD)
{
MCBigoniMiniIH(STRESS,STATEV,DDSOE,STRAN,DSTRAN,DTIME,TEMP,DTEMP,
PREDEF,DPRED,NTENS,NSTATV,PROPS,NPROPS,DROT,PNEWDT,NUMMOD);
}

} // end of extern "C"
