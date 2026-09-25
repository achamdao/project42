/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:38:37 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 14:31:55 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	ft_open(char *str, int falg, int permission)
{
	int	fd;

	fd = open(str, falg, permission);
	if (fd == -1)
	{
		ft_putstr_fd("bash: ", 2);
		perror(str);
	}
	return (fd);
}

short	open_file(char *str, short token)
{
	if (token == APP_FILE)
		return (ft_open(str, O_CREAT | O_WRONLY | O_APPEND, 0646));
	else if (token == HER_FILE)
		return (ft_open(str, O_CREAT | O_RDWR | O_TRUNC, 0777));
	else if (token == IN_FILE)
		return (ft_open(str, O_RDONLY, 0646));
	else if (token == OUT_FILE)
		return (ft_open(str, O_CREAT | O_WRONLY | O_TRUNC, 0646));
	return (-2);
}
