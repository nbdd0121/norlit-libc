CC = i686-elf-gcc
CFLAGS = -Wall -Iinclude/ -fpic -Os
LD = i686-elf-ld
LDFLAGS = -shared

OUTPUT = libc.so

SRC_FILES = $(shell find src/ | grep '\'.c$\'')
BIN_FILES = $(SRC_FILES:src/%.c=bin/%.o)
DEP_FILES = $(BIN_FILES:.o=.d)

CRTI = bin/crt/crti.o
CRTBEGIN = $(shell $(CC) $(CFLAGS) --print-file-name=crtbegin.o)
CRTEND = $(shell $(CC) $(CFLAGS) --print-file-name=crtend.o)
CRTN = bin/crt/crtn.o
LIBGCC = $(shell $(CC) $(CFLAGS) --print-file-name=libgcc.a)

.PHONY: all

all: $(OUTPUT)

$(OUTPUT): $(CRTI) $(CRTN) $(BIN_FILES)
	$(LD) $(LDFLAGS) $(CRTI) $(CRTBEGIN) $(BIN_FILES) $(CRTEND) $(CRTN) $(LIBGCC) -o $(OUTPUT)
	strip $(OUTPUT)

-include $(DEP_FILES)

bin/crt/%.o: crt/%.c
	mkdir -p bin/crt
	$(CC) -c $(CFLAGS) crt/$*.c -o bin/crt/$*.o

bin/%.o: src/%.c
	mkdir -p $(dir bin/$*.o)
	$(CC) -c $(CFLAGS) src/$*.c -o bin/$*.o
	$(CC) -MT bin/$*.o -MM $(CFLAGS) src/$*.c > bin/$*.d