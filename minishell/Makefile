CC = cc
CFLAGS = 

SRCS = ./parse/main.c \
	   ./parse/tokenize.c \
	   ./parse/redirection.c \
	   ./parse/utils.c \
	   ./parse/cmd.c \
	   ./parse/env.c \
	   ./parse/replace.c\
	   ./execute/execute.c\
	   

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft

NAME = minishell

all : $(NAME)

$(NAME) : $(OBJS)
	make all -C $(LIBFT_DIR) 
	$(CC) $(CFLAGS) -o $@ $^ -L$(LIBFT_DIR) -lft -lreadline
	@echo "\033[36m" --- 🔹 Compile Complete 🔹 ---

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean :
	make fclean -C $(LIBFT_DIR)
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all