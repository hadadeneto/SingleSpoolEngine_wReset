#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <uavcan/uavcan.hpp>

/*
 * We're going to use messages of type uavcan.protocol.debug.KeyValue, so the appropriate header must be included.
 * Given a data type named X, the header file name would be:
 *      X.replace('.', '/') + ".hpp"
 */
#include <uavcan/protocol/debug/KeyValue.hpp> // uavcan.protocol.debug.KeyValue
#include <uavcan/protocol/debug/LogMessage.hpp>

#include <math.h>

/********* parte que eu estou adicionando para enviar a string via serial *************/
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
/*Common includes for both model and controller*/
#include "ModelCFunc/MtxIntFunctions.h"
#include "ModelCFunc/Interpolation_Types.h"
#include "ModelCFunc/LinMtxFunctions.h"
#include "ModelCFunc/Env_SampTime.h"

/* Includes concerning TJ1200 engine */
#include "PIMinMaxTJ1200.h"
#include "ConstantsTJ1200.h"

/* Controller includes */
#include "ModelCFunc/Control_Types.h"
#include "ModelCFunc/ControlFunctions.h"
#include "ModelCFunc/IO_Types.h"
#include "ModelCFunc/StartingFunctions.h"
#include "ModelCFunc/DigitalOutDefs.h"

#include "ModelCFunc/getTJ1200.h"

}

/******************************************************************************************/

/*-------------------------*/
/* COMMUNICATION VARIABLES */
/*-------------------------*/

//declaração das variáveis das leituras recebidas via UAVCAN
float   i10, i11, i12, i13,                         // Analog Inputs
        o1a, o1b, o1c, o1d,                         // Loopback from Analog Outputs: 1=a, 2=b, 3=c, 4=d
        t11, t12, t13, t14, t15, t16, t17, t18,     // Thermocouple Temperature Value
        t1a, t1b, t1c, t1d, t1e, t1f, t1g, t1h,     // Thermocouple Cold Juntion Value: 1=a, 2=b, ... , 8=h
        d11_float, d21_float,                       // entradas digitais no formato float, posterior convers�o para int
        r11, r12,                                   // valor do RPM-A e RPM-B
        model_d1, model_mf,							// variaveis do modelo
	dT, Tt2_fromModel,					//temperatura ambiente, sendo a variação dT em relação a 288.15 K
	pot_percent;					//porcentagem do potênciometro (manete)
float 	reference = 0.45;
float 	authorize_float, skipStart_float,	//receives the initial values and commands on float format, for later conversion to int
        initialAltitude_float, initialdT_float, engine_float, initialMachNumber_float, initialReference_float, simMod_float, simMod;
unsigned int model_d1_toInt = 0;	//converts the float number corresponding to digital inputs to integer
unsigned int upTime_ms =  0;	//the upTime_ms variable measures the time since the system has been started in miliseconds
                                //and sends on "upd" keyValue message


/* ------------------------------ */
/* DECLARATION OF FADEC VARIABLES */
/* ------------------------------ */

/* STARTING ROUTINE */

/* Starting Routine Structs */
static digital_t digital;
static const digital_t digitalEmpty = { 0 };
keys_t keys;
static const keys_t keysEmpty = { 0 };

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

/* Operating Mode */
int Mode = 0;

/* Lever Mode */
int LeverMode = 1;

/* Starting keys and flag */
static int Current_key_start;
static int Old_key_start;

/* CLOSED-LOOP ROUTINE - SOFTWARE IN THE LOOP */

/* Declares structures for controller input and controller output */
ControlStart ContStart;
static const ControlStart ContStartEmpty = { 0 };
ControllerInput ContInput;
static const ControllerInput ContInputEmpty = { 0 };
ControllerOutput ContOutput;
static const ControllerOutput ContOutputEmpty = { 0 };

/* COMMONLY USED VARIABLES */

double FNpc = 0;
double RefCAN = 0;
static double fValue = 0;
unsigned int keysWord;
unsigned int digitalWord;

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
double N_KiMtx[TJ1200_TOTAL_ELEM];
double N_KpMtx[TJ1200_TOTAL_ELEM];
/* Matrices used for reference calculations */
double NcFANContMtx[TJ1200_TOTAL_ELEM];
double FNperContMtx[TJ1200_TOTAL_ELEM];

/* Sampling Time */
double Tsample = 0.001 * TICK;

/****************************************************************************************/


/********************************************************************************************************************************/
/*																																*/
/*									DECLARAÇÃO DAS FUNÇÕES DOS NÓS UAVCAN          											 	*/
/*																																*/
/********************************************************************************************************************************/

/**
 * These functions are platform dependent, so they are not included in this example.
 * Refer to the relevant platform documentation to learn how to implement them.
 */
extern uavcan::ICanDriver& getCanDriverCAN0();
extern uavcan::ICanDriver& getCanDriverCAN1();
extern uavcan::ISystemClock& getSystemClock();

/**
 * Memory pool size largely depends on the number of CAN ifaces and on application's logic.
 * Please read the documentation for the class uavcan::Node to learn more.
 */
constexpr unsigned NodeMemoryPoolSize = 16384;

typedef uavcan::Node<NodeMemoryPoolSize> Node;

/**
 * Node object will be constructed at the time of the first access.
 * Note that most library objects are noncopyable (e.g. publishers, subscribers, servers, callers, timers, ...).
 * Attempt to copy a noncopyable object causes compilation failure.
 */

static Node& getNodeCAN0()
{
    static Node nodeCAN0(getCanDriverCAN0(), getSystemClock());
    return nodeCAN0;
}

static Node& getNodeCAN1()
{
    static Node nodeCAN1(getCanDriverCAN1(), getSystemClock());
    return nodeCAN1;
}

void sendUAVCANKeyValueMsg(Node& node, char keyID[3], float value);

void ControlUpdate(Node& node0, Node& node1);

int main(int argc, const char** argv)
{
    if (argc < 2)
    {
        std::cerr << "Usage: " << argv[0] << " <node-id>" << std::endl;
        return 1;
    }

    const int self_node_id = std::stoi(argv[1]);

/********************************************************************************************************************************/
/*																																*/
/*												CRIAÇÃO DOS NÓS UAVCAN          											 	*/
/*																																*/
/********************************************************************************************************************************/

    /*
     * Node initialization.
     * Node ID and name are required; otherwise, the node will refuse to start.
     * Version info is optional.
     */
    auto& nodeCAN0 = getNodeCAN0();
    auto& nodeCAN1 = getNodeCAN1();

    nodeCAN0.setNodeID(self_node_id);
    nodeCAN0.setName("FADEC_CAN0");

    nodeCAN1.setNodeID(self_node_id);
    nodeCAN1.setName("FADEC_CAN1");

    uavcan::protocol::SoftwareVersion sw_version;  // Standard type uavcan.protocol.SoftwareVersion
    sw_version.major = 1;
    nodeCAN0.setSoftwareVersion(sw_version);
    nodeCAN1.setSoftwareVersion(sw_version);

    uavcan::protocol::HardwareVersion hw_version;  // Standard type uavcan.protocol.HardwareVersion
    hw_version.major = 1;
    nodeCAN0.setHardwareVersion(hw_version);
    nodeCAN1.setHardwareVersion(hw_version);

    /*
     * Start the node.
     * All returnable error codes are listed in the header file uavcan/error.hpp.
     */
    const int nodeCAN0_start_res = nodeCAN0.start();
    if (nodeCAN0_start_res < 0)
    {
        throw std::runtime_error("Failed to start the node; error: " + std::to_string(nodeCAN0_start_res));
    }

    const int nodeCAN1_start_res = nodeCAN1.start();
    if (nodeCAN1_start_res < 0)
    {
        throw std::runtime_error("Failed to start the node; error: " + std::to_string(nodeCAN1_start_res));
    }


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
    uavcan::Subscriber<uavcan::protocol::debug::LogMessage> log_sub(nodeCAN0);

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
/*												RECEPÇÃO DE MENSAGENS KEYVALUE CAN0											 	*/
/*																																*/
/********************************************************************************************************************************/

    /*
     * Subscribing to messages of type uavcan.protocol.debug.KeyValue.
     * This time we don't want to receive extra information about the received message, so the callback's argument type
     * would be just T& instead of uavcan::ReceivedDataStructure<T>&.
     * The callback will print the message in YAML format via std::cout (also refer to uavcan::OStream).
     */
    uavcan::Subscriber<uavcan::protocol::debug::KeyValue> kv_subCAN0(nodeCAN0);

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
		pot_percent = i10/5;
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

	else if(key.compare("t11") == 0)
		t11 = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t12") == 0)
		t12 = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t13") == 0)
		t13 = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t14") == 0)
		t14 = msg.value;	//converts from Celsius to Kelvin
		
	else if(key.compare("t15") == 0)
		t15 = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t16") == 0)
		t16 = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t17") == 0)
		t17 = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t18") == 0)
		t18 = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t1a") == 0)
		t1a = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t1b") == 0)
		t1b = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t1c") == 0)
		t1c = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t1d") == 0)
		t1d = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t1e") == 0)
		t1e = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t1f") == 0)
		t1f = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t1g") == 0)
		t1g = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("t1h") == 0)
		t1h = msg.value;	//converts from Celsius to Kelvin

	else if(key.compare("d11") == 0)
	{
		d11_float = msg.value;

		unsigned int d11_int = d11_float;		//transformo o float em int

		/*keys.bits.emergency_key = (d11_int >> 2) & 1;
		keys.bits.mode_key = (d11_int >> 3) & 1;
		keys.bits.igniter_key = (d11_int >> 5) & 1;
		keys.bits.shut_off_key = (d11_int >> 6) & 1;
		keys.bits.scaveng_key = (d11_int >> 7) & 1;
		keys.bits.oil_pump_key = (d11_int >> 8) & 1;
		keys.bits.ac_drive_key = (d11_int >> 9) & 1;*/

		keys.bits.igniter_key = d11_int & 1;
		keys.bits.shut_off_key = (d11_int >> 1) & 1;
		keys.bits.scaveng_key = (d11_int >> 2) & 1;
		keys.bits.oil_pump_key = (d11_int >> 3) & 1;
		keys.bits.ac_drive_key = (d11_int >> 4) & 1;
		keys.bits.emergency_key = (d11_int >> 5) & 1;
		keys.bits.mode_key = (d11_int >> 6) & 1;



	}

	else if(key.compare("d21") == 0)
	{
		d21_float = msg.value;
	}

	else if(key.compare("r11") == 0)
		r11 = msg.value;

	else if(key.compare("ref") == 0)
		reference = msg.value;

	else if(key.compare("_mo") == 0)		//authorize
	{
		floatToByte = reinterpret_cast<unsigned char const *>(&msg.value);
		if(floatToByte[0] == 'a')
			Mode = 0;

		else if(floatToByte[0] == 'm')
			Mode = 1;
	}

	else if(key.compare("_lm") == 0)		//authorize
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

	/*else if(key.compare("_al") == 0)
	{
		initialAltitude_float = msg.value;
		Altitude = initialAltitude_float;
	}

	else if(key.compare("_at") == 0)
	{
		initialAmbientTemp_float = msg.value;
		Tt2 = initialAmbientTemp_float;
	}

	else if(key.compare("_en") == 0)
	{
		engine_float = msg.value;
		engine = engine_float;
	}

	else if(key.compare("_mn") == 0)
	{
		initialMachNumber_float = msg.value;
		MN = initialMachNumber_float;
	}*/

	else if(key.compare("_rf") == 0)
	{
		initialReference_float = msg.value;
		RefCAN = initialReference_float;
	}

	/*else if(key.compare("_ps") == 0)		//pause
	{
		if(keyData.valueInBytes[0] == 'p')
			PauseVariable = 1;

		else if(keyData.valueInBytes[0] == 'c')
			PauseVariable = 0;
	}*/

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
    uavcan::Subscriber<uavcan::protocol::debug::KeyValue> kv_subCAN1(nodeCAN1);



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
		reference = msg.value;
        
	else if(key.compare("alt") == 0)				//Altitude
            Altitude = (double) msg.value;

        else if(key.compare("tt2") == 0)				//Ambient Temperature
            Tt2_fromModel = (double) msg.value;

        else if(key.compare("mnb") == 0)				//Initial Mach Number
            MN = (double) msg.value;

        else if(key.compare("_d1") == 0)
        {
            model_d1 = msg.value;
            model_d1_toInt = model_d1;
        }

        else if(key.compare("_mf") == 0)
            model_mf = msg.value;

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
            Wf0 = (double) msg.value;
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


        /*else if(key.compare("_ps") == 0)		//pause
        {
            if(keyData.valueInBytes[0] == 'p')
                PauseVariable = 1;

            else if(keyData.valueInBytes[0] == 'c')
                PauseVariable = 0;
        }*/


	else if(key.compare("_al") == 0)
	{
		initialAltitude_float = msg.value;
		Altitude = initialAltitude_float;
	}

	/*else if(key.compare("_at") == 0)
	{
		initialAmbientTemp_float = msg.value;
	}*/

	/*else if(key.compare("_en") == 0)
	{
		engine_float = msg.value;
		engine = engine_float;
	}*/

	else if(key.compare("_mn") == 0)
	{
		initialMachNumber_float = msg.value;
		MN = initialMachNumber_float;
	}

        // else if(key.compare("_rf") == 0)				//Initial Reference
            // reference0 = (double) msg.value;

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
    nodeCAN0.setModeOperational();
    nodeCAN1.setModeOperational();

    /*
     * Some logging.
     * Log formatting is not available in C++03 mode.
     */
    nodeCAN0.getLogger().setLevel(uavcan::protocol::debug::LogLevel::DEBUG);
    nodeCAN0.logInfo("main", "Hello world da MainBoard FADEC CAN0! My Node ID: %*",
                 static_cast<int>(nodeCAN0.getNodeID().get()));
    nodeCAN1.getLogger().setLevel(uavcan::protocol::debug::LogLevel::DEBUG);
    nodeCAN1.logInfo("main", "Hello world da MainBoard FADEC CAN1! My Node ID: %*",
             static_cast<int>(nodeCAN1.getNodeID().get()));

    std::cout << "MainBoard FADEC Operacional!" << std::endl;	//informo que a MainBoard está rodando

    sendUAVCANKeyValueMsg(nodeCAN0, "stt", 0);	//Sends STarT message to nodes, so they change from INITIALIZATION status to OPERATIONAL
    sendUAVCANKeyValueMsg(nodeCAN0, "d12", 0);
    sendUAVCANKeyValueMsg(nodeCAN0, "o10", 0);

    /* LOADING OF CONTROLLER MATRICES */
    getTJ1200N_KpMtx(N_KpMtx);
    getTJ1200N_KiMtx(N_KiMtx);
    getTJ1200NcFANContMtx(NcFANContMtx);
    getTJ1200FNperContMtx(FNperContMtx);

    /* LOADING OF CONTROLLER STARRING PARAMETERS */
    getTJ1200StartPars(&ContStart);

//double teste = TJ1200_RPM_RAMP_CHANGE;
printf("teste = %f\n",ContStart.RPMRampChange);

    /* Reset variable must be set to 0 in order for inner
    * loop not to reset the timer consecutively */
    Reset = 0;

/********************************************************************************************************************************/
/*                                                                                                                              */
/********************************************************************************************************************************/

/********************************************************************************************************************************/
/*																																*/
/*												CRIAÇÃO E FUNÇÃO DO TIMER               									 	*/
/*																																*/
/********************************************************************************************************************************/


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
    uavcan::Timer periodic_timer(nodeCAN0);
    uavcan::Timer one_shot_timer(nodeCAN0);

    periodic_timer.setCallback([&](const uavcan::TimerEvent& event)
        {
            upTime_ms = upTime_ms + TICK;
            sendUAVCANKeyValueMsg(nodeCAN0,"upd", (float) upTime_ms);
            one_shot_timer.startOneShotWithDelay(uavcan::MonotonicDuration::fromMSec(15));
        });

    one_shot_timer.setCallback([&](const uavcan::TimerEvent& event)
        {
            ControlUpdate(nodeCAN0, nodeCAN1);
            sendUAVCANKeyValueMsg(nodeCAN1,"_sy", (float) upTime_ms);
        });
/********************************************************************************************************************************/
/*                                                                                                                              */
/********************************************************************************************************************************/

/********************************************************************************************************************************/
/*																																*/
/*												LOOP EXTERNO                             									 	*/
/*																																*/
/********************************************************************************************************************************/
    /*
     * Node loop.
     * The thread should not block outside Node::spin().
     */
    while (true)	//loop externo
    {
        /*
         * Spinning once.
         * The method spin() may return earlier if an error occurs (e.g. driver failure).
         * All error codes are listed in the header uavcan/error.hpp.
         */

        int spinCAN0_res = nodeCAN0.spinOnce();
        if (spinCAN0_res < 0)
        {
            std::cerr << "Transient failure: " << spinCAN0_res << std::endl;
        }

        int spinCAN1_res = nodeCAN1.spinOnce();
        if (spinCAN1_res < 0)
        {
            std::cerr << "Transient failure: " << spinCAN1_res << std::endl;
        }

        /* Resets static structs and variables */
        digital = digitalEmpty;
        Current_key_start = 0;
        Old_key_start = 0;
        fValue = 0;

        /* Disable controller actuation until authorized by model */
        Authorize = 0;

        /* Indicates reset request to the controller */
       ContInput.Reset = 1;

        /* Sets reset flag to 0 */
	Reset = 0;

        /* Starts timers */
        periodic_timer.startPeriodic(uavcan::MonotonicDuration::fromMSec(TICK));	// Update period
        upTime_ms = 0;

	sendUAVCANKeyValueMsg(nodeCAN1, "_tk", TICK);	//Sends the TICK value for Engine Model, used in HIL Sync Mode

/********************************************************************************************************************************/
/*																																*/
/*												LOOP INTERNO                             									 	*/
/*																																*/
/********************************************************************************************************************************/

        while(1)	//loop interno
        {

            spinCAN0_res = nodeCAN0.spinOnce();
            if (spinCAN0_res < 0)
            {
                std::cerr << "Transient failure: " << spinCAN0_res << std::endl;
            }

            spinCAN1_res = nodeCAN1.spinOnce();
             if (spinCAN1_res < 0)
             {
                 std::cerr << "Transient failure: " << spinCAN1_res << std::endl;
             }

            if(Reset == 1)
            {
                /* Stops timer */

                periodic_timer.stop();
                
		//upTime_ms = 0;
    		//sendUAVCANKeyValueMsg(nodeCAN1, "_tk", TICK);	//Sends the TICK value for Engine Model, used in HIL Sync Mode


                /* Breaks the current  while loop */
                break;
            }

        }

/********************************************************************************************************************************/
/*                                                                                                                              */
/********************************************************************************************************************************/

    }


}

void sendUAVCANKeyValueMsg(Node& node, char keyID[3], float value)
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
    uavcan::Publisher<uavcan::protocol::debug::KeyValue> kv_pub(node);

    int pub_res = kv_pub.broadcast(keyValue_msg);
    if (pub_res < 0)
    {
        std::cerr << "KV publication failure: " << pub_res << std::endl;
    }

}


void ControlUpdate(Node& node0, Node& node1)
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

    //Altitude = 0;			//from supervisorio (CAN1)
    //MN = 0;					//from supervisorio (CAN1)
//Tt2 = 288.15;			//from supervisorio/model (CAN1)	
Tt2 = Tt2_fromModel;			//from supervisorio/model (CAN1)
//std::cout << Tt2 << std::endl;	
    //Tt2 = t12;			//from input boards (CAN0)
    //Pt3 = 101325;			//from input boards	(CAN0)
    Pt3 = i13 * 100000;			//from input boards	(CAN0), converting from bar to pascal (1 bar = 100000 pascal)
    //Tt5 = 288.15;			//from input boards	(CAN0)
    //Tt5 = t14;			//from input boards	(CAN0)
Tt5 = (t12+t13+t14)/3;
//std::cout << Tt5 << std::endl;
    RPM = r11;
    //reference = .35;		//from supervisorio (CAN1)
    POil = 2;				//from input boards	(CAN0)
    //SkipStart = 0;			//from model (CAN1)
    //Authorize = 1;			//from model (CAN1)
    //Wf0 = 0.05;				//from model (CAN1)
    //ResetButton[0] = 0;		//from supervisorio (CAN1)

    /* Reads mode key */
    //Mode = 0;				//from supervisorio (CAN1)
    //LeverMode = 1;			//from supervisorio (CAN1)

    /* ---------------------------------------- */
    /* INPUT READINS FOR MATLAB SIMULAITON      */
    /* (To be usedi in MATLAB simulations only) */
    /* ---------------------------------------- */

    //	Altitude = InputVars[0];
    //	MN = InputVars[1];
    //	Tt2 = InputVars[2];
    //	Pt3 = InputVars[3];
    //	Tt5 = InputVars[4];
    //	RPM = InputVars[5];
    //	reference = InputVars[6];
    //	POil = InputVars[7];
    //	SkipStart = InputVars[8];
    //	Authorize = InputVars[9];
    //	Wf0 = InputVars[10];
    //	ResetButton[0] = InputVars[11];

    /* Reads mode key */
    //	Mode = InputVars[12];
    //	LeverMode = InputVars[13];

    /*-------------------------*/
    /* RESET REQUEST TREATMENT */
    /*-------------------------*/

    //TESTE INICIO!!!!

    if(ResetButton[0] == 1)
    {
        int teste = 1;
        teste = 1;
    }

    //TESTE FIM!!!

    /* Reads reset signal */
    //Reset = Edge(ResetButton);	//this command has been moved to CAN message reception, under reset ("_rs") message
    //ResetButton[1] = ResetButton[0];
    ResetButton[0] = 0;


//// The following lines has been moved to outer while loop
    /* Verifies if reset has been requested */
 //   if (Reset == 1)
 //   {
        /* Resets static structs and variables */
 //       digital = digitalEmpty;
 //       Current_key_start = 0;
 //       Old_key_start = 0;
//        fValue = 0;

        /* Disable controller actuation until authorized by model */
//        Authorize = 0;

        /* Indicates reset request to the controller */
//       ContInput.Reset = 1;

        /* Sets reset flag to 0 */
//	Reset = 0;
//    }

    /*-----------------------------------------------*/
    /* UPDATES REFERENCE FOR CONTROL LAW CALCULATION */
    /*-----------------------------------------------*/

    //Ignition = digital.bits.igniter;
    RefCAN = (double)reference;
    FNpc = RefCAN;

/* Reads the potentiomenter value if LeverMode == 2 */
	if(LeverMode == 2){
		FNpc = pot_percent;		
		if(!keys.bits.ac_drive_key == 0)
			FNpc = 0;				
	}

//std::cout << FNpc << std::endl;

    /*if(FNpc == 0.5){
        int testando = 1;
        testando = 0;
    }*/

    /*---------------*/
    /* CONTROL LOGIC */
    /*---------------*/
	if (simMod == 3)	//if Simulation Mode is "Test Bench", then there is no need to wait for authorize from Model
	{	
		Authorize = 1;
	}
    /* Checks for authorization of controller calculations */
    if(Authorize == 1)
    {
        /* SIMULATION OF GPIO PINS - MATLAB only */

        /* Simulates reading from each GPIO pin */
        //GPIOIn = (KeyBit6 << 6) | (KeyBit5 << 5) | (KeyBit4 << 4) | (KeyBit3 << 3) | (KeyBit2 << 2) | (KeyBit1 << 1) | (KeyBit0 << 0);
        //keys.in = GPIOIn & 0x7FF;

        /* THE FOLLOWING CODE IS REPRODUCED ALSO IN THE REAL HARDWARE */

        /* Reads start key - pulse detection */
        Old_key_start = Current_key_start;
        //Current_key_start = !keys.bits.ac_drive_key || Authorize;
        //THE FOLLOWING LINE HAS BEEN CHANGED TO AN 'AND' CONDITION FOR THE FACT THAT AUTHORIZE STARTS IN 1
	Current_key_start = !keys.bits.ac_drive_key && Authorize;

        if(Current_key_start==1)
        {
            int teste = 1;
            teste = 1;
        }

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
        PIMinMaxTJ1200(&ContStart, &ContInput, &ContOutput, &digitalWord, &keysWord,
                       NcFANContMtx, FNperContMtx, N_KpMtx, N_KiMtx, Tsample);

        /* Updates digital outputs and fuel flow value */
        digital.out = digitalWord;
        fValue = ContOutput.fValue;

    }

/*static int contagem = 0;
    
if(FNpc == 1)
{
	if(contagem < 100)
	{
        //printf("x(k) = %f; ",RPM);
		//printf("u(k) = %f\n",fValue);
		std::cout << contagem << ". x(k) = " << RPM;
		std::cout << "; u(k) = " << fValue << std::endl;
		contagem = contagem + 1;
	}
	
}
else
{
	contagem = 0;
}*/

        /*---------------------------------------------*/
        /* UPDATES OUTPUTS - To be used in MATLAB only */
        /*---------------------------------------------*/

        /* Writes SIMULINK outputs */
    //		Iout[0] = fValue;
    //		Iout[1] = ContOutput.Active;
    //		Iout[2] = digital.bits.igniter;
    //		Iout[3] = ContOutput.RPMRef;
    //		Iout[4] = ContOutput.FiltRef;



    /*---------------------------------------------------------------*/
    /* THE FOLLOWING CODE SENDS A MESSAGE THROUGH CAN COMMUNICATION  */
    /*---------------------------------------------------------------*/

     /* Sends Tt4-1 value to UAVCAN net in Celcius degrees*/
    //	 CANVar.valueInFloat = (float) Tt4 - 273.00;
    //	 sendUAVCANKeyValueMsg(CAN0,"_t4", CANVar);

     /* Sends Tt4-1 value to UAVCAN net in Celcius degrees*/
    //	 CANVar.valueInFloat = (float) Tt4 - 273.00;
    //	 sendUAVCANKeyValueMsg(CAN0,"_t4", CANVar);

    //	 CANVar.valueInFloat = (float) RPM;
    //	 sendUAVCANKeyValueMsg(CAN0,"_ra", CANVar);

    //	 CANVar.valueInFloat = ((float) Pt3 - (float) P0) * 1e-5;
    //	 sendUAVCANKeyValueMsg(CAN0,"_p3", CANVar);

    //	 CANVar.valueInFloat = ((float) Pt3 - (float) P0) * 1e-5;
    //	 sendUAVCANKeyValueMsg(CAN0,"_p3", CANVar);

    //	 CANVar.valueInFloat = (float) fValue;
    //	 sendUAVCANKeyValueMsg(CAN0,"fvl", CANVar);

    float pump_flowToVoltage = (fValue/TJ1200_WFMAX);		//converts 0~max fuel pump flow to 0~5V
    pump_flowToVoltage = pump_flowToVoltage * 5;	//converts 0~max fuel pump flow to 0~5V
/*printf("fValue = %f; ", fValue);
float wfmaxtemp = TJ1200_WFMAX;
printf("WFMAX = %f; ", wfmaxtemp);
printf("flow2Volts = %.2f;\n\n", pump_flowToVoltage);*/
    sendUAVCANKeyValueMsg(node0, "o10", pump_flowToVoltage);
    usleep(1000);

    sendUAVCANKeyValueMsg(node0, "d12", (float) digital.out);

/* Messages to Supervisorio/Model */
    sendUAVCANKeyValueMsg(node1, "i10", i10);	//send to Supervisorio the value of Potentiometer in Volts (0~5V)
sendUAVCANKeyValueMsg(node1, "i11", i11);	
sendUAVCANKeyValueMsg(node1, "i12", i12);	
sendUAVCANKeyValueMsg(node1, "i13", i13);	
sendUAVCANKeyValueMsg(node1, "t11", t11);	//send to Supervisorio the value of Thermocouple 1
sendUAVCANKeyValueMsg(node1, "t12", t12);	
sendUAVCANKeyValueMsg(node1, "t13", t13);	
sendUAVCANKeyValueMsg(node1, "t14", t14);	
sendUAVCANKeyValueMsg(node1, "t15", t15);	
sendUAVCANKeyValueMsg(node1, "t16", t16);	
sendUAVCANKeyValueMsg(node1, "t17", t17);	
sendUAVCANKeyValueMsg(node1, "t18", t18);	
sendUAVCANKeyValueMsg(node1, "r11", r11);	//send to Supervisorio the value of rpm channel 1
sendUAVCANKeyValueMsg(node1, "r12", r12);
sendUAVCANKeyValueMsg(node1, "d12", (float) digital.out);
sendUAVCANKeyValueMsg(node1, "d11", (float) keys.in);		
    sendUAVCANKeyValueMsg(node1, "o10", pump_flowToVoltage);	//send to Supervisorio the value of Potentiometer in Volts (0~5V)

	if(Mode == 0)
		sendUAVCANKeyValueMsg(node1, "act", (float) ContOutput.Active);	//send to Supervisorio the active controller

    sendUAVCANKeyValueMsg(node1, "o1a", o1a);	//send to Supervisorio the value of Potentiometer in Volts (0~5V)
    sendUAVCANKeyValueMsg(node1, "_cj", t1d);	//send the cold junction temperature to Model Board, to use on thermocouple simulation

//std::cout << Mode << std::endl;

    //usleep(1000);

    //sendUAVCANKeyValueMsg(node, "mrf", (float) ContOutput.FiltRef);
    //usleep(1000);

    /*APENASTESTE*/
    //CANVar.valueInFloat = d11_float;
    //sendUAVCANKeyValueMsg(CAN0, "d12", CANVar);
    //mandar duas vezes pq esta demorando para atualizar a saida digital, mesmo a mensagem sendo enviada
    //CANVar.valueInFloat = d11_float;
    //sendUAVCANKeyValueMsg(CAN0, "d12", CANVar);
    /*APENASTESTE*/


}

