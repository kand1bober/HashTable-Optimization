
;------------------------------------------------
section .data

section .text
    global MyStrcmp
 
;------------------------------------------------
MyStrcmp:
        mov     rax, rdi
        mov     rdi, rdx
        mov     edx, ecx
        vmovdqu xmm0, [rax]
        mov     eax, esi
        vpcmpestri      xmm0, [rdi], 12
        mov     eax, ecx
        ret
;------------------------------------------------
