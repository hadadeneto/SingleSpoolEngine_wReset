#ifndef CONTROL_TYPES_H
#define CONTROL_TYPES_H

/*---------------------------------------*/
/* STRUCTURE FOR PI REGULATOR PARAMETERS */
/*---------------------------------------*/

/* Structure for PI parameters */
struct PIOutput
{
    /* Control Signal */
    double u;
    /* Integral Term - must be updated outside this code */
    double Iout;
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
   
    /* Double constants */
    double NDes, Ath, NMax, RefRampValue, RUMin, Tt4Max, WfMax, KbN, KbT, KpTt4, KiTt4;
    
    /* Number of sensors */
    int NumTs2Sens, NumPs3Sens, NumTt4Sens, NumRPMSens; 
    int NumVibrationSens, NumPOilSens, NumPFuelSens;

    /* Minimum number of sensors to be trusted */
    int NumTs2SensTrust, NumPs3SensTrust, NumTt4SensTrust, NumRPMSensTrust; 
    int NumVibrationSensTrust, NumPOilSensTrust, NumPFuelSensTrust; 

    /*STARTING ROUTINE PARAMETERS*/

    /* Oil Pressure Parameters */
    double POilAlarm, POilShutDown;

    /* RPM Parameters */
    double RPMValve100, RPMIdle, RPMRelaysOn, RPMIgnOff;
    double RPMRampChange, RPMCLStartRamp, RPMCLStartRampFaster, RPMCLStartMaxRef;

    /* Windmilling Valve Parameters */
    double ValveInit, ValveTotal;

    /* Tt4 Parameters */
    double Tt4AvFlameOn, Tt4AvMax, Tt4CLSafeStart, Tt4CLRampCoef;

    /* Time Parameters */
	double TimeAccomodation, WaitAction;

    /* Fuel Flow Parameters */
	double WfImpulseTime, WfHighPulse;
	double WfInit, WfRamp, WfPerc;
	double  WfRampLow, TimeBeforeRamp;

    /* NOMINAL SHUT DOWN CONSTANTS */

    /* Nominal shut down parameters */
    double ErrorFracSD;
    double RPMMinSD;
    double FuelRampSD;

    /* ENGINE STATUS PARAMETERS */

    /* Time parameters */
    double TimeWindmill, TimeReadytoStart;

    /* RPM parameters */
    double RPMWindmill;

    /* FAIL PROTECTION PARAMETERS */

    /* Time parameters */
    double TimeOverspeed;
    double TimeOvertemp;
    double TimeLowPOil, TimeHighPOil;
    double TimeLowPFuel, TimeHighPFuel;
    double TimeHighVibration;
    double TimeIgnition;
    double TimeFaultAnaylsis;

    /* Short-Open sensor values */
    double PSOpen, PSOpenThresh, PSShort, PSShortThresh;
    double PFuelOpen, PFuelShort;
    double VibOpen, VibOpenThresh, VibShort, VibShortThresh;
    double TCOpen;

    /* Thresholds */
    double TCThreshold, Tt4ShaftLock;
    double PSThreshold;
    double VibThreshold;
    double RPMThreshold;

    /* Limit Values */
    double PFuelHigh, PFuelLow;
    double POilHigh, POilLow;
    double VibHigh;

    /* ENGINE MODEL PARAMETERS */
    double POilModel, PFUelModel, VibModel;
    int NumSteps, MaxInterFault;

    /* EXTERNAL ON/OFF COMMAND PARAMETERS */
    double StartWait;
    double ShutDownWait;
    double EmergencyWait;
    int StartCom;
    int ShutDownCom;
    int EmergencyCom;

    /* PERIPHERALS TIME CONSTANTS */
    double TTCTimeConst, PSensTimeConst, FuelPumpTimeConstant;

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
    double Wf0SD;
    /* Shut down ramp timer */
    double TimeSD;

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

	/* Initial fuel value - simulation only */
	double Wf0;

	/* Ambient Inputs */
	double Altitude;
	double MN;

	/* Station 2 */
	double Tt2;
	double Pt2;

	/* Station 3 */
	double Pt3;
    
    /* Station 4 */
    double Tt4;

	/* Station 5 */
	double Tt5;

	/* Main controlled variable */
	double RPM;

	/* Thrust Command */
	double FNpc;

	/* Bearings oil pressure */
	double POil;
    
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
	double Wf, RPMRef, MinRef;
    int ControlPhase, IgnitionFail, StartComplete;
	int Active;

    /* Calculated memory variables */
    double uNk1;
	double urk1;
	double ITermNk1;
	double uTt4k1;
	double ITermTk1;
	double eNk1;
	double eTt4k1;
	double eBNk1;
	double eBTk1;

    /*---------------------------------------------------------------------------------------*/
    /* ADDITIONAL OLD VARIABLES - TO BE USED ONLY DURING SOFTWARE MIGRATION  AND ERASED LATER*/
    /*---------------------------------------------------------------------------------------*/

    double fValue, FiltRef;

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
	double ValveInit, ValveTotal, RPMValve100, RPMIdle;
	double WfImpulseTime, RPMRelaysOn, WaitAction, WfHighPulse;
	double WfInit, Tt4AvFlameOn, WfRamp, RPMIgnOff, TimeAccomodation;
	double TimeIgnition, Tt4AvMax, TimeOvertemp;
	double POilAlarm, POilShutDown, TimeLowPOil;
	double WfPerc;
	double RPMRampChange, WfRampLow, TimeBeforeRamp;

    /* Previous samples of errors and control signals */
	double uNk1, urk1, ITermNk1, uTt4k1, ITermTk1, eNk1, eTt4k1, eBNk1, eBTk1;
    double Active, RPMRef, RPMCLInit, Tt4CLInit, Tt4CLRef;

    /*The following vars come from the FuelRamp struct*/
    double Wf;	        /*Fuel Flow Value*/
	double TimePulse;	/* Time Value for Fuel Pulse */	
	double TimeIgn;		/* Time Value for Ignition */
	double PulseWidith; /* Pulse Widith*/
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
    double TimeRamp;
    double WaitTime;

	/* Local static Variables */
	int status;
	double IgnTries;
	double TimeAccom;
	double WfAccom;
	double WfChangeRamp;
    double WfTrigger;

    /* Variables for initial RPM reference ramp - smooth transition */
    double RefInit;
    int RefInitStatus;
    
    /* Variables for Open-Loop case */
    int OpenLoopStatus;

    /* Variables for engine status definition */
    double TimerWindMill, TimerReadytoStart;
    int StartCommand;

    /*---------------------------------------------------------------------------------------*/
    /* ADDITIONAL OLD VARIABLES - TO BE USED ONLY DURING SOFTWARE MIGRATION  AND ERASED LATER*/
    /*---------------------------------------------------------------------------------------*/

	double FuelImpulseTime, FuelHighPulse;
	double FuelInit, Tt5AvFlameOn, FuelRamp;
	double Tt5AvMax;
	double FuelPerc;

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
    
    double Altitude, MN, gamma_air;
    double Tt2, Ts2, Ts2Sensed, Ts2Std, Tt2StdSL, Ts2StdSL, dT;
    double Pt2, Ps2;
    double W2;
    double Pt3, Pt3Sensed;
    double W5;
    double Pt5;
    double MFP;
    double Tt4, Tt4Sensed, Wf, WfOutfp;
    double Tt5;
    double RPM;
    double FNpc;
    double Fn;
    double Fg;
    double POil;
    double PFuel;
    double Vibration;
    double Vjet;
    double MNth;
    double Ts;
    double NumSteps;

    /* Peripherals time constants */
    double TTCTimeConst, PSensTimeConst, FuelPumpTimeConstant;
    
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
    double StartTimer;
    double ShutDownTimer;
    double EmergencyTimer;

    /* Time period for confirming each command */
    double StartWait;
    double ShutDownWait;
    double EmergencyWait;

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
    double Altitude, MN;
    /* Station 2 */
    double Ts2[5];   
    /* Station 3 */
    double Pt3[5]; 
    /* Station 4 */
    double Tt4[5];
    /* Shaft */
    double RPM[5];
    /* Structure */
    double Vibration[5];
    /* Lubrication */
    double POil[5];
    /* Fuel System */
    double PFuel[5];
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
    double Model[5];
    /* Short-Circuit with Vcc - Thermocouple Only */
    double SCV[5]; 
    int SCVCount[5];
    /* Shorg-Circuit with GND - Thermocouple Only */
    double SCG[5]; 
    int SCGCount[5];
    /* Short-Circuit - Sensors Only */
    double Short[5]; 
    int ShortCount[5];
    /* Open-Circuit - Sensors and Thermocouples */
    double Open[5];
    int OpenCount[5];
    /* 1 Pulse Loss - RPM Sensor Only */
    double PulseLoss1[5];
    int PulseLoss1Count[5];
    /* 2 Pulses Loss - RPM Sensor Only */
    double PulseLoss2[5];
    int PulseLoss2Count[5];
    /* 3 Pulses Loss - RPM Sensor Only */
    double PulseLoss3[5];
    int PulseLoss3Count[5];
    /* High Value */
    double High[5];
    int HighCount[5];
    /* Low Value */
    double Low[5];
    int LowCount[5];
    /* Blow Out */
    double BlowOut[5];
    int BlowOutCount[5];
    /* Balde Loss */
    double BladeLoss[5];
    int BladeLossCount[5];
    /* Shaft Lock */
    double ShaftLock[5];
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
    double Altitude, MN;
    /* Station 2 */
    double Ts2[5];   
    /* Station 3 */
    double Pt3[5];    
    /* Station 5 */
    double Tt4[5];   
    /* Shaft */
    double RPM[5];
    /* Structure */
    double Vibration[5];
    /* Lubrication */
    double POil[5];
    /* Fuel System */
    double PFuel[5];
};
typedef struct ParsResiduals ParsResiduals;

/*-------------------------------------------------------------------------------------*/

#endif /* CONTROL_TYPES_H */
