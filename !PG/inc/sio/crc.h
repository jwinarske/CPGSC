#ifndef   _CRC_
#define  _CRC_
/**** FUNCTION PROTOTYPES ****/

uint16_t  crchware(uint16_t ,uint16_t ,uint16_t );
uint16_t  crcrevhware(uint16_t ,uint16_t ,uint16_t );
void    crcrevupdate(uint16_t ,uint16_t *,uint16_t *);
void    crcupdate(uint16_t, uint16_t*, uint16_t *);
uint16_t *mk_crctbl(uint16_t ,uint16_t (*)(uint16_t, uint16_t, uint16_t));
uint16_t  polydiv(uint16_t, uint16_t, uint16_t);

#define  CRCCCITT  0x1021         /* CCITT polynomial                */
#define  CCCITT_REV 0x8408        /* reverse CCITT polynomial        */
#define  CRC16       0x8005       /* CRC16 polynomial                */
#define  CRC16_REV 0xA001         /* reverse CRC16 polynomial 0x8005 */

/*#define  crcupdate(d,a,t)     *(a) = (*(a) << 8) ^ (t)[(*(a) >> 8) ^ (d)];
#define  crcupdate16(d,a,t) *(a)=((*(a)>>8) ^ (t)[(*(a) ^ (d)) &0x00ff])*/

#endif   /* _CRC_ */

