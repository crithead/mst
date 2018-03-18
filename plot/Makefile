CC = g++
CXXFLAGS = -O2 -Wall -pedantic -std=c++11 -DNO_FREETYPE
CXXFLAGS += -isystem $(PNGWRITERSRC)

PNGWRITERSRC := pngwriter/src
PNGWRITER_CONFIG := -L $(PNGWRITERSRC)
PNGWRITER_CONFIG += -lz
PNGWRITER_CONFIG += -lpng
PNGWRITER_CONFIG += -lpngwriter

#INCLUDE := -isystem $(PNGWRITERSRC)
CXXFLAGS += -isystem $(PNGWRITERSRC)

SOURCES := plotgraph.cpp
SOURCES += edge.cpp
SOURCES += point.cpp

OBJECTS := $(SOURCES:.cpp=.o)
DEPENDS := $(SOURCES:.cpp=.d)

EXEC = mstplot

all: $(EXEC)

$(EXEC): pngwriter depends $(OBJECTS)
	$(CC) $(CXXFLAGS) -o $(EXEC) $(OBJECTS) $(PNGWRITER_CONFIG)

#%.o : %.cpp
#	$(CC) $(CXXFLAGS) $< -o $@ $(INCLUDE)

%.d : %.cpp
	$(CC) -MM -E $< -o $@

depends: $(DEPENDS)

-include $(DEPENDS)

# PNGwriter is a separate project included here as a submodule
.PHONY: pngwriter
pngwriter :
	$(MAKE) -C pngwriter

.PHONY: print
print:
	@echo "SOURCES: $(SOURCES)"
	@echo "OBJECTS: $(OBJECTS)"
	@echo "DEPENDS: $(DEPENDS)"

.PHONY: clean
clean:
	@rm -f *.o *.d
	@rm -f $(EXEC)
	@rm -f $(PNGWRITERLIB)
	(cd pngwriter; make clean; cd ..)


