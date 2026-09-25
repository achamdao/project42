/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:19:20 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/29 12:30:35 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	handle_sigint_heredoc(int sig)
{
	(void)sig;
	g_lobal_var = -2;
	close(STDIN_FILENO);
}

short	run_here_doc(t_info *info, int cmd_index,
		t_env *export_var, int pipe_fd[2])
{
	char	*fd_str;

	signal(SIGINT, handle_sigint_heredoc);
	fd_str = handle_here_doc2(info, cmd_index, export_var);
	if (g_lobal_var == -2)
	{
		remove_file(fd_str);
		free(fd_str);
		close(pipe_fd[1]);
		exit(1);
	}
	if (fd_str)
	{
		write(pipe_fd[1], fd_str, ft_strlen(fd_str));
		free(fd_str);
	}
	close(pipe_fd[1]);
	exit(0);
}

pid_t	launch_here_doc_child(t_info *info, int cmd_index,
		t_env *export_var, int pipe_fd[2])
{
	pid_t	pid;

	g_lobal_var = HERE_DOC;
	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return (1);
	}
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		run_here_doc(info, cmd_index, export_var, pipe_fd);
	}
	close(pipe_fd[1]);
	return (pid);
}

int	receive_fd_from_child(int pipe_fd[2], pid_t pid)
{
	int		status;
	char	buffer[80];
	int		bytes_read;
	int		fd;

	waitpid(pid, &status, 0);
	status = wait_for_child(status);
	bytes_read = read(pipe_fd[0], buffer, sizeof(buffer) - 1);
	close(pipe_fd[0]);
	if (status != 0)
		return (NOT_VALID);
	if (bytes_read < 0)
		return (FAILER);
	buffer[bytes_read] = '\0';
	fd = reopen_temp_file(buffer);
	remove_file(buffer);
	return (fd);
}

int	create_pipe(int pipe_fd[2])
{
	if (pipe(pipe_fd) == FAILER)
	{
		perror("pipe creation failed");
		return (FAILER);
	}
	return (0);
}
