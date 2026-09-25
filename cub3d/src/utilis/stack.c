/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:12:43 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 14:31:15 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	stack_push(t_env **env, char *nam_var, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return ;
	new_node->name_var = ft_strdup(nam_var);
	new_node->value = ft_strdup(value);
	new_node->next = *env;
	*env = new_node;
}

int	lstsize(t_stack *lst)
{
	int	i;

	i = 0;
	while (lst && lst->token != PIPE)
	{
		if (lst->is_space || !lst->next || lst->next->token == PIPE)
			i++;
		lst = lst->next;
	}
	return (i);
}

char	push_here_doc(t_here_doc **head, char *limiter)
{
	t_here_doc	*new_node;
	t_here_doc	*current;

	new_node = malloc(sizeof(t_here_doc));
	if (!new_node)
		return (FAILER);
	new_node->limeter = ft_strdup(limiter);
	if (!new_node->limeter)
	{
		free_and_null((void **)&new_node);
		return (FAILER);
	}
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
	new_node->next = NULL;
	return (0);
}

t_here_doc	*pop_here_doc(t_here_doc **stack)
{
	t_here_doc	*top;
	t_here_doc	*next_node;

	if (!stack || !*stack)
		return (NULL);
	top = *stack;
	next_node = top->next;
	free_and_null((void **)&top->limeter);
	free_and_null((void **)&top);
	*stack = next_node;
	return (next_node);
}

void	ft_stack_pop(t_stack **stack)
{
	t_stack	*top;

	if (!stack || !*stack)
		return ;
	top = *stack;
	*stack = top->next;
	if (*stack)
		(*stack)->prev = NULL;
	top->next = NULL;
	free_and_null((void **)&top->word);
	free_and_null((void **)&top);
}
