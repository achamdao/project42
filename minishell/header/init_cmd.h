/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmd.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:18:44 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 12:22:12 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_CMD_H
# define INIT_CMD_H

# include "types.h"

char		**array_cmd(t_stack *info_cmd);
void		pop_to_limiter(t_stack **info_cmd);
void		pop_to_limiter_file(t_files **file);
void		move_to_next_pipe(t_stack **stack);
void		cleanup_after_execution(t_data *data);
t_info_cmd	*initialize_cmd_all(t_data *data, t_info *info, char **paths);
int			fill_cmd_struct(t_info_cmd *cmd, t_data *data,
				t_info *info, int i);
int			initialize_cmd(t_info_cmd *s_info_cmd,
				t_data *data, int number_cmd);
t_files		*extract_files_for_current_cmd(t_files **files);
t_files		*pop_limiter_file_nofree(t_files **files);
char		**ft_get_path(char *str, short *error);
char		*get_cmd_and_path(t_info_cmd *info_cmd, char **paths);
char		update_underscore_value(t_env **export_var,
				t_info_cmd *s_info_cmd, int is_pipe);

#endif
