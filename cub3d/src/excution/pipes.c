/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:00:39 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 08:46:38 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	launch_pipeline_processes(t_info_cmd *cmds,
		t_data *data, int total_cmds)
{
	int				**pipes;
	t_pipeline_data	pipe_data;

	pipes = fn_pipe(total_cmds);
	if (!pipes)
		return (1);
	pipe_data.cmds = cmds;
	pipe_data.data = data;
	pipe_data.total_cmds = total_cmds;
	pipe_data.pipes = pipes;
	return (launch_pipeline_processes_core(&pipe_data));
}

int	pipe_line(t_info *info, t_data *data)
{
	t_info_cmd	*cmds;
	char		**paths;
	int			status;

	paths = ft_get_path(search_env_value(data->user_stack,
				"PATH"), &(info->error));
	if (info->error == -1)
		return (-1);
	cmds = initialize_cmd_all(data, info, paths);
	if (!cmds && info->error == -1)
		return (free_array(paths), -1);
	if (!cmds && info->error == 1)
		return (free_array(paths), ft_files_clear(&info->file), 1);
	status = launch_pipeline_processes(cmds, data, info->number_cmd);
	clean_all(cmds, info->number_cmd, data->envp);
	free_array(paths);
	return (status);
}
