/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereligi <jereligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:33:48 by jereligi          #+#    #+#             */
/*   Updated: 2020/07/23 19:02:55 by jereligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This function replaces the environment variables with their value
*/

#include "minishell.h"

char			*get_name(char *env_var)
{
	int		i;
	int		n;
	char	*tmp;

	i = 0;
	if (env_var[0] == '$')
		while (env_var[i] == '$')
			i++;
	else
		while ((env_var[i] && (ft_isalnum(env_var[i]) || env_var[i] == '_')))
			i++;
	if (i == 0 && (env_var[0] == '?' || env_var[0] == '\0'))
		i++;
	if (!(tmp = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	n = -1;
	while (++n < i)
	{
		if (env_var[0] == ' ' || env_var[0] == '\0')
			tmp[n] = '$';
		else
			tmp[n] = env_var[n];
	}
	tmp[n] = '\0';
	return (tmp);
}

char			*get_value(char *user_input)
{
	int		i;
	int		n;
	char	*tmp;

	i = 0;
	while (user_input[i] != '=' && user_input[i])
		i++;
	if (user_input[i] == '=' && user_input[i])
		i++;
	n = 0;
	while (user_input[i + n])
		n++;
	if (!(tmp = (char *)malloc(sizeof(char) * (n + 1))))
		return (NULL);
	n = 0;
	while (user_input[i])
	{
		tmp[n] = user_input[i];
		i++;
		n++;
	}
	tmp[n] = '\0';
	return (tmp);
}

char			**get_env_var(char *ui, int nb_env_var)
{
	int		i;
	int		n;
	int		quote;
	char	**tab_env_var;

	i = 0;
	n = 0;
	quote = 0;
	tab_env_var = pre_malloc_arrstring(nb_env_var);
	while (ui[i])
	{
		if (ui[i] == '\'' || ui[i] == '\"')
		{
			word_between_simple_quote(&i, ui, &quote);
			i++;
		}
		if (ui[i] == '$' && (!is_escape(i, ui)) & (quote == 0 || quote == 2))
		{
			free(tab_env_var[n]);
			tab_env_var[n++] = get_name(&ui[i + 1]);
			spend_if_multiple_dollars(ui, &i);
		}
		i++;
	}
	return (tab_env_var);
}

static char		**if_exist(char **tab_env_var, int nb_env_var, char **envp, \
t_stock *s)
{
	int		i;
	char	**value;

	i = 0;
	value = pre_malloc_arrstring(nb_env_var);
	while (tab_env_var[i])
	{
		if (tab_env_var[i][0] == '$')
		{
			free(value[i]);
			value[i] = ft_strdup(tab_env_var[i]);
		}
		else
		{
			find_env_var(tab_env_var, envp, value, i);
			is_env_exit_status(tab_env_var[i], value, i, s);
		}
		i++;
	}
	return (value);
}

char			*env_var(t_stock *s)
{
	int		nb_env_var;
	char	**tab_env_var;
	char	**value;
	char	*new;

	if ((nb_env_var = number_env_var(s->user_input)) != 0)
		tab_env_var = get_env_var(s->user_input, nb_env_var);
	if (nb_env_var > 0)
	{
		value = if_exist(tab_env_var, nb_env_var, s->envp, s);
		new = remove_and_replace(s->user_input, value);
		free(s->user_input);
		s->user_input = new;
		free_env_var_data(tab_env_var, value);
	}
	if (s->is_debug == TRUE)
		l_printf("user_input = %s\n", s->user_input);
	return (NULL);
}
