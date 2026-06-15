
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

#include "mex.h"

/* -------------------------------------------------- */

#include <math.h>

#include "ConstantsTJ1200.h"
#include "Env_SampTime.h"
#include "MtxIntFunctions.h"		
// #include "Interpolation_Types.h"
// #include "LinMtxFunctions.h"

/* Includes for Ambient Calculations */

// #include "constants_TMATS.h"
// #include "functions_TMATS.h"

/* Controller includes */

#include "Control_Types.h"
#include "ControlFunctions.h"
// #include "IO_Types.h"
// #include "StartingFunctions.h"
// #include "DigitalOutDefs.h"


void PIFuelPump(struct ControllerConstants *ContConst, struct ControllerInput *ContInputP, 
                struct ControllerOutput *ContOutputP, double Tsample)
{
    
	/*--------------------------*/
	/* DECLARATION OF VARIABLES */
	/*--------------------------*/

	/* Operating Mode */
	int Mode = 0;
	/* Lever Mode */
	int LeverMode;
    /* Engineering units flag */
    int EngUnits;
 
	/* CLOSED-LOOP ROUTINE VARIABLES */

	/* Errors and control signals */
	double eNk;
	double eTt4k;
	double uNk;
	double uTt4k;
	double uMMk;
	double uRUk;

	/* Previous samples of errors and control signals */
	double uNk1 = ContOutputP->uNk1;
	double urk1 = ContOutputP->urk1;
	double ITermNk1 = ContOutputP->ITermNk1;
	double eNk1 = ContOutputP->eNk1;
	double eBNk1 = ContOutputP->eBNk1;

	/* Active controller flag */
	double Active = ContOutputP->Active;
	double CalcSigVec[] = { 100, 100, 100, 100 };
	double LastSignalIndex = 3;
	double *CSVPointer = &CalcSigVec;

	/* Controller Gains */
	double KiN;
	double KpN;
	double KbN = 1;// ContConst->KbN;
    
    /* Controller Constants */
    int ManualMode = 1;//ContConst->ManualMode;
    double WfMax = 5;//ContConst->WfMax;
	double WfMin = 0;
       
	/* Reference variables */
	double ASRef;
	double MinRef = ContOutputP->MinRef;

	/* Structures for PI outputs */
	PIOutput PIOutN;
	PIOutput PIOutT;

	/* Reference variableS */
	double RPMRef = ContOutputP->RPMRef;
	double FNpc;

	/* Actuation signal */
	double Wf = ContOutputP->Wf;
		
	/* Variables to be provided externaly via CAN communication */
	double RPM;
    
    /* Dummy variable for 2D or 1D calculations */
    double DummyVar = 1;

	/*----------------------------*/
	/* STARTTING OF CONTROL LOGIC */
	/*----------------------------*/

	/* READS CONTROLLER INPUT DATA */

	Mode = ContInputP->Mode;

 	/* Fuel Pump Input */
	FNpc = ContInputP->FNpc;
	RPM = ContInputP->RPM;

	/* LOGIC FOR ENGINE FUEL - MANUAL OR AUTOMATIC*/

	if (Mode == ManualMode)
	{
		/* LOGIC FOR MANUAL FUNCITONING */
	
		/* Updates Wf according to the option chosen for LeverMode */
		uMMk = FNpc;
		uMMk = Min(uMMk, 5);
		uMMk = Max(uMMk, 0);
		Wf = uMMk;

	}
	else
	{

		/* CALCULATION OF KpN AND KiN */

		/* Calculates gains used in PI controllers */
		KpN = 0.0021179; 
		KiN = 3.6301e-03; 

		/* CONVERTION OF FUEL FLOW INTO ROTATION SPEED */

		/* Calculates roatation speed reference */
		RPMRef = FNpc * 1;
		/* Updates MinRef value */
		MinRef = RPMRef;

		/* CALCULATION OF ERRORS */

		/* Calculates Rotation Speed Error and Back Calculation Error*/
		eNk = MinRef - RPM;
		eBNk1 = uNk1 - urk1;

		/* CALCULATES PI CONTROL SIGNALS */

		/* Calculates Control Signal for Rotation Speed and Tt4 Protection */
		PIControl(KiN, KpN, KbN, Tsample, ITermNk1, eNk, eNk1, eBNk1, &PIOutN);
		uNk = PIOutN.u;

		/* IDENTIFIES THE ACTIVE CONTROLLER */
		/*	1 - Power Management
			2 - Saturated at 5 V
			3 - Saturated at 0 V
			9 - Output Different From Any Calculated Signal
		*/

		/* FUEL PUMP SATURATION */
		uMMk = Min(uNk, WfMax);
		uMMk = Max(uMMk, WfMin);

		/* COMPUTES ACTUATION SIGNAL OUTPUT */

		/* Computes the actuation signal at desired output */
		Wf = uMMk;

		/* CHECKS FOR ACTUATION SATURATION */

		/* Updates Signals in String */
		*(CSVPointer + 1) = uNk;
		*(CSVPointer + 2) = 5;
		*(CSVPointer + 3) = 0;

		/* Identifies Active Controller */
		Active = ActiveCont(CSVPointer, LastSignalIndex, uMMk);

		/* MEMORY UPDATE FOR PI CONTROLLER */

		/* Delayed control variables */
		uNk1 = PIOutN.u;
		urk1 = uMMk;
		ITermNk1 = PIOutN.Iout;
		eNk1 = eNk;

	}
	
	/* Returns the fuel flow value */
	ContOutputP->Wf = Wf;
	ContOutputP->Active = Active;
	ContOutputP->RPMRef = RPMRef;
	ContOutputP->MinRef = MinRef;

	/* Updates calculated memory variables */
	ContOutputP->uNk1 = uNk1;
	ContOutputP->urk1 = urk1;
	ContOutputP->ITermNk1 = ITermNk1;
	ContOutputP->eNk1 = eNk1;
	ContOutputP->eBNk1 = eBNk1;

}
