/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dkramer <dkramer@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/14 17:44:09 by dkramer       #+#    #+#                 */
/*   Updated: 2022/01/18 11:19:42 by dkramer       ########   odam.nl         */
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

void	ft_execute(t_pipex *pipex, char **newenv)
{
	int		i;
	char	*pathjoined;

	i = -1;
	// pipex->cmd++;
	while (pipex->path2d[i + 1])
	{
		i++;
		pathjoined = ft_strjoin(pipex->path2d[i], "/");
		if (!pathjoined)
			exit(EXIT_FAILURE);
		pathjoined = ft_strjoin(pathjoined, pipex->ls);
		if (!pathjoined)
			exit(EXIT_FAILURE);
		execve(pathjoined, pipex->args, newenv);
	}
	// int	status;
	// waitpid(pipex->cpid, &status, 0);
	// if (WIFEXITED(status))
	// 	exit(status);
	// perror ("");
	exit (127);
	// exit (EXIT_FAILURE);
	// perror("");
	// printf("\n%d\n", pipex->cpid);
	// if (pipex->cpid == 0)
	// exit(127);
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
	free (split[1]);
}

void	getpathoptions(char **argv, int argint, t_pipex *pipex, char **newenv)
{
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
	free (pipex->split[0]);
	free (pipex->split[1]);
	free (pipex->split);
	getpath(newenv, pipex);
	pipex->path2d = ft_split(pipex->path, ':');
	if (!pipex->split)
		exit(EXIT_FAILURE);
}
