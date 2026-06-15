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

#define S_FUNCTION_NAME  SSModelLoop
#define S_FUNCTION_LEVEL 2

//#define pi 3.14


/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"

/*=================================================*/
/* INCLUDES CALLED BEFORE HIL INCLUDES STARTS HERE */
/*=================================================*/

#include <math.h>
#include <stdio.h>
#include <string.h>

/******** SAVETO START: HIL_INCLUDES *********/

 /*===========================================================*/
 /* INCLUDES REFERENT TO THE SOFTWARE IN THE LOOP STARTS HERE */
 /*===========================================================*/

/*-------------------*/
/* STANDARD INCLUDES */
/*-------------------*/

#include <inttypes.h>
#include <stdint.h>

/*----------------------------------------------*/
/* COMMON INCLUDES - USED BY BOTH FADEC AND HIL */
/*----------------------------------------------*/

#include "FADEC_Defines_H/constants_TMATS.h"        		/* Adapted from T-MATS */
#include "FADEC_Defines_H/Control_Types.h"          		/* Controller calculations */
#include "FADEC_Defines_H/DigitalOutDefs.h"         		/* Controller calculations */
#include "FADEC_Defines_H/Env_SampTime.h"           		/* General Calculations*/
#include "FADEC_Defines_H/FaultSim_Types.h"         		/* Fault analysis */
#include "FADEC_Defines_H/FloatPoint_Precision.h"			/* Defines the size of used floating point */
#include "FADEC_Defines_H/Interpolation_Types.h"    		/* General Calculations*/
#include "FADEC_Defines_H/IO_Types.h"               		/* Controller calculations */
#include "FADEC_Defines_H/Model_Types.h"            		/* Used for model calculations */
#include "FADEC_Functions_H/Ambient_TMATS.h"          		/* Adapted from T-MATS */
#include "FADEC_Functions_H/ControlFunctions.h"       		/* Controller calculations */
#include "FADEC_Functions_H/FailSafeFunctions.h"      		/* Fault analysis */
#include "FADEC_Functions_H/functions_TMATS.h"        		/* Adapted from T-MATS */
// #include "FADEC_Functions_H/LinMtxFunctions.h"        		/* General Calculations*/
#include "FADEC_Functions_H/MtxIntFunctions.h"        		/* General Calculations*/
#include "FADEC_Functions_H/PIMinMaxRF.h"             		/* Controller calculations */
#include "FADEC_Functions_H/ShutDownFunctions.h"      		/* Functions for engine shutting down */
#include "FADEC_Functions_H/StartingFunctions.h"      		/* Functions for engine start */
#include "FADEC_Functions_H/TCFault.h"                		/* Fault analysis */

/* TJ1200 INCLUDES */

#include "TJ1200/FADEC_Constants_H/ConstantsTJ1200.h"
#include "TJ1200/FADEC_get_H/getTJ1200FADEC.h"
#include "TJ1200/FADEC_get_H/getTJ1200FADECContConst.h"		/* Controller Constants */
#include "TJ1200/FADEC_get_H/getTJ1200FADECMtx.h"			/* FADEC matrices */
#include "TJ1200/FADEC_get_H/getTJ1200FADECSizeConst.h"		/* Matrices sizes */

/* TF1200 INCLUDES */

#include "TF1200/FADEC_Constants_H/ConstantsTF1200.h"
#include "TF1200/FADEC_get_H/getTF1200FADEC.h"
#include "TF1200/FADEC_get_H/getTF1200FADECContConst.h"		/* Controller Constants */
#include "TF1200/FADEC_get_H/getTF1200FADECMtx.h"			/* FADEC matrices */
#include "TF1200/FADEC_get_H/getTF1200FADECSizeConst.h"		/* Matrices sizes */

/* GEJ85 INCLUDES */

#include "GEJ85/FADEC_Constants_H/ConstantsGEJ85.h"
#include "GEJ85/FADEC_get_H/getGEJ85FADEC.h"
#include "GEJ85/FADEC_get_H/getGEJ85FADECContConst.h"		/* Controller Constants */
#include "GEJ85/FADEC_get_H/getGEJ85FADECMtx.h"				/* FADEC matrices */
#include "GEJ85/FADEC_get_H/getGEJ85FADECSizeConst.h"		/* Matrices sizes */

/* TJ700 INCLUDES */

#include "TJ700/FADEC_Constants_H/ConstantsTJ700.h"
#include "TJ700/FADEC_get_H/getTJ700FADEC.h"
#include "TJ700/FADEC_get_H/getTJ700FADECContConst.h"		/* Controller Constants */
#include "TJ700/FADEC_get_H/getTJ700FADECMtx.h"				/* FADEC matrices */
#include "TJ700/FADEC_get_H/getTJ700FADECSizeConst.h"		/* Matrices sizes */

/* TJ200 INCLUDES */

#include "TJ200/FADEC_Constants_H/ConstantsTJ200.h"
#include "TJ200/FADEC_get_H/getTJ200FADEC.h"
#include "TJ200/FADEC_get_H/getTJ200FADECContConst.h"		/* Controller Constants */
#include "TJ200/FADEC_get_H/getTJ200FADECMtx.h"				/* FADEC matrices */
#include "TJ200/FADEC_get_H/getTJ200FADECSizeConst.h"		/* FADEC matrices sizes */

/* TJ40 INCLUDES */

#include "TJ40/FADEC_Constants_H/ConstantsTJ40.h"
#include "TJ40/FADEC_get_H/getTJ40FADEC.h"
#include "TJ40/FADEC_get_H/getTJ40FADECContConst.h"		/* Controller Constants */
#include "TJ40/FADEC_get_H/getTJ40FADECMtx.h"				/* FADEC matrices */
#include "TJ40/FADEC_get_H/getTJ40FADECSizeConst.h"		/* FADEC matrices sizes */


/*----------------------------------*/
/* HIL INCLUDES - NOT USED BY FADEC */
/*----------------------------------*/
	
#include "HIL_Functions_H/BearingModel.h"					/* Bearing model functions */													
#include "HIL_Functions_H/EngineModel.h"					/* Funciton for engine model simulation */
#include "HIL_Functions_H/FaultSimFunctions.h"				/* Functions for fault simulations */
#include "HIL_Functions_H/InitCond.h"						/* Funciton for calculating simulation initial conditions */
#include "FADEC_Functions_H/PeripheralDyn.h"				/* Perypherals' dynamics functions */

/* TJ1200 INCLUDES */

#include "TJ1200/HIL_get_H/getTJ1200HIL.h"
#include "TJ1200/HIL_get_H/getTJ1200HILEngConst.h"			/* Engine constants */
#include "TJ1200/HIL_get_H/getTJ1200HILMtx.h"				/* HIL matrices*/
#include "TJ1200/HIL_get_H/getTJ1200HILSizeConst.h"			/* HIL matrices sizes */
#include "TJ1200/HIL_get_H/getTJ1200HILStartPars.h"

/* TF1200 INCLUDES */

#include "TF1200/HIL_get_H/getTF1200HIL.h"
#include "TF1200/HIL_get_H/getTF1200HILEngConst.h"			/* Engine constants */
#include "TF1200/HIL_get_H/getTF1200HILMtx.h"				/* HIL matrices*/
#include "TF1200/HIL_get_H/getTF1200HILSizeConst.h"			/* HIL matrices sizes */
#include "TF1200/HIL_get_H/getTF1200HILStartPars.h"

/* GEJ85 INCLUDES */

#include "GEJ85/HIL_get_H/getGEJ85HIL.h"
#include "GEJ85/HIL_get_H/getGEJ85HILEngConst.h"			/* Engine constants */
#include "GEJ85/HIL_get_H/getGEJ85HILMtx.h"					/* HIL matrices*/
#include "GEJ85/HIL_get_H/getGEJ85HILSizeConst.h"			/* HIL matrices sizes */
#include "GEJ85/HIL_get_H/getGEJ85HILStartPars.h"

/* TJ700 INCLUDES */

#include "TJ700/HIL_get_H/getTJ700HIL.h"
#include "TJ700/HIL_get_H/getTJ700HILEngConst.h"			/* Engine constants */
#include "TJ700/HIL_get_H/getTJ700HILMtx.h"					/* HIL matrices*/
#include "TJ700/HIL_get_H/getTJ700HILSizeConst.h"			/* HIL matrices sizes */
#include "TJ700/HIL_get_H/getTJ700HILStartPars.h"

/* TJ200 INCLUDES */

#include "TJ200/HIL_get_H/getTJ200HIL.h"
#include "TJ200/HIL_get_H/getTJ200HILEngConst.h"			/* Engine constants */
#include "TJ200/HIL_get_H/getTJ200HILMtx.h"					/* HIL matrices*/
#include "TJ200/HIL_get_H/getTJ200HILSizeConst.h"			/* HIL matrices sizes */
#include "TJ200/HIL_get_H/getTJ200HILStartPars.h"

/* TJ40 INCLUDES */

#include "TJ40/HIL_get_H/getTJ40HIL.h"
#include "TJ40/HIL_get_H/getTJ40HILEngConst.h"			/* Engine constants */
#include "TJ40/HIL_get_H/getTJ40HILMtx.h"					/* HIL matrices*/
#include "TJ40/HIL_get_H/getTJ40HILSizeConst.h"			/* HIL matrices sizes */
#include "TJ40/HIL_get_H/getTJ40HILStartPars.h"


/******** SAVETO END: HIL_INCLUDES *********/

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

	if (!ssSetNumInputPorts(S, 4)) return;

	ssSetInputPortWidth(S, 0, 23);				/* General inputs */
    ssSetInputPortWidth(S, 1, 1);				/* Sensor faults */
	ssSetInputPortWidth(S, 2, 1);				/* System faults */
	ssSetInputPortWidth(S, 3, 14);				/* Bias inputs */    
    
	ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/
    ssSetInputPortRequiredContiguous(S, 1, true); /*direct input signal access*/
    ssSetInputPortRequiredContiguous(S, 2, true); /*direct input signal access*/
	ssSetInputPortRequiredContiguous(S, 3, true); /*direct input signal access*/

	/*
	 * Set direct feedthrough flag (1=yes, 0=no).
	 * A port has direct feedthrough if the input is used in either
	 * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
	 */
	ssSetInputPortDirectFeedThrough(S, 0, 1);
	ssSetInputPortDirectFeedThrough(S, 1, 1);
	ssSetInputPortDirectFeedThrough(S, 2, 1);
	ssSetInputPortDirectFeedThrough(S, 3, 1);
	
	if (!ssSetNumOutputPorts(S, 7)) return;
	ssSetOutputPortWidth(S, 0, 34);
	ssSetOutputPortWidth(S, 1, 3);
    ssSetOutputPortWidth(S, 2, 14);
	ssSetOutputPortWidth(S, 3, 4);
	ssSetOutputPortWidth(S, 4, 4);
	ssSetOutputPortWidth(S, 5, 4);
	ssSetOutputPortWidth(S, 6, 4);

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

	/* ---------------------------------------- */
	/* DECLARATION OF MATLAB INPUT VARIABLES    */
	/* (To be usedi in MATLAB simulations only) */
	/* ---------------------------------------- */

	const real_T *InputVars = (const real_T*)ssGetInputPortSignal(S, 0);
	const real_T *InputSensFaults = (const real_T*)ssGetInputPortSignal(S, 1);
	const real_T *InputSysFaults = (const real_T*)ssGetInputPortSignal(S, 2);
    const real_T *InputBias = (const real_T*)ssGetInputPortSignal(S, 3);

	real_T       *Iout = ssGetOutputPortSignal(S, 0);
	real_T       *Init = ssGetOutputPortSignal(S, 1);
	real_T       *ISens = ssGetOutputPortSignal(S, 2);
	real_T       *IoutModel = ssGetOutputPortSignal(S, 3);
    real_T       *IoutBlowOut = ssGetOutputPortSignal(S, 4);
	real_T       *IoutSensModel = ssGetOutputPortSignal(S, 5);
	real_T       *IoutModelCL = ssGetOutputPortSignal(S, 6);

	/* -------------------------------------------------- */
    /* INCLUDE - T-MATS & PWLM                            */
    /* (To be usedi in MATLAB and TMATS simulations only) */
    /* -------------------------------------------------- */

	floating FuelIn;		
	int IgniterIn;	
	floating OPRPMIn;	
    
    /* -------------------------------------------------- */

/******** SAVETO START: HIL_VARS_1 ********/

	/*===================================================================================*/
	/* DECLARATION OF VARIABLES USED BY HIL SOFTWARE - MUST BE DONE BEFORE MAIN FUNCTION */
	/*===================================================================================*/

	/* --------------------------*/
	/* FADEC AND MODEL VARIABLES */
	/* --------------------------*/

	/* DECLARATION OF STRUCTURES */

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

    /* DECLARATION OF UNIONS */

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

/******** SAVETO END: HIL_VARS_1 ********/	

/******** SAVETO START: HIL_INIT_FAULTS ********/

	/*==========================*/
    /* REQUIRED INITIALIZATIONS */
	/*==========================*/
/******** COMMENT START ********/
    SoftSimFaults = FaultSensEmpty;						   /* Union - Thermocouple full scale simulation */

    /* Each union is initiated with null values */
    Ts2_0.TCFaultBits = 0;                              
    Ts2_1.TCFaultBits = 0;
    Tt4_0.TCFaultBits = 0;
    Tt4_1.TCFaultBits = 0;
    Tt4_2.TCFaultBits = 0;
    TB_0.TCFaultBits = 0;
    TB_1.TCFaultBits = 0;
    TB_2.TCFaultBits = 0;
/******** COMMENT END ********/
/******** SAVETO END: HIL_INIT_FAULTS ********/	

/******** SAVETO START: HIL_VARS_2 ********/

	/*===========*/
	/* VARIABLES */
    /*===========*/

/******** COMMENT START *********/
	/* PREVIOUSLY DELCARED IN HARDWARE */

	/*floating TYPE*/

    //floating reference = 0.35;                            /* Reference value used initially */    

	/*---------------------------------*/
/******** COMMENT END *********/

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

	/* floating TYPE */

    floating Altitude = 567;                              /* Altitude value */
    floating Delta = 1;                                       /* Delta = Pt2/PSTD - correction parameter */
    floating dT = 0;                                      /* Day temperature variation */
    floating FNcMax = 0;                                  /* Maximum allowed corrected net thrust */
    floating FNpc = 0;                                    /* Corrected net thrust */
    floating MemSize = 0;									/* Memory size occupied by matrices */
	floating MN = 0;                                      /* Flight Mach number value */
	floating OPRPMManual = 0;								/* Manual reference for oil pump rotation speed */
    floating POil = 0;                                    /* Oil pressure */
    floating Pt2 = 101325;                                /* Compressor inlet total pressure */
    floating Pt3 = 101325;                                /* Compressor exhaust total pressure */ 
    floating Pt3MedVal = 101325;                          /* Pt3 medium value */
    floating RefCAN = 0;                                  /* Reference from CAN */    
    floating RPM = 0;                                     /* Engine mechanical rotation speed */  
    floating RPMMedVal = 0;                               /* RPM medium value */
    floating TBear[5] = {0,0,0,0,0};                      /* String containing bearings temperatures */
    floating Ts2 = 288.15;                              	/* Compressor inlet static temperature */
    floating Ts2MedVal = 288.15;                          /* Ts2 medium value */
    floating Tt2 = 288.15;                                /* Compressor inlet total temperature */
    floating Tt4 = 288.15;                                /* Combustion chamber total temperature */
    floating Tt4MedVal = 288.15;                          /* Tt4 medium value */
    floating Tt5 = 288.15;                                /* Turbine inlet total temperature */
    floating WaitTime = 0;                                /* Used by general purpose timer */
    floating Wf0 = 0;                                     /* Initial fuel flow value */

    /* static floating TYPE */

	static floating OPRPM = 0;                            /* Oil pump rotation speed */
    static floating Wf = 0;                               /* Fuel flow */

	/*----------------------*/
	/* MODEL ONLY VARIABLES */
	/*----------------------*/

	/* STRUCTURES */

	static EngineOutput EngOutput = { 0 };				/* Struct - Contains engine outputs */
	static EngineOutput EngOutputEmpty = { 0 };			/* Struct - Contains engine outputs */

	static EnginePars EngPars = { 0 };					/* Struct - Contains engine parameters */
	static EnginePars EngParsEmpty = { 0 };				/* Struct - Contains engine parameters */

	static EngineStart Starting;						/* Struct - Contains engine starging parameters */
	static EngineStart StartingEmpty = { 0 };			/* Struct - Contains engine starging parameters */
	    
	static SensedPars SensorBias;						/* Struct - Sensors bias for foult simulation */	
 
	/* UNIONS */

	static EngineFaults Faults;							/* Union - Indicates engine faults to be simulated */

	static FaultDetect SysFaults;						/* Union - Indicates system faults to be simulated  */

	static SensorFaults SensFaults;						/* Union - Sensors faults for foult simulation */

	/* int TYPE */
    
    int Alt_Elem = 0;                                   	/* Number of altitude elements */
    int AS_Elem = 0;                                    	/* Number of acceleration schedule elements */  
    int ExtFPModel = 0;										/* Choses between external or internal fuel pump model */
	int FlightStart = 0;									/* Flag defining ground start or start during flight */
	int Fn_Elem = 0;                                   		/* Number of Fn elements */
    int HILMode = 0;                                    	/* Hardware in the Loop Mode */
    int i = 0;                                          	/* Loop index variable */
    int MN_Elem = 0;                                    	/* Number of Mach number elements */
    int NcFANMap_Elem = 0;                                  /* Number of Nc elements - fan map */
    int NcHPCMap_Elem = 0;                                  /* Number of Nc elements - high power compressor map */
    int NcHPTMap_Elem = 0;                                  /* Number of Nc elements - turbine map */
    int PowerMan_Elem = 0;                                  /* Number of total steady operating points used for Power Management Controller - all altitudes */
    int PRHPTMap_Elem = 0;                                  /* Number of pressure ratio elements - turbine map */
    int SteadyOp_Elem = 0;                                  /* Number of steady operating points used for linearization at Sea Level */
    int TsampDiv = 10;                                  	/* Possibility of lower sampling time for the model */
    int Wc_per_Nc_FAN = 0;                                  /* Number of pressure ratio elements - fan map */
    int Wc_per_Nc_HPC = 0;                                  /* Number of pressure ratio elements - high power compressor map */
    int WcFANMap_Elem = 0;                                  /* Number of Wc elements - fan map */
    int WcHPCMap_Elem = 0;                                  /* Number of Wc elements - high power compressor map */
    int WcHPTMap_Elem = 0;                                  /* Number of Wc elements - turbine map */
    int WhichEngine = 1;                                    /* Flag defining the engine to be simulated */  

	/* static int TYPE */

	static int bit_start = 0;								/* Starting flag */

	/* floating TYPE */
	
	floating BPFAN = 0;                                       /* Fan bypass ratio */
    floating Fg = 0;                                          /* Engine gross thrust */
    floating Fn = 0;                                          /* Engine net thrust */
    floating FNpc0 = 0;                                  		/* Initial percent net thrust reference */
    floating MN8 = 0;                                         /* Nozzle thruat gas Mach number */
    floating Mwm = 0.3;                                   	/* Mach number value for windmill simulation - currently used as 0.3 */
    floating NcFAN = 0;                                       /* Fan corrected rotation speed */
    floating NcHPC = 0;                                       /* Compressor corrected rotation speed */
    floating P0 = 101325;                                     /* Ambient pressure */
    floating PRFAN = 1;                                       /* Fan pressure ratio */
    floating PRHPC = 1;                                       /* Compressor pressure ratio */
    floating Pt21 = 101325;                                   /* Fan exhaust total pressure */
    floating Pt4 = 101325;                                    /* Burner exhaust total pressure */
    floating Pt5 = 101325;                                    /* Turbine exhaust total pressure */
    floating Pt6 = 101325;                                    /* Mixer exhaust total pressure */
    floating SMFAN = 25;                                      /* Fan stall margin */
    floating SMHPC = 25;                                      /* Compressor stall margin */
    floating TCOpen = ContConst.TCOpen;                   	/* Thermocouple value when open-circuited */
    floating TsamModel = 0.001 * TICK / TsampDiv;         	/* Model sampling time */
    floating Ts = 0.001 * TICK;                      			/* Sampling Time */  
    floating Tt21 = 288.15;                                   /* Fan exhaust total temperature */
    floating Tt3 = 288.15;                                    /* Compressor exhaust total temperature */
    floating Tt6 = 288.15;                                    /* Mixer exhaust total temperature */
    floating V8 = 0;                                          /* Nozzle throat gas speed */
    floating W2 = 0;                                          /* Compressor inlet air flow */
    floating W21 = 0;                                         /* Fan exhaust air flow */
    floating W8 = 0;                                          /* Nozzle exhaust gas mass flow */
    floating WcFAN = 0;                                       /* Fan inlet corrected air flow */
    floating WcHPC = 0;                                       /* Compressor inlet corrected air mass flow */
    floating WfMax_Pump = 0;                                  /* Maximum pump fuel flow value */

	/* static floating TYPE */

	static floating fValue = 0;							/* Fuel flow value */

	/* floating (*) TYPE  */

    floating *AltLinVec;                                  /* Controller and Model - Altitude break points  */
    floating *AMtx;                                       /* Model - pointer for A matrix */
    floating *AshMtx;                                     /* Model - pointer for hot sub idle Ash matrix */
    floating *ASVec;                                      /* Controller - Asceleration schedule (ASVec) break points */
    floating *AwmMtx;                                     /* Model - pointer for windmill Awm matrix */
    floating *BMtx;                                       /* Model - pointer for B matrix */
    floating *BshMtx;                                     /* Model - pointer for hot sub idle Bsh matrix */
    floating *BwmMtx;                                     /* Model - pointer for wind mill Bwm matrix */
    floating *DeltaMtx;                                   /* Controller and Model - Delta break points  */
    floating *DeltaMtx1D;                                 /* Auxiliar matrix - Delta */
    floating *DeltaMtx1DH;                                /* Auxiliar matrix - Delta */
    floating *DeltaMtx2D;                                 /* Auxiliar matrix - Delta */
    floating *DeltaMtx2DH;                                /* Auxiliar matrix - Delta */
    floating *DSVec;                                      /* Controller - Deceleration schedule (DSVec) break points */
    floating *EffFANMapMtx;                               /* Model - pointer for Efficiency values matrix - fan map */
    floating *EffHPCMapMtx;                               /* Model - pointer for Efficiency values matrix - HPC map */
    floating *EffHPTMapMtx;                               /* Model - pointer for Efficiency values matrix - HPT map */
    floating *FNcMaxContMtx;                              /* Controller - pointer for maximum net thrust breakpoint values */
    floating *FNperContMtx;                               /* Controller - pointer for net thrust percent breakpoint values */
    floating *MapFAN1D;                                   /* Auxiliar matrix - fan map */
    floating *MapFAN1DH;                                  /* Auxiliar matrix - fan map */
    floating *MapFAN2D;                                   /* Auxiliar matrix - fan map */
    floating *MapFAN2DH;                                  /* Auxiliar matrix - fan map */
    floating *MapHPC1D;                                   /* Auxiliar matrix - HPC map */
    floating *MapHPC1DH;                                  /* Auxiliar matrix - HPC map */
    floating *MapHPC2D;                                   /* Auxiliar matrix - HPC map */
    floating *MapHPC2DH;                                  /* Auxiliar matrix - HPC map */
    floating *MNLinVec;                                   /* Controller and Model - Mach number break points */
    floating *Mtx1D;                                      /* Auxiliar matrix */
    floating *Mtx1DH;                                     /* Auxiliar matrix */
    floating *Mtx2D;                                      /* Auxiliar matrix */
    floating *Mtx2DH;                                     /* Auxiliar matrix */
	floating *N_KiMtx;                                    /* Controller - pointer for Ki matrix of N control law */
    floating *N_KishMtx;									/* Controller - pointer for Ki matrix of N control law - sub-idle */
	floating *N_KpMtx;                                    /* Controller - pointer for Kp matrix of N control law */
    floating *N_KpshMtx;									/* Controller - pointer for Kp matrix of N control law - sub-idle */
	floating *NcFANContMtx;                               /* Controller - pointer for fan Nc breakpoint values */
    floating *NcFANMapMtx;                                /* Model - pointer for Nc values matrix - fan map */
    floating *NcFANshContMtx;								/* Controller - pointer for fan Nc breakpoints values - sub-idle */
	floating *NcFANshMtx;									/* Model - pointer for Ncvalues matrix for sub-idle model */
	floating *NcHPCMapMtx;                                /* Model - pointer for Nc values matrix - HPC map */
    floating *NcHPTMapMtx;                                /* Model - pointer for Nc values matrix - HPT map */
    floating *NcMtx;                                      /* Model - pointer for Nc matrix */
    floating *NcVec;                                      /* Controller - Nc schedule (for ASVec and DSVec) break points  */
    floating *PRFANMapMtx;                                /* Model - pointer for PR values matrix - fan map */
    floating *PRFANStallMtx;                              /* Model - pointer for PR stall values matrix - fan map */
    floating *PRHPCMapMtx;                                /* Model - pointer for PR values matrix - HPC map */
    floating *PRHPCStallMtx;                              /* Model - pointer for PR stall values matrix - HPC map */
    floating *PRHPTMapMtx;                                /* Model - pointer for PR values matrix - HPT map */
    floating *Pt21DMtx;                                   /* Model - pointer for Pt21D matrix */
    floating *Pt21DshMtx;
	floating *Pt21DwmMtx;
    floating *Pt21Mtx;                                    /* Model - pointer for Pt21 matrix */
    floating *Pt21shMtx;
	floating *Pt21wmMtx;
	floating *Pt3DMtx;                                    /* Model - pointer for Pt3D matrix */
    floating *Pt3DshMtx;									/* Model - pointer for Pt3Dsh matrix */
	floating *Pt3DwmMtx;
	floating *Pt3Mtx;                                     /* Model - pointer for Pt3 matrix */
	floating *Pt3shMtx;									/* Model - pointer for Pt3sh matrix */
	floating *Pt3wmMtx;
	floating *Pt5DMtx;                                    /* Model - pointer for Pt5D matrix */
    floating *Pt5DshMtx;
	floating *Pt5DwmMtx;
	floating *Pt5Mtx;                                     /* Model - pointer for Pt5 matrix */
    floating *Pt5shMtx;
	floating *Pt5wmMtx;
	floating *Pt6DMtx;									/* Model - pointer for Pt6D matrix */
	floating *Pt6DshMtx;                                  /* Model - pointer for Pt6Dsh matrix */
    floating *Pt6DwmMtx;
	floating *Pt6Mtx;                                     /* Model - pointer for Pt6 matrix */
    floating *Pt6shMtx;
	floating *Pt6wmMtx;
	floating *RPMshMtx;                                   /* Model - pointer for hot sub idle RPMsh matrix */
    floating *RPMwmMtx;                                   /* Model - pointer for windmill RPMwm matrix */
    floating *Ts0Mtx;                                     /* Controller and Model - pointer Ts0 break points  */
    floating *Ts0Mtx1D;                                   /* Auxiliar matrix - Ts0 */
    floating *Ts0Mtx1DH;                                  /* Auxiliar matrix - Ts0 */
    floating *Ts0Mtx2D;                                   /* Auxiliar matrix - Ts0 */
    floating *Ts0Mtx2DH;                                  /* Auxiliar matrix - Ts0 */
    floating *Tt21DMtx;                                   /* Model - pointer for Tt21D matrix */  
    floating *Tt21DshMtx;
	floating *Tt21DwmMtx;
	floating *Tt21Mtx;                                    /* Model - pointer for Nc matrix */
    floating *Tt21shMtx;
	floating *Tt21wmMtx;
	floating *Tt3DMtx;                                    /* Model - pointer for Tt3D matrix */
    floating *Tt3DshMtx;
	floating *Tt3DwmMtx;
	floating *Tt3Mtx;                                     /* Model - pointer for Tt3 matrix */
    floating *Tt3shMtx;
	floating *Tt3wmMtx;
	floating *Tt4CshMtx;                                  /* Model - pointer for hot sub idle Tt4Csh matrix */
    floating *Tt4DMtx;                                    /* Model - pointer for Tt4D matrix */
	floating *Tt4DshMtx;                                  /* Model - pointer for hot sub idle Tt4Dsh matrix */
	floating *Tt4DwmMtx;
    floating *Tt4Mtx;                                     /* Model - pointer for Tt4 matrix */
    floating *Tt4shMtx;                                   /* Model - pointer for hot sub idle Tt4sh matrix */
    floating *Tt4wmMtx;
	floating *Tt5DMtx;                                    /* Model - pointer for Tt5D matrix */
    floating *Tt5DshMtx;
	floating *Tt5DwmMtx;
	floating *Tt5Mtx;                                     /* Model - pointer for Tt5 matrix */
    floating *Tt5shMtx;
	floating *Tt5wmMtx;
	floating *Tt6DMtx;                                    /* Model - pointer for Tt6D matrix */
    floating *Tt6DshMtx;
	floating *Tt6DwmMtx;
	floating *Tt6Mtx;                                     /* Model - pointer for Tt6 matrix */
    floating *Tt6shMtx;
	floating *Tt6wmMtx;
	floating *WcFANMapMtx;                                /* Model - pointer for Wc values matrix - fan map */
    floating *WcFANStallMtx;                              /* Model - pointer for Nc stall values matrix - fan map */
    floating *WcHPCMapMtx;                                /* Model - pointer for Wc values matrix - HPC map */
    floating *WcHPCStallMtx;                              /* Model - pointer for Wc stall values matrix - HPC map */
    floating *WcHPTMapMtx;                                /* Model - pointer for Wc values matrix - HPT map */
    floating *WfMtx;                                      /* Model - pointer for Wf matrix */
    floating *WfshMtx;                                    /* Model - pointer for hot sub idle Wfsh matrix */
	floating *WfwmMtx;									/* Model - pointer for windmill Wfwm matrix */

	/*---------------------------------------------------------------------------------------*/
	/* BEARING MODEL VARIABLES - MUST BE INCORPORATED AT CONSTANTS ONCE VALIDATED */
	/*---------------------------------------------------------------------------------------*/

	/* NOTE: Currently, the three bearigs are common to all engines simulated by the software.
	In a near future, when the current model or a final model is validated to be used as a 
	mathematical description of a bearing, the model parameters must be treated by the functions
	getXXXMtx and getXXXContConst */

	// /* Engine RPM vector */
    // floating RPMEVec[3] = {0, 20000, 23000};				/* Engine rotation speed breakpoints (RPME) */

    // /* Bearing 0 data */
    // floating DelT_Bear0[3] = {1, 100, 130};				/* Temperature decrease if maximum oil flow is used at given RPME */
    // floating TNOil_Bear0[3] = {300, 450, 573};			/* Temperature reached if no oil is used at the given RPME */

    // /* Bearing 1 data */
    // floating DelT_Bear1[3] = {1, 40, 120};				/* Temperature decrease if maximum oil flow is used at given RPME */
    // floating TNOil_Bear1[3] = {300, 400, 530};			/* Temperature reached if no oil is used at the given RPME */

    // /* Bearing 2 Data */
    // floating DelT_Bear2[3] = {1, 50, 110};				/* Temperature decrease if maximum oil flow is used at given RPME */
    // floating TNOil_Bear2[3] = {300, 410, 540};			/* Temperature reached if no oil is used at the given RPME */

	/* Engine RPM vector */
    floating RPMEVec[3] = {0, 20000, 23000};//{0.00, 20000.00, 23000.00};				/* Engine rotation speed breakpoints (RPME) */
	/* Bearing 0 data */
    floating DelT_Bear0[3] = {1.00, 50.00, 20.00};				/* Temperature decrease if maximum oil flow is used at given RPME */
    floating TNOil_Bear0[3] = {300.00, 415.00, 450.00};			/* Temperature reached if no oil is used at the given RPME */

    /* Bearing 1 data */
    floating DelT_Bear1[3] = {1.00, 40.00, 70.00};				/* Temperature decrease if maximum oil flow is used at given RPME */
    floating TNOil_Bear1[3] = {300.00, 400.00, 480.00};			/* Temperature reached if no oil is used at the given RPME */

    /* Bearing 2 Data */
    floating DelT_Bear2[3] = {1.00, 50.00, 51.00};				/* Temperature decrease if maximum oil flow is used at given RPME */
    floating TNOil_Bear2[3] = {300.00, 410.00, 480.00};			/* Temperature reached if no oil is used at the given RPME */

	static BearingPars Bear0;
    static BearingPars Bear1;
    static BearingPars Bear2;
    static BearingPars BearEmpty = {0};

/******** SAVETO END: HIL_VARS_2 ********/

/******** SAVETO START: SINGLESTOP_RESET ********/  

	/* ============================================================================================================= */
	/* THE FOLLOWIN CODE MUST BE EXECUTED DIRECTLY IN THE MAIN MAIN FUNCTION RIGHT BEFORE THE INFINITE LOOP while(1) */
	/* ============================================================================================================= */

	/*-------------*/
	/* SINGLE STOP */
	/*-------------*/

	if (SingleStop == 0)
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

		/*------------*/
		/* MODEL ONLY */
		/*------------*/

		/* STRUCTS INITIALIZATION */

		Bear0 = BearEmpty;
		Bear1 = BearEmpty;
		Bear2 = BearEmpty;
        EngPars = EngParsEmpty;	
        SensorBias = SensorsEmpty; 
        Starting = StartingEmpty;	

		/* UNIONS INITIALIZATION */

        Faults = FaultEmpty;	
        SensFaults = FaultSensEmpty;	
        SysFaults = FaultDetectEmpty;	

	}

	/*----------------*/
	/* RESET FUNCTION */
	/*----------------*/

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

		/* RESETS floating TYPE */

		OPRPMManual = 0;

        /* RESETS static floating TYPE */

        Wf = 0;	

		/*------------*/
		/* MODEL ONLY */
		/*------------*/	

		/* RESETS STRUCTS */

        Bear0 = BearEmpty;	
        Bear1 = BearEmpty;	
        Bear2 = BearEmpty;	
        EngOutput = EngOutputEmpty;	
        EngPars = EngParsEmpty;	
        SensorBias = SensorsEmpty;	
        Starting = StartingEmpty;

		/* RESETS UNIONS */	

        Faults = FaultEmpty;	
        SensFaults = FaultSensEmpty;	
        SysFaults = FaultDetectEmpty;	

		/* RESETS int TYPE */

		digitalWord = 0;
		Ignition = 0;
		keysWord = 0;

		/* RESETS static int TYPE */

		bit_start = 0;		
		Current_key_start = 0;
		OnOffCom= 0xFF;
		SkipStart = 0;

		/* RESETS floating TYPE*/
		
        Altitude = 0;
        BPFAN = 0;  
        dT = 0;
        Fg = 0;
        Fn = 0;
        FNpc = 0;
        FNpc0 = 0;
        MN = 0;
        NcFAN = 0;
        NcHPC = 0;
        P0 = 101325;
        POil = 0;
        PRFAN = 0;
        PRHPC = 0;
        Pt2 = 101325;
        Pt21 = 0;
        Pt3 = 0;
        Pt4 = 0;
        Pt5 = 0;
        Pt6 = 0;
        RefCAN = 0;
        //reference = 0;
        RPM = 0;
        SMFAN = 0;
        SMHPC = 0;  
        Tt2 = 288.25;
        Tt21 = 0;
        Tt3 = 0;
        Tt4 = 0;
        Tt5 = 0;
        Tt6 = 0;
        V8 = 0;
        W2 = 0; 
        W21 = 0;
        W8 = 0;
        WcFAN = 0;
        WcHPC = 0;
        Wf0 = 0;

		/* RESETS static floating TYPE */

		fValue = 0;

/******** COMMENT START ********/
		/* -------------------------------------------------- */
        /* T-MATS & PWLM  RESETS                          */
        /* (To be usedi in MATLAB and TMATS simulations only) */
        /* -------------------------------------------------- */
        
		/* int TYPE */

		IgniterIn = 0;

		/* floating TYPE */

		FuelIn = 0;

        
        /* -------------------------------------------------- */    
/******** COMMENT END ********/

	}

/******** SAVETO END: SINGLESTOP_RESET ********/

	/*-------------------------------------------------------------------------------------------------------------*/
	/*  INPUT READING BEFORE MAIN LOOP - Make sure to use the appropriate piece of code: MATLAB or actual hardware */
	/*-------------------------------------------------------------------------------------------------------------*/

	/* HARDWARE */

	/* -------------------------------------------------- */
    /* IMPUT READING - PWLM                               */
    /* (To be usedi in MATLAB (PWLM) simulations only)    */
    /* -------------------------------------------------- */


	/*Reads input for calculating initial conditions*/
	Altitude = InputVars[0];							/* Reads altitude value */
	MN = InputVars[1];									/* Reads Mach number value */
	dT = InputVars[2];									/* Reads day temperature variation */
	FuelIn = InputVars[3];
	IgniterIn = InputVars[4];							/* Reads igniter input */
	//reference = InputVars[5];							/* Reads reference value */														
	RefCAN = InputVars[5];								/* Reads reference value */														
	ResetButton[0] = InputVars[6];						/* Reads reset button input */
	Mode = InputVars[7];								/* Reads mode key */			
	LeverMode = InputVars[8];							/* Reads lever mode */
	HILMode = InputVars[9];								/* Reads HIL mode */
	WhichEngine = InputVars[10];						/* Reads which engine is to be simulated */
    EngUnits = InputVars[11];							/* Reads option for thrust command in N (SI units) */
    Mwm = InputVars[12];								/* Reads Mach number values for windmill simulation */
	OnOffCom = InputVars[13];							/* Reads external command treatment */
	OPRPMIn = InputVars[14];							/* Reads oil pump rpm input */

	/* Temperatures from external bearings models */
	TBear[0] = InputVars[15];
	TBear[1] = InputVars[16];
	TBear[2] = InputVars[17];

	/* External manual oil pump rotation speed reference */
	OPRPMManual = InputVars[18];

	/* Boosters status */
	BoosterLStatus = InputVars[19];
	BoosterRStatus = InputVars[20];

	/* Choice of pump model */
	ExtFPModel = InputVars[21]; 						/* Reads fuel pump model choice */

	/* Engine starting - flight or ground */
	FlightStart = InputVars[22];
    
    /* Reads fault bits */
	SensFaults.FaultBits = (uint64_t)InputSensFaults[0];
	SysFaults.FaultBits = (uint64_t)InputSysFaults[0];

	/* Reads CAN fault bits */
	CANFault.FaultBits = (uint64_t)InputSysFaults[0];
// mexPrintf("CAN0Fault=%" PRIu64 " ",CANFault.DetFaults.CAN_0_Fault);
// mexPrintf("CAN1Fault=%" PRIu64 "\n",CANFault.DetFaults.CAN_1_Fault);
	/* Reads sensor bias */
	SensorBias.Ts2[0] = InputBias[0];
	SensorBias.Ts2[1] = InputBias[1];	
	SensorBias.Pt3[0] = InputBias[2];	
	SensorBias.Tt4[0] = InputBias[3];	
	SensorBias.Tt4[1] = InputBias[4];
	SensorBias.Tt4[2] = InputBias[5];
	SensorBias.RPM[0] = InputBias[6];
	SensorBias.RPM[1] = InputBias[7];
	SensorBias.POil[0] = InputBias[8];
	SensorBias.PFuel[0] = InputBias[9];    
	SensorBias.Vibration[0] = InputBias[10]; 
	SensorBias.TBear[0] = InputBias[11];
	SensorBias.TBear[1] = InputBias[12];
	SensorBias.TBear[2] = InputBias[13];

    /* -------------------------------------------------- */

	/* -------------------------------------------------- */
    /* RESET VERIFICATION - PWLM                          */
    /* (To be usedi in MATLAB (PWLM) simulations only)    */
    /* -------------------------------------------------- */

	Reset = Edge(ResetButton);
	ResetButton[1] = ResetButton[0];

    /* -------------------------------------------------- */

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
        
/******** SAVETO START: MATRICES_AND_CONSTANTS ********/

	/*-----------------------------------------------------------*/
	/* DEFINES MATRICES AND CONSTANTS DEPENDING ON CHOSEN ENGINE */
	/*-----------------------------------------------------------*/

	/* ENGINES TO BE SIMULATED */
	/*	WhichEngine == 1 -> TJ1200
		WhichEngine == 2 -> TF1200			   
		WhichEngine == 3 -> GEJ85
		WhichEngine == 4 -> TJ700
		WhichEngine == 5 -> TJ200
		WhichEngine == 6 -> TJ40
									*/
	if (WhichEngine == 1)
	{

		/* Loads the constants of chosen engine used by FADEC */
		getTJ1200FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
							   &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);
		
		/* Loads the constants of chosen engine used by HIL */
		getTJ1200HILSizeConst(&NcFANMap_Elem, &WcFANMap_Elem, &Wc_per_Nc_FAN, &NcHPTMap_Elem, &PRHPTMap_Elem,
							 &WcHPTMap_Elem);

		/* Loads the constants of chosen engine */
		getTJ1200HILEngConst(&EngPars, &WfMax_Pump);

		/*Loads the controller starting parameters*/
		getTJ1200HILStartPars(&ContStart);
	}

	if (WhichEngine == 2)
	{

		/* Loads the constants of chosen engine used by FADEC */
		getTF1200FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
							   &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);
		
		/* Loads the constants of chosen engine used by HIL */
		getTF1200HILSizeConst(&NcFANMap_Elem, &WcFANMap_Elem, &Wc_per_Nc_FAN, &NcHPTMap_Elem, &PRHPTMap_Elem,
							 &WcHPTMap_Elem);

		/* Loads the constants of chosen engine */
		getTF1200HILEngConst(&EngPars, &WfMax_Pump);

		/*Loads the controller starting parameters*/
		getTF1200HILStartPars(&ContStart);
	}

	if (WhichEngine == 3)
	{

		/* Loads the constants of chosen engine used by FADEC */
		getGEJ85FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
							   &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);
		
		/* Loads the constants of chosen engine used by HIL */
		getGEJ85HILSizeConst(&NcFANMap_Elem, &WcFANMap_Elem, &Wc_per_Nc_FAN, &NcHPTMap_Elem, &PRHPTMap_Elem,
							 &WcHPTMap_Elem);

		/* Loads the constants of chosen engine */
		getGEJ85HILEngConst(&EngPars, &WfMax_Pump);

		/*Loads the controller starting parameters*/
		getGEJ85HILStartPars(&ContStart);
	}

	if (WhichEngine == 4)
	{

		/* Loads the constants of chosen engine used by FADEC */
		getTJ700FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
							   &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);
		
		/* Loads the constants of chosen engine used by HIL */
		getTJ700HILSizeConst(&NcFANMap_Elem, &WcFANMap_Elem, &Wc_per_Nc_FAN, &NcHPTMap_Elem, &PRHPTMap_Elem,
							 &WcHPTMap_Elem);

		/* Loads the constants of chosen engine */
		getTJ700HILEngConst(&EngPars, &WfMax_Pump);

		/*Loads the controller starting parameters*/
		getTJ700HILStartPars(&ContStart);
	}

	if (WhichEngine == 5)
	{

		/* Loads the constants of chosen engine used by FADEC */
		getTJ200FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
							   &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);
		
		/* Loads the constants of chosen engine used by HIL */
		getTJ200HILSizeConst(&NcFANMap_Elem, &WcFANMap_Elem, &Wc_per_Nc_FAN, &NcHPTMap_Elem, &PRHPTMap_Elem,
							 &WcHPTMap_Elem);

		/* Loads the constants of chosen engine */
		getTJ200HILEngConst(&EngPars, &WfMax_Pump);

		/*Loads the controller starting parameters*/
		getTJ200HILStartPars(&ContStart);
	}

	if (WhichEngine == 6)
	{

		/* Loads the constants of chosen engine used by FADEC */
		getTJ40FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
							   &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);
		
		/* Loads the constants of chosen engine used by HIL */
		getTJ40HILSizeConst(&NcFANMap_Elem, &WcFANMap_Elem, &Wc_per_Nc_FAN, &NcHPTMap_Elem, &PRHPTMap_Elem,
							 &WcHPTMap_Elem);

		/* Loads the constants of chosen engine */
		getTJ40HILEngConst(&EngPars, &WfMax_Pump);

		/*Loads the controller starting parameters*/
		getTJ40HILStartPars(&ContStart);
	}

	/* Loads number of elements of engine matrices into struct to be used by EngineModel */
	EngPars.Alt_Elem = Alt_Elem;
	EngPars.MN_Elem = MN_Elem;
	EngPars.Fn_Elem = Fn_Elem;
	EngPars.NcFANMap_Elem = NcFANMap_Elem;
	EngPars.NcHPCMap_Elem = NcHPCMap_Elem;
	EngPars.NcHPTMap_Elem = NcHPTMap_Elem;
	EngPars.PowerMan_Elem = PowerMan_Elem;
	EngPars.PRHPTMap_Elem = PRHPTMap_Elem;
	EngPars.SteadyOp_Elem = SteadyOp_Elem;
	EngPars.WcFANMap_Elem = WcFANMap_Elem;
	EngPars.WcHPCMap_Elem = WcHPCMap_Elem;
	EngPars.WcHPTMap_Elem = WcHPTMap_Elem;

	/*----------------------------------------*/
	/* ALLOCATES MEMORY FOR ENGINE SIMULATION */
	/*----------------------------------------*/

	/* Veryfies if reset has not been requested and it is the first software run so malloc is not used more than once in a row */
	if (Reset == 0) 
	{

		/* Matrices used for reference and gain calculations */
		N_KiMtx = 		 FADECMalloc(PowerMan_Elem, &MemSize);
		N_KishMtx = 	 FADECMalloc(PowerMan_Elem, &MemSize);
		N_KpMtx = 		 FADECMalloc(PowerMan_Elem, &MemSize);
		N_KpshMtx =      FADECMalloc(PowerMan_Elem, &MemSize);		
		NcFANContMtx =   FADECMalloc(PowerMan_Elem, &MemSize);
		NcFANshContMtx = FADECMalloc(PowerMan_Elem, &MemSize);
		FNperContMtx =   FADECMalloc(PowerMan_Elem, &MemSize);
        FNcMaxContMtx =  FADECMalloc(MN_Elem, &MemSize);

		/* Matrices used for model calculations */
		NcMtx =          FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21Mtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21Mtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		WfMtx =          FADECMalloc(SteadyOp_Elem, &MemSize);
		AMtx =           FADECMalloc(SteadyOp_Elem, &MemSize);
		BMtx = 	         FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21DMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21DMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
        
    	/* Matrices used for sub-idle calculations */
        AwmMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		AshMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
        BwmMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		BshMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
        RPMshMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		RPMwmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		NcFANshMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21shMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21wmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21DshMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21DwmMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21shMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21wmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21DshMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21DwmMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4CshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
    	Tt5shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
	    WfshMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);		
		WfwmMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);

		/* Low Pressure Compressor or Fan */
		NcFANMapMtx =    FADECMalloc(NcFANMap_Elem, &MemSize);
		WcFANStallMtx =  FADECMalloc(NcFANMap_Elem, &MemSize);
		PRFANStallMtx =  FADECMalloc(NcFANMap_Elem, &MemSize);
		WcFANMapMtx =    FADECMalloc(WcFANMap_Elem, &MemSize);
		PRFANMapMtx =    FADECMalloc(WcFANMap_Elem, &MemSize);
		EffFANMapMtx =   FADECMalloc(WcFANMap_Elem, &MemSize);

		/* High Pressure Compressor */
		NcHPCMapMtx =    FADECMalloc(NcHPCMap_Elem, &MemSize);
		WcHPCStallMtx =  FADECMalloc(NcHPCMap_Elem, &MemSize);
		PRHPCStallMtx =  FADECMalloc(NcHPCMap_Elem, &MemSize);
		WcHPCMapMtx =    FADECMalloc(WcHPCMap_Elem, &MemSize);
		PRHPCMapMtx =    FADECMalloc(WcHPCMap_Elem, &MemSize);
		EffHPCMapMtx =   FADECMalloc(WcHPCMap_Elem, &MemSize);

		/* Turbine */
		NcHPTMapMtx =    FADECMalloc(NcHPTMap_Elem, &MemSize);
		WcHPTMapMtx =    FADECMalloc(WcHPTMap_Elem, &MemSize);
		EffHPTMapMtx =   FADECMalloc(WcHPTMap_Elem, &MemSize);
		PRHPTMapMtx =    FADECMalloc(PRHPTMap_Elem, &MemSize);

		/* Auxiliar matrices */
		Mtx2D = 		 FADECMalloc(MN_Elem * Fn_Elem, &MemSize);
		Mtx2DH = 		 FADECMalloc(MN_Elem * Fn_Elem, &MemSize);
		Mtx1D = 		 FADECMalloc(Fn_Elem, &MemSize);
		Mtx1DH = 		 FADECMalloc(Fn_Elem, &MemSize);
        
        DeltaMtx2D =     FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
		DeltaMtx2DH =    FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
		DeltaMtx1D =     FADECMalloc(MN_Elem, &MemSize);
		DeltaMtx1DH =    FADECMalloc(MN_Elem, &MemSize);
 
		Ts0Mtx2D =       FADECMalloc(Fn_Elem, &MemSize);
		Ts0Mtx2DH = 	 FADECMalloc(Fn_Elem, &MemSize);
		Ts0Mtx1D = 		 FADECMalloc(Alt_Elem, &MemSize);
		Ts0Mtx1DH = 	 FADECMalloc(Alt_Elem, &MemSize);
 
		MapFAN2D = 		 FADECMalloc(WcFANMap_Elem, &MemSize);
		MapFAN2DH = 	 FADECMalloc(WcFANMap_Elem, &MemSize);
		MapFAN1D = 		 FADECMalloc(Wc_per_Nc_FAN, &MemSize);
		MapFAN1DH = 	 FADECMalloc(Wc_per_Nc_FAN, &MemSize);
 
		MapHPC2D = 		 FADECMalloc(WcHPCMap_Elem, &MemSize);
		MapHPC2DH = 	 FADECMalloc(WcHPCMap_Elem, &MemSize);
		MapHPC1D = 		 FADECMalloc(Wc_per_Nc_HPC, &MemSize);
		MapHPC1DH = 	 FADECMalloc(Wc_per_Nc_HPC, &MemSize);

		/* MN linerizing vector */
		MNLinVec = 		 FADECMalloc(MN_Elem, &MemSize);
        AltLinVec = 	 FADECMalloc(Alt_Elem, &MemSize);
        DeltaMtx = 		 FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
		Ts0Mtx = 		 FADECMalloc(Alt_Elem * MN_Elem, &MemSize);

		/* Reference filter vectors */
		ASVec = 		 FADECMalloc(AS_Elem, &MemSize);
		DSVec = 		 FADECMalloc(AS_Elem, &MemSize);
		NcVec = 		 FADECMalloc(AS_Elem, &MemSize);
		
	}
	else
	{
		/* HARDWARE */
/******** UNCOMMENT START ********/
		// /* Matrices used for reference and gain calculations */
		// N_KiMtx = 	     FADECRealloc(N_KiMtx, PowerMan_Elem);
		// N_KishMtx = 	 FADECRealloc(N_KishMtx, PowerMan_Elem);
		// N_KpMtx = 	     FADECRealloc(N_KpMtx, PowerMan_Elem);
		// N_KpshMtx =      FADECRealloc(N_KpshMtx, PowerMan_Elem);
		// NcFANContMtx =   FADECRealloc(NcFANContMtx, PowerMan_Elem);
		// NcFANshContMtx = FADECRealloc(NcFANshContMtx, PowerMan_Elem);
		// FNperContMtx =   FADECRealloc(FNperContMtx, PowerMan_Elem);
		// FNcMaxContMtx =  FADECRealloc(FNcMaxContMtx, MN_Elem);

		// /* Matrices used for model calculations */
		// NcMtx = 		 FADECRealloc(NcMtx, SteadyOp_Elem);
		// Pt21Mtx = 	     FADECRealloc(Pt21Mtx, SteadyOp_Elem);
		// Pt3Mtx = 		 FADECRealloc(Pt3Mtx, SteadyOp_Elem);
		// Pt5Mtx = 		 FADECRealloc(Pt5Mtx, SteadyOp_Elem);
		// Pt6Mtx = 		 FADECRealloc(Pt6Mtx, SteadyOp_Elem);
		// Tt21Mtx = 	     FADECRealloc(Tt21Mtx, SteadyOp_Elem);
		// Tt3Mtx = 	     FADECRealloc(Tt3Mtx, SteadyOp_Elem);
		// Tt4Mtx = 	     FADECRealloc(Tt4Mtx, SteadyOp_Elem);
		// Tt5Mtx = 	     FADECRealloc(Tt5Mtx, SteadyOp_Elem);
		// Tt6Mtx = 	     FADECRealloc(Tt6Mtx, SteadyOp_Elem);
		// WfMtx = 	     FADECRealloc(WfMtx, SteadyOp_Elem);
		// AMtx = 		     FADECRealloc(AMtx, SteadyOp_Elem);
		// BMtx = 		     FADECRealloc(BMtx, SteadyOp_Elem);
		// Pt21DMtx = 	     FADECRealloc(Pt21DMtx, SteadyOp_Elem);
		// Pt3DMtx = 	     FADECRealloc(Pt3DMtx, SteadyOp_Elem);
		// Pt5DMtx = 	     FADECRealloc(Pt5DMtx, SteadyOp_Elem);
		// Pt6DMtx = 	     FADECRealloc(Pt6DMtx, SteadyOp_Elem);
		// Tt21DMtx = 	     FADECRealloc(Tt21DMtx, SteadyOp_Elem);
		// Tt3DMtx = 	     FADECRealloc(Tt3DMtx, SteadyOp_Elem);
		// Tt4DMtx = 	     FADECRealloc(Tt4DMtx, SteadyOp_Elem);
		// Tt5DMtx = 	     FADECRealloc(Tt5DMtx, SteadyOp_Elem);
		// Tt6DMtx = 	     FADECRealloc(Tt6DMtx, SteadyOp_Elem);
        
		// /* Matrices used for sub-idle calculations */
        // AwmMtx = 		 FADECRealloc(AwmMtx, SteadyOp_Elem);
		// AshMtx = 		 FADECRealloc(AshMtx, SteadyOp_Elem);
        // BwmMtx = 		 FADECRealloc(BwmMtx, SteadyOp_Elem);
		// BshMtx = 		 FADECRealloc(BshMtx, SteadyOp_Elem);
        // RPMshMtx = 	     FADECRealloc(RPMshMtx, SteadyOp_Elem);
		// RPMwmMtx = 	     FADECRealloc(RPMwmMtx, SteadyOp_Elem);
		// NcFANshMtx = 	 FADECRealloc(NcFANshMtx, SteadyOp_Elem);
		// Pt21shMtx = 	 FADECRealloc(Pt21shMtx, SteadyOp_Elem);
		// Pt21wmMtx = 	 FADECRealloc(Pt21wmMtx, SteadyOp_Elem);
		// Pt21DshMtx = 	 FADECRealloc(Pt21DshMtx, SteadyOp_Elem);
		// Pt21DwmMtx = 	 FADECRealloc(Pt21DwmMtx, SteadyOp_Elem);
		// Pt3shMtx = 	     FADECRealloc(Pt3shMtx, SteadyOp_Elem);
		// Pt3wmMtx = 	     FADECRealloc(Pt3wmMtx, SteadyOp_Elem);
		// Pt3DshMtx = 	 FADECRealloc(Pt3DshMtx, SteadyOp_Elem);
		// Pt3DwmMtx = 	 FADECRealloc(Pt3DwmMtx, SteadyOp_Elem);
		// Pt5shMtx = 	     FADECRealloc(Pt5shMtx, SteadyOp_Elem);
		// Pt5wmMtx = 	     FADECRealloc(Pt5wmMtx, SteadyOp_Elem);
		// Pt5DshMtx = 	 FADECRealloc(Pt5DshMtx, SteadyOp_Elem);
		// Pt5DwmMtx = 	 FADECRealloc(Pt5DwmMtx, SteadyOp_Elem);
		// Pt6shMtx = 	     FADECRealloc(Pt6shMtx, SteadyOp_Elem);
		// Pt6wmMtx = 	     FADECRealloc(Pt6wmMtx, SteadyOp_Elem);
		// Pt6DshMtx = 	 FADECRealloc(Pt6DshMtx, SteadyOp_Elem);
		// Pt6DwmMtx = 	 FADECRealloc(Pt6DwmMtx, SteadyOp_Elem);
		// Tt21shMtx = 	 FADECRealloc(Tt21shMtx, SteadyOp_Elem);
		// Tt21wmMtx = 	 FADECRealloc(Tt21wmMtx, SteadyOp_Elem);
		// Tt21DshMtx = 	 FADECRealloc(Tt21DshMtx, SteadyOp_Elem);
		// Tt21DwmMtx = 	 FADECRealloc(Tt21DwmMtx, SteadyOp_Elem);
		// Tt3shMtx = 	     FADECRealloc(Tt3shMtx, SteadyOp_Elem);
		// Tt3wmMtx = 	     FADECRealloc(Tt3wmMtx, SteadyOp_Elem);
		// Tt3DshMtx = 	 FADECRealloc(Tt3DshMtx, SteadyOp_Elem);
		// Tt3DwmMtx = 	 FADECRealloc(Tt3DwmMtx, SteadyOp_Elem);
		// Tt4shMtx = 	     FADECRealloc(Tt4shMtx, SteadyOp_Elem);
		// Tt4wmMtx = 	     FADECRealloc(Tt4wmMtx, SteadyOp_Elem);
		// Tt4CshMtx = 	 FADECRealloc(Tt4CshMtx, SteadyOp_Elem);
		// Tt4DshMtx = 	 FADECRealloc(Tt4DshMtx, SteadyOp_Elem);
		// Tt4DwmMtx = 	 FADECRealloc(Tt4DwmMtx, SteadyOp_Elem);
    	// Tt5shMtx = 	     FADECRealloc(Tt5shMtx, SteadyOp_Elem);
		// Tt5wmMtx = 	     FADECRealloc(Tt5wmMtx, SteadyOp_Elem);
		// Tt5DshMtx = 	 FADECRealloc(Tt5DshMtx, SteadyOp_Elem);
		// Tt5DwmMtx = 	 FADECRealloc(Tt5DwmMtx, SteadyOp_Elem);
		// Tt6shMtx = 	     FADECRealloc(Tt6shMtx, SteadyOp_Elem);
		// Tt6wmMtx = 	     FADECRealloc(Tt6wmMtx, SteadyOp_Elem);
		// Tt6DshMtx = 	 FADECRealloc(Tt6DshMtx, SteadyOp_Elem);
		// Tt6DwmMtx = 	 FADECRealloc(Tt6DwmMtx, SteadyOp_Elem);
	    // WfshMtx = 	     FADECRealloc(WfshMtx, SteadyOp_Elem);		
		// WfwmMtx = 	     FADECRealloc(WfwmMtx, SteadyOp_Elem);

		// /* Low Pressure Compressor or Fan */
		// NcFANMapMtx =    FADECRealloc(NcFANMapMtx, NcFANMap_Elem);
		// WcFANStallMtx =  FADECRealloc(WcFANStallMtx, NcFANMap_Elem);
		// PRFANStallMtx =  FADECRealloc(PRFANStallMtx, NcFANMap_Elem);
		// WcFANMapMtx =    FADECRealloc(WcFANMapMtx, WcFANMap_Elem);
		// PRFANMapMtx =    FADECRealloc(PRFANMapMtx, WcFANMap_Elem);
		// EffFANMapMtx =   FADECRealloc(EffFANMapMtx, WcFANMap_Elem);

		// /* High Pressure Compressor */
		// NcHPCMapMtx =    FADECRealloc(NcHPCMapMtx, NcHPCMap_Elem);
		// WcHPCStallMtx =  FADECRealloc(WcHPCStallMtx, NcHPCMap_Elem);
		// PRHPCStallMtx =  FADECRealloc(PRHPCStallMtx, NcHPCMap_Elem);
		// WcHPCMapMtx =    FADECRealloc(WcHPCMapMtx, WcHPCMap_Elem);
		// PRHPCMapMtx =    FADECRealloc(PRHPCMapMtx, WcHPCMap_Elem);
		// EffHPCMapMtx =   FADECRealloc(EffHPCMapMtx, WcHPCMap_Elem);

		// /* Turbine */
		// NcHPTMapMtx =    FADECRealloc(NcHPTMapMtx, NcHPTMap_Elem);
		// WcHPTMapMtx =    FADECRealloc(WcHPTMapMtx, WcHPTMap_Elem);
		// EffHPTMapMtx =   FADECRealloc(EffHPTMapMtx, WcHPTMap_Elem);
		// PRHPTMapMtx =    FADECRealloc(PRHPTMapMtx, PRHPTMap_Elem);

	   	// /* Auxiliar matrices */
		// Mtx2D = 		 FADECRealloc(Mtx2D, MN_Elem * Fn_Elem);
		// Mtx2DH = 		 FADECRealloc(Mtx2DH, MN_Elem * Fn_Elem);
		// Mtx1D = 		 FADECRealloc(Mtx1D, Fn_Elem);
		// Mtx1DH = 		 FADECRealloc(Mtx1DH, Fn_Elem);

	    // DeltaMtx2D = 	 FADECRealloc(DeltaMtx2D, Alt_Elem * MN_Elem);
		// DeltaMtx2DH =    FADECRealloc(DeltaMtx2DH, Alt_Elem * MN_Elem);
		// DeltaMtx1D = 	 FADECRealloc(DeltaMtx1D, MN_Elem);
		// DeltaMtx1DH =    FADECRealloc(DeltaMtx1DH, MN_Elem);

		// Ts0Mtx2D = 	     FADECRealloc(Ts0Mtx2D, Fn_Elem);
		// Ts0Mtx2DH = 	 FADECRealloc(Ts0Mtx2DH, Fn_Elem);
		// Ts0Mtx1D = 	     FADECRealloc(Ts0Mtx1D, Alt_Elem);
		// Ts0Mtx1DH = 	 FADECRealloc(Ts0Mtx1DH, Alt_Elem);
        
		// MapFAN2D = 	     FADECRealloc(MapFAN2D, WcFANMap_Elem);
		// MapFAN2DH = 	 FADECRealloc(MapFAN2DH, WcFANMap_Elem);
		// MapFAN1D = 	     FADECRealloc(MapFAN1D, Wc_per_Nc_FAN);
		// MapFAN1DH = 	 FADECRealloc(MapFAN1DH, Wc_per_Nc_FAN);

		// MapHPC2D = 	     FADECRealloc(MapHPC2D, WcHPCMap_Elem);
		// MapHPC2DH = 	 FADECRealloc(MapHPC2DH, WcHPCMap_Elem);
		// MapHPC1D = 	     FADECRealloc(MapHPC1D, Wc_per_Nc_HPC);
		// MapHPC1DH = 	 FADECRealloc(MapHPC1DH, Wc_per_Nc_HPC);

		// /* MN linerizing vector */
		// MNLinVec = 	     FADECRealloc(MNLinVec, MN_Elem);
        // AltLinVec = 	 FADECRealloc(AltLinVec, Alt_Elem);
        // DeltaMtx = 	     FADECRealloc(DeltaMtx, Alt_Elem * MN_Elem);
		// Ts0Mtx = 		 FADECRealloc(Ts0Mtx, Alt_Elem * MN_Elem);

		// /* Reference filter vectors */
		// ASVec = 		 FADECRealloc(ASVec, AS_Elem);
		// DSVec = 		 FADECRealloc(DSVec, AS_Elem);
		// NcVec = 		 FADECRealloc(NcVec, AS_Elem);

/******** UNCOMMENT END ********/

/******** EXCLUDE START ********/
		///* Matrices used for reference and gain calculations */
		//N_KiMtx = 	   (floating *)realloc(N_KiMtx,PowerMan_Elem * sizeof(floating));
		//N_KishMtx = 	   (floating *)realloc(N_KiMtx,PowerMan_Elem * sizeof(floating));
		//N_KpMtx = 	   (floating *)realloc(N_KpMtx,PowerMan_Elem * sizeof(floating));
		//N_KpshMtx =      (floating *)realloc(N_KpMtx,PowerMan_Elem * sizeof(floating));
		//NcFANContMtx =   (floating *)realloc(NcFANContMtx,PowerMan_Elem * sizeof(floating));
		//NcFANshContMtx = (floating *)realloc(NcFANContMtx,PowerMan_Elem * sizeof(floating));
		//FNperContMtx =   (floating *)realloc(FNperContMtx,PowerMan_Elem * sizeof(floating));
        //FNcMaxContMtx =  (floating *)realloc(FNcMaxContMtx,MN_Elem * sizeof(floating));

		///* Matrices used for model calculations */
		//NcMtx = 		   (floating *)realloc(NcMtx,SteadyOp_Elem * sizeof(floating));
		//Pt21Mtx = 	   (floating *)realloc(Pt21Mtx,SteadyOp_Elem * sizeof(floating));
		//Pt3Mtx = 		   (floating *)realloc(Pt3Mtx,SteadyOp_Elem * sizeof(floating));
		//Pt5Mtx = 		   (floating *)realloc(Pt5Mtx,SteadyOp_Elem * sizeof(floating));
		//Pt6Mtx = 		   (floating *)realloc(Pt6Mtx,SteadyOp_Elem * sizeof(floating));
		//Tt21Mtx = 	   (floating *)realloc(Tt21Mtx,SteadyOp_Elem * sizeof(floating));
		//Tt3Mtx = 		   (floating *)realloc(Tt3Mtx,SteadyOp_Elem * sizeof(floating));
		//Tt4Mtx = 		   (floating *)realloc(Tt4Mtx,SteadyOp_Elem * sizeof(floating));
		//Tt5Mtx = 		   (floating *)realloc(Tt5Mtx,SteadyOp_Elem * sizeof(floating));
		//Tt6Mtx = 		   (floating *)realloc(Tt6Mtx,SteadyOp_Elem * sizeof(floating));
		//WfMtx = 		   (floating *)realloc(WfMtx,SteadyOp_Elem * sizeof(floating));
		//AMtx = 		   (floating *)realloc(AMtx,SteadyOp_Elem * sizeof(floating));
		//BMtx = 		   (floating *)realloc(BMtx,SteadyOp_Elem * sizeof(floating));
		//Pt21DMtx = 	   (floating *)realloc(Pt21DMtx,SteadyOp_Elem * sizeof(floating));
		//Pt3DMtx = 	   (floating *)realloc(Pt3DMtx,SteadyOp_Elem * sizeof(floating));
		//Pt5DMtx = 	   (floating *)realloc(Pt5DMtx,SteadyOp_Elem * sizeof(floating));
		//Pt6DMtx = 	   (floating *)realloc(Pt6DMtx,SteadyOp_Elem * sizeof(floating));
		//Tt21DMtx = 	   (floating *)realloc(Tt21DMtx,SteadyOp_Elem * sizeof(floating));
		//Tt3DMtx = 	   (floating *)realloc(Tt3DMtx,SteadyOp_Elem * sizeof(floating));
		//Tt4DMtx = 	   (floating *)realloc(Tt4DMtx,SteadyOp_Elem * sizeof(floating));
		//Tt5DMtx = 	   (floating *)realloc(Tt5DMtx,SteadyOp_Elem * sizeof(floating));
		//Tt6DMtx = 	   (floating *)realloc(Tt6DMtx,SteadyOp_Elem * sizeof(floating));
        
		///* Matrices used for sub-idle calculations */
        //AwmMtx = 		   (floating *)realloc(AwmMtx,SteadyOp_Elem * sizeof(floating));
		//AshMtx = 		   (floating *)realloc(AshMtx,SteadyOp_Elem * sizeof(floating));
        //BwmMtx = 		   (floating *)realloc(BwmMtx,SteadyOp_Elem * sizeof(floating));
		//BshMtx = 		   (floating *)realloc(BshMtx,SteadyOp_Elem * sizeof(floating));
        //RPMshMtx = 	   (floating *)realloc(RPMshMtx,SteadyOp_Elem * sizeof(floating));
		//RPMwmMtx = 	   (floating *)realloc(RPMwmMtx,SteadyOp_Elem * sizeof(floating));
		//NcFANshMtx = 	   (floating *)realloc(NcFANshMtx,SteadyOp_Elem * sizeof(floating));
		//Pt21shMtx = 	   (floating *)realloc(Pt21shMtx,SteadyOp_Elem * sizeof(floating));
		//Pt21wmMtx = 	   (floating *)realloc(Pt21wmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt21DshMtx = 	   (floating *)realloc(Pt21DshMtx,SteadyOp_Elem * sizeof(floating));
		//Pt21DwmMtx = 	   (floating *)realloc(Pt21DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt3shMtx = 	   (floating *)realloc(Pt3shMtx,SteadyOp_Elem * sizeof(floating));
		//Pt3wmMtx = 	   (floating *)realloc(Pt3wmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt3DshMtx = 	   (floating *)realloc(Pt3DshMtx,SteadyOp_Elem * sizeof(floating));
		//Pt3DwmMtx = 	   (floating *)realloc(Pt3DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt5shMtx = 	   (floating *)realloc(Pt5shMtx,SteadyOp_Elem * sizeof(floating));
		//Pt5wmMtx = 	   (floating *)realloc(Pt5wmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt5DshMtx = 	   (floating *)realloc(Pt5DshMtx,SteadyOp_Elem * sizeof(floating));
		//Pt5DwmMtx = 	   (floating *)realloc(Pt5DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt6shMtx = 	   (floating *)realloc(Pt6shMtx,SteadyOp_Elem * sizeof(floating));
		//Pt6wmMtx = 	   (floating *)realloc(Pt6wmMtx,SteadyOp_Elem * sizeof(floating));
		//Pt6DshMtx = 	   (floating *)realloc(Pt6DshMtx,SteadyOp_Elem * sizeof(floating));
		//Pt6DwmMtx = 	   (floating *)realloc(Pt6DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt21shMtx = 	   (floating *)realloc(Tt21shMtx,SteadyOp_Elem * sizeof(floating));
		//Tt21wmMtx = 	   (floating *)realloc(Tt21wmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt21DshMtx = 	   (floating *)realloc(Tt21DshMtx,SteadyOp_Elem * sizeof(floating));
		//Tt21DwmMtx = 	   (floating *)realloc(Tt21DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt3shMtx = 	   (floating *)realloc(Tt3shMtx,SteadyOp_Elem * sizeof(floating));
		//Tt3wmMtx = 	   (floating *)realloc(Tt3wmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt3DshMtx = 	   (floating *)realloc(Tt3DshMtx,SteadyOp_Elem * sizeof(floating));
		//Tt3DwmMtx = 	   (floating *)realloc(Tt3DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt4shMtx = 	   (floating *)realloc(Tt4shMtx,SteadyOp_Elem * sizeof(floating));
		//Tt4wmMtx = 	   (floating *)realloc(Tt4wmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt4CshMtx = 	   (floating *)realloc(Tt4CshMtx,SteadyOp_Elem * sizeof(floating));
		//Tt4DshMtx = 	   (floating *)realloc(Tt4DshMtx,SteadyOp_Elem * sizeof(floating));
		//Tt4DwmMtx = 	   (floating *)realloc(Tt4DwmMtx,SteadyOp_Elem * sizeof(floating));
    	//Tt5shMtx = 	   (floating *)realloc(Tt5shMtx,SteadyOp_Elem * sizeof(floating));
		//Tt5wmMtx = 	   (floating *)realloc(Tt5wmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt5DshMtx = 	   (floating *)realloc(Tt5DshMtx,SteadyOp_Elem * sizeof(floating));
		//Tt5DwmMtx = 	   (floating *)realloc(Tt5DwmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt6shMtx = 	   (floating *)realloc(Tt6shMtx,SteadyOp_Elem * sizeof(floating));
		//Tt6wmMtx = 	   (floating *)realloc(Tt6wmMtx,SteadyOp_Elem * sizeof(floating));
		//Tt6DshMtx = 	   (floating *)realloc(Tt6DshMtx,SteadyOp_Elem * sizeof(floating));
		//Tt6DwmMtx = 	   (floating *)realloc(Tt6DwmMtx,SteadyOp_Elem * sizeof(floating));
	    //WfshMtx = 	   (floating *)realloc(WfshMtx,SteadyOp_Elem * sizeof(floating));		
		//WfwmMtx = 	   (floating *)realloc(WfwmMtx,SteadyOp_Elem * sizeof(floating));


		///* Low Pressure Compressor or Fan */
		//NcFANMapMtx =    (floating *)realloc(NcFANMapMtx,NcFANMap_Elem * sizeof(floating));
		//WcFANStallMtx =  (floating *)realloc(WcFANStallMtx,NcFANMap_Elem * sizeof(floating));
		//PRFANStallMtx =  (floating *)realloc(PRFANStallMtx,NcFANMap_Elem * sizeof(floating));
		//WcFANMapMtx =    (floating *)realloc(WcFANMapMtx,WcFANMap_Elem * sizeof(floating));
		//PRFANMapMtx =    (floating *)realloc(PRFANMapMtx,WcFANMap_Elem * sizeof(floating));
		//EffFANMapMtx =   (floating *)realloc(EffFANMapMtx,WcFANMap_Elem * sizeof(floating));

		///* High Pressure Compressor */
		//NcHPCMapMtx =    (floating *)realloc(NcHPCMapMtx,NcHPCMap_Elem * sizeof(floating));
		//WcHPCStallMtx =  (floating *)realloc(WcHPCStallMtx,NcHPCMap_Elem * sizeof(floating));
		//PRHPCStallMtx =  (floating *)realloc(PRHPCStallMtx,NcHPCMap_Elem * sizeof(floating));
		//WcHPCMapMtx =    (floating *)realloc(WcHPCMapMtx,WcHPCMap_Elem * sizeof(floating));
		//PRHPCMapMtx =    (floating *)realloc(PRHPCMapMtx,WcHPCMap_Elem * sizeof(floating));
		//EffHPCMapMtx =   (floating *)realloc(EffHPCMapMtx,WcHPCMap_Elem * sizeof(floating));

		///* Turbine */
		//NcHPTMapMtx =    (floating *)realloc(NcHPTMapMtx,NcHPTMap_Elem * sizeof(floating));
		//WcHPTMapMtx =    (floating *)realloc(WcHPTMapMtx,WcHPTMap_Elem * sizeof(floating));
		//EffHPTMapMtx =   (floating *)realloc(EffHPTMapMtx,WcHPTMap_Elem * sizeof(floating));
		//PRHPTMapMtx =    (floating *)realloc(PRHPTMapMtx,PRHPTMap_Elem * sizeof(floating));

	   	///* Auxiliar matrices */
		//Mtx2D = 		   (floating *)realloc(Mtx2D,MN_Elem * Fn_Elem * sizeof(floating));
		//Mtx2DH = 		   (floating *)realloc(Mtx2DH,MN_Elem * Fn_Elem * sizeof(floating));
		//Mtx1D = 		   (floating *)realloc(Mtx1D,Fn_Elem * sizeof(floating));
		//Mtx1DH = 		   (floating *)realloc(Mtx1DH,Fn_Elem * sizeof(floating));

	    //DeltaMtx2D = 	   (floating *)realloc(DeltaMtx2D,Alt_Elem * MN_Elem * sizeof(floating));
		//DeltaMtx2DH =    (floating *)realloc(DeltaMtx2DH,Alt_Elem * MN_Elem * sizeof(floating));
		//DeltaMtx1D = 	   (floating *)realloc(DeltaMtx1D,MN_Elem * sizeof(floating));
		//DeltaMtx1DH =    (floating *)realloc(DeltaMtx1DH,MN_Elem * sizeof(floating));

		//Ts0Mtx2D = 	   (floating *)realloc(Ts0Mtx2D,Fn_Elem * sizeof(floating));
		//Ts0Mtx2DH = 	   (floating *)realloc(Ts0Mtx2DH,Fn_Elem * sizeof(floating));
		//Ts0Mtx1D = 	   (floating *)realloc(Ts0Mtx1D,Alt_Elem * sizeof(floating));
		//Ts0Mtx1DH = 	   (floating *)realloc(Ts0Mtx1DH,Alt_Elem * sizeof(floating));
        
		//MapFAN2D = 	   (floating *)realloc(MapFAN2D,WcFANMap_Elem * sizeof(floating));
		//MapFAN2DH = 	   (floating *)realloc(MapFAN2DH,WcFANMap_Elem * sizeof(floating));
		//MapFAN1D = 	   (floating *)realloc(MapFAN1D,Wc_per_Nc_FAN * sizeof(floating));
		//MapFAN1DH = 	   (floating *)realloc(MapFAN1DH,Wc_per_Nc_FAN * sizeof(floating));

		//MapHPC2D = 	   (floating *)realloc(MapHPC2D,WcHPCMap_Elem * sizeof(floating));
		//MapHPC2DH = 	   (floating *)realloc(MapHPC2DH,WcHPCMap_Elem * sizeof(floating));
		//MapHPC1D = 	   (floating *)realloc(MapHPC1D,Wc_per_Nc_HPC * sizeof(floating));
		//MapHPC1DH = 	   (floating *)realloc(MapHPC1DH,Wc_per_Nc_HPC * sizeof(floating));

		///* MN linerizing vector */
		//MNLinVec = 	   (floating *)realloc(MNLinVec,MN_Elem * sizeof(floating));
        //AltLinVec = 	   (floating *)realloc(AltLinVec,Alt_Elem * sizeof(floating));
        //DeltaMtx = 	   (floating *)realloc(DeltaMtx,Alt_Elem * MN_Elem * sizeof(floating));
		//Ts0Mtx = 		   (floating *)realloc(Ts0Mtx,Alt_Elem * MN_Elem * sizeof(floating));

		///* Reference filter vectors */
		//ASVec = 		   (floating *)realloc(ASVec,AS_Elem * sizeof(floating));
		//DSVec = 		   (floating *)realloc(DSVec,AS_Elem * sizeof(floating));
		//NcVec = 		   (floating *)realloc(NcVec,AS_Elem * sizeof(floating));

/******** EXCLUDE END ********/

/******** EXCLUDE START ********/
		/* -------------------------------------------------- */
        /* REALLOCKING MEMORY - PWLM                          */
        /* (To be usedi in MATLAB (PWLM) simulations only)    */
        /* -------------------------------------------------- */

		/* Matrices used for reference and gain calculations */
		N_KiMtx = 		 FADECMalloc(PowerMan_Elem, &MemSize);
		N_KishMtx = 	 FADECMalloc(PowerMan_Elem, &MemSize);
		N_KpMtx = 		 FADECMalloc(PowerMan_Elem, &MemSize);
		N_KpshMtx =      FADECMalloc(PowerMan_Elem, &MemSize);		
		NcFANContMtx =   FADECMalloc(PowerMan_Elem, &MemSize);
		NcFANshContMtx = FADECMalloc(PowerMan_Elem, &MemSize);
		FNperContMtx =   FADECMalloc(PowerMan_Elem, &MemSize);
        FNcMaxContMtx =  FADECMalloc(MN_Elem, &MemSize);

		/* Matrices used for model calculations */
		NcMtx =          FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21Mtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21Mtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6Mtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		WfMtx =          FADECMalloc(SteadyOp_Elem, &MemSize);
		AMtx =           FADECMalloc(SteadyOp_Elem, &MemSize);
		BMtx = 	         FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21DMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21DMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6DMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);
        
    	/* Matrices used for sub-idle calculations */
        AwmMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		AshMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
        BwmMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
		BshMtx =         FADECMalloc(SteadyOp_Elem, &MemSize);
        RPMshMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		RPMwmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		NcFANshMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21shMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21wmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21DshMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt21DwmMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt3DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt5DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Pt6DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21shMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21wmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21DshMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt21DwmMtx =     FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt3DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4CshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt4DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
    	Tt5shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt5DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6shMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6wmMtx =       FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6DshMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
		Tt6DwmMtx =      FADECMalloc(SteadyOp_Elem, &MemSize);
	    WfshMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);		
		WfwmMtx =        FADECMalloc(SteadyOp_Elem, &MemSize);

		/* Low Pressure Compressor or Fan */
		NcFANMapMtx =    FADECMalloc(NcFANMap_Elem, &MemSize);
		WcFANStallMtx =  FADECMalloc(NcFANMap_Elem, &MemSize);
		PRFANStallMtx =  FADECMalloc(NcFANMap_Elem, &MemSize);
		WcFANMapMtx =    FADECMalloc(WcFANMap_Elem, &MemSize);
		PRFANMapMtx =    FADECMalloc(WcFANMap_Elem, &MemSize);
		EffFANMapMtx =   FADECMalloc(WcFANMap_Elem, &MemSize);

		/* High Pressure Compressor */
		NcHPCMapMtx =    FADECMalloc(NcHPCMap_Elem, &MemSize);
		WcHPCStallMtx =  FADECMalloc(NcHPCMap_Elem, &MemSize);
		PRHPCStallMtx =  FADECMalloc(NcHPCMap_Elem, &MemSize);
		WcHPCMapMtx =    FADECMalloc(WcHPCMap_Elem, &MemSize);
		PRHPCMapMtx =    FADECMalloc(WcHPCMap_Elem, &MemSize);
		EffHPCMapMtx =   FADECMalloc(WcHPCMap_Elem, &MemSize);

		/* Turbine */
		NcHPTMapMtx =    FADECMalloc(NcHPTMap_Elem, &MemSize);
		WcHPTMapMtx =    FADECMalloc(WcHPTMap_Elem, &MemSize);
		EffHPTMapMtx =   FADECMalloc(WcHPTMap_Elem, &MemSize);
		PRHPTMapMtx =    FADECMalloc(PRHPTMap_Elem, &MemSize);

		/* Auxiliar matrices */
		Mtx2D = 		 FADECMalloc(MN_Elem * Fn_Elem, &MemSize);
		Mtx2DH = 		 FADECMalloc(MN_Elem * Fn_Elem, &MemSize);
		Mtx1D = 		 FADECMalloc(Fn_Elem, &MemSize);
		Mtx1DH = 		 FADECMalloc(Fn_Elem, &MemSize);
         
        DeltaMtx2D =     FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
		DeltaMtx2DH =    FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
		DeltaMtx1D =     FADECMalloc(MN_Elem, &MemSize);
		DeltaMtx1DH =    FADECMalloc(MN_Elem, &MemSize);
 
		Ts0Mtx2D =       FADECMalloc(Fn_Elem, &MemSize);
		Ts0Mtx2DH = 	 FADECMalloc(Fn_Elem, &MemSize);
		Ts0Mtx1D = 		 FADECMalloc(Alt_Elem, &MemSize);
		Ts0Mtx1DH = 	 FADECMalloc(Alt_Elem, &MemSize);
 
		MapFAN2D = 		 FADECMalloc(WcFANMap_Elem, &MemSize);
		MapFAN2DH = 	 FADECMalloc(WcFANMap_Elem, &MemSize);
		MapFAN1D = 		 FADECMalloc(Wc_per_Nc_FAN, &MemSize);
		MapFAN1DH = 	 FADECMalloc(Wc_per_Nc_FAN, &MemSize);
 
		MapHPC2D = 		 FADECMalloc(WcHPCMap_Elem, &MemSize);
		MapHPC2DH = 	 FADECMalloc(WcHPCMap_Elem, &MemSize);
		MapHPC1D = 		 FADECMalloc(Wc_per_Nc_HPC, &MemSize);
		MapHPC1DH = 	 FADECMalloc(Wc_per_Nc_HPC, &MemSize);

		/* MN linerizing vector */
		MNLinVec = 		 FADECMalloc(MN_Elem, &MemSize);
        AltLinVec = 	 FADECMalloc(Alt_Elem, &MemSize);
        DeltaMtx = 		 FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
		Ts0Mtx = 		 FADECMalloc(Alt_Elem * MN_Elem, &MemSize);

		/* Reference filter vectors */
		ASVec = 		 FADECMalloc(AS_Elem, &MemSize);
		DSVec = 		 FADECMalloc(AS_Elem, &MemSize);
		NcVec = 		 FADECMalloc(AS_Elem, &MemSize);

        /* -------------------------------------------------- */
/******** EXCLUDE END ********/

	}

	/*----------------------------------*/
	/* UPDATES ENGINE MATRICES ELEMENTS */
	/*----------------------------------*/

	if (WhichEngine == 1)
	{
		
		/* Loads FADEC matrices */
		getTJ1200FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
						  DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
						  N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
						  Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
						  Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
						  WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);

		/* Loads HIL matrices */
		getTJ1200HILMtx(AshMtx, AwmMtx, BshMtx, BwmMtx, EffFANMapMtx,
						EffHPCMapMtx, EffHPTMapMtx, NcFANMapMtx, NcHPTMapMtx, NcMtx,
						PRFANMapMtx, PRFANStallMtx, PRHPCStallMtx, PRHPTMapMtx, Pt21DMtx,
						Pt21Mtx, Pt6DMtx, Pt6Mtx, RPMshMtx, RPMwmMtx,
						Tt21DMtx, Tt21Mtx, Tt3DMtx, Tt3Mtx, Tt4CshMtx,
						Tt4DshMtx, Tt4shMtx, Tt6DMtx, Tt6Mtx, WcFANMapMtx,
						WcFANStallMtx, WcHPCStallMtx, WcHPTMapMtx, WfshMtx, NcFANshMtx,
						WfwmMtx, Pt3shMtx, Pt3DshMtx, Pt21wmMtx, Pt21DwmMtx,
						Pt3wmMtx, Pt3DwmMtx, Pt5wmMtx, Pt5DwmMtx, Pt6wmMtx,
						Pt6DwmMtx, Tt21wmMtx, Tt21DwmMtx, Tt3wmMtx, Tt3DwmMtx,
						Tt4wmMtx, Tt4DwmMtx, Tt5wmMtx, Tt5DwmMtx, Tt6wmMtx,
						Tt6DwmMtx, Pt21shMtx, Pt21DshMtx, Pt5shMtx, Pt5DshMtx,
						Pt6shMtx, Pt6DshMtx, Tt21shMtx, Tt21DshMtx, Tt3shMtx,
						Tt3DshMtx, Tt5shMtx, Tt5DshMtx, Tt6shMtx, Tt6DshMtx);

		/* Loads controller constants */
    	getTJ1200FADECContConst(&ContConst);

	}

	if (WhichEngine == 2)
	{

		/* Loads FADEC matrices */
		getTF1200FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
						  DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
						  N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
						  Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
						  Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
						  WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);


		/* Loads HIL matrices */
		getTF1200HILMtx(AshMtx, AwmMtx, BshMtx, BwmMtx, EffFANMapMtx,
						EffHPCMapMtx, EffHPTMapMtx, NcFANMapMtx, NcHPTMapMtx, NcMtx,
						PRFANMapMtx, PRFANStallMtx, PRHPCStallMtx, PRHPTMapMtx, Pt21DMtx,
						Pt21Mtx, Pt6DMtx, Pt6Mtx, RPMshMtx, RPMwmMtx,
						Tt21DMtx, Tt21Mtx, Tt3DMtx, Tt3Mtx, Tt4CshMtx,
						Tt4DshMtx, Tt4shMtx, Tt6DMtx, Tt6Mtx, WcFANMapMtx,
						WcFANStallMtx, WcHPCStallMtx, WcHPTMapMtx, WfshMtx, NcFANshMtx,
						WfwmMtx, Pt3shMtx, Pt3DshMtx, Pt21wmMtx, Pt21DwmMtx,
						Pt3wmMtx, Pt3DwmMtx, Pt5wmMtx, Pt5DwmMtx, Pt6wmMtx,
						Pt6DwmMtx, Tt21wmMtx, Tt21DwmMtx, Tt3wmMtx, Tt3DwmMtx,
						Tt4wmMtx, Tt4DwmMtx, Tt5wmMtx, Tt5DwmMtx, Tt6wmMtx,
						Tt6DwmMtx, Pt21shMtx, Pt21DshMtx, Pt5shMtx, Pt5DshMtx,
						Pt6shMtx, Pt6DshMtx, Tt21shMtx, Tt21DshMtx, Tt3shMtx,
						Tt3DshMtx, Tt5shMtx, Tt5DshMtx, Tt6shMtx, Tt6DshMtx);

		/* Loads controller constants */
		getTF1200FADECContConst(&ContConst);

    }
	
	if (WhichEngine == 3)
	{

		/* Loads FADEC matrices */
		getGEJ85FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
						  DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
						  N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
						  Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
						  Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
						  WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);

		/* Loads HIL matrices */
		getGEJ85HILMtx(AshMtx, AwmMtx, BshMtx, BwmMtx, EffFANMapMtx,
					   EffHPCMapMtx, EffHPTMapMtx, NcFANMapMtx, NcHPTMapMtx, NcMtx,
					   PRFANMapMtx, PRFANStallMtx, PRHPCStallMtx, PRHPTMapMtx, Pt21DMtx,
					   Pt21Mtx, Pt6DMtx, Pt6Mtx, RPMshMtx, RPMwmMtx,
					   Tt21DMtx, Tt21Mtx, Tt3DMtx, Tt3Mtx, Tt4CshMtx,
					   Tt4DshMtx, Tt4shMtx, Tt6DMtx, Tt6Mtx, WcFANMapMtx,
					   WcFANStallMtx, WcHPCStallMtx, WcHPTMapMtx, WfshMtx, NcFANshMtx,
					   WfwmMtx, Pt3shMtx, Pt3DshMtx, Pt21wmMtx, Pt21DwmMtx,
					   Pt3wmMtx, Pt3DwmMtx, Pt5wmMtx, Pt5DwmMtx, Pt6wmMtx,
					   Pt6DwmMtx, Tt21wmMtx, Tt21DwmMtx, Tt3wmMtx, Tt3DwmMtx,
					   Tt4wmMtx, Tt4DwmMtx, Tt5wmMtx, Tt5DwmMtx, Tt6wmMtx,
					   Tt6DwmMtx, Pt21shMtx, Pt21DshMtx, Pt5shMtx, Pt5DshMtx,
					   Pt6shMtx, Pt6DshMtx, Tt21shMtx, Tt21DshMtx, Tt3shMtx,
					   Tt3DshMtx, Tt5shMtx, Tt5DshMtx, Tt6shMtx, Tt6DshMtx);

		/* Loads controller constants */
		getGEJ85FADECContConst(&ContConst);
    }

	if (WhichEngine == 4)
	{

		/* Loads FADEC matrices */
		getTJ700FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
						  DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
						  N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
						  Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
						  Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
						  WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);

		/* Loads HIL matrices */
		getTJ700HILMtx(AshMtx, AwmMtx, BshMtx, BwmMtx, EffFANMapMtx,
					   EffHPCMapMtx, EffHPTMapMtx, NcFANMapMtx, NcHPTMapMtx, NcMtx,
					   PRFANMapMtx, PRFANStallMtx, PRHPCStallMtx, PRHPTMapMtx, Pt21DMtx,
					   Pt21Mtx, Pt6DMtx, Pt6Mtx, RPMshMtx, RPMwmMtx,
					   Tt21DMtx, Tt21Mtx, Tt3DMtx, Tt3Mtx, Tt4CshMtx,
					   Tt4DshMtx, Tt4shMtx, Tt6DMtx, Tt6Mtx, WcFANMapMtx,
					   WcFANStallMtx, WcHPCStallMtx, WcHPTMapMtx, WfshMtx, NcFANshMtx,
					   WfwmMtx, Pt3shMtx, Pt3DshMtx, Pt21wmMtx, Pt21DwmMtx,
					   Pt3wmMtx, Pt3DwmMtx, Pt5wmMtx, Pt5DwmMtx, Pt6wmMtx,
					   Pt6DwmMtx, Tt21wmMtx, Tt21DwmMtx, Tt3wmMtx, Tt3DwmMtx,
					   Tt4wmMtx, Tt4DwmMtx, Tt5wmMtx, Tt5DwmMtx, Tt6wmMtx,
					   Tt6DwmMtx, Pt21shMtx, Pt21DshMtx, Pt5shMtx, Pt5DshMtx,
					   Pt6shMtx, Pt6DshMtx, Tt21shMtx, Tt21DshMtx, Tt3shMtx,
					   Tt3DshMtx, Tt5shMtx, Tt5DshMtx, Tt6shMtx, Tt6DshMtx);

		/* Loads controller constants */
		getTJ700FADECContConst(&ContConst);
    }

	if (WhichEngine == 5)
	{

		/* Loads FADEC matrices */
		getTJ200FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
						 DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
						 N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
						 Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
						 Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
						 WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);

		/* Loads HIL matrices */
		getTJ200HILMtx(AshMtx, AwmMtx, BshMtx, BwmMtx, EffFANMapMtx,
					   EffHPCMapMtx, EffHPTMapMtx, NcFANMapMtx, NcHPTMapMtx, NcMtx,
					   PRFANMapMtx, PRFANStallMtx, PRHPCStallMtx, PRHPTMapMtx, Pt21DMtx,
					   Pt21Mtx, Pt6DMtx, Pt6Mtx, RPMshMtx, RPMwmMtx,
					   Tt21DMtx, Tt21Mtx, Tt3DMtx, Tt3Mtx, Tt4CshMtx,
					   Tt4DshMtx, Tt4shMtx, Tt6DMtx, Tt6Mtx, WcFANMapMtx,
					   WcFANStallMtx, WcHPCStallMtx, WcHPTMapMtx, WfshMtx, NcFANshMtx,
					   WfwmMtx, Pt3shMtx, Pt3DshMtx, Pt21wmMtx, Pt21DwmMtx,
					   Pt3wmMtx, Pt3DwmMtx, Pt5wmMtx, Pt5DwmMtx, Pt6wmMtx,
					   Pt6DwmMtx, Tt21wmMtx, Tt21DwmMtx, Tt3wmMtx, Tt3DwmMtx,
					   Tt4wmMtx, Tt4DwmMtx, Tt5wmMtx, Tt5DwmMtx, Tt6wmMtx,
					   Tt6DwmMtx, Pt21shMtx, Pt21DshMtx, Pt5shMtx, Pt5DshMtx,
					   Pt6shMtx, Pt6DshMtx, Tt21shMtx, Tt21DshMtx, Tt3shMtx,
					   Tt3DshMtx, Tt5shMtx, Tt5DshMtx, Tt6shMtx, Tt6DshMtx);

		/* Loads controller constants */
		getTJ200FADECContConst(&ContConst);
    }

	if (WhichEngine == 6)
	{

		/* Loads FADEC matrices */
		getTJ40FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
						  DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
						  N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
						  Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
						  Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
						  WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);

		/* Loads HIL matrices */
		getTJ40HILMtx(AshMtx, AwmMtx, BshMtx, BwmMtx, EffFANMapMtx,
					   EffHPCMapMtx, EffHPTMapMtx, NcFANMapMtx, NcHPTMapMtx, NcMtx,
					   PRFANMapMtx, PRFANStallMtx, PRHPCStallMtx, PRHPTMapMtx, Pt21DMtx,
					   Pt21Mtx, Pt6DMtx, Pt6Mtx, RPMshMtx, RPMwmMtx,
					   Tt21DMtx, Tt21Mtx, Tt3DMtx, Tt3Mtx, Tt4CshMtx,
					   Tt4DshMtx, Tt4shMtx, Tt6DMtx, Tt6Mtx, WcFANMapMtx,
					   WcFANStallMtx, WcHPCStallMtx, WcHPTMapMtx, WfshMtx, NcFANshMtx,
					   WfwmMtx, Pt3shMtx, Pt3DshMtx, Pt21wmMtx, Pt21DwmMtx,
					   Pt3wmMtx, Pt3DwmMtx, Pt5wmMtx, Pt5DwmMtx, Pt6wmMtx,
					   Pt6DwmMtx, Tt21wmMtx, Tt21DwmMtx, Tt3wmMtx, Tt3DwmMtx,
					   Tt4wmMtx, Tt4DwmMtx, Tt5wmMtx, Tt5DwmMtx, Tt6wmMtx,
					   Tt6DwmMtx, Pt21shMtx, Pt21DshMtx, Pt5shMtx, Pt5DshMtx,
					   Pt6shMtx, Pt6DshMtx, Tt21shMtx, Tt21DshMtx, Tt3shMtx,
					   Tt3DshMtx, Tt5shMtx, Tt5DshMtx, Tt6shMtx, Tt6DshMtx);

		/* Loads controller constants */
		getTJ40FADECContConst(&ContConst);
    }

	/*------------------------------------------*/
	/* CALCULATION OF ENGINE INITIAL CONDITIONS */
	/*------------------------------------------*/

	if (EngOutput.ICCalc == 0)
	{	
mexPrintf("EngUnits=%d, RefCAN=%f\n",EngUnits,RefCAN);        
		/* Reads Altitude, MN and dT for calculating initial conditions */
		InitCond(&SkipStart, SteadyOp_Elem, MN_Elem, Fn_Elem, Altitude, MN, dT, EngPars.NDes, RefCAN, &Ambient, MNLinVec, FNperContMtx,
			NcFANContMtx, FNcMaxContMtx, WfMtx, Mtx2D, Mtx2DH, Mtx1D, Mtx1DH, &EngOutput, EngUnits);

		/* Calculates initial conditions */
		Wf0 = EngOutput.Wf;
		fValue = Wf0;

		/* Sets initial conditions for oil pump rotation speed - bearings model must be validated!! */
		OPRPM = ContConst.OPRPMMax;

		/*If Wf0 is zero, OPRPM must start with zero*/
		if (Wf0 <= 0.000001)
		{
			OPRPM = 0;
		}
mexPrintf("Wf0 = %f\n\n",Wf0);
	}

/******** SAVETO END: MATRICES_AND_CONSTANTS ********/

	/*---------------------------------------------*/
	/* INITIATES REFERENCE COMMAND WITH IDLE VALUE */
	/*---------------------------------------------*/

	/* In the case of the model, initialization of */
	/* RefCAN or even reference is made after the  */
	/* calculation of initial conditions, since    */
	/* the variable reference is directly used for */
	/* such */

	//RefCAN = ContConst.FNIdle;
	//reference = ContConst.FNIdle;			/* This line is to be executed only in the hardware */

	/* ================================================================================= */
	/* THE FOLLOWIN CODE MUST BE EXECUTED BY A TIMER ROUTINE OF THE HARDWARE IN THE LOOP */
	/* ================================================================================= */



	/* --------------------------------------------------------------------------------------------------- */
	/*   HARDWARE IN THE LOOP - Make sure to use the appropriate piece of code: MATLAB or actual hardware  */
	/* --------------------------------------------------------------------------------------------------- */

	/* ACTUAL HARDWARE */

	//if (HILMode == 1) {

	// /* Reads values of wf and digital inputs from CAN network */
	// fValue = (floating)model_mf;
	// fValue = fValue / 5 * WFMAX;
	// digital.bits.igniter = model_d1_toInt & 1;

	//}

   /* -------------------------------------------------- */
   /* UPDATING fValue & igniter - PWLM                   */
   /* (To be usedi in MATLAB (PWLM) simulations only)    */
   /* -------------------------------------------------- */

	if (HILMode != 0 && EngOutput.ICCalc != 0) {

		fValue = FuelIn;
		digital.bits.igniter = IgniterIn;
		OPRPM = OPRPMIn;

	}

    /* -------------------------------------------------- */
        
	/*--------------------*/
	/* MODEL CALCULATIONS */
	/*--------------------*/

	/* Input readings */
	Ignition = digital.bits.igniter;
	Wf = fValue;
	// RefCAN = (floating)reference;				/* This should be done in the hardware */
	/* -------------------------------------------------- */
	/* UPDATING RefCAN and FNpc - PWLM		              */
	/* (To be usedi in MATLAB (PWLM) simulations only)    */
	/* -------------------------------------------------- */

	// if (EngStatus.EngineStatus == 32 | ContInput.ThrustCommandOn > 0)
	// {
	// 	RefCAN = (floating)reference;
	// }

	/* -------------------------------------------------- */

	//FNpc = RefCAN;

	// /* Stores CAN fault bit value */
	// FaultSSys.SysFaults.CAN_0_Fault = CANFault.SysFaults.CAN_0_Fault;
	// FaultSSys.SysFaults.CAN_1_Fault = CANFault.SysFaults.CAN_1_Fault;

/******** SAVETO START: ENGINEMODEL ********/

	/* Updates FNpc and allows transition from IDLE to REGIME depending no reference value */
	IdleToRegime(&EngStatus, &ContInput, RefCAN, 0, ContConst.FNIdle, &FNpc, LeverMode);

	// mexPrintf("Outside PIMMRF.c: FNpc = %f\n", FNpc);
	/* Bearing 0 Model Inputs */
    Bear0.A = -0.1;//-0.5;
    Bear0.B = 1;
    Bear0.C = -0.1;//-0.5;
    Bear0.DelTExt = 0;
    Bear0.ElNumRPME = 3;
    Bear0.MaxRPMP = 4500;
    Bear0.Ts = TsamModel;

	/* Bearing 1 Model Inputs */
    Bear1.A = -0.1;//-0.5;
    Bear1.B = 1;
    Bear1.C = -0.1;//-0.5;
    Bear1.DelTExt = 0;
    Bear1.ElNumRPME = 3;
    Bear1.MaxRPMP = 4500;
    Bear1.Ts = TsamModel;

	/* Bearing 2 Model Inputs */
    Bear2.A = -0.1;//-0.5;
    Bear2.B = 1;
    Bear2.C = -0.1;//-0.5;
    Bear2.DelTExt = 0;
    Bear2.ElNumRPME = 3;
    Bear2.MaxRPMP = 4500;
    Bear2.Ts = TsamModel;

    /* Smulation of Engine BlowOut */
	BlowOutSim(&SysFaults, &Wf);

	/* Smulation of Ignition Fault */
	IgnitionFault(&SysFaults, &Ignition);
//mexPrintf("Executing Engine Model Loop\n");    
// mexPrintf("Wf=%f FuelIn=%f\n",Wf,FuelIn);
    for(i = 1; i < TsampDiv + 1; i++)
    {
        
	/* Calculates model outputs */
	EngineModel(&Ambient, &EngOutput, Wf,
		Altitude, MN, dT, Mwm, Ignition, NcMtx, Pt21Mtx, Pt3Mtx, Pt5Mtx, Pt6Mtx,
		Tt21Mtx, Tt3Mtx, Tt4Mtx, Tt5Mtx, Tt6Mtx, WfMtx, AMtx, BMtx,
		Pt21DMtx, Pt3DMtx, Pt5DMtx, Pt6DMtx, Tt21DMtx, Tt3DMtx, Tt4DMtx, Tt5DMtx, Tt6DMtx,
		NcFANMapMtx, WcFANMapMtx, WcFANStallMtx, PRFANMapMtx, PRFANStallMtx, EffFANMapMtx, 
		NcHPCMapMtx, WcHPCMapMtx, WcHPCStallMtx, PRHPCMapMtx, PRHPCStallMtx, EffHPCMapMtx,
		NcHPTMapMtx, WcHPTMapMtx, PRHPTMapMtx, EffHPTMapMtx, &EngPars,
		Mtx2D, Mtx2DH, Mtx1D, Mtx1DH, 
		MapFAN2D, MapFAN2DH, MapFAN1D, MapFAN1DH, MNLinVec,
		MapHPC2D, MapHPC2DH, MapHPC1D, MapHPC1DH,
        AwmMtx, AshMtx, BwmMtx, BshMtx, RPMwmMtx, RPMshMtx, 
        NcFANshMtx, Pt21shMtx, Pt21wmMtx,
		Pt21DshMtx, Pt21DwmMtx, Pt3shMtx, Pt3wmMtx,
		Pt3DshMtx, Pt3DwmMtx, Pt5shMtx, Pt5wmMtx, Pt5DshMtx, Pt5DwmMtx, Pt6shMtx, Pt6wmMtx, 
		Pt6DshMtx, Pt6DwmMtx, Tt21shMtx, Tt21wmMtx, Tt21DshMtx, Tt21DwmMtx,
		Tt3shMtx, Tt3wmMtx, Tt3DshMtx, Tt3DwmMtx, Tt4shMtx, Tt4wmMtx, Tt4CshMtx, Tt4DshMtx, Tt4DwmMtx, 
		Tt5shMtx, Tt5wmMtx, Tt5DshMtx, Tt5DwmMtx, Tt6shMtx, Tt6wmMtx, Tt6DshMtx, Tt6DwmMtx, WfshMtx, WfwmMtx,
        &Faults, &Sensors,
        TsamModel, ExtFPModel, FlightStart);

        /* Loads bearing varying data */
        Bear0.RPME = EngOutput.RPM;
        Bear0.RPMP = OPRPM;
        Bear0.RPMPss = 0;
        Bear0.Tss = 0;

        /* Loads bearing varying data */
        Bear1.RPME = EngOutput.RPM;
        Bear1.RPMP = OPRPM;
        Bear1.RPMPss = 0;
        Bear1.Tss = 0;

        /* Loads bearing varying data */
        Bear2.RPME = EngOutput.RPM;
        Bear2.RPMP = OPRPM;
        Bear2.RPMPss = 0;
        Bear2.Tss = 0;

		/* Correction of RPMEVec for adaptation to engines */
		RPMEVec[1] = ContConst.NDes * 20000 / 23000;
		RPMEVec[2] = ContConst.NDes;
		/* Bearings calculations */
		BearingModel(&Bear0, &RPMEVec[0], &TNOil_Bear0[0], &DelT_Bear0[0]);
	    BearingModel(&Bear1, &RPMEVec[0], &TNOil_Bear1[0], &DelT_Bear1[0]);
	    BearingModel(&Bear2, &RPMEVec[0], &TNOil_Bear2[0], &DelT_Bear2[0]);

		/* Updates engine outputs - should be done inside EnginModel in the future!! */
		EngOutput.TBear[0] = Bear0.Tout;
		EngOutput.TBear[1] = Bear1.Tout;
		EngOutput.TBear[2] = Bear2.Tout;

		/* FUEL PRESSURE AND OIL PRESSURE MODELS - Must be updated EngineModel in the future!! */

		/* The following fuel pressure equation is to be used whenever Wf < 0.5 * WfInit (Wf init is the value of the lower fuel pulse during ignitions) */
		if (Wf < 0.5 * ContConst.WfInit)
		{
			EngOutput.PFuel = ContConst.PFuelLow / 0.005 * Wf;
		}
		else
		{
			/* Updates PFuell model value, which becomes proportional to the fuel flow */
			EngOutput.PFuel = (ContConst.PFuelHigh - ContConst.PFuelLow) / (1.5 * ContConst.WfMax - 0.5 * ContConst.WfInit) * (Wf - 1.5 * ContConst.WfMax) + ContConst.PFuelHigh;
		}

		/* Updates POil model value, which becomes proportional to OPRPM */
		EngOutput.POil = ContConst.POilHigh * OPRPM / ContConst.OPRPMMax * 0.95;
		
		/* Limits the maximum oil pressure to 4 bar for avoiding DAC saturation during simulation with non-null initial conditions */
		EngOutput.POil = Min(EngOutput.POil,4*100000);
        
    }
//mexPrintf("\n");            
    /* Simulation of mechanical failures */
	SysFaultSim(&SysFaults, &EngPars, &EngOutput);
        
	/* Updates outputs */
	W2 = EngOutput.W2;
	Pt2 = EngOutput.Pt2;
    Ts2 = EngOutput.Ts2;
	Tt2 = EngOutput.Tt2;
	NcFAN = EngOutput.N2c;
	WcFAN = EngOutput.W2c;
	PRFAN = EngOutput.PRFAN;
	SMFAN = EngOutput.SMFAN;
	W21 = EngOutput.W21;
	Pt21 = EngOutput.Pt21;
	Tt21 = EngOutput.Tt21;
	NcHPC = EngOutput.N21c;
	WcHPC = EngOutput.W21c;
	PRHPC = EngOutput.PRHPC;
	SMHPC = EngOutput.SMHPC;
	Pt3 = EngOutput.Pt3;
	Tt3 = EngOutput.Tt3;
	Tt4 = EngOutput.Tt4;
	Wf = EngOutput.Wf;
	Pt5 = EngOutput.Pt5;
	Tt5 = EngOutput.Tt5;
	Pt6 = EngOutput.Pt6;
	Tt6 = EngOutput.Tt6;
	W8 = EngOutput.W8;
	V8 = EngOutput.V8;
	MN8 = EngOutput.MN8;
	Fn = EngOutput.Fn;
	Fg = EngOutput.Fg;
	RPM = EngOutput.RPM;
	POil = EngOutput.POil;
   
    /* Updates sensor values */
    SensorsUpdt(&Sensors, &EngOutput);

	/* Simulation of sensors faults */
    SensFaultSim(&SensFaults, &Sensors, &EngPars);
	
	/* Simulation of sensor bias */
	BiasFaultSim(&SysFaults, &SensorBias, &Sensors);

/******** SAVETO END: ENGINEMODEL ********/

    /* ---------------------------------------------------------------- */
    /* UPDATING bit_start - is done within a condition in HARDWARE CASE */
    /* (To be usedi in MATLAB (PWLM) simulations only)                  */
    /* ---------------------------------------------------------------- */
    
	bit_start = EngOutput.ICAuthorize;
    
    /* ---------------------------------------------------------------- */
    
/******** SAVETO START: CONTROLLER ********/

	/*----------------------*/
	/* SOFTWARE IN THE LOOP */
	/*----------------------*/

	/* Verifies if software in the loop is required */
    if(HILMode == 0 && bit_start == 1){
        
        /* CONTROL LOGIC - SOFTWARE IN THE LOOP */
        
        /* Simulates reading from each GPIO pin */
        GPIOIn = (KeyBit6 << 6) | (KeyBit5 << 5) | (KeyBit4 << 4) | (KeyBit3 << 3) | (KeyBit2 << 2) | (KeyBit1 << 1) | (KeyBit0 << 0);
        keys.in = GPIOIn & 0x7FF;

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

		/*------------------------*/
		/* CONTROL AND MONITORING */
        /*------------------------*/

		/* Reads word containing faults simulated by siftware */
    	SoftSimFaults.FaultBits = SensFaults.FaultBits;

		/* -------------------------------------------------- */
	    /* SIMULATION OF GPIO PINES - TMATS & PWLM            */
	    /* (To be usedi in MATLAB and TMATS simulations only) */
	    /* -------------------------------------------------- */
        
        /* Simulates reading from each GPIO pin */
        keys.in = GPIOIn & 0x7FF;

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
		EngOnOff.StartKey = 0;
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

		/*=====================================================================*/
		/*   START OF SSModelLoop.c AND PIMMRF_TJ1200.c IDENTICAL CODE PIECE   */
		/*																       */
		/*   NOTE: The following procedures must be accomplished for the       */
		/*         current versions of FADEC and HIL					       */
		/*			- The matrices in the FADEC are stored in strings, being   */
		/*        directly declared as so, i.e., floating Matrix(Size);    	   */
		/*			- The matrices in the HIL are stored with "alloc" command  */
		/*        and each matrix variable is a poiter for floating, i.e.,       */
		/*        floating *Matrix; 											   */
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
		EstIndex(&ModelPars, AltLinVec, MNLinVec,
				 Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
				 FNperContMtx, &ContConst, &Index3D);
        /* CALCULATION OF ENGINE MODEL Ts2 */

        /* Calculation of model ambient temperature */
        /* In this case, the structure ModelPars must be used - Open-Loop model */
		Ts2ModelCalc(Ts0Mtx, &ContConst,
					 Ts0Mtx2D, Ts0Mtx2DH, Ts0Mtx1D, Ts0Mtx1DH,
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
        Pt3 = Pt3MedVal;
        Tt4 = Tt4MedVal;
        RPM = RPMMedVal;

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
        InterpInd3DRPM(0, MN, 0.95, AltLinVec, MNLinVec, FNperContMtx, Mtx2D, Mtx2DH, Mtx1D, Mtx1DH, 1, MN_Elem, Fn_Elem, &Index3D);
		
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
		PIMinMaxRF(AltLinVec, MNLinVec, NcVec, ASVec, DSVec,
				   Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
				   DeltaMtx2D, DeltaMtx2DH, DeltaMtx1D, DeltaMtx1DH,
				   &ContConst, &ContStart, &ContInput, &ContOutput, &digitalWord, &keysWord,
				   DeltaMtx, NcFANContMtx, FNcMaxContMtx, FNperContMtx,
				   N_KpMtx, N_KpshMtx, N_KiMtx, N_KishMtx, Ts);                
        
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
        ModelCalc(&ModelPars, DeltaMtx,
                  AltLinVec, MNLinVec, &ContConst,
                  Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
                  DeltaMtx2D, DeltaMtx2DH, DeltaMtx1D, DeltaMtx1DH,
                  NcFANContMtx, Tt4Mtx, Pt3Mtx,
                  AMtx, BMtx, Tt4DMtx, Pt3DMtx,
                  WfMtx, Ts0Mtx,
                  Pt5Mtx, Pt5DMtx, Tt5Mtx, Tt5DMtx,
                  NcHPCMapMtx, WcHPCMapMtx, PRHPCMapMtx,
                  MapHPC1D, MapHPC1DH, MapHPC2D, MapHPC2DH);
        
        /* Calculates model for fuel lack */  
		ModelCalc(&BlowOutPars, DeltaMtx,
				  AltLinVec, MNLinVec, &ContConst,
				  Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
				  DeltaMtx2D, DeltaMtx2DH, DeltaMtx1D, DeltaMtx1DH,
				  NcFANContMtx, Tt4Mtx, Pt3Mtx,
				  AMtx, BMtx, Tt4DMtx, Pt3DMtx,
				  WfMtx, Ts0Mtx,
				  Pt5Mtx, Pt5DMtx, Tt5Mtx, Tt5DMtx,
				  NcHPCMapMtx, WcHPCMapMtx, PRHPCMapMtx,
				  MapHPC1D, MapHPC1DH, MapHPC2D, MapHPC2DH);

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
			PIMinMaxRF(AltLinVec, MNLinVec, NcVec, ASVec, DSVec,
					   Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
					   DeltaMtx2D, DeltaMtx2DH, DeltaMtx1D, DeltaMtx1DH,
					   &ContConst, &ContStModCL, &ContInModCL, &ContOutModCL, &digitalWord, &keysWord,
					   DeltaMtx, NcFANContMtx, FNcMaxContMtx, FNperContMtx,
					   N_KpMtx, N_KpshMtx, N_KiMtx, N_KishMtx, Ts);

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
		ModelCalc(&ModelParsCL, DeltaMtx,
				  AltLinVec, MNLinVec, &ContConst,
				  Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
				  DeltaMtx2D, DeltaMtx2DH, DeltaMtx1D, DeltaMtx1DH,
				  NcFANContMtx, Tt4Mtx, Pt3Mtx,
				  AMtx, BMtx, Tt4DMtx, Pt3DMtx,
				  WfMtx, Ts0Mtx,
				  Pt5Mtx, Pt5DMtx, Tt5Mtx, Tt5DMtx,
				  NcHPCMapMtx, WcHPCMapMtx, PRHPCMapMtx,
				  MapHPC1D, MapHPC1DH, MapHPC2D, MapHPC2DH);

        /*===============================================================*/
        /* END OF SSModelLoop.c AND PIMMRF_TJ1200.c IDENTICAL CODE PIECE */
        /*                                                               */
        /* NOTE: The codes are to be identical except for the considera- */
        /*       tions mentioned at the note above                       */
        /*===============================================================*/

		/*---------------------------------------*/
		/* UPDATES PRESENT ONLY ON MODEL (MATLAB)*/
		/*---------------------------------------*/

		/* UPDATES Wf AND fValue - THE VARIABLE fValue MUST BE REPLACED BY Wf IN FUTURE VERSIONS*/
		ContOutput.fValue = Wf;
		ContOutput.FiltRef = ContOutput.MinRef;
		/* Updates digital outputs and fuel flow value */
		digital.out = digitalWord;
		fValue = ContOutput.fValue;
	}

/******** SAVETO END: CONTROLLER ********/

	// /*---------------------------------------*/
	// /* UPDATES PRESENT ONLY ON MODEL (MATLAB)*/
	// /*---------------------------------------*/

	// /* UPDATES Wf AND fValue - THE VARIABLE fValue MUST BE REPLACED BY Wf IN FUTURE VERSIONS*/
	// ContOutput.fValue = Wf;
	// ContOutput.FiltRef = ContOutput.MinRef;
	// /* Updates digital outputs and fuel flow value */
    // digital.out = digitalWord;
    // fValue = ContOutput.fValue;


	/* ------------------------------------------------- */
    /* UPDATING OUTPUT - PWLM & TMATS                    */
    /* (To be usedi in MATLAB (PWLM) simulations only)   */              
    /* ------------------------------------------------- */

	/* Writes SIMULINK outputs */
	Iout[0] = EngOutput.W2;		
	Iout[1] = EngOutput.Pt2;
	Iout[2] = EngOutput.Tt2;
	Iout[3] = EngOutput.N2c;//NcFAN;
	Iout[4] = EngOutput.W2c;//WcFAN;
	Iout[5] = EngOutput.PRFAN;
	Iout[6] = EngOutput.SMFAN;
	Iout[7] = EngOutput.BPFAN;
	Iout[8] = EngOutput.W21;
	Iout[9] = EngOutput.Pt21;
	Iout[10] = EngOutput.Tt21;
	Iout[11] = EngOutput.N21c;//NcHPC;
	Iout[12] = EngOutput.W21c;//WcHPC;
	Iout[13] = EngOutput.PRHPC;
	Iout[14] = EngOutput.SMHPC;
	Iout[15] = EngOutput.Pt3;
	Iout[16] = EngOutput.Tt3;
	Iout[17] = EngOutput.Tt4;
	Iout[18] = EngOutput.WfPumpOut;//fValue; 					/* Model fuel flow input - controller command */
	Iout[19] = EngOutput.Pt5;
	Iout[20] = EngOutput.Tt5;
	Iout[21] = EngOutput.Pt6;
	Iout[22] = EngOutput.Tt6;
	Iout[23] = EngOutput.W8;
	Iout[24] = EngOutput.MN8;
	Iout[25] = EngOutput.Fn;
	Iout[26] = EngOutput.Fg;
	Iout[27] = EngOutput.RPM;
	Iout[28] = EngOutput.POil;
	Iout[29] = Ignition;				/* Model Ignition Input */
	Iout[30] = ContOutput.RPMRef;
	Iout[31] = ContOutput.FiltRef;
	Iout[32] = ContOutput.Active;
	Iout[33] = OPRPM;

	Init[0] = Wf0;
	Init[1] = SkipStart;
	Init[2] = EngOutput.ICAuthorize;
    
    /* Simulation of sensors - SIMULINK Output */
    
    /* Station 2 */
    ISens[0] = Sensors.Ts2[0];
    ISens[1] = Sensors.Ts2[1];
    /* Station 3 */
    ISens[2] = Sensors.Pt3[0];
    /* Station 4 */
    ISens[3] = Sensors.Tt4[0];
    ISens[4] = Sensors.Tt4[1];
    ISens[5] = Sensors.Tt4[2];
    /* Shaft */
    ISens[6] = Sensors.RPM[0];
    ISens[7] = Sensors.RPM[1];
    /* POil */
    ISens[8] = Sensors.POil[0];
    /* PFuel */
    ISens[9] = Sensors.PFuel[0];
    /* Vibrabion */
    ISens[10] = Sensors.Vibration[0];
	/* Bearings Temp */
	ISens[11] = Sensors.TBear[0];
	ISens[12] = Sensors.TBear[1];
	ISens[13] = Sensors.TBear[2];

	/* Output for Normal Model */
	IoutModel[0] = ModelPars.RPM;
    IoutModel[1] = ModelPars.Tt4 * (floating)StartFaultAnalysis;
    IoutModel[2] = ModelPars.Pt3;
    IoutModel[3] = ModelPars.WfOutfp;//Tt2;//ModelPars.MNth;
    /* Output for Fuel Lack Model */
    IoutBlowOut[0] = BlowOutPars.RPM;
    IoutBlowOut[1] = BlowOutPars.Tt4;
    IoutBlowOut[2] = BlowOutPars.Pt3;
    IoutBlowOut[3] = BlowOutPars.Tt2;
	/* Output for closed loop Model */
	IoutModelCL[0] = ModelParsCL.RPM;
    IoutModelCL[1] = ModelParsCL.Tt4;
    IoutModelCL[2] = ModelParsCL.Pt3;
    IoutModelCL[3] = ModelParsCL.WfOutfp;
	/* Output from sensor model */
	IoutSensModel[0] = EngOutput.Ts2Sensed;
	IoutSensModel[1] = EngOutput.Pt3Sensed;
	IoutSensModel[2] = EngOutput.Tt4Sensed;
	IoutSensModel[3] = EngOutput.WfPumpOut;

    /* ---------------------------------------------------------------- */

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
