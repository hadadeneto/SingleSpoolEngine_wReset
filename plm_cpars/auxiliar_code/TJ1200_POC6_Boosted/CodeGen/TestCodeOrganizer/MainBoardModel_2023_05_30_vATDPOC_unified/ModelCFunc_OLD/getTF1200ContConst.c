
#include "Control_Types.h"
#include "ConstantsTF1200.h"

void getTF1200ContConst(struct ControllerConstants *ContConst)
{
    
    /*--------------------------*/
    /* CONTROL REGIME CONSTANTS */
    /*--------------------------*/

    /* PI Constants */
    ContConst->KpTt4 = TF1200_KPTT4;
	ContConst->KiTt4 = TF1200_KITT4;
    ContConst->KbT = TF1200_KBT;
    ContConst->KbN = TF1200_KBN;
    
    /* Elements numbers */
    ContConst->Alt_Elem = TF1200_ALT_ELEM;
    ContConst->As_Elem = TF1200_AS_ELEM;
    ContConst->Fn_Elem = TF1200_FN_ELEM;
    ContConst->MN_Elem = TF1200_MN_ELEM;
    ContConst->NcHPCMAP_Elem = TF1200_FAN_NC;
    ContConst->WcHPCMAP_Elem = TF1200_FAN_NC * TF1200_FAN_PR;
    ContConst->Wc_per_Nc_HPCMAP = TF1200_FAN_PR;
    
    /* Flags */
    ContConst->CLLever = TF1200_CLOOP;
    ContConst->ManualMode = TF1200_MANUAL;
    ContConst->UseEngUnits = TF1200_ENGUNITS;
    
    /* Design Point */
    ContConst->NDes = TF1200_NDES;
    ContConst->Ath = TF1200_Ath_NOZZLE;
    
    /* Limiters */
    ContConst->NMax = TF1200_NMAX;
    ContConst->NMaxRef = TF1200_NMAX;
    ContConst->RefRampValue = TF1200_REFRAMP;
    ContConst->RUMin = TF1200_RUMIN;
    ContConst->Tt4Max = TF1200_TT4MAX; 
    ContConst->Tt4MaxRef = TF1200_TT4MAXREF;    
    ContConst->WfMax = TF1200_WFMAX;
    
    /* Sensors Numbers */
    ContConst->NumTs2Sens = TF1200_TS2SENS;
    ContConst->NumPs3Sens = TF1200_PS3SENS;
    ContConst->NumTt4Sens = TF1200_TT4SENS;
    ContConst->NumRPMSens = TF1200_RPMSENS;
    ContConst->NumVibrationSens = TF1200_VIBRATIONSENS;
    ContConst->NumPOilSens = TF1200_POILSENS;
    ContConst->NumPFuelSens = TF1200_PFUELSENS;

    /* Miminum number of trusted sensors */
    ContConst->NumTs2SensTrust = TF1200_TS2SENSTRUST;
    ContConst->NumPs3SensTrust = TF1200_PS3SENSTRUST;    
    ContConst->NumTt4SensTrust = TF1200_TT4SENSTRUST;
    ContConst->NumRPMSensTrust = TF1200_RPMSENSTRUST;

    /*--------------------------*/
    /* STARGING LOGIC CONSTANTS */
    /*--------------------------*/

    ContConst->WfHighPulse = TF1200_FUEL_HIGH_PULSE;
    ContConst->WfImpulseTime = TF1200_FUEL_IMPULSE_TIME;
    ContConst->WfInit = TF1200_FUEL_INIT;
    ContConst->WfKdStart = TF1200_FUEL_KDSTART;
    ContConst->WfPerc = TF1200_FUEL_PERC;
    ContConst->WfRamp = TF1200_FUEL_RAMP;
    ContConst->WfRampDec = TF1200_FUEL_RAMP_DEC;
    ContConst->WfRampDecFast = TF1200_FUEL_RAMP_DEC_FAST;
    ContConst->WfRampDecLowLim = TF1200_FUEL_RAMP_DEC_LOWLIM;    
    ContConst->WfRampLow = TF1200_FUEL_RAMP_LOW;
    ContConst->POilAlarm = TF1200_POIL_ALARM;
    ContConst->POilShutDown = TF1200_POIL_SHUTDOWN;
    ContConst->RPMIdle = TF1200_RPM_IDLE;
    ContConst->RPMIgnOff = TF1200_RPM_IGN_OFF;
    ContConst->RPMRampChange = TF1200_RPM_RAMP_CHANGE;
    ContConst->RPMCLStartRamp = TF1200_RPM_CLSTARTRAMP;
    ContConst->RPMCLStartRampFaster = TF1200_RPM_CLSTARTRAMPFASTER;
    ContConst->RPMCLStartMaxRef = TF1200_RPM_CLSTARTMAXREF;
    ContConst->RPMRelaysOn = TF1200_RPM_RELAYS_ON;
    ContConst->RPMValve100 = TF1200_RPM_VALVE_100;
    ContConst->TimeAccomodation = TF1200_TIME_ACCOMODATION;
    ContConst->TimeBeforeRamp = TF1200_TIME_BEFORE_RAMP;
    //ContConst->TimeIgnition = TF1200_TIME_IGNITION;
    ContConst->TimeLowPOil = TF1200_TIME_LOW_POIL;
    ContConst->TimeOvertemp = TF1200_TIME_OVERTEMP;
    ContConst->Tt4AvFlameOn = TF1200_Tt4AV_FLAME_ON;
    ContConst->Tt4AvMax = TF1200_Tt4AV_MAX;
    ContConst->Tt4CLSafeStart = TF1200_Tt4_CLSAFESTART;
    ContConst->Tt4CLRampCoef = TF1200_Tt4_CLRAMPCOEF;
    ContConst->Tt4RampDecFast = TF1200_Tt4_RAMPDECFAST;
    ContConst->ValveInit = TF1200_VALVE_INIT;
    ContConst->ValveTotal = TF1200_VALVE_TOTAL;
    ContConst->WaitAction = TF1200_WAIT_ACTION;

    /*-----------------------------*/
    /* NOMINAL SHUT DOWN CONSTANTS */
    /*-----------------------------*/

    ContConst->RPMMinSD = TF1200_SD_RMPMIN;
    ContConst->ErrorFracSD = TF1200_SD_ERRORFRAC;
    ContConst->FuelRampSD = TF1200_SD_FUELRAMP;
    ContConst->TimeToEmergSD = TF1200_SD_TIME_TOEMERG;
    ContConst->TimeToRampSD = TF1200_SD_TIME_TORAMP;

    /*---------------------------*/
    /* FAIL PROTECTION CONSTANTS */
    /*---------------------------*/

    /* Time parameters */
    ContConst->TimeOverspeed = TF1200_TIME_OVERSPEED;
    ContConst->TimeOvertemp = TF1200_TIME_OVERTEMP;
    ContConst->TimeLowPOil = TF1200_TIME_POILLOW; 
    ContConst->TimeHighPOil = TF1200_TIME_POILHIHG;
    ContConst->TimeLowPFuel = TF1200_TIME_PFUELLOW; 
    ContConst->TimeHighPFuel = TF1200_TIME_PFUELHIGH;
    ContConst->TimeHighVibration = TF1200_TIME_VIBHIGH;
    ContConst->TimeIgnition = TF1200_TIME_IGNITION;
    ContConst->TimeFaultAnaylsis = TF1200_TIME_FAULTANALYSIS;
    ContConst->TimeBearOverTemp[0] = TF1200_TIME_BEAR0OT;
    ContConst->TimeBearOverTemp[1] = TF1200_TIME_BEAR1OT;
    ContConst->TimeBearOverTemp[2] = TF1200_TIME_BEAR2OT;

    /* Short-Open sensor values */
    ContConst->PFuelShort = TF1200_PFUELSHORT;
    ContConst->PFuelOpen = TF1200_PFUELOPEN;
    ContConst->POilShort = TF1200_POILSHORT;
    ContConst->POilOpen = TF1200_POILOPEN;
    ContConst->PSOpen = TF1200_PSSOPEN;
    ContConst->PSOpenThresh = TF1200_PSOPENTHRESH; 
    ContConst->PSShort = TF1200_PSSHORT; 
    ContConst->PSShortThresh = TF1200_PSSHORTTHRESH;
    ContConst->TCOpen = TF1200_TCOPEN;
    ContConst->VibOpen = TF1200_VIBOPEN;
    ContConst->VibOpenThresh = TF1200_VIBOPENTHRESH;
    ContConst->VibShort = TF1200_VIBSHORT;
    ContConst->VibShortThresh = TF1200_VIBSHORTTHRESH;
    ContConst->RPMShort = TF1200_RPMSHORT;
    ContConst->RPMOpen = TF1200_RPMOPEN;

    /* Thresholds */
    ContConst->TCThreshold = TF1200_TCTHRESHOLD; 
    ContConst->Ts2Threshold = TF1200_TS2THRESHOLD;
    ContConst->Tt4Threshold = TF1200_TT4THRESHOLD;
    ContConst->Tt4ShaftLock = TF1200_Tt4SHLCK;
    ContConst->Tt4BlowOut = TF1200_Tt4BOUT;
    ContConst->PSThreshold = TF1200_PSTHRESHOLD;
    ContConst->Pt3Threshold = TF1200_PT3THRESHOLD;
    ContConst->Pt3ShaftLock = TF1200_Pt3SHLCK;
    ContConst->Pt3BlowOut = TF1200_Pt3BOUT;
    ContConst->VibThreshold = TF1200_VIBTHRESHOLD;
    ContConst->RPMThreshold = TF1200_RPMTHRESHOLD;
    ContConst->RPMBlowOut = TF1200_RPM_BOUT;
    ContConst->POilThreshold = TF1200_POILTHRESHOLD;
    ContConst->PFuelThreshold = TF1200_PFUELTHRESHOLD;

    /* Limit Values */
    ContConst->PFuelHigh = TF1200_PFUELHIGH; 
    ContConst->PFuelLow = TF1200_PFUELLOW;
    ContConst->POilHigh = TF1200_POILHIGH; 
    ContConst->POilLow = TF1200_POILLOW;
    ContConst->VibHigh = TF1200_VIBHIGH;

    /*------------------------*/
    /* ENGINE MODEL CONSTANTS */
    /*------------------------*/

    ContConst->PFUelModel = TF1200_PFUELMODEL;
    ContConst->POilModel = TF1200_POILMODEL;
    ContConst->VibModel = TF1200_VIBMODEL;
    ContConst->NumSteps = TF1200_NUMSTEPS;
    ContConst->MaxInterFault = TF1200_MAXINTERFAULT;
    ContConst->TTCTimeConst = TF1200_TTCTIMECONST;
    ContConst->PSensTimeConst = TF1200_PSENSTIMECONST;
    ContConst->FuelPumpTimeConstant = TF1200_FUELPUMPTIMECONSTANT;

    /*-------------------------*/
    /* ENGINE STATUS CONSTANTS */
    /*-------------------------*/

    ContConst->TimeReadytoStart = TF1200_TIME_READYTOSTART;
    ContConst->TimeWindmill = TF1200_TIME_WINDMILL;
    ContConst->RPMWindmill = TF1200_RPM_WINDMILL;
    ContConst->FNIdle = TF1200_FN_IDLE;

    /*-------------------------------------------------------------*/
    /* ENGINE START/SHUT DOWN/EMERGENCY EXTERNAL COMMAND CONSTANTS */
    /*-------------------------------------------------------------*/

    ContConst->StartWait = TF1200_WAIT_START_COMMAND;
    ContConst->StartCom = TF1200_COMMAND_START;
    ContConst->ShutDownWait = TF1200_WAIT_SHUTDOWN_COMMAND;
    ContConst->ShutDownCom = TF1200_COMMAND_SHUTDOWN;
    ContConst->EmergencyWait = TF1200_WAIT_EMERGENCY_COMMAND;
    ContConst->EmergencyCom = TF1200_COMMAND_EMERGENCY;

    /*---------------------------*/
    /* ENGINE BEARINGS CONSTANTS */
    /*---------------------------*/

    ContConst->KpBear = TF1200_BEAR_KP;
    ContConst->KiBear = TF1200_BEAR_KI;
    ContConst->KbBear = TF1200_BEAR_KB;
    ContConst->NumBear = TF1200_BEAR_NUM;
    ContConst->OPRPMInt = TF1200_BEAR_OPRPMINT;
    ContConst->OPRPMMax = TF1200_BEAR_OPRPMMAX;
    ContConst->OPRPMMin = TF1200_BEAR_OPRPMMIN;
    ContConst->RPMOilInt = TF1200_BEAR_RPMOILINT;
    ContConst->RPMOilOn = TF1200_BEAR_RPMOILON;    
    ContConst->TMaxBear[0] = TF1200_BEAR_TMAX_0;
    ContConst->TMaxBear[1] = TF1200_BEAR_TMAX_1;
    ContConst->TMaxBear[2] = TF1200_BEAR_TMAX_2;
    ContConst->TRefBear[0] = TF1200_BEAR_TREF_0;
    ContConst->TRefBear[1] = TF1200_BEAR_TREF_1;
    ContConst->TRefBear[2] = TF1200_BEAR_TREF_2;

    /*-------------------*/
    /* BOOSTER CONSTANTS */
    /*-------------------*/

    ContConst->BoostTime = TF1200_BOOST_TIME;

};