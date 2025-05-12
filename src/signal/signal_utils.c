/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:13:09 by hailong           #+#    #+#             */
/*   Updated: 2025/05/11 04:13:09 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/sig.h"

t_env	*g_env;

void	set_signal_env(t_env *env)
{
	g_env = env;
}

/* Ctrl C handler
    - print a new line
    - tell readline to move to a new line
    - clear the current input line
    - re display the prompt
    - reset the exit status: 130 for SIGINT
*/
void	sigint_handler(int sig)
{
	(void)sig;
	if (g_env && g_env->at_prompt)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		set_exit_status(g_env, 130);
	}
}

/* Ctrl \ handler */
void	sigquit_handler(int sig)
{
	(void)sig;
	if (g_env && g_env->at_prompt)
	{
		rl_on_new_line();
		rl_redisplay();
		set_exit_status(g_env, 0);
		return ;
	}
	else if (g_env)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		set_exit_status(g_env, 131);
	}
}

/* Ctrl C handler for heredoc */
void	heredoc_sigint_handler(int sig)
{
	if (sig == SIGINT && g_env)
	{
		g_env->heredoc_interrupted = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		write(STDERR_FILENO, "\n", 1);
		set_exit_status(g_env, 130);
	}
}

void	setup_heredoc_signals(t_env *env)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	set_signal_env(env);
	disable_echo();
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = heredoc_sigint_handler;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = SIG_IGN;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}
