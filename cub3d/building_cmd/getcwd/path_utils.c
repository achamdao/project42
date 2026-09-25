/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:39:57 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 14:09:27 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	safe_replace(char **dst, char *new_val)
{
	if (!new_val)
		return (0);
	free(*dst);
	*dst = new_val;
	return (1);
}

char	*absolute_path(char *pwd, char *path)
{
	char	*dir;
	char	*result;
	int		i;
	int		dir_len;

	result = ft_strdup(pwd);
	if (!result)
		return (NULL);
	i = 0;
	while (path[i])
	{
		dir = get_dir(&path[i], &dir_len);
		if (!dir)
			return (free(result), NULL);
		if (!ft_strcmp(dir, ".."))
			safe_replace(&result, process_parent_directory(result));
		else if (ft_strcmp(dir, ".") != 0 && dir[0] != '\0')
			safe_replace(&result, process_child_directory(result, dir));
		free(dir);
		i += dir_len;
		i = skip_slashes(path, i);
	}
	return (result);
}

char	*relative_path(char *path)
{
	int	i;

	i = 0;
	while (path[i] && path[i] == '/')
		i++;
	return (absolute_path("/", &path[i]));
}

char	*get_dir(char *path, int *length)
{
	int		i;
	char	*slash;

	i = 0;
	while (path[i] == '/')
		i++;
	slash = ft_strchr(&path[i], '/');
	if (slash)
		*length = slash - &path[i];
	else
		*length = ft_strlen(&path[i]);
	return (ft_strndup(&path[i], *length));
}

int	skip_slashes(char *path, int i)
{
	while (path[i] && path[i] == '/')
		i++;
	return (i);
}
