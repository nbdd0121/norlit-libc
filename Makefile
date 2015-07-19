CC = i686-elf-gcc
CFLAGS = -Wall -Iinclude/ -fpic
LD = i686-elf-gcc
LDFLAGS = -shared -Wl,-shared

OUTPUT = libc.so

SRC_FILES = $(shell find src/ | grep '\'.c$\'')
BIN_FILES = $(SRC_FILES:src/%.c=bin/%.o)
DEP_FILES = $(BIN_FILES:.o=.d)

.PHONY: all directory

all: directory $(OUTPUT)

$(OUTPUT): $(BIN_FILES)
	$(LD) $(LDFLAGS) $(BIN_FILES) -o $(OUTPUT)

directory:
	mkdir -p $(sort $(dir $(BIN_FILES)))

-include $(DEP_FILES)

bin/%.o: src/%.c
	$(CC) -c $(CFLAGS) src/$*.c -o bin/$*.o
	$(CC) -MM $(CFLAGS) src/$*.c > bin/$*.d