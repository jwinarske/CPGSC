/*-

FUNCTION NAME:  s_icntrl
        LEVEL:  3
 PROTOTYPE IN:  SIODEF.H
      LIBRARY:  SIO.LIB
  DESCRIPTION:  Sets or fetches the value of the flag, delay, and mode
                members of an sictl_ input control structure.
      RETURNS:  int.  0 if successful, otherwise, -1.
     COMMENTS:  Constants are in SIOCTL.H. The range of the 'code'
                arguments is not checked.
*/


#include <sio\siodef.h>
#include <sio\sioctl.h>

/* 2: SET or GET (see SIOCTL.H)         */
/* 4: new value for member (SET only )  */

int s_icntrl(SIO *siop, short function, short member, unsigned newval)
{
     int retval  = 0;
     if (function == SET)
          switch (member)
               {
               case T_OUT     : siop->s_ictl->t_out     = newval;  break;
               case T_OUTFLAG : siop->s_ictl->t_outflag  =  newval;  break;
               case RAWFLAG   : siop->s_ictl->rawflag    =  newval;  break;
               case EKOBAKFLAG: siop->s_ictl->ekobakflag =  newval;  break;
               case ASCIIFLAG : siop->s_ictl->asciiflag  =  newval;  break;
               case EOLMODE   : siop->s_ictl->eolmode   = newval;  break;
               case CONSFLAG  : siop->s_ictl->consflag   =  newval;  break;
               case CASEMODE  : siop->s_ictl->casemode  = newval;  break;
               case CNTRLFLAG : siop->s_ictl->cntrlflag  =  newval;  break;
               case FILTERFLAG: siop->s_ictl->filterflag =  newval;  break;
               default:
                    retval = -1;
               }
     else if (function == GET)
          switch (member)
               {
               case T_OUT     : retval  = siop->s_ictl->t_out    ;  break;
               case T_OUTFLAG : retval  = (int)siop->s_ictl->t_outflag ;  break;
               case RAWFLAG   : retval  = (int)siop->s_ictl->rawflag   ;  break;
               case EKOBAKFLAG: retval  = (int)siop->s_ictl->ekobakflag;  break;
               case ASCIIFLAG : retval  = (int)siop->s_ictl->asciiflag ;  break;
               case EOLMODE   : retval  = siop->s_ictl->eolmode  ;  break;
               case CONSFLAG  : retval  = (int)siop->s_ictl->consflag  ;  break;
               case CASEMODE  : retval  = siop->s_ictl->casemode ;  break;
               case CNTRLFLAG : retval  = (int)siop->s_ictl->cntrlflag ;  break;
               case FILTERFLAG: retval  = (int)siop->s_ictl->filterflag;  break;
               default:
                    retval = -1;
               }
     return retval;
}
