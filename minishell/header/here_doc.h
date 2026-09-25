/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:21:51 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 12:22:05 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HERE_DOC_H
# define HERE_DOC_H

# include "types.h"

char		read_heredoc(t_here_doc **here_doc, int file_fd,
				t_env *env, int error);
t_here_doc	*pop_here_doc(t_here_doc **stack);
char		push_here_doc(t_here_doc **head, char *limiter);
void		clear_here_doc(t_here_doc **stack);
int			lstsize_herdoc(t_here_doc *lst, char *limiter);
char		*handle_here_doc2(t_info *info, int cmd_index, t_env *export_var);
void		fack_here_doc(t_here_doc **here_doc);
int			reopen_temp_file(char *file_tmp);
void		pop_to_here_doc(t_here_doc **here_doc);
int			reopen_temp_file(char *file_tmp);
int			expand_and_write_line(char *line, int file_fd);
int			is_limiter_reached(char *line, t_here_doc **here_doc);
char		*read_line_from_user(void);
int			lstsize_herdoc(t_here_doc *lst, char *limiter);
pid_t		launch_here_doc_child(t_info *info, int cmd_index,
				t_env *export_var, int pipe_fd[2]);
int			receive_fd_from_child(int pipe_fd[2], pid_t pid);

#endif
