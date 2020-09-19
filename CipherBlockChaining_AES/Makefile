PROG = CBC_AES
CXX = g++ -std=c++17
INCLUDEDIR = ../AES
LIBDIR = ../AES
#CPPFLAGS = -I$(INCLUDEDIR) -L $(LIBDIR)



OBJS = main.o $(INCLUDEDIR)/AES.o
all: build run
run:
	./$(PROG)

build: $(PROG)

$(PROG): $(OBJS)
	$(CXX) $(CPPFLAGS) -o $@ $(OBJS) $(LDFLAGS)

#.depend:
#	-@$(CXX) $(CPPFLAGS) -MM $(OBJS:.o=.cpp) > $@ 2> /dev/null

#-include .depend

clean:
	rm -f *stackdump $(PROG) *.o .depend



