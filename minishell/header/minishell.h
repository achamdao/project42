/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:23:13 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 12:22:28 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lbft/libft.h"
# include "types.h"
# include "cwd_utils.h"
# include "env_utils.h"
# include "exec_pipeline.h"
# include "file_utils.h"
# include "here_doc.h"
# include "init_cmd.h"
# include "lexer.h"
# include "redir.h"
# include "utils.h"
# include "builtins.h"
# include "start.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <dirent.h>
# include <limits.h>
# include <string.h>
# include <sys/stat.h>
# include <term.h>

# define FACK_PIPE -50
# define ASCII_START 33
# define ASCII_RANGE 94

void	run_all_cmds(t_info_cmd *cmds, t_data *data, int number_cmd);
int		pipe_line(t_info *info, t_data *data);
int		run_simple_cmd(t_info *info, t_data *data);
char	start(t_info *info, t_env **export_var);
int		open_cmd_io_files(t_files *files, int file_here_doc);
int		get_outfile(t_files *files, int file_here_doc);
void	close_file(int input_fd, int output_fd);
int		check_path_status(char *path);
char	*ft_getcwd(char *pwd, char *path);
void	run_here_doc_fack(t_here_doc **here_doc);

#endif
