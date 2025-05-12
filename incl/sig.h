/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hailong <hailong@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 22:55:09 by hailong           #+#    #+#             */
/*   Updated: 2025/05/12 22:55:09 by hailong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIG_H
# define SIG_H
# include "../incl/minishell.h"

void	set_signal_env(t_env *env);
void	disable_echo(void);
void	enable_echo(void);
void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	setup_signal(t_env *env);
void	reset_input_state(void);

void	heredoc_sigint_handler(int sig);
void	setup_heredoc_signals(t_env *env);

#endif
