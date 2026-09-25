/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   override_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:37:23 by achamdao          #+#    #+#             */
/*   Updated: 2025/05/07 14:42:20 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	word_can_concat(t_stack *node)
{
	if (node->token == WORD || node->token == EMPTY_STR
		|| node->token == VAR)
		return (1);
	return (0);
}

int	is_valid_token(t_stack *node, short token)
{
	if (!node)
		return (0);
	if (word_can_concat(node))
	{
		if (node->prev && node->prev->token == token && node->prev->is_space)
			return (0);
		else
			return (1);
	}
	else if ((node->token >= OPEN_S_Q
			&& node->token <= CLOSE_D_Q))
	{
		if ((node->token == CLOSE_D_Q
				|| node->token == CLOSE_S_Q) && node->is_space)
			return (0);
		if (node->next && !node->next->is_space)
			return (1);
	}
	else
		return (0);
	return (1);
}

void	check_and_concat(t_stack *current, char **str, short token)
{
	if (!current)
		return ;
	if (is_valid_token(current, token))
	{
		if (!((current)->token >= OPEN_S_Q && (current)->token <= CLOSE_D_Q))
		{
			*str = ft_strjoin(*str, (current)->word, 1);
			(current)->token = token;
		}
	}
}

char	*concatenate_word(t_stack **stack, short token)
{
	char	*str;
	t_stack	*new;

	str = NULL;
	new = *stack;
	while (new && is_valid_token(new, token))
	{
		check_and_concat(new, &str, token);
		(new) = (new)->next;
	}
	check_and_concat(*stack, &str, token);
	return (str);
}

char	expansion_var(t_info *info, t_env *env)
{
	t_stack	*current;
	char	*temp;

	current = info->info;
	if (!current)
		return (FAILER);
	while (current)
	{
		if (current->token == VAR)
		{
			temp = override_var(env, current->word, 0, info->error);
			if (!ft_strcmp(temp, "") && current->next
				&& current->next->token == CLOSE_D_Q)
				current->token = EMPTY_STR;
			if (current->next && current->next->token == CLOSE_D_Q)
				current->token = WORD;
			current->word = temp;
		}
		current = current->next;
	}
	return (-2);
}
