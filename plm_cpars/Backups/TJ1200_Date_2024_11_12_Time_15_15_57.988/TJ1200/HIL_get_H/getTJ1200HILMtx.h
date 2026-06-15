#ifndef GETTJ1200HILMTX_H
#define GETTJ1200HILMTX_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* MAIN FUNCTION FOR LOADING MATRICES USED BY HIL CODE */ 

void getTJ1200HILMtx(double *AshMtx, double *AwmMtx, double *BshMtx, double *BwmMtx, double *EffFANMapMtx, 
     double *EffHPCMapMtx, double *EffHPTMapMtx, double *NcFANMapMtx, double *NcHPTMapMtx, double *NcMtx, 
     double *PRFANMapMtx, double *PRFANStallMtx, double *PRHPCStallMtx, double *PRHPTMapMtx, double *Pt21DMtx, 
     double *Pt21Mtx, double *Pt6DMtx, double *Pt6Mtx, double *RPMshMtx, double *RPMwmMtx, 
     double *Tt21DMtx, double *Tt21Mtx, double *Tt3DMtx, double *Tt3Mtx, double *Tt4CshMtx, 
     double *Tt4DshMtx, double *Tt4shMtx, double *Tt6DMtx, double *Tt6Mtx, double *WcFANMapMtx, 
     double *WcFANStallMtx, double *WcHPCStallMtx, double *WcHPTMapMtx, double *WfshMtx, double *NcFANshMtx, 
     double *WfwmMtx, double *Pt3shMtx, double *Pt3DshMtx, double *Pt21wmMtx, double *Pt21DwmMtx, 
     double *Pt3wmMtx, double *Pt3DwmMtx, double *Pt5wmMtx, double *Pt5DwmMtx, double *Pt6wmMtx, 
     double *Pt6DwmMtx, double *Tt21wmMtx, double *Tt21DwmMtx, double *Tt3wmMtx, double *Tt3DwmMtx, 
     double *Tt4wmMtx, double *Tt4DwmMtx, double *Tt5wmMtx, double *Tt5DwmMtx, double *Tt6wmMtx, 
     double *Tt6DwmMtx, double *Pt21shMtx, double *Pt21DshMtx, double *Pt5shMtx, double *Pt5DshMtx, 
     double *Pt6shMtx, double *Pt6DshMtx, double *Tt21shMtx, double *Tt21DshMtx, double *Tt3shMtx, 
     double *Tt3DshMtx, double *Tt5shMtx, double *Tt5DshMtx, double *Tt6shMtx, double *Tt6DshMtx);

#endif