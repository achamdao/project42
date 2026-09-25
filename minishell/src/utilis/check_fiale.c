/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fiale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:00:54 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/28 14:34:24 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	check_pipe(char check)
{
	if (check == -1)
	{
		perror("bash: pipe");
		exit(1);
	}
}

pid_t	check_fork(pid_t pid)
{
	if (pid == -1)
	{
		perror("bash: fork");
		return (-1);
	}
	return (pid);
}

void	check_execve(int result)
{
	if (result == -1)
	{
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

int	safe_dup2(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
	{
		perror("dup2 failed");
		return (-1);
	}
	return (0);
}
