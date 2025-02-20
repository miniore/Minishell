/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: porellan <porellan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:12:37 by porellan          #+#    #+#             */
/*   Updated: 2024/11/14 11:24:22 by porellan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*read_nl(char *temp, int fd)
{
	char	*buffer;
	ssize_t	data;
	char	*aux;

	buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(temp), temp = NULL, NULL);
	if (!temp)
		temp = (char *)ft_calloc(1, 1);
	if (!temp)
		return (free(buffer), NULL);
	data = 1;
	while (!ft_strchr_gnl(temp, '\n'))
	{
		data = read(fd, buffer, BUFFER_SIZE);
		if (data == -1)
			return (free(temp), temp = NULL, free(buffer), buffer = NULL, NULL);
		if (data == 0)
			return (free(buffer), buffer = NULL, temp);
		buffer[data] = '\0';
		aux = temp;
		temp = ft_strjoin_gnl(temp, buffer);
		free(aux);
	}
	return (free(buffer), buffer = NULL, temp);
}

char	*sub_nl(char *s)
{
	size_t	i;
	char	*result;

	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
		i++;
	if (s[i] == '\n')
		i++;
	result = ft_calloc(i + 1, 1);
	if (!result)
		return (NULL);
	while (i--)
		result[i] = s[i];
	return (result);
}

char	*delete_nl(char *line_rd)
{
	char			*line_rs;
	unsigned int	i;
	unsigned int	j;
	int				size;

	i = 0;
	j = 0;
	while (line_rd[i] != '\n' && line_rd[i] != '\0')
		i++;
	size = ft_strlen(line_rd) - i;
	line_rs = ft_calloc(size + 1, 1);
	if (!line_rs)
		return (free(line_rd), line_rd = NULL, NULL);
	while (size--)
		line_rs[j++] = line_rd[++i];
	return (free(line_rd), line_rd = NULL, line_rs);
}

char	*get_next_line(int fd)
{
	static char	*line_rd[FOPEN_MAX];
	char		*line;

	if (fd < 0)
		return (free(line_rd[fd]), line_rd[fd] = NULL, NULL);
	line_rd[fd] = read_nl(line_rd[fd], fd);
	if (!line_rd[fd])
		return (NULL);
	if (line_rd[fd] == NULL || line_rd[fd][0] == 0)
		return (free(line_rd[fd]), line_rd[fd] = NULL, NULL);
	line = sub_nl(line_rd[fd]);
	if (!line)
		return (free(line_rd[fd]), line_rd[fd] = NULL, NULL);
	line_rd[fd] = delete_nl(line_rd[fd]);
	return (line);
}
