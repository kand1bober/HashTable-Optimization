;
;
; Function only works, if stinrgs are prepared and  
; insignificant bytes are filled with nulls 
;
; In this programm I use HUYCALL calling convention
;
;   addr of args = R9, 
;   stack: [R9] = 1 --> 2 --> 3 --> ... 
;               +0*8  +1*8  +2*8  ...
;------------------------------------------------
section .data
    _CMP_EQ_OQ equ 0x00

section .text
    global MyStrcmp

;------------------------------------------------

MyStrcmp:   
;------------------------------------------------
    pop rax     ; save return addr 

    push rsi    ; saving arguments from  
    push rdi    ; registers to stack 

;pointer to arguments 
    mov r9, rsp ; <======  DON'T TOUCH THIS MAN !!!!!!!! 
    
    push rax    ; push return addr
;------------------------------------------------

;------------------------------------------------
    push rbp   
    mov rbp, rsp

    vmovdqu ymm1, [r9]
    vmovdqu ymm2, [r9 + 32]

    vcmpps ymm0, ymm1, ymm2, _CMP_EQ_OQ 

    vptest ymm0, ymm0 
    je _not_equal 

_equal:
    mov rax, 0
    jmp _end 

_not_equal:
    mov rax, 1 

_end:
    leave       ;
    ret         ;
;------------------------------------------------
