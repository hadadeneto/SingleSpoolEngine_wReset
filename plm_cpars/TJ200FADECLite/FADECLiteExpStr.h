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

// External inputs structure
typedef struct {

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
    // Percent lever value
    int valorManete;
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
    //
    int simMod;

} ExpInputs_t;

// External outputs struct
typedef struct {

            /* Updates das saídas */
            // 1 - Wf                           (Fuel flow value - musst normalize)
            // 2 - ContStart.StrtRPMAct         (Oil pump rpm - must normalize)
            // 3 - digital.out                  (digital outputs)
            // 4 - EngStatus.EngineStatus       (Engine status variable)

            // Fuel flow
            floating Wf;
            // Dital output bits
            digital_t digitalout;
            // Electric motor starting variable
            floating StrRPMAct;
            // Engine status bits
            uint64_t EngineStatus;
            // Flag indicating reset has been accomplished
            int ResetOK;

} ExpOutputs_t;

#endif /* FADECLITEEXPSTR_H_ */
