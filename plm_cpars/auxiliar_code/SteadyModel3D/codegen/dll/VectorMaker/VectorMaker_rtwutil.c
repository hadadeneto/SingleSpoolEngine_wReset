/*
 * Student License - for use by students to meet course requirements and
 * perform academic research at degree granting institutions only.  Not
 * for government, commercial, or other organizational use.
 *
 * VectorMaker_rtwutil.c
 *
 * Code generation for function 'VectorMaker_rtwutil'
 *
 */

/* Include files */
#include "VectorMaker_rtwutil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Function Declarations */
static boolean_T rtIsNullOrEmptyString(const char *aString);
static void rtReportErrorLocation(const char * aFcnName, int aLineNo);

/* Function Definitions */
static boolean_T rtIsNullOrEmptyString(const char *aString)
{
  return (aString == NULL) || (*aString == '\x00');
}

static void rtReportErrorLocation(const char * aFcnName, int aLineNo)
{
  fprintf(stderr, "Error in %s (line %d)", aFcnName, aLineNo);
  fprintf(stderr, "\n");
}

void rtDynamicBoundsError(int aIndexValue, int aLoBound, int aHiBound, const
  rtBoundsCheckInfo *aInfo)
{
  if (aLoBound == 0) {
    aIndexValue++;
    aLoBound = 1;
    aHiBound++;
  }

  if (rtIsNullOrEmptyString(aInfo->aName)) {
    fprintf(stderr,
            "Index exceeds array dimensions.  Index value %d exceeds valid range [%d-%d].",
            aIndexValue, aLoBound, aHiBound);
    fprintf(stderr, "\n");
  } else {
    fprintf(stderr,
            "Index exceeds array dimensions.  Index value %d exceeds valid range [%d-%d] of array %s.",
            aIndexValue, aLoBound, aHiBound, aInfo->aName);
    fprintf(stderr, "\n");
  }

  if (aInfo != NULL) {
    rtReportErrorLocation(aInfo->fName, aInfo->lineNo);
  }

  fflush(stderr);
  abort();
}

void rtSizeEq1DError(const int aDim1, const int aDim2, const rtEqualityCheckInfo
                     *aInfo)
{
  fprintf(stderr, "Sizes mismatch: %d ~= %d.", aDim1, aDim2);
  fprintf(stderr, "\n");
  if (aInfo != NULL) {
    rtReportErrorLocation(aInfo->fName, aInfo->lineNo);
  }

  fflush(stderr);
  abort();
}

/* End of code generation (VectorMaker_rtwutil.c) */
