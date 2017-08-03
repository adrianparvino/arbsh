all: 

	# Create the object code
	gcc -c frog.c dog.c swan.c -static
	# Create a dynamic library
	cc -shared -Wl,-soname,libanim.so -o libanim.so frog.o swan.o dog.o
	# And finally link it into our executable test driver "main.c"
	gcc main.c libanim.so -o main "-Wl,-rpath=$(PWD)"

clean:

	rm frog.o dog.o swan.o libanim.so main


