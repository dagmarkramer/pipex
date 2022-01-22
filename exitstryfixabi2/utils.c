/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/14 17:44:09 by dkramer       #+#    #+#                 */
/*   Updated: 2022/01/22 15:04:49 by dkramer       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "libft/libft.h"
#include "pipex.h"
#include <fcntl.h>
#include <errno.h>

void	ft_execute(t_pipex *pipex, char **newenv, char *argv)
{
	int		i;
	char	*pathjoined;

	i = -1;
	// pipex->cmd++;
	printf("%s\n", pipex->args[0]);
	printf("%s\n", pipex->args[1]);
	// exit(7);
	
	while (pipex->path2d[i + 1])
	{
		i++;
		pathjoined = ft_strjoin(pipex->path2d[i], "/");
		if (!pathjoined)
			exit(EXIT_FAILURE);
		pathjoined = ft_strjoin(pathjoined, pipex->ls);
		if (!pathjoined)
			exit(EXIT_FAILURE);
		execve(pathjoined, &argv, newenv);
	}
	
	// ft_putendl_fd("hi", 2);
	// if (cpid == 0)
	exit (127);
	// else
	// 	exit (EXIT_SUCCESS);
	// exit (2);
	// errno = 127;
	// perror("");
	// printf("\n%d\n", pipex->cpid);
	// if (pipex->cpid == 0)

	// return ;
}

void	getpath(char **newenv, t_pipex *pipex)
{
	int		i;
	char	**split;

	i = 0;
	while (newenv[i])
	{
		if (ft_strnstr(newenv[i], "PATH=", ft_strlen(newenv[i])))
		{
			split = ft_split(newenv[i], '=');
			if (!split)
				exit(EXIT_FAILURE);
			pipex->path = split[1];
		}
		i++;
	}
	free (split[0]);
	// free (split[1]);
}

void	getpathoptions(char **argv, int argint, t_pipex *pipex, char **newenv)
{
	// pipex->split = ft_calloc(1, sizeof(char *) * 4);
	pipex->split = ft_split(argv[argint], ' ');
	if (!pipex->split)
		exit(EXIT_FAILURE);
	pipex->ls = ft_strdup(pipex->split[0]);
	if (!pipex->ls)
		exit(EXIT_FAILURE);
	pipex->options = NULL;
	if (pipex->split[1])
	{
		pipex->options = ft_strdup(pipex->split[1]);
		if (!pipex->options)
			exit(EXIT_FAILURE);
	}
	
	pipex->extraoptions = NULL;

	if (pipex->split[2])
	{
		pipex->extraoptions = pipex->split[2];
	
	
	}
		
	free (pipex->split[0]);
	free (pipex->split[1]);
	free (pipex->split);
	getpath(newenv, pipex);
	pipex->path2d = ft_split(pipex->path, ':');
	if (!pipex->split)
		exit(EXIT_FAILURE);
}
