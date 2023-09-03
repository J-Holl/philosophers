NAME = philo

# Compile
CC = clang
CFLAGS = -Wall -Wextra -Werror -pthread #-fsanitize=thread
INC = -I$(INC_DIR)
HEADER = $(INC_DIR)/philo.h

# Location
SRC_DIR = src
INC_DIR = inc

# Source files
MAIN = philo.c time.c init.c write.c routine.c action.c write_utils.c
SRC = $(addprefix src/, $(MAIN)) 

# Object files
OBJ = $(SRC:.c=.o)

# Patern rule 
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c ${HEADER}
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
