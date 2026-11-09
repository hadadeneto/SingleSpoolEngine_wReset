#ifndef MTXINIT_FUNCTIONS_H
#define MTXINIT_FUNCTIONS_H


/*		T-MATS -- functions.h
 * % *************************************************************************
 * % written by Jeffryes Chapman
 * % NASA Glenn Research Center, Cleveland, OH
 * % August 2nd, 2016
 * %
 * %  This is a file that contains various functions for use in the T-MATS C-code
 * % *************************************************************************/

#include "../FADEC_Defines_H/FloatPoint_Precision.h"
#include "../FADEC_Defines_H/Interpolation_Types.h"

/* Performs memory allocation for specified matrix */
floating *FADECMalloc(int Elements, floating *MemSize);

/* Performs memory reallocation for specified matrix */
floating *FADECRealloc(floating *Pointer, int Elements);

//Index Finder - Finds the necessary indexes for matrix interpolation
void IndFind(floating Value, int NumEls, floating *VectorP, struct InterpIndex *IndexP);

//Element Access - Gets the desired element of a matrix
floating getElement(floating *MtxElP, int page, int line, int column, int totallines, int totalcolumns);

//Copies a portion of the Vector to another one 
void getVecPart(int k, int NumElements, floating *VectorTo, floating *VectorFrom);

//Gets indexes for 3D interpolation from RPM vector
void InterpInd3DRPM(floating Altitude, floating MN, floating RPM, floating *AltLinVecP, floating *MNLinVecP, floating *RPMP, floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating Alt_Elem, floating MN_Elem, floating FN_Elem, struct InterpIndex3D *Index3DP);

//Gets interpolated value of necessary gains
floating InterpValue(struct InterpIndex3D *Index3DP, floating *MtxP, floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating NumEl2D, floating NumEl1D);

//Performs an interpolation of VecL and VecH with the parameter f
void InterpVectors(floating *Result, floating *VecL, floating *VecH, int NumElements, floating f);


#endif  /* CONTROL_FUNCTIONS_H */
