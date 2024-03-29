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

platformer: Platformer.o Texture.o SDLHelper.o Obstacles.o SpriteSheet.o Background.o Character.o Score.o Coins.o
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) Platformer.o Texture.o SDLHelper.o Obstacles.o SpriteSheet.o Background.o Character.o Score.o Coins.o

Platformer.o: Platformer.cpp Texture.h SDLHelper.h Obstacles.h SpriteSheet.h Coins.h
	$(CC) -c Platformer.cpp

Texture.o: Texture.cpp Texture.h
	$(CC) -c Texture.cpp

SDLHelper.o: SDLHelper.cpp SDLHelper.h Texture.h
	$(CC) -c SDLHelper.cpp

SpriteSheet.o: SpriteSheet.cpp SpriteSheet.h
	$(CC) -c SpriteSheet.cpp

Obstacles.o: Obstacles.cpp Obstacles.h ScrollableEntity.h
	$(CC) -c Obstacles.cpp

Background.o: Background.cpp Background.h
	$(CC) -c Background.cpp

Character.o: Character.cpp Character.h
	$(CC) -c Character.cpp

Score.o: Score.cpp Score.h  SpriteSheet.h SDLHelper.h
	$(CC) -c Score.cpp

Coins.o: Coins.cpp Coins.h  SpriteSheet.h SDLHelper.h Score.h ScrollableEntity.h
	$(CC) -c Coins.cpp
