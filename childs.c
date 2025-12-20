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

int	new_child()
{
	pid_t	id1;

	id1 = fork();
	if (id1 == -1)
		return (perror("fork"), 1);
	else if (id1 == 0)
	{
		printf("i'am the child\n");
	}
	else
	{
		printf("i'am the parent\n");
	}
	
}

int	find_child()
{

}