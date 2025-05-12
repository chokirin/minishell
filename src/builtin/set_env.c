/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinzhang <xinzhang@student.42Paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:55:25 by xinzhang          #+#    #+#             */
/*   Updated: 2025/05/12 16:55:29 by xinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/builtin.h"

static char	*create_env_var(char *key, char *value)
{
	int		key_len;
	int		value_len;
	char	*new_entry;

	key_len = ft_strlen(key);
	value_len = ft_strlen(value);
	new_entry = (char *)malloc(key_len + value_len + 2);
	if (!new_entry)
	{
		perror("malloc");
		return (NULL);
	}
	ft_memcpy(new_entry, key, key_len);
	new_entry[key_len] = '=';
	ft_memcpy(new_entry + key_len + 1, value, value_len);
	new_entry[key_len + value_len + 1] = '\0';
	return (new_entry);
}

/* helper function to reproduce realloc
	- malloc for the new_env array
	- copy old_env to new_env
	- null terminated
	- free up old_env array
	- return new_env
*/
static char	**resize_env_array(char **old_env, int new_size)
{
	char	**new_env;
	int		i;

	new_env = (char **)malloc(new_size * sizeof(char *));
	if (!new_env)
	{
		perror("malloc");
		return (NULL);
	}
	i = 0;
	while (old_env[i] && i < new_size - 1)
	{
		new_env[i] = old_env[i];
		i++;
	}
	new_env[i] = NULL;
	if (old_env)
		free(old_env);
	return (new_env);
}

/* add new_entry to the end of the existing env array
	- count the # of items in the existing env array
	- relloac for count + 2: new entry + null terminator
*/
static void	append_env_var(char *key, char *value, t_env *env)
{
	int		count;
	char	**new_env;
	char	*new_entry;

	if (!key || !env)
		return ;
	new_entry = create_env_var(key, value);
	if (!new_entry)
		return ;
	count = count_env(env);
	new_env = resize_env_array(env->env_var, (count + 2) * sizeof(char *));
	if (!new_env)
	{
		free(new_entry);
		return ;
	}
	env->env_var = new_env;
	env->env_var[count] = new_entry;
	env->env_var[count + 1] = NULL;
}

/* update the env var after calling ft_cd
    - malloc for thes new entry
    - loop through the env array
        - if find key matches, update the old entry with new entry
        - if not, add the new entry at the end, null terminated
*/
void	update_env_var(char *key, char *value, t_env *env)
{
	int		i;
	int		key_len;
	char	*new_entry;

	if (!key || !env || !env->env_var)
		return ;
	key_len = ft_strlen(key);
	new_entry = create_env_var(key, value);
	if (!new_entry)
		return ;
	i = 0;
	while (env->env_var[i])
	{
		if (ft_strncmp(env->env_var[i], key, key_len) == 0
			&& env->env_var[i][key_len] == '=')
		{
			free(env->env_var[i]);
			env->env_var[i] = new_entry;
			return ;
		}
		i++;
	}
	append_env_var(key, value, env);
	free(new_entry);
}

/* count the nbr of env_var */
int	count_env(t_env *env)
{
	int	i;

	i = 0;
	if (!env || !env->env_var)
		return (0);
	while (env->env_var[i])
		i++;
	return (i);
}
