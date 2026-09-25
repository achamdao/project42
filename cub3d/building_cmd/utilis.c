/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:39:52 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/03 15:44:41 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*to_lowercase(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += ('a' - 'A');
		i++;
	}
	return (str);
}

enum e_builtin	check_if_buildin_cmd(char **cmd)
{
	char	*low_cmd;
	char	*str;

	if (!cmd || !*cmd)
		return (BNONE);
	str = ft_strdup(cmd[0]);
	if (!str)
		return (FIAL);
	low_cmd = to_lowercase(str);
	if (!ft_strcmp(low_cmd, "echo"))
		return (free(low_cmd), ECHO);
	else if (!ft_strcmp(low_cmd, "cd"))
		return (free(low_cmd), CD);
	else if (!ft_strcmp(low_cmd, "env"))
		return (free(low_cmd), ENV);
	else if (!ft_strcmp(low_cmd, "pwd"))
		return (free(low_cmd), PWD);
	else if (!ft_strcmp(low_cmd, "export"))
		return (free(low_cmd), EXPORT);
	else if (!ft_strcmp(low_cmd, "unset"))
		return (free(low_cmd), UNSET);
	else if (!ft_strcmp(low_cmd, "exit"))
		return (free(low_cmd), EXIT);
	return (free(low_cmd), BNONE);
}

int	execute_builtin(t_info_cmd *info, t_data *data, int error)
{
	if (data->user_stack)
	{
		if (info->buiilding == EXPORT)
			return (ft_export(data->stack, &data->user_stack));
		else if (info->buiilding == ENV)
			return (ft_env(info, data->user_stack));
		else if (info->buiilding == UNSET)
			return (ft_unset(&data->user_stack, info));
	}
	if (info->buiilding == ECHO)
		return (ft_echo(info->cmd));
	else if (info->buiilding == CD)
		return (ft_cd(info, &data->user_stack));
	else if (info->buiilding == PWD)
		return (ft_pwd(data->user_stack));
	else if (info->buiilding == EXIT)
		return (ft_exit(info, error));
	return (0);
}
