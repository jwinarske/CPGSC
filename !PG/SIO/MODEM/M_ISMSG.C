/*-
FUNCTION NAME:  m_ismessage
        LEVEL:  3
 PROTOTYPE IN:  MODEM.H
      LIBRARY:  MODEM.LIB
  DESCRIPTION:  Converts modem message to an integer code.
      RETURNS:  int: an integer result code or -1 if the code is not
                valid or is not a terminal.  Calls parser function if
                indicated.
     COMMENTS:
*/

#include <stdlib.h>
#include <string.h>
#include <sio\siodef.h>
#include <sio\modem.h>


static struct parse_info m_result[] =
     {
/* String     Terminal  Code	 Parser */
        { "OK",          TRUE,  M_OK,       NIL },
        { "NO CARRIER",  TRUE,  M_NODCD ,   NIL },
        { "ERROR",       TRUE,  M_CMDERR,   NIL },
        { "NO DIAL",     TRUE,  M_NOTONE,   NIL },
        { "BUSY",        TRUE,  M_BUSY  ,   NIL },
        { "NO ANSWER",   TRUE,  M_NOANSW,   NIL },
        { "RING",        TRUE,  M_RING,     NIL },
        { "CONNECT",     FALSE, M_CONN,     m_parsemsg },
        { "PROTOCOL:",   FALSE, M_PROTOCOL, m_parsemsg },
        { "COMPRESSION:",FALSE, M_COMPRESS, m_parsemsg },
        { "CARRIER",     FALSE, M_CARRIER,  m_parsemsg },
     };



int m_ismessage(SIO* siop, char *str)
{
     int row;
     int numrows = arraysize(m_result);            /* macro                    */

     for (row = 0; row < numrows; row++)           /* for every row            */
          {
          if (strstr(str, m_result[row].message))  /* string submatch?  */
               {
               if (m_result[row].fn != NIL)     /* if processing needed */
                    m_result[row].fn(siop, &m_result[row], str);
               if (m_result[row].terminal)
                    return m_result[row].id;
               else
                    return MSG_NON_TERMINAL;   /* continue                 */
               }
          }
     return MSG_INVALID;                    /* -1 if not a substring    */
}
