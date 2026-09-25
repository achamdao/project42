/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cleaner_stack.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 20:53:26 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/28 20:59:06 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	is_valid(t_stack *current)
{
	char	result;

	result = (current->token == WORD
			|| current->token == CMD
			|| current->token == VAR
			|| current->token == EMPTY_STR
			|| current->token == PIPE);
	return (result);
}

char	inherit_is_space(t_stack *current, t_stack **cleaner_stack)
{
	if (current->next && !is_valid(current->next))
		get_last_node_cleaner(cleaner_stack, current->next->is_space);
	if (current->next && current->next->token == VAR
		&& !ft_strcmp(current->next->word, ""))
		get_last_node_cleaner(cleaner_stack, current->next->is_space);
	return (0);
}

char	convert_empty_var_to_garbage(t_stack **current)
{
	if ((*current)->token == VAR && !ft_strcmp((*current)->word, ""))
		(*current)->token = GARBAGE_VALUE;
	return (0);
}

char	check_valid_valid(t_stack *current)
{
	return (is_valid(current));
}

char	cleaner_stack(t_info *info)
{
	t_stack	*current;
	t_stack	*clean_stack;

	clean_stack = NULL;
	current = info->info;
	while (current)
	{
		convert_empty_var_to_garbage(&current);
		if (is_valid(current))
			if (append_to_end(&clean_stack, current) == FAILER)
				return (FAILER);
		inherit_is_space(current, &clean_stack);
		current = current->next;
	}
	ft_stack_clear(&info->info);
	info->info = clean_stack;
	return (add_node_btw_empty_pipe(info));
}
