LINK_TARGET = game

SETTINGS_NONSENSE = $(later)

OBJS = \
       shapes.o \
       helper.o\
       vars.o\
       file.o\

GAME_OBJS =\
	game.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

all: $(LINK_TARGET)
	@printf "\e[0mdone\n"
	@printf "\e[0muse \e[92m./game\e[0m to play or \e[93m./settings\e[0m to view settings.\n"

$(LINK_TARGET): $(OBJS) $(GAME_OBJS) makefile vars.h helper.h
	gcc -o $@ $(GAME_OBJS) $(OBJS) -lsodium

%.o : %.c settings.h
	gcc -o $@ -c $<

game.o: shapes.h
helper.o: file.h shapes.h


clean:
	@printf "\e[0m"
	rm -f $(REBUILDABLES)
	rm -f globalvars.h
