CC=clang++
CFLAGS=-lc++

all: test clean

test:
	$(CC) $(CFLAGS) -o test_cpp test_vdo_gauge_calc.cpp ../vdo_gauge_calc.cpp && ./test_cpp

clean:
	rm -f test_cpp
