Memory Game
=================
This application is licenced under [GNU General Public License, Version 3.0](http://www.gnu.org/copyleft/gpl.html)

Summary
-------

Memory Game written in C++ using SDL graphic library

Building
--------

### On GNU/Linux:
To build the game you will need SDL developement library: [www.libsdl.org](http://www.libsdl.org). On debian-based distributions, a simple
```
sudo apt-get install libsdl1.2-dev
```
should do the job.
Then
```
make
./memory-game
```
    
### On Windows:
To build with ming32, you need SDL Library as well. Paste Include files into {include path}\SDL and lib files into {lib path}. Make sure you add these options for link editing:
```
-lmingw32 -lSDLmain -lSDL
```
To run the game, put the SDL's DLL file in the same directory as the built exe.

About
-----

This little game is intended to have fun, train your memory skills and obviously for the developper to play with SDL Library features and object-oriented programming

