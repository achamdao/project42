/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utilis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:58:35 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/29 12:47:34 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	setup_output_redirection(t_info_cmd *cmd)
{
	int	fd;
	int	saved_stdout;

	saved_stdout = dup(STDOUT_FILENO);
	if (saved_stdout == FAILER)
		return (FAILER);
	fd = get_outfile(cmd->my_files, cmd->fd_here_doc);
	if (fd == FAILER || fd == NOT_VALID)
	{
		close(saved_stdout);
		return (FAILER);
	}
	if (fd != STDOUT_FILENO)
	{
		if (dup2(fd, STDOUT_FILENO) == FAILER)
		{
			close(fd);
			close(saved_stdout);
			return (FAILER);
		}
		close_file_if_needed(fd);
	}
	return (saved_stdout);
}

static int	restore_stdout(int saved_stdout)
{
	if (dup2(saved_stdout, STDOUT_FILENO) == FAILER)
	{
		close(saved_stdout);
		return (FAILER);
	}
	close(saved_stdout);
	return (0);
}

int	run_single_builtin(t_info_cmd *cmd, t_data *data, int error)
{
	int	status;
	int	saved_stdout;

	saved_stdout = setup_output_redirection(cmd);
	if (saved_stdout == FAILER)
		return (1);
	status = execute_builtin(cmd, data, error);
	if (restore_stdout(saved_stdout) == FAILER)
		return (FAILER);
	return (status);
}
