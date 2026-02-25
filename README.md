# shapes-game
A game about shapes.

# requirements
`make, gcc, libsodium`

Fedora:\
`sudo dnf install make gcc libsodium-devel`

Debian: \
`sudo apt install make gcc libsodium-dev`

Arch (with pacman): \
`sudo pacman -S make gcc libsodium`

# installation and running
installation:
```
git clone https://github.com/me05458/shapes-game&&cd shapes-game
make
```
to run the game: `./game`

# settings
There are two settings files: settings.txt and color.txt. Settings.txt has all of the normal settings, described below (not necessarily in ordder). color.txt has all of the colors in it. (see [color.txt](#colortxt))

## basic stuff
- `verbose`: if this is set to 1, settings will be printed out at start of game. Otherwise, they won't.
- `reload`: if this is set to 1, when a piece cannot be placed on the board, a new piece will be generated. If this is set to 0, you will loose once a piece cannot be placed.
- `clear`: if this is set to 1, completed rows and collumns will be cleared (the game is won if you clear the whole field and lost if there is nowhere left to place a piece if RELOAD is disabled). 0 will use normal mode.
- `subdivisions`: this is the amount of "subsections" the field will be broken into. This doesn't have to go into size an even number of times, but it looks better if it does. This is purely visual so that the field looks better. Values of <=2 usually look bad. **don't set this to 0!** that will break everything in all sorts of fun catastrophic ways. If you don't want subdivisions, set `BIGOFF` to 0 instead.

## blocks
Should be entered in the blocks: line in settings. The following formatting must be followed, or the game cannot run:
```blocks: <#>,<#>,<#>```
Supported blocks are:  

   0. square
```
x
```
1. line
```
x
x
x
```
2. line
```
xxx
```
3. square
```
xx
xx
```
4. line
```
xx
```
5. line
```
x
x
```
6. square
```
xxx
xxx
xxx
```
7. plus
```
 x
xxx
 x
```
8. bent shape thingy
```
xxx
x
```
9. bent shape thingy
```
xxx
  x
```
10. bent shape thingy
```
x
xxx
```
11. bent shape thingy
```
  x
xxx
```

## random advanced stuff
- `wait time`: this is the amount (in ms) that the stars will falsh for when a line is cleared (assuming CLEAR is enabled).
- `normal coordinates`: if this is 1, enter coordinates in terms of <col>/<row>, if this is 0 enter them <row>/<col>
- `double numbers`: if this is 0, coordinates are to be entered with a comma between them (4,5). If this is 1, for SIZE <= 10, enter coordinates in format 01. For SIZE > 10 eter coordinates in the format 0102.
- `animate`: if this is 0, dissappearing rows will have all *s and vanish. If this is 1, vanishing animation will be played.

## color stuff
It is possible to mess the color stuff up so badly it breaks the game. If this is the case, the game will warn you and you can use the settings application to find out where the issue is.  
- `BASECOL`: this is the base color of the background. The smaller it is, the darker the backgorund will be. (the background is always gray unless you mess with the MOD values described bellow)
- `BIGOFF`: this is the difference in darkness between subsections. (darker parts are darker by this much)
- `SMALLOFF`: this is the difference in darkness between adjacent squares. This should be less than `BIGOFF`.
- `RMOD` `GMOD` and `BMOD`: these can be used to set different colors in the background (these numbers will be added to the r, g, and b components of the base color respectively). Messing with these can quite easily break the game.
- `MODCOL`: unlike it's dangerous cousin (linked below), MODCOL doesn't really hurt you. If this is 1, BIGOFF and SMALLOFF will be applied to blocks placed in the field. Otherwise, it wont. Turning this off can help with some color problems.
- `MODBLOCK`: **I DON'T RECOMMEND TURNING THIS ON**. This means that the MOD values are applied to block colors, which will make everything very weird very fast, and will probably break the game. But hey, it's there if you want to mess with it, I guess. I don't know why I put it in.

## color.txt
This guy just has each color's r,g,b values listed separated by commas. USE NO SPACES or odd formatting. This will fundamentally break the game. The first color is the default color in case something goes wrong, the others are each of the colors.

# known issues
- the `system()` function poses a security vulnerability
- no way to change settings from program
- Some iniefficiency/redundancy in rendering
- animation causes flickering
- Check (settings checker) DOES NOT EXIST AT ALL DON'T WORRY ABOUT IT
- Should really put overall helpers and game-specific helpers in different .h/.c files
- I just realized that the difference between hints and rendering is weird inelegant
- Tabs break everything but only in specific places
