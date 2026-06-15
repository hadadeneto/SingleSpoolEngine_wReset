#ifndef PERIPHERALDYN_H
#define PERIPHERALDYN_H


/*		FADEC -- FailSafeFunctoins.h
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % Turbomachine, S�o Jos� dos Campos, SP
 * % July, 2021
 * %
 * %  This is a file that contains various functions for use in the FADEC C-code
 * % *************************************************************************/

/* PeripheralDyn.c */

#include "FaultSim_Types.h"
#include "Control_Types.h"

void FirstOrderSensor(double RawVar, double *SensedVar, double FiltConst);

#endif  /* PERIPHERALDYN_H */
