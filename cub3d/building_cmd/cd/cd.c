/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:37:09 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/03 16:05:57 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	run_chid(char *path)
{
	if (chdir(path) != 0)
	{
		print_cd_error(path);
		free(path);
	}
	else
		free(path);
}

char	lost_current_directory(char *path, char *oldpwd, t_env **env)
{
	if (errno == ENOENT && (!ft_strcmp(path, "..") || !ft_strcmp(path, ".")))
	{
		ft_putstr_fd("error retrieving current directory: ", 2);
		ft_putstr_fd("getcwd: ", 2);
		ft_putstr_fd("cannot access parent directories: ", 2);
		ft_putstr_fd("No such file or directory\n", 2);
		if (chdir("/") != 0)
		{
			print_cd_error("/");
			return (1);
		}
		update_pwd(env, ft_strdup("/"), oldpwd);
		return (1);
	}
	return (0);
}

int	ft_cd(t_info_cmd *s_info_cmd, t_env **env)
{
	char	*home;

	if (!s_info_cmd->cmd || !s_info_cmd->cmd[0])
		return (-1);
	if (!s_info_cmd->cmd[1])
	{
		home = get_env_var(*env, "HOME");
		if (!home || home[0] == '\0')
		{
			ft_putstr_fd("bash: cd: HOME not set\n", 2);
			return (1);
		}
		return (excute_chdir(home, env));
	}
	return (excute_chdir(s_info_cmd->cmd[1], env));
}
