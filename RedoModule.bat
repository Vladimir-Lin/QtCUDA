set MODNAME=QtCUDA
nmake distclean
rd  /s /q lib
rd  /s /q mkspecs
cd src/%MODNAME%
rd  /s /q .moc
rd  /s /q .obj
rd  /s /q .pch
del /s /q *_resource.rc
del /s /q vc120.*
cd ../../
