#ifndef INTERPOLATION_TYPES_H
#define INTERPOLATION_TYPES_H


/* Structure for indexes parameters */
struct InterpIndex
{
    int K;
    double f;
};
typedef struct InterpIndex InterpIndex;

/* Structure for interpolation Indexes */
struct InterpIndex3D
{
    int kA,kMN,kRPM;
	int kAH, kMNH, kRPMH;
    double fA,fMN,fRPM;
};
typedef struct InterpIndex3D InterpIndex3D;


#endif /* INTERPOLATION_TYPES_H */
