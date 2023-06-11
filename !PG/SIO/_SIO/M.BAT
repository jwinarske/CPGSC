nmake sio.nmk
if errorlevel 1 goto end
ncd progs
nmake progs.nmk
:end
