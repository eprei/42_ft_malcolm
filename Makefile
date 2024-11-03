NAME = ft_malcolm

SRC_DIR = src
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRCS:.c=.o)

NAME_LIB_FT = libft.a
LIB_FT_PATH = ./libft/

TEST_PATH = ./test/
TEST_NAME = test

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c99

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB_FT_PATH)
	$(CC) $(CFLAGS) -g $(OBJ) -L$(LIB_FT_PATH) -lft -o $(NAME)
	@$(CC) $(CFLAGS) $(TEST_PATH)$(TEST_NAME)".c" -o $(TEST_PATH)$(TEST_NAME)

clean:
	@rm -rf $(OBJ)
	@make clean -C $(LIB_FT_PATH)

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIB_FT_PATH)
	@rm -rf $(TEST_PATH)$(TEST_NAME)


test: all
	@$(TEST_PATH)$(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test