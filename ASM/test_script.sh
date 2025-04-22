
nasm -f elf64 $1.asm -l $1.lst

gcc -no-pie -z execstack test.cpp $1.o -o ready

./ready
