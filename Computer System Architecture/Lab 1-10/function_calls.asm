bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, printf, fopen, fclose, fread, fwrite, rename, remove
import exit msvcrt.dll 
import fopen msvcrt.dll 
import fread msvcrt.dll 
import fwrite msvcrt.dll 
import fclose msvcrt.dll 
import rename msvcrt.dll
import remove msvcrt.dll
import printf msvcrt.dll
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; A text file is given. Read the content of the file, count the number of letters 'y' and 'z' and display the values on the screen. The file name is defined in the data segment.

inputfile dd 'a.txt',0
modread dd 'r',0
c dd 0
cnt dd 0
handle1 dd -1
handle2 dd -1
eroare db 'error',0
format dd "%d",0
; our code starts here
segment code use32 class=code
    start:
        ; ...
        push dword modread ;how to act with file
        push dword inputfile ;name of the file
        call[fopen]
        add esp,4*2;free 2 dwords from stack
        mov[handle1],eax
        cmp eax,0;check if there is any error when opening the file
        je theend
        again:
            skip:
            push dword [handle1]
            push dword 1;1 byte
            push dword 1;1 time
            push dword c ;where to save the byte
            call [fread]
            add esp,4*4
            cmp eax,0;check if any error during file
            je theend
            mov ebx,[c]
            cmp ebx,'y'
            je increase
            cmp ebx,'z'
            je increase
            jne skip;if not an y or z just skip

            
                increase:
                inc dword [cnt]
               
        loop again
        theend:
        push dword [cnt] ;cnt stores the number of y and z
        push dword format
        call [printf]
        add esp,4*2
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program