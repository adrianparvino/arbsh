ld -m elf_i386 -s -o syscall syscall.o

nasm -f elf syscall.s


