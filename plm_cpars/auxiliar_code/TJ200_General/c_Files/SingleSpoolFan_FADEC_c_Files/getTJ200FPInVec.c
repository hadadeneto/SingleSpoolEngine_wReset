


void getTJ200FPInVec(double *Pointer)
{
int i;
int TotalElem = 16;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200FPInVec[16] = {0.00000e+00, 9.72000e-02, 9.92000e-02, 1.13400e-01, 1.27500e-01, 1.41700e-01, 1.55900e-01, 1.61500e-01, 1.70100e-01, 1.55900e-01, 1.41700e-01, 1.27500e-01, 1.13400e-01, 9.92000e-02, 8.50000e-02, 3.20350e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200FPInVec + i);
};
};