nmake fax.nmk
goto end
cl run2t4.c /c
cl t4encode.c /c
if errorlevel 1 goto end
link run2t4 t4encode,,,fax.lib /CO;
run2t4
xir /c t4_1d.a4
:end