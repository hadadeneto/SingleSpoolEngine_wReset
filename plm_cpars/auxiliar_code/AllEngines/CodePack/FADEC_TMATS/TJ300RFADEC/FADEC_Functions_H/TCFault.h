#ifndef TCFAULT_FUNCTIONS_H
#define TCFAULT_FUNCTIONS_H

/*		HIL -- FaultSimFunctions.h
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % Autust 19, 2021
 * %
 * %  This is a file that contains various functions for use in the HIL code
 * % *************************************************************************/

/* TCFault.c */

#include "../FADEC_Defines_H/FaultSim_Types.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"

void TCFault(struct SensedPars *SensorsP, SensorFaults *FaultsP, SensorFaults *FaultSensAuthP, TCFaults *Ts2_0, TCFaults *Ts2_1, TCFaults *Tt4_0, TCFaults *Tt4_1, TCFaults *Tt4_2, TCFaults *TBear_0, TCFaults *TBear_1, TCFaults *TBear_2, floating TCOpen); 

#endif  /* TCFAULT_FUNCTIONS_H */
