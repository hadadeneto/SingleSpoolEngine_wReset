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

#include "../FADEC_Defines_H/FaultSim_Types.h"
#include "../FADEC_Defines_H/Control_Types.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"

void FirstOrderSensor(floating RawVar, floating *SensedVar, floating FiltConst);

#endif  /* PERIPHERALDYN_H */
