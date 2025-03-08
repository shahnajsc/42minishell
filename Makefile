# Name
NAME 			= minishell

# Compiler and flags
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -g
RLFLAGS			= -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
#LDFLAGS 		= -fsanitize=address  -fsanitize=address -g
INCLUDES 		= -I./includes -I./libft/includes
RM 				= rm -f

# LIBFT
LIBFT	 		= ./libft/libft.a

# Source files by directory
MAN_DIR 		= srcs/envp/envp_duplicate.c	\
				srcs/minishell/minishell_initiate.c	\
				srcs/parse/input_pre_validation.c	srcs/parse/utils_pre_validation.c	\
				srcs/parse/parse_error_handle.c	\

MAN_BUILT  		= srcs/builtins/ft_pwd.c \
				srcs/builtins/ft_env.c 	srcs/builtins/ft_export.c \
				srcs/builtins/ft_cd.c 	srcs/builtins/ft_echo.c \
				srcs/builtins/ft_unset.c srcs/builtins/builtins_error_handle.c \
				srcs/builtins/builtins.c srcs/builtins/utils_cd.c \
				srcs/builtins/env_init.c  srcs/builtins/utils_export.c \
				srcs/builtins/utils_builtins.c \
				srcs/minishell/minishell_initiate.c srcs/builtins/ft_exit.c \
				srcs/signals/signals.c \

# Source path

MAN_SRCS		= builtins_main.c $(MAN_BUILT)

# Marker files to track which version is built
#mandatory : .mandatory
#bonus : .bonus

all: mandatory

$(LIBFT):
	$(MAKE) -C ./libft

mandatory : .mandatory
.mandatory: $(LIBFT) $(MAN_SRCS)
	$(CC) $(CFLAGS) $(RLFLAGS) $(INCLUDES) $(MAN_SRCS) $(LIBFT) -o $(NAME)
	@touch .mandatory

clean:
	$(MAKE) -C ./libft clean
	$(RM) .mandatory

fclean: clean
	$(MAKE) -C ./libft fclean
	$(RM) $(NAME) .mandatory

re: fclean all

.PHONY: all clean fclean re
