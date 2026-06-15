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
/*TJ1200*/

#include "ConstantsTJ1200.h"

/* AMBIENT CALCULATIONS INCLUDES */

#include "functions_TMATS.h"
#include "constants_TMATS.h"
#include "Ambient_TMATS.h"

/* MODEL TYPES */
#include "Model_Types.h"

/* CONTROLLER INCLUDES */

#include "Control_Types.h"
#include "ControlFunctions.h"
#include "IO_Types.h"
#include "StartingFunctions.h"
#include "DigitalOutDefs.h"
#include "PIMinMaxRF.h"
#include "ShutDownFunctions.h"

/* FAULT ANALYSIS INCLUDES */

#include "FaultSim_Types.h"
#include "TCFault.h"
#include "FailSafeFunctions.h"

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

	/* STARTING ROUTINE */

	/* Starting Routine Structs */
	static digital_t digital;	
	static digital_t digitalEmpty = { 0 };
	static keys_t keys;	
    static keys_t keysEmpty = {0};

	/* Operating Mode */
	int Mode;		
	/* Lever Mode */
	int LeverMode;	
    /* Engineering units for thrust referenc*/
    int EngUnits;
    
	/* Starting keys */
	static int Current_key_start;	
	static int Old_key_start;		

	/* DECLARATION OF STRUCTURES */

    /* Structure for ambient Calculations */
    static AmbientPars Ambient;
    static AmbientPars AmbientEmpty = { 0 };

	/* Declares structures for controller input and controller output */
    static ControllerConstants ContConst;
    ControllerConstants ContConstEmpty = {0};

	static ControlStart ContStart;
    static ControlStart ContStartEmpty = {0};

	static ControllerInput ContInput;		
    static ControllerInput ContInputEmpty = {0};

	static ControllerOutput ContOutput;
    static ControllerOutput ContOutputEmpty = {0};

    /* Declares structure for on/off logic */
	static EngineOnOff EngOnOff;
	static EngineOnOff EngOnOffEmpty = {0};
    
    /* Declared structure for fail-safe control implementation */
    static EstimatedPars ModelPars;
    static EstimatedPars BlowOutPars;
    static EstimatedPars EstParsEmpty = {0};

    /* Index variable */
    static InterpIndex3D Index3D;
    static InterpIndex3D Index3DEmpty = {0};

    static SensedPars Sensors;
    static SensedPars SensorsEmpty = {0};

    /* Union used for sending engine fault status */
    static EngineFaults FaultStatus;
    static EngineFaults FaultWarning;   
    static EngineFaults FaultEmpty = {0};
     
    /* Union used for software fault simulation */
    static SensorFaults SoftSimFaults;
    static SensorFaults FaultSSens;
    static SensorFaults FaultWSens;
    static SensorFaults FaultSensEmpty = {0};
    SoftSimFaults = FaultSensEmpty;
    
    /* Union used for fault analysis */
    static SystemFaults FaultSSys;
    static SystemFaults FaultWSys;
    static SystemFaults FaultSysEmpty = {0};

    /* Union used for fault analysis */
    static ModelParsFault ModPFault;
    //ModPFault.ModParsBits = 0;
    
    /* Unions containing more general information about sensor faults */
    static FaultDetect HardFStatus;
    static FaultDetect SoftFStatus;
    static FaultDetect ExistFStatus;
    static FaultDetect HardFWarning;
    static FaultDetect SoftFWarning;
    static FaultDetect ExistFWarning;
    static FaultDetect TrustSens;
    static FaultDetect TrustHard;
    static FaultDetect FaultDetectEmpty = {0};

    /* Union containing engine status */
    static EngineStatus EngStatus;
    static EngineStatus EngStatusEmpty = {0};
    
    /* Union containing thermocouple faults */
    TCFaults Ts2_0; 
    TCFaults Ts2_1; 
    TCFaults Tt4_0; 
    TCFaults Tt4_1; 
    TCFaults Tt4_2;
    
    /* Each union is initiated with null values */
    Ts2_0.TCFaultBits = 0;
    Ts2_1.TCFaultBits = 0;
    Tt4_0.TCFaultBits = 0;
    Tt4_1.TCFaultBits = 0;
    Tt4_2.TCFaultBits = 0;
            
    static AllResiduals Ts2Res;      
    static AllResiduals Pt3Res;
    static AllResiduals Tt4Res;
    static AllResiduals RPMRes;
    static AllResiduals POilRes;
    static AllResiduals PFuelRes;
    static AllResiduals VibrationRes;
    static AllResiduals DefaultRes = {1000000};
         
	/* COMMONLY USED VARIABLES */

	double FNpc = 0;	
    double FNcMax = 0;
	double RefCAN = 0;	
	//static double fValue = 0;
    static double Wf = 0;	
	int keysWord;	
	int digitalWord;
    static int EmergencyCommand = 0;	
    static int ShutDownCommand = 0;
    static int StartCommand = 0;
    static int CriticalFailure = 0;
    static int EmergShutDwn = 0;
    static int OnOffCom = 0xFF;

	/*  OBSERVED ENGINE VARIABLES */

    /* Medium value of each main sensored variable */
    double Ts2MedVal = 288.15;
    double Pt3MedVal = 0;
    double Tt4MedVal = 0;
    double RPMMedVal = 0;

	/* Variables read from the GUI */
	double Altitude = 0;
	double MN = 0;
    double dT = 0;
    double Ts2 = 288.15;
	double Tt2;
    double Pt2;
    double Delta;
	/* Compressor Exhaust */
	double Pt3;	
    double Tt4;
	double Tt5;		
	/* Bearings Cooling */
	double POil = 0;
	/* Ignition Signal */
	int Ignition = 0;
	/* Mechanical Rotation Speed*/
	double RPM;		

    /* CONTROLLER OUPTUTS UPDATED EXCLUSIVELLY DURING START PHASE */
    static int ControlPhase = 0;
    static int IgnitionFail = 0;
    static int StartComplete = 0;
    static int StartFaultAnalysis = 0;

	/* GENERAL PROPOSE TIMER */
	double WaitTime;

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

    /* MN AND THRUST MATRICES ELEMENTS */
    int MN_Elem = TJ1200_MN_ELEM;
    int Fn_Elem = TJ1200_FN_ELEM;
	   
	/* MATRICES USED BY ENGINE PI CONTROLLER */

	/* Matrices used for gain calculations */
	double N_KiMtx[TJ1200_TOTAL_ELEM];	
	double N_KpMtx[TJ1200_TOTAL_ELEM];	
    
    /* Matrices used for model estimation */
    double Ts0Mtx[TJ1200_ALT_ELEM];
    
	/* Matrices used for reference calculations */
    double DeltaMtx[TJ1200_ALT_ELEM * TJ1200_MN_ELEM];
    double FNcMaxContMtx[TJ1200_MN_ELEM];
	double NcFANContMtx[TJ1200_TOTAL_ELEM];	
	double FNperContMtx[TJ1200_TOTAL_ELEM];  
    
    /* Matrices used for model estimation */
    double AMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];
    double BMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];
    double Pt3DMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];
    double Pt5DMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];
    double Tt4DMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];
    double Tt5DMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];
    double Pt3Mtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];
    double Pt5Mtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];
    double Tt4Mtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];
    double Tt5Mtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];
    double WfMtx[TJ1200_MN_ELEM * TJ1200_FN_ELEM];
	double NcHPCMapMtx[TJ1200_FAN_NC];
	double WcHPCMapMtx[TJ1200_FAN_NC * TJ1200_FAN_PR];
	double PRHPCMapMtx[TJ1200_FAN_NC * TJ1200_FAN_PR];
    
    /* Auxiliary matrices */
    double Mtx2D[TJ1200_MN_ELEM * TJ1200_FN_ELEM];
	double Mtx2DH[TJ1200_MN_ELEM * TJ1200_FN_ELEM];
	double Mtx1D[TJ1200_FN_ELEM];
	double Mtx1DH[TJ1200_FN_ELEM];
    double MapHPC2D[TJ1200_FAN_NC * TJ1200_FAN_PR];
	double MapHPC2DH[TJ1200_FAN_NC * TJ1200_FAN_PR];
	double MapHPC1D[TJ1200_FAN_PR]; 
	double MapHPC1DH[TJ1200_FAN_PR]; 
    
    /* Matrices for delta calculation */
    double DeltaMtx2D[TJ1200_ALT_ELEM * TJ1200_MN_ELEM];
    double DeltaMtx2DH[TJ1200_ALT_ELEM * TJ1200_MN_ELEM];
    double DeltaMtx1D[TJ1200_MN_ELEM];
    double DeltaMtx1DH[TJ1200_MN_ELEM];
    
    double Ts0Mtx2D[TJ1200_FN_ELEM];
	double Ts0Mtx2DH[TJ1200_FN_ELEM];
	double Ts0Mtx1D[TJ1200_ALT_ELEM];
	double Ts0Mtx1DH[TJ1200_ALT_ELEM];
    
    /* Vectors containing breakpoints */
    double AltLinVec[TJ1200_ALT_ELEM];
    double MNLinVec[TJ1200_MN_ELEM];
    double NcVec[TJ1200_AS_ELEM];
    double ASVec[TJ1200_AS_ELEM];

    /* Thermocouple value when opened */
    double TCOpen = ContConst.TCOpen;
    
    /* Sampling Time */
    double Ts = 0.001 * TICK;

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

		/* Ambient Structure */
		Ambient = AmbientEmpty;

		/* Digital IO */
		digital = digitalEmpty;
		keys = keysEmpty;

		/* Initializes structs with null values */
		ContStart = ContStartEmpty;
		ContInput = ContInputEmpty;
		ContOutput = ContOutputEmpty;
		EngOnOff = EngOnOffEmpty;
		/* Engine sensors */
		Sensors = SensorsEmpty;
		/* Interpolation Structure */
		Index3D = Index3DEmpty;
		/* Sets Controller Constants to zero */
		ContConst = ContConstEmpty;
		/* Declared structure for fail-safe control implementation */
		ModelPars = EstParsEmpty;
		BlowOutPars = EstParsEmpty;
		/* Union used for sending engine fault status */
		FaultStatus = FaultEmpty;
		FaultWarning = FaultEmpty;
		/* Union used for software fault simulation */;
		FaultSSens = FaultSensEmpty;
		FaultWSens = FaultSensEmpty;
		SoftSimFaults = FaultSensEmpty;
		/* Union used for fault analysis */
		FaultSSys = FaultSysEmpty;
		FaultWSys = FaultSysEmpty;
		/* Union used for fault analysis */
		ModPFault.ModParsBits = 0;
		/* Unions containing more general information about sensor faults */
		HardFStatus = FaultDetectEmpty;
		SoftFStatus = FaultDetectEmpty;
		ExistFStatus = FaultDetectEmpty;
		HardFWarning = FaultDetectEmpty;
		SoftFWarning = FaultDetectEmpty;
		ExistFWarning = FaultDetectEmpty;
		TrustSens = FaultDetectEmpty;
		TrustHard = FaultDetectEmpty;
		/* Union containing engine status */
		EngStatus = EngStatusEmpty;
		/* Each union is initiated with null values */
		Ts2_0.TCFaultBits = 0;
		Ts2_1.TCFaultBits = 0;
		Tt4_0.TCFaultBits = 0;
		Tt4_1.TCFaultBits = 0;
		Tt4_2.TCFaultBits = 0;

		Ts2Res = DefaultRes;
		Pt3Res = DefaultRes;
		Tt4Res = DefaultRes;
		RPMRes = DefaultRes;
		POilRes = DefaultRes;
		PFuelRes = DefaultRes;
		VibrationRes = DefaultRes;

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
    
    /* Reads word containing faults simulated by siftware */
    SoftSimFaults.FaultBits = (uint64_t)InputFaults[0];
        
    /* -------------------------------------------------- */

    /*--------------------------------------------*/
	/* THERMOCOUPLE FAULT SIMULATION VIA SOFTWARE */
	/*--------------------------------------------*/
    
    /* Thermocouple fault simulation */
    TCFault(&Sensors, &SoftSimFaults, &Ts2_0, &Ts2_1, &Tt4_0, &Tt4_1, &Tt4_2, TCOpen);
    
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
		Current_key_start = 0;
		Old_key_start = 0;
        /* Sets starting flat to zero */
        StartComplete = 0;
		//fValue = 0;
        Wf = 0;
		/* Disable controller actuation untill authorized by model */
		Authorize = 0;
		/* Indicates reset request to the controller */
		ContInput.Reset = 1;
		/* Sets reset flag to 0 */
		Reset = 0;

        /* SETS ALL STRUCTS TO ZERO */

        /* Ambient Structure */
		Ambient = AmbientEmpty;

		/* Digital IO */
		digital = digitalEmpty;
		keys = keysEmpty;

		/* Initializes structs with null values */
		ContStart = ContStartEmpty;
		ContInput = ContInputEmpty;
		ContOutput = ContOutputEmpty;
		EngOnOff = EngOnOffEmpty;
		/* Engine sensors */
		Sensors = SensorsEmpty;
		/* Interpolation Structure */
		Index3D = Index3DEmpty;
		/* Sets Controller Constants to zero */
		ContConst = ContConstEmpty;
		/* Declared structure for fail-safe control implementation */
		ModelPars = EstParsEmpty;
		BlowOutPars = EstParsEmpty;
		/* Union used for sending engine fault status */
		FaultStatus = FaultEmpty;
		FaultWarning = FaultEmpty;
		/* Union used for software fault simulation */;
		FaultSSens = FaultSensEmpty;
		FaultWSens = FaultSensEmpty;
		SoftSimFaults = FaultSensEmpty;
		/* Union used for fault analysis */
		FaultSSys = FaultSysEmpty;
		FaultWSys = FaultSysEmpty;
		/* Union used for fault analysis */
		ModPFault.ModParsBits = 0;
		/* Unions containing more general information about sensor faults */
		HardFStatus = FaultDetectEmpty;
		SoftFStatus = FaultDetectEmpty;
		ExistFStatus = FaultDetectEmpty;
		HardFWarning = FaultDetectEmpty;
		SoftFWarning = FaultDetectEmpty;
		ExistFWarning = FaultDetectEmpty;
		TrustSens = FaultDetectEmpty;
		TrustHard = FaultDetectEmpty;
		/* Union containing engine status */
		EngStatus = EngStatusEmpty;
		/* Each union is initiated with null values */
		Ts2_0.TCFaultBits = 0;
		Ts2_1.TCFaultBits = 0;
		Tt4_0.TCFaultBits = 0;
		Tt4_1.TCFaultBits = 0;
		Tt4_2.TCFaultBits = 0;

		Ts2Res = DefaultRes;
		Pt3Res = DefaultRes;
		Tt4Res = DefaultRes;
		RPMRes = DefaultRes;
		POilRes = DefaultRes;
		PFuelRes = DefaultRes;
		VibrationRes = DefaultRes;

        /* Command Reset */
        ShutDownCommand = 0;
        EmergencyCommand = 0;
        StartCommand = 0;
		CriticalFailure = 0;
        
		/* Sets fault analysis flag to 0 */
		StartFaultAnalysis = 0;

        /* -------------------------------------------------- */
        /* SIMULATION OF A SINGLE READ OF SkipStart           */
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

    /**/
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

        /* Sets starting variables */
        ContStart.WfTrigger = ContOutput.Wf;
        ContStart.RefInitStatus = 1;

        /* Sets SkipStart to 0 */
        SkipStart = 0;

        /* Sets StartComplete to 1 */
        StartComplete = 1;

        /* Sets engine status to REGIME */
        EngStatus.EngineStatus = 0;
        EngStatus.EngStatusBist.Regime = 1;

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
	RefCAN = (double)reference;
	FNpc = RefCAN;

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

        /* -------------------------------------------------- */
	    /* SIMULATION OF GPIO PINES - TMATS & PWLM            */
	    /* (To be usedi in MATLAB and TMATS simulations only) */
	    /* -------------------------------------------------- */
        
        /* Simulates reading from each GPIO pin */
        keys.in = GPIOIn & 0x7FF;

        /* Reads start key - pulse detection */
        Old_key_start = Current_key_start;
        Current_key_start = 0;// !keys.bits.ac_drive_key || Authorize;

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
                
        /*----------------*/
        /* FAULT ANALYSIS */
        /*----------------*/

        TCResCalc(&Ts2_0, &Ts2_1, &Tt4_0, &Tt4_1,
                        &Tt4_2, &Ts2Res, &Tt4Res);

        EstIndex(&ModelPars, &AltLinVec, &MNLinVec,
                       &Mtx2D, &Mtx2DH, &Mtx1D, &Mtx1DH,
                       &FNperContMtx, &ContConst, &Index3D);      

/*=========== PREVIOUS RESIDUAL CALCULATION AND PROCESSING==*/

        // /* RESIDUAL CALCULATIONS */      

        // /* Execution of residual calculation subroutine */
        // ResCalc(&Ts0Mtx, &ContConst,
        //         &Ts0Mtx2D, &Ts0Mtx2DH, &Ts0Mtx1D, &Ts0Mtx1DH,
        //         &ModelPars, &BlowOutPars, &Sensors,
        //         &Ts2Res, &Pt3Res, &Tt4Res,
        //         &RPMRes, &POilRes, &PFuelRes,
        //         &VibrationRes,
        //         &FaultSSens, &FaultWSens,
        //         &FaultSSys, &FaultWSys,
        //         &HardFStatus, &HardFWarning, &Index3D);

/*=======================================================*/

        /* CALCULATION OF ENGINE MODEL Ts2 */

        /* Calculation of model ambient temperature */
        Ts2ModelCalc(&Ts0Mtx, &ContConst,
             &Ts0Mtx2D, &Ts0Mtx2DH, &Ts0Mtx1D, &Ts0Mtx1DH,
             &ModelPars, &Index3D);

        /* RESIDUAL CALCULATION AND PROCESSING */

        /* Residuals calculations */
        ResidualsCalc(&ContConst,
             &ModelPars, &Sensors,
             &Ts2Res, &Pt3Res, &Tt4Res,
             &RPMRes, &POilRes, &PFuelRes,
             &VibrationRes);

        /* Sensors residuals processing */
        ResProcSens(&ContConst, &ModelPars, &Sensors,
            &Ts2Res, &Pt3Res, &Tt4Res,
            &RPMRes, &POilRes, &PFuelRes,
            &VibrationRes, 
            &FaultSSens, &FaultWSens);

        /* Systems residuals processing */
        ResProcSys(&ContConst, &ModelPars, 
             &BlowOutPars, &Sensors,
             &Ts2Res, &Pt3Res, &Tt4Res,
             &RPMRes, &POilRes, &PFuelRes,
             &VibrationRes,
             &FaultSSys, &FaultWSys);

        /* Sensor bias residuals processing */
        ResProcBias(&ContConst, &ModelPars,
             &Ts2Res, &Pt3Res, &Tt4Res,
             &RPMRes, &POilRes, &PFuelRes,
             &VibrationRes, &HardFStatus, &HardFWarning); 

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

		/* Fault analysis is carried on as StartFaultAnalysis becomes 1 */
		if (StartFaultAnalysis == 1)
        {

            /* HARD FAULTS - HIGH BIAS - AT EACH SENSOR */

            /* Updates sensor hard faults - Warnings */
            HardFaultUpdt(&FaultWarning, &HardFWarning);
            /* Updates sensor hard faults - Status */
            HardFaultUpdt(&FaultStatus, &HardFStatus);

            /* SENSOR FAULTS ISOLATED AT EACH SENSOR */

            /* Updates sensor isolated faults - Warnings */
            SensFaultUpdt(&FaultWarning, &FaultWSens);
            /* Updates sensor isolated faults - Status */
            SensFaultUpdt(&FaultStatus, &FaultSSens);

            /* ANALYSES OF SENSOR TRUSTWORTHINES */

            /* Sensors thrustworthiness analysis - checks if isolated sensor faults have occurred */
            SensorTrust(&TrustSens, &FaultSSens);
            /* Sensors thrustworthiness analysis - checks if high bias has occurred */
            HardTrust(&TrustHard, &HardFStatus, &HardFWarning);

            /* ISOLATION OF SYSTEMS FAULTS */

            /* Identification and isolation engine blow out */
            BlowOut(&TrustSens, &FaultSSys, &FaultStatus);
            /* Identification and isolation engine blow out */
            MecLock(&TrustSens, &FaultSSys, &FaultStatus);
        
}

        /* IDENTIFICATION OF ENGINE STATUS */

        /* Identifies initial or windmilling status */
        EngStatusDeff(&EngStatus, &ModPFault, &ContInput,
                    &ContStart, &ContConst, 
                    0, 6,
                    StartCommand, 1, FNpc, 
                    ShutDownCommand, 1, EmergencyCommand, 1,
                    CriticalFailure, 1, Ts);

        /* SYSTEM FAULTS ISOLATED AT EACH SENSOR */

        /* Updates sensor faults - Warnings */
        SysFaultUpdt(&FaultWarning, &FaultWSys);
        /* Updates sensor faults - Status */
        SysFaultUpdt(&FaultStatus, &FaultSSys);


        /* VERIFICATION OF OVERTEMP */
        OverTemp(&ContConst, &TrustSens, &FaultSSys, &Sensors, &FaultStatus);

        /* VERIFICATION OF OVERSPEED */
        OverSpeed(&TrustSens, &FaultSSys, &Sensors, &FaultStatus);

        /* IGINTION FAIL */
        FaultStatus.Faults.Ignition = ContStart.IgnitionFail;


        /* CALCULATION OF MEDIUM VALUES */

        /* Below, the ModPFault struct indicates which modeled parameters has any fault at each of its sensors, indicating 
        that, for this particular parameter, only the model estimation is being used */

        /* Calculates the medium value of Ts2 - The last indicates the minimum number of trusted sensors before 
        untrusted sensors are replaced by model calculated values */
        Ts2MediumValue(&ModPFault, &Ts2MedVal, ContConst.NumTs2Sens, &TrustHard, &Sensors, ModelPars.Ts2,ContConst.NumTs2SensTrust);
        /* Calculates the medium value of Pt3 - The last indicates the minimum number of trusted sensors before 
        untrusted sensors are replaced by model calculated values */
        Pt3MediumValue(&ModPFault, &Pt3MedVal, ContConst.NumPs3Sens, &TrustHard, &Sensors, ModelPars.Pt3,ContConst.NumPs3SensTrust);
        /* Calculates the medium value of Tt4 - The last indicates the minimum number of trusted sensors before 
        untrusted sensors are replaced by model calculated values */
        Tt4MediumValue(&ModPFault, &Tt4MedVal, ContConst.NumTt4Sens, &TrustHard, &Sensors, ModelPars.Tt4,ContConst.NumTt4SensTrust);
        /* Calculates the medium value of RPM - The last indicates the minimum number of trusted sensors before 
        untrusted sensors are replaced by model calculated values */
        RPMMediumValue(&ModPFault, &RPMMedVal, ContConst.NumRPMSens, &TrustHard, &Sensors, ModelPars.RPM,ContConst.NumRPMSensTrust);
       
        /* Updates variables with calculated medium values */
        Ts2 = Ts2MedVal;
        Pt3 = Pt3MedVal;
        Tt4 = Tt4MedVal;
        RPM = RPMMedVal;

        /* ESTIMATION OF BACKGROUND STANDARD TEMPERATURE BASED ON ALTITUDE AND MN */
		Ambient.Alt = Altitude;
		Ambient.MN = MN;
		Ambient.dT = 0;
		Ambient_TMATS(&Ambient);
//mexPrintf("Antes: Ambient T-MATS: Tt2 = %f\n", Ambient.Tt);  
        /* Loads parameters fo Tt2 Calculations */
		ModelPars.gamma_air = GAMMA_AIR;
    	ModelPars.MN = MN;
    	ModelPars.Ts2Std = Ambient.Ts;

        /* Calculation of total temperature */        
        Tt2Calc(Ts2, &ModelPars); 

        /* Updates Tt2 and dT values */
        Tt2 = ModelPars.Tt2;
        dT = ModelPars.dT;
//mexPrintf("Meio: dT = %f\n", dT);  

// PrintFaults(&FaultWarning,0,1);
// PrintFaults(&FaultStatus,1,0);
// PrintEngStatus(&EngStatus,1);

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
//mexPrintf("Meio: Ambient T-MATS: Tt2 = %f\n", Ambient.Tt);  
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

        // /*-----------------------------*/
        // /* NOMINAL SHUT DWON REFERENCE */
        // /*-----------------------------*/

        // /* If nominal shut down has been requested, controller reference must be set to minimum */
        // ShutDownRef(ShutDownCommand, &ContInput, &ContOutput, &ContConst);

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
        ShutDownRef(ShutDownCommand, &ContInput, &ContOutput, &ContConst);

        /* CALCULATES THE CONTROL LAW */            
                    
        /* Calculates fuel flow from control law */
        PIMinMaxRF(&AltLinVec, &MNLinVec, &NcVec, &ASVec,
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
                     &ContStart, &ContStartEmpty, &digital,
                     &ContConst, Ts);

        /* EXECUTES EMERGENCY SHUT DOWN ROUTINE IF EMERGENCY HAS OCCURRED */

        /* Engine must execute emergency shut down either through external command of 
        Emergency or through detection of critical failure */
        EmergShutDwn = EmergencyCommand || CriticalFailure;

        EmergencyShutDown(&ContInput, &ContInputEmpty,
						  &ContOutput, &ContOutputEmpty,
						  &ContStart, &ContStartEmpty, &digital, EmergShutDwn);
        
        /* Updates fuel flow value */
        Wf = ContOutput.Wf;

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

            /* Sets falt indicating starting of model parameters to zero */
            ModelParsStart = 0;

        }
//mexPrintf("Depois: Ambient T-MATS: Tt2 = %f\n", Ambient.Tt);        

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
        
        /* Update fuel lack model inputs */
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
        //Out5 = ContStart.status;//EngStatus.EngineStatus;
                
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
    
    IoutModel[0] = ModelPars.RPM;
    IoutModel[1] = ModelPars.Tt4;
//mexPrintf("\n ModelPars.Tt4 = %f", ModelPars.Tt4);
    IoutModel[2] = ModelPars.Pt3;
    IoutModel[3] = ModelPars.WfOutfp;
    
    IoutBlowOut[0] = BlowOutPars.RPM;
    IoutBlowOut[1] = BlowOutPars.Tt4;
    IoutBlowOut[2] = BlowOutPars.Pt3;
    IoutBlowOut[3] = BlowOutPars.Tt2;
    
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
