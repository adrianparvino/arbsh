
all: 

	# create the object code
	gcc -c frog.c dog.c swan.c
	# Here we use `ar' to create the static library "libanimals.a"
	ar -cvq libanimals.a frog.o dog.o swan.o 
	# And finally link it into our executable test driver "main.c"
	gcc main.c libanimals.a -o main

clean:

	rm frog.o dog.o swan.o libanimals.a main


