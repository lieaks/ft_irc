SRCS_MAIN = main.cpp Server.cpp Client.cpp utils.cpp
SRCS = $(addprefix srcs/, $(SRCS_MAIN))
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
	make && ./$(NAME) && make fclean

leak: $(NAME)
	make && valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) && make fclean

.PHONY: all clean fclean re mac leak 
