/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:36:39 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 16:31:31 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

char	*get_env_var(t_env *env_list, const char *var_name)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->name_var, var_name) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

char	set_env_var(t_env *env_list, const char *var_name,
		const char *new_value)
{
	char	*tmp;

	while (env_list)
	{
		if (ft_strcmp(env_list->name_var, var_name) == 0)
		{
			tmp = ft_strdup(new_value);
			if (!tmp)
				return (0);
			free_and_null((void **)&env_list->value);
			env_list->value = tmp;
			return (1);
		}
		env_list = env_list->next;
	}
	return (0);
}

char	update_pwd(t_env **env_list, char *path, char *old_pwd)
{
	if (!path || !old_pwd)
		return (free(path), free(old_pwd), -1);
	if (!set_env_var(*env_list, "OLDPWD", old_pwd))
	{
		if (update_or_add_env(env_list, "OLDPWD", old_pwd, 0) == -1)
			return (free(path), free(old_pwd), -1);
	}
	set_env_var(*env_list, "@PWD", path);
	set_env_var(*env_list, "PWD", path);
	free(path);
	free(old_pwd);
	return (0);
}

void	print_cd_error(const char *path)
{
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd((char *)path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
}

char	*hyphen_cd(char *path, t_env *env, char *is_hyphen)
{
	char	*oldpwd;

	if (!path)
		return (NULL);
	if (path[0] == '-' && path[1] == '\0')
	{
		*is_hyphen = 1;
		oldpwd = get_env_var(env, "OLDPWD");
		if (oldpwd)
			ft_putendl_fd(oldpwd, 1);
		else
		{
			ft_putstr_fd("bash: cd: OLDPWD not set\n", 2);
			return (NULL);
		}
		return (ft_strdup(oldpwd));
	}
	return (NULL);
}
