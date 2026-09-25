/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_stored_file.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 21:09:35 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/27 13:32:41 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	check_empty_node(t_files *current)
{
	if ((!current->prev || !current->next) && current->token == PIPE)
		return (0);
	if (current->next && current->next->token == PIPE && current->token == PIPE)
		return (0);
	return (1);
}

char	fixe_stack(t_files *current, t_files **temp)
{
	if (!current->prev && !current->next && current->token == PIPE)
		return (add_pipe(temp, current->file, 3));
	else if (!current->prev && current->next && current->next->token == PIPE)
		return (add_pipe(temp, current->file, 3));
	if (!current->next && current->token == PIPE)
		return (add_pipe(temp, current->file, 2));
	else if (!current->prev && current->token == PIPE)
		return (add_pipe(temp, current->file, 1));
	else if (current->next && current->next->token == PIPE
		&& current->token == PIPE)
		return (add_pipe(temp, current->file, 2));
	return (0);
}

char	complete_fixe_node_empty(t_files *current, t_files **temp)
{
	if (!check_empty_node(current))
	{
		if (fixe_stack(current, temp) == FAILER)
			return (FAILER);
	}
	else
	{
		if (push_file(temp, current->file
				, current->token) == FAILER)
			return (FAILER);
	}
	return (0);
}

char	fixe_node_empty(t_files **files)
{
	t_files	*current;
	t_files	*temp;

	current = *files;
	temp = NULL;
	while (current)
	{
		if (complete_fixe_node_empty(current, &temp) == FAILER)
			return (FAILER);
		current = current->next;
	}
	ft_files_clear(files);
	*files = temp;
	if (!*files)
	{
		if (push_file(files, "AKATSUKI"
				, AKATSUKI) == FAILER)
			return (FAILER);
	}
	return (0);
}
