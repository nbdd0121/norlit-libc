CC = i686-elf-gcc
CFLAGS = -Wall -Iinclude/ -fpic -Os
LD = i686-elf-ld
LDFLAGS = -shared

OUTPUT = libc.so
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