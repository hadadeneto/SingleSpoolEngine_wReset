
/*		T-MATS -- Nozzle_TMATS.c
 * % *************************************************************************
 * % written by Jeffryes Chapman based on work by R. May and T. Lavelle
 * % NASA Glenn Research Center, Cleveland, OH
 * % February 27th, 2013
 * %
 * %  This file models the Nozzle Element for T-MATS simulation
 * % *************************************************************************/

#include <math.h>
#include "constants_TMATS.h"
#include "SI_AU_Convert.h"
#include "functions_TMATS.h"
#include "Model_Types.h"

/* -------------------------------------------------- */
/* INCLUDE - T-MATS & PWLM                            */
/* (To be usedi in MATLAB and TMATS simulations only) */
/* -------------------------------------------------- */

#include "mex.h"

/* -------------------------------------------------- */

void Nozzle_TMATS(struct NozzlePars *Pointer)
{
   
    double WIn;     /* Input Flow [pps] 	*/
    double htIn;     /* enthaply [BTU/lbm] 	*/
    double TtIn;     /* Temperature Input [degR] 	*/
    double PtIn;     /* Pressure Input [psia] 	*/
    double FARcIn;     /* Combusted Fuel to Air Ratio [frac] 	*/
    double PambIn;     /* Ambient Pressure [psia] 	*/
    double AthroatIn;     /* Throat area [in2] 	*/
    double AexitIn;     /* Exit area [in2] 	*/
    
	/* Define used matrices */
	double X_A_AltVec[15] = { -5000, 0, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 60000, 70000, 80000 };
	double T_A_TsVec[15] = { 536.51, 518.67, 500.84, 483.03, 465.22, 447.41, 429.62, 411.84, 394.06, 389.97, 389.97, 389.97, 389.97, 392.25, 397.69 };
	double T_A_PsVec[15] = { 17.554, 14.696, 12.228, 10.108, 8.297, 6.759, 5.461, 4.373, 3.468, 2.73, 2.149, 1.692, 1.049, 0.651, 0.406 };
	double FAR = 0;
	double Y_N_FARVec[7] = {0, 0.0050, 0.0100, 0.0150, 0.0200, 0.0250, 0.0300};
	double T_N_RtArray[7] = {0.0686, 0.0686, 0.0686, 0.0686, 0.0686, 0.0686, 0.0686};
	double T_N_MAP_gammaArray[14] = {1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4};
	double X_N_TVec[20] = {300, 10000};

    /* Define Constants */
    double choked, Ts, rhos, V, Test, MN1, Ptin;
    double CdTh, Cv, Cfg, Therm_growth, PQPa, PQPaMap, AthroatHot;
    double Rt, TsMN1, PsMN1, Woutcalc;
    double WOut, FgOut, NErrorOut, Ath, Vth, Psth, Ax, Vx, Psx, Tsx, gammasx, MNx;
    double gammatg, gammasth,gammasMN1, gammasg, MNg, TsMNg, PsMNg, PsMNg_new, PsMNg_old, VMN1;
    double MNth, Tsth, rhosth, rhosMN1, rhosx;
    double Axcalc, Psxg, Psxg_new, Psxg_old, Exthr;
    double Athcalc, Psthg, Psthg_new, Psthg_old;
    double Sin, hsg, hs, htin, rhosg, Rs, Vg;
    double gammas_s, MN_s, V_s, rhos_s, Ts_s;
    double Ex, Ex_old;
    double erMN_old, erMN, erthr;
    int maxiter, iter, maxiterx, iterx, CDNoz;
    int interpErr = 0;
        
	/* Reads Inputs */
	PtIn = Pointer->Pt;
	TtIn = Pointer->Tt;
	FARcIn = Pointer->FAR;
	WOut = Pointer->Wt;
	PambIn = Pointer->Pamb;
	Ath = Pointer->Ath;

	/* Converts to American Units for using TMATS software directly */
	PtIn = PtIn * P_GIn;
	TtIn = TtIn * T_GIn;
	WOut = WOut * W_GIn;
	Ath = Ath * Area_GIn;
	PambIn = PambIn * P_GIn;

    /* Calc entropy */
    Sin = pt2sc(PtIn, TtIn, FARcIn);
    
    /* Compute Input enthalpy */
    htin = t2hc(TtIn,FARcIn);
    
    /*  Where gas constant is R = f(FAR), but NOT P & T */
	Rt = 0.0686;
    Rs = Rt;
      
    /* Warn if there is the potential for back flow */
    Ptin = PtIn;
 
    /* Determine ideal velocity defined by perfect expansion to Pambient */
    PcalcStat(Ptin, PambIn, TtIn, htin, FARcIn, Rt, &Sin, &Ts, &hs, &rhos, &V);
 
	gammas_s = 1.4;
    MN_s = V*divby(sqrtT(gammas_s*Rs*Ts*C_GRAVITY*JOULES_CONST));
    Ts_s = Ts;
    V_s = V;
    rhos_s = rhos;
        
    /* Determine if nozzle throat is choked by comparing pressure when MN = 1 to ambient pressure
     * ---- set MN = 1 and calc throat Ps for iteration IC --------*/
    MNg = 1;
	gammatg = 1.4;
 
    /* Use isentropic equations for a first cut guess */
    TsMNg = TtIn*divby(1+MNg*MNg*(gammatg-1)/2);
    PsMNg = Ptin*powT((TsMNg*divby(TtIn)),(gammatg*divby(gammatg-1)));
    
    /* Calculate velcocity and MN using guessed static pressure */
    PcalcStat(Ptin, PsMNg, TtIn, htin, FARcIn, Rt, &Sin, &TsMNg, &hsg, &rhosg, &Vg);
	gammasg = 1.4;
    MNg = Vg*divby(sqrtT(gammasg*Rs*TsMNg*C_GRAVITY*JOULES_CONST));
    
    /* Determine error based on calculated MN and 1 */
    erMN = 1 - MNg;
    
    PsMNg_new = PsMNg + 0.05;
    maxiter = 200;
    iter = 0;
    erthr = 0.001;
    
    /* if Ps is not close enough to Ps at MN = 1, iterate to find Ps at MN = 1 */
    while (fabs(erMN) > erthr && iter < maxiter) {
        erMN_old = erMN;
        PsMNg_old = PsMNg;
        if(fabs(PsMNg - PsMNg_new) < 0.003)
            PsMNg = PsMNg + 0.005;
        else
            PsMNg = PsMNg_new;
        PcalcStat(Ptin, PsMNg, TtIn, htin, FARcIn, Rt, &Sin, &TsMNg, &hsg, &rhosg, &Vg);
		gammasg = 1.4;
	    MNg = Vg*divby(sqrtT(gammasg*Rs*TsMNg*C_GRAVITY*JOULES_CONST));
        erMN = 1 - MNg;

        /*  */
        if (fabs(erMN) > erthr) {
            /* Determine next guess pressure by secant algorithm */
            PsMNg_new = PsMNg - erMN *(PsMNg - PsMNg_old)*divby(erMN - erMN_old);
        }
        iter = iter + 1;
    }

    /*  MN = 1 parameters */
    TsMN1 = TsMNg;
    PsMN1 = PsMNg;
    rhosMN1 = rhosg;
    gammasMN1 = gammasg;
    VMN1 = Vg;
    
    /* Determine if Nozzle is choked  */
    if (PsMN1<PambIn)
        choked = 0;
    else {
        choked = 1;
    }
    
    /* Throat not choked, set Psth to ideal expansion to Pambient values */
    if (choked ==0){
        Psth = PambIn;
        Tsth = Ts_s;
        Vth = V_s;
        rhosth = rhos_s;
        MNth = MN_s;
    }
    /* If nozzle is choked, determine throat parameters based on MN = 1 values */
    else{  
        Psth = PsMN1;
        Tsth = TsMN1;
        MNth = 1;
		gammasth = 1.4;
        Vth = MNth*sqrtT(gammasth*Rs*Tsth*C_GRAVITY*JOULES_CONST);
        rhosth = rhosMN1;
    }
     
    /* Pressure before nozzle/P ambient */
    PQPa = Ptin*divby(PambIn);
    
    /* cacluate Thermal Constants */
    PQPaMap = PQPa;
    
    /* Look up Flow Coefficient */
	CdTh = 1;
                 
    /* Lookup thrust and velocity coefficients */
	Cv = 1;
	Cfg = 0.99;

    /* Calculatio of gross thrust */
	FgOut = (WOut / C_GRAVITY)*Vth*Cv + (Psth - PambIn)*Ath;

	/* Updates Outputs */
	Pointer->MN = MNth;
	Pointer->Fg = FgOut * Thrust_GOut;
	Pointer->Vj = Vth * Alt_GOut;

}
