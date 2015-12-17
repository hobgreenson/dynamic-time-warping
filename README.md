This is some C code to do vanilla (i.e. no global constraints) 
dynamic time warping (DTW) using MATLAB. 

Only the distance between time series is returned.
You can expect a dramatic speed-up over equivalent MATLAB code
because the DTW algorithm is not (easily) vecotrizable. 
This code has been informally tested against the "dtw" library for R.

To get it to work:

> mex -setup
> mex -O dtw.c

Example usage:

> x = rand(1, 10000); y = rand(1, 10000); d = dtw(x, y)

Note: x and y must be row vectors.

Sometimes mex is a pain in the ass to work with. I got it working on
Mac OSX 10.9.5 by following instructions here:
http://www.mathworks.com/matlabcentral/answers/246507-why-can-t-mex-find-a-supported-compiler-in-matlab-r2015b-after-i-upgraded-to-xcode-7
