
/*
 * PIOil.c - FADEC and HIL File
 *
 *  Created on: July 14, 2022
 *      Author: Antonio Hadade Neto
 */


/* LINUX INCLUDES */

/* INCLUDES FOR SENDING STRINGS THROUGH SERIAL COMMUNICATION */

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

/* -------------------------------------------------- */
/* INCLUDE - T-MATS & PWLM                            */
/* (To be usedi in MATLAB and TMATS simulations only) */
/* -------------------------------------------------- */

//#include "mex.h"

/* -------------------------------------------------- */

#include <math.h>

/* CONTROLLER INCLUDES */

#include "Control_Types.h"
#include "ControlFunctions.h"

/* MAIN FUNCTION */

void PIOil(struct ControllerGeneral *ContGenP)
{
    
	/*--------------------------*/
	/* DECLARATION OF VARIABLES */
	/*--------------------------*/

	/* CLOSED-LOOP ROUTINE VARIABLES */

	/* Errors and control signals */
	double ek[5];
	//double eTt4k;
	double uk[5];
	double uTt4k[5];
	double uMMk[5];
	double uRUk[5];

	/* Previous samples of errors and control signals */
	double uk1[5];
	double urk1[5];
	double ITermk1[5];
	double ek1[5];
	double eBk1[5];

	/* Active controller flag */
	int Active;

	/* Controller Gains */
	double Ki[5];
	double Kp[5];
	double Kb[5];

	/* References and input variables */
	double Ref[5];
	double Input[5];

	/* Structures for PI outputs */
	PIOutput PIOut;
	/* Output signal */
	double uOut;

	/* Controller parameters */
	double KiPI, KpPI, KbPI, TsPI, ITermk1PI, ekPI, ek1PI, eBk1PI;
	double proportional, integral, eIk1;

	/*---------------*/
	/* INPUT READING */
	/*---------------*/

	/* Defines the number of bearings to be cooled - Maximum of 5 */
	int NumBearings = ContGenP->NumContVar;

	/* READS CONTROLLER INPUT DATA */

	/* Each data corresponds to a different bearing */
	for (int i = 0; i < NumBearings; i++)
	{
		/* Previous samples of errors and control signals */
		uk1[i] = ContGenP->uk1[i];
		urk1[i] = ContGenP->urk1[i];
		ITermk1[i] = ContGenP->ITermk1[i];
		ek1[i] = ContGenP->ek1[i];
		eBk1[i] = ContGenP->eBk1[i];

		/* Controller Constants */
		Ki[i] = ContGenP->Ki[i];
		Kp[i] = ContGenP->Kp[i];
		Kb[i] = ContGenP->Kb[i];

		/* References and Inputs */
		Ref[i] = ContGenP->Ref[i];
		Input[i] = ContGenP->Input[i];
	}

	/* EXECUTES CONTROL LAW AND UPDATES OUTPUTS */

	/* Initiates uOut with low value */
	/* Note: The minimum value for motor rotation speed is the same for
	every bearing */
	uOut = ContGenP->uMin[1];

	/* Each data corresponds to a different bearing */
	for (int i = 0; i < NumBearings; i++)
	{

		/* Calculates bearing temp error and Back Calculation Error*/
		ek[i] = Ref[i] - Input[i];
		eBk1[i] = uk1[i] - urk1[i];

		/* CALCULATES PI CONTROL SIGNALS */

		/* Calculates Control Signal for Rotation Speed and Tt4 Protection */
		PIControl(Ki[i], Kp[i], Kb[i], ContGenP->Ts, ITermk1[i], ek[i], ek1[i], eBk1[i], &PIOut);

		/* Updates bearing's control variable */
		uk[i] = PIOut.u;

		/* Updates memory variables */
		uk1[i] = uk[i];
		ITermk1[i] = PIOut.Iout;
		ek1[i] = ek[i];

	}

	/* MAX LOGIC FOR CONTROLLER OUTPUT */

	/* Each data corresponds to a different bearing */
	for (int i = 0; i < NumBearings; i++)
	{
		uOut = Max(uOut,uk[i]);
	}

	/* MIN-MAX LOGIC FOR FUEL PUMP SATURATION */

	/* The uMax and uMin values are the fuel pump maximum and minimum values, which are
	 the same for any bearing */
	uOut = Min(uOut,ContGenP->uMax[1]);
	uOut = Max(uOut,ContGenP->uMin[1]);

	/* UPDATES urk1 SIGNALS AND VERIFIES ACTIVE BEARING */

	/* Initiates Active with 0 */
	Active = 0;

	/* Each data corresponds to a different bearing */
	for (int i = 0; i < NumBearings; i++)
	{
		urk1[i] = uOut;

		/* Verifies which bearing is activating the controller */
		if (uOut == uk[i])
		{
			Active = i;
		}

	}

	/* Each data corresponds to a different bearing */
	for (int i = 0; i < NumBearings; i++)
	{
		/* Previous samples of errors and control signals */
		ContGenP->uk1[i] = uk1[i];
		ContGenP->urk1[i] = urk1[i];
		ContGenP->ITermk1[i] = ITermk1[i];
		ContGenP->ek1[i] = ek1[i];
		ContGenP->eBk1[i] = eBk1[i];
		ContGenP->Active[i] = Active;
		ContGenP->uOut[i] = uOut;
	}

}
