if exist \!pg\trapdoor.bat goto bozo
#rem erase all objs, nmake all files.

rem REMOVE THESE REMS IF YOU WANT TO CHANGE THE ASSEMBLER
rem cd \!pg\sio\asm
rem del objs\*.obj
rem del *.lib
rem nmake asm.nmk
rem if errorlevel 1 goto end

cd \!pg\sio\buos       
del objs\*.obj
del *.lib
nmake buos.nmk
if errorlevel 1 goto end

cd \!pg\sio\crc        
del objs\*.obj
del *.lib
nmake crc.nmk
if errorlevel 1 goto end

cd \!pg\sio\fax        
del objs\*.obj
del *.lib
nmake fax.nmk
if errorlevel 1 goto end

cd \!pg\sio\ibmpc
del objs\*.obj
del *.lib
nmake ibmpc.nmk
if errorlevel 1 goto end

cd \!pg\sio\misc
del objs\*.obj
del *.lib
nmake misc.nmk
if errorlevel 1 goto end

cd \!pg\sio\modem      
del objs\*.obj
del *.lib
nmake modem.nmk               
if errorlevel 1 goto end

cd \!pg\sio\u16x50      
del objs\*.obj
del *.lib
nmake u16x50.nmk               
if errorlevel 1 goto end

cd \!pg\sio\xmodem
del objs\*.obj
del *.lib
nmake xmodem.nmk
if errorlevel 1 goto end

cd \!pg\sio\_sio
del objs\*.obj
del *.lib
nmake sio.nmk
if errorlevel 1 goto end

cd \!pg\sio\termfunc
del objs\*.obj
del *.lib
nmake termfunc.nmk
if errorlevel 1 goto end

cd \!pg\sio\progs
del objs\*.obj
del *.lib
nmake progs.nmk
if errorlevel 1 goto end

goto ok

:bozo
ECHO OFF
CLS
ECHO If You Can Read This You Haven't Read Your Instruction Sheet
:end
:ok
