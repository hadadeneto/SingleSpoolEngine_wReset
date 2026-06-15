/*		T-MATS -- Ambient_TMATS.c
 * % *************************************************************************
 * % written by Jeffryes Chapman
 * % NASA Glenn Research Center, Cleveland, OH
 * % Aug 12, 2014
 * %
 * %  This file converts Altitude and MN to common engine input variables.
 * % *************************************************************************/

#include <math.h>

/* -------------------------------------------------- */
/* INCLUDE - T-MATS & PWLM                            */
/* (To be usedi in MATLAB and TMATS simulations only) */
/* -------------------------------------------------- */

#include "mex.h"

/* -------------------------------------------------- */

 /*Common includes for both model and controller*/
#include "Env_SampTime.h"
#include "MtxIntFunctions.h"		//Also MtxInitFunctions.c
#include "Interpolation_Types.h"

/* Model includes */
#include "Model_Types.h"


void InitCond(int *SkipStartP, int Total_Elem, int MN_Elem, int Fn_Elem, double Altitude, double MN, double dT, double NDes, double FNpc0, struct AmbientPars *AmbientP, double *MNLinVecP, double *FNperContMtxP, 
			  double *NcFANContMtxP, double *FNcMaxContMtxP ,double *WfMtxP, double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP, struct EngineOutput *EngOutputP, int EngUnits)

{

	/* Declares ambient variables */
	double Tt2, Pt2, Theta, Delta, ThetaSL, DeltaSL;
	double AltLinVec = 0;

	/* Number of auxiliar matrices elements */
	int NumEl2D = MN_Elem * Fn_Elem;
	int NumEl1D = Fn_Elem;

	/* Initial conditions variables */
	double RPM0, Wf0;

	double FNcMax;

	/* Declares pointer for 3D interpolation indexes */
	InterpIndex3D Index3D;

	/* CALCULATION OF AMBIENT PARAMETERS */
	
	AmbientP->Alt = Altitude;
	AmbientP->MN = MN;
	AmbientP->dT = dT;

	Ambient_TMATS(AmbientP);
	Tt2 = AmbientP->Tt;
	//Ts2Std0 = AmbientP->Ts;
	Pt2 = AmbientP->Pt;
	MN = AmbientP->MN;
	Theta = Tt2 / TSTD;
	Delta = Pt2 / PSTD;
mexPrintf("Alt=%f, MN=%f, dT=%f, Tt2=%f,Pt2=%f, Theta=%f, Delta=%f\n",AmbientP->Alt,AmbientP->MN,AmbientP->dT,Tt2,Pt2,Theta,Delta);
	/* CALCULATION OF AMBIENT PARAMETERS FOR SEA LEVEL AND dT = 0 */

	AmbientP->Alt = 0;
	AmbientP->dT = 0;

	Ambient_TMATS(AmbientP);
	Tt2 = AmbientP->Tt;
	Pt2 = AmbientP->Pt;
	ThetaSL = Tt2 / TSTD;
	DeltaSL = Pt2 / PSTD;

	/* CALCULATION OF MAXIMUM CORRECTED THRUST AT GIVEN FLIGHT MACH NUMBER IN CASE ENGINEERING UNITS ARE USED */

	/* Finds indexes from a dummy percentual value of Fnpc for obtaining the Mach number indexes */
	InterpInd3DRPM(0, MN, 0.95, &AltLinVec, MNLinVecP, FNperContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, 1, MN_Elem, Fn_Elem, &Index3D);
	
	/* Shifts the indexes of Index3D for finding a 1D element */
	Index3D.kRPM = Index3D.kMN;
	Index3D.kRPMH = Index3D.kMNH;
	Index3D.fRPM = Index3D.fMN;
	Index3D.kMN = 0;
	Index3D.kMNH = 0;
	Index3D.fMN = 0;
	Index3D.kA = 0;
	Index3D.kAH = 0;
	Index3D.fA = 0;

	/* Finds the corrected value for maximum thrust at given flight Mach number */
	//FNcMax = InterpValue(&Index3D, FNcMaxContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	FNcMax = InterpValue(&Index3D, FNcMaxContMtxP, Mtx1DP, Mtx1DHP, Mtx1DP, Mtx1DHP, MN_Elem, MN_Elem);

	/* Verifies if engineering units are to be used */
	if (EngUnits == 1)
	{
		/* Corrects FNpc0 in case engineering units are used */
		FNpc0 = FNpc0 / FNcMax / Delta;
	}
mexPrintf("FNpc0=%f\n",FNpc0);

	/* CALCULATION OF INITIAL VALUES OF ROTATION SPEED AND FUEL FLOW */

	/* Finds indexes from initial percentual thrust value and percentual thrust matrix at sea level */
	InterpInd3DRPM(0, MN, FNpc0, &AltLinVec, MNLinVecP, FNperContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, 1, MN_Elem, Fn_Elem, &Index3D);
	
	/* Evaluates if the engine is at stargin phase - what is true if fRPM is negative */
	if (Index3D.fRPM < 0) {

		/* sets fRPM to zero in order for the first elements of state-matrices to be selected */
		RPM0 = 0;
		Wf0 = 0;
		*(SkipStartP) = 0;

	}
	else {

		/* Finds the corrected value of RPM0 from Sea Level Matrix */
		RPM0 = InterpValue(&Index3D, NcFANContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
		/* Finds the absolute value of RPM0 for the corresponding altitude */
		RPM0 = RPM0 * NDes * sqrt(Theta);

		/* Finds the value of Wf0 from Sea Level Matrix */
		Wf0 = InterpValue(&Index3D, WfMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
		/* Calculates the corrected value of Wf0 */
		Wf0 = Wf0 / DeltaSL / sqrt(ThetaSL);
		/* Calculates the absolute value of Wf0 for the corresponding altitude */
		Wf0 = Wf0 * Delta * sqrt(Theta);
		/* Indicates that starting must be skipped */
		*(SkipStartP) = 1;

	}


	/* Updates initial values */
	EngOutputP->RPM = RPM0;
	EngOutputP->Wf = Wf0;

}

