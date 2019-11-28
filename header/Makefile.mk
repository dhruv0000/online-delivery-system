CC=g++

CFLAGS = -O3 -w

compile:login.cpp
	$(CC) $(CFLAGS) login.cpp -o login

clean:
	rm -rf login 