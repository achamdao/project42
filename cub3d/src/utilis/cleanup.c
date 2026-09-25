/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:32:55 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/05/03 18:08:59 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	clean_cmd(t_info_cmd *cmd)
{
	free_array(cmd->cmd);
	close_file_if_needed(cmd->fd_here_doc);
	ft_files_clear(&cmd->my_files);
	free(cmd->path);
	cmd->path = NULL;
}

void	clean_all(t_info_cmd *cmds, int number_cmd, char **envp)
{
	int	i;

	i = 0;
	free_array(envp);
	while (i < number_cmd)
	{
		clean_cmd(&cmds[i]);
		i++;
	}
	free(cmds);
}

void	clear_here_doc(t_here_doc **stack)
{
	t_here_doc	*current;
	t_here_doc	*tmp;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->next;
		free_and_null((void **)&current->limeter);
		free_and_null((void **)&current);
		current = tmp;
	}
	*stack = NULL;
}

void	ft_stack_clear(t_stack **stack)
{
	t_stack	*tmp;

	if (!stack)
		return ;
	while ((*stack))
	{
		tmp = (*stack)->next;
		free((*stack)->word);
		free((*stack));
		(*stack) = tmp;
	}
	*stack = NULL;
}
