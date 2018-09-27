#ifndef   _T4_
#define   _T4_

/**** FUNCTION PROTOTYPES ****/
USHORT bit2run(BYTE *, USHORT, USHORT *);
int    run2bits(FILE *, FILE *, BYTE *, short, short *, short);
short  t4encode(FAST *, short, FAST *);
int    t4decode(FILE *, FILE *, short *, USHORT, FAST *, USHORT);

/*
STRUCTURE:  MHcode (typedef)
 FUNCTION:  Contains a description of a Huffman code.
*/
typedef struct
     {
     USHORT t4token;          /* The Huffman code                 */
     USHORT t4token_len;      /* Number of bits in same           */
     } MHcode;

/*
STRUCTURE:  T4NODE (typedef)
 FUNCTION:  Contains a node for the Huffman code binary tree.
*/
typedef struct t4node
    {
    struct t4node near *zero; /* pointer to the next zero branch  */
    struct t4node near *one;  /* pointer to the next one branch   */
    short  run_len;
    } near T4NODE;

#define NOTTERMINAL   12000
#define WHITE        0x0000
#define BLACK        0xFFFF
#define EOL_MARKER    32512
#define EOL_INDEX       104   /* Index into the encoding tables   */
#define BYTES_PER_LINE  216
#define LINES_PER_PAGE 1728

#endif   /*_T4_ */
