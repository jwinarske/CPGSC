#ifndef  _SIODEF_
#define  _SIODEF_

#include "siolocal.h"
#include "siodef.h"

//TODO #include "sio/uart.h"

/**** FUNCTION PROTOTYPES ****/
int    br_to_bcode(uint16_t);
RANK   get232(SIO*, RANK);
short  getbaud(SIO *);
short  getformat(SIO*, RANK);
int    s_close(SIO*);
void   s_clearerr(SIO *);
int    s_clrsio(SIO *,uint16_t);
int    s_fgetln(SIO *, char *, short);
int    s_fgets(SIO *, char *, int );
void   s_fputs(SIO *,char *);
int    s_ipop(SIO *);
int    s_ipush(SIO *);
bool   s_keybort(SIO *);
SIO   *s_open(uint16_t);
int    s_opop(SIO *);
int    s_opush(SIO *);
void   s_puts(SIO *,char *);
short  s_write(SIO *, uint8_t *, short);
short  serial_status(SIO *, RANK);
short  set232(SIO*, RANK, bool);
short  setbaud(SIO *, RANK);
short  setformat(SIO *, RANK, RANK);
short  stat232(SIO *, RANK);
int    setuart(SIO *, RANK, uint16_t);
short  tx_iwrite(SIO *, uint8_t *, short);
short  tx_write(SIO *, uint8_t *, short);

#define  OFF  0
#define  ON   1
#define  CLOSED FALSE
#define  OPEN   TRUE

#define NOT_READY  -1

#define CMDBUFSIZ   50          /* Capacity of modem's command buffer     */
#define CMDSIZ      7           /* Max storage needed for modem command   */

#define TX_BUFSIZ   BUFSIZ      /* From stdio.h                           */
#define TX_NUMBUFFS  10         /* Number of buffers in tx queue          */

#ifdef DEBUG_IBUFF
#define RCV_BUFSIZ  8           /* Size of rxrdy interrupt buffer         */
#else
#define RCV_BUFSIZ  2000        /* Size of rxrdy interrupt buffer         */
#endif


/**** Manifest contants for UART Interrupts ****/

enum intrp                      /* Manifest constant names for interrupts */
  {
    RS232 =   0,                /* Changes on RS232 inputs                */
    THRE,                       /* Transmitter buffer emtpy               */
    RXRDY,                      /* Receive data ready                     */
    SERERR,                     /* Serialization errors                   */
    RXTIMEOUT                   /* For receiver FIFO                      */
  };

/**** CONSTANTS FOR INTERRUPT TRANSMIT ROUTINES ****/

/* Transmit shut down modes*/
#define WAIT_TIL_FINISH  0
#define SHUTDOWN_NOW     1

/* Return Codes from tx_write */
#define Q_OK           0
#define Q_FULL         1
#define Q_BUF2BIG      2

#define TX_INUSE       1
#define TX_FREE        0

/**** Constants for Baud Clock Functions ****/
enum clk { X1 = 0, X16, X32, X64 };

/**** Constants for Transmit/Recieve enable Arguments ****/
enum enable{XMITON = 0, RCVON, RXHSON, TXHSON, SETCLK};

/**** Constants for S_OPEN/S_CLOSE ****/
#define  CLOSED FALSE
#define  OPEN   TRUE

/**** Constants for GET/SET FORMAT/BAUD Functions ****/
enum brfmt { BAUD = 0, STOPS, DATALEN, PARITY };

/**** Constants for RS232 GET/SET RS232 Functions ****/
enum rs232 { DTR = 0, RTS, GPO1, GPO2, BRK };

/**** Constants for STAT232 Function ****/
enum st232 { CTS = 0, DCD, DSR, RI, GPI1, GPI2 };

/**** Arguments for serial_status function ****/
enum serstat { ANY_ERRORS = 0, PARITY_ERR, OVERRUN_ERR, FRAME_ERR, BREAK_ON };

/**** Constants for Parity Arguments ****/
enum par { NONE = 0, ODD, EVEN, MARK, SPACE };

/**** Constants for Stop Bit Arguments ****/
enum sb {STOP1 = 0, STOP1_5, STOP2 };


/**** Constants for Receive Data Length Arguments ****/
enum rcvdl { DL5 = 0, DL6, DL7, DL8 };


/**** Constants for Transmit Arguments ****/
enum txdl { TxDL5 = 0, TxDL6, TxDL7, TxDL8 };

/**** Manifest Constants for Baud Rate Arguments ****/
enum baudcodes
    {
    BAUD50 = 0, BAUD75, BAUD110,  BAUD134_5, BAUD150,  BAUD300,  BAUD600,
    BAUD1200, BAUD1800, BAUD2000, BAUD2400,  BAUD3600, BAUD4800, BAUD7200,
    BAUD9600, BAUD14K4, BAUD19K2, BAUD28K8,  BAUD38K4, BAUD57K6, BAUD115K2,
    NUMBAUDS
    };

/*
    STRUCT : sictl_
HEADER FILE: SIODEF.H
DESCRIPTION: Control structure for formatted input.
*/
struct sictl_
     {
     bool      t_outflag;           /*0  Timeout on/off flag              */
     unsigned  t_out;               /*1  Timeout period                   */
     bool      rawflag;             /*2  Perform no processing at all     */
     bool      ekobakflag;          /*3  Echo all input back to sender    */
     bool      asciiflag;           /*4  Reset strip bit 7                */
     short     eolmode;             /*5  End-of-line formatting           */
     bool      consflag;            /*6  Echo characters to console       */
     short     casemode;            /*7  Change to upper or lower case    */
     bool      cntrlflag;           /*10 Remove control characters        */
     short     ok_cntrls[32];       /*11 Permitted control characters     */
     short     numcc;               /*12 Number of controls in ok_cntrls  */
     bool      filterflag;          /*13 Filter-remove characters         */
     short     filtlist[128][2];    /*14 List of uint8_t to remove or filter */
     short     numfc;               /*15 Number of uint8_ts in filter list   */
     FAST      lastc;               /*16 Previous uint8_t output             */
     bool      rbakflag;            /*17 A pending eol decision resolved  */
     FAST      rbakc;               /*18 Pending readback character       */
     };

/*
  STRUCTURE: soctl_
HEADER FILE: SIODEF.H
DESCRIPTION: Control structure for formatted output.
*/
struct soctl_
     {
     bool      rawflag;             /*0  Perform no processing at all     */
     short     eolmode;             /*1  End-of-line formatting           */
     bool      consflag;            /*2  Echo characters to console       */
     bool      wechoflag;           /*3  Interuint8_t wait for return echo   */
     unsigned  wecho_dly;           /*4  Tsecs to wait for return echo    */
     uint16_t    casemode;            /*5  Change to upper or lower case    */
     bool      asciiflag;           /*9  Reset strip bit 7                */
     bool      cntrlflag;           /*10 Remove control characters        */
     uint8_t      ok_cntrls[32];       /*11 Permitted control characters     */
     uint16_t    numcc;               /*12 Number of controls  in ok_cntrls */
     bool      filterflag;          /*13 Filter-remove characters         */
     short     filtlist[128][2];    /*14 List of uint8_t to remove or filter */
     uint16_t    numfc;               /*15 Number of uint8_ts in  filter list  */
     bool      ib_dlyflag;          /*16 Interuint8_t delay in  tsecs        */
     unsigned  ib_dly;              /*17 Pause between uint8_ts              */
     bool      il_dlyflag;          /*18 Interline pause flag             */
     FAST      il_dlyc;             /*19 Char to begin inter-line pause   */
     unsigned  il_dly;              /*20 Inter-line     pause in tsecs    */
     FAST      kbortc;              /*21 Key to break out of loops        */
     int       lastc;               /*22 Previous uint8_t output             */
     bool      flushflag;           /*23 An end of line decision pending  */
     };

/**** Constants for Timing ****/

#define  TIMEOUT    -1
#define  _0_SEC_05   1              /* 50 ms  */
#define  _0_SEC_1    2              /* 1.8    */
#define _0_SEC_15    3              /* 150 ms */
#define  _0_SEC_2    4              /* 3.6    */
#define _0_SEC_25    5              /* 250 ms */
#define  _0_SEC_3    6              /* 5.5    */
#define  _0_SEC_4    7              /* 7.3    */
#define  _0_SEC_5    9              /* 9.1    */
#define  _0_SEC_6    11             /* 10.9   */
#define  _0_SEC_7    13             /* 12.7   */
#define  _0_SEC_8    15             /* 14.6   */
#define  _0_SEC_9    16             /* 16.4   */
#define  _1_SEC_0    18             /* 18.2   */

/**** Error Codes Returned by SIO Functions ****/

enum {
     BAD_FCN = 2,    /* Function not supported */
     OR_ARG,         /* Argument out of range  */
     BAD_ARG,        /* Argument not supported */
     BAD_PORT,       /* Illegal device number  */
     NO_PORT,        /* Device not installed   */
     NO_SIO,         /* No SIO declared        */
     OPEN_NOW,       /* Device already open    */
     NO_CLOSE,       /* No such device open    */
     KEY_CAN,        /* Aborted from keyboard  */
     NO_FILE,        /* File not found         */
     NO_IMEM,        /* Out of heap memory     */
     };

#define  NUMMASKS    5          /* ORDINAL elements in "setmask" array    */
#define  VIRGIN     -2          /* Dummy initializer (must be < -1)       */
#define  SUPPLIED    0          /* Dummy initializer                      */

/****Manifest Constants for Columns in the Virtual Register Array ****/
#define  VIR       0
#define  USR       1

/*
  STRUCTURE:  vregbits_
HEADER FILE:  SIODEF.H
DESCRIPTION:  General structure   for virtual register maniupulation.
   COMMENTS:
*/
struct vregbits_
     {
#ifdef bozo
     MASK      resetmask;           /* AND mask apply to virtual register */
     MASK      setmask[NUMMASKS];   /* Array of OR masks for each setting */
     uint8_t   vregnum;             /* Virtual register number (row)      */
     uint16_t  offset;              /* Offset of physical uart register   */
     RANK      now;                 /* Code for current value             */
     uint16_t  start;               /* Code to use at initialization      */
     struct vregbits_ *next;        /* Next struct for this function      */
#else
     MASK      resetmask;           /* AND mask apply to virtual register */
     MASK      setmask[NUMMASKS];   /* Array of OR masks for each setting */
     RANK      vregnum;             /* Virtual register number (row)      */
     uint16_t  offset;              /* Offset of physical uart register   */
     RANK      now;                 /* Code for current value             */
     RANK      start;               /* Code to use at initialization      */
     struct vregbits_ *next;        /* Next struct for this function      */
#endif     
     };

/*
  STRUCTURE:  vout232_
HEADER FILE:  SIODEF.H
DESCRIPTION:  Control structure for an RS-232 output.
   COMMENTS:  The next member enables constuction of a linked list.
*/
struct vout232_
   {
   MASK       resetmask;            /* AND mask apply to virtual register */
   uint16_t     vregnum;              /* Virtual register number (row)      */
   uint16_t     offset;               /* Offset of physical uart register   */
   bool       now;                  /* Code for current value             */
   bool       start;                /* Code to use at initialization      */
   };

/*
  STRUCTURE:  vin232_
HEADER FILE:  SIODEF.H
DESCRIPTION:  Control structure for an RS-232 input.
*/
struct vin232_
     {
     uint16_t    offset;             /* Offset of physical register in UART */
     MASK      mask;               /* Mask to isolate active bit          */
     bool      now;                /* Current value of this input         */
     };

/*
  STRUCTURE:  ser_err_
HEADER FILE:  SIODEF.H
DESCRIPTION:  Control structure for serialization errors.
*/
struct ser_err_
     {
     uint16_t    offset;             /* Offset of physical register in UART */
     MASK      mask;               /* Mask to isolate active bit          */
     bool      now;                /* Current value of this input         */
     };

/*
  STRUCTURE:  vbaud_
HEADER FILE:  SIODEF.H
DESCRIPTION:  Control structure for baud rate.
*/
struct vbaud_
   {
   uint8_t       vregnuml;        /* Virtual array of baud rate lo           */
   uint8_t       vregnumh;        /* Virtual array of baud rate hi           */
   uint16_t     offsetlo;        /* Offset of lo-order baud  rate register  */
   uint16_t     offsethi;        /* Offset of hi-order baud  rate register  */
   short      divisor[NUMBAUDS][2]; /* Array of two-uint8_t divisors         */
   RANK       now;             /* Rank of current divisorin divisor array */
   RANK       start;           /* Rank of value to use at start up        */
   };

union inbits_232
   {
   REG reg232;
   struct
      {
      unsigned int cts : 1;     /* <--  This is the lsb but may be msb in */
      unsigned int dsr : 1;     /*    other compilers.                    */
      unsigned int ri  : 1;
      unsigned int dcd : 1;
      unsigned int gpi1: 1;
      unsigned int gpi2: 1;
      unsigned int unused : 10;
      }bitmap;
   };

/*
  STRUCTURE:  SIOLIST
HEADER FILE:  SIODEF.H
DESCRIPTION:  Holds status information about SIO capabilities.  Used by
              level-1 functions.
   COMMENTS:
*/
struct SIOLIST
    {
    SIO  *siop;                         /* Address of an SIO              */
    bool sio_openflag;                  /* Whether it's already open      */
    bool intrpt_supp;                   /* Whether it supports interrupts */
    };

/*
  STRUCTURE:  SYS_ILIST
HEADER FILE:  SIODEF.H
DESCRIPTION:  Holds pertinent system information about the SIO.  Used by
              level-1 functions.
   COMMENTS:
*/
struct SYS_ILIST
     {
     RANK   inum;           /* Rank in system interrupt vector table      */
     MASK   imask;          /* Mask for Interrupt Mask Register of 8259   */
//TODO     INTPTR isr;            /* Pointer to interrupt handler function      */
//TODO     INTPTR oldivect;       /* Save existing vector here                  */
     FAST  oldimr;          /* Save existing Interrupt Mask Register here */
     struct vout232_ *oldgpo2;  /* Save address of gpo2 structure         */
     };

/*
  STRUCTURE:  tx_queue
DESCRIPTION:  Ring buffer for transmitter interrupts.
   COMMENTS:  tx_list is used only for high speed data transmission
*/
struct tx_queue
   {
   char *locbuff;           /* pointer to local buffer                    */
   char *buffp;             /* pointer to next charater to be transmitted */
   short buffcnt;           /* actual size of this buffer                 */
   short inuseflag;         /* 'buffer empty or ready to be xmitted' flag */
   short id;                /*debug*/
   };

/*-39
    STRUCTURE:  SIO
         FILE:  SIODEF.H
  DESCRIPTION:  Master structure defining a serial port.
*/
struct sio
   {
   uint8_t   * uart_base;                 /*0  Base address of UART             */
   uint16_t data_off;                    /*1  Offset of data port from base    */
   uint16_t status_off;                  /*2  Offset of status port from base  */
   MASK   rcvmask;                     /*3  RxRDY mask                       */
   MASK   xmitmask;                    /*4  Xmit holding reg. empty mask     */
   MASK   tx_emptymask;                /*5  Xmit shift reg. empty mask       */
   FAST   (*readuint8_t)(uint8_t *);         /*6  Pointer to RAM/port read routine */
   void   (*writeuint8_t)(uint8_t *, FAST);  /*7  Pointer to RAM/port read routine */
   FAST   (*s_rstat)(SIO *);           /*8  Pointer to receiver status       */
   FAST   (*s_read)(SIO *);            /*9  Pointer to fetch routine         */
   FAST   (*s_xstat)(SIO *);           /*10 Pointer to xmit status           */
   void   (*s_send)(SIO *, FAST);      /*11 Pointer to xmit function         */
   short  (*s_txblock)(SIO *, uint8_t*,short); /*12 "    block xmit function    */
   REG    (*v_regp)[2];                /*13 Virtual UART register            */
   uint16_t v_regpsize;                  /*14 Length of virtual array          */
   struct vregbits_ *par;              /*15 Pointer to parity struct         */
   struct vregbits_ *sb;               /*16 Pointer to stop bit struct       */
   struct vregbits_ *dl;               /*17 Pointer to data length struct    */
   struct vbaud_    *br;               /*18 Pointer to baud rate  struct     */
   struct vout232_  *rts;              /*19 Pointer to RTS struct            */
   struct vout232_  *dtr;              /*20 Pointer to DTR struct            */
   struct vout232_  *gpo1;             /*21 Pointer to GPOUTPUT1  struct     */
   struct vout232_  *gpo2;             /*22 Pointer to GPOOUTPUT2 struct     */
   struct vout232_  *brkbit;           /*23 Pointer to BREAK struct          */
   struct vin232_   *cts;              /*24 Pointer to  CTS struct           */
   struct vin232_   *dsr;              /*25 Pointer to  DSR struct           */
   struct vin232_   *dcd;              /*26 Pointer to  DCD struct           */
   struct vin232_   *ri;               /*27 Pointer to  RI struct            */
   struct vin232_   *gpi1;             /*28 Pointer to  GPINPUT1  struct     */
   struct vin232_   *gpi2;             /*29 Pointer to  GPINPUT2  struct     */
   FAST  (*read232)(SIO *, struct vin232_*); /*30 * to lev-1 fetch function  */
   union inbits_232 status;            /*31 See if any RS-232 inputs         */
   union inbits_232 delta;             /*32 Changed since last read          */
   struct vregbits_  *txenable;        /*33  "  xmitter enable struct        */
   struct vregbits_  *rxenable;        /*34  "  receiver enable struct       */
   struct vregbits_  *ctshs;           /*35  "  cts handshake on xmitter     */
   struct vregbits_  *dcdhs;           /*36  "  dcd handshake on rcvr        */
   struct vregbits_  *clkf;            /*37  "  clock factor struct          */
   uint16_t flow_wanted;                 /*38 0 none,1 xon-xoff, 2 RTS/CTS     */
   uint16_t tx_vflowstate;               /*39 State of virtual xmit flow ctrl  */
   uint16_t rcv_vflowstate;              /*40 State of virtual rcv    "    "   */
   uint16_t tx_iflowstate;               /*41 State of interrupt xmit "    "   */
   uint16_t rcv_iflowstate;              /*42 State of interrupt rcv  "    "   */
   uint16_t (*getflow_req)(SIO *,...);   /*43 pointer to flow-status routine   */
   void   (*flowon)(SIO *);            /*44 pointer to flow-off routine      */
   void   (*flowoff)(SIO *);           /*45 pointer to flow-on routine       */
   short  devnum;                      /*46 s_opened device number           */
   struct soctl_    *s_octl;           /*47 Pointer to output struct         */
   struct sictl_    *s_ictl;           /*48 Pointer to input  struct         */
   struct                              /*49 Interrupt status bitfield        */
     {
     unsigned int rcv_wanted     :1;   /* Are interrupts desired?            */
     unsigned int tx_wanted      :1;
     unsigned int rs232_wanted   :1;
     unsigned int serr_wanted    :1;
     unsigned int rcv_on         :1;   /* Are interrupts on?                 */
     unsigned int tx_on          :1;
     unsigned int rs232_on       :1;
     unsigned int serr_on        :1;
     unsigned int reserved       :8;
     } intrpt_status;

//TODO   void (*isr[NUM_INTRPT])(SIO * siop);/*50 Array of sub-handlers vectors    */
   void   (*old_isr_232)(SIO *);       /*51 Pointer to saved: rs232 ISR      */
   void   (*old_isr_serr)(SIO *);      /*52  : serial error ISR              */
   void   (*old_isr_rcv)(SIO *);       /*53  : rcv ISR                       */
   void   (*old_isr_tx)(SIO *);        /*54  : xmit ISR                      */

   union                               /*55  : serialization errors          */
         {
         REG       s_errors;           /* The raw bit-map                    */
         struct                        /* Individual bits                    */
            {
            unsigned  overrun : 1;     /* overrun error flag                 */
            unsigned  parity  : 1;     /* parity error flag                  */
            unsigned  frame   : 1;     /* framing error flag                 */
            unsigned  Break   : 1;     /* break error flag                   */
            unsigned  reserved: 12;
            } bitmap;              
         } serr;                   
   short  rcv_buffsize;                /*56 Size of the rxrdy buffer         */
   short  rcv_fifo_depth;              /*57 Size UART's receive FIFO         */
   short  rcv_fifo_trigger;            /*58 Receive FIFO Trigger Level       */
   FAST   *rcv_buff;                   /*59 Pointer to receive buffer        */
   FAST   *rcv_buffend;                /*60 Pointer to end of  "             */
   FAST   *rcv_headp;                  /*61 Where to put next uint8_t           */
   FAST   *rcv_tailp;                  /*62 Where to fetch next uint8_t         */
   short  tx_fifo_depth;               /*63 Size of UART's xmit FIFO         */
   short  tx_fifo_trigger;             /*64 Trasmit FIFO Trigger Level       */
   short  tx_numbuffs;                 /*65 Number of xmit buffers           */
   short  tx_buffsize;                 /*66 Size of each xmit buffer         */
   struct tx_queue *tx_list;           /*67 The circular queue               */
   struct tx_queue *tx_headp;          /*68 Input to tx queue                */
   struct tx_queue *tx_tailp;          /*69 Output to tx queue               */
   struct tx_queue *tx_queue_end;      /*70 Pointer to last member   "       */
   FAST   tx_idle;                     /*71 Transmitter needs kickstart      */
   struct modem     *sm;               /*72 Pointer to modem struct          */
   };
#endif  /* _SIODEF_*/

