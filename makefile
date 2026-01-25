LINK_TARGET = game

SETTINGS_TARGET = settings

OBJS = \
       shapes.o \
       helper.o\

GAME_OBJS =\
	game.o

SETTINGS_OBJS = \
	check.o \

REBUILDABLES = $(OBJS) $(SETTINGS_OBJS) $(LINK_TARGET)

all: $(LINK_TARGET)
	@echo done
	@echo use './game' to play or './settings' to change settings

$(LINK_TARGET): $(OBJS) $(SETTINGS_OBJS) $(GAME_OBJS) settings.h
	gcc -o $@ $(GAME_OBJS) settings.h $(OBJS) -lsodium
	gcc -o $(SETTINGS_TARGET) settings.h $(OBJS) $(SETTINGS_OBJS) -lsodium


%.o : %.c clean
	gcc -o $@ -c $<


game.o: settings.h shapes.h helper.h
check.o: settings.h helper.h
shapes.o: settings.h


clean:
	rm -f $(REBUILDABLES)
