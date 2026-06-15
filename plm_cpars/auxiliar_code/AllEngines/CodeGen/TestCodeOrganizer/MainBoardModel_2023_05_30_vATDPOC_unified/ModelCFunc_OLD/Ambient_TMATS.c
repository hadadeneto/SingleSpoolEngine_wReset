/*		T-MATS -- Ambient_TMATS.c
 * % *************************************************************************
 * % written by Jeffryes Chapman
 * % NASA Glenn Research Center, Cleveland, OH
 * % Aug 12, 2014
 * %
 * %  This file converts Altitude and MN to common engine input variables.
 * % *************************************************************************/

#include <math.h>
#include "constants_TMATS.h"
#include "SI_AU_Convert.h"
#include "functions_TMATS.h"
#include "Model_Types.h"


void Ambient_TMATS(struct AmbientPars *Pointer){
  
        
    double X_A_AltVec[15] = {-5000, 0, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 60000, 70000, 80000};
    double T_A_TsVec[15] = {536.51, 518.67, 500.84, 483.03, 465.22, 447.41, 429.62, 411.84, 394.06, 389.97, 389.97, 389.97, 389.97, 392.25, 397.69};
    double T_A_PsVec[15] = {17.554, 14.696, 12.228, 10.108, 8.297, 6.759, 5.461, 4.373, 3.468, 2.73, 2.149, 1.692, 1.049, 0.651, 0.406};
    double FAR = 0;
    double Rt = 0.0686;
    double gammasg = 1.4;
// double X_A_FARVec = {0, 0.0050, 0.0100, 0.0150, 0.0200, 0.0250, 0.0300};
// double T_A_RtArray = {0.0686, 0.0686, 0.0686, 0.0686, 0.0686, 0.0686, 0.0686};
// double Y_A_TVec = {1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4, 1.4};
//
    double AltIn = Pointer->Alt;
    double MNIn = Pointer->MN;
    double dTempIn = Pointer->dT;
    
    int interpErr = 0;
    
    double Rs = Rt;
    double TsOut;
    double PsOut;
    double Sout;
    double hs;
    
    double Ttg;
    double Ptg;
    double Ptg_new;
    double Ptg_old;
    double htg;
    double Vg;
    double Vsg;
    double MNg;
    
    double er;
    double maxiter;
    double iter = 0;
    double erthr = 0.001;
    double er_old = er;
    
// /* ------- get strings -------------- */
// char * BlkNm;
// int_T buflen;
// int_T status;
//
// /* Get name of block from dialog parameter (string) */
// buflen = mxGetN(BN_p(S))*sizeof(mxChar)+1;
// BlkNm = mxMalloc(buflen);
// status = mxGetString(BN_p(S), BlkNm, buflen);
    
//FAR = AFARc;
    
// Rt = interp1Ac(X_A_FARVec,T_A_RtArray,FAR,B,&interpErr);
// if (interpErr == 1 && ssGetIWork(S)[Er1] == 0){
//     printf("Warning in %s, Error calculating Rt. Vector definitions may need to be expanded.\n", BlkNm);
//     ssSetIWorkValue(S,Er1,1);
// }
    
//Rs = Rt;
    
/* Unit Correction */
AltIn = AltIn*Alt_GIn;
dTempIn = dTempIn*T_GIn;
    
/*  Static Temperature */
//TsStDayOut = interp1Ac(X_A_AltVec,T_A_TsVec,AltIn,A,&interpErr);
TsOut = interp1Ac(&X_A_AltVec,&T_A_TsVec,AltIn,15,&interpErr);
    
// if (interpErr == 1 && ssGetIWork(S)[Er2] == 0){
//     printf("Warning in %s, Error calculating TsStDayOut. Vector definitions may need to be expanded.\n", BlkNm);
//     ssSetIWorkValue(S,Er2,1);
// }
//TsOut = TsStDayOut + dTempIn;
TsOut = TsOut + dTempIn;
Pointer->Ts = TsOut*T_GOut;
    
    
/* Static Pressure*/
PsOut = interp1Ac(X_A_AltVec,T_A_PsVec,AltIn,15,&interpErr);
Pointer->Ps = PsOut*P_GOut;
// if (interpErr == 1 && ssGetIWork(S)[Er3] == 0){
//     printf("Warning in %s, Error calculating PsOut. Vector definitions may need to be expanded.\n", BlkNm);
//     ssSetIWorkValue(S,Er3,1);
// }
//
/* Calc output entropy */
Sout = pt2sc(PsOut, TsOut, FAR);
/* Determine Static enthalpy */
hs = t2hc(TsOut,FAR);

/* Pt guess */
/*------ Total Temperature ---------*/
Ttg = TsOut * (1+MNIn*MNIn*(C_GAMMA-1)/2);
/*------ Total Pressure ---------*/
Ptg = PsOut*divby((powT((TsOut*divby(Ttg)),(C_GAMMA*divby(C_GAMMA-1)))));

/* calculate total temperature */
Ttg = sp2tc(Sout,Ptg,FAR);
/* calculate total enthalpy */
htg = t2hc(Ttg,FAR);
/* calculate velocity */
Vg = sqrtT(2 * (htg - hs)*C_GRAVITY*JOULES_CONST);

// gammasg = interp2Ac(X_A_FARVec,Y_A_TVec,T_A_gammaArray,FAR,TsOut,B,C,&interpErr);
// if (interpErr == 1 && ssGetIWork(S)[Er4] == 0){
//     printf("Warning in %s, Error calculating iteration gammasg. Vector definitions may need to be expanded.\n", BlkNm);
//     ssSetIWorkValue(S,Er4,1);
// }
Vsg = sqrtT(gammasg*Rs*TsOut*C_GRAVITY*JOULES_CONST);
MNg = Vg*divby(Vsg);
er = MNIn - MNg;
Ptg_new = Ptg + 0.05;
maxiter = 15;
iter = 0;
erthr = 0.001;

while (fabs(er) > erthr && iter < maxiter) {
    er_old = er;
    Ptg_old = Ptg;
    if(fabs(Ptg - Ptg_new) < 0.03)
        Ptg = Ptg + 0.05;
    else
        Ptg = Ptg_new;

    /* calculate Total emperature */
    Ttg = sp2tc(Sout,Ptg,FAR);
    /* calculate total enthalpy */
    htg = t2hc(Ttg,FAR);
    /* calculate velocity */
    Vg = sqrtT(2 * (htg - hs)*C_GRAVITY*JOULES_CONST);

    Vsg = sqrtT(gammasg*Rs*TsOut*C_GRAVITY*JOULES_CONST);
    MNg = Vg*divby(Vsg);
    er = MNIn - MNg;
    if (fabs(er) > erthr) {
        /* determine next guess pressure by secant algorithm */
        Ptg_new = Ptg - er *(Ptg - Ptg_old)*divby(er - er_old);
    }
    iter = iter + 1;
}
// if (iter == maxiter && ssGetIWork(S)[Er5]==0 ){
//     printf("Warning in %s, Error calculating Pt at input MN. There may be error in output pressure\n", BlkNm);
//     ssSetIWorkValue(S,Er5,1);
// }

Pointer->Tt = Ttg*T_GOut;
Pointer->Pt = Ptg*P_GOut;
Pointer->Vf = Vsg * MNIn * Alt_GOut;

// htOut = htg;
// TtOut = Ttg;
// PtOut = Ptg;
//
// /*---- Engine Velocity ---------*/
// Vsound = Vsg;
// VengOut = Vsound * MNIn;
//
// FAROut = FAR;
//
//Test = divby(dTempIn);
    
}

