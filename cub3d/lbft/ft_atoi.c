/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 09:51:21 by achamdao          #+#    #+#             */
/*   Updated: 2024/11/07 09:55:32 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	comp_atoi(const char *str, int *i, int *sing)
{
	if (str[(*i)] == '-' || str[(*i)] == '+')
	{
		if (str[(*i)] == '-')
			(*sing) *= -1;
		(*i)++;
	}
}

int	ft_atoi(const char *str)
{
	int		i;
	int		sing;
	long	error;
	long	result;

	result = 0;
	i = 0;
	sing = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	comp_atoi(str, &i, &sing);
	while (str[i] >= '0' && str[i] <= '9')
	{
		error = result;
		result = result * 10 + str[i] - '0';
		if ((result / 10) != error)
		{
			if (sing == -1)
				return (0);
			return (-1);
		}
		i++;
	}
	return (result * sing);
}
