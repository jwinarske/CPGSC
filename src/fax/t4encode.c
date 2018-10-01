/*-44
FUNCTION NAME:  t4encode
 PROTOTYPE IN:  T4.H
      LIBRARY:  FAX.LIB
  DESCRIPTION:  Converts a buffer of run lengths to a buffer of 1-dimensional
                Group 3 (T.4) facsimile Modified Huffman codes.
      RETURNS:  int: the number of Huffman codes in the output buffer.
     COMMENTS:  EOLs are BYTE-aligned.  Calling with a run-length count of
                zero flushes the buffer.
     CAUTION:   The T.4 buffer must be large enough to hold
                all the codes generated from the run-length buffer.
*/

#include <stdio.h>
#include <sio/siolocal.h>
#include <sio/t4.h>

#define START_TABLE encblack
#define TERMINATING 63
#define MAKEUP_CODE runlen>63

short t4encode(FAST *runbuffp, short run_count, FAST *t4buffp)
{
     extern MHcode encwhite[], encblack[];     /* The Huffman tables       */
     FAST t4token;                  /* Huffman code for current run length */
     FAST t4token_len;              /* Number of bits in Huffman code      */
     FAST runlen;                   /* Run length to be encoded            */
     FAST bits_lost;                /* Used in bit-smooshing               */
     FAST index;                    /* Converts make-up to a base-64 index */

     FAST  *t4startbuffp   = t4buffp;     /* Remember buffer address       */
     static MHcode *t4tblp = START_TABLE; /* Must be initialized like this */
     static FAST accum     = 0;           /* The T4 bit-smoosher           */
     static FAST accum_len = 0;           /* Number of bits in the accum   */

     if (run_count == 0)                 /* Zero flushes accum   */
          {
          short num_codes = 0;
          if (accum_len)
               {
               *t4buffp = accum;         /* Put accumulator in buffer      */
               num_codes = 1;
               accum = accum_len = 0;    /* Re-initialize all statics ...  */
               t4tblp = START_TABLE;     /* ... for next user.             */
               }
          return num_codes;
          }

     ++run_count;                        /* Enables use of pre-increment   */
     while (--run_count)
          {
          runlen   = *runbuffp++;        /* Fetch run length               */
          t4tblp = (t4tblp == encwhite) ? encblack : encwhite;     /* flip */
          if (runlen == EOL_MARKER)      /* Special run length             */
               {
               runlen = EOL_INDEX;       /* Change it to an index          */
               t4tblp = START_TABLE;     /* Use white table after EOL      */
               if (accum_len <= 4)       /* BYTE align EOL: make sure ...  */
                    accum_len = 4;       /* ... accum is 4 or 12 bits long */
               else if (accum_len <= 12)
                    accum_len = 12;
               else
                    {
                    *t4buffp++ = accum;  /* Output to accumulator          */
                    accum      = 0;      /* Clear accum, then claim..      */
                    accum_len  = 4;      /* ..4 bits ...                   */
                    }
               }
          else
               {
               if (MAKEUP_CODE)                         /* If runlen > 63    */
                    {
                    index = (runlen >> 6) + 63;         /* Make base-64      */
                    t4token = t4tblp[index].t4token;    /* From table        */
                    t4token_len = t4tblp[index].t4token_len; /* from table   */
                    accum |= t4token << accum_len;      /* Drop it in; if .. */
                    if (accum_len + t4token_len >= 16)  /* ..it didn't fit.. */
                         {
                         *t4buffp++ = accum;        /* ..output to buffer .. */
                         bits_lost = 16 - accum_len;    /* then install what.*/
                         accum      = t4token >> bits_lost;  /* .. didn't .. */
                         accum_len  = t4token_len - bits_lost;  /* .. fit  ..*/
                         }
                    else
                         accum_len += t4token_len;
                    runlen &= 63;   /* remainder = terminating code */
                    }
               }

          t4token     = t4tblp[runlen].t4token;        /* from table         */
          t4token_len = t4tblp[runlen].t4token_len;    /* from table         */
          accum      |= t4token << accum_len;          /* drop it in         */
          if (accum_len + t4token_len >= 16)           /* if it didn't fit.. */
               {
               *t4buffp++ = accum;                     /* ..output to buffer */
               bits_lost  = 16 - accum_len;            /* .. then install .. */
               accum      = t4token >> bits_lost;      /* .. what didn't fit */
               accum_len  = t4token_len - bits_lost;
               }
          else
               accum_len += t4token_len;
          }
     return (short)(t4buffp - t4startbuffp);     /* number of t4 codes in buffer */
}
