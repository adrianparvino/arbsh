
all: frog.o dog.o swan.o 

	ar -cvq libanimals.a frog.o dog.o swan.o 
	gcc main.c libanimals.a -o main

clean:

	-$(RM) *.o
	-$(RM) libanimals.a
	-$(RM) main
