CC = cc

CFLAGS = -fsanitize=address
COMFILE_FLAGS = -I${HOME}/.brew/opt/readline/include
LDFLAGS = -L${HOME}/.brew/opt/readline/lib
LDLIBS = -lreadline

SRCS = ./parse/main.c \
	   ./parse/tokenize.c \
	   ./parse/pipe.c \
	   ./parse/redirection.c \
	   ./parse/utils.c \
	   ./parse/cmd.c \
	   ./parse/env.c \
	   ./parse/path.c \
	   ./parse/replace.c \
	   ./parse/expand.c \
	   ./parse/syntax.c \
	   ./parse/free.c \
	   ./parse/signal.c \
	   ./parse/terminal.c \
	   ./execute/execute.c\
	   ./execute/heredoc.c \
	   ./builtins/builtins.c \
	   ./builtins/builtin_cd.c \
	   ./builtins/builtin_echo.c \
	   ./builtins/builtin_pwd.c \
	   ./builtins/builtin_env.c \
	   ./builtins/builtin_export.c \
	   ./builtins/builtin_unset.c \
	   ./builtins/builtin_exit.c \
	   ./builtins/builtin_utils.c  \
	   ./execute/pipe.c \
	   ./execute/process.c \
	   ./execute/redirection.c \
	   ./execute/execute_utils.c \
	   ./execute/execute_error.c \
	   ./builtins/builtin_error.c \
	   ./execute/heredoc_utils.c \
	   ./builtins/builtin_utils2.c \
	   ./builtins/builtin_error2.c 

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS)

	make all -C $(LIBFT_DIR) 
	$(CC) $(CFLAGS)  $(COMFILE_FLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft $(LDFLAGS) $(LDLIBS)
	@echo "\033[36m" --- 🔹 Compile Complete 🔹 ---


%.o : %.c
	$(CC) $(CFLAGS) $(COMFILE_FLAGS) -c -o $@ $<

clean :
	make fclean -C $(LIBFT_DIR)
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
