#ifndef GETTJ700HIL_H
#define GETTJ700HIL_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* FUNCTIONS FOR LOADING MATRICES USED BY HIL CODE */

/* Gets TJ700AshMtx Matrix */
void getTJ700AshMtx(floating *Pointer);

/* Gets TJ700AwmMtx Matrix */
void getTJ700AwmMtx(floating *Pointer);

/* Gets TJ700BshMtx Matrix */
void getTJ700BshMtx(floating *Pointer);

/* Gets TJ700BwmMtx Matrix */
void getTJ700BwmMtx(floating *Pointer);

/* Gets TJ700EffFANMapMtx Matrix */
void getTJ700EffFANMapMtx(floating *Pointer);

/* Gets TJ700EffHPCMapMtx Matrix */
void getTJ700EffHPCMapMtx(floating *Pointer);

/* Gets TJ700EffHPTMapMtx Matrix */
void getTJ700EffHPTMapMtx(floating *Pointer);

/* Gets TJ700NcFANMapMtx Matrix */
void getTJ700NcFANMapMtx(floating *Pointer);

/* Gets TJ700NcHPTMapMtx Matrix */
void getTJ700NcHPTMapMtx(floating *Pointer);

/* Gets TJ700NcMtx Matrix */
void getTJ700NcMtx(floating *Pointer);

/* Gets TJ700PRFANMapMtx Matrix */
void getTJ700PRFANMapMtx(floating *Pointer);

/* Gets TJ700PRFANStallMtx Matrix */
void getTJ700PRFANStallMtx(floating *Pointer);

/* Gets TJ700PRHPCStallMtx Matrix */
void getTJ700PRHPCStallMtx(floating *Pointer);

/* Gets TJ700PRHPTMapMtx Matrix */
void getTJ700PRHPTMapMtx(floating *Pointer);

/* Gets TJ700Pt21DMtx Matrix */
void getTJ700Pt21DMtx(floating *Pointer);

/* Gets TJ700Pt21Mtx Matrix */
void getTJ700Pt21Mtx(floating *Pointer);

/* Gets TJ700Pt6DMtx Matrix */
void getTJ700Pt6DMtx(floating *Pointer);

/* Gets TJ700Pt6Mtx Matrix */
void getTJ700Pt6Mtx(floating *Pointer);

/* Gets TJ700RPMshMtx Matrix */
void getTJ700RPMshMtx(floating *Pointer);

/* Gets TJ700RPMwmMtx Matrix */
void getTJ700RPMwmMtx(floating *Pointer);

/* Gets TJ700Tt21DMtx Matrix */
void getTJ700Tt21DMtx(floating *Pointer);

/* Gets TJ700Tt21Mtx Matrix */
void getTJ700Tt21Mtx(floating *Pointer);

/* Gets TJ700Tt3DMtx Matrix */
void getTJ700Tt3DMtx(floating *Pointer);

/* Gets TJ700Tt3Mtx Matrix */
void getTJ700Tt3Mtx(floating *Pointer);

/* Gets TJ700Tt4CshMtx Matrix */
void getTJ700Tt4CshMtx(floating *Pointer);

/* Gets TJ700Tt4DshMtx Matrix */
void getTJ700Tt4DshMtx(floating *Pointer);

/* Gets TJ700Tt4shMtx Matrix */
void getTJ700Tt4shMtx(floating *Pointer);

/* Gets TJ700Tt6DMtx Matrix */
void getTJ700Tt6DMtx(floating *Pointer);

/* Gets TJ700Tt6Mtx Matrix */
void getTJ700Tt6Mtx(floating *Pointer);

/* Gets TJ700WcFANMapMtx Matrix */
void getTJ700WcFANMapMtx(floating *Pointer);

/* Gets TJ700WcFANStallMtx Matrix */
void getTJ700WcFANStallMtx(floating *Pointer);

/* Gets TJ700WcHPCStallMtx Matrix */
void getTJ700WcHPCStallMtx(floating *Pointer);

/* Gets TJ700WcHPTMapMtx Matrix */
void getTJ700WcHPTMapMtx(floating *Pointer);

/* Gets TJ700WfshMtx Matrix */
void getTJ700WfshMtx(floating *Pointer);

/* Gets TJ700NcFANshMtx Matrix */
void getTJ700NcFANshMtx(floating *Pointer);

/* Gets TJ700WfwmMtx Matrix */
void getTJ700WfwmMtx(floating *Pointer);

/* Gets TJ700Pt3shMtx Matrix */
void getTJ700Pt3shMtx(floating *Pointer);

/* Gets TJ700Pt3DshMtx Matrix */
void getTJ700Pt3DshMtx(floating *Pointer);

/* Gets TJ700Pt21wmMtx Matrix */
void getTJ700Pt21wmMtx(floating *Pointer);

/* Gets TJ700Pt21DwmMtx Matrix */
void getTJ700Pt21DwmMtx(floating *Pointer);

/* Gets TJ700Pt3wmMtx Matrix */
void getTJ700Pt3wmMtx(floating *Pointer);

/* Gets TJ700Pt3DwmMtx Matrix */
void getTJ700Pt3DwmMtx(floating *Pointer);

/* Gets TJ700Pt5wmMtx Matrix */
void getTJ700Pt5wmMtx(floating *Pointer);

/* Gets TJ700Pt5DwmMtx Matrix */
void getTJ700Pt5DwmMtx(floating *Pointer);

/* Gets TJ700Pt6wmMtx Matrix */
void getTJ700Pt6wmMtx(floating *Pointer);

/* Gets TJ700Pt6DwmMtx Matrix */
void getTJ700Pt6DwmMtx(floating *Pointer);

/* Gets TJ700Tt21wmMtx Matrix */
void getTJ700Tt21wmMtx(floating *Pointer);

/* Gets TJ700Tt21DwmMtx Matrix */
void getTJ700Tt21DwmMtx(floating *Pointer);

/* Gets TJ700Tt3wmMtx Matrix */
void getTJ700Tt3wmMtx(floating *Pointer);

/* Gets TJ700Tt3DwmMtx Matrix */
void getTJ700Tt3DwmMtx(floating *Pointer);

/* Gets TJ700Tt4wmMtx Matrix */
void getTJ700Tt4wmMtx(floating *Pointer);

/* Gets TJ700Tt4DwmMtx Matrix */
void getTJ700Tt4DwmMtx(floating *Pointer);

/* Gets TJ700Tt5wmMtx Matrix */
void getTJ700Tt5wmMtx(floating *Pointer);

/* Gets TJ700Tt5DwmMtx Matrix */
void getTJ700Tt5DwmMtx(floating *Pointer);

/* Gets TJ700Tt6wmMtx Matrix */
void getTJ700Tt6wmMtx(floating *Pointer);

/* Gets TJ700Tt6DwmMtx Matrix */
void getTJ700Tt6DwmMtx(floating *Pointer);

/* Gets TJ700Pt21shMtx Matrix */
void getTJ700Pt21shMtx(floating *Pointer);

/* Gets TJ700Pt21DshMtx Matrix */
void getTJ700Pt21DshMtx(floating *Pointer);

/* Gets TJ700Pt5shMtx Matrix */
void getTJ700Pt5shMtx(floating *Pointer);

/* Gets TJ700Pt5DshMtx Matrix */
void getTJ700Pt5DshMtx(floating *Pointer);

/* Gets TJ700Pt6shMtx Matrix */
void getTJ700Pt6shMtx(floating *Pointer);

/* Gets TJ700Pt6DshMtx Matrix */
void getTJ700Pt6DshMtx(floating *Pointer);

/* Gets TJ700Tt21shMtx Matrix */
void getTJ700Tt21shMtx(floating *Pointer);

/* Gets TJ700Tt21DshMtx Matrix */
void getTJ700Tt21DshMtx(floating *Pointer);

/* Gets TJ700Tt3shMtx Matrix */
void getTJ700Tt3shMtx(floating *Pointer);

/* Gets TJ700Tt3DshMtx Matrix */
void getTJ700Tt3DshMtx(floating *Pointer);

/* Gets TJ700Tt5shMtx Matrix */
void getTJ700Tt5shMtx(floating *Pointer);

/* Gets TJ700Tt5DshMtx Matrix */
void getTJ700Tt5DshMtx(floating *Pointer);

/* Gets TJ700Tt6shMtx Matrix */
void getTJ700Tt6shMtx(floating *Pointer);

/* Gets TJ700Tt6DshMtx Matrix */
void getTJ700Tt6DshMtx(floating *Pointer);

#endif