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
	if (pipex->cmd2_args)
		free_tab(pipex->cmd2_args);
	if (pipex->path1)
		free(pipex->path1);
	if (pipex->path2)
		free(pipex->path2);
	if (pipex->true_path1)
		free(pipex->true_path1);
	if (pipex->true_path2)
		free(pipex->true_path2);
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
		perror("open");
	pipex->file2 = av[4];
	pipex->oldfd2 = open(pipex->file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipex->oldfd2 == -1)
		return (perror("open"), 1);
	return (0);
}

int	test_input(char **av)
{
	if (!av[1])
		return (1);
	if (!av[2])
		return (1);
	if (!av[3])
		return (1);
	if (!av[4])
		return (1);
	return (0);
}

int	fd_close(t_pipex *pipex)
{
	if (pipex->oldfd1 != -1)
		close(pipex->oldfd1);
	close(pipex->oldfd2);
	close(pipex->newfd1);
	close(pipex->newfd2);
	close(pipex->pipedes[0]);
	close(pipex->pipedes[1]);
	return (0);
}
