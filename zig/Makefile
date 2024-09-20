build: 
	zig build-exe -fPIC app.zig raylib-5.0_linux_amd64/lib/libraylib.a -I ./raylib-5.0_linux_amd64/include -lm -lpthread -ldl

run: build run-only

run-only:
	./app

clean:
	rm -f app.o app

