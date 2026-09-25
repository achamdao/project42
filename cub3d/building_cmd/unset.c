/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:53:24 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 15:49:32 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

static void	stack_remove_head_nodes(t_env **begin_list, char *data_ref)
{
	t_env	*tmp;

	while (*begin_list && !ft_strcmp((*begin_list)->name_var, data_ref))
	{
		tmp = *begin_list;
		*begin_list = tmp->next;
		free_and_null((void **)&tmp->value);
		free_and_null((void **)&tmp->name_var);
		free_and_null((void **)&tmp);
	}
}

static void	stack_remove_inner_nodes(t_env **begin_list, char *data_ref)
{
	t_env	*cur;
	t_env	*prev;
	t_env	*tmp;

	cur = *begin_list;
	prev = NULL;
	while (cur)
	{
		if (!ft_strcmp(cur->name_var, data_ref))
		{
			prev->next = cur->next;
			free_and_null((void **)&cur->value);
			free_and_null((void **)&cur->name_var);
			tmp = cur;
			cur = cur->next;
			free_and_null((void **)&tmp);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
}

void	stack_remove_node(t_env **begin_list, char *data_ref)
{
	if (!begin_list || !*begin_list)
		return ;
	stack_remove_head_nodes(begin_list, data_ref);
	stack_remove_inner_nodes(begin_list, data_ref);
}

char	valid_var(char *clean_name)
{
	if (!check_var(clean_name))
	{
		ft_putstr_fd("bash: unset: `", STDERR_FILENO);
		ft_putstr_fd(clean_name, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		return (1);
	}
	return (0);
}

char	ft_unset(t_env **begin_list, t_info_cmd *s_info_cmd)
{
	int	size;
	int	i;
	int	error;

	size = count_matrix(s_info_cmd->cmd);
	i = 1;
	error = 0;
	if (size > 1)
	{
		while (i < size)
		{
			if (valid_var(s_info_cmd->cmd[i]))
				error = 1;
			else
			{
				if (!ft_strcmp(s_info_cmd->cmd[i], "PATH"))
					stack_remove_node(begin_list, "@PATH");
				stack_remove_node(begin_list, s_info_cmd->cmd[i]);
			}
			i++;
		}
		return (error);
	}
	return (error);
}
