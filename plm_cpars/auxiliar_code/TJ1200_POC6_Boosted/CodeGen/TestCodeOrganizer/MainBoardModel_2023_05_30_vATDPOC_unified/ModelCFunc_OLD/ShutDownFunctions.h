#ifndef SHUTDOWN_FUNCTIONS_H
#define SHUTDOWN_FUNCTIONS_H


/*		T-MATS -- functions.h
 * % *************************************************************************
 * % written by Jeffryes Chapman
 * % NASA Glenn Research Center, Cleveland, OH
 * % August 2nd, 2016
 * %
 * %  This is a file that contains various functions for use in the T-MATS C-code
 * % *************************************************************************/

/* functions_TMATS.c */

#include "Control_Types.h"
#include "IO_Types.h"
#include "FaultSim_Types.h"

void EmergencyShutDown(struct ControllerInput *ContInputP, struct ControllerInput *ContInputEmptyP,
						 struct ControllerOutput *ContOutputP, struct ControllerOutput *ContOutputEmptyP,
						 struct ControlStart *ContStartP, struct ControlStart *ContStartEmptyP, 
                         struct ControllerGeneral *ContGenOilP, struct ControllerGeneral *ContGenEmptyP,
                         digital_t *digitalP, int Emergency);

void ShutDownRef(int ShutDown, struct ControllerInput *ContInputP, struct ControllerOutput *ContOutputP, struct ControllerConstants *ContContsP, double Ts);

void ShutDownRamp(struct ControllerInput *ContInputP, struct ControllerInput *ContInputEmptyP,
                  struct ControllerOutput *ContOutputP, struct ControllerOutput *ContOutputEmptyP,
                  struct ControlStart *ContStartP, struct ControlStart *ContStartEmptyP, 
                  struct ControllerGeneral *ContGenOilP, struct ControllerGeneral *ContGenEmptyP,
                  digital_t *digitalP, struct ControllerConstants *ContConstP, double Ts);

void FailureShutDown(EngineFaults *FaultStatusP, int *Failure);



#endif  /* SHUTDOWN_FUNCTIONS_H */
