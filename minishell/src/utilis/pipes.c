/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 15:34:05 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/29 13:43:31 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	**alloc_pipes(int nb_cmds)
{
	int	**pipes;
	int	i;

	if (nb_cmds < 2)
		return (NULL);
	pipes = malloc(sizeof(int *) * (nb_cmds - 1));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < nb_cmds - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			while (--i >= 0)
				free(pipes[i]);
			free(pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

int	init_pipes(int **pipes, int nb_cmds)
{
	int	i;

	i = 0;
	while (i < nb_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			while (--i >= 0)
				close_file(pipes[i][0], pipes[i][1]);
			return (1);
		}
		i++;
	}
	return (0);
}

void	free_pipes(int **pipes, int nb_cmds)
{
	int	i;

	i = 0;
	while (i < nb_cmds - 1)
	{
		close_file(pipes[i][0], pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
}

int	**fn_pipe(int nb_cmds)
{
	int	**pipes;

	pipes = alloc_pipes(nb_cmds);
	if (!pipes)
		return (NULL);
	if (init_pipes(pipes, nb_cmds) == 1)
		return (NULL);
	return (pipes);
}
