/*-
FUNCTION NAME: br_to_bcode
  DESCRIPTION: Converts an integer number to a baud rate code for use by
               the setbaud function.
        LEVEL: 3
 PROTOTYPE IN: SIODEF.H
      LIBRARY: SIO.LIB
     RETURNS : int: The baud code or -1 if the integer is not in the table.
     COMMENTS: br_2bc_table is a two-element look-up table containing integers
               on the left and baud rate codes on the right.
*/

#include "sio/siodef.h"

#define WIDTH 2

uint16_t br_2bc_table[][WIDTH] = {
  
   {300,   BAUD300 }, {600,   BAUD600 }, {1200,  BAUD1200},{2400,  BAUD2400 },
   {4800,  BAUD4800}, {7200,  BAUD7200}, {9600,  BAUD9600}, {14400, BAUD14K4},
   {19200, BAUD19K2}, {28800, BAUD28K8}, {38400L, BAUD28K8}, {57600L, BAUD57K6},
};

int br_to_bcode(uint16_t baudrate)
{
     int i;
     int numrows = WIDTH * arraysize(br_2bc_table);
     for (i = 0; i < numrows; i++)
          {
          if (baudrate == br_2bc_table[i][0])
               return br_2bc_table[i][1];
          }
     return -1;
}
