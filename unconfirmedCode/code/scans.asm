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
    call .addManuel
    mov al, '1'
    mov ecx, scanCodeToAsciiLookup+0x02
.loop:
    mov [ecx],  al
    cmp al, '9'
    je .end
    inc al
    inc ecx
    jmp .loop
.addManuel:
    ; this is needed because 0s keyboard code is greater than 9 
    ; but its ascii value is lower
    mov [scanCodeToAsciiLookup + 0x0B], byte '0'
    ret
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

    ; cmp eax, 0x1C
    ; je .end
    test al, al ; check if invalid char
    jz .end

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

    test al, 1
    jz getKeyPress ; if nothing in buffer do nothing
    
    in al, 0x60
    cmp al, 0
    je getKeyPress

    cmp al, 0x80 ; if al > 0x80 reset as thats too high
    jae getKeyPress
    ret