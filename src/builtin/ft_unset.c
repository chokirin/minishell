/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 07:58:44 by hailong           #+#    #+#             */
/*   Updated: 2025/05/12 07:58:44 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/builtin.h"

/* remove the var from the array
	- loop through the env array
	- strncmp the input name and the env_var array
	- if match
		- free the env_var[i] memory
		- shift the array forward
	- if not
		- do nothing
*/
void	ft_unsetenv(char *name, t_env *env)
{
	int	i;
	int	j;

	if (!env || !env->env_var)
		return ;
	i = 0;
	while (env->env_var[i])
	{
		if (ft_strncmp(env->env_var[i], name, ft_strlen(name)) == 0
			&& env->env_var[i][ft_strlen(name)] == '=')
		{
			free(env->env_var[i]);
			j = i;
			while (env->env_var[j + 1])
			{
				env->env_var[j] = env->env_var[j + 1];
				j++;
			}
			env->env_var[j] = NULL;
			return ;
		}
		i++;
	}
}

/* check if the variable name is valid
	- only accept aphabetic & numeric arg or "_"
*/
int	is_valid_name(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	i = 1;
	while (name[i])
	{
		if (ft_isalnum(name[i]) != 1 && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

/* unset with no option
	- check argument
		- need to have >= 1 arg
		- only accept alphabetic & numeric input
	- if the env struct has not been initialized
		- init & store the envp from the main
	- loop through the arg array
		- if arg[i] invalid
			- print out error msg
			- continue to the next arg
		- if arg valid
			- call ft_unsetenv to remove the var
*/
void	ft_unset(char **av, t_env *env)
{
	int	i;

	if (!av || !env)
		return ;
	if (!av[1])
		return ;
	i = 1;
	while (av[i])
	{
		if (!is_valid_name(av[i]))
		{
			printf("unset: %s: not a valid identifier\n", av[i]);
			i++;
			continue ;
		}
		ft_unsetenv(av[i], env);
		i++;
	}
}
