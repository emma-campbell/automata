#! /bin/bash

make

# Valgrind debug
#
#
#

# valgrind --tool=memcheck --leak-check=fill ./auto

# gdb debug
#

gdb ./auto

# Execution of the program
#
#

# ./auto

