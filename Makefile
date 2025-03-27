# Name
NAME 			= minishell

# Compiler and flags
CC 				= cc
CFLAGS 			= -Wall -Wextra -Werror -g
#RLFLAGS			= -lreadline -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include
LDFLAGS			 = -lreadline -L /opt/homebrew/opt/readline/lib -I /opt/homebrew/opt/readline/include

#-L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
#CFLAGS 			= -Wall -Wextra -Werror -g
#RLFLAGS			= -lreadline -L ~/.brew/opt/readline/lib -I ~/.brew/opt/readline/include
#LDFLAGS 		= -fsanitize=address  -fsanitize=address -g
INCLUDES 		= -I./includes -I./libft/includes
RM 				= rm -f

# LIBFT
LIBFT	 		= ./libft/libft.a

# Source files by directory
DIR_PAR 		= srcs/envp/envp_duplicate.c	\
				srcs/minishell/minishell_initiate.c	\
				srcs/minishell/cleanup_mshell.c	\
				srcs/parse/pre_validation_input.c	srcs/parse/utils_pre_validation.c	\
				srcs/parse/error_handle_parse.c	srcs/parse/parse_input.c\
				srcs/parse/split_input_by_pipe.c	srcs/parse/tokenize_input.c\
				srcs/parse/utils_tokenize.c		srcs/parse/utils_expand.c\
				srcs/parse/token_creation.c		srcs/parse/utils_token_creation.c\
				srcs/parse/test_parse.c		srcs/parse/splitted_cmd.c	\
				srcs/parse/token_post_process.c		srcs/parse/token_expand.c	\
				srcs/parse/token_quote_remove.c		srcs/parse/token_merge.c	\
				srcs/parse/redirect_list_create.c	srcs/parse/cleanup_input.c\

DIR_REDI 		= srcs/redirect/redirect_fds.c	srcs/redirect/redirect_handle.c\
				srcs/redirect/error_handle_file.c	srcs/redirect/heredoc_handle.c	\
				srcs/redirect/heredoc_expand.c	\

DIR_EXE 		= srcs/execution/command_path.c	srcs/execution/execution.c\
				srcs/execution/utils_execution.c	srcs/execution/error_handle_exe.c	\

# DIR_EXE 		= srcs/execution/command_path.c	srcs/execution/execution.c\
# 				srcs/execution/utils_execution.c	srcs/execution/execution_child.c	\

MAN_BUILT  		= srcs/builtins/ft_pwd.c \
				srcs/builtins/ft_env.c 	srcs/builtins/ft_export.c \
				srcs/builtins/ft_cd.c 	srcs/builtins/ft_echo.c \
				srcs/builtins/ft_unset.c srcs/builtins/builtins_error_handle.c \
				srcs/builtins/builtins.c srcs/builtins/utils_cd.c \
				srcs/builtins/env_init.c  srcs/builtins/utils_export.c \
				srcs/builtins/utils_builtins.c \
				srcs/builtins/ft_exit.c \
				srcs/signals/signals.c      srcs/signals/utils_signals.c \
				#srcs/minishell/minishell_initiate.c

# Source path

MAN_SRCS		= main.c $(MAN_BUILT) $(DIR_PAR) $(DIR_REDI) $(DIR_EXE)

# Marker files to track which version is built
#mandatory : .mandatory
#bonus : .bonus

valgrind:
		valgrind --leak-check=full --show-reachable=yes --show-leak-kinds=all \
		--track-origins=yes --track-fds=yes --trace-children=yes \
		--suppressions=readline.supp -s ./minishell

all: mandatory

$(LIBFT):
	$(MAKE) -C ./libft

mandatory : .mandatory
.mandatory: $(LIBFT) $(MAN_SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(MAN_SRCS) $(LIBFT) -o $(NAME)
	@touch .mandatory

clean:
	$(MAKE) -C ./libft clean
	$(RM) .mandatory

fclean: clean
	$(MAKE) -C ./libft fclean
	$(RM) $(NAME) .mandatory

re: fclean all

.PHONY: all clean fclean re
