
#include "Control_Types.h"
#include "ConstantsGEJ85.h"

void getGEJ85ContConst(struct ControllerConstants *ContConst)
{
    
    /*--------------------------*/
    /* CONTROL REGIME CONSTANTS */
    /*--------------------------*/

    /* PI Constants */
    ContConst->KpTt4 = GEJ85_KPTT4;
	ContConst->KiTt4 = GEJ85_KITT4;
    ContConst->KbT = GEJ85_KBT;
    ContConst->KbN = GEJ85_KBN;
    
    /* Elements numbers */
    ContConst->Alt_Elem = GEJ85_ALT_ELEM;
    ContConst->As_Elem = GEJ85_AS_ELEM;
    ContConst->Fn_Elem = GEJ85_FN_ELEM;
    ContConst->MN_Elem = GEJ85_MN_ELEM;
    ContConst->NcHPCMAP_Elem = GEJ85_FAN_NC;
    ContConst->WcHPCMAP_Elem = GEJ85_FAN_NC * GEJ85_FAN_PR;
    ContConst->Wc_per_Nc_HPCMAP = GEJ85_FAN_PR;
    
    /* Flags */
    ContConst->CLLever = GEJ85_CLOOP;
    ContConst->ManualMode = GEJ85_MANUAL;
    ContConst->UseEngUnits = GEJ85_ENGUNITS;
    
    /* Design Point */
    ContConst->NDes = GEJ85_NDES;
    ContConst->Ath = GEJ85_Ath_NOZZLE;
    
    /* Limiters */
    ContConst->NMax = GEJ85_NMAX;
    ContConst->NMaxRef = GEJ85_NMAX;
    ContConst->RefRampValue = GEJ85_REFRAMP;
    ContConst->RUMin = GEJ85_RUMIN;
    ContConst->Tt4Max = GEJ85_TT4MAX; 
    ContConst->Tt4MaxRef = GEJ85_TT4MAXREF;
    ContConst->WfMax = GEJ85_WFMAX;
    
    /* Sensors Numbers */
    ContConst->NumTs2Sens = GEJ85_TS2SENS;
    ContConst->NumPs3Sens = GEJ85_PS3SENS;
    ContConst->NumTt4Sens = GEJ85_TT4SENS;
    ContConst->NumRPMSens = GEJ85_RPMSENS;
    ContConst->NumVibrationSens = GEJ85_VIBRATIONSENS;
    ContConst->NumPOilSens = GEJ85_POILSENS;
    ContConst->NumPFuelSens = GEJ85_PFUELSENS;

    /* Miminum number of trusted sensors */
    ContConst->NumTs2SensTrust = GEJ85_TS2SENSTRUST;
    ContConst->NumPs3SensTrust = GEJ85_PS3SENSTRUST;    
    ContConst->NumTt4SensTrust = GEJ85_TT4SENSTRUST;
    ContConst->NumRPMSensTrust = GEJ85_RPMSENSTRUST;

    /*--------------------------*/
    /* STARGING LOGIC CONSTANTS */
    /*--------------------------*/

    ContConst->WfHighPulse = GEJ85_FUEL_HIGH_PULSE;
    ContConst->WfImpulseTime = GEJ85_FUEL_IMPULSE_TIME;
    ContConst->WfInit = GEJ85_FUEL_INIT;
    ContConst->WfKdStart = GEJ85_FUEL_KDSTART;
    ContConst->WfPerc = GEJ85_FUEL_PERC;
    ContConst->WfRamp = GEJ85_FUEL_RAMP;
    ContConst->WfRampDec = GEJ85_FUEL_RAMP_DEC;
    ContConst->WfRampDecFast = GEJ85_FUEL_RAMP_DEC_FAST;
    ContConst->WfRampDecLowLim = GEJ85_FUEL_RAMP_DEC_LOWLIM;
    ContConst->WfRampLow = GEJ85_FUEL_RAMP_LOW;
    ContConst->POilAlarm = GEJ85_POIL_ALARM;
    ContConst->POilShutDown = GEJ85_POIL_SHUTDOWN;
    ContConst->RPMIdle = GEJ85_RPM_IDLE;
    ContConst->RPMIgnOff = GEJ85_RPM_IGN_OFF;
    ContConst->RPMRampChange = GEJ85_RPM_RAMP_CHANGE;
    ContConst->RPMCLStartRamp = GEJ85_RPM_CLSTARTRAMP;
    ContConst->RPMCLStartRampFaster = GEJ85_RPM_CLSTARTRAMPFASTER;
    ContConst->RPMCLStartMaxRef = GEJ85_RPM_CLSTARTMAXREF;
    ContConst->RPMRelaysOn = GEJ85_RPM_RELAYS_ON;
    ContConst->RPMValve100 = GEJ85_RPM_VALVE_100;
    ContConst->TimeAccomodation = GEJ85_TIME_ACCOMODATION;
    ContConst->TimeBeforeRamp = GEJ85_TIME_BEFORE_RAMP;
    //ContConst->TimeIgnition = GEJ85_TIME_IGNITION;
    ContConst->TimeLowPOil = GEJ85_TIME_LOW_POIL;
    ContConst->TimeOvertemp = GEJ85_TIME_OVERTEMP;
    ContConst->Tt4AvFlameOn = GEJ85_Tt4AV_FLAME_ON;
    ContConst->Tt4AvMax = GEJ85_Tt4AV_MAX;
    ContConst->Tt4CLSafeStart = GEJ85_Tt4_CLSAFESTART;
    ContConst->Tt4CLRampCoef = GEJ85_Tt4_CLRAMPCOEF;
    ContConst->Tt4RampDecFast = GEJ85_Tt4_RAMPDECFAST;    
    ContConst->ValveInit = GEJ85_VALVE_INIT;
    ContConst->ValveTotal = GEJ85_VALVE_TOTAL;
    ContConst->WaitAction = GEJ85_WAIT_ACTION;

    /*-----------------------------*/
    /* NOMINAL SHUT DOWN CONSTANTS */
    /*-----------------------------*/

    ContConst->RPMMinSD = GEJ85_SD_RMPMIN;
    ContConst->ErrorFracSD = GEJ85_SD_ERRORFRAC;
    ContConst->FuelRampSD = GEJ85_SD_FUELRAMP;
    ContConst->TimeToEmergSD = GEJ85_SD_TIME_TOEMERG;
    ContConst->TimeToRampSD = GEJ85_SD_TIME_TORAMP;

    /*---------------------------*/
    /* FAIL PROTECTION CONSTANTS */
    /*---------------------------*/

    /* Time parameters */
    ContConst->TimeOverspeed = GEJ85_TIME_OVERSPEED;
    ContConst->TimeOvertemp = GEJ85_TIME_OVERTEMP;
    ContConst->TimeLowPOil = GEJ85_TIME_POILLOW; 
    ContConst->TimeHighPOil = GEJ85_TIME_POILHIHG;
    ContConst->TimeLowPFuel = GEJ85_TIME_PFUELLOW; 
    ContConst->TimeHighPFuel = GEJ85_TIME_PFUELHIGH;
    ContConst->TimeHighVibration = GEJ85_TIME_VIBHIGH;
    ContConst->TimeIgnition = GEJ85_TIME_IGNITION;
    ContConst->TimeFaultAnaylsis = GEJ85_TIME_FAULTANALYSIS;
    ContConst->TimeBearOverTemp[0] = GEJ85_TIME_BEAR0OT;
    ContConst->TimeBearOverTemp[1] = GEJ85_TIME_BEAR1OT;
    ContConst->TimeBearOverTemp[2] = GEJ85_TIME_BEAR2OT;

    /* Short-Open sensor values */
    ContConst->PFuelShort = GEJ85_PFUELSHORT;
    ContConst->PFuelOpen = GEJ85_PFUELOPEN;
    ContConst->POilShort = GEJ85_POILSHORT;
    ContConst->POilOpen = GEJ85_POILOPEN;
    ContConst->PSOpen = GEJ85_PSSOPEN;
    ContConst->PSOpenThresh = GEJ85_PSOPENTHRESH; 
    ContConst->PSShort = GEJ85_PSSHORT; 
    ContConst->PSShortThresh = GEJ85_PSSHORTTHRESH;
    ContConst->TCOpen = GEJ85_TCOPEN;
    ContConst->VibOpen = GEJ85_VIBOPEN;
    ContConst->VibOpenThresh = GEJ85_VIBOPENTHRESH;
    ContConst->VibShort = GEJ85_VIBSHORT;
    ContConst->VibShortThresh = GEJ85_VIBSHORTTHRESH;
    ContConst->RPMShort = GEJ85_RPMSHORT;
    ContConst->RPMOpen = GEJ85_RPMOPEN;

    /* Thresholds */
    ContConst->TCThreshold = GEJ85_TCTHRESHOLD; 
    ContConst->Ts2Threshold = GEJ85_TS2THRESHOLD;
    ContConst->Tt4Threshold = GEJ85_TT4THRESHOLD;
    ContConst->Tt4ShaftLock = GEJ85_Tt4SHLCK;
    ContConst->Tt4BlowOut = GEJ85_Tt4BOUT;
    ContConst->PSThreshold = GEJ85_PSTHRESHOLD;
    ContConst->Pt3Threshold = GEJ85_PT3THRESHOLD;
    ContConst->Pt3ShaftLock = GEJ85_Pt3SHLCK;
    ContConst->Pt3BlowOut = GEJ85_Pt3BOUT;
    ContConst->VibThreshold = GEJ85_VIBTHRESHOLD;
    ContConst->RPMThreshold = GEJ85_RPMTHRESHOLD;
    ContConst->RPMBlowOut = GEJ85_RPM_BOUT;
    ContConst->POilThreshold = GEJ85_POILTHRESHOLD;
    ContConst->PFuelThreshold = GEJ85_PFUELTHRESHOLD;

    /* Limit Values */
    ContConst->PFuelHigh = GEJ85_PFUELHIGH; 
    ContConst->PFuelLow = GEJ85_PFUELLOW;
    ContConst->POilHigh = GEJ85_POILHIGH; 
    ContConst->POilLow = GEJ85_POILLOW;
    ContConst->VibHigh = GEJ85_VIBHIGH;

    /*------------------------*/
    /* ENGINE MODEL CONSTANTS */
    /*------------------------*/

    ContConst->PFUelModel = GEJ85_PFUELMODEL;
    ContConst->POilModel = GEJ85_POILMODEL;
    ContConst->VibModel = GEJ85_VIBMODEL;
    ContConst->NumSteps = GEJ85_NUMSTEPS;
    ContConst->MaxInterFault = GEJ85_MAXINTERFAULT;
    ContConst->TTCTimeConst = GEJ85_TTCTIMECONST;
    ContConst->PSensTimeConst = GEJ85_PSENSTIMECONST;
    ContConst->FuelPumpTimeConstant = GEJ85_FUELPUMPTIMECONSTANT;

    /*-------------------------*/
    /* ENGINE STATUS CONSTANTS */
    /*-------------------------*/

    ContConst->TimeReadytoStart = GEJ85_TIME_READYTOSTART;
    ContConst->TimeWindmill = GEJ85_TIME_WINDMILL;
    ContConst->RPMWindmill = GEJ85_RPM_WINDMILL;
    ContConst->FNIdle = GEJ85_FN_IDLE;

    /*-------------------------------------------------------------*/
    /* ENGINE START/SHUT DOWN/EMERGENCY EXTERNAL COMMAND CONSTANTS */
    /*-------------------------------------------------------------*/

    ContConst->StartWait = GEJ85_WAIT_START_COMMAND;
    ContConst->StartCom = GEJ85_COMMAND_START;
    ContConst->ShutDownWait = GEJ85_WAIT_SHUTDOWN_COMMAND;
    ContConst->ShutDownCom = GEJ85_COMMAND_SHUTDOWN;
    ContConst->EmergencyWait = GEJ85_WAIT_EMERGENCY_COMMAND;
    ContConst->EmergencyCom = GEJ85_COMMAND_EMERGENCY;
    
    /*---------------------------*/
    /* ENGINE BEARINGS CONSTANTS */
    /*---------------------------*/

    ContConst->KpBear = GEJ85_BEAR_KP;
    ContConst->KiBear = GEJ85_BEAR_KI;
    ContConst->KbBear = GEJ85_BEAR_KB;
    ContConst->NumBear = GEJ85_BEAR_NUM;
    ContConst->OPRPMInt = GEJ85_BEAR_OPRPMINT;
    ContConst->OPRPMMax = GEJ85_BEAR_OPRPMMAX;
    ContConst->OPRPMMin = GEJ85_BEAR_OPRPMMIN;
    ContConst->RPMOilInt = GEJ85_BEAR_RPMOILINT;
    ContConst->RPMOilOn = GEJ85_BEAR_RPMOILON;
    ContConst->TMaxBear[0] = GEJ85_BEAR_TMAX_0;
    ContConst->TMaxBear[1] = GEJ85_BEAR_TMAX_1;
    ContConst->TMaxBear[2] = GEJ85_BEAR_TMAX_2;
    ContConst->TRefBear[0] = GEJ85_BEAR_TREF_0;
    ContConst->TRefBear[1] = GEJ85_BEAR_TREF_1;
    ContConst->TRefBear[2] = GEJ85_BEAR_TREF_2;

    /*-------------------*/
    /* BOOSTER CONSTANTS */
    /*-------------------*/

    ContConst->BoostTime = GEJ85_BOOST_TIME;

};