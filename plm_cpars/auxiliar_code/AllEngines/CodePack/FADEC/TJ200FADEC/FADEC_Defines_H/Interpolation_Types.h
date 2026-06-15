#ifndef INTERPOLATION_TYPES_H
#define INTERPOLATION_TYPES_H

#include "FloatPoint_Precision.h"

/* Structure for indexes parameters */
struct InterpIndex
{
    int K;
    floating f;
};
typedef struct InterpIndex InterpIndex;

/* Structure for interpolation Indexes */
struct InterpIndex3D
{
    int kA,kMN,kRPM;
	int kAH, kMNH, kRPMH;
    floating fA,fMN,fRPM;
};
typedef struct InterpIndex3D InterpIndex3D;


#endif /* INTERPOLATION_TYPES_H */
