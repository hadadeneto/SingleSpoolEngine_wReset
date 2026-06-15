/*		HIL Code - PeripheralDyn.c
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % March, 2022
 * % *************************************************************************/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "../FADEC_Defines_H/Control_Types.h"
#include "../FADEC_Defines_H/Interpolation_Types.h"
#include "../FADEC_Defines_H/Env_SampTime.h"
#include "../FADEC_Functions_H/MtxIntFunctions.h"
#include "../FADEC_Defines_H/FaultSim_Types.h"
#include "../FADEC_Defines_H/SI_AU_Convert.h"
#include "../FADEC_Defines_H/constants_TMATS.h"
#include "../FADEC_Functions_H/functions_TMATS.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"

/* -------------------------------------------------- */
/* INCLUDE - T-MATS & PWLM                            */
/* (To be usedi in MATLAB and TMATS simulations only) */
/* -------------------------------------------------- */

//#include "mex.h"

/* -------------------------------------------------- */

/*******************************************************************************
 *
 *	FUNCTION:		FirstOrderSensor()
 *
 *	PURPOSE:		Updates status when a value of RPM larger than zero is detected
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		floating RPM,  struct ControlStart *ContStartP, digital_t *digitalP, int *status
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void FirstOrderSensor(floating RawVar, floating *SensedVar, floating FiltConst)
{

    /* Calculates sensor output */
    *SensedVar = *SensedVar + FiltConst * (RawVar - *SensedVar);
}

