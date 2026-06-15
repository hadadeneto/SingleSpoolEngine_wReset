/*
 * BearingModel.h
 *
 *  Created on: Aug 11, 2022
 *      Author: anton
 */

#ifndef BEARINGMODEL_H_
#define BEARINGMODEL_H_

#include "../FADEC_Defines_H/FloatPoint_Precision.h"

/* Declares the funcion PI with Min-Max structure and Reference Filter */
void BearingModel(struct BearingPars *BearModP, floating *RPMEVecP, floating *TNOilP, floating *TMaxRPMP);

#endif /* BEARINGMODEL_H_ */
