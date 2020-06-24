/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remplace_env_var.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jereligi <jereligi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 17:17:46 by jereligi          #+#    #+#             */
/*   Updated: 2020/06/23 17:28:21 by jereligi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int		remplace_env_var(char *new, char *value)
{
	int i;

	i = 0;
	while (value[i])
	{
		new[i] = value[i];
		i++;
	}
	return (i);
}