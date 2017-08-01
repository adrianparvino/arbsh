# "make" is an implicit language. so basically we imply that the .o 
# files are there .. and it creates them from the .c files. .o files 
# are object code for libraries, whereas executables don't end in .o 
# they have no suffix


all: frog.o dog.o swan.o 

	# Here we use `ar' to create the static library "libanimals.a"
	ar -cvq libanimals.a frog.o dog.o swan.o 
	gcc main.c libanimals.a -o main

clean:

	-$(RM) *.o
	-$(RM) libanimals.a
	-$(RM) main
