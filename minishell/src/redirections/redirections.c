/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:34:17 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/29 12:45:14 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	get_input_fd(t_files *curr, int file_here_doc, int in_fd)
{
	if (file_here_doc != in_fd)
		close_file(in_fd, 0);
	if (curr->token == HERE_DOC)
		return (file_here_doc);
	return (open_file(curr->file, curr->token));
}

int	get_output_fd(t_files *curr, int out_fd)
{
	close_file(out_fd, 0);
	return (open_file(curr->file, curr->token));
}

int	get_outfile(t_files *files, int file_here_doc)
{
	int		in_fd;
	int		out_fd;
	t_files	*curr;

	out_fd = STDOUT_FILENO;
	in_fd = STDIN_FILENO;
	curr = files;
	while (curr && curr->token != PIPE)
	{
		if (curr->token == AKATSUKI)
			break ;
		if (curr->token == AMBIGUOUS)
			return (close_file(in_fd, out_fd),
				close(file_here_doc), fatal_report(AMBIGUOUS), NOT_VALID);
		if (curr->token == OUT_FILE || curr->token == APP_FILE)
			out_fd = get_output_fd(curr, out_fd);
		else
			in_fd = get_input_fd(curr, file_here_doc, in_fd);
		if (in_fd == FAILER || out_fd == FAILER)
			return (FAILER);
		curr = curr->next;
	}
	return (out_fd);
}

static int	process_files(t_files *curr, int *in_fd,
			int *out_fd, int file_here_doc)
{
	while (curr && curr->token != PIPE)
	{
		if (curr->token == AKATSUKI)
			break ;
		if (curr->token == AMBIGUOUS)
			return (close_file(*in_fd, *out_fd),
				close(file_here_doc), fatal_report(AMBIGUOUS), 0);
		if (curr->token == OUT_FILE || curr->token == APP_FILE)
			*out_fd = get_output_fd(curr, *out_fd);
		else
			*in_fd = get_input_fd(curr, file_here_doc, *in_fd);
		if (*in_fd == -1 || *out_fd == -1)
			return (close_file(*in_fd, *out_fd), close(file_here_doc), 0);
		curr = curr->next;
	}
	return (1);
}

int	open_cmd_io_files(t_files *files, int file_here_doc)
{
	int		in_fd;
	int		out_fd;
	int		result;

	in_fd = STDIN_FILENO;
	out_fd = STDOUT_FILENO;
	result = process_files(files, &in_fd, &out_fd, file_here_doc);
	if (!result)
		return (0);
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close_file(in_fd, 0);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close_file(out_fd, 0);
	}
	close(file_here_doc);
	return (1);
}
