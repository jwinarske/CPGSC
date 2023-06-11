/*
PROGRAM NAME: RUN2T4
 DESCRIPTION: Reads runlength file, outputs 1-D T.4 file.
    COMMENTS:  Input file RUNLEN0.A4: 31,096 bytes CRC = 26D0.
              Output file   T4_1D.A4: 26,486 bytes CRC = 07BC.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sio\siolocal.h>
#include <sio\t4.h>

#define RUNBUFFSIZE  2048
#define T4BUFFSIZE   RUNBUFFSIZE

void main(void)
{
     char  *infilename  = "RUNLEN0.A4";  /* File of un-lengths           */
     char  *outfilename = "T4_1D.A4";    /* File of 1-D T4 codes         */
     FILE  *outfilep, *infilep;
     FAST  *runbuff;                     /* Input buffer for run lengths */
     FAST  *t4buff;                      /* Output buffer for T.4 codes  */
     USHORT num_t4codes;                 /* Number of T4 codes in buffer */
     USHORT rl_read;                     /* Run lengths read from disk   */
     USHORT t4_written;                  /* Number of T4 codes in written*/
     USHORT read_total, write_total;     /* Statistics                   */

     if ((t4buff  = (FAST*) malloc(T4BUFFSIZE * sizeof(FAST))) == NIL)
         exit(puts("Error allocating T.4 buffer."));
     if ( (runbuff = (FAST *) malloc(RUNBUFFSIZE * sizeof(FAST))) == NIL)
         exit(puts("Error allocating run-length buffer."));

     if ( (infilep = fopen(infilename, "rb")) == NIL)
          exit(printf("Error opening %s\n", infilename));
     if ( (outfilep = fopen(outfilename, "wb")) == NIL)
          exit(printf("Error opening %s\n", outfilename));
     printf("Input file = %s  Output file = %s \n", infilename, outfilename);

/* Read run lengths, encode T.4, write T.4 codes */
     read_total = write_total = 0;
     do
          {
          rl_read = fread(runbuff, sizeof(FAST), RUNBUFFSIZE, infilep);
          if ( (rl_read != RUNBUFFSIZE)  && ferror(outfilep) )
               {
               printf("Error reading %s\n", infilename);
               break;
               }
          num_t4codes = t4encode(runbuff, rl_read, t4buff);  /* encode */
          t4_written = fwrite(t4buff, sizeof(short), num_t4codes, outfilep);
          if ( (t4_written != num_t4codes)  && ferror(outfilep) )
               {
               printf("Error writing %s\n", outfilename);
               break;
               }
          read_total += rl_read;
          write_total += t4_written;
          } while (t4_written);
     printf("\n%d Runlength bytes read\n", read_total * 2);
     printf("%d T4 bytes written\n", write_total * 2);
     fclose(infilep);                    /* clean up   */
     fclose(outfilep);
     free(t4buff);
     free(runbuff);
}
