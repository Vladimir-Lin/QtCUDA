/****************************************************************************
 *
 * Copyright (C) 2001~2016 Neutrino International Inc.
 *
 ****************************************************************************/

#include <qtcuda.h>
#include <GL/glew.h>
#include <GL/wglew.h>

#ifdef Q_OS_WIN
#include <windows.h>
#endif

#ifdef Q_OS_WIN

LRESULT CALLBACK OpenGLTestingWndProc ( HWND   ,
                                        UINT   ,
                                        WPARAM ,
                                        LPARAM )
{
  return 1 ;
}

#endif

bool InitializeQtGL = false ;

QtGL:: QtGL (void)
{
  Initialize ( ) ;
}

QtGL::~QtGL (void)
{
}

bool QtGL::Initialize(void)
{
  if ( InitializeQtGL ) return true ;
  ::glewInit ( )                    ;
  InitializeQtGL = true             ;
  return true                       ;
}

bool QtGL::Details(QMap<int,QString> & information)
{
  #ifdef Q_OS_WIN
  HWND      hWnd                                                             ;
  HGLRC     hRC                                                              ;
  HDC       hDC                                                              ;
  HINSTANCE hInstance                                                        ;
  WNDCLASS  windClass                                                        ;
  TCHAR     szWindowName [ 50 ] = TEXT ( "OpenGL_Window_Info" )              ;
  TCHAR     szClassName  [ 50 ] = TEXT ( "OpenGL_Class_Info"  )              ;
  ////////////////////////////////////////////////////////////////////////////
  hInstance = GetModuleHandle ( NULL )                                       ;
  windClass . lpszClassName = szClassName                                    ;
  windClass . lpfnWndProc   = (WNDPROC) OpenGLTestingWndProc                 ;
  windClass . hInstance     = hInstance                                      ;
  windClass . hCursor       = LoadCursor ( NULL , IDC_ARROW   )              ;
  windClass . hIcon         = LoadIcon   ( NULL , IDI_WINLOGO )              ;
  windClass . hbrBackground = NULL                                           ;
  windClass . lpszMenuName  = NULL                                           ;
  windClass . style         = 0                                              ;
  windClass . cbClsExtra    = 0                                              ;
  windClass . cbWndExtra    = 0                                              ;
  ////////////////////////////////////////////////////////////////////////////
  if ( ! RegisterClass ( &windClass ) ) return false                         ;
  ////////////////////////////////////////////////////////////////////////////
  PIXELFORMATDESCRIPTOR pfd                                                  ;
  hWnd = CreateWindowEx                                                      (
           0                                                                 ,
           szClassName                                                       ,
           szWindowName                                                      ,
           0                                                                 ,
           0                                                                 ,
           0                                                                 ,
           0                                                                 ,
           0                                                                 ,
           NULL                                                              ,
           NULL                                                              ,
           hInstance                                                         ,
           NULL                                                            ) ;
  hDC = ::GetDC            ( hWnd           )                                ;
  ::SetPixelFormat         ( hDC , 1 , &pfd )                                ;
  hRC = ::wglCreateContext ( hDC            )                                ;
  ::wglMakeCurrent         ( hDC , hRC      )                                ;
  #endif
  ////////////////////////////////////////////////////////////////////////////
  information [ GL_VERSION                  ] = Version  ( )                 ;
  information [ GL_VENDOR                   ] = Vendor   ( )                 ;
  information [ GL_RENDERER                 ] = Renderer ( )                 ;
  information [ GL_SHADING_LANGUAGE_VERSION ] = Shading  ( )                 ;
  ////////////////////////////////////////////////////////////////////////////
  #ifdef Q_OS_WIN
  ::wglMakeCurrent   ( NULL        , NULL      )                             ;
  ::wglDeleteContext ( hRC                     )                             ;
  ::ReleaseDC        ( hWnd        , hDC       )                             ;
  ::DestroyWindow    ( hWnd                    )                             ;
  UnregisterClass    ( szClassName , hInstance )                             ;
  #endif
  return true ;
}

QString QtGL::Version(void)
{
  QString v                                 ;
  char  * s                                 ;
  s = (char *) ::glGetString ( GL_VERSION ) ;
  if ( NULL != s )                          {
    v = QString::fromUtf8 ( s )             ;
  }                                         ;
  return v                                  ;
}

QString QtGL::Vendor(void)
{
  QString v                                ;
  char  * s                                ;
  s = (char *) ::glGetString ( GL_VENDOR ) ;
  if ( NULL != s )                         {
    v = QString::fromUtf8 ( s )            ;
  }                                        ;
  return v                                 ;
}

QString QtGL::Renderer(void)
{
  QString v                                  ;
  char  * s                                  ;
  s = (char *) ::glGetString ( GL_RENDERER ) ;
  if ( NULL != s )                           {
    v = QString::fromUtf8 ( s )              ;
  }                                          ;
  return v                                   ;
}

QString QtGL::Shading(void)
{
  QString v                                                  ;
  char  * s                                                  ;
  s = (char *) ::glGetString ( GL_SHADING_LANGUAGE_VERSION ) ;
  if ( NULL != s )                                           {
    v = QString::fromUtf8 ( s )                              ;
  }                                                          ;
  return v                                                   ;
}

QString QtGL::Extensions(unsigned int index)
{
  QString v                                           ;
  char  * s                                           ;
  s = (char *) glGetStringi ( GL_EXTENSIONS , index ) ;
  if ( NULL != s )                                    {
    v = QString::fromUtf8 ( s )                       ;
  }                                                   ;
  return v                                            ;
}

int QtGL::GetError(void)
{
  return ::glGetError ( ) ;
}

void QtGL::GetBoolean(int pname,unsigned char * params)
{
  ::glGetBooleanv ( (GLenum) pname , (GLboolean *) params ) ;
}

void QtGL::GetDouble(int pname,double * params)
{
  ::glGetDoublev ( (GLenum) pname , (GLdouble *) params ) ;
}

void QtGL::GetFloat(int pname,float * params)
{
  ::glGetFloatv ( (GLenum) pname , (GLfloat  *) params ) ;
}

void QtGL::GetInteger(int pname,int * params)
{
  ::glGetIntegerv ( (GLenum) pname , (GLint *) params ) ;
}

void QtGL::GetLongLong(int pname,qint64 * params)
{
  glGetInteger64v ( (GLenum) pname , (GLint64 *) params ) ;
}

void QtGL::AliasedRange(double & minv,double & maxv)
{
  GLdouble v [ 2 ]                                   ;
  ::glGetDoublev ( GL_ALIASED_LINE_WIDTH_RANGE , v ) ;
  minv = v [ 0 ]                                     ;
  maxv = v [ 1 ]                                     ;
}

void QtGL::SmoothRange(double & minv,double & maxv)
{
  GLdouble v [ 2 ]                                  ;
  ::glGetDoublev ( GL_SMOOTH_LINE_WIDTH_RANGE , v ) ;
  minv = v [ 0 ]                                    ;
  maxv = v [ 1 ]                                    ;
}

double QtGL::LineGranularity(void)
{
  GLdouble v                                               ;
  ::glGetDoublev ( GL_SMOOTH_LINE_WIDTH_GRANULARITY , &v ) ;
  return (double) v                                        ;
}

void QtGL::Frustum    (
       double left    ,
       double right   ,
       double bottom  ,
       double top     ,
       double nearVal ,
       double farVal  )
{
  ::glFrustum (
    left      ,
    right     ,
    bottom    ,
    top       ,
    nearVal   ,
    farVal  ) ;
}

void QtGL::Ortho      (
       double left    ,
       double right   ,
       double bottom  ,
       double top     ,
       double nearVal ,
       double farVal  )
{
  ::glOrtho  (
    left     ,
    right    ,
    bottom   ,
    top      ,
    nearVal  ,
    farVal ) ;
}

void QtGL::Projection(int type,double * params)
{
  switch ( type )                {
    case 0                       :
      ::glOrtho                  (
        params [ 0 ]             ,
        params [ 1 ]             ,
        params [ 2 ]             ,
        params [ 3 ]             ,
        params [ 4 ]             ,
        params [ 5 ]           ) ;
    break                        ;
    case 1                       :
      ::glFrustum                (
        params [ 0 ]             ,
        params [ 1 ]             ,
        params [ 2 ]             ,
        params [ 3 ]             ,
        params [ 4 ]             ,
        params [ 5 ]           ) ;
    break                        ;
    case 2                       :
      ::glLoadMatrixd ( params ) ;
    break                        ;
    case 3                       :
      ::glMultMatrixd ( params ) ;
    break                        ;
    case 4                       :
      ::glLoadIdentity (       ) ;
    break                        ;
    case 5                       :
      ::gluPerspective           (
        params [ 0 ]             ,
        params [ 1 ]             ,
        params [ 2 ]             ,
        params [ 3 ]           ) ;
    break                        ;
    case 6                       :
      ::gluLookAt                (
        params [ 0 ]             ,
        params [ 1 ]             ,
        params [ 2 ]             ,
        params [ 3 ]             ,
        params [ 4 ]             ,
        params [ 5 ]             ,
        params [ 6 ]             ,
        params [ 7 ]             ,
        params [ 8 ]           ) ;
    break                        ;
  }                              ;
}

void QtGL::Begin(int mode)
{
  ::glBegin ( (GLenum) mode ) ;
}

void QtGL::LineWidth(double w)
{
  ::glLineWidth ( (GLfloat) w ) ;
}

void QtGL::PointSize(double s)
{
  ::glPointSize ( (GLfloat) s ) ;
}

void QtGL::Points(void)
{
  ::glBegin ( GL_POINTS ) ;
}

void QtGL::Lines(void)
{
  ::glBegin ( GL_LINES ) ;
}

void QtGL::Strips(void)
{
  ::glBegin ( GL_LINE_STRIP ) ;
}

void QtGL::Loop(void)
{
  ::glBegin ( GL_LINE_LOOP ) ;
}

void QtGL::Triangles(void)
{
  ::glBegin ( GL_TRIANGLES ) ;
}

void QtGL::Quadrilateral(void)
{
  ::glBegin ( GL_QUADS ) ;
}

void QtGL::Polygon(void)
{
  ::glBegin ( GL_POLYGON ) ;
}

void QtGL::End(void)
{
  ::glEnd ( ) ;
}

void QtGL::Flush(void)
{
  ::glFlush ( ) ;
}

void QtGL::Enable(int cap)
{
  ::glEnable ( (GLenum) cap ) ;
}

void QtGL::Disable(int cap)
{
  ::glDisable ( (GLenum) cap ) ;
}

void QtGL::Enable(QMap<int,bool> & enablings)
{
  if ( enablings . count ( ) <= 0 ) return ;
  QList<int> K = enablings . keys ( )      ;
  int k                                    ;
  foreach ( k , K )                        {
    bool enable = enablings     [ k ]      ;
    if ( enable ) QtGL::Enable  ( k )      ;
             else QtGL::Disable ( k )      ;
  }                                        ;
}

void QtGL::Clear(int bits)
{
  ::glClear ( (GLbitfield) bits ) ;
}

void QtGL::ShadeModel(int mode)
{
  ::glShadeModel ( (GLenum) mode ) ;
}

void QtGL::BlendFunc(int sfactor,int dfactor)
{
  ::glBlendFunc ( (GLenum) sfactor , (GLenum) dfactor ) ;
}

void QtGL::DepthFunc(int func)
{
  ::glDepthFunc ( (GLenum) func ) ;
}

void QtGL::ClearColor(double r,double g,double b,double a)
{
  ::glClearColor ( r , g , b , a ) ;
}

void QtGL::Viewport (
       int x        ,
       int y        ,
       int width    ,
       int height   )
{
  ::glViewport ( x , y , width , height ) ;
}

void QtGL::Viewport(QRect & area)
{
  ::glViewport          (
    area . left   ( )   ,
    area . top    ( )   ,
    area . width  ( )   ,
    area . height ( ) ) ;
}

void QtGL::Viewport(QRectF & area)
{
  ::glViewport          (
    area . left   ( )   ,
    area . top    ( )   ,
    area . width  ( )   ,
    area . height ( ) ) ;
}

void QtGL::MatrixMode(int mode)
{
  ::glMatrixMode ( (GLenum) mode ) ;
}

void QtGL::LoadIdentity(void)
{
  ::glLoadIdentity ( ) ;
}

void QtGL::Perspective (
       double fovy     ,
       double aspect   ,
       double zNear    ,
       double zFar     )
{
  ::gluPerspective ( fovy , aspect , zNear , zFar ) ;
}

void QtGL::LookAt     (
       double eyeX    ,
       double eyeY    ,
       double eyeZ    ,
       double centerX ,
       double centerY ,
       double centerZ ,
       double upX     ,
       double upY     ,
       double upZ     )
{
  ::gluLookAt (
    eyeX      ,
    eyeY      ,
    eyeZ      ,
    centerX   ,
    centerY   ,
    centerZ   ,
    upX       ,
    upY       ,
    upZ     ) ;
}

void QtGL::PushMatrix(void)
{
  ::glPushMatrix ( ) ;
}

void QtGL::PopMatrix(void)
{
  ::glPopMatrix  ( ) ;
}

void QtGL::LoadMatrixd(void * m)
{
  if ( NULL == m ) return                  ;
  #if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  GLfloat f [ 16 ]                         ;
  for (int i=0;i<16;i++) f [ i ] = m [ i ] ;
  ::glLoadMatrixf ( (GLfloat  *) f )       ;
  #else
  ::glLoadMatrixd ( (GLdouble *) m )       ;
  #endif
}

void QtGL::LoadMatrixf(void * m)
{
  if ( NULL == m ) return           ;
  ::glLoadMatrixf ( (GLfloat *) m ) ;
}

void QtGL::GetMatrixd(int pname,void * m)
{
  if ( NULL == m ) return                    ;
  #if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  GLfloat    f [ 16 ]                        ;
  GLdouble * d = (GLdouble *) m              ;
  QtGL::GetFloat ( pname , f )               ;
  for (int i=0;i<16;i++) d [ i ] = f [ i ]   ;
  #else
  QtGL::GetDouble ( pname , (GLdouble *) m ) ;
  #endif
}

void QtGL::GetMatrixf(int pname,void * m)
{
  if ( NULL == m ) return            ;
  GetFloat ( pname , (GLfloat *) m ) ;
}

void QtGL::MultMatrixd(void * m)
{
  if ( NULL == m ) return                  ;
  #if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  GLfloat f [ 16 ]                         ;
  for (int i=0;i<16;i++) f [ i ] = m [ i ] ;
  ::glMultMatrixf ( (GLfloat  *) f )       ;
  #else
  ::glMultMatrixd ( (GLdouble *) m )       ;
  #endif
}

void QtGL::MultMatrixf(void * m)
{
  if ( NULL == m ) return           ;
  ::glMultMatrixf ( (GLfloat *) m ) ;
}

void QtGL::VertexPointer    (
       int          size    ,
       int          type    ,
       int          stride  ,
       const void * pointer )
{
  ::glVertexPointer ( size , type , stride , pointer ) ;
}

void QtGL::Vertex2f(float x,float y)
{
  ::glVertex2f ( x , y ) ;
}

void QtGL::Vertex2fv(float  * v)
{
  ::glVertex2fv ( v ) ;
}

void QtGL::Vertex3f(float x,float y,float z)
{
  ::glVertex3f ( x , y , z ) ;
}

void QtGL::Vertex3fv(float * v)
{
  ::glVertex3fv ( v ) ;
}

void QtGL::Vertex4f(float x,float y,float z,float w)
{
  ::glVertex4f ( x , y , z , w ) ;
}

void QtGL::Vertex4fv(float * v)
{
  ::glVertex4fv ( v ) ;
}

void QtGL::Vertexfv(int size,float  * v)
{
  switch ( size )         {
    case 2                :
      ::glVertex2fv ( v ) ;
    break                 ;
    case 3                :
      ::glVertex3fv ( v ) ;
    break                 ;
    case 4                :
      ::glVertex4fv ( v ) ;
    break                 ;
  }                       ;
}

void QtGL::Vertex2d(double x,double y)
{
  ::glVertex2d ( x , y ) ;
}

void QtGL::Vertex2dv(double * v)
{
  ::glVertex2dv ( v ) ;
}

void QtGL::Vertex3d(double x,double y,double z)
{
  ::glVertex3d ( x , y , z ) ;
}

void QtGL::Vertex3dv(double * v)
{
  ::glVertex3dv ( v ) ;
}

void QtGL::Vertex4d(double x,double y,double z,double w)
{
  ::glVertex4d ( x , y , z , w ) ;
}

void QtGL::Vertex4dv(double * v)
{
  ::glVertex4dv ( v ) ;
}

void QtGL::Vertexdv(int size,double * v)
{
  switch ( size )         {
    case 2                :
      ::glVertex2dv ( v ) ;
    break                 ;
    case 3                :
      ::glVertex3dv ( v ) ;
    break                 ;
    case 4                :
      ::glVertex4dv ( v ) ;
    break                 ;
  }                       ;
}

void QtGL::Color3f(float r,float g,float b)
{
  ::glColor3f ( r , g , b ) ;
}

void QtGL::Color3fv(float * v)
{
  ::glColor3fv ( v ) ;
}

void QtGL::Color4f(float r,float g,float b,float a)
{
  ::glColor4f ( r , g , b , a ) ;
}

void QtGL::Color4fv(float * v)
{
  ::glColor4fv ( v ) ;
}

void QtGL::Colorfv(int size,float * v)
{
  switch ( size )        {
    case 3               :
      ::glColor3fv ( v ) ;
    break                ;
    case 4               :
      ::glColor4fv ( v ) ;
    break                ;
  }                      ;
}

void QtGL::Color3d(double r,double g,double b)
{
  ::glColor3d ( r , g , b ) ;
}

void QtGL::Color3dv(double * v)
{
  #if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  ::glColor4d  ( v [ 0 ] , v [ 1 ]  , v [ 2 ] , 1.0 ) ;
  #else
  ::glColor3dv ( v                                  ) ;
  #endif
}

void QtGL::Color4d(double r,double g,double b,double a)
{
  ::glColor4d ( r , g , b , a ) ;
}

void QtGL::Color4dv(double * v)
{
  ::glColor4dv ( v ) ;
}

void QtGL::Colordv(int size,double * v)
{
  switch ( size )        {
    case 3               :
      ::glColor3dv ( v ) ;
    break                ;
    case 4               :
      ::glColor4dv ( v ) ;
    break                ;
  }                      ;
}

void QtGL::TexCoord1f(float  s)
{
  ::glTexCoord1f ( s ) ;
}

void QtGL::TexCoord2f(float s,float t)
{
  ::glTexCoord2f ( s , t ) ;
}

void QtGL::TexCoord3f(float s,float t,float r)
{
  ::glTexCoord3f ( s , t , r ) ;
}

void QtGL::TexCoord4f(float s,float t,float r,float q)
{
  ::glTexCoord4f ( s , t , r , q ) ;
}

void QtGL::TexCoord1d(double s)
{
  ::glTexCoord1d ( s ) ;
}

void QtGL::TexCoord2d(double s,double t)
{
  ::glTexCoord2d ( s , t ) ;
}

void QtGL::TexCoord3d(double s,double t,double r)
{
  ::glTexCoord3d ( s , t , r ) ;
}

void QtGL::TexCoord4d(double s,double t,double r,double q)
{
  ::glTexCoord4d ( s , t , r , q ) ;
}

void QtGL::TexCoord1fv(float * v)
{
  ::glTexCoord1fv ( v ) ;
}

void QtGL::TexCoord2fv(float * v)
{
  ::glTexCoord2fv ( v ) ;
}

void QtGL::TexCoord3fv(float * v)
{
  ::glTexCoord3fv ( v ) ;
}

void QtGL::TexCoord4fv(float * v)
{
  ::glTexCoord4fv ( v ) ;
}

void QtGL::TexCoordfv(int size,float * v)
{
  switch ( size )           {
    case 1                  :
      ::glTexCoord1fv ( v ) ;
    break                   ;
    case 2                  :
      ::glTexCoord2fv ( v ) ;
    break                   ;
    case 3                  :
      ::glTexCoord3fv ( v ) ;
    break                   ;
    case 4                  :
      ::glTexCoord4fv ( v ) ;
    break                   ;
  }                         ;
}

void QtGL::TexCoord1dv(double * v)
{
  ::glTexCoord1dv ( v ) ;
}

void QtGL::TexCoord2dv(double * v)
{
  ::glTexCoord2dv ( v ) ;
}

void QtGL::TexCoord3dv(double * v)
{
  ::glTexCoord3dv ( v ) ;
}

void QtGL::TexCoord4dv(double * v)
{
  ::glTexCoord4dv ( v ) ;
}

void QtGL::TexCoorddv(int size,double * v)
{
  switch ( size )           {
    case 1                  :
      ::glTexCoord1dv ( v ) ;
    break                   ;
    case 2                  :
      ::glTexCoord2dv ( v ) ;
    break                   ;
    case 3                  :
      ::glTexCoord3dv ( v ) ;
    break                   ;
    case 4                  :
      ::glTexCoord4dv ( v ) ;
    break                   ;
  }                         ;
}

void QtGL::Scalef(float x,float  y,float  z)
{
  ::glScalef ( x , y , z ) ;
}

void QtGL::Scalefv(float * v)
{
  ::glScalef ( v [ 0 ] , v [ 1 ] , v [ 2 ] ) ;
}

void QtGL::Scaled(double x,double y,double z)
{
  ::glScaled ( x , y , z ) ;
}

void QtGL::Scaledv(double * v)
{
  ::glScaled ( v [ 0 ] , v [ 1 ] , v [ 2 ] ) ;
}

void QtGL::Translatef(float x,float y,float z)
{
  ::glTranslatef ( x , y , z ) ;
}

void QtGL::Translatefv(float * v)
{
  ::glTranslatef ( v [ 0 ] , v [ 1 ] , v [ 2 ] ) ;
}

void QtGL::Translated(double x,double y,double z)
{
  #if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  ::glTranslatef ( x , y , z ) ;
  #else
  ::glTranslated ( x , y , z ) ;
  #endif
}

void QtGL::Translatedv(double * v)
{
  #if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  ::glTranslatef ( v [ 0 ] , v [ 1 ] , v [ 2 ] ) ;
  #else
  ::glTranslated ( v [ 0 ] , v [ 1 ] , v [ 2 ] ) ;
  #endif
}

void QtGL::Rotatef(float r,float x,float y,float z)
{
  ::glRotatef ( r , x , y , z ) ;
}

void QtGL::Rotated(double r,double x,double y,double z)
{
  ::glRotated ( r , x , y , z ) ;
}

void QtGL::ColorMaterial(int face,int mode)
{
  ::glColorMaterial ( (GLenum) face , (GLenum) mode ) ;
}

void QtGL::LightModelf(int pname,float param)
{
  ::glLightModelf ( (GLenum) pname , (GLfloat) param ) ;
}

void QtGL::LightModeli(int pname,int param)
{
  ::glLightModeli ( (GLenum) pname , (GLint) param ) ;
}

void QtGL::Lightf(int light,int pname,float param)
{
  ::glLightf((GLenum)light,(GLenum)pname,(GLfloat)param) ;
}

void QtGL::Lighti(int light,int pname,int param)
{
  ::glLighti((GLenum)light,(GLenum)pname,(GLint)param) ;
}

void QtGL::Lightfv(int light,int pname,const float * params)
{
  ::glLightfv((GLenum)light,(GLenum)pname,(GLfloat *)params) ;
}

void QtGL::Lightiv(int light,int pname,const int * params)
{
  ::glLightiv((GLenum)light,(GLenum)pname,(GLint *)params) ;
}

void QtGL::Materiald(int face,int pname,double param)
{
  ::glMaterialf ( (GLenum) face , (GLenum) pname , (GLfloat) param ) ;
}

void QtGL::Materialf(int face,int pname,float param)
{
  ::glMaterialf ( (GLenum) face , (GLenum) pname , (GLfloat) param ) ;
}

void QtGL::Materiali(int face,int pname,int param)
{
  ::glMateriali ( (GLenum) face , (GLenum) pname , (GLint) param ) ;
}

void QtGL::Materialdv        (
       int            face   ,
       int            pname  ,
       int            items  ,
       const double * params )
{
  if ( items <= 0 ) return                          ;
  GLfloat * fv = new GLfloat [ items ]              ;
  for (int i=0;i<items;i++) fv [ i ] = params [ i ] ;
  ::glMaterialfv ( (GLenum)          face           ,
                   (GLenum)          pname          ,
                   (const GLfloat *) fv           ) ;
  delete [ ] fv                                     ;
}

void QtGL::Materialfv        (
       int            face   ,
       int            pname  ,
       int            items  ,
       const float  * params )
{ Q_UNUSED       ( items                    ) ;
  ::glMaterialfv ( (GLenum)          face     ,
                   (GLenum)          pname    ,
                   (const GLfloat *) params ) ;
}

void QtGL::Materialiv        (
       int            face   ,
       int            pname  ,
       int            items  ,
       const int    * params )
{ Q_UNUSED       ( items                  ) ;
  ::glMaterialiv ( (GLenum)        face     ,
                   (GLenum)        pname    ,
                   (const GLint *) params ) ;
}

void QtGL::Normal3b(unsigned char nx,unsigned char ny,unsigned char nz)
{
  ::glNormal3b ( (GLbyte) nx   ,
                 (GLbyte) ny   ,
                 (GLbyte) nz ) ;
}

void QtGL::Normal3d(double nx,double ny,double nz)
{
  ::glNormal3d ( (GLdouble) nx   ,
                 (GLdouble) ny   ,
                 (GLdouble) nz ) ;
}

void QtGL::Normal3f(float nx,float ny,float nz)
{
  ::glNormal3f ( (GLfloat) nx   ,
                 (GLfloat) ny   ,
                 (GLfloat) nz ) ;
}

void QtGL::Normal3i(int nx,int ny,int nz)
{
  ::glNormal3i ( (GLint) nx   ,
                 (GLint) ny   ,
                 (GLint) nz ) ;
}

void QtGL::Normal3s(short nx,short ny,short nz)
{
  ::glNormal3s ( (GLshort) nx   ,
                 (GLshort) ny   ,
                 (GLshort) nz ) ;
}

void QtGL::Normal3bv(const unsigned char * v)
{
  ::glNormal3bv ( (const GLbyte *) v ) ;
}

void QtGL::Normal3dv(const double * v)
{
  #if defined(Q_OS_ANDROID) || defined(Q_OS_IOS)
  ::glNormal3f  ( v [ 0 ] , v [ 1 ] , v [ 2 ] ) ;
  #else
  ::glNormal3dv ( (const GLdouble *) v        ) ;
  #endif
}

void QtGL::Normal3fv(const float * v)
{
  ::glNormal3fv ( (const GLfloat *) v ) ;
}

void QtGL::Normal3iv(const int * v)
{
  ::glNormal3iv ( (const GLint *) v ) ;
}

void QtGL::Normal3sv(const short * v)
{
  ::glNormal3sv ( (const GLshort *) v ) ;
}

bool QtGL::PixelStorei(int pname,int param)
{
  ::glPixelStorei ( (GLenum) pname , (GLint) param ) ;
  GLenum err = (GLenum) ::glGetError ( )             ;
  return ( GL_NO_ERROR == err )                      ;
}

bool QtGL::PixelStoref(int pname,float param)
{
  ::glPixelStoref ( (GLenum) pname , (GLfloat) param ) ;
  GLenum err = (GLenum) ::glGetError ( )               ;
  return ( GL_NO_ERROR == err )                        ;
}

void QtGL::PixelZoom(float xfactor,float yfactor)
{
  ::glPixelZoom ( (GLfloat) xfactor , (GLfloat) yfactor ) ;
}

void QtGL::PixelZoom(float * factors)
{
  ::glPixelZoom ( (GLfloat) factors [ 0 ] , (GLfloat) factors [ 1 ] ) ;
}

void QtGL::PixelZoom(QSizeF factors)
{
  ::glPixelZoom ( (GLfloat) factors . width  ( )   ,
                  (GLfloat) factors . height ( ) ) ;
}

bool QtGL::BindTexture(int target,unsigned int TID)
{
  ::glBindTexture ( (GLenum) target , (GLuint) TID ) ;
  GLenum err = (GLenum) ::glGetError ( )             ;
  return ( GL_NO_ERROR == err )                      ;
}

bool QtGL::GenTexture(unsigned int & TID)
{
  GLuint TX [ 2 ]                 ;
  GLenum err                      ;
  ::glGenTextures ( 1 , TX )      ;
  TID = TX  [ 0 ]                 ;
  err = (GLenum) ::glGetError ( ) ;
  return ( GL_NO_ERROR == err )   ;
}

bool QtGL::GenTextures(int n,unsigned int * TIDs)
{
  if ( n <= 0       ) return false   ;
  if ( NULL == TIDs ) return false   ;
  GLenum   err                       ;
  GLuint * TX = new GLuint [ n + 1 ] ;
  ::glGenTextures ( n , TX )         ;
  for (int i=0;i<n;i++)              {
    TIDs [ i ] = TX [ i ]            ;
  }                                  ;
  delete [ ] TX                      ;
  err = (GLenum) ::glGetError ( )    ;
  return ( GL_NO_ERROR == err )      ;
}

void QtGL::DeleteTexture(unsigned int id)
{
  GLuint TX [ 2 ]               ;
  TX [ 0 ] = id                 ;
  ::glDeleteTextures ( 1 , TX ) ;
}

void QtGL::DeleteTextures(int s,unsigned int * TIDs)
{
  if ( s <= 0 ) return                   ;
  GLuint * TX = new GLuint [ s + 1 ]     ;
  for (int i = 0 ; i < s ; i++ )         {
    TX [ i ] = TIDs [ i ]                ;
  }                                      ;
  ::glDeleteTextures( (GLsizei) s , TX ) ;
  delete [ ] TX                          ;
}

void QtGL::TexImage2D  (
       int    target   ,
       int    level    ,
       int    internal ,
       int    width    ,
       int    height   ,
       int    border   ,
       int    format   ,
       int    type     ,
       void * data     )
{
  if ( NULL == data ) return  ;
  ::glTexImage2D              (
    (GLenum)         target   ,
    (GLint)          level    ,
    (GLint)          internal ,
    (GLsizei)        width    ,
    (GLsizei)        height   ,
    (GLint)          border   ,
    (GLenum)         format   ,
    (GLenum)         type     ,
    (const GLvoid *) data   ) ;
}

void QtGL::TexImage2D   (
       int     target   ,
       int     level    ,
       int     internal ,
       QSize   s        ,
       int     format   ,
       int     type     ,
       void  * data     )
{
  if ( NULL == data ) return        ;
  ::glTexImage2D                    (
    (GLenum)         target         ,
    (GLint)          level          ,
    (GLint)          internal       ,
    (GLsizei)        s . width  ( ) ,
    (GLsizei)        s . height ( ) ,
    (GLint)          0              ,
    (GLenum)         format         ,
    (GLenum)         type           ,
    (const GLvoid *) data         ) ;
}

bool QtGL::TexEnvf  (
       int   target ,
       int   pname  ,
       float param  )
{
  ::glTexEnvf ( (GLenum) target , (GLenum) pname , (GLfloat) param ) ;
  GLenum err = (GLenum) ::glGetError ( )                             ;
  return ( GL_NO_ERROR == err )                                      ;
}

bool QtGL::TexEnvi (
       int target  ,
       int pname   ,
       int param   )
{
  ::glTexEnvi ( (GLenum) target , (GLenum) pname , (GLint) param ) ;
  GLenum err = (GLenum) ::glGetError ( )                           ;
  return ( GL_NO_ERROR == err )                                    ;
}

bool QtGL::TexEnvm(int target,QMap<int,double> & p)
{
  QList<int> K = p . keys ( )                ;
  int        k                               ;
  GLenum     err                             ;
  ////////////////////////////////////////////
  foreach ( k , K )                          {
    ::glTexEnvf                              (
      (GLenum)  target                       ,
      (GLenum)  k                            ,
      (GLfloat) p [ k ]                    ) ;
      err = (GLenum) ::glGetError ( )        ;
      if ( GL_NO_ERROR != err ) return false ;
  }                                          ;
  ////////////////////////////////////////////
  return true                                ;
}

bool QtGL::TexParameterf (
       int   target      ,
       int   pname       ,
       float param       )
{
  ::glTexParameterf ( (GLenum) target , (GLenum) pname , (GLfloat) param ) ;
  GLenum err = (GLenum) ::glGetError ( )                                   ;
  return ( GL_NO_ERROR == err )                                            ;
}

bool QtGL::TexParameteri (
       int target        ,
       int pname         ,
       int param         )
{
  ::glTexParameteri ( (GLenum) target , (GLenum) pname , (GLint) param ) ;
  GLenum err = (GLenum) ::glGetError ( )                                 ;
  return ( GL_NO_ERROR == err )                                          ;
}

bool QtGL::TexParameterm (int target,QMap<int,double> & p)
{
  QList<int> K = p . keys ( )                ;
  int        k                               ;
  GLenum     err                             ;
  ////////////////////////////////////////////
  foreach ( k , K )                          {
    ::glTexParameterf                        (
      (GLenum)  target                       ,
      (GLenum)  k                            ,
      (GLfloat) p [ k ]                    ) ;
      err = (GLenum) ::glGetError ( )        ;
      if ( GL_NO_ERROR != err ) return false ;
  }                                          ;
  ////////////////////////////////////////////
  return true                                ;
}

void QtGL::RasterPos2i(int x,int y)
{
  ::glRasterPos2i ( x , y ) ;
}

void QtGL::RasterPos3i (
       int x           ,
       int y           ,
       int z           )
{
  ::glRasterPos3i ( x , y , z ) ;
}

void QtGL::RasterPos4i (
       int x           ,
       int y           ,
       int z           ,
       int w           )
{
  ::glRasterPos4i ( x , y , z , w ) ;
}

void QtGL::RasterPos2f(float x,float y)
{
  ::glRasterPos2f ( x , y ) ;
}

void QtGL::RasterPos3f (
       float x         ,
       float y         ,
       float z         )
{
  ::glRasterPos3f ( x , y , z ) ;
}

void QtGL::RasterPos4f (
       float x         ,
       float y         ,
       float z         ,
       float w         )
{
  ::glRasterPos4f ( x , y , z , w ) ;
}

void QtGL::RasterPos2d(double x,double y)
{
  ::glRasterPos2d ( x , y ) ;
}

void QtGL::RasterPos3d (
       double x        ,
       double y        ,
       double z        )
{
  ::glRasterPos3d ( x , y , z ) ;
}

void QtGL::RasterPos4d (
       double x        ,
       double y        ,
       double z        ,
       double w        )
{
  ::glRasterPos4d ( x , y , z , w ) ;
}

void QtGL::DrawPixels (
       int    width   ,
       int    height  ,
       int    format  ,
       int    type    ,
       void * pixels  )
{
  ::glDrawPixels              (
    (GLsizei)        width    ,
    (GLsizei)        height   ,
    (GLenum)         format   ,
    (GLenum)         type     ,
    (const GLvoid *) pixels ) ;
}

void QtGL::DrawPixels (
       QSize  s       ,
       int    format  ,
       int    type    ,
       void * pixels  )
{
  ::glDrawPixels                    (
    (GLsizei)        s . width  ( ) ,
    (GLsizei)        s . height ( ) ,
    (GLenum)         format         ,
    (GLenum)         type           ,
    (const GLvoid *) pixels       ) ;
}

void QtGL::Map1f      (
       int     target ,
       float   u1     ,
       float   u2     ,
       int     stride ,
       int     order  ,
       void  * points )
{
  ::glMap1f                    (
    (GLenum)          target   ,
    (GLfloat)         u1       ,
    (GLfloat)         u2       ,
    (GLint)           stride   ,
    (GLint)           order    ,
    (const GLfloat *) points ) ;
}

void QtGL::Map1d      (
       int     target ,
       double  u1     ,
       double  u2     ,
       int     stride ,
       int     order  ,
       void  * points )
{
  ::glMap1d                     (
    (GLenum)           target   ,
    (GLdouble)         u1       ,
    (GLdouble)         u2       ,
    (GLint)            stride   ,
    (GLint)            order    ,
    (const GLdouble *) points ) ;
}

void QtGL::Map2f      (
       int    target  ,
       float  u1      ,
       float  u2      ,
       int    ustride ,
       int    uorder  ,
       float  v1      ,
       float  v2      ,
       int    vstride ,
       int    vorder  ,
       void * points  )
{
  ::glMap2f                    (
    (GLenum)          target   ,
    (GLfloat)         u1       ,
    (GLfloat)         u2       ,
    (GLint)           ustride  ,
    (GLint)           uorder   ,
    (GLfloat)         v1       ,
    (GLfloat)         v2       ,
    (GLint)           vstride  ,
    (GLint)           vorder   ,
    (const GLfloat *) points ) ;
}

void QtGL::Map2d      (
       int    target  ,
       double u1      ,
       double u2      ,
       int    ustride ,
       int    uorder  ,
       double v1      ,
       double v2      ,
       int    vstride ,
       int    vorder  ,
       void * points  )
{
  ::glMap2d                     (
    (GLenum)           target   ,
    (GLdouble)         u1       ,
    (GLdouble)         u2       ,
    (GLint)            ustride  ,
    (GLint)            uorder   ,
    (GLdouble)         v1       ,
    (GLdouble)         v2       ,
    (GLint)            vstride  ,
    (GLint)            vorder   ,
    (const GLdouble *) points ) ;
}

void QtGL::MapGrid1d     (
       int    partitions ,
       double u1         ,
       double u2         )
{
  ::glMapGrid1d ( (GLint) partitions , (GLdouble) u1 , (GLdouble) u2 ) ;
}

void QtGL::MapGrid1f     (
       int    partitions ,
       float  u1         ,
       float  u2         )
{
  ::glMapGrid1f ( (GLint) partitions , (GLfloat) u1 , (GLfloat) u2 ) ;
}

void QtGL::MapGrid2d (
       int    un     ,
       double u1     ,
       double u2     ,
       int    vn     ,
       double v1     ,
       double v2     )
{
  ::glMapGrid2d ( (GLint) un , (GLdouble) u1 , (GLdouble) u2   ,
                  (GLint) vn , (GLdouble) v1 , (GLdouble) v2 ) ;
}

void QtGL::MapGrid2f (
       int   un      ,
       float u1      ,
       float u2      ,
       int   vn      ,
       float v1      ,
       float v2      )
{
  ::glMapGrid2f ( (GLint) un , (GLfloat) u1 , (GLfloat) u2   ,
                  (GLint) vn , (GLfloat) v1 , (GLfloat) v2 ) ;
}

void QtGL::EvalMesh1 (
       int mode      ,
       int i1        ,
       int i2        )
{
  ::glEvalMesh1 ( (GLenum) mode ,
                  (GLint) i1 ,
                  (GLint) i2 ) ;
}

void QtGL::EvalMesh2 (
       int mode      ,
       int i1        ,
       int i2        ,
       int j1        ,
       int j2        )
{
  ::glEvalMesh2 ( (GLenum) mode ,
                  (GLint)  i1   ,
                  (GLint)  i2   ,
                  (GLint)  j1   ,
                  (GLint)  j2 ) ;
}

void QtGL::EvalCoord1d(double u)
{
  ::glEvalCoord1d ( (GLdouble) u ) ;
}

void QtGL::EvalCoord1f(float u)
{
  ::glEvalCoord1f ( (GLfloat) u ) ;
}

void QtGL::EvalCoord2d(double u,double v)
{
  ::glEvalCoord2d ( (GLdouble) u , (GLdouble) v ) ;
}

void QtGL::EvalCoord2f(float u,float v)
{
  ::glEvalCoord2f ( (GLfloat) u , (GLfloat) v ) ;
}

void QtGL::Hint(int target,int mode)
{
  ::glHint ( (GLenum) target , (GLenum) mode ) ;
}

bool QtGL::IsGLEW(QString name)
{
  if ( name . length ( ) <= 0 ) return false          ;
  QByteArray B = name . toUtf8 ( )                    ;
  return (bool) glewIsSupported ( B . constData ( ) ) ;
}

bool QtGL::IsExtension(QString name)
{
  if ( name . length ( ) <= 0 ) return false           ;
  QByteArray B = name . toUtf8 ( )                     ;
  return (bool) glewGetExtension ( B . constData ( ) ) ;
}
