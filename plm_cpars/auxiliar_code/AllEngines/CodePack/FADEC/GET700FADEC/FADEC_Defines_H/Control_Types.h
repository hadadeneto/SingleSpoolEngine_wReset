#ifndef CONTROL_TYPES_H
#define CONTROL_TYPES_H

#include "FloatPoint_Precision.h"

/*---------------------------------------*/
/* STRUCTURE FOR PI REGULATOR PARAMETERS */
/*---------------------------------------*/

/* Structure for PI parameters */
struct PIOutput
{
    /* Control Signal */
    floating u;
    /* Integral Term - must be updated outside this code */
    floating Iout;
};
typedef struct PIOutput PIOutput;

/*--------------------------------*/
/* STRUCTURE FOR ENGINE CONSTANTS */
/*--------------------------------*/

/* Constants used by the controller */
struct ControllerConstants
{

    /* PARAMETERS USED FOR ENGINE CALCULATIONS */

    /* Integer constants */
    int Alt_Elem, As_Elem, NcHPCMAP_Elem, WcHPCMAP_Elem, Wc_per_Nc_HPCMAP, CLLever, Fn_Elem, ManualMode, MN_Elem, UseEngUnits;
   
    /* floating constants */
    floating NDes, Ath, NMax, RefRampValue, RUMin, Tt4Max, WfMax, KbN, KbT, KpTt4, KiTt4;
    floating NMaxRef, Tt4MaxRef, Tt5MaxRef;
    
    /* Number of sensors */
    int NumTs2Sens, NumPs3Sens, NumTt4Sens, NumRPMSens; 
    int NumVibrationSens, NumPOilSens, NumPFuelSens;

    /* Minimum number of sensors to be trusted */
    int NumTs2SensTrust, NumPs3SensTrust, NumTt4SensTrust, NumRPMSensTrust; 
    int NumVibrationSensTrust, NumPOilSensTrust, NumPFuelSensTrust; 

    /*STARTING ROUTINE PARAMETERS*/

    /* Oil Pressure Parameters */
    floating POilAlarm, POilShutDown;

    /* RPM Parameters */
    floating RPMValve100, RPMIdle, RPMRelaysOn, RPMIgnOff;
    floating RPMRampChange, RPMCLStartRamp, RPMCLStartRampFaster, RPMCLStartMaxRef;

    /* Windmilling Valve Parameters */
    floating ValveInit, ValveTotal;

    /* Tt4 Parameters */
    floating Tt4AvFlameOn, Tt4AvMax, Tt4CLSafeStart, Tt4CLRampCoef, Tt4RampDecFast;

    /* Time Parameters */
	floating TimeAccomodation, WaitAction;

    /* Fuel Flow Parameters */
	floating WfImpulseTime, WfHighPulse;
	floating WfInit, WfRamp, WfPerc;
	floating  WfRampLow, TimeBeforeRamp;
    floating WfRampDec, WfRampDecFast, WfRampDecLowLim;
    floating WfKdStart;

    /* Parameters used during start with electric motor */
    floating StrtInit, StrtMax, StrtRampCoeff, StrtRPMOff, StrtWhich;

    /* NOMINAL SHUT DOWN CONSTANTS */

    /* Nominal shut down parameters */
    floating ErrorFracSD;
    floating RPMMinSD;
    floating FuelRampSD;
    floating TimeToRampSD;
    floating TimeToEmergSD;

    /* ENGINE STATUS PARAMETERS */

    /* Time parameters */
    floating TimeWindmill, TimeReadytoStart;

    /* RPM parameters */
    floating RPMWindmill;

    /* Fn command parameters */
    floating FNIdle;

    /* FAIL PROTECTION PARAMETERS */

    /* Time parameters */
    floating TimeOverspeed;
    floating TimeOvertemp;
    floating TimeLowPOil, TimeHighPOil;
    floating TimeLowPFuel, TimeHighPFuel;
    floating TimeHighVibration;
    floating TimeIgnition;
    floating TimeFaultAnaylsis;
    floating TimeBearOverTemp[5];

    /* Short-Open sensor values */
    floating RPMShort, RPMOpen;
    floating PSOpen, PSOpenThresh, PSShort, PSShortThresh;
    floating PFuelOpen, PFuelShort;
    floating POilOpen, POilShort;
    floating VibOpen, VibOpenThresh, VibShort, VibShortThresh;
    floating TCOpen;

    /* Thresholds */
    floating TCThreshold, Ts2Threshold, Tt4Threshold, Tt4ShaftLock, Tt4BlowOut;
    floating PSThreshold, Pt3Threshold, Pt3ShaftLock, Pt3BlowOut;
    floating VibThreshold;
    floating RPMThreshold, RPMShaftLock, RPMBlowOut;
    floating POilThreshold, PFuelThreshold;

    /* Limit Values */
    floating PFuelHigh, PFuelLow;
    floating POilHigh, POilLow;
    floating VibHigh;

    /* ENGINE MODEL PARAMETERS */
    floating POilModel, PFUelModel, VibModel;
    int NumSteps, MaxInterFault;

    /* EXTERNAL ON/OFF COMMAND PARAMETERS */
    floating StartWait;
    floating ShutDownWait;
    floating EmergencyWait;
    int StartCom;
    int ShutDownCom;
    int EmergencyCom;

    /* PERIPHERALS TIME CONSTANTS */
    floating TTCTimeConst, PSensTimeConst, FuelPumpTimeConstant;

    /* BEARINGS PARAMETERS */
    int NumBear;
    floating KpBear, KiBear, KbBear, OPRPMInt, OPRPMMax, OPRPMMin, RPMOilInt, RPMOilOn;
    floating TMaxBear[5], TRefBear[5];

    /* BOOSTER PARAMETERS */
    floating BoostTime;

};
typedef struct ControllerConstants ControllerConstants;

/*----------------------------------*/
/* STRUCTURE FOR CONTROLLER INPUTS */
/*----------------------------------*/

/* Structure containing the controller input parameters */
struct ControllerInput
{

    /* Flag indicating shut down status */
    int StatusSD;
    /* Flag indicating shut down ramp initial fuel value */
    floating Wf0SD;
    /* Shut down ramp timer */
    floating TimeSD;
    floating TimeToRampSD;    /* Time allowed before ramp execution in nominal shut off */
    floating TimeToEmergSD;   /* Time allowed before emergency sequence execution in nominal shut off */

	/* Flag indicating that reset has been requested */
	int Reset;

	/* Flag indicating that start must be skipped */
	int SkipStart;
	
	/* Digital Inputs */
	int Old_key_start;
	int Current_key_start;
	int bits_inverter;
	int Mode;
	int LeverMode;
    int EngUnits;

    /* Activation of external thrust command */
    int ThrustCommandOn;    

	/* Initial fuel value - simulation only */
	floating Wf0;

	/* Ambient Inputs */
	floating Altitude;
	floating MN;

	/* Station 2 */
	floating Tt2;
	floating Pt2;

	/* Station 3 */
	floating Pt3;
    
    /* Station 4 */
    floating Tt4;

	/* Station 5 */
	floating Tt5;

	/* Main controlled variable */
	floating RPM;

	/* Thrust Command */
	floating FNpc;

	/* Bearings oil pressure */
	floating POil;

    /* Booster parameters */
    int statusBooster;
    floating TimerBoost;                            
    
    /*-----------------------------------------------*/
    /* AUXILIARY STARTCOMPLETE - used in T-MATS only */
    /*-----------------------------------------------*/
    
    int TMATS_StartComplete;
    
    /*-----------------------------------------------*/

};
typedef struct ControllerInput ControllerInput;

/*----------------------------------*/
/* STRUCTURE FOR CONTROLLER OUTPUTS */
/*----------------------------------*/

/* Struct containing controller outputs */
struct ControllerOutput
{

    /* Calculated output */
	floating Wf, RPMRef, MinRef;
    int ControlPhase, IgnitionFail, StartComplete;
	int Active;

    /* Calculated memory variables */
    floating uNk1;
	floating urk1;
	floating ITermNk1;
	floating uTt4k1;
	floating ITermTk1;
	floating eNk1;
	floating eTt4k1;
	floating eBNk1;
	floating eBTk1;

    /*---------------------------------------------------------------------------------------*/
    /* ADDITIONAL OLD VARIABLES - TO BE USED ONLY DURING SOFTWARE MIGRATION  AND ERASED LATER*/
    /*---------------------------------------------------------------------------------------*/

    floating fValue, FiltRef;

    /*---------------------------------------------------------------------------------------*/

};
typedef struct ControllerOutput ControllerOutput;

/*------------------------------*/
/* STRUCTURE FOR STARTING LOGIC */
/*------------------------------*/

/* Struct containing the necessary parameters for engine start */
struct ControlStart
{

    /* PARAMETERS USED AT START LOGIC */

    /* Parameters used for comparison */
	floating ValveInit, ValveTotal, RPMValve100, RPMIdle;
	floating WfImpulseTime, RPMRelaysOn, WaitAction, WfHighPulse;
	floating WfInit, Tt4AvFlameOn, WfRamp, RPMIgnOff, TimeAccomodation;
	floating TimeIgnition, Tt4AvMax, TimeOvertemp;
	floating POilAlarm, POilShutDown, TimeLowPOil;
	floating WfPerc;
	floating RPMRampChange, WfRampLow, TimeBeforeRamp;

    /* Previous samples of errors and control signals */
	floating uNk1, urk1, ITermNk1, uTt4k1, ITermTk1, eNk1, eTt4k1, eBNk1, eBTk1;
    floating Active, RPMRef, RPMCLInit, Tt4CLInit, Tt4CLRef;

    /*The following vars come from the FuelRamp struct*/
    floating Wf;	        /*Fuel Flow Value*/
	floating TimePulse;	/* Time Value for Fuel Pulse */	
	floating TimeIgn;		/* Time Value for Ignition */
	floating PulseWidith; /* Pulse Widith*/
	int PulsesOn;		/* Flag indicating that fuel pulses are being generated */
	int IgnitionFail;	/* Flag indicating if ignition has failed */
	int StartComplete;	/* Flag indicating if stargin sequence is complete */
	int OvertempFail;	/* Flag indicating if overtemperature has happened for too long */
    int ControlPhase;
    int Start;
    int RampAllowed;    /* Flag indicating if fuel increase is allowed during open loop starting fuel ramp - FuelIncrease function */
    int Current_key_start;
    int Old_key_start;

    /* Reset Flag */
	int Reset;

    /* Time parameters */
    floating TimeRamp;
    floating WaitTime;

	/* Local static Variables */
	int status;
	int IgnTries;
	floating TimeAccom;
	floating WfAccom;
	floating WfChangeRamp;
    floating WfTrigger;

    /* Variables for initial RPM reference ramp - smooth transition */
    floating RefInit;
    int RefInitStatus;
    
    /* Variables for Open-Loop case */
    int OpenLoopStatus;

    /* Variables for engine status definition */
    floating TimerWindMill, TimerReadytoStart;
    int StartCommand;

    /* Electric motor speed */
    floating StrtRPMAct;

    /*---------------------------------------------------------------------------------------*/
    /* ADDITIONAL OLD VARIABLES - TO BE USED ONLY DURING SOFTWARE MIGRATION  AND ERASED LATER*/
    /*---------------------------------------------------------------------------------------*/

	floating FuelImpulseTime, FuelHighPulse;
	floating FuelInit, Tt5AvFlameOn, FuelRamp;
	floating Tt5AvMax;
	floating FuelPerc;

    /*---------------------------------------------------------------------------------------*/

};
typedef struct ControlStart ControlStart;

/*-------------------------------*/
/* STRUCTURE FOR ENGINE MODELING */
/*-------------------------------*/

/* Struct containing the estimated engine parameters */
struct EstimatedPars
{
    
    /*
     * Tt2      - Total temperature at compressor inlet at ISA + dT conditions
     * Ts2      - Static temperature at compressor inlet at ISA + dT conditions1
     * Ts2Std   - Static temperature at compressor inlet at ISA + 0 conditions
     * Ts2StdSL - Static temperature at compressor inlet at ISA + 0 and Sea Level 
     */
    
    floating Altitude, MN, gamma_air;
    floating Tt2, Ts2, Ts2Sensed, Ts2Std, Tt2StdSL, Ts2StdSL, dT;
    floating Pt2, Ps2;
    floating W2;
    floating Pt3, Pt3Sensed;
    floating W5;
    floating Pt5;
    floating MFP;
    floating Tt4, Tt4Sensed, Wf, WfOutfp;
    floating Tt5;
    floating RPM;
    floating FNpc;
    floating Fn;
    floating Fg;
    floating POil;
    floating PFuel;
    floating Vibration;
    floating Vjet;
    floating MNth;
    floating Ts;
    floating NumSteps;

    /* Bearing temperatures */
    floating TBear[5];

    /* Peripherals time constants */
    floating TTCTimeConst, PSensTimeConst, FuelPumpTimeConstant;
    
    /* Number of interactions for fautl identification */
    int MaxInter;
};
typedef struct EstimatedPars EstimatedPars;

/*--------------------------------------------------------*/
/* STRUCTURE FOR ENGINE START/SHUT OFF/EMERGENCY COMMANDS */
/*--------------------------------------------------------*/

/* Struct containing the engine sensed parameters */
struct EngineOnOff
{
    /* Status for start/shut down/emergency verification */
    int statusOnOff;

    /* External command */
    // int OnOffCom[2];
    int OnOffCom;

    /* Keys for edge verification */
    int CurrentKey;
    int OldKey;

    /* External keys - alternative to external commabnd activation way */
    int StartKey;
    int ShutDownKey;
    int EmergencyKey;

    /* Engine commands */
    int Start;
    int ShutDown;
    int Emergency;

    /* Timers for detecting each status */
    floating StartTimer;
    floating ShutDownTimer;
    floating EmergencyTimer;

    /* Time period for confirming each command */
    floating StartWait;
    floating ShutDownWait;
    floating EmergencyWait;

    /* Exteranal command words */
    int StartCom;
    int ShutDownCom;
    int EmergencyCom;

};
typedef struct EngineOnOff EngineOnOff;

/*-------------------------------------------------*/
/* STRUCTURE CONTAINING ENGINE SENSORED PARAMETERS */
/*-------------------------------------------------*/

/* Struct containing the engine sensed parameters */
struct SensedPars
{
    /* Ambient */
    floating Altitude, MN;
    /* Station 2 */
    floating Ts2[5];   
    /* Station 3 */
    floating Pt3[5]; 
    /* Station 4 */
    floating Tt4[5];
    /* Shaft */
    floating RPM[5];
    /* Structure */
    floating Vibration[5];
    /* Lubrication */
    floating POil[5];
    /* Fuel System */
    floating PFuel[5];
    /* Bearings - each sensor corresponds to a different bearing */
    floating TBear[5];
};
typedef struct SensedPars SensedPars;

/*------------------------------------------*/
/* STRUCTURE CONTAINING RESIDUAL PARAMETERS */
/*------------------------------------------*/

/* Structure containing the parameters residuals */
struct AllResiduals
{
   
    /* Counters for hard and soft fault detections */
    int HardCount[5];
    int SoftCount[5];
    
    /* Normal operation */
    floating Model[5];
    /* Short-Circuit with Vcc - Thermocouple Only */
    floating SCV[5]; 
    int SCVCount[5];
    /* Shorg-Circuit with GND - Thermocouple Only */
    floating SCG[5]; 
    int SCGCount[5];
    /* Short-Circuit - Sensors Only */
    floating Short[5]; 
    int ShortCount[5];
    /* Open-Circuit - Sensors and Thermocouples */
    floating Open[5];
    int OpenCount[5];
    /* 1 Pulse Loss - RPM Sensor Only */
    floating PulseLoss1[5];
    int PulseLoss1Count[5];
    /* 2 Pulses Loss - RPM Sensor Only */
    floating PulseLoss2[5];
    int PulseLoss2Count[5];
    /* 3 Pulses Loss - RPM Sensor Only */
    floating PulseLoss3[5];
    int PulseLoss3Count[5];
    /* High Value */
    floating High[5];
    int HighCount[5];
    /* Low Value */
    floating Low[5];
    int LowCount[5];
    /* Blow Out */
    floating BlowOut[5];
    int BlowOutCount[5];
    /* Balde Loss */
    floating BladeLoss[5];
    int BladeLossCount[5];
    /* Shaft Lock */
    floating ShaftLock[5];
    int ShaftLockCount[5];
    
    /* INDEX POSITION OF RESIDUALS */
    /*
     *0  - Model
     *1  - SCV 
     *2  - SCG
     *3  - Short
     *4  - Open
     *5  - Pulse Loss 1
     *6  - Pulse Loss 2
     *7  - Pulse Loss 3
     *8  - Oil Choke
     *9  - Oil Lack
     *10 - Fuel Choke
     *11 - Fuel Lack
     *12 - Blade Loss
     *13 - Shaft Lock
     */
    /* This stirng can be used for any indications about each residual */
    int ResPosition[5][20];
    
};
typedef struct AllResiduals AllResiduals;

/*-------------------------------------------------------------------------------------*/
/* ADDITIONAL STRUCT PRESENT AT OLDER VERSION - TO BE ERASED AFTER SOFTWARE TRANSITION */
/*-------------------------------------------------------------------------------------*/

/* Structure containing the parameters residuals */
struct ParsResiduals
{
    /* Ambient */
    floating Altitude, MN;
    /* Station 2 */
    floating Ts2[5];   
    /* Station 3 */
    floating Pt3[5];    
    /* Station 5 */
    floating Tt4[5];   
    /* Shaft */
    floating RPM[5];
    /* Structure */
    floating Vibration[5];
    /* Lubrication */
    floating POil[5];
    /* Fuel System */
    floating PFuel[5];
};
typedef struct ParsResiduals ParsResiduals;

/*------------------------------------*/
/* STRUCTURE FOR GENERAL PI VARIABLES */
/*------------------------------------*/

/* Struct containing PI controller variables - to be applied to more general problems,
such as oil control */
struct ControllerGeneral
{
    /* Number of controlled variables */
    int NumContVar;

    /* Controller sampling time */
    floating Ts;

    /* Inputs */
    floating Ref[5];
    floating Input[5];

    /* Calculated output */
	floating u[5];
	int Active[5];

    /* Calculated memory variables */
    floating uk1[5];
    floating urk1[5];
	floating ITermk1[5];
	floating ek1[5];
	floating eBk1[5];

    /* Controller gains */
    floating Kp[5];
    floating Ki[5];
    floating Kb[5];

    /* Maximum control signal values */
    floating uMax[5];
    floating uMin[5];

    /* Real Output */
    floating uOut[5];

};
typedef struct ControllerGeneral ControllerGeneral;

/*-------------------------------------------------------------------------------------*/

#endif /* CONTROL_TYPES_H */
