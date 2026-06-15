


void getTJ1200FNcMaxContMtx(double *Pointer)
{
int i;
int TotalElem = 11;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TJ1200FNcMaxContMtx[11] = {4.52791e+03, 4.29952e+03, 4.11521e+03, 3.97329e+03, 3.87023e+03, 3.80124e+03, 3.76069e+03, 3.74204e+03, 3.74136e+03, 3.74556e+03, 3.75091e+03};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TJ1200FNcMaxContMtx + i);
};
};