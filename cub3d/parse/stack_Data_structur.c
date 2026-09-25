/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_Data_structur.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:59:21 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/27 23:04:33 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_stack	*add_new_list(char *data, int is_space)
{
	t_stack	*newlist;

	newlist = malloc(sizeof(t_stack));
	if (!newlist)
		return (NULL);
	newlist->word = data;
	newlist->next = NULL;
	newlist->prev = NULL;
	newlist->is_space = is_space;
	newlist->prev_is_space = 0;
	newlist->token = NONE;
	return (newlist);
}

t_stack	*lstlast(t_stack *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	lstadd_back(t_stack **lst, t_stack *new)
{
	t_stack	*lstback;

	lstback = *lst;
	if (!new || !lst)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (lstback->next)
		lstback = lstback->next;
	lstback->next = new;
	new->prev = lstback;
}

char	push(t_stack **oldlist, char *data, int is_space)
{
	t_stack	*newlist;

	newlist = add_new_list(data, is_space);
	if (!newlist)
		return (FAILER);
	lstadd_back(oldlist, newlist);
	return (0);
}
