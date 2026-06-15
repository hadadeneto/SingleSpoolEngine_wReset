#define VERSAO_DO_DIA "VERSAO DO DIA 30/05/2023"

#include <iostream>
#include <cstdlib>

// includes to send a raw can message via socket can
#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/can.h>
#include <linux/can/raw.h>

//include to create threads (for file saving, CAN1 message transmission/reception, etc)
#include <pthread.h>

// include to save data on file
#include <fstream>
#include <chrono>

/*
 * We're going to use messages of type uavcan.protocol.debug.KeyValue, so the appropriate header must be included.
 * Given a data type named X, the header file name would be:
 *      X.replace('.', '/') + ".hpp"
 */
#include <uavcan/uavcan.hpp>
#include <uavcan/protocol/node_status_monitor.hpp>      // For uavcan::NodeStatusMonitor
#include <uavcan_linux/uavcan_linux.hpp>
#include <uavcan/protocol/debug/KeyValue.hpp> // uavcan.protocol.debug.KeyValue
#include <uavcan/protocol/debug/LogMessage.hpp>

#include <math.h>

/********* Files to send debug strings via serial *************/
#include <stdio.h>	//standard input/output functions
#include <stdlib.h>
#include <string.h>	//string function definitions
#include <unistd.h>	//UNIX standard function definitions
#include <fcntl.h>	//File control definitions
#include <errno.h>	//Error number definitions
#include <termios.h>	//POSIX terminal control definitions
/***************************************************************/

/********* Motor Model Includes ********************************************/
extern "C"
{

/*-------------------*/
/* STANDARD INCLUDES */
/*-------------------*/

/* Standard includes - Total of 04 files currently */
#include <inttypes.h>
//#include <math.h>
#include <stdint.h>
//#include <stdio.h>
//#include <string.h>

/*----------------------------------------------*/
/* COMMON INCLUDES - USED BY BOTH FADEC AND HIL */
/*----------------------------------------------*/

/* Created .h files - Total of 19 files currently */
#include "ModelCFunc/Ambient_TMATS.h"          /* Adapted from T-MATS */
#include "ModelCFunc/constants_TMATS.h"        /* Adapted from T-MATS */
#include "ModelCFunc/Control_Types.h"          /* Controller calculations */
#include "ModelCFunc/ControlFunctions.h"       /* Controller calculations */
#include "ModelCFunc/DigitalOutDefs.h"         /* Controller calculations */
#include "ModelCFunc/Env_SampTime.h"           /* General Calculations*/
#include "ModelCFunc/FailSafeFunctions.h"      /* Fault analysis */
#include "ModelCFunc/FaultSim_Types.h"         /* Fault analysis */
#include "ModelCFunc/functions_TMATS.h"        /* Adapted from T-MATS */
#include "ModelCFunc/Interpolation_Types.h"    /* General Calculations*/
#include "ModelCFunc/IO_Types.h"               /* Controller calculations */
#include "ModelCFunc/LinMtxFunctions.h"        /* General Calculations*/
#include "ModelCFunc/Model_Types.h"            /* Used for model calculations */
#include "ModelCFunc/MtxIntFunctions.h"        /* General Calculations*/
#include "ModelCFunc/PIMinMaxRF.h"             /* Controller calculations */
//#include "ModelCFunc/PIOil.h"                  /* Controller calculations */
#include "ModelCFunc/ShutDownFunctions.h"      /* Controller calculations */
#include "ModelCFunc/StartingFunctions.h"      /* Controller calculations */
#include "ModelCFunc/TCFault.h"                /* Fault analysis */

/*----------------------------------*/
/* HIL INCLUDES - NOT USED BY FADEC */
/*----------------------------------*/

/* Created .h files - Total of 10 files currently */
#include "ModelCFunc/BearingModel.h"			/* Bearing model functions */
#include "ModelCFunc/ContSoftLoop.h"			/* Functions of individuals PI controllers for the different engines - NO LONGER USED! */
#include "ModelCFunc/EngineModel.h"             /* Funciton for engine model simulation */
#include "ModelCFunc/FaultSimFunctions.h"		/* Functions for fault simulations */
#include "ModelCFunc/getContConst.h"			/* Functions for loading controller constants for each individual engine depending on user's choice */
#include "ModelCFunc/getEngConst.h"             /* Loading of engine constants */
#include "ModelCFunc/getMtx.h"                  /* Functions for loading matrices for different engines depending on user's choice */
#include "ModelCFunc/getStartPars.h"            /* Starting parameters */
#include "ModelCFunc/InitCond.h"                /* Function for calculating simulation initial conditions */
#include "ModelCFunc/PeripheralDyn.h"			/* Perypherals' dynamics functions */

}

/******************************************************************************************/

/********************************************************************************************/
/*
 *                  UAVCAN COMMUNICATION DEFINES AND VARIABLES
 */
/********************************************************************************************/

//declaração das variáveis das leituras recebidas via UAVCAN
float   i11, i12, i13, i14,                         // Analog Inputs
        o1a, o1b, o1c, o1d,                         // Loopback from Analog Outputs: 1=a, 2=b, 3=c, 4=d
        t11, t12, t13, t14, t15, t16, t17, t18,     // Thermocouple Temperature Value
        t1a, t1b, t1c, t1d, t1e, t1f, t1g, t1h,     // Thermocouple Cold Juntion Value: 1=a, 2=b, ... , 8=h
        d11_float, d21_float,                       // entradas digitais no formato float, posterior conversão para int
        r11, r12,                                   // valor do RPM-A e RPM-B
        model_d1, model_mf, model_oilFlow, model_i2, model_i3, ambientTemp_float, engine_float;							// variaveis do modelo
float 	reference = 0;//0.45;
float 	Altitude0 = 0;
float	MN0 = 0;
float	dT0 = 0;	//initial conditions
float	reference0 = 0;//0.45;
float 	authorize_float, skipStart_float;	//receives the authorize and skip start commands on float format, for later conversion to int
float 	simMod_float;		//float number of Simulation Mode (SIL or HIL), converted to uint later
float	thermoSim_coldJunction = 25;	//receives the cold junction temperature from FADEC, to use on thermocouple simulation
unsigned int simMod = 0;    //0 = SIL, 1 = HIL Async, 2 = HIL Sync, 3 = Test Bench		//set if the simulation will be Software In the Loop (SIL) or Hardware In the Loop (HIL)
unsigned int model_d1_toInt = 0;	//converts the float number corresponding to digital inputs to integer

unsigned long upTime_ms =  0;	//the upTime_ms variable measures the time since the system has been started in milliseconds
                                //and sends on "upd" keyValue message
unsigned long lastUpdateTime_ms =  0;	//the upTime_ms variable measures the time since the system has been started in milliseconds
                                //and sends on "upd" keyValue message
unsigned long syncTime_ms = 0;   //the syncTime_ms is used on HIL Sync Mode. Represents the sync time sent by FADEC, in miliseconds.
                                //syncTime_ms is also used to confirm that no sync message has been lost.
unsigned long lastSyncTime_ms = 0;   //stores the last time in miliseconds that the model was synced on HIL Sync Mode.
int tickFromFADEC = 0; //stores the TICK sent by FADEC
int flagSync = 0;   //flag used on Sync message over SIATT CAN protocol.

unsigned int lastTime_rcvOBCmsg_ms = 0;    //holds the last time in milliseconds that the OBC_FADEC_THRUST_MACH_ALT_CANID has been received from OBC

uavcan::MonotonicTime monotonicTimer_initialValue;

std::string keyMessage;	//only for debug

/********************************************************************************************/
/*
 *                  END OF UAVCAN COMMUNICATION DEFINES AND VARIABLES
 */
/********************************************************************************************/

/********************************************************************************************/
/*
 *                  OBC COMMUNICATION DEFINES AND VARIABLES
 */
/********************************************************************************************/
unsigned long tempo1, tempo2, tempo3, tempo4, tempo5, tempo6, tempo7, tempo8, tempo9;

std::ofstream tempos;      //arquivo com os tempos medidos
std::ifstream testFileExistence;        // used on test if file already exists. If file exists, create a new file with a sequencial number suffix.
std::string filename = "/home/root/Desktop/ModelTelemetry/tempos.csv";     //initial file name
int flag_updFile = 0;
//int flag_syncFile = 0;
unsigned int last_saveTelemetryFile_ms = 0;     //holds the last time the telemetry was saved.


struct timespec initialTime;                //initial monotonic timer value, for time elapsed calculation
struct timespec actualTime;                 //actual monotonic timer value, for time elapsed calculation
unsigned long upTime_sendATDPOCmsg_ms = 0;  //time elapsed in millisecond from the start or last reset
unsigned long last_sendATDPOCmsg_ms = 0;    //the last time the function has been executed

#define CAN0 0
#define CAN1 1
#define UPDATE_TIMERATE_MS                  200     //control loop or engine model calculation loop interval
#define SYNC_UPDATE_TIMERATE_MS             200     //value of time to add to upTime_ms when using HIL Sync Mode.

#define FADEC_STATUS_CANID                  0xF2A1001
#define FADEC_TLM_1_CANID                   0xF321000
#define FADEC_TLM_2_CANID                   0xF3A1000
#define FADEC_TLM_FAILURE_CODES_CANID       0xF421000
#define FADEC_TLM_WARNING_CODES_CANID       0xF4A1000
#define FADEC_OBC_ESTIMATED_THRUST_CANID 	0xFE21001

#define OBC_FADEC_THRUST_MACH_ALT_CANID		0x8908008
#define OBC_FADEC_ENGINE_CMD_CANID          0x8B08008
#define HILS_FADEC_RESET_CANID              0xFCF8008
#define TLM_OBC_BOOSTER_SEP                 0x8068001

#define OBC_FADEC_HEARTBEAT_TIMEOUT         1000         //after 1000ms not receiving the OBC_FADEC_THRUST_MACH_ALT_CANID message from OBC, FADEC assumes the communication is lost and sets CANFault.DetFaults.CAN_x_Fault bit.

#define FADEC_SKIPSTART_AUTHORIZE_COMMAND   0xF321100
#define MODEL_TS2_SENSOR                    0xF321101
#define FADEC_DIG_INPUTS_OUTPUTS            0xF321102
#define FADEC_RPMA_RPMB                     0xF321103
#define FADEC_AN_INPUTS                     0xF321104
#define FADEC_AN_OUTPUTS                    0xF321105
#define FADEC_THERMOCOUPLE_1_4              0xF321106
#define FADEC_THERMOCOUPLE_5_8              0xF321107
#define FADEC_SIM_FAILURE_CODES_CANID       0xF321008
//#define FADEC_RESET_COMMAND                 0xF321010

#define FADEC_OBC_TIMERATE_MS               200             //interval for sending messages to OBC.
#define FADEC_TLM_2_CANMSG_PERIOD_MS        1000            //only the message TLM_2 has a different interval.
#define FADEC_SAVE_TELEMETRY_FILE_PERIOD_MS 1000

#define CAN_29BIT_ID_MASK                   0x1FFFFFFF

// FADEC Status, used to sync on HIL Sync Mode
union fadec_status
{
    struct
    {
        uint16_t fuelFlow;
        uint16_t TurbineChamberTemperature;
        uint16_t oilPressure;
        uint8_t pFuel;
        uint8_t fadecState;
    } value;

    uint8_t valueInBytes[8];
}fadecStatus;

// FADEC variables to Telemetry 1
union fadec_tlm_1
{
    struct
    {
        uint16_t rotationSpeed;
        uint16_t compressorInletTotalTemperature;
        uint16_t vibration;
        uint16_t combustionChamberStaticPressure;
    } value;

    uint8_t valueInBytes[8];
};

// FADEC variables to Telemetry 2
union fadec_tlm_2
{
    struct
    {
        uint16_t bearing_0_temperature;
        uint16_t bearing_1_temperature;
        uint16_t bearing_2_temperature;
    } value;

    uint8_t valueInBytes[6];
};

//FADEC Estimated thrust
union fadec_obc_estimated_thrust
{
    struct
    {
        uint16_t estimated_thrust;
    } value;

    uint8_t valueInBytes[2];
};

//OBC Thrust Command, Mach Number and Estimated Altitude, from OBC
union estimatedAlt_union
{
    float value_in_float;
    uint8_t value_in_bytes[4];
} estimatedAlt;

union net_thrust_cmd_union
{
    uint16_t value_in_uint16;
    uint8_t value_in_bytes[2];
} net_thrust_cmd;

uint8_t machNumber_uint8;

//OBC Engine Start, Engine Shut Down and Emergency Shut Down Command, from OBC
int engineCommandFromATDPOC;

//FADEC Failure Codes
union fadec_tlm_failure_codes
{
//    struct Faults
//    {

//        /* SENSOR FAILURES */

//        /*Ts2 sensor 1 possible faults - Bits 0 to 2*/
//        uint8_t Ts2_0_SCV       :1;
//        uint8_t Ts2_0_SCG       :1;
//        uint8_t Ts2_0_Open      :1;

//        /*Ts2 sensor 2 possible faults - Bits 3 to 5*/
//        uint8_t Ts2_1_SCV       :1;
//        uint8_t Ts2_1_SCG       :1;
//        uint8_t Ts2_1_Open      :1;

//        /*Pt3 sensor 1 possible faults - Bits 6 to 7*/
//        uint8_t Pt3_0_Short     :1;
//        uint8_t Pt3_0_Open      :1;

//        /*Tt4 sensor 1 possible faults - Bits 8 to 10*/
//        uint8_t Tt4_0_SCV       :1;
//        uint8_t Tt4_0_SCG       :1;
//        uint8_t Tt4_0_Open      :1;

//        /*Tt4 sensor 2 possible faults - Bits 11 to 13*/
//        uint8_t Tt4_1_SCV       :1;
//        uint8_t Tt4_1_SCG       :1;
//        uint8_t Tt4_1_Open      :1;

//        /*Tt4 sensor 3 possible faults - Bits 14 to 16*/
//        uint8_t Tt4_2_SCV       :1;
//        uint8_t Tt4_2_SCG       :1;
//        uint8_t Tt4_2_Open      :1;

//        /*RPM sensor 1 possible faults - Bits 17 to 20*/
//        uint8_t RPM_0_Short     :1;
//        uint8_t RPM_0_Open      :1;
//        uint8_t RPM_0_1PLoss    :1;
//        uint8_t RPM_0_2PLoss    :1;

//        /*RPM sensor 2 possible faults - Bits 21 to 24*/
//        uint8_t RPM_1_Short     :1;
//        uint8_t RPM_1_Open      :1;
//        uint8_t RPM_1_1PLoss    :1;
//        uint8_t RPM_1_2PLoss    :1;

//       /*POil sensor 1 possible faults - Bits 25 to 26*/
//        uint8_t POil_0_Short    :1;
//        uint8_t POil_0_Open     :1;

//        /* PFuel sensor 1 possible faults - Bits 27 to 28*/
//        uint8_t PFuel_0_Short   :1;
//        uint8_t PFuel_0_Open    :1;

//        /* Vibration sensor 1 possible faults - Bits 29 to 30*/
//        uint8_t Vib_0_Short     :1;
//        uint8_t Vib_0_Open      :1;

//        /* SYSTEM FAILURES */

//        /* Lubrication system faults - Bits 31 to 32*/
//        uint8_t POil_High       :1;
//        uint8_t POil_Low        :1;

//        /* Fuel system faults - Bits 33 to 34 */
//        uint8_t PFuel_High      :1;
//        uint8_t PFuel_Low       :1;

//        /* Engine Blowout - Bit 35 */
//        uint8_t BlowOut         :1;

//        /* Mec system faults - Bits 36 to 40*/
//        uint8_t VibrationHigh   :1;
//        uint8_t Mec_Lock        :1;
//        uint8_t OverTemp        :1;
//        uint8_t OverSpeed       :1;
//        uint8_t Ignition        :1;

//        /* Sensors bias - Bits 41 to 51 */
//        uint8_t Ts2_0_Bias      :1;
//        uint8_t Ts2_1_Bias      :1;
//        uint8_t Pt3_0_Bias      :1;
//        uint8_t Tt4_0_Bias      :1;
//        uint8_t Tt4_1_Bias      :1;
//        uint8_t Tt4_2_Bias      :1;
//        uint8_t RPM_0_Bias      :1;
//        uint8_t RPM_1_Bias      :1;
//        uint8_t POil_0_Bias     :1;
//        uint8_t PFuel_0_Bias    :1;
//        uint8_t Vib_0_Bias      :1;

//        /* Bit indicating that thermocouple faults are simulated by software - Bit 52 */
//        /* The float number MATLAB is able to work with must contain 53 bits or less.
//        Therefore, the position of TCFaultSoftSim was placed at bit 52 (last bit
//        countig from 0)  */
//        uint8_t TCFaultSoftSim  :1;

//        /* Reserved bits - Bits 53 to 63 */
//        uint16_t NotUsedBits     :11;

//    } Faults;

    EngineFaults Faults;

    uint8_t valueInBytes[8];

    uint64_t valueUint64;
};

fadec_tlm_failure_codes faultsCANmsg;

//FADEC Reset Command
union init_estimatedAlt_union
{
   uint16_t value_in_uint16;
   uint8_t value_in_bytes[2];
} init_estimatedAlt;

union init_net_thrust_cmd_union
{
   uint16_t value_in_uint16;
   uint8_t value_in_bytes[2];
} init_net_thrust_cmd;

union reset_mode
{
   struct
   {
       uint8_t starting_mode : 2;
       uint8_t engine : 2;
       uint8_t lever_mode : 2;
       uint8_t simulation_mode : 2;
   } value;

   uint8_t valueInByte;
}resetMode;

uint8_t init_machNumber_uint8;     //mach number on OBD to FADEC Messages is on percent (0% ~ 100%), so multiplies the 0~1 by 100
uint8_t init_dT = 0;

//Booster Separation Message
union booster_sep
{
   struct
   {
       uint8_t leftBoosterSwitch;
       uint8_t rightBoosterSwitch;
   } value;

   uint16_t valueInUint16;
}booster_separation;

/********************************************************************************************/
/*
 *                 END OF OBC COMMUNICATION DEFINES AND VARIABLES
 */
/********************************************************************************************/


/******** Model Variables Declaration ****************************************/

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

/* REQUIRED INITIALIZATIONS */

//SoftSimFaults = FaultSensEmpty;						   /* Union - Thermocouple full scale simulation */

///* Each union is initiated with null values */
//Ts2_0.TCFaultBits = 0;
//Ts2_1.TCFaultBits = 0;
//Tt4_0.TCFaultBits = 0;
//Tt4_1.TCFaultBits = 0;
//Tt4_2.TCFaultBits = 0;
//TB_0.TCFaultBits = 0;
//TB_1.TCFaultBits = 0;
//TB_2.TCFaultBits = 0;

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
//double reference = 0.35;                            /* Reference value used initially */
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

int Alt_Elem = 0;                                   /* Number of altitude elements */
int AS_Elem = 0;                                    /* Number of acceleration schedule elements */
int Fn_Elem = 0;                                    /* Number of Fn elements */
int HILMode = 0;                                    /* Hardware in the Loop Mode */
int i = 0;                                          /* Loop index variable */
int MN_Elem = 0;                                    /* Number of Mach number elements */
int NcFANMap_Elem = 0;                              /* Number of Nc elements - fan map */
int NcHPCMap_Elem = 0;                              /* Number of Nc elements - high power compressor map */
int NcHPTMap_Elem = 0;                              /* Number of Nc elements - turbine map */
int PowerMan_Elem = 0;                              /* Number of total steady operating points used for Power Management Controller - all altitudes */
int PRHPTMap_Elem = 0;                              /* Number of pressure ratio elements - turbine map */
int SteadyOp_Elem = 0;                              /* Number of steady operating points used for linearization at Sea Level */
int TsampDiv = 10;                                  /* Possibility of lower sampling time for the model */
int Wc_per_Nc_FAN = 0;                              /* Number of pressure ratio elements - fan map */
int Wc_per_Nc_HPC = 0;                              /* Number of pressure ratio elements - high power compressor map */
int WcFANMap_Elem = 0;                              /* Number of Wc elements - fan map */
int WcHPCMap_Elem = 0;                              /* Number of Wc elements - high power compressor map */
int WcHPTMap_Elem = 0;                              /* Number of Wc elements - turbine map */
int WhichEngine = 1;                                /* Flag defining the engine to be simulated */

/* static int TYPE */

static int bit_start = 0;							/* Starting flag */

/* double TYPE */

double BPFAN = 0;                                   /* Fan bypass ratio */
double Fg = 0;                                      /* Engine gross thrust */
double Fn = 0;                                      /* Engine net thrust */
double FNpc0 = 0;                                   /* Initial percent net thrust reference */
double MN8 = 0;                                     /* Nozzle thruat gas Mach number */
double Mwm = 0.3;                                   /* Mach number value for windmill simulation - currently used as 0.3 */
double NcFAN = 0;                                   /* Fan corrected rotation speed */
double NcHPC = 0;                                   /* Compressor corrected rotation speed */
double P0 = 101325;                                 /* Ambient pressure */
double PRFAN = 1;                                   /* Fan pressure ratio */
double PRHPC = 1;                                   /* Compressor pressure ratio */
double Pt21 = 101325;                               /* Fan exhaust total pressure */
double Pt4 = 101325;                                /* Burner exhaust total pressure */
double Pt5 = 101325;                                /* Turbine exhaust total pressure */
double Pt6 = 101325;                                /* Mixer exhaust total pressure */
double SMFAN = 25;                                  /* Fan stall margin */
double SMHPC = 25;                                  /* Compressor stall margin */
double TCOpen = ContConst.TCOpen;                   /* Thermocouple value when open-circuited */
double TsamModel = 0.001 * TICK / TsampDiv;         /* Model sampling time */
double Tsample = 0.001 * TICK;                      /* Sampling Time */
double Tt21 = 288.15;                               /* Fan exhaust total temperature */
double Tt3 = 288.15;                                /* Compressor exhaust total temperature */
double Tt6 = 288.15;                                /* Mixer exhaust total temperature */
double V8 = 0;                                      /* Nozzle throat gas speed */
double W2 = 0;                                      /* Compressor inlet air flow */
double W21 = 0;                                     /* Fan exhaust air flow */
double W8 = 0;                                      /* Nozzle exhaust gas mass flow */
double WcFAN = 0;                                   /* Fan inlet corrected air flow */
double WcHPC = 0;                                   /* Compressor inlet corrected air mass flow */
double WfMax_Pump = 0;                              /* Maximum pump fuel flow value */

/* static double TYPE */

static double fValue = 0;							/* Fuel flow value */

/* double (*) TYPE  */

double *AltLinVec;                                  /* Controller and Model - Altitude break points  */
double *AMtx;                                       /* Model - pointer for A matrix */
double *AshMtx;                                     /* Model - pointer for hot sub idle Ash matrix */
double *ASVec;                                      /* Controller - Asceleration schedule (ASVec) break points */
double *AwmMtx;                                     /* Model - pointer for windmill Awm matrix */
double *BMtx;                                       /* Model - pointer for B matrix */
double *BshMtx;                                     /* Model - pointer for hot sub idle Bsh matrix */
double *BwmMtx;                                     /* Model - pointer for wind mill Bwm matrix */
double *DeltaMtx;                                   /* Controller and Model - Delta break points  */
double *DeltaMtx1D;                                 /* Auxiliar matrix - Delta */
double *DeltaMtx1DH;                                /* Auxiliar matrix - Delta */
double *DeltaMtx2D;                                 /* Auxiliar matrix - Delta */
double *DeltaMtx2DH;                                /* Auxiliar matrix - Delta */
double *DSVec;                                      /* Controller - Deceleration schedule (DSVec) break points */
double *EffFANMapMtx;                               /* Model - pointer for Efficiency values matrix - fan map */
double *EffHPCMapMtx;                               /* Model - pointer for Efficiency values matrix - HPC map */
double *EffHPTMapMtx;                               /* Model - pointer for Efficiency values matrix - HPT map */
double *FNcMaxContMtx;                              /* Controller - pointer for maximum net thrust breakpoint values */
double *FNperContMtx;                               /* Controller - pointer for net thrust percent breakpoint values */
double *MapFAN1D;                                   /* Auxiliar matrix - fan map */
double *MapFAN1DH;                                  /* Auxiliar matrix - fan map */
double *MapFAN2D;                                   /* Auxiliar matrix - fan map */
double *MapFAN2DH;                                  /* Auxiliar matrix - fan map */
double *MapHPC1D;                                   /* Auxiliar matrix - HPC map */
double *MapHPC1DH;                                  /* Auxiliar matrix - HPC map */
double *MapHPC2D;                                   /* Auxiliar matrix - HPC map */
double *MapHPC2DH;                                  /* Auxiliar matrix - HPC map */
double *MNLinVec;                                   /* Controller and Model - Mach number break points */
double *Mtx1D;                                      /* Auxiliar matrix */
double *Mtx1DH;                                     /* Auxiliar matrix */
double *Mtx2D;                                      /* Auxiliar matrix */
double *Mtx2DH;                                     /* Auxiliar matrix */
double *N_KiMtx;                                    /* Controller - pointer for Ki matrix of N control law */
double *N_KpMtx;                                    /* Controller - pointer for Kp matrix of N control law */
double *NcFANContMtx;                               /* Controller - pointer for fan Nc breakpoint values */
double *NcFANMapMtx;                                /* Model - pointer for Nc values matrix - fan map */
double *NcHPCMapMtx;                                /* Model - pointer for Nc values matrix - HPC map */
double *NcHPTMapMtx;                                /* Model - pointer for Nc values matrix - HPT map */
double *NcMtx;                                      /* Model - pointer for Nc matrix */
double *NcVec;                                      /* Controller - Nc schedule (for ASVec and DSVec) break points  */
double *PRFANMapMtx;                                /* Model - pointer for PR values matrix - fan map */
double *PRFANStallMtx;                              /* Model - pointer for PR stall values matrix - fan map */
double *PRHPCMapMtx;                                /* Model - pointer for PR values matrix - HPC map */
double *PRHPCStallMtx;                              /* Model - pointer for PR stall values matrix - HPC map */
double *PRHPTMapMtx;                                /* Model - pointer for PR values matrix - HPT map */
double *Pt21DMtx;                                   /* Model - pointer for Pt21D matrix */
double *Pt21Mtx;                                    /* Model - pointer for Pt21 matrix */
double *Pt3DMtx;                                    /* Model - pointer for Pt3D matrix */
double *Pt3Mtx;                                     /* Model - pointer for Pt3 matrix */
double *Pt5DMtx;                                    /* Model - pointer for Pt5D matrix */
double *Pt5Mtx;                                     /* Model - pointer for Pt5 matrix */
double *Pt6DMtx;                                    /* Model - pointer for Pt6D matrix */
double *Pt6Mtx;                                     /* Model - pointer for Pt6 matrix */
double *RPMshMtx;                                   /* Model - pointer for hot sub idle RPMsh matrix */
double *RPMwmMtx;                                   /* Model - pointer for windmill RPMwm matrix */
double *Ts0Mtx;                                     /* Controller and Model - pointer Ts0 break points  */
double *Ts0Mtx1D;                                   /* Auxiliar matrix - Ts0 */
double *Ts0Mtx1DH;                                  /* Auxiliar matrix - Ts0 */
double *Ts0Mtx2D;                                   /* Auxiliar matrix - Ts0 */
double *Ts0Mtx2DH;                                  /* Auxiliar matrix - Ts0 */
double *Tt21DMtx;                                   /* Model - pointer for Tt21D matrix */
double *Tt21Mtx;                                    /* Model - pointer for Nc matrix */
double *Tt3DMtx;                                    /* Model - pointer for Tt3D matrix */
double *Tt3Mtx;                                     /* Model - pointer for Tt3 matrix */
double *Tt4CshMtx;                                  /* Model - pointer for hot sub idle Tt4Csh matrix */
double *Tt4DMtx;                                    /* Model - pointer for Tt4D matrix */
double *Tt4DshMtx;                                  /* Model - pointer for hot sub idle Tt4Dsh matrix */
double *Tt4Mtx;                                     /* Model - pointer for Tt4 matrix */
double *Tt4shMtx;                                   /* Model - pointer for hot sub idle Tt4sh matrix */
double *Tt5DMtx;                                    /* Model - pointer for Tt5D matrix */
double *Tt5Mtx;                                     /* Model - pointer for Tt5 matrix */
double *Tt6DMtx;                                    /* Model - pointer for Tt6D matrix */
double *Tt6Mtx;                                     /* Model - pointer for Tt6 matrix */
double *WcFANMapMtx;                                /* Model - pointer for Wc values matrix - fan map */
double *WcFANStallMtx;                              /* Model - pointer for Nc stall values matrix - fan map */
double *WcHPCMapMtx;                                /* Model - pointer for Wc values matrix - HPC map */
double *WcHPCStallMtx;                              /* Model - pointer for Wc stall values matrix - HPC map */
double *WcHPTMapMtx;                                /* Model - pointer for Wc values matrix - HPT map */
double *WfMtx;                                      /* Model - pointer for Wf matrix */
double *WfshMtx;                                    /* Model - pointer for hot sub idle Wfsh matrix */

/*---------------------------------------------------------------------------------------*/
/* BEARING MODEL VARIABLES - MUST BE INCORPORATED AT CONSTANTS ONCE VALIDATED */
/*---------------------------------------------------------------------------------------*/

/* NOTE: Currently, the three bearigs are common to all engines simulated by the software.
    In a near future, when the current model or a final model is validated to be used as a
    mathematical description of a bearing, the model parameters must be treated by the functions
    getXXXMtx and getXXXContConst */

// /* Engine RPM vector */
// double RPMEVec[3] = {0, 20000, 23000};				/* Engine rotation speed breakpoints (RPME) */

// /* Bearing 0 data */
// double DelT_Bear0[3] = {1, 100, 130};				/* Temperature decrease if maximum oil flow is used at given RPME */
// double TNOil_Bear0[3] = {300, 450, 573};			/* Temperature reached if no oil is used at the given RPME */

// /* Bearing 1 data */
// double DelT_Bear1[3] = {1, 40, 120};				/* Temperature decrease if maximum oil flow is used at given RPME */
// double TNOil_Bear1[3] = {300, 400, 530};			/* Temperature reached if no oil is used at the given RPME */

// /* Bearing 2 Data */
// double DelT_Bear2[3] = {1, 50, 110};				/* Temperature decrease if maximum oil flow is used at given RPME */
// double TNOil_Bear2[3] = {300, 410, 540};			/* Temperature reached if no oil is used at the given RPME */

/* Engine RPM vector */
double RPMEVec[3] = {0, 20000, 23000};				/* Engine rotation speed breakpoints (RPME) */

/* Bearing 0 data */
double DelT_Bear0[3] = {1, 50, 20};                 /* Temperature decrease if maximum oil flow is used at given RPME */
double TNOil_Bear0[3] = {300, 415, 450};			/* Temperature reached if no oil is used at the given RPME */

/* Bearing 1 data */
double DelT_Bear1[3] = {1, 40, 70};                 /* Temperature decrease if maximum oil flow is used at given RPME */
double TNOil_Bear1[3] = {300, 400, 480};			/* Temperature reached if no oil is used at the given RPME */

/* Bearing 2 Data */
double DelT_Bear2[3] = {1, 50, 50};                 /* Temperature decrease if maximum oil flow is used at given RPME */
double TNOil_Bear2[3] = {300, 410, 480};			/* Temperature reached if no oil is used at the given RPME */

static BearingPars Bear0;
static BearingPars Bear1;
static BearingPars Bear2;
static BearingPars BearEmpty = {0};

/****************************************************************************************/


/********************************************************************************************/
/*
 *                 UAVCAN NODE FUNCTIONS DECLARATION
 */
/********************************************************************************************/

/**
 * These functions are platform dependent, so they are not included in this example.
 * Refer to the relevant platform documentation to learn how to implement them.
 */
//extern uavcan::ICanDriver& getCanDriverCAN0();      //CAN0 used to internal and external (supervisory) communication
//extern uavcan::ICanDriver& getCanDriverCAN1();    //CAN1 used only for SIATT's protocol
//extern uavcan::ISystemClock& getSystemClock();

/**
 * Memory pool size largely depends on the number of CAN ifaces and on application's logic.
 * Please read the documentation for the class uavcan::Node to learn more.
 */
//constexpr unsigned NodeMemoryPoolSize = 16384;

//typedef uavcan::Node<NodeMemoryPoolSize> Node;

/**
 * Node object will be constructed at the time of the first access.
 * Note that most library objects are noncopyable (e.g. publishers, subscribers, servers, callers, timers, ...).
 * Attempt to copy a noncopyable object causes compilation failure.
 */

//static Node& getNodeCAN0()
//{
//    static Node nodeCAN0(getCanDriverCAN0(), getSystemClock());
//    return nodeCAN0;
//}

/*static Node& getNodeCAN1()
{
    static Node nodeCAN1(getCanDriverCAN1(), getSystemClock());
    return nodeCAN1;
}*/


void sendUAVCANKeyValueMsg(uavcan_linux::NodePtr& node, char keyID[3], float value);    //send KeyValue messages over UAVCAN.
void EngineModelUpdate(uavcan_linux::NodePtr& node0, int can_atd_poc);                  //model calculation loop


/**************************** NODE STATUS MONITORING **********************************************/
/**
 * This class implements a passive node monitor.
 * There's a basic node monitor implementation in the library: uavcan::NodeStatusMonitor
 * Extension through inheritance allows to add more complex logic to it.
 */
class NodeMonitor : public uavcan::NodeStatusMonitor
{
    /**
     * This method is not required to implement.
     * It is called when a remote node becomes online, changes status, or goes offline.
     */
    void handleNodeStatusChange(const NodeStatusChangeEvent& event) override
    {
        if (event.was_known)
        {
            std::cout << "Node " << int(event.node_id.get()) << " has changed status from "
                      << modeToString(event.old_status) << "/" << healthToString(event.old_status)
                      << " to "
                      << modeToString(event.status) << "/" << healthToString(event.status)
                      << std::endl;

            /*fadecSensorsDataFile << "Node " << int(event.node_id.get()) << " has changed status from "          //writes also in fadec telemetry file
                                << modeToString(event.old_status) << "/" << healthToString(event.old_status)
                                << " to "
                                << modeToString(event.status) << "/" << healthToString(event.status)
                                << std::endl;*/

            if(event.status.mode != uavcan::protocol::NodeStatus::MODE_OPERATIONAL)     //if the node that has changed is not on operational status
            {
                printf("TAKE ACTION TO NODE %d STATUS!\n", event.node_id.get());
                CANFault.DetFaults.CAN_0_Fault = 1;
            }
        }
        else
        {
            std::cout << "Node " << int(event.node_id.get()) << " has just appeared with status "
                      << modeToString(event.status) << "/" << healthToString(event.status)
                      << std::endl;

        }

    }

    /**
     * This method is not required to implement.
     * It is called for every received message uavcan.protocol.NodeStatus after handleNodeStatusChange(), even
     * if the status code has not changed.
     */
    void handleNodeStatusMessage(const uavcan::ReceivedDataStructure<uavcan::protocol::NodeStatus>& msg) override
    {
        (void)msg;
        //std::cout << "Remote node status message\n" << msg << std::endl << std::endl;
    }

public:
    NodeMonitor(uavcan::INode& node) :
        uavcan::NodeStatusMonitor(node)
    { }

    static const char* modeToString(const NodeStatus status)
    {
        switch (status.mode)
        {
        case uavcan::protocol::NodeStatus::MODE_OPERATIONAL:     return "OPERATIONAL";
        case uavcan::protocol::NodeStatus::MODE_INITIALIZATION:  return "INITIALIZATION";
        case uavcan::protocol::NodeStatus::MODE_MAINTENANCE:     return "MAINTENANCE";
        case uavcan::protocol::NodeStatus::MODE_SOFTWARE_UPDATE: return "SOFTWARE_UPDATE";
        case uavcan::protocol::NodeStatus::MODE_OFFLINE:         return "OFFLINE";
        default: return "???";
        }
    }

    static const char* healthToString(const NodeStatus status)
    {
        switch (status.health)
        {
        case uavcan::protocol::NodeStatus::HEALTH_OK:       return "OK";
        case uavcan::protocol::NodeStatus::HEALTH_WARNING:  return "WARNING";
        case uavcan::protocol::NodeStatus::HEALTH_ERROR:    return "ERROR";
        case uavcan::protocol::NodeStatus::HEALTH_CRITICAL: return "CRITICAL";
        default: return "???";
        }
    }
};
/**************************** END OF NODE STATUS MONITORING **********************************************/

void sendUAVCANKeyValueMsg(uavcan_linux::NodePtr& node, char keyID[3], float value)
{

    uavcan::protocol::debug::KeyValue keyValue_msg;  // Always zero initialized

    keyValue_msg.value = value;
    keyValue_msg.key = keyID;

    /*
     * Arrays in DSDL types are quite extensive in the sense that they can be static,
     * or dynamic (no heap needed - all memory is pre-allocated), or they can emulate std::string.
     * The last one is called string-like arrays.
     * ASCII strings can be directly assigned or appended to string-like arrays.
     * For more info, please read the documentation for the class uavcan::Array<>.
     */
    //keyValue_msg.key = keyID[0];   // "a"
    //keyValue_msg.key += keyID[1];  // "ab"
    //keyValue_msg.key += keyID[2];  // "abc"

    /*
     * Publishing the message.
     */
    uavcan::Publisher<uavcan::protocol::debug::KeyValue> kv_pub(*node);

    int pub_res = kv_pub.broadcast(keyValue_msg);
    if (pub_res < 0)
    {
        std::cerr << "KV publication failure: " << pub_res << std::endl;
    }

}

/********************************************************************************************/
/*
 *                 END OF UAVCAN NODE FUNCTIONS DECLARATION
 */
/********************************************************************************************/

/********************************************************************************************/
/*
 *                 ATDPOC COMMUNICATION FUNCTIONS
 */
/********************************************************************************************/
// CAN Timeout Time Variables
struct timeval tvCANATDPOC;	//timer used for timeout of CAN message reception

void send_ATDPOC_canmsg(int can_atd_poc, struct can_frame frame)    //Sends a CAN frame on ATDPOC format
{
    int nbytes;

    nbytes = write(can_atd_poc, &frame, sizeof(struct can_frame));

    //printf("Wrote %d bytes\n", nbytes);
}


/********************************************************************************************/
/*
 *                   END OF ATDPOC COMMUNICATION FUNCTIONS
 */
/********************************************************************************************/

/********************************************************************************************/
/*
 *                                 THREADS FUNCTIONS
 */
/********************************************************************************************/

//pthread_t thread_ATDPOC_CANmsg_rcv;          //thread declaration
pthread_t thread_ATDPOC_CANmsg_send_rcv;          //thread declaration
pthread_t thread_telemetry_updateFile;          //thread declaration
pthread_t thread_telemetry_syncFile;          //thread declaration

void *thread_ATDPOC_CANmsg_send_rcv_fcn(void *ptr);
void *thread_telemetry_updateFile_fcn(void *ptr);
void *thread_telemetry_syncFile_fcn(void *ptr);
//void *thread_EngineModelUpdate_fcn(void *ptr);

void *thread_ATDPOC_CANmsg_send_rcv_fcn(void *ptr)
{
    int cansock = (long) ptr;   //can socket channel being used inside this function (CAN1).

    struct can_frame frame_read;
    struct can_frame frame_send;

    clock_gettime(CLOCK_MONOTONIC, &initialTime);

    while(1)    //never exits this thread
    {
        clock_gettime(CLOCK_MONOTONIC, &actualTime);

        upTime_sendATDPOCmsg_ms = ( (actualTime.tv_sec*1000) + (actualTime.tv_nsec/1000000) ) - ( (initialTime.tv_sec*1000) + (initialTime.tv_nsec/1000000) );  //converts seconds and nanoseconds to milliseconds,
                                                                                                                                                                //then calculates the difference of actual and initial time.

        if(last_sendATDPOCmsg_ms > upTime_sendATDPOCmsg_ms)     //if the last time the message has been sent is bigger than the actual time, it means that the node was resetted.
            last_sendATDPOCmsg_ms = 0;      //then sets the last time to zero.

//std::cout << "upTime:" << upTime_sendATDPOCmsg_ms << std::endl << std::endl;

        /**************************** CAN1 MESSAGE RECEPTION **********************************************/
        if ( upTime_sendATDPOCmsg_ms >= (last_sendATDPOCmsg_ms + FADEC_OBC_TIMERATE_MS - 20) )  //the reception of CAN messages works until 20ms before the send message sequence,
                                                                                                //in order to finish any task during this interval of 20ms.
        {
            tempo7 = upTime_sendATDPOCmsg_ms;
            //std::chrono::steady_clock::time_point begin_tempo5 = std::chrono::steady_clock::now();

            if(recv(cansock, &frame_read, sizeof(struct can_frame), MSG_DONTWAIT) > 0)  //using recv() instead of read(), because recv() has MSG_DONTWAIT flag, so the function does not block
            {

                switch (frame_read.can_id & CAN_29BIT_ID_MASK)
                {
                    case FADEC_STATUS_CANID:
                        flagSync = 1;
                    break;

                    case OBC_FADEC_THRUST_MACH_ALT_CANID:
                        net_thrust_cmd.value_in_bytes[0] = frame_read.data[0];
                        net_thrust_cmd.value_in_bytes[1] = frame_read.data[1];
                        machNumber_uint8 = frame_read.data[2];
                        estimatedAlt.value_in_bytes[0] = frame_read.data[3];
                        estimatedAlt.value_in_bytes[1] = frame_read.data[4];
                        estimatedAlt.value_in_bytes[2] = frame_read.data[5];
                        estimatedAlt.value_in_bytes[3] = frame_read.data[6];

                        reference = net_thrust_cmd.value_in_uint16;
                        MN = (float) machNumber_uint8 / 100;
                        Altitude = estimatedAlt.value_in_float;

                        if(EngStatus.EngStatusBist.Starting | EngStatus.EngStatusBist.Idle | EngStatus.EngStatusBist.Regime | EngStatus.EngStatusBist.Degraded)  //if FADEC is in one of these status, execute the communication monitoring
                        {
                            lastTime_rcvOBCmsg_ms = upTime_sendATDPOCmsg_ms;  //holds the last time the OBC_FADEC_THRUST_MACH_ALT_CANID message has been received, used as the HeartBeat from OBC to FADEC communication.
                        }
                    break;

                    case OBC_FADEC_ENGINE_CMD_CANID:
                        engineCommandFromATDPOC = frame_read.data[0];
                        printf("EngComm=%x\n",engineCommandFromATDPOC);
                        OnOffCom = engineCommandFromATDPOC;
                    break;

                    //case FADEC_TLM_FAILURE_CODES_CANID;
                    case FADEC_SIM_FAILURE_CODES_CANID:
                        for(i=0; i < frame_read.can_dlc; i++)
                        {
                            faultsCANmsg.valueInBytes[i] = frame_read.data[i];
         //printf("%x ",faultsCANmsg.valueInBytes[i]);

         //Faults.FaultBits = Faults.FaultBits | (faultsCANmsg.valueInBytes[7-i] << (8*i));
                        }

                        Faults.FaultBits = faultsCANmsg.valueUint64;

                        SensFaults.FaultBits = Faults.FaultBits;
                        //SysFaults.FaultBits = Faults.FaultBits >> 31;
                        SysFaults.DetFaults.POil_High = Faults.Faults.POil_High;
                        SysFaults.DetFaults.POil_Low = Faults.Faults.POil_Low;
                        SysFaults.DetFaults.PFuel_High = Faults.Faults.PFuel_High;
                        SysFaults.DetFaults.PFuel_Low = Faults.Faults.PFuel_Low;
                        SysFaults.DetFaults.BlowOut = Faults.Faults.BlowOut;
                        SysFaults.DetFaults.VibrationHigh = Faults.Faults.VibrationHigh;
                        SysFaults.DetFaults.Mec_Lock = Faults.Faults.Mec_Lock;
                        SysFaults.DetFaults.OverTemp = Faults.Faults.OverTemp;
                        SysFaults.DetFaults.OverSpeed = Faults.Faults.OverSpeed;
                        SysFaults.DetFaults.Ignition = Faults.Faults.Ignition;
                        SysFaults.DetFaults.TB_0_High = Faults.Faults.TBear_0_High;
                        SysFaults.DetFaults.TB_1_High = Faults.Faults.TBear_1_High;
                        SysFaults.DetFaults.TB_2_High = Faults.Faults.TBear_2_High;
                        //SysFaults.DetFaults.CAN_0_Fault = Faults.Faults.CAN_0_Fault;
                        //SysFaults.DetFaults.CAN_1_Fault = Faults.Faults.CAN_1_Fault;
                        CANFault.DetFaults.CAN_0_Fault = Faults.Faults.CAN_0_Fault;
                        CANFault.DetFaults.CAN_1_Fault = Faults.Faults.CAN_1_Fault;

         printf("\nFaultsUin64=%llu\n",faultsCANmsg.valueUint64);
         printf("Faults=%llu\n",Faults.FaultBits);
         printf("SensFaults=%llu\n",SensFaults.FaultBits);
         printf("SysFaults=%llu\n",SysFaults.FaultBits);
                    break;

                    case HILS_FADEC_RESET_CANID:
                        init_net_thrust_cmd.value_in_bytes[0] = frame_read.data[0];
                        init_net_thrust_cmd.value_in_bytes[1] = frame_read.data[1];
                        init_machNumber_uint8 = frame_read.data[2];
                        init_estimatedAlt.value_in_bytes[0] = frame_read.data[3];
                        init_estimatedAlt.value_in_bytes[1] = frame_read.data[4];
                        init_dT = frame_read.data[5];
                        resetMode.valueInByte = frame_read.data[6];

                        Mode = resetMode.value.starting_mode;
                        LeverMode = resetMode.value.lever_mode;
                        WhichEngine = resetMode.value.engine;
                        simMod = resetMode.value.simulation_mode;   //0 = SIL, 1 = HIL Async, 2 = HIL Sync, 3 = Test Bench

                        Altitude0 = (float) init_estimatedAlt.value_in_uint16;      //Initial Altitude

                        dT0 = (float) init_dT - 100;				//Initial Ambient Temperature. IMPORTANT! The value is shifted by 100K, so the temperature range is from -100K to +155K

                        MN0 = (float) init_machNumber_uint8 / 100;        //Initial Mach Number in percent (%), but MN0 is 0 to 1, so divide by 100

                        reference0 = (float) init_net_thrust_cmd.value_in_uint16;
            printf("RESET! Mode=%f, Eng=%f, Lever=%f, simMod=%f\n", Mode, engine_float, LeverMode, simMod);
            printf("resetMode: Mode=%x, Eng=%x, Lever=%x, simMod=%x\n", resetMode.value.starting_mode, resetMode.value.engine, resetMode.value.lever_mode, resetMode.value.simulation_mode);
            printf("InitRef=%f, InitAlt=%f, InitMN=%f, InitdT=%f\n", reference0, Altitude0, MN0, dT0);
                        ResetButton[0] = 1;
                        upTime_ms = 0;
                        lastTime_rcvOBCmsg_ms = 0;
                        Reset = Edge(ResetButton);
                    break;

                    case TLM_OBC_BOOSTER_SEP:
                        booster_separation.value.leftBoosterSwitch = frame_read.data[0];
                        booster_separation.value.rightBoosterSwitch = frame_read.data[1];

                        BoosterLStatus = booster_separation.value.leftBoosterSwitch;
                        BoosterRStatus = booster_separation.value.rightBoosterSwitch;
            //printf("BoosterStatus: L=0x%x R=0x%x\n", BoosterLStatus, BoosterRStatus);
                    break;




                }   // END OF switch (frame_read.can_id & CAN_29BIT_ID_MASK)


            } // END OF if(read(cansock, &frame_read, sizeof(struct can_frame)) > 0)


            /************ CHECKING OBC TO FADEC COMMUNICATION HEARTBEAT ****************************/
            //if(EngStatus.EngStatusBist.Starting | EngStatus.EngStatusBist.Idle | EngStatus.EngStatusBist.Regime | EngStatus.EngStatusBist.ShutOff)  //if FADEC is in one of these status, check the communication
            if(EngStatus.EngStatusBist.Starting | EngStatus.EngStatusBist.Idle | EngStatus.EngStatusBist.Regime | EngStatus.EngStatusBist.Degraded)  //if FADEC is in one of these status, check the communication
            {
//std::cout << "up=" << upTime_sendATDPOCmsg_ms << "   last=" << lastTime_rcvOBCmsg_ms << std::endl;
                if(lastTime_rcvOBCmsg_ms == 0)  //if it is the first time that the monitoring is being executed
                {
                    lastTime_rcvOBCmsg_ms = upTime_sendATDPOCmsg_ms;
                }

                else        //if the first message was received or the TJ_STARTING state has been reached
                {
                    if(upTime_sendATDPOCmsg_ms > (lastTime_rcvOBCmsg_ms + OBC_FADEC_HEARTBEAT_TIMEOUT))   //if 1000ms has passed since last received message from OBC
                    {
        //                if(EngStatus.EngStatusBist.Starting)
        //                {
        //                    OnOffCom = 0xCC;    //forces the Emergency command to FADEC
        //                }

        //                else
        //                {
        //                    OnOffCom = 0x00;    //forces the ShutOff command to FADEC
        //                }

                        CANFault.DetFaults.CAN_1_Fault = 1;

                        //fadecSensorsDataFile << "LOST OBC COMMUNICATION!" << std::endl;

                        printf("\nLOST OBC COMMUNICATION!\n");

                    }
                }

            }   //END OF if(EngStatus.EngStatusBist.Starting | EngStatus.EngStatusBist.Idle | EngStatus.EngStatusBist.Regime)


            //std::chrono::steady_clock::time_point end_tempo5 = std::chrono::steady_clock::now();
            //tempo5 = std::chrono::duration_cast<std::chrono::microseconds>(end_tempo5 - begin_tempo5).count();
        }   //END OF if ( upTime_sendATDPOCmsg_ms >= (last_sendATDPOCmsg_ms + FADEC_OBC_TIMERATE_MS - 20) )
        /**************************** END OF CAN1 MESSAGE RECEPTION **********************************************/





        /**************************** CAN1 MESSAGE TRANSMISSION **********************************************/
        if ( upTime_sendATDPOCmsg_ms >= (last_sendATDPOCmsg_ms + FADEC_OBC_TIMERATE_MS) )   //after the interval defined by FADEC_OBC_TIMERATE_MS, the messages are sent to ATDPOC bus.
        {
//tempo1++;   //teste gravação ofstream
            last_sendATDPOCmsg_ms = upTime_sendATDPOCmsg_ms;
//std::cout << "ATDPOC:" << upTime_sendATDPOCmsg_ms << std::endl;

            /********************************************************************************************/
            /*
             *                                 OBC MESSAGES TRANSMISSION
             */
            /********************************************************************************************/
            //std::chrono::steady_clock::time_point begin_tempo1 = std::chrono::steady_clock::now();

//                if (last_ATDPOC_upd_ms > upTime_ms)
//                    last_ATDPOC_upd_ms = 0;

            if(HILMode == 0)    //0 = SIL, 1 = HIL Async, 2 = HIL Sync. So, if it is SIL Mode (no FADEC), the messages from FADEC will be sent by this board
            {
                //if ( upTime_ms >= (last_ATDPOC_upd_ms+FADEC_OBC_TIMERATE_MS) )
                //{
                    //last_ATDPOC_upd_ms = upTime_ms;
            //printf("ATDPOC_upd\n");
            // FADEC Status


                fadec_status fadecStatus;
                fadecStatus.value.fuelFlow = Wf*100000;                 //converts fValue range (0 to 0.2 kg/s) to be transmitted on uint format (0 to 20000). Must be divided by 100000 on destination!
                fadecStatus.value.TurbineChamberTemperature = Tt4;      //Kelvin (0 to 2000K)
                fadecStatus.value.oilPressure = Sensors.POil[0] / 100;  //converting from PA to mbar: 1PA = 0.01mbar || 100PA = 1mbar, so divide the PA value by 100. The range is: 0 to 10000mbar (0 to 10bar)
                fadecStatus.value.pFuel = Sensors.PFuel[0] / 100000;      //converting from PA to bar: 100000PA = 1bar, so divide the PA value by 100000. The range is: 0 to 160bar

            /* TS2 0 Faults */
                if (EngStatus.EngStatusBist.Degraded)
                {
                    fadecStatus.value.fadecState = 10;
                }
                else if (EngStatus.EngStatusBist.Emergency)
                {
                    fadecStatus.value.fadecState = 8;
                }
                else if (EngStatus.EngStatusBist.Fail)
                {
                    fadecStatus.value.fadecState = 9;
                }
                else if (EngStatus.EngStatusBist.Idle)
                {
                    fadecStatus.value.fadecState = 5;
                }
                else if (EngStatus.EngStatusBist.Initialize)
                {
                    fadecStatus.value.fadecState = 1;
                }
                else if (EngStatus.EngStatusBist.ReadyToStart)
                {
                    fadecStatus.value.fadecState = 3;
                }
                else if (EngStatus.EngStatusBist.Regime)
                {
                    fadecStatus.value.fadecState = 6;
                }
                /*else if (EngStatus.EngStatusBist.Reserved)
                {
                    //fadecStatus.value.fadecState = 10;
                }*/
                else if (EngStatus.EngStatusBist.ShutOff)
                {
                    fadecStatus.value.fadecState = 7;
                }
                else if (EngStatus.EngStatusBist.Starting)
                {
                    fadecStatus.value.fadecState = 4;
                }
                else if (EngStatus.EngStatusBist.Windmilling)
                {
                    fadecStatus.value.fadecState = 2;
                }

                else
                {
//                            printf("Status Error!\n");
                }

            //printf("FadecStatus=%d\n", fadecStatus.value.fadecState);

                frame_send.can_id = FADEC_STATUS_CANID | 1 << 31;	//1<<31 sets the Extended Flag ID bit

                frame_send.can_dlc = 8;
                frame_send.data[0] = fadecStatus.valueInBytes[0];
                frame_send.data[1] = fadecStatus.valueInBytes[1];
                frame_send.data[2] = fadecStatus.valueInBytes[2];
                frame_send.data[3] = fadecStatus.valueInBytes[3];
                frame_send.data[4] = fadecStatus.valueInBytes[4];
                frame_send.data[5] = fadecStatus.valueInBytes[5];
                frame_send.data[6] = fadecStatus.valueInBytes[6];
                frame_send.data[7] = fadecStatus.valueInBytes[7];

                send_ATDPOC_canmsg(cansock, frame_send);

                // FADEC variables to Telemetry 1
                fadec_tlm_1 telemetry1;
                telemetry1.value.rotationSpeed = RPM;                                       //0 to 30000RPM
                telemetry1.value.compressorInletTotalTemperature = Tt2;                     //Kelvin (0 to 2000K)
//telemetry1.value.compressorInletTotalTemperature = tempo1;      //teste gravação ofstream
                telemetry1.value.vibration = Sensors.Vibration[0] * 1000;                   //converting from mm/s to um/s (micrometers per second). 1mm/s = 1000 um/s, so multiply the value by 1000. The range is: 0 to 50000um/s (0 to 50mm/s)
                telemetry1.value.combustionChamberStaticPressure = Sensors.Pt3[0] / 100;	//converting from PA to mbar: 1PA = 0.01mbar || 100PA = 1mbar, so divide the PA value by 100. The range is: 0 to 10000mbar (0 to 10bar)

                frame_send.can_id = FADEC_TLM_1_CANID | 1 << 31;	//1<<31 sets the Extended Flag ID bit

                frame_send.can_dlc = 8;
                frame_send.data[0] = telemetry1.valueInBytes[0];
                frame_send.data[1] = telemetry1.valueInBytes[1];
                frame_send.data[2] = telemetry1.valueInBytes[2];
                frame_send.data[3] = telemetry1.valueInBytes[3];
                frame_send.data[4] = telemetry1.valueInBytes[4];
                frame_send.data[5] = telemetry1.valueInBytes[5];
                frame_send.data[6] = telemetry1.valueInBytes[6];
                frame_send.data[7] = telemetry1.valueInBytes[7];

                send_ATDPOC_canmsg(cansock, frame_send);

            // FADEC variables to Telemetry 2
                static uint32_t last_fadecTLM2_msg_ms = 0;
                if (last_fadecTLM2_msg_ms > upTime_sendATDPOCmsg_ms)      //if a reset was performed, make last_fadecTLM2_msg_ms=0.
                    last_fadecTLM2_msg_ms = 0;

                if ( upTime_sendATDPOCmsg_ms >= (last_fadecTLM2_msg_ms + FADEC_TLM_2_CANMSG_PERIOD_MS) )    //rate limit of FADEC_TLM_2 msg: 1000ms
                {
                    last_fadecTLM2_msg_ms = upTime_sendATDPOCmsg_ms;


                    fadec_tlm_2 telemetry2;
                    telemetry2.value.bearing_0_temperature = Sensors.TBear[0];      //Kelvin (0 to 2000K)
                    telemetry2.value.bearing_1_temperature = Sensors.TBear[1];      //Kelvin (0 to 2000K)
                    telemetry2.value.bearing_2_temperature = Sensors.TBear[2];      //Kelvin (0 to 2000K)

                    frame_send.can_id = FADEC_TLM_2_CANID | 1 << 31;	//1<<31 sets the Extended Flag ID bit

                    frame_send.can_dlc = 6;
                    frame_send.data[0] = telemetry2.valueInBytes[0];
                    frame_send.data[1] = telemetry2.valueInBytes[1];
                    frame_send.data[2] = telemetry2.valueInBytes[2];
                    frame_send.data[3] = telemetry2.valueInBytes[3];
                    frame_send.data[4] = telemetry2.valueInBytes[4];
                    frame_send.data[5] = telemetry2.valueInBytes[5];

                    send_ATDPOC_canmsg(cansock, frame_send);
                }


                fadec_obc_estimated_thrust thrust;
                thrust.value.estimated_thrust = ModelPars.Fn;

                frame_send.can_id = FADEC_OBC_ESTIMATED_THRUST_CANID | 1 << 31;	//1<<31 sets the Extended Flag ID bit

                frame_send.can_dlc = 2;
                frame_send.data[0] = thrust.valueInBytes[0];
                frame_send.data[1] = thrust.valueInBytes[1];

                send_ATDPOC_canmsg(cansock, frame_send);

            //FADEC Failure Codes
                fadec_tlm_failure_codes faultsCANmsg;
                faultsCANmsg.valueUint64 = FaultStatus.FaultBits;

                frame_send.can_id = FADEC_TLM_FAILURE_CODES_CANID | 1 << 31;	//1<<31 sets the Extended ID Flag bit

                frame_send.can_dlc = 8;
                frame_send.data[0] = faultsCANmsg.valueInBytes[0];
                frame_send.data[1] = faultsCANmsg.valueInBytes[1];
                frame_send.data[2] = faultsCANmsg.valueInBytes[2];
                frame_send.data[3] = faultsCANmsg.valueInBytes[3];
                frame_send.data[4] = faultsCANmsg.valueInBytes[4];
                frame_send.data[5] = faultsCANmsg.valueInBytes[5];
                frame_send.data[6] = faultsCANmsg.valueInBytes[6];
                frame_send.data[7] = faultsCANmsg.valueInBytes[7];

                send_ATDPOC_canmsg(cansock, frame_send);

//            //FADEC Warning Codes
//                fadec_tlm_warning_codes warningsCANmsg;

//                warningsCANmsg.valueUint64 = FaultWarning.FaultBits;

//                frame_send.can_id = FADEC_TLM_WARNING_CODES_CANID | 1 << 31;	//1<<31 sets the Extended Flag ID bit


//                frame_send.can_dlc = 8;
//                frame_send.data[0] = warningsCANmsg.valueInBytes[0];
//                frame_send.data[1] = warningsCANmsg.valueInBytes[1];
//                frame_send.data[2] = warningsCANmsg.valueInBytes[2];
//                frame_send.data[3] = warningsCANmsg.valueInBytes[3];
//                frame_send.data[4] = warningsCANmsg.valueInBytes[4];
//                frame_send.data[5] = warningsCANmsg.valueInBytes[5];
//                frame_send.data[6] = warningsCANmsg.valueInBytes[6];
//                frame_send.data[7] = warningsCANmsg.valueInBytes[7];

//                send_ATDPOC_canmsg(cansock, frame_send);

            }   // END OF if(HILMode == 0)    //if it is SIL Mode (no FADEC), the messages from FADEC will be sent by this board

        /********************************************************************************************/
        /*
         *                                 END OF OBC MESSAGES TRANSMISSION
         */
        /********************************************************************************************/

            else if(HILMode != 3)   //0 = SIL, 1 = HIL Async, 2 = HIL Sync, 3 = Test Bench. So, if it is not on Test Bench mode, i.e., HIL Mode Sync or Async, sends Ts2 from model.
            {

                if ( upTime_sendATDPOCmsg_ms >= (last_sendATDPOCmsg_ms+FADEC_OBC_TIMERATE_MS) )
                {
                    last_sendATDPOCmsg_ms = upTime_sendATDPOCmsg_ms;
                    //struct can_frame frame_send_Ts2;    //model will sent on every cycle the Ts2 value to FADEC via CAN

                    union model_ts2
                    {
                        struct
                        {
                            uint16_t Ts2;
                        } value;

                        uint8_t valueInBytes[2];
                    }modelTs2;

                    modelTs2.value.Ts2 = EngOutput.Ts2;

                    frame_send.can_id = MODEL_TS2_SENSOR | 1 << 31;	//1<<31 sets the Extended Flag ID bit
                    frame_send.can_dlc = 2;
                    frame_send.data[0] = modelTs2.valueInBytes[0];
                    frame_send.data[1] = modelTs2.valueInBytes[1];

                    send_ATDPOC_canmsg(cansock, frame_send);
                }
            }//END OF else    //if this board will work as HIL, send the Ts2 value to FADEC

            //std::chrono::steady_clock::time_point end_tempo1 = std::chrono::steady_clock::now();
            //tempo1 = std::chrono::duration_cast<std::chrono::microseconds>(end_tempo1 - begin_tempo1).count();
            //std::cout << "t4:" << tempo4 << std::endl;

            //std::cout << "MsgsSent" << std::endl;
        }
    }
    /**************************** END OF CAN1 MESSAGE TRANSMISSION **********************************************/

//std::cout << "thread_ATDPOC_CANmsg_send_fcn OUT" << std::endl;
}

void *thread_telemetry_updateFile_fcn(void *ptr)
{
    //int fileToSync = open(filename.c_str(), O_RDONLY);  //opens the file just one time.
    while(1)
    {
        if (flag_updFile == 1)
        {

    //std::chrono::steady_clock::time_point begin_tempo2 = std::chrono::steady_clock::now();
            tempos << tempo1 << ";" << tempo2 << ";" << tempo3 << ";" << tempo4 << ";" << tempo5 << ";" << tempo6 << ";" << tempo7 << ";" << tempo8 << ";" << tempo9 << ";" << std::endl;

            //TESTE PARA MEDIR OS TEMPOS DE FLUSH() E SYNC(). Os valores gravados na telemetria correspondem ao tempo da amostra anterior.
std::chrono::steady_clock::time_point begin_tempo2 = std::chrono::steady_clock::now();
            tempos.flush();     //saves the ofstream buffer immediately to file.
std::chrono::steady_clock::time_point end_tempo2 = std::chrono::steady_clock::now();
tempo2 = std::chrono::duration_cast<std::chrono::microseconds>(end_tempo2 - begin_tempo2).count();



            flag_updFile = 0;
    //std::chrono::steady_clock::time_point end_tempo2 = std::chrono::steady_clock::now();
    //tempo2 = std::chrono::duration_cast<std::chrono::microseconds>(end_tempo2 - begin_tempo2).count();
    //std::cout << "t6:" << tempo6 << std::endl;

        }
    }

}

void *thread_telemetry_syncFile_fcn(void *ptr)
{
    int fileToSync = open(filename.c_str(), O_RDONLY);  //opens the file just one time.
    while(1)
    {
        if ( upTime_ms >= (last_saveTelemetryFile_ms + FADEC_SAVE_TELEMETRY_FILE_PERIOD_MS) )
        {

            last_saveTelemetryFile_ms = upTime_ms;
    //std::chrono::steady_clock::time_point begin_tempo2 = std::chrono::steady_clock::now();
            tempos << tempo1 << ";" << tempo2 << ";" << tempo3 << ";" << tempo4 << ";" << tempo5 << ";" << tempo6 << ";" << tempo7 << ";" << tempo8 << ";" << tempo9 << ";" << std::endl;

std::chrono::steady_clock::time_point begin_tempo3 = std::chrono::steady_clock::now();
            //sync();             //The sync command writes all unwritten system buffers to disk - https://www.ibm.com/docs/en/aix/7.2?topic=s-sync-command
            fsync(fileToSync);      //The fsync() function forces all currently queued I/O operations associated with the file indicated by file descriptor to the synchronised I/O completion state.
            //fdatasync(fileToSync);     //fdatasync() is similar to fsync(), but does not flush modified metadata unless that metadata is needed in order to allow a subsequent data retrieval to be correctly handled.
std::chrono::steady_clock::time_point end_tempo3 = std::chrono::steady_clock::now();
tempo3 = std::chrono::duration_cast<std::chrono::microseconds>(end_tempo3 - begin_tempo3).count();


    //std::chrono::steady_clock::time_point end_tempo2 = std::chrono::steady_clock::now();
    //tempo2 = std::chrono::duration_cast<std::chrono::microseconds>(end_tempo2 - begin_tempo2).count();
    //std::cout << "t6:" << tempo6 << std::endl;

        }
    }

}


/********************************************************************************************/
/*
 *                                 END OF THREADS FUNCTIONS
 */
/********************************************************************************************/

/********************************************************************************************/
/*
 *                                 UAVCAN NODE POINTER CREATION
 */
/********************************************************************************************/
static uavcan_linux::NodePtr initNodePtr(const std::vector<std::string>& ifaces, uavcan::NodeID nid,
                                      const std::string& name)
{
    auto node = uavcan_linux::makeNode(ifaces);

    /*
     * Configuring the node.
     */
    node->setNodeID(nid);
    node->setName(name.c_str());

    /*
     * Starting the node.
     */
    //std::cout << "Starting the node..." << std::endl;
    const int start_res = node->start();
    std::cout << "Start returned: " << start_res << std::endl;

    /*
     * Say Hi to the world.
     */
    node->logInfo("init", "Hello world! I'm [%*], NID %*",
                  node->getNodeStatusProvider().getName().c_str(), int(node->getNodeID().get()));

    return node;
}


int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <node-id>" << std::endl;
        return 1;
    }
tempo1 = 0;     //teste gravação ofstream
    nice(-4);       //priority of the process. The lower the number, higher the priority. Standard value: 0. Max priority: -20. Min Priority: +20.

    const int self_node_id = std::stoi(argv[1]);
    std::cout << VERSAO_DO_DIA << std::endl;


    /******************************************** CREATING DATA REGISTER FILE ******************************************************/
    int fileSuffixNumber = 0;   //suffix number for file name
    //std::string filename = "/home/root/Desktop/ModelTelemetry/tempos.csv";     //initial file name    //now this variable is global, to use with fsync()

    do
    {
       testFileExistence.open(filename);    //tries to open file

       if(testFileExistence.good()) //if file already exists
       {
           testFileExistence.close();   //closes the file

           fileSuffixNumber++;                                      //increases the file number suffix
           filename = "/home/root/Desktop/ModelTelemetry/tempos";                              //creates the base file name
           filename.append(std::to_string(fileSuffixNumber));       //appends the suffix on the end of file name
           filename.append(".csv");                                 //and the extension
       }
    }
    while(testFileExistence.good());    //while the file exists, keep increasing the suffix.

    tempos.open(filename);    //creates the file with correct number suffix

    //fadecSensorsDataFile << "t11, t12, t13, t14, t15, t16, t17, t18, i10, i11, i12, i13, r11, r12, d11, d12, d13, o10, o11, o12, o13" << std::endl; //the first line is the column title
    tempos << "OBCmsgTx; FileSave; EngModelUpd; UAVCANTx; OBCmsgRx; upTime; upTime_ATDPOC; tempo8; tempo9;" << std::endl; //the first line is the column title
    /******************************************** END OF CREATING DATA REGISTER FILE *************************************************/

/********************************************************************************************/
/*
 *                 STARTING OBC CAN INTERFACE
 */
/********************************************************************************************/
    int can_atd_poc;
    struct sockaddr_can addr;
    struct ifreq ifr;

    const char *ifname = "can1";

    if ((can_atd_poc = socket(PF_CAN, SOCK_RAW, CAN_RAW)) == -1) {
        perror("Error while opening socket");
    }

    strcpy(ifr.ifr_name, ifname);
    ioctl(can_atd_poc, SIOCGIFINDEX, &ifr);

    addr.can_family  = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(can_atd_poc, (struct sockaddr *)&addr, sizeof(addr)) == -1) {
        perror("Error in socket bind");
    }

    /***************** INITIALIZING THE TIMEOUT TIMER OF CAN1 ******************/
     tvCANATDPOC.tv_sec = 0;
     tvCANATDPOC.tv_usec = 20000;	//IMPORTANTE!!! Fazendo testes, descobri que o mínimo valor de timeout é 10ms (10000 us)!
     //setsockopt(can_atd_poc, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tvCANATDPOC, sizeof tvCANATDPOC);
     setsockopt(can_atd_poc, SOL_SOCKET, SO_RCVTIMEO, &tvCANATDPOC, sizeof tvCANATDPOC);
     setsockopt(can_atd_poc, SOL_SOCKET, SO_SNDTIMEO, &tvCANATDPOC, sizeof tvCANATDPOC);
    /**********************************************************/


     /************ CONFIGURATION OF MESSAGE FILTERS ************************/
     //Only the following messages will be received:
//          - OBC to FADEC messages
//                - Name: OBC_FADEC_ENGINE_COMMAND; ID: 0x8B08008
//                - Name: OBC_FADEC_THRUST_MACH_ALT ID: 0x8908008
//            - Supervisorio/Model to FADEC messages:
//                 - FADEC_SKIPSTART_AUTHORIZE_COMMAND   0xF321100
//                 - MODEL_TS2_SENSOR                    0xF321101
//                 - FADEC_SIM_FAILURE_CODES_CANID       0xF321008
//                 - FADEC_DIG_OUTPUTS_SUPERVISORIO      0xF321009
//                 - FADEC_RESET_COMMAND                 0xF321010

     struct can_filter rfilter[8];

     //OBC to FADEC Message Filters
     rfilter[0].can_id   = OBC_FADEC_ENGINE_CMD_CANID | CAN_EFF_FLAG;
     rfilter[0].can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);

     rfilter[1].can_id   = OBC_FADEC_THRUST_MACH_ALT_CANID | CAN_EFF_FLAG;
     rfilter[1].can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);

     rfilter[2].can_id   = HILS_FADEC_RESET_CANID | CAN_EFF_FLAG;
     rfilter[2].can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);

     rfilter[3].can_id   = TLM_OBC_BOOSTER_SEP | CAN_EFF_FLAG;
     rfilter[3].can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);

     //Supervisorio/Model to FADEC Message Filters:
     rfilter[4].can_id   = FADEC_SKIPSTART_AUTHORIZE_COMMAND | CAN_EFF_FLAG;
     rfilter[4].can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);

     rfilter[5].can_id   = MODEL_TS2_SENSOR | CAN_EFF_FLAG;
     rfilter[5].can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);

     rfilter[6].can_id   = FADEC_SIM_FAILURE_CODES_CANID | CAN_EFF_FLAG;
     rfilter[6].can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);

     //rfilter[6].can_id   = FADEC_RESET_COMMAND | CAN_EFF_FLAG;
     //rfilter[6].can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);

     //Setting the Message Filter
     setsockopt(can_atd_poc, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

     /*********** END OF CONFIGURATION OF MESSAGE FILTERS *****************/




  /********************************************************************************************/
  /*
   *                END OF STARTING OBC CAN INTERFACE
   */
  /********************************************************************************************/


 /********************************************************************************************/
 /*
  *                UAVCAN NODE CREATION AND CONFIGURATION
  */
 /********************************************************************************************/


    /*
     * Node initialization.
     * Node ID and name are required; otherwise, the node will refuse to start.
     * Version info is optional.
     */
    std::vector<std::string> iface_names;   //string of can channels to be configured as UAVCAN node.
    iface_names.emplace_back("can0");       //only CAN0 will be used as UAVCAN node.
    uavcan_linux::NodePtr nodeCAN0 = initNodePtr(iface_names, self_node_id, "EngineModel_CAN0");

    uavcan::protocol::SoftwareVersion sw_version;  // Standard type uavcan.protocol.SoftwareVersion
    sw_version.major = 1;
    nodeCAN0->setSoftwareVersion(sw_version);
    //nodeCAN1.setSoftwareVersion(sw_version);

    uavcan::protocol::HardwareVersion hw_version;  // Standard type uavcan.protocol.HardwareVersion
    hw_version.major = 1;
    nodeCAN0->setHardwareVersion(hw_version);
    //nodeCAN1.setHardwareVersion(hw_version);

    /******************** NODE STATUS MONITORING ***************************/
    /*
      * Instantiating the monitor.
      * The object is noncopyable.
      */
     NodeMonitor monitor(*nodeCAN0);

     /*
      * Starting the monitor.
      * Once started, it runs in the background and does not require any attention.
      */
     const int monitor_start_res = monitor.start();
     if (monitor_start_res < 0)
     {
         throw std::runtime_error("Failed to start the monitor; error: " + std::to_string(monitor_start_res));
     }

     /*
      * Spinning the node for 2 seconds and then printing the list of nodes in the network.
      */
     if (nodeCAN0->spin(uavcan::MonotonicDuration::fromMSec(2000)) < 0)
     {
         throw std::runtime_error("Spin failed");
     }

     std::cout << "Known nodes:" << std::endl;
     for (int i = 1; i <= uavcan::NodeID::Max; i++)
     {
         if (monitor.isNodeKnown(i))
         {
             auto status = monitor.getNodeStatus(i);
             std::cout << "Node " << i << ": "
                       << NodeMonitor::modeToString(status) << "/" << NodeMonitor::healthToString(status)
                       << std::endl;
             /*
              * It is left as an exercise for the reader to call the following services for each discovered node:
              *  - uavcan.protocol.GetNodeInfo       - full node information (name, HW/SW version)
              *  - uavcan.protocol.GetTransportStats - transport layer statistics (num transfers, errors, iface stats)
              *  - uavcan.protocol.GetDataTypeInfo   - data type check: is supported? how used? is compatible?
              */
         }
     }
    /***************** END OF NODE STATUS MONITORING ****************************************/


    /*
     * Subscribing to standard log messages of type uavcan.protocol.debug.LogMessage.
     *
     * Received messages will be passed to the application via a callback, the type of which can be set via the second
     * template argument.
     * In C++11 mode, callback type defaults to std::function<>.
     * In C++03 mode, callback type defaults to a plain function pointer; use a binder object to call member
     * functions as callbacks (refer to uavcan::MethodBinder<>).
     *
     * N.B.: Some libuavcan users report that C++ lambda functions when used with GCC may actually break the code
     *       on some embedded targets, particularly ARM Cortex M0. These reports still remain unconfirmed though;
     *       please refer to the UAVCAN mailing list to learn more.
     *
     * The type of the argument of the callback can be either of these two:
     *  - T&
     *  - uavcan::ReceivedDataStructure<T>&
     * For the first option, ReceivedDataStructure<T>& will be cast into a T& implicitly.
     *
     * The class uavcan::ReceivedDataStructure extends the received data structure with extra information obtained from
     * the transport layer, such as Source Node ID, timestamps, Transfer ID, index of the redundant interface this
     * transfer was picked up from, etc.
     */
    uavcan::Subscriber<uavcan::protocol::debug::LogMessage> log_sub(*nodeCAN0);

    const int log_sub_start_res = log_sub.start(
        [&](const uavcan::ReceivedDataStructure<uavcan::protocol::debug::LogMessage>& msg)
        {
            /*
             * The message will be streamed in YAML format.
             */
            std::cout << msg << std::endl;
            /*
             * If the standard iostreams are not available (they rarely available in embedded environments),
             * use the helper class uavcan::OStream defined in the header file <uavcan/helpers/ostream.hpp>.
             */
            // uavcan::OStream::instance() << msg << uavcan::OStream::endl;
        });
    /*
     * C++03 WARNING
     * The code above will not compile in C++03, because it uses a lambda function.
     * In order to compile the code in C++03, move the code from the lambda to a standalone static function.
     * Use uavcan::MethodBinder<> to invoke member functions.
     */

    if (log_sub_start_res < 0)
    {
        throw std::runtime_error("Failed to start the log subscriber; error: " + std::to_string(log_sub_start_res));
    }

    /******************************************* TIMER CREATION *****************************************************/

    /*
     * Creating timers.
     * Timers are objects that instruct the libuavcan core to pass control to their callbacks either periodically
     * at specified interval, or once at some specific time point in the future.
     * Note that timer objects are noncopyable.
     *
     * A timer callback accepts a reference to an object of type uavcan::TimerEvent, which contains two fields:
     *  - The time when the callback was expected to be invoked.
     *  - The actual time when the callback was invoked.
     *
     * Timers do not require initialization and never fail (because of the very simple logic).
     *
     * Note that periodic timers do not accumulate phase error over time.
     */
//    uavcan::Timer periodic_timer(nodeCAN0);
//    uavcan::Timer one_shot_timer(nodeCAN0);
//    uavcan::Timer one_shot_timer_sync(nodeCAN0);

//    periodic_timer.setCallback([&](const uavcan::TimerEvent& event)
//        {
//schdTime_periodic = (long unsigned int)event.scheduled_time.toMSec();
//realTime_periodic = (long unsigned int)event.real_time.toMSec();
//            upTime_ms = upTime_ms + Tsample*1000;
//            sendUAVCANKeyValueMsg(nodeCAN0,"_up", (float) upTime_ms);
//            flag_disableReadATDPOCmsg = 1;
//            flag_sendATDPOCmsg = 1;

//        //sendUAVCANKeyValueMsg(nodeCAN1,"_up", (float) upTime_ms);     //as CAN1 is used only for ATDPOC, this message is removed
//            one_shot_timer.startOneShotWithDelay(uavcan::MonotonicDuration::fromMSec(10));
//        });

//    one_shot_timer.setCallback([&](const uavcan::TimerEvent& event)
//        {

//schdTime_oneshot = (long unsigned int)event.scheduled_time.toMSec();
//realTime_oneshot = (long unsigned int)event.real_time.toMSec();
//            //EngineModelUpdate(nodeCAN0, nodeCAN1, can_atd_poc);
//            EngineModelUpdate(nodeCAN0, can_atd_poc);
//            flag_disableReadATDPOCmsg = 0;  //after sending the messages over CAN1, enables the reading of messages from ATDPOC.

//            flag_updFile = 1;
//        });

//    one_shot_timer_sync.setCallback([&](const uavcan::TimerEvent& event)
//        {
//            /*
//             * if(syncTime_ms != (lastSyncTime_ms + tickFromFADEC))
//             * {
//             *      //TODO error
//             * }
//             * */
//        //upTime_ms = syncTime_ms;	//stores the syncTime on upTime. upTime_ms is used in other parts of the program.
//        upTime_ms = upTime_ms + FADEC_OBC_TIMERATE_MS; //as the upTime from FADEC is not sent over SIATT CAN protocol, the upTime_ms from model is increased by the known rate of FADEC messages.

//            sendUAVCANKeyValueMsg(nodeCAN0,"_up", (float) upTime_ms);
//            flag_disableReadATDPOCmsg = 1;
//            flag_sendATDPOCmsg = 1;
//    //sendUAVCANKeyValueMsg(nodeCAN1,"_up", (float) upTime_ms);     //as CAN1 is used only for ATDPOC, this message is removed
//            one_shot_timer.startOneShotWithDelay(uavcan::MonotonicDuration::fromMSec(10));
//            //lastSyncTime_ms = syncTime_ms;

//        });


    /*
     * Starting the timer at 20 Hz.
     * Start cannot fail.
     */
    //periodic_timer.startPeriodic(uavcan::MonotonicDuration::fromMSec(20));	//PERIODO DE ATUALIZACAO DOS DADOS NO BARRAMENTO


    /******************************************* END OF TIMER CREATION *****************************************************/



    /******************************************* KEYVALUE MESSAGE RECEPTION CAN0 *****************************************************/


    /*
     * Subscribing to messages of type uavcan.protocol.debug.KeyValue.
     * This time we don't want to receive extra information about the received message, so the callback's argument type
     * would be just T& instead of uavcan::ReceivedDataStructure<T>&.
     * The callback will print the message in YAML format via std::cout (also refer to uavcan::OStream).
     */
    uavcan::Subscriber<uavcan::protocol::debug::KeyValue> kv_subCAN0(*nodeCAN0);

    const int kv_subCAN0_start_res = kv_subCAN0.start([&](const uavcan::protocol::debug::KeyValue& msg)
    {

        /*keyMessage += msg.key[0];	//os tres primeiros caracteres informam a origem do dado
        keyMessage += msg.key[1];
        keyMessage += msg.key[2];
        keyMessage += std::to_string(msg.value);	//formato o valor float para string, para enviar via serial
        keyMessage += ",";	//a virgula eh o delimitador de cada dado

        std::cout << keyMessage << "\n";

        keyMessage = "";*/

        int error = 0;
        std::string key = "";
        unsigned char const * floatToByte;// = reinterpret_cast<unsigned char const *>(&f);

        key += msg.key[0];	//os tres primeiros caracteres informam a origem do dado
        key += msg.key[1];
        key += msg.key[2];

//std::cout << msg << std::endl;

        if(key.compare("ref") == 0)
            reference = msg.value;

        else if(key.compare("alt") == 0)				//Altitude
            Altitude = (double) msg.value;

        else if(key.compare("dtk") == 0)				//dT
            dT = (double) msg.value;

        else if(key.compare("mnb") == 0)				//Initial Mach Number
            MN = (double) msg.value;

        else if(key.compare("_d1") == 0)
        {
            model_d1 = msg.value;
            model_d1_toInt = model_d1;
//printf("_d1=%x\n", model_d1_toInt);
        }

//        else if(key.compare("_mf") == 0)
//            model_mf = msg.value;
        else if(key.compare("_i0") == 0)
        {
            model_mf = msg.value;
//printf("model_mf=%f\n", model_mf);

        }
        else if(key.compare("_i1") == 0)
            model_oilFlow = msg.value;
        else if(key.compare("_i2") == 0)
            model_i2 = msg.value;
        else if(key.compare("_i3") == 0)
            model_i3 = msg.value;

        else if(key.compare("_rs") == 0)		//reset
        {
            ResetButton[0] = 1;
            upTime_ms = 0;
            Reset = Edge(ResetButton);
        }

        else if(key.compare("_mo") == 0)		//Mode: 'a' Automatic, 'm' Manual
        {
            floatToByte = reinterpret_cast<unsigned char const *>(&msg.value);
            if(floatToByte[0] == 'a')
                Mode = 0;

            else if(floatToByte[0] == 'm')
                Mode = 1;
        }

        else if(key.compare("_lm") == 0)		//Lever Mode: 'c' Control Law, 'm' Manual
        {
            floatToByte = reinterpret_cast<unsigned char const *>(&msg.value);
            if(floatToByte[0] == 'c')
                LeverMode = 1;

            else if(floatToByte[0] == 'm')
                LeverMode = 0;
        }

        else if(key.compare("_en") == 0)		//Engine
        {
            engine_float = msg.value;
            WhichEngine = engine_float;
        }

        else if(key.compare("_sm") == 0)		//Simulation Mode
        {										//0 = SIL, 1 = HIL Async, 2 = HIL Sync, 3 = Test Bench
            simMod_float = msg.value;
            simMod = simMod_float;
        }


        /*else if(key.compare("_ps") == 0)		//pause
        {
            if(keyData.valueInBytes[0] == 'p')
                PauseVariable = 1;

            else if(keyData.valueInBytes[0] == 'c')
                PauseVariable = 0;
        }*/


        else if(key.compare("_al") == 0)				//Initial Altitude
            Altitude0 = (double) msg.value;

        else if(key.compare("_dt") == 0)				//Initial Ambient Temperature
            dT0 = (double) msg.value;

        else if(key.compare("_mn") == 0)				//Initial Mach Number
            MN0 = (double) msg.value;

        else if(key.compare("_rf") == 0)				//Initial Reference
            reference0 = (double) msg.value;


        /*else if(key.compare("_tk") == 0)
        {								//TICK value received from FADEC, used on HIL Sync Mode. Informs the model the interval of the simulation in miliseconds
            tickFromFADEC = (double) msg.value;

            if(simMod == 2)
            {
                Tsample = 0.001 * tickFromFADEC;
                TsamModel = Tsample / TsampDiv;
            }

        }*/


        /*else if(key.compare("_sy") == 0)				//Sync value received from FADEC, used on HIL Sync Mode. Stores the actual instant of the simulation, in miliseconds
        {
            syncTime_ms = (double) msg.value;

            if(simMod == 2)
                one_shot_timer_sync.startOneShotWithDelay(uavcan::MonotonicDuration::fromMSec(5));

        }*/


        else
            error = 1;	//TODO error

    });

    if (kv_subCAN0_start_res < 0)
    {
        throw std::runtime_error("Failed to start the key/value subscriber; error: " + std::to_string(kv_subCAN0_start_res));
    }

    /******************************************* END OF KEYVALUE MESSAGE RECEPTION CAN0 *****************************************************/



/********************************************************************************************************************************/
/*                                                                                                                              */
/********************************************************************************************************************************/


/********************************************************************************************************************************/
/*																																*/
/*                                   INICIALIZAÇÃO DOS NÓS UAVCAN E MATRIZES FADEC                                 			 	*/
/*																																*/
/********************************************************************************************************************************/



    /*
     * Informing other nodes that we're ready to work.
     * Default mode is INITIALIZING.
     */
    nodeCAN0->setModeOperational();
    //nodeCAN1.setModeOperational();

    /*
     * Some logging.
     * Log formatting is not available in C++03 mode.
     */
    nodeCAN0->getLogger().setLevel(uavcan::protocol::debug::LogLevel::DEBUG);
    nodeCAN0->logInfo("main", "Hello world da MainBoard EngineModel CAN0! My Node ID: %*",
                 static_cast<int>(nodeCAN0->getNodeID().get()));
    //nodeCAN1.getLogger().setLevel(uavcan::protocol::debug::LogLevel::DEBUG);    //as CAN1 is used only for ATDPOC, this message is removed
    //nodeCAN1.logInfo("main", "Hello world da MainBoard EngineModel CAN1! My Node ID: %*",   //as CAN1 is used only for ATDPOC, this message is removed
             //static_cast<int>(nodeCAN1.getNodeID().get()));

    std::cout << "EngineModel Operacional!" << std::endl;	//informo que a MainBoard está rodando

    sendUAVCANKeyValueMsg(nodeCAN0, "stt", 0);	//Sends STarT message to nodes, so they change from INITIALIZATION status to OPERATIONAL
    //sendUAVCANKeyValueMsg(nodeCAN0, "d12", 0);
    //sendUAVCANKeyValueMsg(nodeCAN0, "o11", 0);

    /* Reset variable must be set to 0 in order for inner
    * loop not to reset the timer consecutively */
    Reset = 0;

/********************************************************************************************************************************/
/*                                                                                                                              */
/********************************************************************************************************************************/


    /*
     * Node loop.
     * The thread should not block outside Node::spin().
     */
    /**************************** INITIALIZING THREAD TO SEND AND RECEIVE MESSAGES ON CAN1, AND THREAD TO SAVE TELEMETRY FILE **********************************************/

    std::cout << "Create Thread:" << strerror(pthread_create(&thread_ATDPOC_CANmsg_send_rcv, NULL, thread_ATDPOC_CANmsg_send_rcv_fcn, (void*) can_atd_poc)) << std::endl;

    std::cout << "Create Thread:" << strerror(pthread_create(&thread_telemetry_updateFile, NULL, thread_telemetry_updateFile_fcn, (void*) can_atd_poc)) << std::endl;

    std::cout << "Create Thread:" << strerror(pthread_create(&thread_telemetry_syncFile, NULL, thread_telemetry_syncFile_fcn, (void*) can_atd_poc)) << std::endl;


/********************************************************************************************************************************/
/*																																*/
/*												LOOP EXTERNO                             									 	*/
/*																																*/
/********************************************************************************************************************************/

    while (true)	//outer loop
    {
        /*
         * Spinning once.
         * The method spin() may return earlier if an error occurs (e.g. driver failure).
         * All error codes are listed in the header uavcan/error.hpp.
         */

        int spinCAN0_res = nodeCAN0->spinOnce();
        if (spinCAN0_res < 0)
        {
            std::cerr << "Transient failure: " << spinCAN0_res << std::endl;
        }

//        int spinCAN1_res = nodeCAN1.spinOnce();
//        if (spinCAN1_res < 0)
//        {
//            std::cerr << "Transient failure: " << spinCAN1_res << std::endl;
//        }
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

            /* RESETS double TYPE */

            OPRPMManual = 0;

            /* RESETS static double TYPE */

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

            /* RESETS double TYPE*/

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
            reference = 0;
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

            /* RESETS static double TYPE */

            fValue = 0;

//            /* -------------------------------------------------- */
//            /* T-MATS & PWLM  RESETS                          */
//            /* (To be usedi in MATLAB and TMATS simulations only) */
//            /* -------------------------------------------------- */

//            /* int TYPE */

//            IgniterIn = 0;

//            /* double TYPE */

//            FuelIn = 0;


//            /* -------------------------------------------------- */

        }

        /*-------------------------------------------------------------------------------------------------------------*/
        /*  INPUT READING BEFORE MAIN LOOP - Make sure to use the appropriate piece of code: MATLAB or actual hardware */
        /*-------------------------------------------------------------------------------------------------------------*/

        /* HARDWARE */

//        /* -------------------------------------------------- */
//        /* IMPUT READING - PWLM                               */
//        /* (To be usedi in MATLAB (PWLM) simulations only)    */
//        /* -------------------------------------------------- */


//        /*Reads input for calculating initial conditions*/
//        Altitude = InputVars[0];							/* Reads altitude value */
//        MN = InputVars[1];									/* Reads Mach number value */
//        dT = InputVars[2];									/* Reads day temperature variation */
//        FuelIn = InputVars[3];								/* Reads fuel input */
//        IgniterIn = InputVars[4];							/* Reads igniter input */
//        reference = InputVars[5];							/* Reads reference value */
//        ResetButton[0] = InputVars[6];						/* Reads reset button input */
//        Mode = InputVars[7];								/* Reads mode key */
//        LeverMode = InputVars[8];							/* Reads lever mode */
//        HILMode = InputVars[9];								/* Reads HIL mode */
//        WhichEngine = InputVars[10];						/* Reads which engine is to be simulated */
//        EngUnits = InputVars[11];							/* Reads option for thrust command in N (SI units) */
//        Mwm = InputVars[12];								/* Reads Mach number values for windmill simulation */
//        OnOffCom = InputVars[13];							/* Reads external command treatment */
//        OPRPMIn = InputVars[14];							/* Reads oil pump rpm input */

//        /* Temperatures from external bearings models */
//        TBear[0] = InputVars[15];
//        TBear[1] = InputVars[16];
//        TBear[2] = InputVars[17];

//        /* Reads fault bits */
//        SensFaults.FaultBits = (uint64_t)InputSensFaults[0];
//        SysFaults.FaultBits = (uint64_t)InputSysFaults[0];

//        /* Reads sensor bias */
//        SensorBias.Ts2[0] = InputBias[0];
//        SensorBias.Ts2[1] = InputBias[1];
//        SensorBias.Pt3[0] = InputBias[2];
//        SensorBias.Tt4[0] = InputBias[3];
//        SensorBias.Tt4[1] = InputBias[4];
//        SensorBias.Tt4[2] = InputBias[5];
//        SensorBias.RPM[0] = InputBias[6];
//        SensorBias.RPM[1] = InputBias[7];
//        SensorBias.POil[0] = InputBias[8];
//        SensorBias.PFuel[0] = InputBias[9];
//        SensorBias.Vibration[0] = InputBias[10];
//        SensorBias.TBear[0] = InputBias[11];
//        SensorBias.TBear[1] = InputBias[12];
//        SensorBias.TBear[2] = InputBias[13];

//        /* -------------------------------------------------- */

        Altitude = Altitude0;
        MN = MN0;
        dT = dT0;
        reference = reference0;//0.35;
        //Mode = 0;
        //LeverMode = 1;
        //HILMode = 1;
        HILMode = simMod;
        //WhichEngine = 1;

        /* MATLAB */

        /*Reads input for calculating initial conditions*/
        /*
        Altitude = InputVars[0];
        MN = InputVars[1];
        dT = InputVars[2];
        reference = InputVars[5];
        */

        /* Reads mode key */
        //Mode = InputVars[7];//0;
        //LeverMode = InputVars[8];//1;
        //HILMode = InputVars[9];//1;
        //WhichEngine = InputVars[10];//1;
        //Mode = 0;
        //LeverMode = 1;
        //HILMode = 1;
        //WhichEngine = 1;

        /*!!!!!NOVAS VARIÁVEIS A SEREM LIDAS DO SUPERVISÓRIO!!!!*/
        EngUnits = 1;//InputVars[11];
        Mwm = 0.3;//InputVars[12];

        /* External command treatment */
        //OnOffCom = 50;//InputVars[13];

        /* Reads fault bits */
        SensFaults.FaultBits = 0;//(uint64_t)InputSensFaults[0];
        SysFaults.FaultBits = 0;//(uint64_t)InputSysFaults[0];

        /* Reads sensor bias */
        SensorBias.Ts2[0] = 0;//InputBias[0];
        SensorBias.Ts2[1] = 0;//InputBias[1];
        SensorBias.Pt3[0] = 0;//InputBias[2];
        SensorBias.Tt4[0] = 0;//InputBias[3];
        SensorBias.Tt4[1] = 0;//InputBias[4];
        SensorBias.Tt4[2] = 0;//InputBias[5];
        SensorBias.RPM[0] = 0;//InputBias[6];
        SensorBias.RPM[1] = 0;//InputBias[7];
        SensorBias.POil[0] = 0;//InputBias[8];
        SensorBias.PFuel[0] = 0;//InputBias[9];
        SensorBias.Vibration[0] = 0;//InputBias[10];
//        SensorBias.TBear[0] = 0;                                  //UNCOMMENT LATER!!!!!
//        SensorBias.TBear[1] = 0;                                  //UNCOMMENT LATER!!!!!
//        SensorBias.TBear[2] = 0;                                  //UNCOMMENT LATER!!!!!

//        /* -------------------------------------------------- */
//        /* RESET VERIFICATION - PWLM                          */
//        /* (To be usedi in MATLAB (PWLM) simulations only)    */
//        /* -------------------------------------------------- */

//        Reset = Edge(ResetButton);
//        ResetButton[1] = ResetButton[0];

//        /* -------------------------------------------------- */

        /*-----------------------------------------------------------*/
        /* DEFINES MATRICES AND CONSTANTS DEPENDING ON CHOSEN ENGINE */
        /*-----------------------------------------------------------*/

        /* ENGINES TO BE SIMULATED */
        /*	WhichEngine == 1 -> TJ1200
            WhichEngine == 2 -> TF1200
            WhichEngine == 10 -> GEJ85
                                        */

        /* Loads the constants of chosen engine */
        getEngConst(&Alt_Elem, &MN_Elem, &AS_Elem, &Fn_Elem, &SteadyOp_Elem, &PowerMan_Elem, &NcFANMap_Elem, &WcFANMap_Elem, &Wc_per_Nc_FAN,
                    &NcHPCMap_Elem, &WcHPCMap_Elem, &Wc_per_Nc_HPC, &NcHPTMap_Elem, &PRHPTMap_Elem, &WcHPTMap_Elem, &WfMax_Pump,
                    &EngPars, WhichEngine);

        /*Loads the controller starting parameters*/
        getStartPars(&ContStart, WhichEngine);

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
            N_KiMtx = (double *)malloc(PowerMan_Elem * sizeof(double));
            N_KpMtx = (double *)malloc(PowerMan_Elem * sizeof(double));
            NcFANContMtx = (double *)malloc(PowerMan_Elem * sizeof(double));
            FNperContMtx = (double *)malloc(PowerMan_Elem * sizeof(double));
            FNcMaxContMtx = (double *)malloc(MN_Elem * sizeof(double));

            /* Matrices used for model calculations */
            NcMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Pt21Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Pt3Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Pt5Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Pt6Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Tt21Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Tt3Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Tt4Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Tt5Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Tt6Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            WfMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            AMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            BMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Pt21DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Pt3DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Pt5DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Pt6DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Tt21DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Tt3DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Tt4DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Tt5DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
            Tt6DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));

            /* Matrices used for sub-idle calculations */
            AwmMtx = (double *)malloc(MN_Elem * sizeof(double));
            AshMtx = (double *)malloc(MN_Elem * sizeof(double));
            BwmMtx = (double *)malloc(MN_Elem * sizeof(double));
            BshMtx = (double *)malloc(MN_Elem * sizeof(double));
            RPMwmMtx = (double *)malloc(MN_Elem * sizeof(double));
            RPMshMtx = (double *)malloc(MN_Elem * sizeof(double));
            Tt4CshMtx = (double *)malloc(1 * sizeof(double));
            Tt4DshMtx = (double *)malloc(1 * sizeof(double));
            Tt4shMtx = (double *)malloc(1 * sizeof(double));
            WfshMtx = (double *)malloc(1 * sizeof(double));


            /* Low Pressure Compressor or Fan */
            NcFANMapMtx = (double *)malloc(NcFANMap_Elem * sizeof(double));
            WcFANStallMtx = (double *)malloc(NcFANMap_Elem * sizeof(double));
            PRFANStallMtx = (double *)malloc(NcFANMap_Elem * sizeof(double));
            WcFANMapMtx = (double *)malloc(WcFANMap_Elem * sizeof(double));
            PRFANMapMtx = (double *)malloc(WcFANMap_Elem * sizeof(double));
            EffFANMapMtx = (double *)malloc(WcFANMap_Elem * sizeof(double));

            /* High Pressure Compressor */
            NcHPCMapMtx = (double *)malloc(NcHPCMap_Elem * sizeof(double));
            WcHPCStallMtx = (double *)malloc(NcHPCMap_Elem * sizeof(double));
            PRHPCStallMtx = (double *)malloc(NcHPCMap_Elem * sizeof(double));
            WcHPCMapMtx = (double *)malloc(WcHPCMap_Elem * sizeof(double));
            PRHPCMapMtx = (double *)malloc(WcHPCMap_Elem * sizeof(double));
            EffHPCMapMtx = (double *)malloc(WcHPCMap_Elem * sizeof(double));

            /* Turbine */
            NcHPTMapMtx = (double *)malloc(NcHPTMap_Elem * sizeof(double));
            WcHPTMapMtx = (double *)malloc(WcHPTMap_Elem * sizeof(double));
            EffHPTMapMtx = (double *)malloc(WcHPTMap_Elem * sizeof(double));
            PRHPTMapMtx = (double *)malloc(PRHPTMap_Elem * sizeof(double));

            /* Auxiliar matrices */
            Mtx2D = (double *)malloc(MN_Elem * Fn_Elem * sizeof(double));
            Mtx2DH = (double *)malloc(MN_Elem * Fn_Elem * sizeof(double));
            Mtx1D = (double *)malloc(Fn_Elem * sizeof(double));
            Mtx1DH = (double *)malloc(Fn_Elem * sizeof(double));

            DeltaMtx2D = (double *)malloc(Alt_Elem * MN_Elem * sizeof(double));
            DeltaMtx2DH = (double *)malloc(Alt_Elem * MN_Elem * sizeof(double));
            DeltaMtx1D = (double *)malloc(MN_Elem * sizeof(double));
            DeltaMtx1DH = (double *)malloc(MN_Elem * sizeof(double));

            Ts0Mtx2D = (double *)malloc(Fn_Elem * sizeof(double));
            Ts0Mtx2DH = (double *)malloc(Fn_Elem * sizeof(double));
            Ts0Mtx1D = (double *)malloc(Alt_Elem * sizeof(double));
            Ts0Mtx1DH = (double *)malloc(Alt_Elem * sizeof(double));

            MapFAN2D = (double *)malloc(WcFANMap_Elem * sizeof(double));
            MapFAN2DH = (double *)malloc(WcFANMap_Elem * sizeof(double));
            MapFAN1D = (double *)malloc(Wc_per_Nc_FAN * sizeof(double));
            MapFAN1DH = (double *)malloc(Wc_per_Nc_FAN * sizeof(double));

            MapHPC2D = (double *)malloc(WcHPCMap_Elem * sizeof(double));
            MapHPC2DH = (double *)malloc(WcHPCMap_Elem * sizeof(double));
            MapHPC1D = (double *)malloc(Wc_per_Nc_HPC * sizeof(double));
            MapHPC1DH = (double *)malloc(Wc_per_Nc_HPC * sizeof(double));

            /* MN linerizing vector */
            MNLinVec = (double *)malloc(MN_Elem * sizeof(double));
            AltLinVec = (double *)malloc(Alt_Elem * sizeof(double));
            DeltaMtx = (double *)malloc(Alt_Elem * MN_Elem * sizeof(double));
            Ts0Mtx = (double *)malloc(Alt_Elem * MN_Elem * sizeof(double));

            /* Reference filter vectors */
            ASVec = (double *)malloc(AS_Elem * sizeof(double));
            DSVec = (double *)malloc(AS_Elem * sizeof(double));
            NcVec = (double *)malloc(AS_Elem * sizeof(double));

        }
        else
        {
            /* HARDWARE */

            /* Matrices used for reference and gain calculations */
            N_KiMtx = (double *)realloc(N_KiMtx,PowerMan_Elem * sizeof(double));
            N_KpMtx = (double *)realloc(N_KpMtx,PowerMan_Elem * sizeof(double));
            NcFANContMtx = (double *)realloc(NcFANContMtx,PowerMan_Elem * sizeof(double));
            FNperContMtx = (double *)realloc(FNperContMtx,PowerMan_Elem * sizeof(double));
            FNcMaxContMtx = (double *)realloc(FNcMaxContMtx,MN_Elem * sizeof(double));

            /* Matrices used for model calculations */
            NcMtx = (double *)realloc(NcMtx,SteadyOp_Elem * sizeof(double));
            Pt21Mtx = (double *)realloc(Pt21Mtx,SteadyOp_Elem * sizeof(double));
            Pt3Mtx = (double *)realloc(Pt3Mtx,SteadyOp_Elem * sizeof(double));
            Pt5Mtx = (double *)realloc(Pt5Mtx,SteadyOp_Elem * sizeof(double));
            Pt6Mtx = (double *)realloc(Pt6Mtx,SteadyOp_Elem * sizeof(double));
            Tt21Mtx = (double *)realloc(Tt21Mtx,SteadyOp_Elem * sizeof(double));
            Tt3Mtx = (double *)realloc(Tt3Mtx,SteadyOp_Elem * sizeof(double));
            Tt4Mtx = (double *)realloc(Tt4Mtx,SteadyOp_Elem * sizeof(double));
            Tt5Mtx = (double *)realloc(Tt5Mtx,SteadyOp_Elem * sizeof(double));
            Tt6Mtx = (double *)realloc(Tt6Mtx,SteadyOp_Elem * sizeof(double));
            WfMtx = (double *)realloc(WfMtx,SteadyOp_Elem * sizeof(double));
            AMtx = (double *)realloc(AMtx,SteadyOp_Elem * sizeof(double));
            BMtx = (double *)realloc(BMtx,SteadyOp_Elem * sizeof(double));
            Pt21DMtx = (double *)realloc(Pt21DMtx,SteadyOp_Elem * sizeof(double));
            Pt3DMtx = (double *)realloc(Pt3DMtx,SteadyOp_Elem * sizeof(double));
            Pt5DMtx = (double *)realloc(Pt5DMtx,SteadyOp_Elem * sizeof(double));
            Pt6DMtx = (double *)realloc(Pt6DMtx,SteadyOp_Elem * sizeof(double));
            Tt21DMtx = (double *)realloc(Tt21DMtx,SteadyOp_Elem * sizeof(double));
            Tt3DMtx = (double *)realloc(Tt3DMtx,SteadyOp_Elem * sizeof(double));
            Tt4DMtx = (double *)realloc(Tt4DMtx,SteadyOp_Elem * sizeof(double));
            Tt5DMtx = (double *)realloc(Tt5DMtx,SteadyOp_Elem * sizeof(double));
            Tt6DMtx = (double *)realloc(Tt6DMtx,SteadyOp_Elem * sizeof(double));

            /* Matrices used for sub-idle calculations */
            AwmMtx = (double *)realloc(AwmMtx,MN_Elem * sizeof(double));
            AshMtx = (double *)realloc(AshMtx,MN_Elem * sizeof(double));
            BwmMtx = (double *)realloc(BwmMtx,MN_Elem * sizeof(double));
            BshMtx = (double *)realloc(BshMtx,MN_Elem * sizeof(double));
            RPMwmMtx = (double *)realloc(RPMwmMtx,MN_Elem * sizeof(double));
            RPMshMtx = (double *)realloc(RPMshMtx,MN_Elem * sizeof(double));
            Tt4CshMtx = (double *)realloc(Tt4CshMtx,1 * sizeof(double));
            Tt4DshMtx = (double *)realloc(Tt4DshMtx,1 * sizeof(double));
            Tt4shMtx = (double *)realloc(Tt4shMtx,1 * sizeof(double));
            WfshMtx = (double *)malloc(1 * sizeof(double));


            /* Low Pressure Compressor or Fan */
            NcFANMapMtx = (double *)realloc(NcFANMapMtx,NcFANMap_Elem * sizeof(double));
            WcFANStallMtx = (double *)realloc(WcFANStallMtx,NcFANMap_Elem * sizeof(double));
            PRFANStallMtx = (double *)realloc(PRFANStallMtx,NcFANMap_Elem * sizeof(double));
            WcFANMapMtx = (double *)realloc(WcFANMapMtx,WcFANMap_Elem * sizeof(double));
            PRFANMapMtx = (double *)realloc(PRFANMapMtx,WcFANMap_Elem * sizeof(double));
            EffFANMapMtx = (double *)realloc(EffFANMapMtx,WcFANMap_Elem * sizeof(double));

            /* High Pressure Compressor */
            NcHPCMapMtx = (double *)realloc(NcHPCMapMtx,NcHPCMap_Elem * sizeof(double));
            WcHPCStallMtx = (double *)realloc(WcHPCStallMtx,NcHPCMap_Elem * sizeof(double));
            PRHPCStallMtx = (double *)realloc(PRHPCStallMtx,NcHPCMap_Elem * sizeof(double));
            WcHPCMapMtx = (double *)realloc(WcHPCMapMtx,WcHPCMap_Elem * sizeof(double));
            PRHPCMapMtx = (double *)realloc(PRHPCMapMtx,WcHPCMap_Elem * sizeof(double));
            EffHPCMapMtx = (double *)realloc(EffHPCMapMtx,WcHPCMap_Elem * sizeof(double));

            /* Turbine */
            NcHPTMapMtx = (double *)realloc(NcHPTMapMtx,NcHPTMap_Elem * sizeof(double));
            WcHPTMapMtx = (double *)realloc(WcHPTMapMtx,WcHPTMap_Elem * sizeof(double));
            EffHPTMapMtx = (double *)realloc(EffHPTMapMtx,WcHPTMap_Elem * sizeof(double));
            PRHPTMapMtx = (double *)realloc(PRHPTMapMtx,PRHPTMap_Elem * sizeof(double));

            /* Auxiliar matrices */
            Mtx2D = (double *)realloc(Mtx2D,MN_Elem * Fn_Elem * sizeof(double));
            Mtx2DH = (double *)realloc(Mtx2DH,MN_Elem * Fn_Elem * sizeof(double));
            Mtx1D = (double *)realloc(Mtx1D,Fn_Elem * sizeof(double));
            Mtx1DH = (double *)realloc(Mtx1DH,Fn_Elem * sizeof(double));

            DeltaMtx2D = (double *)realloc(DeltaMtx2D,Alt_Elem * MN_Elem * sizeof(double));
            DeltaMtx2DH = (double *)realloc( DeltaMtx2DH,Alt_Elem * MN_Elem * sizeof(double));
            DeltaMtx1D = (double *)realloc(DeltaMtx1D,MN_Elem * sizeof(double));
            DeltaMtx1DH = (double *)realloc(DeltaMtx1DH,MN_Elem * sizeof(double));

            Ts0Mtx2D = (double *)realloc(Ts0Mtx2D,Fn_Elem * sizeof(double));
            Ts0Mtx2DH = (double *)realloc(Ts0Mtx2DH,Fn_Elem * sizeof(double));
            Ts0Mtx1D = (double *)realloc(Ts0Mtx1D,Alt_Elem * sizeof(double));
            Ts0Mtx1DH = (double *)realloc(Ts0Mtx1DH,Alt_Elem * sizeof(double));

            MapFAN2D = (double *)realloc(MapFAN2D,WcFANMap_Elem * sizeof(double));
            MapFAN2DH = (double *)realloc(MapFAN2DH,WcFANMap_Elem * sizeof(double));
            MapFAN1D = (double *)realloc(MapFAN1D,Wc_per_Nc_FAN * sizeof(double));
            MapFAN1DH = (double *)realloc(MapFAN1DH,Wc_per_Nc_FAN * sizeof(double));

            MapHPC2D = (double *)realloc(MapHPC2D,WcHPCMap_Elem * sizeof(double));
            MapHPC2DH = (double *)realloc(MapHPC2DH,WcHPCMap_Elem * sizeof(double));
            MapHPC1D = (double *)realloc(MapHPC1D,Wc_per_Nc_HPC * sizeof(double));
            MapHPC1DH = (double *)realloc(MapHPC1DH,Wc_per_Nc_HPC * sizeof(double));

            /* MN linerizing vector */
            MNLinVec = (double *)realloc(MNLinVec,MN_Elem * sizeof(double));
            AltLinVec = (double *)realloc(AltLinVec,Alt_Elem * sizeof(double));
            DeltaMtx = (double *)realloc(DeltaMtx,Alt_Elem * MN_Elem * sizeof(double));
            Ts0Mtx = (double *)realloc(Ts0Mtx,Alt_Elem * MN_Elem * sizeof(double));

            /* Reference filter vectors */
            ASVec = (double *)realloc(ASVec,AS_Elem * sizeof(double));
            DSVec = (double *)realloc(DSVec,AS_Elem * sizeof(double));
            NcVec = (double *)realloc(NcVec,AS_Elem * sizeof(double));

//            /* -------------------------------------------------- */
//            /* REALLOCKING MEMORY - PWLM                          */
//            /* (To be usedi in MATLAB (PWLM) simulations only)    */
//            /* -------------------------------------------------- */


//            /* Matrices used for reference and gain calculations */
//            N_KiMtx = (double *)malloc(PowerMan_Elem * sizeof(double));
//            N_KpMtx = (double *)malloc(PowerMan_Elem * sizeof(double));
//            NcFANContMtx = (double *)malloc(PowerMan_Elem * sizeof(double));
//            FNperContMtx = (double *)malloc(PowerMan_Elem * sizeof(double));
//            FNcMaxContMtx = (double *)malloc(MN_Elem * sizeof(double));

//            /* Matrices used for model calculations */
//            NcMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Pt21Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Pt3Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Pt5Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Pt6Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Tt21Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Tt3Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Tt4Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Tt5Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Tt6Mtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            WfMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            AMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            BMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Pt21DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Pt3DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Pt5DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Pt6DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Tt21DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Tt3DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Tt4DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Tt5DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));
//            Tt6DMtx = (double *)malloc(SteadyOp_Elem * sizeof(double));

//            /* Matrices used for sub-idle calculations */
//            AwmMtx = (double *)malloc(MN_Elem * sizeof(double));
//            AshMtx = (double *)malloc(MN_Elem * sizeof(double));
//            BwmMtx = (double *)malloc(MN_Elem * sizeof(double));
//            BshMtx = (double *)malloc(MN_Elem * sizeof(double));
//            RPMwmMtx = (double *)malloc(MN_Elem * sizeof(double));
//            RPMshMtx = (double *)malloc(MN_Elem * sizeof(double));
//            Tt4CshMtx = (double *)malloc(1 * sizeof(double));
//            Tt4DshMtx = (double *)malloc(1 * sizeof(double));
//            Tt4shMtx = (double *)malloc(1 * sizeof(double));
//            WfshMtx = (double *)malloc(1 * sizeof(double));

//            /* Low Pressure Compressor or Fan */
//            NcFANMapMtx = (double *)malloc(NcFANMap_Elem * sizeof(double));
//            WcFANStallMtx = (double *)malloc(NcFANMap_Elem * sizeof(double));
//            PRFANStallMtx = (double *)malloc(NcFANMap_Elem * sizeof(double));
//            WcFANMapMtx = (double *)malloc(WcFANMap_Elem * sizeof(double));
//            PRFANMapMtx = (double *)malloc(WcFANMap_Elem * sizeof(double));
//            EffFANMapMtx = (double *)malloc(WcFANMap_Elem * sizeof(double));

//            /* High Pressure Compressor */
//            NcHPCMapMtx = (double *)malloc(NcHPCMap_Elem * sizeof(double));
//            WcHPCStallMtx = (double *)malloc(NcHPCMap_Elem * sizeof(double));
//            PRHPCStallMtx = (double *)malloc(NcHPCMap_Elem * sizeof(double));
//            WcHPCMapMtx = (double *)malloc(WcHPCMap_Elem * sizeof(double));
//            PRHPCMapMtx = (double *)malloc(WcHPCMap_Elem * sizeof(double));
//            EffHPCMapMtx = (double *)malloc(WcHPCMap_Elem * sizeof(double));

//            /* Turbine */
//            NcHPTMapMtx = (double *)malloc(NcHPTMap_Elem * sizeof(double));
//            WcHPTMapMtx = (double *)malloc(WcHPTMap_Elem * sizeof(double));
//            EffHPTMapMtx = (double *)malloc(WcHPTMap_Elem * sizeof(double));
//            PRHPTMapMtx = (double *)malloc(PRHPTMap_Elem * sizeof(double));

//            /* Auxiliar matrices */
//            Mtx2D = (double *)malloc(MN_Elem * Fn_Elem * sizeof(double));
//            Mtx2DH = (double *)malloc(MN_Elem * Fn_Elem * sizeof(double));
//            Mtx1D = (double *)malloc(Fn_Elem * sizeof(double));
//            Mtx1DH = (double *)malloc(Fn_Elem * sizeof(double));

//            DeltaMtx2D = (double *)malloc(Alt_Elem * MN_Elem * sizeof(double));
//            DeltaMtx2DH = (double *)malloc(Alt_Elem * MN_Elem * sizeof(double));
//            DeltaMtx1D = (double *)malloc(MN_Elem * sizeof(double));
//            DeltaMtx1DH = (double *)malloc(MN_Elem * sizeof(double));

//            Ts0Mtx2D = (double *)malloc(Fn_Elem * sizeof(double));
//            Ts0Mtx2DH = (double *)malloc(Fn_Elem * sizeof(double));
//            Ts0Mtx1D = (double *)malloc(Alt_Elem * sizeof(double));
//            Ts0Mtx1DH = (double *)malloc(Alt_Elem * sizeof(double));

//            MapFAN2D = (double *)malloc(WcFANMap_Elem * sizeof(double));
//            MapFAN2DH = (double *)malloc(WcFANMap_Elem * sizeof(double));
//            MapFAN1D = (double *)malloc(Wc_per_Nc_FAN * sizeof(double));
//            MapFAN1DH = (double *)malloc(Wc_per_Nc_FAN * sizeof(double));

//            MapHPC2D = (double *)malloc(WcHPCMap_Elem * sizeof(double));
//            MapHPC2DH = (double *)malloc(WcHPCMap_Elem * sizeof(double));
//            MapHPC1D = (double *)malloc(Wc_per_Nc_HPC * sizeof(double));
//            MapHPC1DH = (double *)malloc(Wc_per_Nc_HPC * sizeof(double));

//            /* MN linerizing vector */
//            MNLinVec = (double *)malloc(MN_Elem * sizeof(double));
//            AltLinVec = (double *)malloc(Alt_Elem * sizeof(double));
//            DeltaMtx = (double *)malloc(Alt_Elem * MN_Elem * sizeof(double));
//            Ts0Mtx = (double *)malloc(Alt_Elem * MN_Elem * sizeof(double));

//            /* Reference filter vectors */
//            ASVec = (double *)malloc(AS_Elem * sizeof(double));
//            DSVec = (double *)malloc(AS_Elem * sizeof(double));
//            NcVec = (double *)malloc(AS_Elem * sizeof(double));

//            /* -------------------------------------------------- */

        }

        /*----------------------------------*/
        /* UPDATES ENGINE MATRICES ELEMENTS */
        /*----------------------------------*/

        if (WhichEngine == 1)
        {
            /* Loads matrices */
            getTJ1200Mtx(NcFANContMtx, N_KpMtx, N_KiMtx, FNperContMtx, FNcMaxContMtx, NcMtx, Pt21Mtx, Pt3Mtx, Pt5Mtx, Pt6Mtx,
                         Tt21Mtx, Tt3Mtx, Tt4Mtx, Tt5Mtx, Tt6Mtx, WfMtx, AMtx, BMtx, Pt21DMtx, Pt3DMtx, Pt5DMtx, Pt6DMtx,
                         Tt21DMtx, Tt3DMtx, Tt4DMtx, Tt5DMtx, Tt6DMtx, NcFANMapMtx, WcFANMapMtx, WcFANStallMtx, PRFANMapMtx,
                         PRFANStallMtx, EffFANMapMtx, NcHPTMapMtx, WcHPTMapMtx, PRHPTMapMtx, EffHPTMapMtx,
                         NcHPCMapMtx, WcHPCMapMtx, WcHPCStallMtx, PRHPCMapMtx, PRHPCStallMtx, EffHPCMapMtx, MNLinVec, AltLinVec, DeltaMtx, Ts0Mtx,
                         AwmMtx, AshMtx, BwmMtx, BshMtx, RPMwmMtx, RPMshMtx, Tt4CshMtx, Tt4DshMtx, Tt4shMtx, WfshMtx,
                         ASVec, DSVec, NcVec);

            /* Loads controller constants */
            getTJ1200ContConst(&ContConst);

        }
        if (WhichEngine == 2)
        {
            /* Loads matrices */
            getTF1200Mtx(NcFANContMtx, N_KpMtx, N_KiMtx, FNperContMtx, FNcMaxContMtx, NcMtx, Pt21Mtx, Pt3Mtx, Pt5Mtx, Pt6Mtx,
                         Tt21Mtx, Tt3Mtx, Tt4Mtx, Tt5Mtx, Tt6Mtx, WfMtx, AMtx, BMtx, Pt21DMtx, Pt3DMtx, Pt5DMtx, Pt6DMtx,
                         Tt21DMtx, Tt3DMtx, Tt4DMtx, Tt5DMtx, Tt6DMtx, NcFANMapMtx, WcFANMapMtx, WcFANStallMtx, PRFANMapMtx,
                         PRFANStallMtx, EffFANMapMtx, NcHPTMapMtx, WcHPTMapMtx, PRHPTMapMtx, EffHPTMapMtx,
                         NcHPCMapMtx, WcHPCMapMtx, WcHPCStallMtx, PRHPCMapMtx, PRHPCStallMtx, EffHPCMapMtx, MNLinVec, AltLinVec, DeltaMtx, Ts0Mtx,
                         AwmMtx, AshMtx, BwmMtx, BshMtx, RPMwmMtx, RPMshMtx, Tt4CshMtx, Tt4DshMtx, Tt4shMtx, WfshMtx,
                         ASVec, DSVec, NcVec);

            /* Loads controller constants */
            getTF1200ContConst(&ContConst);

        }
        if (WhichEngine == 3)
        {
            /* Loads matrices */
            getGEJ85Mtx(NcFANContMtx, N_KpMtx, N_KiMtx, FNperContMtx, FNcMaxContMtx, NcMtx, Pt21Mtx, Pt3Mtx, Pt5Mtx, Pt6Mtx,
                        Tt21Mtx, Tt3Mtx, Tt4Mtx, Tt5Mtx, Tt6Mtx, WfMtx, AMtx, BMtx, Pt21DMtx, Pt3DMtx, Pt5DMtx, Pt6DMtx,
                        Tt21DMtx, Tt3DMtx, Tt4DMtx, Tt5DMtx, Tt6DMtx, NcFANMapMtx, WcFANMapMtx, WcFANStallMtx, PRFANMapMtx,
                        PRFANStallMtx, EffFANMapMtx, NcHPTMapMtx, WcHPTMapMtx, PRHPTMapMtx, EffHPTMapMtx,
                        NcHPCMapMtx, WcHPCMapMtx, WcHPCStallMtx, PRHPCMapMtx, PRHPCStallMtx, EffHPCMapMtx, MNLinVec, AltLinVec, DeltaMtx, Ts0Mtx,
                        AwmMtx, AshMtx, BwmMtx, BshMtx, RPMwmMtx, RPMshMtx, Tt4CshMtx, Tt4DshMtx, Tt4shMtx, WfshMtx,
                        ASVec, DSVec, NcVec);

            /* Loads controller constants */
            getGEJ85ContConst(&ContConst);
        }

        /*------------------------------------------*/
        /* CALCULATION OF ENGINE INITIAL CONDITIONS */
        /*------------------------------------------*/

        if (EngOutput.ICCalc == 0)
        {
printf("EngUnits=%d, reference=%f\n",EngUnits,reference);
            /* Reads Altitude, MN and dT for calculating initial conditions */
            InitCond(&SkipStart, SteadyOp_Elem, MN_Elem, Fn_Elem, Altitude, MN, dT, EngPars.NDes, reference, &Ambient, MNLinVec, FNperContMtx,
                     NcFANContMtx, FNcMaxContMtx, WfMtx, Mtx2D, Mtx2DH, Mtx1D, Mtx1DH, &EngOutput, EngUnits);

            /* Calculates initial conditions */
            Wf0 = EngOutput.Wf;
            fValue = Wf0;

            /* Sets initial conditions for oil pump rotation speed - bearings model must be validated!! */
            OPRPM = ContConst.OPRPMMax;

            /* If Wf0 is zero, OPRPM must start with zero */
            if (Wf0 <= 0.000001)
            {
                OPRPM = 0;
            }

printf("Wf0 = %f, OPRPM = %f\n\n", Wf0, OPRPM);
        }

        /*---------------------------------------------*/
        /* INITIATES REFERENCE COMMAND WITH IDLE VALUE */
        /*---------------------------------------------*/

        /* In the case of the model, initialization of */
        /* RefCAN or even reference is made after the  */
        /* calculation of initial conditions, since    */
        /* the variable reference is directly used for */
        /* such */

        /* The value of RefCAN and reference are set
         to ContConst.FNIdle only if and engine start
         is executed, which is indicated by the low
         value of Wf0*/
//        if(Wf0 < 0.0001)
//        {
//            RefCAN = ContConst.FNIdle;
//            reference = ContConst.FNIdle;
//        }

        /***************** INICIALIZANDO O TIMER ******************/

        /* Reset variable must be set to 0 in order for inner
         * loop not to reset the timer consecutively */
        Reset = 0;

        /* Starts timers */
        //startTimers();
        //if(!(simMod == 2))  //0 = SIL, 1 = HIL Async, 2 = HIL Sync, 3 = Test Bench. So, if the mode is SIL or HIL Async, starts the periodic_timer, without sync from FADEC.
        if((HILMode == 0) | (HILMode == 1))  //0 = SIL, 1 = HIL Async, 2 = HIL Sync, 3 = Test Bench. So, if the mode is SIL or HIL Async, starts the periodic_timer.
        {

            Tsample = 0.001 * TICK;
            TsamModel = Tsample / TsampDiv;
                    //periodic_timer.startPeriodic(uavcan::MonotonicDuration::fromMSec(Tsample*1000));	//PERIODO DE ATUALIZACAO DOS DADOS NO BARRAMENTO
                    //upTime_ms = 0;
                    //lastUpdateTime_ms = 0;
        }

/********************************************************************************************************************************/
/*																																*/
/*												LOOP INTERNO                             									 	*/
/*																																*/
/********************************************************************************************************************************/
        monotonicTimer_initialValue = nodeCAN0->getMonotonicTime();     //initial value of monotonic value to calculate uptime of the node.
        while(1)	//inner loop
        {

            /*spinCAN0_res = nodeCAN0->spinOnce();
            if (spinCAN0_res < 0)
            {
                std::cerr << "Transient failure: " << spinCAN0_res << std::endl;
            }*/

//            spinCAN1_res = nodeCAN1.spinOnce();
//             if (spinCAN1_res < 0)
//             {
//                 std::cerr << "Transient failure: " << spinCAN1_res << std::endl;
//             }

            //read_ATDPOC_canmsg(can_atd_poc);

            /*if(flagSync == 1)   //if the FADEC_STATUS message was received, starts the sync timer
            {
                flagSync = 0;
                if(HILMode == 2) //0 = SIL, 1 = HIL Async, 2 = HIL Sync, 3 = Test Bench
                    one_shot_timer_sync.startOneShotWithDelay(uavcan::MonotonicDuration::fromMSec(5));
            }*/

            //upTime_ms = upTime_ms + Tsample*1000;
            if(HILMode != 2)    //0 = SIL, 1 = HIL Async, 2 = HIL Sync, 3 = Test Bench. If the mode is NOT HIL Sync
            {
                upTime_ms = nodeCAN0->getMonotonicTime().toMSec() - monotonicTimer_initialValue.toMSec();

                if( upTime_ms < (lastUpdateTime_ms + UPDATE_TIMERATE_MS - 6) )  //runs nodespin() until 6ms before the next update cycle.
                {
                    spinCAN0_res = nodeCAN0->spin(uavcan::MonotonicDuration::fromMSec(2));
                    if (spinCAN0_res < 0)
                    {
                        std::cerr << "Transient failure: " << spinCAN0_res << std::endl;
                    }
                }



                if ( upTime_ms >= (lastUpdateTime_ms + UPDATE_TIMERATE_MS) )
                {
    //std::cout << upTime_ms << std::endl;
                    tempo6 = upTime_ms;
                    lastUpdateTime_ms = upTime_ms;
                    sendUAVCANKeyValueMsg(nodeCAN0,"_up", (float) upTime_ms);

                    spinCAN0_res = nodeCAN0->spin(uavcan::MonotonicDuration::fromMSec(5));    //spins again to wait for response of uavcan nodes
                    if (spinCAN0_res < 0)
                    {
                        std::cerr << "Transient failure: " << spinCAN0_res << std::endl;
                    }

                    EngineModelUpdate(nodeCAN0, can_atd_poc);

                    flag_updFile = 1;

                }
            }

            else if (HILMode == 2)  //0 = SIL, 1 = HIL Async, 2 = HIL Sync, 3 = Test Bench
            {
                if(flagSync == 1)   //if the FADEC_STATUS message was received, starts the sync timer
                {
                    flagSync = 0;
                    upTime_ms = upTime_ms + SYNC_UPDATE_TIMERATE_MS;    //Known timerate of FADEC.

                    sendUAVCANKeyValueMsg(nodeCAN0,"_up", (float) upTime_ms);

                    spinCAN0_res = nodeCAN0->spin(uavcan::MonotonicDuration::fromMSec(5));    //spins again to wait for response of uavcan nodes
                    if (spinCAN0_res < 0)
                    {
                        std::cerr << "Transient failure: " << spinCAN0_res << std::endl;
                    }

                    EngineModelUpdate(nodeCAN0, can_atd_poc);

                    flag_updFile = 1;
                }
            }

            else
            {
                std::cout << "HILMode ERROR!" << std::endl;
            }



            if(Reset == 1)
            {
                /* Stops timer */
                //periodic_timer.stop();

                upTime_ms = 0;
                lastUpdateTime_ms = 0;      //clears the last time the model was updated.

                clock_gettime(CLOCK_MONOTONIC, &initialTime);   //resets the initial time for ATDPOC thread, so upTime_sendATDPOCmsg_ms becomes near zero on next calculation inside the thread.
                last_sendATDPOCmsg_ms = 0;

                last_saveTelemetryFile_ms = 0;
				
                /* Breaks the current  while loop */
                break;
            }

        }

/*********************************************************************************************************************/


    }
}   //END OF main(int argc, const char** argv)





void EngineModelUpdate(uavcan_linux::NodePtr& node0, int can_atd_poc)
{
//std::chrono::steady_clock::time_point begin_tempo3 = std::chrono::steady_clock::now();

	/* ================================================================================= */
    /* THE FOLLOWIN CODE MUST BE EXECUTED BY A TIMER ROUTINE OF THE HARDWARE IN THE LOOP */
    /* ================================================================================= */

    /* ------------------------------------------------------------------------------------------ */
    /* INPUT READING - Make sure to use the appropriate piece of code: MATLAB or actual hardware  */
    /* ------------------------------------------------------------------------------------------ */

    /* ACTUAL HARDWARE  */

    //Altitude = 0;
    //MN = 0;
    //dT = 0;
    Ignition = digital.bits.igniter;
    Wf = fValue;
//    RefCAN = (double)reference;
//    FNpc = RefCAN;
	//Reset = Edge(ResetButton);	//the Edge function will be called on reset CAN message ("_rs") reception

    ResetButton[1] = ResetButton[0];
    ResetButton[0] = 0;

    /* MATLAB */

    /*
    Altitude = InputVars[0];
    MN = InputVars[1];
    dT = InputVars[2];
    FuelIn = InputVars[3];
    IgniterIn = InputVars[4];
    reference = InputVars[5];
    ResetButton[0] = InputVars[6];
    Reset = Edge(ResetButton);
    ResetButton[1] = ResetButton[0];
    */

    /* --------------------------------------------------------------------------------------------------- */
    /*   HARDWARE IN THE LOOP - Make sure to use the appropriate piece of code: MATLAB or actual hardware  */
    /* --------------------------------------------------------------------------------------------------- */

    /* ACTUAL HARDWARE */

    if (HILMode != 0 && bit_start == 1) {   //if it is HIL Mode,

     /* Reads values of wf and digital inputs from CAN network */

     fValue = (double)model_mf;

     fValue = fValue / 5 * WfMax_Pump;
     digital.bits.igniter = model_d1_toInt & 1;

     OPRPM = ( (double)model_oilFlow / 5 ) * 12000;     //The oilflow conversion is: 0~5V to 0~12000RPM. IMPORTANT: the max RPM of oilpump is 9000 RPM = 3.75V.

    }

    /* -------------------------------------------------- */
    /* UPDATING fValue & igniter - PWLM                   */
    /* (To be usedi in MATLAB (PWLM) simulations only)    */
    /* -------------------------------------------------- */
    /*
    if (HILMode != 0 && EngOutput.ICCalc != 0) {

        fValue = FuelIn;
        digital.bits.igniter = IgniterIn;

    }
    */
    /* -------------------------------------------------- */

    /*--------------------*/
    /* MODEL CALCULATIONS */
    /*--------------------*/

    /* Input readings */
    Ignition = digital.bits.igniter;
    Wf = fValue;
//    RefCAN = (double)reference;
//    FNpc = RefCAN;

    /* Updates FNpc and allows transition from IDLE to REGIME depending no reference value */
    IdleToRegime(&EngStatus, &ContInput, reference, 0, ContConst.FNIdle, &FNpc, LeverMode);

//printf("Outside PIMMRF.c: FNpc = %f\n", FNpc);
    /* Bearing 0 Model Inputs */
    Bear0.A = -0.5;
    Bear0.B = 1;
    Bear0.C = -0.5;
    Bear0.DelTExt = 0;
    Bear0.ElNumRPME = 3;
    Bear0.MaxRPMP = 4500;
    Bear0.Ts = TsamModel;

    /* Bearing 1 Model Inputs */
    Bear1.A = -0.5;
    Bear1.B = 1;
    Bear1.C = -0.5;
    Bear1.DelTExt = 0;
    Bear1.ElNumRPME = 3;
    Bear1.MaxRPMP = 4500;
    Bear1.Ts = TsamModel;

    /* Bearing 2 Model Inputs */
    Bear2.A = -0.5;
    Bear2.B = 1;
    Bear2.C = -0.5;
    Bear2.DelTExt = 0;
    Bear2.ElNumRPME = 3;
    Bear2.MaxRPMP = 4500;
    Bear2.Ts = TsamModel;

    /* Smulation of Engine BlowOut */
    BlowOutSim(&SysFaults, &Wf);

    /* Smulation of Ignition Fault */
    IgnitionFault(&SysFaults, &Ignition);
//mexPrintf("Executing Engine Model Loop\n");
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
        Tt4CshMtx, Tt4DshMtx, Tt4shMtx,WfshMtx,
        &Faults, &Sensors,
        TsamModel);

        /* Calculates bearing model outputs */
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

        /* Bearings calculations */
        BearingModel(&Bear0, RPMEVec, TNOil_Bear0, DelT_Bear0);
        BearingModel(&Bear1, RPMEVec, TNOil_Bear1, DelT_Bear1);
        BearingModel(&Bear2, RPMEVec, TNOil_Bear2, DelT_Bear2);

        /* Updates engine outputs - should be done inside EnginModel in the future!! */
        EngOutput.TBear[0] = Bear0.Tout;
        EngOutput.TBear[1] = Bear1.Tout;
        EngOutput.TBear[2] = Bear2.Tout;
//printf("EngOutput.TBear[0]=%0.1f\tEngOutput.TBear[1]=%0.1f\tEngOutput.TBear[2]=%0.1f\n",EngOutput.TBear[0],EngOutput.TBear[1],EngOutput.TBear[2]);

        /* FUEL PRESSURE AND OIL PRESSURE MODELS - Must be updated EngineModel in the future!! */

        /* Updates PFuell model value, which becomes proportional to the fuel flow */
        //EngOutput.PFuel = ContConst.PFuelHigh * Wf / ContConst.WfMax * 0.95;

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
//printf("Sensors.TBear[0]=%0.1f\Sensors.TBear[1]=%0.1f\Sensors.TBear[2]=%0.1f\n",Sensors.TBear[0],Sensors.TBear[1],Sensors.TBear[2]);

    /*------------------------------------------------------------------------------------*/
    /* PROVISORY UPDATE OF BEARINGS THERMOCOUPLES - THIS SHOULD BE DONE BY THE ABOVE LINE */
    /* EngOutput must contain, in the future, outputs from a bearing model, which is ready*/
    /*------------------------------------------------------------------------------------*/
    // Sensors.TBear[0] = InputVars[14];
    // Sensors.TBear[1] = InputVars[15];
    // Sensors.TBear[2] = InputVars[16];
    //Sensors.TBear[0] = EngOutput.TBear[0];//Bear0.Tout;
    //Sensors.TBear[1] = EngOutput.TBear[1];//Bear1.Tout;
    //Sensors.TBear[2] = EngOutput.TBear[2];//Bear2.Tout;
    /*------------------------------------------------------------------------------------*/

    /* Simulation of sensors faults */
    SensFaultSim(&SensFaults, &Sensors, &EngPars);

    /* Simulation of sensor bias */
    BiasFaultSim(&SysFaults, &SensorBias, &Sensors);


	/* Sends CAN messages of flag values */

	if(bit_start == 0 & (upTime_ms > (Tsample*2000)))
	{
        //sendUAVCANKeyValueMsg(node1,"_au", (float) EngOutput.ICAuthorize);
		//usleep(1000);
        //sendUAVCANKeyValueMsg(node1,"_sk", (float) SkipStart);
		//usleep(1000);
        //sendUAVCANKeyValueMsg(node1,"_w0", (float) Wf0);
        //usleep(1000);

/************************* Sending authorize and skip_start commands to FADEC via CAN1 (SIATT CAN protocol) ******************************************/
        struct can_frame frame_send;

        union initial_wf
        {
            uint16_t valueInUint16;
            uint8_t valueInBytes[2];
        }initialWf; //as used on fadec_status message, the fuel flow is multiplied by 10000, so the range is 0 to 2000

        union skipStart_authorize_commands
        {
            uint8_t valueInByte;

            struct skipStart_authorize_commands_values
            {
                uint8_t skipStart : 1;
                uint8_t authorize : 1;
                uint8_t reserved : 6;
            }value;
        }commands;



        commands.value.skipStart = (uint8_t) SkipStart;
        commands.value.authorize = (uint8_t) EngOutput.ICAuthorize;
        initialWf.valueInUint16 = Wf0 * 10000; //as used on fadec_status message, the fuel flow is multiplied by 10000, so the range is 0 to 2000
printf("Wf0=%d, command=%x\n", initialWf.valueInUint16, commands.valueInByte);
        frame_send.can_id = FADEC_SKIPSTART_AUTHORIZE_COMMAND | 1 << 31;
        frame_send.can_dlc = 3;
        frame_send.data[0] = initialWf.valueInBytes[0];
        frame_send.data[1] = initialWf.valueInBytes[1];
        frame_send.data[2] = commands.valueInByte;

        send_ATDPOC_canmsg(can_atd_poc, frame_send);
/**********************************************************************************************************************************************************/

		bit_start = EngOutput.ICAuthorize;	
	}

    /* ---------------------------------------------------------------- */
    /* UPDATING bit_start - is done within a condition in HARDWARE CASE */
    /* (To be usedi in MATLAB (PWLM) simulations only)                  */
    /* ---------------------------------------------------------------- */

    //bit_start = EngOutput.ICAuthorize;

    /* ---------------------------------------------------------------- */

    /*----------------------*/
    /* SOFTWARE IN THE LOOP */
    /*----------------------*/

    /* Verifies if software in the loop is required */
    if(HILMode == 0 && bit_start == 1){ //if it is SIL Mode (HILmode==0)

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
//printf("\n\n");
//printf("Dentro de SkipStart: ThrustCommandOn=%d\n\n",ContInput.ThrustCommandOn);
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

        OnOffLogicSR(&EngOnOff, Tsample);

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
            StatusDelay(&WaitTime, Tsample, ContConst.TimeFaultAnaylsis, &StartFaultAnalysis, 1);
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
                      CriticalFailure, 1, Tsample);

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
        Ts2MediumValue(&ModPFault, &Ts2MedVal, ContConst.NumTs2Sens, &TrustAll, &Sensors, ModelParsChosen.Ts2, ContConst.NumTs2SensTrust);
        /* Calculates the medium value of Pt3 - The last indicates the minimum number of trusted sensors before
        untrusted sensors are replaced by model calculated values */
        Pt3MediumValue(&ModPFault, &Pt3MedVal, ContConst.NumPs3Sens, &TrustAll, &Sensors, ModelParsChosen.Pt3, ContConst.NumPs3SensTrust);
        /* Calculates the medium value of Tt4 - The last indicates the minimum number of trusted sensors before
        untrusted sensors are replaced by model calculated values */
        Tt4MediumValue(&ModPFault, &Tt4MedVal, ContConst.NumTt4Sens, &TrustAll, &Sensors, ModelParsChosen.Tt4, ContConst.NumTt4SensTrust);
        /* Calculates the medium value of RPM - The last indicates the minimum number of trusted sensors before
        untrusted sensors are replaced by model calculated values */
        RPMMediumValue(&ModPFault, &RPMMedVal, ContConst.NumRPMSens, &TrustAll, &Sensors, ModelParsChosen.RPM, ContConst.NumRPMSensTrust);

        /* Updates variables with calculated medium values */
        Ts2 = Ts2MedVal;
        Pt3 = Pt3MedVal;
        Tt4 = Tt4MedVal;
        RPM = RPMMedVal;

        /*------------------------------*/
        /* BEARINGS TEMPERATURE CONTROL */
        /*------------------------------*/

        /* Performs oil control as soon as Windmill is reached */
        TBearControl(&ContGenOil, &ContGenEmpty, &EngStatus, &ContConst, &Sensors, OPRPMManual, RPM, LeverMode, Tsample);

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

//        PrintFaults(&FaultWarning, 0, 1);
//        PrintFaults(&FaultStatus, 1, 0);
//        PrintEngStatus(&EngStatus, 1);

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
        ShutDownRef(ShutDownCommand, &ContInput, &ContOutput, &ContConst, Tsample);

        /* BOOSTER PHASE PROTECTION */

        /* If booster is connected, measured value of Pt3 must not be considered and blow out protection must be deactivated */
        BoosterProtect(&ContConst, &ContInput, Delta, BoosterLStatus, BoosterRStatus, Tsample);
//printf("RealCont: BoostL=%d BoostR=%d Time=%f status=%d Delta=%f Pt3=%f\n",BoosterLStatus, BoosterRStatus, ContInput.TimerBoost, ContInput.statusBooster, Delta, ContInput.Pt3);

        /* CALCULATES THE CONTROL LAW */

        /* Calculates fuel flow from control law */
        PIMinMaxRF(AltLinVec, MNLinVec, NcVec, ASVec, DSVec,
                   Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
                   DeltaMtx2D, DeltaMtx2DH, DeltaMtx1D, DeltaMtx1DH,
                   &ContConst, &ContStart, &ContInput, &ContOutput, &digitalWord, &keysWord,
                   DeltaMtx, NcFANContMtx, FNcMaxContMtx, FNperContMtx,
                   N_KpMtx, N_KiMtx, Tsample);
//if(EngStatus.EngStatusBist.ShutOff){printf("FNpc=%f, Wf=%f, StatusSD=%d\n",ContInput.FNpc,ContOutput.Wf,ContInput.StatusSD);}
        /* Updates digital outputs and fuel flow value */
        digital.out = digitalWord;

        /* EXECUTES NOMINAL SHUT DOWN RAMP */

        ShutDownRamp(&ContInput, &ContInputEmpty,
                     &ContOutput, &ContOutputEmpty,
                     &ContStart, &ContStartEmpty,
                     &ContGenOil, &ContGenEmpty,
                     &digital, &ContConst, Tsample);

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
            // ContInModCL.POil = POil;
            // ContInModCL.SkipStart = SkipStart;
            // ContInModCL.Wf0 = Wf0;
            // keysWord = keys.in;
            // digitalWord = digital.out;

            /* NOMINAL SHUT DWON REFERENCE */

            /* If nominal shut down has been requested, controller reference must be set to minimum */
            ShutDownRef(ShutDownCommand, &ContInModCL, &ContOutModCL, &ContConst, Tsample);

            /* BOOSTER PHASE PROTECTION */

            /* If booster is connected, measured value of Pt3 must not be considered and blow out protection must be deactivated
            The same situation is reproduced in the model in order for more accureate reproduction of the real situation */
            BoosterProtect(&ContConst, &ContInModCL, Delta, BoosterLStatus, BoosterRStatus, Tsample);

            /* CALCULATES THE CONTROL LAW */

            /* Calculates fuel flow from control law for closed-loop model */
            PIMinMaxRF(AltLinVec, MNLinVec, NcVec, ASVec, DSVec,
                       Mtx2D, Mtx2DH, Mtx1D, Mtx1DH,
                       DeltaMtx2D, DeltaMtx2DH, DeltaMtx1D, DeltaMtx1DH,
                       &ContConst, &ContStModCL, &ContInModCL, &ContOutModCL, &digitalWord, &keysWord,
                       DeltaMtx, NcFANContMtx, FNcMaxContMtx, FNperContMtx,
                       N_KpMtx, N_KiMtx, Tsample);

            /* EXECUTES NOMINAL SHUT DOWN RAMP */

            /* The same situation during shut down is reproduced in the closed-loop model
            for more accurate reproduction of the real situation */
            ShutDownRamp(&ContInModCL, &ContInputEmpty,
                         &ContOutModCL, &ContOutputEmpty,
                         &ContStModCL, &ContStartEmpty,
                         &ContGenOilCL, &ContGenEmpty,
                         &digModCL, &ContConst, Tsample);

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

//    /*---------------------------------------*/
//    /* UPDATES PRESENT ONLY ON MODEL (MATLAB)*/
//    /*---------------------------------------*/

//    /* UPDATES Wf AND fValue - THE VARIABLE fValue MUST BE REPLACED BY Wf IN FUTURE VERSIONS*/
//    ContOutput.fValue = Wf;
//    ContOutput.FiltRef = ContOutput.MinRef;
//    /* Updates digital outputs and fuel flow value */
//    digital.out = digitalWord;
//    fValue = ContOutput.fValue;


/*static int contagem = 0;

if(FNpc == 1)
{
	if(contagem < 100)
	{
		//printf("Wf = %f\n",fValue);
		std::cout << contagem << ". x(k) = " << RPM;
		std::cout << "; u(k) = " << fValue << std::endl;
		contagem = contagem + 1;
	}
	
}
else
{
	contagem = 0;
}*/

/* !!!!!SAÍDAS DO MATLAB, SÓ PRA SE GUIAR!!!! */

//    /* ------------------------------------------------- */
//    /* UPDATING OUTPUT - PWLM & TMATS                    */
//    /* (To be usedi in MATLAB (PWLM) simulations only)   */
//    /* ------------------------------------------------- */

//	/* Writes SIMULINK outputs */
//	Iout[0] = W2;
//	Iout[1] = Pt2;
//	Iout[2] = Tt2;
//	Iout[3] = NcFAN;
//	Iout[4] = WcFAN;
//	Iout[5] = PRFAN;
//	Iout[6] = SMFAN;
//	Iout[7] = BPFAN;
//	Iout[8] = W21;
//	Iout[9] = Pt21;
//	Iout[10] = Tt21;
//	Iout[11] = NcHPC;
//	Iout[12] = WcHPC;
//	Iout[13] = PRHPC;
//	Iout[14] = SMHPC;
//	Iout[15] = Pt3;
//	Iout[16] = Tt3;
//	Iout[17] = Tt4;
//	Iout[18] = fValue;
//	Iout[19] = Pt5;
//	Iout[20] = Tt5;
//	Iout[21] = Pt6;
//	Iout[22] = Tt6;
//	Iout[23] = W8;
//	Iout[24] = MN8;
//	Iout[25] = Fn;
//	Iout[26] = Fg;
//	Iout[27] = RPM;
//	Iout[28] = POil;
//	Iout[29] = Ignition;
//	Iout[30] = ContOutput.RPMRef;
//	Iout[31] = ContOutput.FiltRef;
//	Iout[32] = ContOutput.Active;

//	Init[0] = Wf0;
//	Init[1] = SkipStart;
//	Init[2] = EngOutput.ICAuthorize;

//    /* Simulation of sensors - SIMULINK Output */

//    /* Station 2 */
//    ISens[0] = Sensors.Ts2[0];
//    ISens[1] = Sensors.Ts2[1];
//    /* Station 3 */
//    ISens[2] = Sensors.Pt3[0];
//    /* Station 4 */
//    ISens[3] = Sensors.Tt4[0];
//    ISens[4] = Sensors.Tt4[1];
//    ISens[5] = Sensors.Tt4[2];
//    /* Shaft */
//    ISens[6] = Sensors.RPM[0];
//    ISens[7] = Sensors.RPM[1];
//    /* POil */
//    ISens[8] = Sensors.POil[0];
//    /* PFuel */
//    ISens[9] = Sensors.PFuel[0];
//    /* Vibrabion */
//    ISens[10] = Sensors.Vibration[0];

//    /* ---------------------------------------------------------------- */

//std::chrono::steady_clock::time_point end_tempo3 = std::chrono::steady_clock::now();
//tempo3 = std::chrono::duration_cast<std::chrono::microseconds>(end_tempo3 - begin_tempo3).count();
//std::cout << "t2:" << tempo2 << std::endl;
    /*---------------------------------------------------------------*/
    /* THE FOLLOWING CODE SENDS A MESSAGE THROUGH CAN COMMUNICATION  */
    /*---------------------------------------------------------------*/
//std::chrono::steady_clock::time_point begin_tempo4 = std::chrono::steady_clock::now();

    float keyValueFloat = 0;

    /* Sends Pt3 - P0 value to UAVCAN net*/
    //keyValueFloat = ((float) Pt3 - (float) P0) * 1e-5;	//sends Pt3 value in bar to Supervisorio
//keyValueFloat = ((float) Pt3) * 1e-5;	//sends Pt3 value in bar to Supervisorio
//sendUAVCANKeyValueMsg(node1, "_p3", keyValueFloat);
//After, Pt3 is converted to voltage
//keyValueFloat = ((((float) Pt3 - (float) P0) * 1e-5) * 0.4) + 1;//P3 needs to be converted from 0~5V to 1~5V, simulating the same signal of testbench
								//this conversion is done on the following way:
								//P3_volts = (P3_bar * 4/10) + 1
								//this way: 0 bar = 1V; 10 bar = 5V; 5 bar = 3V
//                            keyValueFloat = ((((float) Pt3) * 1e-5) * 0.4) + 1;	//IMPORTANT! 16/09/2021: Now the Pt3 signal is being sent with NO DELTA to ambient pressure.
//                                sendUAVCANKeyValueMsg(node0, "_p3", keyValueFloat);
//                                //sendUAVCANKeyValueMsg(node1, "_p3", keyValueFloat);
//                                usleep(1000);

//                                 /* Sends Tt5-1 value to UAVCAN net in Kelvin*/
//                                keyValueFloat = (float) Tt5;
//                                sendUAVCANKeyValueMsg(node0, "_t4", keyValueFloat);	//sends the same value for 3 thermocouples, then FADEC calculates the average temperature
//                                //sendUAVCANKeyValueMsg(node1, "_t4", keyValueFloat);
//                                usleep(1000);
//                                sendUAVCANKeyValueMsg(node0, "_t3", keyValueFloat);
//                                usleep(1000);
//                                sendUAVCANKeyValueMsg(node0, "_t2", keyValueFloat);
//                                usleep(1000);

//                                keyValueFloat = (float) Tt2;
//                                sendUAVCANKeyValueMsg(node0, "_t1", keyValueFloat);
//                                usleep(1000);

//                                 /* Sends Tt2 value to UAVCAN net in Kelvin*/
//                                //keyValueFloat = (float) Tt2;
//                                //sendUAVCANKeyValueMsg(node, CAN0, "_t2", keyValueFloat);
//                                //usleep(1000);
//                                 /* Sends Tt2 value to UAVCAN net in Kelvin*/
//                                keyValueFloat = (float) Tt2;
//                                sendUAVCANKeyValueMsg(node0, "tt2", keyValueFloat);	//sends Tt2 temperature to FADEC via CAN instead of via thermocouple simulator
//                                //sendUAVCANKeyValueMsg(node1, "tt2", keyValueFloat);	//sends Tt2 temperature to FADEC via CAN instead of via thermocouple simulator
//                                usleep(1000);

//                                 /* Sends Pt2 value to UAVCAN net in pascal*/
//                                keyValueFloat = (float) ((float) Pt2 - (float) P0) * 1e-5;
//                                sendUAVCANKeyValueMsg(node0, "_p2", keyValueFloat);
//                                //sendUAVCANKeyValueMsg(node1, "_p2", keyValueFloat);
//                                usleep(1000);

//                                 /* Sends POil value to UAVCAN net in pascal*/
//                                keyValueFloat = (float) ((float) POil - (float) P0) * 1e-5;
//                                sendUAVCANKeyValueMsg(node0, "_po", keyValueFloat);
//                                //sendUAVCANKeyValueMsg(node1, "_po", keyValueFloat);
//                                usleep(1000);

//                                keyValueFloat = (float) RPM;
//                                sendUAVCANKeyValueMsg(node0, "_ra", keyValueFloat);
//                                //sendUAVCANKeyValueMsg(node1, "_ra", keyValueFloat);
//                                usleep(1000);

//                                keyValueFloat = (float) RPM;
//                                sendUAVCANKeyValueMsg(node0, "_rb", keyValueFloat);
//                                //sendUAVCANKeyValueMsg(node1, "_rb", keyValueFloat);
//                                usleep(1000);

    //Saídas Analógicas: _o0 - Pt3 ; _o1 - Vib ; _o2 - PFuel ; _o3 - POil
    //
    //keyValueFloat = ((((float) Sensors.Pt3[0]) * 1e-5) * 0.4) + 1;	//IMPORTANT! 16/09/2021: Now the Pt3 signal is being sent with NO DELTA to ambient pressure.

    //keyValueFloat = (( (Sensors.Pt3[0] - Ambient.Ps) * (4.0/1000000.0) + 1.0) * ((650.0+250.0)/250.0)) / 2;   //conversion from Pa to Volts: Sensor range: 0~10bar = 0~1000000 Pa = 1~5 V.
    keyValueFloat = (( (Sensors.Pt3[0] - Ambient.Ps) * (4.0/1000000.0) + 1.0) * ((620.0+250.0)/250.0)) / 2;   //conversion from Pa to Volts: Sensor range: 0~10bar = 0~1000000 Pa = 1~5 V.
                                                        //When pressure is 0, the voltage output must be 1V to simulate the 4mA sensor output. When sensor is at max range value, the output must be 5V, simulating 20mA.
                                                        //There is a voltage divider in the input of FADEC, with R1 = 620Ohm and R2 = 250Ohm. Also, the output of analog module is configured to 0~10V, but the input command is still 5V, so the value sent to the module must be divided by 2.
                                                        //So the conversion is: (Pt3 * (4/MaxRangeValue) + 1) * VoltDivider = (Pt3 * (4/1000000) + 1) * ((620+250)/250) - IMPORTANT: some adjustment on R1 value is necessary to make the output follow the exact value
                                                        //IMPORTANT: The sensor used on the real motor is relative, so it is necessary to subtract the ambient pressure from the model.
printf("SensorsPt3=%f\tVout=%f\n", Sensors.Pt3[0], keyValueFloat);

    sendUAVCANKeyValueMsg(node0, "_o0", keyValueFloat);
    //sendUAVCANKeyValueMsg(node0, "_p3", keyValueFloat);
    //sendUAVCANKeyValueMsg(node1, "_p3", keyValueFloat);
    usleep(1000);

    keyValueFloat = (float) Sensors.Tt4[0];
//printf("EngOutput.Tt4 = %f\n", EngOutput.Tt4);
    sendUAVCANKeyValueMsg(node0, "_t4", keyValueFloat);	//sends the same value for 3 thermocouples, then FADEC calculates the average temperature
    //sendUAVCANKeyValueMsg(node1, "_t4", keyValueFloat);
    usleep(1000);

    /* Sends Vibration value to UAVCAN net*/
   //keyValueFloat = (float) Sensors.Vibration[0] * 0.1;  //Vibration Range: 0~50mm/s converted to 0~5V
    keyValueFloat = ((Sensors.Vibration[0] * (4.0/50.0) + 1.0) * ((620.0+250.0)/250.0) ) / 2;     //conversion from mm/s to Volts: Sensor range: 0~50mm/s = 1~5 V.
                                                                //When vibration is 0, the voltage output must be 1V to simulate the 4mA sensor output. When sensor is at max range value, the output must be 5V, simulating 20mA.
                                                                //There is a voltage divider in the input of FADEC, with R1 = 620Ohm and R2 = 250Ohm. Also, the output of analog module is configured to 0~10V, but the input command is still 5V, so the value sent to the module must be divided by 2.
                                                                //So the conversion is: ( (Vib * (4/MaxRangeValue) + 1) * VoltDivider ) / 2 = ( (Vib * (4/50) + 1) * ((620+250)/250) ) / 2 - IMPORTANT: some adjustment on R1 value is necessary to make the output follow the exact value

printf("SensorsVib=%f\t\tVout=%f\n", Sensors.Vibration[0], keyValueFloat);
    sendUAVCANKeyValueMsg(node0, "_o1", keyValueFloat);
   usleep(1000);

   keyValueFloat = (float) Sensors.Tt4[1];
   sendUAVCANKeyValueMsg(node0, "_t3", keyValueFloat);
   usleep(1000);

   //keyValueFloat = ((((float) Sensors.PFuel[0]) * 1e-5) * 0.05);// + 1;	//Converts 0~100,000,000Pa to 0~100bar, and then 0~100bar to 0~5V
   keyValueFloat = ((Sensors.PFuel[0] * (4.0/16000000.0) + 1.0) * ((620.0+250.0)/250.0)) / 2;   //conversion from Pa to Volts: Sensor range: 0~160bar = 0~16000000 Pa = 1~5 V.
                                                        //When pressure is 0, the voltage output must be 1V to simulate the 4mA sensor output. When sensor is at max range value, the output must be 5V, simulating 20mA.
                                                        //There is a voltage divider in the input of FADEC, with R1 = 620Ohm and R2 = 250Ohm. Also, the output of analog module is configured to 0~10V, but the input command is still 5V, so the value sent to the module must be divided by 2.
                                                        //So the conversion is: ( (PFuel * (4/MaxRangeValue) + 1) * VoltDivider ) / 2 = ( (PFuel * (4/16000000) + 1) * ((620+250)/250) ) / 2 - IMPORTANT: some adjustment on R1 value is necessary to make the output follow the exact value
                                                        //
printf("SensorsPFuel=%f\tVout=%f\n", Sensors.PFuel[0], keyValueFloat);

   sendUAVCANKeyValueMsg(node0, "_o2", keyValueFloat);
   usleep(1000);

   keyValueFloat = (float) Sensors.Tt4[2];
   sendUAVCANKeyValueMsg(node0, "_t2", keyValueFloat);
   usleep(1000);

    /* Sends POil value to UAVCAN net in pascal*/
   //keyValueFloat = (float) ((float) EngOutput.POil - (float) P0) * 1e-5;
   //keyValueFloat = (float) ((float) Sensors.POil[0] - (float) P0) * 1e-5;

   keyValueFloat = ((Sensors.POil[0] * (4.0/1000000.0) + 1) * ((620.0+250.0)/250.0)) / 2;   //conversion from Pa to Volts: Sensor range: 0~10bar = 0~1000000 Pa = 1~5 V.
                                                                                           //When pressure is 0, the voltage output must be 1V to simulate the 4mA sensor output. When sensor is at max range value, the output must be 5V, simulating 20mA.
                                                                                           //There is a voltage divider in the input of FADEC, with R1 = 620Ohm and R2 = 250Ohm. Also, the output of analog module is configured to 0~10V, but the input command is still 5V, so the value sent to the module must be divided by 2.
                                                                                           //So the conversion is: (POil * (4/MaxRangeValue) + 1) * VoltDivider = (POil * (4/1000000) + 1) * ((620+250)/250) - IMPORTANT: some adjustment on R1 value is necessary to make the output follow the exact value
 printf("SensorsPOil=%f\tVout=%f\n\n", Sensors.POil[0], keyValueFloat);                                                                                            //IMPORTANT: The sensor used on the real motor is relative, so it is necessary to subtract the ambient pressure from the model.
//   //keyValueFloat = Sensors.POil[0] / 100000.0;   //conversion to bar
//   keyValueFloat = 200000.0 / 100000.0;   //conversion to bar

//   keyValueFloat = (keyValueFloat / 2.5) + 1;                  //converts from 0~10bar to 0~4V, then adds +1V to simulate the 4mA.
//   //printf("bar2V=%f\t", keyValueFloat);
//   keyValueFloat =( keyValueFloat * ((600.0+250.0)/250.0) );   //take into account the voltage divider present on FADEC analog input
//   //printf("V2voltDiv=%f\t", keyValueFloat);
//   keyValueFloat = keyValueFloat/2;                            //the calculation is done taking 0~5V range, and the analog output board receives the command in 0~5V range,
//                                                               //but the analog output is configured to 0~10V to the same 0~5V range, i.e. it doubles the input command, so it is necesary to divide the command by 2.
//printf("Sensors.POil[0]=%f\t", Sensors.POil[0]);
//printf("POil_volts=%f\n", keyValueFloat);
   sendUAVCANKeyValueMsg(node0, "_o3", keyValueFloat);
   //sendUAVCANKeyValueMsg(node0, "_po", keyValueFloat);
   //sendUAVCANKeyValueMsg(node1, "_po", keyValueFloat);
   usleep(1000);


    //keyValueFloat = (float) Tt2;
    //keyValueFloat = (float) EngOutput.Ts2;
    keyValueFloat = (float) Sensors.Ts2[0];
    sendUAVCANKeyValueMsg(node0, "_t1", keyValueFloat);
    usleep(1000);

     /* Sends Tt2 value to UAVCAN net in Kelvin*/
    //keyValueFloat = (float) Tt2;
    //sendUAVCANKeyValueMsg(node, CAN0, "_t2", keyValueFloat);
    //usleep(1000);
     /* Sends Tt2 value to UAVCAN net in Kelvin*/
    keyValueFloat = (float) EngOutput.Tt2;
    sendUAVCANKeyValueMsg(node0, "tt2", keyValueFloat);	//sends Tt2 temperature to FADEC via CAN instead of via thermocouple simulator
    //sendUAVCANKeyValueMsg(node1, "tt2", keyValueFloat);	//sends Tt2 temperature to FADEC via CAN instead of via thermocouple simulator
    usleep(1000);

     /* Sends Pt2 value to UAVCAN net in pascal*/
//    keyValueFloat = (float) ((float) EngOutput.Pt2 - (float) P0) * 1e-5;
//    sendUAVCANKeyValueMsg(node0, "_p2", keyValueFloat);
//    //sendUAVCANKeyValueMsg(node1, "_p2", keyValueFloat);
//    usleep(1000);



    //keyValueFloat = (float) EngOutput.RPM;
    keyValueFloat = (float) Sensors.RPM[0];
    sendUAVCANKeyValueMsg(node0, "_ra", keyValueFloat);
    //sendUAVCANKeyValueMsg(node1, "_ra", keyValueFloat);
    usleep(1000);

    //keyValueFloat = (float) EngOutput.RPM;
    keyValueFloat = (float) Sensors.RPM[1];
    sendUAVCANKeyValueMsg(node0, "_rb", keyValueFloat);
    //sendUAVCANKeyValueMsg(node1, "_rb", keyValueFloat);
    usleep(1000);


    keyValueFloat = thermoSim_coldJunction;	//sends the cold junction from FADEC to thermocouple simulation board
    sendUAVCANKeyValueMsg(node0, "_cj", keyValueFloat);
    usleep(1000);
             /* Sends Ambient Pressure*/
//            keyValueFloat = (float) 1;
 //           sendUAVCANKeyValueMsg(node, CAN0,"_pa", keyValueFloat);
//usleep(1000);
             /* Sends Ambient Temperature value to UAVCAN net in Celcius degrees*/
//            keyValueFloat = (float) 2;
//            sendUAVCANKeyValueMsg(node, CAN0,"_ta", keyValueFloat);
//usleep(1000);
             /* Sends Tt4-1 value to UAVCAN net in Celcius degrees*/
//            keyValueFloat = (float) SkipStart;
//            sendUAVCANKeyValueMsg(node, CAN0, "_sk", keyValueFloat);
//usleep(1000);
             /* Sends Tt4-1 value to UAVCAN net in Celcius degrees*/
//            keyValueFloat = (float) Wf0;
//            sendUAVCANKeyValueMsg(node, CAN0,"_w0", keyValueFloat);
//usleep(1000);
             /* Sends Tt4-1 value to UAVCAN net in Celcius degrees*/
//            keyValueFloat = (float) bit_start;
//            sendUAVCANKeyValueMsg(node, CAN0,"_au", keyValueFloat);
//usleep(1000);

    //keyValueFloat = (float) ContOutput.FiltRef;		//min ref modelo
    //sendUAVCANKeyValueMsg(node, CAN0,"_mr", keyValueFloat);
    //usleep(1000);

    keyValueFloat = (float) fValue;
    sendUAVCANKeyValueMsg(node0,"_fv", keyValueFloat);
    //sendUAVCANKeyValueMsg(node1,"_fv", keyValueFloat);

    keyValueFloat = (float) model_d1_toInt;
    //sendUAVCANKeyValueMsg(node1, "_d1", keyValueFloat);		//sends digital inputs to Supervisorio
//std::chrono::steady_clock::time_point end_tempo4 = std::chrono::steady_clock::now();
//tempo4 = std::chrono::duration_cast<std::chrono::microseconds>(end_tempo4 - begin_tempo4).count();
//std::cout << "t3:" << tempo3 << std::endl;

//printf("RPMA=%0.1f\n", Sensors.RPM[0]);
// printf("model_oilflow=%f\tOPRPM=%f\tPOil=%f\n", model_oilFlow, OPRPM, Sensors.POil[0]);
//    printf("Pt3=%f\tVib=%f\tPFuel=%f\tPOil=%f\n", (Sensors.Pt3[0] - Ambient.Ps), Sensors.Vibration[0], Sensors.PFuel[0], Sensors.POil[0]);


}

