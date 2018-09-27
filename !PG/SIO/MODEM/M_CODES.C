/*-45
 ARRAY NAME:  m_codes
    LIBRARY:  MODEM.LIB
DESCRIPTION:  Strings for modem functions.
   COMMENTS:  Corresponding constants are shown in comments.
*/

char *m_codes[] =
     {
     "Successful",                           /*0  M_OK         */
     "Connection Established",               /*1  M_CONN       */
     "Call incoming",                        /*2  M_RING       */
     "No connection Established",            /*3  M_NODCD      */
     "Command Error",                        /*4  M_CMDERR     */
     "No Dialtone",                          /*5  M_NOTONE     */
     "Number Dialed is Busy",                /*6  M_BUSY       */
     "No answer",                            /*7  M_NOANSW     */
     "Unknown Modem Response",               /*8  M_BADMSG     */
     "Didn't hear RING report from modem",   /*9  M_NORING     */
     "Call Already in Progress",             /*10 M_ONLINE     */
     "Blank Dial String",                    /*11 M_NILNUM     */
     "Operation cancelled by user",          /*12 M_USRCAN     */
     "Modem Reset Failed",                   /*13 M_NORESET    */
     "Modem Fails ID request",               /*14 M_NOID,      */
     "Config. error: Out of memory",         /*15 M_CONFIG_MEM */
     "Modem failed to configure",            /*16 M_CONFIG_NOK */
     "Connection Established",               /*17 M_DCD_HIGH   */
     };
