/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:05:00 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 08:46:54 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static void	dup_pipe_ends(int **pipes, int index, int total_cmds)
{
	if (index > 0)
		dup2(pipes[index - 1][0], STDIN_FILENO);
	if (index < total_cmds - 1)
		dup2(pipes[index][1], STDOUT_FILENO);
	close_all_pipes(pipes, total_cmds);
}

static void	exec_child_cmd_core(t_pipeline_data *pipe_data, int index)
{
	int			status;
	t_info_cmd	*cmd;
	t_data		*data;

	data = pipe_data->data;
	cmd = pipe_data->cmds;
	setup_signals_child();
	dup_pipe_ends(pipe_data->pipes, index, pipe_data->total_cmds);
	if (!open_cmd_io_files(cmd[index].my_files, cmd[index].fd_here_doc))
		exit(1);
	if (data->stack->token == AKATSUKI)
		exit(0);
	status = check_path_status(cmd[index].path);
	if (status)
		exit(status);
	if (cmd[index].buiilding == EXIT)
		cmd[index].tmp = EXIT;
	if (cmd[index].buiilding)
		exit(execute_builtin(&cmd[index], data, 0));
	execve(cmd[index].path, cmd[index].cmd, pipe_data->data->envp);
	print_error_3(cmd[index].cmd[0], ": command not found\n");
	exit(127);
}

static char	create_child_process(t_pipeline_data *pipe_data,
			int i, pid_t child_pids[])
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		exec_child_cmd_core(pipe_data, i);
	else if (pid > 0)
		child_pids[i] = pid;
	else
	{
		perror("fork failed");
		free_pipes(pipe_data->pipes, pipe_data->total_cmds);
		return (1);
	}
	return (0);
}

static void	wait_for_all_children(t_pipeline_data *pipe_data,
			int *status, pid_t child_pids[])
{
	int		i;
	pid_t	child_pid;

	i = 0;
	while (i < pipe_data->total_cmds)
	{
		child_pid = waitpid(child_pids[i], status, 0);
		if (child_pid == -1)
		{
			perror("waitpid failed");
			continue ;
		}
		i++;
	}
}

int	launch_pipeline_processes_core(t_pipeline_data *pipe_data)
{
	int		i;
	int		status;
	pid_t	*child_pids;

	i = 0;
	status = 0;
	child_pids = (pid_t *)malloc(sizeof(pid_t) * pipe_data->total_cmds);
	if (!child_pids)
		return (-1);
	ignor_signal_perent();
	while (i < pipe_data->total_cmds)
	{
		if (create_child_process(pipe_data, i, child_pids))
			return (1);
		if (i < pipe_data->total_cmds - 1)
			close(pipe_data->pipes[i][1]);
		if (i > 0)
			close(pipe_data->pipes[i - 1][0]);
		move_to_next_pipe(&pipe_data->data->stack);
		i++;
	}
	wait_for_all_children(pipe_data, &status, child_pids);
	free_pipes(pipe_data->pipes, pipe_data->total_cmds);
	free(child_pids);
	return (wait_for_child(status));
}
