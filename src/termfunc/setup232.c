/*-
FUNCTION NAME: setup232
        LEVEL: 3
 PROTOTYPE IN: TERM.H
  DESCRIPTION: Function to transmit BREAK and control RS-232 outputs: RTS,
               DTR, and two general-purpose outputs.
      RETURNS: void
     COMMENTS: The two general-purpose outputs are not necessarily
               mapped to RS-232 pins.
*/

#include <stdio.h>
#include <sio/siodef.h>
#include <sio/misc.h>
#include <sio/key.h>

void setup232(SIO *siop)
{
     extern char *errstr[];
     static char *statstr[] = {"OFF", "ON", "--"};
     short whichone;
     RANK errcode, rtsstat, dtrstat, gpo1stat, gpo2stat, *statp;
     short choice = 0;
     rtsstat  =  get232(siop, RTS);  dtrstat  =  get232(siop, DTR);
     gpo1stat =  get232(siop, GPO1); gpo2stat =  get232(siop, GPO2);

     while (choice != -1)     /* loop forever, reinitialize pointer */
          {
          puts("\nCURRENT RS-232 INPUT STATUS:");
          puts("\tCTS  DSR  DCD  RI   GP1  GP2");
          printf("\t%3s  %3s  %3s  %3s  %3s  %s\n\n",
            statstr[stat232(siop, CTS)],
            statstr[stat232(siop,DSR)],
            statstr[stat232(siop, DCD)],
            statstr[stat232(siop,RI)],
            statstr[stat232(siop,GPI1)],
            statstr[stat232(siop,GPI2)]);
          printf("\t%3s  %3s  %3s  %3s  %3s  %s\n\n",
            statstr[siop->status.bitmap.cts ],
            statstr[siop->status.bitmap.dsr ],
            statstr[siop->status.bitmap.dcd ],
            statstr[siop->status.bitmap.ri  ],
            statstr[siop->status.bitmap.gpi1],
            statstr[siop->status.bitmap.gpi2]);
          printf("\t%3s  %3s  %3s  %3s  %3s  %s\n\n",
            statstr[siop->delta.bitmap.cts ],
            statstr[siop->delta.bitmap.dsr ],
            statstr[siop->delta.bitmap.dcd ],
            statstr[siop->delta.bitmap.ri  ],
            statstr[siop->delta.bitmap.gpi1],
            statstr[siop->delta.bitmap.gpi2]);
          printf("\n1. Toggle RTS  [ %3s ]\n", statstr[rtsstat]  );
          printf(  "2. Toggle DTR  [ %3s ]\n", statstr[dtrstat]  );
          printf(  "3. Toggle GPO1 [ %3s ]\n", statstr[gpo1stat] );
          printf(  "4. Toggle GPO2 [ %3s ]\n", statstr[gpo2stat] );
          puts(    "5. Exit this function\n");
          printf("Enter your choice : ");
          choice = getkbch();
          switch (choice)               /* assign function & status pointer  */
               {
               case '1': whichone  = RTS; statp = &rtsstat;  break;
               case '2': whichone  = DTR; statp = &dtrstat;  break;
               case '3': whichone  = GPO1;statp = &gpo1stat; break;
               case '4': whichone  = GPO2;statp = &gpo2stat; break;
               case '5': puts("Exiting RS232 setup");
                    return;
               default:puts("\a- invalid entry -");
                    continue;
               }
          if (choice != -1)                   /* if a valid choice was made   */
               {
               if (*statp != BAD_FCN)        /* if this function is supported*/
                    *statp = !(*statp);      /* toggle its status            */
               if ( (errcode = set232(siop, whichone, *statp)) != 0)
                    printf("ERROR:  %s\n\a",errstr[errcode]);
               }
          }
}
