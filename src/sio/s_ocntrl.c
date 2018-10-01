/*-
FUNCTION NAME: s_ocntrl
        LEVEL: 3
 PROTOTYPE IN: SIODEF.H
      LIBRARY: SIO.LIB
  DESCRIPTION: Sets or fetches the value of the flag, delay, and mode
               members of an sictl_ input control structure.
      RETURNS: int.  SET: 0 if successful, otherwise, -1;
               GET: -1 if unsuccessful.
     COMMENTS: Constants are in SIOCTL.H. The range of the 'code'
               arguments is not checked.
*/

#include <sio/siodef.h>
#include <sio/sioctl.h>

/* 2: SET or GET                        */
/* 3: code for member to address        */
/* 4: new value for member (SET only )  */

int s_ocntrl(SIO *siop, short mode, short  whichone, uint16_t newval)
{
     int retval  = 0;
     if ( mode == SET)
          switch (whichone)
               {
               case RAWFLAG:    siop->s_octl->rawflag     = newval; break;
               case EOLMODE:    siop->s_octl->eolmode    = newval; break;
               case CONSFLAG:   siop->s_octl->consflag    = newval; break;
               case WECHOFLAG:  siop->s_octl->wechoflag   = newval; break;
               case WECHO_DLY:  siop->s_octl->wecho_dly  = newval; break;
               case CASEMODE:   siop->s_octl->casemode   = newval; break;
               case ASCIIFLAG:  siop->s_octl->asciiflag   = newval; break;
               case CNTRLFLAG:  siop->s_octl->cntrlflag   = newval; break;
               case FILTERFLAG: siop->s_octl->filterflag  = newval; break;
               case IB_DLYFLAG: siop->s_octl->ib_dlyflag  = newval; break;
               case IB_DLY:     siop->s_octl->ib_dly     = newval; break;
               case IL_DLYFLAG: siop->s_octl->il_dlyflag  = newval; break;
               case IL_DLY:     siop->s_octl->il_dly     = newval; break;
               case IL_DLYC:    siop->s_octl->il_dlyc    = (FAST)newval; break;
               case KBORTC:     siop->s_octl->kbortc     = (FAST)newval; break;
               default:
                    retval = -1;
                    break;
               }
     else if (mode == GET)
          switch (whichone)
               {
               case RAWFLAG:    retval = (int)siop->s_octl->rawflag    ; break;
               case EOLMODE:    retval = siop->s_octl->eolmode   ; break;
               case CONSFLAG:   retval = (int)siop->s_octl->consflag   ; break;
               case WECHOFLAG:  retval = (int)siop->s_octl->wechoflag  ; break;
               case WECHO_DLY:  retval = siop->s_octl->wecho_dly ; break;
               case CASEMODE:   retval = siop->s_octl->casemode  ; break;
               case ASCIIFLAG:  retval = (int)siop->s_octl->asciiflag  ; break;
               case CNTRLFLAG:  retval = (int)siop->s_octl->cntrlflag  ; break;
               case FILTERFLAG: retval = (int)siop->s_octl->filterflag ; break;
               case IB_DLYFLAG: retval = (int)siop->s_octl->ib_dlyflag ; break;
               case IB_DLY:     retval = siop->s_octl->ib_dly    ; break;
               case IL_DLYFLAG: retval = (int)siop->s_octl->il_dlyflag ; break;
               case IL_DLY:     retval = siop->s_octl->il_dly    ; break;
               case IL_DLYC:    retval = siop->s_octl->il_dlyc   ; break;
               case KBORTC:     retval = siop->s_octl->kbortc    ; break;
               default:
                    retval = -1;
                    break;
               }
     return retval;
}
