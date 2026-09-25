/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:20:58 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 12:22:34 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

# include "types.h"

int		open_cmd_io_files(t_files *files, int file_here_doc);
int		get_outfile(t_files *files, int file_here_doc);
int		get_input_fd(t_files *curr, int file_here_doc, int in_fd);
int		get_output_fd(t_files *curr, int out_fd);
void	apply_redirection(int fd, int std_fd);

#endif
