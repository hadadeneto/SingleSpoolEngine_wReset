/*
 * PIMinMax.h
 *
 *  Created on: Dec 11, 2019
 *      Author: anton
 */

#ifndef PIMINMAX_H_
#define PIMINMAX_H_

/* Declares the funcion PI with Min-Max structure and Reference Filter */
void PIMinMaxRF(double *AltLinVecP, double *MNLinVecP, double *NcVecP, double *ASVecP, double *DSVecP,
                    double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP,
                    double *DeltaMtx2DP, double *DeltaMtx2DHP, double *DeltaMtx1DP, double *DeltaMtx1DHP,
                    struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                    struct ControllerInput *ContInputP, 
                    struct ControllerOutput *ContOutputP, unsigned int *digitalP, 
                    unsigned int *keysP, double *DeltaMtxP, double *NcFANContMtxP, 
                    double *FNcMaxContMtxP, double *FNperContMtxP, double *N_KpMtxP, 
                    double *N_KiMtxP, double Tsample);

#endif /* PIMINMAX_H_ */
