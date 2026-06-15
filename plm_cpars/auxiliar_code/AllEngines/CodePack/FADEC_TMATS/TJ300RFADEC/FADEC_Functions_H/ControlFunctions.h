#ifndef CONTROL_FUNCTIONS_H
#define CONTROL_FUNCTIONS_H

#include "../FADEC_Defines_H/FloatPoint_Precision.h"

/*		T-MATS -- functions.h
 * % *************************************************************************
 * % written by Jeffryes Chapman
 * % NASA Glenn Research Center, Cleveland, OH
 * % August 2nd, 2016
 * %
 * %  This is a file that contains various functions for use in the T-MATS C-code
 * % *************************************************************************/

/* functions_TMATS.c */

//Min
floating Min(floating a, floating b);

//Max
floating Max(floating a, floating b);

//Proportional Integra Controller with Back Calculation Anti-Windup Protection
void PIControl(floating Ki, floating Kp, floating Kb, floating Ts, floating Ik1, floating ek, floating ek1, floating ebk1, struct PIOutput *Pointer);

//Acceleration Schedule Reference Finder
floating ASRefFind(floating *NcP, floating *ASP, floating Nc, floating Tt2, floating NcElNum, floating Tstd, floating NDes);

//Identifies the Active Controller
floating ActiveCont(floating *Pointer, floating NumSignals, floating u);

//Logic for a smooth transition of reference from starting mode to automatic mode
void RefRampSR(struct ControlStart *ContStartP, floating *Ref, floating RefRamp, floating Tick);

/*---------------------------------------------------------------------------------*/
/* FUNCTIONS PRESENT IN OLDER VERSION - TO BE USED DURING SOFTWARE TRANSITION ONLY */
/*---------------------------------------------------------------------------------*/

void RefRamp(floating *Ref, floating *RefInit, int *ResetP, floating RefRamp, floating Tick);

/*---------------------------------------------------------------------------------*/

#endif  /* CONTROL_FUNCTIONS_H */
