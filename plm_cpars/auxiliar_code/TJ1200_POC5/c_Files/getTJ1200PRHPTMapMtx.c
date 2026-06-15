


void getTJ1200PRHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200PRHPTMapMtx[21] = {1.24998e+00, 1.49997e+00, 1.56246e+00, 1.62496e+00, 1.68746e+00, 1.74995e+00, 1.81245e+00, 1.87494e+00, 1.93744e+00, 1.99994e+00, 2.06243e+00, 2.12493e+00, 2.18742e+00, 2.24992e+00, 2.31242e+00, 2.37491e+00, 2.43741e+00, 2.49990e+00, 2.56240e+00, 2.62490e+00, 2.74989e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200PRHPTMapMtx + i);
};
};