


void getTJ700PRHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ700PRHPCStallMtx[10] = {7.15273e+00, 6.51897e+00, 5.75879e+00, 4.83447e+00, 4.00183e+00, 3.29086e+00, 2.79440e+00, 2.40980e+00, 1.89012e+00, 1.55322e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ700PRHPCStallMtx + i);
};
};