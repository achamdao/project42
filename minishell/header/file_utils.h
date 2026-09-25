/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:22:04 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 12:21:57 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_UTILS_H
# define FILE_UTILS_H

# include "types.h"

short	remove_file(char *file);
short	open_file(char *str, short token);
void	close_file(int input_fd, int output_fd);
void	close_all_pipes(int **pipes, int number_cmd);
void	close_file_if_needed(int fd);
void	close_files_array(int *fds, int size);
int		allocate_file(int **file[2], int number_cmd);
int		**fn_pipe(int nb_cmds);
void	free_pipes(int **pipes, int nb_cmds);
void	ft_files_pop(t_files **files);
int		create_pipe(int pipe_fd[2]);

#endif
