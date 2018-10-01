#ifndef   _KEY_
#define  _KEY_

#include <sio/siolocal.h>
#ifndef __GNUC__
#include <conio.h>
#endif

/**** FUNCTION PROTOTYPES ****/
FAST getkbch(void);
FAST inkey(void);

#define keystat _kbhit
#define getkey  _getch

#define NOT_READY -1
#define NO_KEY    0

#endif /* _KEY_    */

