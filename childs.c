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
	if (pipe(pipex->pipedes))
		return (perror("pipe"), 1);
	pipex->child1 = fork();
	if (pipex->child1 == -1)
		return (perror("fork"), 1);
	else if (pipex->child1 == 0)
	{
		if (child_do(pipex, envp))
			return (perror("child_do"), 1);
	}
	else
	{
		if (parent_do(pipex, envp))
			return (perror("parent _do"), 1);
	}
	return (0);
}

int	child_do(t_pipex *pipex, char **envp)
{
			printf("child1 existe\n");
	if ((dup2(pipex->oldfd1, 0)) == -1)
		return (perror("dup2.1"), 1);
	if ((dup2(pipex->pipedes[1], 1)) == -1)
		return (perror("dup2.2"), 1);
// 2. NETTOYAGE
    // Je ferme le bout de lecture (inutile pour moi)
    close(pipex->pipedes[0]);
    
    // Je ferme le bout d'écriture (j'ai ma copie sur le 1)
    close(pipex->pipedes[1]);
    
    // Je ferme le infile
    close(pipex->oldfd1);
	if (execve(pipex->true_path1, pipex->cmd_args, envp))
		return (1);
	return (0);
}

int	parent_do(t_pipex *pipex, char **envp)
{
	pipex->child2 = fork();
	if (pipex->child2 == -1)
		return (perror("fork"), 1);
	else if (pipex->child2 == 0)//child2
	{
		printf("child2 existe\n");
		if ((dup2(pipex->pipedes[0], 0)) == -1)
			return (perror("dup2.1"), 1);
		if ((dup2(pipex->oldfd2, 1)) == -1)
			return (perror("dup2.2"), 1);
		close(pipex->pipedes[1]); 
		
		// Je ferme aussi le bout de lecture (j'ai déjà ma copie sur le 0)
		close(pipex->pipedes[0]);
		
		// Je ferme le fichier (j'ai déjà ma copie sur le 1)
		close(pipex->oldfd2);
		if (execve(pipex->true_path2, pipex->cmd2_args, envp))
			return (perror("execve"), 1);
	}
	else
		fd_close(pipex);
	return (0);
}

int	fd_close(t_pipex *pipex)
{
	if (pipex->oldfd1 != -1)
	{
		close(pipex->oldfd1);
		pipex->oldfd1 = -1;
	}
	if (pipex->oldfd2 != -1)
	{
		close(pipex->oldfd2);
		pipex->oldfd2 = -1;
	}
	if (pipex->newfd1 != -1)
	{
		close(pipex->newfd1);
		pipex->newfd1 = -1;
	}
	if (pipex->newfd2 != -1)
	{
		close(pipex->newfd2);
		pipex->newfd2 = -1;
	}
	if (pipex->pipedes[0] != -1)
	{
		close(pipex->pipedes[0]);
		pipex->pipedes[0] = -1;
	}
	if (pipex->pipedes[1] != -1)
	{
		close(pipex->pipedes[1]);
		pipex->pipedes[1] = -1;
	}
	return (0);
}
