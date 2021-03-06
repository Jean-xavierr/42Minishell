/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jecaudal <jecaudal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 09:04:57 by jecaudal          #+#    #+#             */
/*   Updated: 2020/07/04 13:47:04 by jecaudal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_strlen_c(char *str, char c)
{
	int i;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	return (i);
}

int			is_a_c(char *str, char c)
{
	int i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int			push_to_line(char **post_buffer, char **line, char sep)
{
	void *temp;

	if (sep == '\0' && ft_strcmp(*post_buffer, "") == 0)
		return (GNL_CTRLD);
	temp = *post_buffer;
	*line = ft_strdup_c(*post_buffer, sep);
	*post_buffer = ft_strcut_c(*post_buffer, sep);
	free(temp);
	if (sep == '\n')
		return (GNL_LINE_READED);
	else if (sep == '\0')
		return (GNL_EOF);
	return (0);
}

int			get_next_line_reading(int fd, char **post_buffer, char **line)
{
	int			ret_read;
	char		buf[GNL_BUFFER_SIZE + 1];

	while ((ret_read = read(fd, buf, GNL_BUFFER_SIZE)))
	{
		if (ret_read == -1)
			break ;
		buf[ret_read] = '\0';
		if ((*post_buffer = gnl_strjoin(*post_buffer, buf)) &&
		is_a_c(buf, '\n') == 1)
			break ;
	}
	if (ret_read >= 0 && is_a_c(*post_buffer, '\n') == 1)
		return (push_to_line(post_buffer, line, '\n'));
	if (ret_read == 0 && GNL_BUFFER_SIZE > 0)
		return (push_to_line(post_buffer, line, '\0'));
	return (GNL_ERROR);
}

int			get_next_line(int fd, char **line)
{
	static char	*post_buffer[200000];

	if (line == NULL)
		return (GNL_ERROR);
	if (fd >= 0 && !(post_buffer[fd]))
	{
		if (!(post_buffer[fd] = (char*)malloc(1)))
			return (0);
		post_buffer[fd][0] = '\0';
	}
	if (fd >= 0 && is_a_c(post_buffer[fd], '\n') == 1)
		return (push_to_line(&post_buffer[fd], line, '\n'));
	if (fd >= 0)
		return (get_next_line_reading(fd, &post_buffer[fd], line));
	return (GNL_ERROR);
}
