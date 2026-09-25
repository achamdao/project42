/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:20:31 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 12:21:42 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_UTILS_H
# define ENV_UTILS_H

# include "types.h"

char	*search_env_value(t_env *env, const char *name_var);
char	**stack_to_envp(t_env *env);
char	update_or_add_env(t_env **env_list, char *name_var,
			char *new_value, char flag);
char	set_env_var(t_env *env_list, const char *var_name,
			const char *new_value);
char	var_env(t_env **list_env, char **envp);
char	check_var(char *var);
char	*get_env_var(t_env *env_list, const char *var_name);
void	clear_env_list(t_env **env);
t_env	*find_shlvl(t_env *env);
int		env_list_size(t_env *env);
char	*override_var(t_env *env, char *word,
			short is_single_quote, int exit_status);
char	*value_of_var(t_env *env, char *word, int exit_status);
void	stack_push(t_env **env, char *nam_var, char *value);
char	*concatenate_word(t_stack **stack, short token);
t_env	*search_env(t_env *head, const char *name_var);
void	free_env_node(t_env *node);
int		print_sorted_env(t_env *env_list, int fd);

#endif
