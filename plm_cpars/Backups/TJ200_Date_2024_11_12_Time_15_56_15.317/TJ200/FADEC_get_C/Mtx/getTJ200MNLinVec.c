


void getTJ200MNLinVec(double *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200MNLinVec[11] = {0.00000e+00, 1.00000e-01, 2.00000e-01, 3.00000e-01, 4.00000e-01, 5.00000e-01, 6.00000e-01, 7.00000e-01, 8.00000e-01, 9.00000e-01, 9.50000e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200MNLinVec + i);
};
};