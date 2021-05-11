
# Executable names:
EXE = wiki-graph
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = apps/main.o
OBJS = apps/main.o src/core/graph.o src/util/util.o src/core/particle.o src/core/force.o src/core/simulation.o src/core/renderer.o src/core/djikstra.o

# Generated files
CLEAN_RM = actual-*.png

# Use the cs225 makefile template:
include src/cs225/make/cs225.mk

# Data trim target
DSETS_OBJS = apps/prep-data.o

prep-data: $(DSETS_OBJS)
	$(LD) $^ $(LDFLAGS) -o $@