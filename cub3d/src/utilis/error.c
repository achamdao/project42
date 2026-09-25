/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:52:13 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 14:32:32 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	print_error_3(char *path, char *massg)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(massg, 2);
}

int	print_error_2(char *path, int error)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (error);
}

int	check_path_status(char *path)
{
	struct stat	path_stat;

	if (!path)
		return (0);
	if (stat(path, &path_stat) == -1)
	{
		if (errno == ENOENT)
			return (print_error_2(path, 127));
		else
			return (print_error_2(path, 126));
	}
	if (S_ISDIR(path_stat.st_mode))
	{
		return (print_error_3(path, ": is a directory\n"), 126);
	}
	if (S_ISREG(path_stat.st_mode))
	{
		if (access(path, X_OK) == 0)
			return (0);
		else
			return (print_error_2(path, 126));
	}
	return (print_error_3(path, ": Invalid file type\n"), 1);
}
