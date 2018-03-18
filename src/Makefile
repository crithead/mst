CC = g++
CXXFLAGS = -O2 -Wall -Wpedantic -std=c++11

SOURCES := minspantree.cpp
SOURCES += edge.cpp
SOURCES += point.cpp

OBJECTS := $(SOURCES:.cpp=.o)
DEPENDS := $(SOURCES:.cpp=.d)

EXEC = mst

all: $(EXEC)

$(EXEC): depends $(OBJECTS)
	$(CC) $(CXXFLAGS) -o $(EXEC) $(OBJECTS)

%.d : %.cpp
	$(CC) -MM -E $< -o $@

depends: $(DEPENDS)

-include $(DEPENDS)

.PHONY: print
print:
	@echo "SOURCES: $(SOURCES)"
	@echo "OBJECTS: $(OBJECTS)"
	@echo "DEPENDS: $(DEPENDS)"

.PHONY: clean
clean:
	@rm -f *.o *.d
	@rm -f $(EXEC)


