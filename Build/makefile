# Module List & Files
moduleList = Game List Turrets Robots
moduleListC = $(moduleList:=/*.c)
moduleListPathC = $(addprefix ../Source/,$(moduleListC))
moduleListH = $(moduleList:=/*.h)
moduleListPathH = $(addprefix ../Source/,$(moduleListH))

# config
# flags = -lm
flags = -lm $(shell pkg-config --cflags --libs sdl2) -lSDL2_ttf -lSDL2_image -O2

# EXECUTABLE
# cp ../Source/main.c $(moduleListPathC) $(moduleListPathH) ./
TheLastEngineer:
	gcc -Wall ../Source/main.c $(moduleListPathH) $(moduleListPathC) -o TheLastEngineer $(flags)

debug:
	gcc -Wall ../Source/main.c $(moduleListPathH) $(moduleListPathC) -o TheLastEngineer $(flags) -g3

clear:
	rm TheLastEngineer