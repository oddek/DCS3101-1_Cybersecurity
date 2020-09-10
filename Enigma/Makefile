PROG = Enigma
CC = g++
CXXFLAGS = -std=c++17
CPPFLAGS = -I /usr/include -L /usr/lib
LDFLAGS = 

OBJS = main.o Rotor.o Enigma.o
all: build run
run:
	./$(PROG)

build: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f *stackdump $(PROG) *.o .depend


