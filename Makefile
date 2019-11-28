CC=g++

CFLAGS = -O3 -w

all: compile run

run: login
	./login

vpath %.h /header
compile:login.cpp
	$(CC) $(CFLAGS) login.cpp -o login

.PHONY: all run
clean:
	rm -rf login
