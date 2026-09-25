/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Flash_Bash.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 11:47:16 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/03 18:12:54 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

int	g_lobal_var;

void	force_exit(t_info *info, t_env **env, int exit_value)
{
	clear_struct(info);
	clear_env_list(env);
	exit(exit_value);
}

void	initialize_info(t_info *info)
{
	info->here_doc = NULL;
	info->info = NULL;
	info->file = NULL;
	info->is_here_doc = NULL;
	info->number_cmd = 0;
}

char	stop_runing_shell(t_info *info, short item)
{
	if (check_for_run_her_doc(info, item) == 0)
	{
		info->temp_error = 0;
		return (-2);
	}
	return (0);
}

char	start_main(t_env **env, t_info *info, char **input)
{
	struct termios	term;

	info->error = 0;
	tcgetattr(STDIN_FILENO, &term);
	while (1)
	{
		g_lobal_var = SUCCESS;
		handel_signal();
		if (info->temp_error == EXIT)
			force_exit(info, env, info->error);
		if (input_readline(input, env, info))
			return (exit(info->error), 0);
		if (*input && !space(*input))
		{
			*input = ft_strtrim(*input, " \t", 1);
			initialize_info(info);
			start_minishell(info, env, *input);
			clear_struct(info);
			add_history(*input);
		}
		free_and_null((void **)input);
		tcsetattr(STDIN_FILENO, TCSANOW, &term);
	}
	rl_clear_history();
	return (0);
}

int	main(int coun, char **srg, char **envp)
{
	char	*input;
	t_env	*env;
	t_info	info;

	rl_catch_signals = 0;
	coun = 0;
	srg = NULL;
	env = NULL;
	input = NULL;
	g_lobal_var = 0;
	init_env(&env, envp);
	start_main(&env, &info, &input);
	return (0);
}
