/*-
    PROGRAM:  T4TORUN
DESCRIPTION:  Converts a T.4 encode (1-Dimensional) input file to an
              output of run lengths.
   COMMENTS:  Input file is    T4_1D.A4: 26,496 uint8_ts,  CRC = 26D0.
              Output file is RUNLEN1.A4: 44,406 uint8_ts,  CRC = 07BC.

*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <sio/siolocal.h>
#include <sio/t4.h>


#define RUNBUFFSIZE  2048
#define T4BUFFSIZE   RUNBUFFSIZE

int main(void)
{
    char *infilename = "T4_1D.A4";
    char *outfilename = "RUNLEN1.A4";
    FILE *outfilep, *infilep;
    FAST *t4buffp;
    short *runbuffp;
    short t4_len, run_len, errcode;
    run_len = t4_len = 100;
    
    if ((t4buffp  = (FAST*) malloc(T4BUFFSIZE * sizeof(FAST))) == NIL)
        exit(puts("Error allocating T.4 buffer."));
    if ( (runbuffp = (short *) malloc(RUNBUFFSIZE * sizeof(short))) == NIL)
        exit(puts("Error allocating run-length buffer."));
    
    if ( (outfilep = fopen(outfilename, "wb")) == NIL)
     	exit(printf("Error opening output %s\n", outfilename));
    if ((infilep = fopen(infilename, "rb"))  == NIL)
     	exit(printf("Error opening input %s\n", infilename));

    printf("Input file = %s  Output file = %s \n", infilename, outfilename);

    errcode = t4decode(infilep, outfilep, runbuffp, run_len, t4buffp, t4_len);

    if (errcode)
       puts("I/O error during decoding.");
    fclose(outfilep);
    fclose(infilep);
    free(runbuffp);          /* clean up */
    free(t4buffp);

    return 0;
}	
