#ifndef GETTJ200FADEC_H
#define GETTJ200FADEC_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* FUNCTIONS FOR LOADING MATRICES USED BY FADEC CODE */

/* Gets TJ200AMtx Matrix */
void getTJ200AMtx(floating *Pointer);

/* Gets TJ200ASVec Matrix */
void getTJ200ASVec(floating *Pointer);

/* Gets TJ200AltLinVec Matrix */
void getTJ200AltLinVec(floating *Pointer);

/* Gets TJ200BMtx Matrix */
void getTJ200BMtx(floating *Pointer);

/* Gets TJ200DSVec Matrix */
void getTJ200DSVec(floating *Pointer);

/* Gets TJ200DeltaMtx Matrix */
void getTJ200DeltaMtx(floating *Pointer);

/* Gets TJ200FNcMaxContMtx Matrix */
void getTJ200FNcMaxContMtx(floating *Pointer);

/* Gets TJ200FNperContMtx Matrix */
void getTJ200FNperContMtx(floating *Pointer);

/* Gets TJ200MNLinVec Matrix */
void getTJ200MNLinVec(floating *Pointer);

/* Gets TJ200N_KiMtx Matrix */
void getTJ200N_KiMtx(floating *Pointer);

/* Gets TJ200N_KpMtx Matrix */
void getTJ200N_KpMtx(floating *Pointer);

/* Gets TJ200NcFANContMtx Matrix */
void getTJ200NcFANContMtx(floating *Pointer);

/* Gets TJ200NcHPCMapMtx Matrix */
void getTJ200NcHPCMapMtx(floating *Pointer);

/* Gets TJ200NcVec Matrix */
void getTJ200NcVec(floating *Pointer);

/* Gets TJ200PRHPCMapMtx Matrix */
void getTJ200PRHPCMapMtx(floating *Pointer);

/* Gets TJ200Pt3DMtx Matrix */
void getTJ200Pt3DMtx(floating *Pointer);

/* Gets TJ200Pt3Mtx Matrix */
void getTJ200Pt3Mtx(floating *Pointer);

/* Gets TJ200Pt5DMtx Matrix */
void getTJ200Pt5DMtx(floating *Pointer);

/* Gets TJ200Pt5Mtx Matrix */
void getTJ200Pt5Mtx(floating *Pointer);

/* Gets TJ200Ts0Mtx Matrix */
void getTJ200Ts0Mtx(floating *Pointer);

/* Gets TJ200Tt4DMtx Matrix */
void getTJ200Tt4DMtx(floating *Pointer);

/* Gets TJ200Tt4Mtx Matrix */
void getTJ200Tt4Mtx(floating *Pointer);

/* Gets TJ200Tt5DMtx Matrix */
void getTJ200Tt5DMtx(floating *Pointer);

/* Gets TJ200Tt5Mtx Matrix */
void getTJ200Tt5Mtx(floating *Pointer);

/* Gets TJ200WcHPCMapMtx Matrix */
void getTJ200WcHPCMapMtx(floating *Pointer);

/* Gets TJ200WfMtx Matrix */
void getTJ200WfMtx(floating *Pointer);

/* Gets TJ200N_KpshMtx Matrix */
void getTJ200N_KpshMtx(floating *Pointer);

/* Gets TJ200N_KishMtx Matrix */
void getTJ200N_KishMtx(floating *Pointer);

/* Gets TJ200NcFANshContMtx Matrix */
void getTJ200NcFANshContMtx(floating *Pointer);

#endif