/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 09:31:08 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/29 11:57:14 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	execute_commands(t_info *info, t_data *data)
{
	if (info->number_cmd == 1)
		info->error = run_simple_cmd(info, data);
	else
		info->error = pipe_line(info, data);
	if (info->error == -1)
		return (info->error);
	info->info = NULL;
	return (0);
}

char	start(t_info *info, t_env **export_var)
{
	t_data	data;
	int		result;
	t_stack	*stack;

	data.user_stack = *export_var;
	stack = info->info;
	data.stack = info->info;
	data.files = info->file;
	if (!info->info)
		return (0);
	if (info->is_here_doc && info->error == 258 && info->is_here_doc[0] == -1)
		return (run_here_doc_fack(&info->here_doc), 0);
	if (info->error == -1)
		return (info->error);
	result = execute_commands(info, &data);
	*export_var = data.user_stack;
	info->info = stack;
	info->file = NULL;
	return (result);
}
