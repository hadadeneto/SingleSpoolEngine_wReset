/*
 * fakeControl.c
 *
 *  Created on: 13 de mar. de 2026
 *      Author: Marcel
 */

#include "fakeControl.h"

uint32_t initialTime_ms;

void fakeControl_init(void)
{
	// Inicialização do controle fake, se necessário
	initialTime_ms = HAL_GetTick();
}

// ONLY FOR DEBUG! Not using const only for debugging
//void fakeControl_loop(const ControlLoop_Inputs_t* control_inputs, ControlLoop_Outputs_t* control_outputs);
void fakeControl_loop(ControlLoop_Inputs_t* control_inputs, ControlLoop_Outputs_t* control_outputs)
{
	//For testing, the control loop will simply pass the remote actuators command to the actuators output, with some modifications to demonstrate how to read the inputs and write the outputs.

	control_outputs->actuators.powerPwmOut_0_igniter = (control_inputs->remoteActuatorsCommand.remote_actuators.digOut & 0b00000001) ? 1.0f : 0.0f; // If the least significant bit of digital_power_outputs is set, set the igniter command to 1.0 (100% duty cycle), otherwise set it to 0.0 (0% duty cycle).
	control_outputs->actuators.powerPwmOut_1_igniter_SOV = (control_inputs->remoteActuatorsCommand.remote_actuators.digOut & 0b00000010) ? 0.5f : 0.0f; // For TJ-200 valve, the operation is in 50% duty cycle.
	control_outputs->actuators.powerPwmOut_2_fuel_SOV = (control_inputs->remoteActuatorsCommand.remote_actuators.digOut & 0b00000100) ? 0.5f : 0.0f; // For TJ-200 valve, the operation is in 50% duty cycle.
	//control_outputs->actuators.powerPwmOut_3_fuelPump = control_inputs->remoteActuatorsCommand.remote_actuators.powerPwmOut_3_fuelPump; 		// Fuel Pump is PWM controlled, so we take the value directly.
	control_outputs->actuators.powerPwmOut_3_fuelPump = control_inputs->remoteActuatorsCommand.remote_actuators.powerPwmOut_3_fuelPump; 		// Fuel Pump is PWM controlled, so we take the value directly.

	control_outputs->actuators.pwmOut_0_esc_pwmCommand = control_inputs->remoteActuatorsCommand.remote_actuators.pwmOut_0_esc_pwmCommand;
	control_outputs->actuators.pwmOut_1_enable_esc2motor = (control_inputs->remoteActuatorsCommand.remote_actuators.digOut & 0b00010000) ? 1.0f : 0.0f; // Enable ESC to motor command, digital output (0% or 100% of PWM), bit 4 of digOut.
	control_outputs->actuators.pwmOut_2_enable_rectifierOutput = (control_inputs->remoteActuatorsCommand.remote_actuators.digOut & 0b00100000) ? 1.0f : 0.0f; // Enable rectifier output command, digital output (0% or 100% of PWM), bit 5 of digOut.
	control_outputs->actuators.pwmOut_3 = control_inputs->remoteActuatorsCommand.remote_actuators.pwmOut_3;
	control_outputs->actuators.pwmOut_4 = control_inputs->remoteActuatorsCommand.remote_actuators.pwmOut_4;
	control_outputs->actuators.pwmOut_5 = control_inputs->remoteActuatorsCommand.remote_actuators.pwmOut_5;
	control_outputs->actuators.pwmOut_6 = control_inputs->remoteActuatorsCommand.remote_actuators.pwmOut_6;
	control_outputs->actuators.pwmOut_7 = control_inputs->remoteActuatorsCommand.remote_actuators.pwmOut_7;
	control_outputs->actuators.anOut_0_10V = control_inputs->remoteActuatorsCommand.remote_actuators.anOut_0_10V;
	control_outputs->actuators.anOut_4_20mA = control_inputs->remoteActuatorsCommand.remote_actuators.anOut_4_20mA;
	control_outputs->actuators.digOut = control_inputs->remoteActuatorsCommand.remote_actuators.digOut;
	control_outputs->actuators.powerDigOut = control_inputs->remoteActuatorsCommand.remote_actuators.powerDigOut;

	control_outputs->fadecStatus.fadecUptime_ms = HAL_GetTick() - initialTime_ms;	// Example: set FADEC uptime based on the time since initialization.

	control_outputs->controlVariables.activeController = 1;
	control_outputs->controlVariables.fuelPumpRef = control_outputs->actuators.powerPwmOut_3_fuelPump;
	control_outputs->controlVariables.fuelFlow = control_outputs->actuators.powerPwmOut_3_fuelPump * 0.0437f; //157,44 kg/h max (195.82L/h)
	control_outputs->controlVariables.estimatedThrust = 12345;	// float16 limit is 65504
	static float debugValue = 1.0f;
	debugValue += 0.1f;
	control_outputs->controlVariables.debugValue0 = debugValue;
	control_outputs->controlVariables.debugValue1 = debugValue+1.0f;
	control_outputs->controlVariables.debugValue2 = debugValue+2.0f;
	control_outputs->controlVariables.debugValue3 = debugValue+3.0f;



	static int fadecStateCounter = 1;
	fadecStateCounter++;
	if(fadecStateCounter > 11)
	{
		fadecStateCounter = 1;
	}
	//control_outputs->fadecStatus.FADECstate = fadecStateCounter;
	control_outputs->fadecStatus.FADECstate = TJ_IDLE;


//	// Loop de controle fake, onde você pode ler os dados dos sensores, processar a lógica de controle e escrever os comandos para os atuadores
//	// Por exemplo:
////	FADEClite_sensors_t sensors_data;
////	fadecLite_get_sensors_data(&sensors_data);
////	sensors_data.rpm_hall = sensors_data.rpm_hall + 10; // Exemplo: leitura do sensor de RPM
////	sensors_data.thermocouple_0.temperature = sensors_data.thermocouple_0.temperature + 0.1f; // Exemplo: leitura do termopar
////	fadecLite_set_sensors_data(&sensors_data);
////	control_inputs->sensors.rpm_hall = control_inputs->sensors.rpm_hall + 10; // Exemplo: leitura do sensor de RPM
////	control_inputs->sensors.thermocouple_0.temperature = control_inputs->sensors.thermocouple_0.temperature + 0.1f; // Exemplo: leitura do termopar
//
//	// Processar a lógica de controle com base nos dados dos sensores
////	FADEClite_commands_t commands_data;
////	fadecLite_get_commands_data(&commands_data);
////	commands_data.fadecCommand = 1; // Exemplo: comando para ligar o motor
////	commands_data.thrustRef = commands_data.thrustRef + 1; // Exemplo: referência de empuxo
////	fadecLite_set_commands_data(&commands_data);
//	control_inputs->engineCommand.fadecCommand = CMD_START; // Exemplo: comando para ligar o motor
//	control_inputs->thrustRef.thrustRef = control_inputs->thrustRef.thrustRef + 1; // Exemplo: referência de empuxo
//
//	// Escrever os comandos para os atuadores
//	control_outputs->actuators.pwmOut_0_esc_pwmCommand = control_outputs->actuators.pwmOut_0_esc_pwmCommand + 0.01;
//	if(control_outputs->actuators.pwmOut_0_esc_pwmCommand > 1.0f)
//	{
//		control_outputs->actuators.pwmOut_0_esc_pwmCommand = 0.0f; // Exemplo: comando para o atuador PWM
//	}
//
//	control_outputs->actuators.pwmOut_1_enable_esc2motor = control_outputs->actuators.pwmOut_1_enable_esc2motor + 0.01;
//	if(control_outputs->actuators.pwmOut_1_enable_esc2motor > 1.0f)
//	{
//		control_outputs->actuators.pwmOut_1_enable_esc2motor = 0.0f; // Exemplo: comando para o atuador PWM
//	}
//
//	control_outputs->actuators.pwmOut_2_enable_rectifierOutput = control_outputs->actuators.pwmOut_2_enable_rectifierOutput + 0.01;
//	if(control_outputs->actuators.pwmOut_2_enable_rectifierOutput > 1.0f)
//	{
//		control_outputs->actuators.pwmOut_2_enable_rectifierOutput = 0.0f; // Exemplo: comando para o atuador PWM
//	}
//
//	control_outputs->actuators.pwmOut_3 = control_outputs->actuators.pwmOut_3 + 0.01;
//	if(control_outputs->actuators.pwmOut_3 > 1.0f)
//	{
//		control_outputs->actuators.pwmOut_3 = 0.0f; // Exemplo: comando para o atuador PWM
//	}
//
//	control_outputs->actuators.pwmOut_4 = control_outputs->actuators.pwmOut_4 + 0.02;
//	if(control_outputs->actuators.pwmOut_4 > 1.0f)
//	{
//		control_outputs->actuators.pwmOut_4 = 0.0f; // Exemplo: comando para o atuador PWM
//	}
//
//	control_outputs->actuators.pwmOut_5 = control_outputs->actuators.pwmOut_5 + 0.03;
//	if(control_outputs->actuators.pwmOut_5 > 1.0f)
//	{
//		control_outputs->actuators.pwmOut_5 = 0.0f; // Exemplo: comando para o atuador PWM
//	}
//
//	control_outputs->actuators.pwmOut_6 = control_outputs->actuators.pwmOut_6 + 0.04;
//	if(control_outputs->actuators.pwmOut_6 > 1.0f)
//	{
//		control_outputs->actuators.pwmOut_6 = 0.0f; // Exemplo: comando para o atuador PWM
//	}
//
//	control_outputs->actuators.pwmOut_7 = control_outputs->actuators.pwmOut_7 + 0.05;
//	if(control_outputs->actuators.pwmOut_7 > 1.0f)
//	{
//		control_outputs->actuators.pwmOut_7 = 0.0f; // Exemplo: comando para o atuador PWM
//	}
//
////	control_outputs->actuators.powerPwmOut_0 = control_outputs->actuators.powerPwmOut_0 + 0.1;
////	if(control_outputs->actuators.powerPwmOut_0 > 1.0f)
////	{
////		control_outputs->actuators.powerPwmOut_0 = 0.0f; // Exemplo: comando para o atuador Power PWM
////	}
////
////	control_outputs->actuators.powerPwmOut_1 = control_outputs->actuators.powerPwmOut_1 + 0.1;
////	if(control_outputs->actuators.powerPwmOut_1 > 1.0f)
////	{
////		control_outputs->actuators.powerPwmOut_1 = 0.0f; // Exemplo: comando para o atuador Power PWM
////	}
////
////	control_outputs->actuators.powerPwmOut_2 = control_outputs->actuators.powerPwmOut_2 + 0.1;
////	if(control_outputs->actuators.powerPwmOut_2 > 1.0f)
////	{
////		control_outputs->actuators.powerPwmOut_2 = 0.0f; // Exemplo: comando para o atuador Power PWM
////	}
////
////	control_outputs->actuators.powerPwmOut_3 = control_outputs->actuators.powerPwmOut_3 + 0.1;
////	if(control_outputs->actuators.powerPwmOut_3 > 1.0f)
////	{
////		control_outputs->actuators.powerPwmOut_3 = 0.0f; // Exemplo: comando para o atuador Power PWM
////	}
//
//	control_outputs->actuators.anOut_4_20mA = control_outputs->actuators.anOut_4_20mA + 0.06;
//	if(control_outputs->actuators.anOut_4_20mA > 1.0f)
//	{
//		control_outputs->actuators.anOut_4_20mA = 0.0f; // Exemplo: comando para o atuador Analógico 4-20mA
//	}
//
//	control_outputs->actuators.anOut_0_10V = control_outputs->actuators.anOut_0_10V + 0.07;
//	if(control_outputs->actuators.anOut_0_10V > 1.0f)
//	{
//		control_outputs->actuators.anOut_0_10V = 0.0f; // Exemplo: comando para o atuador Analógico 0-10V
//	}
//
//	static uint32_t last_toggle_PWM_power = 0;
//
////	if(control_outputs->actuators.powerPwmOut_0 > 0.5f && (HAL_GetTick() - last_toggle_PWM_power) > 30000)
////	{
////		control_outputs->actuators.powerPwmOut_0 = 0.0f; // Exemplo: comando para o atuador Power PWM
////		control_outputs->actuators.powerPwmOut_1 = 0.0f; // Exemplo: comando para o atuador Power PWM
////		control_outputs->actuators.powerPwmOut_2 = 0.0f; // Exemplo: comando para o atuador Power PWM
////		control_outputs->actuators.powerPwmOut_3 = 0.0f; // Exemplo: comando para o atuador Power PWM
////		last_toggle_PWM_power = HAL_GetTick();
////	}
////	else if(control_outputs->actuators.powerPwmOut_0 <= 0.5f && (HAL_GetTick() - last_toggle_PWM_power) > 30000)
////	{
////		control_outputs->actuators.powerPwmOut_0 = 1.0f; // Exemplo: comando para o atuador Power PWM
////		control_outputs->actuators.powerPwmOut_1 = 1.0f; // Exemplo: comando para o atuador Power PWM
////		control_outputs->actuators.powerPwmOut_2 = 1.0f; // Exemplo: comando para o atuador Power PWM
////		control_outputs->actuators.powerPwmOut_3 = 1.0f; // Exemplo: comando para o atuador Power PWM
////		last_toggle_PWM_power = HAL_GetTick();
////	}
//	if(HAL_GetTick() - last_toggle_PWM_power > 10000)
//	{
//		control_outputs->actuators.powerPwmOut_0_igniter = control_outputs->actuators.powerPwmOut_0_igniter + 0.1f; // Exemplo: comando para o atuador Power PWM
//		control_outputs->actuators.powerPwmOut_1_igniter_SOV = control_outputs->actuators.powerPwmOut_1_igniter_SOV + 0.1f; // Exemplo: comando para o atuador Power PWM
//		control_outputs->actuators.powerPwmOut_2_fuel_SOV = control_outputs->actuators.powerPwmOut_2_fuel_SOV + 0.1f; // Exemplo: comando para o atuador Power PWM
//		control_outputs->actuators.powerPwmOut_3_fuelPump = control_outputs->actuators.powerPwmOut_3_fuelPump + 0.1f; // Exemplo: comando para o atuador Power PWM
//
//		if(control_outputs->actuators.powerPwmOut_0_igniter > 1.05f)
//		{
//			control_outputs->actuators.powerPwmOut_0_igniter = 0.0f; // Exemplo: comando para o atuador Power PWM
//		}
//		if(control_outputs->actuators.powerPwmOut_1_igniter_SOV > 1.05f)
//		{
//			control_outputs->actuators.powerPwmOut_1_igniter_SOV = 0.0f; // Exemplo: comando para o atuador Power PWM
//		}
//		if(control_outputs->actuators.powerPwmOut_2_fuel_SOV > 1.05f)
//		{
//			control_outputs->actuators.powerPwmOut_2_fuel_SOV = 0.0f; // Exemplo: comando para o atuador Power PWM
//		}
//		if(control_outputs->actuators.powerPwmOut_3_fuelPump > 1.05f)
//		{
//			control_outputs->actuators.powerPwmOut_3_fuelPump = 0.0f; // Exemplo: comando para o atuador Power PWM
//		}
//		last_toggle_PWM_power = HAL_GetTick();
//	}
//
//	control_outputs->fadecStatus.fadecUptime_ms = HAL_GetTick() - initialTime_ms; // Exemplo: atualização do tempo de atividade do FADEC
//
////			control_outputs->actuators.powerPwmOut_0 = 0.2f; // Exemplo: comando para o atuador Power PWM
////			control_outputs->actuators.powerPwmOut_1 = 0.2f; // Exemplo: comando para o atuador Power PWM
////			control_outputs->actuators.powerPwmOut_2 = 0.2f; // Exemplo: comando para o atuador Power PWM
////			control_outputs->actuators.powerPwmOut_3 = 0.2f; // Exemplo: comando para o atuador Power PWM
}

// Only allow reset routine after the control loop sets the system in a safe state to reset.
int fakeControl_allowReset(void)
{
	return 1;
}
