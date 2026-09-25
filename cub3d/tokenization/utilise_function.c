/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilise_function.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 13:44:16 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/27 13:32:48 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	allocate_array(t_info *info_cmd)
{
	info_cmd->number_cmd = count_pipe(info_cmd->info);
	if (info_cmd->number_cmd == FAILER)
		return (FAILER);
	info_cmd->number_cmd += 1;
	info_cmd->is_here_doc = ft_calloc(info_cmd->number_cmd, sizeof(int));
	if (!info_cmd->is_here_doc)
		return (FAILER);
	if (info_cmd->number_cmd == FAILER)
		return (FAILER);
	return (0);
}

char	add_pipe_pair(t_files **temp, char *pipe)
{
	if (push_file(temp, "AKATSUKI", AKATSUKI) == FAILER)
		return (FAILER);
	if (push_file(temp, pipe, PIPE) == FAILER)
		return (FAILER);
	if (push_file(temp, "AKATSUKI", AKATSUKI) == FAILER)
		return (FAILER);
	return (0);
}

char	add_pipe(t_files **temp, char *pipe, char flag)
{
	if (flag == 1)
	{
		if (push_file(temp, "AKATSUKI", AKATSUKI) == FAILER)
			return (FAILER);
		if (push_file(temp, pipe, PIPE) == FAILER)
			return (FAILER);
	}
	else if (flag == 2)
	{
		if (push_file(temp, pipe, PIPE) == FAILER)
			return (FAILER);
		if (push_file(temp, "AKATSUKI", AKATSUKI) == FAILER)
			return (FAILER);
	}
	else if (flag == 3)
		add_pipe_pair(temp, pipe);
	return (0);
}

void	free_resources(t_info *info_cmd)
{
	if (info_cmd->is_here_doc)
	{
		free(info_cmd->is_here_doc);
		info_cmd->is_here_doc = NULL;
	}
}

void	clear_struct(t_info *info)
{
	clear_here_doc(&info->here_doc);
	ft_stack_clear(&info->info);
	free_resources(info);
	ft_files_clear(&info->file);
}
