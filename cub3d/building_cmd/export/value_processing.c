/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value_processing.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:46 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/03 20:30:38 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	process_name_and_value(char **name_var,
			char **value, char *flag)
{
	char	error;

	error = var_process(name_var, *value, flag);
	if (!*name_var)
	{
		free_and_null((void **)value);
		return (error);
	}
	if (error == -1)
	{
		free_and_null((void **)name_var);
		free_and_null((void **)value);
		return (-1);
	}
	return (0);
}

static char	update_environment_variable(t_env **export, char *name_var,
			char *value, char flag)
{
	char	update_result;

	if (!ft_strcmp(name_var, "PATH"))
		update_or_add_env(export, "@PATH", value, flag);
	update_result = update_or_add_env(export, name_var, value, flag);
	if (update_result == -1)
	{
		free_and_null((void **)&name_var);
		free_and_null((void **)&value);
		return (-1);
	}
	return (0);
}

char	add_var(t_env **export, t_stack **data, char is_quote)
{
	char	*name_var;
	char	*value;
	char	flag;
	char	error;

	name_var = NULL;
	value = NULL;
	get_value_and_name(data, &name_var, &value, is_quote);
	error = process_name_and_value(&name_var, &value, &flag);
	if (error != 0)
		return (error);
	error = update_environment_variable(export, name_var, value, flag);
	free_and_null((void **)&name_var);
	free_and_null((void **)&value);
	return (error);
}

int	env_list_size(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		count++;
		env = env->next;
	}
	return (count);
}
