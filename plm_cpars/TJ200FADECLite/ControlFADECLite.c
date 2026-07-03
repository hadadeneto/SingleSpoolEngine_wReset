

/* INCLUDES REFERENT TO THE FADEC */
// extern "C"
// {

/* Change for FADEC Lite */
#include <math.h>
#include <stdio.h>


/*--------------------*/
/* ADDITIONAL STRUCTS */
/*--------------------*/

#include "FADECLiteExpStr.h"

/******** COPYFROM START: FADEC_INCLUDES *********/

/*-------------------*/
/* STANDARD INCLUDES */
/*-------------------*/

/* Standard includes */
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

/*-----------------------------------------------*/
/* GENERAL INCLUDES - USED BY ALL FADECS AND HIL */
/*-----------------------------------------------*/

/* General .h files */
#include "FADEC_Functions_H/Ambient_TMATS.h"          /* Adapted from T-MATS */
#include "FADEC_Defines_H/constants_TMATS.h"        /* Adapted from T-MATS */
#include "FADEC_Defines_H/Control_Types.h"          /* Controller calculations */
#include "FADEC_Functions_H/ControlFunctions.h"       /* Controller calculations */
#include "FADEC_Defines_H/DigitalOutDefs.h"         /* Controller calculations */
#include "FADEC_Defines_H/Env_SampTime.h"           /* General Calculations*/
#include "FADEC_Functions_H/FailSafeFunctions.h"      /* Fault analysis */
#include "FADEC_Defines_H/FaultSim_Types.h"         /* Fault analysis */
#include "FADEC_Defines_H/FloatPoint_Precision.h"			/* Defines the size of used floating point */
#include "FADEC_Functions_H/functions_TMATS.h"        /* Adapted from T-MATS */
//#include "getTJ200.h"              /* File containing all get functions for TJ200 */
#include "FADEC_Defines_H/Interpolation_Types.h"    /* General Calculations*/
#include "FADEC_Defines_H/IO_Types.h"               /* Controller calculations */
//#include "FADEC_Functions_H/LinMtxFunctions.h"        /* General Calculations*/
#include "FADEC_Defines_H/Model_Types.h"            /* Used for model calculations */
#include "FADEC_Functions_H/MtxIntFunctions.h"        /* General Calculations*/
#include "FADEC_Functions_H/PeripheralDyn.h"          /* Functions describing peripherals dynamics */
#include "FADEC_Functions_H/PIMinMaxRF.h"             /* Controller calculations */
//#include "PIOil.h"                  /* Controller calculations */
#include "FADEC_Functions_H/ShutDownFunctions.h"      /* Controller calculations */
#include "FADEC_Functions_H/StartingFunctions.h"      /* Controller calculations */
#include "FADEC_Functions_H/TCFault.h"                /* Fault analysis */

/*-----------------*/
/* ENGINE INCLUDES */
/*-----------------*/

/* Engine .h files */
#include "TJ200/FADEC_Constants_H/ConstantsTJ200.h"
#include "TJ200/FADEC_get_H/getTJ200FADECContConst.h"
#include "TJ200/FADEC_get_H/getTJ200FADECMtx.h"       /* TJ200 Engine Constants */
#include "TJ200/FADEC_get_H/getTJ200FADECSizeConst.h"

/******** COPYFROM END: FADEC_INCLUDES *********/

//}

    // The variable below must be declared in this space since in the other FADEC version the same is done. This 
    //should be changded in the future version and the commented declaration must be used
    floating dT = 0;

/******** COPYFROM START: FADEC_VARS *********/

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

/******** COMMENT START *********/
//
//    /* REQUIRED INITIALIZATIONS */
//
//    SoftSimFaults = FaultSensEmpty;                     /* Union - Thermocouple full scale simulation */
//
//    /* Each union is initiated with null values */
//    Ts2_0.TCFaultBits = 0;
//    Ts2_1.TCFaultBits = 0;
//    Tt4_0.TCFaultBits = 0;
//    Tt4_1.TCFaultBits = 0;
//    Tt4_2.TCFaultBits = 0;
//    TB_0.TCFaultBits = 0;
//    TB_1.TCFaultBits = 0;
//    TB_2.TCFaultBits = 0;
//
/******** COMMENT END *********/

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

	/* floating TYPE */

    floating Altitude = 567;                              /* Altitude value */
    floating Delta = 1;                                       /* Delta = Pt2/PSTD - correction parameter */
/******** COMMENT START *********/
//    floating dT = 0;                                      /* Day temperature variation */
/******** COMMENT END *********/
    floating FNcMax = 0;                                  /* Maximum allowed corrected net thrust */
    floating FNpc = 0;                                    /* Corrected net thrust */
    floating MemSize = 0;                                 /* Memory occupied by matrices */
    floating MN = 0;                                      /* Flight Mach number value */
	floating OPRPMManual = 0;								/* Manual reference for oil pump rotation speed */
    floating POil = 0;                                    /* Oil pressure */
    floating Pt2 = 101325;                                /* Compressor inlet total pressure */
    floating Pt3 = 101325;                                /* Compressor exhaust total pressure */
    floating Pt3MedVal = 101325;                          /* Pt3 medium value */
    floating RefCAN = 0;                                  /* Reference from CAN */
/******** COMMENT START *********/
////    floating reference = 0.35;                            /* Reference value used initially */
/******** COMMENT END *********/
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

	// /* floating TYPE */

    // floating Altitude = 0;                                /* Altitude value */
    // floating Delta;                                       /* Delta = Pt2/PSTD - correction parameter */
    // floating dT = 0;                                      /* Day temperature variation */
    // floating FNcMax = 0;                                  /* Maximum allowed corrected net thrust */
    // floating FNpc = 0;                                    /* Corrected net thrust */
    // floating MN = 0;                                      /* Flight Mach number value */
	// floating OPRPMManual = 0;								/* Manual reference for oil pump rotation speed */
    // floating POil = 0;                                    /* Oil pressure */
    // floating Pt2 = 101325;                                /* Compressor inlet total pressure */
    // floating Pt3;                                         /* Compressor exhaust total pressure */
    // floating Pt3MedVal = 0;                               /* Pt3 medium value */
    // floating RefCAN = 0;                                  /* Reference from CAN */
    // floating reference = 0.35;                            /* Reference value used initially */
    // floating RPM;                                         /* Engine mechanical rotation speed */
    // floating RPMMedVal = 0;                               /* RPM medium value */
    // floating TBear[5];                                    /* String containing bearings temperatures */
    // floating Ts2 = 288.15;                                /* Compressor inlet static temperature */
    // floating Ts2MedVal = 288.15;                          /* Ts2 medium value */
    // floating Tt2 = 288.15;                                /* Compressor inlet total temperature */
    // floating Tt4;                                         /* Combustion chamber total temperature */
    // floating Tt4MedVal = 0;                               /* Tt4 medium value */
    // floating Tt5;                                         /* Turbine inlet total temperature */
    // floating WaitTime;                                    /* Used by general purpose timer */
    // floating Wf0;                                         /* Initial fuel flow value */

    // /* static floating TYPE */

    // static floating OPRPM;                                /* Oil pump rotation speed */
    // static floating Wf = 0;                               /* Fuel flow */

    /*-----------------------------------------------------------*/
    /* FADEC VARIABLES - USED ONLY BY FADEC AND NOT BY THE MODEL */
    /*-----------------------------------------------------------*/

    /* int TYPE */

    int Authorize = 0;                                     /* Flag indicating that controller is authorized to perform */
    int Fn_Elem = TJ200_FN_ELEM;                      /* Number of net thrust breakpoint elements */
    int MN_Elem = TJ200_MN_ELEM;                      /* Number of Mach number breakpoint elements */

    int Alt_Elem;
    int AS_Elem;
    int SteadyOp_Elem;
    int PowerMan_Elem;
    int NcHPCMap_Elem;
    int WcHPCMap_Elem;
    int Wc_per_Nc_HPC;

    /* floating TYPE */

    floating AuxTimer = 0;                                    /* Dummy timer for general purposes */
    floating Ts = 0.001 * TICK;                           /* Sampling Time */

    /* floating TYPE STRINGS */

    // floating AltLinVec[TJ200_ALT_ELEM];                      /* Altitude breakpoints */
    // floating AMtx[TJ200_MN_ELEM * TJ200_FN_ELEM];           /* Model - A matrix */
    // floating ASVec[TJ200_AS_ELEM];                           /* Controller - Asceleration schedule (ASVec) break points */
    // floating BMtx[TJ200_MN_ELEM * TJ200_FN_ELEM];           /* Model - B matrix */
    // floating DeltaMtx[TJ200_ALT_ELEM * TJ200_MN_ELEM];      /* Controller - Delta matrix */
    // floating DeltaMtx1D[TJ200_MN_ELEM];                      /* Auxiliar matrix - Delta */
    // floating DeltaMtx1DH[TJ200_MN_ELEM];                     /* Auxiliar matrix - Delta */
    // floating DeltaMtx2D[TJ200_ALT_ELEM * TJ200_MN_ELEM];    /* Auxiliar matrix - Delta */
    // floating DeltaMtx2DH[TJ200_ALT_ELEM * TJ200_MN_ELEM];   /* Auxiliar matrix - Delta */
    // floating DSVec[TJ200_AS_ELEM];                           /* Controller - Deceleration schedule (DSVec) break points */
    // floating FNcMaxContMtx[TJ200_MN_ELEM];                   /* Controller - Maximum corrected net thrust values */
    // floating FNperContMtx[TJ200_TOTAL_ELEM];                 /* Controller - net thrust percentual values matrix */
    // floating MapHPC1D[TJ200_FAN_PR];                         /* Auxiliar matrix - HPC map */
    // floating MapHPC1DH[TJ200_FAN_PR];                        /* Auxiliar matrix - HPC map */
    // floating MapHPC2D[TJ200_FAN_NC * TJ200_FAN_PR];         /* Auxiliar matrix - HPC map */
    // floating MapHPC2DH[TJ200_FAN_NC * TJ200_FAN_PR];        /* Auxiliar matrix - HPC map */
    // floating MNLinVec[TJ200_MN_ELEM];                        /* Mach number breakpoints */
    // floating Mtx1D[TJ200_FN_ELEM];                           /* Auxiliar matrix */
    // floating Mtx1DH[TJ200_FN_ELEM];                          /* Auxiliar matrix */
    // floating Mtx2D[TJ200_MN_ELEM * TJ200_FN_ELEM];          /* Auxiliar matrix */
    // floating Mtx2DH[TJ200_MN_ELEM * TJ200_FN_ELEM];         /* Auxiliar matrix */
    // floating N_KiMtx[TJ200_TOTAL_ELEM];                      /* Controller - Ki matrix of N control law */
    // floating N_KpMtx[TJ200_TOTAL_ELEM];                      /* Controller - Kp matrix of N control law */
    // floating NcFANContMtx[TJ200_TOTAL_ELEM];                 /* Controller - Fan Nc breakpoints */
    // floating NcHPCMapMtx[TJ200_FAN_NC];                      /* Model - Nc break points matrix - HPC map */
    // floating NcVec[TJ200_AS_ELEM];                           /* Controller - Nc schedule (for ASVec and DSVec) break points */
    // floating PRHPCMapMtx[TJ200_FAN_NC * TJ200_FAN_PR];      /* Model - PR break points matrix - HPC map */
    // floating Pt3DMtx[TJ200_MN_ELEM * TJ200_FN_ELEM];        /* Model - Pt3D matrix */
    // floating Pt3Mtx[TJ200_MN_ELEM * TJ200_FN_ELEM];         /* Model - Pt3 matrix */
    // floating Pt5DMtx[TJ200_MN_ELEM * TJ200_FN_ELEM];        /* Model - Pt5D matrix */
    // floating Pt5Mtx[TJ200_MN_ELEM * TJ200_FN_ELEM];         /* Model - Pt5 matrix */
    // floating Ts0Mtx[TJ200_ALT_ELEM];                         /* Controller and Model - Ts0 break points  */
    // floating Ts0Mtx1D[TJ200_ALT_ELEM];                       /* Auxiliar matrix - Ts0 */
    // floating Ts0Mtx1DH[TJ200_ALT_ELEM];                      /* Auxiliar matrix - Ts0 */
    // floating Ts0Mtx2D[TJ200_FN_ELEM];                        /* Auxiliar matrix - Ts0 */
    // floating Ts0Mtx2DH[TJ200_FN_ELEM];                       /* Auxiliar matrix - Ts0 */
    // floating Tt4DMtx[TJ200_MN_ELEM * TJ200_FN_ELEM];        /* Model - Tt4D matrix */
    // floating Tt4Mtx[TJ200_MN_ELEM * TJ200_FN_ELEM];         /* Model - Tt4 matrix */
    // floating Tt5DMtx[TJ200_MN_ELEM * TJ200_FN_ELEM];        /* Model - Tt5D matrix */
    // floating Tt5Mtx[TJ200_MN_ELEM * TJ200_FN_ELEM];         /* Model - Tt5 matrix */
    // floating WcHPCMapMtx[TJ200_FAN_NC * TJ200_FAN_PR];      /* Model - Wc break points matrix - HPC map */
    // floating WfMtx[TJ200_MN_ELEM * TJ200_FN_ELEM];          /* Model - Wf matrix */

    // /* floating TYPE POINTERS */

    floating *Teste;

    floating *AltLinVec;                                  /* Controller and Model - Altitude break points  */
    floating *AMtx;                                       /* Model - pointer for A matrix */
    floating *ASVec;                                      /* Controller - Asceleration schedule (ASVec) break points */
    floating *BMtx;                                       /* Model - pointer for B matrix */
    floating *DeltaMtx;                                   /* Controller and Model - Delta break points  */
    floating *DeltaMtx1D;                                 /* Auxiliar matrix - Delta */
    floating *DeltaMtx1DH;                                /* Auxiliar matrix - Delta */
    floating *DeltaMtx2D;                                 /* Auxiliar matrix - Delta */
    floating *DeltaMtx2DH;                                /* Auxiliar matrix - Delta */
    floating *DSVec;                                      /* Controller - Deceleration schedule (DSVec) break points */
    floating *FNcMaxContMtx;                              /* Controller - pointer for maximum net thrust breakpoint values */
    floating *FNperContMtx;                               /* Controller - pointer for net thrust percent breakpoint values */
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
	floating *N_KishMtx;                                    /* Controller - pointer for Ki matrix of N control law - sub-idle */
    floating *N_KpMtx;                                    /* Controller - pointer for Kp matrix of N control law */
    floating *N_KpshMtx;                                    /* Controller - pointer for Kp matrix of N control law - sub-idle */
    floating *NcFANContMtx;                               /* Controller - pointer for fan Nc breakpoint values */
    floating *NcFANshContMtx;                               /* Controller - pointer for fan Nc breakpoint values - sub-idle */
    floating *NcHPCMapMtx;                                /* Model - pointer for Nc values matrix - HPC map */
    floating *NcVec;                                      /* Controller - Nc schedule (for ASVec and DSVec) break points  */
    floating *PRHPCMapMtx;                                /* Model - pointer for PR values matrix - HPC map */
    floating *Pt3DMtx;                                    /* Model - pointer for Pt3D matrix */
    floating *Pt3Mtx;                                     /* Model - pointer for Pt3 matrix */
    floating *Pt5DMtx;                                    /* Model - pointer for Pt5D matrix */
    floating *Pt5Mtx;                                     /* Model - pointer for Pt5 matrix */
    floating *Ts0Mtx;                                     /* Controller and Model - pointer Ts0 break points  */
    floating *Ts0Mtx1D;                                   /* Auxiliar matrix - Ts0 */
    floating *Ts0Mtx1DH;                                  /* Auxiliar matrix - Ts0 */
    floating *Ts0Mtx2D;                                   /* Auxiliar matrix - Ts0 */
    floating *Ts0Mtx2DH;                                  /* Auxiliar matrix - Ts0 */
    floating *Tt4DMtx;                                    /* Model - pointer for Tt4D matrix */
    floating *Tt4Mtx;                                     /* Model - pointer for Tt4 matrix */
    floating *Tt5DMtx;                                    /* Model - pointer for Tt5D matrix */
    floating *Tt5Mtx;                                     /* Model - pointer for Tt5 matrix */
    floating *WcHPCMapMtx;                                /* Model - pointer for Wc values matrix - HPC map */
    floating *WfMtx;

/******** COPYFROM END: FADEC_VARS *********/


/*******************************************************************************
 *
 *	FUNCTION:		FADECReset()
 *
 *	PURPOSE:		The function below initites engine specifica variables and 
 *                  matrices
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		void
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

 // The function below initites engine specifica variables and matrices
void FADECInitVars(void)
{

/******** COPYFROM START: FADEC_LOADPARS *********/

    /* Loads the constants of chosen engine used by FADEC */
    getTJ200FADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
                            &PowerMan_Elem, &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC);

    AltLinVec      = FADECMalloc(Alt_Elem, &MemSize);
    AMtx           = FADECMalloc(SteadyOp_Elem, &MemSize);
    ASVec          = FADECMalloc(AS_Elem, &MemSize);
    BMtx           = FADECMalloc(SteadyOp_Elem, &MemSize);
    DeltaMtx       = FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
    DeltaMtx1D     = FADECMalloc(MN_Elem, &MemSize);
    DeltaMtx1DH    = FADECMalloc(MN_Elem, &MemSize);
    DeltaMtx2D     = FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
    DeltaMtx2DH    = FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
    DSVec          = FADECMalloc(AS_Elem, &MemSize);
    FNcMaxContMtx  = FADECMalloc(MN_Elem, &MemSize);
    FNperContMtx   = FADECMalloc(PowerMan_Elem, &MemSize);
    MapHPC1D       = FADECMalloc(Wc_per_Nc_HPC, &MemSize);
    MapHPC1DH      = FADECMalloc(Wc_per_Nc_HPC, &MemSize);
    MapHPC2D       = FADECMalloc(WcHPCMap_Elem, &MemSize);
    MapHPC2DH      = FADECMalloc(WcHPCMap_Elem, &MemSize);
    MNLinVec       = FADECMalloc(MN_Elem, &MemSize);
    Mtx1D          = FADECMalloc(Fn_Elem, &MemSize);
    Mtx1DH         = FADECMalloc(Fn_Elem, &MemSize);
    Mtx2D          = FADECMalloc(MN_Elem * Fn_Elem, &MemSize);
    Mtx2DH         = FADECMalloc(MN_Elem * Fn_Elem, &MemSize);
    N_KiMtx        = FADECMalloc(PowerMan_Elem, &MemSize);
    N_KishMtx      = FADECMalloc(PowerMan_Elem, &MemSize);
    N_KpMtx        = FADECMalloc(PowerMan_Elem, &MemSize);
    N_KpshMtx      = FADECMalloc(PowerMan_Elem, &MemSize);
    NcFANContMtx   = FADECMalloc(PowerMan_Elem, &MemSize);
    NcFANshContMtx = FADECMalloc(PowerMan_Elem, &MemSize);
    NcHPCMapMtx    = FADECMalloc(NcHPCMap_Elem, &MemSize);
    NcVec          = FADECMalloc(AS_Elem, &MemSize);
    PRHPCMapMtx    = FADECMalloc(WcHPCMap_Elem, &MemSize);
    Pt3DMtx        = FADECMalloc(SteadyOp_Elem, &MemSize);
    Pt3Mtx         = FADECMalloc(SteadyOp_Elem , &MemSize);
    Pt5DMtx        = FADECMalloc(SteadyOp_Elem, &MemSize);
    Pt5Mtx         = FADECMalloc(SteadyOp_Elem, &MemSize);
    Ts0Mtx         = FADECMalloc(Alt_Elem * MN_Elem, &MemSize);
    Ts0Mtx1D       = FADECMalloc(Alt_Elem, &MemSize);
    Ts0Mtx1DH      = FADECMalloc(Alt_Elem , &MemSize);
    Ts0Mtx2D       = FADECMalloc(Fn_Elem, &MemSize);
    Ts0Mtx2DH      = FADECMalloc(Fn_Elem, &MemSize);
    Tt4DMtx        = FADECMalloc(SteadyOp_Elem, &MemSize);
    Tt4Mtx         = FADECMalloc(SteadyOp_Elem , &MemSize);
    Tt5DMtx        = FADECMalloc(SteadyOp_Elem, &MemSize);
    Tt5Mtx         = FADECMalloc(SteadyOp_Elem, &MemSize);
    WcHPCMapMtx    = FADECMalloc(WcHPCMap_Elem, &MemSize);
    WfMtx          = FADECMalloc(SteadyOp_Elem, &MemSize);

    // AltLinVec = (floating *)malloc(Alt_Elem * sizeof(floating));
    // AMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // ASVec = (floating *)malloc(AS_Elem * sizeof(floating));
    // BMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // DeltaMtx = (floating *)malloc(Alt_Elem * MN_Elem * sizeof(floating));
    // DeltaMtx1D = (floating *)malloc(MN_Elem * sizeof(floating));
    // DeltaMtx1DH = (floating *)malloc(MN_Elem * sizeof(floating));
    // DeltaMtx2D = (floating *)malloc(Alt_Elem * MN_Elem * sizeof(floating));
    // DeltaMtx2DH = (floating *)malloc(Alt_Elem * MN_Elem * sizeof(floating));
    // DSVec = (floating *)malloc(AS_Elem * sizeof(floating));
    // FNcMaxContMtx = (floating *)malloc(MN_Elem * sizeof(floating));
    // FNperContMtx = (floating *)malloc(PowerMan_Elem * sizeof(floating));
    // MapHPC1D = (floating *)malloc(Wc_per_Nc_HPC * sizeof(floating));
    // MapHPC1DH = (floating *)malloc(Wc_per_Nc_HPC * sizeof(floating));
    // MapHPC2D = (floating *)malloc(WcHPCMap_Elem * sizeof(floating));
    // MapHPC2DH = (floating *)malloc(WcHPCMap_Elem * sizeof(floating));
    // MNLinVec = (floating *)malloc(MN_Elem * sizeof(floating));
    // Mtx1D = (floating *)malloc(Fn_Elem * sizeof(floating));
    // Mtx1DH = (floating *)malloc(Fn_Elem * sizeof(floating));
    // Mtx2D = (floating *)malloc(MN_Elem * Fn_Elem * sizeof(floating));
    // Mtx2DH = (floating *)malloc(MN_Elem * Fn_Elem * sizeof(floating));
    // N_KiMtx = (floating *)malloc(PowerMan_Elem * sizeof(floating));
    // N_KishMtx = (floating *)malloc(PowerMan_Elem * sizeof(floating));
    // N_KpMtx = (floating *)malloc(PowerMan_Elem * sizeof(floating));
    // N_KpshMtx = (floating *)malloc(PowerMan_Elem * sizeof(floating));
    // NcFANContMtx = (floating *)malloc(PowerMan_Elem * sizeof(floating));
    // NcHPCMapMtx = (floating *)malloc(NcHPCMap_Elem * sizeof(floating));
    // NcVec = (floating *)malloc(AS_Elem * sizeof(floating));
    // PRHPCMapMtx = (floating *)malloc(WcHPCMap_Elem * sizeof(floating));
    // Pt3DMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Pt3Mtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Pt5DMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Pt5Mtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Ts0Mtx = (floating *)malloc(Alt_Elem * MN_Elem * sizeof(floating));
    // Ts0Mtx1D = (floating *)malloc(Alt_Elem * sizeof(floating));
    // Ts0Mtx1DH = (floating *)malloc(Alt_Elem * sizeof(floating));
    // Ts0Mtx2D = (floating *)malloc(Fn_Elem * sizeof(floating));
    // Ts0Mtx2DH = (floating *)malloc(Fn_Elem * sizeof(floating));
    // Tt4DMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Tt4Mtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Tt5DMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // Tt5Mtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));
    // WcHPCMapMtx = (floating *)malloc(WcHPCMap_Elem * sizeof(floating));
    // WfMtx = (floating *)malloc(SteadyOp_Elem * sizeof(floating));

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
    getTJ200FADECContConst(&ContConst);

    /* Loads FADEC matrices */
    getTJ200FADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
                     DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
                     N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
                     Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
                     Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
                     WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);

    // /* LOADING OF CONTROLLER MATRIX */

    // /* Linearization Vectors */
    // getTJ200AltLinVec(&AltLinVec);
    // getTJ200MNLinVec(&MNLinVec);
    // getTJ200Ts0Mtx(&Ts0Mtx);
    // getTJ200DeltaMtx(&DeltaMtx);

    // /* Controller Gains */
	// getTJ200N_KpMtx(&N_KpMtx);
	// getTJ200N_KiMtx(&N_KiMtx);
	// getTJ200NcFANContMtx(&NcFANContMtx);
    // getTJ200FNcMaxContMtx(&FNcMaxContMtx);
	// getTJ200FNperContMtx(&FNperContMtx);

    // /* Reference Filter */
    // getTJ200ASVec(&ASVec);
    // getTJ200DSVec(&DSVec);
    // getTJ200NcVec(&NcVec);

    // /* LOADING OF MODEL MATRICES */

    // getTJ200AMtx(&AMtx);
    // getTJ200BMtx(&BMtx);
    // getTJ200Pt3DMtx(&Pt3DMtx);
    // getTJ200Pt5DMtx(&Pt5DMtx);
    // getTJ200Tt4DMtx(&Tt4DMtx);
    // getTJ200Tt5DMtx(&Tt5DMtx);
    // getTJ200Pt3Mtx(&Pt3Mtx);
    // getTJ200Pt5Mtx(&Pt5Mtx);
    // getTJ200Tt4Mtx(&Tt4Mtx);
    // getTJ200Tt5Mtx(&Tt5Mtx);
    // getTJ200WfMtx(&WfMtx);
    // getTJ200PRHPCMapMtx(&PRHPCMapMtx);
    // getTJ200WcHPCMapMtx(&WcHPCMapMtx);
    // getTJ200NcHPCMapMtx(&NcHPCMapMtx);

    // getTJ200FADECMtx(&AMtx[0], &ASVec[0], &AltLinVec[0], &BMtx[0], &DSVec[0],
    //                   &DeltaMtx[0], &FNcMaxContMtx[0], &FNperContMtx[0], &MNLinVec[0], &N_KiMtx[0],
    //                   &N_KpMtx[0], &NcFANContMtx[0], &NcHPCMapMtx[0], &NcVec[0], &PRHPCMapMtx[0],
    //                   &Pt3DMtx[0], &Pt3Mtx[0], &Pt5DMtx[0], &Pt5Mtx[0], &Ts0Mtx[0],
    //                   &Tt4DMtx[0], &Tt4Mtx[0], &Tt5DMtx[0], &Tt5Mtx[0], &WcHPCMapMtx[0],
    //                   &WfMtx[0]);

/******** COPYFROM END: FADEC_LOADPARS *********/

}  


/*******************************************************************************
 *
 *	FUNCTION:		FADECReset()
 *
 *	PURPOSE:		The function executes a software reset in the FADEC
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		void
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/

// The function executes a software reset in the FADEC
int FADECReset(void)
{

    /* Flag indicating reset has been accomplished */
    int ResetOK = 0;

    /* Verifies if reset has been requested */
    if (Reset == 1)
    {

        /******** COPYFROM START: FADEC_RESET *********/

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
        /* FADEC ONLY */
        /*------------*/

        /* RESETS int TYPE */

        Authorize = 0;

        /******** COMMENT START *********/
        //
        //        /* -------------------------------------------------- */
        //        /* T-MATS AND PWLM           */
        //        /* (To be usedi in MATLAB and TMATS simulations only) */
        //        /* -------------------------------------------------- */
        //
        //        SkipStartIn[0] = 0;
        //        SkipStartIn[1] = 0;
        //
        //        /* -------------------------------------------------- */
        //
        /******** COMMENT END *********/

        /******** COPYFROM END: FADEC_RESET *********/

        /******** REPLACE START: getTJ1200ContConst BY getTJ1200FADECContConst *********/
        /* LOADING OF CONTROLLER CONSTANTS */
        getTJ200FADECContConst(&ContConst); // QUAL O MOTIVO DE CHAMAR AQUI DE NOVO?? -> TALVEZ POR CAUSA DO RESET, QUE ZEROU A CONTCONST!
        /******** REPLACE END: getTJ1200ContConst BY getTJ1200FADECContConst *********/
    
        ResetOK = 1;
    
    }

    return ResetOK;

}

/*******************************************************************************
 *
 *	FUNCTION:		ControlUpdate()
 *
 *	PURPOSE:		Updates the controller status based on read inputs
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		void
 *
 *	RETURNS:		void
 *
 *	COMMENTS:
 *
 *******************************************************************************/


// Updates the controller status based on read inputs
void ControlUpdate(ExpInputs_t* ExpIn, ExpOutputs_t* ExpOut) 
{

    // i10 a i13 - são sensores analógicos
    //t10 a t17 - são os termpoares
    //na struct de warning e failure, vai ser passado:
    // colocar como argumento: structs com Sensors, ContInputs e ContOutputs

    //Reads FADEC input variables as listed below:

    // 00 - Altitude                    (altitude value in meters) - Function argument
    // 01 - MN                          (flight Mach number) - Function argument
    // 02 - RefCAN                      (thrust reference) - Function argument
    // 03 - Ts2 sensor 0                (Ts2 value measured by sensor 0) - Sensror struct is a function argument
    // 03 - Ts2 sensor 1                (Ts2 value measured by sensor 1) - Sensror struct is a function argument
    // 03 - RPM sensor 0                (RPM value measured by sensor 0) - Sensror struct is a function argument
    // 03 - RPM sensor 1                (RPM value measured by sensor 1) - Sensror struct is a function argument
    // 03 - Ps3 sensor 0                (Ps3 value measured by senror 0) - Sensror struct is a function argument
    // 03 - Tt4 sensor 0                (Tt4 value measured by sensor 0) - Sensror struct is a function argument
    // 03 - Tt4 sensor 1                (Tt4 value measured by sensor 1) - Sensror struct is a function argument
    // 03 - Tt4 sensor 2                (Tt4 value measured by sensor 2) - Sensror struct is a function argument
    // 04 - OnOffCom                    (Command for engine start, shut off or emergency shut off) - Function argument
    // 05 - simMod                      (Variable for changing Authorize variable value) - Function argument
    // 06 - Reset                       (Variable for reseting the FADEC by software) - Function argument
    // 07 - SkipStart                   (Variable for skipping start routine) - Function argument
    // 08 - Authorize                   (Variable for authorizing control loop) - Function argument
    // 09 - Wf0                         (Fuel flow initial value) - Function argument
    // 10 - valorMantete                (Value from 0 to 1) - Function argument
    // 11 - keys.bits.igniter_key       (igniter) - key struct as a function argument
    // 11 - keys.bits.shut_off_key      (shut off) - key struct as a function argument
    // 11 - keys.bits.scaveng_key       (scavenge) - key struct as a function argument
    // 11 - keys.bits.oil_pump_key      (oil pump eneable) - key struct as a function argument
    // 11 - keys.bits.ac_drive_key      (ac driver eneable) - key struct as a function argument
    // 11 - keys.bits.ac_drive_key      (AC Drive button always in 0 (pressed)) - key struct as a function argument
    // 11 - keys.bits.emergency_key     (Emergency button always in 1 (not pressed). No physical button!) - key struct as a function argument
    // 11 - keys.bits.ignSOV_key        (added for TJ-200) - key struct as a function argument
    // 12 - LeverMode                   (Variable defining automatic or manual control after idle is reached) - Function argument
    // 13 - Mode                        (Variable for defining automatic start or complete manual operation) - Function argument
    // 14 - OPRPMManual                 (Manual oil pump rpm value) - Function argument
    // 15 - BoosterLStatus              (Left booster status) - Function argument
    // 16 - BoosterRStatus              (Right booster status) - Funtion argument 
    // 17 - SoftSimFaults               (Struct for thermocouple fault simulation - must be in FADEC) - Struct as function argument
    // 18 - StrRPMAct                   (To be written to ContStart.StrRPMAct)

    /* STRUCTS */

    Sensors = ExpIn->Sensors;//*SensorsExp;
    keys = ExpIn->keys;//*keysExp;
    SoftSimFaults = ExpIn->SoftSimFaults;//*SoftSimFaultsExp;

    /* VARIABLES */

    Altitude                = ExpIn->Altitude;
    MN                      = ExpIn->MN;
    RefCAN                  = ExpIn->RefCAN;
    OnOffCom                = ExpIn->OnOffCom;
    Reset                   = ExpIn->Reset;
    SkipStart               = ExpIn->SkipStart;
    Authorize               = ExpIn->Authorize; 
    Wf0                     = ExpIn->Wf0;
    LeverMode               = ExpIn->LeverMode;
    Mode                    = ExpIn->Mode; 
    OPRPMManual             = ExpIn->OPRPMManual;
    BoosterLStatus          = ExpIn->BoosterLStatus;
    BoosterRStatus          = ExpIn->BoosterRStatus; 

    // ContStart.StrtRPMAct receives external value only if engine start is to be done manually
    if (Mode == 1)
    {
        ContStart.StrtRPMAct    = ExpIn->StrtRPMAct;
    }

    // EngUnits must be set to 0 if manual engine control (post idle) is done manually
    if (LeverMode != 1)
    {
        EngUnits = 0;
    }
    
    
    // The variables below are not declared outside and must be declared here
    floating valorManete         = ExpIn->valorManete;
    int simMod              = ExpIn->simMod;

    // /*-------------*/
    // /* FADEC RESET */
    // /*-------------*/
    
    // // Resets the FADEC if requested
    // int ResetOK = FADECReset();


/******** COPYFROM START: FADEC_SKIPSTART *********/

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

    /* Stores CAN fault bit value */
	// FaultSSys.SysFaults.CAN_0_Fault = CANFault.SysFaults.CAN_0_Fault;
	// FaultSSys.SysFaults.CAN_1_Fault = CANFault.SysFaults.CAN_1_Fault;

    /* Updates FNpc and allows transition from IDLE to REGIME depending no reference value */
	IdleToRegime(&EngStatus, &ContInput, RefCAN, 0, ContConst.FNIdle, &FNpc, LeverMode);

/******** COPYFROM END: FADEC_SKIPSTART *********/


/* Reads the potentiomenter value if LeverMode == 2 */
	if(LeverMode == 2){
        //FNpc = pot_percent;
        FNpc = valorManete;// / 100.0;   //converts the range from 0%-100% to 0-1

		if(!keys.bits.ac_drive_key == 0)
			FNpc = 0;
//printf("FNpc on if(LeverMode==2) = %f\n", FNpc);

	}

//     Sensors.Ts2[0] = t10;
//     Sensors.Ts2[1] = t11;

//     Sensors.Pt3[0] = (i10 - 1) * 250e+03 + ModelPars.Ps2;   //[PA]        //scaling: Sensor is 4~20mA and 0~10bar (0~1000000Pa). The current is converted to 1~5V and transmitted via CAN.
//                                                                             //Converting 1~5V to 0~1000000Pa: POil = (Voltage - 1) * MaxRange/(4 Volts) = (Voltage - 1) * 1000000/4 = (Voltage - 1) * 250000
// //printf("Sensors.Pt3[0]	 = (i10	 - 1) * 250e+03	 + ModelPars.Ps2\n");
// //printf("%f	 = (%f	 - 1) * 250e+03	 + %f\n", Sensors.Pt3[0], i10, ModelPars.Ps2);

//     Sensors.Vibration[0] = (i11 - 1) * 12.5; //[mm/s]   //scaling: Sensor is 4~20mA and 0~50mm/s. The current is converted to 1~5V and transmitted via CAN.
//                                                         //Converting 1~5V to 0~50mm/s: Vib = (Voltage - 1) * MaxRange/(4 Volts) = (Voltage - 1) * 50/4 = (Voltage - 1) * 12.5

//     Sensors.PFuel[0] = (i12 - 1) * 4e+06; //[PA]        //scaling: Sensor is 4~20mA and 0~160bar (0~16000000Pa). The current is converted to 1~5V and transmitted via CAN.
//                                                         //Converting 1~5V to 0~16000000Pa: PFuel = (Voltage - 1) * MaxRange/(4 Volts) = (Voltage - 1) * 16000000/4 = (Voltage - 1) * 4000000

//     Sensors.POil[0] = (i13 - 1) * 250e+03; //[PA]       //scaling: Sensor is 4~20mA and 0~10bar (0~1000000Pa). The current is converted to 1~5V and transmitted via CAN.
//                                                         //Converting 1~5V to 0~1000000Pa: POil = (Voltage - 1) * MaxRange/(4 Volts) = (Voltage - 1) * 1000000/4 = (Voltage - 1) * 250000

//     //Test bench and HIL sensors
//     /*Sensors.Tt4[0] = t12;
//     Sensors.Tt4[1] = t13;
//     Sensors.Tt4[2] = t14;*/

//     //POC sensors
//     Sensors.Tt4[0] = t12;
//     Sensors.Tt4[1] = t13;
//     Sensors.Tt4[2] = t14;

//     //Bearings sensors
//     Sensors.TBear[0] = t15;
//     Sensors.TBear[1] = t16;
//     Sensors.TBear[2] = t17;


//     Sensors.RPM[0] = r11;
// //Sensors.RPM[1] = r11;       //for now, on testbench there is only one rpm sensor, so the same value will be used on both channels
//     Sensors.RPM[1] = r12;


    /*------------------*/
    /* REAL ENGINE MODE */
    /*------------------*/

    /* If Simulation Mode is "Test Bench", then there is no need to wait for authorize from Model */
    if (simMod == 3)
    {
        Authorize = 1;
    }

    /* Checks for authorization of controller calculations */
    if(Authorize == 1)
    {

/******** COPYFROM START: FADEC_AUTHORIZE1 *********/

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

        //        /* -------------------------------------------------- */
        //        /* AUXILIARY VARIABLE - TMATS                         */
        //        /* (To be usedi in MATLAB and TMATS simulations only) */
        //        /* -------------------------------------------------- */

        //        ContInput.TMATS_StartComplete = TMATS_StartComplete;

        //        /* -------------------------------------------------- */


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
        /*		  sample time in the HIL is defined as Ts				   */
        /*		  															   */
        /*	Taking into account the above considerations, the following steps  */
        /*	must be accomplished:											   */
        /*   - Whenever a matrix pointer is passed as a function argument in   */
        /*     the FADEC, it should be called as function(..., &Matrix, ...)   */
        /*   - Whenever a matrix pointer is passed as a function argument in   */
        /*     the HIL, it should be called as function(..., Matrix, ...)      */
        /*   - The sample time is passed as function(..., Ts, ...) in the 	   */
        /*     FADEC and as function (..., Ts, ...) in the HIL	           */
        /*     			  													   */
        /*=====================================================================*/

        /*--------------------------------------------*/
        /* THERMOCOUPLE FAULT SIMULATION VIA SOFTWARE */
        /*--------------------------------------------*/

        /* Thermocouple fault simulation */
        TCFault(&Sensors, &SoftSimFaults, &FaultSensAuthorize, &Ts2_0, &Ts2_1, &Tt4_0, &Tt4_1, &Tt4_2, &TB_0, &TB_1, &TB_2, ContConst.TCOpen);

        /*-----------------------------------------*/
        /* CONDITION FOR OIL PUMP TO BECOME ACTIVE */
        /*-----------------------------------------*/

//        if(RPM < 1000 & LeverMode == 1)
//        {
//            ContGenOil = ContGenEmpty;
//        }

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

//printf("\nSensors: Alt = %f, MN = %f, dT = %f\n", Altitude,MN,dT);
//printf("Model  : Alt = %f, MN = %f, dT = %f\n", ModelPars.Altitude,ModelPars.MN,ModelPars.dT);
//printf("\nSensors: Ts2 = %f, Pt3 = %f, Tt4 = %f, RPM = %f, Wf = %f", Sensors.Ts2[0],Sensors.Pt3[0],Sensors.Tt4[0],Sensors.RPM[0], Wf);
//printf("Model  : Ts2 = %f, Pt3 = %f, Tt4 = %f, RPM = %f, Wf = %f\n", ModelPars.Ts2,ModelPars.Pt3,ModelPars.Tt4,ModelPars.RPM, ModelPars.Wf);
//printf("MedVals: Ts2 = %f, Pt3 = %f, Tt4 = %f, RPM = %f\n",Ts2MedVal,  Pt3MedVal, Tt4MedVal, RPMMedVal);
//printf("ActiveController: %d\n", ContOutput.Active);

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

 /******** COPYFROM END: FADEC_AUTHORIZE1 *********/

 //FaultSensAuthorize.FaultBits = 0;
 FaultSysAuthorize.FaultBits = 0;
 FaultSysAuthorize.SysFaults.CAN_0_Fault = 1;
 FaultSysAuthorize.SysFaults.CAN_1_Fault = 1;
 HardFAuthorize.DetFaults.POil_0_Fault = 0;
 HardFAuthorize.DetFaults.PFuel_0_Fault = 0;
 HardFAuthorize.DetFaults.Vib_0_Fault = 0;
 HardFAuthorize.FaultBits = 0;

/******** COPYFROM START: FADEC_AUTHORIZE2 *********/

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

/******** COPYFROM END: FADEC_AUTHORIZE2 *********/

        // PrintFaults(&FaultWarning,0,1);
        // PrintFaults(&FaultStatus,1,0);
        // PrintEngStatus(&EngStatus,1);

/******** COPYFROM START: FADEC_AUTHORIZE3 *********/

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
//printf("RealCont: BoostL=%d BoostR=%d Time=%f status=%d Delta=%f Pt3=%f\n",BoosterLStatus, BoosterRStatus, ContInput.TimerBoost, ContInput.statusBooster, Delta, ContInput.Pt3);
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
//printf("Model: BoostL=%d BoostR=%d Time=%f status=%d Delta=%f Pt3=%f\n",BoosterLStatus, BoosterRStatus, ContInModCL.TimerBoost, ContInModCL.statusBooster, Delta, ContInModCL.Pt3);
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
        /* END OF SSModelLoop.c AND PIMMRF_TJ200.c IDENTICAL CODE PIECE */
        /*                                                               */
        /* NOTE: The codes are to be identical except for the considera- */
        /*       tions mentioned at the note above                       */
        /*===============================================================*/

/******** COPYFROM END: FADEC_AUTHORIZE3 *********/

        /*-----------------------------*/
        /* WRITES OUTPUTS IN STRUCTURE */
        /*-----------------------------*/

        /* Updates das saídas */
            // 1 - Wf                           (Fuel flow value - musst normalize)
            // 2 - ContStart.StrtRPMAct         (Oil pump rpm - must normalize)
            // 3 - digital.out                  (digital outputs)
            // 4 - EngStatus.EngineStatus       (Engine status variable)

            /* OUTPUT STRUCTS */

            ExpOut->FaultStatus = FaultStatus;
            ExpOut->FaultWarning = FaultWarning;

            /* OUTPUT VARIABLES */

            ExpOut->Wf = Wf;
            ExpOut->digitalout = digital;
            ExpOut->StrRPMAct = ContStart.StrtRPMAct;
            ExpOut->EngineStatus = EngStatus.EngineStatus;
            //ExpOut->ResetOK = ResetOK;

    }

}
