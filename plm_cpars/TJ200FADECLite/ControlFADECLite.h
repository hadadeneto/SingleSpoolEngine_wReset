/*
 * FADECLiteExpStr.h
 *
 *  Created on: 19 de jun. de 2026
 *      Author: Antonio Hadade Neto
 */

#ifndef CONTROLFADECLITE_H_
#define CONTROLFADECLITE_H_

#include <stdint.h>
#include "FADEC_Defines_H/FloatPoint_Precision.h"
#include "FADEC_Defines_H/Control_Types.h"
#include "FADEC_Defines_H/IO_Types.h"
#include "FADEC_Defines_H/FaultSim_Types.h"
#include "FADECLiteExpStr.h"

// The function below initites engine specifica variables and matrices
void FADECInitVars(void);

// The function executes a software reset in the FADEC
int FADECReset(void);

// Updates the controller status based on read inputs
void ControlUpdate(SensedPars* SensorsExp, keys_t* keysExp, SensorFaults* SoftSimFaultsExp, ExpInputs_t* ExpIn, ExpOutputs_t* ExpOut); 


#endif /* CONTROLFADECLITE_H_ */
