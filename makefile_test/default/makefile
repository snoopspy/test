SOURCES=main.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=$(shell basename $(PWD))
LDFLAGS+=-lpthread

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CXX) -o $@ $(OBJECTS) $(LDFLAGS)

clean:
	rm -rf *.o
	rm -rf $(EXECUTABLE)
