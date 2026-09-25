/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_utlis.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:59:07 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/29 12:37:01 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	execute_command(t_info_cmd *info, char **envp)
{
	execve(info->path, info->cmd, envp);
	print_error_3(info->cmd[0], ": command not found\n");
	exit(127);
}

char	the_last_cmd(t_info_cmd *info, t_data *data)
{
	pid_t	pid;

	ignor_signal_perent();
	pid = check_fork(fork());
	if (pid == 0)
	{
		setup_signals_child();
		if (!open_cmd_io_files(info->my_files, info->fd_here_doc))
			exit(1);
		if (data->stack->token == AKATSUKI)
			exit(0);
		execute_command(info, data->envp);
	}
	else if (pid == -1)
		return (1);
	return (0);
}

int	finale_cmd(t_info_cmd *info, t_data *data)
{
	int	status;

	if (!info->buiilding)
	{
		status = check_path_status(info->path);
		if (status)
			return (status);
	}
	if (the_last_cmd(info, data))
		return (1);
	return (NOT_VALID);
}
