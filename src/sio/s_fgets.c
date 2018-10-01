/*-
FUNCTION NAME:  s_fgets
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Inputs a NUL-terminated string of numc uint8_ts into
                buffer.
      RETURNS:  int: number of uint8_ts in buffer (0 if timeout occured).
     COMMENTS:  Buffer must be numc+1 uint8_ts long to accommodate the NUL
                terminator.  Timeout mode is forced for the duration of the
                function.

*/

#include <sio/siodef.h>
#include <sio/sioctl.h>
#include <sio/buos.h>


int s_fgets(SIO *siop, char *buff, int numc)
{
     int count;
     int c;

//     s_icntrl(siop, SET, T_OUTFLAG, ON);    /* turn on input timeout         */
//     if (s_icntrl(siop, GET, T_OUT) == 0)   /* save timeout interval         */
//          s_icntrl(siop, SET, T_OUT, 9);    /* make sure there is some delay */
     count = 0;
     while (count < numc)
          {
          if ( (c = s_fgetc(siop)) == TIMEOUT)
               return count;
          if (c == IGNORE)                   /* exclude this character       */
               continue;
          *buff++ =  (char)c;                /* install uint8_t in buffer       */
          ++count;
          }

     if ( (c =  s_iflush(siop)) != -1)       /* uint8_t pending in s_fgetc?     */
          {
          *buff++ = (char)c;
          ++count;
          }
     *buff = NUL;                            /* terminate buffer with NUL    */
     return count;
}
