#ifndef GETTF1200FADECMTX_H
#define GETTF1200FADECMTX_H

/* MAIN FUNCTION FOR LOADING MATRICES USED BY FADEC CODE */ 

void getTF1200FADECMtx(double *AMtx, double *ASVec, double *AltLinVec, double *BMtx, double *DSVec, 
     double *DeltaMtx, double *FNcMaxContMtx, double *FNperContMtx, double *MNLinVec, double *N_KiMtx, 
     double *N_KpMtx, double *NcFANContMtx, double *NcHPCMapMtx, double *NcVec, double *PRHPCMapMtx, 
     double *Pt3DMtx, double *Pt3Mtx, double *Pt5DMtx, double *Pt5Mtx, double *Ts0Mtx, 
     double *Tt4DMtx, double *Tt4Mtx, double *Tt5DMtx, double *Tt5Mtx, double *WcHPCMapMtx, 
     double *WfMtx, double *N_KpshMtx, double *N_KishMtx, double *NcFANshContMtx);

#endif