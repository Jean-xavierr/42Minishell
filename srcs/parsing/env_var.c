/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereligi <jereligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 14:33:48 by jereligi          #+#    #+#             */
/*   Updated: 2020/06/23 17:10:57 by jereligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*get_name(char *env_var)
{
	int		i;
	int		n;
	char	*tmp;

	i = 0;
	while (ft_isalnum(env_var[i]) && env_var[i])
		i++;
	if (!(tmp = (char *)malloc(sizeof(char) * i)))
		return (NULL);
	n = 0;
	while (n < i)
	{
		tmp[n] = env_var[n];
		n++;
	}
	tmp[n] = '\0';
	return (tmp);
}

char		*get_value(char *user_input)
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
	if (!(tmp = (char *)malloc(sizeof(char) * n + 1)))
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

char		**get_env_var(char *user_input, int nb_env_var)
{
	int		i;
	int		n;
	char	**tab_env_var;

	i = 0;
	n = 0;
	l_printf("nb_var = %d\n", nb_env_var);
	tab_env_var = pre_malloc_arrstring(nb_env_var);
	while (user_input[i])
	{
		if (user_input[i] == '$' && user_input[i - 1] != '\\')
		{
			free(tab_env_var[n]);
			tab_env_var[n] = get_name(&user_input[i + 1]);
			n++;
		}
		i++;
	}
	i = 0;
	while (i < nb_env_var)
	{
		printf("env_var[%d]:%s\n", i, tab_env_var[i]);
		i++;
	}
	return (tab_env_var);
}

char		**if_exist(char **tab_env_var, int nb_env_var, char **envp)
{
	int		i;
	int		n;
	int		len_var;
	char	**value;

	i = 0;
	value = pre_malloc_arrstring(nb_env_var);
	while (tab_env_var[i])
	{
		n = 0;
		len_var = ft_strlen(tab_env_var[i]);
		while (envp[n])
		{
			if (ft_strncmp(tab_env_var[i], envp[n], len_var) == 0)
			{
				free(value[i]);
				value[i] = get_value(envp[n]);
				break ;
			}
			n++;
		}
		i++;
	}
	i = 0;
	while (value[i])
		printf("value: %s\n", value[i++]);
	return (value);
}

char		*env_var(t_stock *s)
{
	int		nb_env_var;
	char	**tab_env_var;
	char	**value;
	char	*new;

	if ((nb_env_var = number_env_var(s->user_input)) != 0)
		tab_env_var = get_env_var(s->user_input, nb_env_var);
	if (nb_env_var > 0)
	{
		value = if_exist(tab_env_var, nb_env_var, s->envp);
		new = remove_and_replace(s->user_input, tab_env_var, value);
		free(s->user_input);
		s->user_input = new;
		free_env_var_data(tab_env_var, value);
	}
	l_printf("%s", s->user_input);
	return (NULL);
}