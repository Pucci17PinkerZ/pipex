/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfiora-d <nfiora-d@student.42.f            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 17:18:34 by nfiora-d          #+#    #+#             */
/*   Updated: 2025/12/16 17:32:55 by nfiora-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		ft_printf("way of use -> ./pipex <infile>"
			" \"cmd1\" \"cmd2\" <outfile>\n");
		return (1);
	}
	if (test_input(av))
		return (perror("test_input"), 1);
	ft_bzero(&pipex, sizeof(t_pipex));
	if (set_fd(&pipex, av))
		return (perror("set_fd"), 1);
	if (new_child(&pipex, av, envp))
		return (clean_exit(&pipex), 1);
	waitpid(pipex.child1, NULL, 0);
	waitpid(pipex.child2, NULL, 0);
	return (clean_exit(&pipex), 0);
}

