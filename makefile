LINK_TARGET = game

SETTINGS_TARGET = settings

SETTINGS_NONSENSE = $(later)

OBJS = \
       shapes.o \
       helper.o\
       vars.o\

GAME_OBJS =\
	game.o

SETTINGS_OBJS = \
	check.o \

REBUILDABLES = $(OBJS) $(SETTINGS_OBJS) $(LINK_TARGET)

all: $(LINK_TARGET)
	@printf "\e[0mdone\n"
	@printf "\e[0muse \e[92m./game\e[0m to play or \e[93m./settings\e[0m to view settings.\n"

$(LINK_TARGET): $(OBJS) $(SETTINGS_OBJS) $(GAME_OBJS) settings.h makefile
	gcc -o $@ settings.h $(GAME_OBJS) $(OBJS) -lsodium
	gcc -o $(SETTINGS_TARGET) settings.h $(OBJS) $(SETTINGS_OBJS) -lsodium

%.o : %.c settings.h
	gcc -o $@ -c $<

game.o: settings.h shapes.h helper.h vars.h
check.o: settings.h helper.h vars.h
shapes.o: settings.h vars.h


clean:
	@printf "\e[0m"
	rm -f $(REBUILDABLES)
	rm -f globalvars.h
