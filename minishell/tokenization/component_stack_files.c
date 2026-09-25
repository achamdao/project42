/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component_stack_files.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achamdao <achamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 11:52:19 by achamdao          #+#    #+#             */
/*   Updated: 2025/04/23 19:20:47 by achamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/minishell.h"

t_files	*add_new_file(char *file, short token)
{
	t_files	*newfile;

	newfile = malloc(sizeof(t_files));
	if (!newfile)
		return (NULL);
	newfile->file = ft_strdup(file);
	if (!newfile->file)
	{
		free(newfile);
		return (NULL);
	}
	newfile->token = token;
	newfile->next = NULL;
	newfile->prev = NULL;
	return (newfile);
}

t_files	*filelst_last(t_files *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	filelst_add_back(t_files **lst, t_files *new)
{
	t_files	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = filelst_last(*lst);
	last->next = new;
	new->prev = last;
}

char	push_file(t_files **oldlist, char *file, short token)
{
	t_files	*newfile;

	newfile = add_new_file(file, token);
	if (!newfile)
		return (FAILER);
	filelst_add_back(oldlist, newfile);
	return (0);
}

void	ft_files_clear(t_files **files)
{
	t_files	*tmp;

	if (!files)
		return ;
	while ((*files))
	{
		tmp = (*files)->next;
		free((*files)->file);
		(*files)->file = NULL;
		free((*files));
		(*files) = tmp;
	}
	*files = NULL;
}
