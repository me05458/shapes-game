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
to run the game: `./game`\
to run the settings (this will allow you to debug colors/settings or just view stuff): `./settings`

# settings
The settings file has the following definitions. You can change them depending on desired game behavior:
For example, if you want to change the RELOAD definition, change `#define RELOAD 0` to `#define RELOAD <YOUR VALUE>`

## basic stuff:
- `RELOAD`: if this is set to 1, when a piece cannot be placed on the board, a new piece will be generated. If this is set to 0, you will loose once a piece cannot be placed.
- `CLEAR`: if this is set to 1, completed rows and collumns will be cleared (the game is won if you clear the whole field and lost if there is nowhere left to place a piece if RELOAD is disabled). 0 will use normal mode.
- `SIZE` is the side length of the field. If you make this too small, you'll have a hard time playing.
- `SUBDIV`: this is the amount of "subsections" the field will be broken into. This doesn't have to go into size an even number of times, but it looks better if it does. This is purely visual so that the field looks better. Values of <=2 usually look bad. **don't set this to 0!** that will break everything in all sorts of fun catastrophic ways. If you don't want subdivisions, set `BIGOFF` to 0 instead.

## random advanced stuff:
- `WAITTIME`: this is the amount (in ms) that the stars will falsh for when a line is cleared (assuming CLEAR is enabled).
- `NORM_COORD`: if this is 1, enter coordinates in terms of <col>/<row>, if this is 0 enter them <row>/<col>
- `DOUBLEINT`: if this is 0, coordinates are to be entered with a comma between them (4,5). If this is 1, for SIZE <= 10, enter coordinates in format 01. For SIZE > 10 eter coordinates in the format 0102.
- `ANIMATE`: if this is 0, dissappearing rows will have all *s and vanish. If this is 1, vanishing animation will be played.

## color stuff:
It is possible to mess the color stuff up so badly it breaks the game. If this is the case, the game will warn you and you can use the settings application to find out where the issue is.  
- `TEXTCOL`: this is the color of the star that marks the spot that is being placed. Consider setting it to `0,0,0` if using light colors and `225,225,225` if using dark colors (it uses RGB).
- `BASECOL`: this is the base color of the background. The smaller it is, the darker the backgorund will be. (the background is always gray unless you mess with the MOD values described bellow)
- `BIGOFF`: this is the difference in darkness between subsections. (darker parts are darker by this much)
- `SMALLOFF`: this is the difference in darkness between adjacent squares. This should be less than `BIGOFF`.
- `RMOD` `GMOD` and `BMOD`: these can be used to set different colors in the background (these numbers will be added to the r, g, and b components of the base color respectively). Messing with these can quite easily break the game.
- `MODBLOCK`: **I DON'T RECOMMEND TURNING THIS ON**. This means that the MOD values are applied to block colors, which will make everything very weird very fast, and will probably break the game. But hey, it's there if you want to mess with it, I guess. I don't know why I put it in.

## more color stuff:
- `COLORS`: This describes all of the colors that should be included in the game. The first color should be the backup color in case something goes wrong. They should be described in the following format: ```{{default r, default g, default b},{color1 r, color1 g, color1 b},{color2 r, color2 g, color3 b}}```
Another, advanced, way of describing them is:
```
#define COLORONENAME r, g, b
#define COLORTWONAME r, g, b
#define COLORTHREENAME r,g,b
#define BACKUPCOLOR r,g,b
#define COLORS {{BACKUPCOLOR},{COLORONENAME},{COLORTWONAME},{COLORTHREENAME}}
```
- `COLNUM`: This is the number of colors (not collumns, sorry). This has to be the number of your colors excluding the backup color. This has to be correct in order for all colors to be displayed, but an incorrect value will not break the game.

## block stuff:
Supported blocks are:  
0. square:
```
x
```
1. line:
```
x
x
x
```
2. line:
```
xxx
```
3. square:
```
xx
xx
```
4. line:
```
xx
```
5. line:
```
x
x
```
6. square (note that it is your business to make sure that the board size is big enough for any of the blocks you choose)
```
xxx
xxx
xxx
```
7. cross thing
```
 x
xxx
 x
```
- `BLOCKS` is defined a bit like colors, in the form `{#,#,#}` where the #s are the numbers of blocks described above you wish to use.
- `BLOCKNUM` works exactly like colornum, except for types of block.

# known issues
- the `system()` function poses a security vulnerability
- Messing with the settings.h file seems like it could pose an issue
- Some iniefficiency/redundancy in rendering
- animation causes flickering
- the shapes stuff is quite inelegant and needs fixing
- Settings has some problems with field rendering (you have to press enter on it)
