CPP=c++
CFLAGS = -std=c++11 -I/usr/local/include -Wall

all: test main

clean:
	rm test main

test:
	$(CPP) -o test $(CFLAGS) test.cpp HitAndBlow.cpp

main:
	$(CPP) -o main $(CFLAGS) main.cpp HitAndBlow.cpp

run: main
	./main

testrun: test
	./test
