CC = cc

<<<<<<< HEAD
CFLAGS = -g3 -fsanitize=address
COMFILE_FLAGS = -I${HOME}/.brew/opt/readline/include
LDFLAGS = -L${HOME}/.brew/opt/readline/lib
LDLIBS = -lreadline

=======
CFLAGS = -Wall -Wextra -Werror
>>>>>>> 70bcc58bf02d3999aa1e72f95622baece5918269


SRCS = ./parse/main.c \
	   ./parse/tokenize.c \
	   ./parse/redirection.c \
	   ./parse/utils.c \
	   ./parse/cmd.c \
	   ./parse/env.c \
	   ./parse/path.c \
	   ./parse/replace.c \
	   ./parse/syntax.c \
	   ./parse/free.c \
	   ./parse/signal.c \
<<<<<<< HEAD
	   ./parse/terminal.c \
	   ./execute/execute.c\
	   ./execute/error.c \
	   ./builtins/builtins.c\
	   ./builtins/builtin_cd.c\
	   ./builtins/builtin_echo.c\
	   ./builtins/builtin_pwd.c\
	   ./builtins/builtin_env.c\
	   ./builtins/ft_strncpy.c
=======
	   ./parse/terminal.c
	   ./execute/execute.c\
>>>>>>> 70bcc58bf02d3999aa1e72f95622baece5918269

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS)

	make all -C $(LIBFT_DIR) 
<<<<<<< HEAD
	$(CC) $(CFLAGS)  $(COMFILE_FLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft $(LDFLAGS) $(LDLIBS)
=======
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft -lreadline
>>>>>>> 70bcc58bf02d3999aa1e72f95622baece5918269
	@echo "\033[36m" --- 🔹 Compile Complete 🔹 ---


%.o : %.c
	$(CC) $(CFLAGS) $(COMFILE_FLAGS) -c -o $@ $<

clean :
	make fclean -C $(LIBFT_DIR)
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
