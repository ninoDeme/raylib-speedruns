build: 
	gcc -fPIC -I./raylib-5.0_linux_amd64/include ./app.c -o app.o -L./raylib-5.0_linux_amd64/lib -l:libraylib.a -lm -lpthread -ldl

run: build run-only

run-only:
	./app.o

clean:
	rm -f app.o

