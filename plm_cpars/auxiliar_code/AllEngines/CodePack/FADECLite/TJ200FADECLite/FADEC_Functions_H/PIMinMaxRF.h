/*
 * PIMinMax.h
 *
 *  Created on: Dec 11, 2019
 *      Author: anton
 */

#ifndef PIMINMAX_H_
#define PIMINMAX_H_

#include "../FADEC_Defines_H/FloatPoint_Precision.h"

/* Declares the funcion PI with Min-Max structure and Reference Filter */
void PIMinMaxRF(floating *AltLinVecP, floating *MNLinVecP, floating *NcVecP, floating *ASVecP, floating *DSVecP,
                floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP,
                floating *DeltaMtx2DP, floating *DeltaMtx2DHP, floating *DeltaMtx1DP, floating *DeltaMtx1DHP,
                struct ControllerConstants *ContConst, struct ControlStart *ContStartP, 
                struct ControllerInput *ContInputP, 
                struct ControllerOutput *ContOutputP, unsigned int *digitalP, 
                unsigned int *keysP, floating *DeltaMtxP, floating *NcFANContMtxP, 
                floating *FNcMaxContMtxP, floating *FNperContMtxP, floating *N_KpMtxP, floating *N_KpshMtxP,
                floating *N_KiMtxP, floating *N_KishMtxP, floating Tsample);

#endif /* PIMINMAX_H_ */
