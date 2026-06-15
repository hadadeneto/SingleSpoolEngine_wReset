/*
 * PIMinMax.h
 *
 *  Created on: Dec 11, 2019
 *      Author: anton
 */

#ifndef PIMINMAX_H_
#define PIMINMAX_H_

void PIMinMaxTJ1200(struct ControlStart *ContStartP, struct ControllerInput *ContInputP, struct ControllerOutput *ContOutputP, unsigned int *digitalP, unsigned int *keysP, double *NcFANContMtxP, double *FNperContMtxP, double *N_KpMtxP, double *N_KiMtxP, double Tsample);
#endif /* PIMINMAX_H_ */
