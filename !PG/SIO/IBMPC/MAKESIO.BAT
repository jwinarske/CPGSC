
copy COM3SIO.C COM1SIO.C
copy template.rpl A_sio.rpl
repl A_.rpl A_sio.rpl
rem wsp A_sio.rpl
repl A_sio.rpl COM1SIO.C 


copy COM3SIO.C COM2sio.c
copy template.rpl B_sio.rpl
repl B_.rpl B_sio.rpl
repl B_sio.rpl COM2SIO.C


copy COM3SIO.C COM4SIO.c
copy template.rpl D_sio.rpl
repl D_.rpl D_sio.rpl
repl D_sio.rpl COM4SIO.C
