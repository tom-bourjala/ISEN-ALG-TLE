# Module List & Files
moduleList = Game List Turrets Robots Maps UI Language
moduleListC = $(moduleList:=/*.c)
moduleListPathC = $(addprefix ../Source/,$(moduleListC))
moduleListH = $(moduleList:=/*.h)
moduleListPathH = $(addprefix ../Source/,$(moduleListH))

# config
# flags = -lm
flags = -lm $(shell pkg-config --cflags --libs sdl2) -lSDL2_ttf -lSDL2_image -Og

# EXECUTABLE
# cp ../Source/main.c $(moduleListPathC) $(moduleListPathH) ./
TheLastEngineer:
	gcc -Wall ../Source/main.c $(moduleListPathH) $(moduleListPathC) -o TheLastEngineer $(flags)

debug:
	gcc -Wall ../Source/main.c $(moduleListPathH) $(moduleListPathC) -o TheLastEngineer $(flags) -g3

nodeMap:
	gcc -Wall ../Source/nodeMap.c $(moduleListPathH) $(moduleListPathC) -o nodeMap $(flags) -g3

clear:
	rm TheLastEngineer