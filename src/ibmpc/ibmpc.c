/*
**************************************************************************
*    NOTICE:
*   The following must either be defined here or passed in
*   on the compiler command line.  If defined here they must be
*   at the top of this file
*
*   One or more of the following:
*    #define COM1SIO       (Com1)
*    #define COM2SIO       (Com2)
*    #define COM3SIO       (Com3)
*    #define COM4SIO       (Com4)
**************************************************************************
*/

//TODO #define COM1SIO
//TODO #define COM2SIO
//TODO #define COM3SIO
//TODO #define COM4SIO

#include <stdio.h>
#if !defined(__GNUC__)
#include <conio.h>
#include <dos.h>           /*//*/
#endif

#include <sio/siodef.h>
#include <sio/ascii.h>
#include <sio/uart.h>
#include <sio/sioctl.h>
#include <sio/ibmpc.h>
#include <sio/buos.h>
#include <sio/modem.h>

#pragma check_stack-                 /* turn off stack checking */

#ifdef COM1SIO
#include "COM1SIO.C"
#endif

#ifdef COM2SIO
#include "COM2SIO.C"
#endif

#ifdef COM3SIO
#include "COM3SIO.C"
#endif


#ifdef COM4SIO
#include "COM4SIO.C"
#endif

/*-
FUNCTION NAME:  __delay
 PROTOTYPE IN:  IBMPC.H
        LEVEL:  0
      LIBRARY:  IBMPC.C
  DESCRIPTION:  Does nothing for tsecs Tsecs.
      RETURNS:  void
     COMMENTS:  The system interval is defined as 1 Tsec (about 50 msecs).
*/


void __delay(unsigned tsecs)
{
     unsigned volatile tickref;
     for (; tsecs > 0; --tsecs)
          {
          tickref = __peekw(TIMER_LO, 0);
          while (tickref == (unsigned) __peekw(TIMER_LO, 0))
               {;} /* Warning: compiler optimization may toss this */
          }
}

/*-
FUNCTION NAME:  __s_waitch
 PROTOTYPE IN:  IBMPC.H
        LEVEL:  0
      LIBRARY:  IBMPC.C
  DESCRIPTION:  Waits for a serial uint8_t to arrive for tsecs Tsecs.
      RETURNS:  int, the uint8_t if one arrives, otherwise NOT_REAY at timeout.
     COMMENTS:  The system timing interval is defined as a  "Tsec," or
                about 50 msec.
*/



int __s_waitch(register SIO *siop, unsigned tsecs)
{
     unsigned tickref;
     tickref = __peekw(TIMER_LO, 0);         /* initialize reference count   */
     while (tsecs > 0)
          {
          if ( (*siop->s_rstat)(siop) & siop->rcv_vflowstate) /* check UART for uint8_t ready         */
               return  ((*siop->s_read)(siop));  /* return uint8_t if ready     */
          if ((unsigned) __peekw(TIMER_LO, 0) != tickref) /* compare new count to old */
               {
               tickref = __peekw(TIMER_LO, 0);   /* get new reference ....   */
               tsecs--;                          /* ...and reduce timeout    */
               }
          }
     return s_inchar(siop);                   /* timed out--no uint8_t received */
}


/*-
FUNCTION NAME:  __isport
 PROTOTYPE IN:  IBMPC.H
        LEVEL:  0
      LIBRARY:  IBMPC.C
  DESCRIPTION:  Verifies that a UART is present at "devnum."
      RETURNS:  bool:  TRUE if the device exists.
     COMMENTS:  Bits 4 and 5 of the IER are Read-only and always 0.
                write the DLAB bit in the Data Format (Line Control
                Register) to uncover the msb of the baud register, then
                writes 80H.  It then flips the DLAB back to the IER
                register and tests its high bit. Since the IER's bits 4
                and 5 are always 0, they cannot be set.  Voila.
*/

bool __isport(RANK devnum)
{
     uint8_t *uartp;
     bool retcode = 1;
     switch(devnum)
          {
          case 0: uartp = COM1; break;
          case 1: uartp = COM2; break;
          case 2: uartp = COM3; break;
          case 3: uartp = COM4; break;
          default:retcode = 0;
          }
     if (retcode)
          {
#if 0 //TODO              
          FAST old_msb, old_format;
          old_format = _a_inport(uartp + DLAB);
          _a_outport(uartp + DLAB, old_format | 0x80);   /* flip DLAB to baud*/
          old_msb = _a_inport(uartp + BAUDHI);           /* save old msb     */
          _a_outport(uartp + BAUDHI, 0x30);              /* bits 4&5 never 1 */
          _a_outport(uartp + DLAB, old_format & 0x7f);   /* flip DLAB to IER */
          retcode = !(_a_inport(uartp + INT_ID)  & 0x30);/* are 4&5 now 1?   */
          _a_outport(uartp + DLAB, old_format | 0x80);   /* flip DLAB to baud*/
          _a_outport(uartp + BAUDHI, old_msb);           /* ...restore msb   */
          _a_outport(uartp + DLAB, old_format & 0x7f);   /* flip DLAB to IER */
          _a_outport(uartp + DLAB, old_format);
#endif          
          }
     return retcode;
}

/*-
  STRUCT NAME:  __siolist
  HEADER FILE:  IBMPC.C
  DESCRIPTION:  An array of struct _siostat, MAX_PORTS in length.
     COMMENTS:  The global integer __maxsios contains the maximum number of
                serial devices possible in the system.
*/

unsigned __maxsios = MAX_PORTS;          /* global                            */
struct SIOLIST __siolist[MAX_PORTS] = /* IBM has four serial ports          */
    {
/*      SIO       Open   Supported  */
#ifdef COM1SIO                                    /* COM1 */
     { &COM1sio , FALSE, TRUE },
#else
     { NIL, FALSE, FALSE },
#endif
/*................................*/

#ifdef COM2SIO                                    /* COM2 */
     { &COM2sio , FALSE, TRUE },
#else
     { NIL, FALSE, FALSE},
#endif

/*................................*/

#ifdef COM3SIO                                     /* COM3 */
     { &COM3sio , FALSE, TRUE },
#else
      { NIL, FALSE, FALSE },
#endif
/*................................*/

#ifdef COM4SIO                                    /* COM4  */
     { &COM4sio , FALSE, TRUE}
#else
     { NIL, FALSE, FALSE,}
#endif
    };

/*-
  STRUCT NAME:  __sys_ilist
  HEADER FILE:  IBMPC.C
  DESCRIPTION:  An array, MAX_PORTS in length, of structures describing
                interrupt information for each serial port.
     COMMENTS:
*/

struct SYS_ILIST __sys_ilist[MAX_PORTS] =
     {
#ifdef COM1SIO
         {
         I_COM1,       /* Number in vector table */
         IMR_IRQ4,       /* IMR Mask for the PIC   */
         _a_com1isr,   /* Interrupt handler      */
         SUPPLIED,     /* Old interrupt vector   */
         SUPPLIED,     /* Old IMR of PIC         */ 
         SUPPLIED      /* Save GPO2 structure    */
         },
#else
         { 0, 0, 0, 0},   /* null if not SIO supported */ // NIL, 0
#endif
#ifdef COM2SIO
         {  I_COM2, IMR_IRQ3, _a_com2isr, SUPPLIED, SUPPLIED, SUPPLIED },
#else
         { 0, 0, 0, 0},      /* null if not SIO supported    */ // NIL, 0
#endif
#ifdef COM3SIO
         {  I_COM3, IMR_IRQ4, _a_com3isr, SUPPLIED, SUPPLIED, SUPPLIED },
#else
         { 0, 0, 0, 0},     /* null if not SIO supported    */ // NIL, 0
#endif
#ifdef COM4SIO
         {  I_COM4, IMR_IRQ3, _a_com4isr, SUPPLIED, SUPPLIED, SUPPLIED },
#else
         { 0, 0, 0, 0}, // NIL, 0, 
#endif
     };


/*-
FUNCTION NAME:  __sysintron
 PROTOTYPE IN:  IBMPC.H
        LEVEL:  0
      LIBRARY:  IBMPC.C
  DESCRIPTION:  Deactivates system interrupts for the port specified.
                (UART's GPO2 output is considered a system function.)
      RETURNS:  void
     COMMENTS:  The assembly-language functions a_inport and a_outport 
                reside in INTRP.ASM.

*/

void __sysintron(SIO *siop, RANK portnum)
{
//TODO     FAST imr;
     __sys_disable();

          /** STEP 1: change the interrupt vector, save current value **/
#if 0 //TODO          
     __sys_ilist[portnum].oldivect = _dos_getvect(__sys_ilist[portnum].inum);
     _dos_setvect( __sys_ilist[portnum].inum, __sys_ilist[portnum].isr);
#endif     

           /** STEP 2: unmask bit in 16x50's Interrupt Mask Register **/
#if 0
     __sys_ilist[portnum].oldimr =  imr = _a_inport ((uint8_t*)IMR);
     imr = (uint8_t) (imr &  __sys_ilist[portnum].imask);
     _a_outport((uint8_t*) IMR, imr);
#endif

           /** STEP 3: Unblock 16x50's INTR line **/
     __sys_enable();
     set232(siop, GPO2, ON);                        /* Unblock interrupts  */
     __sys_ilist[portnum].oldgpo2 = siop->gpo2;     /* Save gpo2 structure */
     siop->gpo2 = NIL;                              /* Remove gpo2 control */
     s_iadmin(siop);
     return;
}

/*-
FUNCTION NAME:  __sysintroff
 PROTOTYPE IN:  IBMPC.H
        LEVEL:  0
      LIBRARY:  IBMPC.C
  DESCRIPTION:  Deactivates system interrupts for the port specified.
                (UART's GPO2 output is considered a system function.)
      RETURNS:  void
     COMMENTS:  Values are restored from the __sys_ilist structure array.
                The assembly-language functions a_inport and a_outport 
                reside in INTRP.ASM.
*/

void __sysintroff(SIO *siop, RANK portnum)
{
     __sys_disable();
//TODO     _a_outport( (uint8_t*)IMR, __sys_ilist[portnum].oldimr); /* restore Int.Mask Register */
     __sys_enable();
//TODO     _dos_setvect(__sys_ilist[portnum].inum, __sys_ilist[portnum].oldivect);  /* restore vector */
     siop->gpo2 = __sys_ilist[portnum].oldgpo2 ;  /* Restore gpo2 */
     set232(siop, GPO2, OFF);                    
}

#pragma check_stack+    /* turn stack checking back on */
