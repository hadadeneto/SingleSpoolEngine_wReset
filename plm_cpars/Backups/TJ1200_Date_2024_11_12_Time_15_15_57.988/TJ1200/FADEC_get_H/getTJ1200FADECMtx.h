#ifndef GETTJ1200FADECMTX_H
#define GETTJ1200FADECMTX_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* MAIN FUNCTION FOR LOADING MATRICES USED BY FADEC CODE */ 

void getTJ1200FADECMtx(double *AMtx, double *ASVec, double *AltLinVec, double *BMtx, double *DSVec, 
     double *DeltaMtx, double *FNcMaxContMtx, double *FNperContMtx, double *MNLinVec, double *N_KiMtx, 
     double *N_KpMtx, double *NcFANContMtx, double *NcHPCMapMtx, double *NcVec, double *PRHPCMapMtx, 
     double *Pt3DMtx, double *Pt3Mtx, double *Pt5DMtx, double *Pt5Mtx, double *Ts0Mtx, 
     double *Tt4DMtx, double *Tt4Mtx, double *Tt5DMtx, double *Tt5Mtx, double *WcHPCMapMtx, 
     double *WfMtx, double *N_KpshMtx, double *N_KishMtx, double *NcFANshContMtx);

#endif