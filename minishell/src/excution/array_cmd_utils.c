/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_cmd_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:18:48 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/27 13:51:34 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	**array_cmd(t_stack *info_cmd)
{
	int		count_node;
	char	**words;
	int		i;
	t_stack	*current;

	if (!info_cmd)
		return (NULL);
	count_node = lstsize(info_cmd);
	words = ft_calloc((count_node + 1), sizeof(char *));
	if (!words)
		return (NULL);
	current = info_cmd;
	i = 0;
	while (current && i < count_node)
	{
		words[i] = ft_strjoin(words[i], current->word, 1);
		if (!words[i])
			return (free_array(words));
		if (current->is_space || !current->next
			|| current->next->token == PIPE)
			i++;
		current = current->next;
	}
	words[count_node] = NULL;
	return (words);
}

char	update_underscore_value(t_env **export_var,
		t_info_cmd *s_info_cmd, int is_pipe)
{
	if (is_pipe == 1)
		return (update_or_add_env(export_var, "_",
				get_last_node(s_info_cmd->cmd), 0));
	return (update_or_add_env(export_var, "_", "", 0));
}
