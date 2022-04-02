# SmashTVSwarm

## Compile for windows
### Compile raylib on windows.
Follow this tutorial: https://www.youtube.com/watch?v=HPDLTQ4J_zQ

### Compile command
g++ src/game.cpp -c -o obj/game.o -I include/ -L lib -lraylib -lopengl32 -lgdi32 -lwinmm
g++ obj/game.o obj/texturelist.o -o game.exe -I include/ -L lib -lraylib -lopengl32 -lgdi32 -lwinmm

Something like that.

## Compile for linux
In process.