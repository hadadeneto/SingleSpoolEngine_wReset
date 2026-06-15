
#include "Control_Types.h"
#include "ConstantsTJ1200.h"

void getTJ1200ContConst(struct ControllerConstants *ContConst)
{
    
    /*--------------------------*/
    /* CONTROL REGIME CONSTANTS */
    /*--------------------------*/

    /* PI Constants */
    ContConst->KpTt4 = TJ1200_KPTT4;
	ContConst->KiTt4 = TJ1200_KITT4;
    ContConst->KbT = TJ1200_KBT;
    ContConst->KbN = TJ1200_KBN;
    
    /* Elements numbers */
    ContConst->Alt_Elem = TJ1200_ALT_ELEM;
    ContConst->As_Elem = TJ1200_AS_ELEM;
    ContConst->Fn_Elem = TJ1200_FN_ELEM;
    ContConst->MN_Elem = TJ1200_MN_ELEM;
    ContConst->NcHPCMAP_Elem = TJ1200_FAN_NC;
    ContConst->WcHPCMAP_Elem = TJ1200_FAN_NC * TJ1200_FAN_PR;
    ContConst->Wc_per_Nc_HPCMAP = TJ1200_FAN_PR;
    
    /* Flags */
    ContConst->CLLever = TJ1200_CLOOP;
    ContConst->ManualMode = TJ1200_MANUAL;
    ContConst->UseEngUnits = TJ1200_ENGUNITS;
    
    /* Design Point */
    ContConst->NDes = TJ1200_NDES;
    ContConst->Ath = TJ1200_Ath_NOZZLE;
    
    /* Limiters */
    ContConst->NMax = TJ1200_NMAX;
    ContConst->RefRampValue = TJ1200_REFRAMP;
    ContConst->RUMin = TJ1200_RUMIN;
    ContConst->Tt4Max = TJ1200_TT4MAX; 
    ContConst->WfMax = TJ1200_WFMAX;
    
    /* Sensors Numbers */
    ContConst->NumTs2Sens = TJ1200_TS2SENS;
    ContConst->NumPs3Sens = TJ1200_PS3SENS;
    ContConst->NumTt4Sens = TJ1200_TT4SENS;
    ContConst->NumRPMSens = TJ1200_RPMSENS;
    ContConst->NumVibrationSens = TJ1200_VIBRATIONSENS;
    ContConst->NumPOilSens = TJ1200_POILSENS;
    ContConst->NumPFuelSens = TJ1200_PFUELSENS;

    /* Miminum number of trusted sensors */
    ContConst->NumTs2SensTrust = TJ1200_TS2SENSTRUST;
    ContConst->NumPs3SensTrust = TJ1200_PS3SENSTRUST;    
    ContConst->NumTt4SensTrust = TJ1200_TT4SENSTRUST;
    ContConst->NumRPMSensTrust = TJ1200_RPMSENSTRUST;

    /*--------------------------*/
    /* STARGING LOGIC CONSTANTS */
    /*--------------------------*/

    ContConst->WfHighPulse = TJ1200_FUEL_HIGH_PULSE;
    ContConst->WfImpulseTime = TJ1200_FUEL_IMPULSE_TIME;
    ContConst->WfInit = TJ1200_FUEL_INIT;
    ContConst->WfPerc = TJ1200_FUEL_PERC;
    ContConst->WfRamp = TJ1200_FUEL_RAMP;
    ContConst->WfRampLow = TJ1200_FUEL_RAMP_LOW;
    ContConst->POilAlarm = TJ1200_POIL_ALARM;
    ContConst->POilShutDown = TJ1200_POIL_SHUTDOWN;
    ContConst->RPMIdle = TJ1200_RPM_IDLE;
    ContConst->RPMIgnOff = TJ1200_RPM_IGN_OFF;
    ContConst->RPMRampChange = TJ1200_RPM_RAMP_CHANGE;
    ContConst->RPMCLStartRamp = TJ1200_RPM_CLSTARTRAMP;
    ContConst->RPMCLStartRampFaster = TJ1200_RPM_CLSTARTRAMPFASTER;
    ContConst->RPMCLStartMaxRef = TJ1200_RPM_CLSTARTMAXREF;
    ContConst->RPMRelaysOn = TJ1200_RPM_RELAYS_ON;
    ContConst->RPMValve100 = TJ1200_RPM_VALVE_100;
    ContConst->TimeAccomodation = TJ1200_TIME_ACCOMODATION;
    ContConst->TimeBeforeRamp = TJ1200_TIME_BEFORE_RAMP;
    //ContConst->TimeIgnition = TJ1200_TIME_IGNITION;
    ContConst->TimeLowPOil = TJ1200_TIME_LOW_POIL;
    ContConst->TimeOvertemp = TJ1200_TIME_OVERTEMP;
    ContConst->Tt4AvFlameOn = TJ1200_Tt4AV_FLAME_ON;
    ContConst->Tt4AvMax = TJ1200_Tt4AV_MAX;
    ContConst->Tt4CLSafeStart = TJ1200_Tt4_CLSAFESTART;
    ContConst->Tt4CLRampCoef = TJ1200_Tt4_CLRAMPCOEF;
    ContConst->ValveInit = TJ1200_VALVE_INIT;
    ContConst->ValveTotal = TJ1200_VALVE_TOTAL;
    ContConst->WaitAction = TJ1200_WAIT_ACTION;

    /*-----------------------------*/
    /* NOMINAL SHUT DOWN CONSTANTS */
    /*-----------------------------*/

    ContConst->RPMMinSD = TJ1200_SD_RMPMIN;
    ContConst->ErrorFracSD = TJ1200_SD_ERRORFRAC;
    ContConst->FuelRampSD = TJ1200_SD_FUELRAMP;

    /*---------------------------*/
    /* FAIL PROTECTION CONSTANTS */
    /*---------------------------*/

    /* Time parameters */
    ContConst->TimeOverspeed = TJ1200_TIME_OVERSPEED;
    ContConst->TimeOvertemp = TJ1200_TIME_OVERTEMP;
    ContConst->TimeLowPOil = TJ1200_TIME_POILLOW; 
    ContConst->TimeHighPOil = TJ1200_TIME_POILHIHG;
    ContConst->TimeLowPFuel = TJ1200_TIME_PFUELLOW; 
    ContConst->TimeHighPFuel = TJ1200_TIME_PFUELHIGH;
    ContConst->TimeHighVibration = TJ1200_TIME_VIBHIGH;
    ContConst->TimeIgnition = TJ1200_TIME_IGNITION;
    ContConst->TimeFaultAnaylsis = TJ1200_TIME_FAULTANALYSIS;

    /* Short-Open sensor values */
    ContConst->PFuelShort = TJ1200_PFUELSHORT;
    ContConst->PSOpen = TJ1200_PSSOPEN;
    ContConst->PSOpenThresh = TJ1200_PSOPENTHRESH; 
    ContConst->PSShort = TJ1200_PSSHORT; 
    ContConst->PSShortThresh = TJ1200_PSSHORTTHRESH;
    ContConst->TCOpen = TJ1200_TCOPEN;
    ContConst->VibOpen = TJ1200_VIBOPEN;
    ContConst->VibOpenThresh = TJ1200_VIBOPENTHRESH;
    ContConst->VibShort = TJ1200_VIBSHORT;
    ContConst->VibShortThresh = TJ1200_VIBSHORTTHRESH;

    /* Thresholds */
    ContConst->TCThreshold = TJ1200_TCTHRESHOLD; 
    ContConst->Tt4ShaftLock = TJ1200_Tt4SHLCK;
    ContConst->PSThreshold = TJ1200_PSTHRESHOLD;
    ContConst->VibThreshold = TJ1200_VIBTHRESHOLD;
    ContConst->RPMThreshold = TJ1200_RPMTHRESHOLD;

    /* Limit Values */
    ContConst->PFuelHigh = TJ1200_PFUELHIGH; 
    ContConst->PFuelLow = TJ1200_PFUELLOW;
    ContConst->POilHigh = TJ1200_POILHIGH; 
    ContConst->POilLow = TJ1200_POILLOW;
    ContConst->VibHigh = TJ1200_VIBHIGH;

    /*------------------------*/
    /* ENGINE MODEL CONSTANTS */
    /*------------------------*/

    ContConst->PFUelModel = TJ1200_PFUELMODEL;
    ContConst->POilModel = TJ1200_POILMODEL;
    ContConst->VibModel = TJ1200_VIBMODEL;
    ContConst->NumSteps = TJ1200_NUMSTEPS;
    ContConst->MaxInterFault = TJ1200_MAXINTERFAULT;
    ContConst->TTCTimeConst = TJ1200_TTCTIMECONST;
    ContConst->PSensTimeConst = TJ1200_PSENSTIMECONST;
    ContConst->FuelPumpTimeConstant = TJ1200_FUELPUMPTIMECONSTANT;

    /*-------------------------*/
    /* ENGINE STATUS CONSTANTS */
    /*-------------------------*/

    ContConst->TimeReadytoStart = TJ1200_TIME_READYTOSTART;
    ContConst->TimeWindmill = TJ1200_TIME_WINDMILL;
    ContConst->RPMWindmill = TJ1200_RPM_WINDMILL;

    /*-------------------------------------------------------------*/
    /* ENGINE START/SHUT DOWN/EMERGENCY EXTERNAL COMMAND CONSTANTS */
    /*-------------------------------------------------------------*/

    ContConst->StartWait = TJ1200_WAIT_START_COMMAND;
    ContConst->StartCom = TJ1200_COMMAND_START;
    ContConst->ShutDownWait = TJ1200_WAIT_SHUTDOWN_COMMAND;
    ContConst->ShutDownCom = TJ1200_COMMAND_SHUTDOWN;
    ContConst->EmergencyWait = TJ1200_WAIT_EMERGENCY_COMMAND;
    ContConst->EmergencyCom = TJ1200_COMMAND_EMERGENCY;

};