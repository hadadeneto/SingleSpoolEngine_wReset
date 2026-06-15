


void getTJ1200OPOutVec(double *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200OPOutVec[2] = {0.00000e+00, 1.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200OPOutVec + i);
};
};