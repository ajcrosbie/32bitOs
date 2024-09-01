; ; public scans


section .data
    tableComplete db 0
    scanCodeToAsciiLookup db  128 dup(0)

section .text
    global scans
    global constructTable


constructTable:
    mov al, [tableComplete]
    cmp al, 1
    je .end
    call makeTable
.end:
    ret
makeTable:
    mov al, '0'
    mov ecx, scanCodeToAsciiLookup+0x02
.loop:
    mov [ecx],  al
    cmp al, '9'
    je .end
    inc al
    inc ecx
    jmp .loop
.end:
    mov byte [tableComplete], 1
    mov byte [scanCodeToAsciiLookup+0x1C], 0
    ret
 
scans:
    push ebp  
    mov ebp, esp
    mov esi, [ebp+8]
    pusha

.readChar:
    call getKeyPress
    movzx eax, al
    mov al, [scanCodeToAsciiLookup+eax]

    test al, al ; check if invalid char
    jz .end
    cmp al, 0
    je .end
    mov [esi], al
    inc esi
    jmp .readChar
.end:
    mov [esi], byte 0
    popa
    mov esp, ebp
    pop ebp
    ret

getKeyPress:
    in al, 0x64
    test al, 1 ; if test is 0 then no charracter in buffer
    jz getKeyPress
    in al, 0x60 ;read scan from data port
    ret
