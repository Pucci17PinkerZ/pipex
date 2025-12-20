/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfiora-d <nfiora-d@student.42.f            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:18:34 by nfiora-d          #+#    #+#             */
/*   Updated: 2025/12/16 17:32:55 by nfiora-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	new_child(t_pipex *pipex, char **envp)
{
	pid_t	id;

	pipe(&pipex->pipedes);
	id = fork();
	if (id == -1)
		return (perror("fork"), 1);
	else if (id == 0)
	{
		if (child_do(pipex, envp))
			return (1);
	}
	else
	{
		if (parent_do(pipex, envp))
			return (1);
	}
	return (0);
}


int	child_do(t_pipex *pipex, char **envp)
{
	close(pipex->oldfd1);
	close(pipex->oldfd2);
	if (execve(pipex->true_path1, pipex->cmd_args, envp))
		return (1);
	
}

int	parent_do(t_pipex *pipex, char **envp)
{
	close(pipex->newfd1);
	dup2(pipex->newfd2, 0);
	if (execve(pipex->true_path2, pipex->cmd2_args, envp))
	return (1);
}