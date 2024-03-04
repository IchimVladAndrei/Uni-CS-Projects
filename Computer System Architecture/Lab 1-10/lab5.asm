bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; ...
    
 s1 db 'a', 'b', 'c', 'b', 'e', 'f'
 len1 equ $-s1
 s2 db  '1', '2', '3', '4', '5'
 len2 equ $-s2
 d times len1+len2 db 0
 
 ; our code starts here
segment code use32 class=code
    start:
        ; ...
       mov esi,0
       mov ecx,len2 
       jecxz gata
       vlad:
            mov al,[s2+esi]
            test esi,1 ;zf=1 impar
            jnz sari
            mov [d+esi],al
            sari:
            inc esi 
       loop vlad 
       gata:
       mov ecx,len1

       jecxz gatit
       andrei:
            mov al,[s1+esi-len2]
            test esi,1 
            jnz sari2
            mov [d+esi],al
            sari2:
            inc esi
        loop andrei
        gatit:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
