/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_of_word.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:52:09 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/19 21:34:23 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

short	complete_named_meta_char(char *str, int flag)
{
	if (!ft_strcmp(str, "`") && !flag)
		return (META_BACKTICK);
	else if (!ft_strcmp(str, "~") && !flag)
		return (META_TILDE);
	else if (!ft_strcmp(str, "!") && !flag)
		return (META_EXCLAMATION);
	else if (!ft_strcmp(str, "#") && !flag)
		return (META_HASH);
	else if (!ft_strcmp(str, "*") && !flag)
		return (META_STAR);
	else if (!ft_strcmp(str, "?") && !flag)
		return (META_QUESTION);
	return (WORD);
}

short	named_meta_char(char *str, int flag)
{
	if (!ft_strcmp(str, "&") && !flag)
		return (META_AMPERSAND);
	else if (!ft_strcmp(str, ";") && !flag)
		return (META_SEMICOLON);
	else if (!ft_strcmp(str, "(") && !flag)
		return (META_LPAREN);
	else if (!ft_strcmp(str, ")") && !flag)
		return (META_RPAREN);
	else if (!ft_strcmp(str, "{") && !flag)
		return (META_LBRACE);
	else if (!ft_strcmp(str, "}") && !flag)
		return (META_RBRACE);
	else if (!ft_strcmp(str, "[") && !flag)
		return (META_LBRACKET);
	else if (!ft_strcmp(str, "]") && !flag)
		return (META_RBRACKET);
	else if (!ft_strcmp(str, "\\") && !flag)
		return (META_BACKSLASH);
	else
		return (complete_named_meta_char(str, flag));
	return (WORD);
}

short	name_of_string(char *str, int flag)
{
	if (!str)
		return (NONE);
	if (!ft_strcmp(str, "<") && !flag)
		return (INP_RED);
	else if (!ft_strcmp(str, ">") && !flag)
		return (OUT_RED);
	else if (!ft_strcmp(str, "|") && !flag)
		return (PIPE);
	else if (!ft_strcmp(str, "\"") && (flag == OPEN_D_Q || !flag))
		return (DOUBLE_QT);
	else if (!ft_strcmp(str, "\'") && (flag == OPEN_S_Q || !flag))
		return (SINGLE_QT);
	else if (!ft_strcmp(str, ""))
		return (EMPTY_STR);
	else
		return (named_meta_char(str, flag));
	return (WORD);
}
