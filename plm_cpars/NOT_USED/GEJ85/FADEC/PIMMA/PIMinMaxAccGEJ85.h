/*
 * PIMinMax.h
 *
 *  Created on: Dec 11, 2019
 *      Author: anton
 */

#ifndef PIMINMAXGEJ85_H_
#define PIMINMAXGEJ85_H_

void PIMinMaxAccGEJ85(struct ControlStart *ContStartP, struct ControllerInput *ContInputP, struct ControllerOutput *ContOutputP, unsigned int *digitalP, unsigned int *keysP, double *NcFANContMtxP, double *FNperContMtxP, double *N_KpMtxP, double *N_KiMtxP, double Tsample);

#endif /* PIMINMAXGEJ85_H_ */
