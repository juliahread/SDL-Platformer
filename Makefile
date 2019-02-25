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
OBJ_NAME = platformer

#This is the target that compiles our executable
# all : $(OBJS)
# 	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

platformer: platformer.o texture.o SDLHelper.o obstacles.o spriteSheet.o
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) platformer.o texture.o SDLHelper.o obstacles.o spriteSheet.o

platformer.o: platformer.cpp texture.h SDLHelper.h obstacles.h spriteSheet.h
	$(CC) -c platformer.cpp

texture.o: texture.cpp texture.h
	$(CC) -c texture.cpp

SDLHelper.o: SDLHelper.cpp SDLHelper.h texture.h
	$(CC) -c SDLHelper.cpp

spriteSheet.o: spriteSheet.cpp spriteSheet.h
	$(CC) -c spriteSheet.cpp

animationTest.o: animationTest.cpp animationTest.h
	$(CC) -c animationTest.cpp

obstacles.o: obstacles.cpp obstacles.h
	$(CC) -c obstacles.cpp
