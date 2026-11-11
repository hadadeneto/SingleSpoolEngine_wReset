#ifndef GETTF1200FADEC_H
#define GETTF1200FADEC_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* FUNCTIONS FOR LOADING MATRICES USED BY FADEC CODE */

/* Gets TF1200AMtx Matrix */
void getTF1200AMtx(floating *Pointer);

/* Gets TF1200ASVec Matrix */
void getTF1200ASVec(floating *Pointer);

/* Gets TF1200AltLinVec Matrix */
void getTF1200AltLinVec(floating *Pointer);

/* Gets TF1200BMtx Matrix */
void getTF1200BMtx(floating *Pointer);

/* Gets TF1200DSVec Matrix */
void getTF1200DSVec(floating *Pointer);

/* Gets TF1200DeltaMtx Matrix */
void getTF1200DeltaMtx(floating *Pointer);

/* Gets TF1200FNcMaxContMtx Matrix */
void getTF1200FNcMaxContMtx(floating *Pointer);

/* Gets TF1200FNperContMtx Matrix */
void getTF1200FNperContMtx(floating *Pointer);

/* Gets TF1200MNLinVec Matrix */
void getTF1200MNLinVec(floating *Pointer);

/* Gets TF1200N_KiMtx Matrix */
void getTF1200N_KiMtx(floating *Pointer);

/* Gets TF1200N_KpMtx Matrix */
void getTF1200N_KpMtx(floating *Pointer);

/* Gets TF1200NcFANContMtx Matrix */
void getTF1200NcFANContMtx(floating *Pointer);

/* Gets TF1200NcHPCMapMtx Matrix */
void getTF1200NcHPCMapMtx(floating *Pointer);

/* Gets TF1200NcVec Matrix */
void getTF1200NcVec(floating *Pointer);

/* Gets TF1200PRHPCMapMtx Matrix */
void getTF1200PRHPCMapMtx(floating *Pointer);

/* Gets TF1200Pt3DMtx Matrix */
void getTF1200Pt3DMtx(floating *Pointer);

/* Gets TF1200Pt3Mtx Matrix */
void getTF1200Pt3Mtx(floating *Pointer);

/* Gets TF1200Pt5DMtx Matrix */
void getTF1200Pt5DMtx(floating *Pointer);

/* Gets TF1200Pt5Mtx Matrix */
void getTF1200Pt5Mtx(floating *Pointer);

/* Gets TF1200Ts0Mtx Matrix */
void getTF1200Ts0Mtx(floating *Pointer);

/* Gets TF1200Tt4DMtx Matrix */
void getTF1200Tt4DMtx(floating *Pointer);

/* Gets TF1200Tt4Mtx Matrix */
void getTF1200Tt4Mtx(floating *Pointer);

/* Gets TF1200Tt5DMtx Matrix */
void getTF1200Tt5DMtx(floating *Pointer);

/* Gets TF1200Tt5Mtx Matrix */
void getTF1200Tt5Mtx(floating *Pointer);

/* Gets TF1200WcHPCMapMtx Matrix */
void getTF1200WcHPCMapMtx(floating *Pointer);

/* Gets TF1200WfMtx Matrix */
void getTF1200WfMtx(floating *Pointer);

/* Gets TF1200N_KpshMtx Matrix */
void getTF1200N_KpshMtx(floating *Pointer);

/* Gets TF1200N_KishMtx Matrix */
void getTF1200N_KishMtx(floating *Pointer);

/* Gets TF1200NcFANshContMtx Matrix */
void getTF1200NcFANshContMtx(floating *Pointer);

#endif