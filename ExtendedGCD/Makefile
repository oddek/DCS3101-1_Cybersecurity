PROG = main
CC = gnatmake
all: build run
run:
	./$(PROG)
build:
	$(CC) $(PROG).adb
clean:
	rm -f $(PROG) $(PROG)*.ali $(PROG)*.o 