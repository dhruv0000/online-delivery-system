CC=g++

CFLAGS = -O3 -w

all: compile clear run

clear: login
	clear

run: login
	./login

compile:login.cpp
	$(CC) $(CFLAGS) login.cpp -o login

.PHONY: all run clear

clean:
	rm -rf login 