Memory Game
=================
This application is licenced under [GNU General Public License, Version 3.0](http://www.gnu.org/copyleft/gpl.html)

Summary
-------

Memory Game written in C++ using SDL graphic library

Building
--------

### On GNU/Linux:
To build the game you will need:
* SDL developement library: [www.libsdl.org](http://www.libsdl.org)
* SDL_ttf development library [http://www.libsdl.org/projects/SDL_ttf](http://www.libsdl.org/projects/SDL_ttf)
On debian-based distributions, a simple
`sudo apt-get install libsdl1.2-dev libsdl-ttf2.0-dev`
should do the job.

Then `make` to build the game.
    
### On Windows:
To build with ming32, you need SDL and SDL_ttf Libraries as well. Paste Include files into {include path}\SDL and lib files into {lib path}. Make sure you add these options for link editing:
`-lmingw32 -lSDLmain -lSDL`

To run the game, put the SDL.dll and SDL_ttf.dll files in the same directory as the built exe.

About
-----

This little game is intended to have fun, train your memory skills and obviously for the developper to play with SDL Library features and object-oriented programming

Thanks
------

 **Matthew Welch** for the *Hit The Road* font I used. See [http://www.squaregear.net/fonts/](http://www.squaregear.net/fonts/).