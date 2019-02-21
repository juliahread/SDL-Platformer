#OBJS specifies which files to compile as part of the project
OBJS = connect4.cpp

#CC specifies which compiler we're using
CC = clang++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = connect4

#This is the target that compiles our executable
# all : $(OBJS)
# 	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

connect4: connect4.o board.o Ltexture.o
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) connect4.o board.o Ltexture.o

connect4.o: connect4.cpp board.h Ltexture.h
	$(CC) -c connect4.cpp

texture.o: texture.cpp texture.h
	$(CC) -c texture.cpp

SDLHelper.o: SDLHelper.cpp SDLHelper.h
	$(CC) -c SDLHelper.cpp
