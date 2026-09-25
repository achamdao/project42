/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:32:02 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/27 23:49:00 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	check_var(char *var)
{
	int	i;

	if (!var)
		return (-1);
	if (!ft_isalpha(var[0]) && var[0] != '_')
		return (0);
	i = 1;
	while (var[i])
	{
		if (!ft_isalpha(var[i]) && (var[i] != '_') && !ft_isdigit(var[i]))
			return (0);
		i++;
	}
	return (1);
}

char	*if_add_value(char *name_var, char *flag)
{
	int		length;
	char	*new_name;

	length = ft_strlen(name_var);
	*flag = 0;
	if (count_char(name_var, '+') != 1 || name_var[length - 1] != '+')
		return (name_var);
	new_name = ft_strndup(name_var, length - 1);
	*flag = 1;
	free(name_var);
	return (new_name);
}

char	*get_updated_value(t_env *current, char *new_value, char flag)
{
	char	*dup;
	char	*result;

	dup = ft_strdup(new_value);
	if (!dup)
		return (NULL);
	if (flag)
	{
		result = ft_strjoin(current->value, dup, 1);
		free_and_null((void **)&dup);
		return (result);
	}
	else
	{
		free_and_null((void **)&current->value);
		return (dup);
	}
}

char	update_or_add_env(t_env **env_list, char *name_var,
		char *new_value, char flag)
{
	t_env	*current;
	char	*new_val;

	current = *env_list;
	if (!env_list || !name_var)
		return (-1);
	while (current)
	{
		if (!ft_strcmp(current->name_var, name_var))
		{
			if (new_value != NULL)
			{
				new_val = get_updated_value(current, new_value, flag);
				if (!new_val)
					return (-1);
				current->value = new_val;
			}
			return (0);
		}
		current = current->next;
	}
	stack_push(env_list, name_var, new_value);
	return (0);
}

char	*add_spaces(char *str, int length_space, char first_end)
{
	char	*spaces;
	char	*result;
	int		i;

	spaces = malloc(length_space + 1);
	if (!spaces)
		return (NULL);
	i = 0;
	while (i < length_space)
		spaces[i++] = ' ';
	spaces[i] = '\0';
	if (first_end)
		result = ft_strjoin(str, spaces, 0);
	else
		result = ft_strjoin(spaces, str, 0);
	free(spaces);
	free(str);
	return (result);
}
