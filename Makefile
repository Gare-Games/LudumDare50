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
	$(CC) obj/game.o obj/texturelist.o obj/player.o obj/dialog.o obj/collision.o obj/mouse.o obj/garegames.o obj/colors.o -o $(OUTPUTFILE) $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/game.o : src/game.cpp obj/texturelist.o obj/player.o obj/dialog.o obj/collision.o obj/mouse.o obj/garegames.o obj/colors.o
	$(CC) src/game.cpp -c -o obj/game.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 


obj/colors.o : src/colors.cpp src/colors.h
	$(CC) src/colors.cpp -c -o obj/colors.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/texturelist.o : src/texturelist.cpp src/texturelist.h
	$(CC) src/texturelist.cpp -c -o obj/texturelist.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/player.o : src/player.cpp src/player.h
	$(CC) src/player.cpp -c -o obj/player.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/dialog.o : src/dialog.cpp src/dialog.h
	$(CC) src/dialog.cpp -c -o obj/dialog.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/collision.o : src/collision.cpp src/collision.h
	$(CC) src/collision.cpp -c -o obj/collision.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/mouse.o : src/mouse.cpp src/mouse.h
	$(CC) src/mouse.cpp -c -o obj/mouse.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

obj/garegames.o : src/garegames.cpp src/garegames.h
	$(CC) src/garegames.cpp -c -o obj/garegames.o $(HEADFILESPATH) $(LIBSHARPATH) $(LINKPATHS) 

Clean : 
	$(RM) game.exe
	$(RM) game.out
	$(RM) obj/*
	$(RM) bin/*
	test ! -d obj || rmdir obj
clean : Clean
