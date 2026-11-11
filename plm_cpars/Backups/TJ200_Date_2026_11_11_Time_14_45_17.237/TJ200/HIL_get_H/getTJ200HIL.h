#ifndef GETTJ200HIL_H
#define GETTJ200HIL_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* FUNCTIONS FOR LOADING MATRICES USED BY HIL CODE */

/* Gets TJ200AshMtx Matrix */
void getTJ200AshMtx(floating *Pointer);

/* Gets TJ200AwmMtx Matrix */
void getTJ200AwmMtx(floating *Pointer);

/* Gets TJ200BshMtx Matrix */
void getTJ200BshMtx(floating *Pointer);

/* Gets TJ200BwmMtx Matrix */
void getTJ200BwmMtx(floating *Pointer);

/* Gets TJ200EffFANMapMtx Matrix */
void getTJ200EffFANMapMtx(floating *Pointer);

/* Gets TJ200EffHPCMapMtx Matrix */
void getTJ200EffHPCMapMtx(floating *Pointer);

/* Gets TJ200EffHPTMapMtx Matrix */
void getTJ200EffHPTMapMtx(floating *Pointer);

/* Gets TJ200NcFANMapMtx Matrix */
void getTJ200NcFANMapMtx(floating *Pointer);

/* Gets TJ200NcHPTMapMtx Matrix */
void getTJ200NcHPTMapMtx(floating *Pointer);

/* Gets TJ200NcMtx Matrix */
void getTJ200NcMtx(floating *Pointer);

/* Gets TJ200PRFANMapMtx Matrix */
void getTJ200PRFANMapMtx(floating *Pointer);

/* Gets TJ200PRFANStallMtx Matrix */
void getTJ200PRFANStallMtx(floating *Pointer);

/* Gets TJ200PRHPCStallMtx Matrix */
void getTJ200PRHPCStallMtx(floating *Pointer);

/* Gets TJ200PRHPTMapMtx Matrix */
void getTJ200PRHPTMapMtx(floating *Pointer);

/* Gets TJ200Pt21DMtx Matrix */
void getTJ200Pt21DMtx(floating *Pointer);

/* Gets TJ200Pt21Mtx Matrix */
void getTJ200Pt21Mtx(floating *Pointer);

/* Gets TJ200Pt6DMtx Matrix */
void getTJ200Pt6DMtx(floating *Pointer);

/* Gets TJ200Pt6Mtx Matrix */
void getTJ200Pt6Mtx(floating *Pointer);

/* Gets TJ200RPMshMtx Matrix */
void getTJ200RPMshMtx(floating *Pointer);

/* Gets TJ200RPMwmMtx Matrix */
void getTJ200RPMwmMtx(floating *Pointer);

/* Gets TJ200Tt21DMtx Matrix */
void getTJ200Tt21DMtx(floating *Pointer);

/* Gets TJ200Tt21Mtx Matrix */
void getTJ200Tt21Mtx(floating *Pointer);

/* Gets TJ200Tt3DMtx Matrix */
void getTJ200Tt3DMtx(floating *Pointer);

/* Gets TJ200Tt3Mtx Matrix */
void getTJ200Tt3Mtx(floating *Pointer);

/* Gets TJ200Tt4CshMtx Matrix */
void getTJ200Tt4CshMtx(floating *Pointer);

/* Gets TJ200Tt4DshMtx Matrix */
void getTJ200Tt4DshMtx(floating *Pointer);

/* Gets TJ200Tt4shMtx Matrix */
void getTJ200Tt4shMtx(floating *Pointer);

/* Gets TJ200Tt6DMtx Matrix */
void getTJ200Tt6DMtx(floating *Pointer);

/* Gets TJ200Tt6Mtx Matrix */
void getTJ200Tt6Mtx(floating *Pointer);

/* Gets TJ200WcFANMapMtx Matrix */
void getTJ200WcFANMapMtx(floating *Pointer);

/* Gets TJ200WcFANStallMtx Matrix */
void getTJ200WcFANStallMtx(floating *Pointer);

/* Gets TJ200WcHPCStallMtx Matrix */
void getTJ200WcHPCStallMtx(floating *Pointer);

/* Gets TJ200WcHPTMapMtx Matrix */
void getTJ200WcHPTMapMtx(floating *Pointer);

/* Gets TJ200WfshMtx Matrix */
void getTJ200WfshMtx(floating *Pointer);

/* Gets TJ200NcFANshMtx Matrix */
void getTJ200NcFANshMtx(floating *Pointer);

/* Gets TJ200WfwmMtx Matrix */
void getTJ200WfwmMtx(floating *Pointer);

/* Gets TJ200Pt3shMtx Matrix */
void getTJ200Pt3shMtx(floating *Pointer);

/* Gets TJ200Pt3DshMtx Matrix */
void getTJ200Pt3DshMtx(floating *Pointer);

/* Gets TJ200Pt21wmMtx Matrix */
void getTJ200Pt21wmMtx(floating *Pointer);

/* Gets TJ200Pt21DwmMtx Matrix */
void getTJ200Pt21DwmMtx(floating *Pointer);

/* Gets TJ200Pt3wmMtx Matrix */
void getTJ200Pt3wmMtx(floating *Pointer);

/* Gets TJ200Pt3DwmMtx Matrix */
void getTJ200Pt3DwmMtx(floating *Pointer);

/* Gets TJ200Pt5wmMtx Matrix */
void getTJ200Pt5wmMtx(floating *Pointer);

/* Gets TJ200Pt5DwmMtx Matrix */
void getTJ200Pt5DwmMtx(floating *Pointer);

/* Gets TJ200Pt6wmMtx Matrix */
void getTJ200Pt6wmMtx(floating *Pointer);

/* Gets TJ200Pt6DwmMtx Matrix */
void getTJ200Pt6DwmMtx(floating *Pointer);

/* Gets TJ200Tt21wmMtx Matrix */
void getTJ200Tt21wmMtx(floating *Pointer);

/* Gets TJ200Tt21DwmMtx Matrix */
void getTJ200Tt21DwmMtx(floating *Pointer);

/* Gets TJ200Tt3wmMtx Matrix */
void getTJ200Tt3wmMtx(floating *Pointer);

/* Gets TJ200Tt3DwmMtx Matrix */
void getTJ200Tt3DwmMtx(floating *Pointer);

/* Gets TJ200Tt4wmMtx Matrix */
void getTJ200Tt4wmMtx(floating *Pointer);

/* Gets TJ200Tt4DwmMtx Matrix */
void getTJ200Tt4DwmMtx(floating *Pointer);

/* Gets TJ200Tt5wmMtx Matrix */
void getTJ200Tt5wmMtx(floating *Pointer);

/* Gets TJ200Tt5DwmMtx Matrix */
void getTJ200Tt5DwmMtx(floating *Pointer);

/* Gets TJ200Tt6wmMtx Matrix */
void getTJ200Tt6wmMtx(floating *Pointer);

/* Gets TJ200Tt6DwmMtx Matrix */
void getTJ200Tt6DwmMtx(floating *Pointer);

/* Gets TJ200Pt21shMtx Matrix */
void getTJ200Pt21shMtx(floating *Pointer);

/* Gets TJ200Pt21DshMtx Matrix */
void getTJ200Pt21DshMtx(floating *Pointer);

/* Gets TJ200Pt5shMtx Matrix */
void getTJ200Pt5shMtx(floating *Pointer);

/* Gets TJ200Pt5DshMtx Matrix */
void getTJ200Pt5DshMtx(floating *Pointer);

/* Gets TJ200Pt6shMtx Matrix */
void getTJ200Pt6shMtx(floating *Pointer);

/* Gets TJ200Pt6DshMtx Matrix */
void getTJ200Pt6DshMtx(floating *Pointer);

/* Gets TJ200Tt21shMtx Matrix */
void getTJ200Tt21shMtx(floating *Pointer);

/* Gets TJ200Tt21DshMtx Matrix */
void getTJ200Tt21DshMtx(floating *Pointer);

/* Gets TJ200Tt3shMtx Matrix */
void getTJ200Tt3shMtx(floating *Pointer);

/* Gets TJ200Tt3DshMtx Matrix */
void getTJ200Tt3DshMtx(floating *Pointer);

/* Gets TJ200Tt5shMtx Matrix */
void getTJ200Tt5shMtx(floating *Pointer);

/* Gets TJ200Tt5DshMtx Matrix */
void getTJ200Tt5DshMtx(floating *Pointer);

/* Gets TJ200Tt6shMtx Matrix */
void getTJ200Tt6shMtx(floating *Pointer);

/* Gets TJ200Tt6DshMtx Matrix */
void getTJ200Tt6DshMtx(floating *Pointer);

#endif