NAME = philo

SRCS =	srcs/main.c \
		srcs/utils.c \
		srcs/philosophers.c \
		srcs/init.c \
		srcs/parsing.c \

FLAGS = -Wall -Wextra -Werror

HEADER_FILE = ./include

HEADERS = $(HEADER_FILE)/philo.h

OBJS = ${SRCS:.c=.o}

.PHONY: all
.PHONY: clean
.PHONY: fclean
.PHONY: re

$(NAME): $(OBJS)
	clang $(OBJS) -o $(NAME)

$(OBJS): %.o: %.c $(HEADERS)
	clang $(FLAGS) -I$(HEADER_FILE) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all