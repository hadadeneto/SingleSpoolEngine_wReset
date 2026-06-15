/*		FADEC -- StartingFunctions.c
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % December, 2021
 * %
 * %  This is a file that contains various functions for use in the FADEC C-code
 * % *************************************************************************/

//#include "constants_TMATS.h"
#include <math.h>

#include "../FADEC_Defines_H/IO_Types.h"
#include "../FADEC_Defines_H/Env_SampTime.h"

// #include "IO_Types.h"
// #include "Env_SampTime.h"
#include "../FADEC_Defines_H/Control_Types.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../FADEC_Defines_H/Interpolation_Types.h"
#include "../FADEC_Defines_H/Model_Types.h"
//#include "../FADEC_Functions_H/LinMtxFunctions.h"
#include "../FADEC_Functions_H/MtxIntFunctions.h"
#include "../FADEC_Functions_H/ControlFunctions.h"

/*******************************************************************************
 *
 *	FUNCTION:		WindMillingModel()
 *
 *	PURPOSE:		Simulates engine windmilling
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		tbd
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

	// floating *AshMtxP, floating *BshMtxP, floating *RPMshMtxP,
	// floating *NcFANshMtxP, floating *Pt21shMtxP, floating *Pt21DshMtxP,
	// floating *Pt3shMtxP, floating *Pt3DshMtxP, floating *Pt5shMtxP, floating *Pt5DshMtxP,
	// floating *Pt6shMtxP, floating *Pt6DshMtxP, floating *Tt21shMtxP, floating *Tt21DshMtxP,
	// floating *Tt3shMtxP, floating *Tt3DshMtxP, floating *Tt4shMtxP, floating *Tt4CshMtxP, floating *Tt4DshMtxP,
	// floating *Tt5shMtxP, floating *Tt5DshMtxP, floating *Tt6shMtxP, floating *Tt6DshMtxP, floating *WfshMtxP,

	// floating *AwmMtxP, floating *BwmMtxP, floating *RPMwmMtxP,
	// floating *Pt21wmMtxP,	floating *Pt21DwmMtxP, floating *Pt3wmMtxP,	floating *Pt3DwmMtxP,
	// floating *Pt5wmMtxP, floating *Pt5DwmMtxP, floating *Pt6wmMtxP, floating *Pt6DwmMtxP,
	// floating *Tt21wmMtxP, floating *Tt21DwmMtxP, floating *Tt3wmMtxP, floating *Tt3DwmMtxP, floating *Tt4wmMtxP, floating *Tt4DwmMtxP,
	// floating *Tt5wmMtxP, floating *Tt5DwmMtxP, floating *Tt6wmMtxP, floating *Tt6DshMtxP, floating *Tt6DwmMtxP, floating *WfwmMtxP,

// int WindMillingModel(struct EnginePars *ParsP, struct EngineStart *StartingP,
// 					 floating *AwmMtxP, floating *BwmMtxP, floating *RPMwmMtxP, floating *WfwmMtxP,
// 					 floating Mwm, floating *MNLinVecP,
// 					 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating RPM, floating sqrTheta,
// 					 floating MN_Elem, floating Fn_Elem, floating NumEl1D, floating NumEl2D, floating Pt2, floating Tt2,
// 					 floating PN, floating PNSL, floating PNdot, floating PNdotSL, floating Pu, floating PuSL)

int WindMillingModel(struct EnginePars *ParsP, struct EngineStart *StartingP,
					 floating *AwmMtxP, floating *BwmMtxP, floating *RPMwmMtxP,
					 floating *Pt21wmMtxP, floating *Pt21DwmMtxP, floating *Pt3wmMtxP, floating *Pt3DwmMtxP,
					 floating *Pt5wmMtxP, floating *Pt5DwmMtxP, floating *Pt6wmMtxP, floating *Pt6DwmMtxP,
					 floating *Tt21wmMtxP, floating *Tt21DwmMtxP, floating *Tt3wmMtxP, floating *Tt3DwmMtxP, floating *Tt4wmMtxP, floating *Tt4DwmMtxP,
					 floating *Tt5wmMtxP, floating *Tt5DwmMtxP, floating *Tt6wmMtxP, floating *Tt6DshMtxP, floating *Tt6DwmMtxP, floating *WfwmMtxP,
					 floating Mwm, floating *MNLinVecP,
					 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating RPM, floating sqrTheta,
					 floating MN_Elem, floating Fn_Elem, floating NumEl1D, floating NumEl2D, floating Pt2, floating Tt2,
					 floating PN, floating PNSL, floating PNdot, floating PNdotSL, floating Pu, floating PuSL)

{

	/* Definition of parameters:
	 	PN    = sqrTheta
	 	PNdot = Delta
	 	SL parameters correspond to sea level */

	/* Outside, the following operations will be accomplished:

	 	B = 1/PNdotSL * B * PuSL;
		A = 1/PNdotSL * A * PNSL;
		Wfss = Wfss / PuSL;

		B = PNdot * B / Pu;
		A = PNdot * A / PN;
		Wfss = Wfss * Pu;

		The inverse operations must be done in order for ousied
		operations not to have any influence on the parameters
		calculated in this routine*/

	/* Declares pointer for 3D interpolation indexes */
	InterpIndex3D Index3D;
	floating DummyVec = 0;

	/* Calculates corrected rotatin speed */
	floating Nc = RPM / sqrTheta / ParsP->NDes;

	/* Finds 3D indexes necessary for interpolation of controller gains */
	// InterpInd3DRPM(0, MN, Nc, &DummyVec, MNLinVecP, NcFANContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Alt_Elem, MN_Elem, Fn_Elem, &Index3D);
	/* The state-space coefficients are found from current windmillin Mach number */
	InterpInd3DRPM(0, 0, Mwm, &DummyVec, &DummyVec, WfwmMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, 1, MN_Elem, Fn_Elem, &Index3D);
	/* Calculates state-space sea-level coefficients */
	StartingP->B = InterpValue(&Index3D, BwmMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	StartingP->A = InterpValue(&Index3D, AwmMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);

	/* The current Wfss is found from current corrected rotation speed */
	InterpInd3DRPM(0, 0, Nc, &DummyVec, &DummyVec, RPMwmMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, 1, MN_Elem, Fn_Elem, &Index3D);
	StartingP->WfssOut = InterpValue(&Index3D, WfwmMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);

	/* Correction using sea level parameters */
	StartingP->A = (StartingP->A) * PNSL / PNdotSL;
	StartingP->B = (StartingP->B) / PNdotSL;

	/* Calculates absolute values for current altitude */
	StartingP->A = (StartingP->A) * PNdot / PN;
	StartingP->B = (StartingP->B) * PNdot;

	/* Performs adaptation to ouside operations */
	StartingP->A = (StartingP->A) * PNdotSL / PNSL * PN / PNdot;
	StartingP->B = (StartingP->B) * PNdotSL / PuSL * Pu / PNdot;
	StartingP->WfssOut = (StartingP->WfssOut) / (Pu) * (PuSL);

	/* State-space output parameters */
	StartingP->Pt21D = 0;
 	StartingP->Pt3D = 0;
	StartingP->Pt5D = 0;
 	StartingP->Pt6D = 0;
	StartingP->Tt21D = 0;
	StartingP->Tt3D = 0;
	StartingP->Tt4D = 0;
	StartingP->Tt5D = 0;
 	StartingP->Tt6D = 0;

	/* Steady values */
 	StartingP->Pt21ss = Pt2;
    StartingP->Pt3ss = Pt2;
	StartingP->Pt5ss = Pt2;
 	StartingP->Pt6ss = Pt2;
	StartingP->Tt21ss = Tt2;
	StartingP->Tt3ss = Tt2;
	StartingP->Tt4ss = Tt2;
	StartingP->Tt5ss = Tt2;
 	StartingP->Tt6ss = Tt2;

	// /* Output variables */
 	// StartingP->Pt21 = Pt2;
    // StartingP->Pt3 = Pt2;
	// StartingP->Pt5 = Pt2;
 	// StartingP->Pt6 = Pt2;
	// StartingP->Tt21 = Tt2;
	// StartingP->Tt3 = Tt2;
	// StartingP->Tt4 = Tt2;
	// StartingP->Tt5 = Tt2;
 	// StartingP->Tt6 = Tt2;

	// /* Sets current difference between Tt5 and Tt4 */
	// StartingP->DeltaTt = 0;

	/* Current "fuel flow" */
    StartingP->WfOut = Mwm;

	/* Current POil is set to POilMin (minimum allowed oil pressure) */
	StartingP->POil = ParsP->POilMin;

	return 0;
}

/*******************************************************************************
 *
 *	FUNCTION:		SubidleModel()
 *
 *	PURPOSE:		Simulates engine sub-idle after ignition
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		tbd
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

// int SubIdleModel(struct EnginePars *ParsP, struct EngineStart *StartingP, floating *AshMtxP, floating *BshMtxP, floating *WfshMtxP, floating *NcFANshMtxP, floating *MNLinVecP,
// 					 floating *Pt3shMtxP, floating *Tt4shMtxP, floating *Pt3DshMtxP, floating *Tt4DshMtxP,
// 					 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating RPM, floating sqrTheta,
// 					 floating MN_Elem, floating Fn_Elem, floating NumEl1D, floating NumEl2D, floating Pt2, floating Tt2,
// 					 floating PN, floating PNSL, floating PNdot, floating PNdotSL, floating Pu, floating PuSL)

int SubIdleModel(struct EnginePars *ParsP, struct EngineStart *StartingP, floating *MNLinVecP,
				 floating *AshMtxP, floating *BshMtxP, floating *RPMshMtxP,
				 floating *NcFANshMtxP, floating *Pt21shMtxP, floating *Pt21DshMtxP,
				 floating *Pt3shMtxP, floating *Pt3DshMtxP, floating *Pt5shMtxP, floating *Pt5DshMtxP,
				 floating *Pt6shMtxP, floating *Pt6DshMtxP, floating *Tt21shMtxP, floating *Tt21DshMtxP,
				 floating *Tt3shMtxP, floating *Tt3DshMtxP, floating *Tt4shMtxP, floating *Tt4CshMtxP, floating *Tt4DshMtxP,
				 floating *Tt5shMtxP, floating *Tt5DshMtxP, floating *Tt6shMtxP, floating *Tt6DshMtxP, floating *WfshMtxP,
				 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating RPM, floating sqrTheta,
				 floating MN_Elem, floating Fn_Elem, floating NumEl1D, floating NumEl2D, floating Pt2, floating Tt2,
				 floating PN, floating PNSL, floating PNdot, floating PNdotSL, floating Pu, floating PuSL)

{

	/* Declares pointer for 3D interpolation indexes */
	InterpIndex3D Index3D;
	floating DummyVec = 0;

	/* Calculates corrected rotatin speed */
	floating Nc = RPM / sqrTheta / ParsP->NDes;

	/* Finds 3D indexes necessary for interpolation of controller gains */
	// InterpInd3DRPM(0, MN, Nc, &DummyVec, MNLinVecP, NcFANContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Alt_Elem, MN_Elem, Fn_Elem, &Index3D);
	InterpInd3DRPM(0, 0, Nc, &DummyVec, &DummyVec, NcFANshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, 1, MN_Elem, Fn_Elem, &Index3D);

	/* Calculates state-space sea-level coefficients */
	StartingP->B = InterpValue(&Index3D, BshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	StartingP->A = InterpValue(&Index3D, AshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	StartingP->WfssOut = InterpValue(&Index3D, WfshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);

	// /* Correction using sea level parameters */
	// StartingP->A = (StartingP->A) * PNSL / PNdotSL;
	// StartingP->B = (StartingP->B) / PNdotSL;

	// /* Calculates absolute values for current altitude */
	// StartingP->A = (StartingP->A) * PNdot / PN;
	// StartingP->B = (StartingP->B) * PNdot;

	// /* Performs adaptation to ouside operations */
	// StartingP->A = (StartingP->A) * (PNdotSL / PNSL) * (PN / PNdot);
	// StartingP->B = (StartingP->B) * (PNdotSL / PuSL) * (Pu / PNdot);
	// StartingP->WfssOut = (StartingP->WfssOut) / (Pu) * (PuSL);

	// /* State-space output parameters */
	// StartingP->Pt21D = InterpValue(&Index3D, Pt3DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	// StartingP->Pt3D = InterpValue(&Index3D, Pt3DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Pt5D = InterpValue(&Index3D, Pt3DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	// StartingP->Pt6D = InterpValue(&Index3D, Pt3DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Tt21D = 0;//InterpValue(&Index3D, BshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Tt3D = 0;//InterpValue(&Index3D, BshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Tt4D = InterpValue(&Index3D, Tt4DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Tt5D = InterpValue(&Index3D, Tt4DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	// StartingP->Tt6D = InterpValue(&Index3D, Tt4DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);

	/* State-space output parameters */
	StartingP->Pt21D = InterpValue(&Index3D, Pt21DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	StartingP->Pt3D = InterpValue(&Index3D, Pt3DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	StartingP->Pt5D = InterpValue(&Index3D, Pt5DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	StartingP->Pt6D = InterpValue(&Index3D, Pt6DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	StartingP->Tt21D = InterpValue(&Index3D, Tt21DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	StartingP->Tt3D = InterpValue(&Index3D, Tt3DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	StartingP->Tt4D = InterpValue(&Index3D, Tt4DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	StartingP->Tt5D = InterpValue(&Index3D, Tt5DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	StartingP->Tt6D = InterpValue(&Index3D, Tt6DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);


	// /* Steady values */
 	// StartingP->Pt21ss = Pt2;
    // StartingP->Pt3ss = InterpValue(&Index3D, Pt3shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Pt5ss = InterpValue(&Index3D, Pt3shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	// StartingP->Pt6ss = InterpValue(&Index3D, Pt3shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Tt21ss = Tt2;
	// StartingP->Tt3ss = Tt2;
	// StartingP->Tt4ss = InterpValue(&Index3D, Tt4shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Tt5ss = InterpValue(&Index3D, Tt4shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	// StartingP->Tt6ss = InterpValue(&Index3D, Tt4shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);

	/* Steady values */
 	StartingP->Pt21ss = InterpValue(&Index3D, Pt21shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
    StartingP->Pt3ss = InterpValue(&Index3D, Pt3shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	StartingP->Pt5ss = InterpValue(&Index3D, Pt5shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	StartingP->Pt6ss = InterpValue(&Index3D, Pt6shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	StartingP->Tt21ss = InterpValue(&Index3D, Tt21shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	StartingP->Tt3ss = InterpValue(&Index3D, Tt3shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	StartingP->Tt4ss = InterpValue(&Index3D, Tt4shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	StartingP->Tt5ss = InterpValue(&Index3D, Tt5shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	StartingP->Tt6ss = InterpValue(&Index3D, Tt6shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);

	// /* Provisory reduction of Pt5 and Pt6 until actual matrices are used */
	// floating FinalCoef = 2;
	// floating InitCoef = 1.2;
	// int Index = MN_Elem * Fn_Elem - 1;
	// floating NcInit = *(NcFANshMtxP);
	// floating NcFinal = *(NcFANshMtxP + Index);
	// floating f = (Nc - NcInit)/(NcFinal - NcInit);
	// floating Den = InitCoef + f * (FinalCoef - InitCoef);
	// StartingP->Pt5ss = StartingP->Pt5ss / Den;
	// StartingP->Pt6ss = StartingP->Pt6ss / Den;

	return 0;
}

/*******************************************************************************
 *
 *	FUNCTION:		SubidleModel()
 *
 *	PURPOSE:		Simulates engine sub-idle after ignition
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		tbd
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

// int StartingModel(struct EnginePars *ParsP, struct EngineStart *StartingP, floating *AshMtxP, floating *BshMtxP, floating *WfshMtxP, floating *NcFANshMtxP,
// 					 floating *AwmMtxP, floating *BwmMtxP, floating *WfwmMtxP, floating *RPMwmMtxP, floating Mwm, floating *MNLinVecP,
// 					 floating *Pt3shMtxP, floating *Tt4shMtxP, floating *Pt3DshMtxP, floating *Tt4DshMtxP,
// 					 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating RPM, floating sqrTheta,
// 					 floating MN_Elem, floating Fn_Elem, floating NumEl1D, floating NumEl2D, floating Pt2, floating Tt2,
// 					 floating PN, floating PNSL, floating PNdot, floating PNdotSL, floating Pu, floating PuSL, floating Ts)

int StartingModel(struct EnginePars *ParsP, struct EngineStart *StartingP, floating *MNLinVecP,
				  floating *AwmMtxP, floating *AshMtxP, floating *BwmMtxP, floating *BshMtxP, floating *RPMwmMtxP, floating *RPMshMtxP,
				  floating *NcFANshMtxP, floating *Pt21shMtxP, floating *Pt21wmMtxP,
				  floating *Pt21DshMtxP, floating *Pt21DwmMtxP, floating *Pt3shMtxP, floating *Pt3wmMtxP,
				  floating *Pt3DshMtxP, floating *Pt3DwmMtxP, floating *Pt5shMtxP, floating *Pt5wmMtxP, floating *Pt5DshMtxP, floating *Pt5DwmMtxP, floating *Pt6shMtxP, floating *Pt6wmMtxP,
				  floating *Pt6DshMtxP, floating *Pt6DwmMtxP, floating *Tt21shMtxP, floating *Tt21wmMtxP, floating *Tt21DshMtxP, floating *Tt21DwmMtxP,
				  floating *Tt3shMtxP, floating *Tt3wmMtxP, floating *Tt3DshMtxP, floating *Tt3DwmMtxP, floating *Tt4shMtxP, floating *Tt4wmMtxP, floating *Tt4CshMtxP, floating *Tt4DshMtxP, floating *Tt4DwmMtxP,
				  floating *Tt5shMtxP, floating *Tt5wmMtxP, floating *Tt5DshMtxP, floating *Tt5DwmMtxP, floating *Tt6shMtxP, floating *Tt6wmMtxP, floating *Tt6DshMtxP, floating *Tt6DwmMtxP, floating *WfshMtxP, floating *WfwmMtxP,
				  floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating RPM, floating Mwm, floating sqrTheta,
				  floating MN_Elem, floating Fn_Elem, floating NumEl1D, floating NumEl2D, floating Pt2, floating Tt2,
				  floating PN, floating PNSL, floating PNdot, floating PNdotSL, floating Pu, floating PuSL, floating Ts)

{

	/* Timers for ignition */
	static floating TimeIgn = 0;
	static floating TimeZero = 0;

	/* Loads Engine Parameters */
	floating Fuel_BOut = ParsP->Fuel_BOut;
	floating Ign_Delta = ParsP->Ign_Delta;
	floating Ign_Time = ParsP->Ign_Time;
	floating POilMin = ParsP->POilMin;
	floating Valve_Fuel = ParsP->Valve_Fuel;

	/* Loades number of elements of engine matrices */
	floating NcFANMap_Elem = ParsP->NcFANMap_Elem;
	floating NcHPCMap_Elem = ParsP->NcHPCMap_Elem;
	floating NcHPTMap_Elem = ParsP->NcHPTMap_Elem;
	floating PowerMan_Elem = ParsP->PowerMan_Elem;
	floating PRHPTMap_Elem = ParsP->PRHPTMap_Elem;
	floating SteadyOp_Elem = ParsP->SteadyOp_Elem;
	floating WcFANMap_Elem = ParsP->WcFANMap_Elem;
	floating WcHPCMap_Elem = ParsP->WcHPCMap_Elem;
	floating WcHPTMap_Elem = ParsP->WcHPTMap_Elem;

	/* Calculates the value of the oil pressure */
	StartingP->POil = POilMin;

	/* Verifies if reset has been requested */
	if (StartingP->Reset == 1)
	{
		/* If reset is requested, resets static variables and sets reset flag to zero */
		TimeIgn = 0;
		TimeZero = 0;
		StartingP->Reset = 0;
	}

	/*  */
	switch (StartingP->statusIgn)
	{
	case 0:
		/* In state 0, the engine is still windmilling and no ignition has been activated */
		// WindMillingModel(ParsP, StartingP,
		// 				 AwmMtxP, BwmMtxP, WfwmMtxP, RPMwmMtxP,
		// 				 Mwm, MNLinVecP,
		// 				 Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,  RPM,  sqrTheta,
		// 			 	 MN_Elem, Fn_Elem, NumEl1D, NumEl2D, Pt2, Tt2,
		// 			     PN, PNSL, PNdot, PNdotSL, Pu, PuSL);

		WindMillingModel(ParsP, StartingP,
						 AwmMtxP, BwmMtxP, RPMwmMtxP,
						 Pt21wmMtxP, Pt21DwmMtxP, Pt3wmMtxP, Pt3DwmMtxP,
						 Pt5wmMtxP, Pt5DwmMtxP, Pt6wmMtxP, Pt6DwmMtxP,
						 Tt21wmMtxP, Tt21DwmMtxP, Tt3wmMtxP, Tt3DwmMtxP, Tt4wmMtxP, Tt4DwmMtxP,
						 Tt5wmMtxP, Tt5DwmMtxP, Tt6wmMtxP, Tt6DshMtxP, Tt6DwmMtxP, WfwmMtxP,
						 Mwm, MNLinVecP,
						 Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, RPM, sqrTheta,
						 MN_Elem, Fn_Elem, NumEl1D, NumEl2D, Pt2, Tt2,
						 PN, PNSL, PNdot, PNdotSL, Pu, PuSL);

		/* Waits a small fraction for zero rotation to be shown in graphic */
		if (TimeZero < 0.50)
		{
			TimeZero = TimeZero + Ts;
			/* Holds "fuel" at 0 during this time */
			StartingP->WfOut = 0;
		}

		/* If ignition is active, changes for next state */
		if (StartingP->IgnitOn)
		{
			StartingP->statusIgn = 1;
		}

		break;
	case 1:
		/* In state 0, the engine is still windmilling and no ignition has been activated */
		// WindMillingModel(ParsP, StartingP,
		// 				 AwmMtxP, BwmMtxP, RPMwmMtxP, WfwmMtxP,
		// 				 Mwm, MNLinVecP,
		// 				 Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, RPM, sqrTheta,
		// 				 MN_Elem, Fn_Elem, NumEl1D, NumEl2D, Pt2, Tt2,
		// 				 PN, PNSL, PNdot, PNdotSL, Pu, PuSL);
		WindMillingModel(ParsP, StartingP,
						 AwmMtxP, BwmMtxP, RPMwmMtxP,
						 Pt21wmMtxP, Pt21DwmMtxP, Pt3wmMtxP, Pt3DwmMtxP,
						 Pt5wmMtxP, Pt5DwmMtxP, Pt6wmMtxP, Pt6DwmMtxP,
						 Tt21wmMtxP, Tt21DwmMtxP, Tt3wmMtxP, Tt3DwmMtxP, Tt4wmMtxP, Tt4DwmMtxP,
						 Tt5wmMtxP, Tt5DwmMtxP, Tt6wmMtxP, Tt6DshMtxP, Tt6DwmMtxP, WfwmMtxP,
						 Mwm, MNLinVecP,
						 Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, RPM, sqrTheta,
						 MN_Elem, Fn_Elem, NumEl1D, NumEl2D, Pt2, Tt2,
						 PN, PNSL, PNdot, PNdotSL, Pu, PuSL);

		/* Updates ignition time */
		TimeIgn = TimeIgn + Ts;

        /* If ignition is not active, the status flag is set to 0. If the fuel flow value
        is less than the blow out value, ignition does not take place */
		if (!StartingP->IgnitOn & (TimeIgn < Ign_Time)) {
//printf("\nFirst Condition = Sets TimeIgn to 0 and status to 0 and Wf = %f", Pointer->WfOut);
			StartingP->statusIgn = 0;
			TimeIgn = 0;
		}
        else if (StartingP->WfIn <= Fuel_BOut)
        {
//printf("\nSecond Condition = Sets TimeIgn to 0 and Wf = %f", Pointer->WfOut);
            TimeIgn = 0;
        }
		else if (TimeIgn >= Ign_Time) {
//printf("\nThird Condition = changes state to 2 and Wf = %f", Pointer->WfOut);
			TimeIgn = 0;
			StartingP->statusIgn = 2;
		}

		break;
	case 2:
		/* Sub-idle model after ignition is accomplished */
		// SubIdleModel(ParsP, StartingP, AshMtxP, BshMtxP, WfshMtxP, NcFANshMtxP, MNLinVecP,
		// 			 Pt3shMtxP, Tt4shMtxP, Pt3DshMtxP, Tt4DshMtxP,
		// 			 Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, RPM, sqrTheta,
		// 			 MN_Elem, Fn_Elem, NumEl1D, NumEl2D, Pt2, Tt2,
		// 			 PN, PNSL, PNdot, PNdotSL, Pu, PuSL);

		SubIdleModel(ParsP, StartingP, MNLinVecP,
					 AshMtxP, BshMtxP, RPMshMtxP,
					 NcFANshMtxP, Pt21shMtxP, Pt21DshMtxP,
					 Pt3shMtxP, Pt3DshMtxP, Pt5shMtxP, Pt5DshMtxP,
					 Pt6shMtxP, Pt6DshMtxP, Tt21shMtxP, Tt21DshMtxP,
					 Tt3shMtxP, Tt3DshMtxP, Tt4shMtxP, Tt4CshMtxP, Tt4DshMtxP,
					 Tt5shMtxP, Tt5DshMtxP, Tt6shMtxP, Tt6DshMtxP, WfshMtxP,
					 Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, RPM, sqrTheta,
					 MN_Elem, Fn_Elem, NumEl1D, NumEl2D, Pt2, Tt2,
					 PN, PNSL, PNdot, PNdotSL, Pu, PuSL);

		/* If the fuel flow level lies below FUEL_BOUT, the engine is shut off */
		if (StartingP->WfOut < Fuel_BOut) {
			StartingP->statusIgn = 0;
		}

		break;

	default:
		break;
	}

	// /* Definition of parameters:
	//  	PN    = sqrTheta
	//  	PNdot = Delta
	//  	SL parameters correspond to sea level */

	// /* Outside, the following operations will be accomplished:

	//  	B = 1/PNdotSL * B * PuSL;
	// 	A = 1/PNdotSL * A * PNSL;
	// 	Wfss = Wfss / PuSL;

	// 	B = PNdot * B / Pu;
	// 	A = PNdot * A / PN;
	// 	Wfss = Wfss * Pu;

	// 	The inverse operations must be done in order for ousied
	// 	operations not to have any influence on the parameters
	// 	calculated in this routine*/

	// /* Declares pointer for 3D interpolation indexes */
	// InterpIndex3D Index3D;
	// floating DummyVec = 0;
	// /* Declares initial value of MN */
	// floating MN = 0;

	// /* Calculates corrected rotatin speed */
	// floating Nc = RPM / sqrTheta;

	// /* Finds 3D indexes necessary for interpolation of controller gains */
	// // InterpInd3DRPM(0, MN, Nc, &DummyVec, MNLinVecP, NcFANContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Alt_Elem, MN_Elem, Fn_Elem, &Index3D);
	// InterpInd3DRPM(0, 0, Nc, &DummyVec, &DummyVec, NcFANshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, 1, MN_Elem, Fn_Elem, &Index3D);

	// /* Calculates state-space sea-level coefficients */
	// StartingP->B = InterpValue(&Index3D, BshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->A = InterpValue(&Index3D, AshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->WfssOut = InterpValue(&Index3D, WfshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);

	// // /* Correction using sea level parameters */
	// // StartingP->A = (StartingP->A) * PNSL / PNdotSL;
	// // StartingP->B = (StartingP->B) / PNdotSL;

	// // /* Calculates absolute values for current altitude */
	// // StartingP->A = (StartingP->A) * PNdot / PN;
	// // StartingP->B = (StartingP->B) * PNdot;

	// // /* Performs adaptation to ouside operations */
	// // StartingP->A = (StartingP->A) * (PNdotSL / PNSL) * (PN / PNdot);
	// // StartingP->B = (StartingP->B) * (PNdotSL / PuSL) * (Pu / PNdot);
	// // StartingP->WfssOut = (StartingP->WfssOut) / (Pu) * (PuSL);

	// /* State-space output parameters */
	// StartingP->Pt21D = InterpValue(&Index3D, Pt3DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	// StartingP->Pt3D = InterpValue(&Index3D, Pt3DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Pt5D = InterpValue(&Index3D, Pt3DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	// StartingP->Pt6D = InterpValue(&Index3D, Pt3DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Tt21D = 0;//InterpValue(&Index3D, BshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Tt3D = 0;//InterpValue(&Index3D, BshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Tt4D = InterpValue(&Index3D, Tt4DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Tt5D = InterpValue(&Index3D, Tt4DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	// StartingP->Tt6D = InterpValue(&Index3D, Tt4DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);

	// /* Steady values */
 	// StartingP->Pt21ss = Pt2;
    // StartingP->Pt3ss = InterpValue(&Index3D, Pt3shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Pt5ss = InterpValue(&Index3D, Pt3shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	// StartingP->Pt6ss = InterpValue(&Index3D, Pt3shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Tt21ss = Tt2;
	// StartingP->Tt3ss = Tt2;
	// StartingP->Tt4ss = InterpValue(&Index3D, Tt4shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
	// StartingP->Tt5ss = InterpValue(&Index3D, Tt4shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
 	// StartingP->Tt6ss = InterpValue(&Index3D, Tt4shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);

	return 0;
}

// /*******************************************************************************
//  *
//  *	FUNCTION:		Edge()
//  *
//  *	PURPOSE:		Edge detection of a variable
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		Signal[] (must be at least a string of two elements)
//  *
//  *	RETURNS:		EdgeFlag
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/


// int Edge(int Signal[])
// {

// 	/* Initiates Edge with zero value */
// 	int	EdgeFlag = 0;

// 	/* Signal[0] > Signal[1] -> risign edge -> Edge = 1 */
// 	if (Signal[0] > Signal[1]) {
// 		EdgeFlag = 1;
// 	}

// 	/* Signal[0] < Signal[1] -> risign edge -> Edge = 2 */
// 	if (Signal[0] < Signal[1]) {
// 		EdgeFlag = 2;
// 	}

// 	return EdgeFlag;

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		TimerSR()
//  *
//  *	PURPOSE:		Updates and resets timer value
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		floating *Time, floating Ts, floating TimeMax
//  *
//  *	RETURNS:		int TimeReset
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// int TimerSR(floating *TimeP, floating Ts, floating TimeMax)
// {

// 	/* Flag indicating that the value of TimeMax has been reached and timer
// 	has been reset */
// 	int TimeReset = 0;

// 	/* Updates Time Value */
// 	*TimeP = *TimeP + Ts;

// 	/* If Time value is greater or equal TimeMax, the timer must be reset */
// 	if(*TimeP >= TimeMax ){
// 		/* Resets Timer Value and sets reset flag to 1 */
// 		//*TimeP = 0;
// 		TimeReset = 1;
// 	}

// 	/* Returns Timer Value */
// 	return TimeReset;
// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		StatusDelay()
//  *
//  *	PURPOSE:		Updates the status once a given value has been reached by the
//  *					timer
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		floating *TimeP, floating Ts, floating TimeMax, int *status
//  *
//  *	RETURNS:
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void StatusDelay(floating *TimeP, floating Ts, floating TimeMax, int *status, int NextStatus)
// {

// 	/* Declaration of reset flag */
// 	int TimerReset = 0;

// 	/* Executes the timer subroutine for desired delay */
// 	TimerReset = TimerSR(TimeP, Ts, TimeMax);

// 	/* Updates status if timer has been reset */
// 	if (TimerReset == 1)
// 	{
// 		*status = NextStatus;
// 		*TimeP = 0;
// 	}

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		AirValveOpen()
//  *
//  *	PURPOSE:		Obtains the smaller value between two variables (floating)
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		RPM, ValveSR
//  *
//  *	RETURNS:		ValveSR
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// floating AirValveOpen(struct ControlStart *ContStart, floating RPM, int EngineShutDown)
// {

// 	floating ValveInit = ContStart->ValveInit;
// 	floating ValveTotal = ContStart->ValveTotal;
// 	floating RPMValve100 = ContStart->RPMValve100;
// 	floating RPMIdle = ContStart->RPMIdle;


// 	//Initiates ValveSR with defined initial apperture
// 	floating ValveSR = ValveInit;

// 	//If rotation speed is greater or equal RPM_VALVE_100,
// 	//valve is opened at its maximum allowed apperture
// 	if (RPM >= RPMValve100) {
// 		ValveSR = ValveTotal;
// 	}

// 	//If rotation speed is greater or equal TJ1200_RPM_IDLE or engine is shut down,
// 	//valve must be totally closed
// 	if ((RPM >= RPMIdle) | (EngineShutDown > 0.5)) {
// 		ValveSR = 0;
// 	}

// 	return ValveSR;
// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		StratEdge()
//  *
//  *	PURPOSE:		Identifies the edge indicating the engine start
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		struct ControlStart *ContStartP, int *status, int NextStatus
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void StartEdge(struct ControlStart *ContStartP, int *status, int NextStatus)
// {

// 	int StartKey[2] = {0,0};
// 	int KeyEdge;

// 	/* Computes the values of current and old keys in StartKey */
// 	StartKey[0] = ContStartP->Current_key_start;
// 	StartKey[1] = ContStartP->Old_key_start;

// 	/* Identifies if an edge has occurred */
// 	KeyEdge = Edge(StartKey);

// 	/* Updates the value of the starting command for stauts computing */
// 	ContStartP->StartCommand = KeyEdge;

// 	/* An edge from 0 to 1 in the signal indicates that the variable status, which
// 	is used in the starting state machine, must be increased by 1 unit */
// 	if (KeyEdge == 1)
// 	{
// 		*status = NextStatus;
// 	}
// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		DigOutOn()
//  *
//  *	PURPOSE:		Activates the ditital outputs
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		floating RPM,  struct ControlStart *ContStartP, digital_t *digitalP, int *status
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void DigOutOn(floating RPM,  struct ControllerConstants *ContConstP, digital_t *digitalP, int *status, int NextStatus)
// {
// 	/* Verifies if rotation speed is sufficient for activating digital ouptuts */
// 	if (RPM >= ContConstP->RPMRelaysOn)
// 		{
// 			/* Activation of output relays */
// 			digitalP->bits.igniter = 1;
// 			digitalP->bits.solenoid = 1;
// 			digitalP->bits.suction_bomb = 1;
// 			digitalP->bits.oil_pump = 1;
// 			digitalP->bits.inverter = 1;
// 			digitalP->bits.T4_alarm_led = 0;
// 			digitalP->bits.oil_pump_led = 0;
// 			digitalP->bits.igniter_led = 0;

// 			/* Updates state-machine status */
// 			*status = NextStatus;
// 		}
// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		FuelPulse()
//  *
//  *	PURPOSE:		Sets fuel flow value to pulse high value
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		floating *TimePulseP, floating Ts, floating PulseWidth, floating *Fuel, floating FuelHigh, floating Tt4, floating Tt4FlameOn, int *status, int NextStatus
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void FuelPulse(floating *TimePulseP, floating Ts, floating PulseWidth, floating *WfP, floating WfHigh, floating Tt4, floating Tt4FlameOn, int *status, int NextStatus)
// {

// 	int TimerReset;

// 	/* Sets the fuel flow with the high value of fuel pulse */
// 	*WfP = WfHigh;

// 	/* Executes the timer subroutine for desired delay */
// 	TimerReset = TimerSR(TimePulseP, Ts, PulseWidth);

// 	/* If ignition has been detected or the pulsewidth has been achieved */
// 	if((Tt4 > Tt4FlameOn) | (TimerReset == 1))
// 	{
// 		*status = NextStatus;
// 		*TimePulseP = 0;
// 	}

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		IgnMonitor()
//  *
//  *	PURPOSE:		Sets fuel flow value to pulse high value
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		Various
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void IgnitAttempt(digital_t *digitalP, floating *IgnTryTimeP, floating MaxIgnTryTime,
// 				floating Ts, floating Tt4, floating Tt4Ign, int *statusP, int statusIgn,
// 				int *IgnTries,int IgnMaxTries, floating *WfP, floating WfInit,
// 				 int *IgnitionFailP, int NextState)
// {

// 	/* Initiation of flag indicating ignition fail */
// 	int TRIgnTry = 0;

// 	/*----------------------------------*/
// 	/* SETS FUEL VALUE TO INITIAL VALUE */
// 	/*----------------------------------*/

// 	*WfP = WfInit;

// 	/*--------------------------*/
// 	/* MONITORS IGNITION TIMER  */
// 	/*--------------------------*/

// 	/* If the igniter is active, ignition trial time is counted */
// 	if (digitalP->bits.igniter)
// 	{
// 		/* Executes the timer subroutine */
// 		TRIgnTry = TimerSR(IgnTryTimeP, Ts, MaxIgnTryTime);
// 	}
// 	/* If the igniter is not active, the time should not be counted */
// 	else
// 	{
// 		*IgnTryTimeP = 0;
// 	}

// 	/*----------------------------*/
// 	/* IDENTIFICATION OF IGNITION */
// 	/*----------------------------*/

// 	/* If the combustion chamber temeprature exceeds the ignition temperature,
// 	ignition is detected */
// 	if (Tt4 > Tt4Ign)
// 	{
// 		*IgnTryTimeP = 0;
// 		TRIgnTry = 0;
// 		*statusP = NextState;
// 		*IgnTries = 0;
// 	}


// 	/*---------------------------*/
// 	/* MONITORS IGNITION STATUS  */
// 	/*---------------------------*/

// 	/* If an ignition trial time has elapsed, IgnTryTime must be reset, the counter of trials must
// 	be increased by 1 and a new pulse must be sent to the fuel pump*/
// 	if (TRIgnTry == 1)
// 	{
// 		*IgnTries = *IgnTries + 1;
// 		*IgnTryTimeP = 0;

// 		/* If the number of trials have been exceeded, fail must be indicated. Otherwise, aother
// 		attempt must be accomplished  */
// 		if (*IgnTries > IgnMaxTries)
// 		{
// 			*IgnitionFailP = 1;
// 		}
// 		else
// 		{
// 			*statusP = statusIgn;
// 		}
// 	}
// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		FuelRampSR()
//  *
//  *	PURPOSE:		Increses fuel value following desired ramp
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		floating *WfP, floating WfInit, floating RampCoef, floating *RampTimeP, floating Ts
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void FuelRampSR(floating *WfP, floating WfInit, floating RampCoef, floating *RampTimeP, floating Ts)
// {
// 	floating Time = *RampTimeP;

// 	/* Updates fuel value */
// 	*WfP = WfInit + RampCoef * Time;

// 	/* Updates ramp time */
// 	Time = Time + Ts;
// 	*RampTimeP = Time;

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		PITempStart()
//  *
//  *	PURPOSE:		Closed-Loop to be used during engine start
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		various
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void PITempStart(struct ControllerConstants *ContConst, struct ControlStart *ContStartP,
//                 struct ControllerInput *ContInputP, floating Tsample)

// {
// 	/*--------------------------*/
// 	/* DECLARATION OF VARIABLES */
// 	/*--------------------------*/

// 	/* CLOSED-LOOP ROUTINE VARIABLES */

// 	/* Errors and control signals */
// 	floating eTt4k;
// 	floating uTt4k;
// 	floating uMMk;

// 	/* Previous samples of errors and control signals */
// 	floating urk1 = ContStartP->urk1;
// 	floating uTt4k1 = ContStartP->uTt4k1;
// 	floating ITermTk1 = ContStartP->ITermTk1;
// 	floating eTt4k1 = ContStartP->eTt4k1;
// 	floating eBTk1 = ContStartP->eBTk1;

// 	/* Active controller flag */
// 	floating KbT = ContConst->KbT;
//     floating KpTt4 = ContConst->KpTt4;
// 	floating KiTt4 = ContConst->KiTt4;

//     /* Controller Constants */
//     floating    Tt4Max = ContStartP->Tt4CLRef;//ContConst->Tt4CLSafeStart;//ContConst->Tt4Max;
//     floating    WfMax = ContConst->WfMax;

// 	/* Structures for PI outputs */
// 	PIOutput PIOutT;

// 	/* Actuation signal */
// 	floating Wf = ContStartP->Wf;

// 	/* Stations variables */
// 	floating Tt4;

// 	/* Declares pointer for 3D interpolation indexes */
// 	InterpIndex3D Index3D;

// 	/* Starging Parameters */
// 	floating POil;

//     /* Dummy variable for 2D or 1D calculations */
//     floating DummyVar = 1;


// 	/*----------------------------*/
// 	/* STARTTING OF CONTROL LOGIC */
// 	/*----------------------------*/

// 	/* READS CONTROLLER INPUT DATA */

// 	/* Engine input */
// 	Tt4 = ContInputP->Tt4;

// 	/* CALCULATION OF ERRORS */

// 	/* Calculates Rotation Speed Error and Back Calculation Error*/
// 	eTt4k = Tt4Max - Tt4;
// 	eBTk1 = uTt4k1 - urk1;

// //printf("\nInside Tem PI of state 45: eTt4k = %f, Tt4 = %f, Tt4Max = %f\n",eTt4k, Tt4,Tt4Max);

// 	/* CALCULATES PI CONTROL SIGNALS */

// 	PIControl(KiTt4, KpTt4, KbT, Tsample, ITermTk1, eTt4k, eTt4k1, eBTk1, &PIOutT);
// 	uTt4k = PIOutT.u;


// 	/* FUEL PUMP SATURATION */

// 	uMMk = Min(uTt4k, WfMax);
// 	uMMk = Max(uMMk, 0);

// 	/* COMPUTES ACTUATION SIGNAL OUTPUT */

// 	/* Computes the actuation signal at desired output */
// 	Wf = uMMk;

// 	/* MEMORY UPDATE FOR PI CONTROLLER */

// 	/* Delayed control variables */
// 	urk1 = uMMk;
// 	uTt4k1 = PIOutT.u;
// 	ITermTk1 = PIOutT.Iout;
// 	eTt4k1 = eTt4k;

// 	/* Updates fuel flow value */
// 	ContStartP->Wf = Wf;

// 	/* Updates calculated memory variables */
// 	ContStartP->urk1 = urk1;
// 	ContStartP->uTt4k1 = uTt4k1;
// 	ContStartP->ITermTk1 = ITermTk1;
// 	ContStartP->eTt4k1 = eTt4k1;
// 	ContStartP->eBTk1 = eBTk1;

// }

// /*******************************************************************************
//  *
//  *	FUNCTION:		PIMMStart()
//  *
//  *	PURPOSE:		Closed-Loop to be used during engine start
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		various
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void PIMMStart(floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP,
//                 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
//                 struct ControllerConstants *ContConst, struct ControlStart *ContStartP,
//                 struct ControllerInput *ContInputP, floating *NcFANContMtxP,
// 				floating *N_KpMtxP, floating *N_KiMtxP, floating Tsample)

// {
// 	/*--------------------------*/
// 	/* DECLARATION OF VARIABLES */
// 	/*--------------------------*/

// 	/* CLOSED-LOOP ROUTINE VARIABLES */

// 	/* Errors and control signals */
// 	floating eNk;
// 	floating eTt4k;
// 	floating uNk;
// 	floating uTt4k;
// 	floating uMMk;
// 	floating uRUk;

// 	/* Previous samples of errors and control signals */
// 	floating uNk1 = ContStartP->uNk1;
// 	floating urk1 = ContStartP->urk1;
// 	floating ITermNk1 = ContStartP->ITermNk1;
// 	floating uTt4k1 = ContStartP->uTt4k1;
// 	floating ITermTk1 = ContStartP->ITermTk1;
// 	floating eNk1 = ContStartP->eNk1;
// 	floating eTt4k1 = ContStartP->eTt4k1;
// 	floating eBNk1 = ContStartP->eBNk1;
// 	floating eBTk1 = ContStartP->eBTk1;

// 	/* Active controller flag */
// 	floating Active = ContStartP->Active;
// 	floating CalcSigVec[] = { 100, 100, 100, 100 };
// 	floating LastSignalIndex = 3;
// 	floating *CSVPointer = &CalcSigVec;

// 	/* Controller Gains */
// 	floating KiN;
// 	floating KpN;
// 	floating KbN = ContConst->KbN;
// 	floating KbT = ContConst->KbT;
//     floating KpTt4 = ContConst->KpTt4;
// 	floating KiTt4 = ContConst->KiTt4;

//     /* Controller Constants */
//     int       Alt_Elem = ContConst->Alt_Elem;
//     int       Fn_Elem = ContConst->Fn_Elem;
//     int       MN_Elem = ContConst->MN_Elem;
//     floating    NDes = ContConst->NDes;
//     floating    NMax = ContConst->NMax;
//     floating    Tt4Max = ContConst->Tt4AvMax;//ContConst->Tt4Max;
//     floating    WfMax = ContConst->WfMax;

//     /* Number of elements of gains and thrust elements */
// 	floating NumEl2D = MN_Elem * Fn_Elem;
// 	floating NumEl1D = Fn_Elem;

// 	/* Structures for PI outputs */
// 	PIOutput PIOutN;
// 	PIOutput PIOutT;

// 	/* Reference variableS */
// 	floating RPMRef = ContStartP->RPMRef;

// 	/* Actuation signal */
// 	floating Wf = ContStartP->Wf;

// 	/* Variables to be provided externaly via CAN communication */
// 	floating Altitude;
// 	floating MN;
// 	floating RPM;

// 	/* Stations variables */
// 	floating Tt2;
// 	floating Pt3;
// 	floating Tt4;

// 	/* Correction parameter */
//     floating FNcMax;
// 	floating Nc;
// 	floating Theta;
//     floating Delta;

// 	/* Declares pointer for 3D interpolation indexes */
// 	InterpIndex3D Index3D;

// 	/* Starging Parameters */
// 	floating POil;

//     /* Dummy variable for 2D or 1D calculations */
//     floating DummyVar = 1;


// 	/*----------------------------*/
// 	/* STARTTING OF CONTROL LOGIC */
// 	/*----------------------------*/

// 	/* READS CONTROLLER INPUT DATA */

// 	/* Ambient input */
// 	Altitude = ContInputP->Altitude;
// 	MN = ContInputP->MN;

// 	/* Engine input */
// 	Tt2 = ContInputP->Tt2;
// 	Pt3 = ContInputP->Pt3;
// 	Tt4 = ContInputP->Tt4;
// 	RPM = ContInputP->RPM;
// 	POil = ContInputP->POil;

// 	/* CALCULATION OF USED NORMALIZED PARAMETERS */

// 	/* Calculates the Value of Theta */
// 	Theta = Tt2 / TSTD;

// 	/* Calculates the Value of Nc */
// 	Nc = RPM / sqrt(Theta);
// 	Nc = Nc / NDes;

// 	/* CALCULATION OF KpN AND KiN */

// 	/* Finds 3D indexes necessary for interpolation of controller gains */
// 	InterpInd3DRPM(Altitude, MN, Nc, AltLinVecP, MNLinVecP, NcFANContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Alt_Elem, MN_Elem, Fn_Elem, &Index3D);

// 	/* Calculates gains used in PI controllers */
// 	KpN = InterpValue(&Index3D, N_KpMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);
// 	KiN = InterpValue(&Index3D, N_KiMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, NumEl2D, NumEl1D);

// 	/**/
// 	// KpN = KpN / 10;
// 	// KiN = KiN / 10;
// 	// KpTt4 = KpTt4 / 10;
// 	// KiTt4 = KiTt4 / 10;

// 	/* CALCULATION OF ERRORS */

// 	/* Calculates Rotation Speed Error and Back Calculation Error*/
// 	eNk = RPMRef - RPM;
// 	eTt4k = Tt4Max - Tt4;
// 	eBNk1 = uNk1 - urk1;
// 	eBTk1 = uTt4k1 - urk1;

// 	/* CALCULATES PI CONTROL SIGNALS */

// 	/* Calculates Control Signal for Rotation Speed and Tt4 Protection */
// 	PIControl(KiN, KpN, KbN, Tsample, ITermNk1, eNk, eNk1, eBNk1, &PIOutN);
// 	uNk = PIOutN.u;
// 	PIControl(KiTt4, KpTt4, KbT, Tsample, ITermTk1, eTt4k, eTt4k1, eBTk1, &PIOutT);
// 	uTt4k = PIOutT.u;

// 	/* IMPLEMENTS MIN-MAX LOGIC */

// 	/* Min Logic */
// 	uMMk = Min(uNk, uTt4k);

// 	/* IDENTIFIES THE ACTIVE CONTROLLER */
// 	/*	1 - Power Management
// 		2 - Tt4 Limiter
// 		3 - RU Limiter
// 		9 - Output Different From Any Calculated Signal
// 	*/

// 	/* Updates Signals in String */
// 	*(CSVPointer + 1) = uNk;
// 	*(CSVPointer + 2) = uTt4k;

// 	/* Identifies Active Controller */
// 	Active = ActiveCont(CSVPointer, LastSignalIndex, uMMk);

// 	/* FUEL PUMP SATURATION */
// 	uMMk = Min(uMMk, WfMax);
// 	uMMk = Max(uMMk, 0);

// 	/* COMPUTES ACTUATION SIGNAL OUTPUT */

// 	/* Computes the actuation signal at desired output */
// 	Wf = uMMk;

// 	/* MEMORY UPDATE FOR PI CONTROLLER */

// 	/* Delayed control variables */
// 	uNk1 = PIOutN.u;
// 	urk1 = uMMk;
// 	ITermNk1 = PIOutN.Iout;
// 	uTt4k1 = PIOutT.u;
// 	ITermTk1 = PIOutT.Iout;
// 	eNk1 = eNk;
// 	eTt4k1 = eTt4k;

// 	ContStartP->Wf = Wf;
// 	ContStartP->Active = Active;

// 	/* Updates calculated memory variables */
// 	ContStartP->uNk1 = uNk1;
// 	ContStartP->urk1 = urk1;
// 	ContStartP->ITermNk1 = ITermNk1;
// 	ContStartP->uTt4k1 = uTt4k1;
// 	ContStartP->ITermTk1 = ITermTk1;
// 	ContStartP->eNk1 = eNk1;
// 	ContStartP->eTt4k1 = eTt4k1;
// 	ContStartP->eBNk1 = eBNk1;
// 	ContStartP->eBTk1 = eBTk1;

// }

// /*******************************************************************************
//  *
//  *	FUNCTION:		StartVarsUpdt()
//  *
//  *	PURPOSE:		Closed-Loop to be used during engine start
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		various
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void StartVarsUpdt(struct ControlStart *ContStartP, struct ControllerConstants *ContConstP, floating Wf, floating RPM, floating Tt4)
// {
// 	/* Updates calculated memory variables */
// 	ContStartP->uNk1 = Wf;
// 	ContStartP->urk1 = Wf;
// 	ContStartP->ITermNk1 = Wf;
// 	ContStartP->uTt4k1 = Wf;
// 	ContStartP->ITermTk1 = Wf;
// 	ContStartP->eNk1 = 0;
// 	ContStartP->eTt4k1 = 0;
// 	ContStartP->eBNk1 = 0;
// 	ContStartP->eBTk1 = 0;
// 	ContStartP->RPMRef = RPM;//ContConstP->RPMIdle;
// 	ContStartP->RPMCLInit = RPM;
// 	ContStartP->Tt4CLInit = Tt4;
// }

// /*******************************************************************************
//  *
//  *	FUNCTION:		LowFuelRamp()
//  *
//  *	PURPOSE:		Sets fuel flow value to pulse high value
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		various
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void FuelIncrease(struct ControllerConstants *ContConstP, struct ControlStart *ContStartP, digital_t *digitalP, floating RPM, floating RPMChange, floating RPMIgnOff, floating Tt4,
// 				floating Tt4FlameOn, floating *WfP, floating *WfChangeP, floating WfInit, floating WfRampCoef,
// 				floating *RampTimeP, floating Ts, int *statusP, int StatusIgn, int NextStatus)
// {

// 	/* Initiates flat indicating if ramp may be increased */
// 	int RampAllowed = ContStartP->RampAllowed;
// 	/* Reads values of minimum and maximum temperature for allowing fuel ramp */
// 	floating Tt4Min = ContConstP->Tt4CLSafeStart;
// 	floating Tt4Max = ContConstP->Tt4AvMax;
// 	/* Reads the error (difference between Tt4AvMax and Tt4) */
// 	floating ekTt4 = Tt4Max - Tt4;
// 	/* Caluclates error delta (derivative) */
// 	floating DeTt4 = ekTt4 - ContStartP->eTt4k1;

// 	/* Local maximum WfMaxLocal*/
// 	floating WfMaxLocal;

// 	/*Updates previous value of temperature error */
// 	ContStartP->eTt4k1 = ekTt4;

// 	/* Ramp should freeze if Tt4 >= Tt4 Max */
// 	if (Tt4 >= Tt4Max)
// 	{
// 		RampAllowed = 0;
// 	}

// 	/* Ramp should continue if Tt4 <= Tt4 Max */
// 	if (Tt4 <= Tt4Min)
// 	{
// 		RampAllowed = 1;
// 	}

// 	/* Calculates the local maximum Wf value */
// 	WfMaxLocal = *WfP + WfRampCoef;

// 	/* Verifies if Tt4 lies within the boundaries  */

// 	/* Verifies if engine is ignited */
// 	if (Tt4 >= Tt4FlameOn & RampAllowed == 1)
// 	{
// 		/* Verifies if RPM value is slower than ramp change RPM value */
// 		if (RPM < RPMChange)
// 		{
// 			/* Updates fuel flow value according to desired ramp */
// 			*WfP = *WfP + WfRampCoef * Ts;

// 			/*Adds derivative term*/
// 			*WfP = *WfP + ContConstP->WfKdStart * DeTt4;

// 			/* Gets smalle value between signal with pure ramp (WfMaxLocal) and signal with the derivative term */
// 			*WfP = Min(*WfP ,WfMaxLocal);

// 			/* Fuel pump saturation */
// 			*WfP = Min(*WfP, ContConstP->WfMax);
// 			*WfP = Max(*WfP, ContConstP->WfInit);

// 			/* Verifes if igniter must be shut off */
// 			if(RPM > RPMIgnOff)
// 			{
// 				digitalP->bits.igniter = 0;
// 			}
// 		}
// 		else
// 		{
// 			/* Updates ramp change fuel value, status value and sets ramp time to 0 */
// 			*WfChangeP = *WfP;
// 			*RampTimeP = 0;
// 			*statusP = NextStatus;
// 		}

// 	}

// 	/* If the engine has cooled down to a temperature below ignition temperature, new ignition attempts are accomplished */
// 	if (Tt4 < Tt4FlameOn)
// 	{
// 		*statusP = StatusIgn;
// 	}


// 	/* A decreasing rapm is applied in case overtemp possibility is detected */
// 	if (RampAllowed == 0)
// 	{
// 		if(Tt4 < ContConstP->Tt4RampDecFast)
//         {
//             /* Calculation of fuel flow */
//             *WfP = *WfP + ContConstP->WfRampDec * Ts;

//         }
//         else
//         {
//             /* Calculation of fuel flow */
//             *WfP = *WfP + ContConstP->WfRampDecFast * Ts;
//         }

// 		/*Adds derivative term*/
// 		*WfP = *WfP + ContConstP->WfKdStart * DeTt4;

// 		/* Gets smalle value between signal with pure ramp (WfMaxLocal) and signal with the derivative term */
// 		*WfP = Min(*WfP, WfMaxLocal);

// 		/* Fuel pump saturation */
// 		*WfP = Min(*WfP, ContConstP->WfMax);
// 		*WfP = Max(*WfP, ContConstP->WfRampDecLowLim);
// 	}


// 	/* Updates ContStart structure with current flag value */
// 	ContStartP->RampAllowed = RampAllowed;

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		FuelLowCL()
//  *
//  *	PURPOSE:		Sets fuel flow value to pulse high value
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		various
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void FuelLowCL(floating Tt4, floating Tt4FlameOn,
//                 struct ControllerConstants *ContConst, struct ControlStart *ContStartP,
//                 struct ControllerInput *ContInputP,
// 				floating Tsample,	int *statusP, int NextStatus)
// {

// 	floating Tt4CLSafeStart = ContConst->Tt4CLSafeStart;

// 	/* Verifies if engine is ignited */
// 	if (Tt4 > Tt4FlameOn)
// 	{
// 		/* Verifies if RPM value is slower than ramp change RPM value */
// 		if (Tt4 > Tt4CLSafeStart)
// 		{
// 			PITempStart(ContConst, ContStartP, ContInputP, Tsample);
// 		}
// 		else
// 		{
// 			/* Updates ramp change fuel value, status value and sets ramp time to 0 */
// 			*statusP = NextStatus;
// 		}

// 	}

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		FuelIncreaseCL()
//  *
//  *	PURPOSE:		Sets fuel flow value to pulse high value
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		various
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// // void FuelIncreaseCL(digital_t *digitalP, floating RPM, floating RPMChange, floating RPMIgnOff, floating Tt4,
// // 				floating Tt4FlameOn, floating *WfP, floating *RampTimeP,
// // 				floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP,
// //                 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
// //                 struct ControllerConstants *ContConst, struct ControlStart *ContStartP,
// //                 struct ControllerInput *ContInputP, floating *NcFANContMtxP,
// // 				floating *N_KpMtxP, floating *N_KiMtxP, floating Tsample,
// // 				int *statusP, int NextStatus)
// void FuelIncreaseCL(digital_t *digitalP, floating RPM, floating RPMChange, floating RPMIgnOff, floating Tt4,
// 				floating Tt4FlameOn, floating *WfP, floating *RampTimeP, floating RPMRampCoef,
// 				floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP,
//                 floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
//                 struct ControllerConstants *ContConst, struct ControlStart *ContStartP,
//                 struct ControllerInput *ContInputP, floating *NcFANContMtxP,
// 				floating *N_KpMtxP, floating *N_KiMtxP, floating Tsample,
// 				int *statusP, int NextStatus)
// {

// 	floating RPMRef = ContStartP->RPMRef;
// 	floating RPMInit = ContStartP->RPMCLInit;

// 	/* Verifies if engine is ignited */
// 	if (Tt4 > Tt4FlameOn)
// 	{

// 		/* Increases reference ramp only if temperature protection has not been activated */
// 		if (ContStartP->Active == 2)
// 		{
// 			RPMRef = RPM;
// 		}
// 		else
// 		{
// 			/* Updates fuel flow value according to desired ramp */
// 			FuelRampSR(&RPMRef, RPMInit, RPMRampCoef, RampTimeP, Tsample);
// 		}

// 		/* Limits the RPM reference to RPMIdle value */
// 		RPMRef = Min(RPMRef, ContConst->RPMCLStartMaxRef);

// 		/* Verifes if igniter must be shut off */
// 		if (RPM > RPMIgnOff)
// 		{
// 			digitalP->bits.igniter = 0;
// 		}

// 		/* Verifies if RPM value is slower than ramp change RPM value */
// 		if (RPM < RPMChange)
// 		{
// 			/* Runs closed-loop start sub routine */
// 			PIMMStart(AltLinVecP, MNLinVecP, NcVecP,
//                 	  Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,
//                 	  ContConst, ContStartP,
//                 	  ContInputP, NcFANContMtxP,
// 					  N_KpMtxP, N_KiMtxP, Tsample);
// 		}
// 		else
// 		{
// 			/* Updates ramp change fuel value, status value and sets ramp time to 0 */
// 			*statusP = NextStatus;
// 		}

// 		/* Updates starting RPM reference */
// 		ContStartP->RPMRef = RPMRef;

// 	}

// 	/* Updates fuel value with value calculated by the function above */
// 	*WfP = ContStartP->Wf;

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		TempDecreaseCL()
//  *
//  *	PURPOSE:		Decreases engine temperature to a safer value before starting ramp
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		various


//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void TempDecreaseCL(struct ControllerConstants *ContConst, struct ControlStart *ContStartP,
//                 struct ControllerInput *ContInputP, floating *WfP, floating *RampTimeP,
// 				floating Tsample,	int *statusP, int NextStatus)
// {


// 	floating RampCoef = (-1) * ContConst->Tt4CLRampCoef;
// 	floating Tt4Init =  ContStartP->Tt4CLInit;
// 	floating Tt4Ref, Tt4Min, Tt4Max;

// 	/* Initiates Tt4Min and Tt4Max assuming that Tt4Init is higher than the safe start value */
// 	Tt4Min = ContConst->Tt4CLSafeStart;
// 	Tt4Max = Tt4Init;

// 	/* Executes temperature reduction only if ignition temperature is higher than safe start temperature */
// 	if (Tt4Init > ContConst->Tt4CLSafeStart)
// 	{
// 		/* The FuelRampSR is also suitable for calculating ramp values of any other variable, not only fuel
// 		Therefore, the same subroutine is used to calculate the temeprature reference according to a ramp function
// 		determined by its parameters */
// 		FuelRampSR(&Tt4Ref, Tt4Init, RampCoef, RampTimeP, Tsample);

// 		/* Tt4Ref must lie between Tt4Max and Tt4Min */
// 		Tt4Ref = Min(Tt4Ref,Tt4Max);
// 		Tt4Ref = Max(Tt4Ref,Tt4Min);

// 		/* Updates reference value for PITempStart use */
// 		ContStartP->Tt4CLRef = Tt4Ref;

// 		/* PI controller actuates for decreasing combustion chamber temperature */
// 		PITempStart(ContConst, ContStartP,
// 					ContInputP, Tsample);

// 		/* Updates fuel value with value calculated by the function above */
// 		*WfP = ContStartP->Wf;
// 	}

// //    printf("Inside temp reduction: eTt4k1 = %f, Tt4CLSafeStart = %f\n, ", ContStartP->eTt4k1, ContConst->Tt4CLSafeStart);
// //    printf("Inside temp reduction: RampCoef = %f, Tt4 = %f, Wf = %f\n",RampCoef, ContInputP->Tt4,ContStartP->Wf);

// 	/* If the temeprature error is small enough or if the engine ignition temperature is already lower than
// 	the safe value, next status is activated */
// 	//if (fabs(ContStartP->eTt4k1) < 0.01 * ContConst->Tt4CLSafeStart || Tt4Init < ContConst->Tt4CLSafeStart)
//     if (fabs(ContInputP->Tt4 - ContConst->Tt4CLSafeStart) <= 0.01 * ContConst->Tt4CLSafeStart || ContInputP->Tt4 <= ContConst->Tt4CLSafeStart || Tt4Init < ContConst->Tt4CLSafeStart)
// 	{
// 		/* Updates status */
// 		*statusP = NextStatus;
// 		/* Sets RampTimeP value to zero for use in next status */
// 		*RampTimeP = 0;
// 	}

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		LowFuelRamp()
//  *
//  *	PURPOSE:		Sets fuel flow value to pulse high value
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		floating *TimePulseP, floating Ts, floating PulseWidth, floating *Wf, floating WfHigh, floating Tt4, floating Tt4FlameOn, int *status, int NextStatus
//  *
//  *	RETURNS:		void
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void AccomodSR(floating *AccomTimeP, floating MaxAccomTime, floating Ts, int *StartCompleteP, floating *WfP, floating WfAccom)
// {

// 	/* Internal timer reset flag */
// 	int TRAccom = 0;

// 	/* Updates accomodation time and verifies if it has reached maximum accomodation time value */
// 	TRAccom = TimerSR(AccomTimeP, Ts, MaxAccomTime);

// 	/* If accomodation time has reached its maximum value, engine start has been completed */
// 	if (TRAccom == 1)
// 	{
// 		*StartCompleteP = 1;
// 		*WfP =WfAccom;
// 		*AccomTimeP = 0;
// 	}

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		StartLogic()
//  *
//  *	PURPOSE:		Accomplishes the necessary fuel logic for engine starging at
//  *					test bench
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		Time, Ts, TimeMax
//  *
//  *	RETURNS:		Time
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void StartLogic(struct ControllerConstants *ContConstP,struct ControlStart *ContStartP, floating RPM, floating Tt4, digital_t *digitalP, floating Tsample)
// {
// 	/* Local variables */
// 	floating Wf = ContStartP->Wf;
// 	int    IgnitionFail = ContStartP->IgnitionFail;
// 	int	   StartComplete = 0;
// 	int    OvertempFail = ContStartP->OvertempFail;
// 	int	   DigitalOut = digitalP->out;
// 	int    Inverter = digitalP->bits.inverter;
// 	int	   RecogEdge = 0;
// 	int    PulsesOn = ContStartP->PulsesOn;
// 	int    status = ContStartP->status;
// 	floating TimeIgn = ContStartP->TimeIgn;
// 	floating IgnTries = ContStartP->IgnTries;
// 	floating TimeAccom = ContStartP->TimeAccom;
// 	floating WfAccom = ContStartP->WfAccom;
// 	floating PulseWidith = ContStartP->PulseWidith;
// 	floating TimePulse = ContStartP->TimePulse;
// 	floating TimeRamp = ContStartP->TimeRamp;
// 	floating WaitTime = ContStartP->WaitTime;
// 	floating TimeBeforeRamp = ContStartP->TimeBeforeRamp;
// 	floating WfChangeRamp = ContStartP->WfChangeRamp;

// 	/*-------------------------*/
// 	/* READS FUEL PULSE WIDITH */
// 	/*-------------------------*/

// 	PulseWidith = ContConstP->WfImpulseTime;

// 	/*---------------------------------------------------*/
// 	/* SUBROUTINE FOR STARTING PROCEDURE - STATE MACHINE */
// 	/*---------------------------------------------------*/

// 	/* Fuel Pulses must be activated if RPM >= TJ1200_RPM_RELAYS_ON and Tt4 < Tt4_FLAME_ON */
// 	PulsesOn = 1;

// 	/* Verifies if pulse high widith or pulse low widith is over */
// 	switch (status)
// 	{
// 	/* STATE 0 -> Waits for positive edge on Starting key */
// 	case 0:
// 		StartEdge(ContStartP, &status, 1);
// 		break;

// 	/* STATE 1 -> Waits for RPM to reach TJ1200_RPM_RELAYS_ON and activates the digital outputs for startgint the engine */
// 	case 1:
// 		DigOutOn(RPM, ContConstP, digitalP, &status, 2);
// 		break;

// 	/* STATE 2 -> Waits for digital relays to be actually closed */
// 	case 2:
// 		StatusDelay(&WaitTime, Tsample, ContConstP->WaitAction, &status, 3);
// 		break;

// 	/* STATE 3 -> Gives initial pulse for pump release and sets fuel at initial value */
// 	case 3:
// 		FuelPulse(&TimePulse, Tsample, PulseWidith, &Wf, ContConstP->WfHighPulse, Tt4, ContConstP->Tt4AvFlameOn, &status, 4);
// 		break;

// 		/* STATE 4 -> Waits for ignition to take place, counting how long it has been since igniter was activated */
// 	case 4:
// 		IgnitAttempt(digitalP, &TimeIgn, ContConstP->TimeIgnition,
// 					Tsample, Tt4, ContConstP->Tt4AvFlameOn, &status, 3,
// 					&IgnTries,2, &Wf, ContConstP->WfInit,
// 				 	&IgnitionFail, 41);
// 		break;

// 		/* STATE 4 -> Waits for ignition to take place, counting how long it has been since igniter was activated */
// 	case 41:
// 		StatusDelay(&TimeBeforeRamp, Tsample, ContConstP->TimeBeforeRamp, &status, 5);
// 		break;

// 	/* STATE 5 -> Executes the subroutine of fuel ramp at lower rotation speeds*/
// 	case 5:

// 		FuelIncrease(ContConstP, ContStartP, digitalP, RPM, ContConstP->RPMRampChange, ContConstP->RPMIgnOff, Tt4,
// 					ContConstP->Tt4AvFlameOn, &Wf, &WfChangeRamp, ContConstP->WfInit, ContConstP->WfRampLow,
// 					&TimeRamp, Tsample, &status, 3, 51);

// 		break;

// 	/* STATE 51 -> Executes the subroutine of fuel ramp at higher rotation speeds */
// 	case 51:

// 		FuelIncrease(ContConstP, ContStartP, digitalP, RPM, ContConstP->RPMIdle, ContConstP->RPMIgnOff, Tt4,
// 					ContConstP->Tt4AvFlameOn, &Wf, &WfAccom, WfChangeRamp, ContConstP->WfRamp,
// 					&TimeRamp, Tsample, &status, 3, 6);

// 		break;

// 	/* STATE 6 -> Waits TJ1200_TIME_ACCOMODATION seconds for the engine to reach steady-state */
// 	case 6:
// 		AccomodSR(&TimeAccom, ContConstP->TimeAccomodation, Tsample, &StartComplete, &Wf, WfAccom);
// 		break;
// 	}

// 	/*---------------------*/
// 	/* INVERTER MUST BE ON */
// 	/*---------------------*/

// 	/* If the inverter is not on, the fuel pump must not be activated */
// 	if (!digitalP->bits.inverter)
// 	{
// 		Wf = 0;
// 		PulsesOn = 0;
// 	}

// 	/*-----------------*/
// 	/* OUTPUT UPDATING */
// 	/*-----------------*/

// 	/* Updates ControlStartP struct*/
// 	ContStartP->Wf = Wf;
// 	ContStartP->IgnitionFail = IgnitionFail;
// 	ContStartP->StartComplete = StartComplete;
// 	ContStartP->OvertempFail = OvertempFail;
// 	ContStartP->ControlPhase = status;
// 	ContStartP->TimeRamp = TimeRamp;
// 	ContStartP->WaitTime = WaitTime;
// 	ContStartP->TimeBeforeRamp = TimeBeforeRamp;
// 	ContStartP->WfChangeRamp = WfChangeRamp;
// 	ContStartP->TimePulse = TimePulse;
// 	ContStartP->PulseWidith = PulseWidith;
// 	ContStartP->WfAccom = WfAccom;
// 	ContStartP->PulsesOn = PulsesOn;
// 	ContStartP->status = status;
// 	ContStartP->TimeIgn = TimeIgn;
// 	ContStartP->IgnTries = IgnTries;
// 	ContStartP->TimeAccom = TimeAccom;

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		StartLogicCL()
//  *
//  *	PURPOSE:		Accomplishes the necessary fuel logic for engine starging at
//  *					test bench
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		Time, Ts, TimeMax
//  *
//  *	RETURNS:		Time
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void StartLogicCL(floating RPM, floating Tt4, digital_t *digitalP,
// 				  floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP,
//                   floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
//                   struct ControllerConstants *ContConstP, struct ControlStart *ContStartP,
//                   struct ControllerInput *ContInputP, floating *NcFANContMtxP,
// 				  floating *N_KpMtxP, floating *N_KiMtxP, floating Tsample)
// {
// 	/* Local variables */
// 	floating Wf = ContStartP->Wf;
// 	int    IgnitionFail = ContStartP->IgnitionFail;
// 	int	   StartComplete = 0;
// 	int    OvertempFail = ContStartP->OvertempFail;
// 	int	   DigitalOut = digitalP->out;
// 	int    Inverter = digitalP->bits.inverter;
// 	int	   RecogEdge = 0;
// 	int    PulsesOn = ContStartP->PulsesOn;
// 	int    status = ContStartP->status;
// 	floating TimeIgn = ContStartP->TimeIgn;
// 	floating IgnTries = ContStartP->IgnTries;
// 	floating TimeAccom = ContStartP->TimeAccom;
// 	floating WfAccom = ContStartP->WfAccom;
// 	floating PulseWidith = ContStartP->PulseWidith;
// 	floating TimePulse = ContStartP->TimePulse;
// 	floating TimeRamp = ContStartP->TimeRamp;
// 	floating WaitTime = ContStartP->WaitTime;
// 	floating TimeBeforeRamp = ContStartP->TimeBeforeRamp;
// 	floating WfChangeRamp = ContStartP->WfChangeRamp;

// 	/*-------------------------*/
// 	/* READS FUEL PULSE WIDITH */
// 	/*-------------------------*/

// 	PulseWidith = ContConstP->WfImpulseTime;

// 	/*---------------------------------------------------*/
// 	/* SUBROUTINE FOR STARTING PROCEDURE - STATE MACHINE */
// 	/*---------------------------------------------------*/

// 	/* Fuel Pulses must be activated if RPM >= TJ1200_RPM_RELAYS_ON and Tt4 < Tt4_FLAME_ON */
// 	PulsesOn = 1;

// //printf("\nStatus Inside StartLogicCL: %d\n", status);

// 	/* Verifies if pulse high widith or pulse low widith is over */
// 	switch (status)
// 	{
// 	/* STATE 0 -> Waits for positive edge on Starting key */
// 	case 0:
// 		StartEdge(ContStartP, &status, 1);
// 		break;

// 	/* STATE 1 -> Waits for RPM to reach TJ1200_RPM_RELAYS_ON and activates the digital outputs for startgint the engine */
// 	case 1:
// 		DigOutOn(RPM, ContConstP, digitalP, &status, 2);
// 		break;

// 	/* STATE 2 -> Waits for digital relays to be actually closed */
// 	case 2:
// 		StatusDelay(&WaitTime, Tsample, ContConstP->WaitAction, &status, 3);
// 		break;

// 	/* STATE 3 -> Gives initial pulse for pump release and sets fuel at initial value */
// 	case 3:
// 		FuelPulse(&TimePulse, Tsample, PulseWidith, &Wf, ContConstP->WfHighPulse, Tt4, ContConstP->Tt4AvFlameOn, &status, 4);
// 		break;

// 		/* STATE 4 -> Waits for ignition to take place, counting how long it has been since igniter was activated
// 		and updates the starting memory variables */
// 	case 4:
// 		IgnitAttempt(digitalP, &TimeIgn, ContConstP->TimeIgnition,
// 					Tsample, Tt4, ContConstP->Tt4AvFlameOn, &status, 3,
// 					&IgnTries,2, &Wf, ContConstP->WfInit,
// 				 	&IgnitionFail, 45);
// 		StartVarsUpdt(ContStartP, ContConstP, Wf, RPM, Tt4);
// 		break;

// 		/* STATE 41 -> Waits for ignition to take place, counting how long it has been since igniter was activated */
// 	case 41:
// 		StatusDelay(&TimeBeforeRamp, Tsample, ContConstP->TimeBeforeRamp, &status, 52);
// 		StartVarsUpdt(ContStartP, ContConstP, Wf, RPM, Tt4);
// 		break;

// 	/* STATE 45 -> Temperature is reduced to 950 K in order for a safer engine start - ALTERNATIVE TO STATE 41 */
// 	case 45:
// 		//StatusDelay(&TimeBeforeRamp, Tsample, ContConstP->TimeBeforeRamp, &status, 52);
// 		// TempDecreaseCL(ContConstP, ContStartP, ContInputP, &Wf,
// 		// 			   Tsample, &status, 52);
// 		TempDecreaseCL(ContConstP, ContStartP, ContInputP, &Wf, &TimeRamp,
// 				 	   Tsample,	&status, 52);

// 		/* If the status has changed, the following updates must be accomplished */
// 		if (status == 52)
// 		{
// 			/* Updates status variables */
// 			StartVarsUpdt(ContStartP, ContConstP, Wf, RPM, Tt4);
// 		}
// 		break;

// 	/* STATE 5 -> Executes the subroutine of fuel ramp at lower rotation speeds*/
// 	case 5:

// 		// FuelIncrease(digitalP, RPM, ContConstP->RPMRampChange, ContConstP->RPMIgnOff, Tt4,
// 		// 			ContConstP->Tt4AvFlameOn, &Wf, &WfChangeRamp, ContConstP->WfInit, ContConstP->WfRampLow,
// 		// 			&TimeRamp, Tsample, &status, 51);

// 		FuelIncrease(ContConstP, ContStartP, digitalP, RPM, ContConstP->RPMRampChange, ContConstP->RPMIgnOff, Tt4,
// 					ContConstP->Tt4AvFlameOn, &Wf, &WfChangeRamp, ContConstP->WfInit, ContConstP->WfRampLow,
// 					&TimeRamp, Tsample, &status, 3, 51);
// 		break;

// 	/* STATE 51 -> Executes the subroutine of fuel ramp at higher rotation speeds */
// 	case 51:

// 		// FuelIncrease(digitalP, RPM, ContConstP->RPMIdle, ContConstP->RPMIgnOff, Tt4,
// 		// 			ContConstP->Tt4AvFlameOn, &Wf, &WfAccom, WfChangeRamp, ContConstP->WfRamp,
// 		// 			&TimeRamp, Tsample, &status, 6);

// 		FuelIncrease(ContConstP, ContStartP, digitalP, RPM, ContConstP->RPMIdle, ContConstP->RPMIgnOff, Tt4,
// 					ContConstP->Tt4AvFlameOn, &Wf, &WfAccom, WfChangeRamp, ContConstP->WfRamp,
// 					&TimeRamp, Tsample, &status, 3, 6);
// 		break;

// 	/* STATE 52 -> Executes the subroutine of closed loop rotation speed ramp at lower rotation speeds */
// 	case 52:

// 		FuelIncreaseCL(digitalP, RPM, ContConstP->RPMRampChange, ContConstP->RPMIgnOff, Tt4,
// 				ContConstP->Tt4AvFlameOn, &Wf, &TimeRamp, ContConstP->RPMCLStartRamp,
// 				AltLinVecP, MNLinVecP, NcVecP,
//                 Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,
//                 ContConstP, ContStartP,
//                 ContInputP, NcFANContMtxP,
// 				N_KpMtxP, N_KiMtxP, Tsample,
// 				&status, 53);

// 		/* If the status has changed, the following updates must be accomplished */
// 		if (status == 53)
// 		{
// 			/* Updates values of ramp initial value to current RPM value */
// 			ContStartP->RPMCLInit = ContStartP->RPMRef;
// 			/* Sets TimeRamp to Tsample in order for the ramp to be properly updated */
// 			TimeRamp = Tsample;
// 		}

// 		break;

// 	/* STATE 53 -> Executes the subroutine of closed loop rotation speed ramp at higher rotation speeds */
// 	case 53:

// 		FuelIncreaseCL(digitalP, RPM, ContConstP->RPMIdle, ContConstP->RPMIgnOff, Tt4,
// 				ContConstP->Tt4AvFlameOn, &Wf, &TimeRamp, ContConstP->RPMCLStartRampFaster,
// 				AltLinVecP, MNLinVecP, NcVecP,
//                 Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,
//                 ContConstP, ContStartP,
//                 ContInputP, NcFANContMtxP,
// 				N_KpMtxP, N_KiMtxP, Tsample,
// 				&status, 6);

// 		/* Updates fuel value with value calculated by the function above */
// 		WfAccom = Wf;

// 		break;

// 	/* STATE 6 -> Waits TJ1200_TIME_ACCOMODATION seconds for the engine to reach steady-state */
// 	case 6:
// 		AccomodSR(&TimeAccom, ContConstP->TimeAccomodation, Tsample, &StartComplete, &Wf, WfAccom);
// 		break;
// 	}

// 	/*---------------------*/
// 	/* INVERTER MUST BE ON */
// 	/*---------------------*/

// 	/* If the inverter is not on, the fuel pump must not be activated */
// 	if (!digitalP->bits.inverter)
// 	{
// 		Wf = 0;
// 		PulsesOn = 0;
// 	}

// 	/*-----------------*/
// 	/* OUTPUT UPDATING */
// 	/*-----------------*/

// 	/* Updates ControlStartP struct*/
// 	ContStartP->Wf = Wf;
// 	ContStartP->IgnitionFail = IgnitionFail;
// 	ContStartP->StartComplete = StartComplete;
// 	ContStartP->OvertempFail = OvertempFail;
// 	ContStartP->ControlPhase = status;
// 	ContStartP->TimeRamp = TimeRamp;
// 	ContStartP->WaitTime = WaitTime;
// 	ContStartP->TimeBeforeRamp = TimeBeforeRamp;
// 	ContStartP->WfChangeRamp = WfChangeRamp;
// 	ContStartP->TimePulse = TimePulse;
// 	ContStartP->PulseWidith = PulseWidith;
// 	ContStartP->WfAccom = WfAccom;
// 	ContStartP->PulsesOn = PulsesOn;
// 	ContStartP->status = status;
// 	ContStartP->TimeIgn = TimeIgn;
// 	ContStartP->IgnTries = IgnTries;
// 	ContStartP->TimeAccom = TimeAccom;

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		ManualKeysSR()
//  *
//  *	PURPOSE:		Transfer input keys to digital outputs
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		RPM
//  *
//  *	RETURNS:		digitalP
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void ManualKeysSR(digital_t *digitalP, keys_t *keysP, int EngineShutDown, floating *WfP)
// {

// 	digitalP->bits.igniter = !keysP->bits.igniter_key;
// 	digitalP->bits.solenoid = !keysP->bits.shut_off_key;
// 	digitalP->bits.suction_bomb = !keysP->bits.scaveng_key;
// 	digitalP->bits.oil_pump = !keysP->bits.oil_pump_key;
// 	digitalP->bits.inverter = !keysP->bits.ac_drive_key;
// 	digitalP->bits.oil_pump_led = 0;
// 	digitalP->bits.igniter_led = 0;
// 	digitalP->bits.T4_alarm_led = 0;

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		OpenLoopSR()
//  *
//  *	PURPOSE:		Open Loop Fuel Response
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		Signal[] (must be at least a string of two elements)
//  *
//  *	RETURNS:		status
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// int OpenLoopSR(struct ControlStart *ContStartP, floating WfStart, floating *WfP)
// {

// 	/* Reads status from ContStartP */
// 	int status = ContStartP->OpenLoopStatus;
// 	floating WfMin = ( 1 - ContStartP->WfPerc ) * WfStart;
// 	floating WfMax = ( 1 + ContStartP->WfPerc ) * WfStart;

// 	switch (status)
// 	{
// 	case 0:
// 		/* Condition for fuel flow value not to be changed until it reaches a value between
// 		WfMin and WfMax  */
// 		if ((*WfP >= WfMin) & (*WfP <= WfMax)) {
// 			status = 1;
// 		}
// 		*WfP = WfStart;

// 		break;
// 	}

// 	/* Updates ContStartP */
// 	ContStartP->OpenLoopStatus = status;

// return status;

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		OnOffLogicSR()
//  *
//  *	PURPOSE:		Treatment of Start, Shut Donw and Emergency external commands
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:
//  *
//  *	RETURNS:
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void OnOffLogicSR(struct EngineOnOff *EngOnOffP, floating Ts)
// {

// 	/*------------------------------------*/
// 	/* DECLARES AUXILIARY LOCAL VARIABLES */
// 	/*------------------------------------*/

// 	/* External command */
// 	int OnOffCom = EngOnOffP->OnOffCom;

// 	/* Keys for edge verification - must be updated in the struct afterwards */
// 	int OldKey = EngOnOffP->OldKey;
// 	int CurrentKey = EngOnOffP->CurrentKey;

// 	/* Individual keys */
// 	int StartKey = EngOnOffP->StartKey;
// 	int ShutDownKey = EngOnOffP->ShutDownKey;
// 	int EmergencyKey = EngOnOffP->EmergencyKey;

// 	/* On/Off status - must be updated in the struct afterwards */
// 	int statusOnOff = EngOnOffP->statusOnOff;

// 	/* Commands */
// 	int Start = EngOnOffP->Start;
// 	int Emergency = EngOnOffP->Emergency;
// 	int ShutDown = EngOnOffP->ShutDown;
// 	// int Start = 0;//EngOnOffP->Start;
// 	// int Emergency = 0;//EngOnOffP->Emergency;
// 	// int ShutDown = 0;//EngOnOffP->ShutDown;
// 	/* Timers - must be updated in the struct afterwards */

// 	floating StartTimer = EngOnOffP->StartTimer;
// 	floating ShutDownTimer = EngOnOffP->ShutDownTimer;
// 	floating EmergencyTimer = EngOnOffP->EmergencyTimer;

// 	/* Wait timer values */
// 	floating StartWait = EngOnOffP->StartWait;
// 	floating ShutDownWait = EngOnOffP->ShutDownWait;
// 	floating EmergencyWait = EngOnOffP->EmergencyWait;

// 	/* Auxiliary timer reset flag */
// 	int TimerReset = 0;

// 	/* Flag authorizing status update */
// 	int statusUpdt = 0;

// 	/*-------------------------------------------------*/
// 	/* VERIFIES EXTERNAL KEYS COMMAND - FOR TEST BENCH */
// 	/*-------------------------------------------------*/

// 	/* Verifies if start key is set */
// 	if (StartKey == 1)
// 	{
// 		/* Updates start command value */
// 		Start = 1;
// 		/*Updates key values*/
// 		CurrentKey = 1;
// 	}
// 	/* Verifies if shut down key has been activated */
// 	if (ShutDownKey == 1)
// 	{
// 		ShutDown = 1;
// 		Emergency = 0;
// 	}
// 	/* Verifies if emergency key has been activated */
// 	if (EmergencyKey == 1)
// 	{
// 		Emergency = 1;
// 		ShutDown = 0;
// 	}

// 	/*---------------------------------*/
// 	/* STATE MACHINE FOR ENGINE ON OFF */
// 	/*---------------------------------*/

// 	if(statusOnOff == 0)
// 	{

// 		/* Verifies if start command is set */
// 		// if (OnOffCom == 0xAA)
// 		if (OnOffCom == EngOnOffP->StartCom)
// 		{
// 			/* Updates start timer */
// 			statusUpdt = TimerSR(&StartTimer, Ts, StartWait);

// 		}

// 		/* Updates on off status and start commands */
// 		if (statusUpdt == 1)
// 		{
// 				/* Updates status */
// 				statusOnOff = 1;
// 				/* Updates start command value */
// 				Start = 1;
// 				/*Updates key values*/
// 				CurrentKey = 1;
// 		}
// 	}
// 	else if(statusOnOff == 1){

// 		/*Updates current key value*/
// 		CurrentKey = 0;

// 		/* In this sate, external emergency has priority over nominal shut down */
// 		//if (OnOffCom == 0xEE)
// 		if(OnOffCom == EngOnOffP->EmergencyCom)
// 		{
// 			/* Updates start timer */
// 			Emergency = TimerSR(&ShutDownTimer, Ts, ShutDownWait);
// 			/* Sets other commands to zero */
// 			if (Emergency == 1)
// 			{
// 				Start = 0;
// 				ShutDown = 0;
// 			}

// 		}
// 		// else if (OnOffCom == 0xCC)
// 		else if (OnOffCom == EngOnOffP->ShutDownCom)
// 		{
// 			/* Updates start timer */
// 			ShutDown = TimerSR(&ShutDownTimer, Ts, ShutDownWait);
// 			/* Sets other commands to zero */
// 			if (ShutDown == 1)
// 			{
// 				Start = 0;
// 				Emergency = 0;
// 			}
// 		}
// 	}

// //printf("EmergencyKey = %d, EmergencyCom = %d\n", EmergencyKey, EngOnOffP->EmergencyCom);

// 	/* Structure updates */
// 	EngOnOffP->StartTimer = StartTimer;
// 	EngOnOffP->ShutDownTimer = ShutDownTimer;
// 	EngOnOffP->EmergencyTimer = EmergencyTimer;
// 	EngOnOffP->statusOnOff = statusOnOff;
// 	EngOnOffP->OldKey = OldKey;
// 	EngOnOffP->CurrentKey = CurrentKey;
// 	EngOnOffP->Start = Start;
// 	EngOnOffP->Emergency = Emergency;
// 	EngOnOffP->ShutDown = ShutDown;

// };



// /*------------------------------------------------------------------------------*/
// /* FUNCTIONS PRESENT IN THE OLDER VERSION - USE DURING SOFTWARE TRANSITION ONLY */
// /*------------------------------------------------------------------------------*/

// /*******************************************************************************
//  *
//  *	FUNCTION:		AirValveOpen()
//  *
//  *	PURPOSE:		Obtains the smaller value between two variables (floating)
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		RPM, ValveSR
//  *
//  *	RETURNS:		ValveSR
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// // floating AirValveOpen(struct ControlStart *ContStart, floating RPM, int EngineShutDown)
// // {

// // 	floating ValveInit = ContStart->ValveInit;
// // 	floating ValveTotal = ContStart->ValveTotal;
// // 	floating RPMValve100 = ContStart->RPMValve100;
// // 	floating RPMIdle = ContStart->RPMIdle;


// // 	//Initiates ValveSR with defined initial apperture
// // 	floating ValveSR = ValveInit;

// // 	//If rotation speed is greater or equal RPM_VALVE_100,
// // 	//valve is opened at its maximum allowed apperture
// // 	if (RPM >= RPMValve100) {
// // 		ValveSR = ValveTotal;
// // 	}

// // 	//If rotation speed is greater or equal TJ1200_RPM_IDLE or engine is shut down,
// // 	//valve must be totally closed
// // 	if ((RPM >= RPMIdle) | (EngineShutDown > 0.5)) {
// // 		ValveSR = 0;
// // 	}

// // 	return ValveSR;
// // };

// /*******************************************************************************
//  *
//  *	FUNCTION:		FuelLogicSR()
//  *
//  *	PURPOSE:		Accomplishes the necessary fuel logic for engine starging at
//  *					test bench
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		Time, Ts, TimeMax
//  *
//  *	RETURNS:		Time
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void FuelLogic(struct ControlStart *ContStartP, floating RPM, floating Tt5, FuelRamp_t *FuelSRP, digital_t *digitalP, int EngineShutDown, floating Tsample)
// {
// 	/* Local volatile variables */
// 	floating Fuel = FuelSRP->FuelFlow;
// 	int    IgnitionFail = FuelSRP->IgnitionFail;
// 	int	   StartComplete = 0;
// 	int    OvertempFail = FuelSRP->OvertempFail;
// 	int	   DigitalOut = digitalP->out;
// 	int    Inverter = digitalP->bits.inverter;
// 	int Current_key_start = FuelSRP->Current_key_start;
// 	int Old_key_start = FuelSRP->Old_key_start;
// 	int	   RecogEdge = 0;

// 	/* Local static Variables */
// 	static int PulsesOn = 0;
// 	static int status = 0;
// 	static floating TimeIgn = 0;
// 	static floating TimeOvertemp = 0;
// 	static floating TimeAccom;
// 	static floating WfAccom = 0;
// 	static floating PulseWidith = 0;
// 	static floating TimePulse = 0;
// 	static floating TimeRamp = 0;
// 	static floating WaitTime = 0;


// 	/*-----------------*/
// 	/* RESET TREATMENT */
// 	/*-----------------*/
// 	if (FuelSRP->Reset == 1)
// 	{
// 		/* Resets all static variables */
// 		PulsesOn = 0;
// 		status = 0;
// 		TimeIgn = 0;
// 		TimeOvertemp = 0;
// 		TimeAccom = 0;
// 		WfAccom = 0;
// 		TimePulse = 0;
// 		TimeRamp = 0;
// 		WaitTime = 0;

// 		/* Sets reset flag to 1 */
// 		FuelSRP->Reset = 0;
// 	}

// 	/*-------------------------*/
// 	/* READS FUEL PULSE WIDITH */
// 	/*-------------------------*/

// 	PulseWidith = ContStartP->FuelImpulseTime;

// 	/*-------------------------*/
// 	/* SUBROUTINE FOR IGNITION */
// 	/*-------------------------*/

// 	//Fuel Pulses must be activated if RPM >= TJ1200_RPM_RELAYS_ON and Tt5 < Tt5_FLAME_ON
// 	PulsesOn = 1;
// 	//Verifies if pulse high widith or pulse low widith is over

// 	switch (status)
// 	{
// 		/* STATE 0 -> Waits for positive edge on Starting key */
// 	case 0:
// 		if ((Old_key_start == 0) && (Current_key_start == 1)) // from STOP to START
// 		{
// 			status = 1;
// 		}
// 		break;

// 		/* STATE 1 -> Waits for RPM to reach TJ1200_RPM_RELAYS_ON and activates the digital outputs for startgint the engine */
// 	case 1:

// 		if ((RPM >= ContStartP->RPMRelaysOn))
// 		{
// 			//Activation of output relays
// 			digitalP->bits.igniter = 1;
// 			digitalP->bits.solenoid = 1;
// 			digitalP->bits.suction_bomb = 1;
// 			digitalP->bits.oil_pump = 1;
// 			digitalP->bits.inverter = 1;
// 			digitalP->bits.T4_alarm_led = 0;
// 			digitalP->bits.oil_pump_led = 0;
// 			digitalP->bits.igniter_led = 0;
// 			status = 2;
// 		}
// 		break;

// 		/* STATE 2 -> Waits for digital relays to be actually closed */
// 	case 2:
// 		if ((RPM >= ContStartP->RPMRelaysOn))
// 		{
// 			if (WaitTime < ContStartP->WaitAction) {
// 				WaitTime = WaitTime + Tsample;
// 			}
// 			else {
// 				status = 3;
// 			}
// 		}
// 		break;

// 		/* STATE 3 -> Gives initial pulse for pump release and sets fuel at initial value */
// 	case 3:
// 		if ((RPM >= ContStartP->RPMRelaysOn))
// 		{
// 			if (TimePulse < PulseWidith) {
// 				//Sets fuel value for high pulse value
// 				Fuel = ContStartP->FuelHighPulse;
// 				TimePulse = TimePulse + Tsample;
// 			}
// 			else {
// 				TimePulse = 0;
// 				status = 4;
// 			}
// 		}
// 		break;

// 		/* STATE 4 -> Waits for ignition to take place, counting how long it has been since igniter was activated */
// 	case 4:
// 		TimeIgn = TimeIgn + Tsample;
// 		Fuel = ContStartP->FuelInit;
// 		if (Tt5 > ContStartP->Tt5AvFlameOn) {
// 			status = 5;
// 		}
// 		break;

// 	/* STATE 5 -> Executes the subroutine of fuel ramp */
// 	case 5:

// 		/* If idle rotation speed has been reached, ramp must stop */
// 		if ((RPM < ContStartP->RPMIdle) && (Tt5 > ContStartP->Tt5AvFlameOn))
// 		{
// 			Fuel = ContStartP->FuelInit + ( ContStartP->FuelRamp ) * TimeRamp;
// 			TimeRamp = TimeRamp + Tsample;			/*if (RPM > TJ1200_RPM_IGN_OFF) {*/
// 			if (RPM > ContStartP->RPMIgnOff) {
// 				//Deactivates Ignition
// 				digitalP->bits.igniter = 0;
// 			}
// 		}
// 		if ((RPM >= ContStartP->RPMIdle) && (Tt5 > ContStartP->Tt5AvFlameOn))
// 		{
// 			status = 6;
// 			WfAccom = Fuel;
// 		}
// 		break;
// 	/* STATE 6 -> Waits TJ1200_TIME_ACCOMODATION seconds for the engine to reach steady-state */
// 	case 6:
// 		TimeAccom = TimeAccom + Tsample;
// 		if (TimeAccom >= ContStartP->TimeAccomodation) {
// 			StartComplete = 1;
// 			Fuel = WfAccom;
// 		}

// 		break;
// 	}


// 	//If Time is greater or equal TimePMin-Ts, ignition fail must be indicated
// 	if (TimeIgn >= (ContStartP->TimeIgnition))
// 	{
// 		IgnitionFail = 1;
// 	}
// 	/* If the inverter is not on, the fuel pump must not be activated */
// 	if (!digitalP->bits.inverter)
// 	{
// 		Fuel = 0;
// 		PulsesOn = 0;
// 	}

// 	///* The conditional below is not needed for the real case */
// 	//if (RPM < TJ1200_RPM_RELAYS_ON) {
// 	//	/* AIR VALVE LOGIC */
// 	//	Fuel = AirValveOpen(RPM, EngineShutDown);
// 	//}


// 	/* TEMPERATURE PROTECTION */

// 	/* If overtempreature is detected, time must be counted in order for shutdown to be activated */
// 	if (Tt5 > ContStartP->Tt5AvMax)
// 	{
// 		//Updates timer for overtemp
// 		TimeOvertemp = TimeOvertemp + Tsample;

// 		//Verifies if engine must be shut down
// 		if (TimeOvertemp > ContStartP->TimeOvertemp)
// 		{
// 			digitalP->bits.T4_alarm_led = 1;
// 		}
// 	}
// 	else
// 	{
// 		TimeOvertemp = 0;
// 	}

// 	/* Verifies if the engine must be shut down */
// 	if( EngineShutDown ){

// 		/* Shuts down the fuel flow in case engine must be shut down  */
// 		Fuel = 0;
// 		TimePulse = 0;
// 		TimeIgn = 0;
// 		TimeOvertemp = 0;
// 		PulseWidith = 0;
// 		PulsesOn = 0;
// 		StartComplete = 0;

// 		//Deactivates all relays
// 		digitalP->out = 0x00000000;
// 		status = 0;
// 	}

// 	/* Updates structure before returning it */
// 	FuelSRP->FuelFlow = Fuel;
// 	FuelSRP->IgnitionFail = IgnitionFail;
// 	FuelSRP->StartComplete = StartComplete;
// 	FuelSRP->OvertempFail = OvertempFail;
// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		DOLogic()
//  *
//  *	PURPOSE:		Treats the ditigal outputs according to rotation speed
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		RPM
//  *
//  *	RETURNS:		digitalP
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// void ManualKeys(digital_t *digitalP, keys_t *keysP, int EngineShutDown, floating *fValueP)
// {
// 	digitalP->bits.igniter = !keysP->bits.igniter_key;
// 	digitalP->bits.solenoid = !keysP->bits.shut_off_key;
// 	digitalP->bits.suction_bomb = !keysP->bits.scaveng_key;
// 	digitalP->bits.oil_pump = !keysP->bits.oil_pump_key;
// 	digitalP->bits.inverter = !keysP->bits.ac_drive_key;
// 	digitalP->bits.oil_pump_led = 0;
// 	digitalP->bits.igniter_led = 0;
// 	digitalP->bits.T4_alarm_led = 0;

// 	if (EngineShutDown) {
// 		digitalP->out = 0;
// 		*fValueP = 0;
// 	}
// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		POilLogic()
//  *
//  *	PURPOSE:		Treats the logic of oil pressure
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		RPM, POilSRP
//  *
//  *	RETURNS:		POilSRP
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/



// void POilLogic(struct ControlStart *ContStartP, floating POil, POil_t *POilSRP, digital_t *digitalp, int EngineShutDown, floating Tsample)
// {

// 	static int statusPoil=0;
// 	int    OilPumpOn;
// 	static floating TimePOil=0;

// 	/*Treats reset request*/
// 	if (POilSRP->Reset == 1)
// 	{
// 		/* Resets static variables */
// 		statusPoil = 0;
// 		TimePOil = 0;

// 		/* Sets reset flag to 0 */
// 		POilSRP->Reset = 0;
// 	}

// 	OilPumpOn =	digitalp->bits.oil_pump;

// 	int	POilAlarm = 0;
// 	int	POilFailure = 0;
// 	int Recog = 0;

// 	/* Verifies if the oil pump is activated */
// 	if(OilPumpOn)
// 	{

// 		/* Verifies if the Oil Pressure is lower then TJ1200_POIL_ALARM */
// 		if (POil < ContStartP->POilAlarm) {
// 			/* Sets Oil Pressure Alarm to 1 */
// 			POilAlarm = 1;
// 		}

// 		switch (statusPoil)
// 		{
// 			case 0:
// 				/* Verifies if oil pressure has been low for too long */
// 				if (POil < ContStartP->POilShutDown) {
// 					/* Indicates that lubrication system is failing */
// 					statusPoil = 1;
// 				}
// 			break;
// 			case 1:
// 				/* If the oil pressure is too low, increments timer and compares with TJ1200_TIME_LOW_POIL */
// 				if (TimePOil < ContStartP->TimeLowPOil) {

// 					/*Increases Timer for lubrication failure*/
// 					TimePOil = TimePOil + Tsample;

// 					if (POil > ContStartP->POilShutDown) {
// 						/* Indicates that lubrication system is OK */
// 						statusPoil = 0;
// 						TimePOil = 0;
// 					}
// 				}
// 				/* If timer has exceeded TJ1200_TIME_LOW_POIL, lubrication failure is indicated */
// 				else {
// 					POilFailure = 1;
// 				}
// 			break;
// 		}
// 	}
// 	else{
// 		/* If oil pump is not active, Timer is reset */
// 		TimePOil = 0;
// 	}

// 	if( EngineShutDown ){
// 		POilAlarm = 0;
// 		POilFailure = 0;
// 		statusPoil = 0;
// 	}

// 	/* Updates struct before it is returned */
// 	POilSRP->POilAlarm = POilAlarm;
// 	POilSRP->POilFailure = POilFailure;

// };

// /*******************************************************************************
//  *
//  *	FUNCTION:		Emergency()
//  *
//  *	PURPOSE:		Verifies if engine must be shut down
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		POilSRP
//  *
//  *	RETURNS:		EngineShutDown
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/

// int Emergency(POil_t *POilSRP, digital_t *digital, FuelRamp_t *FuelSRP, int EmergencyButton)
// {

// 	//Reads the failure flags
// 	int	POilFailure = POilSRP->POilFailure;
// 	int IgnitionFail = FuelSRP->IgnitionFail;
// 	int OvertempFail = FuelSRP->OvertempFail;
// 	int EngineShutDown = 0;

// 	//Engine must shut down in case of too low oil pressure
// 	if(POilFailure || IgnitionFail || OvertempFail || EmergencyButton){
// 		EngineShutDown = 1;
// 		digital->out = 0x00000000;
// 	}

// 	return EngineShutDown;
// };


// // /*******************************************************************************
// //  *
// //  *	FUNCTION:		Edge()
// //  *
// //  *	PURPOSE:		Edge detection of a variable
// //  *
// //  *	CALLED FROM:	tbd
// //  *
// //  *	PARAMETERS:		Signal[] (must be at least a string of two elements)
// //  *
// //  *	RETURNS:		EdgeFlag
// //  *
// //  *	COMMENTS:
// //  *
// //  *******************************************************************************/


// // int Edge(int Signal[])
// // {

// // 	/* Initiates Edge with zero value */
// // 	int	EdgeFlag = 0;

// // 	/* Signal[0] > Signal[1] -> risign edge -> Edge = 1 */
// // 	if (Signal[0] > Signal[1]) {
// // 		EdgeFlag = 1;
// // 	}

// // 	/* Signal[0] < Signal[1] -> risign edge -> Edge = 2 */
// // 	if (Signal[0] < Signal[1]) {
// // 		EdgeFlag = 2;
// // 	}

// // 	return EdgeFlag;

// // };

// /*******************************************************************************
//  *
//  *	FUNCTION:		OpenLoop()
//  *
//  *	PURPOSE:		Open Loop Fuel Response
//  *
//  *	CALLED FROM:	tbd
//  *
//  *	PARAMETERS:		Signal[] (must be at least a string of two elements)
//  *
//  *	RETURNS:		EdgeFlag
//  *
//  *	COMMENTS:
//  *
//  *******************************************************************************/


// void OpenLoop(struct ControlStart *ContStartP, floating StartFuel, floating *fValue, int Emergency, int *ResetP)
// {

// 	static int status = 0;

// 	if (*ResetP == 1)
// 	{
// 		/* Resets status */
// 		status = 0;

// 		/* Sets reset flag to 0 */
// 		*ResetP = 0;
// 	}

// 	switch (status)
// 	{
// 	case 0:
// 		/* Verifies if the value read by the valve is  */
// 		if ((*fValue >= ( 1 - ContStartP->FuelPerc ) * StartFuel) & (*fValue <= ( 1 + ContStartP->FuelPerc ) * StartFuel)) {
// 			status = 1;
// 		}
// 		*fValue = StartFuel;

// 		/*If Emergency is active, fValue receives null value*/
// 		if (Emergency == 1) {
// 			fValue = 0;
// 		}

// 		break;
// 	}

// };

// /*-------------------------------------------------------------------------------*/

