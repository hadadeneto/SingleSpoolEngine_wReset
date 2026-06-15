/*
 * BearingModel.h
 *
 *  Created on: Aug 11, 2022
 *      Author: anton
 */

#ifndef BEARINGMODEL_H_
#define BEARINGMODEL_H_

/* Declares the funcion PI with Min-Max structure and Reference Filter */
void BearingModel(struct BearingPars *BearModP, double *RPMEVecP, double *TNOilP, double *TMaxRPMP);

#endif /* BEARINGMODEL_H_ */
