LINK_TARGET = game

SETTINGS_NONSENSE = $(later)

OBJS = \
       shapes.o \
       helper.o\
       vars.o\
       file.o\
       render.o\

GAME_OBJS =\
	game.o

REBUILDABLES = $(OBJS) $(LINK_TARGET)

all: $(LINK_TARGET)
	@printf "\e[0mdone\n"
	@printf "\e[0muse \e[92m./game\e[0m to play or edit \e[93msettings.txt\e[0m or \e[93mcolor.txt\e[0m to change settings.\n"

$(LINK_TARGET): $(OBJS) $(GAME_OBJS) makefile vars.h helper.h
	gcc -o $@ $(GAME_OBJS) $(OBJS) -lsodium

%.o : %.c settings.h
	gcc -o $@ -c $<

game.o: shapes.h
helper.o: file.h shapes.h render.h


clean:
	@printf "\e[0m"
	rm -f $(REBUILDABLES)
	rm -f globalvars.h
