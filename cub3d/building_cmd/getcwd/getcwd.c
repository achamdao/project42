/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:39:16 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/17 14:39:35 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*ft_getcwd(char *pwd, char *path)
{
	if (!pwd || !path)
		return (NULL);
	if (!ft_is_root(path))
		return (absolute_path(pwd, path));
	return (relative_path(path));
}
