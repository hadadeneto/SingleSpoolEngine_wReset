


void getTJ1200FPOutVec(double *Pointer)
{
int i;
int TotalElem = 16;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200FPOutVec[16] = {0.00000e+00, 5.97530e-02, 6.23690e-02, 7.95610e-02, 9.47120e-02, 1.09300e-01, 1.23470e-01, 1.28560e-01, 1.36700e-01, 1.22620e-01, 1.08310e-01, 9.36320e-02, 7.89210e-02, 6.40970e-02, 4.81490e-02, 2.83500e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200FPOutVec + i);
};
};