# usage: ./compile.sh <name without extension>
name=$1
nasm -f elf -l $name.lst $name.asm
gcc -m32 -o $name  $name.o
