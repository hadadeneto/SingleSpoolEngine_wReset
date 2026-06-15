


void getTJ1200AltLinVec(double *Pointer)
{
int i;
int TotalElem = 13;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200AltLinVec[13] = {0.00000e+00, 1.00000e+03, 2.00000e+03, 3.00000e+03, 4.00000e+03, 5.00000e+03, 6.00000e+03, 7.00000e+03, 8.00000e+03, 9.00000e+03, 1.00000e+04, 1.10000e+04, 1.20000e+04};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200AltLinVec + i);
};
};