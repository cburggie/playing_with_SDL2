
# source directories
SD   = source
ID   = include
BD   = build

# files to install
EXE  = playing_with_SDL2.exe

# header file
HDR  = ${ID}/cburggie.h
HDR += ${ID}/cburggie_App.h
HDR += ${ID}/cburggie_Font.h
HDR += ${ID}/cburggie_Logger.h


# object files to build
OBJ  = ${BD}/main.o
OBJ += ${BD}/App.o
OBJ += ${BD}/Font.o
OBJ += ${BD}/Logger.o

LIB  = -L/usr/lib
LIB += -lpthread
LIB += -lSDL2
LIB += -lSDL2_ttf

# compiler and options
CFLG = -Wall
CINC = -I${ID}
COPT = ${CFLG} ${CINC}
CC   = g++ ${COPT}


# recipes
all: ${EXE}

clean:
	rm -f ${OBJ}
	rm -f ${EXE}
	rmdir ${BD}

${BD}:
	mkdir -p $@

${EXE}: ${BD} ${OBJ} ${HDR}
	${CC} -o $@ ${OBJ} ${LIB}

${BD}/main.o: ${SD}/main.cpp ${HDR}
	${CC} -o $@ -c $<

${BD}/App.o: ${SD}/App/App.cpp ${HDR}
	${CC} -o $@ -c $<

${BD}/Font.o: ${SD}/Font/Font.cpp ${HDR}
	${CC} -o $@ -c $<

${BD}/Logger.o: ${SD}/Logger/Logger.cpp ${HDR}
	${CC} -o $@ -c $<
