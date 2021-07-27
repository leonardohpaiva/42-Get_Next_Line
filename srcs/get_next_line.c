/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lehenriq <lehenriq@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 13:22:11 by lehenriq          #+#    #+#             */
/*   Updated: 2021/07/25 21:57:54 by lehenriq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void	ft_buf(char **storage, char **temp, char **buffer)
{
	if (!*storage)
		*storage = ft_strdup(*buffer);
	else
	{
		*temp = ft_strdup(*storage);
		free(*storage);
		*storage = ft_strjoin(*temp, *buffer);
		free(*temp);
	}
}

static int	ft_linebreak(char **storage, size_t *cut)
{
	int	i;

	i = 0;
	if (!*storage)
		return (0);
	while ((*storage)[i])
	{
		if ((*storage)[i] == '\n')
		{
			*cut = i;
			return (1);
		}
		i++;
	}
	return (0);
}

static char	*ft_line(char **storage, size_t *cut)
{
	int		i;
	char	*temp;
	char	*line;

	i = 0;
	line = NULL;
	if (!*storage)
		return (NULL);
	temp = ft_strdup(*storage);
	if (ft_linebreak(&*storage, &*cut))
	{
		line = ft_substr(*storage, 0, *cut + 1);
		free(*storage);
		*storage = ft_substr(temp, *cut + 1, ft_strlen(temp));
	}
	else
	{
		i = ft_strlen(temp);
		if (i > 0)
			line = ft_substr(temp, 0, i);
		free(*storage);
		*storage = NULL;
	}
	free(temp);
	return (line);
}

char	*get_next_line(int fd)
{
	size_t		ret;
	size_t		cut;
	static char	*storage;
	char		*buffer;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) != 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	ret = read(fd, buffer, BUFFER_SIZE);
	cut = 0;
	while (ret > 0)
	{
		buffer[ret] = '\0';
		ft_buf(&storage, &temp, &buffer);
		if (ft_linebreak(&storage, &cut))
			break ;
		ret = read(fd, buffer, BUFFER_SIZE);
	}	
	free(buffer);
	return (ft_line(&storage, &cut));
}
