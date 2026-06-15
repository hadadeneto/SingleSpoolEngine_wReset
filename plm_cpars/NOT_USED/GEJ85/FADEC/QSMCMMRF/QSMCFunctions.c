/*		T-MATS -- functions_TMATS.c 
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % Turbomachine, Jacareí - Brasil
 * % April 14th, 2020
 * %
 * %  This is a file that contains functions calculating the control laws of 
 * %  QSMC for controlled state-variable and controlled observed variable
 * %  Functions:
 * %  QSMCx - control law for controlled state-variable
 * %  QSMCy - control law for controlled observed variable
 * % *************************************************************************/

//#include "constants_TMATS.h"
#include <math.h>
#include "Control_Types.h"
#include "Interpolation_Types.h"
#include "Env_SampTime.h"
#include "MtxIntFunctions.h"


/*******************************************************************************
 *
 *	FUNCTION:		QSMCy()
 *
 *	PURPOSE:		Calculates QSMC control law for observed value (double)
 *					in the case where it differs from state variable
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		*QSMCInP
 *
 *	RETURNS:		uk
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void QSMCy(struct QSMCInput *QSMCInP)
{
	/* Variables */
	double Drk, Dxk, Dyk, Duk, Sk, vk, dxk1, dyk, delta_x, delta_y;
	double A, B, C, D, xk, xke, yk, yke, uk, xss, yss, uss, Ref, G, q, Eps, Rho, Kia, T;
	double Dxk1, Duk1, dxk2, dyk1;
	double v1, v2, v3, v4, v5, v6;
	double k0, k1a, k1b, k2, k3, k4, k5, k6;

	/* READS INPUT VARIABLES */

	/* Obs.: The variables xk, yk and uk are, respectively, x(k), y(k) and u(k), which are explained as follows:   
	*
	* x(k) - last read value of the state variable (currently in the memory)
	* y(k) - last read value of the observed variable (currently in the memory)
	* u(k) - last read value of the control signal (currently in the memory).This value can be either the last
	*		 calculated value of u(k) by the controller or the last actual value sent to the plant (in case of
	*		 saturation or Min-Max logic). This is defined outside this function
	*
	* If the last value actually sent to the plant is not used, Anti-Windup technique is required
	* and must be developed for QSMC */

	A = QSMCInP->A;
	B = QSMCInP->B;
	C = QSMCInP->C;
	D = QSMCInP->D;
	xk = QSMCInP->x;
	xke = QSMCInP->xe;
	yk = QSMCInP->y;
	yke = QSMCInP->ye;
	uk = QSMCInP->uIn;
	uss = QSMCInP->uss;
	xss = QSMCInP->xss;
	yss = QSMCInP->yss;
	Ref = QSMCInP->Ref;
	G = QSMCInP->G;
	q = QSMCInP->q;
	Eps = QSMCInP->Eps;
	Rho = QSMCInP->Rho;
	Kia = QSMCInP->Kia;
	T = QSMCInP->T;

	/* LOADS MEMORY VARIABLES */

	Dxk1 = QSMCInP->Dxk;
	Duk1 = QSMCInP->Duk;
	dyk1 = QSMCInP->dyk;
	dxk2 = QSMCInP->dxk1;

	/* CALCULATES DELTA VALUES */

	Dxk = xk - xss;
	//Dyk = yk - yss;
	Duk = uk - uss;
	Drk = Ref - yss;

	/* CALCULATES CONTROL LAW COEFFICIENTS */

	k0 = -1 / G / D;
	//k1a = G * C * A; 
	//k1b = G * (C * B + D);
	k1a = G * C ; 
	k1b = G * D;
	k2 = -(1 - q * T);
	k3 = Eps * T;
	k4 = -G;
	k5 = 0;//G * C;
	k6 = G;

	/* CALCULATES SLIDING SURFACE VALUE */
	
	Sk = G * (yk - Ref);

	/* CALCULATES DISTURBANCE VALUES */

	/* Calculates respective disturbance values */
	//dxk1 = Dxk - (A * Dxk1 + B * Duk1);
	//dyk = Dyk - (C * Dxk1 + D * Duk1);
	/* Calculates respective disturbance values */
	/* Obs.: The variables xss1 and yss1 are from the system below:
			 x(k+1) - xss = A * (x(k) - xss) + B * (u(k) - uss);
			 y(k) = C * 
			 */
	dxk1 = xk - xke; 
	dyk = yk - yke;

	/* Calculates respective delta values */
	delta_x = 2 * dxk1 - dxk2;
	delta_y = 2 * dyk - dyk1;

	/* CALCULATES TERMOS OF v(k) */

	vk = k0 * (k1a * Dxk + k1b * Duk + k2 * Sk + k3 * (Sk / (fabs(Sk) + Rho)) + k4 * Drk);
	vk = vk + k0 * k5*delta_x + k0 * k6 * delta_y;

    /* CALCULATES Du(k+1) - Du(k) IS UPDATED */
    
    Duk = Duk + Kia * vk;
    
    /* CALCULATES CONTROL SIGNAL */
    
    uk = Duk + uss;

	/* ESTIMATES FUTURE VALUES OF xk AND yk */
	xke = A * Dxk + B * Duk + xss;
	yke = C * Dxk + D * Duk + yss;

	/* UPDATES CALCULATED DELTA VALUES */

	QSMCInP->Duk = Duk;
	QSMCInP->Dxk = Dxk;
	QSMCInP->dxk1 = dxk1;
	QSMCInP->dyk = dyk;
	QSMCInP->xe = xke;
	QSMCInP->ye = yke;

	/* UPDATES OUTPUT */ 

	QSMCInP->uOut = uk;
}


/*******************************************************************************
 *
 *	FUNCTION:		QSMCx()
 *
 *	PURPOSE:		Calculates QSMC control law for observed value (double)
 *					in the case where it equals the state variable
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		*QSMCInP
 *
 *	RETURNS:		uk
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void QSMCx(struct QSMCInput *QSMCInP)
{
	/* Variables */
	double Drk, Dxk, Duk, Sk, dxk1;
	double A, B, C, D, xk, xke, uk, xss, uss, Ref, G, q, Eps, Rho, T;
	double Dxk1, Duk1, dxk2, delta_x;
	double k0, k1, k2, k3, k4, k5;

	/* READS INPUT VARIABLES */

		/* Obs.: The variables xk, yk and uk are, respectively, x(k), y(k) and u(k), which are explained as follows:
	*
	* x(k) - last read value of the state variable (currently in the memory)
	* u(k) - last read value of the control signal (currently in the memory).This value can be either the last
	*		 calculated value of u(k) by the controller or the last actual value sent to the plant (in case of
	*		 saturation or Min-Max logic). This is defined outside this function */

	A = QSMCInP->A;
	B = QSMCInP->B;
	C = QSMCInP->C;
	D = QSMCInP->D;
	xk = QSMCInP->x;
	xke = QSMCInP->xe;
	uk = QSMCInP->uIn;
	uss = QSMCInP->uss;
	xss = QSMCInP->xss;
	Ref = QSMCInP->Ref;
	G = QSMCInP->G;
	q = QSMCInP->q;
	Eps = QSMCInP->Eps;
	Rho = QSMCInP->Rho;
	T = QSMCInP->T;
	
	/* LOADS MEMORY VARIABLES */ 

	Dxk1 = QSMCInP->Dxk;
	Duk1 = QSMCInP->Duk;
	dxk2 = QSMCInP->dxk1;

	/* CALCULATES DELTA VALUES */

	Dxk = xk - xss;
	Duk = uk - uss;
	Drk = Ref - xss;

	/* CALCULATES SLIDING SURFACE VALUE */

	Sk = G * (xk - Ref);

	/* CALCULATES DISTURBANCE VALUE d(k) */

	//dxk1 = Dxk - (A * Dxk1 + B * Duk1);
	dxk1 = xk - xke;


	/* CALCULATES THE VALUE OF DELTA */

	delta_x = 2 * dxk1 - dxk2;

	/* CALCULATES CONTROL LAW COEFFICIENTS */

	k0 = - 1 / G / B;
	k1 = G * A;
	k2 = -(1 - q * T);
	k3 = Eps * T;
	k4 = -G;
	k5 = G;


	/* CALCULATES THE CONTROL LAW */

	Duk = k0 * (k1 * Dxk + k2 * Sk + k3 * (Sk / (fabs(Sk) + Rho)) + k4 * Drk);
	Duk = Duk + k0 * k5 * delta_x;

	/* CALCULATES CONTROL SIGNAL */

	uk = Duk + uss;

	/* ESTIMATES FUTURE VALUE OF xk */
	
	xke = A * Dxk + B * Duk + xss;

	/* UPDATES CALCULATED DELTA VALUES */

	QSMCInP->Duk = Duk;
	QSMCInP->Dxk = Dxk;
	QSMCInP->dxk1 = dxk1;
	QSMCInP->xe = xke;

	/* UPDATES OUTPUT */

	QSMCInP->uOut = uk;
}

/*******************************************************************************
 *
 *	FUNCTION:		QSMCr()
 *
 *	PURPOSE:		Calculates QSMC 
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		*QSMCInP
 *
 *	RETURNS:		uk
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void QSMCr(struct QSMCInput *QSMCInP, double urk)
{

	/* Variables */
	double Dxk, Duk, uss, xss, yss, xek, yek;
	double A, B, C, D;

	/* Reads static value of control signal */
	uss = QSMCInP->uss;
	xss = QSMCInP->xss;
	yss = QSMCInP->yss;
	Dxk = QSMCInP->Dxk;
	A = QSMCInP->A;
	B = QSMCInP->B;
	C = QSMCInP->C;
	D = QSMCInP->D;

	/* Calculates the real Duk value */
	Duk = urk - uss;

	/* Calculates the estimate values of xk and yk */
	xek = A * Dxk + B * Duk + xss;
	yek = C * Dxk + D * Duk + yss;

	/* Updates estimated values */
	QSMCInP->xe = xek;
	QSMCInP->ye = yek;
	QSMCInP->Duk = Duk;

}