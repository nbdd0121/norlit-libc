# Copyright (c) 2015, Gary Guo 
# All rights reserved. 
# 
# Redistribution and use in source and binary forms, with or without 
# modification, are permitted provided that the following conditions are met: 
# 
#  * Redistributions of source code must retain the above copyright notice, 
#    this list of conditions and the following disclaimer. 
#  * Redistributions in binary form must reproduce the above copyright 
#    notice, this list of conditions and the following disclaimer in the 
#    documentation and/or other materials provided with the distribution. 
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY 
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE 
# DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY 
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES 
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY 
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH 
# DAMAGE. 

CC = x86_64-elf-gcc
CFLAGS_32 = -m32 -Wall -Iinclude/ -fpic -Os
CFLAGS = -Wall -Iinclude/ -Os -mcmodel=large -Werror
LD = x86_64-elf-ar
LDFLAGS = crf
LDFLAGS_32 = crf
OUTPUT = libc.a
OUTPUT_32 = libc.32.a

SRC_FILES    = $(shell find src/ | grep '\'.c$\'')
BIN_FILES    = $(SRC_FILES:src/%.c=bin/%.o)
BIN_FILES_32 = $(SRC_FILES:src/%.c=bin/%.32.o)
DEP_FILES    = $(BIN_FILES:.o=.d)

CRTI        = bin/crt/crti.o
CRTI_32     = bin/crt/crti.32.o
CRTBEGIN    = $(shell $(CC) $(CFLAGS) --print-file-name=crtbegin.o)
CRTBEGIN_32 = $(shell $(CC) $(CFLAGS_32) --print-file-name=crtbegin.o)
CRTEND      = $(shell $(CC) $(CFLAGS) --print-file-name=crtend.o)
CRTEND_32   = $(shell $(CC) $(CFLAGS_32) --print-file-name=crtend.o)
CRTN        = bin/crt/crtn.o
CRTN_32     = bin/crt/crtn.32.o
LIBGCC      = $(shell $(CC) $(CFLAGS) --print-file-name=libgcc.a)
LIBGCC_32   = $(shell $(CC) $(CFLAGS_32) --print-file-name=libgcc.a)

.PHONY: all

all: $(OUTPUT) $(OUTPUT_32)

$(OUTPUT): $(CRTI) $(CRTN) $(BIN_FILES)
#	$(LD) $(LDFLAGS) $(CRTI) $(CRTBEGIN) $(BIN_FILES) $(CRTEND) $(CRTN) $(LIBGCC) -o $(OUTPUT)
#	strip $(OUTPUT)
	$(LD) $(LDFLAGS) $(OUTPUT) $(BIN_FILES)

$(OUTPUT_32): $(CRTI_32) $(CRTN_32) $(BIN_FILES_32)
#	$(LD) $(LDFLAGS_32) $(CRTI_32) $(CRTBEGIN_32) $(BIN_FILES_32) $(CRTEND_32) $(CRTN_32) $(LIBGCC_32) -o $(OUTPUT_32)
#	strip $(OUTPUT)
	$(LD) $(LDFLAGS_32) $(OUTPUT_32) $(BIN_FILES_32)

-include $(DEP_FILES)

bin/crt/%.o: crt/%.c
	mkdir -p bin/crt
	$(CC) -c $(CFLAGS) crt/$*.c -o bin/crt/$*.o

bin/crt/%.32.o: bin/crt/%.o
	$(CC) -c $(CFLAGS_32) crt/$*.c -o bin/crt/$*.32.o

bin/%.o: src/%.c
	mkdir -p $(dir bin/$*.o)
	$(CC) -c $(CFLAGS) src/$*.c -o bin/$*.o
	$(CC) -MT bin/$*.o -MM $(CFLAGS) src/$*.c > bin/$*.d

bin/%.32.o: bin/%.o
	$(CC) -c $(CFLAGS_32) src/$*.c -o bin/$*.32.o