#OBJS specifies which files to compile as part of the project
OBJS = code.c

#CC specifies which compiler we're using
CC = gcc

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = `pkg-config gtk+-3.0 --cflags` -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = `pkg-config --libs gtk+-3.0` -export-dynamic -lSDL2 -lSDL2_mixer -lSDL2main


#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = Game

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
