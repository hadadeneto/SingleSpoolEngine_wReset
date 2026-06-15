


void getGEJ85FPOutVec(double *Pointer)
{
int i;
int TotalElem = 2;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double GEJ85FPOutVec[2] = {0.00000e+00, 1.00000e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(GEJ85FPOutVec + i);
};
};