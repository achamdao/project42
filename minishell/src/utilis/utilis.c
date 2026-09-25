/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:20:20 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 14:29:33 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	wait_for_child(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (128 + WTERMSIG(status));
}

size_t	ft_strlen_to_limiter(const char *s, char c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (*s && *s != c)
	{
		i++;
		s++;
	}
	return (i);
}

int	ft_strchr_index(const char *str, char c)
{
	int	index;

	if (!str)
		return (-1);
	index = 0;
	while (str[index] != '\0')
	{
		if (str[index] == c)
			return (index);
		index++;
	}
	return (-1);
}

int	count_char(const char *str, char c)
{
	int	count;

	count = 0;
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == c)
			count++;
		str++;
	}
	return (count);
}

char	*get_last_node(char **matrix)
{
	int	i;

	if (!matrix)
		return (NULL);
	i = 0;
	while (matrix[i])
		i++;
	if (i == 0)
		return (NULL);
	return (matrix[i - 1]);
}
