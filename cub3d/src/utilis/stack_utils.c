/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:27:53 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 14:30:06 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	move_to_next_pipe(t_stack **stack)
{
	if (!stack || !*stack)
		return ;
	while (*stack && (*stack)->token != PIPE)
		*stack = (*stack)->next;
	if (*stack && (*stack)->token == PIPE)
		*stack = (*stack)->next;
}

t_files	*extract_files_for_current_cmd(t_files **files)
{
	t_files	*head;
	t_files	*current;

	current = *files;
	head = *files;
	while (current && current->token != PIPE)
		current = current->next;
	if (current)
	{
		*files = current->next;
		current->next = NULL;
	}
	else
		*files = NULL;
	return (head);
}

void	cleanup_after_execution(t_data *data)
{
	pop_to_limiter(&data->stack);
}
