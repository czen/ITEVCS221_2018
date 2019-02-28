name=$1
nasm -f elf $name.asm
ld -m elf_i386 -s -o $name $name.o
