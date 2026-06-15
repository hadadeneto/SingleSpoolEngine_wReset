/*
 * PIMinMax.h
 *
 *  Created on: Dec 11, 2019
 *      Author: anton
 */

#ifndef CONTSOFTLOOP_H_
#define CONTSOFTLOOP_H_

/*===============*/
/* TJ1200 ENGINE */
/*===============*/

/* PI with Min Max and Reference Filter for TJ1200 */
void PIMinMaxTJ1200(struct ControlStart *ContStart, struct ControllerInput *ContInputP, struct ControllerOutput *ContOutputP, unsigned int *digitalP, unsigned int *keysP, double *NcFANContMtxP, double *FNperContMtxP, double *N_KpMtx, double *N_KiMtxP, double Tsample);

/*===============*/
/* TF1200 ENGINE */
/*===============*/

/* PI with Min Max and Reference Filter for TF1200 */
void PIMinMaxTF1200(struct ControlStart *ContStart, struct ControllerInput *ContInputP, struct ControllerOutput *ContOutputP, unsigned int *digitalP, unsigned int *keysP, double *NcFANContMtxP, double *FNperContMtxP, double *N_KpMtx, double *N_KiMtxP, double Tsample);


/*===============*/
/* GEJ85 ENGINE */
/*===============*/

/* PI with Min Max and Reference Filter for GEJ85 */
void PIMinMaxGEJ85(struct ControlStart *ContStart, struct ControllerInput *ContInputP, struct ControllerOutput *ContOutputP, unsigned int *digitalP, unsigned int *keysP, double *NcFANContMtxP, double *FNperContMtxP, double *N_KpMtx, double *N_KiMtxP, double Tsample);


#endif /* CONTSOFTLOOP_H_ */
