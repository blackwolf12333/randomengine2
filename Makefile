CC = g++
CFLAGS=-lSDL2 -lSDL2_image -lyaml-cpp -std=c++11 -ggdb -Wall # -Weffc++

SOURCE_FILES = src/main.cpp src/scene.cpp game/gamescene.cpp src/node.cpp src/spritenode.cpp src/yaml_config.cpp

all:
	$(CC) $(CFLAGS) $(SOURCE_FILES) -Iinclude/ -o towerdefend
