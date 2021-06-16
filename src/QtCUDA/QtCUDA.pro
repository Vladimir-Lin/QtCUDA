NAME                       = QtCUDA
TARGET                     = $${NAME}
QT                         = core
QT                        -= script

load(qt_module)

INCLUDEPATH               += $${PWD}/../../include/$${NAME}

HEADERS                   += $${PWD}/../../include/$${NAME}/qtcuda.h
HEADERS                   += $${PWD}/../../include/$${NAME}/GL/*.h

CUDASRCS                  =
CUDADEFS                  =

include ($${PWD}/CUDA/CUDA.pri)
include ($${PWD}/GLEW/GLEW.pri)

OTHER_FILES += $${PWD}/../../include/$${NAME}/headers.pri

include ($${PWD}/../../doc/Qt/Qt.pri)

SOURCES                   += qtcuda.cpp
SOURCES                   += qtgl.cpp

TRNAME                     = $${NAME}
include ($${PWD}/../../Translations.pri)

# CUDA settings <-- may change depending on your system

win32 {
  contains(QMAKE_TARGET.arch, x86_64) {
    CUDADIR               = $$(CUDA_PATH)
    SYSARCH               = 64
    CUDALIB               = x64
    CUDAARCH              = 52
    NVCCOPTS              = --use_fast_math --ptxas-options=-v
    # library directories
    LIBS                 += -L$${CUDADIR}/lib/$${CUDALIB}
    LIBS                 += -lcuda
    LIBS                 += -lcudart
    LIBS                 += -lcublas
    LIBS                 += -lcublas_device
    LIBS                 += -lcudadevrt
    LIBS                 += -lcufft
    LIBS                 += -lcufftw
    LIBS                 += -lcurand
    LIBS                 += -lcusolver
    LIBS                 += -lcusparse
    LIBS                 += -lnppc
    LIBS                 += -lnppi
    LIBS                 += -lnpps
    LIBS                 += -lnvblas
    LIBS                 += -lnvcuvid
    LIBS                 += -lnvrtc
    LIBS                 += -lOpenCL
    DEFINES              += CUDA_X64
  } else {
    CUDADIR               = $$(CUDA_PATH)
    SYSARCH               = 32
    CUDALIB               = Win32
    CUDAARCH              = 52
    NVCCOPTS              = --use_fast_math --ptxas-options=-v
    LIBS                 += -L$${CUDADIR}/lib/$${CUDALIB}
    LIBS                 += -lcuda
    LIBS                 += -lcudart
    LIBS                 += -lcudadevrt
    LIBS                 += -lnvcuvid
    LIBS                 += -lOpenCL
    DEFINES              += CUDA_X86
  }
  INCLUDEPATH            += $${CUDADIR}/include
  CONFIG(debug, debug|release) {
    LIBS                   += -lmsvcrtd
  } else {
    LIBS                   += -lmsvcrt
  }
    LIBS                   += -lglu32
    LIBS                   += -lopengl32
    LIBS                   += -luser32
    LIBS                   += -lgdi32
}

NVCCOPTS                   += -gencode=arch=compute_$${CUDAARCH},code=compute_$${CUDAARCH}

# The following makes sure all path names (which often include spaces) are put between quotation marks
CUDAINC                   = $$join(INCLUDEPATH,'" -I"','-I"','"')

# The following library conflicts with something in Cuda
QMAKE_LFLAGS_RELEASE      = /NODEFAULTLIB:msvcrt.lib
QMAKE_LFLAGS_DEBUG        = /NODEFAULTLIB:msvcrtd.lib

# Configuration of the CUDA compiler
CONFIG(debug, debug|release) {
  # Debug mode
  NVCCOPTS              += -Xcompiler /EHsc,/O2,/Zi,/MDd -g
  cuda_d.input           = CUDASRCS
  cuda_d.output          = debug/${QMAKE_FILE_BASE}_cuda.o
  cuda_d.commands        = $$CUDADIR/bin/nvcc.exe -D_DEBUG $$CUDADEFS $$NVCCOPTS $$CUDAINC $$LIBS --machine $$SYSARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
  cuda_d.dependency_type = TYPE_C
  QMAKE_EXTRA_COMPILERS += cuda_d
} else {
  # Release mode
  NVCCOPTS              += -Xcompiler /EHsc,/O2,/MD
  cuda.input             = CUDASRCS
  cuda.output            = release/${QMAKE_FILE_BASE}_cuda.o
  cuda.commands          = $$CUDADIR/bin/nvcc.exe $$NVCCOPTS $$CUDAINC $$LIBS --machine $$SYSARCH -c -o ${QMAKE_FILE_OUT} ${QMAKE_FILE_NAME}
  cuda.dependency_type   = TYPE_C
  QMAKE_EXTRA_COMPILERS += cuda
}
