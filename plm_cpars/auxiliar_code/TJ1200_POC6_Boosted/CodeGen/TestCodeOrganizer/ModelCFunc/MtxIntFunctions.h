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

//Index Finder - Finds the necessary indexes for matrix interpolation
void IndFind(double Value, int NumEls, double *VectorP, struct InterpIndex *IndexP);

//Element Access - Gets the desired element of a matrix
double getElement(double Mtx[], int line, int column, int page, int totallines, int totalcolumns);

//Copies a portion of the Vector to another one 
void *getVecPart(int k, int NumElements, double *VectorTo, double *VectorFrom);

//Gets indexes for 3D interpolation from RPM vector
//void InterpInd3DRPM(double Altitude, double MN, double RPM, double *AltLinVecP, double *MNLinVecP, double *RPMP, struct InterpIndex3D *Index3DP);
void InterpInd3DRPM(double Altitude, double MN, double RPM, double *AltLinVecP, double *MNLinVecP, double *RPMP, double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP, double Alt_Elem, double MN_Elem, double FN_Elem, struct InterpIndex3D *Index3DP);

//Gets interpolated value of necessary gains
double InterpValue(struct InterpIndex3D *Index3DP, double *MtxP, double *Mtx2DP, double *Mtx2DHP, double *Mtx1DP, double *Mtx1DHP, double NumEl2D, double NumEl1D);

//Performs an interpolation of VecL and VecH with the parameter f
void InterpVectors(double *Result, double *VecL, double *VecH, int NumElements, double f);


#endif  /* CONTROL_FUNCTIONS_H */
