/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 07:14:48 by hailong           #+#    #+#             */
/*   Updated: 2025/05/12 07:14:48 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/pipe.h"
#include "../../incl/minishell.h"

/* Save the original signal handlers before changing them */
void	save_signal_handlers(struct sigaction *old_int,
			struct sigaction *old_quit)
{
	sigaction(SIGINT, NULL, old_int);
	sigaction(SIGQUIT, NULL, old_quit);
}

/* Set parent process signal handling during pipeline execution */
void	set_parent_signals_for_pipeline(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_handler = SIG_IGN;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

/* Restore original signal handlers */
void	restore_signal_handlers(struct sigaction *old_int,
			struct sigaction *old_quit)
{
	sigaction(SIGINT, old_int, NULL);
	sigaction(SIGQUIT, old_quit, NULL);
}
