#ifndef   _KEY_
#define  _KEY_

#include <sio/siolocal.h>
#if !defined(__GNUC__)
#include <conio.h>
#endif

/**** FUNCTION PROTOTYPES ****/
FAST getkbch(void);
FAST inkey(void);

#if defined(__WIN32)
#define keystat kbhit          /* For Microsoft's run-time*/
#define getkey  getch          /* For Microsoft's run-time*/
#else
#endif
#define NOT_READY -1
#define NO_KEY    0

#endif /* _KEY_    */

