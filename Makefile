# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hailong <hailong@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/11 08:38:16 by hailong           #+#    #+#              #
#    Updated: 2025/05/11 08:38:16 by hailong          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# executable name
NAME = minishell

# compiler & flags
CC = cc
# TODO clear up debugger
CFLAGS = -g -Wall -Wextra -Werror

VAL_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes --suppressions=supp.supp

# main src files
SRC_DIR = src
EXEC_DIR = $(SRC_DIR)/execution
BUILTIN_DIR = $(SRC_DIR)/builtin
MAIN_DIR = $(SRC_DIR)/main
PARSING_DIR = $(SRC_DIR)/parsing
SIG_DIR = $(SRC_DIR)/signal
PIPE_DIR = $(SRC_DIR)/pipe
EXPAND_DIR = $(SRC_DIR)/expander
REDIRECT_DIR = $(SRC_DIR)/redirect
SRC = $(BUILTIN_DIR)/set_env.c \
		$(BUILTIN_DIR)/init_builtin.c \
		$(BUILTIN_DIR)/ft_pwd.c \
		$(BUILTIN_DIR)/ft_cd.c \
		$(BUILTIN_DIR)/ft_echo.c \
		$(BUILTIN_DIR)/ft_env.c \
		$(BUILTIN_DIR)/ft_exit.c \
		$(BUILTIN_DIR)/ft_export.c \
		$(BUILTIN_DIR)/ft_unset.c \
		$(PARSING_DIR)/parsing.c \
		$(PARSING_DIR)/cmd_parser.c \
		$(PARSING_DIR)/exit_status.c \
		$(PARSING_DIR)/redirct.c \
		$(PARSING_DIR)/cmd_utils.c \
		$(PARSING_DIR)/cmd_builder.c \
		$(PARSING_DIR)/token_creation.c \
		$(PARSING_DIR)/token_validation.c \
		$(PARSING_DIR)/tokenize_operators.c \
		$(PARSING_DIR)/tokenize_quotes.c \
		$(PARSING_DIR)/tokenize_word.c \
		$(PARSING_DIR)/execution.c \
		$(MAIN_DIR)/minishell.c \
		$(MAIN_DIR)/utils.c \
		$(MAIN_DIR)/main.c \
		$(SIG_DIR)/signal.c \
		$(SIG_DIR)/signal_utils.c \
		$(EXEC_DIR)/execute_path.c \
		$(EXEC_DIR)/execute_utils.c \
		$(EXPAND_DIR)/expander.c \
		$(EXPAND_DIR)/var_expand.c \
		$(EXPAND_DIR)/expand_utils.c \
		$(PIPE_DIR)/pipe.c \
		$(PIPE_DIR)/pipe_exec.c \
		$(PIPE_DIR)/pipe_input.c \
		$(PIPE_DIR)/pipe_output.c \
		$(PIPE_DIR)/pipe_setup.c \
		$(PIPE_DIR)/pipe_signal.c \
		$(PIPE_DIR)/pipe_utils.c \
		$(REDIRECT_DIR)/redirect.c \
		$(REDIRECT_DIR)/redir_input.c \
		$(REDIRECT_DIR)/redir_output.c \
		$(REDIRECT_DIR)/redir_heredoc.c

OBJ = $(SRC:.c=.o)

# readline
READLINE_INC = -I/opt/homebrew/opt/readline/include
READLINE_LIB = -L/opt/homebrew/opt/readline/lib -lreadline -lhistory

# include directory
INC = -I./incl -I$(SRC_DIR)/libft $(READLINE_INC)

# libft directory
LIBFT_DIR = $(SRC_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

# rules
all: $(NAME)

# build libft first
$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE_LIB) -L$(LIBFT_DIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean

valgrind: $(NAME)
	@valgrind $(VAL_FLAGS) ./$(NAME)

re: fclean all

.PHONY: all clean fclean re