/*-

 ARRAY NAME:  errstr
       TYPE:  Array of char *
       FILE:  SIO.LIB
DESCRIPTION:  Messages for error codes returned by data format and baud rate
              functions.
*/

char *errstr[] =
     {
     "",
     "",
     "Function not supported",                       /* 2   #define BAD_FCN  */
     "Argument out of range",                        /* 3   #define OR_ARG   */
     "Argument not supported",                       /* 4   #define BAD_ARG  */
     "Illegal device number",                        /* 5   #define BAD_PORT */
     "Device not installed",                         /* 6   #define NO_PORT  */
     "Device not available",                         /* 7   #define NO_SIO   */
     "Device already open",                          /* 8   #define OPEN_NOW */
     "No such device or device not open",            /* 9   #define NO_CLOSE */
     "Transfer Cancelled from keyboard",             /* 10  #define KEY_CAN  */
     "File not found",                               /* 11  #define NO_FIL   */
      ""                                             /* NIL array terminator */
      };
