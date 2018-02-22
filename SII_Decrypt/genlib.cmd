@echo off

call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86

rem 64-bit version is easy
lib.exe /def:SII_Decrypt.def /name:SII_Decrypt_64.dll /machine:x64 /out:SII_Decrypt_64.lib

rem 32-bit version is more complicated...
cl.exe /c /Ob0 SII_Decrypt.cpp
lib.exe /def:SII_Decrypt.def SII_Decrypt.obj /name:SII_Decrypt_32.dll /out:SII_Decrypt_32.lib
del /q *.exp *.obj
