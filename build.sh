i686-elf-gcc -Wall -Iinclude/ -fPIC -shared -Wl,-shared `find src | grep '\.c$'` -o ../libc.so
#x86_64-elf-gcc -Wall -Iinclude/ -fPIC -shared -Wl,-shared `find src | grep '\.c$'` -o ../libc64.so
#i686-elf-gcc -O3 -Wall -Iinclude/ -fPIC -shared -Wl,-shared `find src | grep '\.c$'` -o ../libc.so
#x86_64-elf-gcc -O3 -Wall -Iinclude/ -fPIC -shared -Wl,-shared `find src | grep '\.c$'` -o ../libc64.so