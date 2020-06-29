/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecaudal <jecaudal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 13:22:38 by jecaudal          #+#    #+#             */
/*   Updated: 2020/06/29 15:50:15 by jecaudal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
# define MINISHELL_H

# define TRUE 1
# define FALSE 0
# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define SIG_CTRLD 1

# define ERR_MALLOC 1
# define ERR_ERRNO 2
# define ERR_SYNTAX 3
# define ERR_EXIT 4

# define OUR_PS1 "minishell$>"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <libgen.h>
# include <string.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "get_next_line.h"

typedef char t_bool;

typedef struct	s_stock
{
	char		**envp;
	char		*user_input;
	char		***jobs;
	int			n_jobs;
	t_bool		is_pipe;
	int			*pipes;
	char		exit_status;
	char		*error_strings;
	t_bool		is_debug;
}				t_stock;

t_stock	*init_stock(char **envp);
void	free_t_stock(t_stock *stock);
void	error_printer(int err);
int		parsing(t_stock *stock);
int		execution(t_stock *stock);

/*
**	Debug functions.
*/
void	print_jobs(char ***jobs, int n_jobs);

# include "lib.h"
# include "parsing.h"
# include "execution.h"
# include "error_messages.h"
# include "split_command.h"

#endif