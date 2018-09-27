/*- 
GLOBAL variables for XMOD.LIB 
Compile these and add them to he XMODEM library
*/

#include <stdio.h>                   /* Needed by modem.h                 */
#include <sio\siodef.h>
#include <sio\xmod.h>

struct rcvpacket *rcvbuffp = NIL;    /* pointer to receive packet buffer  */
int    paksize = 0;                  /* number of bytes to xmit or rcv    */
USHORT (*r_errckp)()= NIL;           /* pointer to the error check funct  */
char   *ckvname = 0;                 /* string indicating CRC or cksum    */
BYTE   csync= 0;                     /* "NAK" for checksum, 'C' for crc   */
USHORT *crctblp = NIL;               /* pointer to the CRC lookup table   */
