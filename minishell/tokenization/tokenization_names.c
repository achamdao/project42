/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_names.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:15:33 by achamdao          #+#    #+#             */
/*   Updated: 2025/05/04 11:53:28 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

short	is_quote_pars(short quote, int flage_quote, t_stack **stack)
{
	if (quote == '\'' && !flage_quote)
	{
		(*stack)->token = OPEN_S_Q;
		flage_quote = OPEN_S_Q;
	}
	else if (quote == '\"' && !flage_quote)
	{
		(*stack)->token = OPEN_D_Q;
		flage_quote = OPEN_D_Q;
	}
	else
	{
		if (flage_quote == OPEN_S_Q && quote == '\'')
		{
			flage_quote = NONE;
			(*stack)->token = CLOSE_S_Q;
		}
		else if (flage_quote == OPEN_D_Q && quote == '\"')
		{
			flage_quote = NONE;
			(*stack)->token = CLOSE_D_Q;
		}
	}
	return (flage_quote);
}

char	uniform_tokenize_stack(t_stack **stack, short token)
{
	t_stack	*current;

	current = *stack;
	while (current)
	{
		(current)->token = token;
		current = current->next;
	}
	return (0);
}

char	is_var(char *word)
{
	int	i;

	if (!word)
		return (FAILER);
	i = 0;
	while (word[i])
	{
		if (word[i] == '$')
		{
			i++;
			if ((!ft_isalpha(word[i]) && word[i] != '_' && word[i] != '?')
				|| word[i] == '\0')
				;
			else
				return (1);
		}
		else
			i++;
	}
	return (0);
}

char	complete_token_name(t_stack **stack, short *flag)
{
	if (name_of_string((*stack)->word, *flag) == SINGLE_QT)
		*flag = is_quote_pars(SINGLE_QT, *flag, stack);
	else if (name_of_string((*stack)->word, *flag) == PIPE && !*flag)
		(*stack)->token = PIPE;
	else
		(*stack)->token = name_of_string((*stack)->word, *flag);
	return (0);
}

short	token_name(t_stack **stack)
{
	t_stack	*current;
	short	flag;

	current = *stack;
	flag = 0;
	while (current)
	{
		if (name_of_string((current)->word, flag) == WORD
			&& is_var((current)->word) == 1 && (!(current)->prev
				|| ((current)->prev && (current)->prev->token != OPEN_S_Q)))
			((current))->token = VAR;
		else if (name_of_string(current->word, flag) == WORD
			&& is_var(current->word) != 1 && (!(current)->prev
				|| ((current)->prev && (current)->prev->token == PIPE)))
			(current)->token = CMD;
		else if (name_of_string(current->word, flag) == DOUBLE_QT)
			flag = is_quote_pars(DOUBLE_QT, flag, &current);
		else
			complete_token_name(&current, &flag);
		current = current->next;
	}
	return (SUCCESS);
}
