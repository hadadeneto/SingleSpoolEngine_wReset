


void getTJ1200PRHPCStallMtx(double *Pointer)
{
int i;
int TotalElem = 10;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200PRHPCStallMtx[10] = {1.46874e+00, 1.75419e+00, 2.19452e+00, 2.52039e+00, 2.94103e+00, 3.54343e+00, 4.24892e+00, 5.03209e+00, 5.67618e+00, 6.21317e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200PRHPCStallMtx + i);
};
};