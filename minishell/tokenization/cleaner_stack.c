/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_stack.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 01:35:09 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/28 20:58:29 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	get_last_node_cleaner(t_stack **last_cleaner_stack, int is_space)
{
	t_stack	*current;

	current = *last_cleaner_stack;
	while (current && current->next)
		current = current->next;
	if (current && !current->is_space)
		current->is_space = is_space;
	return (0);
}

char	count_spaces(char *s1, int *end, int *star)
{
	int	lenght;

	lenght = ft_strlen(s1);
	(*star) = 0;
	if (!lenght)
		return (0);
	while (s1[(*star)] && (my_isspace(s1[(*star)])))
		(*star)++;
	if ((*star) == (lenght - 1))
		return (0);
	while (lenght && (my_isspace(s1[lenght -1])))
	{
		lenght--;
		(*end)++;
	}
	return (0);
}

char	process_convert_var_to_stack(t_stack *temp_current,
		t_stack **clean_stack, t_stack *current)
{
	int	end;
	int	star;

	end = 0;
	star = 0;
	count_spaces(current->word, &end, &star);
	if (temp_current)
		temp_current->prev_is_space = star;
	while (temp_current)
	{
		if (!temp_current->next)
		{
			if (end)
				temp_current->is_space = end;
			else
				temp_current->is_space = current->is_space;
		}
		append_to_end(clean_stack, temp_current);
		temp_current = temp_current->next;
	}
	return (0);
}

char	convert_var_to_stack(t_stack **clean_stack, t_stack *current)
{
	t_stack	*temp;
	char	*trim_str;
	t_stack	*temp_current;

	temp = NULL;
	trim_str = ft_strtrim(current->word, " \t", 0);
	if (!trim_str)
		return (FAILER);
	if (lexer(trim_str, " \t\n:&;()[]\\`~!@#%^*=|\'\"<>", &temp) == FAILER)
		return (ft_stack_clear(&temp), free(trim_str), FAILER);
	free(trim_str);
	uniform_tokenize_stack(&temp, EXPANSION);
	temp_current = temp;
	process_convert_var_to_stack(temp_current, clean_stack, current);
	ft_stack_clear(&temp);
	return (0);
}

char	final_cleaner_stack(t_info *info)
{
	t_stack	*current;
	t_stack	*clean_stack;

	clean_stack = NULL;
	if (cleaner_stack(info) == FAILER)
		return (FAILER);
	current = info->info;
	while (current)
	{
		if (current->token == VAR)
		{
			if (convert_var_to_stack(&clean_stack, current) == FAILER)
				return (FAILER);
		}
		else
			append_to_end(&clean_stack, current);
		current = current->next;
	}
	ft_stack_clear(&info->info);
	info->info = clean_stack;
	return (0);
}
