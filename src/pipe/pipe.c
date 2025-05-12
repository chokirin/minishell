/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xinzhang <xinzhang@student.42Paris.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 17:05:43 by xinzhang          #+#    #+#             */
/*   Updated: 2025/05/12 17:05:46 by xinzhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipe.h"

static void	cleanup_pipeline(t_pipe *ctx, t_cmd *cmd,
	t_env *env,	struct sigaction original[2])
{
	close_all_pipe_fds(ctx);
	restore_std_fd(ctx);
	if (!env->exit_requested)
	{
		wait_for_child(ctx, env);
		free_cmds(cmd);
	}
	else
		free_cmds(cmd);
	reset_input_state();
	restore_signal_handlers(&original[0], &original[1]);
	env->at_prompt = 1;
}

static void	handle_exit_cmd(t_cmd *current, t_env *env)
{
	if (!current->next)
	{
		ft_exit(current->args, env);
		return ;
	}
	env->exit_requested = 1;
}

static void	cleanup_after_exit(t_pipe *ctx, t_cmd *cmd)
{
	close_all_pipe_fds(ctx);
	restore_std_fd(ctx);
	free_cmds(cmd);
}

static void	process_pipeline(t_pipe *ctx, t_cmd *cmd, t_env *env)
{
	t_cmd	*current;

	current = cmd;
	while (current)
	{
		if (current->args && current->args[0]
			&& ft_strcmp(current->args[0], "exit") == 0)
		{
			handle_exit_cmd(current, env);
			break ;
		}
		fork_and_execute_pipe(cmd, current, ctx, env);
		if (env->exit_requested)
		{
			cleanup_after_exit(ctx, cmd);
			break ;
		}
		current = current->next;
	}
}

void	run_pipeline(t_cmd *cmd, t_env *env)
{
	t_pipe				ctx;
	struct sigaction	original[2];

	setup_pipeline(&ctx, cmd, env, original);
	process_pipeline(&ctx, cmd, env);
	cleanup_pipeline(&ctx, cmd, env, original);
}
