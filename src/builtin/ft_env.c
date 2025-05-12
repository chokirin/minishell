/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 07:21:59 by hailong           #+#    #+#             */
/*   Updated: 2025/05/12 07:21:59 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/builtin.h"

void	print_env(t_env *env)
{
	int	i;

	i = 0;
	while (env && env->env_var && env->env_var[i])
	{
		printf("%s\n", env->env_var[i]);
		i++;
	}
}

void	ft_env(char **args, t_env *env)
{
	(void)args;
	if (!env || !env->env_var)
	{
		printf("env not initialized\n");
		return ;
	}
	print_env(env);
}
