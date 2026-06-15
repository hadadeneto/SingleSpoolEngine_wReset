#ifndef QSMC_FUNCTIONS_H
#define QSMC_FUNCTIONS_H


/*		QSMCFunctions.h
 * % *************************************************************************
 * % written by Antonio Hadade Neto
 * % Turbomachine, São José dos Campos, SP
 * % April 16th, 2020
 * %
 * %  Declaration of functions to be used for calculation of QSMC control law
 * % *************************************************************************/

void QSMCx(struct QSMCInput *QSMCInP);

void QSMCy(struct QSMCInput *QSMCInP);

void QSMCr(struct QSMCInput *QSMCInP, double urk);

#endif  /* QSMC_FUNCTIONS_H */
