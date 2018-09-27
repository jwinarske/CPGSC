/*-44
    PROGRAM:  BMAP2RUN
DESCRIPTION:  Converts 216-uint8_ts per line bitmap to runlength file.
   COMMENTS: Input  file is BITMAP0.A4: 746,496  CRC = 7160
             Output file is RUNLEN0.A4:  31,096  CRC = 26D0
*/

#include <stdio.h>
#include <stdlib.h>
#include <sio/siolocal.h>
#include <sio/t4.h>

int main(void)
{
     char   *infilename =  "BITMAP0.A4";
     char   *outfilename = "RUNLEN0.A4";
     FILE   *outfilep, *infilep;
     uint8_t   *bitbuffp;                  /* buffer for bits             */
     uint16_t *runbuffp;                  /* buffer for run lengths      */
     uint16_t count, lines, uint8_tS_PER_LINE;

     if ( (bitbuffp = (uint8_t*) malloc(BYTES_PER_LINE)) == NIL)
        exit(puts("Error allocating bit buffer."));
     if ( (runbuffp = (uint16_t *) malloc(BYTES_PER_LINE * 8)) == NIL)
        exit(puts("Error allocating run-length buffer."));

     if ( (infilep = fopen(infilename, "rb")) == NIL)
     	exit(printf("Error opening %s\n", infilename));
     if ( (outfilep = fopen(outfilename, "wb")) == NIL)
     	exit(printf("Error opening %s\n", outfilename));

     printf("Input file = %s  Output file = %s \n", infilename, outfilename);

/* Read bits, make run lengths, write run lengths */
     BYTES_PER_LINE = BYTES_PER_LINE;
     for(lines = 1; count = BYTES_PER_LINE; lines++)
          {
          if (!fread(bitbuffp, sizeof(uint8_t), BYTES_PER_LINE, infilep))
               {
               if (ferror(infilep))
     	          printf("Error reading %s\n", infilename);
     	       break;
     	       }
          count = bit2run(bitbuffp, count, runbuffp);      /* encode   */
          if (!fwrite(runbuffp, sizeof(short), count, outfilep))
               {
     	       printf("Error writing %s\n", outfilename);
     	       break;
     	       }
          printf("Writing line: %d\r",lines);
          }
     free(bitbuffp);                                       /* clean up */
     free(runbuffp);
     fclose(infilep);
     fclose(outfilep);

     return 0;
}
