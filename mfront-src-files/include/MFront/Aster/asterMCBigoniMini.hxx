/*!
* \file   include/MFront/Aster/asterMCBigoniMini.hxx
* \brief  This file declares the aster interface for the MCBigoniMini behaviour law
* \author Simon Raude
* \date   07 / 10 / 2022
*/

#ifndef LIB_ASTER_MCBIGONIMINI_HXX
#define LIB_ASTER_MCBIGONIMINI_HXX

#include"TFEL/Config/TFELConfig.hxx"

#include"MFront/Aster/Aster.hxx"

#ifdef __cplusplus
#include"MFront/Aster/AsterTraits.hxx"
#include"TFEL/Material/MCBigoniMini.hxx"
#endif /* __cplusplus */

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif /* NOMINMAX */
#include <windows.h>
#ifdef small
#undef small
#endif /* small */
#endif /* _WIN32 */

#ifndef MFRONT_SHAREDOBJ
#define MFRONT_SHAREDOBJ TFEL_VISIBILITY_EXPORT
#endif /* MFRONT_SHAREDOBJ */

#ifdef __cplusplus

namespace aster{

template<tfel::material::ModellingHypothesis::Hypothesis H,typename Type>
struct AsterTraits<tfel::material::MCBigoniMini<H,Type,false> >
{
//! behaviour type
static constexpr AsterBehaviourType btype = aster::STANDARDSTRAINBASEDBEHAVIOUR;
//! space dimension
static constexpr unsigned short N = tfel::material::ModellingHypothesisToSpaceDimension<H>::value;
// tiny vector size
static constexpr unsigned short TVectorSize = N;
// symmetric tensor size
static constexpr unsigned short StensorSize = tfel::math::StensorDimeToSize<N>::value;
// tensor size
static constexpr unsigned short TensorSize  = tfel::math::TensorDimeToSize<N>::value;
// size of the driving variable array
static constexpr unsigned short GradientSize = StensorSize;
// size of the thermodynamic force variable array (STRESS)
static constexpr unsigned short ThermodynamicForceVariableSize = StensorSize;
static constexpr AsterErrorReportPolicy errorReportPolicy = ASTER_NOERRORREPORT;
static constexpr bool requiresUnAlteredStiffnessTensor = false;
static constexpr bool requiresStiffnessTensor = false;
static constexpr bool requiresThermalExpansionCoefficientTensor = false;
static constexpr AsterSymmetryType type = aster::ISOTROPIC;
static constexpr AsterFiniteStrainFormulation afsf = aster::UNDEFINEDFINITESTRAINFORMULATION;
static constexpr unsigned short material_properties_nb = 6;
static constexpr AsterSymmetryType etype = aster::ISOTROPIC;
static constexpr unsigned short elasticPropertiesOffset = 0u;
static constexpr unsigned short thermalExpansionPropertiesOffset = 0u;
}; // end of class AsterTraits

} // end of namespace aster

#endif /* __cplusplus */

#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

MFRONT_SHAREDOBJ void
astermcbigonimini_setOutOfBoundsPolicy(const int);

MFRONT_SHAREDOBJ int
astermcbigonimini_setParameter(const char *const,const double);

MFRONT_SHAREDOBJ int
astermcbigonimini_setUnsignedShortParameter(const char *const,const unsigned short);

MFRONT_SHAREDOBJ char *astermcbigonimini_getIntegrationErrorMessage();

MFRONT_SHAREDOBJ void
MCBigoniMini(aster::AsterReal *const,aster::AsterReal *const,aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterInt  *const,const aster::AsterInt  *const,const aster::AsterReal *const,const aster::AsterInt  *const,const aster::AsterReal *const,aster::AsterReal *const,const aster::AsterInt  *const);

MFRONT_SHAREDOBJ void
astermcbigonimini(aster::AsterReal *const,aster::AsterReal *const,aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterReal *const,const aster::AsterInt  *const,const aster::AsterInt  *const,const aster::AsterReal *const,const aster::AsterInt  *const,const aster::AsterReal *const,aster::AsterReal *const,const aster::AsterInt  *const);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* LIB_ASTER_MCBIGONIMINI_HXX */
