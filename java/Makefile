JAVA_HOME= /usr/lib/jvm/java-21-openjdk-amd64
build: header lib

header:
	javac -h . App.java

lib: 
	gcc -shared -fPIC -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -I./raylib-5.0_linux_amd64/include ./App.c -o ./libraylibjava.so -L./raylib-5.0_linux_amd64/lib -lm -lpthread -ldl -lraylib -Wl,-rpath,./raylib-5.0_linux_amd64/lib 

run-only:
	java -cp . -Djava.library.path=$(shell dirname $(realpath $(firstword $(MAKEFILE_LIST)))) App

run: build run-only

clean:
	rm -f *.class App.h libraylibjava.so

