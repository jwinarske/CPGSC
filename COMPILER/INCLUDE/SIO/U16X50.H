#ifndef  _U16x50_
#define  _U16x50_

/**** FUNCTION PROTOTYPES ****/
void isr_tx(SIO *);               /* transmit interrupt handler      */
void isr_stat232(SIO *);          /* RS232 interrupt handler         */
void isr_serr(SIO *);	          /* Serialization interrupt handler */
void isr_rcv450(SIO *);           /* Receive data interrupt handler  */
void isr_rcv450_xoxo(SIO *);      /* XON/XOFF "     "        "       */
void isr_rcv450_rcts(SIO *);      /* RTS/CTS  "     "        "       */
void isr_rcv550(SIO *);           /* Receive data interrupt handler  */
void isr_tx_dummy(SIO *);         /* transmit interrupt handler      */
void isr_stat232_dummy(SIO *);    /* RS232 interrupt handler         */
void isr_serr_dummy(SIO *);       /* Serialization interrupt handler */
void isr_rcv_dummy(SIO *);        /* Receive data interrupt handler  */
void s_iadmin(SIO *);
void s_config(SIO *);
void s_restore(SIO *);
void u_intrpt_mgr(SIO*, short, BOOL);
void _vset232(SIO *,struct vout232_ *, REG);
void _vsetbr(SIO *,struct vbaud_ *, REG, REG);
FAST _vstat232(SIO *,struct vin232_ *);
void _vsetbits(SIO *,struct vregbits_ *, REG);
void (*s_revector(SIO *, USHORT, void (*)(SIO *) )) (SIO*);

/*** Offsets of 16x50 Registers ***/
#define DATA_IO         0   /* Data read and write                          */
#define INT_EN          1   /* Interrupt enable  (IER)                      */
#define INT_ID          2   /* Interrrupt identification (read-only)        */
#define FIFO            2   /* Interrrupt identification (write-only 16550) */
#define FMT             3   /* Data format (LCR)                            */
#define DLAB            3   /* Register containing DLAB bit                 */
#define OUT232          4   /* RS232 control (MCR)                          */
#define SER_STAT        5   /* Serialization status register (LSR)          */
#define STAT_232        6   /* RS232 status (MSR)                           */

#define BAUDLO          0   /* LSB of the baud rate divisor                 */
#define BAUDHI          1   /* MSB of the baud rate divisor                 */

/*** Rows in the Virtual Register Array ***/
enum vir_row {
    	VBAUDLO = 0,           /* lo byte of baud rate register       */
        VBAUDHI,               /* hi byte of baud rate register       */
        VINT_EN,               /* interrupt enable register           */
        VFIFO,                 /* FIFO register                       */
        VFMT,                  /* Data format register                */
        VOUT232,               /* RS-232 outpu register               */
        V_REG_SIZE             /* number of elements in virtual array */
        };

/***************************
* Constants for Interrupts *
****************************/

/* Bit masks for Interrupt Enable register */

#define I_RXRDY    0x1
#define I_THRE     0x2         /* Values may be compounded....        */
#define I_SERERR   0x4         /* e.g., I_RXRDY + I_THRE              */
#define I_RS232    0x8

#define INT_ID_MASK   0x0F    /* Only bits 0, 1,2,&3 needed after shift  */

/* Index number for interrupts */
enum {
     INDEX_RS232 =  0,
     INDEX_THRE,
     INDEX_RXRDY,
     INDEX_SERERR,
     INDEX_UNUSED1,
     INDEX_UNUSED2,
     INDEX_RXTIMEOUT,          /* when recevier FIFO times out unfull */
     NUM_INTRPT           /* This is dimensions isr array in SIODEF.H */
     };

/* Receiver's FIFO Trigger Depth */

#define TRIG_1  0x01
#define TRIG_4  0x41
#define TRIG_8  0x81
#define TRIG_16 0xC1

/*** Bit Masks for Transmit/Receive Status ***/
#define  RCV_MASK       0x01     /* 00000001 received byte ready      */
#define  XMIT_MASK      0x20     /* 00000010 transmitter buffer clear */
#define  TX_EMPTY_MASK  0x40     /* 00000100 shift register clear     */

#define s_txempty(x) (*(x)->readbyte)((x)->uart_base+(x)->status_off)&(x)->tx_emptymask

/*** Bit Masks for Data Length ***/
#define  DLMASK         0xFC    /* AND mask 11111100 */
#define  DL5_MASK       0x00    /* OR mask 00000000  */
#define  DL6_MASK       0x01    /* OR mask 00000001  */
#define  DL7_MASK       0x02    /* OR mask 00000010  */
#define  DL8_MASK       0x03    /* OR mask 00000011  */

/*** Bit Masks for Stop Bits ***/
#define  STOPMASK       0xFB    /* AND mask 11111011 */
#define  ONE_MASK       0x00    /* OR mask 00000000  */
#define  ONE_5_MASK     0x04    /* OR mask 00000100  */
#define  TWO_MASK       0x04    /* OR mask 00000100  */

/***Bit Masks for Parity Bits ***/
#define  PARITYMASK     0xC7    /* AND MASK 11000111 */
#define  NONE_MASK      0x00    /* OR mask 00000000  */
#define  ODD_MASK       0x08    /* OR mask 00001000  */
#define  EVEN_MASK      0x18    /* OR mask 00011000  */
#define  MARK_MASK      0x28    /* OR mask 00101000  */
#define  SPACE_MASK     0x38    /* OR mask 00111000  */

/*** Bit Masks for BREAK Bits ***/
#define  BRK_MASK       0xBF    /* AND mask 10111111 */
#define  BRKON_MASK     0x40    /* OR mask  01000000 */
#define  BRKOFF_MASK    0x00

/*** Bit Masks for RS232 Inputs ***/
#define  CTSMASK        0x10       /* 00010000 */
#define  DSRMASK        0x20       /* 00100000 */
#define  RIMASK         0x40       /* 01000000 */
#define  DCDMASK        0x80       /* 10000000 */

/*** Bit Masks for RS232 Outputs ***/
#define  DTRMASK        0xFE       /* 11111110 */
#define  RTSMASK        0xFD       /* 11111101 */
#define  GPO1MASK       0xFB       /* 11111011 */
#define  GPO2MASK       0xF7       /* 11110111 */

/*** Masks for Baud Rate Divisior Registers ***/
#define  BH_50          0x09
#define  BL_50          0x00
#define  BH_75          0x06
#define  BL_75          0x00
#define  BH_110         0x04
#define  BL_110         0x17
#define  BH_134         0x03
#define  BL_134         0x59
#define  BH_150         0x03
#define  BL_150         0x00
#define  BH_300         0x01
#define  BL_300         0x80
#define  BH_600         0x00
#define  BL_600         0xC0
#define  BH_1200        0x00
#define  BL_1200        0x60
#define  BH_1800        0x00
#define  BL_1800        0x40
#define  BH_2000        0x00
#define  BL_2000        0x3A
#define  BH_2400        0x00
#define  BL_2400        0x30
#define  BH_3600        0x00
#define  BL_3600        0x20
#define  BH_4800        0x00
#define  BL_4800        0x18
#define  BH_7200        0x00
#define  BL_7200        0x10
#define  BH_9600        0x00
#define  BL_9600        0x0C
#define  BH_14K4        0x00
#define  BL_14K4        0x08
#define  BH_19K2        0x00
#define  BL_19K2        0x06
#define  BH_28K8        0x00
#define  BL_28K8        0x04
#define  BH_38K4        0x00
#define  BL_38K4        0x03
#define  BH_57K6        0x00
#define  BL_57K6        0x02
#define  BH_115K2       0x00
#define  BL_115K2       0x01

#endif  /* _U16x50_*/
