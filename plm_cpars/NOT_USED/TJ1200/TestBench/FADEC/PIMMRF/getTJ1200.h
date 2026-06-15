/*
 * getTJ1200.h
 *
 *  Created on: January 08, 2021
 *      Author: Antonio Hadade Neto
 */

#ifndef GETTJ1200_H
#define GETTJ1200_H

#include "Control_Types.h"

// /* CONTROLLER CONSTANTS */

// void getTJ1200ContConst(struct ControllerConsts *ContConst);

// /* CONTROLLER MATRICES */

// void getTJ1200N_KpMtx(double *Pointer);

// void getTJ1200N_KiMtx(double *Pointer);

// void getTJ1200Ts0Mtx(double *Pointer);

// void getTJ1200DeltaMtx(double *Pointer);

// void getTJ1200FNcMaxContMtx(double *Pointer);

// void getTJ1200NcFANContMtx(double *Pointer);

// void getTJ1200FNperContMtx(double *Pointer);

// /* MODEL MATRICES */

// void getTJ1200AMtx(double *Pointer);

// void getTJ1200BMtx(double *Pointer);

// void getTJ1200Pt3DMtx(double *Pointer);

// void getTJ1200Tt4DMtx(double *Pointer);

// void getTJ1200Tt5DMtx(double *Pointer);

// void getTJ1200Pt3Mtx(double *Pointer);

// void getTJ1200Tt4Mtx(double *Pointer);

// void getTJ1200Tt5Mtx(double *Pointer);

// /* CONTROLLER STARTING MATRICES */

// void getTJ1200StartPars(struct ControlStart *ContStartP);


/* CONTROLLER CONSTANTS */

void getTJ1200ContConst(struct ControllerConstants *ContConst);

/* CONTROLLER MATRICES */

void getTJ1200AltLinVec(double *Pointer);

void getTJ1200MNLinVec(double *Pointer);

void getTJ1200N_KpMtx(double *Pointer);

void getTJ1200N_KiMtx(double *Pointer);

void getTJ1200Ts0Mtx(double *Pointer);

void getTJ1200DeltaMtx(double *Pointer);

void getTJ1200FNcMaxContMtx(double *Pointer);

void getTJ1200NcFANContMtx(double *Pointer);

void getTJ1200FNperContMtx(double *Pointer);

void getTJ1200ASVec(double *Pointer);

void getTJ1200DSVec(double *Pointer);

void getTJ1200NcVec(double *Pointer);

/* MODEL MATRICES */

void getTJ1200AMtx(double *Pointer);

void getTJ1200BMtx(double *Pointer);

void getTJ1200Pt3DMtx(double *Pointer);

void getTJ1200Pt5DMtx(double *Pointer);

void getTJ1200Tt4DMtx(double *Pointer);

void getTJ1200Tt5DMtx(double *Pointer);

void getTJ1200Pt3Mtx(double *Pointer);

void getTJ1200Pt5Mtx(double *Pointer);

void getTJ1200Tt4Mtx(double *Pointer);

void getTJ1200Tt5Mtx(double *Pointer);

void getTJ1200WfMtx(double *Pointer);

void getTJ1200PRHPCMapMtx(double *Pointer);

void getTJ1200WcHPCMapMtx(double *Pointer);

void getTJ1200NcHPCMapMtx(double *Pointer);

/* CONTROLLER STARTING MATRICES */

void getTJ1200StartPars(struct ControlStart *ContStartP);


#endif /* GETTJ1200_H */
