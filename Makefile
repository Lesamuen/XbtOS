# Specifies which files to compile
FILEIN = game/main.cpp game/windowDefs.cpp game/SDLhelpers.cpp game/randomGen.cpp game/actions.cpp game/standardActions.cpp

# Specifies compiler
CC = g++

# Specifies the additional compilation options we're using
# -Wall keeps all warnings on
# -Wl,-subsystem,windows removes console popup
ifeq ($(OS), Windows_NT)
	COMPILER_FLAGS = -Wall -Wl,-subsystem,windows
else
	COMPILER_FLAGS = -Wall
endif

# Specifies the include directories
ifeq ($(OS), Windows_NT)
	INCLUDE_FLAGS = -Igame -Iinclude
else
	INCLUDE_FLAGS = -Igame
endif

# Specifies the libraries we're linking against
ifeq ($(OS), Windows_NT)
	LINKER_FLAGS = -Llib -lmingw32 -lSDL2main -lSDL2
else
	LINKER_FLAGS = -lSDL2
endif

# Specifies the name of our executable
ifeq ($(OS), Windows_NT)
	FILEOUT = a.exe
else
	FILEOUT = a.out
endif

# Target that compiles our executable
all : $(FILEIN)
	$(CC) $(FILEIN) $(COMPILER_FLAGS) $(INCLUDE_FLAGS) $(LINKER_FLAGS) -o $(FILEOUT)

# Target that runs our executable
run : $(FILEOUT)
	./$(FILEOUT)

# Target that removes our executable
clean: $(FILEOUT)
	rm ./$(FILEOUT)