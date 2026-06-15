
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
#include "Interpolation_Types.h"	
// #include "Interpolation_Types.h"
// #include "LinMtxFunctions.h"

/* Includes for Ambient Calculations */

// #include "constants_TMATS.h"
// #include "functions_TMATS.h"

/* Controller includes */

#include "Control_Types.h"
#include "ControlFunctions.h"
#include "Model_Types.h"
// #include "IO_Types.h"
// #include "StartingFunctions.h"
// #include "DigitalOutDefs.h"


void BearingModel(struct BearingPars *BearModP, double *RPMEVecP, double *TNOilP, double *TMaxRPMP)
{
    
	/* Structure for finding values */
	InterpIndex Indexes;
// double test0 = *(RPMEVecP + 0);
// double test1 = *(RPMEVecP + 1);
// double test2 = *(RPMEVecP + 2);

// mexPrintf("Elem 1 = %f, Elem 2 = %f, Elem 3 = %f\n", test0, test1, test2);

	/* Calculates position of engine rotation speed inside breakpoints vector */
	//IndFind(Engine RPM, Num of Elems in Engine RPM Vector, Engine RPM Vector, Pointer for indexes)
 	IndFind(BearModP->RPME, BearModP->ElNumRPME, RPMEVecP, &Indexes);
 
 	/* Reads the value of the Acceleration Schedule corrected rotation reference */
 	int k = Indexes.K;
 	double f = Indexes.f;

	/* If f < 0, f is set to 0 */
	f = Max(f,0);

	/* Calculates the bearing temperature if no oil is applied at given engine RPM */
	double TNOil = *(TNOilP + k) + f*(*(TNOilP + k + 1) - *(TNOilP + k));
	/* Calculates the bearing temperature reduction if maximum oil flow is applied at given engine RPM */
	double DelTMax = *(TMaxRPMP + k) + f*(*(TMaxRPMP + k + 1) - *(TMaxRPMP + k));
 	 
	/*----------------------------*/
	/* STARTTING OF CONTROL LOGIC */
	/*----------------------------*/

	// /* READS CONTROLLER INPUT DATA */

	// Mode = ContInputP->Mode;

 	// /* Fuel Pump Input */
	// FNpc = ContInputP->FNpc;
	// RPM = ContInputP->RPM;

	// /* LOGIC FOR ENGINE FUEL - MANUAL OR AUTOMATIC*/

	/* Calculation of discrete coefficients */
    double Ad = exp(BearModP->A * BearModP->Ts);
    double Bd = (Ad - 1) * BearModP->B / BearModP->A;

	/* Calculation of plant input */
	double Input = BearModP->RPMP *  DelTMax / BearModP->MaxRPMP;

	/* Calculation of bearing temperature from dynamic equation */
	BearModP->T = BearModP->Tss + Ad * (BearModP->T - BearModP->Tss) + Bd * (Input - BearModP->RPMPss);
	/* Adds TNOil and additional external temperature increase to bearing temperature*/
	BearModP->Tout = BearModP->Tss + BearModP->C * (BearModP->T - BearModP->Tss) + TNOil + BearModP->DelTExt;

	// if (Mode == ManualMode)
	// {
	// 	/* LOGIC FOR MANUAL FUNCITONING */
	
	// 	/* Updates Wf according to the option chosen for LeverMode */
	// 	uMMk = FNpc;
	// 	uMMk = Min(uMMk, 5);
	// 	uMMk = Max(uMMk, 0);
	// 	Wf = uMMk;

	// }
	// else
	// {

	// 	/* CALCULATION OF KpN AND KiN */

	// 	/* Calculates gains used in PI controllers */
	// 	KpN = 0.0021179 / 10; 
	// 	KiN = 3.6301e-03 / 10; 

	// 	/* CONVERTION OF FUEL FLOW INTO ROTATION SPEED */

	// 	/* Calculates roatation speed reference */
	// 	RPMRef = FNpc * 1;
	// 	/* Updates MinRef value */
	// 	MinRef = RPMRef;

	// 	/* CALCULATION OF ERRORS */

	// 	/* Calculates Rotation Speed Error and Back Calculation Error*/
	// 	eNk = MinRef - RPM;
	// 	eBNk1 = uNk1 - urk1;

	// 	/* CALCULATES PI CONTROL SIGNALS */

	// 	/* Calculates Control Signal for Rotation Speed and Tt4 Protection */
	// 	PIControl(KiN, KpN, KbN, Tsample, ITermNk1, eNk, eNk1, eBNk1, &PIOutN);
	// 	uNk = PIOutN.u;

	// 	/* IDENTIFIES THE ACTIVE CONTROLLER */
	// 	/*	1 - Power Management
	// 		2 - Saturated at 5 V
	// 		3 - Saturated at 0 V
	// 		9 - Output Different From Any Calculated Signal
	// 	*/

	// 	/* FUEL PUMP SATURATION */
	// 	uMMk = Min(uNk, WfMax);
	// 	uMMk = Max(uMMk, WfMin);

	// 	/* COMPUTES ACTUATION SIGNAL OUTPUT */

	// 	/* Computes the actuation signal at desired output */
	// 	Wf = uMMk;

	// 	/* CHECKS FOR ACTUATION SATURATION */

	// 	/* Updates Signals in String */
	// 	*(CSVPointer + 1) = uNk;
	// 	*(CSVPointer + 2) = 5;
	// 	*(CSVPointer + 3) = 0;

	// 	/* Identifies Active Controller */
	// 	Active = ActiveCont(CSVPointer, LastSignalIndex, uMMk);

	// 	/* MEMORY UPDATE FOR PI CONTROLLER */

	// 	/* Delayed control variables */
	// 	uNk1 = PIOutN.u;
	// 	urk1 = uMMk;
	// 	ITermNk1 = PIOutN.Iout;
	// 	eNk1 = eNk;

	// }
	
	// /* Returns the fuel flow value */
	// ContOutputP->Wf = Wf;
	// ContOutputP->Active = Active;
	// ContOutputP->RPMRef = RPMRef;
	// ContOutputP->MinRef = MinRef;

	// /* Updates calculated memory variables */
	// ContOutputP->uNk1 = uNk1;
	// ContOutputP->urk1 = urk1;
	// ContOutputP->ITermNk1 = ITermNk1;
	// ContOutputP->eNk1 = eNk1;
	// ContOutputP->eBNk1 = eBNk1;

}
