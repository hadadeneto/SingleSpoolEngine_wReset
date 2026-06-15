


void getTJ1200FNcMaxContMtx(double *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200FNcMaxContMtx[11] = {4.90845e+03, 4.67176e+03, 4.47729e+03, 4.32357e+03, 4.20733e+03, 4.12402e+03, 4.06827e+03, 4.03390e+03, 4.01744e+03, 4.00659e+03, 4.00469e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200FNcMaxContMtx + i);
};
};