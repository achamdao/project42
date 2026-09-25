/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 15:17:03 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/04 12:22:20 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "types.h"

// Tokenization + Parsing
char	stop_runing_shell(t_info *info, short item);
char	lexer(char *cmd_line, char *sep, t_stack **s_lexer);
short	name_of_string(char *str, int flag);
short	token_name(t_stack **stack);
char	analyse_token(t_stack **stack);
short	check_valid_redirection(t_stack *current);
char	parsing_minishell(t_info *info_cmd);
char	handle_redirection(t_stack **stack, t_info *info_cmd, t_files **files);
char	check_for_run_her_doc(t_info *info, short item_error);
char	stored_herd_doc_error(t_info *info_cmd);
char	final_cleaner_stack(t_info *info);
char	uniform_tokenize_stack(t_stack **stack, short token);
char	expansion_var(t_info *info, t_env *env);
char	ft_close(t_info *info, short flag, int i);
char	allocate_array(t_info *info_cmd);
char	check_char(char *str, char c);
short	check_valid_quote(char *str);
short	check_last_pipe(char *str);
char	syntax_error(char *str);
int		count_pipe(t_stack *current_stack);
short	is_quote(char quote, int flage_quote);
char	add_node_btw_empty_pipe(t_info *info);
char	add_pipe(t_files **temp, char *pipe, char flag);
char	free_node(void *ptr, char *str);
char	process_empty_btw_pipe(t_stack *current, t_stack **temp);
char	node_akatsuky(t_stack **new_node);
void	init_env(t_env **env, char **envp);
char	handle_her_doc(t_stack **stack, t_info *info_cmd, int i);
char	set_final_limiter(t_stack *stack,
			t_here_doc **hre_doc, short temp_error);
int		count_word_var(char *str, char *sep);
char	get_last_node_cleaner(t_stack **last_cleaner_stack, int is_space);
// Stack Lexer
char	push(t_stack **oldlist, char *data, int is_space);
void	lstadd_back(t_stack **lst, t_stack *node);
t_stack	*lstlast(t_stack *lst);
t_stack	*add_new_list(char *data, int is_space);
void	remove_node(t_stack **begin_list);
t_stack	*copy_stack_node(t_stack *node);
char	append_to_end(t_stack **head, t_stack *node);
t_stack	*pop_cmd(t_stack **stack);
void	ft_clear(t_stack **lst);
char	cleaner_stack(t_info *info);
char	push_file(t_files **oldlist, char *file, short token);
void	ft_files_clear(t_files **files);
void	clear_struct(t_info *info);
void	free_resources(t_info *info_cmd);

//Error
short	print_error(char *error, short token);

#endif
