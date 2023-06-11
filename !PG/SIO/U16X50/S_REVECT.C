/*-
FUNCTION NAME: s_revector
        LEVEL: 1
 PROTOTYPE IN: U16X50.H
      LIBRARY: U16X50.LIB
     DESCRIPT: Installs new UART interrupt handlers.
     RETURNS : pointer to the previous handler.
     COMMENTS: Declaration is "function returning a pointer to a function
               returning void."
*/

#include <sio\siodef.h>      
#include <sio\level0.h>
#include <sio\uart.h>       /* ADD */

#pragma check_stack-
                             /* changed */
void (*s_revector(SIO *siop, USHORT int_wanted, void (*newisr)(SIO*))) ()
{
     void (*oldisr)(SIO *);         /* temporary storage for current isr */
     short index;   /* index into the interrupt vector array in s_iadmin */
     short error = 0;
     switch (int_wanted)
          {
          case RS232    :  index = INDEX_RS232; break;     /*changed*/
          case THRE     :  index = INDEX_THRE; break;      /*changed*/ 
          case RXRDY    :  index = INDEX_RXRDY; break;     /*changed*/
          case SERERR   :  index = INDEX_SERERR; break;    /*changed*/
          case RXTIMEOUT:  index = INDEX_RXTIMEOUT; break; /*changed*/
          default:  error = 1; break;
          }
     if (!error)        /* don't revector an undefined interrupt */
          {
          __sys_disable();
          oldisr     = siop->isr[index];     /* save current isr */
          siop->isr[index] = newisr;        /* install new isr */
          __sys_enable();
          }
     else
          oldisr = NIL;
     return oldisr;                        /* return old isr */
}

#pragma check_stack+
