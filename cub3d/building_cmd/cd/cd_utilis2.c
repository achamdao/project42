/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utilis2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:52:35 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 16:32:57 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

static int	handle_target_and_oldpwd(char *path, t_env **env,
			char **target, char **old_pwd)
{
	char	is_hyphen;

	is_hyphen = 0;
	*target = hyphen_cd(path, *env, &is_hyphen);
	if (is_hyphen && !*target)
		return (1);
	*old_pwd = ft_strdup(get_env_var(*env, "@PWD"));
	if (!*old_pwd)
	{
		if (chdir(*target) != 0)
		{
			print_cd_error(*target);
			free(*target);
			return (1);
		}
		free(*target);
		return (0);
	}
	return (-1);
}

static int	handle_chdir_and_update(char *path, char *old_pwd,
			char *target, t_env **env)
{
	char	*new_pwd;

	if (target)
		new_pwd = ft_strdup(target);
	else
		new_pwd = ft_getcwd(old_pwd, path);
	if (!new_pwd)
	{
		print_cd_error(target);
		free(target);
		free(old_pwd);
		return (1);
	}
	if (chdir(new_pwd) != 0)
	{
		if (lost_current_directory(path, old_pwd, env))
			return (free(target), free(new_pwd), 1);
		print_cd_error(path);
		free(target);
		free(old_pwd);
		free(new_pwd);
		return (1);
	}
	free(target);
	return (update_pwd(env, new_pwd, old_pwd));
}

int	excute_chdir(char *path, t_env **env)
{
	char	*old_pwd;
	char	*target;
	int		ret;

	ret = handle_target_and_oldpwd(path, env, &target, &old_pwd);
	if (ret != -1)
		return (ret);
	return (handle_chdir_and_update(path, old_pwd, target, env));
}
