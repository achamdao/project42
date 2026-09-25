/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component_stack_cleaner.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 14:14:06 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/27 23:05:14 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_stack	*copy_stack_node(t_stack *node)
{
	t_stack	*new_node;

	if (!node)
		return (NULL);
	new_node = malloc(sizeof(t_stack));
	if (!new_node)
		return (NULL);
	new_node->word = ft_strdup(node->word);
	if (!new_node->word)
	{
		free(new_node);
		return (NULL);
	}
	new_node->token = node->token;
	new_node->is_space = node->is_space;
	new_node->prev_is_space = node->prev_is_space;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

char	append_to_end(t_stack **head, t_stack *node)
{
	t_stack	*tail;
	t_stack	*new;

	new = copy_stack_node(node);
	if (!new)
		return (FAILER);
	if (!*head)
	{
		*head = new;
		(*head)->prev = NULL;
		(*head)->next = NULL;
		return (0);
	}
	tail = *head;
	while (tail->next)
		tail = tail->next;
	tail->next = new;
	new->prev = tail;
	new->next = NULL;
	return (0);
}
