/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 07:14:59 by hailong           #+#    #+#             */
/*   Updated: 2025/05/12 07:14:59 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipe.h"

/* wrapper function of dup and handle error */
int	ft_dup(int fd, int *backup_ptr, char *name)
{
	*backup_ptr = dup(fd);
	if (*backup_ptr == -1)
	{
		perror(name);
		return (1);
	}
	return (0);
}

/* wrapper function of dup2 and handle error */
int	ft_dup2(int oldfd, int newfd, int backup, char *name)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror(name);
		close(backup);
		return (1);
	}
	return (0);
}

/* handle redirect error
    - if there is a next cmd
        - close the read & write end of the pipe
    - if there is a prev_pipe_read, close it too
	- free cmds and env
    - exit 1
*/
void	handle_redirect_error(t_cmd *cmd, t_pipe *ctx,
		int redirect_error, t_env *env)
{
	if (redirect_error)
	{
		if (cmd->next)
		{
			close(ctx->pipefd[0]);
			close(ctx->pipefd[1]);
		}
		if (ctx->prev_pipe_read != -1)
		{
			close(ctx->prev_pipe_read);
			ctx->prev_pipe_read = -1;
		}
		free_cmds(cmd);
		free_env(env);
		exit(1);
	}
}

/* helper function for fork_and_execute_pipe */
void	handle_fork_error(t_pipe *ctx, t_env *env)
{
	perror("fork");
	set_exit_status(env, 1);
	close_all_pipe_fds(ctx);
	restore_std_fd(ctx);
}
