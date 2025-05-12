/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:12:02 by hailong           #+#    #+#             */
/*   Updated: 2025/05/11 04:12:02 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/parsing.h"
#include "../../incl/minishell.h"

/* helper function to extract a filename that follows a redirect ops */
void	extract_redirect_filename(char *input, int *i, t_token **tokens)
{
	int		start;
	char	*word;
	t_token	*new_token;

	start = *i;
	new_token = NULL;
	while (input[*i] && !ft_isspace(input[*i])
		&& !is_quote(input[*i]) && input[*i] != '|'
		&& input[*i] != '>' && input[*i] != '<')
		(*i)++;
	if (*i > start)
	{
		word = strndup(&input[start], *i - start);
		new_token = create_token(word, TOKEN_WORD);
		add_token(tokens, new_token);
		free(word);
	}
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	int		i;

	tokens = NULL;
	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (is_quote(input[i]) && input[i] == input[i + 1]
			&& !ft_isspace(input[i + 2]))
			i += 2;
		if (is_special_char(input[i]))
			tokenize_operators(&tokens, &i, input);
		else if (input[i] == '|')
			tokenize_pipe(&tokens, &i, input);
		else if (input[i] == '\'' || input[i] == '"')
		{
			if (tokenize_quotes(&tokens, &i, input) == 1)
				return (NULL);
		}
		else
			tokenize_word(&tokens, &i, input);
	}
	return (tokens);
}
