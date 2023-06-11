INCLUDE CPGSC.MAC       ; contains model-dependent macros
;.....................................................
;MASM COMMAND LINE:
;MASM CPGSC,, /Ml XXXX YYYY;
;Where XXXX is 
;     For LARGE Model: /DLARGEMODEL
;     For SMALL Model: /DSMALLMODEL
;Where YYYY is 
;     For 1 SIO, /DCOM1SIO 
;     For 2 SIOs /DCOM1SIO  /DCOM2SIO 
;     For 3 SIOs /DCOM1SIO  /DCOM2SIO   /DCOM3SIO 
;     For 4 SIOs /DCOM1SIO  /DCOM2SIO   /DCOM3SIO   /DCOM4SIO 
;.....................................................
;Global/external functions in this file:             ;
; one or more of the comXisr's will be public also   ;
PUBLIC      __a_inport, __a_outport                  ;
externfunct _s_iadmin           ;macro               ;
;....................................................;
CODESEG                        ; macro declaring code segment
DATAGROUP                      ; macro declaring DGROUP

STACKSIZ  EQU 128
           ;; new stack and storage for SS/SP during interrupt
           DB  STACKSIZ-2 dup (?)       ; stack size
newstack   DW  0
oldss      DW  0
oldsp      DW  0
ASSUME DS:NOTHING, ES:NOTHING, SS:NOTHING
;;.....................................................................;
; FUNCTION NAME:  __a_com1isr, __a_com2isr, __a_com3isr, __a_com4isr   ;
;       LIBRARY:  PCDOS.LIB                                            ;
;  DESCRIPTION:   Main ISR's for devices 0-3 (COM1-4).                 ;
;      COMMENTS:  All four handlers share the same stack--this is fine.;
;......................................................................;
IFDEF COM1SIO      ;                                                   ;
INCLUDE COM1ISR.ASM;                                                   ;
ENDIF              ;                                                   ;
;..................;                                                   ;
IFDEF COM2SIO      ;                                                   ;
INCLUDE COM2ISR.ASM;                                                   ;
ENDIF              ;                                                   ;
;..................;                                                   ;
IFDEF COM3SIO      ;                                                   ;
INCLUDE COM3ISR.ASM;                                                   ;
ENDIF              ;                                                   ;
;..................;                                                   ;
IFDEF COM4SIO      ;                                                   ;
INCLUDE COM4ISR.ASM;                                                   ;
ENDIF              ;                                                   ;
;..................;                                                   ;
;;.....................................................................;
;.....................................................;
; FUNCTION NAME:  __a_outport                         ;
;       LIBRARY:  ASM.LIB                             ;
;   DESCRIPTION:  Port output routine for the IBM PC. ;
;       RETURNS:  void                                ;
; SYNTAX FROM C:  __a_outport(BYTE * port, FAST data) ;
;.....................................................;
procdef __a_outport
        push bp
        mov  bp,sp
        mov  dx, [bp + ARG1]        ; low order byte of pointer
        LOAD_DATA                   ; macro to get data off stack 
        out  dx, al                 ; null out high byte
        pop  bp
        ret
__a_outport ENDP
;...................................................;
; FUNCTION NAME:  __a_inport                        ;
;       LIBRARY:  ASM.LIB                           ;
;   DESCRIPTION:  Port input routine for the IBM PC.;
;       RETURNS:  FAST                              ;
; SYNTAX FROM C:  c = __a_inport(BYTE *port)        ;  
;...................................................;
procdef __a_inport
        push bp
        mov  bp,sp
        mov  dx, [bp + ARG1]        ; low order byte of pointer
        in   al, dx                 ; data returned in ax (al)
        and  ax, 00FFh              ; reset hi bitso can be used as an int
        pop  bp
        ret
__a_inport ENDP
endpseg           ;macro
END
