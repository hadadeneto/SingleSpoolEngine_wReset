/************************************************************************************************
 * IMPORTANT CHANGE ON THIS VERSION:
 * - Before:
 *  - CAN0 was used to internal communication between FADEC's motherboard and sensor boards (analog, digital and thermocouple)
 *  - CAN1 was used to communicate with supervisory
 * - Now:
 *  - CAN0 is used to internal communication between FADEC's motherboard and sensor boards (analog, digital and thermocouple) AND supervisory, using UAVCAN messages
 *  - CAN1 is used to communicate with ATDPOC, using SIATT's protocol. Only ATDPOC messages will be sent and received on this channel.
 * ***********************************************************************************************/
#define VERSAO_DO_DIA   "FADEC Versao do dia 18/07/2024 DEV - UAVCAN e Code Generator para a TJ-200"

#include <iostream>
#include <cstdlib>
#include <unistd.h>

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
#include <uavcan_linux/uavcan_linux.hpp>                // For NodePtr
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
/**************************************************************************************/

/* INCLUDES REFERENT TO THE FADEC */
extern "C"
{

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
//#include "getTJ300AR.h"              /* File containing all get functions for TJ300AR */
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
#include "TJ300AR/FADEC_Constants_H/ConstantsTJ300AR.h"
#include "TJ300AR/FADEC_get_H/getTJ300ARFADECContConst.h"
#include "TJ300AR/FADEC_get_H/getTJ300ARFADECMtx.h"       /* TJ300AR Engine Constants */
#include "TJ300AR/FADEC_get_H/getTJ300ARFADECSizeConst.h"

/******** COPYFROM END: FADEC_INCLUDES *********/

}

/******************************************************************************************/

/*-------------------------*/
/* COMMUNICATION VARIABLES */
/*-------------------------*/

/********************************************************************************************/
/*
 *                  UAVCAN COMMUNICATION DEFINES AND VARIABLES
 */
/********************************************************************************************/

//declaração das variáveis das leituras recebidas via UAVCAN
float   i10, i11, i12, i13,                         // Analog Inputs
        o1a, o1b, o1c, o1d,                         // Loopback from Analog Outputs: 1=a, 2=b, 3=c, 4=d
        t10, t11, t12, t13, t14, t15, t16, t17,     // Thermocouple Temperature Value
        t1a, t1b, t1c, t1d, t1e, t1f, t1g, t1h,     // Thermocouple Cold Juntion Value: 1=a, 2=b, ... , 8=h
        t1A, t1B, t1C, t1D, t1E, t1F, t1G, t1H,     // Thermocouple Status bits: 1=A, 2=B, ... , 8=H
        d11_float, d21_float,                       // entradas digitais no formato float, posterior convers�o para int
        r11, r12,                                   // valor do RPM-A e RPM-B
        //eRPMFuel, eRPMOil,                          // Electric RPM da Fuel Pump e Oil Pump. Converter para RPM mecãnico posteriormente com: RPM = eRPM / (poles/2)
        RPMFuelPump, RPMOilPump,                    // Mechanical RPM of Oil and Fuel Pump, calculated on Analog Board: RPM = eRPM / (poles/2)
        model_d1, model_mf,							// variaveis do modelo
        dT;				//temperatura ambiente, sendo a variação dT em relação a 288.15
float	pot_percent = 0;					//porcentagem do potênciometro (manete)
float   Tt2_fromModel = 288.15;
float   Ts2_fromModel = 293;
//float 	reference = 0.45;
float 	authorize_float, skipStart_float,	//receives the initial values and commands on float format, for later conversion to int
        initialAltitude_float, initialdT_float, engine_float, initialMachNumber_float, initialReference_float, simMod_float,
        engineCommand_fromSupervisorio;
//float oilRPM_ref = 0;
uint8_t simMod = 3;

enum CAN1_protocol
{
    OBC_SIATT,
    UAVCAN,
    CANopen
};
enum CAN1_protocol can1_currentProtocol = OBC_SIATT;   //informs which protocol is being used on CAN1 bus.

uint8_t plcOutputs = 0;

unsigned int model_d1_toInt = 0;	//converts the float number corresponding to digital inputs to integer


unsigned int upTime_ms =  0;	//the upTime_ms variable measures the time since the system has been started in miliseconds
                                //and sends on "upd" keyValue message.
unsigned long lastUpdateTime_ms =  0;	//holds the last time that the update cycle has been executed.
unsigned long syncTime_ms = 0;   //the syncTime_ms is used on HIL Sync Mode. Represents the sync time sent by FADEC, in miliseconds.
                                //syncTime_ms is also used to confirm that no sync message has been lost.
unsigned long lastSyncTime_ms = 0;   //stores the last time in miliseconds that the model was synced on HIL Sync Mode.


unsigned int lastTime_rcvOBCmsg_ms = 0;    //holds the last time in milliseconds that the OBC_FADEC_THRUST_MACH_ALT_CANID has been received from OBC

uavcan::MonotonicTime monotonicTimer_initialValue;

EngineFaults faultsFromSuperv;
keys_t keys_fromSupervisorio;

std::ofstream fadecSensorsDataFile;      //file used to save all sensors data on FADEC. The CSV file format is used, with first line being the columns title and comma separator.
std::ifstream testFileExistence;        // used on test if file already exists. If file exists, create a new file with a sequencial number suffix.
std::string filename = "/home/root/Desktop/FADECTelemetry/fadecRegister.csv";     //initial file name
int flag_writeSensorsDataFile = 0;      //flag used to update the fadecSensorsDataFile
//int flag_syncFile = 0;
unsigned int last_saveTelemetryFile_ms = 0;     //holds the last time the telemetry was saved.

float valorManete = 0;  // Valor recebido da Manete CAN. Range: 0 a 100%, com opção de ser linear ou exponencial.

int pwm_0a100_TJ200 = 0;
int rcpwm_startMotor_TJ200 = 0;
int flag_tj200_selected = 0;
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

struct timespec initialTime;                //initial monotonic timer value, for time elapsed calculation
struct timespec actualTime;                 //actual monotonic timer value, for time elapsed calculation
unsigned long upTime_sendATDPOCmsg_ms = 0;  //time elapsed in millisecond from the start or last reset
unsigned long last_sendATDPOCmsg_ms = 0;    //the last time the function has been executed

union estimatedAlt_union
{
    float value_in_float;
    uint8_t value_in_bytes[4];
};

union net_thrust_cmd_union
{
    uint16_t value_in_uint16;
    uint8_t value_in_bytes[2];
};

uint8_t machNumber_uint8;

int engineCommandFromATDPOC;

// FADEC Status
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
};

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

//FADEC Warning Codes
union fadec_tlm_warning_codes
{
//    struct Warnings
//    {

//        /* SENSOR WARNINGS */

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
//    } Warnings;

    EngineFaults Warnings;

    uint8_t valueInBytes[8];

    uint64_t valueUint64;
};

// Digital Inputs and Outputs, including PLC outputs, and Cold Junction Average Temperature
union fadec_dig_inputs_outputs_coldjunction
{
    struct
    {
        uint16_t dig_inputs;
        uint16_t dig_outputs;
        uint16_t plc_outputs;
        uint16_t coldjunction_avg;
    } value;

    uint8_t valueInBytes[8];
};

fadec_dig_inputs_outputs_coldjunction digInOut_coldjunction;

union fadec_rpma_rpmb_rpmoil_rpmfuel
{
    struct
    {
        int16_t rpmA;
        int16_t rpmB;
        int16_t rpmOil;
        int16_t rpmFuel;
    } value;

    uint8_t valueInBytes[8];
};

//FADEC Analog Inputs
union fadec_an_inputs
{
    struct
    {
        uint16_t i10;
        uint16_t i11;
        uint16_t i12;
        uint16_t i13;
    } value;

    uint8_t valueInBytes[8];
};

//FADEC Analog Outputs
union fadec_an_outputs
{
    struct
    {
        uint16_t o10;
        uint16_t o11;
        uint16_t o12;
        uint16_t o13;
    } value;

    uint8_t valueInBytes[8];
};

//FADEC Thermocouples 0 to 3
union fadec_thermocouple_0_3
{
    struct
    {
        uint16_t t10;
        uint16_t t11;
        uint16_t t12;
        uint16_t t13;

    } value;

    uint8_t valueInBytes[8];
};

//FADEC Thermocouples 4 to 7
union fadec_thermocouple_4_7
{
    struct
    {
        uint16_t t14;
        uint16_t t15;
        uint16_t t16;
        uint16_t t17;

    } value;

    uint8_t valueInBytes[8];
};

//FADEC Debug Values. Two float values sent to Supervisorio. Can assume any value.
union fadec_debug_float_values
{
    struct
    {
        float value1;
        float value2;
    } value;

    uint8_t valueInBytes[8];
};

//Booster Separation Message, por Pt3 enable
union booster_sep
{
    struct
    {
        uint8_t leftBoosterSwitch;
        uint8_t rightBoosterSwitch;
    } value;

    uint16_t valueInUint16;
};


//HIL skip start, authorize command and Wf0
union initial_wf
{
    uint16_t valueInUint16;
    uint8_t valueInBytes[2];
}; //as used on fadec_status message, the fuel flow is multiplied by 10000, so the range is 0 to 2000

union skipStart_authorize_commands
{
    uint8_t valueInByte;

    struct skipStart_authorize_commands_values
    {
        uint8_t skipStart : 1;
        uint8_t authorize : 1;
        uint8_t reserved : 6;
    }value;
};

//Supervisorio Reset Command
union init_estimatedAlt_union
{
    uint16_t value_in_uint16;
    uint8_t value_in_bytes[2];
};

union init_net_thrust_cmd_union
{
    uint16_t value_in_uint16;
    uint8_t value_in_bytes[2];
};


union reset_mode
{
    struct
    {
        uint8_t starting_mode : 2;  //Mode: 0 = Auto Start; 1 = Manual Start.
        uint8_t engine : 2;
        uint8_t lever_mode : 2;
        uint8_t simulation_mode : 2;
    } value;

    uint8_t valueInByte;
};

uint8_t init_machNumber_uint8;     //mach number on OBD to FADEC Messages is on percent (0% ~ 100%), so multiplies the 0~1 by 100
uint8_t init_dT = 0;

//Ts2 From Model
union model_ts2
{
    struct
    {
        uint16_t Ts2;
    } value;

    uint8_t valueInBytes[2];
};

//Digital Inputs Command from Supervisorio. This byte is used in an OR logic with physical keys connected on FADEC's digital input.
union fadec_dig_inputs_supervisorio
{
    struct
    {
        uint8_t igniter   	   : 1;
        uint8_t shutoff 	   : 1;
        uint8_t scaveng        : 1;
        uint8_t oil_pump 	   : 1;
        uint8_t acdrive 	   : 1;
        uint8_t reserved       : 3;
    } value;
    uint8_t valueUint8;
    uint8_t valueInBytes[1];
};

//Oil RPM reference from Supervisório. Used to obtain the model of bearing temperature.
union oilRPM_reference_union
{
    uint16_t value_in_uint16;
    uint8_t value_in_bytes[2];
};

//TJ-200 digital outputs
union fadec_tj200_dig_inputs_supervisorio
{
    struct
    {
        uint8_t vela                : 1;
        uint8_t valvula_vela        : 1;
        uint8_t valvula_combustivel : 1;
        uint8_t reserved            : 5;
    } value;
    uint8_t valueUint8;
    uint8_t valueInBytes[1];
};

fadec_tj200_dig_inputs_supervisorio digInputs_TJ200_fromSupervisorio;


// defines used on ATDPOC
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

#define UPDATE_TIMERATE_MS                  200
#define OBC_FADEC_HEARTBEAT_TIMEOUT         1000        //after 1000ms not receiving the OBC_FADEC_THRUST_MACH_ALT_CANID message from OBC, FADEC assumes the communication is lost and sets CANFault.DetFaults.CAN_x_Fault bit.

//These IDs are only for use with Supervisorio, DO NOT USE ON OBC NET!
#define ENABLE_FADEC_SUPERVISORY_MESSAGES   1//0                   //enables the sensors messages above to be sent from FADEC to Supervisorio. DO NOT USE ON OBC NET!

#define FADEC_SKIPSTART_AUTHORIZE_COMMAND   0xF321100
#define MODEL_TS2_SENSOR                    0xF321101
#define FADEC_DIG_INPUTS_OUTPUTS_CJ         0xF321102
#define FADEC_RPMA_RPMB_RPMOIL_RPMFUEL      0xF321103
#define FADEC_AN_INPUTS                     0xF321104
#define FADEC_AN_OUTPUTS                    0xF321105
#define FADEC_THERMOCOUPLE_0_3              0xF321106
#define FADEC_THERMOCOUPLE_4_7              0xF321107
#define FADEC_SIM_FAILURE_CODES_CANID       0xF321008
#define FADEC_DIG_OUTPUTS_SUPERVISORIO      0xF321009
//#define FADEC_RESET_COMMAND                 0xF321010
#define FADEC_OIL_RPM_REFERENCE             0xF321011
#define FADEC_DEBUG_FLOAT_VALUES            0xF321012
#define FADEC_DEBUG_FLOAT_VALUES_2          0xF321013
#define FADEC_CAN1_CHOOSE_PROTOCOL          0xF321017       //new message, to choose CAN1 working protocol, e.g. OBC (SIATT), UAVCAN, CANopen, etc, sent with reset command


#define FADEC_OBC_TIMERATE_MS               200
#define FADEC_TLM_2_CANMSG_PERIOD_MS        1000
#define FADEC_SAVE_TELEMETRY_FILE_PERIOD_MS 1000


//Added messages to TJ200
#define FADEC_TJ200_DIG_OUTPUTS_SUPERVISORIO    0xF321014
#define FADEC_TJ200_PWM_0TO100_OUTPUT           0xF321015   //PWM 0 to 100% used on fuel pump
#define FADEC_TJ200_PWM_START_MOTOR             0xF321016   //RCPWM used on starter motor


#define CAN_29BIT_ID_MASK                   0x1FFFFFFF
//

/********************************************************************************************/
/*
 *                 END OF OBC COMMUNICATION DEFINES AND VARIABLES
 */
/********************************************************************************************/

/* -------------------------------------------------- */

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
    int Fn_Elem = TJ300AR_FN_ELEM;                      /* Number of net thrust breakpoint elements */
    int MN_Elem = TJ300AR_MN_ELEM;                      /* Number of Mach number breakpoint elements */

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

    // floating AltLinVec[TJ300AR_ALT_ELEM];                      /* Altitude breakpoints */
    // floating AMtx[TJ300AR_MN_ELEM * TJ300AR_FN_ELEM];           /* Model - A matrix */
    // floating ASVec[TJ300AR_AS_ELEM];                           /* Controller - Asceleration schedule (ASVec) break points */
    // floating BMtx[TJ300AR_MN_ELEM * TJ300AR_FN_ELEM];           /* Model - B matrix */
    // floating DeltaMtx[TJ300AR_ALT_ELEM * TJ300AR_MN_ELEM];      /* Controller - Delta matrix */
    // floating DeltaMtx1D[TJ300AR_MN_ELEM];                      /* Auxiliar matrix - Delta */
    // floating DeltaMtx1DH[TJ300AR_MN_ELEM];                     /* Auxiliar matrix - Delta */
    // floating DeltaMtx2D[TJ300AR_ALT_ELEM * TJ300AR_MN_ELEM];    /* Auxiliar matrix - Delta */
    // floating DeltaMtx2DH[TJ300AR_ALT_ELEM * TJ300AR_MN_ELEM];   /* Auxiliar matrix - Delta */
    // floating DSVec[TJ300AR_AS_ELEM];                           /* Controller - Deceleration schedule (DSVec) break points */
    // floating FNcMaxContMtx[TJ300AR_MN_ELEM];                   /* Controller - Maximum corrected net thrust values */
    // floating FNperContMtx[TJ300AR_TOTAL_ELEM];                 /* Controller - net thrust percentual values matrix */
    // floating MapHPC1D[TJ300AR_FAN_PR];                         /* Auxiliar matrix - HPC map */
    // floating MapHPC1DH[TJ300AR_FAN_PR];                        /* Auxiliar matrix - HPC map */
    // floating MapHPC2D[TJ300AR_FAN_NC * TJ300AR_FAN_PR];         /* Auxiliar matrix - HPC map */
    // floating MapHPC2DH[TJ300AR_FAN_NC * TJ300AR_FAN_PR];        /* Auxiliar matrix - HPC map */
    // floating MNLinVec[TJ300AR_MN_ELEM];                        /* Mach number breakpoints */
    // floating Mtx1D[TJ300AR_FN_ELEM];                           /* Auxiliar matrix */
    // floating Mtx1DH[TJ300AR_FN_ELEM];                          /* Auxiliar matrix */
    // floating Mtx2D[TJ300AR_MN_ELEM * TJ300AR_FN_ELEM];          /* Auxiliar matrix */
    // floating Mtx2DH[TJ300AR_MN_ELEM * TJ300AR_FN_ELEM];         /* Auxiliar matrix */
    // floating N_KiMtx[TJ300AR_TOTAL_ELEM];                      /* Controller - Ki matrix of N control law */
    // floating N_KpMtx[TJ300AR_TOTAL_ELEM];                      /* Controller - Kp matrix of N control law */
    // floating NcFANContMtx[TJ300AR_TOTAL_ELEM];                 /* Controller - Fan Nc breakpoints */
    // floating NcHPCMapMtx[TJ300AR_FAN_NC];                      /* Model - Nc break points matrix - HPC map */
    // floating NcVec[TJ300AR_AS_ELEM];                           /* Controller - Nc schedule (for ASVec and DSVec) break points */
    // floating PRHPCMapMtx[TJ300AR_FAN_NC * TJ300AR_FAN_PR];      /* Model - PR break points matrix - HPC map */
    // floating Pt3DMtx[TJ300AR_MN_ELEM * TJ300AR_FN_ELEM];        /* Model - Pt3D matrix */
    // floating Pt3Mtx[TJ300AR_MN_ELEM * TJ300AR_FN_ELEM];         /* Model - Pt3 matrix */
    // floating Pt5DMtx[TJ300AR_MN_ELEM * TJ300AR_FN_ELEM];        /* Model - Pt5D matrix */
    // floating Pt5Mtx[TJ300AR_MN_ELEM * TJ300AR_FN_ELEM];         /* Model - Pt5 matrix */
    // floating Ts0Mtx[TJ300AR_ALT_ELEM];                         /* Controller and Model - Ts0 break points  */
    // floating Ts0Mtx1D[TJ300AR_ALT_ELEM];                       /* Auxiliar matrix - Ts0 */
    // floating Ts0Mtx1DH[TJ300AR_ALT_ELEM];                      /* Auxiliar matrix - Ts0 */
    // floating Ts0Mtx2D[TJ300AR_FN_ELEM];                        /* Auxiliar matrix - Ts0 */
    // floating Ts0Mtx2DH[TJ300AR_FN_ELEM];                       /* Auxiliar matrix - Ts0 */
    // floating Tt4DMtx[TJ300AR_MN_ELEM * TJ300AR_FN_ELEM];        /* Model - Tt4D matrix */
    // floating Tt4Mtx[TJ300AR_MN_ELEM * TJ300AR_FN_ELEM];         /* Model - Tt4 matrix */
    // floating Tt5DMtx[TJ300AR_MN_ELEM * TJ300AR_FN_ELEM];        /* Model - Tt5D matrix */
    // floating Tt5Mtx[TJ300AR_MN_ELEM * TJ300AR_FN_ELEM];         /* Model - Tt5 matrix */
    // floating WcHPCMapMtx[TJ300AR_FAN_NC * TJ300AR_FAN_PR];      /* Model - Wc break points matrix - HPC map */
    // floating WfMtx[TJ300AR_MN_ELEM * TJ300AR_FN_ELEM];          /* Model - Wf matrix */

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

/* COMMONLY USED VARIABLES */

floating FNIdle = 350;//1800; /* VARIAVEL PARA TESTE - NA TJ200, MODIFICADO PARA 350 N */

/* Thermocouple value when opened */
floating TCOpen = 0;//ContConst.TCOpen;
/******** COMMENT START *********/
/////* Sampling Time */
////floating Ts = 0.001 * TICK;
/******** COMMENT END *********/
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


//void sendUAVCANKeyValueMsg(Node& node, char keyID[3], float value);
void sendUAVCANKeyValueMsg(uavcan_linux::NodePtr& node, char keyID[3], float value);

//void ControlUpdate(Node& node0, Node& node1);     //now only CAN0 will be used to send UAVCAN messages
//void ControlUpdate(Node& node0, int can_atd_poc);
void ControlUpdate(uavcan_linux::NodePtr& node0, uavcan_linux::NodePtr& node1, int can_atd_poc);

//void reset_command_ATDPOC(int can_atd_poc);    // Sends the reset command to CAN1 (ATPOC bus)


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

            fadecSensorsDataFile << "Node " << int(event.node_id.get()) << " has changed status from "          //writes also in fadec telemetry file
                                << modeToString(event.old_status) << "/" << healthToString(event.old_status)
                                << " to "
                                << modeToString(event.status) << "/" << healthToString(event.status)
                                << std::endl;

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
//struct sigaction sa;
//struct itimerval timer;
struct timeval tvCANATDPOC;	//timer used for timeout of CAN message reception
//struct timeval tvCAN1;

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
//pthread_t thread_ATDPOC_CANmsg_send_rcv;          //thread declaration
//pthread_t thread_saveFile;          //thread declaration

//void *thread_ATDPOC_CANmsg_send_rcv_fcn(void *ptr);
//void *thread_saveFile_fcn(void *ptr);
//void *thread_EngineModelUpdate_fcn(void *ptr);

pthread_t thread_ATDPOC_CANmsg_send_rcv;          //thread declaration
pthread_t thread_telemetry_updateFile;          //thread declaration
pthread_t thread_telemetry_syncFile;          //thread declaration

void *thread_ATDPOC_CANmsg_send_rcv_fcn(void *ptr);
void *thread_telemetry_updateFile_fcn(void *ptr);
void *thread_telemetry_syncFile_fcn(void *ptr);

void *thread_ATDPOC_CANmsg_send_rcv_fcn(void *ptr)
{
    int cansock = (long) ptr;   //can socket channel being used inside this function (CAN1).

    struct can_frame frame_read;
    struct can_frame frame_send;

    clock_gettime(CLOCK_MONOTONIC, &initialTime);

    while(1)    //never exits this thread
    {
        clock_gettime(CLOCK_MONOTONIC, &actualTime);

        //converts seconds and nanoseconds to milliseconds, then calculates the difference of actual and initial time.
        upTime_sendATDPOCmsg_ms = ( (actualTime.tv_sec*1000) + (actualTime.tv_nsec/1000000) ) - ( (initialTime.tv_sec*1000) + (initialTime.tv_nsec/1000000) );

        if(last_sendATDPOCmsg_ms > upTime_sendATDPOCmsg_ms)     //if the last time the message has been sent is bigger than the actual time, it means that the node was resetted.
            last_sendATDPOCmsg_ms = 0;      //so, sets the last time to zero.

//std::cout << "upTime:" << upTime_sendATDPOCmsg_ms << std::endl << std::endl;


        /********************************************************************************************/
        /*
         *                                 OBC MESSAGES RECEPTION
         */
        /********************************************************************************************/

        if ( upTime_sendATDPOCmsg_ms >= (last_sendATDPOCmsg_ms + FADEC_OBC_TIMERATE_MS - 20) )  //the reception of CAN messages works until 20ms before the send message sequence,
                                                                                                //in order to finish any task during this interval of 20ms.
        {
            if(recv(cansock, &frame_read, sizeof(struct can_frame), MSG_DONTWAIT) > 0)  //using recv() instead of read(), because recv() has MSG_DONTWAIT flag, so the function does not block
            {

                switch (frame_read.can_id & CAN_29BIT_ID_MASK)
                {
                    case OBC_FADEC_THRUST_MACH_ALT_CANID:
                        net_thrust_cmd_union net_thrust_cmd;
                        estimatedAlt_union estimatedAlt;

                        net_thrust_cmd.value_in_bytes[0] = frame_read.data[0];
                        net_thrust_cmd.value_in_bytes[1] = frame_read.data[1];
                        machNumber_uint8 = frame_read.data[2];
                        estimatedAlt.value_in_bytes[0] = frame_read.data[3];
                        estimatedAlt.value_in_bytes[1] = frame_read.data[4];
                        estimatedAlt.value_in_bytes[2] = frame_read.data[5];
                        estimatedAlt.value_in_bytes[3] = frame_read.data[6];

                        RefCAN = net_thrust_cmd.value_in_uint16;
                        if(LeverMode == 0)
                        {
                            RefCAN = (float) net_thrust_cmd.value_in_uint16 / 10000;    //if lever mode is Manual (PC), converts the 0 ~ 10000 range from slider to 0 ~ 1.
                        }
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

                    case FADEC_SKIPSTART_AUTHORIZE_COMMAND:
                        initial_wf initialWf;
                        skipStart_authorize_commands commands;

                        initialWf.valueInBytes[0] = frame_read.data[0];
                        initialWf.valueInBytes[1] = frame_read.data[1];
                        commands.valueInByte = frame_read.data[2];

            //printf("skipStart=%d, authorize=%d, wf0=%d\n", commands.value.skipStart, commands.value.authorize, initialWf.valueInUint16);

                        SkipStart = commands.value.skipStart;
                        Authorize = commands.value.authorize;
                        Wf0 = (float) initialWf.valueInUint16 / 10000;  //as the range is 0 to 2000, the number is divided by 10000, and the new range is 0 to 0.2

            printf("SkipStart=%d, Authorize=%d, Wf0=%f\n\n", SkipStart, Authorize, Wf0);
                    break;


                    case FADEC_SIM_FAILURE_CODES_CANID:
                        fadec_tlm_failure_codes faultsCANmsg;
                        for(int i=0; i < frame_read.can_dlc; i++)
                        {
                            faultsCANmsg.valueInBytes[i] = frame_read.data[i];
                        }

                        faultsFromSuperv.FaultBits = faultsCANmsg.valueUint64;
                        //SoftSimFaults.FaultBits = faultsFromSuperv.FaultBits;
                        SoftSimFaults.SensFaults.Ts2_0_SCV = faultsFromSuperv.Faults.Ts2_0_SCV;
                        SoftSimFaults.SensFaults.Ts2_0_SCG = faultsFromSuperv.Faults.Ts2_0_SCG;
                        SoftSimFaults.SensFaults.Ts2_0_Open = faultsFromSuperv.Faults.Ts2_0_Open;

                        SoftSimFaults.SensFaults.Ts2_1_SCV = faultsFromSuperv.Faults.Ts2_1_SCV;
                        SoftSimFaults.SensFaults.Ts2_1_SCG = faultsFromSuperv.Faults.Ts2_1_SCG;
                        SoftSimFaults.SensFaults.Ts2_1_Open = faultsFromSuperv.Faults.Ts2_1_Open;

                        SoftSimFaults.SensFaults.TB_0_Open = faultsFromSuperv.Faults.TB_0_Open;
                        SoftSimFaults.SensFaults.TB_1_Open = faultsFromSuperv.Faults.TB_1_Open;
                        SoftSimFaults.SensFaults.TB_2_Open = faultsFromSuperv.Faults.TB_2_Open;

                        SoftSimFaults.SensFaults.Pt3_0_Short = faultsFromSuperv.Faults.Pt3_0_Short;
                        SoftSimFaults.SensFaults.Pt3_0_Open = faultsFromSuperv.Faults.Pt3_0_Open;

                        SoftSimFaults.SensFaults.Tt4_0_SCV = faultsFromSuperv.Faults.Tt4_0_SCV;
                        SoftSimFaults.SensFaults.Tt4_0_SCG = faultsFromSuperv.Faults.Tt4_0_SCG;
                        SoftSimFaults.SensFaults.Tt4_0_Open = faultsFromSuperv.Faults.Tt4_0_Open;

                        SoftSimFaults.SensFaults.Tt4_1_SCV = faultsFromSuperv.Faults.Tt4_1_SCV;
                        SoftSimFaults.SensFaults.Tt4_1_SCG = faultsFromSuperv.Faults.Tt4_1_SCG;
                        SoftSimFaults.SensFaults.Tt4_1_Open = faultsFromSuperv.Faults.Tt4_1_Open;

                        SoftSimFaults.SensFaults.Tt4_2_SCV = faultsFromSuperv.Faults.Tt4_2_SCV;
                        SoftSimFaults.SensFaults.Tt4_2_SCG = faultsFromSuperv.Faults.Tt4_2_SCG;
                        SoftSimFaults.SensFaults.Tt4_2_Open = faultsFromSuperv.Faults.Tt4_2_Open;

                        SoftSimFaults.SensFaults.RPM_0_Short = faultsFromSuperv.Faults.RPM_0_Short;
                        SoftSimFaults.SensFaults.RPM_0_Open = faultsFromSuperv.Faults.RPM_0_Open;
                        SoftSimFaults.SensFaults.RPM_0_PLoss1 = faultsFromSuperv.Faults.RPM_0_1PLoss;
                        SoftSimFaults.SensFaults.RPM_0_PLoss2 = faultsFromSuperv.Faults.RPM_0_2PLoss;

                        SoftSimFaults.SensFaults.RPM_1_Short = faultsFromSuperv.Faults.RPM_1_Short;
                        SoftSimFaults.SensFaults.RPM_1_Open = faultsFromSuperv.Faults.RPM_1_Open;
                        SoftSimFaults.SensFaults.RPM_1_PLoss1 = faultsFromSuperv.Faults.RPM_1_1PLoss;
                        SoftSimFaults.SensFaults.RPM_1_PLoss2 = faultsFromSuperv.Faults.RPM_1_2PLoss;

                        SoftSimFaults.SensFaults.POil_0_Short = faultsFromSuperv.Faults.POil_0_Short;
                        SoftSimFaults.SensFaults.POil_0_Open = faultsFromSuperv.Faults.POil_0_Open;

                        SoftSimFaults.SensFaults.PFuel_0_Short = faultsFromSuperv.Faults.PFuel_0_Short;
                        SoftSimFaults.SensFaults.PFuel_0_Open = faultsFromSuperv.Faults.PFuel_0_Open;

                        SoftSimFaults.SensFaults.Vib_0_Short = faultsFromSuperv.Faults.Vib_0_Short;
                        SoftSimFaults.SensFaults.Vib_0_Open = faultsFromSuperv.Faults.Vib_0_Open;

                        SoftSimFaults.SensFaults.TB_0_Open = faultsFromSuperv.Faults.TB_0_Open;
                        SoftSimFaults.SensFaults.TB_1_Open = faultsFromSuperv.Faults.TB_1_Open;
                        SoftSimFaults.SensFaults.TB_2_Open = faultsFromSuperv.Faults.TB_2_Open;

                    break;

                    case HILS_FADEC_RESET_CANID:
                        init_net_thrust_cmd_union init_net_thrust_cmd;
                        init_estimatedAlt_union init_estimatedAlt;
                        reset_mode resetMode;

                        init_net_thrust_cmd.value_in_bytes[0] = frame_read.data[0];
                        init_net_thrust_cmd.value_in_bytes[1] = frame_read.data[1];
                        init_machNumber_uint8 = frame_read.data[2];
                        init_estimatedAlt.value_in_bytes[0] = frame_read.data[3];
                        init_estimatedAlt.value_in_bytes[1] = frame_read.data[4];
                        init_dT = frame_read.data[5];
                        resetMode.valueInByte = frame_read.data[6];

                        //STARTING MODE
                        Mode = resetMode.value.starting_mode;
                        //ENGINE
                        engine_float = resetMode.value.engine;    //Engine: TJ1200
                        if((uint8_t) engine_float == 0)
                             flag_tj200_selected = 1;
                         else
                             flag_tj200_selected = 0;
                        //LEVER  MODE
                        LeverMode = resetMode.value.lever_mode;
                        EngUnits = 1;
                        if(LeverMode != 1)	//if Lever Mode is a signal to directly control the fuel pump (manual reference, not from control law)
                            EngUnits = 0;
                        //SIMULATION MODE
                        simMod = resetMode.value.simulation_mode;    //0 = SIL, 1 = HIL Async, 2 = HIL Sync, 3 = Test Bench

                        if((uint8_t)simMod == 3)
                        {
                            //Ts2_fromModel = 288.15 + 15; //Teste realizado 28/04/2022 15h
                            //Ts2_fromModel = 288.15 + 9; //Teste realizado 28/04/2022 15h
                            //Ts2_fromModel = 288.15 + 13; //Teste realizado 02/05/2022 14h
                            //Ts2_fromModel = 273 + 23; //Teste realizado 06/05/2022 11h
                           // Ts2_fromModel = 273 + 24; //Teste realizado 09/05/2022 15h
                            //Ts2_fromModel = 273 + 22; //Teste realizado 09/05/2022 18h30
                            //Ts2_fromModel = 273 + 20; //Teste realizado 10/05/2022 9h45
                            //Ts2_fromModel = 273 + 24; //Teste realizado 10/05/2022 14h45
                            //Ts2_fromModel = 273 + 24; //Teste realizado 12/05/2022 15h
                            Ts2_fromModel = 273 + 20; //Previsão da temperatura para sexta 20/05/2022
                        }

                        initialReference_float = init_net_thrust_cmd.value_in_uint16;
                        if(LeverMode != 1)
                            initialReference_float = initialReference_float / 10000;    //if Lever Mode is on Manual Mode, the range is 0 ~ 10000, and is converted to 0 ~ 1;
                        initialAltitude_float = init_estimatedAlt.value_in_uint16;
                        initialMachNumber_float = (float) init_machNumber_uint8 / 100;  //mach number on OBD to FADEC Messages is on percent (0% ~ 100%), so multiplies the 0~1 by 100
                        initialdT_float = init_dT - 100;    //Initial Ambient Temperature. IMPORTANT! The value is shifted by 100K, so the temperature range is from -100K to +155K
                        RefCAN = initialReference_float;
                        //FNpc = RefCAN;
                        Altitude = initialAltitude_float;
                        MN = initialMachNumber_float;

            printf("\n*************\nRESET! Mode=%d, Eng=%f, Lever=%x, simMod=%d, EngineeringUnits=%x\n", Mode, engine_float, LeverMode, simMod, EngUnits);
            printf("InitRef=%f, InitAlt=%f, InitMN=%f, InitdT=%f\n", initialReference_float, initialAltitude_float, initialMachNumber_float, initialdT_float);
            printf("\n%s\n", VERSAO_DO_DIA);

                        // Sets Reset flag to 1
                        Reset = 1;
                        // Sets time base to zero - this variable tells how long the device has been operating
                        upTime_ms = 0;
                        lastTime_rcvOBCmsg_ms = 0;
                    break;

                    case FADEC_CAN1_CHOOSE_PROTOCOL:
                        switch (frame_read.data[0])
                        {
                            case 0:    //OBC (SIATT)
                                can1_currentProtocol = OBC_SIATT;
                            break;

                            case 1:     //UAVCAN
                                can1_currentProtocol = UAVCAN;
                            break;

                            case 2:     //CANopen
                                //can1_currentProtocol = CANopen;
                                can1_currentProtocol = OBC_SIATT;   //for now, CANopen is not inmplemented, so use default value
                            break;

                            default:
                                can1_currentProtocol = OBC_SIATT;
                            break;
                        }


                    break;

                    case TLM_OBC_BOOSTER_SEP:
                        booster_sep booster_separation;
                        booster_separation.value.leftBoosterSwitch = frame_read.data[0];
                        booster_separation.value.rightBoosterSwitch = frame_read.data[1];

                        BoosterLStatus = booster_separation.value.leftBoosterSwitch;
                        BoosterRStatus = booster_separation.value.rightBoosterSwitch;
            //printf("BoosterStatus: L=0x%x R=0x%x\n", BoosterLStatus, BoosterRStatus);
                    break;

                    case MODEL_TS2_SENSOR:
                        model_ts2 modelTs2;
                        modelTs2.valueInBytes[0] = frame_read.data[0];
                        modelTs2.valueInBytes[1] = frame_read.data[1];

                        Ts2_fromModel = modelTs2.value.Ts2;
                    break;

                    //Digital Inputs Command from Supervisorio. This byte is used in an OR logic with physical keys connected on FADEC's digital input.
                    case FADEC_DIG_OUTPUTS_SUPERVISORIO:
                        fadec_dig_inputs_supervisorio digInputs_fromSupervisorio;
                        digInputs_fromSupervisorio.valueInBytes[0] = frame_read.data[0];
                        keys_fromSupervisorio.in = digInputs_fromSupervisorio.valueUint8;
                    break;

                    case FADEC_OIL_RPM_REFERENCE:
                        oilRPM_reference_union oilRPM_reference;
                        oilRPM_reference.value_in_bytes[0] = frame_read.data[0];
                        oilRPM_reference.value_in_bytes[1] = frame_read.data[1];
                        OPRPMManual = (float) oilRPM_reference.value_in_uint16;
            printf("oilRPM_reference=%d\n", oilRPM_reference.value_in_uint16);
            printf("OPRPMManual=%f\n\n", OPRPMManual);
                    break;

            //TJ-200 added messages
                    case FADEC_TJ200_DIG_OUTPUTS_SUPERVISORIO:
                        digInputs_TJ200_fromSupervisorio.valueInBytes[0] = frame_read.data[0];
                        keys_fromSupervisorio.bits.igniter_key = digInputs_TJ200_fromSupervisorio.value.vela;
                        keys_fromSupervisorio.bits.ignSOV_key = digInputs_TJ200_fromSupervisorio.value.valvula_vela;
                        keys_fromSupervisorio.bits.shut_off_key = digInputs_TJ200_fromSupervisorio.value.valvula_combustivel;
                        //printf("digFromSup=%d\n", digInputs_TJ200_fromSupervisorio.valueUint8);
                    break;

                    case FADEC_TJ200_PWM_0TO100_OUTPUT:
                        union pwm_0a100_TJ200_union
                        {
                            uint16_t value_in_uint16;
                            uint8_t value_in_bytes[2];
                        };
                        pwm_0a100_TJ200_union pwm_0a100_TJ200;
                        pwm_0a100_TJ200.value_in_bytes[0] = frame_read.data[0];
                        pwm_0a100_TJ200.value_in_bytes[1] = frame_read.data[1];
                        if(LeverMode == 2)	//se Manual (Pot)
                            valorManete = pwm_0a100_TJ200.value_in_uint16 / 100; 	//valor enviado de 0 a 10000,convertido de 0 a 100%
                                                                                    //trata o valor recebido pela CAN1 (Supervisorio) como se fosse a Manete CAN ligada ao CAN0
                        //printf("pwm0a100=%d\n", pwm_0a100_TJ200);
                    break;

                    case FADEC_TJ200_PWM_START_MOTOR:
                        //rcpwm_startMotor_TJ200 = frame_read.data[0];        //
                        ContStart.StrtRPMAct = (floating) frame_read.data[0];
                        //printf("rcpwm=%d\n", rcpwm_startMotor_TJ200);
                    break;


                }   //END OF switch case

            }   //END OF if(recv(cansock, &frame_read, sizeof(struct can_frame), MSG_DONTWAIT) > 0)

            /********************************************************************************************/
            /*
             *                                 CHECKING OBC HEARTBEAT
             */
            /********************************************************************************************/
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

            }   //END OF if(EngStatus.EngStatusBist.Starting | EngStatus.EngStatusBist.Idle | EngStatus.EngStatusBist.Regime)  //if FADEC is in one of these status, check the communication

        }   //END OF if ( upTime_sendATDPOCmsg_ms >= (last_sendATDPOCmsg_ms + FADEC_OBC_TIMERATE_MS - 20) )


        /********************************************************************************************/
        /*
         *                                 OBC MESSAGES TRANSMISSION
         */
        /********************************************************************************************/

        if ( upTime_sendATDPOCmsg_ms >= (last_sendATDPOCmsg_ms + FADEC_OBC_TIMERATE_MS) )   //after the interval defined by FADEC_OBC_TIMERATE_MS, the messages are sent to ATDPOC bus.
        {
            last_sendATDPOCmsg_ms = upTime_sendATDPOCmsg_ms;


            if((uint8_t)simMod != 0)        //if the simulation mode is NOT SIL, send the FADEC to OBC messages.
            {
            // FADEC status
                fadec_status fadecStatus;
                //fadecStatus.value.fuelFlow = ModelParsCL.Wf*100000;//Wf*100000;                 //converts fValue range (0 to 0.2 kg/s) to be transmitted on uint format (0 to 20000). Must be divided by 100000 on destination!
                fadecStatus.value.fuelFlow = Wf*100000; //converts fValue range (0 to 0.2 kg/s) to be transmitted on uint format (0 to 20000). Must be divided by 100000 on destination!
                fadecStatus.value.TurbineChamberTemperature = Tt4;      //Kelvin (0 to 2000K)
                fadecStatus.value.oilPressure = Sensors.POil[0] / 100;  //converting from PA to mbar: 1PA = 0.01mbar || 100PA = 1mbar, so divide the PA value by 100. The range is: 0 to 10000mbar (0 to 10bar)
                fadecStatus.value.pFuel = Sensors.PFuel[0] / 100000;             //converting from PA to bar. 100000PA = 1bar, so divide the PA value by 100000. The range is: 0 to 160bar

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
                 printf("Status Error!\n");
                }

                frame_send.can_id = FADEC_STATUS_CANID | 1 << 31;	//1<<31 sets the Extended ID Flag bit

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
                telemetry1.value.vibration = Sensors.Vibration[0] * 1000;                   //converting from mm/s to um/s (micrometers per second). 1mm/s = 1000 um/s, so multiply the value by 1000. The range is: 0 to 50000um/s (0 to 50mm/s)
                telemetry1.value.combustionChamberStaticPressure = Sensors.Pt3[0] / 100;	//converting from PA to mbar: 1PA = 0.01mbar || 100PA = 1mbar, so divide the PA value by 100. The range is: 0 to 10000mbar (0 to 10bar)

                frame_send.can_id = FADEC_TLM_1_CANID | 1 << 31;	//1<<31 sets the Extended ID Flag bit

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

            // FADEC variables to Telemetry 2 - Rate: 1000ms
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

                    frame_send.can_id = FADEC_TLM_2_CANID | 1 << 31;	//1<<31 sets the Extended ID Flag bit

                    frame_send.can_dlc = 6;
                    frame_send.data[0] = telemetry2.valueInBytes[0];
                    frame_send.data[1] = telemetry2.valueInBytes[1];
                    frame_send.data[2] = telemetry2.valueInBytes[2];
                    frame_send.data[3] = telemetry2.valueInBytes[3];
                    frame_send.data[4] = telemetry2.valueInBytes[4];
                    frame_send.data[5] = telemetry2.valueInBytes[5];

                    send_ATDPOC_canmsg(cansock, frame_send);
                }

            //FADEC Estimated thrust
                fadec_obc_estimated_thrust thrust;
                thrust.value.estimated_thrust = ModelParsCL.Fn;

                frame_send.can_id = FADEC_OBC_ESTIMATED_THRUST_CANID | 1 << 31;	//1<<31 sets the Extended ID Flag bit

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

            //FADEC Warning Codes
                fadec_tlm_warning_codes warningsCANmsg;

                warningsCANmsg.valueUint64 = FaultWarning.FaultBits;

                frame_send.can_id = FADEC_TLM_WARNING_CODES_CANID | 1 << 31;	//1<<31 sets the Extended Flag ID bit

                frame_send.can_dlc = 8;
                frame_send.data[0] = warningsCANmsg.valueInBytes[0];
                frame_send.data[1] = warningsCANmsg.valueInBytes[1];
                frame_send.data[2] = warningsCANmsg.valueInBytes[2];
                frame_send.data[3] = warningsCANmsg.valueInBytes[3];
                frame_send.data[4] = warningsCANmsg.valueInBytes[4];
                frame_send.data[5] = warningsCANmsg.valueInBytes[5];
                frame_send.data[6] = warningsCANmsg.valueInBytes[6];
                frame_send.data[7] = warningsCANmsg.valueInBytes[7];

                send_ATDPOC_canmsg(cansock, frame_send);


/*                if (ENABLE_FADEC_SUPERVISORY_MESSAGES)  // Sends the values of all sensors to Supervisorio. NEVER USE ON OBC NET!
                {

                // Digital Inputs and Outputs, including PLC outputs, and Cold Junction Average Temperature
                    //fadec_dig_inputs_outputs_coldjunction digInOut_coldjunction;

                    digInOut_coldjunction.value.dig_inputs = keys.in;
                    digInOut_coldjunction.value.dig_outputs = digital.out;
                    //digInOut.value.plc_outputs =
                    digInOut_coldjunction.value.coldjunction_avg = (t1a + t1b + t1c + t1d + t1e + t1f + t1g + t1h) / 8;     //calculates the average of cold junctions

                    frame_send.can_id = FADEC_DIG_INPUTS_OUTPUTS_CJ | 1 << 31;	//1<<31 sets the Extended Flag ID bit

                    frame_send.can_dlc = 8;
                    frame_send.data[0] = digInOut_coldjunction.valueInBytes[0];
                    frame_send.data[1] = digInOut_coldjunction.valueInBytes[1];
                    frame_send.data[2] = digInOut_coldjunction.valueInBytes[2];
                    frame_send.data[3] = digInOut_coldjunction.valueInBytes[3];
                    frame_send.data[4] = digInOut_coldjunction.valueInBytes[4];
                    frame_send.data[5] = digInOut_coldjunction.valueInBytes[5];
                    frame_send.data[6] = digInOut_coldjunction.valueInBytes[6];
                    frame_send.data[7] = digInOut_coldjunction.valueInBytes[7];

                    send_ATDPOC_canmsg(cansock, frame_send);

                //RPMA, RPMB, RPMOil and RPMFuel
                    fadec_rpma_rpmb_rpmoil_rpmfuel rpmFADEC;

                    rpmFADEC.value.rpmA = (int16_t) r11;
                    rpmFADEC.value.rpmB = (int16_t) r12;
                    rpmFADEC.value.rpmOil = (int16_t) RPMOilPump;
                    rpmFADEC.value.rpmFuel = (int16_t) RPMFuelPump;

                    frame_send.can_id = FADEC_RPMA_RPMB_RPMOIL_RPMFUEL | 1 << 31;	//1<<31 sets the Extended Flag ID bit

                    frame_send.can_dlc = 8;
                    frame_send.data[0] = rpmFADEC.valueInBytes[0];
                    frame_send.data[1] = rpmFADEC.valueInBytes[1];
                    frame_send.data[2] = rpmFADEC.valueInBytes[2];
                    frame_send.data[3] = rpmFADEC.valueInBytes[3];
                    frame_send.data[4] = rpmFADEC.valueInBytes[4];
                    frame_send.data[5] = rpmFADEC.valueInBytes[5];
                    frame_send.data[6] = rpmFADEC.valueInBytes[6];
                    frame_send.data[7] = rpmFADEC.valueInBytes[7];

                    send_ATDPOC_canmsg(cansock, frame_send);

                //FADEC Analog Inputs
                    fadec_an_inputs anInputsFADEC;

                    anInputsFADEC.value.i10 = i10 * 1000;   //all voltages are transmitted on mV
                    anInputsFADEC.value.i11 = i11 * 1000;
                    anInputsFADEC.value.i12 = i12 * 1000;
                    anInputsFADEC.value.i13 = i13 * 1000;

                    frame_send.can_id = FADEC_AN_INPUTS | 1 << 31;	//1<<31 sets the Extended Flag ID bit

                    frame_send.can_dlc = 8;
                    frame_send.data[0] = anInputsFADEC.valueInBytes[0];
                    frame_send.data[1] = anInputsFADEC.valueInBytes[1];
                    frame_send.data[2] = anInputsFADEC.valueInBytes[2];
                    frame_send.data[3] = anInputsFADEC.valueInBytes[3];
                    frame_send.data[4] = anInputsFADEC.valueInBytes[4];
                    frame_send.data[5] = anInputsFADEC.valueInBytes[5];
                    frame_send.data[6] = anInputsFADEC.valueInBytes[6];
                    frame_send.data[7] = anInputsFADEC.valueInBytes[7];

                    send_ATDPOC_canmsg(cansock, frame_send);

                //FADEC Analog Outputs
                    fadec_an_outputs anOutputsFADEC;

                    //As FADEC now sends the flow instead of voltage, the value must be converted from 0~0.2 kg/s to 0~20000 to match the variable type (unsigned int 16)
                    //anOutputsFADEC.value.o10 = pump_flowToVoltage * 1000;   //sends the value on mV. Needs to be converted on Supervisorio
                    anOutputsFADEC.value.o10 = Wf * 100000;   //converts from 0~0.2 kg/s to 0~20000.
                    anOutputsFADEC.value.o11 = 0;
                    anOutputsFADEC.value.o12 = 0;
                    anOutputsFADEC.value.o13 = 0;

                    frame_send.can_id = FADEC_AN_OUTPUTS | 1 << 31;	//1<<31 sets the Extended Flag ID bit

                    frame_send.can_dlc = 8;
                    frame_send.data[0] = anOutputsFADEC.valueInBytes[0];
                    frame_send.data[1] = anOutputsFADEC.valueInBytes[1];
                    frame_send.data[2] = anOutputsFADEC.valueInBytes[2];
                    frame_send.data[3] = anOutputsFADEC.valueInBytes[3];
                    frame_send.data[4] = anOutputsFADEC.valueInBytes[4];
                    frame_send.data[5] = anOutputsFADEC.valueInBytes[5];
                    frame_send.data[6] = anOutputsFADEC.valueInBytes[6];
                    frame_send.data[7] = anOutputsFADEC.valueInBytes[7];

                    send_ATDPOC_canmsg(cansock, frame_send);

                //FADEC Thermocouples 1 to 4
                    fadec_thermocouple_1_4 thermocouples_1_4_FADEC;

                    thermocouples_1_4_FADEC.value.t11 = t11;   //sends the value on mV. Needs to be converted on Supervisorio
                    thermocouples_1_4_FADEC.value.t12 = t12;
                    thermocouples_1_4_FADEC.value.t13 = t13;
                    thermocouples_1_4_FADEC.value.t14 = t14;

                    frame_send.can_id = FADEC_THERMOCOUPLE_1_4 | 1 << 31;	//1<<31 sets the Extended Flag ID bit

                    frame_send.can_dlc = 8;
                    frame_send.data[0] = thermocouples_1_4_FADEC.valueInBytes[0];
                    frame_send.data[1] = thermocouples_1_4_FADEC.valueInBytes[1];
                    frame_send.data[2] = thermocouples_1_4_FADEC.valueInBytes[2];
                    frame_send.data[3] = thermocouples_1_4_FADEC.valueInBytes[3];
                    frame_send.data[4] = thermocouples_1_4_FADEC.valueInBytes[4];
                    frame_send.data[5] = thermocouples_1_4_FADEC.valueInBytes[5];
                    frame_send.data[6] = thermocouples_1_4_FADEC.valueInBytes[6];
                    frame_send.data[7] = thermocouples_1_4_FADEC.valueInBytes[7];

                    send_ATDPOC_canmsg(cansock, frame_send);

                //FADEC Thermocouples 5 to 8
                    fadec_thermocouple_5_8 thermocouples_5_8_FADEC;

                    thermocouples_5_8_FADEC.value.t15 = t15;   //sends the value on mV. Needs to be converted on Supervisorio
                    thermocouples_5_8_FADEC.value.t16 = t16;
                    thermocouples_5_8_FADEC.value.t17 = t17;
                    thermocouples_5_8_FADEC.value.t18 = t18;

                    frame_send.can_id = FADEC_THERMOCOUPLE_5_8 | 1 << 31;	//1<<31 sets the Extended Flag ID bit

                    frame_send.can_dlc = 8;
                    frame_send.data[0] = thermocouples_5_8_FADEC.valueInBytes[0];
                    frame_send.data[1] = thermocouples_5_8_FADEC.valueInBytes[1];
                    frame_send.data[2] = thermocouples_5_8_FADEC.valueInBytes[2];
                    frame_send.data[3] = thermocouples_5_8_FADEC.valueInBytes[3];
                    frame_send.data[4] = thermocouples_5_8_FADEC.valueInBytes[4];
                    frame_send.data[5] = thermocouples_5_8_FADEC.valueInBytes[5];
                    frame_send.data[6] = thermocouples_5_8_FADEC.valueInBytes[6];
                    frame_send.data[7] = thermocouples_5_8_FADEC.valueInBytes[7];

                    send_ATDPOC_canmsg(cansock, frame_send);

                //FADEC Debug Values. Two float values sent to Supervisorio. Can assume any value.
                    fadec_debug_float_values debug_float_values;

                    //debug_float_values.value.value1 = ContInModCL.FNpc;
                    debug_float_values.value.value1 = ContOutput.Active;    //Active controller
                    debug_float_values.value.value2 = ContInput.FNpc;//ModelParsCL.Wf;

                    frame_send.can_id = FADEC_DEBUG_FLOAT_VALUES | 1 << 31;	//1<<31 sets the Extended Flag ID bit

                    frame_send.can_dlc = 8;
                    frame_send.data[0] = debug_float_values.valueInBytes[0];
                    frame_send.data[1] = debug_float_values.valueInBytes[1];
                    frame_send.data[2] = debug_float_values.valueInBytes[2];
                    frame_send.data[3] = debug_float_values.valueInBytes[3];
                    frame_send.data[4] = debug_float_values.valueInBytes[4];
                    frame_send.data[5] = debug_float_values.valueInBytes[5];
                    frame_send.data[6] = debug_float_values.valueInBytes[6];
                    frame_send.data[7] = debug_float_values.valueInBytes[7];

                    send_ATDPOC_canmsg(cansock, frame_send);

                //FADEC Debug Values #2. Use the same struct as the other.
                    fadec_debug_float_values debug_float_values_2;

                    debug_float_values_2.value.value1 = ModelParsCL.RPM;
                    debug_float_values_2.value.value2 = Wf;

                    frame_send.can_id = FADEC_DEBUG_FLOAT_VALUES_2 | 1 << 31;	//1<<31 sets the Extended Flag ID bit

                    frame_send.can_dlc = 8;
                    frame_send.data[0] = debug_float_values_2.valueInBytes[0];
                    frame_send.data[1] = debug_float_values_2.valueInBytes[1];
                    frame_send.data[2] = debug_float_values_2.valueInBytes[2];
                    frame_send.data[3] = debug_float_values_2.valueInBytes[3];
                    frame_send.data[4] = debug_float_values_2.valueInBytes[4];
                    frame_send.data[5] = debug_float_values_2.valueInBytes[5];
                    frame_send.data[6] = debug_float_values_2.valueInBytes[6];
                    frame_send.data[7] = debug_float_values_2.valueInBytes[7];

                    send_ATDPOC_canmsg(cansock, frame_send);
                }   //END OF if (ENABLE_FADEC_SUPERVISORY_MESSAGES)
*/
            }   //END OF if((uint8_t)simMod != 0)        //if the simulation mode is NOT SIL

        }   //END OF if ( upTime_sendATDPOCmsg_ms >= (last_sendATDPOCmsg_ms + FADEC_OBC_TIMERATE_MS) )

    }   //END OF while(1)    //never exits this thread

}

/********************************************************************************************/
/*
 *                                UPDATING TELEMETRY FILE
 */
/********************************************************************************************/

void *thread_telemetry_updateFile_fcn(void *ptr)
{
    while(1)
    {
        if (flag_writeSensorsDataFile == 1)
        {

            //As FADEC now sends the flow value, the conversion for voltage is not needed
//                float fuelFlowToVoltage = (Wf/TJ1200_WFMAX);//(fValue/TJ1200_WFMAX);		//converts 0~max fuel pump flow to 0~5V
//                fuelFlowToVoltage = fuelFlowToVoltage * 5;	//converts 0~max fuel pump flow to 0~5V

            /*fadecSensorsDataFile << t11 << "," << t12 << "," << t13 << "," << t14 << "," << t15 << "," << t16 << "," << t17 << "," << t18 <<"," ;
            fadecSensorsDataFile << i10 << "," << i11 << "," << i12 << "," << i13 << "," << r11 << "," << r12 << ",";
//                fadecSensorsDataFile << keys.in << "," << digital.out << "," << 0 << "," << fuelFlowToVoltage << "," << 0 << "," << 0 << "," << 0 << std::endl;
            fadecSensorsDataFile << keys.in << "," << digital.out << "," << 0 << "," << Wf << "," << 0 << "," << 0 << "," << 0 << std::endl;*/

//            fadecSensorsDataFile << t11 << ";" << t12 << ";" << t13 << ";" << t14 << ";" << t15 << ";" << t16 << ";" << t17 << ";" << t18 <<";" ;
//            fadecSensorsDataFile << i10 << ";" << i11 << ";" << i12 << ";" << i13 << ";" << r11 << ";" << r12 << ";";
//            fadecSensorsDataFile << keys.in << ";" << digital.out << ";" << 0 << ";" << Wf << ";" << 0 << ";" << 0 << ";" << 0 << ";";//std::endl;
//            fadecSensorsDataFile << ContInput.Tt2 << ";" << ContInput.Tt4 << ";" << ContInput.FNpc << ";" << ContOutput.RPMRef << ";" << ContOutput.eNk1 << ";" << ContOutput.eTt4k1 << ";" << ContOutput.uNk1 << ";"<< ContOutput.uTt4k1 << ";"<< ContOutput.Wf << ";"<< ContOutput.Active << ";" << Ts2MedVal << ";" << ContInput.MN << ";" << std::endl;

            fadecSensorsDataFile << upTime_ms << ";"
                                 << t10 << ";" << t11 << ";" << t12 << ";" << t13 << ";" << t14 << ";" << t15 << ";" << t16 << ";" << t17 <<";"
                                 << i10 << ";" << i11 << ";" << i12 << ";" << i13 << ";"
                                 << r11 << ";" << r12 << ";" << keys.in << ";" << digital.out << ";"
                                 << Wf << ";" << OPRPM << ";" << 0 << ";" << 0 << ";"
                                 << RPMOilPump << ";" << RPMFuelPump << ";"
                                 << Altitude << ";" << RefCAN << ";" << MN << ";" << OnOffCom << ";" << BoosterLStatus << ";" << BoosterRStatus << ";"
                                 << ModelParsCL.Fn << ";" << FaultStatus.FaultBits << ";" << FaultWarning.FaultBits << ";"
                                 << digInOut_coldjunction.value.coldjunction_avg << ";"
                                 << ContInput.Tt2 << ";" << ContInput.Tt4 << ";" << ContInput.FNpc << ";" << ContOutput.RPMRef << ";" << ContOutput.eNk1 << ";" << ContOutput.eTt4k1 << ";" << ContOutput.uNk1 << ";"<< ContOutput.uTt4k1 << ";"<< ContOutput.Wf << ";"<< ContOutput.Active << ";" << Ts2MedVal << ";" << ContInput.MN << ";"
                                 << EngStatus.EngineStatus << ";"
                                 << std::endl;

            fadecSensorsDataFile.flush();   //saves the ofstream buffer immediately to file.

            flag_writeSensorsDataFile = 0;
            //flag_syncFile = 1;

        }
    }

}


/********************************************************************************************/
/*
 *                                SAVING TELEMETRY FILE
 */
/********************************************************************************************/

void *thread_telemetry_syncFile_fcn(void *ptr)
{
    static int fileToSync = open(filename.c_str(), O_RDONLY);  //opens the file just one time.
    while(1)
    {
        //if (flag_syncFile == 1)
        if ( upTime_ms >= (last_saveTelemetryFile_ms + FADEC_SAVE_TELEMETRY_FILE_PERIOD_MS) )
        {

            last_saveTelemetryFile_ms = upTime_ms;
            //sync();             //The sync command writes all unwritten system buffers to disk - https://www.ibm.com/docs/en/aix/7.2?topic=s-sync-command
            fsync(fileToSync);      //The fsync() function forces all currently queued I/O operations associated with the file indicated by file descriptor to the synchronised I/O completion state.
            //fdatasync(fileToSync);     //fdatasync() is similar to fsync(), but does not flush modified metadata unless that metadata is needed in order to allow a subsequent data retrieval to be correctly handled.

            //flag_syncFile = 0;

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

/********************************************************************************************/
/*
 *                                 MAIN
 */
/********************************************************************************************/
int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <node-id>" << std::endl;
        return 1;
    }

    nice(-4);       //priority of the process. The lower the number, higher the priority. Standard value: 0. Max priority: -20. Min Priority: +20.

    const int self_node_id = std::stoi(argv[1]);

    std::cout << VERSAO_DO_DIA << std::endl;

    /******************************************** CREATING DATA REGISTER FILE ******************************************************/
    int fileSuffixNumber = 0;   //suffix number for file name

    do
    {
       testFileExistence.open(filename);    //tries to open file

       if(testFileExistence.good()) //if file already exists
       {
           testFileExistence.close();   //closes the file

           fileSuffixNumber++;                                      //increases the file number suffix
           filename = "/home/root/Desktop/FADECTelemetry/fadecRegister";                              //creates the base file name
           filename.append(std::to_string(fileSuffixNumber));       //appends the suffix on the end of file name
           filename.append(".csv");                                 //and the extension
       }
    }
    while(testFileExistence.good());    //while the file exists, keep increasing the suffix.

    fadecSensorsDataFile.open(filename);    //creates the file with correct number suffix

    //fadecSensorsDataFile << "t11, t12, t13, t14, t15, t16, t17, t18, i10, i11, i12, i13, r11, r12, d11, d12, d13, o10, o11, o12, o13" << std::endl; //the first line is the column title
    //the first line is the column title
    fadecSensorsDataFile << "upTime;"
                         << "t10; t11; t12; t13; t14; t15; t16; t17;"
                         << "i10; i11; i12; i13;"
                         << "r11; r12; d11; d12;"
                         << "o10; o11; o12; o13;"
                         << "RPMOil; RPMFuel;"
                         << "Altitude; ThrustCommand; MachNumber; EngCommand; BoosterLStatus; BoosterRStatus;"
                         << "EstimatedThrust; FaultStatus; FaultWarning;"
                         << "ColdJunction;"
                         << "Tt2; Tt4; FNpc; RPMRef; eNk1; eTk1; uNk1; uTk1; Wf; Active; Ts2; MN;"
                         << "ControlStatus;"
                         << std::endl;


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

     struct can_filter rfilter[10];

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

     rfilter[7].can_id   = FADEC_DIG_OUTPUTS_SUPERVISORIO | CAN_EFF_FLAG;
     rfilter[7].can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);

     //rfilter[6].can_id   = FADEC_RESET_COMMAND | CAN_EFF_FLAG;
     //rfilter[6].can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);

     rfilter[8].can_id   = FADEC_OIL_RPM_REFERENCE | CAN_EFF_FLAG;
     rfilter[8].can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);

     rfilter[9].can_id   = FADEC_CAN1_CHOOSE_PROTOCOL | CAN_EFF_FLAG;
     rfilter[9].can_mask = (CAN_EFF_FLAG | CAN_RTR_FLAG | CAN_EFF_MASK);

     //Setting the Message Filter
    setsockopt(can_atd_poc, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

    /**********************************************************************/


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
    std::cout << iface_names.data() << std::endl;
    uavcan_linux::NodePtr nodeCAN0 = initNodePtr(iface_names, self_node_id, "FADEC_CAN0");

    std::vector<std::string> iface_names1;   //string of can channels to be configured as UAVCAN node.
    iface_names1.emplace_back("can1");       //only CAN0 will be used as UAVCAN node.
    uavcan_linux::NodePtr nodeCAN1 = initNodePtr(iface_names1, 120, "FADEC_CAN1");

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

/********************************************************************************************************************************/
/*                                                                                                                              */
/********************************************************************************************************************************/


/********************************************************************************************************************************/
/*																																*/
/*												KEYVALUE MESSAGE RECEPTION CAN0 											 	*/
/*																																*/
/********************************************************************************************************************************/

    /*
     * Subscribing to messages of type uavcan.protocol.debug.KeyValue.
     * This time we don't want to receive extra information about the received message, so the callback's argument type
     * would be just T& instead of uavcan::ReceivedDataStructure<T>&.
     * The callback will print the message in YAML format via std::cout (also refer to uavcan::OStream).
     */
    uavcan::Subscriber<uavcan::protocol::debug::KeyValue> kv_subCAN0(*nodeCAN0);

    const int kv_subCAN0_start_res = kv_subCAN0.start([&](const uavcan::protocol::debug::KeyValue& msg)
    {

        int error = 0;
        std::string key = "";
        unsigned char const * floatToByte;// = reinterpret_cast<unsigned char const *>(&f);

        key += msg.key[0];	//os tres primeiros caracteres informam a origem do dado
        key += msg.key[1];
        key += msg.key[2];

	//std::cout << msg << std::endl;

	if(key.compare("i10") == 0)	//se a mensagem recebida tem keyValue i11, grava na variável i11
	{
		i10 = msg.value;		//e o float é formado a partir dos 4 bytes
        //pot_percent = i10/5;
//std::cout << pot_percent << " ";
	}

	else if(key.compare("i11") == 0)
		i11 = msg.value;

	else if(key.compare("i12") == 0)
		i12 = msg.value;			//Pt2

	else if(key.compare("i13") == 0)		//Pt3
		i13 = msg.value;

	else if(key.compare("o1a") == 0)
		o1a = msg.value;

	else if(key.compare("o1b") == 0)
		o1b = msg.value;

	else if(key.compare("o1c") == 0)
		o1c = msg.value;

	else if(key.compare("o1d") == 0)
		o1d = msg.value;

    else if(key.compare("t10") == 0)
        t10 = msg.value;	//Kelvin

    else if(key.compare("t11") == 0)
        t11 = msg.value;	//Kelvin

    else if(key.compare("t12") == 0)
        t12 = msg.value;	//Kelvin

    else if(key.compare("t13") == 0)
        t13 = msg.value;	//Kelvin

    else if(key.compare("t14") == 0)
        t14 = msg.value;	//Kelvin

    else if(key.compare("t15") == 0)
        t15 = msg.value;	//Kelvin

    else if(key.compare("t16") == 0)
        t16 = msg.value;	//Kelvin

    else if(key.compare("t17") == 0)
        t17 = msg.value;	//Kelvin

	else if(key.compare("t1a") == 0)
        t1a = msg.value;	//cold junction value channel 1

	else if(key.compare("t1b") == 0)
        t1b = msg.value;	//cold junction value channel 2

	else if(key.compare("t1c") == 0)
        t1c = msg.value;	//cold junction value channel 3

	else if(key.compare("t1d") == 0)
        t1d = msg.value;	//cold junction value channel 4

	else if(key.compare("t1e") == 0)
        t1e = msg.value;	//cold junction value channel 5

	else if(key.compare("t1f") == 0)
        t1f = msg.value;	//cold junction value channel 6

	else if(key.compare("t1g") == 0)
        t1g = msg.value;	//cold junction value channel 7

	else if(key.compare("t1h") == 0)
        t1h = msg.value;	//cold junction value channel 8

    else if(key.compare("t1A") == 0)
    {
        t1A = msg.value;	//status bits channel 1

        union thermoStatus
        {
            struct bits
            {
                uint8_t open_circuit        :1;
                uint8_t short_gnd           :1;
                uint8_t short_vcc           :1;
            } bits;

            uint8_t valueUint8;
        };

        thermoStatus thermo_status;

        thermo_status.valueUint8 = t1A;

        if(faultsFromSuperv.Faults.TCFaultSoftSim == 0)
        {
            SoftSimFaults.SensFaults.Ts2_0_Open = thermo_status.bits.open_circuit;
            SoftSimFaults.SensFaults.Ts2_0_SCV = thermo_status.bits.short_vcc;
            SoftSimFaults.SensFaults.Ts2_0_SCG = thermo_status.bits.short_gnd;
        }

    }

    else if(key.compare("t1B") == 0)
    {
        t1B = msg.value;	//status bits channel 2

        union thermoStatus
        {
            struct bits
            {
                uint8_t open_circuit        :1;
                uint8_t short_gnd           :1;
                uint8_t short_vcc           :1;
            } bits;

            uint8_t valueUint8;
        };

        thermoStatus thermo_status;

        thermo_status.valueUint8 = t1B;

        if(faultsFromSuperv.Faults.TCFaultSoftSim == 0)
        {
            SoftSimFaults.SensFaults.Ts2_1_Open = thermo_status.bits.open_circuit;
            SoftSimFaults.SensFaults.Ts2_1_SCV = thermo_status.bits.short_vcc;
            SoftSimFaults.SensFaults.Ts2_1_SCG = thermo_status.bits.short_gnd;
        }

    }

    else if(key.compare("t1C") == 0)
    {
        t1C = msg.value;	//status bits channel 3

        union thermoStatus
        {
            struct bits
            {
                uint8_t open_circuit        :1;
                uint8_t short_gnd           :1;
                uint8_t short_vcc           :1;
            } bits;

            uint8_t valueUint8;
        };

        thermoStatus thermo_status;

        thermo_status.valueUint8 = t1C;

        if(faultsFromSuperv.Faults.TCFaultSoftSim == 0)
        {
            SoftSimFaults.SensFaults.Tt4_0_Open = thermo_status.bits.open_circuit;
            SoftSimFaults.SensFaults.Tt4_0_SCV = thermo_status.bits.short_vcc;
            SoftSimFaults.SensFaults.Tt4_0_SCG = thermo_status.bits.short_gnd;
        }

    }

    else if(key.compare("t1D") == 0)
    {
        t1D = msg.value;	//status bits channel 4

        union thermoStatus
        {
            struct bits
            {
                uint8_t open_circuit        :1;
                uint8_t short_gnd           :1;
                uint8_t short_vcc           :1;
            } bits;

            uint8_t valueUint8;
        };

        thermoStatus thermo_status;

        thermo_status.valueUint8 = t1D;

        if(faultsFromSuperv.Faults.TCFaultSoftSim == 0)
        {
            SoftSimFaults.SensFaults.Tt4_1_Open = thermo_status.bits.open_circuit;
            SoftSimFaults.SensFaults.Tt4_1_SCV = thermo_status.bits.short_vcc;
            SoftSimFaults.SensFaults.Tt4_1_SCG = thermo_status.bits.short_gnd;
        }

    }

    else if(key.compare("t1E") == 0)
    {
        t1E = msg.value;	//status bits channel 5

        union thermoStatus
        {
            struct bits
            {
                uint8_t open_circuit        :1;
                uint8_t short_gnd           :1;
                uint8_t short_vcc           :1;
            } bits;

            uint8_t valueUint8;
        };

        thermoStatus thermo_status;

        thermo_status.valueUint8 = t1E;

        if(faultsFromSuperv.Faults.TCFaultSoftSim == 0)
        {
            SoftSimFaults.SensFaults.Tt4_2_Open = thermo_status.bits.open_circuit;
            SoftSimFaults.SensFaults.Tt4_2_SCV = thermo_status.bits.short_vcc;
            SoftSimFaults.SensFaults.Tt4_2_SCG = thermo_status.bits.short_gnd;
        }

    }

    else if(key.compare("t1F") == 0)
    {
        t1F = msg.value;	//status bits channel 6

        union thermoStatus
        {
            struct bits
            {
                uint8_t open_circuit        :1;
                uint8_t short_gnd           :1;
                uint8_t short_vcc           :1;
            } bits;

            uint8_t valueUint8;
        };

        thermoStatus thermo_status;

        thermo_status.valueUint8 = t1F;

        if(faultsFromSuperv.Faults.TCFaultSoftSim == 0)
        {
            //SoftSimFaults.SensFaults.Tt4_2_Open = thermo_status.bits.open_circuit;
           // SoftSimFaults.SensFaults.Tt4_2_SCV = thermo_status.bits.short_vcc;
            //SoftSimFaults.SensFaults.Tt4_2_SCG = thermo_status.bits.short_gnd;
        }

    }

    else if(key.compare("t1G") == 0)
    {
        t1G = msg.value;	//status bits channel 7

        union thermoStatus
        {
            struct bits
            {
                uint8_t open_circuit        :1;
                uint8_t short_gnd           :1;
                uint8_t short_vcc           :1;
            } bits;

            uint8_t valueUint8;
        };

        thermoStatus thermo_status;

        thermo_status.valueUint8 = t1G;

        if(faultsFromSuperv.Faults.TCFaultSoftSim == 0)
        {
            //SoftSimFaults.SensFaults.Tt4_2_Open = thermo_status.bits.open_circuit;
            //SoftSimFaults.SensFaults.Tt4_2_SCV = thermo_status.bits.short_vcc;
            //SoftSimFaults.SensFaults.Tt4_2_SCG = thermo_status.bits.short_gnd;
        }

    }

    else if(key.compare("t1H") == 0)
    {
        t1H = msg.value;	//status bitsFTDI channel 8

        union thermoStatus
        {
            struct bits
            {
                uint8_t open_circuit        :1;
                uint8_t short_gnd           :1;
                uint8_t short_vcc           :1;
            } bits;

            uint8_t valueUint8;
        };

        thermoStatus thermo_status;

        thermo_status.valueUint8 = t1H;

        if(faultsFromSuperv.Faults.TCFaultSoftSim == 0)
        {
            //SoftSimFaults.SensFaults.Tt4_2_Open = thermo_status.bits.open_circuit;
            //SoftSimFaults.SensFaults.Tt4_2_SCV = thermo_status.bits.short_vcc;
            //SoftSimFaults.SensFaults.Tt4_2_SCG = thermo_status.bits.short_gnd;
        }

    }

	else if(key.compare("d11") == 0)
	{
		d11_float = msg.value;

		unsigned int d11_int = d11_float;		//transformo o float em int


        //IMNPORTANT! For Flight Version FADEC, the physical keys will not be read, and digital inputs Exciter and Shut Off Valve will come from Supervisorio.

		/*keys.bits.emergency_key = (d11_int >> 2) & 1;
		keys.bits.mode_key = (d11_int >> 3) & 1;
		keys.bits.igniter_key = (d11_int >> 5) & 1;
		keys.bits.shut_off_key = (d11_int >> 6) & 1;
		keys.bits.scaveng_key = (d11_int >> 7) & 1;
		keys.bits.oil_pump_key = (d11_int >> 8) & 1;
		keys.bits.ac_drive_key = (d11_int >> 9) & 1;*/

        /*keys.bits.igniter_key = d11_int & 1;
		keys.bits.shut_off_key = (d11_int >> 1) & 1;
		keys.bits.scaveng_key = (d11_int >> 2) & 1;
		keys.bits.oil_pump_key = (d11_int >> 3) & 1;
		keys.bits.ac_drive_key = (d11_int >> 4) & 1;
		keys.bits.emergency_key = (d11_int >> 5) & 1;
		keys.bits.mode_key = (d11_int >> 6) & 1;

        keys.bits.igniter_key = !(!keys.bits.igniter_key | !keys_fromSupervisorio.bits.igniter_key);
        keys.bits.shut_off_key = !(!keys.bits.shut_off_key | !keys_fromSupervisorio.bits.shut_off_key);
        keys.bits.scaveng_key = !(!keys.bits.scaveng_key | !keys_fromSupervisorio.bits.scaveng_key);
        keys.bits.oil_pump_key = !(!keys.bits.oil_pump_key | !keys_fromSupervisorio.bits.oil_pump_key);
        keys.bits.ac_drive_key = !(!keys.bits.ac_drive_key | !keys_fromSupervisorio.bits.ac_drive_key);*/

        keys.bits.igniter_key = keys_fromSupervisorio.bits.igniter_key;
        keys.bits.shut_off_key = keys_fromSupervisorio.bits.shut_off_key;
        keys.bits.scaveng_key = keys_fromSupervisorio.bits.scaveng_key;
        keys.bits.oil_pump_key = keys_fromSupervisorio.bits.oil_pump_key;
        //keys.bits.ac_drive_key = keys_fromSupervisorio.bits.ac_drive_key;
        keys.bits.ac_drive_key = 0;             //AC Drive button always in 0 (pressed).
        keys.bits.emergency_key = 1;            //Emergency button always in 1 (not pressed). No physical button!

        keys.bits.ignSOV_key = keys_fromSupervisorio.bits.ignSOV_key;   //added for TJ-200.



//printf("keys_fromSupervisorio=%d , d11_int=%d , keysbits=%d\n", keys_fromSupervisorio.in, d11_int, keys.in);



	}

	else if(key.compare("d21") == 0)
	{
		d21_float = msg.value;
	}

	else if(key.compare("r11") == 0)
    {
        if(flag_tj200_selected == 1) //if TJ-200 is selected
            r11 = msg.value*3;          //as TJ-200 is 1 pulse per turn, multiply the RPM by 3
        else
            r11 = msg.value;
    }

    else if(key.compare("r12") == 0)
    {
        if(flag_tj200_selected == 1) //if TJ-200 is selected
            r12 = msg.value*3;          //as TJ-200 is 1 pulse per turn, multiply the RPM by 3
        else
            r12 = msg.value;
    }

    else if(key.compare("rpf") == 0)
    {
        //Now the conversion from eRPM to RPM is done by Analog Board. The RPM received on this message is mechanical RPM.
//        eRPMFuel = msg.value;
//        RPMFuelPump = eRPMFuel / (POLES_BLDC_FUELPUMP/2);   //as on https://discuss.ardupilot.org/t/how-to-read-rpm-signal-from-esc/8326/2?page=2
        RPMFuelPump = msg.value;
    }

    else if(key.compare("rpo") == 0)
    {
        //Now the conversion from eRPM to RPM is done by Analog Board. The RPM received on this message is mechanical RPM.

//        eRPMOil = msg.value;
//        RPMOilPump = eRPMOil / (POLES_BLDC_OILPUMP/2);  //as on https://discuss.ardupilot.org/t/how-to-read-rpm-signal-from-esc/8326/2?page=2
        RPMOilPump = msg.value;
    }

	else if(key.compare("ref") == 0)
    {
        //reference = msg.value;
        RefCAN = msg.value;
    }

	else if(key.compare("_mo") == 0)		//authorize
	{
		floatToByte = reinterpret_cast<unsigned char const *>(&msg.value);
		if(floatToByte[0] == 'a')
			Mode = 0;

		else if(floatToByte[0] == 'm')
			Mode = 1;
	}

    else if(key.compare("alt") == 0)				//Altitude
        Altitude = (floating) msg.value;

    else if(key.compare("tt2") == 0)				//Ambient Temperature
        Tt2_fromModel = (floating) msg.value;

    else if(key.compare("mnb") == 0)				//Initial Mach Number
        MN = (floating) msg.value;

    else if(key.compare("_d1") == 0)
    {
        model_d1 = msg.value;
        model_d1_toInt = model_d1;
    }

    else if(key.compare("_mf") == 0)
        model_mf = msg.value;

    else if(key.compare("_rs") == 0)		//reset
    {
//            // Sets the first button position to 1
//            ResetButton[0] = 1;
        // Sets Reset flag to 1
        Reset = 1;
        // Sets time base to zero - this variable tells how long the device has been operting
        upTime_ms = 0;
//            // Detects an edge in ResetButton - must be a ris USB UARTedge
//            Reset = Edge(ResetButton);
        //reset_command_ATDPOC(can_atd_poc);


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
    if(floatToByte[0] == 'c')	//Lever Mode: Control Law
        LeverMode = 1;

    else if(floatToByte[0] == 's')	//Lever Mode: Manual with reference from Supervisorio
        LeverMode = 0;

    else if(floatToByte[0] == 'p')	//Lever Mode: Manual with reference from Potentiometer
        LeverMode = 2;

//std::cout << LeverMode << std::endl;
    }


    else if(key.compare("_sk") == 0)
    {
        skipStart_float = msg.value;
        SkipStart = skipStart_float;
    }

    else if(key.compare("_au") == 0)		//authorize
    {
        authorize_float = msg.value;
        Authorize = authorize_float;
    }

    else if(key.compare("_w0") == 0)		//authorize
    {
        Wf0 = (floating) msg.value;
    }


     else if(key.compare("_en") == 0)		//Engine
     {
         engine_float = msg.value;
     }

    else if(key.compare("_sm") == 0)	//Simulation Mode
    {                                       //0 = SIL, 1 = HIL Async, 2 = HIL Sync, 3 = Test Bench
        simMod_float = msg.value;
        simMod = simMod_float;

    }


//        else if(key.compare("_ps") == 0)		//pause
//        {
//            if(keyData.valueInBytes[0] == 'p')
//                PauseVariable = 1;

//            else if(keyData.valueInBytes[0] == 'c')
//                PauseVariable = 0;
//        }


    else if(key.compare("_al") == 0)
    {
        initialAltitude_float = msg.value;
        Altitude = initialAltitude_float;
    }

    //	else if(key.compare("_at") == 0)
    //	{
    //		initialAmbientTemp_float = msg.value;
    //	}

    //	else if(key.compare("_en") == 0)
    //	{
    //		engine_float = msg.value;
    //		engine = engine_float;
    //	}

    else if(key.compare("_mn") == 0)
    {
        initialMachNumber_float = msg.value;
        MN = initialMachNumber_float;
    }


	else if(key.compare("_rf") == 0)
	{
		initialReference_float = msg.value;
		RefCAN = initialReference_float;
        //FNpc = RefCAN;
//printf("key.compare(""_rf""): FNpc=%f   RefCAN=%f\n", FNpc, RefCAN);
	}

    else if(key.compare("_dt") == 0)
    {
        initialdT_float = msg.value;
    }

    else if(key.compare("_ec") == 0)
    {

        engineCommand_fromSupervisorio = msg.value;
        printf("EngCommfromCAN0=%x\n", (uint8_t) engineCommand_fromSupervisorio);

        OnOffCom = (uint8_t) engineCommand_fromSupervisorio;




        /***** TO BE IMPLEMENTED ON FUTURE ***********/
        //This message sends the engine command to HIL, so HIL can simulate an OBC_FADEC_ENGINE_COMMAND message and validate if FADEC is acting correctly according to OBC command.
        //The sequence is:
        //- The button Start Engine, Shut Off Engine or Emergency ShutOff is pressed on Supervisorio;
        //- Supervisório sends the corresponding command to FADEC via CAN0;
        //- FADEC receives the message with the command value and sends this value to HIL via CAN1, using the same FADEC_RESET_COMMAND message ID;
        //- HIL receives the message and responds with an OBC_FADEC_ENGINE_COMMAND message, simulating the OBC sending a command
        //Sending the CAN message on ATDPOC format
//        struct can_frame frame_send_engine_command;
//        frame_send_engine_command.can_id = FADEC_RESET_COMMAND | 1 << 31;
//        frame_send_engine_command.can_dlc = 8;
//        frame_send_engine_command.data[0] = 0;
//        frame_send_engine_command.data[1] = 0;
//        frame_send_engine_command.data[2] = 0;
//        frame_send_engine_command.data[3] = 0;
//        frame_send_engine_command.data[4] = 0;
//        frame_send_engine_command.data[5] = 0;
//        frame_send_engine_command.data[6] = 0;
//        frame_send_engine_command.data[7] = (uint8_t) engineCommand_fromSupervisorio;
//        send_ATDPOC_canmsg(can_atd_poc, frame_send_engine_command);


    }

	/*else if(key.compare("_ps") == 0)		//pause
	{
		if(keyData.valueInBytes[0] == 'p')
			PauseVariable = 1;

		else if(keyData.valueInBytes[0] == 'c')
			PauseVariable = 0;
	}*/

    else if(key.compare("man") == 0)
    {
        valorManete = msg.value;
        //printf("Manete: %f\n", valorManete);
    }

        else
            error = 1;	//TODO error

    });

    if (kv_subCAN0_start_res < 0)
    {
        throw std::runtime_error("Failed to start the key/value subscriber; error: " + std::to_string(kv_subCAN0_start_res));
    }

	//kv_sub.allowAnonymousTransfers();


/********************************************************************************************************************************/
/*																																*/
/*												RECEPÇÃO DE MENSAGENS KEYVALUE CAN1											 	*/
/*																																*/
/********************************************************************************************************************************/

    /*
     * Subscribing to messages of type uavcan.protocol.debug.KeyValue.
     * This time we don't want to receive extra information about the received message, so the callback's argument type
     * would be just T& instead of uavcan::ReceivedDataStructure<T>&.
     * The callback will print the message in YAML format via std::cout (also refer to uavcan::OStream).
     */
    uavcan::Subscriber<uavcan::protocol::debug::KeyValue> kv_subCAN1(*nodeCAN1);



    //const uavcan::protocol::debug::KeyValue& msg;


    const int kv_subCAN1_start_res = kv_subCAN1.start([&](const uavcan::protocol::debug::KeyValue& msg)
    {

        int error = 0;
        std::string key = "";
        unsigned char const * floatToByte;// = reinterpret_cast<unsigned char const *>(&f);

        key += msg.key[0];	//os tres primeiros caracteres informam a origem do dado
        key += msg.key[1];
        key += msg.key[2];

        //std::cout << msg << std::endl;

        if(key.compare("ref") == 0)
        RefCAN = msg.value;

	else if(key.compare("alt") == 0)				//Altitude
            Altitude = (floating) msg.value;

        else if(key.compare("tt2") == 0)				//Ambient Temperature
            Tt2_fromModel = (floating) msg.value;

        else if(key.compare("mnb") == 0)				//Initial Mach Number
            MN = (floating) msg.value;

        else if(key.compare("_d1") == 0)
        {
            model_d1 = msg.value;
            model_d1_toInt = model_d1;
        }

        else if(key.compare("_mf") == 0)
            model_mf = msg.value;

        else if(key.compare("_rs") == 0)		//reset
        {
//            // Sets the first button position to 1
//            ResetButton[0] = 1;
            // Sets Reset flag to 1
            Reset = 1;
            // Sets time base to zero - this variable tells how long the device has been operting
            upTime_ms = 0;
//            // Detects an edge in ResetButton - must be a rise edge
//            Reset = Edge(ResetButton);
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
		if(floatToByte[0] == 'c')	//Lever Mode: Control Law
			LeverMode = 1;

		else if(floatToByte[0] == 's')	//Lever Mode: Manual with reference from Supervisorio
			LeverMode = 0;

		else if(floatToByte[0] == 'p')	//Lever Mode: Manual with reference from Potentiometer
			LeverMode = 2;

//std::cout << LeverMode << std::endl;
        }


        else if(key.compare("_sk") == 0)
        {
            skipStart_float = msg.value;
            SkipStart = skipStart_float;
        }

        else if(key.compare("_au") == 0)		//authorize
        {
            authorize_float = msg.value;
            Authorize = authorize_float;
        }

        else if(key.compare("_w0") == 0)		//authorize
        {
            Wf0 = (floating) msg.value;
        }


        // else if(key.compare("_en") == 0)		//Engine
        // {
            // engine_float = msg.value;
            // WhichEngine = engine_float;
        // }

        else if(key.compare("_sm") == 0)	//Simulation Mode
        {                                       //0 = SIL, 1 = HIL Async, 2 = HIL Sync, 3 = Test Bench
            simMod_float = msg.value;
            simMod = simMod_float;

        }


//        else if(key.compare("_ps") == 0)		//pause
//        {
//            if(keyData.valueInBytes[0] == 'p')
//                PauseVariable = 1;

//            else if(keyData.valueInBytes[0] == 'c')
//                PauseVariable = 0;
//        }


	else if(key.compare("_al") == 0)
	{
		initialAltitude_float = msg.value;
		Altitude = initialAltitude_float;
	}

//	else if(key.compare("_at") == 0)
//	{
//		initialAmbientTemp_float = msg.value;
//	}

//	else if(key.compare("_en") == 0)
//	{
//		engine_float = msg.value;
//		engine = engine_float;
//	}

	else if(key.compare("_mn") == 0)
	{
		initialMachNumber_float = msg.value;
		MN = initialMachNumber_float;
	}

        // else if(key.compare("_rf") == 0)				//Initial Reference
            // reference0 = (floating) msg.value;

        else
            error = 1;	//TODO error

    });

    if (kv_subCAN1_start_res < 0)
    {
        throw std::runtime_error("Failed to start the key/value subscriber; error: " + std::to_string(kv_subCAN1_start_res));
    }


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
    //nodeCAN0->logInfo("main", "Hello world da MainBoard FADEC CAN0! My Node ID: %*",
    //             static_cast<int>(nodeCAN0->getNodeID().get()));
//    nodeCAN1.getLogger().setLevel(uavcan::protocol::debug::LogLevel::DEBUG);
//    nodeCAN1.logInfo("main", "Hello world da MainBoard FADEC CAN1! My Node ID: %*",
//             static_cast<int>(nodeCAN1.getNodeID().get()));

    std::cout << "MainBoard FADEC Operacional!" << std::endl;	//informo que a MainBoard está rodando

    sendUAVCANKeyValueMsg(nodeCAN0, "stt", 0);	//Sends STarT message to nodes, so they change from INITIALIZATION status to OPERATIONAL
    usleep(1000);
    sendUAVCANKeyValueMsg(nodeCAN0, "d12", 0);
    usleep(1000);
    sendUAVCANKeyValueMsg(nodeCAN0, "o10", 0);

/******** COPYFROM START: FADEC_LOADPARS *********/

    /* Loads the constants of chosen engine used by FADEC */
    getTJ300ARFADECSizeConst(&Alt_Elem, &MN_Elem, &Fn_Elem, &AS_Elem, &SteadyOp_Elem,
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
    getTJ300ARFADECContConst(&ContConst);

    /* Loads FADEC matrices */
    getTJ300ARFADECMtx(AMtx, ASVec, AltLinVec, BMtx, DSVec,
                     DeltaMtx, FNcMaxContMtx, FNperContMtx, MNLinVec, N_KiMtx,
                     N_KpMtx, NcFANContMtx, NcHPCMapMtx, NcVec, PRHPCMapMtx,
                     Pt3DMtx, Pt3Mtx, Pt5DMtx, Pt5Mtx, Ts0Mtx,
                     Tt4DMtx, Tt4Mtx, Tt5DMtx, Tt5Mtx, WcHPCMapMtx,
                     WfMtx, N_KpshMtx, N_KishMtx, NcFANshContMtx);

    // /* LOADING OF CONTROLLER MATRIX */

    // /* Linearization Vectors */
    // getTJ300ARAltLinVec(&AltLinVec);
    // getTJ300ARMNLinVec(&MNLinVec);
    // getTJ300ARTs0Mtx(&Ts0Mtx);
    // getTJ300ARDeltaMtx(&DeltaMtx);

    // /* Controller Gains */
	// getTJ300ARN_KpMtx(&N_KpMtx);
	// getTJ300ARN_KiMtx(&N_KiMtx);
	// getTJ300ARNcFANContMtx(&NcFANContMtx);
    // getTJ300ARFNcMaxContMtx(&FNcMaxContMtx);
	// getTJ300ARFNperContMtx(&FNperContMtx);

    // /* Reference Filter */
    // getTJ300ARASVec(&ASVec);
    // getTJ300ARDSVec(&DSVec);
    // getTJ300ARNcVec(&NcVec);

    // /* LOADING OF MODEL MATRICES */

    // getTJ300ARAMtx(&AMtx);
    // getTJ300ARBMtx(&BMtx);
    // getTJ300ARPt3DMtx(&Pt3DMtx);
    // getTJ300ARPt5DMtx(&Pt5DMtx);
    // getTJ300ARTt4DMtx(&Tt4DMtx);
    // getTJ300ARTt5DMtx(&Tt5DMtx);
    // getTJ300ARPt3Mtx(&Pt3Mtx);
    // getTJ300ARPt5Mtx(&Pt5Mtx);
    // getTJ300ARTt4Mtx(&Tt4Mtx);
    // getTJ300ARTt5Mtx(&Tt5Mtx);
    // getTJ300ARWfMtx(&WfMtx);
    // getTJ300ARPRHPCMapMtx(&PRHPCMapMtx);
    // getTJ300ARWcHPCMapMtx(&WcHPCMapMtx);
    // getTJ300ARNcHPCMapMtx(&NcHPCMapMtx);

    // getTJ300ARFADECMtx(&AMtx[0], &ASVec[0], &AltLinVec[0], &BMtx[0], &DSVec[0],
    //                   &DeltaMtx[0], &FNcMaxContMtx[0], &FNperContMtx[0], &MNLinVec[0], &N_KiMtx[0],
    //                   &N_KpMtx[0], &NcFANContMtx[0], &NcHPCMapMtx[0], &NcVec[0], &PRHPCMapMtx[0],
    //                   &Pt3DMtx[0], &Pt3Mtx[0], &Pt5DMtx[0], &Pt5Mtx[0], &Ts0Mtx[0],
    //                   &Tt4DMtx[0], &Tt4Mtx[0], &Tt5DMtx[0], &Tt5Mtx[0], &WcHPCMapMtx[0],
    //                   &WfMtx[0]);

/******** COPYFROM END: FADEC_LOADPARS *********/

    /* LOADING OF CONTROLLER STARRING PARAMETERS */
    //getTJ1200StartPars(&ContStart);

    /*---------------------------------------------*/
    /* INITIATES REFERENCE COMMAND WITH IDLE VALUE */
    /*---------------------------------------------*/

//	RefCAN = ContConst.FNIdle;      //DESCOMENTAR DEPOIS!!!

      /* Thermocouple value when opened */
      TCOpen = ContConst.TCOpen;           //RETIRAR DEPOIS!!!

//printf("teste0 = %f\n",ContStart.FuelInit);

//    /* LOADING OF CONTROLLER STARRING PARAMETERS */
//    getTJ1200StartPars(&ContStart);

//floating teste = TJ1200_RPM_RAMP_CHANGE;
//ContStart.FuelInit = TJ1200_FUEL_INIT;
//printf("teste = %f\n",ContStart.RPMRampChange);
//printf("teste1 = %f\n",ContStart.FuelInit);
//printf("Tempo antes da rampa = %f s\n",ContStart.TimeBeforeRamp);
//printf("Tt4 min antes da rampa = %f K\n",ContStart.Tt4MinBeforeRamp);


    /* Reset variable must be set to 0 in order for inner
    * loop not to reset the timer consecutively */
    Reset = 0;

/********************************************************************************************************************************/
/*                                                                                                                              */
/********************************************************************************************************************************/

    /**************************** INITIALIZING THREAD TO SEND AND RECEIVE MESSAGES ON CAN1, AND THREAD TO SAVE TELEMETRY FILE **********************************************/

//    std::cout << "Create Thread:" << strerror(pthread_create(&thread_ATDPOC_CANmsg_send_rcv, NULL, thread_ATDPOC_CANmsg_send_rcv_fcn, (void*) can_atd_poc)) << std::endl;
//    std::cout << "Create Thread:" << strerror(pthread_create(&thread_saveFile, NULL, thread_telemetry_saveFile, (void*) can_atd_poc)) << std::endl;

    std::cout << "Create Thread:" << strerror(pthread_create(&thread_ATDPOC_CANmsg_send_rcv, NULL, thread_ATDPOC_CANmsg_send_rcv_fcn, (void*) can_atd_poc)) << std::endl;

    std::cout << "Create Thread:" << strerror(pthread_create(&thread_telemetry_updateFile, NULL, thread_telemetry_updateFile_fcn, (void*) can_atd_poc)) << std::endl;

    std::cout << "Create Thread:" << strerror(pthread_create(&thread_telemetry_syncFile, NULL, thread_telemetry_syncFile_fcn, (void*) can_atd_poc)) << std::endl;



    /********************************************************************************************************************************/
    /*																																*/
    /*												OUTER LOOP                             									 	*/
    /*																																*/
    /********************************************************************************************************************************/
        /*
         * Node loop.
         * The thread should not block outside Node::spin().
         */

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

        if(can1_currentProtocol == UAVCAN)
        {
           nodeCAN1->setModeOperational();
           int spinCAN1_res = nodeCAN1->spinOnce();
           if (spinCAN1_res < 0)
           {
               std::cerr << "Transient failure: " << spinCAN1_res << std::endl;
           }
        }

        else
        {
            nodeCAN1->setModeInitialization();
        }


        /* Resets static structs and variables */
        digital = digitalEmpty;
        Current_key_start = 0;
        Old_key_start = 0;
        //fValue = 0;
        Wf = 0;

//        /* Disable controller actuation until authorized by model */
//        Authorize = 0;

        /* Indicates reset request to the controller */
        //ContInput.Reset = 1;

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

            fadecSensorsDataFile << "RESET" << std::endl; //Adds a line informing that a reset has been executed
printf("Resetado!\n");

        }

/******** REPLACE START: getTJ1200ContConst BY getTJ1200FADECContConst *********/
    /* LOADING OF CONTROLLER CONSTANTS */
      getTJ200FADECContConst (&ContConst);   //QUAL O MOTIVO DE CHAMAR AQUI DE NOVO??
/******** REPLACE END: getTJ1200ContConst BY getTJ1200FADECContConst *********/

//        /* Sets reset flag to 0 */
//        Reset = 0;
//reset_command_ATDPOC(can_atd_poc);  //after resetting FADEC, sends the reset command to Model

      upTime_ms = 0;

//        sendUAVCANKeyValueMsg(nodeCAN1, "_tk", TICK);	//Sends the TICK value for Engine Model, used in HIL Sync Mode

      monotonicTimer_initialValue = nodeCAN0->getMonotonicTime();     //initial value of monotonic value to calculate uptime of the node.

/********************************************************************************************************************************/
/*																																*/
/*												INNER LOOP                                									 	*/
/*																																*/
/********************************************************************************************************************************/

        while(1)	//inner loop
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

            if(can1_currentProtocol == UAVCAN)
            {
                if( upTime_ms < (lastUpdateTime_ms + UPDATE_TIMERATE_MS - 6) )  //runs nodespin() until 6ms before the next update cycle.
                {
                    int spinCAN1_res = nodeCAN1->spin(uavcan::MonotonicDuration::fromMSec(2));
                    if (spinCAN0_res < 0)
                    {
                        std::cerr << "Transient failure: " << spinCAN1_res << std::endl;
                    }
                }

            }



            if ( upTime_ms >= (lastUpdateTime_ms + UPDATE_TIMERATE_MS) )
            {
//std::cout << upTime_ms << std::endl;
                lastUpdateTime_ms = upTime_ms;
                sendUAVCANKeyValueMsg(nodeCAN0,"upd", (float) upTime_ms);

                spinCAN0_res = nodeCAN0->spin(uavcan::MonotonicDuration::fromMSec(15));    //spins again to wait for response of uavcan nodes
                if (spinCAN0_res < 0)
                {
                    std::cerr << "Transient failure: " << spinCAN0_res << std::endl;
                }

                ControlUpdate(nodeCAN0, nodeCAN1, can_atd_poc);

                //sendUAVCANKeyValueMsg(nodeCAN0,"_sy", (float) upTime_ms);

                flag_writeSensorsDataFile = 1;      //flag to indicate that the data file must be updated
//std::cout << (float) FaultStatus.FaultBits << std::endl;

            }

            if(Reset == 1)
            {
                upTime_ms = 0;
                lastUpdateTime_ms = 0;      //clears the last time the model was updated.

                clock_gettime(CLOCK_MONOTONIC, &initialTime);   //resets the initial time for ATDPOC thread, so upTime_sendATDPOCmsg_ms becomes near zero on next calculation inside the thread.
                last_sendATDPOCmsg_ms = 0;

                last_saveTelemetryFile_ms = 0;


                /* Breaks the current  while loop */
                break;
            }

        }   //END OF while(1)	//inner loop




    }   //END OF while (true)	//outer loop

    /********************************************************************************************************************************/
    /*																																*/
    /*                                                END OF MAIN                              									 	*/
    /*																																*/
    /********************************************************************************************************************************/

}   //END OF int main(int argc, const char** argv)


//void ControlUpdate(Node& node0, Node& node1)
void ControlUpdate(uavcan_linux::NodePtr& node0, uavcan_linux::NodePtr& node1, int can_atd_poc)
{
    /* ================================================================================= */
    /* THE FOLLOWIN CODE MUST BE EXECUTED BY A TIMER ROUTINE OF THE HARDWARE IN THE LOOP */
    /* ================================================================================= */

    /* ------------------------------------------------------------------------------------------ */
    /* INPUT READING - Make sure to use the appropriate piece of code: MATLAB or actual hardware  */
    /* ------------------------------------------------------------------------------------------ */

    /* ACTUAL HARDWARE  */

    /* ---------------------------------------------- */
    /* INPUT READINS FOR CONTROL LAW CALCULATION      */
    /* ---------------------------------------------- */

//    Tt2 = Tt2_fromModel;			//from supervisorio/model (CAN1)
//    Pt3 = i13 * 100000;             //from input boards	(CAN0), converting from bar to pascal (1 bar = 100000 pascal) - USED ON FIRST TEST
//    Tt5 = (t12+t13)/2;              // two tt4 sensors
//    RPM = r11;
//    POil = 2;                       //from input boards	(CAN0)

//    /*-------------------------*/
//    /* RESET REQUEST TREATMENT */
//    /*-------------------------*/

//    //TESTE INICIO!!!!

//    if(ResetButton[0] == 1)
//    {
//        int teste = 1;
//        teste = 1;
//    }

//    //TESTE FIM!!!

//    /* Reads reset signal */
//    //Reset = Edge(ResetButton);	//this command has been moved to CAN message reception, under reset ("_rs") message
//    //ResetButton[1] = ResetButton[0];
//    ResetButton[0] = 0;

    /*--------------------------------------------------------------------------*/
    /* VERIFIES IF FLIGHT HIL SIMULATOIN WITH CRUISE INITIAL IS BEING PERFORMED */
    /*--------------------------------------------------------------------------*/
//printf("loopSkip=%d, SttComp=%d\n", SkipStart, StartComplete);

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

    //if(RefCAN < 0.0001 & LeverMode == 1 & EngUnits == 1) /* ESSE IF É PROVISÓRIO  PARA O TESTE NA BANCADA */
//{
//FNpc = FNIdle;
////printf("Entrou no if\n");
//}
//printf("ControlUpdate: FNpc=%f   RefCAN=%f\n", FNpc, RefCAN);

/* Reads the potentiomenter value if LeverMode == 2 */
	if(LeverMode == 2){
        //FNpc = pot_percent;
        FNpc = valorManete / 100.0;   //converts the range from 0%-100% to 0-1

		if(!keys.bits.ac_drive_key == 0)
			FNpc = 0;
//printf("FNpc on if(LeverMode==2) = %f\n", FNpc);

	}

//std::cout << FNpc << std::endl;

    /*if(FNpc == 0.5){
        int testando = 1;
        testando = 0;
    }*/

//    /* -------------------------------------------------- */
//	/* SENSOR READING - TMATS & PWLM                      */
//	/* (To be usedi in MATLAB and TMATS simulations only) */
//	/* -------------------------------------------------- */

//    Sensors.Ts2[0] = InputSensors[0];
//    Sensors.Ts2[1] = InputSensors[1];
//    Sensors.Pt3[0] = InputSensors[2];
//    Sensors.Tt4[0] = InputSensors[3];
//    Sensors.Tt4[1] = InputSensors[4];
//    Sensors.Tt4[2] = InputSensors[5];
//    Sensors.RPM[0] = InputSensors[6];
//    Sensors.RPM[1] = InputSensors[7];
//    Sensors.POil[0] = InputSensors[8];
//    Sensors.PFuel[0] = InputSensors[9];
//    Sensors.Vibration[0] = InputSensors[10];
//    Sensors.TBear[0] = InputVars[19];
//    Sensors.TBear[1] = InputVars[20];
//    Sensors.TBear[2] = InputVars[21];

    //Sensors.Ts2[0] = t11;
    //Sensors.Ts2[1] = t11;

    //FADEC de laboratório
//    Sensors.Ts2[0] = Ts2_fromModel;
//    Sensors.Ts2[1] = Ts2_fromModel;
//    Sensors.Pt3[0] = i13 * 100000;  //converts from 0-5V, which is 0-5bar, to 0-500000 Pa
//    Sensors.Tt4[0] = t12;
//    Sensors.Tt4[1] = t13;
//    Sensors.Tt4[2] = t14;
//    Sensors.RPM[0] = r11;
//    Sensors.RPM[1] = r11;
//    Sensors.POil[0] = TJ1200_POILMODEL;
//    Sensors.PFuel[0] = TJ1200_PFUELMODEL;
//    Sensors.Vibration[0] = TJ1200_VIBMODEL;

    //FADEC de voo
    //Sensors.Ts2[0] = Ts2_fromModel;
   // Sensors.Ts2[1] = Ts2_fromModel;

    /*Sensors.Pt3[0] = i10 * 100000;  //converts from 0-5V, which is 0-5bar, to 0-50,0000 Pa
    Sensors.Vibration[0] = i11 * 10;     //IMPORTANT! scale the input correctly! Actually is 0~5V to 0~50mm/s
    Sensors.PFuel[0] = i12 * 2000000;    //converts from 0-5V, which is 0-100bar, to 0-10,000,000 Pa
    Sensors.POil[0] = i13 * 200000; //converts from 0-5V, which is 0-10bar, to 0-1,000,000 Pa*/

    Sensors.Ts2[0] = t10;
    Sensors.Ts2[1] = t11;

    Sensors.Pt3[0] = (i10 - 1) * 250e+03 + ModelPars.Ps2;   //[PA]        //scaling: Sensor is 4~20mA and 0~10bar (0~1000000Pa). The current is converted to 1~5V and transmitted via CAN.
                                                                            //Converting 1~5V to 0~1000000Pa: POil = (Voltage - 1) * MaxRange/(4 Volts) = (Voltage - 1) * 1000000/4 = (Voltage - 1) * 250000
//printf("Sensors.Pt3[0]	 = (i10	 - 1) * 250e+03	 + ModelPars.Ps2\n");
//printf("%f	 = (%f	 - 1) * 250e+03	 + %f\n", Sensors.Pt3[0], i10, ModelPars.Ps2);

    Sensors.Vibration[0] = (i11 - 1) * 12.5; //[mm/s]   //scaling: Sensor is 4~20mA and 0~50mm/s. The current is converted to 1~5V and transmitted via CAN.
                                                        //Converting 1~5V to 0~50mm/s: Vib = (Voltage - 1) * MaxRange/(4 Volts) = (Voltage - 1) * 50/4 = (Voltage - 1) * 12.5

    Sensors.PFuel[0] = (i12 - 1) * 4e+06; //[PA]        //scaling: Sensor is 4~20mA and 0~160bar (0~16000000Pa). The current is converted to 1~5V and transmitted via CAN.
                                                        //Converting 1~5V to 0~16000000Pa: PFuel = (Voltage - 1) * MaxRange/(4 Volts) = (Voltage - 1) * 16000000/4 = (Voltage - 1) * 4000000

    Sensors.POil[0] = (i13 - 1) * 250e+03; //[PA]       //scaling: Sensor is 4~20mA and 0~10bar (0~1000000Pa). The current is converted to 1~5V and transmitted via CAN.
                                                        //Converting 1~5V to 0~1000000Pa: POil = (Voltage - 1) * MaxRange/(4 Volts) = (Voltage - 1) * 1000000/4 = (Voltage - 1) * 250000

    //Test bench and HIL sensors
    /*Sensors.Tt4[0] = t12;
    Sensors.Tt4[1] = t13;
    Sensors.Tt4[2] = t14;*/

    //POC sensors
    Sensors.Tt4[0] = t12;
    Sensors.Tt4[1] = t13;
    Sensors.Tt4[2] = t14;

    //Bearings sensors
    Sensors.TBear[0] = t15;
    Sensors.TBear[1] = t16;
    Sensors.TBear[2] = t17;


    Sensors.RPM[0] = r11;
//Sensors.RPM[1] = r11;       //for now, on testbench there is only one rpm sensor, so the same value will be used on both channels
    Sensors.RPM[1] = r12;

/*******************************************************************/
/*ACRESCENTAR LEITURA DE SENSORES DE TEMPERATURA DO ROLAMENTO!!!!!!*/
/*******************************************************************/


//printf("Sensors: Ts2[0]=%.2f ; Ts2[1]=%.2f ; Pt3[0]=%.2f ; Tt4[0]=%.2f ; Tt4[1]=%.2f ; Tt4[2]=%.2f\n", Sensors.Ts2[0], Sensors.Ts2[1], Sensors.Pt3[0], Sensors.Tt4[0], Sensors.Tt4[1], Sensors.Tt4[2]);
//printf("Sensors: RPM[0]=%.2f ; RPM[1]=%.2f ; PPOil[0]=%.2f ; PFuel[0]=%.2f ; Vibration[0]=%.2f\n\n", Sensors.RPM[0], Sensors.RPM[1], Sensors.POil[0], Sensors.PFuel[0], Sensors.Vibration[0]);
// printf("t1B=%.01f	 t1c=%.01f	 t1D=%.01f\n\n", t1B, t1C, t1D);

//    printf("Ts2: Ts2[0]=%f ; Ts2[1]=%f ;\n", Sensors.Ts2[0], Sensors.Ts2[1]);
//    printf("Pt3: Pt3[0]=%f ; \n", Sensors.Pt3[0]);
//    printf("Tt4: Tt4[0]=%f ; Tt4[1]=%f ; Tt4[2]=%f ;\n", Sensors.Tt4[0], Sensors.Tt4[1], Sensors.Tt4[1]);
//    printf("RPM: RPM[0]=%f ; RPM[1]=%f ;\n", Sensors.RPM[0], Sensors.RPM[1]);
//    printf("POil: POil[0]=%f ; \n", Sensors.POil[0]);
//    printf("PFuel: PFuel[0]=%f ; \n", Sensors.PFuel[0]);
//    printf("Vib: Vibration[0]=%f ; \n\n\n", Sensors.Vibration[0]);

//    /* Reads word containing faults simulated by siftware - DEVE LER UNION QUE O SUPERVISÓRIO MANDA CONTENDO AS FALHAS */
//    SoftSimFaults.FaultBits = (uint64_t)InputFaults[0];

//    /* -------------------------------------------------- */

    /*--------------------------------------------*/
    /* THERMOCOUPLE FAULT SIMULATION VIA SOFTWARE */
    /*--------------------------------------------*/

    /* Thermocouple fault simulation */
//    TCFault(&Sensors, &SoftSimFaults, &Ts2_0, &Ts2_1, &Tt4_0, &Tt4_1, &Tt4_2, TCOpen);

    /*------------------*/
    /* REAL ENGINE MODE */
    /*------------------*/

    /* If Simulation Mode is "Test Bench", then there is no need to wait for authorize from Model */
    if (simMod == 3)
    {
        Authorize = 1;
    }

    /*---------------*/
    /* CONTROL LOGIC */
    /*---------------*/

    //    /* -------------------------------------------------- */
    //    /* EXTERNAL SAMPLING TIME - TMATS & PWLM              */
    //    /* (To be usedi in MATLAB and TMATS simulations only) */
    //    /* -------------------------------------------------- */

    //    Authorize = 0;
    //    if (tick != tack) {
    //        Authorize = 1;
    //    }

    //    /*----------------------------------------------------*/

    /* Checks for authorization of controller calculations */
    if(Authorize == 1)
    {

        /* -------------------------------------------------- */
        /* SIMULATION OF GPIO PINES - TMATS & PWLM            */
        /* (To be usedi in MATLAB and TMATS simulations only) */
        /* -------------------------------------------------- */

        /* Simulates reading from each GPIO pin */
//        keys.in = GPIOIn & 0x7FF;

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
 //HardFAuthorize.FaultBits = 0;

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
        /* END OF SSModelLoop.c AND PIMMRF_TJ300AR.c IDENTICAL CODE PIECE */
        /*                                                               */
        /* NOTE: The codes are to be identical except for the considera- */
        /*       tions mentioned at the note above                       */
        /*===============================================================*/

/******** COPYFROM END: FADEC_AUTHORIZE3 *********/

    }



int teste = 0;

//IMPORTANT! For closed loop pump control: FADEC will send the fuel flow instead of voltage.
//The Analog board will convert this value according to number of poles of BLDC and volume per revolution of the pump

//        float pump_flowToVoltage = (Wf/TJ1200_WFMAX);//(fValue/TJ1200_WFMAX);		//converts 0~max fuel pump flow to 0~5V
//    //printf("ControUpdate: Wf = %f", Wf);

//        pump_flowToVoltage = pump_flowToVoltage * 5;	//converts 0~max fuel pump flow to 0~5V
//    //printf("Wf = %f, WfMax = %f, pump_flowToVoltage = %f\n", Wf, TJ1200_WFMAX, pump_flowToVoltage);
//        sendUAVCANKeyValueMsg(node0, "o10", pump_flowToVoltage);
//    //printf("FuelPump = %f    ||     ", pump_flowToVoltage);

    if(flag_tj200_selected == 1) //if TJ-200 is selected
    {
        sendUAVCANKeyValueMsg(node0, "o12", (Wf/0.1669)*100);   //converts the wf value to percentage. Wfmax=0.1669kg/s
        usleep(1000);


        /*sendUAVCANKeyValueMsg(node0, "o13", rcpwm_startMotor_TJ200);*/
        sendUAVCANKeyValueMsg(node0, "o13", ContStart.StrtRPMAct);
        usleep(1000);

    //printf("Fuel=%f	StartMotor=%f\n", (Wf/0.1669)*100, ContStart.StrtRPMAct);
    }

    sendUAVCANKeyValueMsg(node0, "o10", Wf);
//printf("FuelPump = %f    ||     ", pump_flowToVoltage);
    usleep(1000);

//sendUAVCANKeyValueMsg(node0, "o11", i10);   //APENAS PARA AFERIÇÃO DO SINAL NECESSÁRIO PARA QUE A BOMBA DE ÓLEO DÊ 5 BAR.
//printf("OilPump = %f\n", i10);

/*float oilPump_volts = 0;     //se RPM menor que windmill, sem óleo
if(RPM > 2000)
{
    oilPump_volts = 1.5;//Mairum disse que está indo muito óleo para a partida, então diminui para 1.5. Lembrando que abaixo de 1 (20%) nem gira a bomba. //2;      //se RPM menor que idle, 1 bar
}
if(RPM > 20000)
{
    //oilPump_volts = 3.75;//5;       //max oil pum. On 5V, the oil pump runs on 12000 RPM, but the max is 9000 RPM, that is why the max value must be 3.75, which corresponds to 9000 RPM.
    oilPump_volts = 3;              //max oil pump changed to 80% of 3.75V.
}
sendUAVCANKeyValueMsg(node0, "o11", oilPump_volts);
//sendUAVCANKeyValueMsg(node0, "o12", oilPump_volts); //IMPORTANT! As the IC is burned, for now o12 will be used!
printf("OilPump = %f\n", oilPump_volts);*/
//printf("oilRPM_ref=%f\n", oilRPM_ref);



    sendUAVCANKeyValueMsg(node0, "o11", OPRPM);
//printf("OPRPM=%f\n", OPRPM);
    usleep(1000);
//printf("Digital IN = %d\n", keys.in);
    sendUAVCANKeyValueMsg(node0, "d12", (float) digital.out);
    usleep(1000);

    //IMPORTANT! The Flight Version FADEC uses the PLC output to activate Exciter and Shot Off Valve.
    //In order to keep the compatibility with the Laboratorial FADEC, both messages will be sent: the PLC output and low power digital output ("d12" message).
    //PLC Outputs for this version are:
    //O1 and O2 - Exciter
    //O7 and O8 - Shut Off Valve
    //O3, O4, O5, O6 - not used
    //For Exciter and Shut Off Valve there are already functions to turn on and off PLC Output:
    //SetExciter(int) and SetSOV(int).
    //So:
    //- if O1 and/or O2 (bits 0 and 1) is set to ON state on "d13" message, the SetExciter(int) will be called.
    //- if O7 and/or O8 (bits 6 and 7) is set to ON state on "d13" message, the SetSOV(int) will be called.
    plcOutputs = 0;
    if(flag_tj200_selected == 1) //if TJ-200 is selected
    {
        /*plcOutputs = !digInputs_TJ200_fromSupervisorio.value.vela << 2 |                //need to innvert the input, because the key is activated in 0
                     !digInputs_TJ200_fromSupervisorio.value.valvula_vela << 3 |
                     !digInputs_TJ200_fromSupervisorio.value.valvula_combustivel << 4;*/
//printf("plc=%d\n", digital.out);
        plcOutputs =    digital.bits.igniter << 2 |                //need to innvert the input, because the key is activated in 0
                        digital.bits.ignSOV << 3 |
                        digital.bits.solenoid << 4;
    }

    else
    {
        if(digital.bits.solenoid)
            plcOutputs |= 0xC0;     //0b1100 0000, turning ON O7 and O8 PLC outputs
        if(digital.bits.igniter)
            plcOutputs |= 0x3;      //0b0000 0011, turning ON O1 and O2 PLC outputs
    }
    sendUAVCANKeyValueMsg(node0, "d13", (float) plcOutputs);       //PLC outputs
    usleep(1000);


    sendUAVCANKeyValueMsg(node0, "_fs", (float) EngStatus.EngineStatus);    //sends Fadec Status, the same value of FADEC_STATUS OBC message


//if(RPMFuelPump < 0)
//{
//    printf("time in ms = %d\n", upTime_ms);
//}
//printf("RPMFuel = %0.1f 	RPMOil = %0.1f\n", RPMFuelPump, RPMOilPump);
//printf("ColdJunction = %0.1f\n", (t1a + t1b + t1c + t1d + t1e + t1f + t1g + t1h) / 8);

    /* Messages to Supervisorio/Model */
    if(can1_currentProtocol == UAVCAN)
    {
        sendUAVCANKeyValueMsg(node1, "i10", i10);	//send to Supervisorio the value of Potentiometer in Volts (0~5V)
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "i11", i11);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "i12", i12);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "i13", i13);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "t10", t10);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "t11", t11);	//send to Supervisorio the value of Thermocouple 1
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "t12", t12);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "t13", t13);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "t14", t14);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "t15", t15);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "t16", t16);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "t17", t17);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "r11", r11);	//send to Supervisorio the value of rpm channel 1
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "r12", r12);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "d12", (float) digital.out);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "d11", (float) keys.in);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "o10", Wf);	//Fuel flow command
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "o11", OPRPM);	//Oil Pump command
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "o12", 0);     //not used
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "o13", 0);     //not used
        usleep(1000);

        sendUAVCANKeyValueMsg(node1, "rpo", RPMOilPump);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "rpf", RPMFuelPump);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "_cj", (t1a + t1b + t1c + t1d + t1e + t1f + t1g + t1h) / 8);   //average of cold junction
        usleep(1000);

        sendUAVCANKeyValueMsg(node1, "db1", ContOutput.Active); //debug value 1
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "db2", ContInput.FNpc);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "db3", ModelParsCL.RPM);
        usleep(1000);
        sendUAVCANKeyValueMsg(node1, "db4", Wf);
        usleep(1000);
    }

//    if(Mode == 0)
//        sendUAVCANKeyValueMsg(node1, "act", (float) ContOutput.Active);	//send to Supervisorio the active controller

//    sendUAVCANKeyValueMsg(node1, "o1a", o1a);	//send to Supervisorio the value of Potentiometer in Volts (0~5V)
//    sendUAVCANKeyValueMsg(node1, "_cj", t1d);	//send the cold junction temperature to Model Board, to use on thermocouple simulation




}

