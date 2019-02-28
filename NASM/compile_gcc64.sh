# usage: ./compile.sh <name without extension>
name=$1
nasm -f elf64 -l $name.lst $name.asm
gcc -o $name  $name.o
