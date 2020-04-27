
# source directories
SD   = source
ID   = include
BD   = build

# files to install
EXE  = playing_with_SDL2

# header file
HDR  = ${ID}/cburggie.h

# object files to build
OBJ  = ${BD}/main.o
OBJ += ${BD}/constants.o
OBJ += ${BD}/App.o
OBJ += ${BD}/Font.o
OBJ += ${BD}/Logger.o
OBJ += ${BD}/Window.o
OBJ += ${BD}/Element.o
OBJ += ${BD}/EventHandler.o

LIB  = -L/usr/lib
LIB += -lpthread
LIB += -lSDL2
LIB += -lSDL2_ttf
LIB += -lSDL2_image

# compiler and options
CFLG = -Wall
CINC = -I${ID}
COPT = ${CFLG} ${CINC} -g
CC   = g++ ${COPT}


# recipes
all: ${EXE}

clean:
	rm -f ${OBJ}
	rm -f ${EXE}

${BD}:
	mkdir -p $@

${EXE}: ${BD} ${OBJ} ${HDR}
	${CC} -o $@ ${OBJ} ${LIB}

${BD}/image_test.o: ${SD}/image_test.cpp
	${CC} -o $@ -c $<

${BD}/main.o: ${SD}/main.cpp ${HDR}
	${CC} -o $@ -c $<

${BD}/constants.o: ${SD}/constants.cpp ${HDR}
	${CC} -o $@ -c $<

${BD}/App.o: ${SD}/App/App.cpp ${HDR} ${ID}/cburggie_App.h
	${CC} -o $@ -c $<

${BD}/Font.o: ${SD}/Font/Font.cpp ${HDR} ${ID}/cburggie_Font.h
	${CC} -o $@ -c $<

${BD}/Logger.o: ${SD}/Logger/Logger.cpp ${HDR} ${ID}/cburggie_Logger.h
	${CC} -o $@ -c $<

${BD}/Window.o: ${SD}/Window/Window.cpp ${HDR} ${ID}/cburggie_Element.h
	${CC} -o $@ -c $<

${BD}/Element.o: ${SD}/Element/Element.cpp ${HDR} ${ID}/cburggie_Element.h
	${CC} -o $@ -c $<

${BD}/EventHandler.o: ${SD}/EventHandler/EventHandler.cpp ${HDR} ${ID}/EventHandler.h
	${CC} -o $@ -c $<
