/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 08:45:54 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 09:51:17 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	check_char(char *str, char c)
{
	if (!str)
		return (0);
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	if (c == '\0')
		return (1);
	return (0);
}

int	skeep_sep(char *str, char *sep, int token)
{
	int	i;

	if (!str || token)
		return (0);
	i = 0;
	while (str[i] && (check_char(sep, str[i])))
		i++;
	return (i);
}

int	length_words(enum e_token *tmp_token, enum e_token *token
, char *sep, char *str)
{
	int	i;

	i = 0;
	if (*tmp_token != *token && (str[i] == '"' || str[i] == '\''))
	{
		*tmp_token = *token;
		return (1);
	}
	if (check_char(sep, str[i]) && *token == NONE
		&& (str[i] != '"' && str[i] != '\''))
		return (1);
	while (str[i])
	{
		*tmp_token = *token;
		*token = is_quote(str[i], *token);
		if (check_char(sep, str[i]) && ((*tmp_token != *token) || !(*token)))
			return (i);
		i++;
	}
	return (i);
}

char	complete_lexer(t_stack **s_lexer
, char *cmd_line, int **start_end, int token)
{
	int		skeep_space;
	char	*word;

	word = ft_substr(cmd_line, (*start_end)[0], (*start_end)[1]);
	if (!word)
		return (FAILER);
	if (!word[0] && token)
		return (free_and_null((void **)&word), 0);
	(*start_end)[0] += (*start_end)[1];
	skeep_space = skeep_sep(&cmd_line[(*start_end)[0]], " \t", token);
	if (push(s_lexer, word, skeep_space) == FAILER)
		return (free_and_null((void **)&word), FAILER);
	(*start_end)[0] += skeep_space;
	return (0);
}

char	lexer(char *cmd_line, char *sep, t_stack **s_lexer)
{
	int				*start_end;
	enum e_token	tmp_token;
	enum e_token	token;

	if (!cmd_line)
		return (FAILER);
	token = NONE;
	tmp_token = NONE;
	start_end = ft_calloc(2, sizeof(int));
	if (!start_end)
		return (FAILER);
	while (cmd_line[start_end[0]])
	{
		start_end[1] = length_words(&tmp_token, &token, sep,
				&cmd_line[start_end[0]]);
		if (complete_lexer(s_lexer, cmd_line, &start_end, token) == FAILER)
			return (free_and_null((void **)&start_end), FAILER);
	}
	return (free_and_null((void **)&start_end), 0);
}
