/*-
FUNCTION NAME: set_params
        LEVEL: 3
 PROTOTYPE IN: TERM.H
  DESCRIPTION: Function to set baud rate, parity, datalength, and stop bits.
      RETURNS: void
     COMMENTS:
*/

#include <stdio.h>
#include <stdlib.h>
#include <sio/siodef.h>
#include <sio/misc.h>
#include <sio/key.h>

#ifndef gets
extern char *gets(char *buffer);
#endif
extern char *errstr[], *sbstr[], *parstr[], *dlstr[], *brstr[];

/* change data format and baud rate */

void set_params(SIO *siop)
{
     RANK choice, errcode;
     int whichone = 0;
     short baudnow;
     char keybuff[4];
     while (whichone != -1)             /* loop forever, reset pointer */
          {
          puts("\nCURRENT SETTINGS:\n");
          if ( (baudnow = getbaud(siop)) < 0)
               baudnow = BAD_FCN;
          printf("1. Baud Rate [ %-6.6s ]\n", brstr[baudnow]);
          printf("2. Parity    [ %-6.6s ]\n", parstr[getformat(siop, PARITY)]);
          printf("3. Stop bits [ %-6.6s ]\n", sbstr[getformat(siop, STOPS)]);
          printf("4. Data Bits [ %-6.6s ]\n", dlstr[getformat(siop, DATALEN)]);
          printf("5. Exit this function.\n");
          printf("Enter your choice: ");
          choice = getkbch();
          switch (choice)
               {
               case '1': whichone = BAUD;  break;
               case '2': whichone = PARITY; break;
               case '3': whichone = STOPS; break;
               case '4': whichone = DATALEN; break;
               case '5': puts("\nExiting format select");
                    return;
               default:  puts("\n\a- invalid entry -");
                    continue;
               }
          if (whichone != -1)           /* if a valid choice was made  */
               do
                    {
                    printf("\nEnter code for new value and press RETURN: ");
                    gets(keybuff);
                    choice = atoi(keybuff);
                    if (whichone == BAUD)
                         errcode = setbaud(siop, choice);
                    else
                         errcode = setformat(siop, whichone, choice);
                    if (errcode != 0)
                         printf("ERROR:  %s\n\a",errstr[errcode]);
                    } while (errcode !=  0);
          }
}
