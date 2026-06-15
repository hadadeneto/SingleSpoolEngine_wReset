/*
 * EngineModel.c
 *
 *  Created on: Dec 13, 2019
 *      Author: anton
 */

/* -------------------------------------------------- */
/* INCLUDE - T-MATS & PWLM                            */
/* (To be usedi in MATLAB and TMATS simulations only) */
/* -------------------------------------------------- */

//#include "mex.h"

/* -------------------------------------------------- */

/* Math lib */
#include <math.h>

/*Common includes for both model and controller*/
#include "../FADEC_Defines_H/Env_SampTime.h"
#include "../FADEC_Functions_H/Ambient_TMATS.h"
#include "../FADEC_Functions_H/functions_TMATS.h"
#include "../FADEC_Functions_H/MtxIntFunctions.h"		//Also MtxInitFunctions.c
#include "../FADEC_Defines_H/Interpolation_Types.h"
// #include "../FADEC_Functions_H/LinMtxFunctions.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"

/* Model includes */
#include "../FADEC_Defines_H/Model_Types.h"
#include "../FADEC_Functions_H/PeripheralDyn.h"

/* Controller includes */
#include "../FADEC_Defines_H/Control_Types.h"
#include "../FADEC_Functions_H/ControlFunctions.h"
#include "../FADEC_Defines_H/IO_Types.h"
#include "../FADEC_Functions_H/StartingFunctions.h"
#include "../FADEC_Defines_H/FaultSim_Types.h"
#include "../HIL_Functions_H/FaultSimFunctions.h"
#include "../HIL_Functions_H/Nozzle_TMATS.h"
#include "../HIL_Functions_H/SubIdle.h"


// void EngineModel(struct AmbientPars *AmbientP, struct EngineOutput *EngOutputP, floating WfIn,
				//  floating Altitude, floating MN, floating dT, floating Mwm, int Ignition, floating *NcMtxP, floating *Pt21MtxP, floating *Pt3MtxP, floating *Pt5MtxP, floating *Pt6MtxP,
				//  floating *Tt21MtxP, floating *Tt3MtxP, floating *Tt4MtxP, floating *Tt5MtxP, floating *Tt6MtxP, floating *WfMtxP, floating *AMtxP, floating *BMtxP,
				//  floating *Pt21DMtxP, floating *Pt3DMtxP, floating *Pt5DMtxP, floating *Pt6DMtxP, floating *Tt21DMtxP, floating *Tt3DMtxP, floating *Tt4DMtxP, floating *Tt5DMtxP, floating *Tt6DMtxP,
				//  floating *NcFANMapMtxP, floating *WcFANMapMtxP, floating *WcFANStallMtxP, floating *PRFANMapMtxP, floating *PRFANStallMtxP, floating *EffFANMapMtxP,
				//  floating *NcHPCMapMtxP, floating *WcHPCMapMtxP, floating *WcHPCStallMtxP, floating *PRHPCMapMtxP, floating *PRHPCStallMtxP, floating *EffHPCMapMtxP,
				//  floating *NcHPTMapMtxP, floating *WcHPTMapMtxP, floating *PRHPTMapMtxP, floating *EffHPTMapMtxP, struct EnginePars *ParsP,
				//  floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
				//  floating *MapFAN2DP, floating *MapFAN2DHP, floating *MapFAN1DP, floating *MapFAN1DHP, floating *MNLinVecP,
				//  floating *MapHPC2DP, floating *MapHPC2DHP, floating *MapHPC1DP, floating *MapHPC1DHP,
				//  floating *AwmMtxP, floating *AshMtxP, floating *BwmMtxP, floating *BshMtxP, floating *RPMwmMtxP, floating *RPMshMtxP,
				//  floating *NcFANshMtxP, floating *Pt21shMtxP, floating *Pt21wmMtxP,
				//  floating *Pt21DshMtxP, floating *Pt21DwmMtxP, floating *Pt3shMtxP, floating *Pt3wmMtxP,
				//  floating *Pt3DshMtxP, floating *Pt3DwmMtxP, floating *Pt5shMtxP, floating *Pt5wmMtxP, floating *Pt5DshMtxP, floating *Pt5DwmMtxP, floating *Pt6shMtxP, floating *Pt6wmMtxP,
				//  floating *Pt6DshMtxP, floating *Pt6DwmMtxP, floating *Tt21shMtxP, floating *Tt21wmMtxP, floating *Tt21DshMtxP, floating *Tt21DwmMtxP,
				//  floating *Tt3shMtxP, floating *Tt3wmMtxP, floating *Tt3DshMtxP, floating *Tt3DwmMtxP, floating *Tt4shMtxP, floating *Tt4wmMtxP, floating *Tt4CshMtxP, floating *Tt4DshMtxP, floating *Tt4DwmMtxP,
				//  floating *Tt5shMtxP, floating *Tt5wmMtxP, floating *Tt5DshMtxP, floating *Tt5DwmMtxP, floating *Tt6shMtxP, floating *Tt6wmMtxP, floating *Tt6DshMtxP, floating *Tt6DwmMtxP, floating *WfshMtxP, floating *WfwmMtxP,
				//  EngineFaults *FaultsP, struct SensedPars *SensorsP,
				//  floating Ts)

void EngineModel(struct AmbientPars *AmbientP, struct EngineOutput *EngOutputP, floating WfIn,
				 floating Altitude, floating MN, floating dT, floating Mwm, int Ignition, floating *NcMtxP, floating *Pt21MtxP, floating *Pt3MtxP, floating *Pt5MtxP, floating *Pt6MtxP,
				 floating *Tt21MtxP, floating *Tt3MtxP, floating *Tt4MtxP, floating *Tt5MtxP, floating *Tt6MtxP, floating *WfMtxP, floating *AMtxP, floating *BMtxP,
				 floating *Pt21DMtxP, floating *Pt3DMtxP, floating *Pt5DMtxP, floating *Pt6DMtxP, floating *Tt21DMtxP, floating *Tt3DMtxP, floating *Tt4DMtxP, floating *Tt5DMtxP, floating *Tt6DMtxP,
				 floating *NcFANMapMtxP, floating *WcFANMapMtxP, floating *WcFANStallMtxP, floating *PRFANMapMtxP, floating *PRFANStallMtxP, floating *EffFANMapMtxP,
				 floating *NcHPCMapMtxP, floating *WcHPCMapMtxP, floating *WcHPCStallMtxP, floating *PRHPCMapMtxP, floating *PRHPCStallMtxP, floating *EffHPCMapMtxP,
				 floating *NcHPTMapMtxP, floating *WcHPTMapMtxP, floating *PRHPTMapMtxP, floating *EffHPTMapMtxP, struct EnginePars *ParsP,
				 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
				 floating *MapFAN2DP, floating *MapFAN2DHP, floating *MapFAN1DP, floating *MapFAN1DHP, floating *MNLinVecP,
				 floating *MapHPC2DP, floating *MapHPC2DHP, floating *MapHPC1DP, floating *MapHPC1DHP,
				 floating *AwmMtxP, floating *AshMtxP, floating *BwmMtxP, floating *BshMtxP, floating *RPMwmMtxP, floating *RPMshMtxP,
				 floating *NcFANshMtxP, floating *Pt21shMtxP, floating *Pt21wmMtxP,
				 floating *Pt21DshMtxP, floating *Pt21DwmMtxP, floating *Pt3shMtxP, floating *Pt3wmMtxP,
				 floating *Pt3DshMtxP, floating *Pt3DwmMtxP, floating *Pt5shMtxP, floating *Pt5wmMtxP, floating *Pt5DshMtxP, floating *Pt5DwmMtxP, floating *Pt6shMtxP, floating *Pt6wmMtxP,
				 floating *Pt6DshMtxP, floating *Pt6DwmMtxP, floating *Tt21shMtxP, floating *Tt21wmMtxP, floating *Tt21DshMtxP, floating *Tt21DwmMtxP,
				 floating *Tt3shMtxP, floating *Tt3wmMtxP, floating *Tt3DshMtxP, floating *Tt3DwmMtxP, floating *Tt4shMtxP, floating *Tt4wmMtxP, floating *Tt4CshMtxP, floating *Tt4DshMtxP, floating *Tt4DwmMtxP,
				 floating *Tt5shMtxP, floating *Tt5wmMtxP, floating *Tt5DshMtxP, floating *Tt5DwmMtxP, floating *Tt6shMtxP, floating *Tt6wmMtxP, floating *Tt6DshMtxP, floating *Tt6DwmMtxP, floating *WfshMtxP, floating *WfwmMtxP,
				 EngineFaults *FaultsP, struct SensedPars *SensorsP,
				 floating Ts, int ExtFPModel, int FlightStart)

{

	floating NumEl2D;
	floating NumEl1D;

	//Declars pointer for 3D interpolation indexes
	InterpIndex3D Index3D;

	/*-------------------------*/
	/*  ENGINE MODEL VARIABLES */
	/*-------------------------*/

// 	/* Declares and initiates the smapling time Ts */
// 	floating Ts = 0.001 * TICK;
//
//     /* If external tick is not zero, must follow external syncronization */
//     if(ExtTick > 0){
//         Ts = 0.001 * ExtTick;
//     }

	/* Declared Internal Variables */

	/* Station 2 */
	floating P0;
    floating Ts2 = 0;
	floating Tt2 = 288.25;
	floating Pt2 = 101325;
	floating Tt2SL = 288.15;
	floating Pt2SL = 101325;
	floating W2, WcFAN;
	floating N2c;
	floating Vf = 0;

	/*Station 21*/
	floating Pt21;
	floating Tt21;
	floating N21c;
	floating W21, WcHPC; //Compressor Corrected Mass Flow
	floating PRFAN; //Fan Pressure Ratio
	floating PRStallFAN; //Stall Pressure Ratio at a given corrected rotation speed
	floating SMFAN; //Fan Stall Margin
	floating BPFAN; //Fan By Pass Ratio

	/* Station 3 */
	floating Pt3;
	floating Tt3;
	floating PRHPC; //Compressor Pressure Ratio
	floating SMHPC; //Compressor Stall Margin
	floating PRStallHPC; //Stall Pressure Ratio at a given corrected rotation speed

	/* Station 4 */
	floating Tt4;
	/* Wf is used for model calculations */
	floating Wf;

	/* Station 5 */
	floating Pt5;
	floating Tt5;

	/* Station 6 */
	floating Pt6;
	floating Tt6;

	/* Station 8 */
	floating W8;
	floating Ps8;
	floating Ts8;
	floating MNth;
	floating Vth;
	floating Vsth;
	floating FARth;
	floating Fn;
	floating Fg;

	/* Rotation Speed - must be a static variable */
	static floating RPM = 0;

	/* Rotation speed at design point */
	floating NDes;

	/* Correction parameters */
	floating Theta = 0;
	floating Delta = 0;
	floating ThetaSL = 0;
	floating DeltaSL = 0;
	floating sqrTheta = 0;
	floating sqrThetaSL = 0;

	/* Dummy Constant */
	floating DummyConst = 0;

	/* Sensed variables */

	/* Station 2 */
	floating Ts2Sensed = EngOutputP->Ts2Sensed;
	/* Station 3 */
	floating Pt3Sensed = EngOutputP->Pt3Sensed;
	/* Station 4 */
	floating Tt4Sensed = EngOutputP->Tt4Sensed;

	/*State-Space Variables*/
	floating A;
	floating Attc = ParsP->TTCTimeConst;
	floating Apsens = ParsP->PSensTimeConst;
	floating Afp = ParsP->FuelPumpTimeConstant;
	floating B;
	floating Bttc = -1 * ParsP->TTCTimeConst;
	floating Bpsens = -1 * ParsP->PSensTimeConst;
	floating Bfp = -1 * ParsP->FuelPumpTimeConstant;
	floating Ad;
	floating Adttc;
	floating Adpsens;
	floating Adfp;
	floating Bd;
	floating Bdttc;
	floating Bdpsens;
	floating Bdfp;
	floating Pt21D;
	floating Pt21ss;
	floating Pt3D;
	floating Pt3ss;
	floating Pt5D;
	floating Pt5ss;
	floating Pt6D;
	floating Pt6ss;
	floating Tt21D;
	floating Tt21ss;
	floating Tt3D;
	floating Tt3ss;
	floating Tt4D;
	floating Tt4ss;
	floating Tt5D;
	floating Tt5ss;
	floating Tt6D;
	floating Tt6ss;
	floating Wfss;

	/* Correction Matrices for Sea-Level */
	floating PNSL;
	floating PNdotSL;
	floating PuSL;
	floating PTSL;
	floating PPSL;

	/* Correction Matrices for current altitude */
	floating PN;
	floating PNdot;
	floating Pu;
	floating PT;
	floating PP;

	/*Ambient Parameters*/
	AmbientPars Ambient;
	NozzlePars	Nozzle;

	int kAux;
	int kHAux;
	int fAux;

	/* Starging Parameters */
	static EngineStart Starting;
	static int statusIgn = 0;

	/* Oil Pressure Initial Value */
	floating POil;
    floating PFuel;
    floating Vibration;

	/* Fuel Pump Output - filtered */
	floating WfOutfp = EngOutputP->WfPumpOut;

	/*--------------------*/
	/* MODEL CALCULATIONS */
	/*--------------------*/

	/* Loads MN elements and Fn elements */
	floating Fn_Elem = ParsP->Fn_Elem;
	floating MN_Elem = ParsP->MN_Elem;
	floating NcFANMAP_Elem = ParsP->NcFANMap_Elem;
	floating WcFANMAP_Elem = ParsP->WcFANMap_Elem;
	floating NcHPCMAP_Elem = ParsP->NcHPCMap_Elem;
	floating WcHPCMAP_Elem = ParsP->WcHPCMap_Elem;
	floating Wc_per_Nc_FANMAP = WcFANMAP_Elem / NcFANMAP_Elem ;
	floating Wc_per_Nc_HPCMAP = WcHPCMAP_Elem / NcHPCMAP_Elem;

	NumEl2D = MN_Elem * Fn_Elem;
	NumEl1D = Fn_Elem;

	/* Design Point rotation speed */
	NDes = ParsP->NDes;

	/* Throat Nozzle */
	floating Ath_Nozzle = ParsP->Ath;

	/* CALCULATION OF AMBIENT PARAMETERS */

	/* Reads Altitude Values */
	Ambient.Alt = Altitude;
	Ambient.MN = MN;
	Ambient.dT = dT;

	/* MACH NUMBER FOR WINDMILL MODEL CALCULATIONS */
	floating MwmIn = Mwm;

	/* ENGINE START - FLIGHT OR GROUND */

	/*If FlightStart == 1, the engine must start during flight with windmilling*/
	if (FlightStart == 1)
	{
		/* Updates windmilling Mach number with flight Mach number */
		MwmIn = MN;
	}

	/* FUEL PUMP FIRST ORDER MODEL */

	/* Calculation of discrete coefficients - fuel pump */
	Adfp = exp(Afp * Ts);
	Bdfp = (Adfp - 1) * Bfp / Afp;

	/* The routine FirstOrderSensor performs a 1st order filter and is suitable to be used
	with sensors and fuel pump first order models */
	FirstOrderSensor(WfIn, &WfOutfp, Bdfp);

	/* If external fuel pump model is used, the internal model is ignored */
	if (ExtFPModel == 1)
	{
		/* Sets fuel pump output as fuel pump input */
		WfOutfp = WfIn;
	}


	/* Reads initial value of rotation speed and fuel flow for further calculations.
	   These values are initially stored in EngineOutputP. Also, sets the reset flag
	   of StartingEngine to 1 in order for internal reset execution */
	if (EngOutputP->ICCalc == 0)
	{
		RPM = EngOutputP->RPM;
		WfOutfp = WfIn;
		Starting.Reset = 1;
	}

	/* Updates value of Wf - WfOutfp corresponds to fuel pump model output */
	//Wf = WfIn;
	Wf = WfOutfp;

	/* AMBIENT CALCULATIONS */

	/* Calculates the values of total temperature, total pressure and flight speed */
	Ambient_TMATS(&Ambient);
	P0 = Ambient.Ps;
    Ts2 = Ambient.Ts;
	Tt2 = Ambient.Tt;
	Pt2 = Ambient.Pt;
	Vf = Ambient.Vf;

	/* Sets all ambient variables to zero for performing sea-level calculations */
	Ambient.Alt = 0;
	Ambient.MN = MN;
	Ambient.dT = 0;

	/* Calculates sea-level parameters */
	Ambient_TMATS(&Ambient);
	Tt2SL = Ambient.Tt;
	Pt2SL = Ambient.Pt;

	/* CALCULATION OF USED CORRECTED PARAMETERS */

	/* Calculates the values of Theta and Delta at sea level for operating line correction */
	ThetaSL = Tt2SL / TSTD;
	DeltaSL = Pt2SL / PSTD;

	/* Calculates the values of Theta and Delta */
	Theta = Tt2 / TSTD;
	Delta = Pt2 / PSTD;

	/* Calculates the squred root of the theta values - requires definition of sqrtT */
	sqrTheta = sqrtT(Theta);
	sqrThetaSL = sqrtT(ThetaSL);

	/* Calculates the correction matices for sea-level */
	PNSL = sqrThetaSL;
	PNdotSL = DeltaSL;
	PuSL = DeltaSL * sqrThetaSL;
	PTSL = ThetaSL;
	PPSL = DeltaSL;

	/* Calculates the correction matices for sea-level */
	PN = sqrTheta;
	PNdot = Delta;
	Pu = Delta * sqrTheta;
	PT = Theta;
	PP = Delta;

	/* Calculates the Value of N2c */
	N2c = RPM / sqrTheta;
	N2c = N2c / NDes;

	/* CALCULATION OF PARAMETERS USED IN MODEL */

	/* Finds 3D indexes necessary for interpolation of controller gains */
	InterpInd3DRPM(DummyConst, MN, N2c, &DummyConst, MNLinVecP, NcMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, DUMMY_ELEM, MN_Elem, Fn_Elem, &Index3D);
	NumEl2D = MN_Elem * Fn_Elem;
	NumEl1D = Fn_Elem;
//printf("\nN2c=%f Index3D.fRPM=%f StartingOn=%d WhichModel=%d\n", N2c, Index3D.fRPM, Starting.StartingOn, EngOutputP->WhichModel);

	switch (EngOutputP->WhichModel)
	{
	case 0:

		/* Evaluates if the engine is at stargin phase - what is true if fRPM is negative */
		if (Index3D.fRPM < 0.001)
		{
			/* sets fRPM to zero in order for the first elements of state-matrices to be selected */
			Index3D.fRPM = 0;
			Starting.StartingOn = 1;
		}
		else
		{
			Starting.StartingOn = 0;
			EngOutputP->WhichModel = 1;
		}

		break;

	case 1:

		/* Verifies if RPM value is lower than blow out RPM */
		if (RPM < ParsP->RPM_BOut)
		{
			/* code */
			Starting.StartingOn = 1;
			Starting.statusIgn = 0;
			EngOutputP->WhichModel = 0;
		}

		break;

	default:
		break;
	}

// /* Evaluates if the engine is at stargin phase - what is true if fRPM is negative */
// if (Index3D.fRPM < 0.001)
// {
// 	/* sets fRPM to zero in order for the first elements of state-matrices to be selected */
// 	Index3D.fRPM = 0;
// 	Starting.StartingOn = 1;
// }
// else
// {
// 	Starting.StartingOn = 0;
// }

	/* Calculates POil */
	POil = ParsP->POILMODEL;

    /*Calculate PFuel*/
    PFuel = ParsP->PFUELMODEL;

    /* Calcuates Vibration */
    Vibration = ParsP->VIBMODEL;

	/* Calculates parameters used in model */
    B = InterpValue(&Index3D, BMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
    A = InterpValue(&Index3D, AMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	Pt21D = InterpValue(&Index3D, Pt21DMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	Pt3D = InterpValue(&Index3D, Pt3DMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	Pt5D = InterpValue(&Index3D, Pt5DMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	Pt6D = InterpValue(&Index3D, Pt6DMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	Tt21D = InterpValue(&Index3D, Tt21DMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	Tt3D = InterpValue(&Index3D, Tt3DMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	Tt4D = InterpValue(&Index3D, Tt4DMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	Tt5D = InterpValue(&Index3D, Tt5DMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	Tt6D = InterpValue(&Index3D, Tt6DMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	Pt21ss = InterpValue(&Index3D, Pt21MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
    Pt3ss = InterpValue(&Index3D, Pt3MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	Pt5ss = InterpValue(&Index3D, Pt5MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	Pt6ss = InterpValue(&Index3D, Pt6MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	Tt21ss = InterpValue(&Index3D, Tt21MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	Tt3ss = InterpValue(&Index3D, Tt3MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	Tt4ss = InterpValue(&Index3D, Tt4MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	Tt5ss = InterpValue(&Index3D, Tt5MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	Tt6ss = InterpValue(&Index3D, Tt6MtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
    Wfss = InterpValue(&Index3D, WfMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);

    /* Executes the starting routine */
	if(Starting.StartingOn){

		/* Executes the engine starting routine */
		Starting.WfOut = Wf;
		Starting.WfssIn = Wfss;

		//Starting.Tt5 = Tt2;
		Starting.Pt2 = Pt2;
		Starting.Pt21ss = Pt21ss;
		Starting.Pt3ss = Pt3ss;
		Starting.Pt5ss = Pt5ss;
		Starting.Pt6ss = Pt6ss;
		Starting.Tt2 = Tt2;
		Starting.Tt21ss = Tt21ss;
		Starting.Tt3ss = Tt3ss;
		Starting.Tt4ss = Tt4ss;
		Starting.Tt5ss = Tt5ss;
		Starting.Tt6ss = Tt6ss;
		Starting.POil = POil;
		Starting.IgnitOn = Ignition;
		Starting.Ncss = InterpValue(&Index3D, NcMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
		Starting.Nc = N2c;
		Starting.statusIgn = statusIgn;

		Starting.WfIn = Wf;

		/* Complete starting model */
        // StartingModel(ParsP, &Starting, AshMtxP, BshMtxP, WfshMtxP, NcFANshMtxP,
		// 			 AwmMtxP, BwmMtxP, WfwmMtxP, RPMwmMtxP, MwmIn, MNLinVecP,
		// 			 Pt3shMtxP, Tt4shMtxP, Pt3DshMtxP, Tt4DshMtxP,
		// 			 Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, RPM, sqrTheta,
		// 			 MN_Elem, Fn_Elem, NumEl1D, NumEl2D, Pt2, Tt2,
		// 			 PN, PNSL, PNdot, PNdotSL, Pu, PuSL, Ts);

		StartingModel(ParsP, &Starting, MNLinVecP,
					  AwmMtxP, AshMtxP, BwmMtxP, BshMtxP, RPMwmMtxP, RPMshMtxP,
					  NcFANshMtxP, Pt21shMtxP, Pt21wmMtxP,
					  Pt21DshMtxP, Pt21DwmMtxP, Pt3shMtxP, Pt3wmMtxP,
					  Pt3DshMtxP, Pt3DwmMtxP, Pt5shMtxP, Pt5wmMtxP, Pt5DshMtxP, Pt5DwmMtxP, Pt6shMtxP, Pt6wmMtxP,
					  Pt6DshMtxP, Pt6DwmMtxP, Tt21shMtxP, Tt21wmMtxP, Tt21DshMtxP, Tt21DwmMtxP,
					  Tt3shMtxP, Tt3wmMtxP, Tt3DshMtxP, Tt3DwmMtxP, Tt4shMtxP, Tt4wmMtxP, Tt4CshMtxP, Tt4DshMtxP, Tt4DwmMtxP,
					  Tt5shMtxP, Tt5wmMtxP, Tt5DshMtxP, Tt5DwmMtxP, Tt6shMtxP, Tt6wmMtxP, Tt6DshMtxP, Tt6DwmMtxP, WfshMtxP, WfwmMtxP,
					  Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, RPM, MwmIn, sqrTheta,
					  MN_Elem, Fn_Elem, NumEl1D, NumEl2D, Pt2, Tt2,
					  PN, PNSL, PNdot, PNdotSL, Pu, PuSL, Ts);

		A = Starting.A;
		B = Starting.B;
		Pt21D = Starting.Pt21D;
		Pt3D = Starting.Pt3D;
		Pt5D = Starting.Pt5D;
		Pt6D = Starting.Pt6D;
		Tt21D = Starting.Tt21D;
		Tt3D = Starting.Tt3D;
		Tt4D = Starting.Tt4D;
		Tt5D = Starting.Tt5D;
		Tt6D = Starting.Tt6D;
		Pt21ss = Starting.Pt21ss;
		Pt3ss = Starting.Pt3ss;
		Pt5ss = Starting.Pt5ss;
		Pt6ss = Starting.Pt6ss;
		Tt21ss = Starting.Tt21ss;
		Tt3ss = Starting.Tt3ss;
		Tt4ss = Starting.Tt4ss;
		Tt5ss = Starting.Tt5ss;
		Tt6ss = Starting.Tt6ss;

		/* Updates POil */
		POil = Starting.POil;

		/*Calculates the difference between Tt5 and Tt4*/
        Starting.DeltaTt = Tt4ss - Tt5ss;

        /* Engine starting model */
		// StartingEngine(&Starting, ParsP,
        //                AwmMtxP, AshMtxP, BwmMtxP,
        //                BshMtxP, RPMwmMtxP, RPMshMtxP, WfshMtxP,
        //                Tt4CshMtxP, Tt4DshMtxP, Tt4shMtxP,
        //                &A, &B, &Tt4D, RPM, NDes,
        //                MN, MwmIn, MNLinVecP, MN_Elem,
        //                1.0, &DummyConst, 1.0,
        //                N2c, NcMtxP, Fn_Elem,
        //                Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,
        //                PNdotSL, PuSL, PNSL, PTSL,
        //                PNdot, Pu, PN, PT,
        //                Ts);

		/* Updates the value of Wfss */
		Wfss = Starting.WfssOut;
		statusIgn = Starting.statusIgn;
		Wf = Starting.WfOut;
        Tt4ss = Starting.Tt4ss;

	}

// printf("\nA = %f, B = %f ",A,B);//TESTE SOMENTE!! APAGAR DEPOIS!!
// printf("\nDelta = %f, Theta = %f ,sqrTheta = %f ",Delta, Theta,sqrTheta);//TESTE SOMENTE!! APAGAR DEPOIS!!
// printf("\nDeltaSL = %f, ThetaSL = %f ,sqrThetaSL = %f ",DeltaSL, ThetaSL,sqrThetaSL);//TESTE SOMENTE!! APAGAR DEPOIS!!
// printf("\nPNdotSL = %f, PNSL = %f ,PuSL = %f ",PNdotSL, PNSL, PuSL);//TESTE SOMENTE!! APAGAR DEPOIS!!
// printf("\nPNdot = %f, PN = %f ,Pu = %f ",PNdot, PN, Pu);//TESTE SOMENTE!! APAGAR DEPOIS!!
// printf("\nfA = %f, kA = %d,kAH = %d ",Index3D.fA, Index3D.kA,Index3D.kAH);//TESTE SOMENTE!! APAGAR DEPOIS!!
// printf("\nfMN = %f, kMN = %d,kMNH = %d ",Index3D.fMN, Index3D.kMN,Index3D.kMNH);//TESTE SOMENTE!! APAGAR DEPOIS!!
// printf("\nfRPM = %f, kRPM = %d,kRPMH = %d ",Index3D.fRPM, Index3D.kRPM,Index3D.kRPMH);//TESTE SOMENTE!! APAGAR DEPOIS!!

	/* Corrects the calculated parameters for sea level and corresponding MN */
	B = 1/PNdotSL * B * PuSL;
	A = 1/PNdotSL * A * PNSL;
 	Pt21D = 1 / PPSL * Pt21D * PuSL;
	Pt3D = 1 / PPSL * Pt3D * PuSL;
	Pt5D = 1 / PPSL * Pt5D * PuSL;
 	Pt6D = 1 / PPSL * Pt6D * PuSL;
	Tt21D = 1 / PTSL * Tt21D * PuSL;
	Tt3D = 1 / PTSL * Tt3D * PuSL;
	Tt4D = 1 / PTSL * Tt4D * PuSL;
	Tt5D = 1 / PTSL * Tt5D * PuSL;
 	Tt6D = 1 / PTSL * Tt6D * PuSL;
 	Pt21ss = Pt21ss / PPSL;
	Pt3ss = Pt3ss / PPSL;
	Pt5ss = Pt5ss / PPSL;
 	Pt6ss = Pt6ss / PPSL;
	Tt21ss = Tt21ss / PTSL;
	Tt3ss = Tt3ss / PTSL;
	Tt4ss = Tt4ss / PTSL;
	Tt5ss = Tt5ss / PTSL;
 	Tt6ss = Tt6ss / PTSL;
	Wfss = Wfss / PuSL;

	/* Calculates the absolute values from the corresponding corrected values*/
	B = PNdot * B / Pu;
	A = PNdot * A / PN;
 	Pt21D = PP * Pt21D / Pu;
	Pt3D = PP * Pt3D / Pu;
 	Pt6D = PP * Pt6D / Pu;
	Tt21D = PT * Tt21D / Pu;
	Tt3D = PT * Tt3D / Pu;
	Tt4D = PT * Tt4D / Pu;
	Tt5D = PT * Tt5D / Pu;
 	Tt6D = PT * Tt6D / Pu;
 	Pt21ss = Pt21ss * PP;
	Pt3ss = Pt3ss * PP;
	Pt5ss = Pt5ss * PP;
 	Pt6ss = Pt6ss * PP;
	Tt21ss = Tt21ss * PT;
	Tt3ss = Tt3ss * PT;
	Tt4ss = Tt4ss * PT;
	Tt5ss = Tt5ss * PT;
 	Tt6ss = Tt6ss * PT;
	Wfss = Wfss * Pu;

// printf("\nRPM = %f; A = %f; B = %f ",RPM,A,B);//TESTE SOMENTE!! APAGAR DEPOIS!!
// printf("\nA = %f, B = %f ",A,B);//TESTE SOMENTE!! APAGAR DEPOIS!!
// printf("\nTs = %f;", Ts);//TESTE SOMENTE!! APAGAR DEPOIS!!

    /* Calculation of discrete coefficients */
    Ad = exp(A * Ts);
    Bd = (Ad - 1) * B / A;

	/* Calculation of discrete coefficients - sensors */
	Adttc = exp(Attc * Ts);
	Bdttc = (Adttc - 1) * Bttc / Attc;

	/* Calculation of discrete coefficients - sensors */
	Adpsens = exp(Apsens * Ts);
	Bdpsens = (Adpsens - 1) * Bpsens / Apsens;

    /* CALCULATION OF STATE VARIABLE */
// printf("\nN2c = %f",N2c);//TESTE SOMENTE!! APAGAR DEPOIS!!
// printf("\nRPM = %f + %f * (%f - %f)",RPM,Bd,Wf,Wfss);//TESTE SOMENTE!! APAGAR DEPOIS!!
// printf("\nWfss = %f, Wf = %f", Wfss, Wf);
//printf("Engine Model: WfOutfp = %f, WfIn = %f\n", WfOutfp, WfIn);
//floating RPMOut = RPM;
    RPM = RPM + Bd * (Wf - Wfss);


	/* CALCULATION OF OBSERVED VARIABLES */

	Pt21 = Pt21ss + Pt21D * (Wf - Wfss);
	Pt3 = Pt3ss + Pt3D * (Wf - Wfss);
//printf("\nPt3 = %f = %f + %f * (%f - %f)", Pt3, Pt3ss, Pt3D, Wf, Wfss);
	Pt5 = Pt5ss + Pt5D * (Wf - Wfss);
 	Pt6 = Pt6ss + Pt6D * (Wf - Wfss);
	Tt21 = Tt21ss + Tt21D * (Wf - Wfss);
	Tt3 = Tt3ss + Tt3D * (Wf - Wfss);
	Tt4 = Tt4ss + Tt4D * (Wf - Wfss);
	Tt5 = Tt5ss + Tt5D * (Wf - Wfss);
 	Tt6 = Tt6ss + Tt6D * (Wf - Wfss);

	if (Starting.StartingOn) {

		// // Tt21 = Starting.Tt21;
		// // Tt3 = Starting.Tt3;

		// /* DeltaTt obtained inside the sub-idle model*/
        // Tt5 = Tt4 - Starting.DeltaTt;
		// // Tt6 = Starting.Tt6;
 		// POil = Starting.POil;

        // /* The following pressure values are used for calculation of map
        //  * inferior limit */
		// // Pt21 = Starting.Pt21ss;
		// // Pt3 = Starting.Pt3ss;
		// // Pt5 = Starting.Pt5ss;
		// // Pt6 = Starting.Pt6ss;

	}
//printf("\n1: Starting.StartingOn = %d, Starting.StatusIgn = %d, Pt3 = %f", Starting.StartingOn, Starting.statusIgn, Pt3);
	/* CALCULATION OF ADDITIONAL VITAL PARAMETERS */

    /* FAN */

	/* Calculates pressure ratio */
	PRFAN = Pt21 / Pt2;

	/* Calculates the corrected mass flow from fan map */
	InterpInd3DRPM(DummyConst, N2c, PRFAN, &DummyConst, NcFANMapMtxP, PRFANMapMtxP, MapFAN2DP, MapFAN2DHP, MapFAN1DP, MapFAN1DHP, DUMMY_ELEM, NcFANMAP_Elem, Wc_per_Nc_FANMAP, &Index3D);
	WcFAN = InterpValue(&Index3D, WcFANMapMtxP, MapFAN2DP, MapFAN2DHP, MapFAN1DP, MapFAN1DHP, WcFANMAP_Elem, Wc_per_Nc_FANMAP);
//printf("N2c = %f; PRFAN = %f\n", N2c, PRFAN);
	/* Caluclates the stall pressure ratio at the current corrected rotation speed */
	Index3D.kRPM = Index3D.kMN;
	Index3D.kRPMH = Index3D.kMNH;
	Index3D.fRPM = Index3D.fMN;
	Index3D.kMN = 0;
	Index3D.kMNH = 0;
	Index3D.fMN = 0.0;
	PRStallFAN = InterpValue(&Index3D, PRFANStallMtxP, MapFAN1DP, MapFAN1DHP, MapFAN1DP, MapFAN1DHP, NcFANMAP_Elem, NcFANMAP_Elem);

	/* Calculates the total air mass flow */
	W2 = WcFAN * Delta / sqrTheta;

	/*Calculates the stall margin at fan map*/
	SMFAN = (PRStallFAN - PRFAN) / PRFAN;

	/* COMPRESSOR */

    /* Calculates corrected speed - requires definition of sqrtT */
    N21c = RPM / NDes / sqrtT(Tt21 / TSTD);

	/* Calculates pressure ratio */
    PRHPC = Pt3 / Pt21;

	/* Calculates the corrected mass flow from fan map */
	InterpInd3DRPM(DummyConst, N21c, PRHPC, &DummyConst, NcHPCMapMtxP, PRHPCMapMtxP, MapHPC2DP, MapHPC2DHP, MapHPC1DP, MapHPC1DHP, DUMMY_ELEM, NcHPCMAP_Elem, Wc_per_Nc_HPCMAP, &Index3D);
	WcHPC = InterpValue(&Index3D, WcHPCMapMtxP, MapHPC2DP, MapHPC2DHP, MapHPC1DP, MapHPC1DHP, WcHPCMAP_Elem, Wc_per_Nc_HPCMAP);
//printf("WcFAN = %f; Delta = %f, sqrTheta = %f\n", WcFAN, Delta, sqrTheta);
	/* Caluclates the stall pressure ratio at the current corrected rotation speed */
	Index3D.kRPM = Index3D.kMN;
	Index3D.kRPMH = Index3D.kMNH;
	Index3D.fRPM = Index3D.fMN;
	Index3D.kMN = 0;
	Index3D.kMNH = 0;
	Index3D.fMN = 0.0;
	PRStallHPC = InterpValue(&Index3D, PRHPCStallMtxP, MapHPC1DP, MapHPC1DHP, MapHPC1DP, MapHPC1DHP, NcHPCMAP_Elem, NcHPCMAP_Elem);

	/* Calculates the core air mais flow - requires definition of sqrtT */
	W21 = WcHPC * (Pt21 / PSTD) / sqrtT(Tt21 / TSTD);

	/* Calculates the compressor stall margin */
	SMHPC = (PRStallHPC - PRHPC) / PRHPC;

	/* Calculates the bypass ratio */
	BPFAN = W2 / W21;

	/* NOZZLE */

	/* Calculation of total mass flow */
	W8 = WcFAN * Delta / sqrTheta + Wf;
	FARth = Wf / W8;
//printf("W8 = %f; Wf = %f\n", W8, Wf);
    /* Corrects the value of air flows in case engine is starting */
    if (Starting.StartingOn) {

        /* Calculate the flow values respecting the sub-idle rotation speed */
        W21 = 0 + (W21 - 0) / Starting.Ncss * Starting.Nc;
        W2 = 0 + (W2 - 0) / Starting.Ncss * Starting.Nc;
        WcFAN = 0 + (WcFAN - 0) / Starting.Ncss * Starting.Nc;
        WcHPC = 0 + (WcHPC - 0) / Starting.Ncss * Starting.Nc;
        W8 = W2 + Wf;
        FARth = Wf/W8;

        /* Calculates the bypass ratio if W21 is larger than zero */
        if(W21 > 0){
            BPFAN = W21/W2;
        };

        // /* Updates the pressure vaues for the calculated ones */
        // Pt21 = Starting.Pt21;
        // Pt3 = Starting.Pt3;
        // Pt5 = Starting.Pt5;
        // Pt6 = Starting.Pt6;

        /* Update pressure ratio values */
        PRFAN = Pt21 / Pt2;
        PRHPC = Pt3 / Pt21;

    }
//printf("\n2: Starting.StartingOn = %d, Pt3 = %f", Starting.StartingOn, Pt3);
	/* Computes the nozzle inputs */
	Nozzle.FAR = FARth;
	//Nozzle.Pt = Pt5;
	//Nozzle.Tt = Tt5;
	Nozzle.Pt = Pt6;
	Nozzle.Tt = Tt6;
	Nozzle.Wt = W8;
	Nozzle.Ath = Ath_Nozzle;
	Nozzle.Pamb = P0;

	/* Calculates nozzle outputs */
	Nozzle_TMATS(&Nozzle);

	/* Calculates the net thrust */
	Fg = Nozzle.Fg;
	Vth = Nozzle.Vj;
	MNth = Nozzle.MN;
	Fn = Fg - WcFAN * Delta / sqrTheta * Vf;
//printf("Fn = %f =  %f - %f * %f / %f * %f\n", Fn, Fg, WcFAN, Delta, sqrTheta, Vf);
// printf("\nTt4Sensed = %f + %f * (%f - %f)", Tt4Sensed, Bdttc,Tt4,Tt4Sensed);

	/* Updates sensor values */
	FirstOrderSensor(Ts2, &Ts2Sensed, Bdttc);
	FirstOrderSensor(Pt3, &Pt3Sensed, Bdpsens);
	FirstOrderSensor(Tt4, &Tt4Sensed, Bdttc);

	/* Sets sensor values to engine outputs if first calculation is made */
	if (EngOutputP->ICCalc == 0)
	{
		Ts2Sensed = Ts2;
		Pt3Sensed = Pt3;
		Tt4Sensed = Tt4;
	}

	/* Updates outputs */
	EngOutputP->W2 = W2;
	EngOutputP->Ps2 = P0;
	EngOutputP->Pt2 = Pt2;
    EngOutputP->Ts2 = Ts2Sensed;//Ts2; /*Ts2Sensed is the filtered value - sensor model*/
	EngOutputP->Tt2 = Tt2;
	EngOutputP->W2c = WcFAN;
	EngOutputP->N2c = N2c;

	EngOutputP->W21 = W21;
	EngOutputP->Pt21 = Pt21;
	EngOutputP->Tt21 = Tt21;
	EngOutputP->W21c = WcHPC;
	EngOutputP->N21c = N21c;
	EngOutputP->PRFAN = PRFAN;
	EngOutputP->SMFAN = SMFAN;
	EngOutputP->BPFAN = BPFAN;

	EngOutputP->Pt3 = Pt3Sensed;//Pt3; /*Pt3Sensed is the filtered value - sensor model*/
	EngOutputP->Tt3 = Tt3;
	EngOutputP->PRHPC = PRHPC;
	EngOutputP->SMHPC = SMHPC;

	EngOutputP->Pt4 = Pt3;
	EngOutputP->Tt4 = Tt4Sensed;//Tt4; /*Tt4Sensed is the filtered value - sensor model*/
	// EngOutputP->Wf = Wf;
	EngOutputP->Wf = WfIn;
	/* For memory purposes and comparison only */
	EngOutputP->WfPumpOut = WfOutfp;
//printf("\nWf = %f; WfOutfp = %f",Wf,WfOutfp);
	EngOutputP->Pt5 = Pt5;
	EngOutputP->Tt5 = Tt5;

	EngOutputP->Pt6 = Pt6;
	EngOutputP->Tt6 = Tt6;

	EngOutputP->Fn = Fn;
	EngOutputP->Fg = Fg;
	EngOutputP->W8 = W8;
	EngOutputP->V8 = Vth;
	EngOutputP->MN8 = MNth;
//printf("\nRPM=%f RPMOut=%f",RPM,RPMOut);
	EngOutputP->RPM = RPM;//RPMOut;
	EngOutputP->POil = POil;
    EngOutputP->PFuel = PFuel;
    EngOutputP->Vibration = Vibration;

	EngOutputP->Ts2Sensed = Ts2Sensed;
	EngOutputP->Pt3Sensed = Pt3Sensed;
	EngOutputP->Tt4Sensed = Tt4Sensed;
//printf("Engine Model: Wf = %f, Tt4 = %f, StartingOn = %d\n", Wf, Tt4Sensed, Starting.StartingOn);
//printf("\nPt3 = %f; Pt3Sensed = %f",Pt3,Pt3Sensed);
	/* Authorizes the controller to actuate and indicates the IC no longer need to be calculated */
	if (EngOutputP->ICCalc == 0)
	{
		EngOutputP->ICAuthorize = 1;
		EngOutputP->ICCalc = 1;
	}
}

