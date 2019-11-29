CC=g++
CFLAGS = -O3 -w
vpath %.h /header

.PHONY: all run clear clean

all: compile clear run

clear: clear
	clear

run: login
	./login


compile:login.cpp
	$(CC) $(CFLAGS) login.cpp -o login



clean:
	rm -rf login 