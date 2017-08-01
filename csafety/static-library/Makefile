CFLAGS += -Wall -Wextra

OBJ = frog.o \
dog.o \
swan.o

LIBNAME = animals

STATLIB = lib$(LIBNAME).a

TEST_OBJ = main

LDLIBS = -l$(LIBNAME)

LDFLAGS = -L.

all:

	$(MAKE) static
	$(MAKE) create_test

static: $(OBJ)

	$(MAKE) static_link

static_link:

	$(AR) -cvq $(STATLIB) $(OBJ)

create_test: $(TEST_OBJ)

clean:
	$(RM) $(OBJ) 
	$(RM) $(DYNLIB) 
	$(RM) $(STATLIB) 
	$(RM) $(TEST_OBJ)
