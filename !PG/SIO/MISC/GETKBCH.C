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

#include <sio\key.h>

FAST getkbch()                             /* fetch keyboard char, no echo      */
{
     while (keystat() == NO_KEY)      /* while no character is ready....   */
          ;                                      /* ... wait ...                      */
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
     return ( (keystat() == NO_KEY) ? NOT_READY : getkey() );
//     return ( (kbhit()== NO_KEY) ? NOT_READY : getch() );
}
