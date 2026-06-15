


void getTJ1200NcHPTMapMtx(double *Pointer)
{
int i;
int TotalElem = 7;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200NcHPTMapMtx[7] = {2.99388e-01, 3.49286e-01, 3.99184e-01, 4.49083e-01, 4.98981e-01, 5.48879e-01, 9.97961e-01};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200NcHPTMapMtx + i);
};
};