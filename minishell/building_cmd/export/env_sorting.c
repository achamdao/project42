/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_sorting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:33:36 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 18:07:44 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_env	**env_to_array(t_env *env, int size)
{
	t_env	**array;
	int		i;

	array = malloc(sizeof(t_env *) * size);
	if (!array)
		return (NULL);
	i = 0;
	while (env)
	{
		array[i++] = env;
		env = env->next;
	}
	return (array);
}

void	swap_env(t_env **a, t_env **b)
{
	t_env	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_env_array(t_env **array, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size - 1)
	{
		j = -1;
		while (++j < size - i - 1)
		{
			if (ft_strcmp(array[j]->name_var, array[j + 1]->name_var) > 0)
				swap_env(&array[j], &array[j + 1]);
		}
	}
}

static void	print_export_line(t_env *env, int fd)
{
	if (!ft_strcmp(env->name_var, "@PWD") || !ft_strcmp(env->name_var, "@PATH")
		|| !ft_strcmp(env->name_var, "_"))
		return ;
	ft_putstr_fd("declare -x ", fd);
	ft_putstr_fd(env->name_var, fd);
	if (env->value)
	{
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(env->value, fd);
		ft_putstr_fd("\"", fd);
	}
	ft_putendl_fd("", fd);
}

int	print_sorted_env(t_env *env_list, int fd)
{
	t_env	**array;
	int		size;
	int		i;

	size = env_list_size(env_list);
	if (size == 0)
		return (0);
	array = env_to_array(env_list, size);
	if (!array)
		return (-1);
	sort_env_array(array, size);
	i = 0;
	while (i < size)
		print_export_line(array[i++], fd);
	free(array);
	return (0);
}
