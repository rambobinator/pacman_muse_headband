NAME = pacman
SRC = 	srcs/main.cpp \
		srcs/map.cpp \
		srcs/player.cpp \
		srcs/enemy.cpp

OSC = 	osc/tests/OscReceiveTest.o \
		osc/osc/OscTypes.o \
		osc/osc/OscReceivedElements.o \
		osc/osc/OscPrintReceivedElements.o \
		osc/ip/posix/UdpSocket.o \
		osc/ip/IpEndpointName.o \
		osc/ip/posix/NetworkingUtils.o

CC = clang++
CFLAGS = -stdlib=libc++ -Wall -Wextra -Werror -g
COMPILED_OBJ = $(SRC:.cpp=.o)
SFML = SFML2

LIBS = png GLEW jpeg sfml-audio-s sfml-graphics-s sfml-network-s sfml-system-s sfml-window-s 
COMPILED_LIBS = $(shell for l in $(LIBS); do echo '-l'$$l; done)

LIBS_DIRS = SFML2/lib libs
COMPILED_LIBS_DIRS = $(shell for l in $(LIBS_DIRS); do echo '-L'$$l; done)

INCLUDE_DIRS = SFML2/Include
COMPILED_INCLUDE_DIRS = $(shell for i in $(INCLUDE_DIRS); do echo '-I'$$i; done)

FRAMEWORKS = CoreFoundation CoreGraphics IOKit AppKit CoreServices Carbon OpenGL GlKit
COMPILED_FRAMEWORKS = $(shell for f in $(FRAMEWORKS); do echo '-framework '$$f; done) $(pkg-config --cflags --libs x11)

all: $(NAME)

$(NAME): $(SFML) $(COMPILED_OBJ) $(OSC)
	$(CC) $(CFLAGS) -o $@ $(COMPILED_OBJ) $(OSC) $(COMPILED_LIBS_DIRS) $(COMPILED_LIBS) $(COMPILED_FRAMEWORKS) /usr/X11/lib/libfreetype.6.dylib

$(OSC):
	make -C osc

%.o: %.cpp $(COMPILED_HEADERS)
	$(CC) $(CFLAGS) $(COMPILED_INCLUDE_DIRS) -o $@ -c $<

$(SFML):
	curl -O romanmasse.com/nibbler\'s_lib.zip
	unzip nibbler\'s_lib.zip
	mv nibbler\'s_lib/libs .
	mv nibbler\'s_lib/SFML2 .
	rm -rf nibbler\'s_lib nibbler\'s_lib.zip
	rm -rf __MACOSX

clean:
	rm -rf libs SFML2
	$(RM) $(COMPILED_OBJ)

fclean: clean
	$(RM) $(NAME)
	rm -rf __MACOSX SFML2 libs

re: fclean all

.PHONY: all clean fclean re
