CFLAGS += -Wall -Wextra

OBJ = $(shell for i in *.c ; do echo $${i%.c}.o ; done )

LIBNAME = animals

STATLIB = lib$(LIBNAME).a 

TEST_OBJ = main.o

LDLIBS += -L. -l$(LIBNAME)

all:

	$(MAKE) static 
	$(MAKE) create_test

static: $(OBJ)

	$(MAKE) static_link 

static_link:

	$(AR) -cvq $(STATLIB) $(OBJ)





create_test: $(TEST_OBJ)

cleanobj:

	$(RM) $(OBJ) 

clean:
	$(MAKE) cleanobj
	$(RM) $(DYNLIB) 
	$(RM) $(STATLIB) 
	$(RM) $(TEST_OBJ)
