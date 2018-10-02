/*-

FUNCTION NAME:  str_atoi
        LEVEL:  3
 PROTOTYPE IN:  MISC.H
      LIBRARY:  MISC.LIB
  DESCRIPTION:  Scans a string looking for a numeral, then calls atoi.
      RETURNS:  int: the integer or -1 if the string contains no numerals.
*/

#include <stdlib.h>
#include <ctype.h>
#include "sio/siodef.h"

int str_atoi(char *buffp)
{
     if ( buffp!= 0)
          for (; *buffp != NUL; buffp++)
               if (isdigit(*buffp) && isdigit(*(buffp+1)) )
                    return (atoi(buffp));
     return -1;
}
