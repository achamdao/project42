/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handel_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:35:05 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/09 20:49:23 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	open_file_safe(t_stack *stack)
{
	int	count;

	if (stack->token == VAR)
	{
		count = count_word_var(stack->word, " \t");
		if ((count >= 2) || (!count && stack->is_space))
			return (NOT_VALID);
		else if ((!count && !stack->next))
			return (NOT_VALID);
		else
			return (0);
	}
	else
		return (0);
	return (0);
}

char	stored_file(t_files **files, char *word, short token)
{
	if (push_file(files, word, token) == FAILER)
		return (FAILER);
	return (0);
}

char	make_file_str(t_files **files, t_stack **stack, short token)
{
	char	*word;

	if (!stack)
		return (0);
	word = concatenate_word(stack, token);
	if (stored_file(files, word, token) == FAILER)
		return (FAILER);
	free(word);
	return (0);
}

char	complete_handle_redirection(t_stack **stack
	, t_info *info_cmd, t_files **files)
{
	if ((*stack)->token == OUT_RED && info_cmd->temp_error != 258)
	{
		if (make_file_str(files, &(*stack)->next, OUT_FILE) == FAILER)
			return (FAILER);
	}
	else if ((*stack)->token == APPEND && info_cmd->temp_error != 258)
	{
		if (make_file_str(files, &(*stack)->next, APP_FILE) == FAILER)
			return (FAILER);
	}
	else if ((*stack)->token == INP_RED
		&& info_cmd->temp_error != 258)
	{
		if (make_file_str(files, &(*stack)->next, IN_FILE) == FAILER)
			return (FAILER);
	}
	return (0);
}

char	handle_redirection(t_stack **stack, t_info *info_cmd, t_files **files)
{
	if ((*stack)->token == OUT_RED && (*stack)->next
		&& (*stack)->next->token == OUT_RED && info_cmd->temp_error != 258)
	{
		(*stack)->next->token = APPEND;
		(*stack)->token = GARBAGE_VALUE;
	}
	else if (((*stack)->token == APPEND || (*stack)->token == INP_RED
			|| (*stack)->token == OUT_RED) && (*stack)->next
		&& open_file_safe((*stack)->next) == NOT_VALID
		&& info_cmd->temp_error != 258)
	{
		if (make_file_str(files, &(*stack)->next, AMBIGUOUS) == FAILER)
			return (FAILER);
		info_cmd->error = 1;
	}
	else
		return (complete_handle_redirection(stack, info_cmd, files));
	return (0);
}
