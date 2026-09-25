/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:00:00 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 08:45:50 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	child_process_here_doc(t_info *info, int cmd_index,
		t_env *export_var)
{
	int		pipe_fd[2];
	pid_t	child_pid;

	g_lobal_var = HERE_DOC;
	if (create_pipe(pipe_fd) == -1)
		return (-1);
	child_pid = launch_here_doc_child(info, cmd_index, export_var, pipe_fd);
	if (child_pid < 0)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (-1);
	}
	return (receive_fd_from_child(pipe_fd, child_pid));
}

int	fill_cmd_struct(t_info_cmd *cmd, t_data *data, t_info *info,
		int i)
{
	cmd->cmd = array_cmd(data->stack);
	if (!cmd->cmd)
		return (FAILER);
	if (info->is_here_doc[i])
		cmd->fd_here_doc = child_process_here_doc(info, i, data->user_stack);
	else
		cmd->fd_here_doc = -1;
	if (cmd->fd_here_doc == NOT_VALID)
	{
		info->error = 1;
		return (NOT_VALID);
	}
	cmd->buiilding = check_if_buildin_cmd(cmd->cmd);
	if (cmd->buiilding == FIAL)
	{
		info->error = FAILER;
		return (FAILER);
	}
	cmd->my_files = extract_files_for_current_cmd(&data->files);
	if (info->is_here_doc[i])
		pop_to_here_doc(&info->here_doc);
	update_underscore_value(&data->user_stack, cmd, info->number_cmd);
	return (0);
}

t_info_cmd	*initialize_cmd_all(t_data *data, t_info *info, char **paths)
{
	t_info_cmd	*cmds;
	int			i;
	t_stack		*original_stack;
	short		result;

	original_stack = data->stack;
	cmds = malloc(sizeof(t_info_cmd) * info->number_cmd);
	if (!cmds)
		return (NULL);
	ft_bzero(cmds, sizeof(t_info_cmd) * info->number_cmd);
	i = 0;
	while (i < info->number_cmd)
	{
		result = fill_cmd_struct(&cmds[i], data, info, i);
		if (result == -1 || result == NOT_VALID)
			return (clean_all(cmds, i + 1, NULL), NULL);
		if (!cmds[i].buiilding)
			cmds[i].path = get_cmd_and_path(&cmds[i], paths);
		move_to_next_pipe(&data->stack);
		i++;
	}
	data->envp = stack_to_envp(data->user_stack);
	data->stack = original_stack;
	return (cmds);
}
