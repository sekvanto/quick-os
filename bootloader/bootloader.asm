;******************************************
; bootloader.asm
; A Simple Bootloader
;******************************************
bits 16
start: jmp boot

;; constant and variable definitions
msg db "Welcome to My Operating System!", 0x0
msg_len equ $ -msg
cursor_xpos dd 0x0
cursor_ypos dd 0x0

; move a cursor to a specific location
; and remember this location
; bh = Y coordinate
; bl = X coordinate
MovCursor:
  mov dh, bh ; row
  mov dl, bl ; column
  mov bh, 0x0 ; page number
  mov ah, 0x02 ; set cursor position
  int 0x10 ; call BIOS - Video
  ret

; print a character on screen, at the cursor position previously
; set by MovCursor
; al = character to print
; bl = text color
; cx = number of times the character is repeated
PutChar:
  mov bh, 0x0
  mov ah, 0x09 ; write character at cursor pos
  int 0x10
  ret

; print a string
; ds:si = zero terminated string
Print:
  ;; set cursor to (0,0)
  mov bh, 0x0
  mov bl, 0x0
  call MovCursor

  ;; clear screen
  mov al, " "
  mov bl, 0x0 ; black
  mov cx, 0x1000 ; clear screen
  call PutChar

  ;; set cursor to (0,0)
  mov bh, 0x0
  mov bl, 0x0
  call MovCursor

  ;print string
.loop:
  lodsb ; load current character from ds:si to al and increment si
  cmp al, 0x0
  je .end
  mov bl, 0x5 ; magenta
  mov cx, 0x1 ; print one character
  call PutChar
  inc word [cursor_xpos]
  mov bh, [cursor_ypos]
  mov bl, [cursor_xpos] ; only short strings are supported now
  call MovCursor
  jmp .loop

.end:
  ret

boot:
  cli ; no interrupts
  cld ; all that we need to init
  
  push cs
  pop ds
  mov si, msg
  call Print

  mov ax, 0x50

  ;; set the buffer
  mov es, ax
  xor bx, bx

  mov al, 2 ; read 2 sector
  mov ch, 0 ; track 0
  mov cl, 2 ; sector to read (The second sector)
  mov dh, 0 ; head number
  mov dl, 0 ; drive number

  mov ah, 0x02 ; read sectors from disk
  int 0x13 ; call the BIOS routine
  jmp [0x500 + 0x18] ; jump and execute the sector! (0x500 + offset
                     ; of e_entry in ELF header of OS executable, see man elf)

  hlt ; halt the system

; We have to be 512 bytes. Clear the rest of the bytes with 0
times 510 - ($-$$) db 0
dw 0xAA55 ; Boot Signiture
