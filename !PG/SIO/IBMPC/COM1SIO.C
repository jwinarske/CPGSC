/** SERIAL PORT A     (COM1) ***/

/*
OBJECT NAME:  baselineA
       TYPE:  struct modem
      LEVEL:  0
 DEFINED IN:  MODEM.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  SIO control structure for baseline modem.
*/

struct modem baselineA =
     {
     0,                          /*0  Interbyte delay                     */
     OFF,                        /*1  Console echo off                    */
     "",                         /*2  Build all commands here             */
     _0_SEC_3,                   /*3  Tsecs to wait after a modem cmd     */
     2,                          /*4  Number of times to try a command    */
     _1_SEC_0  + _0_SEC_5,       /*5  Escape guard time (Tsecs)           */
     '|',                        /*6  (S2) online escape char             */
     {BAUD57K6, BAUD38K4, BAUD14K4,   /*7  Baud rates to try reset        */
     BAUD9600, BAUD2400,BAUD1200,-1},
     SUPPLIED,                   /*8  Baud rate at which reset occurred   */
     VIRGIN,                     /*9  Our own code for modem type         */
     SUPPLIED,                   /*10 Maximum baud rate of modem          */
     0,                          /*11 (S0) 0 = "Don't answer"             */
     2,                          /*12 (S6)dialtone wait  (secs)           */
     30,                         /*13 (S7) timeout wait for connect (secs)*/
     1,                          /*14 speaker mode arg: on till connect   */
     4,                          /*15 Result codes: highest level         */
     1,                          /*16 Speaker volume (1, 2, or 3)         */
     1,                          /*17 Enable DCD                          */
     2,                          /*18 Enable DTR                          */
     BAUD_FOUND,                 /*19 How to leave baud rate after reset  */
     FALSE,                      /*20 Modem sucessfully configured        */
     SUPPLIED,                   /*21 DTE baud rate (parsed from CONNECT) */
     SUPPLIED,                   /*22 Carrier rate (parsed from CARRIER)  */
     TRUE,                       /*23 Yes, link protocol wanted           */
     SUPPLIED,                   /*24 Link protocol supported?            */
     "",                         /*25 Name of link protocol               */
     TRUE,                       /*26 Yes, compression wanted             */
     SUPPLIED,                   /*27 Compression protocol supported?     */
     "",                         /*28 Name of compression protocol        */
     TRUE,                       /*29 Switch baud rate to incoming call   */
     "" ,                        /*30 Build numeric dial string here      */
     "",                         /*31 Valid chars in dial string          */
     'T',                        /*32 Tone dialing                        */
     ' ',                        /*33 No dial suffix                      */
     "Z",                        /*34 Unconfiguration string              */
     };

/*
OBJECT NAME:  baudA
       TYPE:  struct vbaud_
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  SIO control structure for baud rate.
*/

struct vbaud_ baudA =
     {
     VBAUDLO,                           /* Virtual register for lo byte      */
     VBAUDHI,                           /* Virtual register for hi byte      */
     0,                                 /* Offset of UART lsb baud reg       */
     1,                                 /* Offset of UART msb baud reg       */
     {
{BH_50,   BL_50   },  {BH_75,   BL_75   }, {BH_110,  BL_110  },
{BH_134,  BL_134  },  {BH_150,  BL_150  }, {BH_300,  BL_300  },
{BH_600,  BL_600  },  {BH_1200, BL_1200 }, {BH_1800, BL_1800 },
{BH_2000, BL_2000 },  {BH_2400, BL_2400 }, {BH_3600, BL_3600 },
{BH_4800, BL_4800 },  {BH_7200, BL_7200 }, {BH_9600, BL_9600 },
{BH_14K4, BL_14K4 },  {BH_19K2, BL_19K2 }, {BH_28K8, BL_28K8 },
{BH_38K4, BL_38K4 },  {BH_57K6, BL_57K6 },  {BH_115K2, BL_115K2 },
     },
     SUPPLIED,                          /* Rank of current divisior in table */
     BAUD2400                           /* Start at 1200 baud                */
     };

/*
OBJECT NAME:  ictlA
       TYPE:  struct sictl_
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  Declares and initializes an input control structure.
   COMMENTS:  The numbering in the comments correspond to those in the
              sictl_ structure definition.
*/
struct sictl_  ictlA=
     {
     OFF,                             /* 0  Timeout-on-input flag            */
     _0_SEC_05,                       /* 1  Default timeout in Tsecs         */
     OFF,                             /* 2  "raw" input flag                 */
     OFF,                             /* 3  Echo input back to sender flag   */
     ON,                              /* 4  Reset high bit flag              */
     NOXLAT,                          /* 5  End-of-line mode                 */
     OFF,                             /* 6  Console output flag              */
     UP_LOW,                          /* 7  Upper/lower case conversion mode */
     ON,                              /* 10 Remove unwanted controls flag    */
{NUL,BEL,BS,HT,LF,CR,FF,DC3,DC1,DOS_EOF},/* 11 permitted controls            */
     10,                              /* 12 Number of controls in above list */
     OFF,                             /* 13 Byte translation/removal mode    */
     {{'a','x'},{'b', -1 }},          /* 14 Translation/removal array        */
     2,                               /* 15 Number of entries in above array */
     SUPPLIED,                        /* 16 'last character' buffer          */
     SUPPLIED,                        /* 17 Eol readback flag                */
     SUPPLIED                         /* 18 Pending readback character       */
    };


/*
OBJECT NAME:  struct soctl_ octlA
       TYPE:  struct soctl_
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  Declares and initializes an output control structure.
   COMMENTS:  The numbering in the comments correspond to those in the
              soctl_ structure definition.
*/
struct soctl_ octlA =
     {
     OFF,                             /*0  "Raw" output flag                 */
     NOXLAT,                          /*1  End -of-line mode                 */
     OFF,                             /*2  Con sole output flag              */
     OFF,                             /*3  Echowait flag                     */
     _1_SEC_0 * 5,                    /*4  Echo-wait before timeout in Tsecs */
     UP_LOW,                          /*5  Upper/lower case conversion mode  */
     ON,                              /*9  Strip high bits flag              */
     ON,                              /*10 Remove unwanted controls flag     */
{NUL,BEL,BS,HT,LF,CR,FF,DC3,DC1,DOS_EOF},/*11 permitted controls             */
     10,                              /*12 Number of controls in above list  */
     OFF,                             /*13 Translation/removal flag          */
     {0},                             /*14 Translation/removal list          */
     0,                               /*15 No entries in above array         */
     OFF,                             /*16 No interbyte delay flag           */
     _0_SEC_05,                       /*17 Delay in Tsecs                    */
     OFF,                              /*18 end-of-line pause flag           */
     LF,                              /*19 Character to pause after          */
     _0_SEC_4,                        /*20 Pause in Tsecs                    */
     ESC,                             /*21 Keyboard abort character          */
     SUPPLIED,                        /*22 'last character' buffer           */
     SUPPLIED                         /*23 Flag to flush last character      */
     };


/*
OBJECT NAME:  v_regA
       TYPE:  Two-dimensional array of REG.
      LEVEL:  0
DECLARED IN:  IBMPC.C
DESCRIPTION:  Used for virtual UART registers
*/

REG v_regA[V_REG_SIZE][2]=
    {
/*  VIR   USR  */
     { 0,    0 },                         /* 0 = baud low byte               */
     { 0,    0 },                         /* 1 = baud high byte              */
     { 0,    0 },                         /* 2 = interrupt enable            */
     { 0,    0 },                         /* 3 = FIFO enable                 */
     { 0,    0 },                         /* 4 = data format                 */
     { 0,    0 },                         /* 5 = RS232 output control        */
    };

/*
OBJECT NAME:  pin4A
       TYPE:  vout232_ structure
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  Control structure for RS232 RTS output.
*/

struct vout232_ pin4A =
     {
     RTSMASK,                         /* AND mask to reset RTS bit           */
     VOUT232,                         /* Virtual register                    */
     OUT232,                          /* Offset of UART RTS register         */
     SUPPLIED,                        /* Code for current value (ON/OFF)     */
     OFF,                             /* Initialized value                   */
     };

/*
OBJECT NAME:  pin20A
       TYPE:  vout232_ structure
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  Control structure for RS232 DTR output.
*/

struct vout232_ pin20A =
     {
     DTRMASK,                         /* AND mask to reset DTR bit           */
     VOUT232,                         /* Virtual register                    */
     OUT232,                          /* Offset of DTR register in UART      */
     SUPPLIED,                        /* Code for current value (ON/OFF)     */
     OFF,                             /* Initialized value                   */
     };

/*
OBJECT NAME:  gp1outA
       TYPE:  vout232_ structure
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  Control structure for RS232 GPO1 output.
*/

struct vout232_ gp1outA =
    {
    GPO1MASK,                         /* AND mask to reset GPOUT1 bit        */
    VOUT232,                          /* Virtual register                    */
    OUT232,                           /* Offset of GPO1 register in UART     */
    SUPPLIED,                         /* Code for current value (ON/OFF)     */
    OFF,                              /* Initialized value                   */
    };

/*
OBJECT NAME:  gp2outA
       TYPE:  vout232_ structure
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
     MODULE:  IBMPC.C
DESCRIPTION:  Control structure for RS232 GPO2 output.
*/

struct vout232_ gp2outA =
    {
    GPO2MASK,                         /* AND mask to reset GPO2 bit          */
    VOUT232,                          /* Virtual register                    */
    OUT232,                           /* Offset of GPO2 register in UART     */
    SUPPLIED,                         /* Code for current value (ON/OFF)     */
    OFF,                              /* Initialized value                   */
    };

/*
OBJECT NAME:  breakbA
       TYPE:  vout232_ structure
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  Control structure for BREAK output.
*/

struct vout232_ breakbA =
     {
     BRK_MASK,                        /* AND mask to reset BREAK bit         */
     VFMT,                            /* Virtual register                    */
     FMT,                             /* Offset of GPO1 register in UART     */
     SUPPLIED,                        /* Code for current value (ON/OFF)     */
     OFF,                             /* Initialized value                   */
     };

/*
OBJECT NAME:  pin6A
       TYPE:  vin232_ structure
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  Control structure for RS232 DSR input.
*/

struct vin232_ pin6A =
     {
     STAT_232,                        /* Offset of DSR register in UART      */
     DSRMASK,                         /* AND mask for isolating DSR bits     */
     SUPPLIED,                        /* Current value of this input         */
     };

/*
OBJECT NAME:  pin5A
       TYPE:  vin232_ structure
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  Control structure for RS232 CTS input.
*/

struct vin232_ pin5A =
     {
     STAT_232,                        /* Offset of CTS register in UART      */
     CTSMASK,                         /* AND mask for isolating CTS bits     */
     SUPPLIED,                        /* Current value of this input         */
     };

/*
OBJECT NAME:  pin8A
       TYPE:  vin232_ structure
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  Control structure for RS232 DCD input.
*/

struct vin232_ pin8A =
     {
     STAT_232,                        /* Offset of DCD register in UART      */
     DCDMASK,                         /* AND mask for isolating DCD bits     */
     SUPPLIED,                        /* Current value of this input         */
     };

/*
OBJECT NAME:  pin22A
       TYPE:  vin232_ structure
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  Control structure for RS232 RI input.
*/

struct vin232_ pin22A =
     {
     STAT_232,                        /* Offset of RI register in UART       */
     RIMASK,                          /* AND mask for isolating RI bits      */
     SUPPLIED,                        /* Current value of this input         */
     };

/*
OBJECT NAME:  parityA
       TYPE:  vregbits structure
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  Control structure for parity.
*/

struct vregbits_ parityA =
     {
     PARITYMASK,               /* AND mask to isolate parity bits            */
     { NONE_MASK, ODD_MASK, EVEN_MASK, MARK_MASK, SPACE_MASK },  /* OR masks */
     VFMT,                     /* Virtual register--rank in v_rega           */
     FMT,                      /* Offset of physical register from uart_base */
     SUPPLIED,                 /* Rank in mask table of current setting      */
     NONE,                     /* Rank to use in initialization              */
     NIL                       /* No more structures for parity              */
     };

/*
OBJECT NAME:  stopsA
       TYPE:  vregbits structure
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  Control structure for stop bits.
*/
struct vregbits_ stopsA =          /* for 16x50 UART */
       {
        STOPMASK,              /* AND mask to isolate stop-bit bits          */
        { ONE_MASK, ONE_5_MASK, TWO_MASK, -1, -1 },
        VFMT,                  /* virtual register--rank in v_rega           */
        FMT,                   /* offset of physical register from uart_base */
        SUPPLIED,              /* rank in mask table of current setting      */
        STOP1,                 /* rank to use in initialization              */
        NIL                    /* no more structures for stop bits           */
      };

/*
OBJECT NAME:  dlenA
       TYPE:  vregbits structure
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
DESCRIPTION:  Control structure for data length.
*/

struct vregbits_ dlenA =           /* for 16x50 UART */
     {
     DLMASK,                   /* AND mask to isolate data length bits       */
     { DL5_MASK, DL6_MASK, DL7_MASK, DL8_MASK, -1 },
     VFMT,                     /* virtual register--rank in v_rega           */
     FMT,                      /* offset of physical register from uart_base */
     SUPPLIED,                 /* rank in mask table of current setting      */
     DL8,                      /* rank to use in initialization              */
     NIL                       /* no more structures for parity              */
     };

/*
   SIO NAME:  COM1sio
       FILE:  IBMPC.C
      LEVEL:  0
 DEFINED IN:  SIODEF.H
DECLARED IN:  IBMPC.C
   COMMENTS:  The main SIO structure for COM 1 (device 0).
              Line numbers in comments are for reference only.
*/

SIO COM1sio  =
     {
     COM1,                         /*0  Base address of UART                 */
     DATA_IO,                      /*1  Offset of data port from base        */
     SER_STAT,                     /*2  Offset of status port from base      */
     RCV_MASK,                     /*3  RxRDY mask from UART.H               */
     XMIT_MASK,                    /*4  Xmitter Holding Register Empty mask  */
     TX_EMPTY_MASK,                /*5  Xmitter Shift Register Empty mask    */
     _a_inport,                    /*6  Pointer to RAM/port read routine     */
     _a_outport,                   /*7  Pointer to RAM/port read routine     */
     s_rcvstat,                    /*8  Pointer to receiver status           */
     s_rcv,                        /*9  Pointer to fetch routine             */
     s_xmitstat,                   /*10 Pointer to xmiter status             */
     s_xmit,                       /*11 Pointer to xmit routine              */
     tx_write,                     /*12 Pointer to polled block xmit routine */
     v_regA,                       /*13 Pointer to virtual register array    */
     V_REG_SIZE,                   /*14 Number of rows in virtual array      */
     &parityA,                     /*15 Parity structure                     */
     &stopsA,                      /*16 Stop bit structure                   */
     &dlenA,                       /*17 Data length structure                */
     &baudA,                       /*18 Baud rate structure                  */
     &pin4A,                       /*19 RS-232 RTS output                    */
     &pin20A,                      /*20 RS-232 DTR output                    */
     &gp1outA,                     /*21 RS-232 first user-defined output     */
     &gp2outA,                     /*22 RS-232 first user-defined output     */
     &breakbA,                     /*23 Break bit                            */
     &pin5A,                       /*24 RS-232 CTS input                     */
     &pin6A,                       /*25 RS-232 DSR input                     */
     &pin8A,                       /*26 RS-232 DCD input                     */
     &pin22A,                      /*27 RS-232 RI  input                     */
     NIL,                          /*28 NO 1st user-defined RS-232 input     */
     NIL,                          /*29 NO 2nd user-defined RS-232 input     */
     _vstat232,                    /*30 * to level one fetch function        */
     0,                            /*31 RS-232 status bits                   */
     0,                            /*32 RS-232 delta bits                    */
     NIL,                          /*33 NO transmitter-on structure          */
     NIL,                          /*34 NO receiver-on structure             */
     NIL,                          /*35 NO transmitter/RTS handshake         */
     NIL,                          /*36 NO receiver/DCD handshake            */
     NIL,                          /*37 NO clock factor                      */
     XON_XOFF,                     /*38 State of virtual xmit flow control   */
     FLOW_ON,                      /*39 State of virtual xmit flow control   */
     FLOW_ON,                      /*40 State of virtual rcv    "    "       */
     FLOW_ON,                      /*41 State of interrupt xmit "    "       */
     FLOW_ON,                      /*42 State of interrupt rcv  "    "       */
     flow_req_xoxo,                /*43 Pointer to flow-request routine      */
     xon,                          /*44 Pointer to flow-off routine          */
     xoff,                         /*45 Pointer to flow-on routine           */
     SUPPLIED,                     /*46 Device number supplied during open   */
     &octlA,                       /*47 Pointer to output control structure  */
     &ictlA,                       /*48 Pointer input control structure      */
     {TRUE,TRUE,TRUE,TRUE,0,0,0,0},/*49 Interrupts wanted/on bitfield        */
//     {TRUE,TRUE,FALSE,FALSE,0,0,0,0},/*49 Interrupts wanted/on bitfield        */
     {                             /*50 UART Interrupt vectors (s_iadmin)    */
         isr_stat232_dummy,        /*--   index 0 = RS232 input status       */
         isr_tx_dummy,             /*--   index 1 = transmit hold reg empty  */
         isr_rcv_dummy,            /*--   index 2 = received data ready      */
         isr_serr_dummy,           /*--   index 3 = serialization error      */
         isr_rcv_dummy,            /*--   index 4 = unused                   */
         isr_rcv_dummy,            /*--   index 5 = unused                   */
         isr_rcv_dummy             /*--   index 6 = receiver FIFO timeout    */
     },
     NIL,                          /*51 Pointer to old rs232 isr             */
     NIL,                          /*52 Pointer to old ser  error isr        */
     NIL,                          /*53 Pointer to old rcv interrupt handler */
     NIL,                          /*54 Pointer to old xmit interrupt handler*/
     0,                            /*55 Serialization union                  */
     RCV_BUFSIZ,                   /*56 Size of receive interrupt buffer     */
     SUPPLIED,                     /*57 Size of UART's Receive FIFO          */
     SUPPLIED,                     /*58 Receive FIFO Trigger Level           */
     NIL,                          /*59 Pointer to receive buffer            */
     NIL,                          /*60 Pointer to end of  "        "        */
     NIL,                          /*61 Where in buff to put next byte       */
     NIL,                          /*62 Where in buff to fetch next byte     */
     SUPPLIED,                     /*63 Size of UART's Transmit FIFO         */
     SUPPLIED,                     /*64 Transmit FIFO Trigger Level          */
     SUPPLIED,                     /*65 Number of transmit buffers           */
     SUPPLIED,                     /*66 Transmit buffer size                 */
     NIL,                          /*67 Pointer to transmit interrupt queue  */
     NIL,                          /*68 Pointer to tx queue headp            */
     NIL,                          /*69 Pointer to tx queue tailp            */
     NIL,                          /*70 Pointer to last element in tx queue  */
     FALSE,                        /*71 Transmit queue empty                 */
     &baselineA,                   /*72 Modem control strucutre              */
     };

