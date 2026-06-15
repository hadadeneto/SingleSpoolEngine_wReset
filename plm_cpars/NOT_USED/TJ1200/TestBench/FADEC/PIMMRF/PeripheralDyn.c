/*		HIL Code - PeripheralDyn.c 
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % March, 2022
 * % *************************************************************************/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "Control_Types.h"
#include "Interpolation_Types.h"
#include "Env_SampTime.h"
#include "MtxIntFunctions.h"
#include "FaultSim_Types.h"
#include "SI_AU_Convert.h"
#include "constants_TMATS.h"
#include "functions_TMATS.h"

/* -------------------------------------------------- */
/* INCLUDE - T-MATS & PWLM                            */
/* (To be usedi in MATLAB and TMATS simulations only) */
/* -------------------------------------------------- */

#include "mex.h"

/* -------------------------------------------------- */

/*******************************************************************************
 *
 *	FUNCTION:		FirstOrderSensor()
 *
 *	PURPOSE:		Updates status when a value of RPM larger than zero is detected
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		double RPM,  struct ControlStart *ContStartP, digital_t *digitalP, int *status
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void FirstOrderSensor(double RawVar, double *SensedVar, double FiltConst)
{

    /* Calculates sensor output */
    *SensedVar = *SensedVar + FiltConst * (RawVar - *SensedVar);
}

