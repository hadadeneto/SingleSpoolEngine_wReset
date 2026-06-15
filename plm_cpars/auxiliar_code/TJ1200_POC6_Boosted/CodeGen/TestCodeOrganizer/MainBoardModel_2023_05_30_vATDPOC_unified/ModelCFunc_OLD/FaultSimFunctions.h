#ifndef FAULTSIM_FUNCTIONS_H
#define FAULTSIM_FUNCTIONS_H

/*		HIL -- FaultSimFunctions.h
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % Autust 19, 2021
 * %
 * %  This is a file that contains various functions for use in the HIL code
 * % *************************************************************************/

/* FaultSimFunctions.c */

void BlowOutSim(FaultDetect *FaultsP, double *Wf);

void IgnitionFault(FaultDetect *FaultsP, int *Ignition);

void SensFaultSim(SensorFaults *FaultsP, struct SensedPars *SensorsP, struct EnginePars *EngParsP);

void BiasFaultSim(FaultDetect *FaultsP, struct SensedPars *SensBiasP, struct SensedPars *SensorsP);

void SysFaultSim(FaultDetect *FaultsP, struct EnginePars *EngParsP, struct EngineOutput *EngOutputP);

void SensorsUpdt(struct SensedPars *SensorsP, struct EngineOutput *EngOutputP);

#endif  /* FAULTSIM_FUNCTIONS_H */
