/*-
FUNCTION NAME: x_rcv
        LEVEL: 3
 PROTOTYPE IN: XMOD.H
      LIBRARY: XMODEM.LIB
  DESCRIPTION: Receive a file using the XMODEM protocol.
      RETURNS: int: 0 if transfer is successful, otherwise, the
               terminating error code.
      COMMENT: mk_crctbl and crchware and the constant
               CRCCCITT will not be composed until Chapter 23. In
               the meantime, create dummies.
*/

#include <stdio.h>        /* Needed by modem.h    */
#include <stdlib.h>
#include "sio/siodef.h"
#include "sio/ascii.h"
#include "sio/xmod.h"
#include "sio/crc.h"
#include "sio/buos.h"
#include "sio/misc.h"
#include "sio/key.h"
#include "sio/level0.h"   /* for timing constants */

int x_rcv(SIO *siop)
{
     extern uint16_t (*r_errckp)(uint16_t*); /* pointer to the error check funct */
     extern struct rcvpacket *rcvbuffp;    /* buffer pointer is global    */
     extern uint16_t paksize;          /* number of uint8_ts to xmit or rcv    */

     extern char  *ckvname;          /* string indicating CRC or cksum    */
     extern uint8_t  csync;             /* "NAK" for checksum, 'C' for crc   */
     extern uint16_t *crctblp;         /* pointer to the CRC lookup table   */

/* ----- static locals for speed of access ----- */

     static uint16_t         i, j;
     static uint16_t        *intp;     /* for addressing structure as array */
     static unsigned  long paktot;   /* running packet total              */
     static uint16_t         numpax;   /* number of packets in buffer       */
     static uint16_t         buffpax;  /* number of packets received so far */
     static int            soh;      /* received start of header uint8     */
/* -- */
     struct rcvpacket *rcvbuff;
     FILE *rfp;                      /* file pointer               */
     char fnbuff[MAX_NAME_LEN];      /* file name buffer           */
     int  errcode;                   /* sustains main receive loop */
     uint16_t errcnt;                /* main exception counter     */
     uint16_t nosohtot;              /* special counter for soh timeouts  */
     RANK paritytmp, stoptmp, dltmp; /* to store current data format      */
     if ( (rfp = wfopen("Name of file to receive", fnbuff, MAX_NAME_LEN)) == NIL)
          {
          if (*fnbuff)
               printf("Cannot open %s.\n",fnbuff);  /* input file         */
          return 1;
          }
     if ( (crctblp = mk_crctbl(CRCCCITT, crchware)) == NIL)  /* CRC table */
          {
          puts("Insufficient memory for CRC table.");
          return 1;
          }
     rcvbuff = (struct rcvpacket*)bigbuff(sizeof(struct rcvpacket), HEADROOM, &numpax);
     if (rcvbuff == NIL || numpax == 0)
          {
          puts("Insufficient memory for packet buffer.");
          return 1;
          }
     printf("Buffer = %u packets (%lu uint8_ts).\n", numpax, (long)numpax * DBLKSIZ);

     paritytmp = getformat(siop, PARITY); /* save current data format          */
     stoptmp   = getformat(siop, STOPS);
     dltmp     = getformat(siop, DATALEN);
     setformat(siop, PARITY, NONE);       /* now set for 8-N-1                 */
     setformat(siop, DATALEN, DL8);
     setformat(siop, STOPS, STOP1);
/* ------------------------------------------------------------- */
/* -- the following variables MUST be explicitly initialized --  */
/* ------------------------------------------------------------- */
     errcnt   = 0;
     buffpax  = 0;                   /* packets received so far      */
     paktot   = 1;                   /* running packet total         */
     errcode  = CONTINUE;
     nosohtot = 0;                   /* SOH timeout counter          */
     rcvbuffp = rcvbuff;             /* pointer to main rcvbuffer    */
     rcvbuffp->pnum1 = VIRGIN;       /* used by for startup routine  */
     r_errckp = x_rcvcrc;            /* starting check value routine */
     csync    = (uint8_t) ((r_errckp == x_rcvcrc) ? 'C': NAK); /* match r_errckp   */
     ckvname  = (r_errckp == x_rcvcrc) ? "CRC": "CHECKSUM";
     paksize  = (r_errckp == x_rcvcrc) ? CRCPAKSIZ-1 : CKSPAKSIZ-1;
/* ------------------------------------- */
     s_clrsio(siop, CRCPAKSIZ * numpax);  /* clear buffer            */
     printf("\nAttempting to synchronize in %s mode.\n", ckvname);
     s_putc(siop, csync);            /* send start-up sync character */
     while (errcode == CONTINUE)
          {
          if ( (soh = __s_waitch(siop, SOH_TIMOUT)) != SOH) /* bad SOH */
               {
               switch (soh)
                    {
                    case TIMEOUT:
                         if (!(++nosohtot % 10))  /* every 10th time */
                              errcode = x_except(siop, E_NOSOH, &nosohtot, X_NOSOHMAX);
                         break;
                    case EOT:                /* no more packets        */
                         for (rcvbuffp = rcvbuff, i = buffpax; i > 0; --i, ++rcvbuffp)
                              for (j = 0; j < DBLKSIZ; j ++)
                                   putc(rcvbuffp->data[j], rfp);
                         if (fflush(rfp) == 0)
                              {
                              --paktot;
                              errcode = x_except(siop, E_RCVOK, &errcnt, X_ERCVMAX);
                              printf(" of %s:  %lu uint8_ts (%lu blocks).\
                                    \n", fnbuff, paktot * 128, paktot);
                              }
                         else
                              errcode = x_except(siop, E_DSKWRITE, &errcnt, X_ERCVMAX);
                         break;
                    case CAN:              /* sender canceled transfer */
                         errcode = x_except(siop, E_SNDCAN, &errcnt, X_ERCVMAX);
                         break;
                    default:             /* unmeaningful char received */
                         printf("rcvbuffp->pnum1 = %d\n",rcvbuffp->pnum1);
                         errcode = x_except(siop, E_BADSOH, &errcnt, X_ERCVMAX);
                    }
               if (inkey() == ESC)         /* user kills from keyboard */
                    errcode = x_except(siop, E_USRCAN, &errcnt, X_ERCVMAX);
               continue;
               }
          for (i = 0, intp = (uint16_t *)rcvbuffp; i < paksize; i++)
               *intp++ = __s_waitch(siop, _0_SEC_1);  /*  rest of packet  */
          if (rcvbuffp->ckvhi == TIMEOUT)
               {
               errcode = x_except(siop, E_NODATA, &errcnt, X_ERCVMAX);
               continue;
               }
          if ( (*r_errckp)((uint16_t *)rcvbuffp->data) != 0)    /* bad checkvalue     */
               {
               errcode = x_except(siop, E_BADCKV, &errcnt, X_ERCVMAX);
               continue;
               }
          if (rcvbuffp->pnum1 ^ (~rcvbuffp->pnum2 & 0x00ff)) /* integrity */
               {
               errcode = x_except(siop, E_PAKNUM, &errcnt, X_ERCVMAX);
               continue;
               }
//if (rcvbuffp->pnum1 != (uint16_t)(paktot % 256))    /* wrong sequence     */
          if (rcvbuffp->pnum1 != (short)(paktot & 0x00FF)) /* wrong sequence    */
               {

               if (rcvbuffp->pnum1  == (short)((paktot & 0x00FF)) -1) /* previous  */

//               if (rcvbuffp->pnum1  == (uint16_t)(paktot & 0x00FF) -1) /* previous */
                    errcode = x_except(siop, E_SNDACK, &errcnt, X_ERCVMAX);
               else                                      /* FATAL      */
                    errcode = x_except(siop, E_PAKSEQ, &errcnt, X_ERCVMAX);
               continue;
               }
          printf("%lu\r", paktot);           /* running total on screen*/
          ++rcvbuffp;                        /* next packet in array   */
          ++paktot;
          errcnt = 0;
          if (++buffpax == numpax)           /* buffer full            */
               {
               printf("\nDisk write\n");
               for (rcvbuffp = rcvbuff, i = buffpax ; i > 0; --i, ++rcvbuffp)
                    for (j = 0; j < DBLKSIZ; j ++)
                         putc(rcvbuffp->data[j], rfp);
               if (ferror(rfp))
                    {
                    errcode = x_except(siop, E_DSKWRITE, &errcnt, X_ERCVMAX);
                    break;
                    }
               buffpax  = 0;                 /* reset counter and ...  */
               rcvbuffp = rcvbuff;           /* buffer pointer         */
               s_clrsio(siop, CRCPAKSIZ * numpax);  /* clear buffer    */
               }
          s_putc(siop, ACK);                 /* ACK is your final act  */
          }                                  /* end of receive loop    */
     if (fclose(rfp) != 0)    /* come here when receive loop breaks    */
          printf("Fatal error closing %s\n", fnbuff);
     free((VOID*)rcvbuff);                   /* release buffer         */
     free((VOID*)crctblp);                   /* release crc table      */
     setformat(siop, PARITY, paritytmp);     /* restore data format    */
     setformat(siop, STOPS, stoptmp);
     setformat(siop, DATALEN, dltmp);
     puts("\nEnd of X-Receive");
     return (errcode == E_RCVOK ? 0 : 1);   /* return success or fail  */
}
