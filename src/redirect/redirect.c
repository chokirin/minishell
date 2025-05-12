/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rediect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinzhang <xinzhang@student.42Paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:09:40 by xinzhang          #+#    #+#             */
/*   Updated: 2025/05/12 17:09:44 by xinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minishell.h"

/* process all redirect in order (from left to right) 
    - check if files exist/ can be created, and handle permissions
    - return 0 on success, 1 on error
*/

static int	validate_input_file(t_redir *redir)
{
	int	fd;

	fd = open(redir->file, O_RDONLY);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	close(fd);
	return (0);
}

static int	validate_output_file(t_redir *redir)
{
	int	fd;

	if (redir->type == TOKEN_REDIRECT_APPEND)
		fd = open(redir->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(redir->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("minishell");
		return (1);
	}
	close(fd);
	return (0);
}

static int	handle_redir_result(t_cmd *cmd, t_env *env, int result)
{
	if (result == 1)
	{
		if (!cmd->in_pipe)
			set_exit_status(env, 1);
		return (1);
	}
	return (0);
}

int	exec_redirect(t_cmd *cmd, t_env *env)
{
	t_redir	*redir;
	int		result;

	redir = cmd->redirects;
	while (redir)
	{
		if (redir->type == TOKEN_REDIRECT_IN)
		{
			result = validate_input_file(redir);
			if (handle_redir_result(cmd, env, result) == 1)
				return (1);
		}
		else if (redir->type == TOKEN_REDIRECT_APPEND
			|| redir->type == TOKEN_REDIRECT_OUT)
		{
			result = validate_output_file(redir);
			if (handle_redir_result(cmd, env, result) == 1)
				return (1);
		}
		redir = redir->next;
	}
	return (0);
}

/* restore std input after execution */
void	restore_io(int stdin_backup, int stdout_backup)
{
	if (stdin_backup != -1)
	{
		dup2(stdin_backup, STDIN_FILENO);
		close(stdin_backup);
		stdin_backup = -1;
	}
	if (stdout_backup != -1)
	{
		dup2(stdout_backup, STDOUT_FILENO);
		close(stdout_backup);
		stdout_backup = -1;
	}
}
