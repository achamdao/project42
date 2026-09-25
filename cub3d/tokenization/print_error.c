/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:44:58 by achamdao          #+#    #+#             */
/*   Updated: 2025/05/03 20:56:15 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

short	complete_print_error3(short token)
{
	if (token == META_STAR)
		ft_putchar_fd('*', 2);
	else if (token == META_QUESTION)
		ft_putchar_fd('?', 2);
	else if (token == META_COLON)
		ft_putchar_fd(':', 2);
	else if (token == META_RBRACKET)
		ft_putchar_fd(']', 2);
	else if (token == META_BACKSLASH)
		ft_putchar_fd('\\', 2);
	else if (token == META_BACKTICK)
		ft_putchar_fd('`', 2);
	ft_putendl_fd("\'", 2);
	return (token);
}

short	complete_print_error2( short token)
{
	if (token == META_AMPERSAND)
		ft_putchar_fd('&', 2);
	else if (token == META_SEMICOLON)
		ft_putchar_fd(';', 2);
	else if (token == META_LPAREN)
		ft_putchar_fd('(', 2);
	else if (token == META_RPAREN)
		ft_putchar_fd(')', 2);
	else if (token == META_LBRACE)
		ft_putchar_fd('{', 2);
	else if (token == META_RBRACE)
		ft_putchar_fd('}', 2);
	else if (token == META_LBRACKET)
		ft_putchar_fd('[', 2);
	else
		return (complete_print_error3(token));
	ft_putendl_fd("\'", 2);
	return (token);
}

short	complete_print_error1(short token)
{
	if (token == META_TILDE)
		ft_putchar_fd('~', 2);
	else if (token == META_EXCLAMATION)
		ft_putchar_fd('!', 2);
	else if (token == META_HASH)
		ft_putchar_fd('#', 2);
	else if (token == META_PERCENT)
		ft_putchar_fd('%', 2);
	else if (token == META_CARET)
		ft_putchar_fd('^', 2);
	else if (token == OPEN_D_Q)
		ft_putstr_fd("unclosed double quote `\" ", 2);
	else if (token == OPEN_S_Q)
		ft_putstr_fd("unclosed single quote `\' ", 2);
	else
		return (complete_print_error2(token));
	ft_putendl_fd("\'", 2);
	return (token);
}

short	print_error(char *error, short token)
{
	ft_putstr_fd(error, 2);
	if (token == PIPE)
		ft_putchar_fd('|', 2);
	else if (token == SINGLE_QT)
		ft_putchar_fd('\'', 2);
	else if (token == DOUBLE_QT)
		ft_putchar_fd('\"', 2);
	else if (token == INP_RED)
		ft_putchar_fd('<', 2);
	else if (token == OUT_RED)
		ft_putchar_fd('>', 2);
	else if (token == APPEND)
		ft_putstr_fd(">>", 2);
	else if (token == HERE_DOC)
		ft_putstr_fd("<<", 2);
	else if (token == NEW_LINE)
		ft_putstr_fd("newline", 2);
	else if (token == D_PIPE)
		ft_putstr_fd("||", 2);
	else
		return (complete_print_error1(token));
	ft_putendl_fd("\'", 2);
	return (token);
}
