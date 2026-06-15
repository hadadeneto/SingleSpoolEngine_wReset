/*
 * PIMinMax.h
 *
 *  Created on: Dec 11, 2019
 *      Author: anton
 */

#ifndef PIFUELPUMP_H_
#define PIFUELPUMP_H_

/* Declares the funcion PI with Min-Max structure and Reference Filter */
void PIFuelPump(struct ControllerConstants* ContConst, struct ControllerInput* ContInputP,
    struct ControllerOutput* ContOutputP, double Tsample);

#endif /* PIFUELPUMP_H_ */
