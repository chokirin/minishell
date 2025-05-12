/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 08:03:25 by hailong           #+#    #+#             */
/*   Updated: 2025/05/09 08:03:25 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	update_shlvl(t_env *env, int i)
{
	int		shlvl;
	char	*new_shlvl;
	char	*new_value;

	shlvl = 1;
	if (getenv("SHLVL"))
	{
		shlvl = ft_atoi(getenv("SHLVL")) + 1;
		if (shlvl < 0)
			shlvl = 0;
		if (shlvl > 999)
			shlvl = 1;
		new_value = ft_itoa(shlvl);
		new_shlvl = ft_strjoin("SHLVL=", new_value);
		free(new_value);
		while (env->env_var && env->env_var[i])
		{
			if (ft_strncmp(env->env_var[i], "SHLVL=", 6) == 0)
				break ;
			i++;
		}
		free(env->env_var[i]);
		env->env_var[i] = new_shlvl;
	}
}

void	minishell(t_env *env)
{
	char	*line;
	t_token	*tokens;

	setup_signal(env);
	while (1)
	{
		env->exit = 0;
		env->at_prompt = 1;
		line = get_prompt_line();
		env->at_prompt = 0;
		if (line == NULL)
			break ;
		tokens = process_prompt_line(line, env);
		if (tokens)
			process_tokens_and_execute(tokens, env);
		free(line);
		if (env->exit_requested)
			break ;
		if (!env->exit)
			env->exit_status = 0;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env	env;

	(void)ac;
	(void)av;
	env.exit_requested = 0;
	env.exit = 0;
	init_env(&env, envp);
	update_shlvl(&env, 0);
	minishell(&env);
	free_env(&env);
	enable_echo();
	rl_clear_history();
	return (env.exit_status);
}
