/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cwd_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:19:30 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 12:21:34 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CWD_UTILS_H
# define CWD_UTILS_H

# include "types.h"

char	*ft_getcwd(char *pwd, char *path);
char	*absolute_path(char *pwd, char *path);
char	*relative_path(char *path);
char	*get_dir(char *path, int *length);
char	*join_pwd(char *env_pwd, char *relative_path);
char	*process_parent_directory(char *current_path);
char	*process_child_directory(char *current_path, char *dir);
char	ft_is_root(char *path);
char	*handle_dot_dot(char *env_pwd);
int		skip_slashes(char *path, int i);
char	*get_current_directory(void);
char	*hyphen_cd(char *path, t_env *env, char *is_hyphen);
void	print_cd_error(const char *path);
char	lost_current_directory(char *path, char *oldpwd, t_env **env);
int		excute_chdir(char *path, t_env **env);

#endif
