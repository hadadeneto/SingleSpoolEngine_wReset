/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * VectorMaker.h
 *
 * Code generation for function 'VectorMaker'
 *
 */

#ifndef VECTORMAKER_H
#define VECTORMAKER_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "VectorMaker_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void VectorMaker(const double BPNew[26], const double BPOrigin[16],
    const double VecOrigin[16], double NewVec[26]);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (VectorMaker.h) */
