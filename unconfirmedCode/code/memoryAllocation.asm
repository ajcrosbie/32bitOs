
section .data
    bData times 4096 db 0
    bmask times 16 db 0 ; each bit in the wmask corrisponds to 32bytes in the bData
section .text
    global mallocinator


mallocinator:
    ; passed into this function is an integer for the number of bytes that the program wants reserving
    push ebp 
    mov ebp, esp
    mov esi, [ebp+8]; it seems like they made some strange choices abt how to pass variables, and they just get sent through the stack
    ;esi = number of bytes needed and therefore the number of contiguous bits
    pusha
    xor eax, eax

.searchSpace:
    mov edx, [bmask+eax] ; current byte to search in bmask
    