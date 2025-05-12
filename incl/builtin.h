/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:42:06 by hailong           #+#    #+#             */
/*   Updated: 2025/05/12 22:42:06 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "../incl/minishell.h"

typedef struct s_env
{
	char		**env_var;
	int			*exported;
	long		exit_status;
	int			at_prompt;
	int			heredoc_interrupted;
	int			exit_requested;
	int			exit;
}	t_env;

typedef struct s_builtin
{
	char		*builtin_name;
	void		(*func)(char **args, t_env *env);
}		t_builtin;

/* functions */
t_builtin	*init_builtin(void);

int			count_envp(char **envp);
int			is_digit(char *str);
int			count_env(t_env *env);

void		init_env(t_env *env, char **envp);
void		free_env(t_env *env);
void		update_env_var(char *key, char *value, t_env *env);
void		ft_cd(char **args, t_env *env);
void		ft_echo(char **args, t_env *env);
void		ft_env(char **args, t_env *env);
void		ft_exit(char **args, t_env *env);
void		ft_export(char **args, t_env *env);
void		ft_unset(char **args, t_env *env);
void		ft_pwd(char **args, t_env *env);
void		ft_unset(char **av, t_env *env);
void		ft_unsetenv(char *name, t_env *env);
void		print_env(t_env *env);

#endif
