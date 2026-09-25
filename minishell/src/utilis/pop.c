/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pop.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:30:31 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/23 11:28:36 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

void	ft_files_pop(t_files **files)
{
	t_files	*top;

	if (!files || !*files)
		return ;
	top = *files;
	*files = top->next;
	if (*files)
		(*files)->prev = NULL;
	top->next = NULL;
	free_and_null((void **)&top->file);
	free_and_null((void **)&top);
}

void	pop_to_limiter(t_stack **info_cmd)
{
	while (*info_cmd && (*info_cmd)->token != PIPE)
		ft_stack_pop(info_cmd);
	ft_stack_pop(info_cmd);
}

void	pop_to_limiter_file(t_files **file)
{
	while (*file && (*file)->token != PIPE)
		ft_files_pop(file);
	ft_files_pop(file);
}

void	pop_to_here_doc(t_here_doc **here_doc)
{
	while (*here_doc && (*here_doc)->last_limiter != 1)
		pop_here_doc(here_doc);
	pop_here_doc(here_doc);
}
