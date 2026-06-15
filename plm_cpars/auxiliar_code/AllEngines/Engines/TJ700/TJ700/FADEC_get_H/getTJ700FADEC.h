#ifndef GETTJ700FADEC_H
#define GETTJ700FADEC_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* FUNCTIONS FOR LOADING MATRICES USED BY FADEC CODE */

/* Gets TJ700AMtx Matrix */
void getTJ700AMtx(floating *Pointer);

/* Gets TJ700ASVec Matrix */
void getTJ700ASVec(floating *Pointer);

/* Gets TJ700AltLinVec Matrix */
void getTJ700AltLinVec(floating *Pointer);

/* Gets TJ700BMtx Matrix */
void getTJ700BMtx(floating *Pointer);

/* Gets TJ700DSVec Matrix */
void getTJ700DSVec(floating *Pointer);

/* Gets TJ700DeltaMtx Matrix */
void getTJ700DeltaMtx(floating *Pointer);

/* Gets TJ700FNcMaxContMtx Matrix */
void getTJ700FNcMaxContMtx(floating *Pointer);

/* Gets TJ700FNperContMtx Matrix */
void getTJ700FNperContMtx(floating *Pointer);

/* Gets TJ700MNLinVec Matrix */
void getTJ700MNLinVec(floating *Pointer);

/* Gets TJ700N_KiMtx Matrix */
void getTJ700N_KiMtx(floating *Pointer);

/* Gets TJ700N_KpMtx Matrix */
void getTJ700N_KpMtx(floating *Pointer);

/* Gets TJ700NcFANContMtx Matrix */
void getTJ700NcFANContMtx(floating *Pointer);

/* Gets TJ700NcHPCMapMtx Matrix */
void getTJ700NcHPCMapMtx(floating *Pointer);

/* Gets TJ700NcVec Matrix */
void getTJ700NcVec(floating *Pointer);

/* Gets TJ700PRHPCMapMtx Matrix */
void getTJ700PRHPCMapMtx(floating *Pointer);

/* Gets TJ700Pt3DMtx Matrix */
void getTJ700Pt3DMtx(floating *Pointer);

/* Gets TJ700Pt3Mtx Matrix */
void getTJ700Pt3Mtx(floating *Pointer);

/* Gets TJ700Pt5DMtx Matrix */
void getTJ700Pt5DMtx(floating *Pointer);

/* Gets TJ700Pt5Mtx Matrix */
void getTJ700Pt5Mtx(floating *Pointer);

/* Gets TJ700Ts0Mtx Matrix */
void getTJ700Ts0Mtx(floating *Pointer);

/* Gets TJ700Tt4DMtx Matrix */
void getTJ700Tt4DMtx(floating *Pointer);

/* Gets TJ700Tt4Mtx Matrix */
void getTJ700Tt4Mtx(floating *Pointer);

/* Gets TJ700Tt5DMtx Matrix */
void getTJ700Tt5DMtx(floating *Pointer);

/* Gets TJ700Tt5Mtx Matrix */
void getTJ700Tt5Mtx(floating *Pointer);

/* Gets TJ700WcHPCMapMtx Matrix */
void getTJ700WcHPCMapMtx(floating *Pointer);

/* Gets TJ700WfMtx Matrix */
void getTJ700WfMtx(floating *Pointer);

/* Gets TJ700N_KpshMtx Matrix */
void getTJ700N_KpshMtx(floating *Pointer);

/* Gets TJ700N_KishMtx Matrix */
void getTJ700N_KishMtx(floating *Pointer);

/* Gets TJ700NcFANshContMtx Matrix */
void getTJ700NcFANshContMtx(floating *Pointer);

#endif