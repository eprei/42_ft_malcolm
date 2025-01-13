NAME = ft_malcolm

SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRCS:.c=.o)

TEST_PATH = ./test/
TEST_NAME = test

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=gnu99

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -g $(OBJ) -o $(NAME)
	@$(CC) $(CFLAGS) $(TEST_PATH)$(TEST_NAME)".c" -o $(TEST_PATH)$(TEST_NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf $(TEST_PATH)$(TEST_NAME)


test: all
	@$(TEST_PATH)$(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test