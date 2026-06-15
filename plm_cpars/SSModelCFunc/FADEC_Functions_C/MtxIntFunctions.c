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

#include <math.h>
#include <stdlib.h>
#include "../FADEC_Defines_H/Interpolation_Types.h"
#include "../FADEC_Defines_H/FloatPoint_Precision.h"

/*******************************************************************************
 *
 *	FUNCTION:		FADECMalloc()
 *
 *	PURPOSE:		Allocates memory for specified matrix and computes the used 
 *					memory
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		int Elements, long long int *MemSize
 *
 *	RETURNS:		IndexP
 *
 *	COMMENTS:
 *
 *******************************************************************************/

floating *FADECMalloc(int Elements, floating *MemSize){

	/* Computes the used memory */
	*MemSize += Elements*sizeof(floating);
	/* Allocates required memory */
	floating *Pointer = (floating *)malloc(Elements * sizeof(floating));
	/* Returns pointer */
	return Pointer;

}


/*******************************************************************************
 *
 *	FUNCTION:		FADECRealloc()
 *
 *	PURPOSE:		Allocates memory for specified matrix and computes the used 
 *					memory
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		int Elements, long long int *MemSize
 *
 *	RETURNS:		IndexP
 *
 *	COMMENTS:
 *
 *******************************************************************************/

floating *FADECRealloc(floating *Pointer, int Elements){

	/* Allocates required memory */
	Pointer = (floating *)realloc(Pointer, Elements * sizeof(floating));
	/* Returns the pointer */
	return Pointer;
}

/*******************************************************************************
 *
 *	FUNCTION:		IndFind()
 *
 *	PURPOSE:		Find the values K and f necessary for interpolation
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		value, NumEls, *VectorP
 *
 *	RETURNS:		IndexP
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void IndFind(floating value, int NumEls, floating *VectorP, struct InterpIndex *IndexP)

{
    
    
    //Defines Integer Index Value
    int K = NumEls-1;
    floating f = 0;
    int i= 0;
    
    //Routine for finding the indexes given the value and the vector
    for (i = 0; i < NumEls; i++)
    {
        //Verifies if the index i for wihtch value <= vector[i] was found
        if ((value < *(VectorP + i)) & (i > 0))
        {
            /* If it is smaller then the first value, K = 0 in order for
             * the the first value to be picked, which is the closest value
             * among the mapped ones to the desired value */
            if (i == 0){
                K = 0;
            }
            /* If 0 < i <= NumEls, K and f are calculated normally */
            else{
                K = i-1;
                f = (value - *(VectorP + K))/(*(VectorP + i)-*(VectorP + i - 1));
            }
            break;
        }
    }
        
    /*Stores the address of Index in IndexP and returns IndexP*/
	IndexP->K = K;
	IndexP->f = f;
}


/*******************************************************************************
 *
 *	FUNCTION:		getElement()
 *
 *	PURPOSE:		returns the desired element of a given matrix written in
 *                   the form of a single line string
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		*MtxElP, page, line, column, totallines, totalcolumns
 *
 *	RETURNS:		Element
 *
 *	COMMENTS:
 *
 *******************************************************************************/

floating getElement(floating *MtxElP, int page, int line, int column, int totallines, int totalcolumns)
{
    /* Local Variables */
    floating Element;
    int PageTerm;
    int LineTerm;
    int ColumnTerm;
    int Index;
    
    /* Calculates the terms for index calculation */
    PageTerm = page*totallines*totalcolumns;
    LineTerm = line*totalcolumns;
    ColumnTerm = column;
    
    /* Calculates the index */
    Index = PageTerm + LineTerm + ColumnTerm;
    
    /* Gets the desired element  */
    Element = *(MtxElP + Index);
    
    return Element;
}

/*******************************************************************************
 *
 *	FUNCTION:		getVecPart()
 *
 *	PURPOSE:		returns the pointer carrying the vector part of interest         
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		k, *VectorTo, *VectorFrom
 *
 *	RETURNS:		VectorTo
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void getVecPart(int k, int NumElements, floating *VectorTo, floating *VectorFrom)
{
    
    /* Local Variables */
    int i;
    
    /* Loop for Copying Vector Part */
    for(i = 0; i < NumElements; i++){
        *(VectorTo + i) = *(VectorFrom + i + k);
    };

}

/*******************************************************************************
 *
 *	FUNCTION:		InterpVectors()
 *
 *	PURPOSE:		Performs an interpolation of VecL and VecH with the parameter f
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		*Result, *VecL, *VecH, f
 *
 *	RETURNS:		None
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void InterpVectors(floating *Result, floating *VecL, floating *VecH, int NumElements, floating f)

{

	/* Internal Variables */
	int i;

	/* Performs an element by element interpolation */
	for (i = 0; i < NumElements; i++) {

		*(Result + i) = *(VecL + i) + f * (*(VecH + i) - *(VecL + i));

	};

}


/*******************************************************************************
 *
 *	FUNCTION:		InterpInd3DRPM()
 *
 *	PURPOSE:		returns a struct with desired indexes to be used in 3D
 *                  interpolation
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		Altitude, MN, RPM, *AltLinVecP, *MNLinVecP, *RPMP, *Index3DP
 *
 *	RETURNS:		Index3DP
 *
 *	COMMENTS:
 *
 *******************************************************************************/

void InterpInd3DRPM(floating Altitude, floating MN, floating RPM, floating *AltLinVecP, floating *MNLinVecP, floating *RPMP, floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating Alt_Elem, floating MN_Elem, floating FN_Elem, struct InterpIndex3D *Index3DP)

{
    
    /* Local Variables */
    int i;
    int kA, kAH, kF, kFH, kMN, kMNH, kRPM, kRPMH;
    int InitIndex;
	int NumElements;
    
	floating fA, fMN, fF, fRPM;
    
	InterpIndex IndexValues;
    
    /* GETS INDEXES CORRESPONDING TO AMBINET CONDITIONS */
    
    /* Gets Indexes of Altitude, Mach Number and Rotation Speed */
	IndFind(Altitude, Alt_Elem, AltLinVecP, &IndexValues);
    kA = IndexValues.K;
    fA = IndexValues.f;
    kAH = kA;
    
    /* If The Altitude lies between two mapped values, updates KAH */
    if(kA < Alt_Elem&& fA > 0){
        kAH = kA + 1;
    };

	/* Gets the lower bound 2D matrix*/
	NumElements = MN_Elem * FN_Elem;//MN_ELEM * FN_ELEM;
	InitIndex = kA * NumElements;
	getVecPart(InitIndex, NumElements, Mtx2DP, RPMP);

	/* Gets, if needed, the higher bound Altitude 2D Matrix */
	if (kA != kAH) {

		/* Gets the higher bound 2D matrix */
		InitIndex = kAH * NumElements;
		getVecPart(InitIndex, NumElements, Mtx2DHP, RPMP);
		InterpVectors(Mtx2DP, Mtx2DP, Mtx2DHP, NumElements, fA);

	};
    
    /* Gets Indexes of Altitude, Mach Number and Rotation Speed */
	IndFind(MN, MN_Elem, MNLinVecP, &IndexValues);
    kMN = IndexValues.K;
    fMN = IndexValues.f;
    kMNH = kMN;
    
    /* If The Macn Number lies between two mapped values, updates KMNH */
    if(kMN < MN_Elem && fMN > 0){
        kMNH = kMN + 1;
    };

	/* Gets the lower bound 1D matrix*/
	NumElements = FN_Elem;
	InitIndex = kMN * NumElements;
	getVecPart(InitIndex, NumElements, Mtx1DP, Mtx2DP);

	/* Gets, if needed, the higher bound Altitude 2D Matrix */
	if (kMN != kMNH) {

		/* Gets the higher bound 2D matrix */
		InitIndex = kMNH * NumElements;
		getVecPart(InitIndex, NumElements, Mtx1DHP, Mtx2DP);
		InterpVectors(Mtx1DP, Mtx1DP, Mtx1DHP, NumElements, fMN);

	};

	/* Gets Indexes of RPM*/
	IndFind(RPM, FN_Elem, Mtx1DP, &IndexValues);
	kRPM = IndexValues.K;
	fRPM = IndexValues.f;
	kRPMH = kRPM;

	/* If The Macn Number lies between two mapped values, updates KMNH */
	if (kRPM < FN_Elem && fRPM > 0) {
		kRPMH = kRPM + 1;
	};

    /* Reads calculated coefficients */
	Index3DP->kA = kA;
	Index3DP->kAH = kAH;
    Index3DP->fA = fA;
    Index3DP->kMN = kMN;
	Index3DP->kMNH = kMNH;
    Index3DP->fMN = fMN;
	Index3DP->kRPM = kRPM;
	Index3DP->kRPMH = kRPMH;
    Index3DP->fRPM = fRPM;
        
}


/*******************************************************************************
 *
 *	FUNCTION:		InterpValue()
 *
 *	PURPOSE:		returns the desired element of a given matrix written in
 *                   the form of a single line string
 *
 *	CALLED FROM:	tbd
 *
 *	PARAMETERS:		*Index3DP, RPM, *MtxP
 *
 *	RETURNS:		Value
 *
 *	COMMENTS:
 *
 *******************************************************************************/

floating InterpValue(struct InterpIndex3D *Index3DP, floating *MtxP, floating *Mtx2DP, floating *Mtx2DHP, floating *Mtx1DP, floating *Mtx1DHP, floating NumEl2D, floating NumEl1D)

{
    
    /* Local Variables */

	int InitIndex, NumElements;
    int kA, kMN, kRPM;
	int kAH, kMNH, kRPMH;
    
	floating fA, fMN, fRPM;
	floating Element;
	floating ElementH;

    kA = Index3DP->kA;
	kAH = Index3DP->kAH;
    fA = Index3DP->fA;
    kMN = Index3DP->kMN;
	kMNH = Index3DP->kMNH;
    fMN = Index3DP->fMN;
	kRPM = Index3DP->kRPM;
	kRPMH = Index3DP->kRPMH;
    fRPM = Index3DP->fRPM;
    
	/* CALCULATION OF INTERPOLATED VALUE */

	/* Gets the lower bound 2D matrix*/
	NumElements = NumEl2D;
	InitIndex = kA * NumElements;
	getVecPart(InitIndex, NumElements, Mtx2DP, MtxP);

	/* Gets, if needed, the higher bound Altitude 2D Matrix */
	if (kA != kAH) {

		/* Gets the higher bound 2D matrix */
		InitIndex = kAH * NumElements;
		getVecPart(InitIndex, NumElements, Mtx2DHP, MtxP);
		InterpVectors(Mtx2DP, Mtx2DP, Mtx2DHP, NumElements, fA);

	};

	/* Gets the lower bound 1D matrix*/
	NumElements = NumEl1D;
	InitIndex = kMN * NumElements;
	getVecPart(InitIndex, NumElements, Mtx1DP, Mtx2DP);

	/* Gets, if needed, the higher bound 1D Matrix */
	if (kMN != kMNH) {

		/* Gets the higher bound 2D matrix */
		InitIndex = kMNH * NumElements;
		getVecPart(InitIndex, NumElements, Mtx1DHP, Mtx2DP);
		InterpVectors(Mtx1DP, Mtx1DP, Mtx1DHP, NumElements, fMN);

	};

	/* Gets the lower bound element*/
	NumElements = 1;
	InitIndex = kRPM;
	getVecPart(InitIndex, NumElements, &Element, Mtx1DP);

	/* Gets, if needed, the higher bound Altitude 2D Matrix */
	if (kRPM != kRPMH) {

		/* Gets the higher bound 2D matrix */
		InitIndex = kRPMH;
		getVecPart(InitIndex, NumElements, &ElementH, Mtx1DP);
		InterpVectors(&Element, &Element, &ElementH, NumElements, fRPM);

	};

    return Element;
}



