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
#include "QSMCFunctions.h"
#include "IO_Types.h"
#include "StartingFunctions.h"
#include "DigitalOutDefs.h"

//void QSMCMinMaxGEJ85(struct ControlStart *ContStartP, struct ControllerInput *ContInputP, struct ControllerOutput *ContOutputP, unsigned int *digitalP, unsigned int *keysP, double *NcFANContMtxP, double *FNperContMtxP, double *ThetaMtxP, double *DeltaMtxP, double *AMtxP, double *BMtxP, double *CTMtxP, double *DTMtxP, double *Tt5MtxP, double *WfMtxP, struct QSMCInput *QSMCInP)
void QSMCMinMaxGEJ85(struct ControlStart *ContStartP, struct ControllerInput *ContInputP, struct ControllerOutput *ContOutputP, unsigned int *digitalP, unsigned int *keysP, double *NcFANContMtxP, double *FNperContMtxP, double *ThetaMtxP, double *DeltaMtxP, double *AMtxP, double *BMtxP, double *CTMtxP, double *DTMtxP, double *Tt5MtxP, double *WfMtxP, double Tsample)
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

	/* Errors, control signals and disturbances */
	//double SNk;
	//double STt5k;
	double uNk;
	//double DuNk;
	//double vNk;
	double uTt5k;
	//double DuTt5k;
	//double vTt5k;
	double uMMk;
	double uRUk;
	//double dNk;
	//double dTt5k;
	

	/* Previous samples of errors and control signals */
	//static double DRPMk1 = 0;
	//static double DuNk1 = 0;
	//static double vNk1 = 0;
	//static double urk1 = 0;
	//static double ITermNk1 = 0;
	//static double DuTt5k1 = 0;
	//static double vTt5k1 = 0;
	//static double dNk1 = 0;
	//static double dTt5k1 = 0;
	//static double ITermTk1 = 0;
	//static double eNk1 = 0;
	//static double eTt4k1 = 0;
	//static double eBNk1 = 0;
	//static double eBTk1 = 0;

	/* Active controller flag */
	double Active;
	double CalcSigVec[] = { 100, 100, 100, 100 };
	double LastSignalIndex = 3;
	double *CSVPointer = &CalcSigVec;

	/* Structures for controllers */
	static QSMCInput QSMCInPx;
	static QSMCInput QSMCInPy;
	static QSMCInput QSMCInPEmpty = { 0 };


	/* Controller Gains */
	double A;
	double Ad;
	double B;
	double Bd;
	double CT;
	double DT;
	double Ac;
	double Bc;
	double CTc;
	double DTc;
	//double GN = GEJ85_GN;
	//double EpsN = GEJ85_EPSN;
	//double RhoN = GEJ85_RHON;
	//double GT = GEJ85_GT;
	//double EpsT = GEJ85_EPST;
	//double RhoT = GEJ85_RHOT;
	//double KiN;
	//double KpN;
	//double KbN = GEJ85_KBN;
	//double KbT = GEJ85_KBT;
	//double KpTt4 = GEJ85_KPTT4;
	//double KiTt4 = GEJ85_KITT4;

	/* Matrices used for reference and gain calculations */
	//double N_KiMtx[GEJ85_TOTAL_ELEM];
	//double N_KpMtx[GEJ85_TOTAL_ELEM];
	double NcFANContMtx[GEJ85_TOTAL_ELEM];
	double FNperContMtx[GEJ85_TOTAL_ELEM];
	double Mtx2D[GEJ85_MN_ELEM * GEJ85_FN_ELEM];
	double Mtx2DH[GEJ85_MN_ELEM * GEJ85_FN_ELEM];
	double Mtx1D[GEJ85_FN_ELEM];
	double Mtx1DH[GEJ85_FN_ELEM];

	/* Vectors used in for interpolation during gains caluclation */
	double AltLinVec[] = { 0, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000, 12000 };
	double MNLinVec[] = { 0, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.95 };
	double NcVec[] = { 0.55, 0.6, 0.7, 0.8, 0.9, 0.99 };
	//double ASVec[] = { 1.09, 1.08, 1.06, 1.08, 1.09, 1.011 };
    
	//double ASVec[] = { 1.12, 1.12, 1.12, 1.12, 1.12, 1.011 };
    double ASVec[] = { 1.163, 1.163, 1.163, 1.19, 1.15, 1.011 };
    
	double ASRef;
	double MinRef;

	double NumEl2D = GEJ85_MN_ELEM * GEJ85_FN_ELEM;
	double NumEl1D = GEJ85_FN_ELEM;

	///* Structures for PI outputs */
	//PIOutput PIOutN;
	//PIOutput PIOutT;

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
	double DRPMk;

	/* Stations variables */
	double Tt2;
	double Pt2;
	double Pt3;
	double Wfss;
	double Wfssc;
	double Tt5;
	double DTt5k;
	double Tt5ss;
	double Tt5ssc;
	

	/* Correction parameter */
	double Nc;
	double Theta;
	double Delta;
	double ThetaSL;
	double DeltaSL;

	/* Declares pointer for 3D interpolation indexes */
	InterpIndex3D Index3D;

	/* Starging Parameters */
	double POil;


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

		/* Resets controller structs with zero values */
		QSMCInPx = QSMCInPEmpty;
		QSMCInPy = QSMCInPEmpty;

		//DRPMk1 = 0;
		//DuNk1 = 0;
		//vNk1 = 0;
		//DuTt5k1 = 0;
		//vTt5k1 = 0;
		//dNk1 = 0;
		//dTt5k1 = 0;
		//ITermTk1 = 0;
		//eNk1 = 0;
		//eTt4k1 = 0;
		//eBNk1 = 0;
		//eBTk1 = 0;
		RefInit = 0;
		fValue = 0;

		/* Indicates that reference ramp is to be reset */
		RefRampReset = 1;
		OilPresSRP.Reset = 1;
		FuelSRP.Reset = 1;

		/* Sets reset flag to zero */
		ContInputP->Reset = 0;

	}

	///* Saves reset signal in the QSCM input structure */
	//QSMCInP.Reset = ContInputP->Reset;

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
	Tt2 = ContInputP->Tt2;
	Pt2 = ContInputP->Pt2;
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

		/* Sets the vlaues of controllers structs with zero values */
		QSMCInPx = QSMCInPEmpty;
		QSMCInPy = QSMCInPEmpty;

		/* Sets previous steady points measurements with values of RPM and Tt5 */
		QSMCInPx.xe = RPM;
		QSMCInPy.xe = RPM;
		QSMCInPx.ye = Tt5;
		QSMCInPy.ye = Tt5;

		/*FOR TEST ONLY - ERASE LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
		/***************/
		/* Memory reset for state-space controller */
		//QSMCInPx.Dxk = RPM;
		//QSMCInPx.Duk = fValue;
		//QSMCInPx.dxk1 = 0;
		//QSMCInPx.dyk = 0;
		/* Memory reset for ovserved variable controller */

		//QSMCInPx.Dxk = RPM;
		//QSMCInPx.Duk = fValue;
		//QSMCInPx.dxk1 = 0;
		//QSMCInPx.dyk = 0;

		//QSMCInPy.Dxk = RPM;
		//QSMCInPy.Duk = fValue;
		//QSMCInPy.dxk1 = 0;
		//QSMCInPy.dyk = 0;
		/***************/

		/*  */
		FuelFlow = fValue;
		RPMRef = RPM;
		MinRef = RPM;
		RefInit = RPM;
		Active = 0;

		/* Indicates that start has been completed */
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
			//DRPMk1 = 0;
			//DuNk1 = 0;
			//vNk1 = 0;
			//DuTt5k1 = 0;
			//vTt5k1 = 0;
			//dNk1 = 0;
			//dTt5k1 = 0;
			//ITermTk1 = fValue;
			FuelFlow = fValue;
			//eNk1 = 0;
			//eTt4k1 = 0;
			RPMRef = RPM;
			MinRef = RPM;
			RefInit = RPM;
			Active = 0;
		}
		else
		{
			
			/*---------------*/
			/* CONTROL LOGIC */
			/*---------------*/

			if(LeverMode == GEJ85_CLOOP)
			{
				/* CALCULATION OF USED NORMALIZED PARAMETERS */

				/* Calculates the Value of Theta */
				Theta = Tt2 / TSTD;
				Delta = Pt2 / PSTD;

				/* Calculates the Value of Nc */
				Nc = RPM / sqrt(Theta);
				Nc = Nc / GEJ85_NDES;

				/* CALCULATION OF DELTA AND THETA VALUES AT SEA-LEVEL */

				/* Finds 3D indexes necessary for interpolation of Delta and Theta values at Sea-Level altitude */
				//InterpInd3DRPM(0, MN, Nc, &AltLinVec, &MNLinVec, NcFANContMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, GEJ85_ALT_ELEM, GEJ85_MN_ELEM, GEJ85_FN_ELEM, &Index3D);
				InterpInd3DRPM(0, 0, MN, &AltLinVec, &AltLinVec, &MNLinVec, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, 1, GEJ85_ALT_ELEM, GEJ85_MN_ELEM, &Index3D);
				/* Calculates the values of Delta and Theta for correction of engine parameters */
				DeltaSL = InterpValue(&Index3D, DeltaMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);
				ThetaSL = InterpValue(&Index3D, ThetaMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);

				/* CALCULATION OF REFERENCE FROM THRUST PERCENTUAL INPUT */

				/* Finds value of RPM reference from FNpc reference */
				InterpInd3DRPM(Altitude, MN, FNpc, &AltLinVec, &MNLinVec, FNperContMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, GEJ85_ALT_ELEM, GEJ85_MN_ELEM, GEJ85_FN_ELEM, &Index3D);
				RPMRef = InterpValue(&Index3D, NcFANContMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);
				RPMRef = RPMRef * GEJ85_NDES*sqrt(Theta);


				/* REFERENCE FILTER */

				/* Calculates the Acceleration Schedule Value for current Nc */
				ASRef = ASRefFind(&NcVec, &ASVec, Nc, Tt2, GEJ85_AS_ELEM, TSTD, GEJ85_NDES);

				/* Calculates the minimum value between ASRef and NMAX */
				MinRef = Min(ASRef, GEJ85_NMAX);

				/* Calculates the minimum value between the previous result and the actual RPM reference */
				MinRef = Min(MinRef, RPMRef);
                
//MinRef = RPMRef; //TESTE!! APAGAR DEPOIS

				/* LOGIC FOR SMOOTH REFERENCE TRANSITION */

				/* Keeps the reference from exerting step transition if intended by the user */
				RefRamp(&MinRef, &RefInit, &RefRampReset, GEJ85_REFRAMP, TICK);

				/* Finds 3D indexes necessary for interpolation of controller gains */
				//InterpInd3DRPM(Altitude, MN, Nc, &AltLinVec, &MNLinVec, NcFANContMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, GEJ85_ALT_ELEM, GEJ85_MN_ELEM, GEJ85_FN_ELEM, &Index3D);
				InterpInd3DRPM(0, MN, Nc, &AltLinVec, &MNLinVec, NcFANContMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, GEJ85_ALT_ELEM, GEJ85_MN_ELEM, GEJ85_FN_ELEM, &Index3D);

				/* CALCULATION OF STATE-SPACE COEFFICIENTS AND STEADY VALUES USED BY CONTROLLER */

				/* Calculates state-space coefficients used in QSMC controllers */
				A = InterpValue(&Index3D, AMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);
				B = InterpValue(&Index3D, BMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);
				CT = InterpValue(&Index3D, CTMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);
				DT = InterpValue(&Index3D, DTMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);
				Tt5ss = InterpValue(&Index3D, Tt5MtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);
				Wfss = InterpValue(&Index3D, WfMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);
				
				/* Corrects the parameters A, B, C and D to Sea-Level */
				Ac = A * sqrt(ThetaSL) / DeltaSL;
				Bc = B * DeltaSL;
				CTc = CT / sqrt(ThetaSL);
				DTc = DT * DeltaSL / sqrt(ThetaSL);
				Tt5ssc = Tt5ss / ThetaSL;
				Wfssc = Wfss / DeltaSL / sqrt(ThetaSL);

				/* Corrects the parameters A, B, C and D from corrected values in order to match flight conditions */
				A = Ac / sqrt(Theta) * Delta;
				B = Bc / Delta;
				CT = CTc * sqrt(Theta);
				DT = DTc / Delta * sqrt(Theta);
				Tt5ss = Tt5ssc * Theta;
				Wfss = Wfssc * Delta * sqrt(Theta);
                
				/* Calculates discrete values of A and B */
				Ad = exp(A * Tsample);
				Bd = (Ad - 1) * B / A;

				///* CALCULATION OF KpN AND KiN */

				///* Finds 3D indexes necessary for interpolation of controller gains */
				//InterpInd3DRPM(Altitude, MN, Nc, &AltLinVec, &MNLinVec, NcFANContMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, GEJ85_ALT_ELEM, GEJ85_MN_ELEM, GEJ85_FN_ELEM, &Index3D);
				//
				///* Calculates gains used in PI controllers */
				//KpN = InterpValue(&Index3D, N_KpMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);
				//KiN = InterpValue(&Index3D, N_KiMtxP, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, NumEl2D, NumEl1D);

				/* CALCULATION OF ERRORS */

				/* Calculates Rotation Speed Error and Back Calculation Error*/
				//SNk = GN * (MinRef - RPM);
				//STt4k = GT * (GEJ85_TT4MAX - Tt5);
				//eTt4k = GEJ85_TT5MAX - Tt5;
				//eBNk1 = uNk1 - urk1;
				//eBTk1 = uTt4k1 - urk1;

				/* COMPUTES INPUT DATA FOR STATE VARIABLE CONTROLLER */

				/* Computes input value */
				QSMCInPx.A = Ad;
				QSMCInPx.B = Bd;
				QSMCInPx.C = CT;
				QSMCInPx.D = DT;
				QSMCInPx.xss = RPM;
				QSMCInPx.yss = Tt5ss;
				QSMCInPx.uss = Wfss;
				QSMCInPx.x = RPM;
				QSMCInPx.y = Tt5;
				QSMCInPx.uIn = fValue;
				QSMCInPx.T = Tsample;

				/* Computes reference and constants */
				QSMCInPx.Ref = MinRef; 
				QSMCInPx.G = GEJ85_GN; 
				QSMCInPx.q = GEJ85_QN; 
				QSMCInPx.Eps = GEJ85_EPSN; 
				QSMCInPx.Rho = GEJ85_RHON;

//				/*FOR TEST ONLY - ERASE LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
//				/***************/
//				Ad = exp(-4.9243 * 0.001 * TICK);
//				Bd = (Ad - 1) * 2.636787127207325e+05 / (-4.9243);
//				QSMCInPx.A = Ad;
//				QSMCInPx.B = Bd;
//				QSMCInPx.C = -0.021472666982223;
//				QSMCInPx.D = 4.811687983977808e+03;
//				QSMCInPx.xss = 0;
//				QSMCInPx.yss = 0;
//				QSMCInPx.uss = 0;
//				QSMCInPx.x = RPM;
//				QSMCInPx.y = Tt5;
//				QSMCInPx.uIn = fValue;
//				QSMCInPx.T = 0.001 * TICK;
////				QSMCInPx.Ref = FNpc;
//				/***************/

				/* CALCULATES RPM CONTROL SIGNAL */

				QSMCx(&QSMCInPx);
				uNk = QSMCInPx.uOut;

				/* COMPUTES INPUT DATA FOR OBSERVED VARIABLE CONTROLLER */

				/* Computes input value */
				QSMCInPy.A = Ad;
				QSMCInPy.B = Bd;
				QSMCInPy.C = CT;
				QSMCInPy.D = DT;
				QSMCInPy.xss = RPM;
				QSMCInPy.yss = Tt5ss;
				QSMCInPy.uss = Wfss;
				QSMCInPy.x = RPM;
				QSMCInPy.y = Tt5;
				QSMCInPy.uIn = fValue;
				QSMCInPy.T = Tsample;

				/* Computes reference and constants */
				QSMCInPy.Ref = GEJ85_TT5MAX;
				QSMCInPy.G = GEJ85_GT;
				QSMCInPy.q = GEJ85_QT;
				QSMCInPy.Eps = GEJ85_EPST;
				QSMCInPy.Rho = GEJ85_RHOT;
				QSMCInPy.Kia = GEJ85_KIAT;

				///*FOR TEST ONLY - ERASE LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
				///***************/
				//Ad = exp(-4.9243 * 0.001 * TICK);
				//Bd = (Ad - 1) * 2.636787127207325e+05 / (-4.9243);
				//QSMCInPy.A = Ad;
				//QSMCInPy.B = Bd;
				//QSMCInPy.C = -0.021472666982223;
				//QSMCInPy.D = 4.811687983977808e+03;
				//QSMCInPy.xss = 0;
				//QSMCInPy.yss = 0;
				//QSMCInPy.uss = 0;
				//QSMCInPy.x = RPM;
				//QSMCInPy.y = Tt5;
				//QSMCInPy.uIn = fValue;
				//QSMCInPy.T = 0.001 * TICK;
				//QSMCInPy.Ref = FNpc;
				///***************/
							   
				/* CALCULATES Tt5 CONTROL SIGNAL */
				
				QSMCy(&QSMCInPy);
				uTt5k = QSMCInPy.uOut;

				/* CALCULATES PI CONTROL SIGNALS */

				///* Calculates Control Signal for Rotation Speed and Tt4 Protection */
				//PIControl(KiN, KpN, KbN, Tsample, ITermNk1, eNk, eNk1, eBNk1, &PIOutN);
				//uNk = PIOutN.u;
				//PIControl(KiTt4, KpTt4, KbT, Tsample, ITermTk1, eTt4k, eTt4k1, eBTk1, &PIOutT);
				//uTt4k = PIOutT.u;

				/* Calculates the Minimum Value for Control Signal Considering RU Parameter */
				uRUk = GEJ85_RUMIN * Pt3;

				/* IMPLEMENTS MIN-MAX LOGIC */

				/* Min Logic */
				uMMk = Min(uNk, uTt5k);
				
				/* Max Logic */
				uMMk = Max(uMMk, uRUk);
//uMMk = uNk; //TESTE!! APAGAR DEPOIS

				/*FOR TEST ONLY - ERASE LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
				/***************/
				//uMMk = uTt5k;
				/***************/

				/* Updates memory data for further calculation of QSMC controller - "Anti-Windiup" method */
				QSMCr(&QSMCInPx, uMMk);
				QSMCr(&QSMCInPy, uMMk);

				/*FOR TEST ONLY - ERASE LATER!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
				/***************/
				//uMMk = uTt5k;
				//*QSMCx = *QSMInxP;
				//*QSMCy = *QSMInyP;
				/***************/

				/* IDENTIFIES THE ACTIVE CONTROLLER */
				/*	1 - Power Management
					2 - Tt4 Limiter
					3 - RU Limiter
					9 - Output Different From Any Calculated Signal
				*/
				
				/* Updates Signals in String */
				*(CSVPointer + 1) = uNk;
				*(CSVPointer + 2) = uTt5k;
				*(CSVPointer + 3) = uRUk;

				/* Identifies Active Controller */
				Active = ActiveCont(CSVPointer, LastSignalIndex, uMMk);

				/* COMPUTES ACTUATION SIGNAL OUTPUT */

				/* Computes the actuation signal at desired output */
				fValue = uMMk;

				///* MEMORY UPDATE FOR PI CONTROLLER */

				///* Delayed control variables */
				//uNk1 = PIOutN.u;
				//urk1 = uMMk;
				//ITermNk1 = PIOutN.Iout;
				//uTt4k1 = PIOutT.u;
				//ITermTk1 = PIOutT.Iout;
				//eNk1 = eNk;
				//eTt4k1 = eTt4k;

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
	ContOutputP->QSMC_dx = QSMCInPy.dxk1;
	ContOutputP->QSMC_dy = QSMCInPy.dyk;
	ContOutputP->QSMC_ux = uNk;
	ContOutputP->QSMC_uy = uTt5k;

	*(digitalP) = digital.out;

}
