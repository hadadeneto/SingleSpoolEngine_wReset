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

#define S_FUNCTION_NAME  FuelPumpCL_TJ1200_TestBench
#define S_FUNCTION_LEVEL 2


#include <math.h>
#include <stdio.h>
#include <string.h>



//#define pi 3.14

/*
 * Need to include simstruc.h for the definition of the SimStruct and
 * its associated macro definitions.
 */
#include "simstruc.h"

/* GENERAL INCLUDES */

// #include "MtxIntFunctions.h"		
// #include "Interpolation_Types.h"
// #include "LinMtxFunctions.h"
// #include "Env_SampTime.h"

/* INCLUDES FUNCTIONS AND CONSTANTS CORRESPONDING TO CURRENT ENGINE */
/*TJ1200*/

#include "ConstantsTJ1200.h"

// /* AMBIENT CALCULATIONS INCLUDES */
// 
// #include "functions_TMATS.h"
// #include "constants_TMATS.h"
// #include "Ambient_TMATS.h"
// 
// /* MODEL TYPES */
// #include "Model_Types.h"

/* CONTROLLER INCLUDES */

#include "Control_Types.h"
#include "ControlFunctions.h"
// #include "IO_Types.h"
// #include "StartingFunctions.h"
// #include "DigitalOutDefs.h"
// #include "PIMinMaxRF.h"
// #include "ShutDownFunctions.h"

/* FAULT ANALYSIS INCLUDES */

// #include "FaultSim_Types.h"
// #include "TCFault.h"
// #include "FailSafeFunctions.h"

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

	ssSetInputPortWidth(S, 0, 19);
	ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/

    ssSetInputPortWidth(S, 1, 1);
	ssSetInputPortRequiredContiguous(S, 1, true); /*direct input signal access*/
    
    ssSetInputPortWidth(S, 2, 11);
	ssSetInputPortRequiredContiguous(S, 2, true); /*direct input signal access*/
    
    ssSetInputPortWidth(S, 3, 1);
	ssSetInputPortRequiredContiguous(S, 3, true); /*direct input signal access*/

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
    
    

	if (!ssSetNumOutputPorts(S, 3)) return;
	ssSetOutputPortWidth(S, 0, 6);
    ssSetOutputPortWidth(S, 1, 4);
    ssSetOutputPortWidth(S, 2, 4);


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
    real_T       *Iout = ssGetOutputPortSignal(S, 0);
    real_T       *IoutModel = ssGetOutputPortSignal(S, 1);
    real_T       *IoutBlowOut = ssGetOutputPortSignal(S, 2);
    
    /* --------------------------------------------------- */

    /* -------------------------------------------------- */
	/* AUXILIARY VARIABLE - T-MATS                        */
	/* (To be usedi in MATLAB and TMATS simulations only) */
	/* -------------------------------------------------- */
    
    static int tick = 0;
    static int tack = 1;
    int TMATS_StartComplete = 0;
    static double Out0;//Wf//fvalue
    static double Out1;//active
    static int    Out2;//igniter
    static double Out3;//rpmref
    static double Out4;//filterRef
    static double Out5;//engine operating status
    
    /* -------------------------------------------------- */
    
    
    /* -------------------------------------------------- */
	/* AUXILIARY VARIABLE - DEBUGGING TOOLS               */
	/* (To be usedi in MATLAB and TMATS simulations only) */
	/* -------------------------------------------------- */
    
    /* The followoing variable is used for facilitating the
     use of some debugging tools, such as VSCode, which may 
     need to be restarted after all break points are deleted*/
    static int SingleStop = 0;
    
    /* -------------------------------------------------- */
    
	/* VARIABLES SIMULATING EXTERNAL KEYS */

	/* The variable below is declared outside the main loop */
	unsigned int GPIOIn = 0;	
	/* Input Keys for software in the loop simulation*/
	unsigned int KeyBit0 = 1; //Igniter		
	unsigned int KeyBit1 = 1; //Shut_Off	 
	unsigned int KeyBit2 = 0; //Scaveng		
	unsigned int KeyBit3 = 1; //Oil Pump	
	unsigned int KeyBit4 = 0; //AC_Drive	
	unsigned int KeyBit5 = 1; //Emergency	
	unsigned int KeyBit6 = 0; //Mode		

	/* ---------------------------- */
	/* DECLARATION OF CAN VARIABLES */
	/* ---------------------------- */

	double reference = 0.35;	

	/* ------------------------------ */
	/* DECLARATION OF FADEC VARIABLES */
	/* ------------------------------ */

	/* Operating Mode */
	int Mode = 0;		
	/* Lever Mode */
	int LeverMode;	
    /* Engineering units for thrust referenc*/
    int EngUnits;
    
	/* Starting keys */
	static int Current_key_start;	
	static int Old_key_start;		

	/* DECLARATION OF STRUCTURES */

	/* Declares structures for controller input and controller output */
    static ControllerConstants ContConst;
    ControllerConstants ContConstEmpty = {0};

	// static ControlStart ContStart;
    // static ControlStart ContStartEmpty = {0};

	static ControllerInput ContInput;		
    static ControllerInput ContInputEmpty = {0};

	static ControllerOutput ContOutput;
    static ControllerOutput ContOutputEmpty = {0};
         
	/* COMMONLY USED VARIABLES */

	double FNpc = 0;	
    double FNcMax = 0;
	double RefCAN = 0;	
    static double Wf = 0;	

	/* Mechanical Rotation Speed*/
	double RPM;		

	/* VARIABLES TO BE USED BY HIL ENGINE MODEL */

	/* Flag indicating if starting algorithm is needed */
	static int SkipStart = 0;
    /* Flag indicating if model parameters initiation is needed */
    static int ModelParsStart = 0;
	/* Flag indicating that controller is authorized to perform */
	int Authorize;
	/* Reset flag and pulse detection variable */
	static int Reset = 0;
	static int ResetButton[2] = {0, 0}; 
	/* Initial fuel flow value */
	double Wf0;

    /* Thermocouple value when opened */
    double TCOpen = 0;//ContConst.TCOpen;
    
    /* Sampling Time */
    double Ts = 200 * 0.001;//0.001 * TICK;

    /* Dummy timer for general purposes */
    double AuxTimer;

    /* --------------------------------------------------------------- */
	/* THIS VARIABLE IS USED FOR SIMULATING A SINGLE READ OF SkipStart */
	/* (To be usedi in MATLAB and TMATS simulations only)              */
	/* --------------------------------------------------------------- */

    static int SkipStartIn[2] = {0,0};

	/* --------------------------------------------------------------- */

	/*=======================================================*/
	/* PIECE OF CODE TO BE EXECUTED WITHIN THE MAIN FUNCTION */
	/*=======================================================*/
    
    
    /* -------------------------------------------------- */
	/* SINGLE STOP FOR SETTING TO ZERO STATIC STRUCTURES  */
	/* (To be usedi in MATLAB and TMATS simulations only) */
	/* -------------------------------------------------- */
    
    if(SingleStop == 0)
    {
        SingleStop = 1;

        /* SETS ALL STRUCTS TO ZERO */
 
		/* Initializes structs with null values */
		//ContStart = ContStartEmpty;
		ContInput = ContInputEmpty;
		ContOutput = ContOutputEmpty;
		ContConst = ContConstEmpty;

    } 
    
    /* -------------------------------------------------- */
    
// 	/* ================================================================================= */
// 	/* THE FOLLOWIN CODE MUST BE EXECUTED BY A TIMER ROUTINE OF THE HARDWARE IN THE LOOP */
// 	/* ================================================================================= */
//     
//  /* -------------------------------------------------- */
// 	/* AUXILIARY VARIABLE - TMATS                         */
// 	/* (To be usedi in MATLAB and TMATS simulations only) */
// 	/* -------------------------------------------------- */
//     
//     TMATS_StartComplete = InputTMATS[0];
//     
//     /* -------------------------------------------------- */
// 	
    /* ---------------------------------------- */
	/* INPUT READINS - T-MATS & PWML            */
	/* (To be usedi in MATLAB simulations only) */
	/* ---------------------------------------- */

	/* Reads tick value - FOR USE WITH T-MATS ONLY. COMMENT IF HARDWARE*/
	tack = tick;
	tick = InputVars[18];

    /* Reads RPM Value */
    RPM = InputVars[0];
    /* Reads reference value */
    FNpc = InputVars[1];
    /* Reads functioning mode */
    /*
    Mode = 0 -> Closed-Loop
    Mode = 1 -> Open-Loop
    */
    Mode = InputVars[17];

    /* -------------------------------------------------- */

	/*---------------*/
	/* CONTROL LOGIC */
	/*---------------*/
   
    /* -------------------------------------------------- */
	/* EXTERNAL SAMPLING TIME - TMATS & PWLM              */
	/* (To be usedi in MATLAB and TMATS simulations only) */
	/* -------------------------------------------------- */
    
    Authorize = 0;
    if (tick != tack) {
        Authorize = 1;
    }
    
    /*----------------------------------------------------*/
    
    /* Checks for authorization of controller calculations */
    if(Authorize == 1)
    {

        /*-----------------------*/
        /* FUEL PUMP CONTROL LAW */
        /*-----------------------*/
                
        /* Updates Controller Inputs */
         ContInput.Mode = Mode;
         ContInput.FNpc = FNpc;
         ContInput.RPM = RPM;

        /* Fuel Pump Control Law */
        PIFuelPump(&ContConst, &ContInput, &ContOutput, Ts);
         
        /* Updates fuel flow value */
        Wf = ContOutput.Wf;
  
               
        /* -------------------------------------------------- */
        /* AUXILIARY VARIABLE - PWLM                          */
        /* (To be usedi in MATLAB and TMATS simulations only) */
        /* -------------------------------------------------- */
        
        Out0 = Wf;
        Out1 = ContOutput.Active;
        Out2 = ContOutput.RPMRef;
        Out3 = ContOutput.MinRef;
                
        /* -------------------------------------------------- */


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
    
    IoutModel[0] = 0;//ModelPars.RPM;
    IoutModel[1] = 0;//ModelPars.Tt4;
    IoutModel[2] = 0;// ModelPars.Pt3;
    IoutModel[3] = 0;//ModelPars.WfOutfp;
    
    IoutBlowOut[0] = 0;//BlowOutPars.RPM;
    IoutBlowOut[1] = 0;//BlowOutPars.Tt4;
    IoutBlowOut[2] = 0;//BlowOutPars.Pt3;
    IoutBlowOut[3] = 0;//BlowOutPars.Tt2;
    
    /*---------------------------------------------*/

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
