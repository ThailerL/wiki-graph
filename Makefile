
# Executable names:
EXE = wiki-graph
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = main.o
OBJS = main.o src/core/graph.o src/util/util.o

# Generated files
CLEAN_RM = actual-*.png

# Use the cs225 makefile template:
include src/cs225/make/cs225.mk

# Data trim target
DSETS_OBJS = prep-data.o

prep-data: $(DSETS_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@