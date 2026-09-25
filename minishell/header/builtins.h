/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:17:52 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 12:21:26 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "types.h"

int				execute_builtin(t_info_cmd *info, t_data *data, int error);
enum e_builtin	check_if_buildin_cmd(char **cmd);
int				ft_cd(t_info_cmd *s_info_cmd, t_env **env);
char			ft_echo(char **arr);
char			ft_env(t_info_cmd *s_info_cmd, t_env *env);
short			ft_exit(t_info_cmd *s_info_cmd, int exit_code);
char			ft_pwd(t_env *env);
char			ft_unset(t_env **begin_list, t_info_cmd *s_info_cmd);
char			ft_export(t_stack *data, t_env **env);
int				ft_strsearch(const char *haystack, const char *needle);
char			*increase_shlvl(t_env *env_list);
int				run_single_builtin(t_info_cmd *cmd, t_data *data, int error);
char			update_pwd(t_env **env_list, char *path, char *old_pwd);
int				is_numeric(const char *str);
int				bash_atoi(const char *str, long long *result);

#endif
