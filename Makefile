
SRC =	src/AnimatedSprite.cpp \
		src/Animation.cpp \
		src/assetManager.cpp \
		src/Engine.cpp \
		src/main.cpp


all:
	g++ $(SRC) -lsfml-graphics -lsfml-window -lsfml-system -I./include/  -o DuckDuckDie