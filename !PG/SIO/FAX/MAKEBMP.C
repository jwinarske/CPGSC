/*-38
 PROGRAM NAME:  MAKEBMP
  DESCRIPTION:  Makes a bitmap image suitable for one-dimensional
                facsmile encoding. Beginning at pel 0 line 0,
                a single pel moves one bit to the right on successive lines.
                This produces a left-to-right diagonal, one pel wide.
     COMMENTS:  The output file is BITMAP0.A4: 746,496 CRC = 7160.
*/

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <sio\siolocal.h>
#include <sio\t4.h>

#define ALL_BLACK 	   0xFF
#define ALL_WHITE 	   0x00

void main(void)
{
    char * outfilename = "BITMAP0.A4";
    FILE *outfile;
    USHORT i, j;                      /* general counters                   */
    USHORT page_num;                  /* page number in progress            */
    USHORT maskbyte;                  /* masked byte in each line           */
    USHORT prebits;                   /* number bytes before maskbyte       */
    USHORT postbits;                  /* number bytes after maskbyte        */
    BYTE   color;                     /* color of current diagonal line     */
    BYTE   line_of_bits[BYTES_PER_LINE -1]; /* array of bytes               */

    BYTE   mask[8][2] =               /* black & white maskbyte table       */
        {
        {0x80, 0x7F}, {0x40, 0xBF}, {0x20, 0xDF}, {0x10, 0xEF},
        {0x08, 0xF7}, {0x04, 0xFB}, {0x02, 0xFD}, {0x01, 0xFE}
        };

    if ( (outfile = fopen(outfilename, "wb")) == NIL)
        exit(puts("Cannot open output file."));
/* for each page */
    for (color = ALL_BLACK, page_num = 1; page_num < 2; --page_num)
        {
        maskbyte = prebits = 0;
        postbits = BYTES_PER_LINE -1;
        memset(line_of_bits, color, BYTES_PER_LINE -1);
/* for each line */
        for (i = 0; i < LINES_PER_PAGE ; ++i)
           {
           printf("%s: %d\r", color == ALL_BLACK ? "Black" : "White", i+1);
           fwrite(line_of_bits, 1, prebits, outfile);
           fwrite(&mask[maskbyte][page_num], 1, 1, outfile);
           fwrite(line_of_bits, 1, postbits, outfile);
           if (++maskbyte == 8)       /* if all bits have been used ...     */
               {                      /* ... scoot the mask byte right      */
               maskbyte = 0;
               ++prebits;
               --postbits;
               }
           }
       color = (BYTE) ~color;         /* flip the color                     */
       putchar('\n');
       }
    fclose(outfile);
}
