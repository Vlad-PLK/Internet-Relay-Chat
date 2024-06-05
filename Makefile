NAME = ircserv

SRCS = $(shell find . -name "*.cpp")
OBJS = $(SRCS:.cpp=.o)

CXX = c++
FLAGS = -std=c++98 -Wall -Werror -Wextra -g3

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

%.o: %.cpp
	${CXX} ${FLAGS} -c $< -o $@

clean:
	rm -rf ${OBJS}

fclean: clean
	rm -rf ${NAME}

re: fclean all

.PHONY: all clean fclean re
