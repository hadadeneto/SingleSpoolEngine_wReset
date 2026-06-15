#ifndef GETTJ300RFADEC_H
#define GETTJ300RFADEC_H

#include "../../FADEC_Defines_H/FloatPoint_Precision.h"


/* FUNCTIONS FOR LOADING MATRICES USED BY FADEC CODE */

/* Gets TJ300RAMtx Matrix */
void getTJ300RAMtx(floating *Pointer);

/* Gets TJ300RASVec Matrix */
void getTJ300RASVec(floating *Pointer);

/* Gets TJ300RAltLinVec Matrix */
void getTJ300RAltLinVec(floating *Pointer);

/* Gets TJ300RBMtx Matrix */
void getTJ300RBMtx(floating *Pointer);

/* Gets TJ300RDSVec Matrix */
void getTJ300RDSVec(floating *Pointer);

/* Gets TJ300RDeltaMtx Matrix */
void getTJ300RDeltaMtx(floating *Pointer);

/* Gets TJ300RFNcMaxContMtx Matrix */
void getTJ300RFNcMaxContMtx(floating *Pointer);

/* Gets TJ300RFNperContMtx Matrix */
void getTJ300RFNperContMtx(floating *Pointer);

/* Gets TJ300RMNLinVec Matrix */
void getTJ300RMNLinVec(floating *Pointer);

/* Gets TJ300RN_KiMtx Matrix */
void getTJ300RN_KiMtx(floating *Pointer);

/* Gets TJ300RN_KpMtx Matrix */
void getTJ300RN_KpMtx(floating *Pointer);

/* Gets TJ300RNcFANContMtx Matrix */
void getTJ300RNcFANContMtx(floating *Pointer);

/* Gets TJ300RNcHPCMapMtx Matrix */
void getTJ300RNcHPCMapMtx(floating *Pointer);

/* Gets TJ300RNcVec Matrix */
void getTJ300RNcVec(floating *Pointer);

/* Gets TJ300RPRHPCMapMtx Matrix */
void getTJ300RPRHPCMapMtx(floating *Pointer);

/* Gets TJ300RPt3DMtx Matrix */
void getTJ300RPt3DMtx(floating *Pointer);

/* Gets TJ300RPt3Mtx Matrix */
void getTJ300RPt3Mtx(floating *Pointer);

/* Gets TJ300RPt5DMtx Matrix */
void getTJ300RPt5DMtx(floating *Pointer);

/* Gets TJ300RPt5Mtx Matrix */
void getTJ300RPt5Mtx(floating *Pointer);

/* Gets TJ300RTs0Mtx Matrix */
void getTJ300RTs0Mtx(floating *Pointer);

/* Gets TJ300RTt4DMtx Matrix */
void getTJ300RTt4DMtx(floating *Pointer);

/* Gets TJ300RTt4Mtx Matrix */
void getTJ300RTt4Mtx(floating *Pointer);

/* Gets TJ300RTt5DMtx Matrix */
void getTJ300RTt5DMtx(floating *Pointer);

/* Gets TJ300RTt5Mtx Matrix */
void getTJ300RTt5Mtx(floating *Pointer);

/* Gets TJ300RWcHPCMapMtx Matrix */
void getTJ300RWcHPCMapMtx(floating *Pointer);

/* Gets TJ300RWfMtx Matrix */
void getTJ300RWfMtx(floating *Pointer);

/* Gets TJ300RN_KpshMtx Matrix */
void getTJ300RN_KpshMtx(floating *Pointer);

/* Gets TJ300RN_KishMtx Matrix */
void getTJ300RN_KishMtx(floating *Pointer);

/* Gets TJ300RNcFANshContMtx Matrix */
void getTJ300RNcFANshContMtx(floating *Pointer);

#endif