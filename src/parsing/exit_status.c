/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 08:07:23 by hailong           #+#    #+#             */
/*   Updated: 2025/05/12 08:07:23 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

void	set_exit_status(t_env *env, int exit_status)
{
	if (!env->exit)
	{
		env->exit_status = exit_status;
		env->exit = 1;
	}
}

int	exec_builtin_with_io(t_cmd *cmd, t_env *env,
	int stdin_backup, int stdout_backup)
{
	t_builtin	*builtins;
	int			i;

	builtins = init_builtin();
	i = 0;
	while (builtins[i].builtin_name)
	{
		if (ft_strcmp(cmd->args[0], builtins[i].builtin_name) == 0)
		{
			builtins[i].func(cmd->args, env);
			restore_io(stdin_backup, stdout_backup);
			return (1);
		}
		i++;
	}
	return (0);
}
