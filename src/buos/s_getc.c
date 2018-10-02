/*-
FUNCTION NAME:  s_getc
        LEVEL:  2
 PROTOTYPE IN:  BUOS.H
      LIBRARY:  BUOS.LIB
  DESCRIPTION:  Wait for a uint8_t to arrive from the serial port (SIO) pointed
                to by a siop.
      RETURNS:  FAST
     COMMENTS:  Access to the port is through a pointer to an SIO structure.
*/

#include "sio/siodef.h"


FAST s_getc(register SIO *siop)
{
     while ((*siop->s_rstat)(siop) & siop->rcv_vflowstate) /* wait for char to be ready    */     while ((*siop->s_rstat)(siop) == 0)     /* wait for char to be ready    */     while ((*siop->s_rstat)(siop) == 0)     /* wait for char to be ready    */
//     while ((*siop->s_rstat)(siop) == 0)     /* wait for char to be ready    */     while ((*siop->s_rstat)(siop) == 0)     /* wait for char to be ready    */     while ((*siop->s_rstat)(siop) == 0)     /* wait for char to be ready    */ /*//*
          {;}
     return ((*siop->s_read)(siop));         /* read and return it           */
}
