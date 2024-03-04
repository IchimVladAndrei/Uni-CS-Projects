bits 32
;An unsigned number a on 32 bits is given. Print the hexadecimal representation of a, but also the results of the circular permutations of its hex digits.

global _permutare
segment data public data use32
segment code public code use32
_permutare:
    push ebp
    mov ebp,esp ;create stack frame
    ;[ebp+8]-nr
    ;[ebp] value from the caller
    ;[ebp+4] contains the return value
    mov eax,[ebp+8]
    ror dword eax,4
    mov esp,ebp
    pop ebp
    ret