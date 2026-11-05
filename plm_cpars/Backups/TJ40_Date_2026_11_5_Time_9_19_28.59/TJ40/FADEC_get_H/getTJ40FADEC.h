#ifndef GETTJ40FADEC_H
#define GETTJ40FADEC_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* FUNCTIONS FOR LOADING MATRICES USED BY FADEC CODE */

/* Gets TJ40AMtx Matrix */
void getTJ40AMtx(floating *Pointer);

/* Gets TJ40ASVec Matrix */
void getTJ40ASVec(floating *Pointer);

/* Gets TJ40AltLinVec Matrix */
void getTJ40AltLinVec(floating *Pointer);

/* Gets TJ40BMtx Matrix */
void getTJ40BMtx(floating *Pointer);

/* Gets TJ40DSVec Matrix */
void getTJ40DSVec(floating *Pointer);

/* Gets TJ40DeltaMtx Matrix */
void getTJ40DeltaMtx(floating *Pointer);

/* Gets TJ40FNcMaxContMtx Matrix */
void getTJ40FNcMaxContMtx(floating *Pointer);

/* Gets TJ40FNperContMtx Matrix */
void getTJ40FNperContMtx(floating *Pointer);

/* Gets TJ40MNLinVec Matrix */
void getTJ40MNLinVec(floating *Pointer);

/* Gets TJ40N_KiMtx Matrix */
void getTJ40N_KiMtx(floating *Pointer);

/* Gets TJ40N_KpMtx Matrix */
void getTJ40N_KpMtx(floating *Pointer);

/* Gets TJ40NcFANContMtx Matrix */
void getTJ40NcFANContMtx(floating *Pointer);

/* Gets TJ40NcHPCMapMtx Matrix */
void getTJ40NcHPCMapMtx(floating *Pointer);

/* Gets TJ40NcVec Matrix */
void getTJ40NcVec(floating *Pointer);

/* Gets TJ40PRHPCMapMtx Matrix */
void getTJ40PRHPCMapMtx(floating *Pointer);

/* Gets TJ40Pt3DMtx Matrix */
void getTJ40Pt3DMtx(floating *Pointer);

/* Gets TJ40Pt3Mtx Matrix */
void getTJ40Pt3Mtx(floating *Pointer);

/* Gets TJ40Pt5DMtx Matrix */
void getTJ40Pt5DMtx(floating *Pointer);

/* Gets TJ40Pt5Mtx Matrix */
void getTJ40Pt5Mtx(floating *Pointer);

/* Gets TJ40Ts0Mtx Matrix */
void getTJ40Ts0Mtx(floating *Pointer);

/* Gets TJ40Tt4DMtx Matrix */
void getTJ40Tt4DMtx(floating *Pointer);

/* Gets TJ40Tt4Mtx Matrix */
void getTJ40Tt4Mtx(floating *Pointer);

/* Gets TJ40Tt5DMtx Matrix */
void getTJ40Tt5DMtx(floating *Pointer);

/* Gets TJ40Tt5Mtx Matrix */
void getTJ40Tt5Mtx(floating *Pointer);

/* Gets TJ40WcHPCMapMtx Matrix */
void getTJ40WcHPCMapMtx(floating *Pointer);

/* Gets TJ40WfMtx Matrix */
void getTJ40WfMtx(floating *Pointer);

/* Gets TJ40N_KpshMtx Matrix */
void getTJ40N_KpshMtx(floating *Pointer);

/* Gets TJ40N_KishMtx Matrix */
void getTJ40N_KishMtx(floating *Pointer);

/* Gets TJ40NcFANshContMtx Matrix */
void getTJ40NcFANshContMtx(floating *Pointer);

#endif