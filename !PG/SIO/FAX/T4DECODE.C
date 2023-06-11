/*-50
FUNCTION NAME:  t4decode
 PROTOTYPE IN:  T4.H
      LIBRARY:  FAX.LIB
      RETURNS:  int: 0 if file I/O successful; otherwise 1.
  DESCRIPTION:  Binary-tree T.4 decoder. The 1-D T.4 data is read from 
                input file handle, decoded, and written as run lengths 
                to output handle.  
     COMMENTS:
*/

#include <stdio.h>
#include <memory.h>
#include <sio\siolocal.h>
#include <sio\t4.h>
int t4decode(FILE *t4file, FILE *runfile, short *runbufp,
            USHORT runbuff_len, FAST *t4bufp, USHORT t4_len)
{
     extern   T4NODE eoltree[];            /* Start in EOL tree    */
     register FAST t4_code;                /* The current T.4 byte */
     register T4NODE *curr_node;        /* Current node in tree */
     register FAST numbits;                /* Bit counter          */
     FAST    *t4buff_start  = t4bufp;
     short   *runlen_startp = runbufp;
     short    t4_read;                     /* Bytes in T.4 buffer */
     int      errcode = 0;
     USHORT   numruns = 0;
     memset(runbufp, 0, runbuff_len * sizeof(short));
     curr_node = eoltree;

     while (t4_read = fread(t4bufp, sizeof(FAST), t4_len, t4file))
          {
          ++t4_read;                  
          while (--t4_read)
               {
               t4_code = *t4bufp++;   /* Fetch byte */
               numbits = sizeof(FAST) * 8;  
               ++numbits;             
               while (--numbits)      /* For every bit */                 
                    {                 
//                  curr_node = *((T4NODE **)curr_node + (t4_code & 1));
                    curr_node = t4_code & 1 ? curr_node->one :  curr_node->zero;
                    if (curr_node->run_len != NOTTERMINAL) /* complete code */
                         {                              
                         *runbufp += curr_node->run_len;
                         if ( (curr_node->run_len < 64) || (*runbufp == EOL_MARKER) )
                             {
                             ++numruns;
                             ++runbufp;
                             }
                         if (numruns == runbuff_len)        /* Buffer full? */
                              {
                              if (fwrite(runlen_startp, sizeof(short),
                                  runbuff_len, runfile) != runbuff_len)
                                   {
                                   errcode = 1;  /* Write error */
                                   goto EXIT;
                                   }
                              numruns = 0;                /* Reset */
                              runbufp = runlen_startp;
                              memset(runbufp, 0, runbuff_len * sizeof(short));
                              }
                         }
                   t4_code >>= 1 ;          /* Next bit, please */
                   }
               }
          t4bufp = t4buff_start;            /* Reset */
          }
    if (fwrite(runlen_startp, sizeof(short), numruns, runfile) != numruns)
        errcode = 1;   /* If flush causes an error */
EXIT:
     return errcode;
}
