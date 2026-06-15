/*
 * sfuntmpl_basic.c: Basic 'C' template for a level 2 S-function.
 *
 * Copyright 1990-2013 The MathWorks, Inc.
 */


 /*
  * You must specify the S_FUNCTION_NAME as the name of your S-function
  * (i.e. replace sfuntmpl_basic with the name of your S-function).
  */

  // #ifdef __cplusplus
  // extern "C" { // use the C fcn-call standard for all functions
  // #endif       // defined within this scope

#define S_FUNCTION_NAME  PIMMRF_TJ1200_TestBench
#define S_FUNCTION_LEVEL 2

//#define pi 3.14

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"


/*-------------------*/
/* STANDARD INCLUDES */
/*-------------------*/

/* Standard includes - Total of 04 files currently */
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------*/
/* COMMON INCLUDES - USED BY BOTH FADEC AND HIL */
/*----------------------------------------------*/

/* Created .h files - Total of 21 files currently */
#include "Ambient_TMATS.h"          /* Adapted from T-MATS */
#include "constants_TMATS.h"        /* Adapted from T-MATS */
#include "Control_Types.h"          /* Controller calculations */
#include "ControlFunctions.h"       /* Controller calculations */
#include "DigitalOutDefs.h"         /* Controller calculations */
#include "Env_SampTime.h"           /* General Calculations*/
#include "FailSafeFunctions.h"      /* Fault analysis */
#include "FaultSim_Types.h"         /* Fault analysis */
#include "functions_TMATS.h"        /* Adapted from T-MATS */
#include "getTJ1200.h"              /* File containing all get functions for TJ1200 */
#include "Interpolation_Types.h"    /* General Calculations*/
#include "IO_Types.h"               /* Controller calculations */
#include "LinMtxFunctions.h"        /* General Calculations*/
#include "Model_Types.h"            /* Used for model calculations */
#include "MtxIntFunctions.h"        /* General Calculations*/
#include "PeripheralDyn.h"          /* Functions describing peripherals dynamics */
#include "PIMinMaxRF.h"             /* Controller calculations */
#include "PIOil.h"                  /* Controller calculations */
#include "ShutDownFunctions.h"      /* Controller calculations */
#include "StartingFunctions.h"      /* Controller calculations */
#include "TCFault.h"                /* Fault analysis */

/*-----------------------------------------------------------*/
/* FADEC INCLUDES - USED EXCLUSIVELY BY FADEC AND NOT BY HIL */
/*-----------------------------------------------------------*/

/* Created .h files - Total of 01 files currently */
#include "ConstantsTJ1200.h"        /* TJ1200 Engine Constants */


/* Error handling
 * --------------
 *
 * You should use the following technique to report errors encountered within
 * an S-function:
 *
 *       ssSetErrorStatus(S,"Error encountered due to ...");
 *       return;
 *
 * Note that the 2nd argument to ssSetErrorStatus must be persistent memory.
 * It cannot be a local variable. For example the following will cause
 * unpredictable errors:
 *
 *      mdlOutputs()
 *      {
 *         char msg[256];         {ILLEGAL: to fix use "static char msg[256];"}
 *         sprintf(msg,"Error due to %s", string);
 *         ssSetErrorStatus(S,msg);
 *         return;
 *      }
 *
 */

 /*====================*
  * S-function methods *
  *====================*/

  /* Function: mdlInitializeSizes ===============================================
   * Abstract:
   *    The sizes information is used by Simulink to determine the S-function
   *    block's characteristics (number of inputs, outputs, states, etc.).
   */
static void mdlInitializeSizes(SimStruct *S)
{
	ssSetNumSFcnParams(S, 0);  /* Number of expected parameters */
	if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
		/* Return if number of expected != number of actual parameters */
		return;
	}

	ssSetNumContStates(S, 0);
	ssSetNumDiscStates(S, 0);

	if (!ssSetNumInputPorts(S, 5)) return;

	ssSetInputPortWidth(S, 0, 25);
	ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/

    ssSetInputPortWidth(S, 1, 1);
	ssSetInputPortRequiredContiguous(S, 1, true); /*direct input signal access*/
    
    ssSetInputPortWidth(S, 2, 14);
	ssSetInputPortRequiredContiguous(S, 2, true); /*direct input signal access*/
    
    ssSetInputPortWidth(S, 3, 1);
	ssSetInputPortRequiredContiguous(S, 3, true); /*direct input signal access*/

    ssSetInputPortWidth(S, 4, 1);
	ssSetInputPortRequiredContiguous(S, 4, true); /*direct input signal access*/

// 

	/*
	 * Set direct feedthrough flag (1=yes, 0=no).
	 * A port has direct feedthrough if the input is used in either
	 * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
	 */
	ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortDirectFeedThrough(S, 1, 1);
    ssSetInputPortDirectFeedThrough(S, 2, 1);
    ssSetInputPortDirectFeedThrough(S, 3, 1);
    ssSetInputPortDirectFeedThrough(S, 4, 1);
        

	if (!ssSetNumOutputPorts(S, 4)) return;
	ssSetOutputPortWidth(S, 0, 7);
    ssSetOutputPortWidth(S, 1, 4);
    ssSetOutputPortWidth(S, 2, 4);
    ssSetOutputPortWidth(S, 3, 4);


	ssSetNumSampleTimes(S, 1);
	ssSetNumRWork(S, 0);
	ssSetNumIWork(S, 0);
	ssSetNumPWork(S, 0);
	ssSetNumModes(S, 0);
	ssSetNumNonsampledZCs(S, 0);

	/* Specify the sim state compliance to be same as a built-in block */
	ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

	ssSetOptions(S, 0);
}



/* Function: mdlInitializeSampleTimes =========================================
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
	ssSetSampleTime(S, 0, CONTINUOUS_SAMPLE_TIME);
	ssSetOffsetTime(S, 0, 0.0);

}



#define MDL_INITIALIZE_CONDITIONS   /* Change to #undef to remove function */
#if defined(MDL_INITIALIZE_CONDITIONS)
/* Function: mdlInitializeConditions ========================================
 * Abstract:
 *    In this function, you should initialize the continuous and discrete
 *    states for your S-function block.  The initial states are placed
 *    in the state vector, ssGetContStates(S) or ssGetRealDiscStates(S).
 *    You can also perform any other initialization activities that your
 *    S-function may require. Note, this routine will be called at the
 *    start of simulation and if it is present in an enabled subsystem
 *    configured to reset states, it will be call when the enabled subsystem
 *    restarts execution to reset the states.
 */
static void mdlInitializeConditions(SimStruct *S)
{
}
#endif /* MDL_INITIALIZE_CONDITIONS */



#define MDL_START  /* Change to #undef to remove function */
#if defined(MDL_START)
/* Function: mdlStart =======================================================
 * Abstract:
 *    This function is called once at start of model execution. If you
 *    have states that should be initialized once, this is the place
 *    to do it.
 */
static void mdlStart(SimStruct *S)
{
}
#endif /*  MDL_START */



/* Function: mdlOutputs =======================================================
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{

	/* --------------------------------------------------- */
	/* DECLARATION OF INPUT VARIABLES - T-MATS & PLM       */
	/* (To be usedi in MATLAB and T-MATS simulations only) */
	/* --------------------------------------------------- */

	const real_T *InputVars = (const real_T*)ssGetInputPortSignal(S, 0);
	const real_T *InputTMATS = (const real_T*)ssGetInputPortSignal(S, 1);
    const real_T *InputSensors = (const real_T*)ssGetInputPortSignal(S, 2);
    const real_T *InputFaults = (const real_T*)ssGetInputPortSignal(S, 3);
    const real_T *InputCANFaults = (const real_T*)ssGetInputPortSignal(S, 4);
    real_T       *Iout = ssGetOutputPortSignal(S, 0);
    real_T       *IoutModel = ssGetOutputPortSignal(S, 1);
    real_T       *IoutBlowOut = ssGetOutputPortSignal(S, 2);
    real_T       *IoutModelCL = ssGetOutputPortSignal(S, 3);
    
    /* --------------------------------------------------- */

    /* -------------------------------------------------- */
	/* AUXILIARY VARIABLE - T-MATS                        */
	/* (To be usedi in MATLAB and TMATS simulations only) */
	/* -------------------------------------------------- */
    
    /* int TYPE */

    int TMATS_StartComplete = 0;
 
    /* static int TYPE */

    static int Out2;                            //igniter
    static int SkipStartIn[2] = {0,0};          /* Simulates a single read of skip start */
    static int tick = 0;                        /* Clock variable */
    static int tack = 1;                        /* Clock variable */

    /* static double TYPE */

    static double Out0;                         //Wf//fvalue
    static double Out1;                         //active
    static double Out3;                         //rpmref
    static double Out4;                         //filterRef
    static double Out5;                         //engine operating status
    static double Out6;                         //Oil Pump RPM reference
    
    /* -------------------------------------------------- */

	/* --------------------------*/
	/* FADEC AND MODEL VARIABLES */
	/* --------------------------*/

    /* STRUCTURES */

    static AllResiduals PFuelRes;                       /* Struct - Residuals calcultaions and treatment */ 
    static AllResiduals POilRes;                        /* Struct - Residuals calcultaions and treatment */ 
    static AllResiduals Pt3Res;                         /* Struct - Residuals calcultaions and treatment */ 
    static AllResiduals RPMRes;                         /* Struct - Residuals calcultaions and treatment */ 
    static AllResiduals TBearRes;                       /* Struct - Residuals calcultaions and treatment */ 
    static AllResiduals Ts2Res;                         /* Struct - Residuals calcultaions and treatment */      
    static AllResiduals Tt4Res;                         /* Struct - Residuals calcultaions and treatment */ 
    static AllResiduals VibrationRes;                   /* Struct - Residuals calcultaions and treatment */ 
    static AllResiduals DefaultRes = {1000000};         /* Struct - Residuals calcultaions and treatment */ 

    static AmbientPars Ambient;                         /* Struct - Ambient calculations */
    static AmbientPars AmbientEmpty = { 0 };            /* Struct - Ambient calculations */

    static ControllerConstants ContConst;               /* Struct - Controller Constants */
    static ControllerConstants ContConstEmpty = {0};    /* Struct - Controller Constants */

    static ControllerGeneral ContGenOil;                /* Struct - Bearings temperature control */
    static ControllerGeneral ContGenOilCL;              /* Struct - Bearings temperature control */
    static ControllerGeneral ContGenEmpty = {0};        /* Struct - Bearings temperature control */

	static ControllerInput ContInput;                   /* Struct - Controller Inputs */	
    static ControllerInput ContInModCL;                 /* Struct - Controller Inputs */	
    static ControllerInput ContInputEmpty = {0};        /* Struct - Controller Inputs */

	static ControllerOutput ContOutput;                 /* Struct - Controller outputs */
    static ControllerOutput ContOutModCL;               /* Struct - Controller outputs */
    static ControllerOutput ContOutputEmpty = {0};      /* Struct - Controller outputs */

	static ControlStart ContStart;                      /* Struct - Controller starting parameters */
    static ControlStart ContStModCL;                    /* Struct - Controller starting parameters */
    static ControlStart ContStartEmpty = {0};           /* Struct - Controller starting parameters */

	static EngineOnOff EngOnOff;                        /* Struct - On/Off logic */
	static EngineOnOff EngOnOffEmpty = {0};             /* Struct - On/Off logic */
    
    static EstimatedPars BlowOutPars;                   /* Struct - Engine model parameters */           
    static EstimatedPars ModelPars;                     /* Struct - Engine model parameters */       
    static EstimatedPars ModelParsChosen;               /* Struct - Engine model parameters */
    static EstimatedPars ModelParsCL;                   /* Struct - Engine model parameters */
    static EstimatedPars EstParsEmpty = {0};            /* Struct - Engine model parameters */

    static InterpIndex3D Index3D;                       /* Struct - 3D Matrix indexes */
    static InterpIndex3D Index3DEmpty = {0};            /* Struct - 3D Matrix indexes */

    static SensedPars Sensors;                          /* Struct - Sensors values */
    static SensedPars SensorsEmpty = {0};               /* Struct - Sensors values */

    /* UNIONS */

	static digital_t digital;                           /* Union - Digital outputs */
    static digital_t digModCL;                          /* Union - Digital outputs */	
	static digital_t digitalEmpty = { 0 };              /* Union - Digital outputs */
	
    static EngineFaults FaultStatus;                    /* Union - Fault Status */
    static EngineFaults FaultWarning;                   /* Union - Fault Warining */
    static EngineFaults FaultEmpty = {0};               /* Union - Fault Status and warning */
     
    static EngineStatus EngStatus;                      /* Union - Contains engine status */
    static EngineStatus EngStatusEmpty = {0};           /* Union - Contains engine status */

	static FaultDetect CANFault;						/* Union - Fault analysis */
    static FaultDetect ExistFStatus;                    /* Union - General information about sensors faults*/
    static FaultDetect ExistFWarning;                   /* Union - General information about sensors faults*/
    static FaultDetect HardFAuthorize;                  /* Union - General information about sensors faults*/
    static FaultDetect HardFStatus;                     /* Union - General information about sensors faults*/
    static FaultDetect HardFWarning;                    /* Union - General information about sensors faults*/
    static FaultDetect SoftFStatus;                     /* Union - General information about sensors faults*/
    static FaultDetect SoftFWarning;                    /* Union - General information about sensors faults*/
    static FaultDetect TrustAll;                        /* Union - General information about sensors faults*/
    static FaultDetect TrustHard;                       /* Union - General information about sensors faults*/
    static FaultDetect TrustSens;                       /* Union - General information about sensors faults*/
    static FaultDetect FaultDetectEmpty = {0};          /* Union - General information about sensors faults*/

    static keys_t keys;                                 /* Union - Input keys */	
    static keys_t keysEmpty = {0};                      /* Union - Input keys */

    static ModelParsFault ModPFault;                    /* Union - Fault analysis */

    static SensorFaults FaultSensAuthorize;             /* Union - Fault analysis */
    static SensorFaults FaultSSens;                     /* Union - Fault analysis */
    static SensorFaults FaultWSens;                     /* Union - Fault analysis */
    static SensorFaults SoftSimFaults;                  /* Union - Thermocouple full scale simulation */
    static SensorFaults FaultSensEmpty = {0};           /* Union - Fault analysis */
    
    static SystemFaults FaultSSys;                      /* Union - Fault analysis */
    static SystemFaults FaultSysAuthorize;              /* Union - Fault analysis */
    static SystemFaults FaultWSys;                      /* Union - Fault analysis */
    static SystemFaults FaultSysEmpty = {0};            /* Union - Fault analysis */
   
    static TCFaults Ts2_0;                              /* Union - Contains thermocouple faults*/ 
    static TCFaults Ts2_1;                              /* Union - Contains thermocouple faults*/ 
    static TCFaults Tt4_0;                              /* Union - Contains thermocouple faults*/  
    static TCFaults Tt4_1;                              /* Union - Contains thermocouple faults*/  
    static TCFaults Tt4_2;                              /* Union - Contains thermocouple faults*/ 
    static TCFaults TB_0;                               /* Union - Contains thermocouple faults*/ 
    static TCFaults TB_1;                               /* Union - Contains thermocouple faults*/  
    static TCFaults TB_2;                               /* Union - Contains thermocouple faults*/ 

    /* REQUIRED INITIALIZATIONS */

    SoftSimFaults = FaultSensEmpty;                     /* Union - Thermocouple full scale simulation */

    /* Each union is initiated with null values */
    Ts2_0.TCFaultBits = 0;                              
    Ts2_1.TCFaultBits = 0;
    Tt4_0.TCFaultBits = 0;
    Tt4_1.TCFaultBits = 0;
    Tt4_2.TCFaultBits = 0;
    TB_0.TCFaultBits = 0;
    TB_1.TCFaultBits = 0;
    TB_2.TCFaultBits = 0;

	/* VARIABLES */
    
    /* int TYPE */
                                                        
    int EngUnits = 1;                                   /* Engineering units for thrust reference*/
    int Ignition = 0;                                   /* Ignition Signal */
    int LeverMode = 1;                                  /* Lever Mode */
    int Mode = 0;                                       /* Operating Mode */

    /* static int TYPE */

	static int BoosterLStatus = 0xFF;					/* Indicates if left booster is connected (0x55 -> boster connected; 0xAA -> boster released) */
	static int BoosterRStatus = 0xFF;					/* Indicates if left booster is connected (0x55 -> boster connected; 0xAA -> boster released) */
    static int ControlPhase = 0;                        /* Controller phase */
    static int CriticalFailure = 0;                     /* Flag indicating critical failure */
    static int Current_key_start = 0;                   /* Start key current value */   
    static int EmergencyCommand = 0;                    /* External command for emergency shut-off */    
    static int EmergShutDwn = 0;                        /* Flag (internal) indicating emergency shut-off */
    static int IgnitionFail = 0;                        /* Flag indicating ignition failure */
    static int ModelParsStart = 0;                      /* Flag indicating if model parameters initiation is needed */
    static int Old_key_start = 0;                       /* Start key old value */
    static int OnOffCom = 0xFF;                         /* Command for on/off */
    static int Reset = 0;                               /* Reset flag and pulse detection variable */
    static int ResetButton[2] = {0, 0};                 /* String containing reset button states */ 
    static int ShutDownCommand = 0;                     /* Command for standard shut-Off */
    static int SingleStop = 0;                          /* Flag for single execution of piece of code */
    static int SkipStart = 0;                           /* Flag indicating if starting algorithm is needed */   
    static int StartCommand = 0;                        /* Command for engine start */
    static int StartComplete = 0;                       /* Flag indicating that engine start is complete */
    static int StartFaultAnalysis = 0;                  /* Flag indicating that fault analysis must be accomplished */

    /* unsigned int TYPE */

    unsigned int digitalWord = 0;                      /* Word containing digital outputs states */
	unsigned int GPIOIn = 0;                           /* Contains key states in a single number */	
	unsigned int KeyBit0 = 1;                          // Igniter   - Input Keys for software in the loop simulation		
	unsigned int KeyBit1 = 1;                          // Shut_Off  - Input Keys for software in the loop simulation	 
	unsigned int KeyBit2 = 0;                          // Scaveng   - Input Keys for software in the loop simulation		
	unsigned int KeyBit3 = 1;                          // Oil Pump  - Input Keys for software in the loop simulation	
	unsigned int KeyBit4 = 0;                          // AC_Drive  - Input Keys for software in the loop simulation	
	unsigned int KeyBit5 = 1;                          // Emergency - Input Keys for software in the loop simulation	
	unsigned int KeyBit6 = 0;                          // Mode	    - Input Keys for software in the loop simulation
    unsigned int keysWord = 0;                         /* Word containing external key states */   

	/* double TYPE */

    double Altitude = 567;                              /* Altitude value */
    double Delta = 1;                                       /* Delta = Pt2/PSTD - correction parameter */
    double dT = 0;                                      /* Day temperature variation */
    double FNcMax = 0;                                  /* Maximum allowed corrected net thrust */
    double FNpc = 0;                                    /* Corrected net thrust */
    double MN = 0;                                      /* Flight Mach number value */
	double OPRPMManual = 0;								/* Manual reference for oil pump rotation speed */
    double POil = 0;                                    /* Oil pressure */
    double Pt2 = 101325;                                /* Compressor inlet total pressure */
    double Pt3 = 101325;                                /* Compressor exhaust total pressure */ 
    double Pt3MedVal = 101325;                          /* Pt3 medium value */
    double RefCAN = 0;                                  /* Reference from CAN */    
    double reference = 0.35;                            /* Reference value used initially */    
    double RPM = 0;                                     /* Engine mechanical rotation speed */  
    double RPMMedVal = 0;                               /* RPM medium value */
    double TBear[5] = {0,0,0,0,0};                      /* String containing bearings temperatures */
    double Ts2 = 288.15;                              	/* Compressor inlet static temperature */
    double Ts2MedVal = 288.15;                          /* Ts2 medium value */
    double Tt2 = 288.15;                                /* Compressor inlet total temperature */
    double Tt4 = 288.15;                                /* Combustion chamber total temperature */
    double Tt4MedVal = 288.15;                          /* Tt4 medium value */
    double Tt5 = 288.15;                                /* Turbine inlet total temperature */
    double WaitTime = 0;                                /* Used by general purpose timer */
    double Wf0 = 0;                                     /* Initial fuel flow value */

    /* static double TYPE */

	static double OPRPM = 0;                            /* Oil pump rotation speed */
    static double Wf = 0;                               /* Fuel flow */

    // /* VARIABLES */
    
    // /* int TYPE */
                                                        
    // int EngUnits = 0;                                   /* Engineering units for thrust reference*/
    // int Ignition = 0;                                   /* Ignition Signal */
    // int LeverMode = 1;                                  /* Lever Mode */
    // int Mode = 0;                                       /* Operating Mode */

    // /* static int TYPE */

    // static int ControlPhase = 0;                        /* Controller phase */
    // static int CriticalFailure = 0;                     /* Flag indicating critical failure */
    // static int Current_key_start;                       /* Start key current value */   
    // static int EmergencyCommand = 0;                    /* External command for emergency shut-off */    
    // static int EmergShutDwn = 0;                        /* Flag (internal) indicating emergency shut-off */
    // static int IgnitionFail = 0;                        /* Flag indicating ignition failure */
    // static int ModelParsStart = 0;                      /* Flag indicating if model parameters initiation is needed */
    // static int Old_key_start;                           /* Start key old value */
    // static int OnOffCom = 0xFF;                         /* Command for on/off */
    // static int Reset = 0;                               /* Reset flag and pulse detection variable */
    // static int ResetButton[2] = {0, 0};                 /* String containing reset button states */ 
    // static int ShutDownCommand = 0;                     /* Command for standard shut-Off */
    // static int SingleStop = 0;                          /* Flag for single execution of piece of code */
    // static int SkipStart = 0;                           /* Flag indicating if starting algorithm is needed */   
    // static int StartCommand = 0;                        /* Command for engine start */
    // static int StartComplete = 0;                       /* Flag indicating that engine start is complete */
    // static int StartFaultAnalysis = 0;                  /* Flag indicating that fault analysis must be accomplished */

    // /* unsigned int TYPE */

    // unsigned int digitalWord;                          /* Word containing digital outputs states */
	// unsigned int GPIOIn = 0;                           /* Contains key states in a single number */	
	// unsigned int KeyBit0 = 1;                          // Igniter   - Input Keys for software in the loop simulation		
	// unsigned int KeyBit1 = 1;                          // Shut_Off  - Input Keys for software in the loop simulation	 
	// unsigned int KeyBit2 = 0;                          // Scaveng   - Input Keys for software in the loop simulation		
	// unsigned int KeyBit3 = 1;                          // Oil Pump  - Input Keys for software in the loop simulation	
	// unsigned int KeyBit4 = 0;                          // AC_Drive  - Input Keys for software in the loop simulation	
	// unsigned int KeyBit5 = 1;                          // Emergency - Input Keys for software in the loop simulation	
	// unsigned int KeyBit6 = 0;                          // Mode	    - Input Keys for software in the loop simulation
    // unsigned int keysWord;                             /* Word containing external key states */   

	// /* double TYPE */

    // double Altitude = 0;                                /* Altitude value */
    // double Delta;                                       /* Delta = Pt2/PSTD - correction parameter */
    // double dT = 0;                                      /* Day temperature variation */
    // double FNcMax = 0;                                  /* Maximum allowed corrected net thrust */
    // double FNpc = 0;                                    /* Corrected net thrust */
    // double MN = 0;                                      /* Flight Mach number value */
	// double OPRPMManual = 0;								/* Manual reference for oil pump rotation speed */
    // double POil = 0;                                    /* Oil pressure */
    // double Pt2 = 101325;                                /* Compressor inlet total pressure */
    // double Pt3;                                         /* Compressor exhaust total pressure */ 
    // double Pt3MedVal = 0;                               /* Pt3 medium value */
    // double RefCAN = 0;                                  /* Reference from CAN */    
    // double reference = 0.35;                            /* Reference value used initially */    
    // double RPM;                                         /* Engine mechanical rotation speed */  
    // double RPMMedVal = 0;                               /* RPM medium value */
    // double TBear[5];                                    /* String containing bearings temperatures */
    // double Ts2 = 288.15;                                /* Compressor inlet static temperature */
    // double Ts2MedVal = 288.15;                          /* Ts2 medium value */
    // double Tt2 = 288.15;                                /* Compressor inlet total temperature */
    // double Tt4;                                         /* Combustion chamber total temperature */
    // double Tt4MedVal = 0;                               /* Tt4 medium value */
    // double Tt5;                                         /* Turbine inlet total temperature */
    // double WaitTime;                                    /* Used by general purpose timer */
    // double Wf0;                                         /* Initial fuel flow value */

    // /* static double TYPE */

    // static double OPRPM;                                /* Oil pump rotation speed */
    // static double Wf = 0;                               /* Fuel flow */

    /*-----------------------------------------------------------*/
    /* FADEC VARIABLES - USED ONLY BY FADEC AND NOT BY THE MODEL */
    /*-----------------------------------------------------------*/

    /* int TYPE */

    int Authorize = 0;                                     /* Flag indicating that controller is authorized to perform */
    int Fn_Elem = TJ1200_FN_ELEM;                      /* Number of net thrust breakpoint elements */
    int MN_Elem = TJ1200_MN_ELEM;                      /* Number of Mach number breakpoint elements */

    /* double TYPE */

    double AuxTimer = 0;                                    /* Dummy timer for general purposes */
    double Ts = 0.001 * TICK;                           /* Sampling Time */

    /* double TYPE STRINGS */
  
    double AltLinVec[TJ1200_ALT_ELEM];                      /* Altitude breakpoints */
    double AMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];           /* Model - A matrix */
    double ASVec[TJ1200_AS_ELEM];                           /* Controller - Asceleration schedule (ASVec) break points */
    double BMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];           /* Model - B matrix */
    double DeltaMtx[TJ1200_ALT_ELEM * TJ1200_MN_ELEM];      /* Controller - Delta matrix */
    double DeltaMtx1D[TJ1200_MN_ELEM];                      /* Auxiliar matrix - Delta */
    double DeltaMtx1DH[TJ1200_MN_ELEM];                     /* Auxiliar matrix - Delta */
    double DeltaMtx2D[TJ1200_ALT_ELEM * TJ1200_MN_ELEM];    /* Auxiliar matrix - Delta */
    double DeltaMtx2DH[TJ1200_ALT_ELEM * TJ1200_MN_ELEM];   /* Auxiliar matrix - Delta */
    double DSVec[TJ1200_AS_ELEM];                           /* Controller - Deceleration schedule (DSVec) break points */
    double FNcMaxContMtx[TJ1200_MN_ELEM];                   /* Controller - Maximum corrected net thrust values */
    double FNperContMtx[TJ1200_TOTAL_ELEM];                 /* Controller - net thrust percentual values matrix */
    double MapHPC1D[TJ1200_FAN_PR];                         /* Auxiliar matrix - HPC map */
    double MapHPC1DH[TJ1200_FAN_PR];                        /* Auxiliar matrix - HPC map */
    double MapHPC2D[TJ1200_FAN_NC * TJ1200_FAN_PR];         /* Auxiliar matrix - HPC map */
    double MapHPC2DH[TJ1200_FAN_NC * TJ1200_FAN_PR];        /* Auxiliar matrix - HPC map */
    double MNLinVec[TJ1200_MN_ELEM];                        /* Mach number breakpoints */
    double Mtx1D[TJ1200_FN_ELEM];                           /* Auxiliar matrix */
    double Mtx1DH[TJ1200_FN_ELEM];                          /* Auxiliar matrix */
    double Mtx2D[TJ1200_MN_ELEM * TJ1200_FN_ELEM];          /* Auxiliar matrix */
    double Mtx2DH[TJ1200_MN_ELEM * TJ1200_FN_ELEM];         /* Auxiliar matrix */
    double N_KiMtx[TJ1200_TOTAL_ELEM];                      /* Controller - Ki matrix of N control law */
    double N_KpMtx[TJ1200_TOTAL_ELEM];                      /* Controller - Kp matrix of N control law */
    double NcFANContMtx[TJ1200_TOTAL_ELEM];                 /* Controller - Fan Nc breakpoints */
    double NcHPCMapMtx[TJ1200_FAN_NC];                      /* Model - Nc break points matrix - HPC map */
    double NcVec[TJ1200_AS_ELEM];                           /* Controller - Nc schedule (for ASVec and DSVec) break points */
    double PRHPCMapMtx[TJ1200_FAN_NC * TJ1200_FAN_PR];      /* Model - PR break points matrix - HPC map */
    double Pt3DMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];        /* Model - Pt3D matrix */
    double Pt3Mtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];         /* Model - Pt3 matrix */
    double Pt5DMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];        /* Model - Pt5D matrix */
    double Pt5Mtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];         /* Model - Pt5 matrix */
    double Ts0Mtx[TJ1200_ALT_ELEM];                         /* Controller and Model - Ts0 break points  */
    double Ts0Mtx1D[TJ1200_ALT_ELEM];                       /* Auxiliar matrix - Ts0 */
    double Ts0Mtx1DH[TJ1200_ALT_ELEM];                      /* Auxiliar matrix - Ts0 */
    double Ts0Mtx2D[TJ1200_FN_ELEM];                        /* Auxiliar matrix - Ts0 */
    double Ts0Mtx2DH[TJ1200_FN_ELEM];                       /* Auxiliar matrix - Ts0 */
    double Tt4DMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];        /* Model - Tt4D matrix */
    double Tt4Mtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];         /* Model - Tt4 matrix */
    double Tt5DMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];        /* Model - Tt5D matrix */
    double Tt5Mtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];         /* Model - Tt5 matrix */
    double WcHPCMapMtx[TJ1200_FAN_NC * TJ1200_FAN_PR];      /* Model - Wc break points matrix - HPC map */
    double WfMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];          /* Model - Wf matrix */

	/*=======================================================*/
	/* PIECE OF CODE TO BE EXECUTED WITHIN THE MAIN FUNCTION */
	/*=======================================================*/
        
    /* ----------- */
	/* SINGLE STOP */ 
	/* ----------- */
    
    if(SingleStop == 0)
    {

        /*-----------------*/
        /* FADEC AND MODEL */
        /*-----------------*/
        
        /* STRUCTS INITIALIZATION */

        Ambient = AmbientEmpty;
        BlowOutPars = EstParsEmpty;
        ContConst = ContConstEmpty;
        ContGenOil = ContGenEmpty;
        ContInModCL = ContInputEmpty;
        ContInput = ContInputEmpty;
        ContOutModCL = ContOutputEmpty;
        ContOutput = ContOutputEmpty;
        ContStart = ContStartEmpty;
        ContStModCL = ContStartEmpty;
        EngOnOff = EngOnOffEmpty;
        Index3D = Index3DEmpty;
        ModelPars = EstParsEmpty;
        ModelParsChosen = EstParsEmpty;
        ModelParsCL = EstParsEmpty;
        PFuelRes = DefaultRes;
        POilRes = DefaultRes;
        Pt3Res = DefaultRes;
        RPMRes = DefaultRes;
        Sensors = SensorsEmpty;
        TBearRes = DefaultRes;
        Ts2Res = DefaultRes;
        Tt4Res = DefaultRes;
        VibrationRes = DefaultRes;

        /* UNIONS INITIALIZATION */

		CANFault = FaultDetectEmpty;
        digital = digitalEmpty;
        digModCL = digitalEmpty;
        EngStatus = EngStatusEmpty;
        ExistFStatus = FaultDetectEmpty;
        ExistFWarning = FaultDetectEmpty;
        FaultSensAuthorize = FaultSensEmpty;
        FaultSSens = FaultSensEmpty;
        FaultSSys = FaultSysEmpty;
        FaultStatus = FaultEmpty;
        FaultSysAuthorize = FaultSysEmpty;
        FaultWarning = FaultEmpty;
        FaultWSens = FaultSensEmpty;
        FaultWSys = FaultSysEmpty;
        HardFAuthorize = FaultDetectEmpty;
        HardFStatus = FaultDetectEmpty;
        HardFWarning = FaultDetectEmpty;
        keys = keysEmpty;
        ModPFault.ModParsBits = 0;
        SoftFStatus = FaultDetectEmpty;
        SoftFWarning = FaultDetectEmpty;
        SoftSimFaults = FaultSensEmpty;
        TB_0.TCFaultBits = 0;
        TB_1.TCFaultBits = 0;
        TB_2.TCFaultBits = 0;
        TrustAll = FaultDetectEmpty;
        TrustHard = FaultDetectEmpty;
        TrustSens = FaultDetectEmpty;
        Ts2_0.TCFaultBits = 0;
        Ts2_1.TCFaultBits = 0;
        Tt4_0.TCFaultBits = 0;
        Tt4_1.TCFaultBits = 0;
        Tt4_2.TCFaultBits = 0;

        /* static int TYPE */

        SingleStop = 1;

    } 
    
    /* -------------------------------------------------- */
    

    /* LOADING OF CONTROLLER CONSTANTS */
    getTJ1200ContConst(&ContConst);
    
	/* LOADING OF CONTROLLER MATRIX */

    /* Linearization Vectors */
    getTJ1200AltLinVec(&AltLinVec);
    getTJ1200MNLinVec(&MNLinVec);
    getTJ1200Ts0Mtx(&Ts0Mtx);
    getTJ1200DeltaMtx(&DeltaMtx);

    /* Controller Gains */
	getTJ1200N_KpMtx(&N_KpMtx);
	getTJ1200N_KiMtx(&N_KiMtx);
	getTJ1200NcFANContMtx(&NcFANContMtx);
    getTJ1200FNcMaxContMtx(&FNcMaxContMtx);
	getTJ1200FNperContMtx(&FNperContMtx);

    /* Reference Filter */
    getTJ1200ASVec(&ASVec);
    getTJ1200DSVec(&DSVec);
    getTJ1200NcVec(&NcVec);
    
    /* LOADING OF MODEL MATRICES */
        
    getTJ1200AMtx(&AMtx);
    getTJ1200BMtx(&BMtx);
    getTJ1200Pt3DMtx(&Pt3DMtx);
    getTJ1200Pt5DMtx(&Pt5DMtx);
    getTJ1200Tt4DMtx(&Tt4DMtx);
    getTJ1200Tt5DMtx(&Tt5DMtx);
    getTJ1200Pt3Mtx(&Pt3Mtx);
    getTJ1200Pt5Mtx(&Pt5Mtx);    
    getTJ1200Tt4Mtx(&Tt4Mtx);
    getTJ1200Tt5Mtx(&Tt5Mtx);
    getTJ1200WfMtx(&WfMtx);
    getTJ1200PRHPCMapMtx(&PRHPCMapMtx);
    getTJ1200WcHPCMapMtx(&WcHPCMapMtx);
    getTJ1200NcHPCMapMtx(&NcHPCMapMtx);

	/* LOADING OF CONTROLLER STARRING PARAMETERS */
	//getTJ1200StartPars(&ContStart);

    /*---------------------------------------------*/
	/* INITIATES REFERENCE COMMAND WITH IDLE VALUE */
	/*---------------------------------------------*/

	//RefCAN = ContConst.FNIdle;

	/* ================================================================================= */
	/* THE FOLLOWIN CODE MUST BE EXECUTED BY A TIMER ROUTINE OF THE HARDWARE IN THE LOOP */
	/* ================================================================================= */
    
    /* -------------------------------------------------- */
	/* AUXILIARY VARIABLE - TMATS                         */
	/* (To be usedi in MATLAB and TMATS simulations only) */
	/* -------------------------------------------------- */
    
    TMATS_StartComplete = InputTMATS[0];
    
    /* -------------------------------------------------- */
	
    /* ---------------------------------------- */
	/* INPUT READINS - T-MATS & PWML            */
	/* (To be usedi in MATLAB simulations only) */
	/* ---------------------------------------- */

	Altitude = InputVars[0];
	MN = InputVars[1];
	reference = InputVars[6];
	POil = InputVars[7];
	//SkipStart = InputVars[8];
    SkipStartIn[1] = SkipStartIn[0];
    SkipStartIn[0] = InputVars[8];
	Authorize = InputVars[9];
	Wf0 = InputVars[10];
	ResetButton[0] = InputVars[11];

	/* Reads mode key */
	Mode = InputVars[12];
	LeverMode = InputVars[13];
    
    /* Reads Pt2 - Needed for Delta calculations */
	Pt2 = InputVars[14];

	/* Reads tick value - FOR USE WITH T-MATS ONLY. COMMENT IF HARDWARE*/
	tack = tick;
	tick = InputVars[15];
    
    /* Reads flag indicating that engine units are used for thrust reference */
    EngUnits = InputVars[16];

    /* Reads digital keys */
    GPIOIn = (int)InputVars[17];

    /* Reads Start/Shut Down/Emergency external command */
    OnOffCom = InputVars[18];

    /* Reads bearings temperatures */
    TBear[0] = InputVars[19];
    TBear[1] = InputVars[20];
    TBear[2] = InputVars[21];

	/* External manual oil pump rotation speed reference */
	OPRPMManual = InputVars[22];

    /* Booster state */
    BoosterLStatus = InputVars[23];
    BoosterRStatus = InputVars[24];
 
    /* ---------------------------------------- */
    
    /* -------------------------------------------------- */
	/* SENSOR READING - TMATS & PWLM                      */
	/* (To be usedi in MATLAB and TMATS simulations only) */
	/* -------------------------------------------------- */
    
    Sensors.Ts2[0] = InputSensors[0];
    Sensors.Ts2[1] = InputSensors[1];
    Sensors.Pt3[0] = InputSensors[2];
    Sensors.Tt4[0] = InputSensors[3];
    Sensors.Tt4[1] = InputSensors[4];
    Sensors.Tt4[2] = InputSensors[5];
    Sensors.RPM[0] = InputSensors[6];
    Sensors.RPM[1] = InputSensors[7];
    Sensors.POil[0] = InputSensors[8];
    Sensors.PFuel[0] = InputSensors[9];
    Sensors.Vibration[0] = InputSensors[10];
    Sensors.TBear[0] = InputVars[19];
    Sensors.TBear[1] = InputVars[20];
    Sensors.TBear[2] = InputVars[21];
    
    /* Reads word containing faults simulated by siftware */
    SoftSimFaults.FaultBits = (uint64_t)InputFaults[0];

    /* Reads word containing CAN faults */
    CANFault.FaultBits = (uint64_t)InputCANFaults[0];
        
    /* -------------------------------------------------- */

    // /*--------------------------------------------*/
	// /* THERMOCOUPLE FAULT SIMULATION VIA SOFTWARE */
	// /*--------------------------------------------*/
    
    // /* Thermocouple fault simulation */
    // TCFault(&Sensors, &SoftSimFaults, &FaultSensAuthorize, &Ts2_0, &Ts2_1, &Tt4_0, &Tt4_1, &Tt4_2, &TB_0, &TB_1, &TB_2, ContConst.TCOpen);

	/* -------------------------------------------------- */
    /* VERIFICATION IF reference > 0 after reading        */
    /* (To be usedi in MATLAB (PWLM) simulations only)    */
    /* -------------------------------------------------- */

	/* This condition simulates the reading of thrust
	reference external command, authorizing the engine
	state to be changed to REGIME if a non-zero command
	has been setn  */
	// if(reference > 0)
	// {
	// 	ContInput.ThrustCommandOn = 1;
	// }

    /* -------------------------------------------------- */

	/*-------------------------*/
	/* RESET REQUEST TREATMENT */
	/*-------------------------*/

	/* Reads reset signal */
	Reset = Edge(ResetButton);
	ResetButton[1] = ResetButton[0];

	/* Verifies if reset has been requested */
	if (Reset == 1) 
	{

        /*-----------------*/
        /* FADEC AND MODEL */
        /*-----------------*/

        /* RESETS STRUCTS */

        Ambient = AmbientEmpty;
        BlowOutPars = EstParsEmpty;
        ContConst = ContConstEmpty;
        ContGenOil = ContGenEmpty;
        ContInModCL = ContInputEmpty;
        ContInput = ContInputEmpty;
        ContInput.Reset = 1;
        ContOutModCL = ContOutputEmpty;
        ContOutput = ContOutputEmpty;
        ContStart = ContStartEmpty;
        ContStModCL = ContStartEmpty;
        EngOnOff = EngOnOffEmpty;
        Index3D = Index3DEmpty;
        ModelPars = EstParsEmpty;
        ModelParsChosen = EstParsEmpty;
        ModelParsCL = EstParsEmpty;
        PFuelRes = DefaultRes;
        POilRes = DefaultRes;
        Pt3Res = DefaultRes;
        RPMRes = DefaultRes;
        Sensors = SensorsEmpty;
        TBearRes = DefaultRes;
        Ts2Res = DefaultRes;
        Tt4Res = DefaultRes;
        VibrationRes = DefaultRes;

        /* RESETS UNIONS */
        
		CANFault = FaultDetectEmpty;
        digital = digitalEmpty;
        digModCL = digitalEmpty;
        EngStatus = EngStatusEmpty;
        ExistFStatus = FaultDetectEmpty;
        ExistFWarning = FaultDetectEmpty;
        FaultSensAuthorize = FaultSensEmpty;
        FaultSSens = FaultSensEmpty;
        FaultSSys = FaultSysEmpty;
        FaultStatus = FaultEmpty;
        FaultSysAuthorize = FaultSysEmpty;
        FaultWarning = FaultEmpty;
        FaultWSens = FaultSensEmpty;
        FaultWSys = FaultSysEmpty;
        HardFAuthorize = FaultDetectEmpty;
        HardFStatus = FaultDetectEmpty;
        HardFWarning = FaultDetectEmpty;
        keys = keysEmpty;
        ModPFault.ModParsBits = 0;
        SoftFStatus = FaultDetectEmpty;
        SoftFWarning = FaultDetectEmpty;
        SoftSimFaults = FaultSensEmpty;
        TB_0.TCFaultBits = 0;
        TB_1.TCFaultBits = 0;
        TB_2.TCFaultBits = 0;
        TrustAll = FaultDetectEmpty;
        TrustHard = FaultDetectEmpty;
        TrustSens = FaultDetectEmpty;
        Ts2_0.TCFaultBits = 0;
        Ts2_1.TCFaultBits = 0;
        Tt4_0.TCFaultBits = 0;
        Tt4_1.TCFaultBits = 0;
        Tt4_2.TCFaultBits = 0;

        /* RESETS static int TYPE */
              
        CriticalFailure = 0;
        Current_key_start = 0;
        EmergencyCommand = 0;
        Old_key_start = 0;
        Reset = 0;     
        ShutDownCommand = 0;
        StartCommand = 0;
        StartComplete = 0;
        StartFaultAnalysis = 0;

        /* RESETS double TYPE */

		OPRPMManual = 0;

        /* RESETS static double TYPE */

        Wf = 0;

        /*------------*/
        /* FADEC ONLY */
        /*------------*/

        /* RESETS int TYPE */

		Authorize = 0;

        /* -------------------------------------------------- */
        /* T-MATS AND PWLM           */
        /* (To be usedi in MATLAB and TMATS simulations only) */
        /* -------------------------------------------------- */

        SkipStartIn[0] = 0;
        SkipStartIn[1] = 0;

        /* -------------------------------------------------- */

    }

    /* -------------------------------------------------- */
	/* SIMULATION OF A SINGLE READ OF SkipStart           */
	/* (To be usedi in MATLAB and TMATS simulations only) */
	/* -------------------------------------------------- */

    if (Edge(SkipStartIn) == 1)
    {
        /* Updates SkipStart */
        SkipStart = 1;
    }

	/* --------------------------------------------------------------- */

    /*-----------------------------------------------------------*/
    /* VARIABLES INITIALIZATIONS IN CASE ENGINE START IS SKIPPED */
    /*															 */
    /* In those cases, ain initial operating condition where the */
    /* engine thrust is non-zero is considered					 */
    /*-----------------------------------------------------------*/

    if (SkipStart == 1 && StartComplete == 0) 
	{

		/* Sets initial conditions for fuel values and rotation speed references */
		ContOutput.Wf = Wf0;
		ContOutput.uNk1 = ContOutput.Wf;
		ContOutput.urk1 = ContOutput.Wf;
		ContOutput.ITermNk1 = ContOutput.Wf;
		ContOutput.uTt4k1 = ContOutput.Wf;
		ContOutput.ITermTk1 = ContOutput.Wf;
		ContOutput.eNk1 = 0;
		ContOutput.eTt4k1 = 0;
		ContOutput.RPMRef = RPM;
		ContOutput.MinRef = RPM;
		ContStart.RefInit = RPM;
		ContOutput.Active = 0;
		ContOutput.StartComplete = 1;

        /* Sets initial condition for oil pump rotation speed OPRPM */
        OPRPM = ContConst.OPRPMMax;

        /* Sets initial conditions for bearings temperatures controller */
        /* NOTE: Currently, the idiea is to start the oil pump at its
        maximum rotation speed whenever the simulation is required to
        start from a condition where the engine has already started */
        for (int i = 0; i < ContConst.NumBear; i++)
        {
            ContGenOil.uOut[i] = ContConst.OPRPMMax;
            ContGenOil.uk1[i] = ContConst.OPRPMMax;
            ContGenOil.ITermk1[i] = ContConst.OPRPMMax;
            ContGenOil.ek1[i] = 0;
            ContGenOil.eBk1[i] = 0;
        }

        //OPRPM = ContConst.OPRPMMax;

        /* Sets starting variables */
        ContStart.WfTrigger = ContOutput.Wf;
        ContStart.RefInitStatus = 1;

        /* Sets SkipStart to 0 */
        SkipStart = 0;

        /* Sets StartComplete to 1 */
        StartComplete = 1;

        /* Sets left and right boosters status to ejected */
        BoosterLStatus = 0xAA;
        BoosterRStatus = 0xAA;
        ContInput.statusBooster = 1;
        ContInModCL.statusBooster = 1;

        /* Sets engine status to REGIME */
        EngStatus.EngineStatus = 0;
        EngStatus.EngStatusBist.Regime = 1;
		ContInput.ThrustCommandOn = 1;

        /* Set on off status to 1 */
		EngOnOff.statusOnOff = 1;
		EngOnOff.OnOffCom = 0xAA;

		/* Sets OnOffMessage to its initial value */
		OnOffCom = 0xFF;
        ShutDownCommand = 0;
        EmergencyCommand = 0;
        StartCommand = 1;
		CriticalFailure = 0;

        /* Sets fault analysis flag to initial state */
        StartFaultAnalysis = 0;

        /* Sets flag indicating that model parameters must be started */
        ModelParsStart = 1;

    }

    /*-----------------------------------------------*/
	/* UPDATES REFERENCE FOR CONTROL LAW CALCULATION */
	/*-----------------------------------------------*/

	//Ignition = digital.bits.igniter;
	// RefCAN = (double)reference;				/* This should be done in the hardware */

	/* -------------------------------------------------- */
	/* UPDATING RefCAN and FNpc - PWLM		              */
	/* (To be usedi in MATLAB (PWLM) simulations only)    */
	/* -------------------------------------------------- */

	// if (EngStatus.EngineStatus == 32 | ContInput.ThrustCommandOn > 0)
	// {
	// 	RefCAN = (double)reference;
	// }

	/* -------------------------------------------------- */

	//FNpc = RefCAN;
    
    /* Stores CAN fault bit value */
	// FaultSSys.SysFaults.CAN_0_Fault = CANFault.SysFaults.CAN_0_Fault;
	// FaultSSys.SysFaults.CAN_1_Fault = CANFault.SysFaults.CAN_1_Fault;

    /* Updates FNpc and allows transition from IDLE to REGIME depending no reference value */
	IdleToRegime(&EngStatus, &ContInput, reference, 0, ContConst.FNIdle, &FNpc, LeverMode);

	/*---------------*/
	/* CONTROL LOGIC */
	/*---------------*/
   
    /* -------------------------------------------------- */
	/* EXTERNAL SAMPLING TIME - TMATS & PWLM              */
	/* (To be usedi in MATLAB and TMATS simulations only) */
	/* -------------------------------------------------- */
    
    /* TMATS */

    // Authorize = 0;
    // if (tick != tack) {
    //     Authorize = 1;
    // }

    /* PWLM */

    if (tick == tack) {
        Authorize = 0;
    }
    
    /*----------------------------------------------------*/
    
    /* Checks for authorization of controller calculations */
    if(Authorize == 1)
    {

        /* -------------------------------------------------- */
	    /* SIMULATION OF GPIO PINES - TMATS & PWLM            */
	    /* (To be usedi in MATLAB and TMATS simulations only) */
	    /* -------------------------------------------------- */
        
        /* Simulates reading from each GPIO pin */
        keys.in = GPIOIn & 0x7FF;

        /* Reads start key - pulse detection */
        Old_key_start = Current_key_start;
        Current_key_start = 0;// !keys.bits.ac_drive_key || Authorize;

        /* CAN 1 Misscommunication treatment */
		CAN1MissComm(&FaultStatus, &EngStatus, &OnOffCom, ContConst.EmergencyCom, ContConst.ShutDownCom);

        /* LOADS EngOnOff PARAMETERS */

		EngOnOff.CurrentKey = Current_key_start;
		EngOnOff.EmergencyKey = !keys.bits.emergency_key;
		EngOnOff.EmergencyWait = ContConst.EmergencyWait;
		EngOnOff.OldKey = Old_key_start;
		EngOnOff.OnOffCom = OnOffCom;
		EngOnOff.ShutDownKey = keys.bits.ac_drive_key;
		EngOnOff.ShutDownWait = ContConst.ShutDownWait;
		EngOnOff.StartKey = 0;//!keys.bits.ac_drive_key;
		EngOnOff.StartWait = ContConst.StartWait;	
		EngOnOff.Emergency = EmergencyCommand;
		EngOnOff.Start = StartCommand;
		EngOnOff.ShutDown = ShutDownCommand;
		EngOnOff.StartCom = ContConst.StartCom;
		EngOnOff.ShutDownCom = ContConst.ShutDownCom;
		EngOnOff.EmergencyCom = ContConst.EmergencyCom;

		OnOffLogicSR(&EngOnOff, Ts);

		/* Updates starting keys */
		Old_key_start = EngOnOff.OldKey;
		Current_key_start = EngOnOff.CurrentKey;
	
    	/* Updates commands */
		StartCommand = EngOnOff.Start;
		EmergencyCommand = EngOnOff.Emergency;
		ShutDownCommand = EngOnOff.ShutDown;
                
        /* -------------------------------------------------- */
        /* AUXILIARY VARIABLE - TMATS                         */
        /* (To be usedi in MATLAB and TMATS simulations only) */
        /* -------------------------------------------------- */
   
        ContInput.TMATS_StartComplete = TMATS_StartComplete;
        
        /* -------------------------------------------------- */

		/*=====================================================================*/
		/*   START OF SSModelLoop.c AND PIMMRF_TJ1200.c IDENTICAL CODE PIECE   */
		/*																       */
		/*   NOTE: The following procedures must be accomplished for the       */
		/*         current versions of FADEC and HIL					       */
		/*			- The matrices in the FADEC are stored in strings, being   */
		/*        directly declared as so, i.e., double Matrix(Size);    	   */
		/*			- The matrices in the HIL are stored with "alloc" command  */
		/*        and each matrix variable is a poiter for double, i.e.,       */
		/*        double *Matrix; 											   */
		/*			- The sample time in the FADEC is defined as Ts, while the */
		/*		  sample time in the HIL is defined as Tsample				   */
		/*		  															   */
		/*	Taking into account the above considerations, the following steps  */
		/*	must be accomplished:											   */
		/*   - Whenever a matrix pointer is passed as a function argument in   */
		/*     the FADEC, it should be called as function(..., &Matrix, ...)   */
		/*   - Whenever a matrix pointer is passed as a function argument in   */
		/*     the HIL, it should be called as function(..., Matrix, ...)      */
		/*   - The sample time is passed as function(..., Ts, ...) in the 	   */
		/*     FADEC and as function (..., Tsample, ...) in the HIL	           */
		/*     			  													   */
		/*=====================================================================*/

        /*--------------------------------------------*/
        /* THERMOCOUPLE FAULT SIMULATION VIA SOFTWARE */
        /*--------------------------------------------*/

        /* Thermocouple fault simulation */
        TCFault(&Sensors, &SoftSimFaults, &FaultSensAuthorize, &Ts2_0, &Ts2_1, &Tt4_0, &Tt4_1, &Tt4_2, &TB_0, &TB_1, &TB_2, ContConst.TCOpen);

        /*----------------*/
        /* FAULT ANALYSIS */
        /*----------------*/

        /* Calculates thermocouple residuals according to identified faults */
        TCResCalc(&Ts2_0, &Ts2_1, &Tt4_0, &Tt4_1, &Tt4_2, &TB_0, &TB_1, &TB_2,
                  &Ts2Res, &Tt4Res, &TBearRes);

        /* Estimation of indexes using current Altitude, MN and FNpc values */
        /* In this case, the structure ModelPars must be used - Open-Loop model */
        EstIndex(&ModelPars, &AltLinVec, &MNLinVec,
                       &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH,
                       &FNperContMtx, &ContConst, &Index3D);      

        /* CALCULATION OF ENGINE MODEL Ts2 */

        /* Calculation of model ambient temperature */
        /* In this case, the structure ModelPars must be used - Open-Loop model */
        Ts2ModelCalc(&Ts0Mtx, &ContConst,
             &Ts0Mtx2D, &Ts0Mtx2DH, &Ts0Mtx1D, &Ts0Mtx1DH,
             &ModelPars, &Index3D);

        /* Updates closed loop model ambient parameters from open-loop model */
        ModelParsCL.Ts2StdSL = ModelPars.Ts2StdSL;
        ModelParsCL.Ts2 = ModelPars.Ts2;
        ModelParsCL.Ts2Std = ModelPars.Ts2Std;

        /* CHOSES WHICH MODEL TO BE USED FOR RESIDUAL CALCULATIONS */
        /* ModelParsP - Open-Loop model */
        // ModelParsChosen = ModelPars;
        /* ModelParsP - Closed-Loop model */
        ModelParsChosen = ModelParsCL;

        /* INITIALIZATION OF AUTORIZING VARIABLES FOR FAULT ANALYSIS */
        // FaultSensAuthorize.FaultBits = 0xFFFFFFFFFFFFFFFF;
        // FaultSysAuthorize.FaultBits = 0xFFFFFFFFFFFFFFFF;
        // HardFAuthorize.FaultBits = 0xFFFFFFFFFFFFFFFF;

        /* ANALYSIS AUTHORIZING */

        SensAnalisysAuthorize(&FaultSensAuthorize, &ContStart, &ContInput, &EngStatus, StartFaultAnalysis);

        SysAnalisysAuthorize(&FaultSysAuthorize, &ContStart, &ContInput, &EngStatus, StartFaultAnalysis);

        BiasAnalisysAuthorize(&HardFAuthorize, &ContStart, &ContInput, &EngStatus, StartFaultAnalysis);
// HardFAuthorize.FaultBits = 0;
// FaultSensAuthorize.FaultBits = 0;
// FaultSysAuthorize.FaultBits = 0;
// HardFAuthorize.DetFaults.Ts2_0_Fault = 0;
// HardFAuthorize.DetFaults.Ts2_1_Fault = 0;
        /* RESIDUAL CALCULATION AND PROCESSING */

        /* Residuals calculations */
        /* In this case, two options: 
		- ModelPars for Open-Loop model
		- ModelParsCL for Closed-Loop model
		*/
        ResidualsCalc(&ContConst,
             &ModelParsChosen, &Sensors,
             &Ts2Res, &Pt3Res, &Tt4Res,
             &RPMRes, &POilRes, &PFuelRes,
             &VibrationRes, &TBearRes);

        /* Sensors residuals processing */
        /* In this case, two options: 
		- ModelPars for Open-Loop model
		- ModelParsCL for Closed-Loop model
		*/
        ResProcSens(&ContConst, &ModelParsChosen, &Sensors,
            &Ts2Res, &Pt3Res, &Tt4Res,
            &RPMRes, &POilRes, &PFuelRes,
            &VibrationRes, &TBearRes,
            &FaultSSens, &FaultWSens, &FaultSensAuthorize);

        /* Systems residuals processing */
        /* In this case, two options: 
		- ModelPars for Open-Loop model
		- ModelParsCL for Closed-Loop model
		*/
		ResProcSys(&ContConst, &ModelParsChosen,
				   &BlowOutPars, &Sensors,
				   &Ts2Res, &Pt3Res, &Tt4Res,
				   &RPMRes, &POilRes, &PFuelRes,
				   &VibrationRes, &TBearRes,
				   &FaultSSys, &FaultWSys, &FaultSysAuthorize,
				   &CANFault, &ContStart);

        /* Sensor bias residuals processing */
        /* In this case, two options: 
		- ModelPars for Open-Loop model
		- ModelParsCL for Closed-Loop model
		*/
        ResProcBias(&ContConst, &ModelParsChosen,
             &Ts2Res, &Pt3Res, &Tt4Res,
             &RPMRes, &POilRes, &PFuelRes,
             &VibrationRes, &HardFStatus, &HardFWarning, &HardFAuthorize); 

        /* FAULT ANALYSIS */

        /* Initiates trusted sens with 0xFFFF for possible overtemp and overspeed verification,
        and initial calculation of medium value */
        TrustSens.FaultBits = 0x7FF;
        TrustHard.FaultBits = 0x7FF;

        /* As soon as a complete start is dectedtec, an extra time period must be accounted for
		before fault analysis is carried on in order for the FADEC internal model to start matchin
		sensor measurements */
		if (StartComplete == 1 && StartFaultAnalysis == 0)
		{
			/* code */
			WaitTime = ContStart.WaitTime;
			StatusDelay(&WaitTime, Ts, ContConst.TimeFaultAnaylsis, &StartFaultAnalysis, 1);
			ContStart.WaitTime = WaitTime;

		}

        /* SENSOR FAULTS ISOLATED AT EACH SENSOR */

        /* Updates sensor isolated faults - Warnings */
        SensFaultUpdt(&FaultWarning, &FaultWSens, &FaultSensAuthorize);
        /* Updates sensor isolated faults - Status */
        SensFaultUpdt(&FaultStatus, &FaultSSens, &FaultSensAuthorize);

        /* ANALYSES OF SENSOR TRUSTWORTHINES */

        /* Sensors thrustworthiness analysis - checks if isolated sensor faults have occurred */
        SensorTrust(&TrustSens, &FaultSSens, &FaultWSens);
        

        /* SYSTEM FAULTS ISOLATED AT EACH SENSOR */

        /* Updates sensor faults - Warnings */
        SysFaultUpdt(&FaultWarning, &FaultWSys, &FaultSysAuthorize);
        /* Updates sensor faults - Status */
        SysFaultUpdt(&FaultStatus, &FaultSSys, &FaultSysAuthorize);

        /* HARD FAULTS - HIGH BIAS - AT EACH SENSOR */

        /* Updates sensor hard faults - Warnings */
        HardFaultUpdt(&FaultWarning, &HardFWarning, &HardFAuthorize);
        /* Updates sensor hard faults - Status */
        HardFaultUpdt(&FaultStatus, &HardFStatus, &HardFAuthorize);

        /* ANALYSES OF SENSOR TRUSTWORTHINES */

        /* Sensors thrustworthiness analysis - checks if high bias has occurred */
        HardTrust(&TrustHard, &HardFStatus, &HardFWarning);

        /* ISOLATION OF SYSTEMS FAULTS */

        /* Identification and isolation engine blow out */
        BlowOut(&TrustSens, &FaultSSys, &FaultStatus);

        /* Identification and isolation engine blow out */
        MecLock(&TrustSens, &FaultSSys, &FaultStatus);

        /* Verificatin of overtemp */
        OverTemp(&ContConst, &TrustSens, &FaultSSys, &Sensors, &FaultStatus);

        /* Verification of overspeed */
        OverSpeed(&TrustSens, &FaultSSys, &Sensors, &FaultStatus);

        /* Verification of ignition failure */
        FaultStatus.Faults.Ignition = FaultSSys.SysFaults.Ignition;//ContStart.IgnitionFail;

        /* IDENTIFICATION OF ENGINE STATUS */

        /* Identifies initial or windmilling status */
        EngStatusDeff(&EngStatus, &ModPFault, &ContInput,
                    &ContStart, &ContConst, 
                    0, 6,
                    StartCommand, 1, ContInput.ThrustCommandOn, 
                    ShutDownCommand, 1, EmergencyCommand, 1,
                    CriticalFailure, 1, Ts);

        /* CALCULATION OF MEDIUM VALUES */

        /* In this case, two options: 
		- ModelPars for Open-Loop model
		- ModelParsCL for Closed-Loop model
		*/

        /*The variable TrustAll indicates if either any sensor short/open or any sensor bias has occurred*/
        TrustAll.FaultBits = TrustHard.FaultBits & TrustSens.FaultBits;

        /* Below, the ModPFault struct indicates which modeled parameters has any fault at each of its sensors, indicating 
        that, for this particular parameter, only the model estimation is being used */

        /* Calculates the medium value of Ts2 - The last indicates the minimum number of trusted sensors before 
        untrusted sensors are replaced by model calculated values */
        Ts2MediumValue(&ModPFault, &Ts2MedVal, ContConst.NumTs2Sens, &TrustAll, &Sensors, ModelParsChosen.Ts2,ContConst.NumTs2SensTrust);
        /* Calculates the medium value of Pt3 - The last indicates the minimum number of trusted sensors before 
        untrusted sensors are replaced by model calculated values */
        Pt3MediumValue(&ModPFault, &Pt3MedVal, ContConst.NumPs3Sens, &TrustAll, &Sensors, ModelParsChosen.Pt3,ContConst.NumPs3SensTrust);
        /* Calculates the medium value of Tt4 - The last indicates the minimum number of trusted sensors before 
        untrusted sensors are replaced by model calculated values */
        Tt4MediumValue(&ModPFault, &Tt4MedVal, ContConst.NumTt4Sens, &TrustAll, &Sensors, ModelParsChosen.Tt4,ContConst.NumTt4SensTrust);
        /* Calculates the medium value of RPM - The last indicates the minimum number of trusted sensors before 
        untrusted sensors are replaced by model calculated values */
        RPMMediumValue(&ModPFault, &RPMMedVal, ContConst.NumRPMSens, &TrustAll, &Sensors, ModelParsChosen.RPM,ContConst.NumRPMSensTrust);
       
        /* Updates variables with calculated medium values */
        Ts2 = Ts2MedVal;
// if (EngStatus.EngineStatus > 4)
// {
//     /* If state is Ready STARTING and above, the Ts2 value is no longer obtained from sensors
//     This has been done for temporarely correcting oil pump noise in Ts2 thermocouples
//     MUST BE ERASED!! */
//     Ts2 = ModelPars.dT + ModelPars.Ts2Std;
// }
        Pt3 = Pt3MedVal;
        Tt4 = Tt4MedVal;
        RPM = RPMMedVal;
// mexPrintf("Ts2[0]=%f Ts2[1]=%f Ts2MedVal=%f\n",Sensors.Ts2[0], Sensors.Ts2[1], Ts2);
        /*------------------------------*/
        /* BEARINGS TEMPERATURE CONTROL */
        /*------------------------------*/

		/* Performs oil control as soon as Windmill is reached */
        TBearControl(&ContGenOil, &ContGenEmpty, &EngStatus, &ContConst, &Sensors, OPRPMManual, RPM, !Mode, Ts);

        /* ESTIMATION OF BACKGROUND STANDARD TEMPERATURE BASED ON ALTITUDE AND MN */

        /* In this case, the structure ModelPars must be used - Open-Loop model */

		Ambient.Alt = Altitude;
		Ambient.MN = MN;
		Ambient.dT = 0;
		Ambient_TMATS(&Ambient);

        /* Loads parameters fo Tt2 Calculations */
		ModelPars.gamma_air = GAMMA_AIR;
    	ModelPars.MN = MN;
    	ModelPars.Ts2Std = Ambient.Ts;

        /* Calculation of total temperature */        
        Tt2Calc(Ts2, &ModelPars); 

        /* Updates Tt2 and dT values */
        Tt2 = ModelPars.Tt2;
        dT = ModelPars.dT;
//mexPrintf("Tt2=%f dT=%f",Tt2,dT);
        /* UPDATES CLOSED-LOOP MODEL AMBIENT PARAMETERS FROM OPEN-LOOP MODEL */

        /* Updates closed loop model parameters */
        ModelParsCL.gamma_air = ModelPars.gamma_air;
        ModelParsCL.MN = MN;
        ModelParsCL.Ts2Std = ModelPars.Ts2Std;
        ModelParsCL.Tt2 = ModelPars.Tt2;
        ModelParsCL.dT = ModelPars.dT;
        ModelParsCL.Ts2StdSL = ModelPars.Ts2StdSL;

        PrintFaults(&FaultWarning,0,1);
        PrintFaults(&FaultStatus,1,0);
        PrintEngStatus(&EngStatus,1);

        /*-----------------------------------------------------*/
        /* VERIFIES EMERGENCY SHUT DOWN DUE TO ENGINE FAILURE  */
        /*-----------------------------------------------------*/

        FailureShutDown(&FaultStatus, &CriticalFailure);

		/*-------------------------------------------------------------*/
		/* CALCULATION OF REFERENCE IN CASE ENGINEERING UNITS ARE USED */
		/*-------------------------------------------------------------*/

		/* CALCULATION OF AMBIENT CONTIDIONS BASED ON ALTITUDE AND MACH NUMBER INFORMATION */
		Ambient.Alt = Altitude;
		Ambient.MN = MN;
		Ambient.dT = dT;

		Ambient_TMATS(&Ambient);
		Delta = Ambient.Pt / PSTD;

		/* CALCULATION OF MAXIMUM CORRECTED THRUST AT GIVEN FLIGHT MACH NUMBER IN CASE ENGINEERING UNITS ARE USED */

		/* Finds indexes from a dummy percentual value of Fnpc for obtaining the Mach number indexes */
		InterpInd3DRPM(0, MN, 0.95, &AltLinVec, &MNLinVec, &FNperContMtx, &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH, 1, MN_Elem, Fn_Elem, &Index3D);

		/* Shifts the indexes of Index3D for finding a 1D element */
		Index3D.kRPM = Index3D.kMN;
		Index3D.kRPMH = Index3D.kMNH;
		Index3D.fRPM = Index3D.fMN;
		Index3D.kMN = 0;
		Index3D.kMNH = 0;
		Index3D.fMN = 0;
		Index3D.kA = 0;
		Index3D.kAH = 0;
		Index3D.fA = 0;

		/* Finds the corrected value for maximum thrust at given flight Mach number */
		FNcMax = InterpValue(&Index3D, FNcMaxContMtx, Mtx1D, Mtx1DH, Mtx1D, Mtx1DH, MN_Elem, MN_Elem);

		/* Verifies if engineering units are to be used */
		if (EngUnits == 1)
		{
			/* Corrects FNpc in case engineering units are used */
			FNpc = FNpc / FNcMax / Delta;
		}

        /*--------------------*/
        /* ENGINE CONTROL LAW */
        /*--------------------*/
                
        /* Updates Controller Inputs */
        ContInput.Old_key_start = Old_key_start;
        ContInput.Current_key_start = Current_key_start;
        ContInput.bits_inverter = digital.bits.inverter;
        ContInput.Mode = Mode;
        ContInput.LeverMode = LeverMode;
        ContInput.EngUnits = EngUnits;
        ContInput.Altitude = Altitude;
        ContInput.MN = MN;
        ContInput.Tt2 = Tt2;
        ContInput.Pt3 = Pt3;
        ContInput.Tt4 = Tt4;
        ContInput.FNpc = FNpc;
        ContInput.RPM = RPM;
        ContInput.POil = POil;
        ContInput.SkipStart = SkipStart;
        ContInput.Wf0 = Wf0;
        keysWord = keys.in;
        digitalWord = digital.out;

        /* NOMINAL SHUT DWON REFERENCE */

        /* If nominal shut down has been requested, controller reference must be set to minimum */
        ShutDownRef(ShutDownCommand, &ContInput, &ContOutput, &ContConst, Ts);

        /* BOOSTER PHASE PROTECTION */

		/* If booster is connected, measured value of Pt3 must not be considered and blow out protection must be deactivated */
		BoosterProtect(&ContConst, &ContInput, Delta, BoosterLStatus, BoosterRStatus, Ts);
//mexPrintf("RealCont: BoostL=%d BoostR=%d Time=%f status=%d Delta=%f Pt3=%f\n",BoosterLStatus, BoosterRStatus, ContInput.TimerBoost, ContInput.statusBooster, Delta, ContInput.Pt3);
        /* CALCULATES THE CONTROL LAW */            
                    
        /* Calculates fuel flow from control law */
        PIMinMaxRF(&AltLinVec, &MNLinVec, &NcVec, &ASVec, &DSVec,
                &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH,
                &DeltaMtx2D, &DeltaMtx2DH, &DeltaMtx1D, &DeltaMtx1DH,
                &ContConst, &ContStart, &ContInput, &ContOutput, &digitalWord, &keysWord,
                &DeltaMtx, &NcFANContMtx, &FNcMaxContMtx, &FNperContMtx,
                &N_KpMtx, &N_KiMtx, Ts);
        
        /* Updates digital outputs and fuel flow value */
        digital.out = digitalWord;

        /* EXECUTES NOMINAL SHUT DOWN RAMP */

        ShutDownRamp(&ContInput, &ContInputEmpty,
                     &ContOutput, &ContOutputEmpty,
                     &ContStart, &ContStartEmpty, 
                     &ContGenOil, &ContGenEmpty,
                     &digital, &ContConst, Ts);

        /* EXECUTES EMERGENCY SHUT DOWN ROUTINE IF EMERGENCY HAS OCCURRED */

        /* Engine must execute emergency shut down either through external command of 
        Emergency or through detection of critical failure */
        EmergShutDwn = EmergencyCommand || CriticalFailure;

        EmergencyShutDown(&ContInput, &ContInputEmpty,
						  &ContOutput, &ContOutputEmpty,
						  &ContStart, &ContStartEmpty, 
                          &ContGenOil, &ContGenEmpty,
                          &digital, EmergShutDwn);
        
        /* Updates fuel flow value */
        Wf = ContOutput.Wf;

        /* Updates control signal - must be done after shut down analysis */
        OPRPM = ContGenOil.uOut[0];

        /* Updates starting phase outputs */
        StartComplete = ContOutput.StartComplete;
        IgnitionFail = ContOutput.IgnitionFail;
        ControlPhase = ContOutput.ControlPhase;

        /*--------------------*/             
        /* MODEL CALCULATIONS */
        /*--------------------*/

        /* Verifies if model parameters are to be started */
        if (ModelParsStart == 1)
        {

             /* Sets initial values of filtered parameters */
            ModelPars.WfOutfp = Wf0;
            ModelPars.Ts2Sensed = Ts2;
            ModelPars.Pt3Sensed = Pt3;
            ModelPars.Tt4Sensed = Tt4;

            /* Sets initial values of filtered parameters */
            BlowOutPars.WfOutfp = Wf0;
            BlowOutPars.Ts2Sensed = Ts2;
            BlowOutPars.Pt3Sensed = Pt3;
            BlowOutPars.Tt4Sensed = Tt4;

            /* Sets initial values of closed loop parameters */
            ModelParsCL.WfOutfp = Wf0;
            ModelParsCL.Ts2Sensed = Ts2;
            ModelParsCL.Pt3Sensed = Pt3;
            ModelParsCL.Tt4Sensed = Tt4;

            /* Sets flag indicating starting of model parameters to zero */
            ModelParsStart = 0;
        }

        /* Updates model inputs */
        ModelPars.Altitude = Altitude;
        ModelPars.MN = MN;
        ModelPars.FNpc = FNpc;
        ModelPars.gamma_air = GAMMA_AIR;
        ModelPars.Pt3 = Pt3;
        ModelPars.Tt4 = Tt4;
        ModelPars.Wf = Wf;
        ModelPars.RPM = RPM;
        ModelPars.POil = ContConst.POilModel;
        ModelPars.PFuel = ContConst.PFUelModel;
        ModelPars.Vibration = ContConst.VibModel;
        ModelPars.Ts = 0.001 * TICK;
        ModelPars.NumSteps = ContConst.NumSteps;
        ModelPars.MaxInter = ContConst.MaxInterFault;
        
        /* Updates fuel lack model inputs */
        BlowOutPars = ModelPars;
        /* Sets fuel value to 0 for simulating fuel lack situation */
        BlowOutPars.Wf = 0;
        
        /* Calculates model for normal functioning */
        ModelCalc(&ModelPars, &DeltaMtx, 
                 &AltLinVec, &MNLinVec, &ContConst,
                 &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH,
                 &DeltaMtx2D, &DeltaMtx2DH, &DeltaMtx1D, &DeltaMtx1DH,
                 &NcFANContMtx, &Tt4Mtx, &Pt3Mtx,
                 &AMtx, &BMtx, &Tt4DMtx, &Pt3DMtx,
                 &WfMtx, &Ts0Mtx,
                 &Pt5Mtx, &Pt5DMtx, &Tt5Mtx, &Tt5DMtx,
                 &NcHPCMapMtx, &WcHPCMapMtx, &PRHPCMapMtx,
                 &MapHPC1D, &MapHPC1DH, &MapHPC2D, &MapHPC2DH);
                
        /* Calculates model for fuel lack */
        ModelCalc(&BlowOutPars, &DeltaMtx, 
                 &AltLinVec, &MNLinVec, &ContConst,
                 &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH,
                 &DeltaMtx2D, &DeltaMtx2DH, &DeltaMtx1D, &DeltaMtx1DH,
                 &NcFANContMtx, &Tt4Mtx, &Pt3Mtx,
                 &AMtx, &BMtx, &Tt4DMtx, &Pt3DMtx,
                 &WfMtx, &Ts0Mtx,
                 &Pt5Mtx, &Pt5DMtx, &Tt5Mtx, &Tt5DMtx,
                 &NcHPCMapMtx, &WcHPCMapMtx, &PRHPCMapMtx,
                 &MapHPC1D, &MapHPC1DH, &MapHPC2D, &MapHPC2DH);  

        /* CLOSED-LOOP INTERNAL MODEL */

        /* Checks if fault analysis has started. If not, the closed-loop model must match exactly 
        the open-loop model and simulation controller must match the real one */
        if (EngStatus.EngineStatus <= 8 | StartFaultAnalysis == 0)
        {
            /* Sets input  simulation controller  and real controller parameters as equal, 
            and close-loop and opem-loop models as equal */
            ContStModCL = ContStart;
            ContInModCL = ContInput;
            ContOutModCL = ContOutput;
            ModelParsCL = ModelPars;
        }
        else
        {
            /* Updates Controller Inputs */
            // ContInModCL.Old_key_start = Old_key_start;
            // ContInModCL.Current_key_start = Current_key_start;
            // ContInModCL.bits_inverter = digital.bits.inverter;
            /* Externally defined parameters */
            ContInModCL.Mode = Mode;
            ContInModCL.LeverMode = LeverMode;
            ContInModCL.EngUnits = EngUnits;
            ContInModCL.Altitude = Altitude;
            ContInModCL.MN = MN;
            ContInModCL.FNpc = FNpc;   

            /* Parameters calculated by model */         
            ContInModCL.Tt2 = ModelParsCL.Tt2;
            ContInModCL.Pt3 = ModelParsCL.Pt3;
            ContInModCL.Tt4 = ModelParsCL.Tt4;
            ContInModCL.RPM = ModelParsCL.RPM;
            //ContInModCL.POil = POil;
            //ContInModCL.SkipStart = SkipStart;
            //ContInModCL.Wf0 = Wf0;
            //keysWord = keys.in;
            //digitalWord = digital.out;

			/* NOMINAL SHUT DWON REFERENCE */

            /* If nominal shut down has been requested, controller reference must be set to minimum */
            ShutDownRef(ShutDownCommand, &ContInModCL, &ContOutModCL, &ContConst, Ts);

            /* BOOSTER PHASE PROTECTION */

			/* If booster is connected, measured value of Pt3 must not be considered and blow out protection must be deactivated
			The same situation is reproduced in the model in order for more accureate reproduction of the real situation */
			BoosterProtect(&ContConst, &ContInModCL, Delta, BoosterLStatus, BoosterRStatus, Ts);
//mexPrintf("Model: BoostL=%d BoostR=%d Time=%f status=%d Delta=%f Pt3=%f\n",BoosterLStatus, BoosterRStatus, ContInModCL.TimerBoost, ContInModCL.statusBooster, Delta, ContInModCL.Pt3);
			/* CALCULATES THE CONTROL LAW */

            /* Calculates fuel flow from control law for closed-loop model */
            PIMinMaxRF(&AltLinVec, &MNLinVec, &NcVec, &ASVec, &DSVec,
                       &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH,
                       &DeltaMtx2D, &DeltaMtx2DH, &DeltaMtx1D, &DeltaMtx1DH,
                       &ContConst, &ContStModCL, &ContInModCL, &ContOutModCL, &digitalWord, &keysWord,
                       &DeltaMtx, &NcFANContMtx, &FNcMaxContMtx, &FNperContMtx,
                       &N_KpMtx, &N_KiMtx, Ts);

            /* EXECUTES NOMINAL SHUT DOWN RAMP */

            /* The same situation during shut down is reproduced in the closed-loop model
            for more accurate reproduction of the real situation */
            ShutDownRamp(&ContInModCL, &ContInputEmpty,
                         &ContOutModCL, &ContOutputEmpty,
                         &ContStModCL, &ContStartEmpty, 
                         &ContGenOilCL, &ContGenEmpty,
                         &digModCL, &ContConst, Ts);

			/* EXECUTES EMERGENCY SHUT DOWN ROUTINE IF EMERGENCY HAS OCCURRED */

            /* The same situation during emergency shut down is reproduced in the closed-loop model
            for more accurate reproduction of the real situation */
            EmergencyShutDown(&ContInModCL, &ContInputEmpty,
                              &ContOutModCL, &ContOutputEmpty,
                              &ContStModCL, &ContStartEmpty, 
                              &ContGenOilCL, &ContGenEmpty,
                              &digModCL, EmergShutDwn);
        }

        /* Updates closed-loop model inputs */
        ModelParsCL.Altitude = Altitude;
        ModelParsCL.MN = MN;
        ModelParsCL.FNpc = FNpc;
        ModelParsCL.gamma_air = GAMMA_AIR;
        // ModelParsCL.Pt3 = Pt3;
        // ModelParsCL.Tt4 = Tt4;
        ModelParsCL.Wf = ContOutModCL.Wf;
        // ModelParsCL.RPM = RPM;
        // ModelParsCL.POil = ContConst.POilModel;
        // ModelParsCL.PFuel = ContConst.PFUelModel;
        // ModelParsCL.Vibration = ContConst.VibModel;
        ModelParsCL.Ts = 0.001 * TICK;
        ModelParsCL.NumSteps = ContConst.NumSteps;
        ModelParsCL.MaxInter = ContConst.MaxInterFault;

        /* Performs closed-loop model calculation */
        ModelCalc(&ModelParsCL, &DeltaMtx, 
                 &AltLinVec, &MNLinVec, &ContConst,
                 &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH,
                 &DeltaMtx2D, &DeltaMtx2DH, &DeltaMtx1D, &DeltaMtx1DH,
                 &NcFANContMtx, &Tt4Mtx, &Pt3Mtx,
                 &AMtx, &BMtx, &Tt4DMtx, &Pt3DMtx,
                 &WfMtx, &Ts0Mtx,
                 &Pt5Mtx, &Pt5DMtx, &Tt5Mtx, &Tt5DMtx,
                 &NcHPCMapMtx, &WcHPCMapMtx, &PRHPCMapMtx,
                 &MapHPC1D, &MapHPC1DH, &MapHPC2D, &MapHPC2DH);

        /*===============================================================*/
        /* END OF SSModelLoop.c AND PIMMRF_TJ1200.c IDENTICAL CODE PIECE */
        /*                                                               */
        /* NOTE: The codes are to be identical except for the considera- */
        /*       tions mentioned at the note above                       */
        /*===============================================================*/

        /* -------------------------------------------------- */
        /* AUXILIARY VARIABLE - PWLM                          */
        /* (To be usedi in MATLAB and TMATS simulations only) */
        /* -------------------------------------------------- */
        
        // Out0 = fValue;
        Out0 = Wf;
        Out1 = ContOutput.Active;
        Out2 = digital.bits.igniter;
        Out3 = ContOutput.RPMRef;
        Out4 = ContOutput.MinRef;
        Out5 = (double)EngStatus.EngineStatus;
        Out6 = OPRPM;
        //Out5 = ContStart.status;//EngStatus.EngineStatus;
                
        /* -------------------------------------------------- */
//mexPrintf("StatusSD=%d\n",ContInput.StatusSD);
    }

    /* -------------------------------------------------- */
    /* UPDATES OUTPUTS - TMATS & PWLM                     */
    /* (To be usedi in MATLAB and TMATS simulations only) */
    /* -------------------------------------------------- */

	/* Writes SIMULINK outputs */

    Iout[0] = Out0;
	Iout[1] = Out1;
	Iout[2] = Out2;
	Iout[3] = Out3;
	Iout[4] = Out4;
    Iout[5] = Out5;
    Iout[6] = Out6;
    
    IoutModel[0] = ModelPars.RPM;
    IoutModel[1] = ModelPars.Tt4;
//mexPrintf("\n ModelPars.Tt4 = %f", ModelPars.Tt4);
    IoutModel[2] = ModelPars.Pt3;
    IoutModel[3] = ModelPars.WfOutfp;
    
    IoutBlowOut[0] = BlowOutPars.RPM;
    IoutBlowOut[1] = BlowOutPars.Tt4;
    IoutBlowOut[2] = BlowOutPars.Pt3;
    IoutBlowOut[3] = BlowOutPars.Tt2;

    IoutModelCL[0] = ModelParsCL.RPM;
    IoutModelCL[1] = ModelParsCL.Tt4;
//mexPrintf("\n ModelPars.Tt4 = %f", ModelPars.Tt4);
    IoutModelCL[2] = ModelParsCL.Fn;
    IoutModelCL[3] = ModelParsCL.Tt2;
    
    /*---------------------------------------------*/
// mexPrintf("ModelPOil = %f, CLModelPOil = %f\n",ModelPars.POil, ModelParsCL.POil);
// mexPrintf("ModelPFuel = %f, CLModelPFuel = %f\n",ModelPars.PFuel, ModelParsCL.PFuel);
// mexPrintf("ModelVib = %f, CLModelVib = %f\n",ModelPars.Vibration, ModelParsCL.Vibration);
// mexPrintf("ModelRPM = %f, CLModelRPM = %f\n",ModelPars.RPM, ModelParsCL.RPM);
// mexPrintf("Real Fuel = %f, CLModel Fuel = %f\n", Wf, ContOutModCL.Wf);
}

#define MDL_UPDATE  /* Change to #undef to remove function */
#if defined(MDL_UPDATE)
/* Function: mdlUpdate ======================================================
 * Abstract:
 *    This function is called once for every major integration time step.
 *    Discrete states are typically updated here, but this function is useful
 *    for performing any tasks that should only take place once per
 *    integration step.
 */
static void mdlUpdate(SimStruct *S, int_T tid)
{
}
#endif /* MDL_UPDATE */



#define MDL_DERIVATIVES  /* Change to #undef to remove function */
#if defined(MDL_DERIVATIVES)
/* Function: mdlDerivatives =================================================
 * Abstract:
 *    In this function, you compute the S-function block's derivatives.
 *    The derivatives are placed in the derivative vector, ssGetdX(S).
 */
static void mdlDerivatives(SimStruct *S)
{
}
#endif /* MDL_DERIVATIVES */



/* Function: mdlTerminate =====================================================
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
static void mdlTerminate(SimStruct *S)
{
}


/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif

 // #ifdef __cplusplus
 // } // end of extern "C" scope
 // #endif
