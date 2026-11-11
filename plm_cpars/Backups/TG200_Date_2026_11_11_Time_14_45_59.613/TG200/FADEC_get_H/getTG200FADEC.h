#ifndef GETTG200FADEC_H
#define GETTG200FADEC_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* FUNCTIONS FOR LOADING MATRICES USED BY FADEC CODE */

/* Gets TG200AMtx Matrix */
void getTG200AMtx(floating *Pointer);

/* Gets TG200ASVec Matrix */
void getTG200ASVec(floating *Pointer);

/* Gets TG200AltLinVec Matrix */
void getTG200AltLinVec(floating *Pointer);

/* Gets TG200BMtx Matrix */
void getTG200BMtx(floating *Pointer);

/* Gets TG200DSVec Matrix */
void getTG200DSVec(floating *Pointer);

/* Gets TG200DeltaMtx Matrix */
void getTG200DeltaMtx(floating *Pointer);

/* Gets TG200FNcMaxContMtx Matrix */
void getTG200FNcMaxContMtx(floating *Pointer);

/* Gets TG200FNperContMtx Matrix */
void getTG200FNperContMtx(floating *Pointer);

/* Gets TG200MNLinVec Matrix */
void getTG200MNLinVec(floating *Pointer);

/* Gets TG200N_KiMtx Matrix */
void getTG200N_KiMtx(floating *Pointer);

/* Gets TG200N_KpMtx Matrix */
void getTG200N_KpMtx(floating *Pointer);

/* Gets TG200NcFANContMtx Matrix */
void getTG200NcFANContMtx(floating *Pointer);

/* Gets TG200NcHPCMapMtx Matrix */
void getTG200NcHPCMapMtx(floating *Pointer);

/* Gets TG200NcVec Matrix */
void getTG200NcVec(floating *Pointer);

/* Gets TG200PRHPCMapMtx Matrix */
void getTG200PRHPCMapMtx(floating *Pointer);

/* Gets TG200Pt3DMtx Matrix */
void getTG200Pt3DMtx(floating *Pointer);

/* Gets TG200Pt3Mtx Matrix */
void getTG200Pt3Mtx(floating *Pointer);

/* Gets TG200Pt5DMtx Matrix */
void getTG200Pt5DMtx(floating *Pointer);

/* Gets TG200Pt5Mtx Matrix */
void getTG200Pt5Mtx(floating *Pointer);

/* Gets TG200Ts0Mtx Matrix */
void getTG200Ts0Mtx(floating *Pointer);

/* Gets TG200Tt4DMtx Matrix */
void getTG200Tt4DMtx(floating *Pointer);

/* Gets TG200Tt4Mtx Matrix */
void getTG200Tt4Mtx(floating *Pointer);

/* Gets TG200Tt5DMtx Matrix */
void getTG200Tt5DMtx(floating *Pointer);

/* Gets TG200Tt5Mtx Matrix */
void getTG200Tt5Mtx(floating *Pointer);

/* Gets TG200WcHPCMapMtx Matrix */
void getTG200WcHPCMapMtx(floating *Pointer);

/* Gets TG200WfMtx Matrix */
void getTG200WfMtx(floating *Pointer);

/* Gets TG200N_KpshMtx Matrix */
void getTG200N_KpshMtx(floating *Pointer);

/* Gets TG200N_KishMtx Matrix */
void getTG200N_KishMtx(floating *Pointer);

/* Gets TG200NcFANshContMtx Matrix */
void getTG200NcFANshContMtx(floating *Pointer);

#endif