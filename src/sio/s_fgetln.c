
/*-
FUNCTION NAME:  s_fgetln
        LEVEL:  2
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Converts a carriage-return-delimited string into a
                NUL-terminataed string of uint8_ts.  Leading and trailing
                carriage returns are removed.
      RETURNS:  int: number of uint8_ts in the buffer (0 if timeout occurs).
     COMMENTS:  Buffer must be numc+1 uint8_ts long to accommodate the NUL
                terminator.  The calling function is responsible for calling
                s_iocntrl to enable and set the timeout interval.
*/

enum {LEADING_CR = 0, LEADING_LF, IN_MSG, TRAILING_CR, TRAILING_LF, EXIT};

#include <sio/siodef.h>
#include <sio/sioctl.h>
#include <sio/buos.h>
#include <sio/ascii.h>

int s_fgetln(SIO *siop, char *buff, short numc)
{
     int c;
     int  count;
     int state = LEADING_CR;
     count = 0;
     while (state != EXIT && count < numc)
          {
          c = s_fgetc(siop);
               {
               if (c == TIMEOUT)
                    {
                    count = TIMEOUT;
                    state = EXIT;
                    }
               }
          switch (state)
               {
               case LEADING_CR:
                    if (c == CR)
                         state = LEADING_LF;
                    break;
               case LEADING_LF:
                    if (c == LF)
                         state = IN_MSG;
                    break;
               case IN_MSG:
                    if (c == CR)
                         state = TRAILING_LF;
                    else
                         {
                         count++;
                         *buff++ = (char)c;
                         }
                    break;
               case TRAILING_LF:
                    if (c == LF)
                         state = EXIT;
                    break;
               } /* end of switch */
          }    /* end of while */

     if ( (c = s_iflush(siop)) != -1)        /* uint8_t pending in s_fgetc?     */
          {
          *buff++ = (char)c;
          ++count;
          }
     *buff = NUL;
     return count;
}
