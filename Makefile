# Mandatory files
SRCS_MAIN = main Server Client Channel utils
SRCS = $(addprefix srcs/, $(addsuffix .cpp, $(SRCS_MAIN)))

COMMANDS = nick user pass invite ping info version time privmsg notice oper wallops quit cap join squit mode topic kick
COMMANDS_SRC = $(addprefix srcs/commands/, $(addsuffix .cpp, $(COMMANDS)))

SRCS += $(COMMANDS_SRC)

OBJS = $(SRCS:.cpp=.o)

DEPS = $(SRCS:.cpp=.d)

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 
CXXFLAGS += -MMD
CFLAGS += -g3
# CFLAGS += -fsanitize=address
INCLUDE = -I. 

NAME = ircserv

flag:= 1
.cpp.o :
	@TERM="xterm-256color" setterm -cursor off
	@if [ $(flag) = "1" ]; then\
		clear ;\
		printf "\033[1;35m╔══════════════════════════════════════╗\n";\
		printf "║          IRC IS LOADING ...          ║\n";\
		printf "╠══════════════════════════════════════╣\n";\
	fi
	@printf "\033[1;32m║\033[32m                                                                              \033[m\r"
	@printf "\033[1;35m║\033[0;32m Compiling $@... \033[m\r"
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ 
	$(eval flag=$(shell echo $$(($(flag)+1))))

all: $(NAME)

$(NAME): $(OBJS) 
	@printf "\033[K\033[1;32m║ Irc: compiled                        ║\n\033[m"
	@$(CXX) $(CXXFLAGS) $(INCLUDE) $(OBJS) -o $(NAME)
	@printf "\033[1;32m╠══════════════════════════════════════╣\n"
	@printf "║         COMPILATION FINISHED !       ║\n"
	@printf "╚══════════════════════════════════════╝\n\033[m"
	@TERM="xterm-256color" setterm -cursor on

-include $(DEPS)

clean:
	@printf "\033[1;31m╔══════════════════════════════════════╗\n"
	@printf "║          IRC CLEANING ...            ║\n"
	@printf "╠══════════════════════════════════════╣\n\033[m"
	@printf "\033[K\033[1;31m║\033[1;33m Destroying objects                   \033[1;31m║\n\033[m"
	@rm -f $(OBJS) $(DEPS)
	@printf "\033[1;31m╚══════════════════════════════════════╝\n\033[m"

fclean:
	@printf "\033[1;31m╔══════════════════════════════════════╗\n"
	@printf "║          IRC CLEANING ...            ║\n"
	@printf "╠══════════════════════════════════════╣\n\033[m"
	@printf "\033[K\033[1;31m║\033[1;33m Destroying objects                   \033[1;31m║\n\033[m"
	@rm -f $(OBJS) $(DEPS)
	@printf "\033[K\033[1;31m║\033[1;31m Destroying all                       \033[1;31m║\n\033[m"
	@rm -f $(NAME)
	@printf "\033[1;31m╚══════════════════════════════════════╝\n\033[m"

re: fclean all

mac: $(NAME)
	make && ./$(NAME) 6667 pass && make fclean

leak: $(NAME)
	make && valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) 6667 pass && make fclean

.PHONY: all clean fclean re mac leak 
