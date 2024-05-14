NAME = ircserv

OBJS = main.cpp main_loop.cpp User.cpp SocketServer.cpp Quit.cpp Channel.cpp

SRCS = ${subst .cpp,.o,$(OBJS)}

CXX = c++

FLAGS = -std=c++98 -Wall -Werror -Wextra

all: ${NAME}

${NAME}: ${OBJS}
	@printf "\n"
	@printf "Creating your Internet Relay Chat Server ! : \n"
	${CXX} ${FLAGS} -o ${NAME} ${OBJS}
	@printf "\n"
	@printf "Executable file : ircserv\n"
	@printf "Arguments needed : \n"
	@printf "1 : port - The port number on which your IRC server will be listening to for incoming IRC connections. \n"
	@printf "2 : password - The connection password. It will be needed by any IRC client that tries to connect to your server. \n"
	@printf "\n"

main.o: main.cpp SocketServer.hpp User.hpp Channel.hpp Server_comments.hpp
	${CXX} ${CFLAGS} -c main.cpp

SocketServer.o: SocketServer.hpp

User.o: User.hpp

clean:
	rm -rf ${SRCS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean re%

