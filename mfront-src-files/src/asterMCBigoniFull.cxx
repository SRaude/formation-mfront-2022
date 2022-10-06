/*!
* \file   src/asterMCBigoniFull.cxx
* \brief  This file implements the aster interface for the MCBigoniFull behaviour law
* \author Simon Raude
* \date   15 / 09 / 2022
*/

#include<iostream>
#include<stdexcept>
#include"TFEL/Material/OutOfBoundsPolicy.hxx"
#include"TFEL/Material/MCBigoniFull.hxx"
#include"MFront/Aster/AsterStressFreeExpansionHandler.hxx"

#include"MFront/Aster/AsterInterface.hxx"

#include"MFront/Aster/asterMCBigoniFull.hxx"

static tfel::material::OutOfBoundsPolicy&
astermcbigonifull_getOutOfBoundsPolicy(){
using namespace tfel::material;
static OutOfBoundsPolicy policy = None;
return policy;
}

extern "C"{

MFRONT_SHAREDOBJ const char* 
astermcbigonifull_build_id = "";

MFRONT_SHAREDOBJ const char* 
astermcbigonifull_mfront_ept = "astermcbigonifull";

MFRONT_SHAREDOBJ const char* 
astermcbigonifull_tfel_version = "3.4.0";

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_mfront_mkt = 1u;

MFRONT_SHAREDOBJ const char *
astermcbigonifull_mfront_interface = "Aster";

MFRONT_SHAREDOBJ const char *
astermcbigonifull_src = "MCBigoniFull.mfront";

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_nModellingHypotheses = 4u;

MFRONT_SHAREDOBJ const char * 
astermcbigonifull_ModellingHypotheses[4u] = {"Axisymmetrical",
"PlaneStrain",
"GeneralisedPlaneStrain",
"Tridimensional"};

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_nMainVariables = 1;
MFRONT_SHAREDOBJ unsigned short astermcbigonifull_nGradients = 1;

MFRONT_SHAREDOBJ int astermcbigonifull_GradientsTypes[1] = {1};
MFRONT_SHAREDOBJ const char * astermcbigonifull_Gradients[1] = {"Strain"};
MFRONT_SHAREDOBJ unsigned short astermcbigonifull_nThermodynamicForces = 1;

MFRONT_SHAREDOBJ int astermcbigonifull_ThermodynamicForcesTypes[1] = {1};
MFRONT_SHAREDOBJ const char * astermcbigonifull_ThermodynamicForces[1] = {"Stress"};
MFRONT_SHAREDOBJ unsigned short astermcbigonifull_nTangentOperatorBlocks = 2;

MFRONT_SHAREDOBJ const char * astermcbigonifull_TangentOperatorBlocks[2] = {"Stress",
"Strain"};
MFRONT_SHAREDOBJ unsigned short astermcbigonifull_BehaviourType = 1u;

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_BehaviourKinematic = 0u;

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_SymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_ElasticSymmetryType = 0u;

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_savesTangentOperator = 0;
MFRONT_SHAREDOBJ unsigned short astermcbigonifull_UsableInPurelyImplicitResolution = 1;

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_nMaterialProperties = 7u;

MFRONT_SHAREDOBJ const char *astermcbigonifull_MaterialProperties[7u] = {"YoungModulus",
"PoissonRatio",
"FrictionAngle",
"DilationAngle",
"Cohesion",
"TensionCutOff",
"PiShapeCoef"};

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_nInternalStateVariables = 7;
MFRONT_SHAREDOBJ const char * astermcbigonifull_InternalStateVariables[7] = {"ElasticStrain",
"PlastMultiplier","LocalNewtonIter","PlasticIndex","PVolumStrain","Time",
"LodeAngle"};
MFRONT_SHAREDOBJ int astermcbigonifull_InternalStateVariablesTypes [] = {1,0,0,0,0,0,0};

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_nExternalStateVariables = 0;
MFRONT_SHAREDOBJ const char * const * astermcbigonifull_ExternalStateVariables = nullptr;

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_nParameters = 6;
MFRONT_SHAREDOBJ const char * astermcbigonifull_Parameters[6] = {"theta",
"epsilon","minimal_time_step_scaling_factor","maximal_time_step_scaling_factor","numerical_jacobian_epsilon","iterMax"};
MFRONT_SHAREDOBJ int astermcbigonifull_ParametersTypes [] = {0,0,0,0,0,2};

MFRONT_SHAREDOBJ double astermcbigonifull_theta_ParameterDefaultValue = 1;

MFRONT_SHAREDOBJ double astermcbigonifull_epsilon_ParameterDefaultValue = 1e-14;

MFRONT_SHAREDOBJ double astermcbigonifull_minimal_time_step_scaling_factor_ParameterDefaultValue = 0.1;

MFRONT_SHAREDOBJ double astermcbigonifull_maximal_time_step_scaling_factor_ParameterDefaultValue = 1.7976931348623e+308;

MFRONT_SHAREDOBJ double astermcbigonifull_numerical_jacobian_epsilon_ParameterDefaultValue = 1e-15;

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_iterMax_ParameterDefaultValue  = 100;

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_requiresStiffnessTensor = 0;
MFRONT_SHAREDOBJ unsigned short astermcbigonifull_requiresThermalExpansionCoefficientTensor = 0;
MFRONT_SHAREDOBJ unsigned short astermcbigonifull_ComputesInternalEnergy = 0;

MFRONT_SHAREDOBJ unsigned short astermcbigonifull_ComputesDissipatedEnergy = 0;

MFRONT_SHAREDOBJ int
astermcbigonifull_setParameter(const char *const key,const double value){
using tfel::material::MCBigoniFullParametersInitializer;
auto& i = MCBigoniFullParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ int
astermcbigonifull_setUnsignedShortParameter(const char *const key,const unsigned short value){
using tfel::material::MCBigoniFullParametersInitializer;
auto& i = MCBigoniFullParametersInitializer::get();
try{
i.set(key,value);
} catch(std::runtime_error& e){
std::cerr << e.what() << std::endl;
return 0;
}
return 1;
}

MFRONT_SHAREDOBJ void
astermcbigonifull_setOutOfBoundsPolicy(const int p){
if(p==0){
astermcbigonifull_getOutOfBoundsPolicy() = tfel::material::None;
} else if(p==1){
astermcbigonifull_getOutOfBoundsPolicy() = tfel::material::Warning;
} else if(p==2){
astermcbigonifull_getOutOfBoundsPolicy() = tfel::material::Strict;
} else {
std::cerr << "astermcbigonifull_setOutOfBoundsPolicy: invalid argument\n";
}
}

char *astermcbigonifull_getIntegrationErrorMessage(){
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
} // end of astermcbigonifull_getIntegrationErrorMessage

MFRONT_SHAREDOBJ void
MCBigoniFull(aster::AsterReal *const STRESS,aster::AsterReal *const STATEV,aster::AsterReal *const DDSOE,const aster::AsterReal *const STRAN,const aster::AsterReal *const DSTRAN,const aster::AsterReal *const DTIME,const aster::AsterReal *const TEMP,const aster::AsterReal *const DTEMP,const aster::AsterReal *const PREDEF,const aster::AsterReal *const DPRED,const aster::AsterInt  *const NTENS,const aster::AsterInt  *const NSTATV,const aster::AsterReal *const PROPS,const aster::AsterInt  *const NPROPS,const aster::AsterReal *const DROT,aster::AsterReal *const PNEWDT,const aster::AsterInt *const NUMMOD)
{
char * msg = astermcbigonifull_getIntegrationErrorMessage();
if(aster::AsterInterface<tfel::material::MCBigoniFull>::exe(msg,NTENS,DTIME,DROT,DDSOE,STRAN,DSTRAN,TEMP,DTEMP,PROPS,NPROPS,PREDEF,DPRED,STATEV,NSTATV,STRESS,NUMMOD,astermcbigonifull_getOutOfBoundsPolicy(),aster::AsterStandardSmallStrainStressFreeExpansionHandler)!=0){
*PNEWDT = -1.;
return;
}
}

MFRONT_SHAREDOBJ void
astermcbigonifull(aster::AsterReal *const STRESS,aster::AsterReal *const STATEV,aster::AsterReal *const DDSOE,const aster::AsterReal *const STRAN,const aster::AsterReal *const DSTRAN,const aster::AsterReal *const DTIME,const aster::AsterReal *const TEMP,const aster::AsterReal *const DTEMP,const aster::AsterReal *const PREDEF,const aster::AsterReal *const DPRED,const aster::AsterInt  *const NTENS,const aster::AsterInt  *const NSTATV,const aster::AsterReal *const PROPS,const aster::AsterInt  *const NPROPS,const aster::AsterReal *const DROT,aster::AsterReal *const PNEWDT,const aster::AsterInt *const NUMMOD)
{
MCBigoniFull(STRESS,STATEV,DDSOE,STRAN,DSTRAN,DTIME,TEMP,DTEMP,
PREDEF,DPRED,NTENS,NSTATV,PROPS,NPROPS,DROT,PNEWDT,NUMMOD);
}

} // end of extern "C"
