bits 32



global _findmaximum


segment data public data use32

format db "idk",0

segment code public code use32

_findmaximum:
    push ebp
    mov ebp,esp;stack frame
    push format
    call [printf]
    add esp,4*1
    ;[ebp+8]-list size
    ;[ebp+12]-the list
    mov ecx,[ebp+8];parcurg toate elem
    jecxz final
           mov esi,[ebp+12];load the string
           mov ebx,0
           repeta:
                lodsd
                cmp ebx,eax
                jge nu
                    mov ebx,eax
                nu:
            loop repeta
    final:
    mov eax,ebx
    mov esp,ebp
    pop ebp
    ret