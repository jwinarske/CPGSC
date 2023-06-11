#ifndef   _KEY_
#define  _KEY_

#include <sio\siolocal.h>
#include <conio.h>

/**** FUNCTION PROTOTYPES ****/
FAST getkbch(void);
FAST inkey(void);

#define keystat kbhit          /* For Microsoft's run-time*/
#define getkey  getch          /* For Microsoft's run-time*/
#define NOT_READY -1
#define NO_KEY    0

#endif /* _KEY_    */
