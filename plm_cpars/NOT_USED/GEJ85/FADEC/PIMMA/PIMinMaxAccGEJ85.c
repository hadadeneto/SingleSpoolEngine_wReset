/*
 * PIMinMaxTJ200.c - HIL File
 *
 *  Created on: Dec 11, 2019
 *      Author: Antonio Hadade Neto
 */

#include <math.h>

#include "ConstantsGEJ85.h"
#include "Env_SampTime.h"
#include "MtxIntFunctions.h"		
#include "Interpolation_Types.h"
#include "LinMtxFunctions.h"

/* Controller includes */

#include "Control_Types.h"
#include "ControlFunctions.h"
#include "IO_Types.h"
#include "StartingFunctions.h"
#include "DigitalOutDefs.h"

void PIMinMaxAccGEJ85(struct ControlStart *ContStartP, struct ControllerInput *ContInputP, struct ControllerOutput *ContOutputP, unsigned int *digitalP, unsigned int *keysP, double *NcFANContMtxP, double *FNperContMtxP, double *N_KpMtxP, double *N_KiMtxP, double Tsample)
{

	/*--------------------------*/
	/* DECLARATION OF VARIABLES */
	/*--------------------------*/

	/* STARTING LOGIC ROUTINE VARIABLES */

	/* Starting Routine Structs */
	static digital_t digital;
	digital_t digitalEmpty = { 0 };
	static keys_t keys;
	keys_t keysEmpty = { 0 };
	static FuelRamp_t FuelSRP = { 0 };
	FuelRamp_t FuelSRPEmpty = { 0 };
	static POil_t OilPresSRP = { 0 };
	POil_t OilPresSRPEmpty = { 0 };

	/* Operating Mode */
	int Mode;
	/* Lever Mode */
	int LeverMode;

	/* Resets flags */
	static int RefRampReset;
	static int OpenLoopReset;

	/* FuelRamp_t struct variables  */
	static double FuelFlow;		/*Fuel Flow Value*/
	static int StartComplete;	/* Flag indicating if stargin sequence is complete */
	static int Current_key_start;
	static int Old_key_start;
	static int EngineShutDown = 0;


	/* CLOSED-LOOP ROUTINE VARIABLES */

	/* Errors and control signals */
	double eNk;
	double eNMaxk;
	double eAcck;
	double eTt4k;
	double uNk;
	double uNMaxk;
	double uAcck;
	double uTt4k;
	double uMMk;
	double uRUk;

	/* Previous samples of errors and control signals */
	static double uNk1 = 0;
	static double uNMaxk1 = 0;
	static double uAcck1 = 0;
	static double urk1 = 0;
	static double ITermNk1 = 0;
	static double ITermNMaxk1 = 0;
	static double ITermAcck1 = 0;
	static double uTt4k1 = 0;
	static double ITermTk1 = 0;
	static double eNk1 = 0;
	static double eNMaxk1 = 0;
	static double eAcck1 = 0;
	static double eTt4k1 = 0;
	static double eBNk1 = 0;
	static double eBNMaxk1 = 0;
	static double eBAcck1 = 0;
	static double eBTk1 = 0;
	static double RPM1 = 0;

	/* Active controller flag */
	double Active;
	double CalcSigVec[] = { 100, 100, 100, 100 };
	double LastSignalIndex = 5;
	double *CSVPointer = &CalcSigVec;

	/* Controller Gains */
	double KiN;
	double KpN;
	double KbN = GEJ85_KBN;
	double KbT = GEJ85_KBT;
	double KbAcc = GEJ85_KBACC;
	double KpTt4 = GEJ85_KPTT4;
	double KiTt4 = GEJ85_KITT4;
	double KpAcc = GEJ85_KPACC;
	double KiAcc = GEJ85_KIACC;
	double KpNMax = GEJ85_KPNMAX;
	double KiNMax = GEJ85_KINMAX;

	/* Matrices used for reference and gain calculations */
	double N_KiMtx[GEJ85_TOTAL_ELEM];
	double N_KpMtx[GEJ85_TOTAL_ELEM];
	double NcFANContMtx[GEJ85_TOTAL_ELEM];
	double FNperContMtx[GEJ85_TOTAL_ELEM];
	double Mtx2D[GEJ85_MN_ELEM * GEJ85_FN_ELEM];
	double Mtx2DH[GEJ85_MN_ELEM * GEJ85_FN_ELEM];
	double Mtx1D[GEJ85_FN_ELEM];
	double Mtx1DH[GEJ85_FN_ELEM];

	/* Vectors used in for interpolation during gains caluclation */
	double AltLinVec[] = { 0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000 };
	double MNLinVec[] = { 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.95 };
	//double NcVec[] = { 0.55, 0.6, 0.7, 0.8, 0.9, 0.99 };
	//double ASVec[] = { 1.09, 1.08, 1.06, 1.08, 1.09, 1.011 };
	double ASVec[] = { 0.269, 0.276, 0.294, 0.3, 0.36, 0.441, 0.462, 0.3, 0.18 };
	double NcVec[] = { 0.6, 0.65, 0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 0.99 };
	//double ASVec[] = { 1.18, 1.16, 1.15, 1.18, 1.18, 1.09 };
	double ASRef;
	double MinRef;

	double NumEl2D = GEJ85_MN_ELEM * GEJ85_FN_ELEM;
	double NumEl1D = GEJ85_FN_ELEM;

	/* Structures for PI outputs */
	PIOutput PIOutN;
	PIOutput PIOutNMax;
	PIOutput PIOutAcc;
	PIOutput PIOutT;

	/* Reference variableS */
	double RPMRef;
	double FNpc;
	static double RefInit;

	/* Actuation signal */
	static double fValue;
		
	/* Variables to be provided externaly via CAN communication */
	double Altitude;
	double MN;
	double RPM;
	double Accel;

	/* Stations variables */
	double Pt2;
	double Tt2;
	double Pt3;
	double Tt5;

	/* Correction parameter */
	double Nc;
	double Theta;
	double Delta;

	/* Declares pointer for 3D interpolation indexes */
	InterpIndex3D Index3D;

	/* Starging Parameters */
	double POil;

	/*Dummy Constant*/
	double DummyConst = 0;


	/*----------------------------*/
	/* STARTTING OF CONTROL LOGIC */
	/*----------------------------*/

	/* RESET REQUEST TREATMENT */

	if (ContInputP->Reset == 1) 
	{
		/* Resets all static structures */
		digital = digitalEmpty;
		keys = keysEmpty;
		FuelSRP = FuelSRPEmpty;
		OilPresSRP = OilPresSRPEmpty;

		/* Resets all static variables */
		FuelFlow = 0;		/*Fuel Flow Value*/
		StartComplete = 0;	/* Flag indicating if stargin sequence is complete */
		Current_key_start = 0;
		Old_key_start = 0;
		EngineShutDown = 0;
		uNk1 = 0;
		uNMaxk1 = 0;
		uAcck1 = 0;
		urk1 = 0;
		ITermNk1 = 0;
		ITermNMaxk1 = 0;
		ITermAcck1 = 0;
		uTt4k1 = 0;
		ITermTk1 = 0;
		eNk1 = 0;
		eNMaxk1 = 0;
		eAcck1 = 0;
		eTt4k1 = 0;
		eBNk1 = 0;
		eBNMaxk1 = 0;
		eBAcck1 = 0;
		eBTk1 = 0;
		RPM1 = RPM;
		RefInit = 0;
		fValue = 0;

		/* Indicates that reference ramp is to be reset */
		RefRampReset = 1;
		OilPresSRP.Reset = 1;
		FuelSRP.Reset = 1;

		/* Sets reset flag to zero */
		ContInputP->Reset = 0;

	}

	/* READS CONTROLLER INPUT DATA */

	/* Digital input */
	Old_key_start = ContInputP->Old_key_start;
	Current_key_start = ContInputP->Current_key_start;
	digital.bits.inverter = ContInputP->bits_inverter;
	Mode = ContInputP->Mode;
	LeverMode = ContInputP->LeverMode;

	/* Ambient input */
	Altitude = ContInputP->Altitude;
	MN = ContInputP->MN;

	/* Engine input */
	Pt2 = ContInputP->Pt2;
	Tt2 = ContInputP->Tt2;
	Pt3 = ContInputP->Pt3;
	Tt5 = ContInputP->Tt5;
	FNpc = ContInputP->FNpc;
	RPM = ContInputP->RPM;
	POil = ContInputP->POil;

	/* Reads digital keys */
	keys.in = *(keysP);
	   
	/* EMERGENCY SHUT OFF LOGIC */

	EngineShutDown = Emergency(&OilPresSRP, &digital, &FuelSRP, !keys.bits.emergency_key);

	/* OIL PRESSURE LOGIC */

	POilLogic(ContStartP, POil, &OilPresSRP, &digital, EngineShutDown, Tsample);
	digital.bits.oil_pump_led = OilPresSRP.POilAlarm || OilPresSRP.POilFailure;

	/******** LOGIC FOR VERIFYING IF START MUST BE SKIPPED - MUST BE USED FOR SIMULATION ONLY AND NOT IN FLIGHT VERSION **********/

	if (ContInputP->SkipStart == 1 && StartComplete == 0) 
	{
		/* Sets StartComplete flag with 1 indicating that start has been accomplished */

		/* Sets initial conditions for fuel values and rotation speed references */
		fValue = ContInputP->Wf0;
		uNk1 = fValue;
		uNMaxk1 = fValue;
		uAcck1 = fValue;
		urk1 = fValue;
		ITermNk1 = fValue;
		ITermNMaxk1 = fValue;
		ITermAcck1 = fValue;
		uTt4k1 = fValue;
		ITermTk1 = fValue;
		FuelFlow = fValue;
		eNk1 = 0;
		eNMaxk1 = 0;
		eAcck1 = 0;
		eTt4k1 = 0;
		RPMRef = RPM;
		MinRef = RPM;
		RefInit = RPM;
		RPM1 = RPM;
		Active = 0;
		StartComplete = 1;
	}
	/******************************************************************************************************************************/

	/* LOGIC FOR ENGINE FUEL - MANUAL OR AUTOMATIC*/

	if (Mode == GEJ85_MANUAL)
	{
		/* LOGIC FOR MANUAL FUNCITONING */

		ManualKeys(&digital, &keys, EngineShutDown, &fValue);
	}
	else
	{
		if (StartComplete == 0)
		{
			/* FUEL LOGIC FOR STARRING MODE */

			FuelSRP.Current_key_start = Current_key_start;
			FuelSRP.Old_key_start = Old_key_start;
			FuelLogic(ContStartP, RPM, Tt5, &FuelSRP, &digital, EngineShutDown, Tsample);
			fValue = FuelSRP.FuelFlow;
			StartComplete = FuelSRP.StartComplete;

			/* Updates Controller Memory for Initial Conditions to be matched */
			uNk1 = fValue;
			uNMaxk1 = fValue;
			uAcck1 = fValue;
			urk1 = fValue;
			ITermNk1 = fValue;
			ITermNMaxk1 = fValue;
			ITermAcck1 = fValue;
			uTt4k1 = fValue;
			ITermTk1 = fValue;
			FuelFlow = fValue;
			eNk1 = 0;
			eNMaxk1 = 0;
			eAcck1 = 0;
			eTt4k1 = 0;
			RPMRef = RPM;
			MinRef = RPM;
			RefInit = RPM;
			RPM1 = RPM;
			Active = 0;
		}
		else
		{
			
			/*---------------*/
			/* CONTROL LOGIC */
			/*---------------*/

			if (LeverMode == GEJ85_CLOOP)
			{
				/* CALCULATION OF USED NORMALIZED PARAMETERS */

				if (FNpc > 0.7) 
				{
					double test = 1;
				}

				/* Calculates the Value of Theta */
				Theta = Tt2 / TSTD;
				Delta = Pt2 / PSTD;

				/* Calculates the Value of Nc */
				Nc = RPM / sqrt(Theta);
				Nc = Nc / GEJ85_NDES;

				/* CALCULATION OF ACCELERATION */
				Accel = (RPM - RPM1) / Tsample;
				/* Updates previous RPM value */
				RPM1 = RPM;

				/* CALCULATION OF REFERENCE FROM THRUST PERCENTUAL INPUT */

				/* Finds value of RPM reference from FNpc reference */
				InterpInd3DRPM(Altitude, MN, FNpc, &AltLinVec, &MNLinVec, FNperContMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, GEJ85_ALT_ELEM, GEJ85_MN_ELEM, GEJ85_FN_ELEM, &Index3D);
				RPMRef = InterpValue(&Index3D, NcFANContMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);
				RPMRef = RPMRef * GEJ85_NDES*sqrt(Theta);

				/* CALCULATION OF MAXIMUM ALLOWED ACCELERATION */

				/* Calculates the Acceleration Schedule Value for current Nc */
				//ASRef = ASRefFind(&NcVec, &ASVec, Nc, Tt2, GEJ85_AS_ELEM, TSTD, GEJ85_NDES);
				//ASRef = ASRef * GEJ85_NDES * Delta;
				InterpInd3DRPM(0, 0, Nc, &DummyConst, &DummyConst, &NcVec, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, 1, 1, GEJ85_AS_ELEM, &Index3D);
				ASRef = InterpValue(&Index3D, &ASVec, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);
				ASRef = ASRef * GEJ85_NDES * Delta;

				///* Calculates the minimum value between ASRef and NMAX */
				//MinRef = Min(ASRef, GEJ85_NMAX);
				MinRef = RPMRef;

				///* Calculates the minimum value between the previous result and the actual RPM reference */
				//MinRef = Min(MinRef, RPMRef);

				/* LOGIC FOR SMOOTH REFERENCE TRANSITION */

				/* Keeps the reference from exerting step transition if intended by the user */
				RefRamp(&MinRef, &RefInit, &RefRampReset, GEJ85_REFRAMP, TICK);

				/* CALCULATION OF KpN AND KiN */

				/* Finds 3D indexes necessary for interpolation of controller gains */
				InterpInd3DRPM(Altitude, MN, Nc, &AltLinVec, &MNLinVec, NcFANContMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, GEJ85_ALT_ELEM, GEJ85_MN_ELEM, GEJ85_FN_ELEM, &Index3D);
				
				/* Calculates gains used in PI controllers */
				KpN = InterpValue(&Index3D, N_KpMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);
				KiN = InterpValue(&Index3D, N_KiMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);

				/* CALCULATION OF ERRORS */

				/* Calculates Rotation Speed Error and Back Calculation Error*/
				eNk = MinRef - RPM;
				eNMaxk = GEJ85_NMAX - RPM;
				eAcck = ASRef - Accel;
				eTt4k = GEJ85_TT4MAX - Tt5;
				//eTt4k = GEJ85_TT5MAX - Tt5;
				eBNk1 = uNk1 - urk1;
				eBNMaxk1 = uNMaxk1 - urk1;
				eBAcck1 = uAcck1 - urk1;
				eBTk1 = uTt4k1 - urk1;

				/* CALCULATES PI CONTROL SIGNALS */

				/* Calculates Control Signal for Power Management Controller */
				PIControl(KiN, KpN, KbN, Tsample, ITermNk1, eNk, eNk1, eBNk1, &PIOutN);
				uNk = PIOutN.u;

				/* Calculates Control Signals for Limiters */
				PIControl(KiN, KpN, KbN, Tsample, ITermNMaxk1, eNMaxk, eNMaxk1, eBNMaxk1, &PIOutNMax);
				uNMaxk = PIOutNMax.u;
				PIControl(KiAcc, KpAcc, KbAcc, Tsample, ITermAcck1, eAcck, eAcck1, eBAcck1, &PIOutAcc);
				uAcck = PIOutAcc.u;
				PIControl(KiTt4, KpTt4, KbT, Tsample, ITermTk1, eTt4k, eTt4k1, eBTk1, &PIOutT);
				uTt4k = PIOutT.u;

				/* Calculates the Minimum Value for Control Signal Considering RU Parameter */
				uRUk = GEJ85_RUMIN * Pt3;

				/* IMPLEMENTS MIN-MAX LOGIC */

				/* Min Logic */
				uMMk = Min(uNk, uTt4k);
				uMMk = Min(uMMk, uNMaxk);
				uMMk = Min(uMMk, uAcck);
				
				/* Max Logic */
				uMMk = Max(uMMk, uRUk);

				/* IDENTIFIES THE ACTIVE CONTROLLER */
				/*	1 - Power Management
					2 - Tt4 Limiter
					3 - RU Limiter
					4 - NMax Limiter
					5 - Accel Limiter
					9 - Output Different From Any Calculated Signal
				*/
				
				/* Updates Signals in String */
				*(CSVPointer + 1) = uNk;
				*(CSVPointer + 2) = uTt4k;
				*(CSVPointer + 3) = uRUk;
				*(CSVPointer + 4) = uNMaxk;
				*(CSVPointer + 5) = uAcck;

				/* Identifies Active Controller */
				Active = ActiveCont(CSVPointer, LastSignalIndex, uMMk);

				/* COMPUTES ACTUATION SIGNAL OUTPUT */

				/* Computes the actuation signal at desired output */
				fValue = uMMk;

				/* MEMORY UPDATE FOR PI CONTROLLER */

				/* Delayed control variables */
				uNk1 = PIOutN.u;
				uNMaxk1 = PIOutNMax.u;
				uAcck1 = PIOutAcc.u;
				uTt4k1 = PIOutT.u;
				urk1 = uMMk;
				ITermNk1 = PIOutN.Iout;
				ITermNMaxk1 = PIOutNMax.Iout;
				ITermAcck1 = PIOutAcc.Iout;
				ITermTk1 = PIOutT.Iout;
				eNk1 = eNk;
				eNMaxk1 = eNMaxk;
				eAcck1 = eAcck;
				eTt4k1 = eTt4k;

			}
			else
			{
				/* Calculates OpenLoop Signal */
				OpenLoop(ContStartP, FuelFlow, &fValue, EngineShutDown);

			}

		}

	}

	/* Returns the fuel flow value */
	ContOutputP->fValue = fValue;
	ContOutputP->Active = Active;
	ContOutputP->RPMRef = RPMRef;
	ContOutputP->FiltRef = MinRef;
	*(digitalP) = digital.out;

}
