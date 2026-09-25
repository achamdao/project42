/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 16:13:32 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 12:22:41 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef START_H
# define START_H

# include "types.h"

char	parsing_redirection(t_info *info_cmd);
char	stored_herd_doc(t_info *info_cmd);
char	input_readline(char **input, t_env **env, t_info *info);
char	start_minishell(t_info *info, t_env **env, char *input);
void	handel_signal(void);
void	ignor_signal_perent(void);
void	setup_signals_child(void);
char	*init_new_input(char *old_input);
char	process_pipe_line(t_stack **current, char **new);
short	check_valid_pipe(t_stack *current);
short	check_valid_syntax(t_stack *current);
char	fixe_node_empty(t_files **files);
void	force_exit(t_info *info, t_env **env, int exit_value);

#endif
