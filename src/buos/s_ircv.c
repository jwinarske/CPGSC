// This file contain receiver interrupt handler for all kinds of flow control.

#include <stdlib.h>
#include <sio/siodef.h>
#include <sio/buos.h>           
#include <sio/sioctl.h>           
#include <sio/level0.h>


/*
FUNCTION NAME:  s_ircv_xoxo
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Interrupt function to read a character from buffer. Supports
                XON/XOFF flow control.
      RETURNS:  FAST
     COMMENTS:  Returns the uint8_t in the interrupt buffer pointed to by the
                SIO member rcv_tailp. If, after incrementation,
                rcv_tailp points past the end of the buffer, it is reset
                to the beginning.  XON/XOFF Flow control is implemented based
                upon the amount of room remaining in the buffer.
INCLUDE FILES:  stdlib.h, siodef.h, buos.h, sioctl.h, level0.h
*/



FAST s_ircv_xoxo(register SIO *siop)
{
    static FAST c;                 /* static for speed        */
    ptrdiff_t diff;				/* pointer difference      */
    ptrdiff_t byte_left;           /* room left in buffer     */
    __sys_disable();
    c = *siop->rcv_tailp;          /* put in buffer at pointer */
    if ( ++siop->rcv_tailp == siop->rcv_buffend)
        siop->rcv_tailp = siop->rcv_buff;  /* wrap back to beginning   */
    diff = siop->rcv_headp - siop->rcv_tailp;
    byte_left = (diff >= 0L) ? siop->rcv_buffsize - diff : labs(diff);
    if ((byte_left > siop->rcv_buffsize - FLOW_TAILROOM) && siop->rcv_iflowstate == OFF)
    {
    siop->rcv_iflowstate = ON;
    s_xmit(siop, XON);
    }
    __sys_enable();
    return c;
}
 

/*
FUNCTION NAME:  s_ircv_rcts
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Interrupt function to read a character from buffer. Supports
                XON/XOFF flow control.
      RETURNS:  FAST
     COMMENTS:  Returns the uint8_t in the interrupt buffer pointed to by the
                SIO member rcv_tailp. If, after incrementation,
                rcv_tailp points past the end of the buffer, it is reset
                to the beginning.  XON/XOFF Flow control is implemented based
                upon the amount of room remaining in the buffer.
INCLUDE FILES:  stdlib.h, siodef.h, buos.h, sioctl.h, level0.h
*/


FAST s_ircv_rcts(register SIO *siop)
{
    static FAST c;                 /* static for speed        */
    ptrdiff_t diff;				/* pointer difference      */
    ptrdiff_t bytes_left;          /* room left in buffer     */
    __sys_disable();
    c = *siop->rcv_tailp;          /* put in buffer at pointer */
    if ( ++siop->rcv_tailp == siop->rcv_buffend)
        siop->rcv_tailp = siop->rcv_buff;  /* wrap back to beginning   */
    diff = siop->rcv_headp - siop->rcv_tailp;
    bytes_left = (diff >= 0L) ? siop->rcv_buffsize - diff : labs(diff);
    if ((bytes_left > siop->rcv_buffsize - FLOW_TAILROOM) && siop->rcv_iflowstate == OFF) {
        siop->rcv_iflowstate = ON;
        set232(siop, RTS, ON);
    }
    __sys_enable();
    return c;
}
 

/*-
FUNCTION NAME:  s_ircv
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Interrupt function to read a character.
      RETURNS:  FAST
     COMMENTS:  Returns the uint8_t in the interrupt buffer pointed to by the
                SIO member rcv_tailp. If, after incrementation,
                rcv_tailp points past the end of the buffer, it is reset
                to the beginning.  
INCLUDE FILES:  stdlib.h, siodef.h, buos.h, sioctl.h, level0.h
*/

#include <stdlib.h>
#include <sio/siodef.h>
#include <sio/buos.h>           
#include <sio/sioctl.h>           
#include <sio/level0.h>

FAST s_ircv(register SIO *siop)
{
    static FAST c;                 /* static for speed        */
    __sys_disable();
    c = *siop->rcv_tailp;                          /* put in buffer at pointer */
    if ( ++siop->rcv_tailp == siop->rcv_buffend)
        siop->rcv_tailp = siop->rcv_buff;         /* wrap back to beginning   */
    __sys_enable();
    return c;
}
