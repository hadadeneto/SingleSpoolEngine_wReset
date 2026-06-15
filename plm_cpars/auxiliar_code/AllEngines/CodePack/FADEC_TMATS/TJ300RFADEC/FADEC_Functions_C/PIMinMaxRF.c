
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

//#include "../ConstantsTJ1200.h"
#include "../FADEC_Defines_H/Env_SampTime.h"
#include "../FADEC_Functions_H/MtxIntFunctions.h"
#include "../FADEC_Defines_H/Interpolation_Types.h"
// #include "../FADEC_Functions_H/LinMtxFunctions.h"

/* Includes for Ambient Calculations */

#include "../FADEC_Defines_H/constants_TMATS.h"
#include "../FADEC_Functions_H/functions_TMATS.h"

/* Controller includes */

#include "../FADEC_Defines_H/Control_Types.h"
#include "../FADEC_Functions_H/ControlFunctions.h"
#include "../FADEC_Functions_H/functions_TMATS.h"
#include "../FADEC_Defines_H/IO_Types.h"
#include "../FADEC_Functions_H/StartingFunctions.h"
#include "../FADEC_Defines_H/DigitalOutDefs.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"


void PIMinMaxRF(floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP, floating *ASVecP, floating *DSVecP,
                floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
                floating *DeltaMtx2DP, floating *DeltaMtx2DHP, floating *DeltaMtx1DP, floating *DeltaMtx1DHP,
                struct ControllerConstants *ContConst, struct ControlStart *ContStartP,
                struct ControllerInput *ContInputP,
                struct ControllerOutput *ContOutputP, unsigned int *digitalP,
                unsigned int *keysP, floating *DeltaMtxP, floating *NcFANContMtxP,
                floating *FNcMaxContMtxP, floating *FNperContMtxP, floating *N_KpMtxP, floating *N_KpshMtxP,
                floating *N_KiMtxP, floating *N_KishMtxP, floating Tsample)
{

	/*--------------------------*/
	/* DECLARATION OF VARIABLES */
	/*--------------------------*/

	/* STARTING LOGIC ROUTINE VARIABLES */

	/* Starting Routine Structs */
	digital_t digital;
	keys_t keys;
	// static POil_t OilPresSRP = { 0 };
	// POil_t OilPresSRPEmpty = { 0 };

	/* Operating Mode */
	int Mode;
	/* Lever Mode */
	int LeverMode;
    /* Engineering units flag */
    int EngUnits;

	/* Starging variables  */
	floating WfTrigger = ContStartP->WfTrigger;
	int StartComplete = ContOutputP->StartComplete;	/* Flag indicating if stargin sequence is complete */
	int Current_key_start = ContStartP->Current_key_start;
	int Old_key_start = ContStartP->Old_key_start;
	/* Variable indiating that engine must be shut down */
	//int EngineShutDown = ContOutputP->EngineShutDown;


	/* CLOSED-LOOP ROUTINE VARIABLES */

	/* Errors and control signals */
	floating eNk;
	floating eTt4k;
	floating uNk;
	floating uTt4k;
	floating uMMk;
	floating uRUk;

	/* Previous samples of errors and control signals */
	floating uNk1 = ContOutputP->uNk1;
	floating urk1 = ContOutputP->urk1;
	floating ITermNk1 = ContOutputP->ITermNk1;
	floating uTt4k1 = ContOutputP->uTt4k1;
	floating ITermTk1 = ContOutputP->ITermTk1;
	floating eNk1 = ContOutputP->eNk1;
	floating eTt4k1 = ContOutputP->eTt4k1;
	floating eBNk1 = ContOutputP->eBNk1;
	floating eBTk1 = ContOutputP->eBTk1;

	/* Active controller flag */
	floating Active = ContOutputP->Active;
	floating CalcSigVec[] = { 100, 100, 100, 100 };
	floating LastSignalIndex = 3;
	floating *CSVPointer = CalcSigVec;

	/* Controller Gains */
	floating KiN;
	floating KpN;
	floating KbN = ContConst->KbN;
	floating KbT = ContConst->KbT;
    floating KpTt4 = ContConst->KpTt4;
	floating KiTt4 = ContConst->KiTt4;

    /* Controller Constants */
    int       Alt_Elem = ContConst->Alt_Elem;
    int       As_Elem = ContConst->As_Elem;
    int       CLLever = ContConst->CLLever;
    int       Fn_Elem = ContConst->Fn_Elem;
    int       ManualMode = ContConst->ManualMode;
    int       MN_Elem = ContConst->MN_Elem;
    floating    NDes = ContConst->NDes;
    floating    NMax = ContConst->NMaxRef;
    floating    RefRampValue = ContConst->RefRampValue;
    floating    RUMin = ContConst->RUMin;
    floating    Tt4Max = ContConst->Tt4MaxRef;
    int       UseEngUnits = ContConst->UseEngUnits;
    floating    WfMax = ContConst->WfMax;

    /* Number of elements of gains and thrust elements */
	floating NumEl2D = MN_Elem * Fn_Elem;
	floating NumEl1D = Fn_Elem;

    /* Number of elements of delta matrix */
    floating DeltaNumEl2D = Alt_Elem * MN_Elem;
    floating DeltaNumEl1D = MN_Elem;

	/* Reference variables */
	floating ASRef;
	floating DSRef;
	floating MinRef = ContOutputP->MinRef;

	/* Structures for PI outputs */
	PIOutput PIOutN;
	PIOutput PIOutT;

	/* Reference variableS */
	floating RPMRef = ContOutputP->RPMRef;
	floating FNpc;

	/* Actuation signal */
	floating Wf = ContOutputP->Wf;

	/* Variables to be provided externaly via CAN communication */
	floating Altitude;
	floating MN;
	floating RPM;

	/* Stations variables */
	floating Tt2;
	floating Pt3;
	floating Tt4;

	/* Correction parameter */
    floating FNcMax;
	floating Nc;
	floating Theta;
    floating Delta;

	/* Declares pointer for 3D interpolation indexes */
	InterpIndex3D Index3D;

	/* Starging Parameters */
	//floating POil;

    /* Dummy variable for 2D or 1D calculations */
    floating DummyVar = 1;


	/*----------------------------*/
	/* STARTTING OF CONTROL LOGIC */
	/*----------------------------*/

	/* READS CONTROLLER INPUT DATA */

	/* Digital input */
	Old_key_start = ContInputP->Old_key_start;
	Current_key_start = ContInputP->Current_key_start;
	digital.bits.inverter = ContInputP->bits_inverter;
	Mode = ContInputP->Mode;
	LeverMode = ContInputP->LeverMode;
    EngUnits = ContInputP->EngUnits;

	/* Ambient input */
	Altitude = ContInputP->Altitude;
	MN = ContInputP->MN;

	/* Engine input */
	Tt2 = ContInputP->Tt2;
//Tt2 = 288.15; //TESTE!! APAGAR DEPOIS!!
	Pt3 = ContInputP->Pt3;
	Tt4 = ContInputP->Tt4;
	FNpc = ContInputP->FNpc;
	RPM = ContInputP->RPM;
	//POil = ContInputP->POil;

	/* Reads digital keys */
	keys.in = *(keysP);

	/* Reads digital outputs */
	digital.out = *(digitalP);

	/* EMERGENCY SHUT OFF LOGIC */
	//EngineShutDown = Emergency(&OilPresSRP, &digital, ContStartP, !keys.bits.emergency_key);
	//EngineShutDown = 0;

	/* OIL PRESSURE LOGIC */

	// POilLogic(ContStartP, POil, &OilPresSRP, &digital, EngineShutDown, Tsample);
	// digital.bits.oil_pump_led = OilPresSRP.POilAlarm || OilPresSRP.POilFailure;

	/* LOGIC FOR ENGINE FUEL - MANUAL OR AUTOMATIC*/

	if (Mode == ManualMode)
	{
		/* LOGIC FOR MANUAL FUNCITONING */

		/* Updates Wf according to the option chosen for LeverMode */
		Wf = FNpc * WfMax;

		/* Sets the values of keys according to manual input */
		ManualKeysSR(&digital, &keys, &Wf);
	}
	else
	{
		if (StartComplete == 0)
		{
			/* FUEL LOGIC FOR STARRING MODE */

			ContStartP->Current_key_start = Current_key_start;
			ContStartP->Old_key_start = Old_key_start;

			/* If ContConst->StrWhich == 1, executes start logic for larger engines */
			if (ContConst->StrtWhich == 1)
			{
				/* Executes starting logic */
				StartLogic(ContConst, ContStartP, RPM, Tt4, &digital, Tsample);

				 //StartLogicCL(RPM, Tt4, &digital,
				 //	  AltLinVecP, MNLinVecP, NcVecP,
				 //      Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,
				 //      ContConst, ContStartP,
				 //      ContInputP, NcFANContMtxP,
				 //	  N_KpshMtxP, N_KishMtxP, Tsample);
			}

			/* If ContConst->StrWhich == 2, executes start logic for smaller engines */
			if (ContConst->StrtWhich == 2)
			{
				/* Executes starting logic */
				StartLogicTJ200(ContConst, ContStartP, RPM, Tt4, &digital, Tsample);

				// StartLogicCL(RPM, Tt4, &digital,
				// 	  AltLinVecP, MNLinVecP, NcVecP,
				//       Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,
				//       ContConst, ContStartP,
				//       ContInputP, NcFANContMtxP,
				// 	  N_KpMtxP, N_KiMtxP, Tsample);
			}

			Wf = ContStartP->Wf;
			StartComplete = ContStartP->StartComplete;

			/* Saves starting outputs to corresponding controller outputs */
			ContOutputP->StartComplete = ContStartP->StartComplete;
			ContOutputP->IgnitionFail = ContStartP->IgnitionFail;
			ContOutputP->ControlPhase = ContStartP->ControlPhase;

			/* Updates Controller Memory for Initial Conditions to be matched */
			uNk1 = Wf;
			urk1 = Wf;
			ITermNk1 = Wf;
			uTt4k1 = Wf;
			ITermTk1 = Wf;
			WfTrigger = Wf;
			eNk1 = 0;
			eTt4k1 = 0;
			RPMRef = RPM;
			// MinRef = RPM;
			MinRef = ContStartP->RPMRef;
			ContStartP->RefInit = RPM;
			// Active = 0;
			Active = ContStartP->Active;

		}
		else
		{

			/*---------------*/
			/* CONTROL LOGIC */
			/*---------------*/

			if(LeverMode == CLLever)
			{
				/* CALCULATION OF USED NORMALIZED PARAMETERS */

				/* Calculates the Value of Theta */
				Theta = Tt2 / TSTD;

				/* Calculates the Value of Nc - requries definition of sqrtT */
				Nc = RPM / sqrtT(Theta);
				Nc = Nc / NDes;

                /* CALCULATION OF THRUST PERCENTUAL */

                // /*Fins the thrust percentual value from value sent in engineering units*/
                // if(EngUnits == UseEngUnits)
                // {

                    // /* Gets the indexes of Altitude and MN with a fake Fnpc value suitable for using InterpInd3DRPM */
                    // InterpInd3DRPM(Altitude, MN, 1, AltLinVecP, MNLinVecP, FNperContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Alt_Elem, MN_Elem, Fn_Elem, &Index3D);

                    // /* Shifts the indexes of Index3D for finding a 2D element */
                    // Index3D.kRPM = Index3D.kMN;
                    // Index3D.kRPMH = Index3D.kMNH;
                    // Index3D.fRPM = Index3D.fMN;
                    // Index3D.kMN = Index3D.kA;
                    // Index3D.kMNH = Index3D.kAH;
                    // Index3D.fMN = Index3D.fA;
                    // Index3D.kA = 0;
                    // Index3D.kAH = 0;
                    // Index3D.fA = 0;

                    // /* Find the value of Delta */
                    // Delta = InterpValue(&Index3D, DeltaMtxP, DeltaMtx2DP, DeltaMtx2DHP, DeltaMtx1DP, DeltaMtx1DHP, DeltaNumEl2D, DeltaNumEl1D);

                    // /* Set indees of MN in Index3D for finding a 1D element */
                    // Index3D.kMN = 0;
                    // Index3D.kMNH = 0;
                    // Index3D.fMN = 0;

                    // /* Finds the value of maximum corrected thrust */
                    // FNcMax = InterpValue(&Index3D, FNcMaxContMtxP, DeltaMtx2DP, DeltaMtx2DHP, DeltaMtx1DP, DeltaMtx1DHP, DeltaNumEl2D, DeltaNumEl1D);;

                    // /* Calculates the percent value of thrust */
                    // FNpc = FNpc / FNcMax / Delta;

// printf("\n\nAltitude = %f",Altitude);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// printf("\nMN = %f",MN);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// printf("\nIndex3D.kA = %d",Index3D.kA);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// printf("\nIndex3D.kAH = %d",Index3D.kAH);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// printf("\nIndex3D.kMN = %d",Index3D.kMN);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// printf("\nIndex3D.kMNH = %d",Index3D.kMNH);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// printf("\nIndex3D.kRPM = %d",Index3D.kRPM);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// printf("\nIndex3D.kRPMH = %d",Index3D.kRPMH);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// printf("\nDelta = %f",Delta);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// printf("\nFNcMax = %f",FNcMax);//PARA TESTE SOMENTE!!APAGAR DEPOIS

                // }

				/* CALCULATION OF REFERENCE FROM THRUST PERCENTUAL INPUT */

				/* Finds value of RPM reference from FNpc reference - requires defintion of sqrtT */
				InterpInd3DRPM(Altitude, MN, FNpc, AltLinVecP, MNLinVecP, FNperContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Alt_Elem, MN_Elem, Fn_Elem, &Index3D);
				RPMRef = InterpValue(&Index3D, NcFANContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
// printf("Inside PIMMRF.c: RPMRef = %f, FNpc = %f, NDes = %f, Theta = %f\n",RPMRef, FNpc, NDes, Theta);
				RPMRef = RPMRef * NDes*sqrtT(Theta);

				/* REFERENCE FILTER */

				/* Calculates the Acceleration Schedule Value for current Nc */
				ASRef = ASRefFind(NcVecP, ASVecP, Nc, Tt2, As_Elem, TSTD, NDes);

				/* Calculates the Deceleration Schedule Value for current Nc */
				DSRef = ASRefFind(NcVecP, DSVecP, Nc, Tt2, As_Elem, TSTD, NDes);

				/* Calculates the minimum value between ASRef and NMAX */
				MinRef = Min(ASRef, NMax);

				/* Calculates the minimum value between the previous result and the actual RPM reference */
				MinRef = Min(MinRef, RPMRef);
//printf("%f %f\n", Tt2, MinRef);
				/* Calculates the maximum value between the previous result and DSRef */
				MinRef = Max(MinRef,DSRef);
// printf("RPM=%f AsRef=%f DSRef=%f RPMRef=%f MinRef=%f\n",RPM,ASRef,DSRef,RPMRef,MinRef);
//MinRef = RPMRef;
/* SUGESTÃO PARA CORRIGIR UNDERSHOOT */
//MinRef = Max(MinRef,0.92 * RPM);

				/* LOGIC FOR SMOOTH REFERENCE TRANSITION */

				/* Keeps the reference from exerting step transition if intended by the user */
				RefRampSR(ContStartP, &MinRef, RefRampValue, TICK);

				/* CALCULATION OF KpN AND KiN */

				/* Finds 3D indexes necessary for interpolation of controller gains */
				InterpInd3DRPM(Altitude, MN, Nc, AltLinVecP, MNLinVecP, NcFANContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Alt_Elem, MN_Elem, Fn_Elem, &Index3D);

				/* Calculates gains used in PI controllers */
				KpN = InterpValue(&Index3D, N_KpMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
				KiN = InterpValue(&Index3D, N_KiMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);

				/* CALCULATION OF ERRORS */

				/* Calculates Rotation Speed Error and Back Calculation Error*/
				eNk = MinRef - RPM;
// 				eTt4k = TJ1200_TT5MAX - Tt4;
                eTt4k = Tt4Max - Tt4;
				eBNk1 = uNk1 - urk1;
				eBTk1 = uTt4k1 - urk1;

				/* CALCULATES PI CONTROL SIGNALS */

				/* Calculates Control Signal for Rotation Speed and Tt4 Protection */
				PIControl(KiN, KpN, KbN, Tsample, ITermNk1, eNk, eNk1, eBNk1, &PIOutN);
				uNk = PIOutN.u;
				PIControl(KiTt4, KpTt4, KbT, Tsample, ITermTk1, eTt4k, eTt4k1, eBTk1, &PIOutT);
				uTt4k = PIOutT.u;
// printf("KiTt4k=%f KpTt4=%f KbT=%f, Tsample=%f\n\n", KiTt4, KpTt4, KbT, Tsample);
				/* Calculates the Minimum Value for Control Signal Considering RU Parameter */
				uRUk = RUMin * Pt3;

				/* IMPLEMENTS MIN-MAX LOGIC */

				/* Min Logic */
				uMMk = Min(uNk, uTt4k);

				/* Max Logic */
				uMMk = Max(uMMk, uRUk);

				/* IDENTIFIES THE ACTIVE CONTROLLER */
				/*	1 - Power Management
					2 - Tt4 Limiter
					3 - RU Limiter
					9 - Output Different From Any Calculated Signal
				*/

				/* Updates Signals in String */
				*(CSVPointer + 1) = uNk;
				*(CSVPointer + 2) = uTt4k;
				*(CSVPointer + 3) = uRUk;

				/* Identifies Active Controller */
				Active = ActiveCont(CSVPointer, LastSignalIndex, uMMk);

// printf("\n\n%f uMMk", uMMk);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// printf("\n%f uNk argument(s).", uNk);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// printf("\n%f uTt4k argument(s).", uTt4k);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// printf("\n%f uRUk argument(s).", uRUk);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// printf("\n%f uRUk argument(s).", Active);//PARA TESTE SOMENTE!!APAGAR DEPOIS

                /* FUEL PUMP SATURATION */
                uMMk = Min(uMMk,WfMax);
                uMMk = Max(uMMk,0);

				/* COMPUTES ACTUATION SIGNAL OUTPUT */

				/* Computes the actuation signal at desired output */
				// fValue = uMMk;
				Wf = uMMk;
// printf("Inside PIMMRF.c: Tt2 = %f, Tt4 = %f, Tt4Max = %f, RPM = %f, FNpc = %f\n",Tt2, Tt4, Tt4Max, RPM, FNpc);
// printf("Inside PIMMRF.c: eTt4k = %f, eNk = %f\n", eTt4k, eNk);
// printf("Inside PIMMRF.c: uTt4k = %f, uNk = %f, uMMk = %f, uRUk = %f, Active = %f\n\n", uTt4k, uNk, uMMk, uRUk, Active);

//*********************************
// printf("Alt = %.2f; ",Altitude);
// printf("MN = %.2f; ",MN);
// printf("Tt2 = %.2f;\n",Tt2);

//printf("FNpc = %.2f; ", FNpc);
// floating NDES = NDes;
// printf("NDES = %.2f; ",NDES);
// floating NMAX = NMax;
// printf("NMax = %.2f;\n",NMAX);

// printf("RPMRef = %.2f;\n",RPMRef);
// printf("ASRef = %.2f; ",ASRef);
// printf("MinRef = %.2f; ",MinRef);
// printf("RPM = %.2f;\n\n",RPM);
//*****************************//

//printf("e(k-1) = %.2f; ",eNk1);
//printf("I(k-1) = %.2f; ",ITermNk1);
//printf("Kp = %.2f; ",KpN);
//printf("Ki = %.2f; ",KiN);
//printf("Kb = %.2f; ",KbN);

/*
printf("uNk = %.2f",uNk);
printf("uTt4k = %.2f",uTt4k);
printf("uRUk = %.2f",uRUk);
printf("uMMk = %.2f",uMMk);
printf("fValue = %.2f",fValue);
printf("Active = %.2f\n",Active);
*/



				/* MEMORY UPDATE FOR PI CONTROLLER */

				/* Delayed control variables */
				uNk1 = PIOutN.u;
				urk1 = uMMk;
				ITermNk1 = PIOutN.Iout;
				uTt4k1 = PIOutT.u;
				ITermTk1 = PIOutT.Iout;
				eNk1 = eNk;
				eTt4k1 = eTt4k;

			}
			else
			{

				/* Initiates fuel percentual value with the proper value */
				ContStartP->WfPerc = ContConst->WfPerc;

				/* Updates fValue according to the option chosen for LeverMode */
				// fValue = FNpc * WfMax;
				Wf = FNpc * WfMax;

				/* Calculates OpenLoop Signal */
				//OpenLoop(ContStartP, FuelFlow, &fValue, EngineShutDown,&OpenLoopReset);
				// if(OpenLoop(ContStartP, FuelFlow, &fValue)){
				if(OpenLoopSR(ContStartP, WfTrigger, &Wf)){
							/* Sets the values of keys according to manual input */
							// ManualKeys(&digital, &keys, EngineShutDown, &fValue);
							ManualKeysSR(&digital, &keys, &Wf);
				}

// //O if A SEGUIR EH SOMENTE PARA VALIDAR O ACENDIMENTO SEM A RAMPA! APAGAR DEPOIS!!!
// if (RPM > 4000) {
// //Deactivates Ignition
// digital.bits.igniter = 0;
// }

			}

		}

	}

	/*If Emergency is active, fValue receives null value*/
/*
	if (EngineShutDown == 1) {
		fValue = 0;
	}
*/

	/* Returns the fuel flow value */
	// ContOutputP->fValue = fValue;
	ContOutputP->Wf = Wf;
	ContOutputP->Active = Active;
	ContOutputP->RPMRef = RPMRef;
	ContOutputP->MinRef = MinRef;
	ContStartP->WfTrigger = WfTrigger;
	ContOutputP->StartComplete = StartComplete;	/* Flag indicating if stargin sequence is complete */
	ContStartP->Current_key_start = Current_key_start;
	ContStartP->Old_key_start = Old_key_start;
	*(digitalP) = digital.out;

	/* Updates calculated memory variables */
	ContOutputP->uNk1 = uNk1;
	ContOutputP->urk1 = urk1;
	ContOutputP->ITermNk1 = ITermNk1;
	ContOutputP->uTt4k1 = uTt4k1;
	ContOutputP->ITermTk1 = ITermTk1;
	ContOutputP->eNk1 = eNk1;
	ContOutputP->eTt4k1 = eTt4k1;
	ContOutputP->eBNk1 = eBNk1;
	ContOutputP->eBTk1 = eBTk1;

	/* Updates EngineShutDown variable */
	//ContOutputP->EngineShutDown = EngineShutDown;


}
