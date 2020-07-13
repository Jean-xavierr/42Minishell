/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instance_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecaudal <jecaudal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 16:29:13 by jecaudal          #+#    #+#             */
/*   Updated: 2020/07/09 15:44:51 by jecaudal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	This function will call redirection piping and execute binaries in child.
*/

void	print_exec_err(char *path)
{
	struct stat	path_stat;
	
	stat(path, &path_stat);
	l_printf("minishell: %s: ", path);
	if (ft_c_finder('/', path) == FALSE)
		l_printf("command not found\n");
	else if (S_ISDIR(path_stat.st_mode) == TRUE)
		l_printf("is a directory\n");
	else if (S_ISREG(path_stat.st_mode) == TRUE)
		l_printf("Permission denied\n");
	else
		l_printf("No such file or directory\n");
	exit(127);
}

static void	debug_ib(char *path, char *exec_name, int jobpos)
{
	if (path)
		l_printf("path = %s\n", path);
	if (exec_name)
		l_printf("exec_name = %s\n", exec_name);
	l_printf("jobpos = %d\n", jobpos);
	write(1, "\n", 1);
}

static int	panic_ib(char *path, char *exec_name, int err)
{
	if (path)
		free(path);
	if (exec_name)
		free(exec_name);
	return (err);
}

static int	init_ib(char **path, char **exec_name, char **job)
{
	*path = ft_strdup(find_exec(job)[0]);
	if (!path)
		return (ERR_MALLOC);
	*exec_name = ft_basename(find_exec(job)[0]);
	if (!exec_name)
	{
		free(path);
		return (ERR_MALLOC);
	}
	return (0);
}

int			instance_builder(t_stock *s, int jobpos, int *pipes, t_bool is_pipe)
{
	int		err;
	pid_t	child;
	char	*path;
	char	*exec_name;

	errno = 0;
	if ((init_ib(&path, &exec_name, s->jobs[jobpos])))
		return (ERR_MALLOC);
	if (s->is_debug == TRUE)
		debug_ib(path, exec_name, jobpos);
	if ((child = fork()) == 0)
	{
		free(find_exec(s->jobs[jobpos])[0]);
		find_exec(s->jobs[jobpos])[0] = exec_name;
		err = redirector(pipes, jobpos, is_pipe, s);
		close_pipes(pipes, s->n_jobs * 2 - 2);
		if (err == 0 && is_builtin(path) == TRUE)
			builtin_call_child(s->jobs[jobpos], &(s->exit_status), &(s->envp));
		else if (err == 0 && (ft_c_finder('/', path) == FALSE ||
				execve(path, s->jobs[jobpos], s->envp) == -1))
			print_exec_err(path);
	}
	else if (child == -1)
		return (panic_ib(path, exec_name, ERR_ERRNO));
	return (panic_ib(path, exec_name, 0));
}