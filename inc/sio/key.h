#ifndef   _KEY_
#define  _KEY_

#include "sio/siolocal.h"
#ifndef __GNUC__
#include <conio.h>
#endif

#ifdef _WIN32
#define keystat _kbhit
#define getkey  _getch
#endif
#define NOT_READY -1
#define NO_KEY    0

/**** FUNCTION PROTOTYPES ****/
FAST getkbch(void);
FAST inkey(void);

#endif /* _KEY_    */
