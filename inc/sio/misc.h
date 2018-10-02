#ifndef _MISC_
#define _MISC_

uint8_t *bigbuff(uint16_t ,uint16_t ,uint16_t *);
void  putbin(uint16_t);
FILE *rfopen(char *,char *, size_t);
FILE *wfopen(char *,char *, size_t);
int  str_atoi(char *);
void haktc(void);
char *fgets_wrapper(char *, size_t, FILE *);

#endif     /* _MISC_ */

