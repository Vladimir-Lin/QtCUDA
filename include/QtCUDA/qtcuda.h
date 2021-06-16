/****************************************************************************
 *
 * Copyright (C) 2001~2016 Neutrino International Inc.
 *
 * Author : Brian Lin <lin.foxman@gmail.com>, Skype: wolfram_lin
 *
 * QtCUDA acts as an interface between Qt and CUDA library.
 * Please keep QtCUDA as simple as possible.
 *
 ****************************************************************************/

#ifndef QT_CUDA_H
#define QT_CUDA_H

#include <QtCore>

QT_BEGIN_NAMESPACE

#ifndef QT_STATIC
#    if defined(QT_BUILD_QTCUDA_LIB)
#      define Q_CUDA_EXPORT Q_DECL_EXPORT
#    else
#      define Q_CUDA_EXPORT Q_DECL_IMPORT
#    endif
#else
#      define Q_CUDA_EXPORT
#endif

class Q_CUDA_EXPORT QtCUDA ;
class Q_CUDA_EXPORT QtGL   ;

#if defined(_WIN64) || defined(__LP64__)
typedef unsigned long long cudaPtr    ;
typedef int                cudaHandle ;
#else
typedef unsigned int       cudaPtr    ;
typedef int                cudaHandle ;
#endif

// A CUDA wrapper for Qt to avoid typedef and function conflicts
class Q_CUDA_EXPORT QtCUDA
{
  public:

    explicit          QtCUDA         (void) ;
    virtual          ~QtCUDA         (void) ;

    static int        Initialize     (unsigned int Flags = 0) ;
    static int        Version        (void) ;
    static int        Devices        (void) ;
    static cudaHandle Handle         (int ordinal) ;
    static QString    Name           (cudaHandle handle) ;
    static QString    PciBus         (cudaHandle handle) ;

    // CUDA Memory Management
    static size_t     Memory         (cudaHandle handle) ;
    static cudaPtr    Allocate       (size_t size) ;
    static bool       Free           (cudaPtr cudaMemory) ;
    static void     * AllocateHost   (size_t size) ;
    static bool       FreeHost       (void * hostMemory) ;
    static bool       memcpy         (cudaPtr dst,cudaPtr      src,size_t bytes) ;
    static bool       memcpyHtoD     (cudaPtr dst,const void * src,size_t bytes) ;
    static bool       memcpyDtoH     (void *  dst,cudaPtr      src,size_t bytes) ;
    static bool       memcpyDtoD     (cudaPtr dst,cudaPtr      src,size_t bytes) ;
    static bool       memset         (cudaPtr dst,unsigned char  uc,size_t N) ;
    static bool       memsetD16      (cudaPtr dst,unsigned short uc,size_t N) ;
    static bool       memsetD32      (cudaPtr dst,unsigned int   uc,size_t N) ;

    // CUDA BLAS
    static bool       blasInitialize (void) ;
    static bool       blasShutdown   (void) ;

    static int        blasIsamax     (int n,const float  * x,int incx) ;
    static int        blasIdamax     (int n,const double * x,int incx) ;

    static void       add            (const float * a,const float * b,float * c, int n) ;

  protected:

  private:

} ;

class Q_CUDA_EXPORT QtGL
{
  public:

    explicit       QtGL            (void) ;
    virtual       ~QtGL            (void) ;

    static bool    Initialize      (void) ;

    static bool    Details         (QMap<int,QString> & information) ;

    static QString Version         (void) ;
    static QString Vendor          (void) ;
    static QString Renderer        (void) ;
    static QString Shading         (void) ;
    static QString Extensions      (unsigned int index) ;

    static int     GetError        (void) ;

    static void    GetBoolean      (int pname,unsigned char * params) ;
    static void    GetDouble       (int pname,double        * params) ;
    static void    GetFloat        (int pname,float         * params) ;
    static void    GetInteger      (int pname,int           * params) ;
    static void    GetLongLong     (int pname,qint64        * params) ;

    static void    AliasedRange    (double & minv,double & maxv) ;
    static void    SmoothRange     (double & minv,double & maxv) ;
    static double  LineGranularity (void) ;

    static void    ColorMaterial   (int face,int mode) ;
    static void    LightModelf     (int pname,float param) ;
    static void    LightModeli     (int pname,int   param) ;

    static void    Lightf          (int light,int pname,float         param ) ;
    static void    Lighti          (int light,int pname,int           param ) ;
    static void    Lightfv         (int light,int pname,const float * params) ;
    static void    Lightiv         (int light,int pname,const int   * params) ;

    static void    Frustum         (double left     ,
                                    double right    ,
                                    double bottom   ,
                                    double top      ,
                                    double nearVal  ,
                                    double farVal ) ;
    static void    Ortho           (double left     ,
                                    double right    ,
                                    double bottom   ,
                                    double top      ,
                                    double nearVal  ,
                                    double farVal ) ;
    static void    Projection      (int type,double * params) ;

    static void    Begin           (int mode) ;
    static void    LineWidth       (double width) ;
    static void    PointSize       (double size) ;
    static void    Points          (void) ;
    static void    Lines           (void) ;
    static void    Strips          (void) ;
    static void    Loop            (void) ;
    static void    Triangles       (void) ;
    static void    Quadrilateral   (void) ;
    static void    Polygon         (void) ;
    static void    End             (void) ;
    static void    Flush           (void) ;
    static void    Enable          (int cap) ;
    static void    Disable         (int cap) ;
    static void    Enable          (QMap<int,bool> & enablings) ;
    static void    Hint            (int target,int mode) ;
    static void    Clear           (int bits) ;
    static void    ShadeModel      (int mode) ;
    static void    BlendFunc       (int sfactor,int dfactor) ;
    static void    DepthFunc       (int func) ;
    static void    ClearColor      (double r,double g,double b,double a) ;

    static void    Viewport        (int x        ,
                                    int y        ,
                                    int width    ,
                                    int height ) ;
    static void    Viewport        (QRect  & area) ;
    static void    Viewport        (QRectF & area) ;
    static void    MatrixMode      (int mode) ;
    static void    LoadIdentity    (void) ;
    static void    Perspective     (double fovy    ,
                                    double aspect  ,
                                    double zNear   ,
                                    double zFar  ) ;
    static void    LookAt          (double eyeX    ,
                                    double eyeY    ,
                                    double eyeZ    ,
                                    double centerX ,
                                    double centerY ,
                                    double centerZ ,
                                    double upX     ,
                                    double upY     ,
                                    double upZ   ) ;

    static void    LoadMatrixd     (void * matrix) ;
    static void    LoadMatrixf     (void * matrix) ;
    static void    GetMatrixd      (int pname,void * matrix) ;
    static void    GetMatrixf      (int pname,void * matrix) ;
    static void    MultMatrixd     (void * matrix) ;
    static void    MultMatrixf     (void * matrix) ;

    static void    PushMatrix      (void) ;
    static void    PopMatrix       (void) ;

    static void    VertexPointer   (int          size      ,
                                    int          type      ,
                                    int          stride    ,
                                    const void * pointer ) ;

    static void    Vertex2f        (float    x,float  y) ;
    static void    Vertex2fv       (float  * v) ;
    static void    Vertex3f        (float    x,float  y,float  z) ;
    static void    Vertex3fv       (float  * v) ;
    static void    Vertex4f        (float    x,float  y,float  z,float w) ;
    static void    Vertex4fv       (float  * v) ;
    static void    Vertexfv        (int size,float * v) ;

    static void    Vertex2d        (double   x,double y) ;
    static void    Vertex2dv       (double * v) ;
    static void    Vertex3d        (double   x,double y,double z) ;
    static void    Vertex3dv       (double * v) ;
    static void    Vertex4d        (double   x,double y,double z,double w) ;
    static void    Vertex4dv       (double * v) ;
    static void    Vertexdv        (int size,double * v) ;

    static void    Color3f         (float    r,float  g,float  b) ;
    static void    Color3fv        (float  * v) ;
    static void    Color4f         (float    r,float  g,float  b,float a) ;
    static void    Color4fv        (float  * v) ;
    static void    Colorfv         (int size,float * v) ;

    static void    Color3d         (double   r,double g,double b) ;
    static void    Color3dv        (double * v) ;
    static void    Color4d         (double   r,double g,double b,double a) ;
    static void    Color4dv        (double * v) ;
    static void    Colordv         (int size,double * v) ;

    static void    TexCoord1f      (float  s) ;
    static void    TexCoord2f      (float  s,float  t) ;
    static void    TexCoord3f      (float  s,float  t,float  r) ;
    static void    TexCoord4f      (float  s,float  t,float  r,float  q) ;
    static void    TexCoord1d      (double s) ;
    static void    TexCoord2d      (double s,double t) ;
    static void    TexCoord3d      (double s,double t,double r) ;
    static void    TexCoord4d      (double s,double t,double r,double q) ;

    static void    TexCoord1fv     (float  * v) ;
    static void    TexCoord2fv     (float  * v) ;
    static void    TexCoord3fv     (float  * v) ;
    static void    TexCoord4fv     (float  * v) ;
    static void    TexCoordfv      (int size,float  * v) ;

    static void    TexCoord1dv     (double * v) ;
    static void    TexCoord2dv     (double * v) ;
    static void    TexCoord3dv     (double * v) ;
    static void    TexCoord4dv     (double * v) ;
    static void    TexCoorddv      (int size,double * v) ;

    static void    Scalef          (float    x,float  y,float  z) ;
    static void    Scalefv         (float  * v) ;
    static void    Scaled          (double   x,double y,double z) ;
    static void    Scaledv         (double * v) ;

    static void    Translatef      (float    x,float  y,float  z) ;
    static void    Translatefv     (float  * v) ;
    static void    Translated      (double   x,double y,double z) ;
    static void    Translatedv     (double * v) ;

    static void    Normal3b        (unsigned char nx   ,
                                    unsigned char ny   ,
                                    unsigned char nz ) ;
    static void    Normal3d        (double        nx   ,
                                    double        ny   ,
                                    double        nz ) ;
    static void    Normal3f        (float         nx   ,
                                    float         ny   ,
                                    float         nz ) ;
    static void    Normal3i        (int           nx   ,
                                    int           ny   ,
                                    int           nz ) ;
    static void    Normal3s        (short         nx   ,
                                    short         ny   ,
                                    short         nz ) ;
    static void    Normal3bv       (const unsigned char * v) ;
    static void    Normal3dv       (const double        * v) ;
    static void    Normal3fv       (const float         * v) ;
    static void    Normal3iv       (const int           * v) ;
    static void    Normal3sv       (const short         * v) ;

    static void    Rotatef         (float  r,float  x,float  y,float  z) ;
    static void    Rotated         (double r,double x,double y,double z) ;

    static void    Materiald       (int            face    ,
                                    int            pname    ,
                                    double         param  ) ;
    static void    Materialf       (int            face    ,
                                    int            pname    ,
                                    float          param  ) ;
    static void    Materiali       (int            face     ,
                                    int            pname    ,
                                    int            param  ) ;
    static void    Materialdv      (int            face     ,
                                    int            pname    ,
                                    int            items    ,
                                    const double * params ) ;
    static void    Materialfv      (int            face     ,
                                    int            pname    ,
                                    int            items    ,
                                    const float  * params ) ;
    static void    Materialiv      (int            face     ,
                                    int            pname    ,
                                    int            items    ,
                                    const int    * params ) ;

    static bool    PixelStorei     (int pname,int   param) ;
    static bool    PixelStoref     (int pname,float param) ;

    static void    PixelZoom       (float xfactor,float yfactor) ;
    static void    PixelZoom       (float * factors) ;
    static void    PixelZoom       (QSizeF  factors) ;

    static bool    BindTexture     (int target,unsigned int texture) ;
    static bool    GenTexture      (unsigned int & texture) ;
    static bool    GenTextures     (int size,unsigned int * textures) ;
    static void    DeleteTexture   (unsigned int id) ;
    static void    DeleteTextures  (int size,unsigned int * TIDs) ;

    static void    TexImage2D      (int     target   ,
                                    int     level    ,
                                    int     internal ,
                                    int     width    ,
                                    int     height   ,
                                    int     border   ,
                                    int     format   ,
                                    int     type     ,
                                    void  * data   ) ;
    static void    TexImage2D      (int     target   ,
                                    int     level    ,
                                    int     internal ,
                                    QSize   size     ,
                                    int     format   ,
                                    int     type     ,
                                    void  * data   ) ;

    static bool    TexEnvf         (int   target  ,
                                    int   pname   ,
                                    float param ) ;
    static bool    TexEnvi         (int   target  ,
                                    int   pname   ,
                                    int   param ) ;
    static bool    TexEnvm         (int                target       ,
                                    QMap<int,double> & parameters ) ;

    static bool    TexParameterf   (int   target  ,
                                    int   pname   ,
                                    float param ) ;
    static bool    TexParameteri   (int   target  ,
                                    int   pname   ,
                                    int   param ) ;
    static bool    TexParameterm   (int                target       ,
                                    QMap<int,double> & parameters ) ;

    static void    RasterPos2i     (int    x   ,
                                    int    y ) ;
    static void    RasterPos3i     (int    x   ,
                                    int    y   ,
                                    int    z ) ;
    static void    RasterPos4i     (int    x   ,
                                    int    y   ,
                                    int    z   ,
                                    int    w ) ;
    static void    RasterPos2f     (float  x   ,
                                    float  y ) ;
    static void    RasterPos3f     (float  x   ,
                                    float  y   ,
                                    float  z ) ;
    static void    RasterPos4f     (float  x   ,
                                    float  y   ,
                                    float  z   ,
                                    float  w ) ;
    static void    RasterPos2d     (double x   ,
                                    double y ) ;
    static void    RasterPos3d     (double x   ,
                                    double y   ,
                                    double z ) ;
    static void    RasterPos4d     (double x   ,
                                    double y   ,
                                    double z   ,
                                    double w ) ;

    static void    DrawPixels      (int    width    ,
                                    int    height   ,
                                    int    format   ,
                                    int    type     ,
                                    void * pixels ) ;
    static void    DrawPixels      (QSize  size     ,
                                    int    format   ,
                                    int    type     ,
                                    void * pixels ) ;

    static void    Map1f           (int     target   ,
                                    float   u1       ,
                                    float   u2       ,
                                    int     stride   ,
                                    int     order    ,
                                    void  * points ) ;
    static void    Map1d           (int     target   ,
                                    double  u1       ,
                                    double  u2       ,
                                    int     stride   ,
                                    int     order    ,
                                    void  * points ) ;
    static void    Map2f           (int     target   ,
                                    float   u1       ,
                                    float   u2       ,
                                    int     ustride  ,
                                    int     uorder   ,
                                    float   v1       ,
                                    float   v2       ,
                                    int     vstride  ,
                                    int     vorder   ,
                                    void  * points ) ;
    static void    Map2d           (int     target   ,
                                    double  u1       ,
                                    double  u2       ,
                                    int     ustride  ,
                                    int     uorder   ,
                                    double  v1       ,
                                    double  v2       ,
                                    int     vstride  ,
                                    int     vorder   ,
                                    void  * points ) ;

    static void    MapGrid1d       (int    partitions ,
                                    double u1         ,
                                    double u2       ) ;
    static void    MapGrid1f       (int    partitions ,
                                    float  u1         ,
                                    float  u2       ) ;
    static void    MapGrid2d       (int    un         ,
                                    double u1         ,
                                    double u2         ,
                                    int    vn         ,
                                    double v1         ,
                                    double v2       ) ;
    static void    MapGrid2f       (int    un         ,
                                    float  u1         ,
                                    float  u2         ,
                                    int    vn         ,
                                    float  v1         ,
                                    float  v2       ) ;

    static void    EvalMesh1       (int mode ,
                                    int i1   ,
                                    int i2 ) ;
    static void    EvalMesh2       (int mode ,
                                    int i1   ,
                                    int i2   ,
                                    int j1   ,
                                    int j2 ) ;

    static void    EvalCoord1d     (double u) ;
    static void    EvalCoord1f     (float  u) ;
    static void    EvalCoord2d     (double u,double v) ;
    static void    EvalCoord2f     (float  u,float  v) ;

    // GLEW functions

    // GLboolean glewIsSupported (const char *name);
    static bool    IsGLEW          (QString name) ;
    // GLboolean glewGetExtension (const char *name);
    static bool    IsExtension     (QString name) ;

  protected:

  private:

} ;

QT_END_NAMESPACE

#endif
