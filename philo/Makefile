NAME = philo
NAME_C = philo.c

SRC = src
BUILD_DIR =	build

INCLUDES = -Iincludes

PRINT_FLAG = -s --no-print-directory

CC = cc
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address,undefined
CFLAGS = -Wall -Wextra -Werror -g -O0 $(INCLUDES)

C_PHILO_FILES = \
	printer/printer.c \
	event/event.c \
	utils/time_func.c \
	structures/base_stack/stack_base_basic.c \
	structures/base_stack/stack_base_core.c \
	structures/base_stack/stack_base_operations.c


C_FIlES = $(addprefix $(SRC)/, $(C_PHILO_FILES))
C_OBJ_FIlES =	$(C_FIlES:%.c=$(BUILD_DIR)/%.o)

BUILD_DIRS := $(sort $(dir $(C_OBJ_FIlES)))

all : $(NAME)
bonus : all

${NAME} : $(BUILD_DIRS) $(C_OBJ_FIlES)
	$(CC) $(CFLAGS) $(C_OBJ_FIlES) $(NAME_C) -o $(NAME)
	echo "Build OK"

clean :
	rm -rf $(BUILD_DIR)
	echo "clean OK"

fclean f: clean
	rm -f $(NAME)
	echo "fclean OK"

re	: fclean all

$(BUILD_DIRS):
	mkdir -p $@

$(BUILD_DIR)/%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : all clean fclean re bonus

#valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all -s ./pipex "infiles/basic.txt" "nonexistingcommand" "cat -e" "outfiles/outfile"
