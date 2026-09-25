/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty_command_fix.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 16:47:30 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/25 21:36:24 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	free_node(void *ptr, char *str)
{
	free(str);
	free(ptr);
	return (0);
}

char	check_for_push(t_stack *current)
{
	if ((!current->prev || !current->next) && current->token == PIPE)
		return (0);
	if (current->next && current->next->token == PIPE && current->token == PIPE)
		return (0);
	return (1);
}

char	fix_unconnected_pipes(t_stack *current, t_stack **temp
	, t_stack *new_node, char flag)
{
	if (flag == 1)
	{
		if (append_to_end(temp, new_node) == FAILER)
			return (FAILER);
		if (append_to_end(temp, current) == FAILER)
			return (FAILER);
		if (append_to_end(temp, new_node) == FAILER)
			return (FAILER);
	}
	else if (flag == 2)
	{
		if (append_to_end(temp, new_node) == FAILER)
			return (FAILER);
		if (append_to_end(temp, current) == FAILER)
			return (FAILER);
	}
	else if (flag == 3)
	{
		if (append_to_end(temp, current) == FAILER)
			return (FAILER);
		if (append_to_end(temp, new_node) == FAILER)
			return (FAILER);
	}
	return (0);
}

char	push_word_btw_empty_pipe(t_stack *current
	, t_stack **temp, t_stack *new_node)
{
	if (!current->prev && !current->next && current->token == PIPE)
		return (fix_unconnected_pipes(current, temp, new_node, 1));
	else if (!current->prev && current->next
		&& current->next->token == PIPE)
		return (fix_unconnected_pipes(current, temp, new_node, 1));
	else if (!current->prev && current->token == PIPE)
		return (fix_unconnected_pipes(current, temp, new_node, 2));
	else if (!current->next && current->token == PIPE)
		return (fix_unconnected_pipes(current, temp, new_node, 3));
	else if (current->next && current->next->token == PIPE
		&& current->token == PIPE)
		return (fix_unconnected_pipes(current, temp, new_node, 3));
	return (0);
}

char	process_empty_btw_pipe(t_stack *current, t_stack **temp)
{
	t_stack	*new_node;

	new_node = NULL;
	if (!check_for_push(current))
	{
		if (node_akatsuky(&new_node) == FAILER)
			return (FAILER);
		new_node->token = AKATSUKI;
		if (push_word_btw_empty_pipe(current, temp, new_node) == FAILER)
			return (free_node(new_node, new_node->word), FAILER);
		free_node(new_node, new_node->word);
	}
	else
		if (append_to_end(temp, current) == FAILER)
			return (FAILER);
	return (0);
}
