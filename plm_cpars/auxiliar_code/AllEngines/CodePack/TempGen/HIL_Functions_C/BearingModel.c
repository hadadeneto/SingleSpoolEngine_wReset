
/*
 * PIMinMaxTJ200.c - HIL File
 *
 *  Created on: Dec 11, 2019
 *      Author: Antonio Hadade Neto
 */


/********* parte que eu estou adicionando para enviar a string via serial *************/
#include <stdio.h>	//standard input/output functions
#include <stdlib.h>
#include <string.h>	//string function definitions

/*The file below, unistd.h, is NOT SUPPORTED IN MATLAB and should be
  commented for successful compilation in MATLAB simulation
  The file MUST BE USED IN HARDWARE
 */
//#include <unistd.h>	//UNIX standard function definitions

#include <fcntl.h>	//File control definitions
#include <errno.h>	//Error number definitions

/*The file below, unistd.h, is NOT SUPPORTED IN MATLAB and should be
  commented for successful compilation in MATLAB simulation
  The file MUST BE USED IN HARDWARE
 */
//#include <termios.h>	//POSIX terminal control definitions
/**************************************************************************************/

/* -------------------------------------------------- */
/* INCLUDE - T-MATS & PWLM                            */
/* (To be usedi in MATLAB and TMATS simulations only) */
/* -------------------------------------------------- */

//#include "mex.h"

/* -------------------------------------------------- */

#include <math.h>

#include "../FADEC_Defines_H/Env_SampTime.h"
#include "../FADEC_Functions_H/MtxIntFunctions.h"
#include "../FADEC_Defines_H/Interpolation_Types.h"
#include "../FADEC_Defines_H/Control_Types.h"
#include "../FADEC_Functions_H/ControlFunctions.h"
#include "../FADEC_Defines_H/Model_Types.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"


void BearingModel(struct BearingPars *BearModP, floating *RPMEVecP, floating *TNOilP, floating *TMaxRPMP)
{

	/* Structure for finding values */
	InterpIndex Indexes;
	/* Calculates position of engine rotation speed inside breakpoints vector */
	//IndFind(Engine RPM, Num of Elems in Engine RPM Vector, Engine RPM Vector, Pointer for indexes)
 	IndFind(BearModP->RPME, BearModP->ElNumRPME, RPMEVecP, &Indexes);

 	/* Reads the value of the Acceleration Schedule corrected rotation reference */
 	int k = Indexes.K;
 	floating f = Indexes.f;

	/* If f < 0, f is set to 0 */
	f = Max(f,0);
	/* Calculates the bearing temperature if no oil is applied at given engine RPM */
	floating TNOil = *(TNOilP + k) + f*(*(TNOilP + k + 1) - *(TNOilP + k));
	/* Calculates the bearing temperature reduction if maximum oil flow is applied at given engine RPM */
	floating DelTMax = *(TMaxRPMP + k) + f*(*(TMaxRPMP + k + 1) - *(TMaxRPMP + k));

	/*----------------------------*/
	/* STARTTING OF CONTROL LOGIC */
	/*----------------------------*/

	/* Calculation of discrete coefficients */
    floating Ad = exp(BearModP->A * BearModP->Ts);
    floating Bd = (Ad - 1) * BearModP->B / BearModP->A;
	/* Calculation of plant input */
	floating Input = BearModP->RPMP *  DelTMax / BearModP->MaxRPMP;
	/* Calculation of bearing temperature from dynamic equation */
	BearModP->T = BearModP->Tss + Ad * (BearModP->T - BearModP->Tss) + Bd * (Input - BearModP->RPMPss);
	/* Adds TNOil and additional external temperature increase to bearing temperature*/
	BearModP->Tout = BearModP->Tss + BearModP->C * (BearModP->T - BearModP->Tss) + TNOil + BearModP->DelTExt;

}
