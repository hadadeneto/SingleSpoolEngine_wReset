#ifndef TMATS_FUNCTIONS_H
#define TMATS_FUNCTIONS_H

/*		T-MATS -- functions.h
 * % *************************************************************************
 * % written by Jeffryes Chapman
 * % NASA Glenn Research Center, Cleveland, OH
 * % August 2nd, 2016
 * %
 * %  This is a file that contains various functions for use in the T-MATS C-code
 * % *************************************************************************/

#include "../FADEC_Defines_H/FloatPoint_Precision.h"

/* functions_TMATS.c */
extern floating sqrtT(floating A);
extern floating divby(floating B);
extern floating powT(floating A, floating N);

/* t2hc_TMATS.c */
floating t2hc(floating T, floating fa);
/* pt2sc_TMATS.c */
floating pt2sc(floating P, floating T, floating fa);
/* sp2tc_TMATS.c */
floating sp2tc(floating S, floating P, floating fa);

/* interp1Ac_TMATS.c */
floating interp1Ac(floating *X, floating *Y, floating xi, int A, int *error);
/* interp2Ac_TMATS.c */
floating interp2Ac(floating *X, floating *Y, floating *Z, floating xi, floating yi, int A, int B, int *error);

/* PcalcStat_TMATS.c */
void PcalcStat(floating Pt, floating Ps, floating Tt, floating ht, floating FAR, floating Rt, floating *S, floating *Ts, floating *hs, floating *rhos, floating *V);

#endif  /* TMATS_FUNCTIONS_H */
