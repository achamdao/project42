/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:53:09 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 14:15:17 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	*get_current_directory(void)
{
	char	*cwd_sys;

	cwd_sys = getcwd(NULL, 0);
	if (!cwd_sys)
	{
		perror("getcwd");
		return (NULL);
	}
	return (cwd_sys);
}

char	ft_pwd(t_env *env)
{
	char	*cwd_env;
	char	*cwd_sys;

	cwd_env = get_env_var(env, "@PWD");
	if (cwd_env && cwd_env[0] != '\0')
	{
		ft_putendl_fd(cwd_env, STDOUT_FILENO);
		return (0);
	}
	cwd_sys = get_current_directory();
	ft_putendl_fd(cwd_sys, STDOUT_FILENO);
	free(cwd_sys);
	return (0);
}
