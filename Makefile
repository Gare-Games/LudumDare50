CC = g++

ifeq ($(OS),Windows_NT)
	CFLAGS = -Wl,--subsystem,windows
		LINKPATHS = -lraylib -lopengl32 -lgdi32 -lwinmm
		OUTPUTFILE = game.exe
		LIBSHARPATH = -L lib
else
	UNAME_S := $(shell uname -s)
		ifeq ($(UNAME_S),Linux)
			LINKPATHS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
			OUTPUTFILE = game.out
			LIBSHARPATH = -L liblinux
		endif
endif


HEADFILESPATH = -I include/

all: obj Exe
obj:
	test ! -d obj && mkdir obj

Exe : obj/game.o
	$(CC) obj/game.o obj/fastenemy.o obj/rifleitem.o obj/itemlist.o obj/item.o obj/cash.o obj/rifle.o obj/toughenemy.o obj/spawner.o obj/globalvars.o obj/level.o obj/enemylist.o obj/enemy.o obj/soundlist.o obj/bulletlist.o obj/bullet.o obj/pistol.o obj/weapon.o obj/texturelist.o obj/player.o obj/collision.o obj/mouse.o obj/garegames.o obj/colors.o -o $(OUTPUTFILE) $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) $(CFLAGS)

obj/game.o : src/game.cpp obj/fastenemy.o obj/rifleitem.o obj/itemlist.o obj/cash.o obj/item.o obj/rifle.o obj/toughenemy.o obj/spawner.o obj/globalvars.o obj/level.o obj/enemylist.o obj/enemy.o obj/soundlist.o obj/bulletlist.o obj/bullet.o obj/pistol.o obj/weapon.o obj/texturelist.o obj/player.o obj/collision.o obj/mouse.o obj/garegames.o obj/colors.o
	$(CC) src/game.cpp -c -o obj/game.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/fastenemy.o : src/fastenemy.cpp src/fastenemy.h
	$(CC) src/fastenemy.cpp -c -o obj/fastenemy.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/rifleitem.o : src/rifleitem.cpp src/rifleitem.h
	$(CC) src/rifleitem.cpp -c -o obj/rifleitem.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/itemlist.o : src/itemlist.cpp src/itemlist.h
	$(CC) src/itemlist.cpp -c -o obj/itemlist.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/cash.o : src/cash.cpp src/cash.h
	$(CC) src/cash.cpp -c -o obj/cash.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/item.o : src/item.cpp src/item.h
	$(CC) src/item.cpp -c -o obj/item.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/toughenemy.o : src/toughenemy.cpp src/toughenemy.h
	$(CC) src/toughenemy.cpp -c -o obj/toughenemy.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/rifle.o : src/rifle.cpp src/rifle.h
	$(CC) src/rifle.cpp -c -o obj/rifle.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/colors.o : src/colors.cpp src/colors.h
	$(CC) src/colors.cpp -c -o obj/colors.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/spawner.o : src/spawner.cpp src/spawner.h
	$(CC) src/spawner.cpp -c -o obj/spawner.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/globalvars.o : src/globalvars.cpp src/globalvars.h
	$(CC) src/globalvars.cpp -c -o obj/globalvars.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/level.o : src/level.cpp src/level.h
	$(CC) src/level.cpp -c -o obj/level.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/bullet.o : src/bullet.cpp src/bullet.h
	$(CC) src/bullet.cpp -c -o obj/bullet.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/pistol.o : src/pistol.cpp src/pistol.h
	$(CC) src/pistol.cpp -c -o obj/pistol.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/weapon.o : src/weapon.cpp src/weapon.h
	$(CC) src/weapon.cpp -c -o obj/weapon.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/soundlist.o : src/soundlist.cpp src/soundlist.h
	$(CC) src/soundlist.cpp -c -o obj/soundlist.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/enemylist.o : src/enemylist.cpp src/enemylist.h
	$(CC) src/enemylist.cpp -c -o obj/enemylist.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/texturelist.o : src/texturelist.cpp src/texturelist.h
	$(CC) src/texturelist.cpp -c -o obj/texturelist.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/bulletlist.o : src/bulletlist.cpp src/bulletlist.h
	$(CC) src/bulletlist.cpp -c -o obj/bulletlist.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/player.o : src/player.cpp src/player.h
	$(CC) src/player.cpp -c -o obj/player.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/enemy.o : src/enemy.cpp src/enemy.h
	$(CC) src/enemy.cpp -c -o obj/enemy.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/collision.o : src/collision.cpp src/collision.h
	$(CC) src/collision.cpp -c -o obj/collision.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/mouse.o : src/mouse.cpp src/mouse.h
	$(CC) src/mouse.cpp -c -o obj/mouse.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/garegames.o : src/garegames.cpp src/garegames.h
	$(CC) src/garegames.cpp -c -o obj/garegames.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

Clean : 
	$(RM) game.exe
	$(RM) game.out
	$(RM) game.data
	$(RM) game.html
	$(RM) game.wasm
	$(RM) obj/*
	$(RM) bin/*
	test ! -d obj || rmdir obj
clean : Clean
