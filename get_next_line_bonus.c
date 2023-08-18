/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danevans <danevans@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 12:34:43 by danevans          #+#    #+#             */
/*   Updated: 2023/08/18 14:03:37 by danevans         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*bytes_read(int fd, char *backup, char *buffer)
{
	char	*temp;
	ssize_t	bytes;

	bytes = read(fd, buffer, BUFFER_SIZE);
	while (bytes > 0)
	{
		buffer[bytes] = '\0';
		if (!backup)
			backup = ft_strdup("");
		temp = backup;
		backup = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(backup, '\n'))
			break ;
		bytes = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes == -1)
	{
		free(buffer);
		free(backup);
		return (NULL);
	}
	free(buffer);
	return (backup);
}

static char	*ft_line(char *backup)
{
	int		count;
	char	*line;

	if (!backup)
		return (NULL);
	count = 0;
	while (backup[count] != '\0')
	{
		if (backup[count] == '\n')
			break ;
		count++;
	}
	line = malloc(sizeof(char) * (count + 2));
	if (!line)
		return (NULL);
	ft_strlcpy(line, backup, count + 2);
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*ft_update_backup(char *backup)
{
	int		count;
	char	*new_back;

	count = 0;
	while (backup[count] != '\0')
	{
		if (backup[count] == '\n')
			break ;
		count++;
	}
	if (backup[count] == '\0')
	{
		free (backup);
		return (NULL);
	}
	new_back = malloc(sizeof(char) * (ft_strlen(backup) - count + 1));
	if (!new_back)
		return (NULL);
	ft_strlcpy(new_back, backup + count + 1, ft_strlen(backup) - count + 1);
	free(backup);
	return (new_back);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*backup[OPEN_MAX + 1];

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!buffer)
	{
		free (buffer);
		return (NULL);
	}
	backup[fd] = bytes_read(fd, backup[fd], buffer);
	if (backup[fd] == NULL)
		return (NULL);
	line = ft_line(backup[fd]);
	backup[fd] = ft_update_backup(backup[fd]);
	return (line);
}
