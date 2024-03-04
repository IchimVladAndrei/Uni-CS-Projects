bits 32 

global start        


extern exit,fopen,fclose,fread,fprintf,fwrite,scanf,printf
import printf msvcrt.dll
import exit msvcrt.dll 
import scanf msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import fread msvcrt.dll
import fprintf msvcrt.dll
import fwrite msvcrt.dll


segment data use32 class=data
    ; 
nrcuv dw 0
raspuns db 0
numar resb 1
numefis times 10 db 0
modacces db 'r',0
fnr db "%d",0
fnume db "%s"
fd dd -1
caracter db -1
buffer resb 100
rezultat resb 100

segment code use32 class=code
    start:
        ; ...
        push dword numar;numar
        push dword fnr
        call [scanf]
        add esp,4*2
        push dword numefis
        push dword fnume
        call [scanf]
        add esp,4*2
        push dword modacces
        push dword numefis
        call [fopen]
        add esp,4*2
        cmp eax,0
        je final
        mov [fd],eax
        bucla:
            push dword [fd]
            push dword 100
            push dword 1
            push dword buffer
            call [fread]
            add esp,4*4
            cmp eax,0
            je inchide
            mov esi,buffer
            mov edi,rezultat
            mov ecx,100
            transformare:
                lodsb
                cmp al,' '
                push eax
                jne nuspatiu
               
                inc word[nrcuv]
                nuspatiu:
                mov ax,word[nrcuv]
                div byte[numar]
                cmp ah,0
                jne numultiplu
                pop eax
                stosb
                numultiplu:
               
            loop transformare
            
           
             push dword rezultat
             push dword fnume
             call [printf]
             add esp,4*2
            
            mov ah,byte[numar]
            mov al,byte[nrcuv]
            sub ah,al
            mov byte[raspuns],ah
            
            push dword [raspuns] 
            push dword fnr
            call [printf]
            add esp,4*2
                
            
         
         
         inchide:
         push dword [fd]
         call [fclose]
         add esp,4
        final:
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
