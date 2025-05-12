/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinzhang <xinzhang@student.42Paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:09:15 by xinzhang          #+#    #+#             */
/*   Updated: 2025/05/12 17:09:18 by xinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/* handle output redirect */
static int	create_output_file(t_cmd *cmd, t_env *env)
{
	int	fd;

	if (cmd->append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell");
		set_exit_status(env, 1);
	}
	return (fd);
}

static void	abort_redir_on_error(int fd, int *stdout_backup, t_env *env)
{
	perror("minishell");
	close(fd);
	close(*stdout_backup);
	set_exit_status(env, 1);
}

int	setup_output_redir(t_cmd *cmd, int *stdout_backup, t_env *env)
{
	int	fd;

	if (!cmd->outfile)
	{
		*stdout_backup = -1;
		return (0);
	}
	*stdout_backup = dup(STDOUT_FILENO);
	if (*stdout_backup == -1)
	{
		perror("dup");
		set_exit_status(env, 1);
		return (-1);
	}
	fd = create_output_file(cmd, env);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		abort_redir_on_error(fd, stdout_backup, env);
		return (-1);
	}
	close(fd);
	return (0);
}
