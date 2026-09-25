/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_syntax_error.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 20:03:00 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/25 22:01:48 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

short	close_open_qoute(short token, short flag)
{
	if (token == OPEN_D_Q || token == OPEN_S_Q)
		flag = token;
	if (token == CLOSE_D_Q || token == CLOSE_S_Q)
		flag = 0;
	return (flag);
}

short	complete_analyse_token(t_stack **stack, int item)
{
	if (check_valid_redirection(*stack) != NONE)
	{
		(*stack)->token = ERROR;
		return (item);
	}
	else if (check_valid_pipe(*stack) != NONE)
	{
		(*stack)->token = ERROR;
		return (item);
	}
	else if (check_valid_syntax(*stack) != NONE)
	{
		(*stack)->token = ERROR;
		return (item);
	}
	return (-2);
}

char	error_quote(int item, t_stack **stack, short flag)
{
	int		i;
	t_stack	*current;

	current = *stack;
	i = 0;
	while (current)
	{
		if (i == item)
		{
			current->token = ERROR;
			break ;
		}
		i++;
		current = current->next;
	}
	return (print_error("bash: syntax error:`", flag), item);
}

char	analyse_token(t_stack **stack)
{
	t_stack	*current;
	int		catch_item;
	short	flag;
	int		item;
	int		error;

	current = *stack;
	item = 0;
	while (current)
	{
		error = complete_analyse_token(&current, item);
		if (error != -2)
			return (error);
		flag = close_open_qoute(current->token, flag);
		if (flag == OPEN_D_Q || flag == OPEN_S_Q)
			catch_item = item;
		item++;
		current = current->next;
	}
	if (flag == OPEN_D_Q || flag == OPEN_S_Q)
		return (error_quote(catch_item, stack, flag));
	return (-2);
}
