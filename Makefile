SRC_PATH:=./src/
SRC_NAME:=check_cd.c\
    check_env.c\
    check_exit.c\
    clear_cmd.c\
	check_setenv.c\
    create_cmd.c\
    check_cmd.c\
    env_error.c\
    env_rescue.c\
    errors.c\
    free.c\
    ft_builtin.c\
    ft_cd.c\
    ft_path.c\
    ft_sh1.c\
    ft_unsetenv.c\
    grep_env.c\
    misc_cd.c\
    prompt.c\
    set_env.c
 
CFLAGS=-Wall -Wextra -Werror
OBJ_PATH =./obj/
OBJ_NAME=$(SRC_NAME:.c=.o)
INC_PATH=./includes/
INC_NAME=libft.h\
		 get_next_line.h\
		ft_printf.h\
		ft_sh.h
SRC=$(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ=$(addprefix $(OBJ_PATH), $(OBJ_NAME))
INCF=$(addprefix $(INC_PATH), $(INC_NAME))
INC=$(addprefix -I, $(INC_PATH))
LIBFT:=-L libft -lftprintf
CFLAGS=-Wall -Wextra -Werror
CC=-gcc
NAME=ft_minishell1
RED=\033[30;41m
GREEN=\033[32m
CYAN=\033[36m
ORANGE=\033[33m
NC=\033[0m

all: $(NAME)

$(NAME):$(OBJ)
	@make -s -C libft
	@echo "${GREEN}Compile $(NAME) with $(CFLAGS)${NC}";
	@gcc $(CLFAGS) $(OBJ) $(INC) $(LIBFT) -o $(NAME)

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@echo "${ORANGE}Create bynary $(NAME) : $@ with $<${NC}";
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $<

clean:
	@echo "${RED} Delete OBJ files ${NC}"
	@rm -rf $(OBJ_PATH)

fclean: clean
	@echo "${RED} Delete $(NAME) file ${NC}"
	@rm -rf $(NAME)

re: fclean all clean

.PHONY: all clean fclean re
