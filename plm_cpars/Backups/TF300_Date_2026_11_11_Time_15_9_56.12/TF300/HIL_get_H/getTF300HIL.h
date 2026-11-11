#ifndef GETTF300HIL_H
#define GETTF300HIL_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* FUNCTIONS FOR LOADING MATRICES USED BY HIL CODE */

/* Gets TF300AshMtx Matrix */
void getTF300AshMtx(floating *Pointer);

/* Gets TF300AwmMtx Matrix */
void getTF300AwmMtx(floating *Pointer);

/* Gets TF300BshMtx Matrix */
void getTF300BshMtx(floating *Pointer);

/* Gets TF300BwmMtx Matrix */
void getTF300BwmMtx(floating *Pointer);

/* Gets TF300EffFANMapMtx Matrix */
void getTF300EffFANMapMtx(floating *Pointer);

/* Gets TF300EffHPCMapMtx Matrix */
void getTF300EffHPCMapMtx(floating *Pointer);

/* Gets TF300EffHPTMapMtx Matrix */
void getTF300EffHPTMapMtx(floating *Pointer);

/* Gets TF300NcFANMapMtx Matrix */
void getTF300NcFANMapMtx(floating *Pointer);

/* Gets TF300NcHPTMapMtx Matrix */
void getTF300NcHPTMapMtx(floating *Pointer);

/* Gets TF300NcMtx Matrix */
void getTF300NcMtx(floating *Pointer);

/* Gets TF300PRFANMapMtx Matrix */
void getTF300PRFANMapMtx(floating *Pointer);

/* Gets TF300PRFANStallMtx Matrix */
void getTF300PRFANStallMtx(floating *Pointer);

/* Gets TF300PRHPCStallMtx Matrix */
void getTF300PRHPCStallMtx(floating *Pointer);

/* Gets TF300PRHPTMapMtx Matrix */
void getTF300PRHPTMapMtx(floating *Pointer);

/* Gets TF300Pt21DMtx Matrix */
void getTF300Pt21DMtx(floating *Pointer);

/* Gets TF300Pt21Mtx Matrix */
void getTF300Pt21Mtx(floating *Pointer);

/* Gets TF300Pt6DMtx Matrix */
void getTF300Pt6DMtx(floating *Pointer);

/* Gets TF300Pt6Mtx Matrix */
void getTF300Pt6Mtx(floating *Pointer);

/* Gets TF300RPMshMtx Matrix */
void getTF300RPMshMtx(floating *Pointer);

/* Gets TF300RPMwmMtx Matrix */
void getTF300RPMwmMtx(floating *Pointer);

/* Gets TF300Tt21DMtx Matrix */
void getTF300Tt21DMtx(floating *Pointer);

/* Gets TF300Tt21Mtx Matrix */
void getTF300Tt21Mtx(floating *Pointer);

/* Gets TF300Tt3DMtx Matrix */
void getTF300Tt3DMtx(floating *Pointer);

/* Gets TF300Tt3Mtx Matrix */
void getTF300Tt3Mtx(floating *Pointer);

/* Gets TF300Tt4CshMtx Matrix */
void getTF300Tt4CshMtx(floating *Pointer);

/* Gets TF300Tt4DshMtx Matrix */
void getTF300Tt4DshMtx(floating *Pointer);

/* Gets TF300Tt4shMtx Matrix */
void getTF300Tt4shMtx(floating *Pointer);

/* Gets TF300Tt6DMtx Matrix */
void getTF300Tt6DMtx(floating *Pointer);

/* Gets TF300Tt6Mtx Matrix */
void getTF300Tt6Mtx(floating *Pointer);

/* Gets TF300WcFANMapMtx Matrix */
void getTF300WcFANMapMtx(floating *Pointer);

/* Gets TF300WcFANStallMtx Matrix */
void getTF300WcFANStallMtx(floating *Pointer);

/* Gets TF300WcHPCStallMtx Matrix */
void getTF300WcHPCStallMtx(floating *Pointer);

/* Gets TF300WcHPTMapMtx Matrix */
void getTF300WcHPTMapMtx(floating *Pointer);

/* Gets TF300WfshMtx Matrix */
void getTF300WfshMtx(floating *Pointer);

/* Gets TF300NcFANshMtx Matrix */
void getTF300NcFANshMtx(floating *Pointer);

/* Gets TF300WfwmMtx Matrix */
void getTF300WfwmMtx(floating *Pointer);

/* Gets TF300Pt3shMtx Matrix */
void getTF300Pt3shMtx(floating *Pointer);

/* Gets TF300Pt3DshMtx Matrix */
void getTF300Pt3DshMtx(floating *Pointer);

/* Gets TF300Pt21wmMtx Matrix */
void getTF300Pt21wmMtx(floating *Pointer);

/* Gets TF300Pt21DwmMtx Matrix */
void getTF300Pt21DwmMtx(floating *Pointer);

/* Gets TF300Pt3wmMtx Matrix */
void getTF300Pt3wmMtx(floating *Pointer);

/* Gets TF300Pt3DwmMtx Matrix */
void getTF300Pt3DwmMtx(floating *Pointer);

/* Gets TF300Pt5wmMtx Matrix */
void getTF300Pt5wmMtx(floating *Pointer);

/* Gets TF300Pt5DwmMtx Matrix */
void getTF300Pt5DwmMtx(floating *Pointer);

/* Gets TF300Pt6wmMtx Matrix */
void getTF300Pt6wmMtx(floating *Pointer);

/* Gets TF300Pt6DwmMtx Matrix */
void getTF300Pt6DwmMtx(floating *Pointer);

/* Gets TF300Tt21wmMtx Matrix */
void getTF300Tt21wmMtx(floating *Pointer);

/* Gets TF300Tt21DwmMtx Matrix */
void getTF300Tt21DwmMtx(floating *Pointer);

/* Gets TF300Tt3wmMtx Matrix */
void getTF300Tt3wmMtx(floating *Pointer);

/* Gets TF300Tt3DwmMtx Matrix */
void getTF300Tt3DwmMtx(floating *Pointer);

/* Gets TF300Tt4wmMtx Matrix */
void getTF300Tt4wmMtx(floating *Pointer);

/* Gets TF300Tt4DwmMtx Matrix */
void getTF300Tt4DwmMtx(floating *Pointer);

/* Gets TF300Tt5wmMtx Matrix */
void getTF300Tt5wmMtx(floating *Pointer);

/* Gets TF300Tt5DwmMtx Matrix */
void getTF300Tt5DwmMtx(floating *Pointer);

/* Gets TF300Tt6wmMtx Matrix */
void getTF300Tt6wmMtx(floating *Pointer);

/* Gets TF300Tt6DwmMtx Matrix */
void getTF300Tt6DwmMtx(floating *Pointer);

/* Gets TF300Pt21shMtx Matrix */
void getTF300Pt21shMtx(floating *Pointer);

/* Gets TF300Pt21DshMtx Matrix */
void getTF300Pt21DshMtx(floating *Pointer);

/* Gets TF300Pt5shMtx Matrix */
void getTF300Pt5shMtx(floating *Pointer);

/* Gets TF300Pt5DshMtx Matrix */
void getTF300Pt5DshMtx(floating *Pointer);

/* Gets TF300Pt6shMtx Matrix */
void getTF300Pt6shMtx(floating *Pointer);

/* Gets TF300Pt6DshMtx Matrix */
void getTF300Pt6DshMtx(floating *Pointer);

/* Gets TF300Tt21shMtx Matrix */
void getTF300Tt21shMtx(floating *Pointer);

/* Gets TF300Tt21DshMtx Matrix */
void getTF300Tt21DshMtx(floating *Pointer);

/* Gets TF300Tt3shMtx Matrix */
void getTF300Tt3shMtx(floating *Pointer);

/* Gets TF300Tt3DshMtx Matrix */
void getTF300Tt3DshMtx(floating *Pointer);

/* Gets TF300Tt5shMtx Matrix */
void getTF300Tt5shMtx(floating *Pointer);

/* Gets TF300Tt5DshMtx Matrix */
void getTF300Tt5DshMtx(floating *Pointer);

/* Gets TF300Tt6shMtx Matrix */
void getTF300Tt6shMtx(floating *Pointer);

/* Gets TF300Tt6DshMtx Matrix */
void getTF300Tt6DshMtx(floating *Pointer);

#endif