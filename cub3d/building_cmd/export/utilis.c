/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:54:57 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/03 21:14:46 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	variable_medium_variable(t_stack **data, char **value)
{
	if ((*data) && (*data)->token == EXPANSION)
		*value = add_spaces(*value, (*data)->prev_is_space, 1);
	while ((*data))
	{
		if ((*data)->token != EXPANSION)
			break ;
		*value = ft_strjoin(*value, (*data)->word, 1);
		*value = add_spaces(*value, (*data)->is_space, 1);
		if ((*data)->next
			&& (*data)->next->token != EXPANSION)
			break ;
		*data = (*data)->next;
	}
}

void	get_value(t_stack **data, char **value, char is_quote)
{
	while ((*data) && (*data)->token != PIPE)
	{
		if ((*data)->token == EXPANSION && !is_quote)
			variable_medium_variable(data, value);
		else
			*value = ft_strjoin(*value, (*data)->word, 1);
		if (!(*data) || (*data)->is_space)
			break ;
		*data = (*data)->next;
	}
}

void	get_value_and_name(t_stack **data, char **name_var,
		char **value, char is_quote)
{
	char	is_value;

	if (!data || !*data)
		return ;
	is_value = 0;
	*name_var = NULL;
	*value = NULL;
	while ((*data) && (*data)->token != PIPE)
	{
		if (!is_value || (!is_value && (*data)->is_space))
			*name_var = ft_strjoin(*name_var, (*data)->word, 1);
		if (!is_value && !ft_strcmp((*data)->word, "="))
			is_value = 1;
		else if (is_value)
		{
			get_value(data, value, is_quote);
			break ;
		}
		if (!*data || (*data)->is_space)
			break ;
		*data = (*data)->next;
	}
	if (is_value && !*value)
		*value = ft_strdup("\0");
}

char	var_process(char **name_var, char *value, char *flag)
{
	char	*clean_name;
	int		length;

	if (!name_var || !*name_var)
		return (0);
	length = ft_strlen(*name_var);
	if (length > 1 && (*name_var)[length - 1] == '=')
		clean_name = ft_strndup(*name_var, length - 1);
	else
		clean_name = ft_strdup(*name_var);
	clean_name = if_add_value(clean_name, flag);
	if (!check_var(clean_name))
	{
		ft_putstr_fd("bash: export: `", STDERR_FILENO);
		ft_putstr_fd(*name_var, STDERR_FILENO);
		ft_putstr_fd(value, STDERR_FILENO);
		ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
		free_and_null((void **)name_var);
		*name_var = NULL;
		free_and_null((void **)&clean_name);
		return (1);
	}
	free_and_null((void **)name_var);
	*name_var = clean_name;
	return (0);
}
