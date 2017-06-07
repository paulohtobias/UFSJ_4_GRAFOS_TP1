#Main Makefile
CC = gcc
CFLAGS = -g -Wall -MMD

#Binary
BIN = main

#Directories
IDIR = ./include
SDIR = ./src
ODIR = ./obj

#Paths
INCLUDE_PATHS = -I$(IDIR)

#Libraries
LIBS = `pkg-config --cflags --libs gtk+-3.0`

#Compilation line
COMPILE = $(CC) $(CFLAGS) $(INCLUDE_PATHS)

#FILEs
#---------------Include---------------#
INCS = $(wildcard $(IDIR)/*.h)
#---------------Source----------------#
SRCS = $(INCS:$(IDIR)/%.h=$(SDIR)/%.c)
#---------------Object----------------#
OBJS = $(INCS:$(IDIR)/%.h=$(ODIR)/%.o)
#-------------Dependency--------------#
DEPS = $(INCS:$(IDIR)/%.h=$(ODIR)/%.d)

all: $(OBJS)
	$(COMPILE) $(OBJS) main.c -o $(BIN) $(LIBS)

# Include all .d files
-include $(DEPS)

$(ODIR)/%.o: $(SDIR)/%.c $(IDIR)/%.h
	$(COMPILE) -MMD -c $< -o $@ $(LIBS)

.PHONY : clean
clean :
	-rm $(BIN).d $(OBJS) $(DEPS)

