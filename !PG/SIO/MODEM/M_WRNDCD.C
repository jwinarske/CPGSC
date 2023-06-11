/*-

FUNCTION NAME:  m_warndcd
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Issues a warning and overrides the prompt if the current DCD
                state does not match the argument.
      RETURNS:  int: M_SUCCEED if DCD state is OK, if the user
                elects to ignore the DCD state;otherwise
                M_FAIL.
     COMMENTS:

*/

#include <stdio.h>
#include <sio\siodef.h>
#include <sio\modem.h>
#include <sio\misc.h>
#include <sio\key.h>
#include <ctype.h>


short m_warndcd(SIO *siop, BOOL warnmode)
{
     int  c = -1;
     char *warnp;
     if (siop->sm == NIL) /* modem structure not present */
          return M_SUCCEED;
     warnp = (warnmode) ? "no" : "a";
     if  ( (BOOL)stat232(siop, DCD) != warnmode)
          {
          for (EVER)
               {
               printf("\nTests indicate %s carrier present. OK to ignore?\a (Y/N):", warnp) ;
               c = getkbch();
               c = toupper(c);
               putchar('\n');
               if (c == 'N')
                    return M_FAIL;
               if (c == 'Y')
                    return M_SUCCEED;
               }
          }
     return M_SUCCEED;
}
