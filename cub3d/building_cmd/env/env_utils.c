/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:08:42 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 15:43:56 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*search_env_value(t_env *env, const char *name_var)
{
	while (env)
	{
		if (!ft_strcmp(env->name_var, name_var))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

t_env	*search_env(t_env *head, const char *name_var)
{
	t_env	*current;

	current = head;
	while (current)
	{
		if (!ft_strcmp(current->name_var, name_var))
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	free_and_null((void **)&node->name_var);
	free_and_null((void **)&node->value);
	free_and_null((void **)&node);
}
