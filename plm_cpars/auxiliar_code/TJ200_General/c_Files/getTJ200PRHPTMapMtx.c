


void getTJ200PRHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 21;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ200PRHPTMapMtx[21] = {1.27101e+00, 1.54203e+00, 1.60978e+00, 1.67753e+00, 1.74529e+00, 1.81304e+00, 1.88080e+00, 1.94855e+00, 2.01630e+00, 2.08406e+00, 2.15181e+00, 2.21956e+00, 2.28732e+00, 2.35507e+00, 2.42282e+00, 2.49058e+00, 2.55833e+00, 2.62608e+00, 2.69384e+00, 2.76159e+00, 2.89710e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ200PRHPTMapMtx + i);
};
};