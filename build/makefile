#include header files
CXXFLAGS = -I ../include -I /usr/include/python2.7 -fno-strict-aliasing -g -O2 -DNDEBUG -g -fwrapv -O2 -Wall -Wno-write-strings
CFLAGS = $(CXXFLAGS) 

#external libraries
LXXFLAGS = -lpython2.7
LDFLAGS = $(LXXFLAGS)

#force to use g++
CC = g++
CXX = g++

#executable to be generated
MAIN_NAME = embedded_python

all: spammodule
	$(CXX) $(LDFLAGS) spammodule.o -o $(MAIN_NAME)
	
$(MAIN_NAME): spammodule

spammodule:
	$(CXX) $(CXXFLAGS) -c ../src/spammodule.cpp

#objects removing
.PHONY: clean
clean:
	rm -fv *.o $(MAIN_NAME)
