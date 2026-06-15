/*		T-MATS -- Ambient_TMATS.c
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % NASA Glenn Research Center, Cleveland, OH
 * % Aug 12, 2014
 * %
 * %  This file converts Altitude and MN to common engine input variables.
 * % *************************************************************************/

#include <math.h>
#include "constants_TMATS.h"
#include "Env_SampTime.h"
#include "functions_TMATS.h"
#include "Model_Types.h"
#include "MtxIntFunctions.h"
#include "Interpolation_Types.h"

/* -------------------------------------------------- */
/* INCLUDE - T-MATS & PWLM                            */
/* (To be usedi in MATLAB and TMATS simulations only) */
/* -------------------------------------------------- */

#include "mex.h"

/* -------------------------------------------------- */


void StartingEngine(struct EngineStart *Pointer, struct EnginePars *ParsP, 
                    double *AwmMtxP, double *AshMtxP, double *BwmMtxP, 
                    double *BshMtxP, double *RPMwmMtxP, double *RPMshMtxP, double *WfshMtxP, 
                    double *Tt4CshMtxP, double *Tt4DshMtxP, double *Tt4shMtxP,
                    double *A, double *B, double *D, double RPM, double NDes,
                    double MN, double Mwm, double *MNLinVecP, double MN_Elem,
                    double Altitude, double *AltLinVecP, double Alt_Elem,
                    double Fnpc, double *FNPerContMtxP, double Fn_Elem,
                    double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
                    double PNdotSL, double PuSL, double PNSL, double PTSL, 
                    double PNdot, double Pu, double PN, double PT,
                    double Tsample)
{

	static double TimeIgn = 0;
	static double TimeZero = 0;
    double Dummy1D = 1;
    double Awm;
    double Ash;
    double Bwm;
    double Bsh;
    double Ncsh;
    double Tt4Dsh;
    double RPMwm;
    double RPMsh;
    double Tt4sh;
    double Tt5sh;
    double Wfsswm;
    double Wfsssh;
    double Wfwm;
//     double Wfsh;
    
    InterpIndex3D Index3D;
    InterpIndex Index1D;
    
    /* Gets the indexes MN with fake Altitude and Fnpc values suitable for using InterpInd3DRPM */
    InterpInd3DRPM(Altitude, Mwm, Fnpc, AltLinVecP, MNLinVecP, FNPerContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Alt_Elem, MN_Elem, Fn_Elem, &Index3D);
// double Teste = InterpValue(&Index3D, FNPerContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, MN_Elem * Fn_Elem, Fn_Elem);        
    /* Shifts the indexes of Index3D for finding a 2D element */
    Index3D.kRPM = Index3D.kMN;
    Index3D.kRPMH = Index3D.kMNH;
    Index3D.fRPM = Index3D.fMN;
    Index3D.kMN = 0;
    Index3D.kMNH = 0;
    Index3D.fMN = 0;
    Index3D.kA = 0;
    Index3D.kAH = 0;
    Index3D.fA = 0;
    
// double Teste = InterpValue(&Index3D, MNLinVecP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, MN_Elem, MN_Elem);
    
// mexPrintf("\n\nAltitude = %f",Altitude);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nAlt_Elem = %f",Alt_Elem);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nkA = %d",Index3D.kA);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nkAH = %d",Index3D.kAH);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nfA = %f",Index3D.fA);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\n\nMN = %f",MN);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nMN_Elem = %f",MN_Elem);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nkMN = %d",Index3D.kMN);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nkMNH = %d",Index3D.kMN);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nfMN = %f",Index3D.fMN);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\n\nFnpc = %f",Fnpc);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nFn_Elem = %f",Fn_Elem);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nkRPM = %d",Index3D.kRPM);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nkRPMH = %d",Index3D.kRPMH);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nfRPM = %f",Index3D.fRPM);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nTeste = %f",Teste);//PARA TESTE SOMENTE!!APAGAR DEPOIS

    
    /* Calculate matrices coefficients */
    Awm = InterpValue(&Index3D, AwmMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,  MN_Elem, MN_Elem);
    Bwm = InterpValue(&Index3D, BwmMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,  MN_Elem, MN_Elem);
    RPMwm = InterpValue(&Index3D, RPMwmMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,  MN_Elem, MN_Elem);
    
// mexPrintf("\n\nMwm = %f",Mwm);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\n\nAwm = %f",Awm);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nBwm = %f",Bwm);//PARA TESTE SOMENTE!!APAGAR DEPOIS
    
    /* Corrects values of coeffients for corret use outside of this function */
    Awm = Awm * PNdotSL / PNdot * PN / PNSL;
    Bwm = Bwm * PNdotSL / PNdot * Pu / PuSL;
    
    /* Coeffients for hot sub-idle */
    Ash = *AshMtxP;
    Bsh = *BshMtxP;
    
// Ash = -0.005;
// Bsh = 60000;
// Ash = -0.05;
// Bsh = 12000;
//Bsh = 80000;
    
    Tt4Dsh = *Tt4DshMtxP;
    //Tt4Dsh = 4000;
    Tt4sh = *Tt4shMtxP;
    Tt5sh = Tt4sh;
    RPMsh = *RPMshMtxP;
    Wfsssh = *WfshMtxP;
    Ncsh = RPMsh / PN / NDes;
    
//     /* Corrects Ash to an interpolated value */
//     Ash = (Pointer->Nc - Ncsh)/(Pointer->Ncss - Ncsh) * (*A - Ash) + Ash;
//     
//     /* Corrects Ash to an interpolated value */
//     Bsh = (Pointer->Nc - Ncsh)/(Pointer->Ncss - Ncsh) * (*B - Bsh) + Bsh;
//   
//     /* Corrects Ash to an interpolated value */
//     Wfsssh = (Pointer->Nc - Ncsh)/(Pointer->Ncss - Ncsh) * (Pointer->WfssIn - Wfsssh) + Wfsssh;

    
    /* Finds the right value of Wfsssh */
    Wfsssh = Wfsssh * RPM / RPMsh;
    Wfsssh = Wfsssh * PuSL / Pu;
//mexPrintf("\nWfss = %f",Wfsssh);//PARA TESTE SOMENTE!!APAGAR DEPOIS
    
    /* Corrects values of coeffients for corret use outside of this function */
    Ash = Ash * PNdotSL / PNdot * PN / PNSL;
    Bsh = Bsh * PNdotSL / PNdot * Pu / PuSL;
    Tt4Dsh = Tt4Dsh * PTSL / PT * Pu / PuSL;
    Tt4sh = Tt4sh * PTSL / PT;

    /* Gets the indexes mapping RPM in RPMwmMtx vector */
    InterpInd3DRPM(Altitude, RPM, Fnpc, AltLinVecP, RPMwmMtxP, FNPerContMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, Alt_Elem, MN_Elem, Fn_Elem, &Index3D);

    /* Shifts the indexes of Index3D for finding a 2D element */
    Index3D.kRPM = Index3D.kMN;
    Index3D.kRPMH = Index3D.kMNH;
    Index3D.fRPM = Index3D.fMN;
    Index3D.kMN = 0;
    Index3D.kMNH = 0;
    Index3D.fMN = 0;
    Index3D.kA = 0;
    Index3D.kAH = 0;
    Index3D.fA = 0;
    
    /*  From the indexes above, gets the corresponding value of MN
     for the equation RPM = RPM + B * (Wf - Wfss) to be properly used. 
     The value of the corresponding MN in MNLinVec for the indexes above
     will serve as Wfss, as Mwm will serve as Wf. The equation, therefore,
     becomes RPM = RPM + B * (Mwf - MN)*/
    Wfsswm = InterpValue(&Index3D, MNLinVecP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP,  MN_Elem, MN_Elem);
    Wfwm = Mwm;
    
    /* Corrects the value of Wfss for correct use */
    Wfsswm = Wfsswm * PuSL / Pu;
        
//     Ash = InterpValue(&Index3D, AshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, 1, 1);
//     Bsh = InterpValue(&Index3D, BshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, 1, 1);
//     Tt4Dsh = InterpValue(&Index3D, Tt4DshMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, 1, 1);
//     Tt4sh = InterpValue(&Index3D, Tt4shMtxP, Mtx2DP, Mtx2DHP, Mtx1DP, Mtx1DHP, 1, 1);
    
// mexPrintf("\n\nAltitude = %f",Altitude);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nAlt_Elem = %f",Alt_Elem);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nkA = %d",Index3D.kA);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nkAH = %d",Index3D.kAH);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nfA = %f",Index3D.fA);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\n\nMN = %f",MN);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nMN_Elem = %f",MN_Elem);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nkMN = %d",Index3D.kMN);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nkMNH = %d",Index3D.kMN);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nfMN = %f",Index3D.fMN);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\n\nFnpc = %f",Fnpc);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nFn_Elem = %f",Fn_Elem);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nkRPM = %d",Index3D.kRPM);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nkRPMH = %d",Index3D.kRPMH);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nfRPM = %f",Index3D.fRPM);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\n\nAwm = %f",Awm);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nBwm = %f",Bwm);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nAsh = %f",Ash);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nBsh = %f",Bsh);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nRPM = %f",RPM);//PARA TESTE SOMENTE!!APAGAR DEPOIS
//mexPrintf("\nWfss = %f",Wfsssh);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nTt4sh = %f",Tt4sh);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nTt4Dsh = %f",Tt4Dsh);//PARA TESTE SOMENTE!!APAGAR DEPOIS


	/* Verifies if reset has been requested */
	if (Pointer->Reset == 1) 
	{
		/* If reset is requested, resets static variables and sets reset flag to zero */
		TimeIgn = 0;
		TimeZero = 0;
		Pointer->Reset = 0;
	}

	/* Loads Engine Parameters */
	double Fuel_BOut = ParsP->Fuel_BOut;
	double Ign_Delta = ParsP->Ign_Delta;
	double Ign_Time = ParsP->Ign_Time;
	double POilMin = ParsP->POilMin;
	double Valve_Fuel = ParsP->Valve_Fuel;

	/* Loades number of elements of engine matrices */
	double NcFANMap_Elem = ParsP->NcFANMap_Elem;
	double NcHPCMap_Elem = ParsP->NcHPCMap_Elem;
	double NcHPTMap_Elem = ParsP->NcHPTMap_Elem;
	double PowerMan_Elem = ParsP->PowerMan_Elem;
	double PRHPTMap_Elem = ParsP->PRHPTMap_Elem;
	double SteadyOp_Elem = ParsP->SteadyOp_Elem;
	double WcFANMap_Elem = ParsP->WcFANMap_Elem;
	double WcHPCMap_Elem = ParsP->WcHPCMap_Elem;
	double WcHPTMap_Elem = ParsP->WcHPTMap_Elem;

	/* Calculates the value of the oil pressure */

	Pointer->POil = POilMin;

	/* Calculates the current steady-state fuel flow to be sent to the model*/

	Pointer->WfssOut = Pointer->WfssIn / Pointer->Ncss * Pointer->Nc;
	Pointer->Pt21 = Pointer->Pt2 + (Pointer->Pt21ss - Pointer->Pt2) / Pointer->Ncss * Pointer->Nc;
	Pointer->Pt3 = Pointer->Pt2 + (Pointer->Pt3ss - Pointer->Pt2) / Pointer->Ncss * Pointer->Nc;
	Pointer->Pt5 = Pointer->Pt2 + (Pointer->Pt5ss - Pointer->Pt2) / Pointer->Ncss * Pointer->Nc;
	Pointer->Pt6 = Pointer->Pt2 + (Pointer->Pt6ss - Pointer->Pt2) / Pointer->Ncss * Pointer->Nc;
// mexPrintf("\nStatusIgn = %d",Pointer->statusIgn);
// mexPrintf("\nTsample = %f; TimeIgn = %f; Ign_Time = %f",Tsample,TimeIgn,Ign_Time);
// mexPrintf("\nWf = %f; WfBlowOut = %f;",Pointer->WfOut,Fuel_BOut);
	switch (Pointer->statusIgn)
	{
	/* Ignition has not yet been activated and engine is in windmill */
	case 0:
        Pointer->Tt5 = Pointer->Tt2 + (Pointer->Tt3ss - Pointer->Tt2) * Pointer->Nc / Pointer->Ncss;
		Pointer->Tt6 = Pointer->Tt2 + (Pointer->Tt3ss - Pointer->Tt2) * Pointer->Nc / Pointer->Ncss;
		Pointer->Tt4 = Pointer->Tt5;
        
        /* Calculates the coefficients A and C */
//         *B = Bwm;
//         *A = Awm;
//mexPrintf("\nB = %f",B);//PARA TESTE SOMENTE!!APAGAR DEPOIS
        
		if (Pointer->IgnitOn) {
			Pointer->statusIgn = 1;
		}
		/* Sets the ammount of fuel before ignition for simulation of windmill */
		Pointer->WfOut = Valve_Fuel;

        /* Sets the state-space coefficients */
        *B = Bwm;
        *A = Awm;
        *D = 0;
        Pointer->WfOut = Wfwm;
        Pointer->WfssOut = Wfsswm;
        Pointer->Tt4ss = Pointer->Tt4;
        Pointer->DeltaTt = Pointer->DeltaTt * 0;
        
		//Waits a small fraction for zero rotation to be shown in graphic
		if(TimeZero < 0.50){
			TimeZero = TimeZero + Tsample;
// 			Pointer->WfOut = 0;
           Pointer->WfOut = Wfsswm;
		}
        
		break;

	/* Time starts counting after ignition is active */
	case 1:
		Pointer->Tt5 = Pointer->Tt2 + (Pointer->Tt3ss - Pointer->Tt2) * Pointer->Nc / Pointer->Ncss;
		Pointer->Tt6 = Pointer->Tt2 + (Pointer->Tt3ss - Pointer->Tt2) * Pointer->Nc / Pointer->Ncss;
		Pointer->Tt4 = Pointer->Tt5;
		TimeIgn = TimeIgn + Tsample;

		/* Sets the ammount of fuel before ignition for simulation of windmill */
		//Pointer->WfOut = Valve_Fuel;

        /* If ignition is not active, the status flag is set to 0. If the fuel flow value 
        is less than the blow out value, ignition does not take place */
		if (!Pointer->IgnitOn & (TimeIgn < Ign_Time)) {
//mexPrintf("\nFirst Condition = Sets TimeIgn to 0 and status to 0 and Wf = %f", Pointer->WfOut);
			Pointer->statusIgn = 0;
			TimeIgn = 0;
		}
        else if (Pointer->WfOut <= Fuel_BOut)
        {
//mexPrintf("\nSecond Condition = Sets TimeIgn to 0 and Wf = %f", Pointer->WfOut);
            TimeIgn = 0;
        }
		else if (TimeIgn >= Ign_Time) {
//mexPrintf("\nThird Condition = changes state to 2 and Wf = %f", Pointer->WfOut);
			TimeIgn = 0;
			Pointer->statusIgn = 2;
		}
        
        /* Sets the state-space coefficients */
        *B = Bwm;
        *A = Awm;
        *D = 0;
        Pointer->WfOut = Wfwm;
        Pointer->WfssOut = Wfsswm;
        Pointer->Tt4ss = Pointer->Tt4;
        Pointer->DeltaTt = Pointer->DeltaTt * 0;
        
		break;
        
	case 2:
		/* Dynamics after ignition */	
		Pointer->Tt6 = Ign_Delta + (Pointer->Tt6ss - Ign_Delta) * Pointer->Nc / Pointer->Ncss;
		Pointer->Tt5 = Ign_Delta + (Pointer->Tt5ss - Ign_Delta) * Pointer->Nc / Pointer->Ncss;
		Pointer->Tt4 = Ign_Delta + (Pointer->Tt4ss - Ign_Delta) * Pointer->Nc / Pointer->Ncss;

        /* Sets the state-space coefficients */
        if(RPM >= RPMsh){
            
            /* Corrects hot sub-idle parameters to an interpolated value */
            Ash = (Pointer->Nc - Ncsh)/(Pointer->Ncss - Ncsh) * (*A - Ash) + Ash;
            Bsh = (Pointer->Nc - Ncsh)/(Pointer->Ncss - Ncsh) * (*B - Bsh) + Bsh;
            Wfsssh = (Pointer->Nc - Ncsh)/(Pointer->Ncss - Ncsh) * (Pointer->WfssIn - Wfsssh) + Wfsssh;
            Tt4Dsh = (Pointer->Nc - Ncsh)/(Pointer->Ncss - Ncsh) * (*D - Tt4Dsh) + Tt4Dsh;
            Tt4sh = (Pointer->Nc - Ncsh)/(Pointer->Ncss - Ncsh) * (Pointer->Tt4ss - Tt4sh) + Tt4sh;
            Pointer->DeltaTt = (Pointer->Nc - Ncsh)/(Pointer->Ncss - Ncsh) * Pointer->DeltaTt;
            
        }
        
// if(RPM < 7000){
// //         Pointer->WfOut = Wf;
// //         Pointer->WfssOut = Wfsssh;
// mexPrintf("\nNc = %f",Pointer->Nc);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nNcss = %f",Pointer->Ncss);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nNcsh = %f",Ncsh);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nA = %f",*A);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nAsh = %f",Ash);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// mexPrintf("\nB = %f",*B);//PARA TESTE SOMENTE!!APAGAR DEPOIS
//mexPrintf("\nTt4shNew = %f",Tt4sh);//PARA TESTE SOMENTE!!APAGAR DEPOIS
// }   
        *B = Bsh;
        *A = Ash;
        *D = Tt4Dsh;
        Pointer->WfssOut = Wfsssh;
        Pointer->Tt4ss = Tt4sh;

		/* If the fuel flow level lies below FUEL_BOUT, the engine is shut off */
		if (Pointer->WfOut < Fuel_BOut) {
			Pointer->statusIgn = 0;
		}
		break;

	}
	
}

