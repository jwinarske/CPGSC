/*-
 PROGRAM NAME:  CRC.C
  DESCRIPTION:  Calculates both CRCCCITT and CRC-16 on specified file.
       SYNTAX:  CRCS FILENAME
*/

#include <stdio.h>
#include <stdlib.h>
#include <sio\siodef.h>
#include <sio\crc.h>


main(int argc, char *argv[])
{
     FILE *fp;
     USHORT *tablep, accum;
     USHORT *table16p, accum16;
     int c;
     if (argc < 2)
          exit(puts("Need filename."));
     if ( (fp = fopen(argv[1], "rb")) == NIL)
          exit(printf("Cannot open %s.", argv[1]));
     if ( (tablep = mk_crctbl(CRCCCITT, crchware)) == NIL)
          exit(puts("No space for CCITT table."));
     if ( (table16p = mk_crctbl(CRC16_REV, crcrevhware)) == NIL)
          exit(puts("No space for CRC-16 table."));
     accum = accum16 = 0;                  /* clear both CRC accumulators */
     while ( (c = getc(fp)) != EOF)
          {
          crcupdate(c, &accum, tablep);
          crcrevupdate(c, &accum16, table16p);
          }
     printf("CCITT for %s  = %4.4X\n",argv[1], accum);
     accum16 = (accum16 >> 8) + (accum16 << 8);       /* byte-swap CRC-16 */
     printf("CRC-16 for %s = %4.4X\n ",argv[1], accum16);
     free((VOID*)tablep);
     free((VOID*)table16p);
     return 0;
}
