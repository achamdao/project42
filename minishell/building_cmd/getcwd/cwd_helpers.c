/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:40:31 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/17 14:41:11 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	ft_is_root(char *path)
{
	if (!path)
		return (-1);
	if (path[0] == '/')
		return (1);
	return (0);
}

char	*handle_dot_dot(char *env_pwd)
{
	char	*new_pwd;
	char	*last_slash;

	new_pwd = ft_strdup(env_pwd);
	if (!new_pwd)
		return (NULL);
	last_slash = ft_strrchr(new_pwd, '/');
	if (!last_slash)
		return (free(new_pwd), NULL);
	if (last_slash == new_pwd)
		new_pwd[1] = '\0';
	else
		*last_slash = '\0';
	return (new_pwd);
}
