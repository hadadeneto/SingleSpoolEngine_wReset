/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * VectorMaker_types.h
 *
 * Code generation for function 'VectorMaker'
 *
 */

#ifndef VECTORMAKER_TYPES_H
#define VECTORMAKER_TYPES_H

/* Include files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_rtBoundsCheckInfo
#define typedef_rtBoundsCheckInfo

typedef struct {
  int iFirst;
  int iLast;
  int lineNo;
  int colNo;
  const char * aName;
  const char * fName;
  const char * pName;
  int checkKind;
} rtBoundsCheckInfo;

#endif                                 /*typedef_rtBoundsCheckInfo*/

#ifndef typedef_rtEqualityCheckInfo
#define typedef_rtEqualityCheckInfo

typedef struct {
  int nDims;
  int lineNo;
  int colNo;
  const char * fName;
  const char * pName;
} rtEqualityCheckInfo;

#endif                                 /*typedef_rtEqualityCheckInfo*/
#endif

/* End of code generation (VectorMaker_types.h) */
