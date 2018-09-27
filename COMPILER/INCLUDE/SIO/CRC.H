#ifndef   _CRC_
#define  _CRC_
/**** FUNCTION PROTOTYPES ****/

USHORT  crchware(USHORT ,USHORT ,USHORT );
USHORT  crcrevhware(USHORT ,USHORT ,USHORT );
void    crcrevupdate(USHORT ,USHORT *,USHORT *);
void    crcupdate(USHORT, USHORT*, USHORT *);
USHORT *mk_crctbl(USHORT ,USHORT (*)(USHORT, USHORT, USHORT));
USHORT  polydiv(USHORT, USHORT, USHORT);

#define  CRCCCITT  0x1021         /* CCITT polynomial                */
#define  CCCITT_REV 0x8408        /* reverse CCITT polynomial        */
#define  CRC16       0x8005       /* CRC16 polynomial                */
#define  CRC16_REV 0xA001         /* reverse CRC16 polynomial 0x8005 */

/*#define  crcupdate(d,a,t)     *(a) = (*(a) << 8) ^ (t)[(*(a) >> 8) ^ (d)];
#define  crcupdate16(d,a,t) *(a)=((*(a)>>8) ^ (t)[(*(a) ^ (d)) &0x00ff])*/

#endif   /* _CRC_ */
