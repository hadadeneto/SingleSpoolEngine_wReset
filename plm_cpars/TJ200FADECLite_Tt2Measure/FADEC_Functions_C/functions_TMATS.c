/*		T-MATS -- functions_TMATS.c
 * % *************************************************************************
 * % written by Jeffryes Chapman
 * % NASA Glenn Research Center, Cleveland, OH
 * % August 2nd, 2016
 * %
 * %  This is a file that contains various functions for use in the T-MATS C-code
 * %  Functions:
 * %  sqrtT - square root with input limits
 * %  divby - divide by X with input limits
 * %  powT  - raised to the power of with input limits
 * % *************************************************************************/

//#include "../FADEC_Defines_H/constants_TMATS.h"
#include <math.h>

#include "../FADEC_Defines_H/FloatPoint_Precision.h"

floating sqrtT(floating X)
/* square root with input limits */
{
    floating H;
    /* value must be greater than or equal to 0 */
    if(X < 0)
        H = 0;
    else
#if DOUBLE_PRECISION
        H = sqrt(X);
#else
        H = sqrtf(X);
#endif


    return H;
}

floating divby(floating X)
/* division with input limits */
{
    floating H;
#if DOUBLE_PRECISION
    if(X < pow(10,-10) && X > -pow(10,-10))
        H = ((X >= 0) - (X < 0))*pow(10,10);
    else
        H = 1/X;
#else
    if(X < powf(10,-10) && X > -powf(10,-10))
        H = ((X >= 0) - (X < 0))*powf(10,10);
    else
        H = 1/X;
#endif

    return H;
}

floating powT(floating A, floating N)
/* exponential function with input limits */
{
    floating H;
#if DOUBLE_PRECISION
    if(A < pow(10,-10) && A > -pow(10,-10) && N < 0)
        H = pow(10,10);
    else
        H = pow(A,N);
#else
    if(A < powf(10,-10) && A > -powf(10,-10) && N < 0)
        H = powf(10,10);
    else
        H = powf(A,N);
#endif

    return H;
}




