
# Executable names:
EXE = wiki-graph
TEST = test

# Add all object files needed for compiling:
EXE_OBJ = apps/wiki-graph.o
OBJS = apps/wiki-graph.o src/core/graph.o src/util/util.o src/core/particle.o src/core/force.o src/core/simulation.o src/core/renderer.o

# Generated files
CLEAN_RM = actual-*.png

# Use the cs225 makefile template:
include src/cs225/make/cs225.mk

# Data trim target
OBJS_TRIM += $(filter-out $(EXE_OBJ), $(OBJS))
OBJS_TRIM += apps/prep-data.o

prep-data: output_msg $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_TRIM)) $(LIBS)
	$(LD) $(filter-out $<, $^) $(LDFLAGS) -o $@

OBJS_DP += $(filter-out $(EXE_OBJ), $(OBJS))
OBJS_DP += apps/djikstra-path.o

djikstra-path: output_msg $(patsubst %.o, $(OBJS_DIR)/%.o, $(OBJS_DP)) $(LIBS)
	$(LD) $(filter-out $<, $^) $(LDFLAGS) -o $@