LINK_TARGET = game

SETTINGS_TARGET = settings

SETTINGS_NONSENSE = $(later)

OBJS = \
       shapes.o \
       helper.o\

GAME_OBJS =\
	game.o

SETTINGS_OBJS = \
	check.o \

REBUILDABLES = $(OBJS) $(SETTINGS_OBJS) $(LINK_TARGET)

all: $(LINK_TARGET)
	@printf "\e[0mdone\n"
	@printf "\e[0muse \e[92m./game\e[0m to play or \e[93m./settings\e[0m to change settings. Be sure to run \e[93mmake set\e[0m to update settings.\n"

$(LINK_TARGET): $(OBJS) $(SETTINGS_OBJS) $(GAME_OBJS) settings.h
	gcc -o $@ settings.h $(GAME_OBJS) $(OBJS) -lsodium
	gcc -o $(SETTINGS_TARGET) settings.h $(OBJS) $(SETTINGS_OBJS) -lsodium


%.o : %.c
	gcc -o $@ -c $<

game.o: settings.h shapes.h helper.h
check.o: settings.h helper.h
shapes.o: settings.h

set: clean
	make

clean:
	@printf "\e[0m"
	rm -f $(REBUILDABLES)
	rm -f globalvars.h
