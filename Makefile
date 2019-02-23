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
OBJ_NAME = loop

#This is the target that compiles our executable
# all : $(OBJS)
# 	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)

loop: loop.o texture.o SDLHelper.o animationtest.o spriteSheet.o
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) loop.o texture.o SDLHelper.o animationtest.o spriteSheet.o

loop.o: loop.cpp texture.h SDLHelper.h animationtest.h spriteSheet.h
	$(CC) -c loop.cpp

texture.o: texture.cpp texture.h
	$(CC) -c texture.cpp

SDLHelper.o: SDLHelper.cpp SDLHelper.h texture.h
	$(CC) -c SDLHelper.cpp

spriteSheet.o: spriteSheet.cpp spriteSheet.h
	$(CC) -c spriteSheet.cpp

animationTest.o: animationTest.cp animationTest.h
	$(CC) -c animationTest.cpp

