/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_empty_pipe_line.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 16:47:24 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/26 00:44:14 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	node_akatsuky(t_stack **new_node)
{
	char	*word;

	word = ft_strdup("AKATSUKI");
	if (!word)
		return (FAILER);
	if (push(new_node, word, 0) == FAILER)
		return (free(word), FAILER);
	(*new_node)->token = AKATSUKI;
	return (0);
}

char	fix_null_stack(t_stack **temp)
{
	t_stack	*new_node;

	new_node = NULL;
	if (!*temp)
	{
		if (node_akatsuky(&new_node) == FAILER)
			return (FAILER);
		new_node->token = AKATSUKI;
		if (append_to_end(temp, new_node) == FAILER)
			return (free_node(new_node, new_node->word), FAILER);
		free_node(new_node, new_node->word);
	}
	return (0);
}

char	add_node_btw_empty_pipe(t_info *info)
{
	t_stack	*current;
	t_stack	*temp;

	current = info->info;
	temp = NULL;
	while (current)
	{
		if (process_empty_btw_pipe(current, &temp) == FAILER)
			return (FAILER);
		current = current->next;
	}
	if (fix_null_stack(&temp) == FAILER)
		return (FAILER);
	ft_stack_clear(&info->info);
	info->info = temp;
	return (0);
}
