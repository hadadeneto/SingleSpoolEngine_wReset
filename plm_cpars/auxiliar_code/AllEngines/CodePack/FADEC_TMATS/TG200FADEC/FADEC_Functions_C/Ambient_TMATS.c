/*		T-MATS -- Ambient_TMATS.c
 * % *************************************************************************
 * % written by Jeffryes Chapman
 * % NASA Glenn Research Center, Cleveland, OH
 * % Aug 12, 2014
 * %
 * %  This file converts Altitude and MN to common engine input variables.
 * % *************************************************************************/

#include <math.h>
#include "../FADEC_Defines_H/constants_TMATS.h"
#include "../FADEC_Defines_H/SI_AU_Convert.h"
#include "../FADEC_Functions_H/functions_TMATS.h"
#include "../FADEC_Defines_H/Model_Types.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"


void Ambient_TMATS(struct AmbientPars* Pointer) {


	floating X_A_AltVec[15] = { -5000, 0, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 60000, 70000, 80000 };
	floating T_A_TsVec[15] = { 536.51, 518.67, 500.84, 483.03, 465.22, 447.41, 429.62, 411.84, 394.06, 389.97, 389.97, 389.97, 389.97, 392.25, 397.69 };
	floating T_A_PsVec[15] = { 17.554, 14.696, 12.228, 10.108, 8.297, 6.759, 5.461, 4.373, 3.468, 2.73, 2.149, 1.692, 1.049, 0.651, 0.406 };
	floating FAR = 0;
	floating Rt = 0.0686;
	floating gammasg = 1.4;

	floating AltIn = Pointer->Alt;
	floating MNIn = Pointer->MN;
	floating dTempIn = Pointer->dT;

	int interpErr = 0;

	floating Rs = Rt;
	floating TsOut;
	floating PsOut;
	floating Sout;
	floating hs;

	floating Ttg;
	floating Ptg;
	floating Ptg_new;
	floating Ptg_old;
	floating htg;
	floating Vg;
	floating Vsg;
	floating MNg;

	floating er = 0;
	floating maxiter;
	floating iter = 0;
	floating erthr = 0.001;
	floating er_old = er;


	/* Unit Correction */
	AltIn = AltIn * Alt_GIn;
	dTempIn = dTempIn * T_GIn;

	/*  Static Temperature */
	//TsOut = interp1Ac(&X_A_AltVec,&T_A_TsVec,AltIn,15,&interpErr);
	TsOut = interp1Ac(X_A_AltVec, T_A_TsVec, AltIn, 15, &interpErr);
	/* Addition of day temperature variation (ISA + dTempIn) */
	TsOut = TsOut + dTempIn;
	Pointer->Ts = TsOut * T_GOut;


	/* Static Pressure*/
	PsOut = interp1Ac(X_A_AltVec, T_A_PsVec, AltIn, 15, &interpErr);
	Pointer->Ps = PsOut * P_GOut;

	/* Calc output entropy */
	Sout = pt2sc(PsOut, TsOut, FAR);
	/* Determine Static enthalpy */
	hs = t2hc(TsOut, FAR);

	/* Pt guess */
	/*------ Total Temperature ---------*/
	Ttg = TsOut * (1 + MNIn * MNIn * (C_GAMMA - 1) / 2);
	/*------ Total Pressure ---------*/
	Ptg = PsOut * divby((powT((TsOut * divby(Ttg)), (C_GAMMA * divby(C_GAMMA - 1)))));

	/* calculate total temperature */
	Ttg = sp2tc(Sout, Ptg, FAR);
	/* calculate total enthalpy */
	htg = t2hc(Ttg, FAR);
	/* calculate velocity */
	Vg = sqrtT(2 * (htg - hs) * C_GRAVITY * JOULES_CONST);

	/* Initial guess and errors for sound speed and flight Mach number */
	Vsg = sqrtT(gammasg * Rs * TsOut * C_GRAVITY * JOULES_CONST);
	MNg = Vg * divby(Vsg);
	er = MNIn - MNg;
	Ptg_new = Ptg + 0.05;
	maxiter = 15;
	iter = 0;
	erthr = 0.001;

	/* Interaction loop for refining sound speed and flight Mach number */
	while (fabs(er) > erthr && iter < maxiter) {
		er_old = er;
		Ptg_old = Ptg;
		if (fabs(Ptg - Ptg_new) < 0.03)
			Ptg = Ptg + 0.05;
		else
			Ptg = Ptg_new;

		/* calculate Total emperature */
		Ttg = sp2tc(Sout, Ptg, FAR);
		/* calculate total enthalpy */
		htg = t2hc(Ttg, FAR);
		/* calculate velocity */
		Vg = sqrtT(2 * (htg - hs) * C_GRAVITY * JOULES_CONST);

		Vsg = sqrtT(gammasg * Rs * TsOut * C_GRAVITY * JOULES_CONST);
		MNg = Vg * divby(Vsg);
		er = MNIn - MNg;
		if (fabs(er) > erthr) {
			/* determine next guess pressure by secant algorithm */
			Ptg_new = Ptg - er * (Ptg - Ptg_old) * divby(er - er_old);
		}
		iter = iter + 1;
	}

	/* Updates total temperature, total pressore and fligt speed */
	Pointer->Tt = Ttg * T_GOut;
	Pointer->Pt = Ptg * P_GOut;
	Pointer->Vf = Vsg * MNIn * Alt_GOut;

}

