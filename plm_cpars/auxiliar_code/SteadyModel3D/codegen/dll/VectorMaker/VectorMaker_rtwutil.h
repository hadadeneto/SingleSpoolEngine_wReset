/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * VectorMaker_rtwutil.h
 *
 * Code generation for function 'VectorMaker_rtwutil'
 *
 */

#ifndef VECTORMAKER_RTWUTIL_H
#define VECTORMAKER_RTWUTIL_H

/* Include files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "VectorMaker_types.h"

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void rtDynamicBoundsError(int aIndexValue, int aLoBound, int aHiBound,
    const rtBoundsCheckInfo *aInfo);
  extern void rtSizeEq1DError(const int aDim1, const int aDim2, const
    rtEqualityCheckInfo *aInfo);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (VectorMaker_rtwutil.h) */
