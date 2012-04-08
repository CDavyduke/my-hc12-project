# $Id: Makefile,v 1.6 2003/11/22 02:14:09 cdavyduk Exp $

# Makefile for ELEX8030 term project

# Some compiler flags
CFLAGS  = -O2
CFLAGS += -fno-exceptions
CFLAGS += -fno-rtti
CFLAGS += -fvtable-thunks
CFLAGS += -W
CFLAGS += -Wall
CFLAGS += -Wtraditional
CFLAGS += -Wundef
CFLAGS += -Wbad-function-cast
CFLAGS += -Wcast-qual
CFLAGS += -Wwrite-strings
CFLAGS += -Wconversion
CFLAGS += -Wstrict-prototypes
CFLAGS += -Wmissing-prototypes
CFLAGS += -Wmissing-declarations
CFLAGS += -Wold-style-cast
CFLAGS += -Woverloaded-virtual
CFLAGS += -Werror
CFLAGS += -g
CFLAGS += -Wa,-ahln=$*.lst
CFLAGS += -D__HC912B32__
CFLAGS += -fpcc-struct-return

# And some linker flags
LFLAGS  = -Wl,--defsym,_stack_top=0x8000 
LFLAGS += -Wl,-Map,$*.map
LFLAGS += -Wl,--defsym,_heap_top=0x7C00
LFLAGS += -Wl,-T,$*.ld

# And a flag for copying the object file to a .S19 record
OFLAGS  = --output-target=srec

# And some library files
LIBS += iostream.a

COMMA = ,

LIBFLGS += -Wl,--start-group,$(patsubst %,%$(COMMA),$(LIBS))--end-group

# Project object
PROG	= project.o

# Motorola S-record
S_REC   = project.s19

# Other object files to link into the project
#OBJS	= crt0.o crt1.o main.o malloc.o new.o
OBJS	= $(addsuffix .o, $(basename $(wildcard *.cc) $(wildcard *.s)))

# Compiler [driver] command line including flags
CC	= hc12-coff-gcc

# Object copy command line
OBJCOPY = hc12-coff-objcopy

all : $(PROG)

$(PROG) : $(OBJS) $(LIBS)
	$(CC) $(LFLAGS) -o $@ $^ $(LIBFLGS)
	$(OBJCOPY) $(OFLAGS) $(PROG) $(S_REC)

%.o : %.cc
	$(CC) $(CFLAGS) -c $<

%.o : %.s
	$(CC) -c $<

clean :
	rm -f $(PROG) $(OBJS) $(S_REC)

