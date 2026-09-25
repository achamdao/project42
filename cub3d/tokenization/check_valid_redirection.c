/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_redirection.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:41:00 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/29 18:20:51 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	length_red(t_stack *stack, short *token)
{
	int	i;

	i = 0;
	*token = NONE;
	while (stack && (stack->token == INP_RED || stack->token == OUT_RED))
	{
		if (i == 2)
			*token = stack->token;
		stack = stack->next;
		i++;
	}
	return (i);
}

short	complete_check_valid_redirection(t_stack *current, char *str)
{
	if (current->prev->token != current->token)
		return (print_error(str, current->token));
	else if ((current->prev->token == INP_RED
			|| current->prev->token == OUT_RED)
		&& current->prev->is_space > 0 && (current->token == INP_RED
			|| current->token == OUT_RED))
		return (print_error(str, current->token));
	else if ((current->token == INP_RED
			|| current->token == OUT_RED) && !current->next)
		return (print_error(str, NEW_LINE));
	return (0);
}

short	complete_check_valid_redirection1(t_stack *current, char *str
		, short token)
{
	if (length_red(current->prev, &token) > 3)
	{
		if (token == OUT_RED)
			return (print_error(str, APPEND));
		else
			return (print_error(str, HERE_DOC));
	}
	else
		return (print_error(str, token));
	return (0);
}

short	check_valid_redirection(t_stack *current)
{
	short	token;
	char	*str;

	str = "bash: syntax error near unexpected token `";
	if ((current->token == INP_RED
			|| current->token == OUT_RED) && !current->next)
		return (print_error(str, NEW_LINE));
	if (current->prev)
	{
		if (!((INP_RED <= current->prev->token)
				&& (INP_RED <= current->token)))
			return (0);
		if (length_red(current->prev, &token) > 2)
			return (complete_check_valid_redirection1(current, str, token));
		else
			return (complete_check_valid_redirection(current, str));
	}
	return (0);
}
