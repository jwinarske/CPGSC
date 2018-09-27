#define DEBUG_MODEM        /*//*/
/*

PROGRAM NAME:  TERM7
 DESCRIPTION: Terminal program.
    COMMENTS: New Features:  XMODEM file transfers

*/
#include <malloc.h> /*//*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include <sio\siodef.h>
#include <sio\ascii.h>
#include <sio\misc.h>
#include <sio\sioctl.h>
#include <sio\buos.h>
#include <sio\key.h>
#include <sio\term.h>
#include <sio\xmod.h>
#include <sio\modem.h>
#include <sio\level0.h>        /*//*/

#define MENU         CTRL_A             /* Command summary                */
#define FORMAT       'A'                /* Setup serial parmeters         */
#define RS_232       'B'                /* RS-232 output control          */
#define BRAKE        'C'                /* Send BREAK signal              */
#define UPLOAD       'D'                /* Transmit file                  */
#define DNLOAD1      'E'                /* Download with C's buffer       */
#define DNLOAD2      'F'                /* Download with local buffer     */
#define UART_ID      'G'                /* 16450 (8250) or 16550          */
#define DIAL         'H'                /* Dial phone number              */
#define REDIAL       'I'                /* Redial previous number         */
#define ANSWER       'J'                /* Answer phone phone             */
#define HUP          'K'                /* Hang up phone                  */
#define BASELINE_CFG 'L'                /* Configure base line modem      */
#define PROTO_CFG    'M'                /* Configure protocol modem       */
#define XSEND        'N'                /* Send file with XMODEM protocol */
#define XRECV        'O'                /* Xmit file with XMODEM protocol */
#define EXIT         'Q'                /* Exit from term                 */


int vers = 7;                           /* version number (global)       */


extern int s_errno;
extern char *errstr[],  *brstr[];
extern char *m_codes[];                /* modem id strings                */


void baseline_cfg(SIO* siop)
{
     struct modem *smp;
     short errcode;
     smp = siop->sm;
     s_ipush(siop);                     /* save both control structures      */
#ifdef DEBUG_MODEM       /*//*/
     siop->sm->cmdechoflag = TRUE;        /*//*/
     s_icntrl(siop, SET, CONSFLAG, ON);  /* console echo on */   /*//*/
#else /*//*/
     s_icntrl(siop, SET, CONSFLAG, OFF);  /* console echo off  */
#endif      /*//*/
     putchar('\n');
     if ( ( errcode = m_reset(siop)) != M_SUCCEED)
          printf("%s.  (%d)\n",m_codes[errcode], errcode);
     else if ( (errcode = m_whoru(siop)) != M_SUCCEED)
          printf("%s.  (%d)\n",m_codes[errcode], errcode);
     else if ( (errcode = m_config(siop)) != M_SUCCEED)
          printf("%s.  (%d)\n",m_codes[errcode], errcode);
     else
          {
          printf("\nFound %s bps modem (id = %d) at %s baud. " \
            "Baud rate now set to %s\n", brstr[smp->max_carrier_speed],
            smp->modtype, brstr[smp->max_DTE_baud], brstr[getbaud(siop)]);
          }
     s_ipop(siop);                     /* restore control structure */
}

void proto_cfg(SIO* siop)
{
     short errcode;
     struct modem *smp = siop->sm;
     s_ipush(siop);
#ifdef DEBUG_MODEM                        /*//*/
     siop->sm->cmdechoflag = TRUE;        /*//*/
     s_icntrl(siop, SET, CONSFLAG, ON);  /* console echo on */ /*//*/
#else /*//*/
     s_icntrl(siop, SET, CONSFLAG, OFF);  /* console echo off  */   /*//*/
#endif     /*//*/
     s_ipop(siop);
     putchar('\n');
     if ( (errcode = m_protoconfig(siop)) != M_SUCCEED)
          printf("%s.  (%d)\n",m_codes[errcode], errcode);
}



int menu(siop)          /* menu now gets SIO pointer         */
SIO *siop;
{
     int c;
     int retval = 0;
     static char *menus[] =
          {
          "\tA.  Data Format, Baud rate",
          "\tB.  RS-232 control",
          "\tC.  Transmit BREAK signal",
          "\tD.  Upload Text File",
          "\tE.  Download Text File (small buffer)",
          "\tF.  Download Text File (large buffer)",
          "\tG.  Identify the UART",
          "\tH.  Dial a phone number",
          "\tI.  Redial last phone number",
          "\tJ.  Answer incoming call",
          "\tK.  Hang up phone",
          "\tL.  Attempt to configure baseline modem",
          "\tM.  Attempt to configure protocol modem",
          "\tN.  Send a file using XMODEM protocol",
          "\tO.  Receive a file using XMODEM protocol",
          "\tQ.  EXIT",
          ""                            /* NUL string terminates list       */
          };
     char ** menup;
     c = !EXIT;
     while (c != EXIT)
          {
          puts("\n\n");
          for (menup = menus; **menup != NUL ; menup++)
               printf("%s\n", *menup);
          printf("\n\t\t  Enter selection  (CR to quit menu) :  ");
          if ( (c = getkbch()) == CR)
               break;               /* return to term */
          c = toupper(c);
          switch (c)
               {
               case EXIT:             /* all done */
					retval = 1; break;     /*//*/
                    if (m_warndcd(siop, OFF) == 0)
                        {
                        m_hup(siop);   /* hang up */
                        if (siop->sm->configokflag == TRUE)
                           {   /* "unconfig" modem */
                           siop->sm->configokflag = FALSE;
                           m_cmd_OK(siop, siop->sm->unconfig);
                           }
                        retval = 1;
                        }
                     else
                        {
                        printf("Continuing in terminal\n");
                        retval = 0;
                        }
                    break;
               case FORMAT:            /* Data format, Baud rate           */
                    set_params(siop);
                    break;
               case RS_232:                   /* RS-232 output control              */
                    setup232(siop);
                    break;
               case BRAKE:                     /* send BREAK                        */
                    set232(siop, BRK, ON);
                    break;
               case UPLOAD:                   /* transmit a disk file         */
                    upload(siop);
                    haktc();
                    break;
               case DNLOAD1:           /* receive a file: use C's file buffer */
                    dnload(siop, cbuff);
                    break;
               case DNLOAD2:         /* receive a file: use local file buffer */
                    dnload(siop, locbuff);
                    break;
               case DIAL:
                    s_icntrl(siop, SET, CONSFLAG, OFF);  /* console echo off */
                    if (m_warndcd(siop, OFF) == 0)
                         printf("\n%s.  \n",m_codes[dial(siop)]);
                    s_icntrl(siop, SET, CONSFLAG, ON);  /* console echo on formatted input  */
                    c = EXIT;                        /* leave menu after dial */
                    break;
               case REDIAL:
                    s_icntrl(siop, SET, CONSFLAG, OFF);  /* console echo off */
                    if (m_warndcd(siop, OFF) == 0)
                         printf("\n%s.  \n",m_codes[redial(siop)]);
                    s_icntrl(siop, SET, CONSFLAG, ON);  /* console echo off */
                    c = EXIT;                      /* leave menu after redial */
                    break;
               case ANSWER:
                    s_icntrl(siop, SET, CONSFLAG, OFF);  /* console echo off */
                    if (m_warndcd(siop, OFF) == 0)
                         printf("\n%s.  \n",m_codes[m_answer(siop)]);
                    s_icntrl(siop, SET, CONSFLAG, ON);  /* console echo on formatted input  */
                    c = EXIT;                      /* leave menu after answer */
                    break;
               case HUP:

#ifdef DEBUG_MODEM                                      /*//*/
                    s_icntrl(siop, SET, CONSFLAG, ON);  /*//*/
                    s_ocntrl(siop, SET, CONSFLAG, ON);  /*//*/
#endif                                                  /*//*/
                    puts("\nHanging up...");
                    if (m_warndcd(siop, ON) == 0)
                         printf("\nHangup %s.\n",\
                              m_hup(siop) == 0 ? "OK" : "error");
                    c = EXIT;                     /* leave menu after hangup  */
                    break;
               case XSEND:
                    if (m_warndcd(siop, ON) == 0)
                         x_snd(siop);
                    haktc();
                    break;
               case XRECV:
                    if (m_warndcd(siop, ON) == 0)
                         x_rcv(siop);
                    haktc();
                    break;
               case BASELINE_CFG:
                    (void)baseline_cfg(siop);
                    haktc();
                    break;
               case PROTO_CFG:
				    if (siop->sm->configokflag != TRUE)
     					puts("\nBaseline Configuration Required.");
                    else
                    	proto_cfg(siop);
                    haktc();
                    break;
               case UART_ID:
                    printf("\nUART on device %d is a %s :\n", siop->devnum,
                        siop->rcv_fifo_trigger == 0 ? "16450/8250" : "16550");
                    printf("\t    TX FIFO depth is: %2d\n"
	                    "\t TX Trigger level is: %2d\n"
                        "\t   RCV FIFO depth is: %2d\n"
	                    "\tRCV Trigger level is: %2d\n",
                               siop->tx_fifo_depth,
                               siop->tx_fifo_trigger,
                               siop->rcv_fifo_depth,
                               siop->rcv_fifo_trigger);
                    printf("\nInterrupts Active:\n"
                        "\t       Serial Errors: %s\n"
                        "\t               RS232: %s\n"
                        "\t            Receiver: %s (%d-byte buffer)\n"
                        "\t         Transmitter: %s  (%d %d-byte buffers)\n",
                                  siop->intrpt_status.serr_on ? "Yes" : "No",
                                  siop->intrpt_status.rs232_on ? "Yes" : "No",
                                  siop->intrpt_status.rcv_on? "Yes" : "No",
                                  siop->rcv_buffsize,
                                  siop->intrpt_status.tx_on ? "Yes" : "No",
                                  siop->tx_numbuffs,
                                  siop->tx_buffsize);
              { // curly braces just to declar flow array
              char *flow[3] = {"NONE", "XON/XOFF", "RTS/CTS"};
              int i; /*//*/
              printf("\nFlow Control is %s:\n", flow[siop->flow_wanted]);
              }
                    haktc();
                    break;
               default:
                    puts("Invalid choice\n\a");
                    break;
               }
          }
     putchar('\n');
     siop->sm->cmdechoflag = FALSE;
     s_icntrl(siop, SET, CONSFLAG, OFF);  /* console echo off */
     m_echo(siop, ON);
     s_icntrl(siop, SET, CONSFLAG, ON);  /* console echo off */
     return retval;     /* will be zero except if EXIT */
}



void term(siop)
SIO *siop;
{
     int c;                             /* must be int to detect -1 return   */

     s_ipush(siop);                     /* save both control structures      */
     s_opush(siop);
     m_echo(siop, ON);                   /* macro */
     s_icntrl(siop, SET, CONSFLAG, ON);  /* console echo on formatted input  */
     s_ocntrl(siop, SET, IB_DLYFLAG, OFF);   /* interbyte delay              */
     printf("TERM, Version %d:  Press Control-%c for a summary of commands\n", \
         vers, MENU + '@');

    flowon(siop);
    for (EVER)                              /*         eternal loop         */
          {
          s_fgetc(siop);                     /* s_fgetc will echo            */
          if ( (c = inkey()) != NOT_READY)
               if (c == MENU)
                    {
                    if (menu(siop))
                         break;          /* if menu returns non-zero         */
                    }
               else
                    s_fputc(siop, c);
          if(serial_status(siop, BREAK_ON))
               puts("Break Detected");
          }
     s_opop(siop);                      /* restore both control structures   */
     s_ipop(siop);
     m_unconfig(siop);
}


main(argc, argv)
int argc;
char *argv[];
{
//     long beginmem; /*//*/
     short portnum;
     SIO *siop;                  /* pointer to an SIO            */
//     beginmem = _memavl();
     portnum = 2;
     if (argc > 1)
          portnum = atoi(argv[1]);
     if ( (siop = s_open(portnum)) == NIL)
          {
          printf("\aCannot open:  %s\n",errstr[s_errno]);
          return s_errno;
          }
     setbaud(siop, BAUD19K2);
     term(siop);                           /*   TERM */
     if ( (s_errno = s_close(siop)) != 0 )
          {
          printf("\aCannot close:%s\n",errstr[s_errno]);
          return s_errno;
          }
     puts("\nEnd of TERM\n");
//     printf("Memory consumed = %lu\n",beginmem - _memavl());
     return 0;
}
