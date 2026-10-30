#ifndef GETTF300FADEC_H
#define GETTF300FADEC_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* FUNCTIONS FOR LOADING MATRICES USED BY FADEC CODE */

/* Gets TF300AMtx Matrix */
void getTF300AMtx(floating *Pointer);

/* Gets TF300ASVec Matrix */
void getTF300ASVec(floating *Pointer);

/* Gets TF300AltLinVec Matrix */
void getTF300AltLinVec(floating *Pointer);

/* Gets TF300BMtx Matrix */
void getTF300BMtx(floating *Pointer);

/* Gets TF300DSVec Matrix */
void getTF300DSVec(floating *Pointer);

/* Gets TF300DeltaMtx Matrix */
void getTF300DeltaMtx(floating *Pointer);

/* Gets TF300FNcMaxContMtx Matrix */
void getTF300FNcMaxContMtx(floating *Pointer);

/* Gets TF300FNperContMtx Matrix */
void getTF300FNperContMtx(floating *Pointer);

/* Gets TF300MNLinVec Matrix */
void getTF300MNLinVec(floating *Pointer);

/* Gets TF300N_KiMtx Matrix */
void getTF300N_KiMtx(floating *Pointer);

/* Gets TF300N_KpMtx Matrix */
void getTF300N_KpMtx(floating *Pointer);

/* Gets TF300NcFANContMtx Matrix */
void getTF300NcFANContMtx(floating *Pointer);

/* Gets TF300NcHPCMapMtx Matrix */
void getTF300NcHPCMapMtx(floating *Pointer);

/* Gets TF300NcVec Matrix */
void getTF300NcVec(floating *Pointer);

/* Gets TF300PRHPCMapMtx Matrix */
void getTF300PRHPCMapMtx(floating *Pointer);

/* Gets TF300Pt3DMtx Matrix */
void getTF300Pt3DMtx(floating *Pointer);

/* Gets TF300Pt3Mtx Matrix */
void getTF300Pt3Mtx(floating *Pointer);

/* Gets TF300Pt5DMtx Matrix */
void getTF300Pt5DMtx(floating *Pointer);

/* Gets TF300Pt5Mtx Matrix */
void getTF300Pt5Mtx(floating *Pointer);

/* Gets TF300Ts0Mtx Matrix */
void getTF300Ts0Mtx(floating *Pointer);

/* Gets TF300Tt4DMtx Matrix */
void getTF300Tt4DMtx(floating *Pointer);

/* Gets TF300Tt4Mtx Matrix */
void getTF300Tt4Mtx(floating *Pointer);

/* Gets TF300Tt5DMtx Matrix */
void getTF300Tt5DMtx(floating *Pointer);

/* Gets TF300Tt5Mtx Matrix */
void getTF300Tt5Mtx(floating *Pointer);

/* Gets TF300WcHPCMapMtx Matrix */
void getTF300WcHPCMapMtx(floating *Pointer);

/* Gets TF300WfMtx Matrix */
void getTF300WfMtx(floating *Pointer);

/* Gets TF300N_KpshMtx Matrix */
void getTF300N_KpshMtx(floating *Pointer);

/* Gets TF300N_KishMtx Matrix */
void getTF300N_KishMtx(floating *Pointer);

/* Gets TF300NcFANshContMtx Matrix */
void getTF300NcFANshContMtx(floating *Pointer);

#endif