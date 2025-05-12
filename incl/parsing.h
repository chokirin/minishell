/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:58:12 by hailong           #+#    #+#             */
/*   Updated: 2025/05/12 22:58:12 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../incl/minishell.h"
# include "../incl/pipe.h"

# define TOKEN_WORD 0
# define TOKEN_PIPE 1
# define TOKEN_OR 11
# define TOKEN_REDIRECT_IN 2
# define TOKEN_REDIRECT_OUT 3
# define TOKEN_REDIRECT_APPEND 4
# define TOKEN_HEREDOC 5
# define TOKEN_SINGLE_QUOTE 6
# define TOKEN_DOUBLE_QUOTE 10
# define DIRECTORY '/'
# define TOKEN_AND 7
# define TOKEN_AND_SINGLE 8
# define TOKEN_COMMAND 9

typedef struct s_env	t_env;
typedef struct s_pipe	t_pipe;

typedef struct s_token
{
	char			*value;
	int				type;
	int				consecutive_quote;
	struct s_token	*next;
}	t_token;

typedef struct s_redir
{
	char			*file;
	int				type;
	struct s_redir	*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	int				append;
	int				heredoc;
	char			*delimiter;
	int				fd_in;
	t_redir			*redirects;
	int				in_pipe;
	int				expand_heredoc;
	struct s_cmd	*next;
}	t_cmd;

t_token	*tokenize(char *input);
void	tokenize_operators(t_token **tokens, int *i, char *input);
void	tokenize_pipe(t_token **tokens, int *i, char *input);
int		tokenize_quotes(t_token **tokens, int *i, char *input);
void	tokenize_word(t_token **tokens, int *i, char *input);

void	extract_redirect_filename(char *input, int *i, t_token **tokens);
void	free_cmds(t_cmd *cmds);
t_cmd	*create_new_cmd(void);
t_cmd	*parse_tokens(t_token *tokens);
void	check_format_command(t_token *tokens);

/* redirect */
int		setup_input_redir(t_cmd *cmd, int *stdin_backup, t_env *env);
int		setup_output_redir(t_cmd *cmd, int *stdout_backup, t_env *env);
int		setup_pipe_input(t_cmd *cmd, t_pipe *ctx, int *stdin_backup,
			t_env *env);
int		setup_redirect(t_cmd *cmd, int *stdin_backup, int *stdout_backup,
			t_env *env);
t_redir	*create_redir_node(char *file, int type);
char	*extract_quoted_content(char *input, int *i, char quote);
void	free_redir(t_redir *redir);

/* tokenize_utils1 */
int		ft_isspace(char a);
int		is_special_char(char c);
int		is_quote(char c);
int		exec_redirect(t_cmd *cmd, t_env *env);

/* token_utils_1 */
void	add_token(t_token **head, t_token *new_token);
char	*extract_quoted(char *input, int *i, char quote);
t_token	*create_token(char *value, int type);
int		get_token_type(char *s);
void	free_tokens(t_token *tokens);

/* token_utils_2 */
int		validate_tokens(t_token *tokens);

int		exec_builtin_with_io(t_cmd *cmd, t_env *env,
			int stdin_backup, int stdout_backup);

/* parse_tokens_utils*/
t_cmd	*create_new_command(t_cmd **cmd_head);
void	add_cmd_arg(t_cmd *current_cmd, t_token *tokens);
void	add_redirection(t_cmd *current_cmd, t_token **tokens, int type);
void	update_redir_path(t_cmd *cmd, char *file, int type);
void	setup_heredoc(t_cmd *cmd, t_token **tokens);
void	set_exit_status(t_env *env, int exit_status);
void	free_tokens(t_token *tokens);

#endif
