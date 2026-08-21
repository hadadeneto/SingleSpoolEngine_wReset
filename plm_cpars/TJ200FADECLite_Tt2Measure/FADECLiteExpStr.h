/*
 * FADECLiteExpStr.h
 *
 *  Created on: 19 de jun. de 2026
 *      Author: Antonio Hadade Neto
 */

#ifndef FADECLITEEXPSTR_H_
#define FADECLITEEXPSTR_H_

#include <stdint.h>
#include "FADEC_Defines_H/FloatPoint_Precision.h"
#include "FADEC_Defines_H/IO_Types.h"
#include "FADEC_Defines_H/Control_Types.h"
#include "FADEC_Defines_H/FaultSim_Types.h"

// External inputs structure
typedef struct {

    // Struct for sensors reading
    SensedPars Sensors;
    // Struct for digital keys
    keys_t keys;
    // Struct for fault injection during simulation
    SensorFaults SoftSimFaults;

    // Reads altitude value
    floating Altitude;
    // Reads Mach number value
    floating MN;
    // Reads thrust reference value
    floating RefCAN;
    // Reads on-off command
    int OnOffCom;
    // Reset command
    int Reset;
    // SkipStart command - for simulation from defined initial conditions
    int SkipStart;
    // Flag for authorizing execution of control law
    int Authorize;
    // Intial fuel flow value - HIL simulation
    floating Wf0; 
    // Lever functioning mode - automatic or manual control after idle
    int LeverMode;
    // Startin mode - manual or automatic start
    int Mode; 
    // Oil pump manual rpm value
    floating OPRPMManual;
    // Left booster status
    int BoosterLStatus;
    // Right booster status
    int BoosterRStatus; 
    // Used in electric motor starting algorithm
    floating StrtRPMAct;
    // Variable indicating the simulation mode - used to control Authorize in HIL usage
    int simMod;
    // Variable indicating CAN fault
    int CAN_1_Fault;

} ExpInputs_t;

// External outputs struct
typedef struct {

            /* Updates das saídas */
            // 1 - Wf                           (Fuel flow value - musst normalize)
            // 2 - ContStart.StrtRPMAct         (Oil pump rpm - must normalize)
            // 3 - digital.out                  (digital outputs)
            // 4 - EngStatus.EngineStatus       (Engine status variable)

            // Struct for fault status
            EngineFaults FaultStatus;
            // Struct for fault warnings
            EngineFaults FaultWarning;

            // Fuel flow
            floating Wf;
            // Dital output bits
            digital_t digitalout;
            // Electric motor starting variable
            floating StrRPMAct;
            // Engine status bits
            uint64_t EngineStatus;
            // // Flag indicating reset has been accomplished
            // int ResetOK;

} ExpOutputs_t;

#endif /* FADECLITEEXPSTR_H_ */
