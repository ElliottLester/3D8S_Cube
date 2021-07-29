# We're assuming POSIX conformance
.POSIX:

CC = sdcc
PACKER = packihx 

# In case you ever want a different name for the main source file    
MAINSRC = src/main.c

# These are the sources that must be compiled to .rel files:
EXTRASRCS=\
	src/console.c \
	src/gpio.c \
	src/serial.c \
    
# The list of .rel files can be derived from the list of their source files
RELS = $(EXTRASRCS:.c=.rel)

INCLUDES = -Isrc/inc

# shared compiler flags
CFLAGS=-mmcs51 --std-c99 --model-medium

# Flags for the linker
LDFLAGS  = $(CFLAGS) --iram-size 256 --xram-size 1024 --code-size 61440

# This just provides the conventional target name "all"; it is optional
all: prep main
	$(PACKER) $(MAINSRC:src/%.c=build/%.ihx) > $(notdir $(MAINSRC:.c=.hex))

# How to build the overall program
main: $(MAINSRC) $(RELS)
	$(CC) $(INCLUDES) $(LDFLAGS) $(MAINSRC) $(RELS:src/%=build/%) $(LIBS) -o build/

prep:
	mkdir -p build/
	
# How to build any .rel file from its corresponding .c file
# GNU would have you use a pattern rule for this, but that's GNU-specific
.c.rel:
	$(CC) -c $(INCLUDES) $(CFLAGS) $< -o build/

# Suffixes appearing in suffix rules we care about.
# Necessary because .rel is not one of the standard suffixes.
.SUFFIXES: .c .rel

EXTRAOUTPUTS = $(MAINSRC) $(EXTRASRCS)
	
MAINOUTPUT = \
	$(MAINSRC:src/%.c=build/%.ihx) \
	$(MAINSRC:src/%.c=build/%.lk) \
	$(MAINSRC:src/%.c=build/%.map) \
	$(MAINSRC:src/%.c=build/%.mem) \
	
OUTPUTS = \
	$(MAINOUTPUT) \
	$(EXTRAOUTPUTS:src/%.c=build/%.asm) \
	$(EXTRAOUTPUTS:src/%.c=build/%.rel) \
	$(EXTRAOUTPUTS:src/%.c=build/%.sym) \
	$(EXTRAOUTPUTS:src/%.c=build/%.lst) \
	$(EXTRAOUTPUTS:src/%.c=build/%.rst) \

.PHONY: clean
clean:
	@rm $(OUTPUTS) 2> /dev/null || true
