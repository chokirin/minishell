/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinzhang <xinzhang@student.42Paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:00:26 by xinzhang          #+#    #+#             */
/*   Updated: 2025/05/12 17:00:32 by xinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipe.h"
#include "../../incl/minishell.h"

/* helper function for execute_pipe_child */
static void	cleanup_and_exit(t_cmd *cmd_head,
	t_cmd *current, t_env *env, t_fd *fd)
{
	(void)current;
	if (fd->stdin != -1)
		close(fd->stdin);
	if (fd->stdout != -1)
		close(fd->stdout);
	free_cmds(cmd_head);
	free_env(env);
	exit(env->exit_status);
}

/* helper function for execute_pipe_child
	to cleanup fd from previous process
*/
static void	close_unused_fd(t_pipe *ctx)
{
	if (ctx->stdin_backup != -1)
		close(ctx->stdin_backup);
	if (ctx->stdout_backup != -1)
		close(ctx->stdout_backup);
	if (ctx->stderr_backup != -1)
		close(ctx->stderr_backup);
}

/* execute the child process in pipe */
static void	execute_pipe_child(t_cmd *cmd_head, t_cmd *current,
		t_pipe *ctx, t_env *env)
{
	t_fd	fd_child;
	int		redirect_error;

	fd_child.stdin = -1;
	fd_child.stdout = -1;
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);
	close_unused_fd(ctx);
	redirect_error = exec_redirect(current, env);
	handle_redirect_error(current, ctx, redirect_error, env);
	if (setup_pipe_input(current, ctx, &fd_child.stdin, env))
		cleanup_and_exit(cmd_head, current, env, &fd_child);
	if (setup_pipe_output(current, ctx, &fd_child.stdout, env))
		cleanup_and_exit(cmd_head, current, env, &fd_child);
	if (current->args && current->args[0]
		&& ft_strcmp(current->args[0], "exit") == 0)
	{
		ft_exit(current->args, env);
		cleanup_and_exit(cmd_head, current, env, &fd_child);
	}
	dispatch_cmd(cmd_head, current, env, &fd_child);
	cleanup_and_exit(cmd_head, current, env, &fd_child);
}

/* handle parent process after fork
    - close prev pipe read end
    - if not the last cmd, prepare next pipe read end
    - track last cmd's pid
*/
void	execute_parent_process(t_pipe *ctx, t_cmd *cmd, pid_t pid)
{
	ctx->pids[ctx->pid_count++] = pid;
	if (ctx->prev_pipe_read != -1)
	{
		close(ctx->prev_pipe_read);
		ctx->prev_pipe_read = -1;
	}
	if (cmd->next)
	{
		close(ctx->pipefd[1]);
		ctx->prev_pipe_read = ctx->pipefd[0];
	}
	if (!cmd->next)
		ctx->last_pid = pid;
}

/* main pipeline execution
    - init pipeline ctx and mark cmds
    - check redirect before creating pipes
    - create pipe if not the last cmd
    - fork process
    - restore std fd
    - wait for all child process
*/
void	fork_and_execute_pipe(t_cmd *cmd_head, t_cmd *current,
		t_pipe *ctx, t_env *env)
{
	pid_t	pid;
	int		redirect_error;

	redirect_error = exec_redirect(current, env);
	handle_redirect_error(current, ctx, redirect_error, env);
	if (current->next)
	{
		if (create_cmd_pipe(ctx, env))
			return ;
	}
	pid = fork();
	if (pid == -1)
	{
		handle_fork_error(ctx, env);
		return ;
	}
	if (pid == CHILD_PROCESS)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execute_pipe_child(cmd_head, current, ctx, env);
	}
	else
		execute_parent_process(ctx, current, pid);
}
