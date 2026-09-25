/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:17:27 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/27 13:56:10 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*cmd_true(char *cmd, char *check)
{
	if (ft_strchr(cmd, '/'))
	{
		*check = 1;
		if (access(cmd, X_OK) == 0)
			return (ft_strjoin(NULL, cmd, 0));
		return (ft_strdup(cmd));
	}
	*check = 0;
	return (NULL);
}

int	is_dot_or_dotdot(const char *str)
{
	if (!str)
		return (0);
	return (!ft_strcmp(str, ".") || !ft_strcmp(str, "..")
		|| !ft_strcmp(str, "\0"));
}

char	*search_path(char *cmd, char **paths, int len)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	if (is_dot_or_dotdot(cmd))
		return (NULL);
	while (i < len)
	{
		if (!path)
			path = ft_strjoin(paths[i], cmd, 0);
		if (access(path, X_OK) == -1)
			free_and_null((void **)&path);
		i++;
	}
	return (path);
}

char	*get_cmd_and_path(t_info_cmd *info_cmd, char **paths)
{
	int		i;
	char	check;

	i = 0;
	if (info_cmd->cmd && *info_cmd->cmd)
		info_cmd->path = cmd_true(info_cmd->cmd[0], &check);
	if (info_cmd->path)
		return (info_cmd->path);
	if (!paths)
		return (NULL);
	while (paths[i])
		i++;
	info_cmd->path = search_path(info_cmd->cmd[0], paths, i);
	return (info_cmd->path);
}
