/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_her_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 15:03:37 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/25 21:50:12 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	stored_herd_doc(t_info *info_cmd)
{
	int			i;
	t_stack		*current;

	if (!info_cmd->info)
		return (FAILER);
	current = info_cmd->info;
	i = 0;
	while (current && current->token != ERROR)
	{
		handle_her_doc(&current, info_cmd, i);
		if (current && current->token == PIPE)
			i++;
		set_final_limiter(current, &info_cmd->here_doc, info_cmd->temp_error);
		current = current->next;
	}
	return (0);
}
