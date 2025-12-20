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
	// if (pipex->all_path)
	// 	free_tab(pipex->all_path);
	if (pipex->path1)
		free(pipex->path1);
	if (pipex->path2)
		free(pipex->path2);
	if (pipex->true_path1)
		free(pipex->true_path1);
	// if (pipex->fd)
	// 	close(pipex->fd);
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

int	set_fd(t_pipex *pipex, char **av)
{
	pipex->file1 = av[1];
	pipex->oldfd1 = open(pipex->file1, O_RDONLY, 0644);
	if (pipex->oldfd1 == -1)
		return (perror("open"), 1);
	pipex->newfd1 = dup2(pipex->oldfd1, 0);
	if (pipex->newfd1 == -1)
		return (perror("dup2"), 1);
	pipex->file2 = av[5];
	pipex->oldfd2 = open(pipex->file1, O_RDONLY, 0644);
	if (pipex->oldfd2 == -1)
		return (perror("open"), 1);
	pipex->newfd2 = dup2(pipex->oldfd2, 1);
	if (pipex->newfd2 == -1)
		return (perror("dup2"), 1);
	pipex->pipedes[0] = pipex->newfd1;
	pipex->pipedes[1] = pipex->newfd2;
	return (0);
}
