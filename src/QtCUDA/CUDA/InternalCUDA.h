#ifndef INTERNALCUDA_H
#define INTERNALCUDA_H

#include <cuda.h>
#include <cublas.h>
#include <cufft.h>
#include <cufftw.h>
#include <curand.h>
#include <cusparse.h>
#include <cuComplex.h>

extern "C" {

void vectorAddition(const float * a,const float * b,float* c,int n) ;

}

#endif
