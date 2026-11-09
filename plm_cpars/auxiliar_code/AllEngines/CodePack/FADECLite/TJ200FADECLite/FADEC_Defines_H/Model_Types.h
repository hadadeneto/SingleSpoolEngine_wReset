#ifndef MODEL_TYPES_H
#define MODEL_TYPES_H

#include <stdint.h>

#include "FloatPoint_Precision.h"

/* Structure ambient variables */
struct AmbientPars
{
    /* Ambient Variables */
    floating  Alt,MN,dT,Tt,Ts,Pt,Ps,Vf;

};
typedef struct AmbientPars AmbientPars;

/* Structure for nozzle variables */
struct NozzlePars
{
	/* Ambient Variables */
	floating  Wt, FAR, Pt, Ps, Tt, Ts, MN, Vj, Fg, Ath, Pamb;

};
typedef struct NozzlePars NozzlePars;

/* Structure for starting simulation */
struct EngineStart 
{
	/* Flags */
	int IgnitOn, StartingOn, statusIgn, Reset;
	/* State-space parameters */
	floating A, B, Pt21D, Pt3D, Pt5D, Pt6D, Tt21D, Tt3D, Tt4D, Tt5D, Tt6D;
	/* Steady values */
	floating WfssIn, WfssOut, WfOut, WfIn, Ncss, POil, TimeIgn, Pt21ss, Pt3ss, Pt5ss, Pt6ss, Tt21ss, Tt3ss, Tt4ss, Tt5ss, Tt6ss;
	/* Variables */
	floating Wf, Nc, Pt2, Pt21, Pt3, Pt5, Pt6, Tt2, Tt21, Tt3, Tt4, Tt5, Tt6;
    /* The variable DeltaTt calculates a delta in temperature and can be used for calculating Tt5 in the current 
     windmill and sub-idle combustion model*/
    floating DeltaTt;
};
typedef struct EngineStart EngineStart;

/* Structure for particular parameters storage */
struct EnginePars
{
	int SteadyOp_Elem, PowerMan_Elem, NcFANMap_Elem, WcFANMap_Elem;
	int	NcHPCMap_Elem, WcHPCMap_Elem, NcHPTMap_Elem, PRHPTMap_Elem, WcHPTMap_Elem;
	int Alt_Elem, MN_Elem, Fn_Elem;
	floating POilMin, Valve_Fuel, Ign_Time, Ign_Delta, Fuel_BOut, RPM_BOut;
	floating Ath, NDes;
    floating TCSCV, TCSCG, TCOPEN, PSSHORT, PFUELSHORT, PSSOPEN, Tt4HIGH, Tt4BLLCK, Tt4SHLCK, RPMHIGH, RPMSSHORT, RPMSOPEN;
    floating TBearHIGH[5];
	floating VIBSHORT, VIBOPEN, VIBHIGH, POILHIGH, POILLOW, PFUELHIGH, PFUELLOW;
    floating PFUELMODEL, POILMODEL, VIBMODEL;
	floating TTCTimeConst, PSensTimeConst, FuelPumpTimeConstant;
};
typedef struct EnginePars EnginePars;


/* Structure for engine output parameters */
struct EngineOutput
{

	/* ENGINE VARIABLES */

	/* Station 2 */
	floating W2, Tt2, Ts2, Pt2, Ps2, W2c, N2c;
    /* Station 21 */
    floating W21, Tt21, Pt21, W21c, N21c, PRFAN, SMFAN, BPFAN;        
	/* Station 3 */
	floating Pt3, Tt3, PRHPC, SMHPC;
	/* Station 4*/
	floating Pt4, Tt4, Wf;
	/* Station 5 */
	floating Pt5, Tt5;
    /* Station 6 */
    floating Pt6, Tt6;
	/* Station 8 */
	floating Fn, Fg, V8, W8, MN8;
	/* Shaft */
	floating RPM;
	/* Oil Pressure, Fuel Pressure, Vibration */
	floating POil, PFuel, Vibration;
	/* Bearings temperatures */
	floating TBear[5];

	/* SENSED VARIABLES - FOR MODELING SENSOR DYNAMICS */

	/* Stationn 2 */
	floating Ts2Sensed;
	/* Station 3 */
	floating Pt3Sensed;
	/* Station 4 */
	floating Tt4Sensed;
	/* Oil Pressure, Fuel Pressure, Vibration */
	floating POilSensed, PFuelSensed, VibrationSensed;
	/* Bearings temperatures */
	floating TBearSensed[5];

	/* PUMP MODEL */

	/* Station 4 */
	floating WfPumpOut;
	
	/* FLAGS FOR NON-WINDMILLING INITIAL CONDITIONS */

	/* Initial Condition Flags */
	int ICCalc, ICAuthorize;

	/* FLAGS FOR CHOOSING PROPER MODEL - SUBIDLE OR IDLE AND ABOVE */

	/* Flag for model choice */
	int WhichModel;

};
typedef struct EngineOutput EngineOutput;

/* Structure for Bearing model parameters */
struct BearingPars
{
    /* Input */
    floating A, B, C;        /* Space-state coefficients */
    floating DelTExt;     /* Forced temperature increase */
    floating ElNumRPME;   /* Number of elements in RPME break-point vector*/
    floating MaxRPMP;     /* Maximum oil pump RPM */
    floating RPME;        /* Engine RPM */
    floating RPMP;        /* Oil Pump RPM */
    floating RPMPss;      /* Operating point oil pump RPM */
    floating Tss;         /* Operating point temperature */
    floating Ts;          /* Sampling time */

    /* State variable */
    floating T;           /* Bearing temperature */ 

    /* Output variable */
    floating Tout;
};
typedef struct BearingPars BearingPars;

#endif /* MODEL_TYPES_H */
