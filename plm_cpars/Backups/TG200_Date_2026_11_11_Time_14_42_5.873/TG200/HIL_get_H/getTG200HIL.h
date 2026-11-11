#ifndef GETTG200HIL_H
#define GETTG200HIL_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* FUNCTIONS FOR LOADING MATRICES USED BY HIL CODE */

/* Gets TG200AshMtx Matrix */
void getTG200AshMtx(floating *Pointer);

/* Gets TG200AwmMtx Matrix */
void getTG200AwmMtx(floating *Pointer);

/* Gets TG200BshMtx Matrix */
void getTG200BshMtx(floating *Pointer);

/* Gets TG200BwmMtx Matrix */
void getTG200BwmMtx(floating *Pointer);

/* Gets TG200EffFANMapMtx Matrix */
void getTG200EffFANMapMtx(floating *Pointer);

/* Gets TG200EffHPCMapMtx Matrix */
void getTG200EffHPCMapMtx(floating *Pointer);

/* Gets TG200EffHPTMapMtx Matrix */
void getTG200EffHPTMapMtx(floating *Pointer);

/* Gets TG200NcFANMapMtx Matrix */
void getTG200NcFANMapMtx(floating *Pointer);

/* Gets TG200NcHPTMapMtx Matrix */
void getTG200NcHPTMapMtx(floating *Pointer);

/* Gets TG200NcMtx Matrix */
void getTG200NcMtx(floating *Pointer);

/* Gets TG200PRFANMapMtx Matrix */
void getTG200PRFANMapMtx(floating *Pointer);

/* Gets TG200PRFANStallMtx Matrix */
void getTG200PRFANStallMtx(floating *Pointer);

/* Gets TG200PRHPCStallMtx Matrix */
void getTG200PRHPCStallMtx(floating *Pointer);

/* Gets TG200PRHPTMapMtx Matrix */
void getTG200PRHPTMapMtx(floating *Pointer);

/* Gets TG200Pt21DMtx Matrix */
void getTG200Pt21DMtx(floating *Pointer);

/* Gets TG200Pt21Mtx Matrix */
void getTG200Pt21Mtx(floating *Pointer);

/* Gets TG200Pt6DMtx Matrix */
void getTG200Pt6DMtx(floating *Pointer);

/* Gets TG200Pt6Mtx Matrix */
void getTG200Pt6Mtx(floating *Pointer);

/* Gets TG200RPMshMtx Matrix */
void getTG200RPMshMtx(floating *Pointer);

/* Gets TG200RPMwmMtx Matrix */
void getTG200RPMwmMtx(floating *Pointer);

/* Gets TG200Tt21DMtx Matrix */
void getTG200Tt21DMtx(floating *Pointer);

/* Gets TG200Tt21Mtx Matrix */
void getTG200Tt21Mtx(floating *Pointer);

/* Gets TG200Tt3DMtx Matrix */
void getTG200Tt3DMtx(floating *Pointer);

/* Gets TG200Tt3Mtx Matrix */
void getTG200Tt3Mtx(floating *Pointer);

/* Gets TG200Tt4CshMtx Matrix */
void getTG200Tt4CshMtx(floating *Pointer);

/* Gets TG200Tt4DshMtx Matrix */
void getTG200Tt4DshMtx(floating *Pointer);

/* Gets TG200Tt4shMtx Matrix */
void getTG200Tt4shMtx(floating *Pointer);

/* Gets TG200Tt6DMtx Matrix */
void getTG200Tt6DMtx(floating *Pointer);

/* Gets TG200Tt6Mtx Matrix */
void getTG200Tt6Mtx(floating *Pointer);

/* Gets TG200WcFANMapMtx Matrix */
void getTG200WcFANMapMtx(floating *Pointer);

/* Gets TG200WcFANStallMtx Matrix */
void getTG200WcFANStallMtx(floating *Pointer);

/* Gets TG200WcHPCStallMtx Matrix */
void getTG200WcHPCStallMtx(floating *Pointer);

/* Gets TG200WcHPTMapMtx Matrix */
void getTG200WcHPTMapMtx(floating *Pointer);

/* Gets TG200WfshMtx Matrix */
void getTG200WfshMtx(floating *Pointer);

/* Gets TG200NcFANshMtx Matrix */
void getTG200NcFANshMtx(floating *Pointer);

/* Gets TG200WfwmMtx Matrix */
void getTG200WfwmMtx(floating *Pointer);

/* Gets TG200Pt3shMtx Matrix */
void getTG200Pt3shMtx(floating *Pointer);

/* Gets TG200Pt3DshMtx Matrix */
void getTG200Pt3DshMtx(floating *Pointer);

/* Gets TG200Pt21wmMtx Matrix */
void getTG200Pt21wmMtx(floating *Pointer);

/* Gets TG200Pt21DwmMtx Matrix */
void getTG200Pt21DwmMtx(floating *Pointer);

/* Gets TG200Pt3wmMtx Matrix */
void getTG200Pt3wmMtx(floating *Pointer);

/* Gets TG200Pt3DwmMtx Matrix */
void getTG200Pt3DwmMtx(floating *Pointer);

/* Gets TG200Pt5wmMtx Matrix */
void getTG200Pt5wmMtx(floating *Pointer);

/* Gets TG200Pt5DwmMtx Matrix */
void getTG200Pt5DwmMtx(floating *Pointer);

/* Gets TG200Pt6wmMtx Matrix */
void getTG200Pt6wmMtx(floating *Pointer);

/* Gets TG200Pt6DwmMtx Matrix */
void getTG200Pt6DwmMtx(floating *Pointer);

/* Gets TG200Tt21wmMtx Matrix */
void getTG200Tt21wmMtx(floating *Pointer);

/* Gets TG200Tt21DwmMtx Matrix */
void getTG200Tt21DwmMtx(floating *Pointer);

/* Gets TG200Tt3wmMtx Matrix */
void getTG200Tt3wmMtx(floating *Pointer);

/* Gets TG200Tt3DwmMtx Matrix */
void getTG200Tt3DwmMtx(floating *Pointer);

/* Gets TG200Tt4wmMtx Matrix */
void getTG200Tt4wmMtx(floating *Pointer);

/* Gets TG200Tt4DwmMtx Matrix */
void getTG200Tt4DwmMtx(floating *Pointer);

/* Gets TG200Tt5wmMtx Matrix */
void getTG200Tt5wmMtx(floating *Pointer);

/* Gets TG200Tt5DwmMtx Matrix */
void getTG200Tt5DwmMtx(floating *Pointer);

/* Gets TG200Tt6wmMtx Matrix */
void getTG200Tt6wmMtx(floating *Pointer);

/* Gets TG200Tt6DwmMtx Matrix */
void getTG200Tt6DwmMtx(floating *Pointer);

/* Gets TG200Pt21shMtx Matrix */
void getTG200Pt21shMtx(floating *Pointer);

/* Gets TG200Pt21DshMtx Matrix */
void getTG200Pt21DshMtx(floating *Pointer);

/* Gets TG200Pt5shMtx Matrix */
void getTG200Pt5shMtx(floating *Pointer);

/* Gets TG200Pt5DshMtx Matrix */
void getTG200Pt5DshMtx(floating *Pointer);

/* Gets TG200Pt6shMtx Matrix */
void getTG200Pt6shMtx(floating *Pointer);

/* Gets TG200Pt6DshMtx Matrix */
void getTG200Pt6DshMtx(floating *Pointer);

/* Gets TG200Tt21shMtx Matrix */
void getTG200Tt21shMtx(floating *Pointer);

/* Gets TG200Tt21DshMtx Matrix */
void getTG200Tt21DshMtx(floating *Pointer);

/* Gets TG200Tt3shMtx Matrix */
void getTG200Tt3shMtx(floating *Pointer);

/* Gets TG200Tt3DshMtx Matrix */
void getTG200Tt3DshMtx(floating *Pointer);

/* Gets TG200Tt5shMtx Matrix */
void getTG200Tt5shMtx(floating *Pointer);

/* Gets TG200Tt5DshMtx Matrix */
void getTG200Tt5DshMtx(floating *Pointer);

/* Gets TG200Tt6shMtx Matrix */
void getTG200Tt6shMtx(floating *Pointer);

/* Gets TG200Tt6DshMtx Matrix */
void getTG200Tt6DshMtx(floating *Pointer);

#endif