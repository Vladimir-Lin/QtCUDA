/****************************************************************************
 *
 * Copyright (C) 2015 Neutrino International Inc.
 *
 ****************************************************************************/

#include <qtcuda.h>
#include <InternalCUDA.h>

QtCUDA:: QtCUDA (void)
{
}

QtCUDA::~QtCUDA (void)
{
}

int QtCUDA::Initialize(unsigned int Flags)
{
  return (int) ::cuInit ( Flags ) ;
}

int QtCUDA::Version(void)
{
  int driverVersion = 0                                                   ;
  if ( CUDA_SUCCESS != ::cuDriverGetVersion ( &driverVersion ) ) return 0 ;
  return driverVersion                                                    ;
}

int QtCUDA::Devices(void)
{
  int deviceCount = 0                 ;
  ::cuDeviceGetCount ( &deviceCount ) ;
  return deviceCount                  ;
}

cudaHandle QtCUDA::Handle(int ordinal)
{
  cudaHandle cudaDevice = -1              ;
  ::cuDeviceGet ( &cudaDevice , ordinal ) ;
  return (cudaHandle) cudaDevice          ;
}

QString QtCUDA::Name(cudaHandle handle)
{
  char cudaDeviceName [256]                                  ;
  ::memset                 ( cudaDeviceName , 0   , 256    ) ;
  ::cuDeviceGetName        ( cudaDeviceName , 256 , handle ) ;
  return QString::fromUtf8 ( cudaDeviceName                ) ;
}

QString QtCUDA::PciBus(cudaHandle handle)
{
  char cudaPciName [256]                                  ;
  ::memset                 ( cudaPciName , 0   , 256    ) ;
  ::cuDeviceGetPCIBusId    ( cudaPciName , 256 , handle ) ;
  return QString::fromUtf8 ( cudaPciName                ) ;
}

size_t QtCUDA::Memory(cudaHandle handle)
{
  size_t   bytes = -1                                ;
  CUresult r                                         ;
  r = cuDeviceTotalMem ( &bytes , (CUdevice)handle ) ;
  if ( CUDA_SUCCESS == r ) return bytes              ;
  return -1                                          ;
}

cudaPtr QtCUDA::Allocate(size_t size)
{
  if ( size <= 0 ) return 0                     ;
  CUdeviceptr dptr = 0                          ;
  CUresult    r                                 ;
  r = cuMemAlloc ( &dptr , size )               ;
  if ( CUDA_SUCCESS == r ) return (cudaPtr)dptr ;
  return 0                                      ;
}

bool QtCUDA::Free(cudaPtr cudaMemory)
{
  if ( NULL == cudaMemory ) return true       ;
  CUdeviceptr dptr = (CUdeviceptr) cudaMemory ;
  CUresult    r                               ;
  r = cuMemFree ( dptr )                      ;
  return ( CUDA_SUCCESS == r )                ;
}

void * QtCUDA::AllocateHost (size_t size)
{
  void   * ptr = NULL                 ;
  CUresult r                          ;
  r = cuMemAllocHost ( &ptr , size )  ;
  if ( CUDA_SUCCESS == r ) return ptr ;
  return NULL                         ;
}

bool QtCUDA::FreeHost(void * hostMemory)
{
  if ( NULL == hostMemory ) return true ;
  CUresult r                            ;
  r = ::cuMemFreeHost ( hostMemory )    ;
  return ( CUDA_SUCCESS == r )          ;
}

bool QtCUDA::memcpy(cudaPtr dst,cudaPtr src,size_t bytes)
{
  CUresult r                           ;
  r = ::cuMemcpy ( dst , src , bytes ) ;
  return ( CUDA_SUCCESS == r )         ;
}

bool QtCUDA::memcpyHtoD(cudaPtr dst,const void * src,size_t bytes)
{
  CUresult r                             ;
  r = cuMemcpyHtoD ( dst , src , bytes ) ;
  return ( CUDA_SUCCESS == r )           ;
}

bool QtCUDA::memcpyDtoH(void * dst,cudaPtr src,size_t bytes)
{
  CUresult r                             ;
  r = cuMemcpyDtoH ( dst , src , bytes ) ;
  return ( CUDA_SUCCESS == r )           ;
}

bool QtCUDA::memcpyDtoD(cudaPtr dst,cudaPtr src,size_t bytes)
{
  CUresult r                             ;
  r = cuMemcpyDtoD ( dst , src , bytes ) ;
  return ( CUDA_SUCCESS == r )           ;
}

bool QtCUDA::memset(cudaPtr dst,unsigned char uc,size_t N)
{
  CUresult r                      ;
  r = cuMemsetD8 ( dst , uc , N ) ;
  return ( CUDA_SUCCESS == r )    ;
}

bool QtCUDA::memsetD16(cudaPtr dst,unsigned short uc,size_t N)
{
  CUresult r                       ;
  r = cuMemsetD16 ( dst , uc , N ) ;
  return ( CUDA_SUCCESS == r )     ;
}

bool QtCUDA::memsetD32(cudaPtr dst,unsigned int uc,size_t N)
{
  CUresult r                       ;
  r = cuMemsetD32 ( dst , uc , N ) ;
  return ( CUDA_SUCCESS == r )     ;
}

bool QtCUDA::blasInitialize (void)
{
  #ifdef CUDA_X64
  cublasStatus r                        ;
  r = cublasInit ( )                    ;
  return ( CUBLAS_STATUS_SUCCESS == r ) ;
  #endif
  #ifdef CUDA_X86
  return false ;
  #endif
}

bool QtCUDA::blasShutdown (void)
{
  #ifdef CUDA_X64
  cublasStatus r                        ;
  r = cublasShutdown ( )                ;
  return ( CUBLAS_STATUS_SUCCESS == r ) ;
  #endif
  #ifdef CUDA_X86
  return false ;
  #endif
}

int QtCUDA::blasIsamax(int n,const float * x,int incx)
{
  #ifdef CUDA_X64
  return ::cublasIsamax ( n , x , incx ) ;
  #endif
  #ifdef CUDA_X86
  return 0 ;
  #endif
}

int QtCUDA::blasIdamax(int n,const double * x,int incx)
{
  #ifdef CUDA_X64
  return ::cublasIdamax ( n , x , incx ) ;
  #endif
  #ifdef CUDA_X86
  return 0 ;
  #endif
}

void QtCUDA::add(const float * a,const float * b,float * c, int n)
{
  ::vectorAddition ( a , b , c , n ) ;
}
