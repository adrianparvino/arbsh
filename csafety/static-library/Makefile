# ar has been around for a long time. and it makes very simple archives. These 
# very simple archives happen to be readable by the compiler and we can 
# concatenate object code more or less endlessly into one of these .a and then 
# use it as a "library" the other type of library is called dynamic library and 
# they end with .so 

# Static libraries get the entire thing linked into the executable, dynamic 
# libraries sit in /lib and are loaded at runtime static binaries ofc, will work 
# in a chroot with no fuss or /lib at all but they may need /proc. like top and
# htop depend n parsing /proc in linux


all: 

	# create the object code
	gcc -c frog.c dog.c swan.c
	# Here we use `ar' to create the static library "libanimals.a"
	ar -cvq libanimals.a frog.o dog.o swan.o 
	# And finally link it into our executable test driver "main.c"
	gcc main.c libanimals.a -o main

clean:

	rm frog.o dog.o swan.o libanimals.a main


