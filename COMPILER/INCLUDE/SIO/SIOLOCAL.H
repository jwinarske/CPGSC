#ifndef _SIOLOCAL_
#define _SIOLOCAL_

#undef   NUL
#undef   NIL
#undef   EOF
#undef   TRUE
#undef   BOOL
#undef   BYTE
#undef   DOS_EOF

#define  NIL      		(void*) 0      /* pointer constant               */
#define  NUL      		'\0'           /* ASCII  constant                */
#define  EVER     		;;             /* used in "for (EVER)"           */
#define  FALSE    		0
#define  TRUE     		!FALSE
#define  DOS_EOF  		0x1A           /* end-of-file for text files     */
#define  MAX_NAME_LEN 15
#define  MAX_PATH_LEN  64              /* 63 + NUL byte                  */
#define arraysize(array)     (sizeof(array) / sizeof(array[0]))

#ifndef  EOF
#define  EOF      -1
#endif

typedef  unsigned char      BYTE;
typedef  short              FAST;
typedef  unsigned short     REG;
typedef  short              MASK;
typedef  unsigned short     USHORT;
typedef  unsigned short     RANK;
typedef  unsigned short     BOOL;
typedef  unsigned long int  ULONG;
typedef  void               VOID;
typedef  struct sio         SIO;
typedef void (_interrupt far  *INTPTR)();

/**** Model-independent NULLs ****/

#ifndef NULLDP
#define NULLDP (void *) 0              /* NULL pointer to data           */
#endif

#ifndef NULLFP
#define NULLFP (void(*)()) 0           /* NULL * to function returning   */
#endif

#ifndef FAR_NULL
#define FAR_NULL ( (void far *) 0)     /* far NULL                       */
#endif

#ifndef NEAR_NULL
#define NEAR_NULL ( (void near *) 0 )  /* near NULL                      */
#endif

#define DUMMYC NUL                     /* use for dummy arugments        */
#define DUMMYI 0
#define DUMMYP NULLDP
#define DUMMYL 0L
#endif   /* _SIOLOCAL_ */
