


void getTF1200ASVec(double *Pointer)
{
int i;
int TotalElem = 6;

/* Reallocates the required ammount of memory to the pointer */

/* Matrix containing corresponding value for each breakpoint */
double TF1200ASVec[6] = {1.00850e+00, 1.01120e+00, 1.01875e+00, 1.04400e+00, 1.07400e+00, 1.02041e+00};


for(i = 0; i < TotalElem; i++){
    *(Pointer + i) = *(TF1200ASVec + i);
};
};