var PrivateRelease = "http://www.privatereleases.com/assets/covers/front/SPE118f.jpg" ;
var temp           = "E:/Temp/Private"                ;

function Private()
{
  var html                                                  ;
  var uuid                                                  ;
  js  = new MtJS      (                                   ) ;
  ftp = new FTP       (                                   ) ;
  dir = new Directory (                                   ) ;
  ba  = new ByteArray (                                   ) ;
  mag = new Managers  (                                   ) ;
  dir . SetCurrent    ( temp                              ) ;
  dir . SetPath       ( temp                              ) ;
  dir . Mkpath        ( temp                              ) ;
  html = dir . AbsoluteFilePath ( "SPE118f.jpg" )           ;
  ///////////////////////////////////////////////////////////
  if ( ftp . Download ( PrivateRelease , html , 30*1000 ) ) {
    uuid = mag . ImportPicture ( html                     ) ;
    js . toConsoleLn           ( uuid                     ) ;
//    js . toConsoleLn  ( ftp . HttpHeader ( )              ) ;
//    ba . Load         ( html                              ) ;
//    js . toConsoleLn  ( ba  . toString   ( )              ) ;
//    ba . Clear        (                                   ) ;
  }                                                         ;
  ///////////////////////////////////////////////////////////
  delete ba                                                 ;
  delete dir                                                ;
  delete ftp                                                ;
  delete js                                                 ;
}
