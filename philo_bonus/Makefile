NAME = philo_bonus
NAME_C = philo_bonus.c

SRC = src
BUILD_DIR =	build

INCLUDES = -Iincludes

DEFAULT_SILENT ?= 1
ifneq ($(filter s,$(MAKECMDGOALS)),)
SILENT := 0
else
SILENT ?= $(DEFAULT_SILENT)
endif
ifeq ($(SILENT),1)
MAKEFLAGS += -s --no-print-directory
endif

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O0 $(INCLUDES)
SAN_ASAN = -fsanitize=address,undefined -fno-omit-frame-pointer

C_PHILO_FILES = \
	printer/printer.c \
	philos/philo_data.c \
	philos/philo.c \
	philos/philo_op.c \
	philos/philo_op_2.c \
	philos/philosopher.c \
	philos/philosopher_cycle.c \
	parcer/parcer.c \
	utils/time_func.c \
	utils/errors.c \
	utils/compare_util.c \
	utils/free_and_set_null.c \
	utils/ft_atoi.c \
	utils/ft_itoa.c \
	utils/ft_strlen.c \
	utils/ft_memmove.c \
	utils/ft_memset.c

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

asan: CFLAGS += $(SAN_ASAN)
asan: re

.PHONY : all clean fclean re bonus s

# Rules for testing
t : re
	./$(NAME) 5 50 20 20 4
1 : re
	./$(NAME) 4 310 200 100
2 : re
	./$(NAME) 5 800 200 200 3
3 : re
	./$(NAME) 5 800 200 200

v : re
	valgrind --leak-check=full --show-leak-kinds=all \
	--tool=memcheck --errors-for-leak-kinds=definite --run-libc-freeres=yes -s \
	./$(NAME)  6 180 181 60 2

h : re
	valgrind --tool=helgrind --history-level=full --num-callers=30 -s ./$(NAME) 19 210 71 60 2

#valgrind --leak-check=full --show-leak-kinds=all --errors-for-leak-kinds=all -s ./
# python3 src/__main__.py /home/ybutkov/Documents/Curriculum/philosophers/philo_bonus
