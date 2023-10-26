NAME := minishell

CC := cc

#CFLAGS := -g
CFLAGS :=  -fsanitize=address -g
#CFLAGS := -Wall -Wextra -Werror -g
# find / -name libreadline.aCFLAGS := $(CFLAGS) -fsanitize=address
SRC :=	free.c dup.c print.c \
        parser/input_sort.c parser/input_type.c parser/input_type_strncmp.c parser/env_var.c parser/create_array.c parser/fill_tmp.c parser/error_msg.c parser/get_commands.c \
        modified/modified_lst_func.c modified/modified_split_func.c modified/modified_split_func_two.c modified/modified_strjoin_func.c modified/modified_strjoin_nocheck.c modified/modified_get_env.c modified/modified_substr_func.c\
        main.c \
		executer/execute.c \
		executer/ft_check_command_and_get_path.c \
		executer/utils.c \
		executer/ft_special_split.c \
		executer/errors.c \
		executer/ft_get_command_arg_array.c \
		executer/fork.c \
		executer/utils_two.c \
		builtins/builtins_utils.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/export.c \
		builtins/pwd.c \
		builtins/unset.c \
		builtins/cd.c \
		builtins/exit.c \
		executer/init.c \
		executer/pipe.c \
		executer/pipe_utils.c

SRC_DIR := src
OBJ_DIR := obj

#INCLUDES := -I inc -I tools/ft_printf -I $(HOME)/goinfre/.brew/opt/readline/include/readline/ -L $(HOME)/goinfre/.brew/opt/readline/lib/
#INCLUDES := -I inc -I tools/ft_printf -I readline/include/readline -L readline/lib

OBJ := $(SRC:%.c=$(OBJ_DIR)/%.o)

READLINE_PATH = ${PWD}/readline

INCLUDES := -I inc -I tools/ft_printf  -I${READLINE_PATH}/includes -L${READLINE_PATH}/lib -lreadline -lhistory -ltermcap

all: $(NAME)

$(NAME): $(OBJ)
#	@make -C tools/ft_printf


	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) tools/ft_printf/libftprintf.a $(INCLUDES)
#	@echo "Linking $(NAME)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c inc/
	@make -C tools/ft_printf
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/parser
	@mkdir -p $(OBJ_DIR)/modified
	@mkdir -p $(OBJ_DIR)/executer
	@mkdir -p $(OBJ_DIR)/builtins
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) tools/ft_printf/libftprintf.a
	@echo "Compiling $<"

clean:
	@rm -rf $(OBJ_DIR)
	@make -C tools/ft_printf clean

fclean: clean
	@rm -f $(NAME)
	@make -C tools/ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
