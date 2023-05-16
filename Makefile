SRCS_MAIN = main.cpp Server.cpp Client.cpp Channel.cpp utils.cpp
SRCS = $(addprefix srcs/, $(SRCS_MAIN))

# COMMANDS_SRC will add prefix commands/ and suffix .cpp to nick.cpp, user.cpp, pass.cpp
COMMANDS = nick user pass
COMMANDS_SRC = $(addprefix srcs/commands/, $(addsuffix .cpp, $(COMMANDS)))
SRCS += $(COMMANDS_SRC)

OBJS = $(SRCS:.cpp=.o)

DEPS = $(SRCS:.cpp=.d)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 
CXXFLAGS += -MMD
# CFLAGS += -g3
# CFLAGS += -fsanitize=address
INCLUDE = -I. 

NAME = ircserv

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CPPFLAGS) $(INCLUDE) -o $(NAME) $(OBJS)

-include $(DEPS)

clean:
	rm -f $(OBJS) $(DEPS)

fclean: clean
	rm -f $(NAME)

re: fclean all

mac: $(NAME)
	make && ./$(NAME) 6667 pass && make fclean

leak: $(NAME)
	make && valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 6667 pass && make fclean

.PHONY: all clean fclean re mac leak 
