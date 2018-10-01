/*- 
GLOBAL variables for XMOD.LIB 
Compile these and add them to he XMODEM library
*/

#include <stdio.h>                   /* Needed by modem.h                 */
#include <sio/siodef.h>
#include <sio/xmod.h>

struct rcvpacket *rcvbuffp = NIL;    /* pointer to receive packet buffer  */
int    paksize = 0;                  /* number of uint8_ts to xmit or rcv    */
uint16_t (*r_errckp)()= NIL;           /* pointer to the error check funct  */
char   *ckvname = 0;                 /* string indicating CRC or cksum    */
uint8_t   csync= 0;                     /* "NAK" for checksum, 'C' for crc   */
uint16_t *crctblp = NIL;               /* pointer to the CRC lookup table   */
