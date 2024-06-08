NAME = libft.a
SRC_DIR = .
PRINTF_DIR = ft_printf

SRCS = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(PRINTF_DIR)/*.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I $(SRC_DIR) -I $(PRINTF_DIR)

all: $(PRINTF_DIR)/ft_printf.a $(NAME)

$(PRINTF_DIR)/ft_printf.a:
	$(MAKE) -C $(PRINTF_DIR)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
