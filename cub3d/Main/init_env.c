/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:18:13 by achamdao          #+#    #+#             */
/*   Updated: 2025/05/04 11:08:40 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

void	complete_init_env(t_env **env, t_env *node, char **value)
{
	if (!node)
		update_or_add_env(env, "@PATH",
			"/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.", 0);
	else
		update_or_add_env(env, "@PATH", node->value, 0);
	free(*value);
}

void	init_pldpwd(t_env **env)
{
	t_env	*node;

	node = search_env(*env, "OLDPWD");
	if (!node)
		update_or_add_env(env, "OLDPWD", NULL, 0);
}

void	init_env(t_env **env, char **envp)
{
	t_env	*node;
	char	*value;

	value = NULL;
	var_env(env, envp);
	node = search_env(*env, "SHLVL");
	if (!node)
		update_or_add_env(env, "SHLVL", "1", 0);
	else
	{
		value = increase_shlvl(node);
		update_or_add_env(env, "SHLVL", value, 0);
		free(value);
		value = NULL;
	}
	node = search_env(*env, "PWD");
	value = get_current_directory();
	if (!node)
		update_or_add_env(env, "PWD", value, 0);
	update_or_add_env(env, "@PWD", value, 0);
	node = search_env(*env, "PATH");
	complete_init_env(env, node, &value);
	init_pldpwd(env);
}
