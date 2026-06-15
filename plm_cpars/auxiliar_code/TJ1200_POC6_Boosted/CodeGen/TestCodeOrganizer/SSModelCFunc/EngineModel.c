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

#include "mex.h"

/* -------------------------------------------------- */

/* Math lib */
#include <math.h>

/*Common includes for both model and controller*/
#include "Env_SampTime.h"
#include "MtxIntFunctions.h"		//Also MtxInitFunctions.c
#include "Interpolation_Types.h"
#include "LinMtxFunctions.h"

/* Model includes */
#include "Model_Types.h"
#include "PeripheralDyn.h"

/* Controller includes */
#include "Control_Types.h"
#include "ControlFunctions.h"
#include "IO_Types.h"
#include "StartingFunctions.h"
#include "FaultSim_Types.h"
#include "FaultSimFunctions.h"


void EngineModel(struct AmbientPars *AmbientP, struct EngineOutput *EngOutputP, double WfIn,
	double Altitude, double MN, double dT, double Mwm, int Ignition, double *NcMtxP, double *Pt21MtxP, double *Pt3MtxP, double *Pt5MtxP, double *Pt6MtxP,
	double *Tt21MtxP, double *Tt3MtxP, double *Tt4MtxP, double *Tt5MtxP, double *Tt6MtxP, double *WfMtxP, double *AMtxP, double *BMtxP,
	double *Pt21DMtxP, double *Pt3DMtxP, double *Pt5DMtxP, double *Pt6DMtxP, double *Tt21DMtxP, double *Tt3DMtxP, double *Tt4DMtxP, double *Tt5DMtxP, double *Tt6DMtxP,
	double *NcFANMapMtxP, double *WcFANMapMtxP, double *WcFANStallMtxP, double *PRFANMapMtxP, double *PRFANStallMtxP, double *EffFANMapMtxP,
	double *NcHPCMapMtxP, double *WcHPCMapMtxP, double *WcHPCStallMtxP, double *PRHPCMapMtxP, double *PRHPCStallMtxP, double *EffHPCMapMtxP,
	double *NcHPTMapMtxP, double *WcHPTMapMtxP, double *PRHPTMapMtxP, double *EffHPTMapMtxP, struct EnginePars *ParsP,
	double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
	double *MapFAN2DP, double *MapFAN2DHP, double *MapFAN1DP, double *MapFAN1DHP, double *MNLinVecP,
	double *MapHPC2DP, double *MapHPC2DHP, double *MapHPC1DP, double *MapHPC1DHP, 
    double *AwmMtxP, double *AshMtxP, double *BwmMtxP, double *BshMtxP, double *RPMwmMtxP, double *RPMshMtxP, 
    double *Tt4CshMtxP, double *Tt4DshMtxP, double *Tt4shMtxP, double *WfshMtxP,
    EngineFaults *FaultsP, struct SensedPars *SensorsP,
    double Ts)

{

	double NumEl2D;
	double NumEl1D;

	//Declars pointer for 3D interpolation indexes
	InterpIndex3D Index3D;

	/*-------------------------*/
	/*  ENGINE MODEL VARIABLES */
	/*-------------------------*/
	
// 	/* Declares and initiates the smapling time Ts */
// 	double Ts = 0.001 * TICK;
// 
//     /* If external tick is not zero, must follow external syncronization */
//     if(ExtTick > 0){
//         Ts = 0.001 * ExtTick;
//     }
    
	/* Declared Internal Variables */

	/* Station 2 */
	double P0;
    double Ts2 = 0;
	double Tt2 = 288.25;
	double Pt2 = 101325;
	double Tt2SL = 288.15;
	double Pt2SL = 101325;
	double W2, WcFAN;
	double N2c;
	double Vf = 0;

	/*Station 21*/
	double Pt21;
	double Tt21;
	double N21c;
	double W21, WcHPC; //Compressor Corrected Mass Flow
	double PRFAN; //Fan Pressure Ratio
	double PRStallFAN; //Stall Pressure Ratio at a given corrected rotation speed
	double SMFAN; //Fan Stall Margin
	double BPFAN; //Fan By Pass Ratio

	/* Station 3 */
	double Pt3;
	double Tt3;
	double PRHPC; //Compressor Pressure Ratio
	double SMHPC; //Compressor Stall Margin
	double PRStallHPC; //Stall Pressure Ratio at a given corrected rotation speed

	/* Station 4 */
	double Tt4;
	/* Wf is used for model calculations */
	double Wf;

	/* Station 5 */
	double Pt5;
	double Tt5;	

	/* Station 6 */
	double Pt6;
	double Tt6;

	/* Station 8 */
	double W8;
	double Ps8;
	double Ts8;
	double MNth;
	double Vth;
	double Vsth;
	double FARth;
	double Fn;
	double Fg;

	/* Rotation Speed - must be a static variable */
	static double RPM = 0;

	/* Rotation speed at design point */
	double NDes;

	/* Correction parameters */
	double Theta = 0;
	double Delta = 0;
	double ThetaSL = 0;
	double DeltaSL = 0;
	double sqrTheta = 0;
	double sqrThetaSL = 0;

	/* Dummy Constant */
	double DummyConst = 0;

	/* Sensed variables */

	/* Station 2 */
	double Ts2Sensed = EngOutputP->Ts2Sensed;
	/* Station 3 */
	double Pt3Sensed = EngOutputP->Pt3Sensed;
	/* Station 4 */
	double Tt4Sensed = EngOutputP->Tt4Sensed;

	/*State-Space Variables*/
	double A;
	double Attc = ParsP->TTCTimeConst;
	double Apsens = ParsP->PSensTimeConst;
	double Afp = ParsP->FuelPumpTimeConstant;
	double B;
	double Bttc = -1 * ParsP->TTCTimeConst;
	double Bpsens = -1 * ParsP->PSensTimeConst;
	double Bfp = -1 * ParsP->FuelPumpTimeConstant;
	double Ad;
	double Adttc;
	double Adpsens;
	double Adfp;
	double Bd;
	double Bdttc;
	double Bdpsens;
	double Bdfp;
	double Pt21D;
	double Pt21ss;
	double Pt3D;
	double Pt3ss;
	double Pt5D;
	double Pt5ss;
	double Pt6D;
	double Pt6ss;
	double Tt21D;
	double Tt21ss;
	double Tt3D;
	double Tt3ss;
	double Tt4D;
	double Tt4ss;
	double Tt5D;
	double Tt5ss;
	double Tt6D;
	double Tt6ss;
	double Wfss;

	/* Correction Matrices for Sea-Level */
	double PNSL;
	double PNdotSL;
	double PuSL;
	double PTSL;
	double PPSL;

	/* Correction Matrices for current altitude */
	double PN;
	double PNdot;
	double Pu;
	double PT;
	double PP;

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
	double POil;
    double PFuel;
    double Vibration;

	/* Fuel Pump Output - filtered */
	double WfOutfp = EngOutputP->WfPumpOut;

	/*--------------------*/
	/* MODEL CALCULATIONS */
	/*--------------------*/

	/* Loads MN elements and Fn elements */
	double Fn_Elem = ParsP->Fn_Elem;
	double MN_Elem = ParsP->MN_Elem;
	double NcFANMAP_Elem = ParsP->NcFANMap_Elem;
	double WcFANMAP_Elem = ParsP->WcFANMap_Elem;
	double NcHPCMAP_Elem = ParsP->NcHPCMap_Elem;
	double WcHPCMAP_Elem = ParsP->WcHPCMap_Elem;
	double Wc_per_Nc_FANMAP = WcFANMAP_Elem / NcFANMAP_Elem ;
	double Wc_per_Nc_HPCMAP = WcHPCMAP_Elem / NcHPCMAP_Elem;

	NumEl2D = MN_Elem * Fn_Elem;
	NumEl1D = Fn_Elem;

	/* Design Point rotation speed */
	NDes = ParsP->NDes;

	/* Throat Nozzle */
	double Ath_Nozzle = ParsP->Ath;

	/* CALCULATION OF AMBIENT PARAMETERS */

	/* Reads Altitude Values */
	Ambient.Alt = Altitude;
	Ambient.MN = MN;
	Ambient.dT = dT;

	/* FUEL PUMP FIRST ORDER MODEL */

	/* Calculation of discrete coefficients - fuel pump */
	Adfp = exp(Afp * Ts);
	Bdfp = (Adfp - 1) * Bfp / Afp;

	/* The routine FirstOrderSensor performs a 1st order filter and is suitable to be used
	with sensors and fuel pump first order models */
	FirstOrderSensor(WfIn, &WfOutfp, Bdfp);

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

	/* Calculates the squred root of the theta values */
	sqrTheta = sqrt(Theta);
	sqrThetaSL = sqrt(ThetaSL);

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
//mexPrintf("\nN2c=%f Index3D.fRPM=%f StartingOn=%d WhichModel=%d\n", N2c, Index3D.fRPM, Starting.StartingOn, EngOutputP->WhichModel);

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
        
        /*Calculates the difference between Tt5 and Tt4*/
        Starting.DeltaTt = Tt4ss - Tt5ss;
        
        /* Engine starting model */
		StartingEngine(&Starting, ParsP, 
                       AwmMtxP, AshMtxP, BwmMtxP, 
                       BshMtxP, RPMwmMtxP, RPMshMtxP, WfshMtxP,
                       Tt4CshMtxP, Tt4DshMtxP, Tt4shMtxP,
                       &A, &B, &Tt4D, RPM, NDes,
                       MN, Mwm, MNLinVecP, MN_Elem,
                       1.0, &DummyConst, 1.0,
                       N2c, NcMtxP, Fn_Elem,
                       Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,
                       PNdotSL, PuSL, PNSL, PTSL, 
                       PNdot, Pu, PN, PT,
                       Ts);

		/* Updates the value of Wfss */
		Wfss = Starting.WfssOut;
		statusIgn = Starting.statusIgn;
		Wf = Starting.WfOut;
        Tt4ss = Starting.Tt4ss;
                
	}
  
// mexPrintf("\nA = %f, B = %f ",A,B);//TESTE SOMENTE!! APAGAR DEPOIS!!
// mexPrintf("\nDelta = %f, Theta = %f ,sqrTheta = %f ",Delta, Theta,sqrTheta);//TESTE SOMENTE!! APAGAR DEPOIS!!
// mexPrintf("\nDeltaSL = %f, ThetaSL = %f ,sqrThetaSL = %f ",DeltaSL, ThetaSL,sqrThetaSL);//TESTE SOMENTE!! APAGAR DEPOIS!!
// mexPrintf("\nPNdotSL = %f, PNSL = %f ,PuSL = %f ",PNdotSL, PNSL, PuSL);//TESTE SOMENTE!! APAGAR DEPOIS!!
// mexPrintf("\nPNdot = %f, PN = %f ,Pu = %f ",PNdot, PN, Pu);//TESTE SOMENTE!! APAGAR DEPOIS!!
// mexPrintf("\nfA = %f, kA = %d,kAH = %d ",Index3D.fA, Index3D.kA,Index3D.kAH);//TESTE SOMENTE!! APAGAR DEPOIS!!
// mexPrintf("\nfMN = %f, kMN = %d,kMNH = %d ",Index3D.fMN, Index3D.kMN,Index3D.kMNH);//TESTE SOMENTE!! APAGAR DEPOIS!!
// mexPrintf("\nfRPM = %f, kRPM = %d,kRPMH = %d ",Index3D.fRPM, Index3D.kRPM,Index3D.kRPMH);//TESTE SOMENTE!! APAGAR DEPOIS!!

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

// mexPrintf("\nRPM = %f; A = %f; B = %f ",RPM,A,B);//TESTE SOMENTE!! APAGAR DEPOIS!!
// mexPrintf("\nA = %f, B = %f ",A,B);//TESTE SOMENTE!! APAGAR DEPOIS!!
// mexPrintf("\nTs = %f;", Ts);//TESTE SOMENTE!! APAGAR DEPOIS!!

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
// mexPrintf("\nN2c = %f",N2c);//TESTE SOMENTE!! APAGAR DEPOIS!!
// mexPrintf("\nRPM = %f + %f * (%f - %f)",RPM,Bd,Wf,Wfss);//TESTE SOMENTE!! APAGAR DEPOIS!!
// mexPrintf("\nWfss = %f, Wf = %f", Wfss, Wf);
//mexPrintf("Engine Model: WfOutfp = %f, WfIn = %f\n", WfOutfp, WfIn); 
//double RPMOut = RPM;
    RPM = RPM + Bd * (Wf - Wfss);


	/* CALCULATION OF OBSERVED VARIABLES */

	Pt21 = Pt21ss + Pt21D * (Wf - Wfss);
	Pt3 = Pt3ss + Pt3D * (Wf - Wfss);
//mexPrintf("\nPt3 = %f = %f + %f * (%f - %f)", Pt3, Pt3ss, Pt3D, Wf, Wfss);
	Pt5 = Pt5ss + Pt5D * (Wf - Wfss);
 	Pt6 = Pt6ss + Pt6D * (Wf - Wfss);
	Tt21 = Tt21ss + Tt21D * (Wf - Wfss);
	Tt3 = Tt3ss + Tt3D * (Wf - Wfss);
	Tt4 = Tt4ss + Tt4D * (Wf - Wfss);
	Tt5 = Tt5ss + Tt5D * (Wf - Wfss);
 	Tt6 = Tt6ss + Tt6D * (Wf - Wfss);

	if (Starting.StartingOn) {
		
		Tt21 = Starting.Tt21;
		Tt3 = Starting.Tt3;
        /* The line below uses Tt4 calculated inside the sub-idle model*/
// 		Tt4 = Starting.Tt4;
        /* The line below uses Tt5 calculated inside the sub-idle model*/
// 		Tt5 = Starting.Tt5;
        /* The line below uses Tt5 calculated from the temperature difference 
         * DeltaTt obtained inside the sub-idle model*/
        Tt5 = Tt4 - Starting.DeltaTt;
		Tt6 = Starting.Tt6;
 		POil = Starting.POil;
        
        /* The following pressure values are used for calculation of map
         * inferior limit */
		Pt21 = Starting.Pt21ss;
		Pt3 = Starting.Pt3ss;
		Pt5 = Starting.Pt5ss;
		Pt6 = Starting.Pt6ss;

	}
//mexPrintf("\n1: Starting.StartingOn = %d, Starting.StatusIgn = %d, Pt3 = %f", Starting.StartingOn, Starting.statusIgn, Pt3);
	/* CALCULATION OF ADDITIONAL VITAL PARAMETERS */

    /* FAN */

	/* Calculates pressure ratio */
	PRFAN = Pt21 / Pt2;

	/* Calculates the corrected mass flow from fan map */
	InterpInd3DRPM(DummyConst, N2c, PRFAN, &DummyConst, NcFANMapMtxP, PRFANMapMtxP, MapFAN2DP, MapFAN2DHP, MapFAN1DP, MapFAN1DHP, DUMMY_ELEM, NcFANMAP_Elem, Wc_per_Nc_FANMAP, &Index3D);
	WcFAN = InterpValue(&Index3D, WcFANMapMtxP, MapFAN2DP, MapFAN2DHP, MapFAN1DP, MapFAN1DHP, WcFANMAP_Elem, Wc_per_Nc_FANMAP);
//mexPrintf("N2c = %f; PRFAN = %f\n", N2c, PRFAN);    
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

    /* Calculates corrected speed */
    N21c = RPM / NDes / sqrt(Tt21 / TSTD);
    
	/* Calculates pressure ratio */
    PRHPC = Pt3 / Pt21;

	/* Calculates the corrected mass flow from fan map */
	InterpInd3DRPM(DummyConst, N21c, PRHPC, &DummyConst, NcHPCMapMtxP, PRHPCMapMtxP, MapHPC2DP, MapHPC2DHP, MapHPC1DP, MapHPC1DHP, DUMMY_ELEM, NcHPCMAP_Elem, Wc_per_Nc_HPCMAP, &Index3D);
	WcHPC = InterpValue(&Index3D, WcHPCMapMtxP, MapHPC2DP, MapHPC2DHP, MapHPC1DP, MapHPC1DHP, WcHPCMAP_Elem, Wc_per_Nc_HPCMAP);
//mexPrintf("WcFAN = %f; Delta = %f, sqrTheta = %f\n", WcFAN, Delta, sqrTheta);    
	/* Caluclates the stall pressure ratio at the current corrected rotation speed */
	Index3D.kRPM = Index3D.kMN;
	Index3D.kRPMH = Index3D.kMNH;
	Index3D.fRPM = Index3D.fMN;
	Index3D.kMN = 0;
	Index3D.kMNH = 0;
	Index3D.fMN = 0.0;
	PRStallHPC = InterpValue(&Index3D, PRHPCStallMtxP, MapHPC1DP, MapHPC1DHP, MapHPC1DP, MapHPC1DHP, NcHPCMAP_Elem, NcHPCMAP_Elem);

	/* Calculates the core air mais flow */
	W21 = WcHPC * (Pt21 / PSTD) / sqrt((Tt21 / TSTD));

	/* Calculates the compressor stall margin */
	SMHPC = (PRStallHPC - PRHPC) / PRHPC;

	/* Calculates the bypass ratio */
	BPFAN = W2 / W21;
    
	/* NOZZLE */

	/* Calculation of total mass flow */
	W8 = WcFAN * Delta / sqrTheta + Wf;
	FARth = Wf / W8;
//mexPrintf("W8 = %f; Wf = %f\n", W8, Wf);    
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
        
        /* Updates the pressure vaues for the calculated ones */
        Pt21 = Starting.Pt21;
        Pt3 = Starting.Pt3;
        Pt5 = Starting.Pt5;
        Pt6 = Starting.Pt6;
        
        /* Update pressure ratio values */
        PRFAN = Pt21 / Pt2;
        PRHPC = Pt3 / Pt21;

    }
//mexPrintf("\n2: Starting.StartingOn = %d, Pt3 = %f", Starting.StartingOn, Pt3);
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
//mexPrintf("Fn = %f =  %f - %f * %f / %f * %f\n", Fn, Fg, WcFAN, Delta, sqrTheta, Vf);
// mexPrintf("\nTt4Sensed = %f + %f * (%f - %f)", Tt4Sensed, Bdttc,Tt4,Tt4Sensed);

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
	EngOutputP->Wf = Wf;
	/* For memory purposes and comparison only */
	EngOutputP->WfPumpOut = WfOutfp;
//mexPrintf("\nWf = %f; WfOutfp = %f",Wf,WfOutfp);
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
//mexPrintf("Engine Model: Wf = %f, Tt4 = %f, StartingOn = %d\n", Wf, Tt4Sensed, Starting.StartingOn); 
//mexPrintf("\nPt3 = %f; Pt3Sensed = %f",Pt3,Pt3Sensed);
	/* Authorizes the controller to actuate and indicates the IC no longer need to be calculated */
	if (EngOutputP->ICCalc == 0)
	{
		EngOutputP->ICAuthorize = 1;
		EngOutputP->ICCalc = 1;
	}
}

