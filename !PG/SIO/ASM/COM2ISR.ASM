externdata _COM2sio
PUBLIC __a_com2isr
procdef __a_com2isr
       push  ax                   ; this on system's stack
       mov   oldss, ss            ; save SS
       mov   oldsp, sp            ; save SP
       push  cs                   ; set SS:SP ...
       pop   ss                   ; ...to address ...
       mov   sp, OFFSET newstack  ; ... our local stack
             ;; -- remaining stack operations use local stack --
       push  bp
       push  bx
       push  cx
       push  dx
       push  si
       push  di
       push  es
       push  ds
       mov   ax, SEG DGROUP:_COM2sio     ; address C's data
       mov   ds, ax
       PUSH_SEG                          ; macro to push seg address on stack
       mov   ax, OFFSET DGROUP:_COM2sio  ; pass the address of Com2Sio  on stack
       push  ax
       call  _s_iadmin            ; call C interrupt administrator
       add   sp, NUMARGS          ; remove siop argument from stack
       pop   ds                   ; restore registers from local stack
       pop   es
       pop   di
       pop   si
       pop   dx
       pop   cx
       pop   bx
       pop   bp
       mov   ss, oldss            ; restore the caller's stack (SS:SP)
       mov   sp, oldsp
       mov   al, 20H              ; bid adieu to the 8259 PIC
       out   20H, al
       pop   ax
       iret                       ; allons!
__a_com2isr ENDP
