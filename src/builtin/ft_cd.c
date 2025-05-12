/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinzhang <xinzhang@student.42Paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:20:21 by xinzhang          #+#    #+#             */
/*   Updated: 2025/05/12 16:20:26 by xinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/builtin.h"

static char	*resolve_directory(char **args, t_env *env)
{
	char	*dir;

	(void)env;
	if (!args[1])
	{
		dir = getenv("HOME");
		if (!dir)
		{
			printf("cd: HOME not set\n");
			return (NULL);
		}
	}
	else if (args[1] && args[2])
	{
		set_exit_status(env, 1);
		ft_putstr_fd(" too many arguments\n", 2);
		return (NULL);
	}
	else
		dir = args[1];
	return (dir);
}

static void	execute_cd(char *dir, t_env *env)
{
	char	cwd[1024];

	if (!dir)
		return ;
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		perror("getcwd");
	if (chdir(dir) != 0)
	{
		set_exit_status(env, 1);
		perror("cd");
	}
	else
	{
		update_env_var("OLDPWD", cwd, env);
		if (getcwd(cwd, sizeof(cwd)) != NULL)
			update_env_var("PWD", cwd, env);
	}
}

void	ft_cd(char **args, t_env *env)
{
	char	*dir;

	if (!env)
		return ;
	dir = resolve_directory(args, env);
	execute_cd(dir, env);
}
