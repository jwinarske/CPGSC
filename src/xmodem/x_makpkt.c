/*-
FUNCTION NAME:  makepacket
        LEVEL:  3
 PROTOTYPE IN:  XMOD.H
      LIBRARY:  XMODEM.LIB
  DESCRIPTION:  Makes sndpackets in buffer. Checkvalue character is
                not installed.
      RETURNS:  uint16_t: the number of packets made.
     COMMENTS:  The checkvalues cannot be installed until after start-up.
*/

#include <stdio.h>                        /* Needed by modem.h                 */
#include <sio/ascii.h>
#include <sio/siodef.h>
#include <sio/xmod.h>

 /*1: "packet buffer pointer"      */
 /*2:  number of  packets in buffer */
 /*3:  current packet count         */

uint16_t makepacket(struct sndpacket *pbp, uint16_t pakcnt, ULONG paknum, FILE  *fp)
{
     uint16_t  paksread = 0;                  /* first read in data from disk */
     while (fread(pbp->data, sizeof(uint8_t), sizeof(pbp->data), fp) != 0)
          {
          pbp->soh   = SOH;                  /* install SOH                  */
          pbp->pnum1 = (uint8_t)(paknum++ & 0x00FF); /* install packet number and ...*/
          pbp->pnum2 = (uint8_t)(~(pbp->pnum1));     /* its one's complement         */
          if (++paksread == pakcnt)
               break;
          ++pbp;                             /* next packet, please          */
          }
     return paksread;
}
