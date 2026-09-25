/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hindle_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:58:52 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 22:08:22 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	close_file(int input_fd, int output_fd)
{
	if (input_fd != STDIN_FILENO && input_fd != STDOUT_FILENO)
		close(input_fd);
	if (output_fd != STDIN_FILENO && output_fd != STDOUT_FILENO)
		close(output_fd);
}

short	remove_file(char *file)
{
	if (access(file, F_OK) == 0)
		unlink(file);
	return (0);
}

void	close_files_array(int *fds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (fds[i] != -1)
		{
			close_file_if_needed(fds[i]);
			fds[i] = -1;
		}
		i++;
	}
}

void	close_file_if_needed(int fd)
{
	if (fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != -1)
		close(fd);
}

void	close_all_pipes(int **pipes, int number_cmd)
{
	int	i;

	i = 0;
	while (i < number_cmd - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}
