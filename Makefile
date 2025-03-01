########## Variables ##########

PORT_INCLUDE = /c/msys64/mingw64/include/
PORT_LIB = /c/msys64/mingw64/lib/
PORT_BIN = /c/msys64/mingw64/bin/

CXX = g++                         # Compiler
CXXFLAGS = -std=c++20 -g -Wall -Werror=vla -MMD 	# Compiler flags
MAKEFILE_NAME = ${firstword ${MAKEFILE_LIST}}  # Makefile name

SOURCES = main.cc             # Source files (*.cc)
OBJECTS = ${SOURCES:.cc=.o}            # Object files forming executable
DEPENDS = ${OBJECTS:.o=.d}            # Dependency files
EXEC = example                        # Executable name


########## Targets ##########

.PHONY : clean run                   # Not file names

${EXEC} : ${OBJECTS}                  # Link step
	${CXX} ${CXXFLAGS} $^ -o $@ -L$(PORT_LIB) -lportaudio  # Link against portaudio

${OBJECTS} : ${MAKEFILE_NAME}         # OPTIONAL : changes to this file => recompile

-include ${DEPENDS}                   # Include *.d files containing program dependencies

clean :                               # Remove files that can be regenerated
	rm -f ${DEPENDS} ${OBJECTS} ${EXEC} && clear

run: ${EXEC}
	./$(EXEC)
