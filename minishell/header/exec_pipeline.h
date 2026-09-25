/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:21:16 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 12:21:49 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_PIPELINE_H
# define EXEC_PIPELINE_H

# include "types.h"

void	run_all_cmds(t_info_cmd *cmds, t_data *data, int number_cmd);
void	child_process(t_info_cmd *cmds, t_data *data,
			int **pipes, int number_cmd);
void	dup_pipe(int **pipes, int i, int number_cmd);
char	the_last_cmd(t_info_cmd *info, t_data *data);
int		finale_cmd(t_info_cmd *info, t_data *data);
void	execute_command(t_info_cmd *info, char **envp);
int		wait_for_child(int status);
int		launch_pipeline_processes_core(t_pipeline_data *pipe_data);

#endif
