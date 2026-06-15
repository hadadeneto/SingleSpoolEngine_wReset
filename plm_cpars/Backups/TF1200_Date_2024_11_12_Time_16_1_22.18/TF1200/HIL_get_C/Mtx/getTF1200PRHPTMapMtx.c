


void getTF1200PRHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200PRHPTMapMtx[21] = {1.51215e+00, 2.02429e+00, 2.15233e+00, 2.28036e+00, 2.40840e+00, 2.53644e+00, 2.66447e+00, 2.79251e+00, 2.92055e+00, 3.04858e+00, 3.17662e+00, 3.30466e+00, 3.43269e+00, 3.56073e+00, 3.68877e+00, 3.81680e+00, 3.94484e+00, 4.07288e+00, 4.20091e+00, 4.32895e+00, 4.58502e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200PRHPTMapMtx + i);
};
};