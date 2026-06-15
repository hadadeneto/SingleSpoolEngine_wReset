/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * VectorMaker.c
 *
 * Code generation for function 'VectorMaker'
 *
 */

/* Include files */
#include <string.h>
#include "VectorMaker.h"
#include "VectorMaker_rtwutil.h"
#include <stdio.h>
#include <stdlib.h>

/* Variable Definitions */
static rtEqualityCheckInfo emlrtECI = { -1,/* nDims */
  18,                                  /* lineNo */
  9,                                   /* colNo */
  "VectorMaker",                       /* fName */
  "C:\\Users\\anton\\OneDrive\\TurbineModel\\Modelo_Completo\\Simulink_Engines\\PieceWiseLinModel\\SingleSpoolEngine_wReset\\plm_cpars\\auxil"
  "iar_code\\SteadyModel3D\\VectorMaker.m"/* pName */
};

static rtBoundsCheckInfo emlrtBCI = { 1,/* iFirst */
  16,                                  /* iLast */
  16,                                  /* lineNo */
  64,                                  /* colNo */
  "BPOrigin",                          /* aName */
  "VectorMaker",                       /* fName */
  "C:\\Users\\anton\\OneDrive\\TurbineModel\\Modelo_Completo\\Simulink_Engines\\PieceWiseLinModel\\SingleSpoolEngine_wReset\\plm_cpars\\auxil"
  "iar_code\\SteadyModel3D\\VectorMaker.m",/* pName */
  0                                    /* checkKind */
};

/* Function Definitions */
void VectorMaker(const double BPNew[26], const double BPOrigin[16], const double
                 VecOrigin[16], double NewVec[26])
{
  int i;
  int idx;
  boolean_T x[16];
  int ii_size_idx_1;
  int ii;
  boolean_T exitg1;
  signed char ii_data[1];
  signed char IL_data[1];
  double A_data[1];
  double B_data[1];
  double a;

  /* UNTITLED Summary of this function goes here */
  /*    Detailed explanation goes here */
  /* New vector is initiated with zeros */
  memset(&NewVec[0], 0, 26U * sizeof(double));
  for (i = 0; i < 26; i++) {
    /* If the new breakpoint lies within the bounds of the original */
    /* breakpoint vector, the value must be calculated */
    if ((BPNew[i] >= BPOrigin[0]) && (BPNew[i] <= BPOrigin[15])) {
      /* Finds the indexes bounding the new breakpoint value */
      for (idx = 0; idx < 16; idx++) {
        x[idx] = (BPNew[i] < BPOrigin[idx]);
      }

      idx = 0;
      ii_size_idx_1 = 1;
      ii = 0;
      exitg1 = false;
      while ((!exitg1) && (ii < 16)) {
        if (x[ii]) {
          idx = 1;
          ii_data[0] = (signed char)(ii + 1);
          exitg1 = true;
        } else {
          ii++;
        }
      }

      if (idx == 0) {
        ii_size_idx_1 = 0;
      }

      for (idx = 0; idx < ii_size_idx_1; idx++) {
        IL_data[0] = (signed char)(ii_data[0] - 1);
      }

      /* Calculates the needed fractional value */
      for (idx = 0; idx < ii_size_idx_1; idx++) {
        if (IL_data[0] < 1) {
          rtDynamicBoundsError(0, 1, 16, &emlrtBCI);
        }
      }

      for (idx = 0; idx < ii_size_idx_1; idx++) {
        A_data[0] = BPNew[i] - BPOrigin[IL_data[0] - 1];
      }

      for (idx = 0; idx < ii_size_idx_1; idx++) {
        B_data[0] = BPOrigin[ii_data[0] - 1] - BPOrigin[IL_data[0] - 1];
      }

      if (ii_size_idx_1 == 0) {
        a = 0.0;
      } else {
        a = A_data[0] / B_data[0];
      }

      /* Calculates tne new vector value */
      for (idx = 0; idx < ii_size_idx_1; idx++) {
        A_data[0] = a * (VecOrigin[ii_data[0] - 1] - VecOrigin[IL_data[0] - 1]);
      }

      if (1 != ii_size_idx_1) {
        rtSizeEq1DError(1, 0, &emlrtECI);
      }

      NewVec[i] = VecOrigin[IL_data[0] - 1] + A_data[0];
    }
  }
}

/* End of code generation (VectorMaker.c) */
