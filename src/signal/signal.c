/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 04:12:58 by hailong           #+#    #+#             */
/*   Updated: 2025/05/11 04:12:58 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/sig.h"

void	disable_echo(void)
{
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		perror("tcsetattr");
}

void	enable_echo(void)
{
	struct termios	term;

	if (!isatty(STDIN_FILENO))
		return ;
	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	term.c_lflag |= ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		perror("tcsetattr");
}

void	reset_input_state(void)
{
	int				fd;
	struct termios	term;

	if (tcgetattr(STDIN_FILENO, &term) == -1)
	{
		perror("tcgetattr");
		return ;
	}
	term.c_lflag |= (ICANON | ECHO);
	term.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)
		perror("tcsetattr");
	if (isatty(STDIN_FILENO))
	{
		fd = open("/dev/tty", O_RDONLY);
		if (fd != STDIN_FILENO && fd > 0)
		{
			dup2(fd, STDIN_FILENO);
			close(fd);
		}
	}
}

void	setup_signal(t_env *env)
{
	struct sigaction	sa;

	set_signal_env(env);
	disable_echo();
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sigint_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigemptyset(&sa.sa_mask);
	sa.sa_handler = sigquit_handler;
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}
