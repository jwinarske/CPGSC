/*
FUNCTION NAME:  s_fgetc
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Provides "formatted" character-by-character serial input
                according to the sictl_ structure pointed to by the
                SIO.
      RETURNS:  int: TIMEOUT if t_outflag is TRUE and no uint8_t
                arrives in t_out Tsecs; IGNORE if an EOL decision
                pending; otherwise the uint8_t received.
     COMMENTS:  Functions supported:
                Switchable timeout mode          Raw mode
                Control character filter         Character translation/filter
                End of line conversion           Console output
                XON/XOFF flow control            Upper/lower case conversion
                Echo-back to sender              High bit clearing

*/

#include <stdio.h>
#include <ctype.h>
#include "sio/siodef.h"
#include "sio/sioctl.h"
#include "sio/ascii.h"
#include "sio/level0.h"        /* for timing constants */
#include "sio/buos.h"

int s_fgetc(SIO *siop)
{
    register struct sictl_ *ip;        /* registers and statics for speed   */
    static int retbyte, i, c;
    static bool rxflag;
    if (siop->s_ictl->rawflag)               /* do raw processing asap       */
        return s_inchar(siop);
    ip = siop->s_ictl;                      /* save lots of indexing time   */
    if (ip->rbakflag)                        /* if uint8_t pending              */
        {
        ip->rbakflag = FALSE;
        if (ip->consflag)
            putchar(ip->rbakc);
        return ip->rbakc;
        }
    c = (ip->t_outflag)  ?  __s_waitch(siop, ip->t_out)  :  s_inchar(siop);
    if (c == TIMEOUT)
        return TIMEOUT;
    retbyte  = -1;                          /* postpone initialization      */
    rxflag   = TRUE;
    if (ip->ekobakflag)                      /* -- ECHO TO SENDER -- */
        s_putc(siop, c);
    if (ip->asciiflag)                       /* -- RESET BIT 7 -- */
        c = toascii(c);
    if (ip->filterflag)                      /* -- TRANSLATE/REMOVE uint8_t -- */
        {
        for ( i = ip->numfc-1; i >= 0 ; i--)
            if (c == ip->filtlist[i][0])
                {
                if (ip->filtlist[i][1] == -1)  /*    remove             */
                        rxflag = FALSE;
                else
                        c = ip->filtlist[i][1];    /* translate            */
                break;
                }
        }
    if (iscntrl(c) && rxflag)               /* -- REMOVE CONTROLS -- */
        {
        if (ip->cntrlflag)
            {
            rxflag = FALSE;
            for (i = ip->numcc-1; i >= 0 ; i--)
                if (c == ip->ok_cntrls[i])  /* loop through list       */
                        {
                        rxflag = TRUE;      /* if on list                   */
                        break;
                        }
            }
        }
    if (rxflag)                            /* -- END-OF-LINE TRANSLATION -- */
        {
        switch (ip->eolmode)
            {
            case NOXLAT:                  /*    no conversion             */
                break;
            case LF2CR:                   /*           lf->cr             */
                if (c == LF)
                        retbyte = CR;
                break;
            case CR2LF:                   /*           cr->lf             */
                if ( c == CR)
                        retbyte = LF;
                break;
            case EOL2SPACE:               /* cr & lf converted to spaces  */
                if (c == CR || c == LF) { /*   crlf = one space           */
                    if (c != LF && ip->lastc != CR) {
                        rxflag = FALSE;
                    }
                    else {
                        retbyte = SP;
                    }
                }
                break;
            case REMOVEEOL:               /*   cr and lf not transmitted  */
                if (c == CR || c == LF)
                        rxflag = FALSE;
                break;
            case LF2CRLF:                 /*          lf -> crlf          */
                if (c == LF) {
                    ip->rbakflag = TRUE;
                    ip->rbakc   = LF;
                    retbyte     = CR;
                }
                break;
            case CR2CRLF:                 /*           cr->crlf           */
                if (c == CR) {
                    ip->rbakflag = TRUE;
                    ip->rbakc   = LF;
                }
                break;
            case CRLF2LF:                 /*           crlf -> lf         */
                if ( c == CR && ip->lastc != CR)
                        rxflag = FALSE;                    else
                        retbyte = (ip->lastc == CR) ? LF : CR;
                break;
            case CRLF2CR:                 /*            crlf -> cr        */
                if ( c == CR && ip->lastc != CR)
                        rxflag = FALSE;
                else
                        retbyte = CR;
                break;
            default:
                break;
            }                             /* end of end-of-line switch    */
        }
    if (rxflag)
        switch (ip->casemode)              /* -- CASE CONVERSION -- */
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
    ip->lastc = c;                          /*     save this character      */
    if (retbyte != -1)            /* if uint8_t to return is not uint8_t received */
        c = retbyte;
    if ( ip->consflag && rxflag)
        putchar(c);
    return (rxflag ? c : IGNORE);
}
