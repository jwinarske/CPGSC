/*-

FUNCTION NAME:  s_keybort
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Checks the keyboard to see if the designated abort
                key has been typed.
      RETURNS:  BOOL:  TRUE if the abort key was pressed otherwise FALSE.
     COMMENTS:  The abort key is defined by the kbortc member of the
                soctl_ structure.  This function can be replaced with the
                following macro:

                #define s_keybort(p) inkey() == (p)->s_octl->kbortc
*/

#include <sio\siodef.h>
#include <sio\key.h>


BOOL s_keybort(SIO *siop)
{
     return (BOOL) (inkey() == (int)siop->s_octl->kbortc);
}
