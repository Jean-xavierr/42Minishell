/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecaudal <jecaudal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 15:10:39 by jecaudal          #+#    #+#             */
/*   Updated: 2020/07/27 11:53:45 by jecaudal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# define MAX_PATH_LEN 4096

/*
**	EXECUTION SUB FUNCTIONS
*/

t_bool	is_builtin(char *path);

void	close_pipes(int *pipes, int n_pipes);
void	terminator(t_stock *s, char ***jobs, int n_jobs, int *status);
void	builtin_call_child(char **job, int *exit_stat, char ***envp);
void	builtin_call_parent(char **job, int *ex_stat, int fd, char ***envp);

int		jobs_caller(t_stock *s);
int		init_pipes(int **pipes, int n_jobs);
int		redirector(int *pipes, int jobpos, t_bool is_pipe, t_stock *s);
int		instance_builder(t_stock *s, int jobpos, int *pipes, t_bool is_pipe);

char	**job_cleaner(char **job);

/*
**	### INSTANCE_BUILDER SUB-FONCTIONS ###
*/
int		panic_ib(t_child c, int err);
int		save_child_pid(t_stock *stock, int err);

void	free_child(t_child child);
void	debug_child(t_child child);
void	print_exec_err(char *path);

/*
**	BUILTINS FUNCTIONS
*/

void	ft_exit(char **job);

int		pwd(int fd);
int		cd(char *path, char **envp);
int		echo(char **job, int fd);
int		env(char **job, char **envp, int fd);
int		unset(char ***envp, char **job);
int		export(char ***envp, char **job, int fd);

/*
**	Builtins additionnal functions
*/
t_bool	is_var_exist(char **envp, char *arg);

void	print_envp_export(char **envp, int fd);

int		var_replacement(char **envp, char *arg);

/*
**	Sub function of redirector.
*/
char	**rm_redir(char **job);

t_bool	is_in_redir(char **job);
t_bool	is_out_redir(char **job);
t_bool	is_aborted(t_stock *s, int jobpos);

int		redirector_file_in(char **job);
int		redirector_file_out(t_stock *s, int jobpos);

/*
**	JOBS_CLEANER SUB FUNCTIONS
*/

char	*arg_cleaner(char *arg);

int		escaper_nquote(char *buf);
int		escaper_dquote(char *buf);
int		part_len_quote(char *arg, int i);
int		part_len_dquote(char *arg, int i);
int		part_len_nquote(char *arg, int i);

void	pass_part(char *arg, int *i);

#endif
