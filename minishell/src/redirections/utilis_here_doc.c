/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilis_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaouchi <mjaouchi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:13:31 by mjaouchi          #+#    #+#             */
/*   Updated: 2025/04/29 12:22:13 by mjaouchi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../header/minishell.h"

int	lstsize_herdoc(t_here_doc *lst, char *limiter)
{
	int	i;

	i = 0;
	while (lst && ft_strcmp(limiter, lst->limeter))
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

char	*read_line_from_user(void)
{
	return (readline("> "));
}

int	is_limiter_reached(char *line, t_here_doc **here_doc)
{
	char	is_final;

	is_final = 0;
	if (!ft_strcmp(line, (*here_doc)->limeter) || line == NULL)
	{
		if (*here_doc)
			is_final = (*here_doc)->last_limiter;
		*here_doc = pop_here_doc(here_doc);
		if (is_final)
			return (1);
	}
	return (0);
}

int	expand_and_write_line(char *line, int file_fd)
{
	if (line == NULL && ft_strcmp("\0", line))
		return (FAILER);
	if (ft_putendl_fd(line, file_fd) == FAILER)
		return (FAILER);
	return (0);
}

int	reopen_temp_file(char *file_tmp)
{
	int	fd;

	fd = open(file_tmp, O_RDONLY, 0777);
	if (fd == FAILER)
		perror("open: ");
	return (fd);
}
