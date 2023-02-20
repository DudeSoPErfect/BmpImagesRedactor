CC       := g++
CXXFLAGS := -Wall -Werror -O2 -std=c++17

LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
FILTERS = 


SRCDIRS = ./src/
BINDIR  = ./build/

SOURCES = $(wildcard $(SRCDIRS)*.cpp)
OBJECTS = $(addprefix $(BINDIR),$(notdir $(SOURCES:.cpp=.o)))

EXECUTABLE = BmpRedactor

execute: $(EXECUTABLE)
	./$(EXECUTABLE) $(FILTERS)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(OBJECTS) $(CXXFLAGS) $(LDFLAGS) -o $@

$(BINDIR)%.o: $(SRCDIRS)%.cpp
	$(CC) -c $(CXXFLAGS) $< -o $@

.PHONY: clean, mkdirs

mkdirs:
	mkdir $(BINDIR) $(SRCDIRS)

clean: 
	rm $(BINDIR)*.o