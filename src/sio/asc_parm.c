/*-

 ARRAY NAME:  sbstr, parstr, dlstr, brstr
       TYPE:  Array of char *
       FILE:  SIO.LIB
DESCRIPTION:  ASCII strings for baud rate and data formats.
   COMMENTS:  Use the now member of each structure to index into these
              arrays.
*/

char *sbstr[]  =  { "1", "1 1/2", "2" };
char *parstr[] =  { "None", "Odd", "Even", "Mark", "Space" };
char *dlstr[]  =  { "5", "6", "7", "8" };
char *brstr[]  =  { "50",   "75",    "110",   "134.5", "150",   "300",  "600", 
                    "1200", "1800",  "2000",  "2400",  "3600",  "4800", "7200", 
                    "9600", "14.4K", "19.2K", "28.8K", "38.4K", "57.6K",  "115.2K" };
