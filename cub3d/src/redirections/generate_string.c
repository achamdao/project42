/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 11:51:01 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/29 12:18:35 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	open_urandom(void)
{
	int	fd;

	fd = open("/dev/urandom", O_RDONLY, 0777);
	return (fd);
}

static int	fill_random_bytes(int fd, char *buffer, int length)
{
	ssize_t	bytes_read;
	ssize_t	result;

	bytes_read = 0;
	while (bytes_read < length)
	{
		result = read(fd, buffer + bytes_read, length - bytes_read);
		if (result <= 0)
			return (0);
		bytes_read += result;
	}
	return (1);
}

static int	is_valid_char(char c)
{
	return (c != '/' && c != '\\' && c != '?' && c != '*'
		&& c != ':' && c != '"' && c != '<' && c != '>' && c != '|');
}

static char	*generate_random_chars(int length, int fd)
{
	char	*str;
	char	random_byte;
	int		i;

	str = malloc(length + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < length)
	{
		if (!fill_random_bytes(fd, &random_byte, 1))
		{
			free(str);
			return (NULL);
		}
		random_byte = ASCII_START + ((unsigned char)random_byte % ASCII_RANGE);
		if (is_valid_char(random_byte))
		{
			str[i] = random_byte;
			i++;
		}
	}
	str[length] = '\0';
	return (str);
}

char	*generate_random_string(int length)
{
	char	*str;
	int		fd;
	char	*re_str;

	if (length <= 0)
		return (NULL);
	fd = open_urandom();
	if (fd == FAILER)
		return (NULL);
	str = generate_random_chars(length, fd);
	close(fd);
	if (!str)
		return (NULL);
	re_str = ft_strjoin("/var/tmp/", str, 0);
	re_str = ft_strjoin(re_str, ".c", 1);
	free(str);
	return (re_str);
}
