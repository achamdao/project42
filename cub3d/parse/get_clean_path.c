/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_clean_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:35:39 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/27 13:31:59 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	**ft_get_path(char *str, short *error)
{
	int		i;
	char	**arr_path;
	char	*temp;

	i = 0;
	if (!str)
		return (NULL);
	arr_path = ft_split(str, ':');
	if (!arr_path)
	{
		*error = FAILER;
		return (NULL);
	}
	while (arr_path[i])
	{
		temp = ft_strjoin(arr_path[i], "/", 1);
		if (!temp)
		{
			*error = FAILER;
			return (free_array(arr_path), NULL);
		}
		arr_path[i] = temp;
		i++;
	}
	return (arr_path);
}
