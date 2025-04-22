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

MyStrcmp:   
;------------------------------------------------
    push rbp   
    mov rbp, rsp

    vmovdqu ymm1, [rdi]
    vmovdqu ymm2, [rsi] 

;create mask
    vpxor ymm5, ymm5, ymm5      ; ymm5 = 0
    vpcmpeqd ymm3, ymm5, ymm5   ; Compare 0 == 0 → all bits = 1 

;compare words
    vcmpps ymm0, ymm1, ymm2, _CMP_EQ_OQ 

;make condition in ymm0
    vpxor ymm0, ymm3    ; inverse ymm0
    vptest ymm0, ymm0   ; ymm0 AND ymm0

    je _equal 
    jmp _not_equal 

_equal:
    mov rax, 0
    jmp _end 

_not_equal:
    mov rax, 1 

_end:
    leave       
    ret         
;------------------------------------------------

