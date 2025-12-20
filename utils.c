/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfiora-d <nfiora-d@student.42.f            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:18:34 by nfiora-d          #+#    #+#             */
/*   Updated: 2025/12/16 17:32:55 by nfiora-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean_exit(t_pipex *pipex)
{
	if (pipex->cmd_args)
		free_tab(pipex->cmd_args);
	if (pipex->all_path)
		free_tab(pipex->all_path);
	if (pipex->path1)
		free(pipex->path1);
	if (pipex->path2)
		free(pipex->path2);
	if (pipex->true_path1)
		free(pipex->true_path1);
	return ;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return ;
}

