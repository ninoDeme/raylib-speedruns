build: 
	gcc -fPIC -I./raylib-5.0_linux_amd64/include ./app.c -o app.o -L./raylib-5.0_linux_amd64/lib -lm -lpthread -ldl -lraylib -Wl,-rpath,./raylib-5.0_linux_amd64/lib 

run: build run-only

run-only:
	./app.o

clean:
	rm -f app.o

