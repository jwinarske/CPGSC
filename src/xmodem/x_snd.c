/*-
FUNCTION NAME: x_snd
        LEVEL: 3
 PROTOTYPE IN: XMOD.H
      LIBRARY: XMODEM.LIB
  DESCRIPTION: Transmit a file using XMODEM file-transfer protocol.
      RETURNS: int:  0 if successful; otherwise, the terminating
               error code.
     COMMENTS: mk_crctbl and crchware and the constant
               CRCCCITT will not be composed until Chapter 23. In
               the meantime, create dummies.
*/

#include <stdio.h>              /* Needed by modem.h   */
#include <stdlib.h>
#include "sio/siodef.h"
#include "sio/ascii.h"
#include "sio/xmod.h"
#include "sio/misc.h"
#include "sio/level0.h"        /* for timing constants */
#include "sio/buos.h"
#include "sio/key.h"
#include "sio/crc.h"

int x_snd(SIO *siop)
{
     extern uint16_t paksize;     /* number of uint8_ts to xmit or rcv    */
     extern uint16_t *crctblp;    /* pointer to the CRC lookup table   */

/* ----- static locals for speed of access ----- */
     static struct sndpacket *sndbuff, *sndbuffp;  /* buff & pointer */
     static uint8_t *bytep;    /* for addressing structure as array */
     static uint16_t ack, i;
     static uint16_t numpax;      /* buffer size in packets            */
     static uint16_t paxmade;     /* number of packets received so far */
     static uint16_t (*s_errckp)(uint8_t *);       /* pointer to checkval funct */
     static ULONG paktot;       /* running total of packets sent     */
/* -- */
     FILE *sfp;
     char fnbuff[MAX_NAME_LEN];                  /* file name buffer */
     int  errcode;
     uint16_t  errcnt;
     RANK paritytmp, stoptmp, dltmp; /* to store current data format */
     if ( (sfp = rfopen("Name for file to transmit", fnbuff, MAX_NAME_LEN)) == NIL)
          {
          printf("Cannot open %s.\n", fnbuff);        /* input file  */
          return 1;
          }
     if ( (crctblp = mk_crctbl(CRCCCITT, crchware)) == NIL)/* CRC table*/
          {
          puts("Insufficient memory for CRC table.");
          return 1;
          }
     sndbuff = (struct sndpacket *)bigbuff(sizeof(struct sndpacket), HEADROOM, &numpax);
     if (sndbuff == NIL || numpax == 0)
          {
          puts("Insufficient memory for packet buffer.");
          return 1;
          }
     printf("Buffer size = %u packets (%lu uint8_ts).\n", numpax, (long)numpax * CRCPAKSIZ );
     paritytmp = getformat(siop, PARITY);  /* save current data format */
     stoptmp   = getformat(siop, STOPS);
     dltmp     = getformat(siop, DATALEN);
     setformat(siop, PARITY, NONE);        /* now set for 8-N-1        */
     setformat(siop, DATALEN, DL8);
     setformat(siop, STOPS, STOP1);
/* ------------------------------------------------------------- */
/* -- the following variables MUST be explicitly initialized --  */
/* ------------------------------------------------------------- */
     errcnt   = 0;                /* maintained by x_except            */
     paktot   = 1;                /* running total of packets sent     */
     paxmade  = 0;                /* number of packets read from disk  */
     sndbuffp = sndbuff;          /* pointer to main buffer            */
     errcode  = CONTINUE;         /* this value sustains the main loop */
     s_errckp = NIL;              /* use as a marker in loop below     */
/* --------------------------------------*/
     if ( (paxmade = makepacket(sndbuff, numpax, paktot, sfp)) == 0)
          errcode = x_except(siop, E_FILEMTY, &errcnt, X_ESNDMAX);
     if (ferror(sfp))
          errcode = x_except(siop, E_DSKREAD, &errcnt, X_ESNDMAX);
     s_clrsio(siop, CRCPAKSIZ * numpax);     /* clear entire buffer    */
     puts("Awaiting startup");
     while (errcode == CONTINUE && s_errckp == NIL)
          {
          if (inkey() == ESC)     /* user kills from keyboard          */
               {
               errcode = x_except(siop, E_USRCAN, &errcnt, X_ESNDMAX);
               break;
               }
          switch (__s_waitch(siop, _0_SEC_1))
               {
               case 'C':               /* receiver wants crc           */
                    s_errckp = x_sndcrc;
                    paksize = CRCPAKSIZ;
                    puts("\nCRC startup received"); /* now put ckvals..*/
                    ckvinstall(sndbuff, paxmade, s_errckp); /*in struct*/
                    break;
               case NAK:               /* receiver wants checksum      */
                    s_errckp = x_sndcksum;
                    paksize = CKSPAKSIZ;
                    puts("\nChecksum startup received"); /* put ckvals */
                    ckvinstall(sndbuff, paxmade, s_errckp); /*in struct*/
                    break;
               case CAN:               /* receiver quit                */
                    errcode = x_except(siop, E_RCVCAN, &errcnt, X_ESNDMAX);
                    break;
               case TIMEOUT:           /* no timeout limit             */
                    break;
               default:
                    putchar('?');      /* not meaningful               */
               }
          }
     while (errcode == CONTINUE)       /* BEGIN MAIN TRANSMIT LOOP     */
          {
          if (paxmade == 0)            /* all packets in buffer sent ? */
               {
               printf("\nDisk Read:  ");
               sndbuffp = sndbuff;
               paxmade = makepacket(sndbuff, numpax, paktot, sfp);
               if (paxmade != 0)       /* no more packets              */
                    {
                    ckvinstall(sndbuff, paxmade, s_errckp);
                    printf("%d packets.\n", paxmade);
                    }
               else
                    {
                    errcode = x_except(siop, E_EOF, &errcnt, X_ESNDMAX);
                    --paktot;
                    continue;
                    }
               if (ferror(sfp))
                    {
                    errcode = x_except(siop, E_DSKREAD, &errcnt, X_ESNDMAX);
                    continue;
                    }
               }
#ifdef DEBUG
          for (j=0;j<128;j++)
               putchar(sndbuffp->data[j]);
          bytep = (uint8 *)sndbuffp;
          printf("[%x %x  %x]", bytep[0], bytep[1], bytep[2]);

          for (i = 0, bytep = (uint8 *)sndbuffp; i < paksize; i++)
               {
               s_putc(siop, *bytep++);           /* SEND IT !          */
               }
#endif
          s_write(siop, (uint8_t *) sndbuffp, paksize);

          for (i = ACK_RETRY; i > 0; i--)  /* get ACK or NAK           */
               {
               if (inkey() == ESC)     /* user kills from keyboard     */
                    {
                    errcode = x_except(siop, E_USRCAN, &errcnt, X_ESNDMAX);
                    break;
                    }
               if ( (ack = __s_waitch(siop, _1_SEC_0 )) == ACK)
                    {
                    printf("%lu\r", paktot);
                    ++paktot;
                    --paxmade;
                    errcnt = 0;    /* this is optional             */
                    ++sndbuffp;    /* next packet structure        */
                    break;
                    }
               if (ack == NAK)     /* receiver wants last packet again */
                    {
                    errcode = x_except(siop, E_BADPAK, &errcnt, X_ESNDMAX);
                    break;
                    }
               if (ack == CAN)     /* receiver wants last packet again */
                    {
                    errcode = x_except(siop, E_RCVCAN, &errcnt, X_ESNDMAX);
                    break;
                    }
               }
          if (i == 0)                               /* no ack received */
               {
               errcode = x_except(siop, E_NOACK, &errcnt, X_ESNDMAX);
               s_clrsio(siop, CRCPAKSIZ);  /* clear buffer             */
               }
          }                            /* END OF MAIN TRANSMIT LOOP    */
/* control comes here when receive loop breaks */
     if (errcode == E_EOF)             /* normal transfer              */
          {
          errcode = 0;                 /* for final return             */
          printf("%lu packets sent.\nAwaiting receiver's ACK: ", paktot);
          for (i = ACK_RETRY; i > 0; i--)
               {
               s_putc(siop, EOT);
               if ( (ack = __s_waitch(siop, _1_SEC_0 * 2)) == ACK)
                    {
                    putchar('\n');
                    x_except(siop, E_SNDOK, &errcnt, X_ESNDMAX);
                    printf(" of %s: %lu uint8_ts.\n", fnbuff, paktot * 128);
                    break;
                    }
               if (ack == CAN)         /* receiver cancelled           */
                    {
                    x_except(siop, E_RCVCAN, &errcnt, X_ESNDMAX);
                    break;
                    }
               if (inkey() == ESC)     /* user killed from keyboard    */
                    {
                    errcode = x_except(siop, E_USRCAN, &errcnt, X_ESNDMAX);
                    ack = !ACK;        /* for the test below           */
                    break;
                    }
               putchar('.');           /* for each timeout             */
               }
          if (ack != ACK)              /* final ACK never came         */
               x_except(siop, E_LASTACK, &errcnt, X_ESNDMAX);
          }
     if (fclose(sfp) != 0)
          printf("\nFatal error closing %s\n", fnbuff);
     free((VOID*) sndbuff);                    /* release memory               */
     free((VOID*) crctblp);
     setformat(siop, PARITY, paritytmp);       /* restore data format          */
     setformat(siop, STOPS, stoptmp);
     setformat(siop, DATALEN, dltmp);
     printf("\nEnd of X-Send\n");
     return (errcode != E_EOF);        /* return success or fail       */
}
/* end of xmit */
