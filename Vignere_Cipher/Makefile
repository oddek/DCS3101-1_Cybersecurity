PROG = VignereCipher
CC = g++
CPPFLAGS = -I /usr/include -L /usr/lib
OBJS = main.o
all: build run
run:
	./$(PROG) -e "The quick brown fox jumps over the lazy dog." "Norway" "oslo"

build: $(PROG)

$(PROG): $(OBJS)
	g++ -o $@ $(OBJS)

clean:
	rm -f *stackdump $(PROG) *.o .depend


