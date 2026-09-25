/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:34:03 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/03 20:34:16 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	ft_is_quote(t_stack **data, t_env *export)
{
	char	is_quote;

	is_quote = 0;
	if ((*data)->token == WORD)
		is_quote = 1;
	if (lstsize(*data) == 1)
		return (print_sorted_env(export, 1));
	while (*data && !(*data)->is_space)
	{
		if ((*data)->token == EMPTY_STR)
			is_quote = 1;
		*data = (*data)->next;
	}
	if (!*data)
		return (0);
	if ((*data)->token == EMPTY_STR)
		is_quote = 1;
	*data = (*data)->next;
	return (is_quote);
}

char	ft_export(t_stack *data, t_env **export)
{
	char	error;
	char	is_quote;

	is_quote = ft_is_quote(&data, *export);
	error = 0;
	while (data && data->word[0] != '|')
	{
		if (add_var(export, &data, is_quote))
			error = 1;
		if (error == -1)
			return (-1);
		if (data && data->word[0] != '|')
			data = data->next;
	}
	return (error);
}
