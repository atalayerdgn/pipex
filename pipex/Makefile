NAME = pipex

CC = cc

RM = rm -f

CFLAGS = -Wall -Werror -Wextra -g

SRC = pipex.c utils.c execute.c

all:	$(NAME)

$(NAME): $(SRC)
	@echo "\nCompiling the program files...\n"
	@make -s -C libft
	@$(CC) $(CFLAGS) $(SRC) libft/libft.a -o $(NAME)

clean:
	@find . -type f \( -name "*.o" \) -delete

fclean: clean
	@find . -type f \( -name "*.a" -o -name "pipex" \) -delete

re: fclean all
