/*
 * fadecLite_data_hub.h
 *
 *  Created on: 13 de mar. de 2026
 *      Author: Marcel
 */

#ifndef FADEC_CORE_DATA_HUB_FADECLITE_DATA_HUB_H_
#define FADEC_CORE_DATA_HUB_FADECLITE_DATA_HUB_H_

#include <stdint.h>

/* All variables here are with generic names. Change accordingly to your application. */

typedef enum {
    FADEC_STANDARD = 1,
    FADEC_LITE
} FADEC_model_enum_t;

typedef enum {
    CMD_START     = 0xAA, // 1010 1010
    CMD_SHUTDOWN  = 0x55, // 0101 0101
    CMD_EMERGENCY = 0xCC // 1100 1100
} FADEC_commands_enum_t;

typedef enum {
    AUTO_START_FLIGHT	= 0xAA, // 1010 1010
    AUTO_START_GROUND 	= 0x55, // 0101 0101
    MANUAL_START_GROUND = 0xCC // 1100 1100
} Starting_mode_enum_t;

typedef enum {
    TJ_1200	= 0xAA, // 1010 1010
    TF_1200 = 0x55, // 0101 0101
    TJ_200 	= 0xCC, // 1100 1100
    GE_J85 	= 0x33,	// 0011 0011
    TJ_700 = 0xF0,  // 1111 0000
    TJ_40 = 0x0F,    // 0000 1111
} Which_engine_enum_t;

typedef enum {
    CONTROL_LAW	= 0xAA, // 1010 1010
    MANUAL_POT 	= 0x55, // 0101 0101
    MANUAL_PC 	= 0xCC // 1100 1100
} Lever_mode_enum_t;

typedef enum {
    HIL_ASYNC	= 0xAA, // 1010 1010
    HIL_SYNC 	= 0x55, // 0101 0101
    SIL 		= 0xCC, // 1100 1100
	TEST_BENCH	= 0x33	// 0011 0011
} Simulation_mode_enum_t;

typedef enum {
    DRONE_CAN		= 0xAA, // 1010 1010
    CAN_OPEN 		= 0x55, // 0101 0101
    CUSTOM_PROTOCOL	= 0xCC // 1100 1100
} CAN_protocol_enum_t;

typedef enum
{
    TJ_INITIALIZE = 1,
    TJ_WINDMILLING,
    TJ_READY_TO_START,
    TJ_STARTING,
    TJ_IDLE,
    TJ_REGIME,
    TJ_SHUTTING_DOWN,
	TJ_OFF,
    TJ_EMERGENCY,
    TJ_FAIL,
    TJ_DEGRADED
} FADEC_State_enum_t;

typedef struct
{
	uint8_t resetSource;
	uint8_t resetFlag;
	Starting_mode_enum_t startingMode;
	Which_engine_enum_t whichEngine;
	Lever_mode_enum_t leverMode;
	Simulation_mode_enum_t simMode;
	CAN_protocol_enum_t canProtocol;
} FADEC_reset_command_t;

typedef struct
{
	// For TJ200 with Motor/Generator, RPM will measure t
	//int32_t rpm_hall;
	int32_t rpm_generator;

	struct
	{
		float temperature;
		float coldJunctionTemperature;
		uint8_t status;
	} Ts2;

	struct
	{
		float temperature;
		float coldJunctionTemperature;
		uint8_t status;
	} Tt5;

	float ptc_0;
	float ptc_1;

	uint8_t digitalIn_0;
	uint8_t digitalIn_1;

//	struct
//	{
//		uint32_t duty_us;
//		uint32_t period_us;
//	} pwmIn_0;
	// For TJ200 with Motor/Generator, the PWM input will be used to measure eRPM from ESC.
	int32_t pwmIn_0_rpm_esc;

	struct
	{
		uint32_t duty_us;
		uint32_t period_us;
	} pwmIn_1;

	float anIn_0;
	float anIn_1;

} FADEClite_sensors_t;

typedef struct
{
	float anOut_4_20mA;
	float anOut_0_10V;

	//Low power PWM Outputs
	float pwmOut_0_esc_pwmCommand;
	float pwmOut_1_enable_esc2motor;				// when used as an digital output, just set to 0 or 1 (0% or 100% duty cycle).
	float pwmOut_2_enable_rectifierOutput;		// when used as an digital output, just set to 0 or 1 (0% or 100% duty cycle).
	float pwmOut_3;
	float pwmOut_4;
	float pwmOut_5;
	float pwmOut_6;
	float pwmOut_7;

	//Power PWM outputs
	float powerPwmOut_0_igniter;					// when used as an digital output, just set to 0 or 1 (0% or 100% duty cycle).
	float powerPwmOut_1_igniter_SOV;				// PWM command for SOV
	float powerPwmOut_2_fuel_SOV;					// PWM command for SOV
	float powerPwmOut_3_fuelPump;					// PWM 0% to 100%, direct PWM command for fuel pump.

	uint8_t digOut;					//this variable is used to set the pwm output as digital outputs, by setting the corresponding bit to 1 or 0. For example, if you want to set pwmOut_3 and pwmOut_5 as digital outputs, you should set digOut = 0b00101000 (bit 3 and bit 5 set to 1, counting from bit 0). The actual mapping of which bit corresponds to which output is defined in the control loop implementation.
	uint8_t powerDigOut;			//same

} FADEClite_actuators_t;

typedef struct
{
	FADEC_commands_enum_t fadecCommand;
} Engine_Command_t;

typedef struct
{
	float thrustRef;
} Thrust_Ref_t;

typedef struct
{
	float altitude;
	float machNumber;
	float dT;
} Flight_Conditions_t;



//FADEC Failure Code Visualization
typedef union
{
    struct Faults
    {


        /* SENSOR FAILURES */

        /*Ts2 sensor 1 possible faults - Bits 0 to 2*/
        uint64_t Ts2_0_SCV       :1;
        uint64_t Ts2_0_SCG       :1;
        uint64_t Ts2_0_Open      :1;

        /*Ts2 sensor 2 possible faults - Bits 3 to 5*/
        uint64_t Ts2_1_SCV       :1;
        uint64_t Ts2_1_SCG       :1;
        uint64_t Ts2_1_Open      :1;

        /*Pt3 sensor 1 possible faults - Bits 6 to 7*/
        uint64_t Pt3_0_Short     :1;
        uint64_t Pt3_0_Open      :1;

        /*Tt4 sensor 1 possible faults - Bits 8 to 10*/
        uint64_t Tt4_0_SCV       :1;
        uint64_t Tt4_0_SCG       :1;
        uint64_t Tt4_0_Open      :1;

        /*Tt4 sensor 2 possible faults - Bits 11 to 13*/
        uint64_t Tt4_1_SCV       :1;
        uint64_t Tt4_1_SCG       :1;
        uint64_t Tt4_1_Open      :1;

        /*Tt4 sensor 3 possible faults - Bits 14 to 16*/
        uint64_t Tt4_2_SCV       :1;
        uint64_t Tt4_2_SCG       :1;
        uint64_t Tt4_2_Open      :1;

        /*RPM sensor 1 possible faults - Bits 17 to 20*/
        uint64_t RPM_0_Short     :1;
        uint64_t RPM_0_Open      :1;
        uint64_t RPM_0_1PLoss    :1;
        uint64_t RPM_0_2PLoss    :1;

        /*RPM sensor 2 possible faults - Bits 21 to 24*/
        uint64_t RPM_1_Short     :1;
        uint64_t RPM_1_Open      :1;
        uint64_t RPM_1_1PLoss    :1;
        uint64_t RPM_1_2PLoss    :1;

        /*POil sensor 1 possible faults - Bits 25 to 26*/
        uint64_t POil_0_Short    :1;
        uint64_t POil_0_Open     :1;

        /* PFuel sensor 1 possible faults - Bits 27 to 28*/
        uint64_t PFuel_0_Short   :1;
        uint64_t PFuel_0_Open    :1;

        /* Vibration sensor 1 possible faults - Bits 29 to 30*/
        uint64_t Vib_0_Short     :1;
        uint64_t Vib_0_Open      :1;

        /* SYSTEM FAILURES */

        /* Lubrication system faults - Bits 31 to 32*/
        uint64_t POil_High       :1;
        uint64_t POil_Low        :1;

        /* Fuel system faults - Bits 33 to 34 */
        uint64_t PFuel_High      :1;
        uint64_t PFuel_Low       :1;

        /* Engine Blowout - Bit 35 */
        uint64_t BlowOut         :1;

        /* Mec system faults - Bits 36 to 40*/
        uint64_t VibrationHigh   :1;
        uint64_t Mec_Lock        :1;
        uint64_t OverTemp        :1;
        uint64_t OverSpeed       :1;
        uint64_t Ignition        :1;

        /* Sensors bias - Bits 41 to 51 */
        uint64_t Ts2_0_Bias      :1;
        uint64_t Ts2_1_Bias      :1;
        uint64_t Pt3_0_Bias      :1;
        uint64_t Tt4_0_Bias      :1;
        uint64_t Tt4_1_Bias      :1;
        uint64_t Tt4_2_Bias      :1;
        uint64_t RPM_0_Bias      :1;
        uint64_t RPM_1_Bias      :1;
        uint64_t POil_0_Bias     :1;
        uint64_t PFuel_0_Bias    :1;
        uint64_t Vib_0_Bias      :1;

        /* Bit indicating that thermocouple faults are simulated by software - Bit 52 */
        /* The float number MATLAB is able to work with must contain 53 bits or less.
        Therefore, the position of TCFaultSoftSim was placed at bit 52 (last bit
        countig from 0)  */
        uint64_t TCFaultSoftSim  :1;

        /* TBear 0 sensor possible faults - Bit 53 */
        uint64_t TB_0_Open       :1;
        /* TBear 1 sensor possible faults - Bit 54 */
        uint64_t TB_1_Open       :1;
        /* TBear 2 sensor possible faults - Bit 55 */
        uint64_t TB_2_Open       :1;

        /* Bearing overtemp - Bits 56 to 58 */
        uint64_t TBear_0_High    :1;
        uint64_t TBear_1_High    :1;
        uint64_t TBear_2_High    :1;

        /* CAN network - Bits 59 to 60 */
        uint64_t CAN_0_Fault     :1;
        uint64_t CAN_1_Fault     :1;

        /* Reserved bits - Bits 61 to 63 */
        uint64_t NotUsedBits     :3;

    } Faults;

    uint8_t valueInBytes[8];

    uint64_t valueUint64;
} FADEC_warnings_failures_t;



typedef struct
{
    FADEC_State_enum_t FADECstate;
    FADEC_warnings_failures_t warnings;
    FADEC_warnings_failures_t failures;
    uint32_t fadecUptime_ms;


} FADEC_status_t;

typedef struct
{
	FADEC_warnings_failures_t simFailures;
	FADEC_warnings_failures_t simWarnings;
	float simVar1;
	float simVar2;


} FADEClite_simulation_variables_t;

typedef struct
{
    FADEClite_actuators_t remote_actuators;
    float remote_lever;
} Remote_Actuators_Command_t;

typedef struct
{
    uint8_t activeController;
    float thrustRef;
    float oilPumpRef;
    float fuelPumpRef;
    float fuelFlow;
    float dT;
    float machNumber;
    float altitude;
    float estimatedThrust;
    float consumption_kg;
    float debugValue0;
    float debugValue1;
    float debugValue2;
    float debugValue3;
} Control_Variables_t;


typedef struct
{
	FADEClite_sensors_t sensors;
	FADEClite_actuators_t actuators;
	FADEC_status_t fadecStatus;
	Control_Variables_t controlVariables;

} FADEClite_telemetry_t;

void fadecLite_data_hub_init(void);
void fadecLite_data_hub_get_sensors_data(FADEClite_sensors_t* out_data);
void fadecLite_data_hub_set_sensors_data(const FADEClite_sensors_t* in_data);
void fadecLite_data_hub_get_actuators_data(FADEClite_actuators_t* out_data);
void fadecLite_data_hub_set_actuators_data(const FADEClite_actuators_t* in_data);
void fadecLite_data_hub_get_commands_data(Engine_Command_t* out_data);
void fadecLite_data_hub_set_commands_data(const Engine_Command_t* in_data);
void fadecLite_data_hub_get_thrust_ref(Thrust_Ref_t* out_data);
void fadecLite_data_hub_set_thrust_ref(const Thrust_Ref_t* in_data);
void fadecLite_data_hub_get_flight_conditions(Flight_Conditions_t* out_data);
void fadecLite_data_hub_set_flight_conditions(const Flight_Conditions_t* in_data);
void fadecLite_data_hub_get_fadec_status(FADEC_status_t* out_data);
void fadecLite_data_hub_set_fadec_status(const FADEC_status_t* in_data);
void fadecLite_data_hub_get_telemetry_data(FADEClite_telemetry_t* out_data);
void fadecLite_data_hub_set_telemetry_data(const FADEClite_telemetry_t* in_data);
void fadecLite_data_hub_get_simulation_variables(FADEClite_simulation_variables_t* out_data);
void fadecLite_data_hub_set_simulation_variables(const FADEClite_simulation_variables_t* in_data);
void fadecLite_data_hub_get_remote_actuators_command(Remote_Actuators_Command_t* out_data);
void fadecLite_data_hub_set_remote_actuators_command(const Remote_Actuators_Command_t* in_data);
void fadecLite_data_hub_get_reset_command(FADEC_reset_command_t* out_data);
void fadecLite_data_hub_set_reset_command(const FADEC_reset_command_t* in_data);

#endif /* FADEC_CORE_FADECLITE_DATA_HUB_H_ */
