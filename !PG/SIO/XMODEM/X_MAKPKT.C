/*-
FUNCTION NAME:  makepacket
        LEVEL:  3
 PROTOTYPE IN:  XMOD.H
      LIBRARY:  XMODEM.LIB
  DESCRIPTION:  Makes sndpackets in buffer. Checkvalue character is
                not installed.
      RETURNS:  USHORT: the number of packets made.
     COMMENTS:  The checkvalues cannot be installed until after start-up.
*/

#include <stdio.h>                        /* Needed by modem.h                 */
#include <sio\ascii.h>
#include <sio\siodef.h>
#include <sio\xmod.h>

 /*1: "packet buffer pointer"      */
 /*2:  number of  packets in buffer */
 /*3:  current packet count         */

USHORT makepacket(struct sndpacket *pbp, USHORT pakcnt, ULONG paknum, FILE  *fp)
{
     USHORT  paksread = 0;                  /* first read in data from disk */
     while (fread(pbp->data, sizeof(BYTE), sizeof(pbp->data), fp) != 0)
          {
          pbp->soh   = SOH;                  /* install SOH                  */
          pbp->pnum1 = (BYTE)(paknum++ & 0x00FF); /* install packet number and ...*/
          pbp->pnum2 = (BYTE)(~(pbp->pnum1));     /* its one's complement         */
          if (++paksread == pakcnt)
               break;
          ++pbp;                             /* next packet, please          */
          }
     return paksread;
}
