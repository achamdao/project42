/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_prompt.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 17:50:06 by achamdao          #+#    #+#             */
/*   Updated: 2025/05/03 20:55:51 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

short	check_valid_pipe(t_stack *current)
{
	char	*str;

	str = "bash: syntax error near unexpected token `";
	if (current->prev)
	{
		if (current->token == PIPE && current->prev->token == PIPE)
			return ((print_error(str, D_PIPE)));
		else if (current->token == PIPE && (current->prev->token == INP_RED
				|| current->prev->token == OUT_RED))
			return (print_error(str, PIPE));
		else if (current->token == PIPE && !current->next)
			return (print_error(str, PIPE));
	}
	else if (!current->prev && current->token == PIPE)
		return ((print_error(str, PIPE)));
	return (0);
}

short	check_valid_syntax(t_stack *current)
{
	if (current->token == META_AMPERSAND || current->token == META_SEMICOLON
		|| current->token == META_LPAREN || current->token == META_RPAREN
		|| current->token == META_LBRACE || current->token == META_RBRACE
		|| current->token == META_LBRACKET || current->token == META_RBRACKET
		|| current->token == META_BACKSLASH || current->token == META_BACKTICK
		|| current->token == META_TILDE || current->token == META_EXCLAMATION
		|| current->token == META_HASH || current->token == META_PERCENT
		|| current->token == META_CARET || current->token == META_STAR
		|| current->token == META_QUESTION || current->token == META_COLON)
	{
		return (print_error("bash: syntax error near unexpected token `"
				, current->token));
	}
	return (0);
}

int	get_item_token(t_stack *stack, short token)
{
	t_stack	*current;
	int		item;

	current = stack;
	item = 0;
	if (!current)
		return (FAILER);
	while (current)
	{
		if (current->token == token)
			return (item);
		item++;
		current = current->next;
	}
	return (-2);
}

int	length_token(t_here_doc *herdoc)
{
	t_here_doc	*current;
	int			item;

	current = herdoc;
	item = 0;
	while (current)
	{
		item++;
		current = current->next;
	}
	if (item)
		return (item);
	return (-2);
}

char	check_for_run_her_doc(t_info *info, short item_error)
{
	int	i;

	i = get_item_token(info->info, HERE_DOC);
	if (length_token(info->here_doc) > 15)
		info->temp_error = 2;
	if (item_error == -2)
		return (FAILER);
	if (i == FAILER)
		return (FAILER);
	if ((i > item_error) || i == -2)
		return (0);
	else
	{
		if (info->is_here_doc)
			info->is_here_doc[0] = FAILER;
		return (1);
	}
	return (-2);
}
