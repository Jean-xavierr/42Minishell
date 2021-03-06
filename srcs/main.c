/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecaudal <jecaudal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 16:47:17 by jecaudal          #+#    #+#             */
/*   Updated: 2020/07/27 16:33:45 by jecaudal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool g_is_ctrlc = FALSE;

static void		handler(int nothing)
{
	nothing = 0;
	if (nothing == 0)
	{
		l_printf("\r");
		print_prompt();
		g_is_ctrlc = TRUE;
	}
}

static void		quithandler(int nothing)
{
	nothing = 0;
	if (nothing == 0)
		g_is_ctrlc = TRUE;
}

static int		ctrld_quit(t_stock *stock)
{
	int exit_status;

	exit_status = stock->exit_status;
	write(1, "exit\n", 5);
	free_t_stock(stock);
	return (exit_status);
}

static t_bool	debug_arg_detection(int argc, char **argv)
{
	if (argc >= 2 && ft_strcmp(argv[1], "--debug") == 0)
		return (TRUE);
	return (FALSE);
}

int				main(int argc, char **argv, char **envp)
{
	int		err;
	t_stock	*stock;

	signal(SIGINT, handler);
	signal(SIGQUIT, quithandler);
	if (!(stock = init_stock(envp)))
		return (1);
	stock->is_debug = debug_arg_detection(argc, argv);
	while (1)
	{
		err = 0;
		if ((err = wait_instruction(stock)) != 0 && err != SIG_CTRLD)
			error_manager(stock, err);
		if (err == SIG_CTRLD)
			return (ctrld_quit(stock));
		if (err == 0 && (err = parsing(stock)) != 0)
			error_manager(stock, err);
		ft_putstr_fd(stock->error_strings, STDERR);
		if ((err == 0 || err == ERR_EXIT) && (err = execution(stock)) != 0)
			error_manager(stock, err);
		reset(stock);
	}
	free_t_stock(stock);
	return (stock->exit_status);
}
