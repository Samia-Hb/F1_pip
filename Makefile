CFLAGS = -Wall -Wextra -Werror
CC = cc
NAME = pipex
SRCS = main.c pipex.c pipex_utils.c parsing.c\
		libft/ft_strncmp.c libft/ft_strlen.c libft/ft_strcpy.c libft/ft_strcat.c libft/ft_split.c libft/ft_strtrim.c libft/ft_strdup.c libft/ft_strjoin.c \
		ft_printf/ft_printf.c ft_printf/ft_putchar.c ft_printf/ft_putnbr_base.c \
		ft_printf/ft_putnbr_signed.c ft_printf/ft_putnbr_unsigned.c ft_printf/ft_putstr.c ft_printf/ft_putnbr_base_adr.c \
		multiple_pipe.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: clean all