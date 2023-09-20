NAME := minishell

CC := cc

#CFLAGS := -Wall -Wextra -Werror -g
CFLAGS :=  -fsanitize=address -g
#CFLAGS := -Wall -Wextra -Werror -g
# find / -name libreadline.aCFLAGS := $(CFLAGS) -fsanitize=address
SRC := 	main.c free.c \
		parser/input_sort.c parser/input_type.c parser/input_type_strncmp.c \
		modified/modified_split_func.c modified/modified_lst_func.c

SRC_DIR := src
OBJ_DIR := obj

#INCLUDES := -I inc -I tools/ft_printf -I $(HOME)/goinfre/.brew/opt/readline/include/readline/ -L $(HOME)/goinfre/.brew/opt/readline/lib/
INCLUDES := -I inc -I tools/ft_printf -I readline/include/readline -L readline/lib

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJ)
	@make -C tools/ft_printf
	
	$(CC) -lreadline $(CFLAGS) $(OBJ) -o $(NAME) tools/ft_printf/libftprintf.a $(INCLUDES)
#	@echo "Linking $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/modified
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
