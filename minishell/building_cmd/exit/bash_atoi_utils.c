/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bash_atoi_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:42:11 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 15:42:24 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	skip_whitespace(const char *str, int *index)
{
	while (str[*index] == ' ' || (str[*index] >= 9 && str[*index] <= 13))
		(*index)++;
	return (str[*index] != '\0');
}

static int	parse_sign(const char *str, int *index, int *sign)
{
	*sign = 1;
	if (str[*index] == '-' || str[*index] == '+')
	{
		if (str[*index] == '-')
			*sign = -1;
		(*index)++;
	}
	return (1);
}

static int	parse_digits(const char *str, int *index,
		unsigned long long *result, int sign)
{
	unsigned long long	limit;

	limit = (unsigned long long)LLONG_MAX + 1;
	*result = 0;
	while (str[*index] >= '0' && str[*index] <= '9')
	{
		if (*result > (limit - (str[*index] - '0')) / 10)
			return (0);
		*result = *result * 10 + (str[*index] - '0');
		(*index)++;
	}
	if (sign == 1 && *result > LLONG_MAX)
		return (0);
	if (sign == -1 && *result > limit)
		return (0);
	return (1);
}

int	bash_atoi(const char *str, long long *result)
{
	int					index;
	int					sign;
	unsigned long long	temp_result;

	index = 0;
	sign = 1;
	temp_result = 0;
	if (!str || !str[0])
		return (0);
	if (!skip_whitespace(str, &index))
		return (0);
	if (!parse_sign(str, &index, &sign))
		return (0);
	if (!str[index])
		return (0);
	if (!parse_digits(str, &index, &temp_result, sign))
		return (0);
	*result = (long long)(temp_result * sign);
	return (1);
}

int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (i && str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}
