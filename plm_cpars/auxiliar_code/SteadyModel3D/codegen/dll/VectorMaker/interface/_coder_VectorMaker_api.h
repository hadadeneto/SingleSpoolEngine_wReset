/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * _coder_VectorMaker_api.h
 *
 * Code generation for function '_coder_VectorMaker_api'
 *
 */

#ifndef _CODER_VECTORMAKER_API_H
#define _CODER_VECTORMAKER_API_H

/* Include files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_VectorMaker_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
#ifdef __cplusplus

extern "C" {

#endif

  extern void VectorMaker(real_T BPNew[26], real_T BPOrigin[16], real_T
    VecOrigin[16], real_T NewVec[26]);
  extern void VectorMaker_api(const mxArray * const prhs[3], int32_T nlhs, const
    mxArray *plhs[1]);
  extern void VectorMaker_atexit(void);
  extern void VectorMaker_initialize(void);
  extern void VectorMaker_terminate(void);
  extern void VectorMaker_xil_shutdown(void);
  extern void VectorMaker_xil_terminate(void);

#ifdef __cplusplus

}
#endif
#endif

/* End of code generation (_coder_VectorMaker_api.h) */
