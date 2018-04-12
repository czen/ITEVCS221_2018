// examples from https://www.csee.umbc.edu/portal/help/nasm/sample.shtml

// to install 32-bit libraries on 64-bit machine to link with ld for 32-bit nasm *.o
sudo apt-get install gcc-multilib g++-multilib

// to run examples:
./compile.sh helloworld
./helloworld
> Hello World

./compile_gcc.sh floatarith
./floatarith
> c=5.0 a=3.333....
