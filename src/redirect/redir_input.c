/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinzhang <xinzhang@student.42Paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:08:55 by xinzhang          #+#    #+#             */
/*   Updated: 2025/05/12 17:08:59 by xinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

static int	redir_from_file(t_cmd *cmd, int *stdin_backup, t_env *env)
{
	int	fd;

	fd = open(cmd->infile, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		close(*stdin_backup);
		set_exit_status(env, 1);
		return (-1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(fd);
		close(*stdin_backup);
		set_exit_status(env, 1);
		return (-1);
	}
	close(fd);
	return (0);
}

static int	redir_from_heredoc(t_cmd *cmd, int *stdin_backup, t_env *env)
{
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
	{
		perror("dup2");
		close(*stdin_backup);
		set_exit_status(env, 1);
		return (-1);
	}
	close(cmd->fd_in);
	return (0);
}

int	setup_input_redir(t_cmd *cmd, int *stdin_backup, t_env *env)
{
	if (!cmd->heredoc && !cmd->infile)
	{
		*stdin_backup = -1;
		return (0);
	}
	*stdin_backup = dup(STDIN_FILENO);
	if (*stdin_backup == -1)
	{
		perror("dup");
		set_exit_status(env, 1);
		return (-1);
	}
	if (cmd->heredoc && cmd->fd_in > 0)
		return (redir_from_heredoc(cmd, stdin_backup, env));
	if (cmd->infile)
		return (redir_from_file(cmd, stdin_backup, env));
	return (0);
}
