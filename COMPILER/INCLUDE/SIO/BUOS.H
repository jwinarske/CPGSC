#ifndef  _BUOS_
#define  _BUOS_

/**** FUNCTION PROTOTYPES ****/
int    s_fgetc(SIO*);
int    s_fputc(SIO*, FAST);
BYTE   s_getc(SIO *);
int    s_iflush(SIO *);
int    s_inchar(SIO *);
int    s_ircv(SIO *);
int    s_ircv_xoxo(SIO *);
int    s_ircv_rcts(SIO *);
int    s_ircvstat(SIO *);
void   s_putc(SIO *, int);
FAST   s_rcv(SIO *);
FAST   s_rcvstat(SIO *);
void   s_xmit(SIO *, FAST);
FAST   s_xmitstat(SIO *);
void   s_ixmit(SIO *, FAST);
FAST   s_ixmitstat(SIO *);
int    vset232(SIO*, struct vout232_ *, BOOL);
int    vsetbits(SIO* , struct vregbits_ *, RANK);
int    vsetbr(SIO*, struct vbaud_ *, RANK );
short  vstat232(SIO*, struct vin232_ *);

/******* XON *******/
void   xon(SIO * );
void   xoff(SIO *);
USHORT flow_req_xoxo(SIO *, ... );

void   ixon(SIO * );
void   ixoff(SIO *);
USHORT iflow_req_xoxo(SIO *, ... );

/******* RTS *******/
void   rtson(SIO *siop);
void   rtsoff(SIO *siop);
USHORT flow_req_rcts(SIO *siop, ...);

void irtson(SIO *siop);
void irtsoff(SIO *siop);
USHORT iflow_req_rcts(SIO *siop, ...);

/******** NONE *******/
void   flowon_none(SIO *siop);
void   flowoff_none(SIO *siop);
USHORT flow_req_none(SIO *siop, ...);

short  rs232_ion(SIO *);
short  rs232_ioff(SIO *);
short  serr_ion(SIO *);
short  serr_ioff(SIO *);
short  tx_ion(SIO *, short, short);  
short  tx_ioff(SIO *, short);     
short  rcv_ion(SIO *);
short  rcv_ioff(SIO *);

#endif   /*_BUOS_*/
