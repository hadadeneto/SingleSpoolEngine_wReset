#ifndef QSMCMINMAXGEJ85_H
#define QSMCMINMAXGEJ85_H


/*		T-MATS -- functions.h
 * % *************************************************************************
 * % written by Jeffryes Chapman
 * % NASA Glenn Research Center, Cleveland, OH
 * % August 2nd, 2016
 * %
 * %  This is a file that contains various functions for use in the T-MATS C-code
 * % *************************************************************************/

//Index Finder - Finds the necessary indexes for matrix interpolation
//void QSMCMinMaxGEJ85(struct ControlStart *ContStartP, struct ControllerInput *ContInputP, struct ControllerOutput *ContOutputP, unsigned int *digitalP, unsigned int *keysP, double *NcFANContMtxP, double *FNperContMtxP, double *ThetaMtxP, double *DeltaMtxP, double *AMtxP, double *BMtxP, double *CTMtxP, double *DTMtxP, double *Tt5MtxP, double *WfMtxP, struct QSMCInput *QSMCInP);
void QSMCMinMaxGEJ85(struct ControlStart *ContStartP, struct ControllerInput *ContInputP, struct ControllerOutput *ContOutputP, unsigned int *digitalP, unsigned int *keysP, double *NcFANContMtxP, double *FNperContMtxP, double *ThetaMtxP, double *DeltaMtxP, double *AMtxP, double *BMtxP, double *CTMtxP, double *DTMtxP, double *Tt5MtxP, double *WfMtxP, double Tsample);
#endif  /* QSMCMINMAXGEJ85_H */
