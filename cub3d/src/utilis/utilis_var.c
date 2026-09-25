/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:18:56 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/27 13:34:00 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static char	*build_expanded_str(char *original, int prefix_len,
		char *value, char *remaining)
{
	char	*prefix;
	char	*new_str;

	prefix = ft_strndup(original, prefix_len);
	new_str = ft_strjoin(prefix, value, 1);
	new_str = ft_strjoin(new_str, remaining, 1);
	return (new_str);
}

char	*extract_var_name(char *var_start, int *var_len)
{
	*var_len = 0;
	while (var_start[*var_len] && (ft_isalnum(var_start[*var_len])
			|| var_start[*var_len] == '_'))
		(*var_len)++;
	return (ft_strndup(var_start, *var_len));
}

char	*expand_exit_status(char *word, char *var_start, int status)
{
	char	*exit_str;
	char	*result;

	exit_str = ft_itoa(status);
	if (!exit_str)
		return (NULL);
	result = build_expanded_str(word, var_start - 1 - word,
			exit_str, var_start + 1);
	free(exit_str);
	return (result);
}

char	*expand_named_variable(t_env *env, char *word, char *var_start)
{
	int		var_len;
	char	*var_name;
	char	*value;
	char	*result;

	var_name = extract_var_name(var_start, &var_len);
	if (!var_name)
		return (NULL);
	value = search_env_value(env, var_name);
	value = ft_strdup(value);
	if (!value)
		value = ft_strdup("");
	result = build_expanded_str(word, var_start - 1 - word,
			value, var_start + var_len);
	free_and_null((void **)&var_name);
	free_and_null((void **)&value);
	return (result);
}

char	*value_of_var(t_env *env, char *word, int exit_status)
{
	char	*dollar;
	char	*var_start;

	dollar = ft_strchr(word, '$');
	if (!dollar || !ft_strcmp(word, "$$") || !ft_strcmp(word, "$"))
		return (ft_strdup(word));
	var_start = dollar + 1;
	if (*var_start == '?')
		return (expand_exit_status(word, var_start, exit_status));
	return (expand_named_variable(env, word, var_start));
}
