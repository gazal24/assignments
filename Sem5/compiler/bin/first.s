# 1 "first.S"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "first.S"
# 1 "/usr/include/asm/unistd.h" 1 3 4

# 1 "/usr/include/asm/unistd_32.h" 1 3 4
# 3 "/usr/include/asm/unistd.h" 2 3 4
# 2 "first.S" 2
# 1 "/usr/include/syscall.h" 1 3 4
# 1 "/usr/include/sys/syscall.h" 1 3 4
# 25 "/usr/include/sys/syscall.h" 3 4
# 1 "/usr/include/asm/unistd.h" 1 3 4
# 26 "/usr/include/sys/syscall.h" 2 3 4






# 1 "/usr/include/bits/syscall.h" 1 3 4






# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 8 "/usr/include/bits/syscall.h" 2 3 4
# 33 "/usr/include/sys/syscall.h" 2 3 4
# 1 "/usr/include/syscall.h" 2 3 4
# 3 "first.S" 2


.file "first.S"
.section .rodata
L1:
   .string "My first program\n"
L2:
.text
.globl _start
_start:
movl $(4), %eax
   movl $(1), %ebx
   movl $L1, %ecx
   movl $(L2-L1), %edx
   int $128
   movl $(1), %eax
   movl $0, %ebx
   int $128
