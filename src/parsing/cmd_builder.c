/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_builder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:49:32 by hailong           #+#    #+#             */
/*   Updated: 2025/05/11 04:49:32 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parsing.h"
#include "../../incl/minishell.h"

t_cmd	*create_new_command(t_cmd **cmd_head)
{
	t_cmd	*new_cmd;

	new_cmd = create_new_cmd();
	if (!*cmd_head)
		*cmd_head = new_cmd;
	return (new_cmd);
}

void	add_cmd_arg(t_cmd *current_cmd, t_token *tokens)
{
	int	i;

	if (!current_cmd || !tokens || !tokens->value)
		return ;
	i = 0;
	if ((i == 0 || !tokens->next || (tokens->next->type != TOKEN_REDIRECT_IN
				&& tokens->next->type != TOKEN_REDIRECT_OUT
				&& tokens->next->type != TOKEN_REDIRECT_APPEND))
		&& tokens->value[0] != '\0')
	{
		while (current_cmd->args && current_cmd->args[i])
			i++;
		current_cmd->args[i] = ft_strdup(tokens->value);
		if (!current_cmd->args[i])
			return ;
		current_cmd->args[i + 1] = NULL;
	}
}

static void	add_redir(t_cmd *cmd, char *file, int type)
{
	t_redir	*new_redir;
	t_redir	*temp;

	if (!cmd || !file)
		return ;
	update_redir_path(cmd, file, type);
	new_redir = create_redir_node(file, type);
	if (!new_redir)
		return ;
	if (!cmd->redirects)
		cmd->redirects = new_redir;
	else
	{
		temp = cmd->redirects;
		while (temp->next)
			temp = temp->next;
		temp->next = new_redir;
	}
}

void	add_redirection(t_cmd *current_cmd, t_token **tokens, int type)
{
	*tokens = (*tokens)->next;
	if (*tokens && ((*tokens)->type == TOKEN_WORD
			|| (*tokens)->type == TOKEN_DOUBLE_QUOTE
			|| (*tokens)->type == TOKEN_SINGLE_QUOTE))
		add_redir(current_cmd, (*tokens)->value, type);
}

void	setup_heredoc(t_cmd *current_cmd, t_token **tokens)
{
	*tokens = (*tokens)->next;
	if (*tokens && ((*tokens)->type == TOKEN_WORD
			|| (*tokens)->type == TOKEN_DOUBLE_QUOTE
			|| (*tokens)->type == TOKEN_SINGLE_QUOTE))
	{
		current_cmd->heredoc = 1;
		current_cmd->delimiter = ft_strdup((*tokens)->value);
		current_cmd->expand_heredoc = 1;
		if ((*tokens)->type == TOKEN_DOUBLE_QUOTE
			|| (*tokens)->type == TOKEN_SINGLE_QUOTE)
			current_cmd->expand_heredoc = 0;
	}
}
