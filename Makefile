CC=g++

CFLAGS = -O3 -w

all: compile run

run: login
	./login

compile:login.cpp database.hpp managers.hpp utilities.hpp
	$(CC) $(CFLAGS) login.cpp -o login

vpath %.h /header
.PHONY: all run
clean:
	rm -rf login
