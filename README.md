# shapes-game
A game about putting shapes in a box
(doesn't actually do anything yet)

# requirements
`make, gcc, libsodium`

Fedora:\
`sudo dnf install make gcc libsodium-devel`

Debian: \
`sudo apt install make gcc libsodium-dev`

# installation and running
installation:
```
git clone https://github.com/me05458/code-game&&cd code-game
make
```
to run the game: `./game`\
to run the settings: `./settings`

# known issues
- the `system()` function poses a security vulnerability
