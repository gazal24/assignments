#include <asm/unistd.h>
#include <syscall.h>
#define STDOUT_FILENO 1

.file "first.S"
.section         .rodata
L1:
   .string "My first program\n"
L2:
.text
.globl _start
_start:
movl $(SYS_write), %eax
   movl $(STDOUT_FILENO), %ebx
   movl $L1, %ecx
   movl $(L2-L1), %edx
   int  $128
   movl $(SYS_exit), %eax
   movl $0, %ebx
   int  $128
