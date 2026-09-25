/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:17:56 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/27 13:31:54 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

short	is_quote(char quote, int flage_quote)
{
	if (quote == '\'' && !flage_quote)
		flage_quote = SINGLE_QT;
	else if (quote == '\"' && !flage_quote)
		flage_quote = DOUBLE_QT;
	else
	{
		if (flage_quote == SINGLE_QT && quote == '\'')
			flage_quote = NONE;
		else if (flage_quote == DOUBLE_QT && quote == '\"')
			flage_quote = NONE;
	}
	return (flage_quote);
}
