/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:45:32 by hailong           #+#    #+#             */
/*   Updated: 2025/05/12 22:45:32 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../src/libft/libft.h"
# include "../incl/builtin.h"

typedef struct s_env	t_env;
typedef struct s_cmd	t_cmd;

/* execute_path */
char	*get_path(t_env *env);
char	*find_path(char *cmd, t_env *env);
char	*get_cmd_path(t_cmd *cmd, t_env *env);

/* execute_utils */
pid_t	ft_fork(void);
pid_t	ft_wait(int *status);
void	ft_execve(char *path, char **av, t_env *env);

#endif
