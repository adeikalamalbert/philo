NAME = philo

SRC = 	main.c \
		minilibft.c \
		init.c \
		loop.c \
		loop_utils.c \
		exec_utils.c

OBJ := $(SRC:%.c=%.o)

CC = cc
CCFLAGS = -Werror -Wall -Wextra -pthread

all: $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -I. -c $< -o $@

$(NAME): $(OBJ) 
	$(CC) $(CCFLAGS) $^ -o $@

sanitize_thread: CCFLAGS += -fsanitize=thread -g
sanitize_thread: re

sanitize_memory: CCFLAGS += -fsanitize=address -g
sanitize_memory: re

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re sanitize_memory sanitize_thread 
