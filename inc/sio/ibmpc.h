#ifndef  _IBMPC_
#define  _IBMPC_

#ifndef __GNUC__
#include <dos.h>        /* for _enable/_disable */
#include <conio.h>
#endif
/* NOTICE:
*   One or more of the following must either be defined here or passed in
*   on the compiler's command line:
*       #define COM1SIO       (Com1)
*       #define COM2SIO       (Com2)
*       #define COM3SIO       (Com3)
*       #define COM4SIO       (Com4)
*/

/**** FUNCTION PROTOTYPES ****/
unsigned  __peekw(int, int);
#define   __peekw(o,s) (*((int far*) (((long)(s) << 16) | (o)))) /* (offset,seg) */
#define   __sys_disable()    _disable      /* Use Microsoft runtime */
#define   __sys_enable()     _enable       /* Use Microsoft runtime */
void      __delay(unsigned);
void      __sysintroff(SIO *,RANK);
void      __sysintron(SIO *, RANK);
bool      __isport(RANK);
int       __s_waitch(SIO *, unsigned);

/* C prototypes for assembler functions */
void     _a_outport(uint8_t*, FAST);
FAST     _a_inport(uint8_t*);


#ifdef COM1SIO
void _interrupt far _a_com1isr(void);    /* Declaration of ISR    */
#endif

#ifdef COM2SIO
void _interrupt far _a_com2isr(void);
#endif

#ifdef COM3SIO
void _interrupt far _a_com3isr(void);
#endif

#ifdef COM4SIO
void _interrupt far _a_com4isr(void);
#endif

/**** MISCELLANEOUS MANIFEST CONSTANTS ****/
#define MAX_PORTS 4                 /* Maximum ports Supported in the System */
#define TIMER_LO 0x46C              /* Location of timer lsb of timer        */

/**** MANIFEST CONSTANTS FOR COM PORTS ****/
#define  COM1 (uint8_t*) 0x3f8
#define  COM2 (uint8_t*) 0x2f8
#define  COM3 (uint8_t*) 0x3E8
#define  COM4 (uint8_t*) 0x2E8

/**** INTERRUPTS USED WITH COM PORTS ****/
#define I_COM1   0x0C
#define I_COM2   0x0B
#define I_COM3   I_COM1
#define I_COM4   I_COM2

/**** Constants 8259 PIC ****/
#define IMR       0x21    /* Port addresss of the IMR   */          
#define IMR_IRQ4  0xEF    /* Mask to reset bit 4 in IMR */ 
#define IMR_IRQ3  0xF7    /* Mask to reset bit 3 in IMR */


#endif   /* _IBMPC_*/
