/*
 * getMtx.h
 *
 *  Created on: January 29, 2020
 *      Author: Antonio Hadade Neto
 */

#ifndef GETCONTCONST_H
#define GETCONTCONST_H

/* FUNCTION FOR LOADING TJ1200 MATRICES */

void getTJ1200ContConst(struct ControllerConstants *ContConst);

/* FUNCTION FOR LOADING TF1200 MATRICES */

void getTF1200ContConst(struct ControllerConstants *ContConst);

/* FUNCTION FOR LOADING GE J85 CONTROLLER CONSTANTS */

void getGEJ85ContConst(struct ControllerConstants *ContConst);


#endif /* GETCONTCONST_H */
