/*-

FUNCTION NAME:  ckvinstall
        LEVEL:  3
 PROTOTYPE IN:  XMOD.H
      LIBRARY:  XMODEM.LIB
  DESCRIPTION:  Install checkvalue(s) in the array of packet structures.
      RETURNS:  void
     COMMENTS:  numpaks is the cardinal size of the packet array.  It
                is the responsibility of the error-checking
                function to return the checkvalue in the correct byte-order
                for storage in the sndpacket structure.
*/

#include <stdio.h>                      /* Needed by modem.h                 */
#include <sio\siodef.h>
#include <sio\xmod.h>

/*1: "packet buffer pointer"            */
/*2: number of packets in buffer        */
/*3: pointer to error-checking function */

void ckvinstall
        (struct sndpacket *pbp,
     USHORT numpaks,
     USHORT (*ckvfn)(BYTE*)
        )
{
     for (; numpaks > 0; --numpaks, ++pbp)
          pbp->ckval = (*ckvfn)(pbp->data);
}
