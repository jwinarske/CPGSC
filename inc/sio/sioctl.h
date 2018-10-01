#ifndef  _SIOCTL_
#define  _SIOCTL_

/* MACROS FOR CALLING FLOW CONTROL POINTERS IN SIO*/
#define flowon(p)      (*(p)->flowon)((p))
#define flowoff(p)     (*(p)->flowoff)((p))
#define getflow_req(p) (*(p)->getflow_req)((p))

/* TYPES OF FLOW CONTROL */

enum flowtypes{ NO_FLOW = 0, XON_XOFF, RTS_CTS };

#define XON 		0x11      /* DC1                              */
#define XOFF 		0x13      /* DC3                              */

/* VALUES RETURNED BY GET-FLOW-REQUEST FUNCTION */
#define FLOW_OFF 	0
#define FLOW_NONE 	1
#define FLOW_ON 	0xFFFF    /* this must be 0xFFFF              */

/*END  FOR CHAPTER 16 */

#ifdef DEBUG_IBUFF
#define FLOW_HEADROOM 3
#define FLOW_TAILROOM FLOW_HEADROOM 
#else
#define FLOW_HEADROOM 10   
#define FLOW_TAILROOM FLOW_HEADROOM 
#endif

#define IO_STKSIZ  10         /* Size of I/O push/pop stack       */
int    s_ocntrl(SIO *,short, short, uint16_t);
int    s_icntrl(SIO *, short, short,...);
#define NOT_READY -1
#define IGNORE    -2
#define NOECHO     1

/* Constants for formatted output */
enum ioctl
    {
    NOXLAT = 0,          /* remove nothing--i.e., "raw"           */
    LF2CR,               /* translate LF to CR                    */
    CR2LF,               /* translate CR to LF                    */
    EOL2SPACE,           /* rconvert CR&LF to spaces              */
    REMOVEEOL,           /* remove all CR and LF                  */
    LF2CRLF,             /* convert LF to CRLF                    */
    CR2CRLF,             /* convert CR to CRLF                    */
    CRLF2LF,             /* convert CRLF to LF                    */
    CRLF2CR,             /* convert CRLF to CR                    */
    };

            /* UPPER/LOWER CASE MODES */
#define  UP_LOW    0     /* upper and lower--i.e., "raw"          */
#define  UPPER     1     /* convert to upper                      */
#define  LOWER     2     /* convert to lower                      */

            /* "function" codes */

/* "FUNCTION" ARGUMENTS FOR USE WITH I/O CONTROL FUNCTIONS  */
#define   SET        0
#define   GET        1

/* CONTROL ARGUMENTS FOR USE WITH I/O CONTROL FUNCTIONS     */

           /** FLAGS **/
enum ctlargs
    {
    RAWFLAG = 0,         /*  Minimum processing                   */
    T_OUTFLAG,           /*  Used for formatted input only        */
    EKOBAKFLAG,          /*  Used for formatted input only        */
    WECHOFLAG,           /*  Wait-for-echo flag                   */
    CONSFLAG,            /*  Console   output flag                */
    ASCIIFLAG,           /*  Remove high bit flag (&0x7f)         */
    CNTRLFLAG,           /*  Remove selected controls flag        */
    FILTERFLAG,          /*  Filter unwanted charcters flag       */
    IB_DLYFLAG,          /*  Interuint8_t delay flag (output only)   */
    IL_DLYFLAG ,         /*  Interline delay flag (output only)   */
                         /**           DELAYS                    **/
    WECHO_DLY,           /*  Echo-wait delay (in tsecs)           */
    IB_DLY,              /*  Interuint8_t delay (in tsecs)           */
    IL_DLY,              /*  Interline delay (in tsecs)           */
    T_OUT,               /*  Timeout   on input only (in tsecs)   */
                         /**         MODES                       **/
    EOLMODE,             /*  End-of-line mode argument            */
    CASEMODE,            /*  Upper/lower mode argument            */
    XXMODE,              /*  Xoff mode argument                   */
                         /**        DEFINED CHARACTERS           **/
    XOFFC,               /*  Character defined as XOFF            */
    XONC,                /*  Character defined as XON             */
    IL_DLYC,             /*  Character to trigger interline delay */
    KBORTC,              /*  Keyboard abort character             */
    };

#endif		/* _SIOCTL_ */

