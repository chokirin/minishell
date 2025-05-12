/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:06:53 by hailong           #+#    #+#             */
/*   Updated: 2025/05/12 08:06:53 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parsing.h"
#include "../../incl/minishell.h"

/* helper function for parse_tokens */
static void	handle_word_token(t_cmd **current_cmd, t_token **tokens)
{
	if ((*tokens)->type == TOKEN_WORD
		|| (*tokens)->type == TOKEN_SINGLE_QUOTE
		|| (*tokens)->type == TOKEN_DOUBLE_QUOTE
		|| (*tokens)->type == TOKEN_COMMAND)
		add_cmd_arg(*current_cmd, *tokens);
}

/* helper function for parse_tokens */
static void	handle_redirect_token(t_cmd **current_cmd, t_token **tokens)
{
	if ((*tokens)->type == TOKEN_REDIRECT_OUT)
		add_redirection(*current_cmd, tokens, TOKEN_REDIRECT_OUT);
	if ((*tokens)->type == TOKEN_REDIRECT_APPEND)
		add_redirection(*current_cmd, tokens, TOKEN_REDIRECT_APPEND);
	if ((*tokens)->type == TOKEN_REDIRECT_IN)
		add_redirection(*current_cmd, tokens, TOKEN_REDIRECT_IN);
}

/* helper function for parse_tokens */
static void	handle_pipe_token(t_cmd **current_cmd, t_token **tokens)
{
	if ((*tokens)->type == TOKEN_PIPE && (*tokens)->next)
	{
		(*current_cmd)->next = create_new_cmd();
		*current_cmd = (*current_cmd)->next;
	}
}

t_cmd	*parse_tokens(t_token *tokens)
{
	t_cmd	*cmd_head;
	t_cmd	*current_cmd;

	cmd_head = NULL;
	current_cmd = NULL;
	if (!validate_tokens(tokens))
		return (NULL);
	while (tokens)
	{
		if (!current_cmd)
			current_cmd = create_new_command(&cmd_head);
		handle_word_token(&current_cmd, &tokens);
		handle_redirect_token(&current_cmd, &tokens);
		handle_pipe_token(&current_cmd, &tokens);
		if (tokens->type == TOKEN_HEREDOC)
			setup_heredoc(current_cmd, &tokens);
		tokens = tokens->next;
	}
	return (cmd_head);
}
