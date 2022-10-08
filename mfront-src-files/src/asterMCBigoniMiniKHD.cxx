/*!
* \file   src/asterMCBigoniMiniKHD.cxx
* \brief  This file implements the aster interface for the MCBigoniMiniKHD behaviour law
* \author Simon Raude
* \date   08 / 10 / 2022
*/

#include<iostream>
#include<stdexcept>
#include"TFEL/Material/OutOfBoundsPolicy.hxx"
#include"TFEL/Material/MCBigoniMiniKHD.hxx"
#include"MFront/Aster/AsterStressFreeExpansionHandler.hxx"

#include"MFront/Aster/AsterInterface.hxx"

#include"MFront/Aster/asterMCBigoniMiniKHD.hxx"

static tfel::material::OutOfBoundsPolicy&
astermcbigoniminikhd_getOutOfBoundsPolicy(){
using namespace tfel::material;
static OutOfBoundsPolicy policy = None;
return policy;
}

extern "C"{

MFRONT_SHAREDOBJ const char* 
astermcbigoniminikhd_build_id = "";

MFRONT_SHAREDOBJ const char* 
astermcbigoniminikhd_mfront_ept = "astermcbigoniminikhd";

MFRONT_SHAREDOBJ const char* 
astermcbigoniminikhd_tfel_version = "3.4.0";

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
astermcbigoniminikhd_mfront_interface = "Aster";

MFRONT_SHAREDOBJ const char *
astermcbigoniminikhd_src = "MCBigoniMiniKHD.mfront";

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_nModellingHypotheses = 4u;

MFRONT_SHAREDOBJ const char * 
astermcbigoniminikhd_ModellingHypotheses[4u] = {"Axisymmetrical",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_nMainVariables = 1;
MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_nGradients = 1;

MFRONT_SHAREDOBJ int astermcbigoniminikhd_GradientsTypes[1] = {1};
MFRONT_SHAREDOBJ const char * astermcbigoniminikhd_Gradients[1] = {"Strain"};
MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_nThermodynamicForces = 1;

MFRONT_SHAREDOBJ int astermcbigoniminikhd_ThermodynamicForcesTypes[1] = {1};
MFRONT_SHAREDOBJ const char * astermcbigoniminikhd_ThermodynamicForces[1] = {"Stress"};
MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * astermcbigoniminikhd_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_BehaviourKinematic = 0u;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_savesTangentOperator = 0;
MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_nMaterialProperties = 9u;

MFRONT_SHAREDOBJ const char *astermcbigoniminikhd_MaterialProperties[9u] = {"YoungModulus",
"PoissonRatio",
"FrictionAngle",
"DilationAngle",
"Cohesion",
"TensionCutOff",
"DamageStrength",
"DExpoDamageFunc",
"QDamageFactor"};

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_nInternalStateVariables = 13;
MFRONT_SHAREDOBJ const char * astermcbigoniminikhd_InternalStateVariables[13] = {"ElasticStrain",
"PlasticStrain","PlastMultiplier","DamageVariable","LocalNewtonIter","PlasticIndex",
"PVolumStrain","EquiPlastStrain","Time","PDDomain","EquiPlastStress",
"MeanPlastStress","DamageStress"};
MFRONT_SHAREDOBJ int astermcbigoniminikhd_InternalStateVariablesTypes [] = {1,1,0,0,0,0,0,0,0,0,0,0,0};

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * astermcbigoniminikhd_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_nParameters = 6;
MFRONT_SHAREDOBJ const char * astermcbigoniminikhd_Parameters[6] = {"theta",
"epsilon","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon","iterMax"};
MFRONT_SHAREDOBJ int astermcbigoniminikhd_ParametersTypes [] = {0,0,0,0,0,2};

MFRONT_SHAREDOBJ double astermcbigoniminikhd_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double astermcbigoniminikhd_epsilon_ParameterDefaultValue = 1e-14;

MFRONT_SHAREDOBJ double astermcbigoniminikhd_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double astermcbigoniminikhd_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double astermcbigoniminikhd_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-15;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short astermcbigoniminikhd_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ int
astermcbigoniminikhd_setParameter(const char *const key,const double value){
using tfel::material::MCBigoniMiniKHDParametersInitializer;
auto& i = MCBigoniMiniKHDParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
astermcbigoniminikhd_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::MCBigoniMiniKHDParametersInitializer;
auto& i = MCBigoniMiniKHDParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ void
astermcbigoniminikhd_setOutOfBoundsPolicy(const int p){
if(p==0){
astermcbigoniminikhd_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
astermcbigoniminikhd_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
astermcbigoniminikhd_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "astermcbigoniminikhd_setOutOfBoundsPolicy: invalid argument\n";
}
}

char *astermcbigoniminikhd_getIntegrationErrorMessage(){
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
} // end of astermcbigoniminikhd_getIntegrationErrorMessage

MFRONT_SHAREDOBJ void
MCBigoniMiniKHD(aster::AsterReal *const STRESS,aster::AsterReal *const STATEV,aster::AsterReal *const DDSOE,const aster::AsterReal *const STRAN,const aster::AsterReal *const DSTRAN,const aster::AsterReal *const DTIME,const aster::AsterReal *const TEMP,const aster::AsterReal *const DTEMP,const aster::AsterReal *const PREDEF,const aster::AsterReal *const DPRED,const aster::AsterInt  *const NTENS,const aster::AsterInt  *const NSTATV,const aster::AsterReal *const PROPS,const aster::AsterInt  *const NPROPS,const aster::AsterReal *const DROT,aster::AsterReal *const PNEWDT,const aster::AsterInt *const NUMMOD)
{
char * msg = astermcbigoniminikhd_getIntegrationErrorMessage();
if(aster::AsterInterface<tfel::material::MCBigoniMiniKHD>::exe(msg,NTENS,DTIME,DROT,DDSOE,STRAN,DSTRAN,TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,STATEV,NSTATV,STRESS,NUMMOD,astermcbigoniminikhd_getOutOfBoundsPolicy(),aster::AsterStandardSmallStrainStressFreeExpansionHandler)!=0){
*PNEWDT = -1.;
return;
}
}

MFRONT_SHAREDOBJ void
astermcbigoniminikhd(aster::AsterReal *const STRESS,aster::AsterReal *const STATEV,aster::AsterReal *const DDSOE,const aster::AsterReal *const STRAN,const aster::AsterReal *const DSTRAN,const aster::AsterReal *const DTIME,const aster::AsterReal *const TEMP,const aster::AsterReal *const DTEMP,const aster::AsterReal *const PREDEF,const aster::AsterReal *const DPRED,const aster::AsterInt  *const NTENS,const aster::AsterInt  *const NSTATV,const aster::AsterReal *const PROPS,const aster::AsterInt  *const NPROPS,const aster::AsterReal *const DROT,aster::AsterReal *const PNEWDT,const aster::AsterInt *const NUMMOD)
{
MCBigoniMiniKHD(STRESS,STATEV,DDSOE,STRAN,DSTRAN,DTIME,TEMP,DTEMP,
PREDEF,DPRED,NTENS,NSTATV,PROPS,NPROPS,DROT,PNEWDT,NUMMOD);
}

} // end of extern "C"
