CC = clang++
CFLAGS = -g

all: prog

clean:
	rm *\.o
	rm *\.~
	rm -f program

prog: host population symbulation
	$(CC) $(CFLAGS) -o program symbulation.o population.o host.o

host: host.cpp host.hpp
	$(CC) $(CFLAGS) -c host.cpp -o host.o

population: population.cpp population.hpp host.hpp
	$(CC) $(CFLAGS) -c population.cpp -o population.o

symbulation: symbulation.cpp population.hpp host.hpp
	$(CC) $(CFLAGS) -c symbulation.cpp -o symbulation.o
