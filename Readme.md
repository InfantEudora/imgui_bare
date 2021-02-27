# How To Build
 
 ## Build enrironment: Windows 10 64 bit with MSYS2
 Setup MSYS2 with mingw64 compiler:
 https://repo.msys2.org/distrib/x86_64/msys2-x86_64-20210105.exe

Follow online steps, which are:
- Install it.
- Run ``pacman -Syu`` in MSYS2 console.
- Install needed packages:
- ```pacman -S make```
- ```pacman -S mingw-w64-x86_64-gcc```
- Add  mingw64 to path: ```echo "export PATH=$PATH:/mingw64/bin" >> ~/.bashrc ```
- ```source ~/.bashrc```
- run make

# External Precompiled Libraries 

 ### SDL2

    https://libsdl.org/download-2.0.php
    SDL2-devel-2.0.14-mingw.tar.gz (MinGW 32/64-bit)    

These are located in the ```/lib_compiled``` folder.

# External Libraries, included in project as submodule

### ImGUI
    github: https://github.com/ocornut/imgui on the docking branch.

### ImGUI SDL:
    github: https://github.com/Tyyppi77/imgui_sdl
    Allows ImGUI to render on SDL without OpenGL, so this defaults to Direct3D on Windows.
