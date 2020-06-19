/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereligi <jereligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 15:54:35 by jereligi          #+#    #+#             */
/*   Updated: 2020/06/19 15:55:27 by jereligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	  is_escape(int i, char *user_input)
{
	if (i > 0)
	{
		if (user_input[i - 1] == '\\')
			return (1);
	}
	return (0);
}

static int	  additional_read(char quote, t_stock *s)
{
	int		status;
	char	*tmp;

	status = 0;
	tmp = NULL;
	if (quote != '0')
	{
		l_printf("quote> ");
		status = get_next_line(0, &tmp);
		if (status == GNL_LINE_READED || status == GNL_EOF)
		{
			tmp = ft_strjoindel("\n", tmp, 2);
			s->user_input = ft_strjoindel(s->user_input, tmp, 3);
		}
		else if (status == GNL_CTRLD)
		{
			s->error_strings = ft_strjoin(ERR_QUOTE1, &quote);
			s->error_strings = ft_strjoindel(s->error_strings, ERR_QUOTE2, 1);
			l_printf("%s\n", s->error_strings);
			return (ERR_SYNTAX);
		}
	}
	else
		return (1);
	l_printf("|%s|\n", s->user_input);
	return (0);
}

int			 check_quote(t_stock *s)
{
	int		i;
	int		valid_quote;
	char	quote;

	i = 0;
	valid_quote = 0;
	quote = '0';
	while (valid_quote == 0)
	{
		if (s->user_input[i] == '\0')
			if ((valid_quote = additional_read(quote, s)) == 3)
				return (ERR_SYNTAX);
		if ((s->user_input[i] == '"' && quote == '0') && (!is_escape(i, s->user_input)))
			quote = '\"';
		else if ((s->user_input[i] == '\'' && quote == '0') && (!is_escape(i, s->user_input)))
			quote = '\'';
		else if ((quote == s->user_input[i]) && (!is_escape(i, s->user_input)))
			quote = '0';
		i++;
	}
	return (0);
}