/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:14:15 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/26 17:06:34 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	count_word_var(char *str, char *sep)
{
	int	i;
	int	length;
	int	count;

	if (!str)
		return (0);
	i = 0;
	length = 0;
	count = 0;
	while (str[i])
	{
		if (check_char(sep, str[i]))
		{
			if (length != 0)
				count++;
			length = 0;
		}
		else
			length++;
		i++;
	}
	if (length != 0)
		count++;
	return (count);
}

int	count_pipe(t_stack *current_stack)
{
	int	count;

	if (!current_stack)
		return (FAILER);
	count = 0;
	while (current_stack)
	{
		if (current_stack->token == PIPE)
			count++;
		current_stack = current_stack->next;
	}
	return (count);
}

char	stored_pipe_empty_cmd( t_stack *current, t_files **current_file)
{
	if (current->token == PIPE)
	{
		if (push_file(current_file, current->word, PIPE) == FAILER)
			return (FAILER);
	}
	else if (current->token == HERE_DOC)
	{
		if (push_file(current_file, "HERE_DOC", HERE_DOC) == FAILER)
			return (FAILER);
	}
	return (0);
}

char	parsing_redirection(t_info *info_cmd)
{
	t_stack	*current;

	if (!info_cmd->info)
		return (FAILER);
	current = info_cmd->info;
	info_cmd->file = NULL;
	while (current)
	{
		if (handle_redirection(&current, info_cmd, &info_cmd->file) == FAILER)
			return (FAILER);
		if (stored_pipe_empty_cmd(current, &info_cmd->file) == FAILER)
			return (FAILER);
		current = current->next;
	}
	return (fixe_node_empty(&info_cmd->file));
}
