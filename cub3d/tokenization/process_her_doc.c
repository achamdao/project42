/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_her_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:44:46 by achamdao          #+#    #+#             */
/*   Updated: 2025/05/03 15:46:07 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_here_doc	*get_lstlast(t_here_doc *her_doc)
{
	if (!her_doc)
		return (NULL);
	while (her_doc->next)
		her_doc = her_doc->next;
	return (her_doc);
}

char	set_final_limiter(t_stack *stack
	, t_here_doc **hre_doc, short temp_error)
{
	t_here_doc	*current;

	if (!hre_doc || !*hre_doc)
		return (0);
	current = get_lstlast(*hre_doc);
	if (stack && stack->token == PIPE && temp_error != 258)
		current->last_limiter = 1;
	else if ((!stack || !stack->next) && temp_error != 258)
		current->last_limiter = 1;
	else if (stack->next && stack->next->token == ERROR)
		current->last_limiter = 1;
	return (0);
}

char	check_quote_exists(t_stack *stack)
{
	char	quote;

	quote = 0;
	while (stack && (stack->token == HER_FILE
			|| (stack->token >= OPEN_S_Q && stack->token <= CLOSE_D_Q)))
	{
		if (!stack->is_space && stack->next)
			quote = 1;
		stack = stack->next;
	}
	return (quote);
}

char	process_her_doc(t_info *info_cmd, char *word, int i, t_stack *stack)
{
	t_here_doc	*current_her_doc;

	if (info_cmd->error == 258)
		info_cmd->is_here_doc[i] = FAILER;
	else
		info_cmd->is_here_doc[i] = 1;
	if (push_here_doc(&info_cmd->here_doc, word) == FAILER)
		return (FAILER);
	current_her_doc = get_lstlast(info_cmd->here_doc);
	if (current_her_doc)
	{
		current_her_doc->quote_exists = check_quote_exists(stack);
		current_her_doc->last_limiter = 0;
	}
	return (0);
}

char	handle_her_doc(t_stack **stack, t_info *info_cmd, int i)
{
	char	*word;

	if ((*stack)->token == HERE_DOC && (*stack)->next
		&& (*stack)->next->token == ERROR)
		(*stack)->token = GARBAGE_VALUE;
	else if ((*stack)->token == INP_RED && (*stack)->next
		&& (*stack)->next->token == INP_RED)
	{
		(*stack)->next->token = HERE_DOC;
		(*stack)->token = GARBAGE_VALUE;
	}
	else if ((*stack)->token == HERE_DOC)
	{
		word = concatenate_word(&(*stack)->next, HER_FILE);
		if (process_her_doc(info_cmd, word, i, (*stack)->next) == FAILER)
			return (FAILER);
		free(word);
	}
	return (0);
}
