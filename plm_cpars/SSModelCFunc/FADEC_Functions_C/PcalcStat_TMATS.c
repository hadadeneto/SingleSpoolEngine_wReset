/*		T-MATS -- PcalcStat_TMATS.c
% *************************************************************************
% written by Jeffryes Chapman based on work by T. Lavelle
% NASA Glenn Research Center, Cleveland, OH
% February 2nd, 2012
%
%  (S, Ts, hs, rho, V) = f(Pt, Ps, Tt, ht, FAR, Rt).
% *************************************************************************/

#include <math.h>
#include "../FADEC_Defines_H/constants_TMATS.h"
#include "../FADEC_Functions_H/functions_TMATS.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"

void PcalcStat(floating Pt, floating Ps, floating Tt, floating ht, floating FAR, floating Rt, floating *S, floating *Ts, floating *hs, floating *rhos, floating *V)
{
            floating Rs;

            /* Compute entropy */
            *S = pt2sc(Pt, Tt, FAR);
            /* Compute Static Temperature */
            *Ts = sp2tc(*S,Ps,FAR);
            if (*Ts > Tt) {
                    *Ts = Tt;
            }
            /* Compute static enthalpy */
            *hs = t2hc(*Ts,FAR);
            if (*hs > ht) {
                    *hs = ht;
            }
            /* Assume Rt = Rs */
            Rs = Rt;
            /* Compute static rho */
            *rhos = Ps * C_PSItoPSF*divby(Rs* *Ts * JOULES_CONST);
            /* Compute Velocity */
            *V = sqrtT(2 * (ht - *hs)*C_GRAVITY*JOULES_CONST);
            
}