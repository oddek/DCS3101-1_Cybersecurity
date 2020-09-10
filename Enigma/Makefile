PROG = Enigma
CC = g++
CPPFLAGS = -I /usr/include -L /usr/lib
LDFLAGS = 

OBJS = main.o Rotor.o Enigma.o
all: build run
run:
	./$(PROG)

build: $(PROG)

$(PROG): $(OBJS)
	g++ -o $@ $(OBJS) $(LDFLAGS)

clean:
	rm -f *stackdump $(PROG) *.o .depend


