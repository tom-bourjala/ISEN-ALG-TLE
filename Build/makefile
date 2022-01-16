# Module List & Files
moduleList = Game
moduleListC = $(moduleList:=/*.c)
moduleListPathC = $(addprefix ../Source/,$(moduleListC))
moduleListH = $(moduleList:=/*.h)
moduleListPathH = $(addprefix ../Source/,$(moduleListH))

# files to compile
subModuleList = main
subListC = $(subModuleList:=.c)

# config
# flags = -lm
flags = -lm $(shell pkg-config --cflags --libs sdl2) -lSDL2_ttf

# EXECUTABLE
# cp ../Source/main.c $(moduleListPathC) $(moduleListPathH) ./
AirDolphinApp:
	gcc -Wall ../Source/main.c $(moduleListPathH) $(moduleListPathC) -o TheLastEngineer $(flags)
	rm *.c
	rm *.h

clear:
	rm TheLastEngineer
	rm *.c
	rm *.h