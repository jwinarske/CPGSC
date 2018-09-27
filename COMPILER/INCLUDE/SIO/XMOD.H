#ifndef _XMOD_
#define _XMOD_

/*** FUNCTION PROTOTYPES ***/
int x_snd(SIO *);
int x_rcv(SIO *);
USHORT x_except(SIO *, USHORT , USHORT *, USHORT);
USHORT x_rcvcrc(USHORT *);
USHORT x_rcvcksum(USHORT *);
USHORT x_sndcrc(BYTE *);
USHORT x_sndcksum(BYTE *);
USHORT makepacket(struct sndpacket *,USHORT ,ULONG , FILE *);
void ckvinstall(struct sndpacket *,USHORT , USHORT(*)(BYTE*));

#define DBLKSIZ    128          /* size of data field in packet              */
#define HEADROOM   10           /* amount of memory to save from buffer      */
#define SOH_TIMOUT _1_SEC_0     /* timeout interval for SOH                  */
#define ACK_RETRY  30           /* used in loop to wait for ACK              */
#define CRCPAKSIZ  133          /* number of bytes in CRC packet             */
#define CKSPAKSIZ  132          /* number of bytes in checksum packet        */

/*
  STRUCT NAME:  rcvpacket
  HEADER FILE:  XMOD.H
  DESCRIPTION:  Structure to describe a packet during reception.
     COMMENTS:  The SOH is discarded upon reception so is not stored
                structure.
*/
struct rcvpacket
       {
       short pnum1;             /* packet number                             */
       short pnum2;             /* 1's comp packet number                    */
       short int data[DBLKSIZ]; /* data block                                */
       short int ckvhi;         /* high byte of checkval                     */
       short int ckvlo;         /* low byte of checkval                      */
       };

/*
  STRUCT NAME:  sndpacket
  HEADER FILE:  XMOD.H
  DESCRIPTION:  Description of an XMODEM packet for transmission.
*/
struct sndpacket
       {
       BYTE soh;                /* start of header                           */
       BYTE pnum1;              /* packet number                             */
       BYTE pnum2;              /* 1's comp packet number                    */
       BYTE data[DBLKSIZ];      /* data block                                */
       USHORT ckval;            /* block-check character                     */
       };

/* EXCEPTION CODES */
#define X_ESNDMAX   10          /* max exceptions during transmission        */
#define X_ERCVMAX   10          /* max exceptions during receiving           */
#define X_NOSOHMAX 100          /* max SOH timeout exceptions                */

#define CONTINUE     0          /* errcode value that sustains snd/rcv loop  */
#define BREAK        1          /* one of the errcode value that breaks same */

/* EXCEPTION CODE USED IN BOTH XMIT AND RECEIVE */
#define E_USRCAN    0           /* user cancelled transfer                   */
enum xsndcodes                  /* CODES USED ONLY IN X_SND                  */
     {
     E_FILEMTY = 1,             /* file to transmit is empty                 */
     E_NOACK,                   /* time out waiting on ACK                   */
     E_RCVCAN,                  /* receiver canceled                         */
     E_BADPAK,                  /* NAK instead of ACK                        */
     E_EOF,                     /* End of file read                          */
     E_LASTACK,                 /* final ack not acknowledged                */
     E_SNDOK,                   /* successful transmission                   */
     E_DSKREAD                  /* disk read error                           */
     };
enum xrcvcodes                  /* CODES USED ONLY IN X_RCV                  */
     {
     E_NOSOH = E_DSKREAD+1,     /* timeout receiving SOH                     */
     E_BADCKV,                  /* invalid checkvalue received               */
     E_SNDCAN,                  /* transmitter cancelled transfer            */
     E_BADSOH,                  /* invalid SOH received                      */
     E_NODATA,                  /* timeout receiving data in block           */
     E_PAKNUM,                  /* invalid block number received             */
     E_SNDACK,                  /* sender missed last ack                    */
     E_PAKSEQ,                  /* FATAL: packet out of sequence             */
     E_DSKWRITE,                /* disk write error                          */
     E_RCVOK                    /* successful reception                      */
     };
#endif    /* _XMOD_ */
