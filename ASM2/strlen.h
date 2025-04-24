
inline int MyStrlen(const char* str)
{   
    int length = 0;

    __asm__(                      
    ".intel_syntax noprefix\n\t"    // change syntax

    "endbr64\n\t"                                     
    "mov        rdi, rax\n\t"              
    "vpxor      xmm0, xmm0, xmm0\n\t"      
    "and        eax, 0xfff\n\t"            

    "vpcmpeqb   ymm1, ymm0, [rdi]\n\t"     
    "vpmovmskb  eax, ymm1\n\t"             
    "test       eax, eax\n\t"              
    "tzcnt      eax, eax\n\t"            
    "vzeroupper\n\t"                        

    ".att_syntax prefix"    // change syntax

    : "=a" (length)
    : "a" (str) 
    : "xmm0", "rdi", "ymm1", "ymm0", "cc"
    );                       

    return length;     
}
