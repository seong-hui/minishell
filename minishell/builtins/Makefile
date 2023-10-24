NAME = builtins
CFLAGS = -Wall -Wextra -Werror

SRCS :=
SRCS += builtin_echo.c
SRCS += builtin_pwd.c
SRCS += builtin_cd.c
SRCS += builtins.c
SRCS += ft_split.c
SRCS += ft_strlen.c
SRCS += ft_strncmp.c
SRCS += ft_strrchr.c
SRCS += ft_strncpy.c
SRCS += main.c
SRCS += execute.c
SRCS += utils.c
SRCS += utils2.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -c  $<

$(NAME): $(OBJS)
	$(CC) -o $@ $^
	@echo "\033[36m" --- 🔹 Compile Complete 🔹 ---

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY: all clean fclean re