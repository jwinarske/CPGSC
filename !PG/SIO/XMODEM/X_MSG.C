/*-

   ARRAY NAME:  x_msg
         TYPE:  char *
 PROTOTYPE IN:  XMOD.H
      LIBRARY:  XMODEM.LIB
  DESCRIPTION:  Array of pointers to message strings used in XMODEM
                file transfer modules.
     COMMENTS:  These rank-equivalent constants are shown in comments.
*/

char *x_msg[] =
     {
     "\nTransfer cancelled from keyboard.\a",             /* E_USRCAN   0  */
     "Input file is empty.\a",                            /* E_FILEMTY  1  */
     "Timeout waiting for ACK.",                          /* E_NOACK    2  */
     "Receiver cancelled transfer.\a",                    /* E_RCVCAN   3  */
     "Resending last packet.",                            /* E_BADPAK   4  */
     "End of file read.",                                 /* E_EOF      5  */
     "\nWarning: receiver did not acknowledge EOT.\a",    /* E_LASTACK  6  */
     "Successful transmission.",                          /* E_SNDOK    7  */
     "Fatal error reading disk.",                         /* E_DSKREAD  8  */
     "Timeout waiting for SOH.",                          /* E_NOSOH    9  */
     "\nData error detected. Requesting retransmission.", /* E_BADCKV   10 */
     "Transfer cancelled by sender.\a",                   /* E_SNDCAN   11 */
     "\nByte received, but not SOH.",                     /* E_BADSOH   12 */
     "\nTimeout waiting for packet data.",                /* E_NODATA   13 */
     "\nBad packet number.",                              /* E_PAKNUM   14 */
     "\nSender missed ACK.",                              /* E_SNDACK   15 */
     "Fatal packet sequence error.\a",                    /* E_PAKSEQ   16 */
     "Fatal error writing disk.",                         /* E_DSKWRITE 17 */
     "Successful reception."                              /* E_RCVOK    18 */
     };
