/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_single_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:50:00 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/03 18:12:10 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	setup_and_initialize_cmds(t_info *info, t_data *data,
			char **paths, t_info_cmd **cmds)
{
	*cmds = initialize_cmd_all(data, info, paths);
	if (!*cmds && info->error == 1)
		return (free_array(paths), ft_files_clear(&info->file), 1);
	if (!*cmds)
		return (free_array(paths), FAILER);
	if ((*cmds)[0].buiilding == EXIT)
		info->temp_error = EXIT;
	return (0);
}

static int	execute_cmd(t_info_cmd *cmds, t_data *data, int error)
{
	int	status;

	if (cmds[0].buiilding)
		status = run_single_builtin(&cmds[0], data, error);
	else
		status = finale_cmd(&cmds[0], data);
	return (status);
}

int	run_simple_cmd(t_info *info, t_data *data)
{
	char		**paths;
	t_info_cmd	*cmds;
	int			status;

	if (!info->info)
		return (0);
	paths = ft_get_path(search_env_value
			(data->user_stack, "@PATH"), &(info->error));
	if (info->error == FAILER)
		return (FAILER);
	status = setup_and_initialize_cmds(info, data, paths, &cmds);
	if (status == 1)
		return (1);
	if (status == FAILER)
		return (FAILER);
	status = execute_cmd(cmds, data, info->error);
	if (info->temp_error == EXIT && cmds[0].tmp == FAILER)
		info->temp_error = 0;
	free_array(paths);
	clean_all(cmds, 1, data->envp);
	if (status != NOT_VALID)
		return (status);
	while (wait(&status) > 0)
		;
	return (wait_for_child(status));
}
