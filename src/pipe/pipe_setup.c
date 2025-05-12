/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 07:14:40 by hailong           #+#    #+#             */
/*   Updated: 2025/05/12 07:14:41 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipe.h"
#include "../../incl/minishell.h"

/* init the pipe struct */
void	init_pipe(t_pipe *context)
{
	context->pid_count = 0;
	context->prev_pipe_read = -1;
	context->last_pid = -1;
	context->stdin_backup = dup(STDIN_FILENO);
	context->stdout_backup = dup(STDOUT_FILENO);
	context->stderr_backup = dup(STDERR_FILENO);
	context->pipefd[0] = -1;
	context->pipefd[1] = -1;
}

void	mark_pipeline_cmd(t_cmd *cmd)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		current->in_pipe = 1;
		current = current->next;
	}
}

/* create pipe and handle error */
int	create_cmd_pipe(t_pipe *ctx, t_env *env)
{
	if (pipe(ctx->pipefd) == -1)
	{
		perror("pipe");
		set_exit_status(env, 1);
		close_all_pipe_fds(ctx);
		restore_std_fd(ctx);
		return (1);
	}
	return (0);
}

void	setup_pipeline(t_pipe *ctx, t_cmd *cmd,
	t_env *env, struct sigaction old[2])
{
	init_pipe(ctx);
	mark_pipeline_cmd(cmd);
	save_signal_handlers(&old[0], &old[1]);
	set_parent_signals_for_pipeline();
	env->at_prompt = 0;
}
