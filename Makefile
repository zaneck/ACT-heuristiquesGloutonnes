# Owczarek Valentin
# Makefile type
#------------------------------------------------------------

CC      = gcc
CFLAGS  = -pedantic -Wall -Wextra -Wstrict-prototypes
CFLAGS += -Wtraditional-conversion -Wpointer-arith -Wcast-qual
CFLAGS += -Wcast-align -Wwrite-strings -Wnested-externs -g 
CFLAGS += -Werror #not human anymore
LDFLAGS = -g -lm


BINARIES = binpack
OBJECTS = binpack.o heuristique.o
TARGET= mainBinpack.o
TRASHFILES=*~

all : $(BINARIES) $(OBJECTS) $(TARGET)

###------------------------------
### Entries
###------------------------------------------------------------
binpack:$(OBJECTS) mainBinpack.o
	$(CC) $(LDFLAGS) -o $@ $^

#make depend---------------------------------------------------
binpack.o: binpack.c binpack.h
heuristique.o: heuristique.c binpack.h
mainBinpack.o: mainBinpack.c binpack.h heuristique.h
###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean::
	$(RM) $(OBJECTS) $(TARGET)
realclean:: clean 
	$(RM) $(BINARIES) $(TRASHFILES) $(OTHER)

depend: 
	$(CC) $(CFLAGS) -MM *.c 

