if exist \!pg\trapdoor.bat goto bozo
#rem make all files in all directories.

rem REMOVE THESE REMS IF YOU WANT TO CHANGE THE ASSEMBLER
rem cd \!pg\sio\asm
rem nmake asm.nmk
rem if errorlevel 1 goto end

cd \!pg\sio\buos       
nmake buos.nmk
if errorlevel 1 goto end

cd \!pg\sio\crc        
nmake crc.nmk
if errorlevel 1 goto end

cd \!pg\sio\fax        
nmake fax.nmk
if errorlevel 1 goto end

cd \!pg\sio\ibmpc
nmake ibmpc.nmk
if errorlevel 1 goto end

cd \!pg\sio\misc
nmake misc.nmk
if errorlevel 1 goto end

cd \!pg\sio\modem      
nmake modem.nmk               
if errorlevel 1 goto end

cd \!pg\sio\termfunc
nmake termfunc.nmk
if errorlevel 1 goto end

cd \!pg\sio\u16x50      
nmake u16x50.nmk               
if errorlevel 1 goto end

cd \!pg\sio\_sio
nmake sio.nmk
if errorlevel 1 goto end

cd \!pg\sio\xmodem
nmake xmodem.nmk
if errorlevel 1 goto end

cd \!pg\sio\progs
nmake progs.nmk
if errorlevel 1 goto end

goto ok

:bozo
ECHO OFF
CLS
ECHO If You Can Read This, You Haven't Read Your Instruction Sheet Completely
:end
:ok
