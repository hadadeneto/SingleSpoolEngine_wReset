


void getTF1200NcVec(double *Pointer)
{
int i;
int TotalElem = 6;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200NcVec[6] = {6.95100e-01, 7.41700e-01, 8.00000e-01, 8.62000e-01, 9.12000e-01, 9.80000e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200NcVec + i);
};
};