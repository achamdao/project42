/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:31:11 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 11:29:30 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	fack_here_doc(t_here_doc **here_doc)
{
	char	*line;
	int		limiter_status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = read_line_from_user();
		if (!*here_doc)
			break ;
		limiter_status = is_limiter_reached(line, here_doc);
		if (limiter_status == 1)
			break ;
		free_and_null((void **)&line);
	}
	exit(0);
}

void	run_here_doc_fack(t_here_doc **here_doc)
{
	pid_t	pid;
	int		status;

	g_lobal_var = HERE_DOC;
	ignor_signal_perent();
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
		fack_here_doc(here_doc);
	else
	{
		waitpid(pid, &status, 0);
		g_lobal_var = HERE_DOC;
		setup_signals_child();
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
	}
}

char	read_heredoc(t_here_doc **here_doc, int file_fd, t_env *env, int error)
{
	char	*line;
	int		limiter_status;

	while (1)
	{
		line = readline("> ");
		if (!*here_doc || g_lobal_var == -2)
			break ;
		limiter_status = is_limiter_reached(line, here_doc);
		if (limiter_status == 1)
			break ;
		if (!limiter_status && (*here_doc)->last_limiter)
		{
			line = override_var(env, line, (*here_doc)->quote_exists, error);
			if (expand_and_write_line(line, file_fd) == FAILER)
				return (free(line), FAILER);
		}
		free_and_null((void **)&line);
	}
	if (g_lobal_var == -2)
		return (NOT_VALID);
	return (0);
}

char	*handle_here_doc2(t_info *info, int cmd_index, t_env *export_var)
{
	short	fd;
	char	*tmp_file;
	char	result;

	fd = 0;
	result = 0;
	tmp_file = NULL;
	if (info->is_here_doc && info->is_here_doc[cmd_index])
	{
		tmp_file = generate_random_string(50);
		fd = open(tmp_file, O_CREAT | O_RDWR | O_TRUNC, 0777);
		if (fd == FAILER)
			perror("open: ");
		result = read_heredoc(&info->here_doc, fd, export_var, info->error);
		close_file_if_needed(fd);
	}
	return (tmp_file);
}
