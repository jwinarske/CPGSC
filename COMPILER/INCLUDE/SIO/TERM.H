#ifndef _TERM_
#define _TERM_

int  cbuff(SIO *,FILE *);
int  dial(SIO *);
void dnload(SIO*, int (*)(SIO*, FILE*));
int  locbuff(SIO*, FILE *);
int  menu(SIO *);
int  redial(SIO *);
void set_params(SIO*);
void setup232(SIO *);
void upload(SIO*);
void term(SIO *);

#endif      /* _TERM_ */
