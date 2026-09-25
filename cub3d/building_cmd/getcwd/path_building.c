/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_building.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:40:19 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 14:10:08 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*join_pwd(char *env_pwd, char *relative_path)
{
	char	*joined;
	char	*tmp;
	size_t	len;

	len = ft_strlen(env_pwd);
	if (len > 0 && env_pwd[len - 1] == '/')
		joined = ft_strdup(env_pwd);
	else
		joined = ft_strjoin(env_pwd, "/", 0);
	if (!joined)
		return (NULL);
	tmp = ft_strjoin(joined, relative_path, 1);
	return (tmp);
}

char	*process_parent_directory(char *current_path)
{
	char	*new_path;

	new_path = handle_dot_dot(current_path);
	return (new_path);
}

char	*process_child_directory(char *current_path, char *dir)
{
	char	*new_path;

	new_path = join_pwd(current_path, dir);
	return (new_path);
}
