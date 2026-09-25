/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:52:25 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/03 21:14:27 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	is_valid_echo_n_option(const char *arg)
{
	int	i;

	if (arg[0] != '-')
		return (0);
	i = 1;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (arg[1] != '\0');
}

void	print_word_with_space(char *word, char space)
{
	ft_putstr_fd(word, 1);
	if (space)
		ft_putchar_fd(' ', 1);
}

int	print_echo_arguments(char **arr)
{
	int	print_new_line;
	int	i;

	i = 1;
	print_new_line = 1;
	while (arr[i] && is_valid_echo_n_option(arr[i]))
	{
		print_new_line = 0;
		i++;
	}
	while (arr[i] && ft_strcmp(arr[i], "|"))
	{
		if (!arr[i + 1])
			print_word_with_space(arr[i], 0);
		else
			print_word_with_space(arr[i], 1);
		i++;
	}
	return (print_new_line);
}

char	ft_echo(char **arr)
{
	int	print_new_line;

	if (!*arr)
		return (0);
	if (!arr[1])
		return (ft_putchar_fd('\n', 1), 0);
	print_new_line = print_echo_arguments(arr);
	if (print_new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}
