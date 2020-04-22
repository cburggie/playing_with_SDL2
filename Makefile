
# source directories
SD   = source
ID   = include
BD   = build

# files to install
EXE  = playing_with_SDL2

# header file
HDR  = ${ID}/cburggie.h
HDR += ${ID}/cburggie_App.h
HDR += ${ID}/cburggie_Font.h
HDR += ${ID}/cburggie_Logger.h

# tests
TST  = image_test

# object files to build
OBJ  = ${BD}/main.o
OBJ += ${BD}/constants.o
OBJ += ${BD}/App.o
OBJ += ${BD}/Font.o
OBJ += ${BD}/Logger.o
OBJ += ${BD}/Window.o
OBJ += ${BD}/Element.o

LIB  = -L/usr/lib
LIB += -lpthread
LIB += -lSDL2
LIB += -lSDL2_ttf
LIB += -lSDL2_image

# compiler and options
CFLG = -Wall
CINC = -I${ID}
COPT = ${CFLG} ${CINC}
CC   = g++ ${COPT}


# recipes
all: ${EXE}

test: ${TST}

clean:
	rm -f ${OBJ}
	rm -f ${EXE}

${BD}:
	mkdir -p $@

${EXE}: ${BD} ${OBJ} ${HDR}
	${CC} -o $@ ${OBJ} ${LIB}

image_test: ${BD}/image_test.o
	${CC} -o $@ $< ${LIB}

${BD}/image_test.o: ${SD}/image_test.cpp
	${CC} -o $@ -c $<

${BD}/main.o: ${SD}/main.cpp ${HDR}
	${CC} -o $@ -c $<

${BD}/constants.o: ${SD}/constants.cpp ${HDR}
	${CC} -o $@ -c $<

${BD}/App.o: ${SD}/App/App.cpp ${HDR}
	${CC} -o $@ -c $<

${BD}/Font.o: ${SD}/Font/Font.cpp ${HDR}
	${CC} -o $@ -c $<

${BD}/Logger.o: ${SD}/Logger/Logger.cpp ${HDR}
	${CC} -o $@ -c $<

${BD}/Window.o: ${SD}/Window/Window.cpp ${HDR}
	${CC} -o $@ -c $<

${BD}/Element.o: ${SD}/Element/Element.cpp ${HDR}
	${CC} -o $@ -c $<
