
# Executable names:
EXE = wiki-graph
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o prep-data.o

# Generated files
CLEAN_RM = actual-*.png

# Use the cs225 makefile template:
include cs225/make/cs225.mk

# Data trim target
DSETS_OBJS = prep-data.o

prep-data: $(DSETS_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@