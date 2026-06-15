#ifndef MODEL_TYPES_H
#define MODEL_TYPES_H

#include <stdint.h>

/* Structure ambient variables */
struct AmbientPars
{
    /* Ambient Variables */
    double  Alt,MN,dT,Tt,Ts,Pt,Ps,Vf;

};
typedef struct AmbientPars AmbientPars;

/* Structure for nozzle variables */
struct NozzlePars
{
	/* Ambient Variables */
	double  Wt, FAR, Pt, Ps, Tt, Ts, MN, Vj, Fg, Ath, Pamb;

};
typedef struct NozzlePars NozzlePars;

/* Structure for starting simulation */
struct EngineStart 
{
	int IgnitOn, StartingOn, statusIgn, Reset;
	double WfssIn, WfssOut, WfOut, WfIn, Ncss, POil, TimeIgn, Pt21ss, Pt3ss, Pt5ss, Pt6ss, Tt21ss, Tt3ss, Tt4ss, Tt5ss, Tt6ss;
	double Wf, Nc, Pt2, Pt21, Pt3, Pt5, Pt6, Tt2, Tt21, Tt3, Tt4, Tt5, Tt6;
    /* The variable DeltaTt calculates a delta in temperature and can be used for calculating Tt5 in the current 
     windmill and sub-idle combustion model*/
    double DeltaTt;
};
typedef struct EngineStart EngineStart;

/* Structure for particular parameters storage */
struct EnginePars
{
	int SteadyOp_Elem, PowerMan_Elem, NcFANMap_Elem, WcFANMap_Elem;
	int	NcHPCMap_Elem, WcHPCMap_Elem, NcHPTMap_Elem, PRHPTMap_Elem, WcHPTMap_Elem;
	int Alt_Elem, MN_Elem, Fn_Elem;
	double POilMin, Valve_Fuel, Ign_Time, Ign_Delta, Fuel_BOut, RPM_BOut;
	double Ath, NDes;
    double TCSCV, TCSCG, TCOPEN, PSSHORT, PFUELSHORT, PSSOPEN, Tt4HIGH, Tt4BLLCK, Tt4SHLCK, RPMHIGH, RPMSSHORT, RPMSOPEN;
    double TBearHIGH[5];
	double VIBSHORT, VIBOPEN, VIBHIGH, POILHIGH, POILLOW, PFUELHIGH, PFUELLOW;
    double PFUELMODEL, POILMODEL, VIBMODEL;
	double TTCTimeConst, PSensTimeConst, FuelPumpTimeConstant;
};
typedef struct EnginePars EnginePars;


/* Structure for engine output parameters */
struct EngineOutput
{

	/* ENGINE VARIABLES */

	/* Station 2 */
	double W2, Tt2, Ts2, Pt2, Ps2, W2c, N2c;
    /* Station 21 */
    double W21, Tt21, Pt21, W21c, N21c, PRFAN, SMFAN, BPFAN;        
	/* Station 3 */
	double Pt3, Tt3, PRHPC, SMHPC;
	/* Station 4*/
	double Pt4, Tt4, Wf;
	/* Station 5 */
	double Pt5, Tt5;
    /* Station 6 */
    double Pt6, Tt6;
	/* Station 8 */
	double Fn, Fg, V8, W8, MN8;
	/* Shaft */
	double RPM;
	/* Oil Pressure, Fuel Pressure, Vibration */
	double POil, PFuel, Vibration;
	/* Bearings temperatures */
	double TBear[5];

	/* SENSED VARIABLES - FOR MODELING SENSOR DYNAMICS */

	/* Stationn 2 */
	double Ts2Sensed;
	/* Station 3 */
	double Pt3Sensed;
	/* Station 4 */
	double Tt4Sensed;
	/* Oil Pressure, Fuel Pressure, Vibration */
	double POilSensed, PFuelSensed, VibrationSensed;
	/* Bearings temperatures */
	double TBearSensed[5];

	/* PUMP MODEL */

	/* Station 4 */
	double WfPumpOut;
	
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
    double A, B, C;        /* Space-state coefficients */
    double DelTExt;     /* Forced temperature increase */
    double ElNumRPME;   /* Number of elements in RPME break-point vector*/
    double MaxRPMP;     /* Maximum oil pump RPM */
    double RPME;        /* Engine RPM */
    double RPMP;        /* Oil Pump RPM */
    double RPMPss;      /* Operating point oil pump RPM */
    double Tss;         /* Operating point temperature */
    double Ts;          /* Sampling time */

    /* State variable */
    double T;           /* Bearing temperature */ 

    /* Output variable */
    double Tout;
};
typedef struct BearingPars BearingPars;

#endif /* MODEL_TYPES_H */
