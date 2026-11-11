#ifndef GETTJ1200FADEC_H
#define GETTJ1200FADEC_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* FUNCTIONS FOR LOADING MATRICES USED BY FADEC CODE */

/* Gets TJ1200AMtx Matrix */
void getTJ1200AMtx(floating *Pointer);

/* Gets TJ1200ASVec Matrix */
void getTJ1200ASVec(floating *Pointer);

/* Gets TJ1200AltLinVec Matrix */
void getTJ1200AltLinVec(floating *Pointer);

/* Gets TJ1200BMtx Matrix */
void getTJ1200BMtx(floating *Pointer);

/* Gets TJ1200DSVec Matrix */
void getTJ1200DSVec(floating *Pointer);

/* Gets TJ1200DeltaMtx Matrix */
void getTJ1200DeltaMtx(floating *Pointer);

/* Gets TJ1200FNcMaxContMtx Matrix */
void getTJ1200FNcMaxContMtx(floating *Pointer);

/* Gets TJ1200FNperContMtx Matrix */
void getTJ1200FNperContMtx(floating *Pointer);

/* Gets TJ1200MNLinVec Matrix */
void getTJ1200MNLinVec(floating *Pointer);

/* Gets TJ1200N_KiMtx Matrix */
void getTJ1200N_KiMtx(floating *Pointer);

/* Gets TJ1200N_KpMtx Matrix */
void getTJ1200N_KpMtx(floating *Pointer);

/* Gets TJ1200NcFANContMtx Matrix */
void getTJ1200NcFANContMtx(floating *Pointer);

/* Gets TJ1200NcHPCMapMtx Matrix */
void getTJ1200NcHPCMapMtx(floating *Pointer);

/* Gets TJ1200NcVec Matrix */
void getTJ1200NcVec(floating *Pointer);

/* Gets TJ1200PRHPCMapMtx Matrix */
void getTJ1200PRHPCMapMtx(floating *Pointer);

/* Gets TJ1200Pt3DMtx Matrix */
void getTJ1200Pt3DMtx(floating *Pointer);

/* Gets TJ1200Pt3Mtx Matrix */
void getTJ1200Pt3Mtx(floating *Pointer);

/* Gets TJ1200Pt5DMtx Matrix */
void getTJ1200Pt5DMtx(floating *Pointer);

/* Gets TJ1200Pt5Mtx Matrix */
void getTJ1200Pt5Mtx(floating *Pointer);

/* Gets TJ1200Ts0Mtx Matrix */
void getTJ1200Ts0Mtx(floating *Pointer);

/* Gets TJ1200Tt4DMtx Matrix */
void getTJ1200Tt4DMtx(floating *Pointer);

/* Gets TJ1200Tt4Mtx Matrix */
void getTJ1200Tt4Mtx(floating *Pointer);

/* Gets TJ1200Tt5DMtx Matrix */
void getTJ1200Tt5DMtx(floating *Pointer);

/* Gets TJ1200Tt5Mtx Matrix */
void getTJ1200Tt5Mtx(floating *Pointer);

/* Gets TJ1200WcHPCMapMtx Matrix */
void getTJ1200WcHPCMapMtx(floating *Pointer);

/* Gets TJ1200WfMtx Matrix */
void getTJ1200WfMtx(floating *Pointer);

/* Gets TJ1200N_KpshMtx Matrix */
void getTJ1200N_KpshMtx(floating *Pointer);

/* Gets TJ1200N_KishMtx Matrix */
void getTJ1200N_KishMtx(floating *Pointer);

/* Gets TJ1200NcFANshContMtx Matrix */
void getTJ1200NcFANshContMtx(floating *Pointer);

#endif