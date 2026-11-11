#ifndef GETTJ40HIL_H
#define GETTJ40HIL_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* FUNCTIONS FOR LOADING MATRICES USED BY HIL CODE */

/* Gets TJ40AshMtx Matrix */
void getTJ40AshMtx(floating *Pointer);

/* Gets TJ40AwmMtx Matrix */
void getTJ40AwmMtx(floating *Pointer);

/* Gets TJ40BshMtx Matrix */
void getTJ40BshMtx(floating *Pointer);

/* Gets TJ40BwmMtx Matrix */
void getTJ40BwmMtx(floating *Pointer);

/* Gets TJ40EffFANMapMtx Matrix */
void getTJ40EffFANMapMtx(floating *Pointer);

/* Gets TJ40EffHPCMapMtx Matrix */
void getTJ40EffHPCMapMtx(floating *Pointer);

/* Gets TJ40EffHPTMapMtx Matrix */
void getTJ40EffHPTMapMtx(floating *Pointer);

/* Gets TJ40NcFANMapMtx Matrix */
void getTJ40NcFANMapMtx(floating *Pointer);

/* Gets TJ40NcHPTMapMtx Matrix */
void getTJ40NcHPTMapMtx(floating *Pointer);

/* Gets TJ40NcMtx Matrix */
void getTJ40NcMtx(floating *Pointer);

/* Gets TJ40PRFANMapMtx Matrix */
void getTJ40PRFANMapMtx(floating *Pointer);

/* Gets TJ40PRFANStallMtx Matrix */
void getTJ40PRFANStallMtx(floating *Pointer);

/* Gets TJ40PRHPCStallMtx Matrix */
void getTJ40PRHPCStallMtx(floating *Pointer);

/* Gets TJ40PRHPTMapMtx Matrix */
void getTJ40PRHPTMapMtx(floating *Pointer);

/* Gets TJ40Pt21DMtx Matrix */
void getTJ40Pt21DMtx(floating *Pointer);

/* Gets TJ40Pt21Mtx Matrix */
void getTJ40Pt21Mtx(floating *Pointer);

/* Gets TJ40Pt6DMtx Matrix */
void getTJ40Pt6DMtx(floating *Pointer);

/* Gets TJ40Pt6Mtx Matrix */
void getTJ40Pt6Mtx(floating *Pointer);

/* Gets TJ40RPMshMtx Matrix */
void getTJ40RPMshMtx(floating *Pointer);

/* Gets TJ40RPMwmMtx Matrix */
void getTJ40RPMwmMtx(floating *Pointer);

/* Gets TJ40Tt21DMtx Matrix */
void getTJ40Tt21DMtx(floating *Pointer);

/* Gets TJ40Tt21Mtx Matrix */
void getTJ40Tt21Mtx(floating *Pointer);

/* Gets TJ40Tt3DMtx Matrix */
void getTJ40Tt3DMtx(floating *Pointer);

/* Gets TJ40Tt3Mtx Matrix */
void getTJ40Tt3Mtx(floating *Pointer);

/* Gets TJ40Tt4CshMtx Matrix */
void getTJ40Tt4CshMtx(floating *Pointer);

/* Gets TJ40Tt4DshMtx Matrix */
void getTJ40Tt4DshMtx(floating *Pointer);

/* Gets TJ40Tt4shMtx Matrix */
void getTJ40Tt4shMtx(floating *Pointer);

/* Gets TJ40Tt6DMtx Matrix */
void getTJ40Tt6DMtx(floating *Pointer);

/* Gets TJ40Tt6Mtx Matrix */
void getTJ40Tt6Mtx(floating *Pointer);

/* Gets TJ40WcFANMapMtx Matrix */
void getTJ40WcFANMapMtx(floating *Pointer);

/* Gets TJ40WcFANStallMtx Matrix */
void getTJ40WcFANStallMtx(floating *Pointer);

/* Gets TJ40WcHPCStallMtx Matrix */
void getTJ40WcHPCStallMtx(floating *Pointer);

/* Gets TJ40WcHPTMapMtx Matrix */
void getTJ40WcHPTMapMtx(floating *Pointer);

/* Gets TJ40WfshMtx Matrix */
void getTJ40WfshMtx(floating *Pointer);

/* Gets TJ40NcFANshMtx Matrix */
void getTJ40NcFANshMtx(floating *Pointer);

/* Gets TJ40WfwmMtx Matrix */
void getTJ40WfwmMtx(floating *Pointer);

/* Gets TJ40Pt3shMtx Matrix */
void getTJ40Pt3shMtx(floating *Pointer);

/* Gets TJ40Pt3DshMtx Matrix */
void getTJ40Pt3DshMtx(floating *Pointer);

/* Gets TJ40Pt21wmMtx Matrix */
void getTJ40Pt21wmMtx(floating *Pointer);

/* Gets TJ40Pt21DwmMtx Matrix */
void getTJ40Pt21DwmMtx(floating *Pointer);

/* Gets TJ40Pt3wmMtx Matrix */
void getTJ40Pt3wmMtx(floating *Pointer);

/* Gets TJ40Pt3DwmMtx Matrix */
void getTJ40Pt3DwmMtx(floating *Pointer);

/* Gets TJ40Pt5wmMtx Matrix */
void getTJ40Pt5wmMtx(floating *Pointer);

/* Gets TJ40Pt5DwmMtx Matrix */
void getTJ40Pt5DwmMtx(floating *Pointer);

/* Gets TJ40Pt6wmMtx Matrix */
void getTJ40Pt6wmMtx(floating *Pointer);

/* Gets TJ40Pt6DwmMtx Matrix */
void getTJ40Pt6DwmMtx(floating *Pointer);

/* Gets TJ40Tt21wmMtx Matrix */
void getTJ40Tt21wmMtx(floating *Pointer);

/* Gets TJ40Tt21DwmMtx Matrix */
void getTJ40Tt21DwmMtx(floating *Pointer);

/* Gets TJ40Tt3wmMtx Matrix */
void getTJ40Tt3wmMtx(floating *Pointer);

/* Gets TJ40Tt3DwmMtx Matrix */
void getTJ40Tt3DwmMtx(floating *Pointer);

/* Gets TJ40Tt4wmMtx Matrix */
void getTJ40Tt4wmMtx(floating *Pointer);

/* Gets TJ40Tt4DwmMtx Matrix */
void getTJ40Tt4DwmMtx(floating *Pointer);

/* Gets TJ40Tt5wmMtx Matrix */
void getTJ40Tt5wmMtx(floating *Pointer);

/* Gets TJ40Tt5DwmMtx Matrix */
void getTJ40Tt5DwmMtx(floating *Pointer);

/* Gets TJ40Tt6wmMtx Matrix */
void getTJ40Tt6wmMtx(floating *Pointer);

/* Gets TJ40Tt6DwmMtx Matrix */
void getTJ40Tt6DwmMtx(floating *Pointer);

/* Gets TJ40Pt21shMtx Matrix */
void getTJ40Pt21shMtx(floating *Pointer);

/* Gets TJ40Pt21DshMtx Matrix */
void getTJ40Pt21DshMtx(floating *Pointer);

/* Gets TJ40Pt5shMtx Matrix */
void getTJ40Pt5shMtx(floating *Pointer);

/* Gets TJ40Pt5DshMtx Matrix */
void getTJ40Pt5DshMtx(floating *Pointer);

/* Gets TJ40Pt6shMtx Matrix */
void getTJ40Pt6shMtx(floating *Pointer);

/* Gets TJ40Pt6DshMtx Matrix */
void getTJ40Pt6DshMtx(floating *Pointer);

/* Gets TJ40Tt21shMtx Matrix */
void getTJ40Tt21shMtx(floating *Pointer);

/* Gets TJ40Tt21DshMtx Matrix */
void getTJ40Tt21DshMtx(floating *Pointer);

/* Gets TJ40Tt3shMtx Matrix */
void getTJ40Tt3shMtx(floating *Pointer);

/* Gets TJ40Tt3DshMtx Matrix */
void getTJ40Tt3DshMtx(floating *Pointer);

/* Gets TJ40Tt5shMtx Matrix */
void getTJ40Tt5shMtx(floating *Pointer);

/* Gets TJ40Tt5DshMtx Matrix */
void getTJ40Tt5DshMtx(floating *Pointer);

/* Gets TJ40Tt6shMtx Matrix */
void getTJ40Tt6shMtx(floating *Pointer);

/* Gets TJ40Tt6DshMtx Matrix */
void getTJ40Tt6DshMtx(floating *Pointer);

#endif