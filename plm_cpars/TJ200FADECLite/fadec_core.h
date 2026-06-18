/*
 * fadec_core.h
 *
 *  Created on: 13 de mar. de 2026
 *      Author: Marcel
 */

#ifndef FADEC_CORE_FADEC_CORE_H_
#define FADEC_CORE_FADEC_CORE_H_

#include "fadecLite_data_hub.h"
#include "fadec_io_manager.h"
#include "main.h"

// Here the CAN channels available in the hardware are defined.
// Change it according to actual hardware.
typedef enum {
	FDCAN_1 = 0,
	FDCAN_2,
	MAX_CAN_CHANNELS
} CAN_Channel_t;

/**
 * @brief Opções de protocolos CAN suportados pelo sistema.
 */
typedef enum {
    CAN_PROTOCOL_CANOPEN = 0,
    CAN_PROTOCOL_DRONECAN,
    CAN_PROTOCOL_CUSTOM
} CAN_Protocol_t;

typedef struct {
	CAN_Channel_t channel_id;
	FDCAN_HandleTypeDef* hfdcan;
	CAN_Protocol_t canProtocol;
	void (*hwInitFunc)(void);
	TIM_HandleTypeDef *htim_1ms;
	TIM_HandleTypeDef *htim_1us;
} CAN_Channel_Config_t;

typedef struct {
	FADEClite_sensors_t sensors;
	FADEClite_simulation_variables_t simVars;
	Engine_Command_t engineCommand;
	Thrust_Ref_t thrustRef;
	Flight_Conditions_t flightConditions;
	Remote_Actuators_Command_t remoteActuatorsCommand;
	FADEC_reset_command_t resetCommand;
} ControlLoop_Inputs_t;

typedef struct {
	FADEClite_actuators_t actuators;
	FADEC_status_t fadecStatus;
	Control_Variables_t controlVariables;
} ControlLoop_Outputs_t;

void fadecCore_CANcomm_init(CAN_Channel_Config_t can_channel_config);
void fadecCore_CANcomm_changeProtocol(void);
void fadecCore_CANcomm_timer_1ms_interrupt(void);
void fadecCore_CANcomm_timer_1us_interrupt(void);
void fadecCore_CANcomm_task(void);
void fadecCore_dataHub_controlLoop_init(void);
void fadecCore_controlLoop_task(void);
void fadecCore_io_init(FADEClite_IO_Handles_t* io_config);
void fadecCore_io_readSensors();
void fadecCore_io_writeActuators();
void fadecCore_io_timer_pwmInput_overflow(TIM_HandleTypeDef *htim);
void fadecCore_default_task(void);

#endif /* FADEC_CORE_FADEC_CORE_H_ */
