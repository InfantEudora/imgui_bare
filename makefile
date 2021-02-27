#Compiler
CC = g++
CXX = $(CC)

CFLAGS 	=  -lm -Dmain=SDL_main
CFLAGS += -ISDL2
CFLAGS += -I..
CFLAGS += -I../..
CFLAGS += -Iimgui/

CFLAGS += -Llib_compiled/
CFLAGS += -lmingw32 
CFLAGS += -lSDL2main
CFLAGS += -lSDL2 

CFLAGS += -MMD -MP
#I don't care about your static strings.
CFLAGS += -Wno-write-strings -std=c++17 -g -DDEBUG

CPPFLAGS = $(CFLAGS)
LD_FLAGS =

#Source file list.
SRC_LOCAL =
SRC_LOCAL += main.cpp

SRC_LIBIMGUI += imgui/imgui.cpp
SRC_LIBIMGUI += imgui/imgui_draw.cpp
SRC_LIBIMGUI += imgui/imgui_widgets.cpp
SRC_LIBIMGUI += imgui/imgui_tables.cpp
SRC_LIBIMGUI += imgui/imgui_demo.cpp
SRC_LIBIMGUI += imgui/backends/imgui_impl_sdl.cpp
SRC_LIBIMGUI += imgui_sdl/imgui_sdl.cpp


SRC = 
SRC += $(SRC_LOCAL)
SRC += $(SRC_LIBIMGUI)

OBJ_LOCAL +=  $(patsubst %.cpp, %.o, $(SRC_LOCAL))

OBJ +=  $(patsubst %.cpp, %.o, $(SRC))

PROJECT := bare.exe

EXE := $(PROJECT)

TEST = $(notdir      $(OBJ))

#Phony's are recipes not related to files
#.PHONY: all $(OBJ)  $(OBJ_C)

all: header $(OBJ) $(OBJ_C) move
	$(CC) -o $(PROJECT) $(OBJ) $(OBJ_C)  $(CFLAGS) $(LIBS) $(DEFS)

$(OBJ): %.o: %.cpp
	$(CC) -c $(CFLAGS) $(DEFS) $(LIBS) $< -o $@
$(OBJ_C): %.o: %.c
	$(CC) -c $(CFLAGS) $(DEFS) $(LIBS) $< -o $@

header: ;echo Starting

move:
	-mv *.d build/dep/
	-mv imgui/*.d build/imgui/	
	-mv imgui/backends/*.d build/imgui/backends/	


dirs:
	-mkdir build
	-mkdir build/dep/
	-mkdir build/imgui/
	-mkdir build/imgui/backends/

info: ; $(info $$var is [${SRC_LIBBOX2D}])echo Hello world

clean:
	-rm -rf $(OBJ_LOCAL)
	