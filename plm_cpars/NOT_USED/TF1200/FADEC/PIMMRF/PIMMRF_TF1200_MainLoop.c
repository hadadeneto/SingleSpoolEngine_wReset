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

#define S_FUNCTION_NAME  PIMMRF_TF1200_MainLoop
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

#include "MtxIntFunctions.h"		
#include "Interpolation_Types.h"
#include "LinMtxFunctions.h"
#include "Env_SampTime.h"

/* INCLUDES FUNCTIONS AND CONSTANTS CORRESPONDING TO CURRENT ENGINE */
/*TF1200*/
#include "PIMinMaxTF1200.h"
#include "ConstantsTF1200.h"


/* CONTROLLER INCLUDES */

#include "Control_Types.h"
#include "ControlFunctions.h"
#include "IO_Types.h"
#include "StartingFunctions.h"
#include "DigitalOutDefs.h"


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

	if (!ssSetNumInputPorts(S, 1)) return;

	ssSetInputPortWidth(S, 0, 14);
	ssSetInputPortRequiredContiguous(S, 0, true); /*direct input signal access*/

	/*
	 * Set direct feedthrough flag (1=yes, 0=no).
	 * A port has direct feedthrough if the input is used in either
	 * the mdlOutputs or mdlGetTimeOfNextVarHit functions.
	 */
	ssSetInputPortDirectFeedThrough(S, 0, 1);

	if (!ssSetNumOutputPorts(S, 1)) return;
	ssSetOutputPortWidth(S, 0, 5);


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
	real_T       *Iout = ssGetOutputPortSignal(S, 0);

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

	/* STARTING ROUTINE */

	/* Starting Routine Structs */
	static digital_t digital;	
	static const digital_t digitalEmpty = { 0 };
	keys_t keys;	

	/* Operating Mode */
	int Mode;		
	/* Lever Mode */
	int LeverMode;	

	/* Starting keys */
	static int Current_key_start;	
	static int Old_key_start;		

	/* CLOSED-LOOP ROUTINE - SOFTWARE IN THE LOOP */

	//Declares structures for controller input and controller output
	ControlStart ContStart;
	ControllerInput ContInput;		
	ControllerOutput ContOutput;	

	/* COMMONLY USED VARIABLES */

	double FNpc = 0;	
	double RefCAN = 0;	
	static double fValue = 0;	
	int keysWord;	
	int digitalWord;	

	/*  OBSERVED ENGINE VARIABLES */

	/* Variables read from the GUI */
	double Altitude = 0;
	double MN = 0;
	double Tt2;
	/* Compressor Exhaust */
	double Pt3;			
	double Tt5;		
	/* Bearings Cooling */
	double POil = 0;
	/* Ignition Signal */
	int Ignition = 0;
	/* Mechanical Rotation Speed*/
	double RPM;		

	/* VARIABLES TO BE USED BY ENGINE MODEL */

	/* Flag indicating if starting algorithm is needed */
	int SkipStart;
	/* Flag indicating that controller is authorized to perform */
	int Authorize;
	/* Reset flag and pulse detection variable */
	static int Reset = 0;
	static int ResetButton[2] = {0, 0}; 
	/* Initial fuel flow value */
	double Wf0;
	   
	/* MATRICES USED BY ENGINE PI CONTROLLER */

	/* Matrices used for gain calculations */
	double N_KiMtx[TF1200_TOTAL_ELEM];	
	double N_KpMtx[TF1200_TOTAL_ELEM];	
	/* Matrices used for reference calculations */
	double NcFANContMtx[TF1200_TOTAL_ELEM];	
	double FNperContMtx[TF1200_TOTAL_ELEM];
        
    /* Sampling Time */
    double Ts = 0.001 * TICK;

	/*=======================================================*/
	/* PIECE OF CODE TO BE EXECUTED WITHIN THE MAIN FUNCTION */
	/*=======================================================*/

	/* LOADING OF CONTROLLER MATRIX */
	getTF1200N_KpMtx(&N_KpMtx);
	getTF1200N_KiMtx(&N_KiMtx);
	getTF1200NcFANContMtx(&NcFANContMtx);
	getTF1200FNperContMtx(&FNperContMtx);

	/* LOADING OF CONTROLLER STARTING PARAMETERS */
	getTF1200StartPars(&ContStart);

	/* ================================================================================= */
	/* THE FOLLOWIN CODE MUST BE EXECUTED BY A TIMER ROUTINE OF THE HARDWARE IN THE LOOP */
	/* ================================================================================= */

	/* ---------------------------------------- */
	/* INPUT READINS FOR MATLAB SIMULAITON      */
	/* (To be usedi in MATLAB simulations only) */
	/* ---------------------------------------- */

	Altitude = InputVars[0];
	MN = InputVars[1];
	Tt2 = InputVars[2];
	Pt3 = InputVars[3];
	Tt5 = InputVars[4];
	RPM = InputVars[5];
	reference = InputVars[6];
	POil = InputVars[7];
	SkipStart = InputVars[8];
	Authorize = InputVars[9];
	Wf0 = InputVars[10];
	ResetButton[0] = InputVars[11];

	/* Reads mode key */
	Mode = InputVars[12];
	LeverMode = InputVars[13];


	/*-------------------------*/
	/* RESET REQUEST TREATMENT */
	/*-------------------------*/

	/* Reads reset signal */
	Reset = Edge(ResetButton);
	ResetButton[1] = ResetButton[0];

	/* Verifies if reset has been requested */
	if (Reset == 1) 
	{
		/* Resets static structs and variables */
		digital = digitalEmpty;
		Current_key_start = 0;
		Old_key_start = 0;
		fValue = 0;

		/* Disable controller actuation untill authorized by model */
		Authorize = 0;

		/* Indicates reset request to the controller */
		ContInput.Reset = 1;

		/* Sets reset flag to 0 */
		Reset = 0;
	}

	/*-----------------------------------------------*/
	/* UPDATES REFERENCE FOR CONTROL LAW CALCULATION */
	/*-----------------------------------------------*/

	//Ignition = digital.bits.igniter;
	RefCAN = (double)reference;
	FNpc = RefCAN;

	/*---------------*/
	/* CONTROL LOGIC */
	/*---------------*/
    
    /* Checks for authorization of controller calculations */
    if(Authorize == 1)
    {
        
		/* SIMULATION OF GPIO PINS - MATLAB only */

        /* Simulates reading from each GPIO pin */
        GPIOIn = (KeyBit6 << 6) | (KeyBit5 << 5) | (KeyBit4 << 4) | (KeyBit3 << 3) | (KeyBit2 << 2) | (KeyBit1 << 1) | (KeyBit0 << 0);
        keys.in = GPIOIn & 0x7FF;
        
		/* THE FOLLOWING CODE IS REPRODUCED ALSO IN THE REAL HARDWARE */

        /* Reads start key - pulse detection */
        Old_key_start = Current_key_start;
        Current_key_start = !keys.bits.ac_drive_key || Authorize;
                
        /* Updates Controller Inputs */
        ContInput.Old_key_start = Old_key_start;
        ContInput.Current_key_start = Current_key_start;
        ContInput.bits_inverter = digital.bits.inverter;
        ContInput.Mode = Mode;
        ContInput.LeverMode = LeverMode;
        ContInput.Altitude = Altitude;
        ContInput.MN = MN;
        ContInput.Tt2 = Tt2;
        ContInput.Pt3 = Pt3;
        ContInput.Tt5 = Tt5;
        ContInput.FNpc = FNpc;
        ContInput.RPM = RPM;
        ContInput.POil = POil;
        ContInput.SkipStart = SkipStart;
        ContInput.Wf0 = Wf0;
        keysWord = keys.in;
        
        /* Calculates fuel flow from control law */
        PIMinMaxTF1200(&ContStart, &ContInput, &ContOutput, &digitalWord, &keysWord,
					   NcFANContMtx, FNperContMtx, N_KpMtx, N_KiMtx, Ts);
        
        /* Updates digital outputs and fuel flow value */
        digital.out = digitalWord;
        fValue = ContOutput.fValue;
        
    }

	/*---------------------------------------------*/
	/* UPDATES OUTPUTS - To be used in MATLAB only */
	/*---------------------------------------------*/

	/* Writes SIMULINK outputs */
	Iout[0] = fValue;
	Iout[1] = ContOutput.Active;
	Iout[2] = digital.bits.igniter;
	Iout[3] = ContOutput.RPMRef;
	Iout[4] = ContOutput.FiltRef;

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
