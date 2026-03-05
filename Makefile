NAME = webserv
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

COLOUR_GREEN=\033[0;32m
COLOUR_RED=\033[0;31m
COLOUR_BLUE=\033[0;34m
COLOUR_END=\033[0m

PATH_SRCS = srcs/
PATH_OBJS = objs/

SRC = main.cpp HTTPRequest.cpp HTTPResponse.cpp ResponseGenerator.cpp

SRCS = $(addprefix $(PATH_SRCS), $(SRC))
OBJS = $(addprefix $(PATH_OBJS), $(SRC:.cpp=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(COLOUR_GREEN)Compiled ✅$(COLOUR_END)"

$(PATH_OBJS)%.o: $(PATH_SRCS)%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(PATH_OBJS)
	@echo "$(COLOUR_RED)Cleaned 🧹$(COLOUR_END)"

fclean: clean
	rm -rf $(NAME)
	@echo "$(COLOUR_RED)Cleaned all 🧹$(COLOUR_END)"

re: fclean all

.PHONY: all clean fclean re
