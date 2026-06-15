


void getTJ40DSVec(double *Pointer)
{
int i;
int TotalElem = 6;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ40DSVec[6] = {9.20000e-01, 9.20000e-01, 9.20000e-01, 9.20000e-01, 9.20000e-01, 9.20000e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ40DSVec + i);
};
};