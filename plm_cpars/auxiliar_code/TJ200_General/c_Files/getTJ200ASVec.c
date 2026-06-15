


void getTJ200ASVec(double *Pointer)
{
int i;
int TotalElem = 6;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200ASVec[6] = {1.09000e+00, 1.08000e+00, 1.06000e+00, 1.08000e+00, 1.09000e+00, 1.01100e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200ASVec + i);
};
};