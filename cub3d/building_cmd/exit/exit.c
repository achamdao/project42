/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:52:50 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/27 16:37:20 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	handle_exit_argument_error(char *arg)
{
	ft_putstr_fd("bash: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
	exit(255);
}

short	ft_exit(t_info_cmd *s_info_cmd, int exit_code)
{
	long long	number;
	int			tmp;

	tmp = exit_code;
	if (s_info_cmd->tmp != EXIT)
		ft_putendl_fd("exit", 1);
	if (s_info_cmd->cmd[1])
	{
		if (!is_numeric(s_info_cmd->cmd[1]))
			handle_exit_argument_error(s_info_cmd->cmd[1]);
		exit_code = bash_atoi(s_info_cmd->cmd[1], &number);
		if (!exit_code)
			handle_exit_argument_error(s_info_cmd->cmd[1]);
		exit_code = number % 256;
		if (s_info_cmd->cmd[2])
		{
			s_info_cmd->tmp = -1;
			return (ft_putendl_fd("bash: exit: too many arguments", 2), 1);
		}
	}
	return (exit_code);
}
