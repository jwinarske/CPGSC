/*-

FUNCTION NAME:  getkbch
 PROTOTYPE IN:  KEY.H
        LEVEL:  3
      LIBRARY:  MISC.H
  DESCRIPTION:   Waits until a key is pressed, then return it without echo.
      RETURNS:  int, which allows for modification to detect "special"
                keys.
     COMMENTS:  This should be a "raw" function with no character
                processing.  
*/

#include "sio/key.h"

#if defined(__GNUC__)

#include <stdio.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

int keystat (void)
{
    static const int STDIN = 0;
    static bool initialized = false;

    if (! initialized) {
        // Use termios to turn off line buffering
        struct termios term;
        tcgetattr(STDIN, &term);
        term.c_lflag &= ~ICANON;
        tcsetattr(STDIN, TCSANOW, &term);
        setbuf(stdin, NULL);
        initialized = true;
    }

    int bytesWaiting;
    ioctl(STDIN, FIONREAD, &bytesWaiting);
    return bytesWaiting;
}

char getkey()
{
    char buf = 0;
    struct termios old = { 0 };

    fflush(stdout);

    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");

    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;

    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");

    if(read(0,&buf,1)<0)
        perror("read()");

    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;

    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");

    return buf;
 }
#endif

FAST getkbch()                       /* fetch keyboard char, no echo      */
{
    while (keystat() == NO_KEY)     /* while no character is ready....   */
          ;                          /* ... wait ...                      */
    return (getkey());              /* then return it when ready         */
}

/*

Figure AA-1b

FUNCTION NAME:  inkey
 PROTOTYPE IN:  MISC.H
        LEVEL:  3
      LIBRARY:  MISC.LIB
  DESCRIPTION:  Returns a keyboard character if available, otherwise -1.
      RETURNS:  int: -1 if no character ready.
     COMMENTS:  This should be a "raw" function with no character
                processing.
*/

FAST inkey(void)
{
    return ( (keystat() == NO_KEY) ? NOT_READY : getkey() );  /*//*/
//     return ( (kbhit()== NO_KEY) ? NOT_READY : getch() );
}
