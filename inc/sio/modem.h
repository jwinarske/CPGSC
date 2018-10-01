#ifndef  _MODEM_
#define  _MODEM_

/*
STRUCT NAME:  parse_info
HEADER FILE:  MODEM.H
DESCRIPTION:  Control structure used by modem message parser.
   COMMENTS:
*/
struct parse_info
     {
     char *message;                       /* pointer to the modem response */
     bool terminal;                       /* is it "terminal"              */
     short id;                            /* id code for this message      */
     void (*fn)(SIO *, struct parse_info *, char *);  /* function to process reply */
     };

/**** FUNCTION PROTOTYPES ****/
int   m_answer(SIO *);
void  m_cmd(SIO *, char *);
int   m_config(SIO *);
int   m_protoconfig(SIO *siop);
void  m_echo(SIO *, bool);
int   m_dial(SIO *,char *);
//int   m_getint(SIO *,char *);       /* obsolete */
int   m_hup(SIO *);
int   m_ismessage(SIO*, char *);
void  m_parsemsg(SIO *, struct parse_info *, char *);
int   m_cmd_OK(SIO *,char *);
short m_cmd_str(SIO *, char *, char *, uint16_t);
short m_getstr(SIO *, char *, short);
int   m_redial(SIO *);
int   m_reset(SIO *);
short m_unconfig(SIO *);
int   m_wait4dcd(SIO *);
short m_warndcd(SIO *, bool);
int   m_whoru(SIO *);
int   m_gocmd(SIO *, int);

/****** Modem "types" ******/
enum m_types{
              ID_UNKNOWN= 0,   /* Unable to identify modem   */
              ID_12,           /* Likely 1200 bps modem      */
              ID_12PLUS, 	   /* 1200 bps modem             */
              ID_24,           /* 2400 bps modem             */
              ID_96 ,          /* 9600 bps modem             */
              ID_14K4          /* 14,400 bps modem           */
              };

/****** Function Return Codes ******/
#define  M_SUCCEED    0        /* all modem functions return 0 if successful */
#define  M_FAIL       1        /* most return 1 if unsuccessful              */

/****** Constants for message validation ******/
#define MSG_INVALID          -1
#define MSG_NON_TERMINAL     -2


/****** Buffer Size Constants ******/
#define  MAX_MSG_LEN  30       /* max length of a modem message              */
#define  COMPRESSSIZE 20       /* max length of compression message          */
#define  LPSIZE       20       /* max length of protocol message             */

/****** Manifest Constants for Modem Functions ******/

enum results
{
M_OK = 0,          /*0  Successful command                          */
M_CONN,            /*1  Connect                                     */
M_RING,            /*2  Call incoming                               */
M_NODCD,           /*3  No carrier detected                         */
M_CMDERR,          /*4  Error in modem command                      */
M_NOTONE,          /*5  No dial tone heard                          */
M_BUSY,            /*6  Busy signal heard                           */
M_NOANSW,          /*7  Silence not heard after @                   */
M_BADMSG,          /*8  Invalid modem response                      */
M_NORING,          /*9  Looked for and didn't hear incoming'RING'   */
M_ONLINE,          /*10 Can't dial into a high dcd                  */
M_NILNUM,          /*11 Blank dial string                           */
M_USRCAN,          /*12 Call cancelled from keyboard                */
M_NORESET,         /*13 Reset Failed                                */
M_NOID,            /*14 ID function failed                          */
M_CONFIG_MEM,      /*15 Configuration memeory alloc error           */
M_CONFIG_NOK,      /*16 Modem didn't configure as requested         */
M_DCD_HIGH,        /*17 DCD went high (not a message)               */
M_PROTOCOL,        /*18 Protocol message detected during connect    */
M_CARRIER,         /*19 Carrier message detected during connect     */
M_COMPRESS,        /*20 Compression message detected during connect */
};

/****** How to configure Baud Rate ******/

enum baudcnfg {  BAUD_MAX = 0, BAUD_FOUND};

struct modem
   {
   unsigned ibdelay;              /*0  Interuint8_t delay                     */
   bool     cmdechoflag;          /*1  Modem commands to console           */
   char     cmdbuff[CMDBUFSIZ];   /*2  Build all commands here             */
   int      cmdt_out;             /*3  Tsecs to wait after a modem cmd     */
   int      cmdretry;             /*4  Number of times to try a command    */
   unsigned guardtime;            /*5  Escape guard time                   */
   short    escape_arg;           /*6  (S2)on-line to command mode escape  */
   int      baudtry[7];           /*7  Baud rates to try reset             */
   unsigned max_DTE_baud;         /*8  Maximum baud rate of modem          */
   short    modtype;              /*9  Our code for modem                  */
   short    max_carrier_speed;    /*10 Maximum baud rate of modem          */
   short    autoans_arg;          /*11 (S0)# of rings before autoanswer    */
   short    dtwait_arg;           /*12 (S6)dialtone wait (secs)            */
   short    dcdwait_arg;          /*13 (S7)# secs to wait for carrier      */
   short    speaker_arg;          /*14 Speaker mode                        */
   short    xcmd_arg;             /*15 Result code set                     */
   short    speakvol_arg;         /*16 Speaker volume (0,  1, or 2)        */
   short    firmdcd_arg;          /*17 DCD configuration                   */
   short    firmdtr_arg;          /*18 DTR configuration                   */
   short    baudmode;             /*19 Baud rate initialization mode       */
   bool     configokflag;         /*20 Modem successfully configured       */
   short    connect_XXXX_code;    /*21 Code for baud rate of local link    */
   short    carrier_baud_code;    /*22 Code for baud rate of carrier       */
   bool     linkprot_wanted;      /*23 Want link protocol if available?    */
   bool     linkprot_supported;   /*24 Is a link protocol supported?       */
   char     linkname [LPSIZE];    /*25 ID from the CONNECT message         */
   bool     compress_wanted;      /*26 Want compression if available?      */
   bool     compress_supported;   /*27 Is compression supported? (at init) */
   char compressname[COMPRESSSIZE];     /*28 ID from COMPRESSION message   */
   bool     autobrflag;           /*29 Switch baud rate to incoming call   */
   char     dialbuff[CMDBUFSIZ];  /*30 Build numeric dial string here      */
   char     okalpha[18];          /*31 Alpha chars ok in dial string       */
   char     dialmode;             /*32 (T)one or (P)ulse dialling          */
   char     enddial;              /*33 Dial suffix--e.g.,  ';' or 'R'      */
   char     unconfig[CMDBUFSIZ];  /*34 String to send to smodem at exit    */
};

#endif      /*_MODEM_ */

