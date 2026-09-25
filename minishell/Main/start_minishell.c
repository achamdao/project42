/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_minishell.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 22:25:55 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/28 21:00:20 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

char	fatal_report(short flag)
{
	if (flag == 1)
		ft_putendl_fd("bash: maximum here-document count exceeded", 2);
	else if (flag == 2)
		ft_putendl_fd("bash: Cannot allocate memory", 2);
	else if (flag == AMBIGUOUS)
		ft_putendl_fd("bash: : ambiguous redirect", 2);
	return (0);
}

char	input_readline(char **input, t_env **env, t_info *info)
{
	*input = readline("shell: ");
	if (g_lobal_var == 2)
		info->error = 1;
	if (!*input && g_lobal_var != SUCCESS)
		g_lobal_var = SUCCESS;
	if (!*input && g_lobal_var == SUCCESS)
	{
		ft_putstr_fd("\r\033[1A\033[2K", 1);
		ft_putstr_fd("shell: exit\n", 1);
		clear_env_list(env);
		return (1);
	}
	return (0);
}

char	complete_start_minishell2(t_info *info, t_env **env)
{
	if (info->temp_error != 258 && parsing_redirection(info) == FAILER)
		return (FAILER);
	if (info->temp_error != 258 && final_cleaner_stack(info) == FAILER)
		return (FAILER);
	info->temp_error = 0;
	(void)env;
	if (start(info, env) == FAILER && info->temp_error != EXIT)
		return (FAILER);
	return (0);
}

char	complete_start_minishell(t_info *info, t_env **env, short item_error)
{
	if (stop_runing_shell(info, item_error) != 0)
		return (0);
	if (expansion_var(info, *env) == FAILER)
		return (FAILER);
	if (info->temp_error == 2)
		return (fatal_report(1), force_exit(info, env, 2), 0);
	return (complete_start_minishell2(info, env));
}

char	start_minishell(t_info *info, t_env **env, char *input)
{
	short	item_error;

	if (lexer(input, " \t\n&;()[]\\`~!@#%^*=|\'\"<>", &info->info) == FAILER)
		return (fatal_report(2), force_exit(info, env, 1), 0);
	token_name(&info->info);
	item_error = analyse_token(&info->info);
	if (item_error != -2)
	{
		info->error = 258;
		info->temp_error = info->error;
	}
	if (allocate_array(info) == FAILER)
		return (fatal_report(2), force_exit(info, env, 1), 0);
	if (stored_herd_doc(info) == FAILER)
		return (fatal_report(2), force_exit(info, env, 1), 0);
	if (complete_start_minishell(info, env, item_error) == FAILER)
		return (fatal_report(2), force_exit(info, env, 1), 0);
	return (0);
}
