# We're assuming POSIX conformance
.POSIX:

CC = sdcc
PACKER = packihx 

# Name of resulting .hex file   
MAINSRC = src/main.c

# These are the sources that must be compiled to .rel files:
EXTRASRCS=\
	src/console.c \
	src/gpio.c \
	src/serial.c \
	src/utils.c \
    
# The list of .rel files
RELS = $(EXTRASRCS:.c=.rel)

INCLUDES = -Isrc/inc

CFLAGS=-mmcs51 --std-c99 --model-medium
LDFLAGS  = $(CFLAGS) --iram-size 256 --xram-size 1024 --code-size 61440

all: prep main
	$(PACKER) $(MAINSRC:src/%.c=build/%.ihx) > $(notdir $(MAINSRC:.c=.hex))

main: $(MAINSRC) $(RELS)
	$(CC) $(INCLUDES) $(LDFLAGS) $(MAINSRC) $(RELS:src/%=build/%) $(LIBS) -o build/

prep:
	mkdir -p build/

flash: all
	@{ \
	package='stcgal' ;\
	activate="./$$package/bin/activate" ;\
	devtty='/dev/ttyUSB0' ;\
	mainHex=$(MAINSRC:src/%.c=%.hex) ;\
	\
	python3 -mvenv $$package ;\
	source $$activate ;\
	if not which stcgal > /dev/null 2>&1 ; then \
	echo "stcgal not found! installing..." ; \
	pip -q install --upgrade pip ;\
	pip install $$package ;\
	fi ;\
	sudo bash -c "source $$activate && stcgal -P stc12 -p /dev/ttyUSB0 -b 115200 $$mainHex" ;\
	}

serial:
	sudo picocom -b 115200 -f h -y n -d 8 -p 1 /dev/ttyUSB0

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

mrproper: clean
	@rm -r $(MAINSRC:src/%.c=%.hex) build stcgal 2> /dev/null || true
