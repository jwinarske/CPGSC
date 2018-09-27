/*-
FUNCTION NAME: x_except
        LEVEL: 3
 PROTOTYPE IN: XMOD.H
      LIBRARY: XMODEM.LIB
  DESCRIPTION: Handles execptions (e.g., errors) that occur during XMODEM
               transfers.
      RETURNS: int:  one of the error codes given in XMOD.H
     COMMENTS: A pointer to an exception counter variable and its maximum
               permitted value are passed as arguments.
*/

#include <stdio.h>             /* Needed by modem.h    */
#include <ctype.h>
#include <sio\siodef.h>
#include <sio\misc.h>
#include <sio\ascii.h>
#include <sio\xmod.h>
#include <sio\level0.h>        /* for timing constants */
#include <sio\buos.h>
#include <sio\key.h>


USHORT x_except(SIO *siop, USHORT exceptnum, USHORT *ex_cntp, USHORT maxexcept)
{
     extern struct rcvpacket *rcvbuffp; /* pointer to receive packet buffer */
     extern int   paksize;              /* number of bytes to xmit or rcv   */
     extern USHORT (*r_errckp)();       /* pointer to the error check funct */
     extern char  *ckvname;             /* string indicating CRC or cksum   */
     extern BYTE  csync;                /* "NAK" for checksum, 'C' for crc  */
     extern char *x_msg[];
     extern struct rcvpacket *rcvbuffp; /* pointer to receive packet buffer */
     int errval = CONTINUE;
     switch (exceptnum)
          {
          case E_USRCAN:                /* user aborts from keyboard        */
               puts(x_msg[E_USRCAN]) ;
               errval = BREAK;
               __delay(_0_SEC_5);
               s_putc(siop, CAN);
               break;
/* errors in transmission */
          case E_FILEMTY:
               puts(x_msg[E_FILEMTY]);
               break;
          case E_RCVCAN:                /* transmitter aborted          */
               puts(x_msg[E_RCVCAN]);
               errval = BREAK;          /*           FATAL              */
               break;
          case E_NOACK:                 /* timeout waiting for ACK      */
               puts(x_msg[E_NOACK]);
               ++*ex_cntp;
               break;
          case E_BADPAK:                /* resending previous packet    */
               puts(x_msg[E_BADPAK]);
               ++*ex_cntp;
               s_clrsio(siop, CRCPAKSIZ);  /* clear buffer              */
               break;
          case E_EOF:                   /* end of disk file read        */
               puts(x_msg[E_EOF]);
               errval   = E_EOF;
               *ex_cntp = X_ESNDMAX;
               break;
          case E_DSKREAD:               /* disk read error              */
               puts(x_msg[E_DSKREAD]);
               errval = BREAK;          /*           FATAL              */
               break;
          case E_LASTACK:               /* no ACK response to EOT       */
               puts(x_msg[E_LASTACK]);
               s_putc(siop, CAN);
               break;
          case E_SNDOK:                 /* good transfer                */
               errval = E_EOF;
               printf("%s",x_msg[E_SNDOK]);   /* use printf--no newline */
               break;
/* errors in reception */
          case E_NOSOH:                 /* timeout waiting for SOH      */
               ++*ex_cntp;              /* bump caller's error count    */
               puts(x_msg[E_NOSOH]);
               if (rcvbuffp->pnum1 == VIRGIN) /* negotiate startup mode */
                    {
                    r_errckp = (r_errckp == x_rcvcrc) ? x_rcvcksum : x_rcvcrc;
                    paksize  = (r_errckp == x_rcvcrc) ? CRCPAKSIZ-1: CKSPAKSIZ-1;
                    csync    = (BYTE) ((r_errckp == x_rcvcrc) ? 'C'        : NAK);
                    ckvname  = (r_errckp == x_rcvcrc) ? "CRC"      : "CHECKSUM";
                    s_putc(siop, csync);
                    printf("\nAttempting to synchronize in %s mode.\n", ckvname);
                    }
               else
                    s_putc(siop, NAK);
               break;
          case E_BADCKV:                /* bad checksum or CRC          */
               puts(x_msg[E_BADCKV]);
               ++*ex_cntp;
               s_putc(siop, NAK);
               break;
          case E_SNDCAN:                /* transmitter aborted          */
               puts(x_msg[E_SNDCAN]);
               errval = BREAK;          /*           FATAL              */
               break;
          case E_BADSOH:                /* invalid SOH received         */
               puts(x_msg[E_BADSOH]);
               s_clrsio(siop, CRCPAKSIZ);     /* ignore rest of packet  */
               s_putc(siop, NAK);       /* tell sender to retry         */
               ++*ex_cntp;
               break;
          case E_NODATA:                /* timeout in packet            */
               puts(x_msg[E_NODATA]);
               ++*ex_cntp;
               s_putc(siop, NAK);
               break;
          case E_PAKNUM:                /* packet numbers don't agree   */
               puts(x_msg[E_PAKNUM]) ;
               s_clrsio(siop, CRCPAKSIZ);
               ++*ex_cntp;
               s_putc(siop, NAK);       /* ask for retransmission       */
               break;
          case E_SNDACK:                /* duplicate of previous packet */
               puts(x_msg[E_SNDACK]) ;
               ++*ex_cntp;
               s_putc(siop, ACK);
               break;
          case E_PAKSEQ:                /* packets out of order --FATAL */
               puts(x_msg[E_PAKSEQ]);
               errval = BREAK;          /*           FATAL              */
               break;
          case E_DSKWRITE:              /* disk write error             */
               puts(x_msg[E_DSKWRITE]);
               errval = BREAK;          /*           FATAL              */
               s_putc(siop, CAN);
               break;
          case E_RCVOK:                 /* good transfer                */
               errval = BREAK;
               printf("%s",x_msg[E_RCVOK]);   /* use printf--no newline */
               __delay(_0_SEC_5);             /* let receiver get ready */
               s_putc(siop, ACK);             /* send final ACK         */
               break;
          default:
               break;
          }
     if (errval == CONTINUE && *ex_cntp > maxexcept)
          {
          errval = BREAK;
          printf("%d errors or waits have occured: Keep trying?\
(y/n):\a ", maxexcept);
          if (toupper(getkbch()) == 'Y')
               {
               errval   = CONTINUE;
               *ex_cntp = 0;            /* reset caller's error counter */
               }
          putchar('\n');
          }
     return errval;
}
