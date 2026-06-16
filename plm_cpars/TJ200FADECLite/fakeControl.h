/*
 * fakeControl.h
 *
 *  Created on: 13 de mar. de 2026
 *      Author: Marcel
 */

#ifndef FADEC_CORE_CONTROL_FAKECONTROL_H_
#define FADEC_CORE_CONTROL_FAKECONTROL_H_

#include "fadec_core.h"

void fakeControl_init(void);
// ONLY FOR DEBUG! Not using const only for debugging
//void fakeControl_loop(const ControlLoop_Inputs_t* control_inputs, ControlLoop_Outputs_t* control_outputs);
void fakeControl_loop(ControlLoop_Inputs_t* control_inputs, ControlLoop_Outputs_t* control_outputs);
int fakeControl_allowReset(void);

#endif /* FADEC_CORE_CONTROL_FAKECONTROL_H_ */
