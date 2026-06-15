/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * _coder_VectorMaker_api.c
 *
 * Code generation for function '_coder_VectorMaker_api'
 *
 */

/* Include files */
#include "tmwtypes.h"
#include "_coder_VectorMaker_api.h"
#include "_coder_VectorMaker_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131482U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "VectorMaker",                       /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[26];
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *BPOrigin,
  const char_T *identifier))[16];
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[16];
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[26];
static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *BPNew,
  const char_T *identifier))[26];
static const mxArray *emlrt_marshallOut(const real_T u[26]);
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[16];

/* Function Definitions */
static real_T (*b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[26]
{
  real_T (*y)[26];
  y = e_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *BPOrigin, const char_T *identifier))[16]
{
  real_T (*y)[16];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(BPOrigin), &thisId);
  emlrtDestroyArray(&BPOrigin);
  return y;
}

static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[16]
{
  real_T (*y)[16];
  y = f_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
  static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[26]
{
  real_T (*ret)[26];
  static const int32_T dims[2] = { 1, 26 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[26])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

static real_T (*emlrt_marshallIn(const emlrtStack *sp, const mxArray *BPNew,
  const char_T *identifier))[26]
{
  real_T (*y)[26];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(BPNew), &thisId);
  emlrtDestroyArray(&BPNew);
  return y;
}
  static const mxArray *emlrt_marshallOut(const real_T u[26])
{
  const mxArray *y;
  const mxArray *m0;
  static const int32_T iv0[2] = { 0, 0 };

  static const int32_T iv1[2] = { 1, 26 };

  y = NULL;
  m0 = emlrtCreateNumericArray(2, iv0, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m0, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m0, iv1, 2);
  emlrtAssign(&y, m0);
  return y;
}

static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[16]
{
  real_T (*ret)[16];
  static const int32_T dims[2] = { 1, 16 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 2U, dims);
  ret = (real_T (*)[16])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
  void VectorMaker_api(const mxArray * const prhs[3], int32_T nlhs, const
  mxArray *plhs[1])
{
  real_T (*NewVec)[26];
  real_T (*BPNew)[26];
  real_T (*BPOrigin)[16];
  real_T (*VecOrigin)[16];
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;
  NewVec = (real_T (*)[26])mxMalloc(sizeof(real_T [26]));

  /* Marshall function inputs */
  BPNew = emlrt_marshallIn(&st, emlrtAlias(prhs[0]), "BPNew");
  BPOrigin = c_emlrt_marshallIn(&st, emlrtAlias(prhs[1]), "BPOrigin");
  VecOrigin = c_emlrt_marshallIn(&st, emlrtAlias(prhs[2]), "VecOrigin");

  /* Invoke the target function */
  VectorMaker(*BPNew, *BPOrigin, *VecOrigin, *NewVec);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(*NewVec);
}

void VectorMaker_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  VectorMaker_xil_terminate();
  VectorMaker_xil_shutdown();
  emlrtExitTimeCleanup(&emlrtContextGlobal);
}

void VectorMaker_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

void VectorMaker_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/* End of code generation (_coder_VectorMaker_api.c) */
