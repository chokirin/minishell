/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:19:26 by hailong           #+#    #+#             */
/*   Updated: 2025/05/12 16:19:49 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static void	handle_free_single_token_error(t_token **head,
	t_token *token_to_free)
{
	if (!head || !*head || !token_to_free)
		return ;
	if (*head == token_to_free)
	{
		*head = token_to_free->next;
		free(token_to_free->value);
		free(token_to_free);
		return ;
	}
}

static void	free_single_token(t_token **head,
	t_token *token_to_free)
{
	t_token	*prev;
	t_token	*current;

	handle_free_single_token_error(head, token_to_free);
	prev = *head;
	current = prev->next;
	while (current && current != token_to_free)
	{
		prev = current;
		current = current->next;
	}
	if (current)
	{
		prev->next = current->next;
		free(current->value);
		free(current);
	}
}

static int	should_remove_dollar_token(t_token *current)
{
	if (current->next && (current->next->type == TOKEN_DOUBLE_QUOTE
			|| current->next->type == TOKEN_SINGLE_QUOTE)
		&& ft_strcmp(current->value, "$") == 0)
		return (1);
	if (ft_strcmp(current->value, "$") == 0 && current->consecutive_quote == 1
		&& current->next != NULL)
		return (1);
	if (ft_strcmp(current->value, "$") == 0 && current->consecutive_quote == 1
		&& current->next == NULL && current->type == TOKEN_WORD)
		return (1);
	return (0);
}

static void	expand_token_in_quote(t_token *current, t_env *env)
{
	char	*expanded;

	if (current->type == TOKEN_DOUBLE_QUOTE || current->type == TOKEN_WORD)
	{
		expanded = expand_var_instr(current->value, env);
		if (expanded)
		{
			free(current->value);
			current->value = expanded;
		}
	}
}

void	expand_tokens(t_token *tokens, t_env *env)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		if (should_remove_dollar_token(current))
		{
			free_single_token(&tokens, current);
			current = next;
			continue ;
		}
		expand_token_in_quote(current, env);
		current = current->next;
	}
	current = tokens;
	while (current)
		current = next;
}
