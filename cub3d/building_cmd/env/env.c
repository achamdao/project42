/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:52:39 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/08 09:10:58 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

t_env	*find_shlvl(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name_var, "SHLVL") == 0)
			return (env);
		env = env->next;
	}
	return (NULL);
}

int	ft_atoi_shlvl(char *str)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	if (str[0] == '\0')
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		result = result * 10 + (str[i] - '0');
		if (result >= 1000)
			return (result);
		i++;
	}
	return (result);
}

int	handle_shlvl(char *value)
{
	int	lvl;

	lvl = ft_atoi_shlvl(value);
	if (value[0] == '-')
		return (0);
	if (lvl == 1 && !(value[0] == '1' && value[1] == '\0'))
		return (1);
	if (lvl >= 1000)
		return (1);
	return (lvl + 1);
}

char	*increase_shlvl(t_env *env_list)
{
	t_env	*shlvl_node;
	char	*shlvl_value;

	shlvl_node = env_list;
	if (shlvl_node)
		shlvl_value = ft_itoa(handle_shlvl(shlvl_node->value));
	else
		shlvl_value = ft_strdup("1");
	return (shlvl_value);
}

char	ft_env(t_info_cmd *s_info_cmd, t_env *env)
{
	t_env	*curr;

	if (s_info_cmd->cmd[1])
		return (ft_putstr_fd("with no options or arguments\n", 2), 1);
	curr = env;
	while (curr)
	{
		if (curr->value && ft_strcmp(curr->name_var, "@PWD")
			&& ft_strcmp(curr->name_var, "@PATH"))
		{
			ft_putstr_fd(curr->name_var, 1);
			if (!ft_strcmp(curr->value, "\0"))
				ft_putstr_fd("=\"\"\n", 1);
			else
			{
				ft_putstr_fd("=", 1);
				ft_putstr_fd(curr->value, 1);
				ft_putstr_fd("\n", 1);
			}
		}
		curr = curr->next;
	}
	return (0);
}
