/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_stack_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 11:04:44 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/26 15:43:48 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	clear_env_list(t_env **env)
{
	t_env	*temp;

	if (!env || !*env)
		return ;
	while (*env)
	{
		temp = *env;
		*env = (*env)->next;
		free_env_node(temp);
	}
}

char	var_env(t_env **list_env, char **envp)
{
	int		count_envp;
	char	**array;
	char	*value;

	if (!envp || !*envp)
		return (-1);
	*list_env = NULL;
	count_envp = count_matrix(envp) - 1;
	while (0 <= count_envp)
	{
		array = ft_split(envp[count_envp], '=');
		if (!array)
			return (free_array(array), -1);
		value = getenv(array[0]);
		stack_push(list_env, array[0], value);
		free_array(array);
		array = NULL;
		count_envp--;
	}
	return (1);
}

int	count_env_vars(t_env *env)
{
	int	count;

	count = 0;
	while (env)
	{
		if (env->value)
			count++;
		env = env->next;
	}
	return (count);
}

char	*join_env_string(char *name_var, char *value)
{
	char	*tmp;
	char	*result;

	tmp = ft_strjoin(NULL, name_var, 1);
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, "=", 1);
	if (!result)
		return (NULL);
	result = ft_strjoin(result, value, 1);
	if (!result)
		return (NULL);
	return (result);
}

char	**stack_to_envp(t_env *env)
{
	char	**envp;
	int		len;
	int		i;

	len = count_env_vars(env);
	envp = malloc(sizeof(char *) * (len + 1));
	if (!envp)
		return (NULL);
	i = 0;
	while (env)
	{
		if (env->value && ft_strcmp(env->name_var, "@PWD")
			&& ft_strcmp(env->name_var, "@PATH"))
		{
			envp[i] = join_env_string(env->name_var, env->value);
			if (!envp[i])
				return (free_array(envp));
			i++;
		}
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}
