/*-
FUNCTION NAME:  s_fputc
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Provides "formatted" character-by-character serial output
                according to the soctl_ structure in the structure
                pointed to by siop.
      RETURNS:  int: NOECHO if "wait for echo" times out,
                KEY_CAN if a loop (e.g. XON-XOFF) is aborted from
                keyboard; otherwise 0.
     COMMENTS:  Features:
                Raw (no processing)              High bit clearing
                Inter-byte and _line delay       Character filter
                XON-XOFF flow control            Character translation
                End of line conversion           Console output
                Upper/lower case conversion      Wait-for-echo
*/

#include <stdio.h>
#include <ctype.h>
#include <sio\siodef.h>
#include <sio\sioctl.h>
#include <sio\ascii.h>
#include <sio\buos.h>
#include <sio\level0.h>        /* for timing constants */

/*
  Figure 15.7
FUNCTION NAME:  s_eputc
 PROTOTYPE IN:  BUOS.H
        LEVEL:  2
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Output byte to the SIO and, if consflag is set, to
                standard output.
      RETURNS:  void
     COMMENTS:  Declared static--i.e., local to this file.
*/

static void s_eputc(SIO *siop, int c)
{
     s_putc(siop, c);
     if (siop->s_octl->consflag)              /* echo to standard out       */
          putchar(c);
}


int s_fputc(SIO *siop, FAST c)
{
     register struct soctl_ *op;             /* saves lots of indexing time */
     static int  i, txflag;
     txflag = TRUE;
     op = siop->s_octl;
     op->flushflag = FALSE;
     if (op->rawflag)                         /* -- RAW: XMIT -- */
          {
          s_putc(siop, c);
          return 0;
          }
     if (op->asciiflag)                       /* -- RESET BIT 7 -- */
          c = (BYTE) toascii(c);

     if (getflow_req(siop) == FLOW_OFF)         /* macro */
          for (EVER)                    /* paused awaiting release or abort */
               {
               if (s_keybort(siop))
                    return KEY_CAN;
               if (getflow_req(siop) == FLOW_ON)  /* macro */
                    break;
               }

     if (op->filterflag)                 /* -- TRANSLATE/REMOVE BYTE -- */
          {
          for (i = op->numfc-1; i >= 0 ; i--)
               if ((int) c == op->filtlist[i][0])
                    {
                    if (op->filtlist[i][1] == -1)  /* remove              */
                         txflag = FALSE;
                    else
                         c = op->filtlist[i][1];   /* translate           */
                    break;
                    }
          }
     if (iscntrl(c) && txflag)                  /*  -- REMOVE CONTROLS -- */
          {
          if (op->cntrlflag)
               {
               txflag = FALSE;
               for (i = op->numcc-1; i >= 0 ; i--)
                    if (c == (FAST)op->ok_cntrls[i])  /* loop through list */
                         {
                         txflag = TRUE;      /* if on list        */
                         break;
                         }
               }
          if (txflag)                /* -- END OF LINE TRANSLATION -- */
               {
               switch (op->eolmode)
                    {
                    case NOXLAT:             /*    no conversion  */
                         break;
                    case LF2CR:              /*      lf->cr       */
                         if (c == LF)
                              {
                              s_eputc(siop, op->lastc == CR ? LF : CR);
                              txflag = FALSE;
                              }
                         break;
                    case CR2LF:              /*      cr->lf       */
                         if (c == CR)
                              {
                              txflag = FALSE;
                              op->flushflag = TRUE;
                              break;
                              }
                         if (op->lastc == CR)
                              s_eputc (siop, c == LF ? CR : LF);
                         break;
                    case EOL2SPACE:         /* cr and lf converted to spaces */
                         if (c == CR || c == LF)  /* crlf = one space        */
                              {
                              txflag = FALSE;
                              if (c != LF && op->lastc != CR)
                                   s_eputc(siop, SP);
                              }
                         break;
                    case REMOVEEOL:          /* cr and lf not transmitted    */
                         if (c == CR || c == LF)
                              txflag = FALSE;
                         break;
                    case LF2CRLF:            /* lf -> crlf          */
                         if (c == LF && op->lastc != CR)
                              s_eputc(siop, CR);
                         break;
                    case CR2CRLF:            /*  cr->crlf           */
                         if (c == CR)        /* wait for next byte  */
                              {
                              txflag = FALSE;
                              op->flushflag = TRUE;
                              }
                         if (op->lastc == CR)
                              {
                              s_eputc(siop, CR);
                              if (c != LF)
                                   s_eputc(siop, LF);
                              }
                         break;
                    case CRLF2LF:            /* crlf -> lf */
                         if ( c == CR)
                              {
                              txflag = FALSE;
                              op->flushflag = TRUE;
                              break;
                              }
                         if (op->lastc == CR && c != LF)
                              s_eputc(siop, CR);
                         break;
                    case CRLF2CR:            /* crlf -> cr */
                         if (op->lastc == CR && c == LF)
                              txflag = FALSE;
                         break;
                    default:
                         break;
                    }                        /* end of end-of-line switch */
               }
          }

     if (txflag)
          {                                  /* -- FLOW CONTROL -- */
          switch (op->casemode)              /* -- CONVERT CASE -- */
               {
               case UP_LOW:
                    break;
               case UPPER:
                    c = toupper(c);
                    break;
               case LOWER:
                    c = tolower(c);
                    break;
               }
          if ( op->ib_dlyflag)               /* -- INTERBYTE, -LINE DELAYS -- */
               __delay(op->ib_dly);
          s_eputc(siop, c);             /* xmit with optional console output */
          if (op->wechoflag)                 /* -- WAIT FOR REMOTE ECHO -- */
               if (__s_waitch(siop, op->wecho_dly) == TIMEOUT)
                    return NOECHO;
          if (op->il_dlyflag && (BOOL) c == (BOOL) op->il_dlyc)
               __delay(op->il_dly);          /* end of line delay            */
          }
     op->lastc = c;                          /*     save this character      */
     return 0;
}
