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
	event/event_op.c \
	event/event_queue.c \
	dispatcher/dispatcher_routine.c \
	dispatcher/create_dispatcher_data.c \
	philos/philosopher.c \
	philos/philosopher_routine.c \
	philos/philo_data.c \
	philos/philo_init.c \
	utils/time_func.c \
	utils/compare_util.c \
	utils/free_and_set_null.c \
	utils/ft_atoi.c \
	structures/linked_list/create_linked_list.c \
	structures/linked_list/ft_add_back.c \
	structures/linked_list/ft_add_front.c \
	structures/linked_list/ft_lst_iter.c \
	structures/linked_list/ft_insert.c \
	structures/linked_list/ft_lst_clear.c \
	structures/linked_list/ft_delete_node.c \
	structures/linked_list/ft_lst_new.c



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

t : re
	./$(NAME) 5 50 20 20 4
# 	 198 610 200 200 10

v : re
	valgrind --leak-check=full --show-leak-kinds=all \
	--tool=memcheck --errors-for-leak-kinds=all -s ./$(NAME)  1 180 60 60 5
h : re
	valgrind --tool=helgrind --history-level=full --num-callers=30 ./$(NAME) 1 180 60 60 5

.PHONY : all clean fclean re bonus

#valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all -s ./
# python3 src/__main__.py /home/ybutkov/Documents/Curriculum/philosophers/philo
