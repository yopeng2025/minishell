/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: peiyli <peiyli@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 14:32:25 by peiyli            #+#    #+#             */
/*   Updated: 2025/11/27 14:32:26 by peiyli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int code)
{
	(void)code;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_signal_pid == 0)
		rl_redisplay();
}

static void	handle_sigsegv(int code)
{
	(void)code;
	write(2, "Segmentation fault\n", 20);
	exit(11);
}

static void	handle_sigabrt(int code)
{
	(void)code;
	write(2, "abort\n", 7);
}

void	signals(void)
{
	signal(SIGINT, &handle_sigint);
	signal(SIGSEGV, &handle_sigsegv);
	signal(SIGABRT, &handle_sigabrt);
	signal(SIGQUIT, SIG_IGN);
}
