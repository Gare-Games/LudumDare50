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

## Compiling for web
emcc -o game.html src/game.cpp src/fastenemy.cpp src/rifleitem.cpp src/itemlist.cpp src/item.cpp src/cash.cpp src/rifle.cpp src/toughenemy.cpp src/spawner.cpp src/globalvars.cpp src/level.cpp src/enemylist.cpp src/enemy.cpp src/soundlist.cpp src/bulletlist.cpp src/bullet.cpp src/pistol.cpp src/weapon.cpp src/texturelist.cpp src/player.cpp src/collision.cpp src/mouse.cpp src/garegames.cpp src/colors.cpp -Os -Wall ./lib/libraylib.a -I. -Iinclude -L. -Llib -s USE_GLFW=3 -s ASYNCIFY --shell-file src/shell.html -DPLATFORM_WEB -Wc++11-narrowing --preload-file resources