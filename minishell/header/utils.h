/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:21:28 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 12:23:36 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "types.h"

int		ft_strchr_index(const char *str, char c);
int		count_char(const char *str, char c);
int		count_word(char *str, char *sep);
int		count_pipes(char *str);
int		length_srt(char *str, char *set);
int		lstsize(t_stack *lst);
char	*get_last_node(char **matrix);
char	*generate_random_string(int length);
char	**free_array(char **split);
char	check_char(char *str, char c);
char	syntax_error(char *str);
void	free_and_null(void **ptr);
void	check_pipe(char check);
void	check_execve(int result);
pid_t	check_fork(pid_t pid);
int		safe_dup2(int oldfd, int newfd);
int		fake_fork(void);
void	ft_stack_clear(t_stack **stack);
void	print_error_3(char *path, char *massg);
void	clean_all(t_info_cmd *cmds, int number_cmd, char **envp);
void	ft_stack_pop(t_stack **stack);
char	*ft_strndup(char *s, size_t n);
int		count_matrix(char **matrix);
char	fatal_report(short flag);
char	add_var(t_env **export, t_stack **data, char is_quote);
char	*add_spaces(char *str, int length_space, char first_end);
char	*if_add_value(char *name_var, char *flag);
void	get_value_and_name(t_stack **data, char **name_var,
			char **value, char is_quote);
char	var_process(char **name_var, char *value, char *flag);
int		my_isspace(char c);
char	space(char *str);

#endif
