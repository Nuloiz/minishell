NAME := minishell

CC := gcc

CFLAGS := -Wall -Wextra -Werror -g
# CFLAGS := $(CFLAGS) -fsanitize=address
SRC := main.c input_sort.c input_type.c input_type_strncmp.c linked_list_utils.c free.c modified_libft_func.c

SRC_DIR := src
OBJ_DIR := obj

INCLUDES := -I inc -I tools/ft_printf

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C tools/ft_printf
	@$(CC) -I $(HOME)/goinfre/.brew/opt/readline/include/ -L $(HOME)/goinfre/.brew/opt/readline/lib/ -lreadline \
	$(CFLAGS) $(OBJ) -o $(NAME) tools/ft_printf/libftprintf.a
	@echo "Linking $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@echo "Compiling $<"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C tools/ft_printf clean

fclean: clean
	@rm -f $(NAME)
	@make -C tools/ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
