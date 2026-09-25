/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 16:07:42 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/27 15:55:37 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	length_var(char *word)
{
	int	i;

	i = 0;
	if (word[0] == '$' && word[1] != '\0' && !ft_isalnum(word[1]))
		return (2);
	if (!ft_isalnum(word[0]))
		i++;
	while (word[i] && ft_isalnum(word[i]))
		i++;
	return (i);
}

char	*new_str(char *word, t_env *env, int exit_status)
{
	char	*temp;
	int		start;
	int		end;
	char	*new;
	char	*value;

	end = 0;
	start = end;
	temp = NULL;
	new = NULL;
	while (word[start])
	{
		end = length_var(&word[start]);
		temp = ft_strndup(&word[start], end);
		value = value_of_var(env, temp, exit_status);
		free_and_null((void *)&temp);
		new = ft_strjoin(new, value, 1);
		free_and_null((void *)&value);
		start += end;
	}
	free(word);
	return (new);
}

char	*override_var(t_env *env, char *word,
			short is_single_quote, int exit_status)
{
	char	*new;

	if (!word)
		return (NULL);
	if (!ft_strchr(word, '$') || is_single_quote || ft_strcmp(word, "$") == 0)
	{
		new = ft_strdup(word);
		free(word);
		return (new);
	}
	return (new_str(word, env, exit_status));
}
