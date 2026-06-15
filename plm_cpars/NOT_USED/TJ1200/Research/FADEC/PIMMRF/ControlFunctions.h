#ifndef CONTROL_FUNCTIONS_H
#define CONTROL_FUNCTIONS_H


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
double Min(double a, double b);

//Max
double Max(double a, double b);

//Proportional Integra Controller with Back Calculation Anti-Windup Protection
void PIControl(double Ki, double Kp, double Kb, double Ts, double Ik1, double ek, double ek1, double ebk1, struct PIOutput *Pointer);

//Acceleration Schedule Reference Finder
double ASRefFind(double *NcP, double *ASP, double Nc, double Tt2, double NcElNum, double Tstd, double NDes);

//Identifies the Active Controller
double ActiveCont(double *Pointer, double NumSignals, double u);

//Logic for a smooth transition of reference from starting mode to automatic mode
double RefRamp(double *Ref, double *RefInit, int *ResetP, int RefRamp, double Tick);


#endif  /* CONTROL_FUNCTIONS_H */
