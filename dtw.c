
#include "mex.h"
#include <math.h>
#include <stdlib.h>

static inline double min3(double a, double b, double c) {
    double min = a;
    min = (min < b) ? min : b;
    min = (min < c) ? min : c;
    return min;
}

static double dtw(double* x, int N, double* y, int M) {
    /* Notes: 
       - M must be less than the stack size limit for arrays,
         otherwise you'll get a stack overflow.
       - x and y must be row vectors in MATLAB.
    */ 
    
    double D[M], start, dd, dmin;
    
    D[0] = fabs(x[0] - y[0]);
    for (int j = 1; j < M; ++j) {
        D[j] = D[j-1] + fabs(x[0] - y[j]);
    }
    
    start = D[0];
    for (int i = 1; i < N; ++i) {
        start += fabs(x[i] - y[0]);
        dd = start;
        for (int j = 1; j < M; ++j) {
            dmin = min3(D[j-1], D[j], dd);
            D[j-1] = dd;
            dd = fabs(x[i] - y[j]) + dmin;                 
        }
        D[M-1] = dd;
    }
    
    return D[M-1];
}

void mexFunction(int nlhs, mxArray *plhs[],
                 int nrhs, const mxArray *prhs[])
{
    double* x; 
    double* y;
    size_t lenx;  
    size_t leny; 
    double* d;   
    
    if (nrhs != 2) {
        mexErrMsgIdAndTxt("DTW:nrhs","Two inputs required.");
    }
    
    if (nlhs != 1) {
        mexErrMsgIdAndTxt("DTW:nlhs","One output required.");
    }
    
    if (!mxIsDouble(prhs[0]) || mxIsComplex(prhs[0])) {
        mexErrMsgIdAndTxt("DTW:notDouble","Input matrix must be type double.");
    }
    
    if (!mxIsDouble(prhs[1]) || mxIsComplex(prhs[1])) {
        mexErrMsgIdAndTxt("DTW:notDouble","Input matrix must be type double.");
    }
    
    if (mxGetM(prhs[0]) != 1) {
        mexErrMsgIdAndTxt("DTW:notRowVector","Input must be a row vector.");
    }
    
    if (mxGetM(prhs[1]) != 1) {
        mexErrMsgIdAndTxt("DTW:notRowVector","Input must be a row vector.");
    }
    
    x = mxGetPr(prhs[0]);
    y = mxGetPr(prhs[1]);

    lenx = mxGetN(prhs[0]);
    leny = mxGetN(prhs[1]);

    plhs[0] = mxCreateDoubleMatrix(1, (mwSize)1, mxREAL);

    d = mxGetPr(plhs[0]);

    d[0] = dtw(x, (int)lenx, y, (int)leny);
}
